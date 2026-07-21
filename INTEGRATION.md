# Integrating with Pie UI

Pie UI exposes a small cross-addon API over the **Nexus event bus** (`Events_Raise` /
`Events_Subscribe`). It is an **optional dependency**: if Pie UI isn't installed, raising one of
these events simply does nothing, so your addon never needs a hard dependency on it.

All events are plain Nexus events — no shared headers or linking required. (The event-name constants
are also published in [`PieUiAPI.h`](PieUiAPI.h) if you'd rather include them than hard-code strings.)

A generated reference for that header — every event, its payload and direction, plus the theme
struct — is browsable at **<https://pieorcake.github.io/pie_ui/>**.

---

## Open a chat link (perform its native action)

Hand Pie UI any GW2 chat link and it performs that link's native action on the game thread — exactly
as clicking the same link in chat would. Nothing here travels the player or changes account state;
every action is a read-only window the user could open themselves:

| Chat link | What Pie UI does |
|---|---|
| waypoint / PoI | opens and pans the world map to it (you still click to travel) |
| wardrobe template | opens the native Wardrobe Template window |
| build template | opens the native build window |
| item / skin / outfit | opens the native wardrobe preview |

| | |
|---|---|
| **Event** | `EV_PIEUI_OPEN_CHATLINK` |
| **Direction** | your addon **raises** it; Pie UI listens |
| **Payload** | a pointer to a null-terminated `"[&...]"` chat-link string |
| **Reply** | none |

Pie UI decodes the link type and id itself, so you only need the link string — no decoding on your
side. Any unsupported, malformed, or non-terminated input is ignored silently.

```cpp
// `code` is any chat link, e.g. a waypoint "[&BKgBAAA=]" or a wardrobe template "[&Cg...]".
// Nexus delivers events synchronously, so a pointer to a local string is valid for the call.
std::string code = "[&BKgBAAA=]";
APIDefs->Events_Raise("EV_PIEUI_OPEN_CHATLINK", (void*)code.c_str());
```

That single call is all you need. If Pie UI is present it performs the action; if not, nothing happens.

> **Legacy:** an older map-only event, `EV_PIEUI_OPEN_MAP`, still works (it acts only on
> waypoint/PoI links). New callers should prefer `EV_PIEUI_OPEN_CHATLINK`.

---

## Match Pie UI's theme (colour palette)

Pie UI broadcasts its **entire active ImGui colour palette** so your addon can match its look with no
per-control mapping. Pie sends it on its own load, whenever the user changes the theme or the trim
colour, and in reply to a request.

| | |
|---|---|
| **Event** | `EV_PIEUI_THEME` |
| **Direction** | Pie UI **raises** it; your addon subscribes |
| **Payload** | a pointer to a `PieUiTheme` (see below) |
| **When** | on Pie UI load, on theme/trim change, and in reply to `EV_PIEUI_REQUEST_THEME` |

| | |
|---|---|
| **Event** | `EV_PIEUI_REQUEST_THEME` |
| **Direction** | your addon **raises** it; Pie UI replies with `EV_PIEUI_THEME` |
| **Payload** | none |
| **Use** | pull the current palette on demand (e.g. on your own load) without waiting for a change |

The payload is a flat POD (declared in [`PieUiAPI.h`](PieUiAPI.h)):

```c
typedef struct PieUiTheme {
    uint32_t version;      // = PIEUI_THEME_VERSION; ignore a struct whose version you don't understand
    uint32_t accent;       // Pie's signature highlight (trim-aware); NOT an ImGuiCol
    uint32_t count;        // number of valid entries in colors[] (Pie's ImGuiCol_COUNT)
    uint32_t colors[96];   // IM_COL32 values, indexed by the standard ImGuiCol_ enum
} PieUiTheme;
```

- `colors` is indexed by the standard `ImGuiCol_` enum — the vocabulary every Nexus addon already
  shares (all Nexus addons use Nexus's ImGui, so the indices line up). Copy `colors[i]` straight into
  your `ImGuiStyle.Colors[i]` for the first `min(count, ImGuiCol_COUNT)` entries. A version skew at
  worst leaves a few trailing controls at your own defaults — never corruption.
- `accent` is **not** an `ImGuiCol`; it's Pie's trim-aware highlight colour for your own custom drawing
  (underlines, custom widgets, highlights).
- All colours are `IM_COL32` values packed `0xAABBGGRR` (byte 0 = R, 1 = G, 2 = B, 3 = A). Unpack with
  `ImGui::ColorConvertU32ToFloat4` for an `ImVec4`. A non-C++ consumer mirrors the struct as a
  `#[repr(C)]` / packed record and unpacks the bytes itself.

The pointer is valid **only for the duration of the synchronous `EV_PIEUI_THEME` call** — copy what
you need inside your handler; don't retain the pointer.

```cpp
ImGuiStyle g_pieStyle;        // your saved copy of Pie UI's palette
ImU32      g_pieAccent = 0;   // Pie's highlight, for your own drawing

void OnPieTheme(void* payload) {
    auto* t = static_cast<const PieUiTheme*>(payload);
    if (!t || t->version != PIEUI_THEME_VERSION) return;   // unknown version → ignore
    const uint32_t n = t->count < ImGuiCol_COUNT ? t->count : ImGuiCol_COUNT;
    for (uint32_t i = 0; i < n; ++i)
        g_pieStyle.Colors[i] = ImGui::ColorConvertU32ToFloat4(t->colors[i]);
    g_pieAccent = t->accent;
}

// In your AddonLoad, after APIDefs is set:
APIDefs->Events_Subscribe("EV_PIEUI_THEME", OnPieTheme);
APIDefs->Events_Raise("EV_PIEUI_REQUEST_THEME", nullptr);   // pull the current palette now
```

Then push `g_pieStyle.Colors` onto ImGui around the widgets you want to match Pie UI, and use
`g_pieAccent` for your own accents.

### Picking a slot for custom-drawn decorations

If you go beyond restyling ImGui widgets and draw your **own** decorations (an `ImDrawList` band, a
panel fill, `TextColored`), pick the palette slot by its *semantic role*, not its name — Pie's palette
has a character the raw array doesn't advertise:

- **All Pie themes are dark.** `WindowBg` / `ChildBg` / `TitleBg` / `FrameBg` are near-black in nearly
  every theme (Nyan Cat is the loud exception); only `accent` swings strongly per theme. Map a custom
  accent band or panel to a background slot and it looks static/grey across themes — don't.
- **`accent`** is the bright signature trim — use it for thin highlights (underlines, active
  indicators, small custom widgets), not large fills.
- **`ImGuiCol_Button`** is the best slot for a solid themed band or panel: Pie's resting button is a
  dark, *saturated* dimmed-accent — it carries real hue as a large fill while staying dark enough for
  white/near-white text to sit on it legibly.
- **`ImGuiCol_Tab*`** are deliberately muted and desaturated (correct for real tab strips). Stretched
  into a large solid header band they read as washed-out grey — not a good source for big fills.

> **Read timing.** When you read a palette colour for your *own* drawing, read it from the copied
> `PieUiTheme` struct — **not** from `ImGui::GetStyle()`, unless you've already applied Pie's palette
> into that style earlier in the same frame. Computing your custom-draw colours *before* you push the
> Pie palette makes `GetStyle()` return ImGui's stale defaults (e.g. the pale, semi-transparent default
> `ImGuiCol_Button`) → a washed-out result. Reading straight from the struct sidesteps the ordering.

---

## Detecting whether Pie UI is loaded (optional)

You don't have to detect Pie UI to use the API above — raising the event when Pie UI is absent is a
harmless no-op. But if you want to show or hide UI based on its presence (e.g. only offer an
"open in Pie UI" action when it can actually work), use this handshake:

| Event | Direction | Meaning |
|---|---|---|
| `EV_PIE_UI_PING` | your addon **raises** | "is Pie UI loaded?" — Pie UI replies with `EV_PIE_UI_READY` |
| `EV_PIE_UI_READY` | Pie UI **raises** | Pie UI announcing itself (on its load, and in reply to a ping) |

Recommended flow: on your addon's load, **subscribe** to `EV_PIE_UI_READY`, then **raise**
`EV_PIE_UI_PING` (in case Pie UI loaded first and you missed its initial announcement). Latch
"present" when you receive `EV_PIE_UI_READY`.

```cpp
void OnPieReady(void*) { g_pieUiPresent = true; }

// In your AddonLoad, after APIDefs is set:
APIDefs->Events_Subscribe("EV_PIE_UI_READY", OnPieReady);
APIDefs->Events_Raise("EV_PIE_UI_PING", nullptr);
```

---

## Notes

- **No hard dependency.** Treat Pie UI as optional throughout — same pattern as any other Nexus
  service. Everything degrades to "do nothing" when it's absent.
- **Payload lifetime.** Nexus delivers events synchronously, so a pointer to a local/stack string is
  safe for the duration of the `Events_Raise` call.

Questions or a request for another integration point? Open an issue on the repo.

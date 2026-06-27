# Integrating with Pie UI

Pie UI exposes a small cross-addon API over the **Nexus event bus** (`Events_Raise` /
`Events_Subscribe`). It is an **optional dependency**: if Pie UI isn't installed, raising one of
these events simply does nothing, so your addon never needs a hard dependency on it.

All events are plain Nexus events — no shared headers or linking required. (The event-name constants
are also published in [`PieUiAPI.h`](PieUiAPI.h) if you'd rather include them than hard-code strings.)

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

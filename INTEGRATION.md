# Integrating with Pie UI

Pie UI exposes a small cross-addon API over the **Nexus event bus** (`Events_Raise` /
`Events_Subscribe`). It is an **optional dependency**: if Pie UI isn't installed, raising one of
these events simply does nothing, so your addon never needs a hard dependency on it.

All events are plain Nexus events — no shared headers or linking required.

---

## Open / pan the world map to a waypoint or PoI

Ask Pie UI to open the world map and pan it to a waypoint / Point of Interest, exactly as clicking a
native waypoint chat link does. The user still clicks the point to travel — **Pie UI never travels
for you**, and it makes no change to game state beyond opening and panning the map.

| | |
|---|---|
| **Event** | `EV_PIEUI_OPEN_MAP` |
| **Direction** | your addon **raises** it; Pie UI listens |
| **Payload** | a pointer to a null-terminated `"[&...]"` waypoint/PoI chat-link string |
| **Reply** | none |

Pie UI decodes the PoI id from the chat link itself, so you only need the link string — no decoding
on your side. A non-map or malformed link is ignored silently.

```cpp
// `code` is a waypoint/PoI chat link, e.g. "[&BKgBAAA=]".
// Nexus delivers events synchronously, so a pointer to a local string is valid for the call.
std::string code = "[&BKgBAAA=]";
APIDefs->Events_Raise("EV_PIEUI_OPEN_MAP", (void*)code.c_str());
```

That single call is all you need. If Pie UI is present it opens + pans the map; if not, nothing
happens.

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

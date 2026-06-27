#pragma once
//
// Pie UI — public cross-addon API (Nexus named events)
// =====================================================
// This header is the CONTRACT other Nexus addons implement to talk to Pie UI.
// It is the single source of truth for the event names; Pie includes it too.
// Mirror it to the public repo (PieOrCake/pie_ui) so addon authors can grab it.
//
// All Pie UI cross-addon comms are plain Nexus named events
// (APIDefs->Events_Raise / Events_Subscribe). Pie owns ALL game-memory access
// and game calls: a calling addon only RAISES an event with a chat-link string
// and never touches game memory itself.
//
// Bump PIEUI_API_VERSION on any breaking change to a contract below.
//
#define PIEUI_API_VERSION 1

// --- Discovery handshake (optional) ----------------------------------------
// A caller MAY probe for Pie before using the API; detection is OPTIONAL —
// raising an action event when Pie is absent simply goes nowhere (harmless).
//   Caller raises:  EV_PIE_UI_PING   (payload: none)
//   Pie replies:    EV_PIE_UI_READY  (payload: none) — also raised on Pie load
#define EV_PIE_UI_PING   "EV_PIE_UI_PING"
#define EV_PIE_UI_READY  "EV_PIE_UI_READY"

// --- Open a chat link (perform its native action) --------------------------
// Caller raises EV_PIEUI_OPEN_CHATLINK with a pointer to a NUL-terminated GW2
// chat-link string (the "[&...]" base64 form). Pie decodes it and performs the
// link's native action on the game thread. Nothing here travels the player or
// changes account state; every action is a read-only window the user could
// trigger by clicking the same link in chat:
//   waypoint / PoI    -> open + pan the world map to it (no auto-travel)
//   wardrobe template -> open the native Wardrobe Template window
//   build template    -> open the native build-template window
//   item / skin / outfit -> open the native wardrobe preview
// Any other, malformed, over-long, or non-NUL-terminated input is IGNORED
// silently. Pie copies the string immediately; the caller need not keep it
// alive past the raise. Example (caller side):
//   const char* code = "[&BkgAAAA...]";
//   APIDefs->Events_Raise(EV_PIEUI_OPEN_CHATLINK, (void*)code);
#define EV_PIEUI_OPEN_CHATLINK "EV_PIEUI_OPEN_CHATLINK"

// --- Legacy alias (map only) -----------------------------------------------
// Predates EV_PIEUI_OPEN_CHATLINK. Identical handling but acts ONLY on
// waypoint/PoI links (a non-map link handed here is ignored). Kept for
// back-compat; new callers should use EV_PIEUI_OPEN_CHATLINK.
#define EV_PIEUI_OPEN_MAP "EV_PIEUI_OPEN_MAP"

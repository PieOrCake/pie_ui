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

// --- Theme colours (Pie broadcasts its active palette) ---------------------
// Pie shares its current UI palette so other addons can match its look. Pie
// RAISES EV_PIEUI_THEME (payload: pointer to a PieUiTheme) on Pie load, whenever
// the user changes the theme or the trim colour, and in reply to a request.
// A caller SUBSCRIBES to EV_PIEUI_THEME and copies the struct inside its handler
// (Nexus delivers synchronously; the pointer is valid only for that call). A
// caller MAY raise EV_PIEUI_REQUEST_THEME at any time (e.g. on its own load) to
// pull the current palette without waiting for a change.
//
// Pie ships its ENTIRE ImGui colour palette so a consumer matches every control
// exactly, with no per-control mapping. `colors` is indexed by the standard
// ImGuiCol_ enum (the shared vocabulary every Nexus addon already uses): copy
// colors[i] into your ImGuiStyle.Colors[i] for the common prefix. `count` is the
// ImGuiCol_COUNT Pie was built against — copy min(count, your ImGuiCol_COUNT).
// (ImGui appends, rarely reorders, ImGuiCol_ entries, and Nexus addons share
// Nexus's ImGui, so index alignment holds; a version skew at worst leaves a few
// trailing controls at your own defaults, never corruption.)
//
// `accent` is Pie's signature highlight (trim-aware) and is NOT an ImGuiCol —
// use it for your OWN custom drawing (underlines, custom widgets, highlights).
//
// PICKING A SLOT FOR CUSTOM DRAWING: if you draw your OWN decorations (ImDrawList
// bands/panels, TextColored) rather than only restyling ImGui widgets, choose by the
// slot's semantic role, not its name — the palette has a character the raw array hides:
//   - All Pie themes are DARK. Window/Child/Title/Frame backgrounds are near-black in
//     nearly every theme (Nyan Cat is the loud exception); only `accent` swings strongly
//     by theme. A custom band/panel mapped to a background slot looks static/grey — don't.
//   - `accent` = the bright trim: thin highlights only (underlines, active indicators).
//   - ImGuiCol_Button = best slot for a solid themed band/panel: a dark, SATURATED
//     dimmed-accent that reads richly as a large fill yet stays dark enough for white text.
//   - ImGuiCol_Tab* are deliberately muted/desaturated (right for tab strips); as a large
//     solid band they read washed-out grey — not a good source for big fills.
// READ TIMING: read a slot for your own drawing from the COPIED PieUiTheme struct, NOT
// from ImGui::GetStyle() — unless you already applied Pie's palette into that style earlier
// THIS frame. Reading GetStyle() first returns ImGui's stale default (e.g. the pale,
// semi-transparent default ImGuiCol_Button) → washed out. The struct sidesteps the ordering.
//
// All colours are ImGui IM_COL32 values packed 0xAABBGGRR (byte0=R,1=G,2=B,3=A);
// unpack to ImVec4 for ImGuiStyle. (A non-C++/Rust consumer mirrors PieUiTheme as
// a #[repr(C)] struct and unpacks the bytes itself.)
// Check `version` and ignore a struct whose version you do not understand.
#define EV_PIEUI_THEME         "EV_PIEUI_THEME"
#define EV_PIEUI_REQUEST_THEME "EV_PIEUI_REQUEST_THEME"

// Bump only when the PieUiTheme LAYOUT changes (not when a colour value changes).
#define PIEUI_THEME_VERSION 1

// Fixed cap so PieUiTheme stays a flat, stable-size POD. Comfortably above
// ImGuiCol_COUNT (~58); `count` reports how many entries are actually valid.
#define PIEUI_THEME_MAX_COLORS 96

#include <stdint.h>
typedef struct PieUiTheme {
    uint32_t version;                        // = PIEUI_THEME_VERSION
    uint32_t accent;                         // signature highlight (trim-aware); NOT an ImGuiCol
    uint32_t count;                          // valid entries in colors[] (Pie's ImGuiCol_COUNT)
    uint32_t colors[PIEUI_THEME_MAX_COLORS]; // IM_COL32, indexed by ImGuiCol_
} PieUiTheme;

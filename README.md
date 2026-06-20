# Pie UI

A [Raidcore Nexus](https://raidcore.gg/Nexus) addon for Guild Wars 2 that replaces native HUD elements with configurable, better-looking alternatives. Pie UI only **reads** game memory — it never writes to or modifies the game. Actions you trigger yourself (casting a clicked skill, sending a chat message, opening the map from a link) use the game's normal input and interface paths, not memory edits or automation. Pie UI performs memory reading — see the [Addon Policy](#addon-policy) for how it handles game data and stays within ArenaNet's guidelines.

## AI Notice

This addon has been largely created using Claude. I understand that some folks have a moral, financial or political objection to creating software using an LLM. I just wanted to make a useful tool for the GW2 community, and this was the only way I could do it.

If an LLM creating software upsets you, then perhaps this repo isn't for you. Move on, and enjoy your day.

## Screenshots

![Player vitals and skill bars](screenshots/vitals_hotbars.png)

![Squad and party frames](screenshots/squad.png)

![Quick-toggle bar: show or hide each Pie UI element and its native counterpart](screenshots/ui_toggles.png)

![Boon and condition duration bars](screenshots/boons.png)

![Chat box: item links with a live tooltip, class icons and tabs](screenshots/chatbox2.png)

![Chat box: waypoint links, unread-count tabs and the send bar](screenshots/chatbox3.png)

![The Pie UI chat box alongside the native chat](screenshots/chatbox.png)

## Features

### Player vitals
- HP, barrier, and endurance in four styles: **horizontal bar**, **vertical bar**, **reticle arcs**, and **reticle ring**.
- Live HP/endurance/barrier numbers with a 3-stop HP colour gradient (green → amber → red).
- Barrier shown as a separate strip or overlaid — always visible, even at full HP.
- **Downed warning:** the HP bar turns red with a deep-red border the moment you're downed, whatever your health was.
- **Mount & glider aware:** tracks mount dodge endurance (with per-mount dodge segments) while mounted, the Skyscale's flight stamina, and your **glider stamina** while gliding.
- Every colour is configurable.

### Skill bars
- Live weapon and utility skill icons that follow weapon swaps, kits, transforms, and bundles automatically.
- **Cooldown sweeps** with countdown numbers and grey-out.
- **Click-to-cast** — click a skill to fire it; press-and-hold works for channelled skills (e.g. Siege Turtle jets).
- Keybind labels on each slot, fully rebindable in-app.
- Activation flash and combo/flip animations, plus **theme-coloured slots** with an accent cooldown sweep and an activation glow.
- A **weapon-swap / stow button** that mirrors the native one, with its recharge (and the right behaviour per profession).
- Separate, independently placeable groups for weapons and utilities.

### Profession & pet bars
- **Profession bar** (F1–F7) that auto-fits your specialisation's mechanics.
- **Elementalist attunement highlight** — the active element's F-slot is enlarged with a thick, element-coloured border, matching the native UI.
- **Pet / mech control bar** for Rangers and Mechanists: live pet skills with cooldowns, a creature HP bar, and command buttons (attack, return, swap, combat toggle).
- Optional pet HP readout on the reticle HUD, beside your own health.

### Profession resource bar
A positionable bar for your specialisation's core resource — smooth fill or segmented pips, with a configurable colour per class. Currently covers:
- **Necromancer** — Life Force (all specs).
- **Mesmer** — clones, **Virtuoso** blades, and **Troubadour** notes.
- **Guardian** — **Firebrand** tome pages and **Luminary**'s Radiant Forge.
- **Revenant** — energy, with a recovery/drain **rate indicator**; plus a native-style **legend bar** that shows both legends side by side, the **swap cooldown** on the active legend, and the F1 swap indicator.
- **Conduit** — **Affinity** stacks, shown as pulsing pips beside the energy bar.
- **Warrior** — **Adrenaline**, as segmented bars.
- **Thief** — **Initiative** (all specs), shown as native-style diamond pips; **Specter** adds a **Shadow Force** bar and **Deadeye** a segmented **Malice** bar below the pips.
- **Ranger** — **Galeshot** arrow charges.

### Mounted hotbar
- Per-mount skill layouts with the correct icons and keybind labels, shown automatically while mounted.

### Boon, condition & effect bars
- Three independently placeable sections — **boons**, **conditions**, and **everything else** — showing your live effects.
- Per-section display: icons only, duration bars only, or icons with bars.
- Stack counts, live countdown timers, orientation and wrapping all configurable.

### Target frame
- A positionable bar showing your current target's health percentage.
- **Attitude colouring** — the bar is tinted by the target's disposition (hostile / neutral / friendly), and turns hostile the moment you engage a neutral mob. All colours are configurable.
- **Defiance / break bar** that mirrors the native one: **blue** when intact and ready to break, **orange/gold** while it regenerates back to full — with its own colour choosers.
- Also works on **objects and gadgets** that have health (siege, cannons, attackable structures).

### Squad & party frames
- A movable, resizable roster panel for your party or squad, styled to match the rest of Pie UI.
- Squads are grouped into colour-coded **subgroup columns** (with labels); pick a **list** or native-style **grid** layout, and let long rosters **scroll** or **wrap into extra columns**.
- Each member shows their **class / elite-spec icon**, **name**, and **commander / lieutenant tag**.
- **Live health bars** for members on your map, with a configurable **high → mid → low** colour gradient (or profession colours), a **downed** state, and a **Necromancer shroud** life-force overlay. Out-of-range members show a neutral bar. *(Read-only; health is PvE-only — disabled in WvW / PvP.)*
- Your own row is highlighted, and members in another map instance are dimmed.
- Theme-tinted background with an accent border; configurable cell size, columns, fonts, and colours.

### Minimap
- A clean, positionable minimap with resource-node markers (herb / wood / ore) sized to gather type, plus **Season 3/4 special-node icons** (Winterberries, Difluorite, …).
- **Node-name tooltips** — hover a node to see exactly what it is, named automatically by area (e.g. *Cluster of Desert Herbs* across every desert map).
- **Map service badges** — merchants, crafting stations, banks, the trading post, bounty boards, map-currency collectors, scouts and more, drawn as icons with hover tooltips.
- **Floor / layer system** — follows you between map floors automatically, with a manual floor selector, correct marker layering, and cave / sublevel support.
- **Party / squad dots** — live positions of your group members on the minimap in the native dot style, with a **commander tag**; off-view members clamp to the rim with a direction tick. Toggles and colours configurable.
- Map-completion tinting for mastery insights, pulled live from the GW2 API.

### Bottom-line strip
- A configurable status strip of live readouts: **FPS**, **memory**, **server ping**, **region / map / coordinates**, **character name and class**, **level**, **mount**, **XP**, your **wallet**, and your **active build / gear** names.
- A **clock** showing in-game **Tyrian** time alongside your **local** and **server** time — display one (click to cycle) or **all three at once**, in 12- or 24-hour format.
- **Multi-currency wallet** — pick which currencies the wallet shows (gold plus any others: Karma, Volatile Magic, Bandit Crests, …), each with its own icon and balance.
- Choose which readouts appear, arrange them left / centre / right, and colour each one — with an optional **theme-coloured border**.

### Replacement chat box
- A movable, resizable chat panel with a fully **interactive tab strip**: rename tabs, pick which channels each shows (including guilds G1–G6), drag to reorder, and unread `(N)` badges.
- Rich, clickable lines: **URLs**, **waypoint** links that open and pan the world map, **item** links with name, icon and live vendor/trading-post prices, **skill** links with a full tooltip, and **build template** links that open the native build window.
- Real **guild tags** on guild lines, **class/elite-spec icons** and **commander/lieutenant tags** on party/squad members' messages, and **timestamps** (12/24h).
- Per-channel three-colour styling (name / sender / text) and four font-size presets.
- **Account names on hover** — hover a sender's name to see their account handle (guild, whisper, say and map chat).
- **Sending** built in: an input row with leading slash commands, a channel picker, and **left-click a name to whisper** or right-click for **whisper, add / remove friend, block, and invite to party / squad**.
- A live **character counter** against GW2's 199-character line limit, so a long message is never silently truncated on send.
- Optional **system & emote lines** (the game's yellow notices) shown inline in the chat box.

### Tyrian IM — built-in messenger
- A per-contact whisper messenger (an evolution of the standalone Tyrian IM), with a conversation list, chat bubbles, and a reply box.
- An always-visible **floating icon** that bobs, flashes, and shows an unread badge; click it to jump to your unread conversation.
- Multiple visual **themes**, an optional notification **sound**, and per-conversation history saved to disk.
- Right-click a name in the chat box (or use "Whisper") to open the conversation straight away.

### Quick-toggle bar & native-UI hiding
- One-click **"Hide native …"** toggles in each widget's settings — skill bar (which also covers the F1–F7 profession bar, weapon-swap, XP bar, health globe and native effect icons), chat, target frame, minimap / compass, and party / squad frames — so a Pie UI widget cleanly replaces the game's own.
- A floating, themed **quick-toggle bar** (enable it on the General tab) listing every Pie UI element beside its nearest native counterpart, so you can show or hide either with a single click — with a theme-accent highlight on whatever's currently visible.
- In WvW / PvP the native elements are kept visible automatically (Pie UI's competitive-locked widgets are suppressed there, so you're never left without a HUD).

### General
- A clean settings window (open via keybind, the quick-access tray icon, or the Nexus options panel) with per-subsystem tabs and colour pickers.
- Drag-to-place and resize any widget in unlock mode, with snap-to-grid.
- **Theme-coloured chrome** — widget borders follow the active theme's accent colour for a consistent look across the whole UI.
- **Per-feature opacity** for in-combat and out-of-combat (set to zero to hide a widget entirely).
- **Hide-on-hover** — optionally have a widget fade out for a few seconds while your mouse is over it, so native panels behind it (Hero, Guild, vendors) are visible and clickable.
- Everything hides automatically on loading screens, character select, and the world map.
- Settings persist in a versioned `pieui.json` that survives updates.

## Hiding the native UI

Pie UI draws *replacements*, not overlays that erase the originals — so it can hide the matching native element for you. Each widget's settings tab has a **"Hide native …"** toggle, and the **quick-toggle bar** (General tab) lets you flip every Pie UI element and its native counterpart from one place. Hiding goes through the game's own frame interface, so the addon never touches the render path and stays policy-safe. The native elements are restored automatically in WvW / PvP.

## Addon Policy

Pie UI reads game memory to mirror information Guild Wars 2 already shows you, and triggers actions only through the game's own input and interface paths. It is designed to operate within the guidelines of the Guild Wars 2 [Third-Party Programs](https://help.guildwars2.com/hc/en-us/articles/360013625034-Policy-Third-Party-Programs) and [Macros & Macro Use](https://help.guildwars2.com/hc/en-us/articles/360013762153-Policy-Macros-and-Macro-Use) policies. In areas of ambiguity, development is guided by community consensus and available statements from ArenaNet staff.

### Data Parity

Pie UI never surfaces information you couldn't already get from the native UI:

- **Other players' health** (squad and party frames) is shown only as a bar and, optionally, a whole-number percentage — never a raw current/maximum value.
- **Barrier, boons and conditions** are shown the same way the native frames show them — bar, duration and stacks.
- **Your own** character's detailed readouts (exact resource values and so on) are your own data and are shown in full.

### Mode Restrictions

In competitive zones — PvP and WvW — Pie UI automatically disables its combat-relevant overlays (vitals, hotbars, target frame, resource bars, effect bars, minimap and squad/party frames) and restores the native UI, so it can never give an advantage over other players.

### Memory Access

To avoid providing a ready-made template for cheats, the source code is not public.

### Disclaimer

While every effort is made to keep Pie UI within ArenaNet's current policies, the use of any third-party software is at the sole discretion of the player. The developer of this addon is not responsible for any actions taken against your account. ArenaNet's policies are subject to change without notice; stay informed and decide for yourself whether you are comfortable with the risks of using third-party programs.

## Installation

Requires the [Nexus](https://raidcore.gg/Nexus) host. Copy `PieUI.dll` into your `<Guild Wars 2>/addons/` folder and (re)load it from the Nexus addon list.

**Companion addon (recommended):** chat **item, skill and skin** names and tooltips are resolved by the separate [Decoder Ring](https://github.com/PieOrCake/decoder_ring) addon. Pie UI works fine without it — those links just fall back to generic `[Item]` / `[Skill]` / `[Skin]` labels until Decoder Ring is installed. Waypoint, build-template and URL links work either way.

## Roadmap

See [ROADMAP.md](ROADMAP.md) for what's planned and being explored.

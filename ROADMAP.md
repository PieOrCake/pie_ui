# Pie UI — Roadmap

What's planned and being explored for Pie UI, grouped by feature. This is a living list of
direction and ideas — **not a promise or a timeline.** Items can change, slip, or be dropped, and
some are harder than they look. Anything already shipped lives in the [README](README.md) feature list.

**Status key:** 🔨 In progress · 📋 Planned · 💡 Exploring

---

### Target frame
The target frame now shows health, attitude colouring, a native-style defiance / break bar, the
target's **name** (with player guild name / tag), **level or mastery rank**, **class / elite-spec
icon**, a skills / title line, and a **right-click player context menu** (see the
[README](README.md)). Still to come for full parity:
- 📋 **Rank** indicator (veteran / elite / champion / legendary).
- 💡 **Elite spec for non-group player targets** — currently the elite-spec icon resolves only for your
  party / squad members; arbitrary players show the core profession icon (their spec isn't in readable
  client memory).

### Skill bars
- 💡 **Cast bar** showing the skill currently being cast, with its name.

### Profession & pet bars
- 📋 **Deeper mechanic bars** — richer per-profession treatments for kits, transforms, and the like.
- 📋 **More profession resources** — the resource bar covers Necromancer, Mesmer, Guardian, Revenant
  (incl. Conduit), Ranger Galeshot, Warrior adrenaline, and Thief initiative / Specter Shadow Force
  today; still to come are Engineer heat / Holosmith, Elementalist Catalyst energy, Ranger Druid
  astral force, and the remaining new elite-spec mechanics (Paragon Motivation, Galeshot Wind Force, …).

### Boon, condition & effect bars
- 📋 **Complete "everything else" coverage** — match the native effects bar exactly, including food,
  utility, and banner effects.

### Squad & party frames
The frames show each member's class, name, commander tag, and **live health** (PvE, in-map). Going
further is being explored:
- 💡 **Out-of-range fade / range indicator** — out-of-range members currently just show a neutral bar.
- 💡 **Summon native squad management on demand** — a one-key toggle to pop the native squad panel
  (create / invite / markers) back up while keeping the custom frames in play.

### Minimap
- 🔨 **Live event markers** — dynamic events and hearts shown on the minimap.
- 📋 **Leather / cloth node distinction** — the only gather type the engine doesn't separate from
  its look-alike yet.
- 💡 **Heart completion icons** — distinct icons for completed vs. incomplete renown hearts.

### Chat & Tyrian IM
- 📋 **Item & material counts** — show how many of an item you own (inventory / bank / material
  storage) in its link tooltip, like the native chat does.
- 💡 **Contacts / friends panel** — a floating list of your contacts with quick whisper access.
- 💡 **Richer name hover tooltips** — account names already show on hover; still exploring class and
  current map (online only).

### General & themes
- 💡 **More visual themes** for the unified theme picker.

---

*Have a request? Open an issue on the repo.*

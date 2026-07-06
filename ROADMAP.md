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
  (incl. Conduit Affinity), Warrior adrenaline, Thief initiative / Specter Shadow Force, Holosmith heat,
  Druid astral force, Catalyst energy, Ranger Galeshot (arrow charges + Wind Force), Paragon Motivation,
  and one of the Evoker's two resource rings today; still to come are the remaining new elite-spec
  mechanics (the second Evoker ring, …).

### Boon, condition & effect bars
- 📋 **Complete "everything else" coverage** — match the native effects bar exactly, including food,
  utility, and banner effects.

### Squad & party frames
The frames show each member's class, name, commander tag, **live health** (PvE, in-map), and now **dim
out-of-range members**. Going further is being explored:
- 💡 **Summon native squad management on demand** — a one-key toggle to pop the native squad panel
  (create / invite / markers) back up while keeping the custom frames in play.

### Minimap
- 📋 **Event boundary rings** — live event dots already appear on the minimap; the next step is drawing
  each event's area ring, like the native map.
- 📋 **Leather / cloth node distinction** — the only gather type the engine doesn't separate from
  its look-alike yet.

### Chat & Tyrian IM
- 💡 **Contacts / friends panel** — a floating list of your contacts with quick whisper access.
- 💡 **Richer name hover tooltips** — account names already show on hover; still exploring class and
  current map (online only).

### General & themes
- 💡 **More visual themes** for the unified theme picker.

---

*Have a request? Open an issue on the repo.*

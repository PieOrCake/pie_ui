# Pie UI — Roadmap

What's planned and being explored for Pie UI, grouped by feature. This is a living list of
direction and ideas — **not a promise or a timeline.** Items can change, slip, or be dropped, and
some are harder than they look. Anything already shipped lives in the [README](README.md) feature list.

**Status key:** 🔨 In progress · 📋 Planned · 💡 Exploring

---

### Target frame
The target frame currently shows the target's health percentage. The goal is full parity with the
native frame:
- 🔨 **Defiance / break bar** for targets that have one.
- 📋 **Target name**, **level**, and **rank** (veteran / elite / champion / legendary).
- 📋 **Attitude colour** — friendly / hostile / neutral, matching the native frame.

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
The frames currently show each member's class, name, and commander tag. Going further means reading
live state, which is harder and being explored:
- 💡 **Member health bars** — live HP for members in your map (the native frame's main feature).
- 💡 **Range / out-of-range fade** and **downed indicators**.
- 💡 **Summon native squad management on demand** — a one-key toggle to pop the native squad panel
  (create / invite / markers) back up while keeping the custom frames in play.

- 🔨 **Live event markers** — dynamic events and hearts shown on the minimap.
- 📋 **Leather / cloth node distinction** — the only gather type the engine doesn't separate from
  its look-alike yet.
- 💡 **Commander tags** — friendly squad-commander markers on the minimap.
- 💡 **Heart completion icons** — distinct icons for completed vs. incomplete renown hearts.

### Chat & Tyrian IM
- 📋 **Item & material counts** — show how many of an item you own (inventory / bank / material
  storage) in its link tooltip, like the native chat does.
- 🔨 **System messages** — capture the game's yellow system lines into the chat box.
- 💡 **Contacts / friends panel** — a floating list of your contacts with quick whisper access.
- 💡 **Richer name hover tooltips** — account names already show on hover; still exploring class and
  current map (online only).

### General & themes
- 💡 **More visual themes** for the unified theme picker.

---

*Have a request? Open an issue on the repo.*

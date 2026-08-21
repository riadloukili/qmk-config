# users/riad

Behavior and layer content shared by every keymap named `riad`. Board wiring
stays in each board's `keymaps/riad/`, which only binds the layers here to
its `LAYOUT` macro.

| file | holds |
| --- | --- |
| `riad.h` | layer enum, custom keycodes, key aliases |
| `riad.c` | QMK entry points, dispatching to the host layout |
| `host_layout.h` | the interfaces a host layout and an arrangement implement |
| `host_layout.c` | registry, persistence, switching, dispatch |
| `host_layouts/us.c` | US QWERTY |
| `host_layouts/ca.c` | Canadian Multilingual (CSA) |
| `host_api.c` | raw HID query API for host-side tooling |
| `combos.c` | chords over the base layers |
| `layers/alphas.h` | alpha row fragments, home-row mod wrappers, base composer |
| `layers/shared.h` | layers shared by every layout: FN, NAV, MEDIA, MOUSE |
| `layers/us.h` | US base layers and symbol layers |
| `layers/ca.h` | CA base layers, symbol layers, accents |

## Host layouts

A host layout describes how the firmware talks to an OS configured with a
given keyboard layout. Each one implements `host_layout_t`:

```c
typedef struct {
    const char *name;                     // printed over the HID console
    host_arrangement_t arrangements[5];   // slot 0 is the vanilla base
    uint8_t arrangement_count;
    bool (*process_record)(uint16_t, keyrecord_t *);  // optional
} host_layout_t;
```

Switching layouts is `default_layer_set` onto a base layer. Keys mean
whatever their layer says; nothing is rewritten at press time.
`process_record` exists only for what a layer cannot express, and only the
active layout's hook runs.

`LAY_*` keycodes (on `_MEDIA`, esc + `Y`/`U`) select a layout absolutely;
there is no toggle. Every change prints over `qmk console`.

## Arrangements

An arrangement is a reorder of a layout's alphas: qwerty, colemak-dh, dvorak.
Each layout carries up to `HOST_ARRANGEMENT_MAX` (5) of them as
`{name, base_layer}` pairs — every (layout, arrangement) pair is its own base
layer, so switching either axis stays a `default_layer_set`.

`ARR_1..ARR_5` keycodes (on `_NAV`, space + `Y`/`U`/`I`/`O`/`P`) select an
arrangement by slot within the active layout; `ARR_1` is always the vanilla
QWERTY order. Out-of-range slots are ignored.

Persistence shares the 32-bit user EEPROM word: byte 0 is the layout id and
each layout's arrangement index lives in a 3-bit field starting at bit 8, so
every layout remembers its own choice and a blank or legacy EEPROM decodes as
vanilla everywhere. Switching layouts restores that layout's stored
arrangement.

## Combos

`combos.c` holds the chords. A combo matches keycodes rather than positions,
so each arrangement needs its own entry; building those entries out of the
same fragments the layers use keeps the two from drifting:

```c
const uint16_t PROGMEM combo_save_qwerty[] = {
    HRM_L_ALT(ALPHAS_QWERTY_2L), HRM_L_CTL(ALPHAS_QWERTY_2L), COMBO_END};
```

`HRM_L_ALT`/`HRM_L_CTL` in `layers/alphas.h` pick one key out of a home-row
fragment and wrap it in the same mod-tap `HRM_L` would, so the chord stays on
the same two physical keys whatever letters an arrangement puts there. Add a
picker per slot as chords need it.

| chord | does |
| --- | --- |
| alt + ctrl home keys (`S`+`D` qwerty, `R`+`S` colemak-dh) | Ctrl+S |

Host layouts need no entry of their own: CSA puts its letters where QWERTY
does, so `us` and `ca` share these keycodes.

The table lives in the userspace, not a board's `keymap.c`, which needs one
thing from `rules.mk`. QMK sizes `key_combos[]` with `ARRAY_SIZE` inside
`keymap_introspection.c`, so that file has to *see* the definition:
`INTROSPECTION_KEYMAP_C = combos.c` includes it there, and `combos.c` stays
out of `SRC` so it is not also compiled on its own.

`just draw` does not render combos — `qmk c2json` drops them, so
keymap-drawer never sees them.

## Raw HID API

`host_api.c` exposes the same to host-side tooling (`scripts/host-layout`)
over QMK raw HID. Requests are 32-byte reports, byte 0 the command:

- `0x01` get the active layout.
- `0x02` set it; bytes 1.. carry the layout name, NUL-terminated.
- `0x03` get the active layout's arrangement.
- `0x04` set it; bytes 1.. carry the arrangement name.

On success the response echoes the command in byte 0, the layout id (or
arrangement index) in byte 1, and the name from byte 2. On an unknown command
or name, byte 0 is `0xFF`.

## Layer stack

```
_US_BASE  _US_CDH_BASE          one base per (layout, arrangement),
_CA_BASE  _CA_CDH_BASE          always at the bottom
_FN  _NAV  _MEDIA  _MOUSE       shared: no symbols, so no per-layout copies
_US_NUM  _US_SYM                US symbol layers, shared by its arrangements
_CA_NUM  _CA_SYM  _CA_ACCENTS
```

Key lookup scans layers top-down with the default layer included, so base
layers must stay below every momentary layer or they shadow it. `_US_BASE`
stays 0 so a blank EEPROM boots into it.

## Layer composition

Base layers are composed, not drawn. `layers/alphas.h` defines each
arrangement as six 5-key row fragments; `LAYER_ALPHA` assembles them with the
shared thumb row, and `HRM_L`/`HRM_R` wrap the home row in GACS mod-taps —
positional, so any arrangement gets home-row mods for free. Slots that differ
per layout (the top-right key, quote, slash, thumbs) stay parameters, filled
by each layout's `LAYER_*` definitions in `layers/us.h` / `layers/ca.h`.

One-off layers (FN, NAV, symbol layers) remain literal grids; they have no
duplication to factor out. The board keymap defines
`LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)` — the variadic indirection that
lets fragments expand before the arity check — and lists the `LAYER_*` names
in enum order.

## Adding a host layout

1. Add its base and symbol layers to `enum riad_layers` (bases stay at the
   bottom) and a `layers/<name>.h` composing them; include it from the
   board's `keymap.c` and extend `keymaps[]`.
2. Append an id to `host_layout_id_t` and a `LAY_*` keycode in the same
   position.
3. Create `host_layouts/<name>.c` defining a `host_layout_t` (slot 0 of
   `arrangements` is its vanilla base), declare it in `host_layout.h`,
   register it in `host_layout.c`, add it to `SRC` in `rules.mk`.

## Adding an arrangement

1. Define its six `ALPHAS_<NAME>_*` row fragments in `layers/alphas.h`.
2. Add a base layer per layout that offers it: an enum entry (with the other
   bases), a `LAYER_ALPHA` composition in that layout's `layers/*.h`, and a
   `keymaps[]` entry.
3. Append `{name, base_layer}` to the layout's `arrangements` and bump its
   `arrangement_count` (max 5).

## CSA notes

Letters sit where QWERTY puts them; only symbols move, and the `_CA_*` layers
remap them so the characters on screen match US.

- `` ` `` and `^` exist only as dead keys. `CSA_BTICK` and `CSA_CARET` tap the
  dead key twice, which emits the literal mark.
- `CSA_ACUTE/GRAVE/CFLEX/DIAE` arm a dead key; type the vowel next. Shift on
  the vowel capitalizes.
- Shift+`,` `.` `/` produce `'` `"` `\`; `ca.c` restores `<` `>` `?`.
- Apostrophe is `S(CA_COMM)`, which a mod-tap cannot hold. `CSA_GUI_QUOT`
  (qwerty) and `CSA_ACC_QUOT` (colemak-dh) hold a stand-in and `ca.c`
  substitutes the tap.
- The CA top-right key always holds the accents layer; the tap is the
  arrangement's: `P` on qwerty, quote on colemak-dh.
- Right Alt selects level 3 and right Ctrl level 5, so the right-hand
  home-row mods hold the *left* Ctrl/Alt; the right pair would be layout
  selectors, not modifiers.
- QMK's `CA_TILD` reaches level 5, a dead tilde on current XKB. `CSA_TILDE`
  uses level 3, the literal one.

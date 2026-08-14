# users/riad

Behavior and layer content shared by every keymap named `riad`. Board wiring
stays in each board's `keymaps/riad/`, which only binds the layers here to
its `LAYOUT` macro.

| file | holds |
| --- | --- |
| `riad.h` | layer enum, custom keycodes, key aliases |
| `riad.c` | QMK entry points, dispatching to the host layout |
| `host_layout.h` | the interface a host layout implements |
| `host_layout.c` | registry, persistence, switching, dispatch |
| `host_layouts/us.c` | US QWERTY |
| `host_layouts/ca.c` | Canadian Multilingual (CSA) |
| `host_api.c` | raw HID query API for host-side tooling |
| `layers/alphas.h` | alpha row fragments, home-row mod wrappers, base composer |
| `layers/shared.h` | layers shared by every layout: FN, NAV, MEDIA, MOUSE |
| `layers/us.h` | US base layer and symbol layers |
| `layers/ca.h` | CA base layer, symbol layers, accents |

## Host layouts

A host layout describes how the firmware talks to an OS configured with a
given keyboard layout. Each one implements `host_layout_t`:

```c
typedef struct {
    const char *name;           // printed over the HID console
    uint8_t     default_layer;  // its base layer
    bool (*process_record)(uint16_t, keyrecord_t *);  // optional
} host_layout_t;
```

Switching layouts is `default_layer_set` onto that layout's base layer. Keys
mean whatever their layer says; nothing is rewritten at press time.
`process_record` exists only for what a layer cannot express, and only the
active layout's hook runs.

The active layout is persisted in EEPROM as `host_layout_id_t`. US is id 0, so
a blank EEPROM boots US. `LAY_*` keycodes select a layout absolutely; there is
no toggle. Every change prints over `qmk console`.

## Raw HID API

`host_api.c` exposes the same to host-side tooling (`scripts/host-layout`)
over QMK raw HID. Requests are 32-byte reports, byte 0 the command:

- `0x01` get the active layout.
- `0x02` set it; bytes 1.. carry the layout name, NUL-terminated.

On success the response echoes the command in byte 0, the layout id in byte 1,
and the name from byte 2. On an unknown command or name, byte 0 is `0xFF`.

## Layer stack

```
_US_BASE  _CA_BASE          one base per host layout, always at the bottom
_FN  _NAV  _MEDIA  _MOUSE   shared: no symbols, so no per-layout copies
_US_NUM  _US_SYM            US symbol layers
_CA_NUM  _CA_SYM  _CA_ACCENTS
```

Key lookup scans layers top-down with the default layer included, so base
layers must stay below every momentary layer or they shadow it.

## Layer composition

Base layers are composed, not drawn. `layers/alphas.h` defines the alphas as
six 5-key row fragments; `LAYER_ALPHA` assembles them with the shared thumb
row, and `HRM_L`/`HRM_R` wrap the home row in GACS mod-taps — positional, so
they follow whatever letters sit there. Slots that differ per layout (the
top-right key, quote, slash, thumbs) stay parameters, filled by each layout's
`LAYER_*` definitions in `layers/us.h` / `layers/ca.h`.

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
3. Create `host_layouts/<name>.c` defining a `host_layout_t`, declare it in
   `host_layout.h`, register it in `host_layout.c`, add it to `SRC` in
   `rules.mk`.

## CSA notes

Letters sit where QWERTY puts them; only symbols move, and the `_CA_*` layers
remap them so the characters on screen match US.

- `` ` `` and `^` exist only as dead keys. `CSA_BTICK` and `CSA_CARET` tap the
  dead key twice, which emits the literal mark.
- `CSA_ACUTE/GRAVE/CFLEX/DIAE` arm a dead key; type the vowel next. Shift on
  the vowel capitalizes.
- Shift+`,` `.` `/` produce `'` `"` `\`; `ca.c` restores `<` `>` `?`.
- Apostrophe is `S(CA_COMM)`, which a mod-tap cannot hold. `CSA_GUI_QUOT`
  holds the comma and `ca.c` substitutes the tap.
- Right Alt selects level 3 and right Ctrl level 5, so the right-hand
  home-row mods hold the *left* Ctrl/Alt; the right pair would be layout
  selectors, not modifiers.
- QMK's `CA_TILD` reaches level 5, a dead tilde on current XKB. `CSA_TILDE`
  uses level 3, the literal one.

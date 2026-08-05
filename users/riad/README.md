# users/riad

Behavior shared by every keymap named `riad`. Board wiring stays in each
board's `keymaps/riad/`.

| file | holds |
| --- | --- |
| `riad.h` | layer enum, custom keycodes, key aliases |
| `riad.c` | QMK entry points, dispatching to the host layout |
| `host_layout.h` | the interface a host layout implements |
| `host_layout.c` | registry, persistence, switching, dispatch |
| `host_layouts/us.c` | US QWERTY |
| `host_layouts/ca.c` | Canadian Multilingual (CSA) |
| `host_api.c` | raw HID query API for host-side tooling |

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

`host_api.c` exposes the same over raw HID for host-side tooling
(`scripts/host-layout`): `0x01` gets the active layout, `0x02` sets it by
name. Responses carry the layout id and name; errors answer `0xFF`.

## Layer stack

```
_US_BASE  _CA_BASE          one base per host layout, always at the bottom
_FN  _NAV  _MEDIA  _MOUSE   shared: no symbols, so no per-layout copies
_US_NUM  _US_SYM            US symbol layers
_CA_NUM  _CA_SYM  _CA_ACCENTS
```

Key lookup scans layers top-down with the default layer included, so base
layers must stay below every momentary layer or they shadow it.

## Adding a host layout

1. Add its base and symbol layers to `enum riad_layers` (bases stay at the
   bottom) and to the board's `layers/` and `keymap.c`.
2. Append an id to `host_layout_id_t` and a `LAY_*` keycode in the same
   position.
3. Create `host_layouts/<name>.c` defining a `host_layout_t`, declare it in
   `host_layout.h`, register it in `host_layout.c`, add it to `SRC`.

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
- Right Alt selects level 3 and right Ctrl level 5, so home-row `K`/`L` hold
  the *left* Ctrl/Alt; the right pair would be layout selectors, not
  modifiers.
- QMK's `CA_TILD` reaches level 5, a dead tilde on current XKB. `CSA_TILDE`
  uses level 3, the literal one.

# qmk userspace

Keyboard layouts as C, built with Nix. A QMK [External Userspace][eus], so
keymaps live in this repo instead of inside a `qmk_firmware` checkout.

Everything stays inside this directory. Nothing is written to `$HOME`.

[eus]: https://docs.qmk.fm/newbs_external_userspace

## Setup

```sh
direnv allow      # or: nix develop
just init         # clones qmk_firmware into ./.qmk_firmware
just build
```

## Build

```sh
just build                 # every target in qmk.json
just build <keyboard>      # filter by keyboard
just build "" <keymap>     # filter by keymap
just build <kb> <km>       # both
just                       # list all recipes
```

Firmware lands in `build/`.

## Repo layout

```
qmk.json      build targets, edit via `qmk userspace-add`
flake.nix     dev shell (qmk CLI + arm/avr toolchains)
justfile      task runner
users/riad/   shared across every keyboard: layer enum, aliases, hooks
keyboards/    per-board keymaps, each with its own README
```

`users/riad/` is picked up automatically by any keymap named `riad`, so layer
names and aliases stay consistent across boards. Board-specific wiring belongs
in that board's `keymaps/riad/`.

## Adding a keyboard

```sh
qmk list-keyboards | grep -i <name>                 # find the target
mkdir -p keyboards/<vendor>/<board>/keymaps/riad    # write keymap.c
qmk userspace-add -kb <target> -km riad
just build
```

Start from the board's shipped `default` keymap in
`.qmk_firmware/keyboards/<path>/keymaps/default/`, and `#include "riad.h"` to
pick up the shared layers and aliases. `just build` reads `qmk.json`, so the
justfile needs no edit.

Both the ARM and AVR toolchains are already in the dev shell.

## Keyboards

- [Charybdis Nano (3x5)](keyboards/bastardkb/charybdis/3x5/keymaps/riad/README.md)

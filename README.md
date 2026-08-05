# qmk userspace

Keyboard layouts as C, built with Nix. A QMK [External Userspace][eus], so
keymaps live in this repo instead of inside a `qmk_firmware` checkout.

The firmware checkout and every build artifact stay inside this directory.

[eus]: https://docs.qmk.fm/newbs_external_userspace

## Setup

```sh
direnv allow      # or: nix develop
just init         # clones qmk_firmware into ./.qmk_firmware
just build
```

## Recipes

```sh
just build [kb] [km]   # build targets from qmk.json, args are substring filters
just draw  [kb] [km]   # render each keymap to an SVG beside its keymap.c
just flash [kb] [km]   # build and flash one target (put it in bootloader first)
just                   # everything else
```

Firmware lands in `build/`.

## Map

```
qmk.json        build targets, edit via `qmk userspace-add`
flake.nix       dev shell (qmk CLI + arm/avr toolchains)
pyproject.toml  keymap-drawer, synced by uv on shell entry
justfile        task runner
scripts/        host-side tooling (layout widget)
users/riad/     shared behavior and the host layout system  -> its README
keyboards/      per-board keymaps                            -> their READMEs
```

## Adding a keyboard

```sh
qmk list-keyboards | grep -i <name>
mkdir -p keyboards/<vendor>/<board>/keymaps/riad    # write keymap.c
qmk userspace-add -kb <target> -km riad
just build
```

Include `riad.h` for the shared layers and aliases. Both ARM and AVR
toolchains are already in the dev shell.

## Keyboards

- [Charybdis Nano (3x5)](keyboards/bastardkb/charybdis/3x5/keymaps/riad/README.md)

## License

[MIT](LICENSE).

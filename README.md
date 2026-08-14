# qmk userspace

Keyboard layouts as C, built with Nix. A QMK [External Userspace][eus], so
keymaps live in this repo instead of inside a `qmk_firmware` checkout.

The firmware checkout and every build artifact stay inside this directory.

[eus]: https://docs.qmk.fm/newbs_external_userspace

## Setup

```sh
direnv allow      # or: nix develop
just init         # checks out qmk_firmware at the revision in ./qmk-rev
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
qmk-rev         qmk_firmware revision, used by `just init` and CI
flake.nix       dev shell; `.#ci` is the same without editor tooling
pyproject.toml  keymap-drawer, synced by uv on shell entry
justfile        task runner
scripts/        host-side tooling (layout widget)
users/riad/     shared behavior, layer content, host layouts -> its README
keyboards/      per-board keymaps, binding those layers      -> their READMEs
```

## Adding a keyboard

```sh
qmk list-keyboards | grep -i <name>
mkdir -p keyboards/<vendor>/<board>/keymaps/riad    # write keymap.c
qmk userspace-add -kb <target> -km riad
just build
```

A board's `keymap.c` includes `riad.h`, defines
`LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)`, includes the layer headers from
`users/riad/layers/`, and lists them in `keymaps[]`. Both ARM and AVR
toolchains are already in the dev shell.

## Keyboards

- [Charybdis Nano (3x5)](keyboards/bastardkb/charybdis/3x5/keymaps/riad/README.md)

## License

[MIT](LICENSE).

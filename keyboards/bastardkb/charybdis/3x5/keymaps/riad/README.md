# Charybdis Nano (3x5)

Split 3x5+3 with a trackball on the right half, Splinky (RP2040) controller.

```sh
just build charybdis
```

## Layout

```
 Q  W  E  R  T        Y  U  I  O  P
 A  S  D  F  G        H  J  K  L  '
 Z  X  C  V  B        N  M  ,  .  /
    ESC SPC TAB      ENT BSPC
```

Home-row mods on `ASDF` / `JKL'`. Hold a key for its layer:

| Hold | Layer | Contents |
| --- | --- | --- |
| `ESC` | `_MEDIA` | volume, transport, `QK_BOOT`, `EE_CLR` |
| `SPC` | `_NAV` | arrows on `HJKL`, home/end/page |
| `TAB` | `_FN` | F1–F12 |
| `ENT` | `_SYM` | shifted symbols |
| `BSPC` | `_NUM` | digits, brackets |
| `Z` or `/` | `_MOUSE` | DPI, sniping, drag-scroll, mouse buttons |

`L` sits on left Alt rather than right, since right Alt is AltGr and would
emit accented characters on non-US layouts.

## Flashing

Both halves take the same image. Do them one at a time, each plugged into USB.

1. **Hold `ESC`, press `B`**, or tap reset twice, to mount as `RPI-RP2`.
2. Copy `build/bastardkb_charybdis_3x5_elitec_riad.uf2` onto it.
3. Repeat for the other half.
4. Plug USB into the **right** half, the one with the trackball.

If the drive doesn't auto-mount, `udisksctl mount -b /dev/sdX1`. Verify
`LABEL=RPI-RP2` and `MODEL=RP2` first. Writing to the wrong device is bad.

Only the master half needs reflashing for a keymap change. Reflash both when
changing something structural like `MASTER_RIGHT`.

## Board notes

**The target has no "Splinky" in it.** QMK's 2025-08-31 restructure removed
`bastardkb/charybdis/3x5/v2/splinky_3`. The Splinky is an RP2040 Community
Edition board in an Elite-C footprint, so it builds as
`bastardkb/charybdis/3x5/elitec` with `CONVERT_TO = rp2040_ce` in `rules.mk`.
Guides and configs referencing the old path are out of date.

**`MASTER_RIGHT` is required.** Mainline sets no handedness for this board, so
`is_keyboard_left()` falls through to `is_keyboard_master()`: whichever half
has USB is assumed to be the left one. Without it, plugging into the trackball
half mirrors the entire layout.

**RGB Matrix is disabled** in `rules.mk`; this unit has no per-key LEDs. The
keyboard definition enables it by default, and turning it off saves ~14 KB.

**The `UPDATE` button on the PCB is not `BOOTSEL`.** Holding it through
power-on does not enter the bootloader.

## Recovery

**Layout mirrored after flashing:** press `EE_CLR` (`ESC` + `V`). Stale
handedness can persist in EEPROM and override `MASTER_RIGHT`.

**A half is stuck on firmware where `ESC` + `B` is unreachable:** plug that
half in alone and **hold `Z`, tap `Q`**. Its matrix is read as the opposite
hand, which lands on a key bound to `QK_BOOT`.

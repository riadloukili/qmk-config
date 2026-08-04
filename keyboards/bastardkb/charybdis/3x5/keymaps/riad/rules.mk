# This board ships a Splinky controller: an RP2040 "Community Edition" board
# in an Elite-C footprint. QMK's 2025-08-31 restructure removed the old
# `3x5/v2/splinky_3` path, so the controller is selected here instead.
CONVERT_TO = rp2040_ce

# This board has no per-key LEDs. The keyboard definition enables RGB Matrix
# by default, so turn it off here — it drops the driver, the effect table and
# the animation task.
RGB_MATRIX_ENABLE = no

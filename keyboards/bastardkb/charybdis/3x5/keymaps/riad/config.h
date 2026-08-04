#pragma once

// The USB cable goes into the RIGHT half — the one with the trackball.
//
// Mainline QMK sets no handedness for this board, so `is_keyboard_left()`
// falls through to `is_keyboard_master()` (split_util.c): whichever half is
// plugged in is assumed to be the left one. That is the opposite of how the
// stock BastardKB VIA firmware behaves, and plugging in the right half would
// mirror the layout.
//
// Keeping the trackball half as master also avoids sending pointer deltas
// across the split link on every poll.
#define MASTER_RIGHT

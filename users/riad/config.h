// NOTE: settings shared by every keymap named `riad`; board-specific ones
// stay in keyboards/<vendor>/<board>/keymaps/riad/config.h.
#pragma once

// WARN: the save chord sits on two adjacent home-row mod-taps, so a rolled
// bigram that overlaps them would fire it. QMK needs both keys down at once,
// not merely pressed in sequence, and 35ms narrows that overlap window
// further without making the chord hard to hit deliberately.
#define COMBO_TERM 35

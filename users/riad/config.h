// NOTE: settings shared by every keymap named `riad`; board-specific ones
// stay in keyboards/<vendor>/<board>/keymaps/riad/config.h.
#pragma once

// WARN: the save chord sits on two adjacent home-row mod-taps, so a rolled
// bigram that overlaps them would fire it. QMK needs both keys down at once,
// not merely pressed in sequence, and 35ms narrows that overlap window
// further without making the chord hard to hit deliberately.
#define COMBO_TERM 35

// NOTE: lets combos.c mark chords tap-only, so the ones sitting on home-row
// mod-taps still hold their mods. The window is COMBO_HOLD_TERM, which
// defaults to TAPPING_TERM, so a chord and a single key become a hold at the
// same moment.
#define COMBO_MUST_TAP_PER_COMBO

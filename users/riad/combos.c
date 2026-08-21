// NOTE: chords over the base layers. A combo names keycodes, not positions,
// so each arrangement needs its own entry; deriving them from the same
// fragments the layers are built from keeps the two from drifting.
//
// WARN: not in SRC. QMK counts combos with ARRAY_SIZE inside
// keymap_introspection.c, which only sees what it includes, so rules.mk
// points INTROSPECTION_KEYMAP_C here instead of compiling this separately.
#include "riad.h"
#include "layers/alphas.h"

// NOTE: the alt and ctrl home-row keys chorded save. The pair is the same
// two physical keys under every arrangement, only the letters on them move:
// S+D on qwerty, R+S on colemak-dh.
const uint16_t PROGMEM combo_save_qwerty[]     = {HRM_L_ALT(ALPHAS_QWERTY_2L), HRM_L_CTL(ALPHAS_QWERTY_2L), COMBO_END};
const uint16_t PROGMEM combo_save_colemak_dh[] = {HRM_L_ALT(ALPHAS_COLEMAK_DH_2L), HRM_L_CTL(ALPHAS_COLEMAK_DH_2L), COMBO_END};

// NOTE: one entry per arrangement, not per host layout: CSA puts its letters
// where QWERTY does, so both layouts share these keycodes.
combo_t key_combos[] = {
    COMBO(combo_save_qwerty, LCTL(KC_S)),
    COMBO(combo_save_colemak_dh, LCTL(KC_S)),
};

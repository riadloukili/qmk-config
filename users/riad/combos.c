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

// NOTE: a chord resting on mod-taps must only fire when tapped; held past
// COMBO_HOLD_TERM it is dropped and the keys go back to being the mods they
// are. Deciding from the chord's own contents rather than a list of combo
// indices means anything later placed on the home row inherits this, while a
// chord on plain keys still fires immediately.
bool get_combo_must_tap(uint16_t combo_index, combo_t *combo) {
    uint16_t key;
    for (uint8_t i = 0; (key = pgm_read_word(&combo->keys[i])) != COMBO_END; i++) {
        switch (key) {
            case QK_MOD_TAP ... QK_MOD_TAP_MAX:
            case QK_LAYER_TAP ... QK_LAYER_TAP_MAX:
            case QK_MOMENTARY ... QK_MOMENTARY_MAX:
                return true;
        }
    }
    return false;
}

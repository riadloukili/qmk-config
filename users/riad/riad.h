// NOTE: shared by every keymap named `riad`. Board-specific wiring stays in
// keyboards/<vendor>/<board>/keymaps/riad/.
#pragma once

#include QMK_KEYBOARD_H

enum riad_layers {
    _BASE = 0,
    _FN,
    _NAV,
    _MEDIA,
    _MOUSE,
    _NUM,
    _SYM,
};

// NOTE: each hand uses its own side's modifiers, so a chord spanning both
// halves never collides on the same physical modifier. KC_L is the exception:
// left Alt, because right Alt is AltGr and emits accents on non-US layouts.
#define HR_A LGUI_T(KC_A)
#define HR_S LALT_T(KC_S)
#define HR_D LCTL_T(KC_D)
#define HR_F LSFT_T(KC_F)

#define HR_J RSFT_T(KC_J)
#define HR_K RCTL_T(KC_K)
#define HR_L LALT_T(KC_L)
#define HR_QUOT RGUI_T(KC_QUOT)

#define MOU_Z LT(_MOUSE, KC_Z)
#define MOU_SLSH LT(_MOUSE, KC_SLSH)
#define MED_ESC LT(_MEDIA, KC_ESC)
#define NAV_SPC LT(_NAV, KC_SPC)
#define FN_TAB LT(_FN, KC_TAB)
#define SYM_ENT LT(_SYM, KC_ENT)
#define NUM_BSPC LT(_NUM, KC_BSPC)

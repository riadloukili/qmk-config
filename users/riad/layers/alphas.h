// NOTE: alpha arrangements as 5-key row fragments, composed into base layers
// by LAYER_ALPHA. Home-row mods are positional: HRM_L/HRM_R wrap whatever
// letters an arrangement puts on the home row, so a new arrangement is six
// fragments and one LAYER_* per layout. Slots that differ per layout (the
// top-right key, quote, slash, thumbs) stay parameters.
#pragma once

// clang-format off

// NOTE: variadic indirection so a fragment passed as one macro argument
// expands into five before the arity check.
#define HRM_L(...) HRM_L_IMPL(__VA_ARGS__)
#define HRM_R(...) HRM_R_IMPL(__VA_ARGS__)

// WARN: the right hand holds the *left* Ctrl/Alt. CSA uses right Alt for
// level 3 and right Ctrl for level 5, so the right pair would be layout
// selectors, not mods.
#define HRM_L_IMPL(K1, K2, K3, K4, K5) LGUI_T(K1), LALT_T(K2), LCTL_T(K3), LSFT_T(K4), K5
#define HRM_R_IMPL(K1, K2, K3, K4, K5) K1, RSFT_T(K2), LCTL_T(K3), LALT_T(K4), K5

// NOTE: a combo has to name the exact keycode sitting on the layer, mod-tap
// and all. These pick one key out of the same fragment HRM_L wraps, so a
// combo follows an arrangement instead of hard-coding its letters.
#define HRM_L_ALT(...) HRM_L_ALT_IMPL(__VA_ARGS__)
#define HRM_L_CTL(...) HRM_L_CTL_IMPL(__VA_ARGS__)
#define HRM_L_ALT_IMPL(K1, K2, K3, K4, K5) LALT_T(K2)
#define HRM_L_CTL_IMPL(K1, K2, K3, K4, K5) LCTL_T(K3)

#define ALPHAS_QWERTY_1L           KC_Q, KC_W, KC_E, KC_R, KC_T
#define ALPHAS_QWERTY_1R(TOPR)     KC_Y, KC_U, KC_I, KC_O, TOPR
#define ALPHAS_QWERTY_2L           KC_A, KC_S, KC_D, KC_F, KC_G
#define ALPHAS_QWERTY_2R(QUOT)     KC_H, KC_J, KC_K, KC_L, QUOT
#define ALPHAS_QWERTY_3L(Z)        Z,    KC_X, KC_C, KC_V, KC_B
#define ALPHAS_QWERTY_3R(SLSH)     KC_N, KC_M, KC_COMM, KC_DOT, SLSH

// NOTE: ; moves to the NUM layer; the top-right slot carries quote.
#define ALPHAS_COLEMAK_DH_1L       KC_Q, KC_W, KC_F, KC_P, KC_B
#define ALPHAS_COLEMAK_DH_1R(TOPR) KC_J, KC_L, KC_U, KC_Y, TOPR
#define ALPHAS_COLEMAK_DH_2L       KC_A, KC_R, KC_S, KC_T, KC_G
#define ALPHAS_COLEMAK_DH_2R       KC_M, KC_N, KC_E, KC_I, RGUI_T(KC_O)
#define ALPHAS_COLEMAK_DH_3L(Z)    Z,    KC_X, KC_C, KC_D, KC_V
#define ALPHAS_COLEMAK_DH_3R(SLSH) KC_K, KC_H, KC_COMM, KC_DOT, SLSH

// NOTE: needs LAYOUT_wrapper, defined by the board keymap before inclusion.
#define LAYER_ALPHA(R1L, R1R, R2L, R2R, R3L, R3R, ENT, BSPC) LAYOUT_wrapper( \
    R1L,        R1R, \
    HRM_L(R2L), HRM_R(R2R), \
    R3L,        R3R, \
    MED_ESC, NAV_SPC, FN_TAB,    ENT, BSPC \
)

// clang-format on

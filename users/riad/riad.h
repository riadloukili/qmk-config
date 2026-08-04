// Shared across every keyboard built with the `riad` keymap.
// Board-independent vocabulary lives here; physical wiring stays in
// keyboards/<vendor>/<board>/keymaps/riad/.
#pragma once

#include QMK_KEYBOARD_H

// The layer scheme, reused verbatim on any future board so muscle memory
// transfers. A board with more keys simply leaves more of it unused.
enum riad_layers {
    _BASE = 0,
    _FN,    // F-keys
    _NAV,   // arrows, paging
    _MEDIA, // media transport, RGB, reset
    _MOUSE, // trackball: DPI, sniping, drag-scroll, buttons
    _NUM,   // digits and unshifted symbols
    _SYM,   // the shifted face of _NUM
};

// Home-row mods. Left hand takes the left-side modifiers, right hand the
// right-side ones, so a chord spanning both halves never collides on the same
// physical modifier.
//
// KC_L is the deliberate exception: it stays on *left* Alt, because right Alt
// is AltGr and would emit accented characters on non-US layouts.
#define HR_A LGUI_T(KC_A)
#define HR_S LALT_T(KC_S)
#define HR_D LCTL_T(KC_D)
#define HR_F LSFT_T(KC_F)

#define HR_J RSFT_T(KC_J)
#define HR_K RCTL_T(KC_K)
#define HR_L LALT_T(KC_L)
#define HR_QUOT RGUI_T(KC_QUOT)

// Layer-taps: tap for the keycode, hold for the layer.
#define MOU_Z LT(_MOUSE, KC_Z)
#define MOU_SLSH LT(_MOUSE, KC_SLSH)
#define MED_ESC LT(_MEDIA, KC_ESC)
#define NAV_SPC LT(_NAV, KC_SPC)
#define FN_TAB LT(_FN, KC_TAB)
#define SYM_ENT LT(_SYM, KC_ENT)
#define NUM_BSPC LT(_NUM, KC_BSPC)

// Shared by every keymap named `riad`. Board wiring lives in
// keyboards/<vendor>/<board>/keymaps/riad/.
#pragma once

#include QMK_KEYBOARD_H
#include "keymap_canadian_multilingual.h"
#include "host_layout.h"

// WARN: key lookup scans layers top-down with the default layer included, so
// base layers must stay below every momentary layer or they shadow it.
enum riad_layers {
    _US_BASE = 0,
    _CA_BASE,

    _FN,
    _NAV,
    _MEDIA,
    _MOUSE,

    _US_NUM,
    _US_SYM,

    _CA_NUM,
    _CA_SYM,
    _CA_ACCENTS,
};

enum riad_keycodes {
    // WARN: same order as host_layout_id_t; host_layout.c maps by offset.
    LAY_US = SAFE_RANGE,
    LAY_CA,

    // CSA has ` and ^ only as dead keys; these emit the literal mark.
    CSA_BTICK,
    CSA_CARET,

    // Arm a dead key, then type the vowel. Shift on the vowel capitalizes.
    CSA_ACUTE,
    CSA_GRAVE,
    CSA_CFLEX,
    CSA_DIAE,
};

// WARN: QMK's CA_TILD reaches level 5, a dead tilde on current XKB. The
// literal ~ sits on level 3 (verified against xkb symbols/ca).
#define CSA_TILDE ALGR(CA_CCED)

// Home-row mods.
// WARN: K and L hold the *left* Ctrl/Alt. CSA uses right Alt for level 3 and
// right Ctrl for level 5, so the right pair are layout selectors, not mods.
#define HR_A LGUI_T(KC_A)
#define HR_S LALT_T(KC_S)
#define HR_D LCTL_T(KC_D)
#define HR_F LSFT_T(KC_F)

#define HR_J RSFT_T(KC_J)
#define HR_K LCTL_T(KC_K)
#define HR_L LALT_T(KC_L)

// Layer taps shared by every host layout.
#define MOU_Z LT(_MOUSE, KC_Z)
#define MED_ESC LT(_MEDIA, KC_ESC)
#define NAV_SPC LT(_NAV, KC_SPC)
#define FN_TAB LT(_FN, KC_TAB)

#define US_GUI_QUOT RGUI_T(KC_QUOT)
#define US_MOU_SLSH LT(_MOUSE, KC_SLSH)
#define US_SYM_ENT LT(_US_SYM, KC_ENT)
#define US_NUM_BSPC LT(_US_NUM, KC_BSPC)

// WARN: apostrophe is S(CA_COMM), which a mod-tap cannot hold; the comma is
// held and host_layouts/ca.c substitutes the tap.
#define CSA_GUI_QUOT RGUI_T(KC_COMM)
#define CSA_MOU_SLSH LT(_MOUSE, CA_SLSH)
#define CSA_SYM_ENT LT(_CA_SYM, KC_ENT)
#define CSA_NUM_BSPC LT(_CA_NUM, KC_BSPC)
#define CSA_ACC_P LT(_CA_ACCENTS, KC_P)

// Board keymaps may implement this to handle their own keycodes first.
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);

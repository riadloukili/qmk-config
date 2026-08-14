// NOTE: shared by every keymap named `riad`; layer content lives in
// layers/*.h here, board wiring in keyboards/<vendor>/<board>/keymaps/riad/.
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

    // NOTE: CSA has ` and ^ only as dead keys; these emit the literal mark.
    CSA_BTICK,
    CSA_CARET,

    // NOTE: arm a dead key, then type the vowel. Shift on the vowel capitalizes.
    CSA_ACUTE,
    CSA_GRAVE,
    CSA_CFLEX,
    CSA_DIAE,
};

// WARN: QMK's CA_TILD reaches level 5, a dead tilde on current XKB. The
// literal ~ sits on level 3 (verified against xkb symbols/ca).
#define CSA_TILDE ALGR(CA_CCED)

// WARN: LT() aliases must stay in this file: the draw pipeline stubs it so
// they reach keymap-drawer as tokens, whose LT regex only takes numeric
// layers. Plain mod-taps (LGUI_T, ...) parse fine and may live in layers/.
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

// NOTE: board keymaps may implement this to handle their own keycodes first.
bool process_record_keymap(uint16_t keycode, keyrecord_t *record);

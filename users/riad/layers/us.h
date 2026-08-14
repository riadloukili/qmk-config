// NOTE: US QWERTY.
#pragma once

// clang-format off

#include "shared.h"

#define LAYER_US_BASE LAYER_ALPHA( \
    ALPHAS_QWERTY_1L,        ALPHAS_QWERTY_1R(KC_P), \
    ALPHAS_QWERTY_2L,        ALPHAS_QWERTY_2R(US_GUI_QUOT), \
    ALPHAS_QWERTY_3L(MOU_Z), ALPHAS_QWERTY_3R(US_MOU_SLSH), \
    US_SYM_ENT, US_NUM_BSPC \
)

#define LAYER_US_CDH_BASE LAYER_ALPHA( \
    ALPHAS_COLEMAK_DH_1L,        ALPHAS_COLEMAK_DH_1R(KC_QUOT), \
    ALPHAS_COLEMAK_DH_2L,        ALPHAS_COLEMAK_DH_2R, \
    ALPHAS_COLEMAK_DH_3L(MOU_Z), ALPHAS_COLEMAK_DH_3R(US_MOU_SLSH), \
    US_SYM_ENT, US_NUM_BSPC \
)

#define LAYER_US_NUM LAYOUT_wrapper( \
/* ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮ ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮ */\
       KC_LBRC    ,     KC_7     ,     KC_8     ,     KC_9     ,   KC_RBRC    ,     XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,\
/* ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ */\
       KC_SCLN    ,     KC_4     ,     KC_5     ,     KC_6     ,    KC_EQL    ,     XXXXXXX    ,   KC_LSFT    ,   KC_LCTL    ,   KC_LALT    ,   KC_LGUI    ,\
/* ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ */\
        KC_GRV    ,     KC_1     ,     KC_2     ,     KC_3     ,   KC_BSLS    ,     XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,\
/* ╰──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────╯ */\
                                      KC_DOT    ,     KC_0     ,   KC_MINS    ,     XXXXXXX    ,   _______    \
/*                             ╰──────────────┴──────────────┴──────────────╯ ╰──────────────┴──────────────╯ */\
)

#define LAYER_US_SYM LAYOUT_wrapper( \
/* ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮ ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮ */\
       KC_LCBR    ,   KC_AMPR    ,   KC_ASTR    ,   KC_LPRN    ,   KC_RCBR    ,     XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,\
/* ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ */\
       KC_COLN    ,    KC_DLR    ,   KC_PERC    ,   KC_CIRC    ,   KC_PLUS    ,     XXXXXXX    ,   KC_LSFT    ,   KC_LCTL    ,   KC_LALT    ,   KC_LGUI    ,\
/* ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ */\
       KC_TILD    ,   KC_EXLM    ,    KC_AT     ,   KC_HASH    ,   KC_PIPE    ,     XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,\
/* ╰──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────╯ */\
                                     KC_LPRN    ,   KC_RPRN    ,   KC_UNDS    ,     _______    ,   XXXXXXX    \
/*                             ╰──────────────┴──────────────┴──────────────╯ ╰──────────────┴──────────────╯ */\
)

// clang-format on

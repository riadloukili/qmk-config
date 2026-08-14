// NOTE: Canadian Multilingual (CSA). Same physical layout as US; the
// scancodes differ so the characters on screen do not.
#pragma once

// clang-format off

#include "shared.h"

#define LAYER_CA_BASE LAYER_ALPHA( \
    ALPHAS_QWERTY_1L,        ALPHAS_QWERTY_1R(CSA_ACC_P), \
    ALPHAS_QWERTY_2L,        ALPHAS_QWERTY_2R(CSA_GUI_QUOT), \
    ALPHAS_QWERTY_3L(MOU_Z), ALPHAS_QWERTY_3R(CSA_MOU_SLSH), \
    CSA_SYM_ENT, CSA_NUM_BSPC \
)

#define LAYER_CA_CDH_BASE LAYER_ALPHA( \
    ALPHAS_COLEMAK_DH_1L,        ALPHAS_COLEMAK_DH_1R(CSA_ACC_QUOT), \
    ALPHAS_COLEMAK_DH_2L,        ALPHAS_COLEMAK_DH_2R, \
    ALPHAS_COLEMAK_DH_3L(MOU_Z), ALPHAS_COLEMAK_DH_3R(CSA_MOU_SLSH), \
    CSA_SYM_ENT, CSA_NUM_BSPC \
)

#define LAYER_CA_NUM LAYOUT_wrapper( \
/* ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮ ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮ */\
       CA_LBRC    ,     CA_7     ,     CA_8     ,     CA_9     ,   CA_RBRC    ,     XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,\
/* ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ */\
       CA_SCLN    ,     CA_4     ,     CA_5     ,     CA_6     ,    CA_EQL    ,     XXXXXXX    ,   KC_LSFT    ,   KC_LCTL    ,   KC_LALT    ,   KC_LGUI    ,\
/* ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ */\
      CSA_BTICK   ,     CA_1     ,     CA_2     ,     CA_3     ,   CA_BSLS    ,     XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,\
/* ╰──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────╯ */\
                                      CA_DOT    ,     CA_0     ,   CA_MINS    ,     XXXXXXX    ,   _______    \
/*                             ╰──────────────┴──────────────┴──────────────╯ ╰──────────────┴──────────────╯ */\
)

#define LAYER_CA_SYM LAYOUT_wrapper( \
/* ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮ ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮ */\
       CA_LCBR    ,   CA_AMPR    ,   CA_ASTR    ,   CA_LPRN    ,   CA_RCBR    ,     XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,\
/* ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ */\
       CA_COLN    ,    CA_DLR    ,   CA_PERC    ,  CSA_CARET   ,   CA_PLUS    ,     XXXXXXX    ,   KC_LSFT    ,   KC_LCTL    ,   KC_LALT    ,   KC_LGUI    ,\
/* ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ */\
      CSA_TILDE   ,   CA_EXLM    ,    CA_AT     ,   CA_HASH    ,   CA_PIPE    ,     XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,\
/* ╰──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────╯ */\
                                     CA_LPRN    ,   CA_RPRN    ,   CA_UNDS    ,     _______    ,   XXXXXXX    \
/*                             ╰──────────────┴──────────────┴──────────────╯ ╰──────────────┴──────────────╯ */\
)

#define LAYER_CA_ACCENTS LAYOUT_wrapper( \
/* ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮ ╭──────────────┬──────────────┬──────────────┬──────────────┬──────────────╮ */\
       CA_EACU    ,   CA_EGRV    ,   CA_AGRV    ,   CA_UGRV    ,   CA_CCED    ,     XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   _______    ,\
/* ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ */\
      CSA_ACUTE   ,  CSA_GRAVE   ,  CSA_CFLEX   ,   CSA_DIAE   ,   XXXXXXX    ,     XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,\
/* ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ */\
       CA_LDAQ    ,   CA_RDAQ    ,    CA_OE     ,   CA_EURO    ,   XXXXXXX    ,     XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,\
/* ╰──────────────┼──────────────┼──────────────┼──────────────┼──────────────┤ ├──────────────┼──────────────┼──────────────┼──────────────┼──────────────╯ */\
                                     XXXXXXX    ,   XXXXXXX    ,   XXXXXXX    ,     XXXXXXX    ,   XXXXXXX    \
/*                             ╰──────────────┴──────────────┴──────────────╯ ╰──────────────┴──────────────╯ */\
)

// clang-format on

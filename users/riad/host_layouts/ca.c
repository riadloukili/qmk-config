// NOTE: Canadian Multilingual (CSA). Handles keycodes its layers cannot
// express directly: dead keys, and the shifted punctuation CSA moves away
// from QWERTY.
#include "riad.h"

static void tap_unmodded(uint16_t keycode) {
    uint8_t mods = get_mods();
    clear_mods();
    tap_code16(keycode);
    set_mods(mods);
}

// WARN: mods are stripped first so a held shift cannot change which level the
// dead key reaches. Tapping a dead key twice emits the literal mark.
static void tap_dead(uint16_t keycode, bool twice) {
    uint8_t mods = get_mods();
    clear_mods();
    tap_code16(keycode);
    if (twice) {
        tap_code16(keycode);
    }
    set_mods(mods);
}

static bool shifted(void) {
    return get_mods() & MOD_MASK_SHIFT;
}

static bool ca_process_record(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }

    switch (keycode) {
        case CSA_BTICK:
            tap_dead(CA_GRV, true);
            return false;
        case CSA_CARET:
            tap_dead(CA_CIRC, true);
            return false;

        case CSA_ACUTE:
            tap_dead(CA_ACUT, false);
            return false;
        case CSA_GRAVE:
            tap_dead(CA_GRV, false);
            return false;
        case CSA_CFLEX:
            tap_dead(CA_CIRC, false);
            return false;
        case CSA_DIAE:
            tap_dead(CA_DIAE, false);
            return false;

        // NOTE: on CSA, Shift+, Shift+. and Shift+/ produce ' " and backslash;
        // QWERTY expects < > and ?.
        case KC_COMM:
            if (shifted()) {
                tap_unmodded(CA_LABK);
                return false;
            }
            break;
        case KC_DOT:
            if (shifted()) {
                tap_unmodded(CA_RABK);
                return false;
            }
            break;
        case CSA_MOU_SLSH:
            if (record->tap.count && shifted()) {
                tap_unmodded(CA_QUES);
                return false;
            }
            break;

        // WARN: apostrophe is S(CA_COMM), which a mod-tap cannot hold, so the
        // aliases hold a stand-in and the tap is substituted here.
        case CSA_GUI_QUOT:
        case CSA_ACC_QUOT:
            if (record->tap.count) {
                tap_unmodded(shifted() ? CA_DQUO : CA_QUOT);
                return false;
            }
            break;
    }

    return true;
}

const host_layout_t host_layout_ca = {
    .name = "ca",
    .arrangements =
        {
            {.name = "qwerty", .base_layer = _CA_BASE},
            {.name = "colemak-dh", .base_layer = _CA_CDH_BASE},
        },
    .arrangement_count = 2,
    .process_record    = ca_process_record,
};

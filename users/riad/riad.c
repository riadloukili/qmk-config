#include "riad.h"

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

void keyboard_post_init_user(void) {
    host_layout_init();
}

static bool process_record_macros(uint16_t keycode, keyrecord_t *record) {
    if (!record->event.pressed) {
        return true;
    }
    switch (keycode) {
        // WARN: KC_TILD types a backslash on CSA.
        case SSH_KILL:
            tap_code(KC_ENT);
            switch (host_layout_active()) {
                case HOST_LAYOUT_CA:
                    tap_code16(CSA_TILDE);
                    break;
                case HOST_LAYOUT_US:
                default:
                    tap_code16(KC_TILD);
                    break;
            }
            tap_code(KC_DOT);
            return false;
    }
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return process_record_keymap(keycode, record) && process_record_macros(keycode, record) && host_layout_process_record(keycode, record);
}

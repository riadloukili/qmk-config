#include "riad.h"

// NOTE: shared keycode handling goes here. Since this file defines
// process_record_user, a keymap.c cannot, so per-board handling overrides this
// weak hook instead.
__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return process_record_keymap(keycode, record);
}

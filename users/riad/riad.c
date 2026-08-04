#include "riad.h"

// Per-board hook. A keymap.c may override this to handle its own keycodes
// before the shared logic below runs.
__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return process_record_keymap(keycode, record);
}

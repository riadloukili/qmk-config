#include "riad.h"

__attribute__((weak)) bool process_record_keymap(uint16_t keycode, keyrecord_t *record) {
    return true;
}

void keyboard_post_init_user(void) {
    host_layout_init();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    return process_record_keymap(keycode, record) && host_layout_process_record(keycode, record);
}

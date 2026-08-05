// NOTE: a host layout describes how the firmware talks to an OS configured
// with a given keyboard layout. Every layout, including US, implements this
// interface; US is only special in being the default.
#pragma once

#include QMK_KEYBOARD_H

typedef enum {
    HOST_LAYOUT_US = 0, // NOTE: 0 so a blank EEPROM boots US
    HOST_LAYOUT_CA,
    HOST_LAYOUT_COUNT,
} host_layout_id_t;

typedef struct {
    const char *name;
    uint8_t     default_layer;
    // NOTE: optional; handles keycodes the layout's layers cannot express directly.
    bool (*process_record)(uint16_t keycode, keyrecord_t *record);
} host_layout_t;

extern const host_layout_t host_layout_us;
extern const host_layout_t host_layout_ca;

void host_layout_init(void);
void host_layout_set(host_layout_id_t id);
bool host_layout_set_name(const char *name);
bool host_layout_process_record(uint16_t keycode, keyrecord_t *record);

host_layout_id_t host_layout_active(void);
const char      *host_layout_active_name(void);

// NOTE: a host layout describes how the firmware talks to an OS configured
// with a given keyboard layout. Every layout, including US, implements this
// interface; US is only special in being the default.
//
// An arrangement is a reorder of a layout's alphas (colemak-dh, dvorak, ...).
// Each (layout, arrangement) pair is its own base layer; switching either
// axis is only ever default_layer_set.
#pragma once

#include QMK_KEYBOARD_H

typedef enum {
    HOST_LAYOUT_US = 0, // NOTE: 0 so a blank EEPROM boots US
    HOST_LAYOUT_CA,
    HOST_LAYOUT_COUNT,
} host_layout_id_t;

#define HOST_ARRANGEMENT_MAX 5

typedef struct {
    const char *name;
    uint8_t     base_layer;
} host_arrangement_t;

typedef struct {
    const char *name;
    // NOTE: slot 0 is the vanilla QWERTY-ordered base; a blank EEPROM decodes
    // to it. Unused slots stay zeroed.
    host_arrangement_t arrangements[HOST_ARRANGEMENT_MAX];
    uint8_t            arrangement_count;
    // NOTE: optional; handles keycodes the layout's layers cannot express
    // directly.
    bool (*process_record)(uint16_t keycode, keyrecord_t *record);
} host_layout_t;

extern const host_layout_t host_layout_us;
extern const host_layout_t host_layout_ca;

void host_layout_init(void);
bool host_layout_set_name(const char *name);
bool host_layout_process_record(uint16_t keycode, keyrecord_t *record);

host_layout_id_t host_layout_active(void);
const char      *host_layout_active_name(void);

// NOTE: arrangements are addressed within the active layout; each layout
// remembers its own choice.
bool        host_arrangement_set_name(const char *name);
uint8_t     host_arrangement_active(void);
const char *host_arrangement_active_name(void);

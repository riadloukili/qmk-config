#include "riad.h"
#include "print.h"

static const host_layout_t *const host_layouts[HOST_LAYOUT_COUNT] = {
    [HOST_LAYOUT_US] = &host_layout_us,
    [HOST_LAYOUT_CA] = &host_layout_ca,
};

_Static_assert(LAY_CA - LAY_US == HOST_LAYOUT_COUNT - 1, "LAY_* keycodes must mirror host_layout_id_t");
_Static_assert(ARR_5 - ARR_1 == HOST_ARRANGEMENT_MAX - 1, "ARR_* keycodes must cover HOST_ARRANGEMENT_MAX");

// NOTE: byte 0 holds the layout id; each layout's arrangement index lives in
// a 3-bit field starting at bit 8, so a legacy or blank EEPROM word decodes
// as the vanilla arrangement everywhere.
#define ARRANGEMENT_BITS 3
#define ARRANGEMENT_SHIFT(id) (8 + (id) * ARRANGEMENT_BITS)
#define ARRANGEMENT_MASK 0x7

_Static_assert(HOST_ARRANGEMENT_MAX <= ARRANGEMENT_MASK + 1, "arrangement index must fit its bitfield");
_Static_assert(ARRANGEMENT_SHIFT(HOST_LAYOUT_COUNT) <= 32, "arrangement bits overflow the user EEPROM word");

typedef union {
    uint32_t raw;
    struct {
        uint8_t host_layout;
    };
} user_config_t;

static user_config_t config;

static const host_layout_t *active(void) {
    return host_layouts[config.host_layout];
}

static uint8_t stored_arrangement(host_layout_id_t id) {
    return (config.raw >> ARRANGEMENT_SHIFT(id)) & ARRANGEMENT_MASK;
}

static void store_arrangement(host_layout_id_t id, uint8_t index) {
    config.raw &= ~((uint32_t)ARRANGEMENT_MASK << ARRANGEMENT_SHIFT(id));
    config.raw |= (uint32_t)index << ARRANGEMENT_SHIFT(id);
}

static const host_arrangement_t *active_arrangement(void) {
    const host_layout_t *layout = active();
    uint8_t              index  = stored_arrangement(config.host_layout);
    // NOTE: clamp instead of reject; the EEPROM may predate a shrunk table.
    return &layout->arrangements[index < layout->arrangement_count ? index : 0];
}

static void apply(void) {
    default_layer_set((layer_state_t)1 << active_arrangement()->base_layer);
    uprintf("host layout: %s, arrangement: %s\n", active()->name, active_arrangement()->name);
}

void host_layout_init(void) {
    config.raw = eeconfig_read_user();
    if (config.host_layout >= HOST_LAYOUT_COUNT) {
        config.host_layout = HOST_LAYOUT_US;
    }
    apply();
}

// NOTE: internal; callers outside address a layout by name (the HID API) or
// by keycode.
static void host_layout_set(host_layout_id_t id) {
    if (id >= HOST_LAYOUT_COUNT) {
        return;
    }
    if (id != config.host_layout) {
        config.host_layout = id;
        eeconfig_update_user(config.raw);
    }
    apply();
}

bool host_layout_set_name(const char *name) {
    for (uint8_t id = 0; id < HOST_LAYOUT_COUNT; id++) {
        if (strcmp(host_layouts[id]->name, name) == 0) {
            host_layout_set((host_layout_id_t)id);
            return true;
        }
    }
    return false;
}

host_layout_id_t host_layout_active(void) {
    return (host_layout_id_t)config.host_layout;
}

const char *host_layout_active_name(void) {
    return active()->name;
}

// NOTE: internal; callers outside address an arrangement by name (the HID
// API) or by keycode.
static void host_arrangement_set(uint8_t index) {
    if (index >= active()->arrangement_count) {
        return;
    }
    if (index != stored_arrangement(config.host_layout)) {
        store_arrangement((host_layout_id_t)config.host_layout, index);
        eeconfig_update_user(config.raw);
    }
    apply();
}

bool host_arrangement_set_name(const char *name) {
    const host_layout_t *layout = active();
    for (uint8_t index = 0; index < layout->arrangement_count; index++) {
        if (strcmp(layout->arrangements[index].name, name) == 0) {
            host_arrangement_set(index);
            return true;
        }
    }
    return false;
}

uint8_t host_arrangement_active(void) {
    return (uint8_t)(active_arrangement() - active()->arrangements);
}

const char *host_arrangement_active_name(void) {
    return active_arrangement()->name;
}

bool host_layout_process_record(uint16_t keycode, keyrecord_t *record) {
    // WARN: relies on LAY_*/ARR_* keycodes matching the id/index order.
    if (keycode >= LAY_US && keycode < LAY_US + HOST_LAYOUT_COUNT) {
        if (record->event.pressed) {
            host_layout_set((host_layout_id_t)(keycode - LAY_US));
        }
        return false;
    }
    if (keycode >= ARR_1 && keycode < ARR_1 + HOST_ARRANGEMENT_MAX) {
        if (record->event.pressed) {
            host_arrangement_set((uint8_t)(keycode - ARR_1));
        }
        return false;
    }

    if (active()->process_record != NULL) {
        return active()->process_record(keycode, record);
    }
    return true;
}

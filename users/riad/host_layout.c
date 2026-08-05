#include "riad.h"
#include "print.h"

static const host_layout_t *const host_layouts[HOST_LAYOUT_COUNT] = {
    [HOST_LAYOUT_US] = &host_layout_us,
    [HOST_LAYOUT_CA] = &host_layout_ca,
};

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

static void apply(void) {
    default_layer_set((layer_state_t)1 << active()->default_layer);
}

void host_layout_init(void) {
    config.raw = eeconfig_read_user();
    if (config.host_layout >= HOST_LAYOUT_COUNT) {
        config.host_layout = HOST_LAYOUT_US;
    }
    apply();
    uprintf("host layout: %s\n", active()->name);
}

void host_layout_set(host_layout_id_t id) {
    if (id != config.host_layout) {
        config.host_layout = id;
        eeconfig_update_user(config.raw);
    }
    apply();
    uprintf("host layout: %s\n", active()->name);
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

bool host_layout_process_record(uint16_t keycode, keyrecord_t *record) {
    // WARN: relies on LAY_* keycodes matching host_layout_id_t order.
    if (keycode >= LAY_US && keycode < LAY_US + HOST_LAYOUT_COUNT) {
        if (record->event.pressed) {
            host_layout_set((host_layout_id_t)(keycode - LAY_US));
        }
        return false;
    }

    if (active()->process_record != NULL) {
        return active()->process_record(keycode, record);
    }
    return true;
}

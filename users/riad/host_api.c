// NOTE: raw HID query API for host-side tooling (widgets, scripts).
// Request:  byte 0 = command, rest per command.
// Response: byte 0 echoes the command (0xFF on error), byte 1 = layout id,
//           bytes 2.. = layout name, NUL-terminated.
#include "riad.h"
#include "raw_hid.h"

enum host_api_command {
    HOST_API_GET_LAYOUT = 0x01,
    HOST_API_SET_LAYOUT = 0x02, // NOTE: bytes 1..: layout name; a missing NUL is tolerated
};

void raw_hid_receive(uint8_t *data, uint8_t length) {
    // NOTE: QMK always passes RAW_EPSIZE (32) byte reports; the guard is cheap.
    if (length < 2) {
        return;
    }

    uint8_t command = data[0];
    bool    ok      = true;

    switch (command) {
        case HOST_API_GET_LAYOUT:
            break;
        case HOST_API_SET_LAYOUT: {
            // NOTE: forced terminator; the payload may not carry its own NUL.
            data[length - 1] = '\0';
            ok               = host_layout_set_name((const char *)&data[1]);
            break;
        }
        default:
            ok = false;
            break;
    }

    memset(data, 0, length);
    if (ok) {
        const char *name = host_layout_active_name();
        data[0]          = command;
        data[1]          = host_layout_active();
        // NOTE: the bound leaves data[length - 1] zeroed from the memset, so
        // the name is always NUL-terminated even when truncated.
        for (uint8_t i = 0; name[i] != '\0' && i < length - 3; i++) {
            data[2 + i] = (uint8_t)name[i];
        }
    } else {
        data[0] = 0xFF;
    }
    raw_hid_send(data, length);
}

#include "riad.h"

const host_layout_t host_layout_us = {
    .name = "us",
    .arrangements =
        {
            {.name = "qwerty", .base_layer = _US_BASE},
            {.name = "colemak-dh", .base_layer = _US_CDH_BASE},
        },
    .arrangement_count = 2,
};

#include "riad.h"

#include "layers/shared.h"
#include "layers/us.h"
#include "layers/ca.h"

// clang-format off

// WARN: keep entries in enum order; the draw pipeline reads them textually.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_US_BASE]    = LAYER_US_BASE,
    [_CA_BASE]    = LAYER_CA_BASE,

    [_FN]         = LAYER_FN,
    [_NAV]        = LAYER_NAV,
    [_MEDIA]      = LAYER_MEDIA,
    [_MOUSE]      = LAYER_MOUSE,

    [_US_NUM]     = LAYER_US_NUM,
    [_US_SYM]     = LAYER_US_SYM,

    [_CA_NUM]     = LAYER_CA_NUM,
    [_CA_SYM]     = LAYER_CA_SYM,
    [_CA_ACCENTS] = LAYER_CA_ACCENTS,
};

// clang-format on

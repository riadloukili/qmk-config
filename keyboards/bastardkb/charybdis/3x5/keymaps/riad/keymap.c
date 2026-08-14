// NOTE: layer content lives in users/riad/layers/; this file only binds it
// to this board's LAYOUT macro.
#include "riad.h"

// NOTE: variadic indirection so row fragments expand before LAYOUT's arity
// check.
#define LAYOUT_wrapper(...) LAYOUT(__VA_ARGS__)

#include "layers/shared.h"
#include "layers/us.h"
#include "layers/ca.h"

// clang-format off

// WARN: keep entries in enum order; the draw pipeline reads them textually.
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_US_BASE]     = LAYER_US_BASE,
    [_US_CDH_BASE] = LAYER_US_CDH_BASE,
    [_CA_BASE]     = LAYER_CA_BASE,
    [_CA_CDH_BASE] = LAYER_CA_CDH_BASE,

    [_FN]          = LAYER_FN,
    [_NAV]         = LAYER_NAV,
    [_MEDIA]       = LAYER_MEDIA,
    [_MOUSE]       = LAYER_MOUSE,

    [_US_NUM]      = LAYER_US_NUM,
    [_US_SYM]      = LAYER_US_SYM,

    [_CA_NUM]      = LAYER_CA_NUM,
    [_CA_SYM]      = LAYER_CA_SYM,
    [_CA_ACCENTS]  = LAYER_CA_ACCENTS,
};

// clang-format on

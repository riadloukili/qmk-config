#pragma once

// WARN: USB goes into the right half. Without this, whichever half is plugged
// in is treated as the left one and the layout comes out mirrored.
#define MASTER_RIGHT

// NOTE: tap reset twice to enter the bootloader.
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U

#pragma once
#include QMK_KEYBOARD_H
#include "src/features/remap/remap.h"

// OS
// writes defintions from keymap/features/remap.def
// REMAP(KEY, MODIFIER, REMAPPED_KEYCODE)

#define REMAP(KEYCODE, MODIFIER, REMAPPED_KEYCODE) {KEY, MODIFIER, REMAPPED_KEYCODE},

uint16_t remaps[] = {
#include "features/remap.def"
};

const uint8_t PROGMEM REMAP_COUNT = (sizeof(remaps) / sizeof(remaps[0]));
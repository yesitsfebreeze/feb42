#ifdef REMAP_ENABLE
#  pragma once
#  include QMK_KEYBOARD_H
#  include "keymap.h"
#  include "src/remap.h"

// writes defintions from keymap/remap.def
// REMAP(KEY, MODIFIER, REMAPPED_KEYCODE)

#  define REMAP(OS, ORIGINAL, MODMASK, REMAPPED) {OST_##OS, ORIGINAL, MOD_MASK_##MODMASK, REMAPPED},

remap_t remaps[] = {
#  include "remap.def"
};

const uint8_t PROGMEM REMAP_COUNT = (sizeof(remaps) / sizeof(remaps[0]));

#endif
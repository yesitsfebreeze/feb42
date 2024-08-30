#ifdef REMAP_ENABLE
#  pragma once
#  include QMK_KEYBOARD_H
#  include "src/defines.h"
#  include "keymap.h"
#  include "src/features/remap/remap.h"

// OS
// writes defintions from keymap/features/remap.def
// REMAP(KEY, MODIFIER, REMAPPED_KEYCODE)

#  define REMAP(KEYCODE, MODIFIER, REMAPPED_KEYCODE) {KEYCODE, MOD_MASK_##MODIFIER, REMAPPED_KEYCODE},

remap_t remaps[] = {
#  include "features/remap.def"
};

const uint8_t PROGMEM REMAP_COUNT = (sizeof(remaps) / sizeof(remaps[0]));

#endif
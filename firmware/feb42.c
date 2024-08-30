#include "feb42.h"
#include "src/buffer.h"
#include QMK_KEYBOARD_H
// // #include "keymap.h"
// // #include "src/rgb.h"
// // #include "src/defines.h"
// // #include "src/process.h"

#ifdef CONSOLE_ENABLE
#  include "print.h"
#endif

#ifdef REMAP_ENABLE
#  include "src/features/remap/remap.h"
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // never mess with the bootloader key

  if (keycode == QK_BOOT) return true;

  uint16_t current = keycode;

#include "src/features/remap/feature.inc"

  if (process_buffer(keycode, current, record)) {
    return false;
  }

  return true;
}
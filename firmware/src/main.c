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
  uint16_t current_keycode = keycode;

#ifdef REMAP_ENABLE
  process_remap(&current_keycode, record);
#endif

  if (keycode != current_keycode) {
    unregister_code16(keycode);
    register_code16(current_keycode);
    return false;
  }

  return true;
}
#include "feb42.h"
#include "src/mods.h"
#include "src/buffer.h"
#include QMK_KEYBOARD_H
// // #include "keymap.h"
// // #include "src/rgb.h"
// // #include "src/process.h"

#ifdef CONSOLE_ENABLE
#  include "print.h"
#endif

#ifdef REMAP_ENABLE
#  include "src/remap.h"
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool cancel = false;

  // never mess with the bootloader key
  if (keycode == QK_BOOT) return !cancel;

  uint16_t current = keycode;
  store_mods(current, record);

#ifdef REMAP_ENABLE
  if (!cancel) cancel = process_remap(&current, record);
#endif
  if (!cancel) cancel = process_feb42(&current, record);
  if (!cancel) cancel = process_buffer(keycode, current, record);

  restore_mods();
  return !cancel;
}
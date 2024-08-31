#include "feb42.h"

#include QMK_KEYBOARD_H
#include "src/os.h"
#include "src/mods.h"
#include "src/buffer.h"

#ifdef CONSOLE_ENABLE
#  include "print.h"
#endif

#ifdef COMBO_ENABLE
#  include "combo.def.h"
#endif

#ifdef REMAP_ENABLE
#  include "src/remap.h"
#endif

#ifdef RGB_MATRIX_ENABLE
#  include "src/rgb.h"
#endif

void keyboard_post_init_user(void) {
#ifdef CONSOLE_ENABLE
  debug_enable = true;
#endif
#ifdef RGB_MATRIX_ENABLE
  init_rgb();
#endif
  init_feb42();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool cancel = false;

  // never mess with the bootloader key
  if (keycode == QK_BOOT) return !cancel;

  uint16_t current = keycode;

  store_mods(current, record);
  if (!cancel) cancel = exec_os(current, record);

#ifdef RGB_MATRIX_ENABLE
  if (!cancel) cancel = exec_rgb(current, record);
#endif
#ifdef REMAP_ENABLE
  if (!cancel) exec_remap(&current, record);
#endif
  if (!cancel) cancel = exec_feb42(&current, record);
  if (!cancel) cancel = exec_buffer(keycode, current, record);

  restore_mods();
  return !cancel;
}

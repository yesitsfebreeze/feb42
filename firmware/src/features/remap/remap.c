#include "remap.h"

uint16_t get_remapped_key(uint16_t *keycode, uint8_t mods) {
  uint16_t idx = 0;
  for (idx = 0; idx < REMAP_COUNT; ++idx) {
    remap_t *remap = &remaps[idx];
    if (remap->key == *keycode && (mods & remap->modifier) == remap->modifier) {
      return remap->remap;
    }
  }

  return KC_NO;
}

bool process_remap(uint16_t *keycode, keyrecord_t *record) {
  if (!record->event.pressed) return true;

  // never mess with the bootloader key
  if (*keycode == QK_BOOT) return true;

  uint8_t mods = get_mods();

  uint16_t new_keycode = get_remapped_key(keycode, mods);
  if (new_keycode == KC_NO) return true;
  *keycode = new_keycode;

  return false;
}
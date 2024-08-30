#ifdef REMAP_ENABLE
#  include "remap.h"

#  include "./def.h"

uint16_t get_remapped_key(uint16_t *keycode, uint8_t mods) {
  uint16_t idx = 0;
  for (idx = 0; idx < REMAP_COUNT; ++idx) {
    remap_t *remap = &remaps[idx];
    if (*keycode == remap->keycode && (mods & remap->modifier) > 0) {
      return remap->remap;
    }
  }
  return KC_NO;
}

bool process_remap(uint16_t *keycode, keyrecord_t *record) {
  if (!record->event.pressed) return true;
  const uint8_t mods        = get_mods() | get_oneshot_mods() | get_weak_mods();
  uint16_t      new_keycode = get_remapped_key(keycode, mods);
  if (new_keycode == KC_NO) return true;

  *keycode = new_keycode;

  return false;
}

#endif
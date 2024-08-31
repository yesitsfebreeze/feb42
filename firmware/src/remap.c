#ifdef REMAP_ENABLE
#  include "remap.h"

#  include "remap.def.h"
#  include "os.h"
#  include "mods.h"
#  include "buffer.h"

bool is_valid_remap(remap_t *remap, uint16_t *keycode) {
  uint8_t mods         = get_stored_mods();
  bool    correct_os   = remap->os == CURRENT_OS || remap->os == OS_NONE;
  bool    no_mods      = remap->mod_mask == MOD_MASK_NONE;
  bool    correct_mods = ((mods & ~remap->mod_mask) != mods) || no_mods;
  bool    correct_key  = remap->original == *keycode;

  if (!correct_key) return false;
  if (!correct_os) return false;
  if (!correct_mods) return false;

  return true;
}

uint16_t get_remap_key(uint16_t *keycode) {
  uint16_t idx = 0;
  for (idx = 0; idx < REMAP_COUNT; ++idx) {
    remap_t *remap = &remaps[idx];
    if (!is_valid_remap(remap, keycode)) continue;

    return remap->remapped;
  }
  return KC_NO;
}

bool exec_remap(uint16_t *keycode, keyrecord_t *record) {
  if (!record->event.pressed) return false;

  uint16_t new_keycode = get_remap_key(keycode);
  if (new_keycode == KC_NO) return false;

  *keycode = new_keycode;

  return true;
}

#endif
#ifdef REMAP_ENABLE
#  include "remap.h"

#  include "remap.def.h"
#  include "mods.h"
#  include "buffer.h"
enum OS_TYPE CURRENT_OS = OST_WIN;

bool process_os(uint16_t kc, keyrecord_t *rec) {
  switch (kc) {
#  ifdef REMAP_OS_WIN_ENABLE
    case OS_WIN:
      CURRENT_OS = OST_WIN;
      return true;
#  endif
#  ifdef REMAP_OS_MAC_ENABLE
    case OS_MAC:
      CURRENT_OS = OST_MAC;
      return true;
#  endif
#  ifdef REMAP_OS_LIN_ENABLE
    case OS_LIN:
      CURRENT_OS = OST_LIN;
      return true;
#  endif
    case OS:
      CURRENT_OS = (CURRENT_OS + 1) % OST_LAST;
      if (CURRENT_OS == OST_NONE) CURRENT_OS += 1;
      return true;
    default:
      return false;
  }
}

bool is_valid_remap(remap_t *remap, uint16_t *keycode) {
  bool correct_os   = remap->os == CURRENT_OS || remap->os == OST_NONE;
  bool no_mods      = remap->mod_mask == MOD_MASK_NONE;
  bool correct_mods = (CURRENT_MODS & ~remap->mod_mask) != CURRENT_MODS;
  bool correct_key  = remap->original == *keycode;

  if (!correct_key) return false;
  if (!correct_os) return false;
  if (!correct_mods && !no_mods) return false;

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

bool process_remap(uint16_t *keycode, keyrecord_t *record) {
  if (!record->event.pressed) return true;
  if (process_os(*keycode, record)) return true;

  uint16_t new_keycode = get_remap_key(keycode);
  if (new_keycode == KC_NO) return true;

  *keycode = new_keycode;

  return false;
}

#endif
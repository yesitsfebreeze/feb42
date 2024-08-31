#include "mods.h"

uint8_t STORED_MODS = MOD_MASK_NONE;

void store_mods(void) {
  STORED_MODS = get_mods();
  del_mods(MOD_MASK_ALL);
}

uint8_t get_stored_mods(void) {
  return STORED_MODS;
}

void restore_mods(void) {
  del_mods(MOD_MASK_ALL);
  add_mods(STORED_MODS);
}

void custom_mod_mask(uint16_t keycode, bool active) {
  uint8_t mod_mask = MOD_MASK_NONE;

  // clang-format off
  switch (keycode) {
    case KC_LCTL: mod_mask = MOD_MASK_CTRL_L; break;
    case KC_RCTL: mod_mask = MOD_MASK_CTRL_R; break;
    case KC_LGUI: mod_mask = MOD_MASK_GUI_L; break;
    case KC_RGUI: mod_mask = MOD_MASK_GUI_R; break;
    case KC_LALT: mod_mask = MOD_MASK_ALT_L; break;
    case KC_RALT: mod_mask = MOD_MASK_ALT_R; break;
    case KC_LSFT: mod_mask = MOD_MASK_SHIFT_L; break;
    case KC_RSFT: mod_mask = MOD_MASK_SHIFT_R; break;
    default: return;
  }
  // clang-format on

  if (active) {
    STORED_MODS |= mod_mask;
  } else {
    STORED_MODS &= ~mod_mask;
  }
}
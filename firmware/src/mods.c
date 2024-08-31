#include "mods.h"

uint8_t CURRENT_MODS = MOD_MASK_NONE;
uint8_t PREV_MODS    = MOD_MASK_NONE;

void store_mods(uint16_t keycode, keyrecord_t *record) {
  // bool pressed = record->event.pressed;
  // switch (keycode) {
  //   case KC_LCTL:
  //     if (pressed) {
  //       CURRENT_MODS |= MOD_MASK_CTRL_L; // Add left control
  //     } else {
  //       CURRENT_MODS &= ~MOD_MASK_CTRL_L; // Remove left control
  //     }
  //     break;
  //   case KC_RCTL:
  //     if (pressed) {
  //       CURRENT_MODS |= MOD_MASK_CTRL_R; // Add right control
  //     } else {
  //       CURRENT_MODS &= ~MOD_MASK_CTRL_R; // Remove right control
  //     }
  //     break;
  //   case KC_LGUI:
  //     if (pressed) {
  //       CURRENT_MODS |= MOD_MASK_GUI_L; // Add left gui
  //     } else {
  //       CURRENT_MODS &= ~MOD_MASK_GUI_L; // Remove left gui
  //     }
  //     break;
  //   case KC_RGUI:
  //     if (pressed) {
  //       CURRENT_MODS |= MOD_MASK_GUI_R; // Add right gui
  //     } else {
  //       CURRENT_MODS &= ~MOD_MASK_GUI_R; // Remove right gui
  //     }
  //     break;
  //   case KC_LALT:
  //     if (pressed) {
  //       CURRENT_MODS |= MOD_MASK_ALT_L; // Add left alt
  //     } else {
  //       CURRENT_MODS &= ~MOD_MASK_ALT_L; // Remove left alt
  //     }
  //     break;
  //   case KC_RALT:
  //     if (pressed) {
  //       CURRENT_MODS |= MOD_MASK_ALT_R; // Add right alt
  //     } else {
  //       CURRENT_MODS &= ~MOD_MASK_ALT_R; // Remove right alt
  //     }
  //     break;
  //   case KC_LSFT:
  //     if (pressed) {
  //       CURRENT_MODS |= MOD_MASK_SHIFT_L; // Add left shift
  //     } else {
  //       CURRENT_MODS &= ~MOD_MASK_SHIFT_L; // Remove left shift
  //     }
  //     break;
  //   case KC_RSFT:
  //     if (pressed) {
  //       CURRENT_MODS |= MOD_MASK_SHIFT_R; // Add right shift
  //     } else {
  //       CURRENT_MODS &= ~MOD_MASK_SHIFT_R; // Remove right shift
  //     }
  //     break;
  // }

  // del_mods(MOD_MASK_CSAG);
  // // add_mods(PREV_MODS);
}

void restore_mods(void) {
  // del_mods(MOD_MASK_CSAG);
  // add_mods(PREV_MODS);
}
#include QMK_KEYBOARD_H
#include "custom.h"
#include "keymap.h"
#include "src/os.h"

bool _tab_enabled = false;
bool _tab_ctl     = false;
bool _tab_gui     = false;
bool _tab_alt     = false;
bool _tab_any     = false;

void exec_tabbing(uint16_t keycode, keyrecord_t *record) {
  uint8_t layer = get_highest_layer(layer_state);
  if (layer == GAME) return;

  if (keycode == KC_LCTL) _tab_ctl = record->event.pressed;
  if (keycode == KC_LGUI) _tab_gui = record->event.pressed;
  if (keycode == KC_LALT) _tab_alt = record->event.pressed;

  _tab_any = _tab_ctl || _tab_gui || _tab_alt;

  if (record->event.pressed) {
    if (keycode != KC_TAB) return;
    if (_tab_enabled) return;
    if (!_tab_any) return;
    if (CURRENT_OS == OS_MAC) {
      if (_tab_alt) {
        unregister_code16(KC_LALT);
        del_mods(MOD_MASK_ALT_L);
        register_code16(KC_LGUI);
      }
      if (_tab_gui) {
        unregister_code16(KC_LGUI);
        del_mods(MOD_MASK_GUI_L);
        register_code16(KC_LCTL);
      }
    }

    layer_move(LOWER);
    _tab_enabled = true;
  } else {
    if (!_tab_enabled) return;

    if (CURRENT_OS == OS_MAC && keycode == KC_LALT) {
      unregister_code16(KC_LGUI);
      _tab_alt = false;
    }
    if (CURRENT_OS == OS_MAC && keycode == KC_LGUI) {
      unregister_code16(KC_LCTL);
      _tab_gui = false;
    }
    _tab_any = _tab_ctl || _tab_gui || _tab_alt;

    if (_tab_any) return;

    layer_move(BASE);
    _tab_enabled = false;
  }
}
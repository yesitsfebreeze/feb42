#include QMK_KEYBOARD_H
#include "keymap.h"

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE]  = LAYOUT(
    KC_ESC,   KC_Q,     KC_W,     KC_E,     KC_R,    KC_T,      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_EQL,
    KC_TAB,   KC_A,     KC_S,     KC_D,     KC_F,    KC_G,      KC_H,     KC_J,     KC_K,     KC_L,               KC_ENT,
    KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,    KC_B,      KC_N,     KC_M,               KC_COMM,  KC_DOT,   KC_DEL,
    KC_LCTL,  KC_LGUI,  KC_LALT,            LT_L,               LT_R,                         KC_SLASH, KC_MINS,  KC_UNDS
  ),
  [LOWER] = LAYOUT(
    _______,  KC_HOME,  KC_UP,    KC_END,   KC_LBRC,  KC_RBRC,  _______,  _______,  KC_AMPR,  KC_PIPE,  MA_PTR,   _______,
    _______,  KC_LEFT,  KC_DOWN,  KC_RIGHT, KC_LPRN,  KC_RPRN,  _______,  _______,  KC_SCLN,  KC_QUOT,            KC_BSPC,
    _______,  CK_CTLZ,  CK_CTLX,  CK_CTLC,  CK_CTLV,  _______,  _______,  _______,  KC_LALT,            _______,  _______,
    _______,  _______,  _______,            _______,            LT_C,                         _______,  _______,  _______
  ),
  [RAISE] = LAYOUT(
    _______,  KC_1,     KC_2,     KC_3,     _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,
    KC_0,     KC_4,     KC_5,     KC_6,     _______,  _______,  _______,  _______,  KC_SCLN,  KC_QUOT,            KC_BSPC,
    _______,  KC_7,     KC_8,     KC_9,     _______,  _______,  _______,  _______,  _______,            _______,  _______,
    _______,  _______,  _______,            LT_C,               _______,                      _______,  _______,  _______
  ),
  [COMBO] = LAYOUT(
    OS,       KC_MB1,   KC_MS_U,  KC_MB2,   KC_F1,    KC_F2,    KC_F3,    _______,  _______,  _______,  _______,  QK_BOOT,
    _______,  KC_MS_L,  KC_MS_D,  KC_MS_R,  KC_F4,    KC_F5,    KC_F6,    _______,  _______,  _______,            CK_SENT,
    _______,  KC_WH_U,  KC_MB3,   KC_WH_D,  KC_F7,    KC_F8,    KC_F9,    KC_F10,   TO(GAME),           KC_F12,   _______,
    _______,  _______,  _______,            _______,            _______,                      _______,  _______,  RGB_TOG
  ),
  [GAME] = LAYOUT(
    KC_1,     KC_C,     KC_W,     KC_E,     KC_R,     KC_T,     KC_F5,    KC_F4,    KC_F3,    KC_F2,    KC_F1,    KC_ESC,
    KC_2,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,            KC_ENT,
    KC_LSFT,  KC_Q,     KC_4,     KC_X,     KC_B,     KC_B,     xxxxxxx,  xxxxxxx,  TO(BASE),           KC_UP,    KC_LSFT,
    KC_LCTL,  KC_LALT,  KC_3,               KC_SPC,             CK_STATS,                     KC_LEFT,  KC_DOWN,  KC_RIGHT
  ),
};
// clang-format on

// you can do custom stuff here

void init_feb42(void) {}

bool exec_feb42(uint16_t *keycode, keyrecord_t *record) {
  return false;
}
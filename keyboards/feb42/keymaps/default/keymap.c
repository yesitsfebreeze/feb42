#include QMK_KEYBOARD_H
#include "keymap.h"
#include "src/rgb.h"
#include "src/defines.h"
#include "src/process.h"

uint16_t process_remaps(uint16_t kc, ModState ms) {
  if (kc == KC_ESC && ms.ALT) return KC_TAB;
  if (kc == KC_ESC && ms.SHIFT) return KC_GRV;
  if (kc == KC_ESC && ms.SHIFT && ms.ALT) return KC_GRV;
  if (kc == KC_ENT && ms.SHIFT) return KC_BSPC;
  if (kc == CK_SENT) return RSFT(KC_ENT);
  if (kc == KC_QUOT && ms.SHIFT) return KC_QUOT;
  if (kc == KC_QUOT && ms.NONE) return KC_DQUO;
  if (kc == KC_UNDS && ms.SHIFT) return KC_UNDS;
  if (kc == KC_EQL && ms.SHIFT) return MA_COLCOL;
  if (kc == KC_LBRC && ms.SHIFT) return KC_LABK;
  if (kc == KC_RBRC && ms.SHIFT) return KC_RABK;
  if (kc == KC_LPRN && ms.SHIFT) return KC_LCBR;
  if (kc == KC_RPRN && ms.SHIFT) return KC_RCBR;
  if (kc == KC_AMPR && ms.SHIFT) return MA_AND;
  if (kc == KC_PIPE && ms.SHIFT) return MA_OR;
  if (kc == KC_COMM && ms.SHIFT) return KC_EXLM;
  if (kc == KC_DOT && ms.SHIFT) return KC_QUES;
  if (kc == KC_SLASH && ms.SHIFT) return KC_BACKSLASH;
  if (kc == KC_HOME && ms.CTRL) return KC_PGUP;
  if (kc == KC_END && ms.CTRL) return KC_PGDN;
  if (kc == KC_9 && ms.SHIFT) return KC_TILDE;
  if (kc == KC_MINS && ms.SHIFT) return KC_PPLS;

  return CK_NO;  
}

uint16_t process_os(uint16_t kc, ModState ms, int os) {
  if(os == OS_MAC) {
    switch(kc) {
      case KC_RIGHT:
        if (state.tabbing.enabled) break;
        if (ms.GUI && ms.SHIFT) return LSA(KC_RIGHT);
        if (ms.GUI) return LALT(KC_RIGHT);
        break;
      case KC_LEFT:
        if (state.tabbing.enabled) break;
        if (ms.GUI && ms.SHIFT) return LSA(KC_LEFT);
        if (ms.GUI) return LALT(KC_LEFT);
        break;
      case KC_LCTL:
        return KC_LGUI;
      case KC_LGUI:
        return KC_LCTL;
      case KC_HOME:
        if (state.tabbing.enabled) return LGUI(KC_Q);
        if (ms.GUI) return KC_PGUP;
        break;
      case KC_END:
        if (ms.GUI) return KC_PGDN;
        break;
      case CK_CTLZ:
        return LGUI(KC_Z);
      case CK_CTLX:
        return LGUI(KC_X);
      case CK_CTLC:
        return LGUI(KC_C);
      case CK_CTLV:
        return LGUI(KC_V);
    }
  } else {
    switch (kc) {
      case CK_CTLZ:
        return LCTL(KC_Z);
      case CK_CTLX:
        return LCTL(KC_X);
      case CK_CTLC:
        return LCTL(KC_C);
      case CK_CTLV:
        return LCTL(KC_V);
    }
  }

   return CK_NO;
}

char* process_macros(uint16_t kc) {
  if (kc == MA_OR) return "||";
  if (kc == MA_AND) return "&&";
  if (kc == MA_PTR) return "->";
  if (kc == MA_COLCOL) return "::";

  return "";
}
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [BASE]  = LAYOUT(
    KC_ESC,   KC_Q,     KC_W,     KC_E,     KC_R,    KC_T,      KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_EQL,
    KC_TAB,   KC_A,     KC_S,     KC_D,     KC_F,    KC_G,      KC_H,     KC_J,     KC_K,     KC_L,               KC_ENT,
    CK_HYPE,  KC_Z,     KC_X,     KC_C,     KC_V,    KC_B,      KC_N,     KC_M,               KC_COMM,  KC_DOT,   KC_DEL,
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
    CK_OS,    KC_MB1,   KC_MS_U,  KC_MB2,   KC_F1,    KC_F2,    KC_F3,    _______,  _______,  _______,  _______,  QK_BOOT,
    _______,  KC_MS_L,  KC_MS_D,  KC_MS_R,  KC_F4,    KC_F5,    KC_F6,    _______,  _______,  _______,            CK_SENT,
    _______,  KC_WH_U,  KC_MB3,   KC_WH_D,  KC_F7,    KC_F8,    KC_F9,    KC_F10,   TO(GAME),           KC_F12,   _______,
    _______,  _______,  _______,            _______,            _______,                      CK_RGB,   CK_RGBI,  RGB_TOG
  ),
  [GAME] = LAYOUT(
    KC_1,     KC_C,     KC_W,     KC_E,     KC_R,     KC_T,     KC_F5,    KC_F4,    KC_F3,    KC_F2,    KC_F1,    KC_ESC,
    KC_2,     KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     xxxxxxx,  xxxxxxx,  xxxxxxx,  xxxxxxx,            KC_ENT,
    KC_LSFT,  KC_Q,     KC_4,     KC_X,     KC_B,     KC_B,     xxxxxxx,  xxxxxxx,  TO(BASE),           KC_UP,    KC_LSFT,
    KC_LCTL,  KC_LALT,  KC_3,               KC_SPC,             CK_STATS,                     KC_LEFT,  KC_DOWN,  KC_RIGHT
  ),
};


#include QMK_KEYBOARD_H
#include "custom.h"
#include "keymap.h"
#include "src/os.h"

// Tabbing state management using flags
enum { TAB_NONE = 0, TAB_CTL = 1 << 0, TAB_GUI = 1 << 1, TAB_ALT = 1 << 2 };

uint8_t _tab_flags   = TAB_NONE;
bool    _tab_enabled = false;

void exec_tabbing(uint16_t keycode, keyrecord_t *record) {
  uint8_t layer = get_highest_layer(layer_state);
  if (layer == GAME) return;

  bool pressed = record->event.pressed;
  if (keycode == KC_LCTL) _tab_flags = pressed ? (_tab_flags | TAB_CTL) : (_tab_flags & ~TAB_CTL);
  if (keycode == KC_LGUI) _tab_flags = pressed ? (_tab_flags | TAB_GUI) : (_tab_flags & ~TAB_GUI);
  if (keycode == KC_LALT) _tab_flags = pressed ? (_tab_flags | TAB_ALT) : (_tab_flags & ~TAB_ALT);

  if (!pressed || keycode != KC_TAB || _tab_enabled || _tab_flags == TAB_NONE) return;

  if (CURRENT_OS == OS_MAC) {
    if (_tab_flags & TAB_ALT) {
      unregister_code16(KC_LALT);
      register_code16(KC_LGUI);
    }
    if (_tab_flags & TAB_GUI) {
      unregister_code16(KC_LGUI);
      register_code16(KC_LCTL);
    }
  }

  layer_move(LOWER);
  _tab_enabled = true;
}

void release_tabbing(uint16_t keycode) {
  if (!_tab_enabled) return;

  if (CURRENT_OS == OS_MAC) {
    if (keycode == KC_LALT) unregister_code16(KC_LGUI);
    if (keycode == KC_LGUI) unregister_code16(KC_LCTL);
  }

  if (!(_tab_flags & (TAB_CTL | TAB_GUI | TAB_ALT))) {
    layer_move(BASE);
    _tab_enabled = false;
  }
}

// In-game stats toggle logic
bool     _stats_enabled = false;
bool     _stats_exec    = false;
uint8_t  _stats_state   = 0;
uint16_t _stats_time    = 0;
uint16_t _stats_timer   = 0;
bool     _stats_running = false;
bool     _stats_caps    = false;

bool exec_stats(uint16_t keycode, keyrecord_t *record) {
  if (keycode != CK_STATS) return false;
  _stats_enabled = record->event.pressed;
  if (!_stats_enabled) return false;

  _stats_exec  = true;
  _stats_state = (timer_elapsed(_stats_timer) < _stats_time) ? 1 : 0;
  _stats_timer = timer_read();
  return true;
}

void scan_stats(void) {
  if (!_stats_exec) return;

  if (!_stats_enabled) {
    if (!_stats_running) return;
    _stats_exec = false;
    unregister_code16(KC_TAB);
    unregister_code16(KC_CAPS);
    if (_stats_caps) tap_code16(KC_CAPS);
    _stats_caps = _stats_running = false;
  } else if (!_stats_running) {
    if (_stats_state == 0) register_code16(KC_TAB);
    if (_stats_state == 1) register_code16(KC_CAPS);
    _stats_caps    = (_stats_state == 1);
    _stats_running = true;
  }
}

// Snaptap handling
uint16_t _snap_tap[2] = {KC_NO, KC_NO};

bool exec_snaptap(uint16_t keycode, keyrecord_t *record) {
  if (get_highest_layer(layer_state) != GAME || (keycode != KC_A && keycode != KC_D)) return false;

  uint16_t other_key = (keycode == KC_A) ? KC_D : KC_A;
  bool     pressed   = record->event.pressed;

  if (pressed) {
    if (_snap_tap[0] != keycode) {
      if (_snap_tap[0] != KC_NO) unregister_code16(_snap_tap[0]);
      _snap_tap[1] = _snap_tap[0];
      _snap_tap[0] = keycode;
      register_code16(keycode);
    }
  } else {
    if (keycode == _snap_tap[0]) {
      unregister_code16(keycode);
      if (_snap_tap[1] == other_key) register_code16(other_key);
      _snap_tap[0] = _snap_tap[1];
      _snap_tap[1] = KC_NO;
    } else if (keycode == _snap_tap[1]) {
      _snap_tap[1] = KC_NO;
    }
  }

  return true;
}

// Hyper key handling
bool     _hype_active = false;
int      _hype_taps   = 0;
uint16_t _hype_timer  = 0;

bool exec_hype(uint16_t keycode, keyrecord_t *record) {
  if (keycode != CK_HYPE) return false;
  _hype_active = record->event.pressed;
  _hype_timer  = timer_read();
  if (_hype_active) {
    _hype_taps++;
  } else {
    unregister_code16(KC_LSFT);
  }
  return true;
}

void scan_hype(void) {
  if (!_hype_active && timer_elapsed(_hype_timer) > TAPPING_TERM_SLOW) {
    if (_hype_taps > 0) _hype_taps--;
  }
  if (_hype_active) {
    if (_hype_taps == 2) {
      tap_code16(HYPR(KC_M));
      _hype_taps = 0;
    } else {
      register_code16(KC_LSFT);
    }
  }
}

// Tapping term configuration
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case LT_L:
    case LT_R:
    case LT_C:
      return TAPPING_TERM;
    default:
      return TAPPING_TERM_SLOW;
  }
}

#include QMK_KEYBOARD_H
#include "custom.h"
#include "keymap.h"
#include "src/os.h"

// Tabbing state management using flags
enum { TAB_NONE = 0, TAB_CTL = 1 << 0, TAB_GUI = 1 << 1, TAB_ALT = 1 << 2 };

uint8_t TAB_FLAGS      = TAB_NONE;
bool    TABBING_ACTIVE = false;

void exec_tabbing(uint16_t keycode, keyrecord_t *record) {
  uint8_t layer = get_highest_layer(layer_state);
  if (layer == GAME) return;

  bool pressed = record->event.pressed;
  if (keycode == KC_LCTL) TAB_FLAGS = pressed ? (TAB_FLAGS | TAB_CTL) : (TAB_FLAGS & ~TAB_CTL);
  if (keycode == KC_LGUI) TAB_FLAGS = pressed ? (TAB_FLAGS | TAB_GUI) : (TAB_FLAGS & ~TAB_GUI);
  if (keycode == KC_LALT) TAB_FLAGS = pressed ? (TAB_FLAGS | TAB_ALT) : (TAB_FLAGS & ~TAB_ALT);

  if (!pressed || keycode != KC_TAB || TABBING_ACTIVE || TAB_FLAGS == TAB_NONE) return;

  if (CURRENT_OS == OS_MAC) {
    if (TAB_FLAGS & TAB_ALT) {
      unregister_code16(KC_LALT);
      register_code16(KC_LGUI);
    }
    if (TAB_FLAGS & TAB_GUI) {
      unregister_code16(KC_LGUI);
      register_code16(KC_LCTL);
    }
  }

  layer_move(LOWER);
  TABBING_ACTIVE = true;
}

void release_tabbing(uint16_t keycode) {
  if (!TABBING_ACTIVE) return;

  if (CURRENT_OS == OS_MAC) {
    if (keycode == KC_LALT) unregister_code16(KC_LGUI);
    if (keycode == KC_LGUI) unregister_code16(KC_LCTL);
  }

  if (!(TAB_FLAGS & (TAB_CTL | TAB_GUI | TAB_ALT))) {
    layer_move(BASE);
    TABBING_ACTIVE = false;
  }
}

// In-game stats toggle logic
bool     STATS_ACTIVE  = false;
bool     STATS_EXEC    = false;
uint8_t  STATS_STATE   = 0;
uint16_t STATS_TIME    = 0;
uint16_t STATS_TIMER   = 0;
bool     STATS_RUNNING = false;
bool     STATS_CAPS    = false;

bool exec_stats(uint16_t keycode, keyrecord_t *record) {
  if (keycode != CK_STATS) return false;
  STATS_ACTIVE = record->event.pressed;
  if (!STATS_ACTIVE) return false;

  STATS_EXEC  = true;
  STATS_STATE = (timer_elapsed(STATS_TIMER) < STATS_TIME) ? 1 : 0;
  STATS_TIMER = timer_read();
  return true;
}

void scan_stats(void) {
  if (!STATS_EXEC) return;

  if (!STATS_ACTIVE) {
    if (!STATS_RUNNING) return;
    STATS_EXEC = false;
    unregister_code16(KC_TAB);
    unregister_code16(KC_CAPS);
    if (STATS_CAPS) tap_code16(KC_CAPS);
    STATS_CAPS = STATS_RUNNING = false;
  } else if (!STATS_RUNNING) {
    if (STATS_STATE == 0) register_code16(KC_TAB);
    if (STATS_STATE == 1) register_code16(KC_CAPS);
    STATS_CAPS    = (STATS_STATE == 1);
    STATS_RUNNING = true;
  }
}

// Snaptap handling
uint16_t SNAP_TAP[2] = {KC_NO, KC_NO};

bool exec_snaptap(uint16_t keycode, keyrecord_t *record) {
  if (get_highest_layer(layer_state) != GAME || (keycode != KC_A && keycode != KC_D)) return false;

  uint16_t other_key = (keycode == KC_A) ? KC_D : KC_A;
  bool     pressed   = record->event.pressed;

  if (pressed) {
    if (SNAP_TAP[0] != keycode) {
      if (SNAP_TAP[0] != KC_NO) unregister_code16(SNAP_TAP[0]);
      SNAP_TAP[1] = SNAP_TAP[0];
      SNAP_TAP[0] = keycode;
      register_code16(keycode);
    }
  } else {
    if (keycode == SNAP_TAP[0]) {
      unregister_code16(keycode);
      if (SNAP_TAP[1] == other_key) register_code16(other_key);
      SNAP_TAP[0] = SNAP_TAP[1];
      SNAP_TAP[1] = KC_NO;
    } else if (keycode == SNAP_TAP[1]) {
      SNAP_TAP[1] = KC_NO;
    }
  }

  return true;
}

// Hyper key handling
bool     HYPE_ACTIVE = false;
int      HYPE_TAPS   = 0;
uint16_t HYPE_TIMER  = 0;

bool exec_hype(uint16_t keycode, keyrecord_t *record) {
  if (keycode != CK_HYPE) return false;
  HYPE_ACTIVE = record->event.pressed;
  HYPE_TIMER  = timer_read();
  if (HYPE_ACTIVE) {
    HYPE_TAPS++;
  } else {
    unregister_code16(KC_LSFT);
  }
  return true;
}

void scan_hype(void) {
  if (!HYPE_ACTIVE && timer_elapsed(HYPE_TIMER) > TAPPING_TERM_SLOW) {
    if (HYPE_TAPS > 0) HYPE_TAPS--;
  }
  if (HYPE_ACTIVE) {
    if (HYPE_TAPS == 2) {
      tap_code16(HYPR(KC_M));
      HYPE_TAPS = 0;
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

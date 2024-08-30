#pragma once
#include QMK_KEYBOARD_H

typedef struct remap_t {
  uint16_t key;
  uint8_t  modifier;
  uint16_t remap;
} remap_t;

bool process_remap(uint16_t *keycode, keyrecord_t *record);

extern remap_t remaps[];

const extern uint8_t PROGMEM REMAP_COUNT;
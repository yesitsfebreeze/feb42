#ifdef REMAP_ENABLE
#  pragma once
#  include QMK_KEYBOARD_H
#  include "os.h"

typedef struct remap_t {
  enum OS_TYPE os;
  uint16_t     original;
  uint8_t      mod_mask;
  uint16_t     remapped;
} remap_t;

extern remap_t remaps[];

const extern uint8_t PROGMEM REMAP_COUNT;

bool exec_remap(uint16_t *keycode, keyrecord_t *record);

#endif
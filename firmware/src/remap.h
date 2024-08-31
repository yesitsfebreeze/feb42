#ifdef REMAP_ENABLE
#  pragma once
#  include QMK_KEYBOARD_H

enum OS_TYPE {
  OST_NONE,
#  ifdef REMAP_OS_WIN_ENABLE
  OST_WIN,
#  endif
#  ifdef REMAP_OS_MAC_ENABLE
  OST_MAC,
#  endif
#  ifdef REMAP_OS_LIN_ENABLE
  OST_LIN,
#  endif
  OST_LAST
};

extern enum OS_TYPE CURRENT_OS;

typedef struct remap_t {
  enum OS_TYPE os;
  uint16_t     original;
  uint8_t      mod_mask;
  uint16_t     remapped;
} remap_t;

extern remap_t remaps[];

const extern uint8_t PROGMEM REMAP_COUNT;

bool process_remap(uint16_t *keycode, keyrecord_t *record);

#endif
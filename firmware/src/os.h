#pragma once
#include QMK_KEYBOARD_H

enum OS_TYPE {
  OS_NONE,
#ifdef REMAP_OS_WIN_ENABLE
  OS_WIN,
#endif
#ifdef REMAP_OS_MAC_ENABLE
  OS_MAC,
#endif
#ifdef REMAP_OS_LIN_ENABLE
  OS_LIN,
#endif
  OS_LAST
};

extern enum OS_TYPE CURRENT_OS;

bool exec_os(uint16_t kc, keyrecord_t *rec);
#include "os.h"

enum OS_TYPE CURRENT_OS = OS_WIN;

bool exec_os(uint16_t kc, keyrecord_t *rec) {
  switch (kc) {
#ifdef REMAP_OS_WIN_ENABLE
    case WIN:
      CURRENT_OS = OS_WIN;
      return true;
#endif
#ifdef REMAP_OS_MAC_ENABLE
    case MAC:
      CURRENT_OS = OS_MAC;
      return true;
#endif
#ifdef REMAP_OS_LIN_ENABLE
    case LIN:
      CURRENT_OS = OS_LIN;
      return true;
#endif
    case OS:
      CURRENT_OS = (CURRENT_OS + 1) % OS_LAST;
      if (CURRENT_OS == OS_NONE) CURRENT_OS += 1;
      return true;
    default:
      return false;
  }
}
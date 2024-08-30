#include "./combos.h"

#ifdef COMBO_ENABLE
void process_combo_feature(void) {}

bool handle_combo_feature(uint16_t kc, keyrecord_t *rec) {
  return false;
}
#endif
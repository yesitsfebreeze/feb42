#pragma once

#ifdef COMBO_ENABLE
#  include QMK_KEYBOARD_H
#  include "./defintion.h"

void process_combo_feature(void);
bool handle_combo_feature(uint16_t kc, keyrecord_t *rec);
#endif
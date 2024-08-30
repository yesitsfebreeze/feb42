#pragma once
#include QMK_KEYBOARD_H
#define CORE_FEATURE_ENABLED 1

#include "./defintion.h"

void process_core(void);
bool handle_core(uint16_t kc, keyrecord_t *rec);
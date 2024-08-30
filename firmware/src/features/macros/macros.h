#pragma once
#include QMK_KEYBOARD_H
#define MACROS_FEATURE_ENABLED 1

#include "./defintion.h"

void process_macros(void);
bool handle_macros(uint16_t kc, keyrecord_t *rec);
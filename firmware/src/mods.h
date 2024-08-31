#pragma once
#include QMK_KEYBOARD_H

extern uint8_t CURRENT_MODS;

void store_mods(uint16_t keycode, keyrecord_t *record);
void restore_mods(void);
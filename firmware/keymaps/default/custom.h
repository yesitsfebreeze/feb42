#pragma once
#include QMK_KEYBOARD_H

void exec_tabbing(uint16_t keycode, keyrecord_t *record);
bool exec_snaptap(uint16_t keycode, keyrecord_t *record);
bool exec_stats(uint16_t keycode, keyrecord_t *record);
void scan_stats(void);
bool exec_hype(uint16_t keycode, keyrecord_t *record);
void scan_hype(void);

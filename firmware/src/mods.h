#pragma once
#include QMK_KEYBOARD_H

void    store_mods(void);
uint8_t get_stored_mods(void);
void    restore_mods(void);
void    custom_mod_mask(uint16_t keycode, bool active);
#pragma once
#include "src/defines.h"
#include QMK_KEYBOARD_H

#define CK_RGB  CK_INTERN_1
#define CK_RGBI CK_INTERN_2

#ifdef RGB_MATRIX_ENABLE

#define RGB_BASE   136, 0,   255
#define RGB_LOWER  3,   255, 74
#define RGB_RAISE  5,   59,  255
#define RGB_COMBO  255, 111, 0
#define RGB_GAME   255, 59,  5

#define RGB_LAYER_INDICATOR_KEY 24

#define RGB_LAYER_INDICATOR_W 41 
#define RGB_LAYER_INDICATOR_A 30
#define RGB_LAYER_INDICATOR_S 29
#define RGB_LAYER_INDICATOR_D 28

extern bool RGB_INDICATOR;
extern bool RGB_MODE;
extern uint8_t INDICATOR_R;
extern uint8_t INDICATOR_G;
extern uint8_t INDICATOR_B;

void init_rgb(void);
bool handle_rgb(uint16_t kc, keyrecord_t *rec);

#endif


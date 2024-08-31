#ifdef RGB_MATRIX_ENABLE
#  include "rgb.h"
#  include "keymap.h"
#  include "os.h"

bool RGB_INDICATOR = true;
bool RGB_MODE      = false;

uint8_t INDICATOR_R = 0;
uint8_t INDICATOR_G = 0;
uint8_t INDICATOR_B = 0;

uint8_t last_layer = BASE;

#  define RGB_MATRIX_MAX 41

// clang-format off
led_config_t g_led_config = {
  {
    { 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30 },
    { 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, NO_LED, 19 },
    { 18, 17, 16, 15, 14, 13, 12, 11, 10, NO_LED, 9, 8 },
    { 7, 6, 5, 4, NO_LED, NO_LED, 3, NO_LED, NO_LED, 2, 1, 0 }
  },
  {
    {224,64}, {204,64}, {183,64}, {135,64}, {84,64}, {48,64}, {25,64}, {3,64},
    {224,43}, {204,43}, {181,43}, {158,43}, {137,43}, {117,43}, {97,43}, {76,43}, {56,43}, {36,43}, {8,43},
    {216,21}, {188,21}, {168,21}, {148,21}, {127,21}, {107,21}, {87,21}, {66,21}, {46,21}, {25,21}, {3,21},
    {224,0}, {204,0}, {183,0}, {163,0}, {143,0}, {122,0}, {102,0}, {81,0}, {61,0}, {41,0}, {20,0}, {0,0}
  },
  {
    4, 4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 1, 1, 1, 1, 1, 1, 1, 4,
    4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4,
    4, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 4
  }
};
// clang-format on

HSV rgb_to_hsv(uint8_t r, uint8_t g, uint8_t b) {
  HSV   hsv;
  float nr = r / 255.0f;
  float ng = g / 255.0f;
  float nb = b / 255.0f;

  float max = fmaxf(nr, fmaxf(ng, nb));
  float min = fminf(nr, fminf(ng, nb));
  float d   = max - min;

  float hue = 0.0f;
  if (d != 0.0f) {
    if (max == nr) {
      hue = fmodf(((ng - nb) / d), 6.0f);
    } else if (max == ng) {
      hue = ((nb - nr) / d) + 2.0f;
    } else {
      hue = ((nr - ng) / d) + 4.0f;
    }
    hue *= 60.0f;
    if (hue < 0.0f) {
      hue += 360.0f;
    }
  }

  float s = (max != 0.0f) ? d / max : 0.0f;

  hsv.h = (uint8_t)((hue * 255.0f) / 360.0f);
  hsv.s = (uint8_t)(s * 255.0f);
  hsv.v = (uint8_t)(max * 255.0f);
  return hsv;
}

void set_color(uint8_t r, uint8_t g, uint8_t b) {
  INDICATOR_R = r;
  INDICATOR_G = g;
  INDICATOR_B = b;
  HSV hsv     = rgb_to_hsv(r, g, b);
  rgb_matrix_sethsv_noeeprom(hsv.h, hsv.s, hsv.v);
}

void set_rgb_mode(void) {
  rgb_matrix_set_speed(RGB_MATRIX_ANI_SPEED);
  rgb_matrix_disable();
  rgb_matrix_enable();

  if (RGB_MODE) {
    rgb_matrix_mode(RGB_MATRIX_CUSTOM_INVERSED_REACTIVE);
  } else {
    rgb_matrix_mode(RGB_MATRIX_CUSTOM_REACTIVE);
  }

  layer_move(BASE);
  layer_move(COMBO);
}

bool rgb_matrix_indicators_user(void) {
  if (!RGB_INDICATOR) return true;
  uint8_t current_layer = get_highest_layer(layer_state);

  if (current_layer == GAME) {
    rgb_matrix_set_color(RGB_LAYER_INDICATOR_KEY, 0, 0, 0);
    rgb_matrix_set_color(RGB_LAYER_INDICATOR_W - 2, INDICATOR_R, INDICATOR_G, INDICATOR_B);
    rgb_matrix_set_color(RGB_LAYER_INDICATOR_A - 2, INDICATOR_R, INDICATOR_G, INDICATOR_B);
    rgb_matrix_set_color(RGB_LAYER_INDICATOR_S - 2, INDICATOR_R, INDICATOR_G, INDICATOR_B);
    rgb_matrix_set_color(RGB_LAYER_INDICATOR_D - 2, INDICATOR_R, INDICATOR_G, INDICATOR_B);
  } else {
    if (RGB_MODE) {
      rgb_matrix_set_color(RGB_LAYER_INDICATOR_KEY, 0, 0, 0);
    } else {
      if (CURRENT_OS == OS_MAC) {
        rgb_matrix_set_color(RGB_LAYER_INDICATOR_KEY - 1, INDICATOR_R, INDICATOR_G, INDICATOR_B);
        rgb_matrix_set_color(RGB_LAYER_INDICATOR_KEY + 1, INDICATOR_R, INDICATOR_G, INDICATOR_B);
      } else {
        rgb_matrix_set_color(RGB_LAYER_INDICATOR_KEY, INDICATOR_R, INDICATOR_G, INDICATOR_B);
      }
    }
  }

  return true;
}

void layer_color_change(uint8_t layer) {
  switch (layer) {
    case GAME:
      set_color(RGB_GAME);
      break;
    case COMBO:
      set_color(RGB_COMBO);
      break;
    case LOWER:
      set_color(RGB_LOWER);
      break;
    case RAISE:
      set_color(RGB_RAISE);
      break;
    default:
      set_color(RGB_BASE);
      break;
  }
}

layer_state_t layer_state_set_user(layer_state_t state) {
  uint8_t layer = get_highest_layer(state);
  if (layer != last_layer) {
    layer_color_change(layer);
    last_layer = layer;
  }
  return state;
}

void init_rgb() {
  layer_color_change(BASE);
  set_rgb_mode();
  layer_move(BASE);
}

bool exec_rgb(uint16_t kc, keyrecord_t *rec) {
  if (!rec->event.pressed) return false;
  if (kc == CK_RGB) {
    RGB_MODE = !RGB_MODE;
  } else if (kc == CK_RGBI) {
    RGB_INDICATOR = !RGB_INDICATOR;
  } else {
    return false;
  }

  set_rgb_mode();
  return true;
}

#endif
#include "buffer.h"

#define BUFFER_SIZE 16

typedef struct key_t {
  uint16_t original;
  uint8_t  custom;
} key_t;

key_t buffer[BUFFER_SIZE] = {0};

void _release(uint8_t index) {
  unregister_code16(buffer[index].custom);
  buffer[index].original = KC_NO;
  buffer[index].custom   = KC_NO;
}

void _press(uint8_t slot, uint16_t original, uint8_t custom) {
  buffer[slot].original = original;
  buffer[slot].custom   = custom;

  unregister_code16(original);
  register_code16(custom);
}

int8_t _find_free(void) {
  for (int8_t i = 0; i < BUFFER_SIZE; i++) {
    if (buffer[i].original == KC_NO && buffer[i].custom == KC_NO) {
      return i;
    }
  }

  _release(0);
  return 0;
}

int8_t _find(uint16_t keycode) {
  for (int8_t i = 0; i < BUFFER_SIZE; i++) {
    if (buffer[i].original == keycode) {
      return i;
    }
  }
  return -1; // Not found
}

bool process_buffer(uint16_t original, uint16_t custom, keyrecord_t *record) {
  if (record->event.pressed) {
    if (original == custom) return false;
    if (custom == KC_NO) return false;

    int8_t slot = _find_free();
    _press(slot, original, custom);

    return true;
  } else {
    int8_t slot = _find(original);
    if (slot == -1) return false;
    _release(slot);

    return true;
  }

  return false;
}
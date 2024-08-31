#pragma once

// features
#define REMAP_ENABLE
#define REMAP_OS_WIN_ENABLE
#define REMAP_OS_MAC_ENABLE
// #define REMAP_OS_LIN_ENABLE

// Additional Mod Masks
#define MOD_MASK_NONE 0
#define MOD_MASK_CTRL_L (MOD_BIT(KC_LCTL))
#define MOD_MASK_CTRL_R (MOD_BIT(KC_RCTL))
#define MOD_MASK_ALT_L (MOD_BIT(KC_LALT))
#define MOD_MASK_ALT_R (MOD_BIT(KC_RALT))
#define MOD_MASK_GUI_L (MOD_BIT(KC_LGUI))
#define MOD_MASK_GUI_R (MOD_BIT(KC_RGUI))
#define MOD_MASK_SHIFT_L (MOD_BIT(KC_LSFT))
#define MOD_MASK_SHIFT_R (MOD_BIT(KC_RSFT))

#define LT_L LT(1, KC_SPC)
#define LT_R LT(2, KC_SPC)
#define LT_C LT(3, KC_SPC)

#define xxxxxxx KC_NO
#define CK_NO QK_UNICODE_MAX

#define CK_00 QK_KB_0
#define CK_01 QK_KB_1
#define CK_02 QK_KB_2
#define CK_03 QK_KB_3
#define CK_04 QK_KB_4
#define CK_05 QK_KB_5
#define CK_06 QK_KB_6
#define CK_07 QK_KB_7
#define CK_08 QK_KB_8
#define CK_09 QK_KB_9
#define CK_10 QK_KB_10
#define CK_11 QK_KB_11
#define CK_12 QK_KB_12
#define CK_13 QK_KB_13
#define CK_14 QK_KB_14
#define CK_15 QK_KB_15
#define CK_16 QK_KB_16
#define CK_17 QK_KB_17
#define CK_18 QK_KB_18
#define CK_19 QK_KB_19
#define CK_20 QK_KB_20
#define CK_21 QK_KB_21
#define CK_22 QK_KB_22
#define CK_23 QK_KB_23
#define CK_24 QK_KB_24
#define CK_25 QK_KB_25
#define CK_26 QK_KB_26
#define CK_27 QK_KB_27
#define CK_28 QK_KB_28
#define CK_29 QK_KB_29
#define CK_30 QK_KB_30
#define CK_31 QK_KB_31
#define CK_32 QK_USER_0
#define CK_33 QK_USER_1
#define CK_34 QK_USER_2
#define CK_35 QK_USER_3
#define CK_36 QK_USER_4
#define CK_37 QK_USER_5
#define CK_38 QK_USER_6
#define CK_39 QK_USER_7
#define CK_40 QK_USER_8
#define CK_41 QK_USER_9
#define CK_42 QK_USER_10
#define CK_43 QK_USER_11
#define CK_44 QK_USER_12
#define CK_45 QK_USER_13
#define CK_46 QK_USER_14
#define CK_47 QK_USER_15
#define CK_48 QK_USER_16
#define CK_49 QK_USER_17
#define CK_50 QK_USER_18
#define CK_51 QK_USER_19
#define CK_52 QK_USER_20
#define CK_53 QK_USER_21
#define CK_54 QK_USER_22
#define CK_55 QK_USER_23
#define CK_56 QK_USER_24
#define CK_57 QK_USER_25

// dont use/touch these
#define CK_RGB QK_USER_26
#define CK_RGBI QK_USER_27
#define OS_WIN QK_USER_28
#define OS_MAC QK_USER_29
#define OS_LIN QK_USER_30
#define OS QK_USER_31

// qmk config
#define FORCE_NKRO
#define TAPPING_TERM_PER_KEY
#define TAPPING_TERM 110
#define TAPPING_TERM_SLOW 180
#define COMBO_TERM 120

#define USB_POLLING_INTERVAL_MS 1

#ifdef RGB_MATRIX_ENABLE
#  define WS2812_DI_PIN B3
#  define RGB_MATRIX_LED_COUNT 42

#  define RGB_MATRIX_ANI_SPEED 64
#  define RGB_DISABLE_WHEN_USB_SUSPENDED

#  define RGBLIGHT_HUE_STEP 1
#  define RGBLIGHT_SAT_STEP 1
#  define RGBLIGHT_VAL_STEP 1

#  define RGB_MATRIX_KEYPRESSES
#  undef RGB_MATRIX_LED_PROCESS_LIMIT
#  undef RGB_MATRIX_LED_FLUSH_LIMIT
#endif

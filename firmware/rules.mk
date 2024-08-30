# https://github.com/qmk/qmk_firmware/blob/master/docs/faq_debug.md
CONSOLE_ENABLE        = yes
BOOTMAGIC_ENABLE      = yes
MOUSEKEY_ENABLE       = yes
EXTRAKEY_ENABLE       = yes
NKRO_ENABLE           = yes
SEND_STRING_ENABLE    = yes

# RGB_MATRIX_ENABLE     = yes
# RGB_MATRIX_CUSTOM_KB  = yes
# RGB_MATRIX_DRIVER     = ws2812
# SRC += src/rgb.c

SRC += src/process.c


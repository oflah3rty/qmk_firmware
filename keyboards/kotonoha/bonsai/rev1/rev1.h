#pragma once

#include "../bonsai.h"

//void promicro_bootloader_jmp(bool program);
#include "quantum.h"

#ifdef RGBLIGHT_ENABLE
//rgb led driver
#include "ws2812.h"
#endif

#ifdef USE_I2C
#include <stddef.h>
#ifdef __AVR__
	#include <avr/io.h>
	#include <avr/interrupt.h>
#endif
#endif

//void promicro_bootloader_jmp(bool program);
#define LAYOUT( \
         L01, L02, L03, L04, L05,      R01, R02, R03, R04, R05,      \
    L10, L11, L12, L13, L14, L15,      R10, R11, R12, R13, R14, R15, \
    L20,           L23,                          R20,           R23, \
                             L35, L36, R35, R36                      \
) \
{ \
    { KC_NO,   L01,   L02,   L03,   L04,   L05, KC_NO }, \
    {   L10,   L11,   L12,   L13,   L14,   L15, KC_NO }, \
    {   L20, KC_NO, KC_NO,   L23, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   L35,   L36 }, \
    { KC_NO,   R05,   R04,   R03,   R02,   R01, KC_NO }, \
    {   R15,   R14,   R13,   R12,   R11,   R10, KC_NO }, \
    {   R23, KC_NO, KC_NO,   R20, KC_NO, KC_NO, KC_NO }, \
    { KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,   R36,   R35 }  \
}

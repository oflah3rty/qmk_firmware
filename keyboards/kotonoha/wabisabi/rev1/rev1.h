#pragma once

#include "../wabisabi.h"

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
    L00, L01, L02, L03, L04, R00, R01, R02, R03, R04, \
    L10, L11, L12, L13, L14, R10, R11, R12, R13, R14, \
              L22, L23, L24, R22, R23, R24,           \
                   L33, L34, R33, R34                 \
) \
{ \
    {   L00,   L01,   L02,   L03,   L04 }, \
    {   L10,   L11,   L12,   L13,   L14 }, \
    { KC_NO, KC_NO,   L22,   L23,   L24 }, \
    { KC_NO, KC_NO, KC_NO,   L33,   L34 }, \
    {   R04,   R03,   R02,   R01,   R00 }, \
    {   R14,   R13,   R12,   R11,   R10 }, \
    { KC_NO, KC_NO,   R24,   R23,   R22 }, \
    { KC_NO, KC_NO, KC_NO,   R34,   R33 }  \
}

/*
Copyright 2019 %YOUR_NAME%

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID       0xF813
#define PRODUCT_ID      0x0003
#define DEVICE_VER      0x0001
#define MANUFACTURER    Minamo
#define PRODUCT         Kotonoha ichigoichie
#define DESCRIPTION     A custom keyboard

/* key matrix size */
#define MATRIX_ROWS 2
#define MATRIX_COLS 5

/*
 * Keyboard Matrix Assignments
 *
 * Change this to how you wired your keyboard
 * COLS: AVR pins used for columns, left to right
 * ROWS: AVR pins used for rows, top to bottom
 * DIODE_DIRECTION: COL2ROW = COL = Anode (+), ROW = Cathode (-, marked on diode)
 *                  ROW2COL = ROW = Anode (+), COL = Cathode (-, marked on diode)
 *
*/
#define MATRIX_ROW_PINS { B5, B4 }
#define MATRIX_COL_PINS { B6, B2, B3, B1, F7 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW

/*
 * Split Keyboard specific options, make sure you have 'SPLIT_KEYBOARD = yes' in your rules.mk, and define SOFT_SERIAL_PIN.
 */
#define SOFT_SERIAL_PIN D0 // or D1, D2, D3, E6

//#define BACKLIGHT_PIN D3
//#define BACKLIGHT_BREATHING
//#define BACKLIGHT_LEVELS 3

#define RGB_DI_PIN D3
#ifdef RGB_DI_PIN
  #define RGBLED_NUM 3
  #define RGBLIGHT_HUE_STEP 8
  #define RGBLIGHT_SAT_STEP 8
  #define RGBLIGHT_VAL_STEP 8
  #define RGBLIGHT_LIMIT_VAL 255 /* The maximum brightness level */
  #define RGBLIGHT_SLEEP  /* If defined, the RGB lighting will be switched off when the host goes to sleep */
/*== all animations enable ==*/
//  #define RGBLIGHT_ANIMATIONS
/*== or choose animations ==*/
//  #define RGBLIGHT_EFFECT_BREATHING
//  #define RGBLIGHT_EFFECT_RAINBOW_MOOD
//  #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
//  #define RGBLIGHT_EFFECT_SNAKE
//  #define RGBLIGHT_EFFECT_KNIGHT
//  #define RGBLIGHT_EFFECT_CHRISTMAS
//  #define RGBLIGHT_EFFECT_STATIC_GRADIENT
//  #define RGBLIGHT_EFFECT_RGB_TEST
//  #define RGBLIGHT_EFFECT_ALTERNATING
#endif

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCING_DELAY 5

/* define if matrix has ghost (lacks anti-ghosting diodes) */
//#define MATRIX_HAS_GHOST

/* number of backlight levels */

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

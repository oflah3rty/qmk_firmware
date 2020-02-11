/* Copyright 2019 Naoto Takai
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H

#define _BASE   0
#define _LOWER  1
#define _RAISE  2
#define _EXTEND 3
#define _FUNC   4
#define _MOUSE  5
#define _ADJUST 6

#define _______ KC_TRNS

#define KC_RST RESET
#define KC_DBUG DEBUG
#define KC_RTOG RGB_TOG
#define KC_RMOD RGB_MOD
#define KC_RRMD RGB_RMOD
#define KC_RHUI RGB_HUI
#define KC_RHUD RGB_HUD
#define KC_RSAI RGB_SAI
#define KC_RSAD RGB_SAD
#define KC_RVAI RGB_VAI
#define KC_RVAD RGB_VAD

#define KC_STAB LSFT_T(KC_TAB)
#define KC_CESC LCTL_T(KC_ESC)
#define KC_SENT LSFT_T(KC_ENT)
#define KC_XGUI GUI_T(KC_X)
#define KC_ZGUI GUI_T(KC_Z)
#define KC_ASPC LALT_T(KC_SPC)

#define KC_WADJ LT(_ADJUST, KC_W)
#define KC_DFNC LT(_FUNC, KC_D)
#define KC_GMOU LT(_MOUSE, KC_G)
#define KC_FEXT LT(_EXTEND, KC_F)

#define KC_VLOW LT(_LOWER, KC_V)
#define KC_NRAI LT(_RAISE, KC_N)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
    //,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
        KC_Q    , KC_WADJ , KC_E    , KC_R    , KC_T    , KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , KC_BSPC ,
        KC_STAB , KC_A    , KC_S    , KC_DFNC , KC_FEXT , KC_GMOU , KC_H    , KC_J    , KC_K    , KC_L    , KC_SENT ,
        KC_CESC , KC_ZGUI , KC_XGUI , KC_C    , KC_VLOW , KC_B    , KC_NRAI , KC_M    , KC_ASPC
    //`---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------'
    ),
    [_LOWER] = LAYOUT(
    //,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
        KC_TILD , KC_BSLS , _______ , _______ , _______ , KC_QUOT , KC_DQT  , KC_UNDS , KC_PIPE , KC_COLN , _______ ,
        _______ , KC_GRV  , KC_EQL  , KC_PLUS , KC_MINS , _______ , KC_LBRC , KC_RBRC , KC_LCBR , KC_RCBR , KC_SCLN ,
        _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______
    //`---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------'
    ),
    [_RAISE] = LAYOUT(
    //,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
        KC_EXLM , KC_AT   , KC_HASH , KC_DLR  , KC_PERC , KC_CIRC , KC_AMPR , KC_ASTR , KC_LPRN , KC_RPRN , _______ ,
        _______ , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    ,
        _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______
    //`---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------'
    ),
    [_EXTEND] = LAYOUT(
    //,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
        _______ , _______ , _______ , KC_ESC  , _______ , _______ , KC_LABK , KC_RABK , KC_QUES , KC_COLN , KC_SCLN ,
        _______ , _______ , _______ , KC_BSPC , _______ , _______ , KC_ENT  , KC_SPC  , KC_COMM , KC_DOT  , KC_SLSH ,
        _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_SPC
    //`---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------'
    ),
    [_FUNC] = LAYOUT(
    //,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
        KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , _______ ,
        _______ , KC_F11  , KC_F12  , _______ , KC_HOME , KC_END  , KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT , _______ ,
        _______ , _______ , _______ , _______ , _______ , _______ , KC_PGDN , KC_PGUP , _______
    //`---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------'
    ),
    [_MOUSE] = LAYOUT(
    //,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
        _______ , _______ , _______ , _______ , _______ , _______ , KC_BTN1 , KC_BTN2 , KC_BTN3 , KC_BTN4 , KC_BTN5 ,
        _______ , _______ , _______ , _______ , _______ , _______ , KC_MS_L , KC_MS_D , KC_MS_U , KC_MS_R , _______ ,
        _______ , _______ , _______ , _______ , _______ , KC_WH_L , KC_WH_D , KC_WH_U , KC_WH_R
    //`---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------'
    ),
    [_ADJUST] = LAYOUT(
    //,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
        RESET   , _______ , _______ , _______ , KC_RTOG , KC_RHUI , KC_RSAI , KC_RVAI , _______ , _______ , _______ ,
        _______ , _______ , _______ , KC_RMOD , KC_RRMD , KC_RHUD , KC_RSAD , KC_RVAD , _______ , _______ , _______ ,
        _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______
    //`---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------'
    ),
};

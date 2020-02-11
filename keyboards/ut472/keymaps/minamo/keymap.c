/* Copyright 2018 Carlos Filoteo
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

enum layer_number {
  _BASE = 0,
  _LOWER,
  _RAISE,
  _EXTEND,
  _FUNC,
  _MOUSE,
  _ADJUST,
};

enum custom_keycodes {
  LOWER = SAFE_RANGE,
  RAISE,
  ADJUST,
  RGB_RST
};

#define KC_SENT LSFT_T(KC_ENT)
#define KC_SSPC LSFT_T(KC_SPACE)
#define KC_CTAB LCTL_T(KC_TAB)
#define KC_AESC LALT_T(KC_ESC)

#define KC_DFNC LT(_FUNC, KC_D)
#define KC_GMOU LT(_MOUSE, KC_G)
#define KC_FEXT LT(_EXTEND, KC_F)

#define L_LOWER  LOWER
#define L_RAISE  LT(_RAISE, KC_ENT)
#define L_ADJUST ADJUST

#define KC_RTOG RGB_TOG
#define KC_RMOD RGB_MOD
#define KC_RRMD RGB_RMOD
#define KC_RHUI RGB_HUI
#define KC_RHUD RGB_HUD
#define KC_RSAI RGB_SAI
#define KC_RSAD RGB_SAD
#define KC_RVAI RGB_VAI
#define KC_RVAD RGB_VAD

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_BASE] = LAYOUT(
    //,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
        KC_AESC , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    , KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , KC_BSPC ,
        KC_CTAB , KC_A    , KC_S    , KC_DFNC , KC_FEXT , KC_GMOU , KC_H    , KC_J    , KC_K    , KC_L    , KC_SCLN , KC_SENT ,
        KC_LGUI , KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    , KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , KC_SLSH ,
        KC_LCTL , KC_DEL  , L_ADJUST, KC_APP  , L_LOWER , KC_SSPC           , L_RAISE , KC_DOWN , KC_UP   , KC_LEFT , KC_RGHT
    //,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
    ),
    [_LOWER] = LAYOUT(
    //,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
        _______ , KC_TILD , KC_BSLS , _______ , _______ , KC_TAB  , KC_QUOT , KC_DQT  , KC_UNDS , KC_PIPE , KC_COLN , _______ ,
        _______ , KC_GRV  , KC_EQL  , KC_PLUS , KC_MINS , KC_APP  , KC_LBRC , KC_RBRC , KC_LCBR , KC_RCBR , KC_SCLN , _______ ,
        _______ , _______ , _______ , _______ , _______ , _______ , KC_LPRN , KC_RPRN , KC_LABK , KC_RABK , KC_QUES , _______ ,
        _______ , _______ , _______ , _______ , _______ , _______           , _______ , _______ , _______ , _______ , _______
    //,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
    ),
    [_RAISE] = LAYOUT(
    //,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
        _______ , KC_EXLM , KC_AT   , KC_HASH , KC_DLR  , KC_PERC , KC_CIRC , KC_AMPR , KC_ASTR , KC_LPRN , KC_RPRN , _______ ,
        _______ , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , _______ ,
        _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , KC_COMM , KC_DOT  , KC_SLSH , _______ ,
        _______ , _______ , _______ , _______ , _______ , _______           , _______ , _______ , _______ , _______ , _______
    //,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
    ),
    [_EXTEND] = LAYOUT(
    //,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
        _______ , _______ , _______ , KC_ESC  , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
        _______ , _______ , _______ , KC_BSPC , _______ , _______ , KC_ENT  , KC_SPC  , _______ , _______ , _______ , _______ ,
        _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
        _______ , _______ , _______ , _______ , _______ , _______           , _______ , _______ , _______ , _______ , _______
    //,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
    ),
    [_FUNC] = LAYOUT(
    //,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
        _______ , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , _______ ,
        _______ , KC_F11  , KC_F12  , _______ , KC_HOME , KC_END  , KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT , _______ , _______ ,
        _______ , _______ , _______ , _______ , _______ , _______ , KC_PGUP , KC_PGDN , _______ , _______ , _______ , _______ ,
        _______ , _______ , _______ , _______ , _______ , _______           , _______ , _______ , _______ , _______ , _______
    //,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
    ),
    [_MOUSE] = LAYOUT(
    //,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
        _______ , _______ , _______ , _______ , _______ , _______ , KC_BTN1 , KC_BTN2 , KC_BTN3 , KC_BTN4 , KC_BTN5 , _______ ,
        _______ , _______ , _______ , _______ , _______ , _______ , KC_MS_L , KC_MS_D , KC_MS_U , KC_MS_R , _______ , _______ ,
        _______ , _______ , _______ , _______ , _______ , _______ , KC_WH_L , KC_WH_D , KC_WH_U , KC_WH_R , _______ , _______ ,
        _______ , _______ , _______ , _______ , _______ , _______           , _______ , _______ , _______ , _______ , _______
    //,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
    ),
    [_ADJUST] = LAYOUT(
    //,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
        RESET   , _______ , _______ , _______ , _______ , KC_RTOG , KC_RHUI , KC_RSAI , KC_RVAI , RGB_RST , _______ , _______ ,
        _______ , _______ , _______ , _______ , _______ , KC_RMOD , KC_RHUD , KC_RSAD , KC_RVAD , _______ , _______ , _______ ,
        _______ , _______ , _______ , _______ , _______ , KC_RRMD , _______ , _______ , _______ , _______ , _______ , _______ ,
        _______ , _______ , _______ , _______ , _______ , _______           , _______ , _______ , _______ , _______ , _______
    //,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
            } else {
                layer_off(_LOWER);
            }
            break;
        case RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
            } else {
                layer_off(_RAISE);
            }
            break;
        case ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            break;
        case RGB_RST:
        #ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
                eeconfig_update_rgblight_default();
                rgblight_enable();
            }
        #endif
            break;
        default:
            break;
    }
    return true;
};

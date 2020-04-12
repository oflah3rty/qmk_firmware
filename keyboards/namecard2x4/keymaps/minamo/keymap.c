/* Copyright 2018 takashiski
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

enum Layer
{
  BASE,
  FIZZ,
  BUZZ,
};

#define _______ KC_TRNS

//Tap Dance Declarations
enum {
  TD_FIZZ_BUZZ = 0
};

void dance_fizzbuzz_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    layer_move(BASE);
  }else if (state->count == 2) {
    layer_move(FIZZ);
  } else {
    layer_move(BUZZ);
  }
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_FIZZ_BUZZ]  = ACTION_TAP_DANCE_FN_ADVANCED (NULL, dance_fizzbuzz_finished, NULL)
};

#define KC_BASE TO(BASE)
#define KC_FZBZ TD(TD_FIZZ_BUZZ)
#define KC_MIRR SH_T(KC_SPACE)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[BASE] = LAYOUT(
// ,--------,---------,---------,---------.
    KC_LEFT , KC_BASE , KC_LEAD , KC_ESC  ,
    KC_RGHT , KC_BASE , KC_ENT  , KC_BSPC
// ,--------,---------,---------,---------.
    ),
[FIZZ] = LAYOUT(
// ,--------,---------,---------,---------.
    _______ , _______ , _______ , _______ ,
    _______ , _______ , _______ , _______
// ,--------,---------,---------,---------.
    ),
[BUZZ] = LAYOUT(
// ,--------,---------,---------,---------.
    _______ , _______ , _______ , _______ ,
    _______ , _______ , _______ , _______
// ,--------,---------,---------,---------.
    )
};


void matrix_init_user(void) {

}

LEADER_EXTERNS();

void matrix_scan_user(void) {
  LEADER_DICTIONARY() {
    leading = false;
    leader_end();

    SEQ_ONE_KEY(KC_ENT) {
      // Anything you can do in a macro.
      SEND_STRING("https://docs.google.com/presentation/d/1mz0fW7Gndmv6Mr-leKJEQr0iwjpCXYCkk7U385fEPLA/edit?usp=sharing"SS_TAP(X_ENTER));
    }
  }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  return true;
}

void led_set_user(uint8_t usb_led) {

}


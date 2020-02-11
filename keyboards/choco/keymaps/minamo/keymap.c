/* Copyright 2019 Takuya Urakawa, Dm9Recoreds.com
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

#define _ALPHA     0
#define _ALPHAHALF 1
#define _SYMBOL    2
#define _NUMBER    3
#define _SUPPORT   4
#define _FUNCTION  5
#define _ADJUST    6

#define KC_ETAJ LT(_ADJUST, KC_ENT)
#define KC_ALSP LT(_ALPHAHALF, KC_SPACE)
#define KC_NMSP LT(_NUMBER, KC_SPACE)
#define KC_TBFN LT(_FUNCTION, KC_TAB)
#define KC_DLNU LT(_NUMBER, KC_DEL)

#define KC_SGUI OSMGUI
#define KC_SSFT OSMSFT
#define KC_SCTL OSMCTL
#define KC_SALT OSMALT

#define KC_TDSY TD(TAP_SYMBOL)
#define KC_FNAP TD(TAP_ALPHA)

// for Tap Dance
// -----------------------------------------------------------------------------
typedef struct {
  bool is_press_action;
  int state;
} tap;

enum tap_dance {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};
// -----------------------------------------------------------------------------

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QMKBEST = SAFE_RANGE,
  OSMSFT,
  OSMCTL,
  OSMALT,
  OSMGUI,
  // 以下は Tap Dance
  TAP_SYMBOL = 0,
  TAP_ALPHA,
  SOME_OTHER_DANCE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_ALPHA] = LAYOUT(
  //,---------+---------+---------+---------+---------+---------+---------+
      KC_ESC  , KC_P    , KC_K    , KC_R    , KC_A    , KC_F    , OSMCTL  ,
      KC_TBFN , KC_D    , KC_T    , KC_H    , KC_E    , KC_O    , OSMSFT  ,
      KC_DLNU , KC_Y    , KC_S    , KC_N    , KC_I    , KC_U    , OSMALT  ,
      KC_BSPC , KC_CLCK , XXXXXXX , OSMGUI  , KC_TDSY , KC_ALSP , KC_ETAJ
  //,---------+---------+---------+---------+---------+---------+---------+
  ),
  [_ALPHAHALF] = LAYOUT(
  //,---------+---------+---------+---------+---------+---------+---------+
      _______ , KC_J    , KC_M    , KC_B    , KC_SCLN , KC_COLN , _______ ,
      _______ , KC_V    , KC_C    , KC_L    , KC_Z    , KC_Q    , _______ ,
      _______ , KC_X    , KC_G    , KC_W    , KC_COMM , KC_DOT  , _______ ,
      _______ , _______ , _______ , _______ , _______ , _______ , _______
  //,---------+---------+---------+---------+---------+---------+---------+
  ),
  [_SYMBOL] = LAYOUT(
  //,---------+---------+---------+---------+---------+---------+---------+
      _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
      _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
      _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
      _______ , _______ , _______ , _______ , _______ , _______ , _______
  //,---------+---------+---------+---------+---------+---------+---------+
  ),
  [_NUMBER] = LAYOUT(
  //,---------+---------+---------+---------+---------+---------+---------+
      XXXXXXX , KC_7    , KC_8    , KC_9    , XXXXXXX , XXXXXXX , XXXXXXX ,
      XXXXXXX , KC_4    , KC_5    , KC_6    , XXXXXXX , XXXXXXX , XXXXXXX ,
      _______ , KC_1    , KC_2    , KC_3    , XXXXXXX , XXXXXXX , XXXXXXX ,
      _______ , KC_0    , KC_DOT  , _______ , XXXXXXX , XXXXXXX , XXXXXXX
  //,---------+---------+---------+---------+---------+---------+---------+
  ),
  [_SUPPORT] = LAYOUT(
  //,---------+---------+---------+---------+---------+---------+---------+
      _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
      _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
      _______ , _______ , _______ , _______ , _______ , _______ , _______ ,
      _______ , _______ , _______ , _______ , _______ , _______ , _______
  //,---------+---------+---------+---------+---------+---------+---------+
  ),
  [_FUNCTION] = LAYOUT(
  //,---------+---------+---------+---------+---------+---------+---------+
      XXXXXXX , KC_HOME , KC_UP   , KC_END  , KC_PGUP , XXXXXXX , XXXXXXX ,
      _______ , KC_LEFT , KC_DOWN , KC_RGHT , KC_PGDN , XXXXXXX , XXXXXXX ,
      XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
      XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX
  //,---------+---------+---------+---------+---------+---------+---------+
  ),
  [_ADJUST] = LAYOUT(
  //,---------+---------+---------+---------+---------+---------+---------+
      RESET   , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6   ,
      XXXXXXX , KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  , KC_F12  ,
      XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
      XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , _______
  //,---------+---------+---------+---------+---------+---------+---------+
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  uint8_t modkeys;
  switch (keycode) {
    case QMKBEST:
      if (record->event.pressed) {
        SEND_STRING("QMK is the best thing ever!");
      } else {
      }
      break;
    case OSMGUI:
      if (record->event.pressed) {
        modkeys = get_oneshot_mods() | MOD_LGUI;
        set_oneshot_mods(modkeys);
      } else {
      }
      return false;
    case OSMSFT:
      if (record->event.pressed) {
        modkeys = get_oneshot_mods() | MOD_LSFT;
        set_oneshot_mods(modkeys);
      } else {
      }
      return false;
    case OSMCTL:
      if (record->event.pressed) {
        modkeys = get_oneshot_mods() | MOD_LCTL;
        set_oneshot_mods(modkeys);
      } else {
      }
      return false;
    case OSMALT:
      if (record->event.pressed) {
        modkeys = get_oneshot_mods() | MOD_LALT;
        set_oneshot_mods(modkeys);
      } else {
      }
      return false;
    default:
      break;
  }
  return true;
}

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

void led_set_user(uint8_t usb_led) {
}

int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)  return SINGLE_TAP;
    return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    return DOUBLE_TAP;
  }
  if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    return TRIPLE_HOLD;
  }
  return 8; //magic number
}

static tap xtap_state = {
  .is_press_action = true,
  .state = 0
};

void tap_symbol_finished (qk_tap_dance_state_t *state, void *user_data) {
  xtap_state.state = cur_dance(state);
  switch (xtap_state.state) {
    case SINGLE_TAP: break;
    case SINGLE_HOLD: layer_on(_SUPPORT); break;
  }
}

void tap_alpha_finished (qk_tap_dance_state_t *state, void *user_data) {
  xtap_state.state = cur_dance(state);
  switch (xtap_state.state) {
    case SINGLE_TAP: break;
    case SINGLE_HOLD: layer_on(_SUPPORT); break;
  }
}

void tap_symbol_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (xtap_state.state) {
    case SINGLE_TAP: layer_on(_SYMBOL); layer_off(_FUNCTION); break;
    case SINGLE_HOLD: layer_off(_SUPPORT); break;
    case DOUBLE_TAP: layer_off(_SYMBOL); layer_on(_FUNCTION); break;
  }
  xtap_state.state = 0;
}

void tap_alpha_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (xtap_state.state) {
    case SINGLE_TAP: layer_off(_SYMBOL); layer_off(_FUNCTION); break;
    case SINGLE_HOLD: layer_off(_SUPPORT); break;
    case DOUBLE_TAP: layer_off(_SYMBOL); layer_on(_FUNCTION); break;
  }
  xtap_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TAP_SYMBOL]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,tap_symbol_finished, tap_symbol_reset),
  [TAP_ALPHA]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL,tap_alpha_finished, tap_alpha_reset),
};

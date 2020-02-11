#include QMK_KEYBOARD_H

#define _BASE   0
#define _LOWER  1
#define _RAISE  2
#define _ADJUST 3

enum custom_keycodes {
  M_CLEAR = SAFE_RANGE,
};

typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};

//Tap dance enums
enum {
  TD_SP_ENT = 0,
  TD_LAYER,
};

int cur_dance (qk_tap_dance_state_t *state);

//for the x tap dance. Put it here so it can be used in any keymap
void x_finished (qk_tap_dance_state_t *state, void *user_data);
void x_reset (qk_tap_dance_state_t *state, void *user_data);

#define SP_ENT  TD(TD_SP_ENT)
#define SP_LAY  TD(TD_LAYER)

#define KC_OCTL OSM(MOD_LCTL)
#define KC_OGUI OSM(MOD_LGUI)
#define KC_OALT OSM(MOD_LALT)
#define KC_OSFT OSM(MOD_LSFT)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_ortho_3x10(
      KC_Q    ,KC_W    ,KC_E    ,KC_R    ,KC_T    ,KC_Y    ,KC_U    ,KC_I    ,KC_O    ,KC_P    ,
      KC_A    ,KC_S    ,KC_D    ,KC_F    ,KC_G    ,KC_H    ,KC_J    ,KC_K    ,KC_L    ,SP_ENT  ,
      KC_Z    ,KC_X    ,KC_C    ,KC_V    ,SP_LAY  ,SP_LAY  ,KC_M    ,KC_N    ,KC_B    ,XXXXXXX
  ),
  [_LOWER] = LAYOUT_ortho_3x10(
      KC_1    ,KC_2    ,KC_3    ,KC_4    ,KC_5    ,KC_GRV  ,KC_QUOT ,KC_LBRC ,KC_RBRC ,KC_BSPC ,
      KC_6    ,KC_7    ,KC_8    ,KC_9    ,KC_0    ,KC_SCLN ,KC_COMM ,KC_DOT  ,KC_SLSH ,_______ ,
      KC_OCTL ,KC_OGUI ,KC_OALT ,KC_OSFT ,_______ ,_______ ,KC_MINS ,KC_EQL  ,KC_BSLS ,XXXXXXX
  ),
  [_RAISE] = LAYOUT_ortho_3x10(
      KC_F1   ,KC_F2   ,KC_F3   ,KC_F4   ,KC_F5   ,KC_APP  ,KC_PGDN ,KC_PGUP ,KC_TAB  ,KC_ESC  ,
      KC_F6   ,KC_F7   ,KC_F8   ,KC_F9   ,KC_F10  ,KC_LEFT ,KC_DOWN ,KC_UP   ,KC_RGHT ,_______ ,
      KC_F11  ,KC_F12  ,KC_DEL  ,KC_CAPS ,_______ ,_______ ,KC_HOME ,KC_END  ,M_CLEAR ,RESET
  ),
  [_ADJUST] = LAYOUT_ortho_3x10(
      RESET   ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
      XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,
      XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX ,XXXXXXX
  ),
};

void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  update_tri_layer(_LOWER, _RAISE, _ADJUST);
  switch (keycode) {
    case M_CLEAR:
      clear_oneshot_mods();
      break;
    default:
      break;
  }
  return true;
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
  else return 8; //magic number
}

static tap td_sp_ent_state = {
  .is_press_action = true,
  .state = 0
};

static tap td_layer_state = {
  .is_press_action = true,
  .state = 0
};

void sp_ent_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_sp_ent_state.state = cur_dance(state);
  switch (td_sp_ent_state.state) {
    case SINGLE_TAP:        register_code(KC_ENT); break;
    case SINGLE_HOLD:       register_code(KC_LSFT); break;
    case DOUBLE_TAP:        register_code(KC_ESC); break;
    case DOUBLE_HOLD:       register_code(KC_LCTL); break;
    case DOUBLE_SINGLE_TAP: break;
    case TRIPLE_TAP:        break;
    case TRIPLE_HOLD:       register_code(KC_LALT); break;
  }
}

void sp_ent_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (td_sp_ent_state.state) {
    case SINGLE_TAP:        unregister_code(KC_ENT); break;
    case SINGLE_HOLD:       unregister_code(KC_LSFT); break;
    case DOUBLE_TAP:        unregister_code(KC_ESC); break;
    case DOUBLE_HOLD:       unregister_code(KC_LCTL); break;
    case DOUBLE_SINGLE_TAP: break;
    case TRIPLE_TAP:        break;
    case TRIPLE_HOLD:       unregister_code(KC_LALT); break;
  }
  td_sp_ent_state.state = 0;
}

void layer_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_layer_state.state = cur_dance(state);
  switch (td_layer_state.state) {
    case SINGLE_TAP:        register_code(KC_SPC); break;
    case SINGLE_HOLD:       layer_on(_LOWER); break;
    case DOUBLE_TAP:        break;
    case DOUBLE_HOLD:       layer_on(_RAISE); break;
    case DOUBLE_SINGLE_TAP: break;
    case TRIPLE_TAP:        break;
    case TRIPLE_HOLD:       layer_on(_ADJUST); break;
  }
}

void layer_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (td_layer_state.state) {
    case SINGLE_TAP:        unregister_code(KC_SPC); break;
    case SINGLE_HOLD:       layer_off(_LOWER); break;
    case DOUBLE_TAP:        break;
    case DOUBLE_HOLD:       layer_off(_RAISE); break;
    case DOUBLE_SINGLE_TAP: break;
    case TRIPLE_TAP:        break;
    case TRIPLE_HOLD:       layer_off(_ADJUST); break;
  }
  td_layer_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_SP_ENT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,sp_ent_finished, sp_ent_reset),
  [TD_LAYER]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL,layer_finished, layer_reset)
};

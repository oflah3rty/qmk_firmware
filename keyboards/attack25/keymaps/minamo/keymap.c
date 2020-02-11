#include QMK_KEYBOARD_H
#include <drivers/avr/pro_micro.h>

#ifdef RGBLIGHT_ENABLE
// Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
rgblight_config_t        RGB_current_config;
#endif

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

enum layer_number {
  _ALPHA = 0,
  _ALPHAHALF,
  _SYMBOL,
  _NUMBER,
  _SUPPORT,
  _FUNCTION,
  _ADJUST
};

enum custom_keycodes {
  CYCLESIFT = SAFE_RANGE,
  OSMCTL,
  OSMALT,
  OSMGUI,
  MOVE_ALPHA,
  MOVE_FUNCTION,
  RGBRST,
  PHOTO,
  LEDOFF,
  // 以下は Tap Dance
  TAP_SYMBOL = 0,
  TAP_ALPHA,
  SOME_OTHER_DANCE
};

#define XXXXXXX KC_NO
#define _______ KC_TRNS

#define KC_CSFT CYCLESIFT
#define KC_SGUI OSMGUI
#define KC_SCTL OSMCTL
#define KC_SALT OSMALT

#define KC_ALSP LT(_ALPHAHALF, KC_SPACE)
#define KC_NMSP LT(_NUMBER, KC_SPACE)

#define KC_TDSY TD(TAP_SYMBOL)
#define KC_FNAP TD(TAP_ALPHA)
#define KC_MVAP MOVE_ALPHA
#define KC_MVFN MOVE_FUNCTION

#define KC_RTOG RGB_TOG
#define KC_RMOD RGB_MOD
#define KC_RRMD RGB_RMOD
#define KC_RHUI RGB_HUI
#define KC_RHUD RGB_HUD
#define KC_RSAI RGB_SAI
#define KC_RSAD RGB_SAD
#define KC_RVAI RGB_VAI
#define KC_RVAD RGB_VAD

#define L_ADJST MO(_ADJUST)

#define KC_FN1  SGUI(KC_C)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_ALPHA] = LAYOUT_ortho_5x5(
  // ,-------+-------+-------+-------+-------.
      KC_FN1 ,XXXXXXX,XXXXXXX,XXXXXXX,L_ADJST,
      KC_P   ,KC_K   ,KC_R   ,KC_A   ,KC_F   ,
      KC_D   ,KC_T   ,KC_H   ,KC_E   ,KC_O   ,
      KC_Y   ,KC_S   ,KC_N   ,KC_I   ,KC_U   ,
      KC_CSFT,KC_ENT ,KC_MVFN,KC_TDSY,KC_ALSP
  // ,-------+-------+-------+-------+-------.
  ),
  [_ALPHAHALF] = LAYOUT_ortho_5x5(
  // ,-------+-------+-------+-------+-------.
      KC_MUTE,KC_VOLU,KC_VOLD,XXXXXXX,L_ADJST,
      KC_J   ,KC_M   ,KC_B   ,KC_BSPC,KC_ENT ,
      KC_V   ,KC_C   ,KC_L   ,KC_Z   ,KC_Q   ,
      KC_X   ,KC_G   ,KC_W   ,KC_COMM,KC_DOT ,
      _______,KC_SCLN,KC_SLSH,KC_QUOT,_______
  // ,-------+-------+-------+-------+-------.
  ),
  [_SYMBOL] = LAYOUT_ortho_5x5(
  // ,-------+-------+-------+-------+-------.
      XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,L_ADJST,
      KC_LCBR,KC_LBRC,KC_LPRN,KC_LABK,KC_EQL ,
      KC_RCBR,KC_RBRC,KC_RPRN,KC_RABK,KC_SLSH,
      KC_GRV ,KC_BSLS,KC_MINS,KC_QUOT,KC_SCLN,
      _______,_______,KC_MVAP,KC_FNAP,KC_NMSP
  // ,-------+-------+-------+-------+-------.
  ),
  [_NUMBER] = LAYOUT_ortho_5x5(
  // ,-------+-------+-------+-------+-------.
      XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,L_ADJST,
      KC_MINS,KC_7   ,KC_8   ,KC_9   ,KC_ASTR,
      KC_PLUS,KC_4   ,KC_5   ,KC_6   ,KC_SLSH,
      KC_0   ,KC_1   ,KC_2   ,KC_3   ,KC_TAB ,
      _______,_______,KC_MVFN,_______,_______
  // ,-------+-------+-------+-------+-------.
  ),
  [_SUPPORT] = LAYOUT_ortho_5x5(
  // ,-------+-------+-------+-------+-------.
      KC_HENK,KC_MHEN,XXXXXXX,XXXXXXX,L_ADJST,
      KC_PGUP,KC_HOME,KC_UP  ,KC_END ,KC_INS ,
      KC_PGDN,KC_LEFT,KC_DOWN,KC_RGHT,KC_DEL ,
      KC_SGUI,KC_SALT,KC_SCTL,KC_BSPC,KC_ESC ,
      _______,KC_LGUI,KC_APP ,_______,KC_PSCR
  // ,-------+-------+-------+-------+-------.
  ),
  [_FUNCTION] = LAYOUT_ortho_5x5(
  // ,-------+-------+-------+-------+-------.
      XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,L_ADJST,
      XXXXXXX,KC_F7  ,KC_F8  ,KC_F9  ,XXXXXXX,
      KC_F11 ,KC_F4  ,KC_F5  ,KC_F6  ,KC_F12 ,
      KC_F10 ,KC_F1  ,KC_F2  ,KC_F3  ,KC_TAB ,
      _______,_______,KC_MVAP,_______,_______
  // ,-------+-------+-------+-------+-------.
  ),
  [_ADJUST] = LAYOUT_ortho_5x5(
  // ,-------+-------+-------+-------+-------.
      XXXXXXX,XXXXXXX,LEDOFF ,PHOTO  ,L_ADJST,
      KC_RTOG,KC_RMOD,KC_RHUI,KC_RSAI,KC_RVAI,
      RGBRST ,KC_RRMD,KC_RHUD,KC_RSAD,KC_RVAD,
      XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
      XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,RESET
  // ,-------+-------+-------+-------+-------.
  )
};

bool is_PhotoShooting = false; // 写真撮影用

void matrix_init_user(void) {
#ifdef RGBLIGHT_ENABLE
  rgblight_init();
  rgblight_setrgb(0, 0, 0);
  rgblight_setrgb_at(  0, 255,   0, 0);
  RGB_current_config = rgblight_config;
#endif
  TX_RX_LED_INIT;  // Turn LEDs off by default
  RXLED0;
  TXLED0;
}

void rgb_all_off_onece(void) {
#ifdef RGBLIGHT_ENABLE
  for(int i = 0; i < 25; i++) {
    rgblight_setrgb_at(0, 0, 0, i);
  }
#endif
}

void rgb_shift_mode_reset(void) {
#ifdef RGBLIGHT_ENABLE
  if (is_PhotoShooting) {
    return;
  }
  //rgblight_timer_disable();
  rgblight_setrgb_at(0, 0, 0, 1);
#endif
}
void rgb_shift_mode_oneshot(void) {
#ifdef RGBLIGHT_ENABLE
  if (is_PhotoShooting) {
    return;
  }
  //rgblight_timer_disable();
  rgblight_setrgb_at(0, 32, 255, 1);
#endif
}
void rgb_shift_mode_capslock(void) {
#ifdef RGBLIGHT_ENABLE
  if (is_PhotoShooting) {
    return;
  }
  //rgblight_timer_disable();
  rgblight_setrgb_at(255, 32, 0, 1);
#endif
}

void matrix_scan_user(void) {}

uint32_t layer_state_set_user(uint32_t state) {
#ifdef RGBLIGHT_ENABLE
  if (is_PhotoShooting) {
    return state;
  }
  switch(biton32(state)) {
    case _ALPHA:     rgblight_setrgb_at(  0, 255,   0, 0); break;
    case _ALPHAHALF: rgblight_setrgb_at(  0, 128,   0, 0); break;
    case _NUMBER:    rgblight_setrgb_at(  0,   0, 255, 0); break;
    case _SYMBOL:    rgblight_setrgb_at(255, 128,   0, 0); break;
    case _SUPPORT:   rgblight_setrgb_at(  0, 255, 255, 0); break;
    case _FUNCTION:  rgblight_setrgb_at(255,   0, 255, 0); break;
    case _ADJUST:    rgblight_setrgb_at(255, 255, 255, 0); break;
    default:         rgblight_setrgb_at(  0,   0,   0, 0); break;
  }
#endif
  return state;
}

void persistent_default_layer_set(uint16_t default_layer) {
  // eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

char shift_count = 0;

// Shift 回数をクリアする
void clear_shift_count(uint16_t keycode) {
  if (keycode == CYCLESIFT || shift_count >= 2) {
    return;
  }
  shift_count = 0;
  rgb_shift_mode_reset();
}

// １回限りの Shift モードに入る
void set_oneshot_shift_mode(void) {
  uint8_t modkeys = get_oneshot_mods() | MOD_LSFT;
  set_oneshot_mods(modkeys);
  shift_count = 1;
  rgb_shift_mode_oneshot();
}

// Capslock モードに入る
void set_capslock_mode(void) {
  clear_oneshot_mods(); // ワンショット Shift があった場合の解除
  register_code(KC_CAPSLOCK);
  unregister_code(KC_CAPSLOCK);
  shift_count = 2;
  rgb_shift_mode_capslock();
}

// Capslock モードの解除
void clear_capslock_mode(void) {
  register_code(KC_CAPSLOCK);
  unregister_code(KC_CAPSLOCK);
  shift_count = 0;
  rgb_shift_mode_reset();
}

// ワンショットの状況を確認する
void check_oneshot_state(void) {
#ifdef RGBLIGHT_ENABLE
  if (is_PhotoShooting) {
    return;
  }
  uint8_t state = get_oneshot_mods();
  uint8_t state_index = 0;
  if (state & MOD_LCTL) state_index += 1;
  if (state & MOD_LALT) state_index += 2;
  if (state & MOD_LGUI) state_index += 4;
  switch(state_index) {
    case 1:  rgblight_setrgb_at(  0, 255,   0, 2); break;
    case 2:  rgblight_setrgb_at(255,   0,   0, 2); break;
    case 3:  rgblight_setrgb_at(255, 255,   0, 2); break;
    case 4:  rgblight_setrgb_at(  0,   0, 255, 2); break;
    case 5:  rgblight_setrgb_at(  0, 255, 255, 2); break;
    case 6:  rgblight_setrgb_at(255,   0, 255, 2); break;
    case 7:  rgblight_setrgb_at(255, 255, 255, 2); break;
    case 0:
    default: rgblight_setrgb_at(  0,   0,   0, 2); break;
  }
#endif
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  clear_shift_count(keycode);
  check_oneshot_state();
  uint8_t modkeys;

  switch (keycode) {
    case CYCLESIFT:
      if (record->event.pressed) {
        switch (shift_count) {
          case 0: set_oneshot_shift_mode(); break;
          case 1: set_capslock_mode(); break;
          case 2: clear_capslock_mode(); break;
        }
      }
      return false;
    case OSMGUI:
      if (record->event.pressed) {
        modkeys = get_oneshot_mods() | MOD_LGUI;
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
    case MOVE_ALPHA:
      if (record->event.pressed) {
      } else {
        layer_off(_NUMBER);
        layer_off(_SYMBOL);
        layer_off(_SUPPORT);
        layer_off(_FUNCTION);
      }
      return false;
    case MOVE_FUNCTION:
      if (record->event.pressed) {
      } else {
        layer_off(_NUMBER);
        layer_off(_SYMBOL);
        layer_off(_SUPPORT);
        layer_on(_FUNCTION);
      }
      return false;
    case LEDOFF:
      if(record->event.pressed) {
        rgb_all_off_onece();
      }
      return false;
    case PHOTO:
      if (record->event.pressed) {
        if (is_PhotoShooting) {
          is_PhotoShooting = false;
        } else {
          is_PhotoShooting = true;
        }
      }
      return false;
    case RGBRST:
#ifdef RGBLIGHT_ENABLE
      if (record->event.pressed) {
        eeconfig_update_rgblight_default();
        rgblight_enable();
        RGB_current_config = rgblight_config;
      }
#endif
      return false;
    default:
      break;
  }
  return true;
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

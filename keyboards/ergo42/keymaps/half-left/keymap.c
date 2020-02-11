#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define BASE     0
#define NUMBER   1
#define SCROLL   2
#define FUNCTION 3
#define SYMBOL   4
#define ADJUST   5

//Tap Dance Declarations
enum {
  TD_MODE = 0,
  TD_SHIFT = 1
};

void layer_base(void) {
  layer_move(BASE);
}

void layer_number(void) {
  layer_move(NUMBER);
}

void layer_scroll(void) {
  layer_move(SCROLL);
}

void layer_function(void) {
  layer_move(FUNCTION);
}

void layer_symbol(void) {
  layer_move(SYMBOL);
}

void dance_mode_finished (qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1: layer_base(); break;
    case 2: layer_number(); break;
    case 3: layer_scroll(); break;
    case 4: layer_function(); break;
  }
}

void dance_shift_finished (qk_tap_dance_state_t *state, void *user_data) {
  switch (state->count) {
    case 1: set_oneshot_mods(MOD_LSFT); break;
    case 2: layer_symbol(); break;
  }
}

//Tap Dance Definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_MODE]  = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_mode_finished, NULL),
  [TD_SHIFT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_shift_finished, NULL)
};

enum custom_keycodes {
  RGB_RST = SAFE_RANGE
};

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define KC_AJST MO(ADJUST)
#define KC_MIRR SH_T(KC_SPACE)
#define KC_MODE TD(TD_MODE)
#define KC_SFT  TD(TD_SHIFT)
#define KC_CTRL OSM(MOD_LCTL)
#define KC_ALT  OSM(MOD_LALT)
#define KC_GUI  OSM(MOD_LGUI)

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
  [BASE] = LAYOUT( \
    KC_ESC , KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_MODE,    KC_MODE, KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_BSPC, \
    KC_ENT , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_CTRL,    KC_GUI , KC_H   , KC_J   , KC_K   , KC_L   , KC_SCLN, KC_QUOT, \
    KC_SFT , KC_Z   , KC_X   , KC_C   , KC_V   , KC_B   , KC_ALT ,    KC_APP , KC_N   , KC_M   , KC_COMM, KC_DOT , KC_SLSH, KC_SFT , \
    KC_AJST, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_MIRR, KC_MIRR,    KC_MIRR, KC_MIRR, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX \
  ),
  [NUMBER] = LAYOUT( \
    KC_TAB , KC_MINS, KC_9   , KC_8   , KC_7   , KC_ASTR, _______,    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, \
    KC_ENT , KC_PLUS, KC_6   , KC_5   , KC_4   , KC_DOT , _______,    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, \
    _______, KC_SLSH, KC_3   , KC_2   , KC_1   , KC_0   , _______,    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, \
    _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______ \
  ),
  [SCROLL] = LAYOUT( \
    _______, KC_DEL , KC_PGUP, KC_UP  , KC_HOME, KC_PSCR, _______,    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, \
    _______, XXXXXXX, KC_LEFT, KC_DOWN, KC_RGHT, KC_SLCK, _______,    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, \
    _______, KC_INS , KC_PGDN, KC_NLCK, KC_END , KC_PAUS, _______,    _______, XXXXXXX, XXXXXXX, KC_CLR , XXXXXXX, KC_HELP, _______, \
    _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______ \
  ),
  [FUNCTION] = LAYOUT( \
    _______, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F13 , _______,    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, \
    _______, KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F14 , _______,    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, \
    _______, KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_F15 , _______,    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, \
    _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______ \
  ),
  [SYMBOL] = LAYOUT( \
    _______, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC, _______,    _______, KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC, \
    KC_GRV , KC_RBRC, KC_LBRC, KC_MINS, KC_EQL , KC_CTRL, _______,    _______, XXXXXXX, KC_PLUS, KC_UNDS, KC_LCBR, KC_RCBR, KC_TILD, \
    _______, KC_BSLS, XXXXXXX, KC_CAPS, KC_LGUI, KC_ALT , _______,    _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_PIPE, _______, \
    _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______ \
  ),
  [ADJUST] = LAYOUT( \
    RESET  , _______, RGB_RST, KC_RVAI, KC_RSAI, KC_RHUI, KC_RTOG,    _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, KC_RVAD, KC_RSAD, KC_RHUD, KC_RMOD,    _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, KC_RRMD,    _______, _______, _______, _______, _______, _______, _______, \
    _______, _______, _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______, _______, _______ \
  )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case RGB_RST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
        }
      #endif
      break;
  }
  return true;
}

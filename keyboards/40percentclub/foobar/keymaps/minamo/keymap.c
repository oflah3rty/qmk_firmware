#include "foobar.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _BASE   0
#define _LOWER  1
#define _RAISE  2
#define _EXTEND 3
#define _FNC    4
#define _MOUSE  5
#define _ADJ    6

#define _______ KC_TRNS

// Tap-Hold keys
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

#define KC_CSPC LCTL_T(KC_SPC)
#define KC_SENT LSFT_T(KC_ENT)
#define KC_XGUI GUI_T(KC_X)
#define KC_DGUI GUI_T(KC_DOT)
#define KC_CALT LALT_T(KC_C)
#define KC_BALT LALT_T(KC_B)

#define KC_ZADJ LT(_ADJ, KC_Z)
#define KC_DFNC LT(_FNC, KC_D)
#define KC_GMOU LT(_MOUSE, KC_G)
#define KC_FEXT LT(_EXTEND, KC_F)

#define KC_LOW  MO(_LOWER)
#define KC_RAI  MO(_RAISE)
#define KC_VLOW LT(_LOWER, KC_V)
#define KC_MRAI LT(_RAISE, KC_M)

enum custom_keycodes {
  RGB_RST = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_split(
  //,-------+-------+-------+-------+-------+  -------+-------+-------+-------+-------.
     KC_Q   ,KC_W   ,KC_E   ,KC_R   ,KC_T   ,  KC_Y   ,KC_U   ,KC_I   ,KC_O   ,KC_P   ,
     KC_A   ,KC_S   ,KC_DFNC,KC_FEXT,KC_GMOU,  KC_H   ,KC_J   ,KC_K   ,KC_L   ,KC_N   ,
     KC_ZADJ,KC_XGUI,KC_CALT,KC_VLOW,KC_CSPC,  KC_SENT,KC_MRAI,KC_BALT,KC_DGUI,KC_SLSH
  //`-------+-------+-------+-------+-------+  -------+-------+-------+-------+-------'
  ),
  [_LOWER] = LAYOUT_split(
  //,-------+-------+-------+-------+-------+  -------+-------+-------+-------+-------.
     KC_TILD,KC_BSLS,_______,_______,KC_TAB ,  KC_QUOT,KC_DQT ,KC_UNDS,KC_PIPE,KC_COLN,
     KC_GRV ,KC_EQL ,KC_PLUS,KC_MINS,KC_APP ,  KC_LBRC,KC_RBRC,KC_LCBR,KC_RCBR,KC_SCLN,
     _______,_______,_______,_______,_______,  _______,_______,KC_LABK,KC_RABK,KC_QUES
  //`-------+-------+-------+-------+-------+  -------+-------+-------+-------+-------'
  ),
  [_RAISE] = LAYOUT_split(
  //,-------+-------+-------+-------+-------+  -------+-------+-------+-------+-------.
     KC_EXLM,KC_AT  ,KC_HASH,KC_DLR ,KC_PERC,  KC_CIRC,KC_AMPR,KC_ASTR,KC_LPRN,KC_RPRN,
     KC_1   ,KC_2   ,KC_3   ,KC_4   ,KC_5   ,  KC_6   ,KC_7   ,KC_8   ,KC_9   ,KC_0   ,
     _______,_______,_______,_______,_______,  _______,_______,KC_COMM,KC_DOT ,KC_SLSH
  //`-------+-------+-------+-------+-------+  -------+-------+-------+-------+-------'
  ),
  [_EXTEND] = LAYOUT_split(
  //,-------+-------+-------+-------+-------+  -------+-------+-------+-------+-------.
     _______,_______,KC_ESC ,_______,_______,  KC_COLN,KC_SCLN,KC_LABK,KC_RABK,KC_QUES,
     _______,_______,KC_BSPC,_______,_______,  KC_ENT ,KC_SPC ,KC_COMM,KC_DOT ,KC_SLSH,
     _______,_______,_______,_______,_______,  _______,_______,_______,_______,_______
  //`-------+-------+-------+-------+-------+  -------+-------+-------+-------+-------'
  ),
  [_FNC] = LAYOUT_split(
  //,-------+-------+-------+-------+-------+  -------+-------+-------+-------+-------.
     KC_F1  ,KC_F2  ,KC_F3  ,KC_F4  ,KC_F5  ,  KC_F6  ,KC_F7  ,KC_F8  ,KC_F9  ,KC_F10 ,
     KC_F11 ,KC_F12 ,_______,KC_PGUP,KC_PGDN,  KC_LEFT,KC_DOWN,KC_UP  ,KC_RGHT,KC_PSCR,
     _______,_______,_______,_______,_______,  _______,_______,KC_HOME,KC_END ,_______
  //`-------+-------+-------+-------+-------+  -------+-------+-------+-------+-------'
  ),
  [_MOUSE] = LAYOUT_split(
  //,-------+-------+-------+-------+-------+  -------+-------+-------+-------+-------.
     _______,_______,KC_ESC ,_______,_______,  KC_BTN1,KC_BTN2,KC_BTN3,KC_BTN4,KC_BTN5,
     _______,_______,KC_BSPC,_______,_______,  KC_MS_L,KC_MS_D,KC_MS_U,KC_MS_R,_______,
     _______,_______,_______,_______,_______,  KC_WH_L,KC_WH_D,KC_WH_U,KC_WH_R,_______
  //`-------+-------+-------+-------+-------+  -------+-------+-------+-------+-------'
  ),
  [_ADJ] = LAYOUT_split(
  //,-------+-------+-------+-------+-------+  -------+-------+-------+-------+-------.
     KC_RST ,KC_LCTL,KC_LALT,KC_DEL ,KC_RMOD,  KC_RHUI,KC_RSAI,KC_RVAI,KC_RTOG,KC_RST ,
     _______,_______,KC_RTOG,RGB_RST,KC_RRMD,  KC_RHUD,KC_RSAD,KC_RVAD,KC_DBUG,_______,
     _______,_______,_______,_______,_______,  _______,_______,KC_MUTE,KC_VOLU,KC_VOLD
  //`-------+-------+-------+-------+-------+  -------+-------+-------+-------+-------'
  )
};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

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


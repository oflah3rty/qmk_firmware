#include QMK_KEYBOARD_H
#include "keymap_jp.h"
#include "../common/oled_helper.h"

#define _BASE   0
#define _LOWER  1
#define _RAISE  2
#define _EXTEND 3
#define _FUNC   4
#define _MOUSE  5
#define _ADJUST 6

#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define KC_CSPC LCTL_T(KC_SPACE)
#define KC_SENT LSFT_T(KC_ENTER)
#define KC_LOW  LT(_LOWER, KC_ESC)
#define KC_RAI  LT(_RAISE, KC_BSPC)

#define KC_DFNC LT(_FUNC, KC_D)
#define KC_FEXT LT(_EXTEND, KC_F)

#define KC_MALT OSM(MOD_LALT)
#define KC_MGUI OSM(MOD_LGUI)

enum custom_keycodes {
  ADJUST = SAFE_RANGE,
  FUNC,
  MOUSE,
  RGBRST
};

// Layer Mode aliases

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_base( \
  //,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
      KC_ESC  , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    , KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , KC_DEL  ,\
      KC_TAB  , KC_A    , KC_S    , KC_DFNC , KC_FEXT , KC_G    , KC_H    , KC_J    , KC_K    , KC_L    , KC_SCLN , KC_ENT  ,\
      KC_MGUI , KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    , KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , KC_UP   ,\
      KC_MALT , MOUSE   , FUNC    , KC_LOW  , KC_CSPC , KC_SENT , KC_RAI  , ADJUST  , KC_LEFT , KC_DOWN , KC_RGHT ,\
      KC_BSPC \
  // ExtraKey: Split backspace key or it is below the enter key.
  ),
  [_LOWER] = LAYOUT_base( \
  //,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
      _______ , KC_TILD , KC_BSLS , _______ , _______ , KC_TAB  , KC_QUOT , KC_DQT  , KC_UNDS , KC_PIPE , KC_COLN , _______ ,\
      _______ , KC_GRV  , KC_EQL  , KC_PLUS , KC_MINS , KC_APP  , KC_LBRC , KC_RBRC , KC_LCBR , KC_RCBR , KC_SCLN , _______ ,\
      _______ , _______ , _______ , _______ , _______ , _______ , KC_LPRN , KC_RPRN , KC_LABK , KC_RABK , KC_QUES , _______ ,\
      _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,\
      _______ \
  // ExtraKey: Split backspace key or it is below the enter key.
  ),
  [_RAISE] = LAYOUT_base( \
  //,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
      _______ , KC_EXLM , KC_AT   , KC_HASH , KC_DLR  , KC_PERC , KC_CIRC , KC_AMPR , KC_ASTR , KC_LPRN , KC_RPRN , _______ ,\
      _______ , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , _______ ,\
      _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,\
      _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,\
      _______ \
  // ExtraKey: Split backspace key or it is below the enter key.
  ),
  [_EXTEND] = LAYOUT_base( \
  //,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
      _______ , _______ , _______ , KC_ESC  , _______ , _______ , KC_COLN , KC_SCLN , KC_LABK , KC_RABK , KC_QUES , _______ ,\
      _______ , _______ , _______ , KC_BSPC , _______ , _______ , KC_ENT  , KC_SPC  , KC_COMM , KC_DOT  , KC_SLSH , _______ ,\
      _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,\
      _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,\
      _______ \
  // ExtraKey: Split backspace key or it is below the enter key.
  ),
  [_FUNC] = LAYOUT_base( \
  //,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
      _______ , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , _______ ,\
      _______ , KC_F11  , KC_F12  , _______ , _______ , _______ , KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT , KC_PGUP , _______ ,\
      _______ , _______ , _______ , _______ , _______ , _______ , KC_HOME , KC_END  , _______ , _______ , KC_PGDN , _______ ,\
      _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,\
      _______ \
  // ExtraKey: Split backspace key or it is below the enter key.
  ),
  [_MOUSE] = LAYOUT_base( \
  //,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
      _______ , _______ , _______ , KC_ESC  , _______ , _______ , KC_BTN1 , KC_BTN2 , KC_BTN3 , KC_BTN4 , KC_BTN5 , _______ ,\
      _______ , _______ , _______ , KC_BSPC , _______ , _______ , KC_MS_L , KC_MS_D , KC_MS_U , KC_MS_R , _______ , _______ ,\
      _______ , _______ , _______ , _______ , _______ , _______ , KC_WH_L , KC_WH_D , KC_WH_U , KC_WH_R , _______ , _______ ,\
      _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,\
      _______ \
  // ExtraKey: Split backspace key or it is below the enter key.
  ),
  [_ADJUST] = LAYOUT_base( \
  //,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
      RESET   , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,\
      _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,\
      _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,\
      _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ ,\
      _______ \
  // ExtraKey: Split backspace key or it is below the enter key.
  )
};

static inline void update_change_layer(bool pressed, uint8_t layer1, uint8_t layer2, uint8_t layer3) {
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case FUNC:
      if (record->event.pressed) {
        layer_on(_FUNC);
      } else {
        layer_off(_FUNC);
      }
      return false;
      break;
    case MOUSE:
      if (record->event.pressed) {
        layer_on(_MOUSE);
      } else {
        layer_off(_MOUSE);
      }
      return false;
      break;
    case ADJUST:
      if (record->event.pressed) {
        layer_on(_ADJUST);
      } else {
        layer_off(_ADJUST);
      }
      return false;
      break;
  }
  return true;
}

void matrix_init_user(void) {
}

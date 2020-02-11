#include QMK_KEYBOARD_H
#include "keymap_jp.h"

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
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
  RGBRST = SAFE_RANGE,
  LOWER,
  RAISE,
};

#define KC________ KC_TRNS
#define KC_XXXXXXX KC_NO

// Adjust layer keys
#define KC_LRST  RGBRST
#define KC_LTOG  RGB_TOG
#define KC_LHUI  RGB_HUI
#define KC_LHUD  RGB_HUD
#define KC_LSAI  RGB_SAI
#define KC_LSAD  RGB_SAD
#define KC_LVAI  RGB_VAI
#define KC_LVAD  RGB_VAD
#define KC_LMOD  RGB_MOD
#define KC_LRMD  RGB_RMOD
#define KC_KNRM  AG_NORM
#define KC_KSWP  AG_SWAP

// Base layer mod tap
#define KC_ASF  LSFT_T(KC_A)
#define KC_SSF  LSFT_T(KC_SCLN)
#define KC_ZCT  LCTL_T(KC_Z)
#define KC_SCT  LCTL_T(KC_SLSH)
#define KC_XGU  LGUI_T(KC_X)
#define KC_DTGU LGUI_T(KC_DOT)
#define KC_CAL  LALT_T(KC_C)
#define KC_CMAL LALT_T(KC_COMM)

// Layer tap
#define KC_SPLO  LT(_LOWER, KC_SPC)
#define KC_ETRA  LT(_RAISE, KC_ENT)
#define KC_DFNC  LT(_FUNC, KC_D)
#define KC_FEXT  LT(_EXTEND, KC_F)
#define KC_GMOU  LT(_MOUSE, KC_G)
#define KC_PADJ  LT(_ADJUST, KC_P)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT( \
  //,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
      KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    , KC_Y    , KC_U    , KC_I    , KC_O    , KC_PADJ , \
      KC_ASF  , KC_S    , KC_DFNC , KC_FEXT , KC_GMOU , KC_H    , KC_J    , KC_K    , KC_L    , KC_SSF  , \
      KC_ZCT  , KC_XGU  , KC_CAL  , KC_V    , KC_B    , KC_N    , KC_M    , KC_CMAL , KC_DTGU , KC_SCT  , \
  //`---------+---------+---------+---------+---------+---------+---------+---------+---------+---------'
                                              KC_SPLO , KC_ETRA \
  //                                        `---------|---------'
  ),
  [_LOWER] = LAYOUT( \
  //,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
      KC_TILD , KC_BSLS , _______ , _______ , KC_TAB  , KC_QUOT , KC_DQT  , KC_UNDS , KC_PIPE , KC_COLN , \
      KC_GRV  , KC_EQL  , KC_PLUS , KC_MINS , KC_APP  , KC_LBRC , KC_RBRC , KC_LCBR , KC_RCBR , KC_SCLN , \
      _______ , _______ , _______ , _______ , _______ , KC_LPRN , KC_RPRN , KC_LABK , KC_RABK , KC_QUES , \
  //`---------+---------+---------+---------+---------+---------+---------+---------+---------+---------'
                                              _______ , _______ \
  //                                        `---------|---------'
  ),
  [_RAISE] = LAYOUT( \
  //,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
      KC_EXLM , KC_AT   , KC_HASH , KC_DLR  , KC_PERC , KC_CIRC , KC_AMPR , KC_ASTR , KC_LPRN , KC_RPRN , \
      KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , \
      _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , \
  //`---------+---------+---------+---------+---------+---------+---------+---------+---------+---------'
                                              _______ , _______ \
  //                                        `---------|---------'
  ),
  [_EXTEND] = LAYOUT( \
  //,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
      _______ , _______ , KC_ESC  , _______ , _______ , KC_COLN , KC_SCLN , KC_LABK , KC_RABK , KC_QUES , \
      _______ , _______ , KC_BSPC , _______ , _______ , KC_ENT  , KC_SPC  , KC_COMM , KC_DOT  , KC_SCLN , \
      _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , \
  //`---------+---------+---------+---------+---------+---------+---------+---------+---------+---------'
                                              _______ , _______ \
  //                                        `---------|---------'
  ),
  [_FUNC] = LAYOUT( \
  //,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
      KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , \
      KC_F11  , KC_F12  , _______ , _______ , _______ , KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT , _______ , \
      _______ , _______ , _______ , _______ , _______ , KC_HOME , KC_END  , KC_PGUP , KC_PGDN , _______ , \
  //`---------+---------+---------+---------+---------+---------+---------+---------+---------+---------'
                                              _______ , _______ \
  //                                        `---------|---------'
  ),
  [_MOUSE] = LAYOUT( \
  //,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
      _______ , _______ , KC_ESC  , _______ , _______ , KC_BTN1 , KC_BTN2 , KC_BTN3 , KC_BTN4 , KC_BTN5 , \
      _______ , _______ , KC_BSPC , _______ , _______ , KC_MS_L , KC_MS_D , KC_MS_U , KC_MS_R , _______ , \
      _______ , _______ , _______ , _______ , _______ , KC_WH_L , KC_WH_D , KC_WH_U , KC_WH_R , _______ , \
  //`---------+---------+---------+---------+---------+---------+---------+---------+---------+---------'
                                              _______ , _______ \
  //                                        `---------|---------'
  ),
  [_ADJUST] = LAYOUT( \
  //,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
      RESET   , _______ , _______ , _______ , KC_LTOG , KC_LHUI , KC_LSAI , KC_LVAI , KC_LRST , _______ , \
      _______ , _______ , _______ , _______ , KC_LMOD , KC_LHUD , KC_LSAD , KC_LVAD , _______ , _______ , \
      _______ , _______ , _______ , _______ , KC_LRMD , _______ , _______ , _______ , _______ , _______ , \
  //`---------+---------+---------+---------+---------+---------+---------+---------+---------+---------'
                                              _______ , _______ \
  //                                        `---------|---------'
  )
};

int RGB_current_mode;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  bool result = false;
  switch (keycode) {
    #ifdef RGBLIGHT_ENABLE
      //led operations - RGB mode change now updates the RGB_current_mode to allow the right RGB mode to be set after reactive keys are released
      case RGB_MOD:
          if (record->event.pressed) {
            rgblight_mode(RGB_current_mode);
            rgblight_step();
            RGB_current_mode = rgblight_config.mode;
          }
        break;
      case RGBRST:
          if (record->event.pressed) {
            eeconfig_update_rgblight_default();
            rgblight_enable();
            RGB_current_mode = rgblight_config.mode;
          }
        break;
    #endif
    default:
      result = true;
      break;
  }
  return result;
}

void matrix_init_user(void) {
  #ifdef RGBLIGHT_ENABLE
    RGB_current_mode = rgblight_config.mode;
  #endif
}

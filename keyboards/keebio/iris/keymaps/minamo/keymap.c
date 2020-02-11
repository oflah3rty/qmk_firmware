#include "iris.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

#define _QWERTY 0
#define _LOWER 1
#define _RAISE 2
#define _EXTEND 3
#define _FUNC  4
#define _MOUSE 5
#define _ADJUST 6

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  MOUSE,
  ADJUST,
  //RGB_RST,
  //TAP_ANM,
};

#define KC_ KC_TRNS
#define KC________ KC_TRNS
#define KC_XXXXXXX KC_NO

#define KC_M_SPACE CTL_T(KC_SPC)
#define KC_M_ENT SFT_T(KC_ENT)
#define KC_M_LOWR LT(_LOWER, KC_ESC)
#define KC_M_RASE LT(_RAISE, KC_BSPC)
#define KC_M_ALT ALT_T(KC_BSPC)

#define KC_DFNC LT(_FUNC, KC_D)
#define KC_GMOU LT(_MOUSE, KC_G)
#define KC_FEXT LT(_EXTEND, KC_F)

#define KC_LOWR LOWER
#define KC_RASE RAISE
#define KC_ADJ  ADJUST
#define KC_RST RESET
#define KC_BL_S BL_STEP
#define KC_DBUG DEBUG

#ifdef RGBLIGHT_ENABLE

#define KC_RRST RGB_RST
#define KC_RTOG RGB_TOG
#define KC_RMOD RGB_MOD
#define KC_RRMD RGB_RMOD
#define KC_RHUI RGB_HUI
#define KC_RHUD RGB_HUD
#define KC_RSAI RGB_SAI
#define KC_RSAD RGB_SAD
#define KC_RVAI RGB_VAI
#define KC_RVAD RGB_VAD
#define KC_ANIME TAP_ANM

extern rgblight_config_t rgblight_config;
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_QWERTY] = LAYOUT_kc(
  //.-------+-------+-------+-------+-------+-------.                .-------+-------+-------+-------+-------+-------.
     ESC    ,LCTRL  ,LALT   ,DEL    ,PGUP   ,PGDN   ,                 LEFT   ,DOWN   ,UP     ,RGHT   ,HOME   ,END    ,
     TAB    ,Q      ,W      ,E      ,R      ,T      ,                 Y      ,U      ,I      ,O      ,P      ,BSPC   ,
     LCTL   ,A      ,S      ,DFNC   ,FEXT   ,GMOU   ,                 H      ,J      ,K      ,L      ,SCLN   ,QUOT   ,
     LSFT   ,Z      ,X      ,C      ,V      ,B      ,ADJ    , ADJ    ,N      ,M      ,COMM   ,DOT    ,SLSH   ,ESC    ,
  //`-------+-------+-------+-------+-------+-------+-------||-------+-------+-------+-------+-------+-------+-------'
                                     LGUI   ,M_LOWR ,M_SPACE, M_ENT  ,M_RASE ,M_ALT
  ),

  [_LOWER] = LAYOUT_kc(
  //.-------+-------+-------+-------+-------+-------.                .-------+-------+-------+-------+-------+-------.
     F1     ,F2     ,F3     ,F4     ,F5     ,F6     ,                 F7     ,F8     ,F9     ,F10    ,F11    ,F12    ,
     _______,TILD   ,BSLS   ,_______,_______,TAB    ,                 QUOT   ,DQT    ,UNDS   ,PIPE   ,COLN   ,_______,
     _______,GRV    ,EQL    ,PLUS   ,MINS   ,APP    ,                 LBRC   ,RBRC   ,LCBR   ,RCBR   ,SCLN   ,_______,
     _______,_______,_______,_______,_______,_______,_______, _______,LPRN   ,RPRN   ,LABK   ,RABK   ,QUES   ,_______,
  //`-------+-------+-------+-------+-------+-------+-------||-------+-------+-------+-------+-------+-------+-------'
                                     _______,_______,_______, _______,_______,_______
  ),

  [_RAISE] = LAYOUT_kc(
  //.-------+-------+-------+-------+-------+-------.                .-------+-------+-------+-------+-------+-------.
     _______,_______,_______,_______,_______,_______,                 _______,_______,_______,_______,_______,_______,
     EQL    ,EXLM   ,AT     ,HASH   ,DLR    ,PERC   ,                 CIRC   ,AMPR   ,ASTR   ,LPRN   ,RPRN   ,_______,
     _______,1      ,2      ,3      ,4      ,5      ,                 6      ,7      ,8      ,9      ,0      ,_______,
     _______,PLUS   ,MINS   ,ASTR   ,SLSH   ,DOT    ,_______, _______,_______,_______,COMM   ,DOT    ,SLSH   ,_______,
  //`-------+-------+-------+-------+-------+-------+-------||-------+-------+-------+-------+-------+-------+-------'
                                     _______,_______,_______, _______,_______,_______
  ),

  [_EXTEND] = LAYOUT_kc(
  //.-------+-------+-------+-------+-------+-------.                .-------+-------+-------+-------+-------+-------.
     _______,_______,_______,_______,_______,_______,                 _______,_______,_______,_______,_______,_______,
     _______,_______,_______,ESC    ,_______,_______,                 COLN   ,SCLN   ,LABK   ,RABK   ,QUES   ,_______,
     _______,_______,_______,BSPC   ,_______,_______,                 ENT    ,SPC    ,COMM   ,DOT    ,SLSH   ,_______,
     _______,_______,_______,_______,_______,_______,_______, _______,_______,_______,_______,_______,_______,_______,
  //`-------+-------+-------+-------+-------+-------+-------||-------+-------+-------+-------+-------+-------+-------'
                                     _______,_______,_______, _______,_______,_______
  ),

  [_FUNC] = LAYOUT_kc(
  //.-------+-------+-------+-------+-------+-------.                .-------+-------+-------+-------+-------+-------.
     _______,_______,_______,_______,_______,_______,                 _______,_______,_______,_______,_______,_______,
     _______,_______,_______,_______,_______,_______,                 _______,_______,_______,_______,_______,_______,
     _______,_______,_______,_______,_______,_______,                 LEFT   ,DOWN   ,UP     ,RIGHT  ,_______,_______,
     _______,_______,_______,_______,_______,_______,_______, _______,HOME   ,END    ,_______,_______,_______,_______,
  //`-------+-------+-------+-------+-------+-------+-------||-------+-------+-------+-------+-------+-------+-------'
                                     _______,_______,_______, _______,_______,_______
  ),

  [_MOUSE] = LAYOUT_kc(
  //.-------+-------+-------+-------+-------+-------.                .-------+-------+-------+-------+-------+-------.
     _______,_______,_______,_______,_______,_______,                 _______,_______,_______,_______,_______,_______,
     _______,_______,_______,ESC    ,_______,_______,                 BTN1   ,BTN2   ,BTN3   ,BTN4   ,BTN5   ,_______,
     _______,_______,_______,BSPC   ,_______,_______,                 MS_L   ,MS_D   ,MS_U   ,MS_R   ,_______,_______,
     _______,_______,_______,_______,_______,_______,_______, _______,WH_L   ,WH_D   ,WH_U   ,WH_R   ,_______,_______,
  //`-------+-------+-------+-------+-------+-------+-------||-------+-------+-------+-------+-------+-------+-------'
                                     _______,_______,_______, _______,_______,_______
  ),

  [_ADJUST] = LAYOUT_kc(
  //.-------+-------+-------+-------+-------+-------.                .-------+-------+-------+-------+-------+-------.
     RST    ,_______,_______,_______,_______,_______,                 ACL0   ,ACL1   ,ACL2   ,_______,_______,RST    ,
     _______,_______,_______,_______,_______,_______,                 BTN1   ,BTN2   ,BTN3   ,BTN4   ,_______,_______,
     _______,_______,_______,_______,_______,_______,                 MS_L   ,MS_D   ,MS_U   ,MS_R   ,_______,_______,
     BL_S   ,_______,_______,_______,_______,_______,_______, _______,WH_L   ,WH_D   ,WH_U   ,WH_R   ,_______,_______,
  //`-------+-------+-------+-------+-------+-------+-------||-------+-------+-------+-------+-------+-------+-------'
                                     _______,_______,_______, _______,_______,_______
  )

};

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

//bool isTapAnimation = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer(_LOWER, _RAISE, _ADJUST);
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
//  case RGB_RST:
//    #ifdef RGBLIGHT_ENABLE
//      if (record->event.pressed) {
//        eeconfig_update_rgblight_default();
//        rgblight_enable();
//      }
//    #endif
//    break;
//  case TAP_ANM:
//    if (record->event.pressed) {
//      isTapAnimation = !isTapAnimation;
//    }
//    break;
  }

//if (isTapAnimation) {
//  rgblight_mode_noeeprom(1);
//  uint16_t hue = (rgblight_config.hue + 5) % 360;
//  rgblight_sethsv_noeeprom(hue, rgblight_config.sat, rgblight_config.val);
//}

  return true;
}

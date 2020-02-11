#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define _BASE  0
#define _EXTRA 1
#define _FUNC  2
#define _ADJ   3

#define LAYER_0 TO(_BASE)
#define LAYER_1 TO(_EXTRA)
#define LAYER_2 TO(_FUNC)
#define LAYER_3 TO(_ADJ)

#define MY_SPC  LSFT_T(KC_SPC)
#define MY_TAB  LSFT_T(KC_TAB)
#define MY_ENT  LSFT_T(KC_ENT)
#define MY_SFT  OSM(MOD_LSFT)
#define MY_CTRL OSM(MOD_LCTL)
#define MY_GUI  OSM(MOD_LGUI)
#define MY_ALT  OSM(MOD_LALT)

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
  [_BASE] = LAYOUT_ortho_3x10(
    KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   , KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   ,
    KC_A   , KC_S   , KC_D   , KC_F   , KC_G   , KC_H   , KC_J   , KC_K   , KC_L   , LAYER_1,
    KC_Z   , KC_X   , KC_C   , KC_V   , MY_SPC , MY_SPC , KC_B   , KC_N   , KC_M   , XXXXXXX
  ),
  [_EXTRA] = LAYOUT_ortho_3x10(
    KC_1   , KC_2   , KC_3   , KC_4   , KC_5   , KC_6   , KC_7   , KC_8   , KC_9   , KC_0   ,
    KC_BSPC, KC_ESC , KC_LBRC, KC_RBRC, KC_ENT , KC_EQL , KC_MINS, KC_QUOT, KC_SCLN, LAYER_2,
    MY_CTRL, MY_GUI , MY_ALT , LAYER_0, MY_ENT , MY_ENT , KC_COMM, KC_DOT , KC_SLSH, XXXXXXX
  ),
  [_FUNC] = LAYOUT_ortho_3x10(
    KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 ,
    MY_SFT , KC_F11 , KC_F12 , KC_HOME, KC_END , KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, LAYER_0,
    LAYER_3, KC_PGUP, KC_PGDN, LAYER_0, MY_TAB , MY_TAB , KC_GRV , KC_BSLS, XXXXXXX, XXXXXXX
  ),
  [_ADJ] = LAYOUT_ortho_3x10(
    RESET  , XXXXXXX, XXXXXXX, XXXXXXX, KC_RTOG, KC_RHUI, KC_RSAI, KC_RVAI, XXXXXXX, XXXXXXX,
    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, KC_RMOD, KC_RHUD, KC_RSAD, KC_RVAD, XXXXXXX, LAYER_0,
    XXXXXXX, XXXXXXX, XXXXXXX, LAYER_0, KC_RRMD, XXXXXXX, XXXXXXX, KC_MUTE, KC_VOLU, KC_VOLD
  )
};

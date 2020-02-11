#include QMK_KEYBOARD_H
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

//#define ERGO42
#ifdef ERGO42

#define BASE 0
#define META 1
#define SYMB 2
#define GAME 3
#define BIAC 4
#define BMETA 5
#define BSYMB 6

#else

#define _BASE   0
#define _LOWER  1
#define _RAISE  2
#define _EXTEND 3
#define _FUNC   4
#define _MOUSE  5
#define _ADJUST 6

#define KC_CSPC LCTL_T(KC_SPACE)
#define KC_SENT LSFT_T(KC_ENTER)
#define KC_LOW  LT(_LOWER, KC_ESC)
#define KC_RAI  LT(_RAISE, KC_BSPC)
#define KC_ECAJ LT(_ADJUST, KC_ESC)
#define KC_DLGI LGUI_T(KC_DEL)
#define KC_TBAL LALT_T(KC_TAB)

#define KC_DFNC LT(_FUNC, KC_D)
#define KC_GMOU LT(_MOUSE, KC_G)
#define KC_FEXT LT(_EXTEND, KC_F)

#define KC_SGIC SGUI(KC_C)
#define KC_SGIQ SGUI(KC_Q)

#define KC_MOU  MO(_MOUSE)
#define KC_FUNC MO(_FUNC)

#endif

// Fillers to make layering more clear
#define _______ KC_TRNS
#define XXXXXXX KC_NO

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//#define ERGO42
#ifdef ERGO42

[BASE] = LAYOUT( \
  KC_TAB,   KC_Q,    KC_W,   KC_E,    KC_R,             KC_T,          KC_RBRC,       KC_BSLS,    KC_Y,             KC_U,    KC_I,     KC_O,     KC_P,     KC_LBRC, \
  KC_LALT,  KC_A,    KC_S,   KC_D,    KC_F,             KC_G,          S(KC_8),       S(KC_9),    KC_H,             KC_J,    KC_K,     KC_L,     KC_SCLN,  KC_QUOT, \
  KC_LSFT,  KC_Z,    KC_X,   KC_C,    KC_V,             KC_B,          S(KC_RBRC),    S(KC_BSLS), KC_N,             KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,  SFT_T(KC_RO), \
  KC_LCTRL, KC_LGUI, KC_APP, TG(BIAC),LT(SYMB, KC_ESC), RCTL_T(KC_SPC), SFT_T(KC_TAB), KC_BSPC,    LT(META, KC_ENT), KC_DELT, KC_PSCR,  TG(GAME), TG(SYMB), KC_JYEN \
),
[META] = LAYOUT( \
  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    _______, _______, KC_7,    KC_8,    KC_9,  KC_0,    KC_MINS, KC_EQL, \
  _______, KC_F1,   XXXXXXX, KC_MHEN, KC_HENK, XXXXXXX, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, XXXXXXX, XXXXXXX, \
  _______, KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   _______, _______, KC_F7,   KC_F8,   KC_F9, KC_F10,  KC_F11,  SFT_T(KC_RO), \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET, _______, _______, _______ \
),
[SYMB] = LAYOUT( \
  S(KC_1), S(KC_2), S(KC_3), S(KC_4), S(KC_5), S(KC_6), _______, _______, S(KC_7), S(KC_8), S(KC_9),    S(KC_0),   S(KC_MINS), S(KC_EQL), \
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, XXXXXXX,    XXXXXXX,   S(KC_SCLN), S(KC_QUOT), \
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX, XXXXXXX, S(KC_COMM), S(KC_DOT), S(KC_SLSH), S(KC_RO), \
  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,    _______,   _______,    _______ \
),
[GAME] = LAYOUT( \
  KC_TAB,   KC_Q,    KC_W,   KC_E,    KC_R,   KC_T,   KC_RBRC,    KC_BSLS,    KC_Y,   KC_U,    KC_I,     KC_O,    KC_P,    KC_LBRC, \
  KC_LALT,  KC_A,    KC_S,   KC_D,    KC_F,   KC_G,   S(KC_8),    S(KC_9),    KC_H,   KC_J,    KC_K,     KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT,  KC_Z,    KC_X,   KC_C,    KC_V,   KC_B,   S(KC_RBRC), S(KC_BSLS), KC_N,   KC_M,    KC_COMM,  KC_DOT,  KC_SLSH, SFT_T(KC_RO), \
  KC_LCTRL, KC_LGUI, KC_APP, KC_PSCR, KC_ESC, KC_SPC, KC_TAB,     KC_BSPC,    KC_ENT, KC_DELT, KC_PSCR,  _______, _______, KC_JYEN \
),
[BIAC] = LAYOUT( \
  KC_TAB,   KC_SCLN,KC_COMM, KC_DOT,  KC_P,             KC_Q,          KC_RBRC,       KC_BSLS,    KC_Y,             KC_G,    KC_D,     KC_M,     KC_F,     KC_LBRC, \
  KC_LALT,  KC_A,    KC_O,   KC_E,    KC_I,             KC_U,          S(KC_8),       S(KC_9),    KC_B,             KC_N,    KC_T,     KC_R,     KC_S,     KC_QUOT, \
  KC_LSFT,  KC_Z,    KC_X,   KC_C,    KC_V,             KC_W,          S(KC_RBRC),    S(KC_BSLS), KC_H,             KC_J,    KC_K,     KC_L,     KC_SLSH,  SFT_T(KC_RO), \
  KC_LCTRL, KC_LGUI, KC_APP, _______, LT(BSYMB, KC_ESC),RCTL_T(KC_SPC),SFT_T(KC_TAB), KC_BSPC,    LT(BMETA, KC_ENT),KC_DELT, KC_PSCR,  XXXXXXX,  XXXXXXX,  KC_JYEN \
),
[BMETA] = LAYOUT( \
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   _______, _______, KC_F7,   KC_F8,   KC_F9, KC_F10,  KC_F11,  KC_F12, \
  _______, KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    _______, _______, KC_7,    KC_8,    KC_9,  KC_0,    KC_MINS, KC_EQL, \
  _______, KC_1,    XXXXXXX, KC_MHEN, KC_HENK, XXXXXXX, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, XXXXXXX, SFT_T(KC_RO), \
  _______, _______, _______, XXXXXXX, _______, _______, _______, _______, _______, _______, RESET, _______, _______, _______ \
),
[BSYMB] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, XXXXXXX,    XXXXXXX,    KC_RBRC,    KC_BSLS,   S(KC_SCLN), S(KC_QUOT), \
  _______, S(KC_2), S(KC_3), S(KC_4), S(KC_5), S(KC_6), _______, _______, S(KC_7),    S(KC_8),    S(KC_9),    S(KC_0),   S(KC_MINS), S(KC_EQL), \
  _______, S(KC_1), XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, S(KC_RBRC), S(KC_BSLS), S(KC_COMM), S(KC_DOT), S(KC_SLSH), S(KC_RO), \
  _______, _______, _______, XXXXXXX, _______, _______, _______, _______, _______,    _______,    _______,    _______,   _______,    _______ \
)

#else

[_BASE] = LAYOUT( \
// ,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
     KC_TAB  , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , KC_DEL  , \
     KC_ESC  , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    , KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , KC_BSPC , \
     KC_LCTL , KC_A    , KC_S    , KC_D    , KC_F    , KC_G    , KC_H    , KC_J    , KC_K    , KC_L    , KC_SCLN , KC_LCTL , \
     KC_LSFT , KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    , KC_N    , KC_M    , KC_COMM , KC_DOT  , KC_SLSH , KC_LSFT , \
     KC_MOU  , KC_FUNC , XXXXXXX , KC_DLGI , KC_LOW  , KC_SPC  , KC_ENT  , KC_RAI  , KC_TBAL , XXXXXXX , XXXXXXX , XXXXXXX   \
// ,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
),
[_LOWER] = LAYOUT( \
// ,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
     _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , \
     _______ , KC_TILD , KC_BSLS , _______ , _______ , KC_TAB  , KC_QUOT , KC_DQT  , KC_UNDS , KC_PIPE , KC_COLN , _______ , \
     _______ , KC_GRV  , KC_EQL  , KC_PLUS , KC_MINS , KC_APP  , KC_LBRC , KC_RBRC , KC_LCBR , KC_RCBR , KC_SCLN , _______ , \
     _______ , KC_SGIC , _______ , _______ , _______ , _______ , KC_LPRN , KC_RPRN , KC_LABK , KC_RABK , KC_QUES , _______ , \
     _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______   \
// ,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
),
[_RAISE] = LAYOUT( \
// ,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
     _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , \
     _______ , KC_EXLM , KC_AT   , KC_HASH , KC_DLR  , KC_PERC , KC_CIRC , KC_AMPR , KC_ASTR , KC_LPRN , KC_RPRN , _______ , \
     _______ , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , _______ , \
     _______ , _______ , _______ , _______ , KC_MUTE , KC_VOLU , KC_LEFT , KC_LEFT , KC_RGHT , KC_DOWN , KC_UP   , _______ , \
     _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______   \
// ,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
),
[_EXTEND] =  LAYOUT( \
// ,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
     _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , \
     _______ , _______ , _______ , KC_ESC  , _______ , _______ , KC_COLN , KC_SCLN , KC_LABK , KC_RABK , KC_QUES , _______ , \
     _______ , _______ , _______ , KC_BSPC , _______ , _______ , KC_ENT  , KC_SPC  , KC_COMM , KC_DOT  , KC_SLSH , _______ , \
     _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , \
     _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______   \
// ,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
),
[_FUNC] =  LAYOUT( \
// ,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
     _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , \
     _______ , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6   , KC_F7   , KC_F8   , KC_F9   , KC_F10  , _______ , \
     _______ , KC_F11  , KC_F12  , _______ , KC_HOME , KC_END  , KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT , _______ , _______ , \
     _______ , _______ , _______ , _______ , _______ , _______ , KC_PGUP , KC_PGDN , _______ , _______ , _______ , _______ , \
     _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______   \
// ,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
),
[_MOUSE] =  LAYOUT( \
// ,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
     _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , \
     _______ , _______ , _______ , KC_ESC  , _______ , _______ , KC_BTN1 , KC_BTN2 , KC_BTN3 , KC_BTN4 , KC_BTN5 , _______ , \
     _______ , _______ , _______ , KC_BSPC , _______ , _______ , KC_MS_L , KC_MS_D , KC_MS_U , KC_MS_R , _______ , _______ , \
     _______ , _______ , _______ , _______ , _______ , _______ , KC_WH_L , KC_WH_D , KC_WH_U , KC_WH_R , _______ , _______ , \
     _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______   \
// ,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
),
[_ADJUST] =  LAYOUT( \
// ,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
     _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , \
     _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , \
     _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , \
     _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , \
     _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______ , _______   \
// ,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
)

#endif
};


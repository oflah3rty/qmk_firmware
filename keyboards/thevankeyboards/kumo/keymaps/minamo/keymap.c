#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#define _BASE    0
#define _CUSTOM  1
#define _LOWER   2
#define _RAISE   3
#define _SUPPORT 4
#define _ADJUST  5

enum custom_keycodes {
  ONESHOT_CLEAR = SAFE_RANGE,
  ONESHOT_SHIFT,
  ONESHOT_CTRL,
  ONESHOT_ALT,
  ONESHOT_GUI,
  RGB_RST,
};

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

#define KC_L1 DF(_BASE)
#define KC_L2 DF(_CUSTOM)

#define KC_LCMM LT(_LOWER, KC_COMM)
#define KC_LDOT LT(_RAISE, KC_DOT)
#define KC_LSLS LT(_SUPPORT, KC_SLSH)
#define KC_LENT LT(_ADJUST, KC_ENTER)
#define KC_LLOW MO(_LOWER)
#define KC_LRAI MO(_RAISE)
#define KC_MENT LSFT_T(KC_ENT)
#define KC_MSPC LCTL_T(KC_SPC)

// KUMO
#define KC_GTAB LGUI_T(KC_TAB)

#define KC_1CLR ONESHOT_CLEAR
#define KC_1SFT ONESHOT_SHIFT
#define KC_1CTL ONESHOT_CTRL
#define KC_1ALT ONESHOT_ALT
#define KC_1GUI ONESHOT_GUI

#define KC_JPN  LALT(KC_GRV)

// LED
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
  [_BASE] = LAYOUT_arrow(
//,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
    KC_ESC  , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    , KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , KC_BSPC ,
    KC_GTAB , KC_A    , KC_S    , KC_D    , KC_F    , KC_G    , KC_H    , KC_J    , KC_K    , KC_L    , KC_LENT , KC_LENT ,
    KC_LALT , KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    , KC_N    , KC_M    , KC_LCMM , KC_LDOT , KC_LSLS , KC_UP   ,
    KC_LCTL , KC_APP  , KC_LLOW ,                     KC_MSPC , KC_MENT ,           KC_LRAI , KC_LEFT , KC_RGHT , KC_DOWN
//,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
  ),
  [_CUSTOM] = LAYOUT_arrow(
//,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
    _______ , KC_Q    , KC_W    , KC_F    , KC_P    , KC_G    , KC_J    , KC_L    , KC_U    , KC_Y    , KC_LENT , _______ ,
    _______ , KC_A    , KC_R    , KC_S    , KC_T    , KC_D    , KC_H    , KC_N    , KC_E    , KC_I    , KC_O    , _______ ,
    _______ , KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    , KC_K    , KC_M    , KC_LCMM , KC_LDOT , KC_LSLS , _______ ,
    _______ , _______ , _______ ,                     _______ , _______ ,           _______ , _______ , _______ , _______
//,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
  ),
  [_LOWER] = LAYOUT_arrow(
//,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
    _______ , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , _______ ,
    _______ , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    , KC_GRV  , KC_QUOT , XXXXXXX , KC_SCLN , KC_SCLN , _______ ,
    _______ , KC_1CTL , KC_1ALT , KC_1GUI , KC_1SFT , KC_LBRC , KC_RBRC , KC_EQL  , _______ , KC_MINS , KC_BSLS , _______ ,
    _______ , _______ , _______ ,                     _______ , _______ ,           _______ , _______ , _______ , _______
//,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
  ),
  [_RAISE] = LAYOUT_arrow(
//,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
    _______ , KC_PGUP , KC_HOME , KC_UP   , KC_END  , KC_F1   , KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6   , _______ ,
    _______ , KC_PGDN , KC_LEFT , KC_DOWN , KC_RGHT , KC_F7   , KC_F8   , KC_F9   , KC_F10  , KC_F11  , KC_F12  , _______ ,
    _______ , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_PSCR , KC_APP  , KC_1CLR , _______ , KC_DEL  , _______ ,
    _______ , _______ , _______ ,                     _______ , _______ ,           _______ , _______ , _______ , _______
//,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
  ),
  [_SUPPORT] = LAYOUT_arrow(
//,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
    _______ , KC_ESC  , XXXXXXX , KC_HENK , KC_MHEN , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , _______ , _______ ,
    _______ , KC_TAB  , XXXXXXX , KC_BSPC , KC_SPC  , XXXXXXX , XXXXXXX , KC_JPN  , KC_LCTL , KC_LSFT , KC_BSPC , _______ ,
    _______ , KC_CAPS , XXXXXXX , XXXXXXX , KC_SPC  , KC_SPC  , KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT , _______ , _______ ,
    _______ , _______ , _______ ,                     _______ , _______ ,           _______ , _______ , _______ , _______
//,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
  ),
  [_ADJUST] = LAYOUT_arrow(
//,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
    RESET   , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_RTOG , KC_RHUI , KC_RSAI , KC_RVAI , XXXXXXX , XXXXXXX , XXXXXXX ,
    XXXXXXX , KC_L1   , KC_L2   , XXXXXXX , XXXXXXX , KC_RMOD , KC_RHUD , KC_RSAD , KC_RVAD , XXXXXXX , XXXXXXX , XXXXXXX ,
    XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_RRMD , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,
    XXXXXXX , XXXXXXX , XXXXXXX ,                     XXXXXXX , XXXXXXX ,           XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX
//,---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------+---------.
  )
};

// ワンショットモディファイアの追加
// ※ 各モディファイアは合成、保持される
void append_onshot_modifier(uint8_t newkey) {
  uint8_t modkeys = get_oneshot_mods() | newkey;
  set_oneshot_mods(modkeys);
}
void set_oneshot_shift(void) { append_onshot_modifier(MOD_LSFT); }
void set_oneshot_ctrl(void)  { append_onshot_modifier(MOD_LCTL); }
void set_oneshot_alt(void)   { append_onshot_modifier(MOD_LALT); }
void set_oneshot_gui(void)   { append_onshot_modifier(MOD_LGUI); }
void set_oneshot_clear(void) {
  clear_oneshot_mods();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case ONESHOT_CLEAR: set_oneshot_clear(); break;
        case ONESHOT_SHIFT: set_oneshot_shift(); break;
        case ONESHOT_CTRL:  set_oneshot_ctrl(); break;
        case ONESHOT_ALT:   set_oneshot_alt(); break;
        case ONESHOT_GUI:   set_oneshot_gui(); break;
        default:
            break;
    }
    return true;
};

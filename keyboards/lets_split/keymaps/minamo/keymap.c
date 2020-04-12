#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
#define _BASE    0
#define _CUSTOM  1
#define _TERRARIA 2
#define _LOWER   3
#define _RAISE   4
#define _SUPPORT 5
#define _ADJUST  6

enum custom_keycodes {
  ONESHOT_CLEAR = SAFE_RANGE,
  ONESHOT_SHIFT,
  ONESHOT_CTRL,
  ONESHOT_ALT,
  ONESHOT_GUI,
  RGB_RST,
  TAP_ANM
};

// Fillers to make layering more clear
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
#define KC_TERR DF(_TERRARIA)

#define KC_LCMM LT(_LOWER, KC_COMM)
#define KC_LDOT LT(_RAISE, KC_DOT)
#define KC_LSLS LT(_SUPPORT, KC_SLSH)
#define KC_LENT LT(_ADJUST, KC_ENTER)
#define KC_LLOW LT(_LOWER, KC_ESC)
#define KC_LRAI LT(_RAISE, KC_BSPC)
#define KC_MENT LSFT_T(KC_ENT)
#define KC_MSPC LCTL_T(KC_SPC)

#define KC_1CLR ONESHOT_CLEAR
#define KC_1SFT ONESHOT_SHIFT
#define KC_1CTL ONESHOT_CTRL
#define KC_1ALT ONESHOT_ALT
#define KC_1GUI ONESHOT_GUI

#define KC_JPN  LALT(KC_GRV)

#ifdef RGBLIGHT_ENABLE
extern rgblight_config_t rgblight_config;
#endif

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_BASE] = LAYOUT_ortho_4x12(
// ,---------+---------+---------+---------+---------+---------.  ,---------+---------+---------+---------+---------+---------.
     KC_ESC  , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    ,    KC_Y    , KC_U    , KC_I    , KC_O    , KC_P    , KC_BSPC , \
     KC_TAB  , KC_A    , KC_S    , KC_D    , KC_F    , KC_G    ,    KC_H    , KC_J    , KC_K    , KC_L    , KC_LENT , KC_APP  , \
     KC_LCTL , KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    ,    KC_N    , KC_M    , KC_LCMM , KC_LDOT , KC_LSLS , KC_LSFT , \
     KC_LENT , XXXXXXX , XXXXXXX , KC_LGUI , KC_LLOW , KC_MSPC ,    KC_MENT , KC_LRAI , KC_LALT , XXXXXXX , XXXXXXX , KC_DEL    \
// `---------+---------+---------+---------+---------+---------/  `---------+---------+---------+---------+---------+---------/
),
[_CUSTOM] = LAYOUT_ortho_4x12(
// ,---------+---------+---------+---------+---------+---------.  ,---------+---------+---------+---------+---------+---------.
     _______ , KC_Q    , KC_W    , KC_F    , KC_P    , KC_G    ,    KC_J    , KC_L    , KC_U    , KC_Y    , KC_LENT , _______ , \
     _______ , KC_A    , KC_R    , KC_S    , KC_T    , KC_D    ,    KC_H    , KC_N    , KC_E    , KC_I    , KC_O    , _______ , \
     _______ , KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    ,    KC_K    , KC_M    , KC_LCMM , KC_LDOT , KC_LSLS , _______ , \
     _______ , _______ , _______ , _______ , _______ , _______ ,    _______ , _______ , _______ , _______ , _______ , _______   \
// `---------+---------+---------+---------+---------+---------/  `---------+---------+---------+---------+---------+---------/
),
[_LOWER] = LAYOUT_ortho_4x12( \
// ,---------+---------+---------+---------+---------+---------.  ,---------+---------+---------+---------+---------+---------.
     _______ , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    ,    XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , _______ , \
     _______ , KC_1    , KC_2    , KC_3    , KC_4    , KC_5    ,    KC_GRV  , KC_QUOT , XXXXXXX , KC_SCLN , KC_SCLN , _______ , \
     _______ , KC_1CTL , KC_1ALT , KC_1GUI , KC_1SFT , KC_LBRC ,    KC_RBRC , KC_EQL  , _______ , KC_MINS , KC_BSLS , _______ , \
     _______ , _______ , _______ , _______ , _______ , _______ ,    _______ , _______ , _______ , _______ , _______ , _______   \
// `---------+---------+---------+---------+---------+---------/  `---------+---------+---------+---------+---------+---------/
),
[_RAISE] = LAYOUT_ortho_4x12( \
// ,---------+---------+---------+---------+---------+---------.  ,---------+---------+---------+---------+---------+---------.
     _______ , KC_PGUP , KC_HOME , KC_UP   , KC_END  , KC_F1   ,    KC_F2   , KC_F3   , KC_F4   , KC_F5   , KC_F6   , _______ , \
     _______ , KC_PGDN , KC_LEFT , KC_DOWN , KC_RGHT , KC_F7   ,    KC_F8   , KC_F9   , KC_F10  , KC_F11  , KC_F12  , _______ , \
     _______ , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,    KC_PSCR , KC_APP  , KC_1CLR , _______ , KC_DEL  , _______ , \
     _______ , _______ , _______ , _______ , _______ , _______ ,    _______ , _______ , _______ , _______ , _______ , _______   \
// `---------+---------+---------+---------+---------+---------/  `---------+---------+---------+---------+---------+---------/
),
[_SUPPORT] = LAYOUT_ortho_4x12( \
// ,---------+---------+---------+---------+---------+---------.  ,---------+---------+---------+---------+---------+---------.
     _______ , KC_ESC  , XXXXXXX , KC_HENK , KC_MHEN , XXXXXXX ,    XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , _______ , _______ , \
     _______ , KC_TAB  , XXXXXXX , KC_BSPC , KC_SPC  , XXXXXXX ,    XXXXXXX , KC_JPN  , KC_LCTL , KC_LSFT , KC_BSPC , _______ , \
     _______ , KC_CAPS , XXXXXXX , XXXXXXX , KC_SPC  , KC_SPC  ,    KC_LEFT , KC_DOWN , KC_UP   , KC_RGHT , _______ , _______ , \
     _______ , _______ , _______ , _______ , _______ , _______ ,    _______ , _______ , _______ , _______ , _______ , _______   \
// `---------+---------+---------+---------+---------+---------/  `---------+---------+---------+---------+---------+---------/
),
[_TERRARIA] = LAYOUT_ortho_4x12( \
// ,---------+---------+---------+---------+---------+---------.  ,---------+---------+---------+---------+---------+---------.
     KC_ESC  , KC_Q    , KC_W    , KC_E    , KC_R    , KC_T    ,    XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_LENT , XXXXXXX , \
     KC_LCTL , KC_A    , KC_S    , KC_D    , KC_F    , KC_G    ,    XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_LENT , XXXXXXX , \
     KC_LSFT , KC_Z    , KC_X    , KC_C    , KC_V    , KC_B    ,    XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_LENT , XXXXXXX , \
     KC_TAB  , XXXXXXX , XXXXXXX , XXXXXXX , KC_LLOW , KC_SPC  ,    XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX   \
// `---------+---------+---------+---------+---------+---------/  `---------+---------+---------+---------+---------+---------/
),
[_ADJUST] =  LAYOUT_ortho_4x12( \
// ,---------+---------+---------+---------+---------+---------.  ,---------+---------+---------+---------+---------+---------.
     RESET   , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , KC_RTOG ,    KC_RHUI , KC_RSAI , KC_RVAI , RGB_RST , _______ , _______ , \
     KC_L1   , KC_L2   , XXXXXXX , XXXXXXX , XXXXXXX , KC_RMOD ,    KC_RHUD , KC_RSAD , KC_RVAD , TAP_ANM , _______ , _______ , \
     _______ , KC_TERR , XXXXXXX , XXXXXXX , XXXXXXX , KC_RRMD ,    KC_MUTE , KC_VOLU , KC_VOLD , XXXXXXX , XXXXXXX , _______ , \
     _______ , _______ , _______ , _______ , _______ , _______ ,    _______ , _______ , _______ , _______ , _______ , _______   \
// `---------+---------+---------+---------+---------+---------/  `---------+---------+---------+---------+---------+---------/
)

};

/*
// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void set_rgb_mode_adjust(void) {
  rgblight_setrgb(255, 0, 255);
}

void set_rgb_mode_lower(void) {
  if (!rgblight_config.enable) {
    return;
  }
  rgblight_timer_disable();
  if (IS_LAYER_ON(_RAISE)) {
    set_rgb_mode_adjust();
    return;
  }
  rgblight_setrgb(255, 32, 0);
}

void set_rgb_mode_raise(void) {
  if (!rgblight_config.enable) {
    return;
  }
  rgblight_timer_disable();
  if (IS_LAYER_ON(_LOWER)) {
    set_rgb_mode_adjust();
    return;
  }
  rgblight_setrgb(0, 32, 255);
}

void set_rgb_mode_default(void) {
  if (IS_LAYER_ON(_LOWER)) {
    set_rgb_mode_lower();
    return;
  } else if (IS_LAYER_ON(_RAISE)) {
    set_rgb_mode_raise();
    return;
  } else if (IS_LAYER_ON(_FUNC) || IS_LAYER_ON(_ADJUST)) {
    return;
  }
  rgblight_timer_enable();
}

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}
*/

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

bool isTapAnimation = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  /*
  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_QWERTY);
      }
      return false;
      break;
    case HIDEN:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_HIDEN);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        set_rgb_mode_lower();
      } else {
        layer_off(_LOWER);
        set_rgb_mode_default();
      }
      update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        set_rgb_mode_raise();
      } else {
        layer_off(_RAISE);
        set_rgb_mode_default();
      }
      update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      return false;
      break;
    case FUNC:
      if (record->event.pressed) {
        layer_on(_FUNC);
      } else {
        layer_off(_FUNC);
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
    case RGB_RST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
        }
      #endif
      break;
    case TAP_ANM:
      if (record->event.pressed) {
        isTapAnimation = !isTapAnimation;
      }
      break;
  }
  */
  switch (keycode) {
    case RGB_RST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
        }
      #endif
      break;
    case TAP_ANM:
      if (record->event.pressed) {
        isTapAnimation = !isTapAnimation;
      }
      break;
    case ONESHOT_CLEAR: set_oneshot_clear(); break;
    case ONESHOT_SHIFT: set_oneshot_shift(); break;
    case ONESHOT_CTRL:  set_oneshot_ctrl(); break;
    case ONESHOT_ALT:   set_oneshot_alt(); break;
    case ONESHOT_GUI:   set_oneshot_gui(); break;
  }

  if (isTapAnimation) {
    rgblight_mode_noeeprom(1);
    uint16_t hue = (rgblight_config.hue + 5) % 360;
    rgblight_sethsv_noeeprom(hue, rgblight_config.sat, rgblight_config.val);
  }

  return true;
}


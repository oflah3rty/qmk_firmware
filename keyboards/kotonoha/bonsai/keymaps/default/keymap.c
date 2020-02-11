#include QMK_KEYBOARD_H
#include "bootloader.h"
#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.

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
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
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

#define KC_LCMM LT(_LOWER, KC_COMM)
#define KC_LDOT LT(_RAISE, KC_DOT)
#define KC_LX   LT(_SUPPORT, KC_X)
#define KC_LZ   LT(_ADJUST, KC_Z)
#define KC_LLT  LT(_ADJUST, KC_T)
#define KC_LLOW MO(_LOWER)
#define KC_LRAI MO(_RAISE)
#define KC_MENT LSFT_T(KC_ENT)
#define KC_MSPC LCTL_T(KC_SPC)

#define KC_1CLR ONESHOT_CLEAR
#define KC_1SFT ONESHOT_SHIFT
#define KC_1CTL ONESHOT_CTRL
#define KC_1ALT ONESHOT_ALT
#define KC_1GUI ONESHOT_GUI

#define KC_JPN  LALT(KC_GRV)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT( /* Base */
//       '--------+--------+--------+--------+--------+  '-------+--------+--------+--------+--------'
           KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,   KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , \
  KC_V   , KC_A   , KC_S   , KC_D   , KC_F   , KC_G   ,   KC_H   , KC_J   , KC_K   , KC_L   , KC_N   , KC_B   , \
           KC_LZ  ,          KC_C   ,                                       KC_M   ,          KC_LX  , \
                                      KC_LLOW, KC_MSPC,   KC_MENT, KC_LRAI                    \
//                                  '--------+--------+  --------+--------'
  ),
  [_CUSTOM] = LAYOUT(
//       '--------+--------+--------+--------+--------+  '-------+--------+--------+--------+--------'
           KC_Q   , KC_W   , KC_F   , KC_P   , KC_G   ,   KC_J   , KC_L   , KC_U   , KC_Y   , KC_LX  , \
  KC_V   , KC_A   , KC_R   , KC_S   , KC_T   , KC_D   ,   KC_H   , KC_N   , KC_E   , KC_I   , KC_O   , KC_B   , \
           KC_LZ  ,          KC_C   ,                                       KC_M   ,          KC_K   , \
                                      _______, _______,   _______, _______                    \
//                                  '--------+--------+  --------+--------'
  ),
  [_LOWER] = LAYOUT(
//       '--------+--------+--------+--------+--------+  '-------+--------+--------+--------+--------'
           KC_6   , KC_7   , KC_8   , KC_9   , KC_0   ,   KC_MINS, KC_BSLS, KC_COMM, KC_DOT , KC_SLSH, \
  KC_LBRC, KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,   KC_GRV , KC_QUOT, XXXXXXX, KC_SCLN, KC_SCLN, KC_RBRC, \
           XXXXXXX,          KC_1GUI,                                       KC_1ALT,          KC_EQL , \
                                      _______, _______,   _______, _______                    \
//                                  '--------+--------+  --------+--------'
  ),
  [_RAISE] = LAYOUT(
//       '--------+--------+--------+--------+--------+  '-------+--------+--------+--------+--------'
           KC_PGUP, KC_HOME, KC_UP  , KC_END , KC_F1  ,   KC_F2  , KC_F3  , KC_F4  , KC_F5  , KC_F6  , \
  KC_APP , KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_F7  ,   KC_F8  , KC_F9  , KC_F10 , KC_F11 , KC_F12 , KC_DEL , \
           XXXXXXX,          KC_PSCR,                                       KC_1CLR,          XXXXXXX, \
                                      _______, _______,   _______, _______                    \
//                                  '--------+--------+  --------+--------'
  ),
  [_SUPPORT] = LAYOUT(
//       '--------+--------+--------+--------+--------+  '-------+--------+--------+--------+--------'
           KC_ESC , XXXXXXX, KC_HENK, KC_MHEN, XXXXXXX,   KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, _______, \
  KC_TAB , XXXXXXX, XXXXXXX, KC_BSPC, KC_SPC , XXXXXXX,   XXXXXXX, KC_JPN , KC_LCTL, KC_LSFT, XXXXXXX, KC_BSPC, \
           _______,          XXXXXXX,                                       XXXXXXX,          XXXXXXX, \
                                      _______, _______,   _______, _______                    \
//                                  '--------+--------+  --------+--------'
  ),
  [_ADJUST] = LAYOUT(
//       '--------+--------+--------+--------+--------+  '-------+--------+--------+--------+--------'
           RESET  , XXXXXXX, XXXXXXX, XXXXXXX, RGB_TOG,   RGB_HUI, RGB_SAI, RGB_VAI, RGBRST , XXXXXXX, \
  KC_L1  , KC_L2  , XXXXXXX, XXXXXXX,RGB_MOD ,RGB_RMOD,   RGB_HUD, RGB_SAD, RGB_VAD, XXXXXXX, XXXXXXX, XXXXXXX, \
           _______,          XXXXXXX,                                       XXXXXXX,          XXXXXXX, \
                                      XXXXXXX, XXXXXXX,   XXXXXXX, XXXXXXX                    \
//                                  '--------+--------+  --------+--------'
  )
};

int RGB_current_mode;

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
    //SSD1306 OLED init, make sure to add #define SSD1306OLED in config.h
    #ifdef SSD1306OLED
        iota_gfx_init(!has_usb());   // turns on the display
    #endif
}

//SSD1306 OLED update loop, make sure to add #define SSD1306OLED in config.h
#ifdef SSD1306OLED

// When add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void matrix_scan_user(void) {
   iota_gfx_task();
}

void matrix_render_user(struct CharacterMatrix *matrix) {
  if (is_master) {
    // If you want to change the display of OLED, you need to change here
    matrix_write_ln(matrix, read_layer_state());
    matrix_write_ln(matrix, read_keylog());
    matrix_write_ln(matrix, read_keylogs());
    //matrix_write_ln(matrix, read_mode_icon(keymap_config.swap_lalt_lgui));
    //matrix_write_ln(matrix, read_host_led_state());
    //matrix_write_ln(matrix, read_timelog());
  } else {
    matrix_write(matrix, read_logo());
  }
}

void matrix_update(struct CharacterMatrix *dest, const struct CharacterMatrix *source) {
  if (memcmp(dest->display, source->display, sizeof(dest->display))) {
    memcpy(dest->display, source->display, sizeof(dest->display));
    dest->dirty = true;
  }
}

void iota_gfx_task_user(void) {
  struct CharacterMatrix matrix;
  matrix_clear(&matrix);
  matrix_render_user(&matrix);
  matrix_update(&display, &matrix);
}
#endif//SSD1306OLED

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
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
  /*
    case BASE:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL<<_BASE);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
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
*/
    case RGB_MOD:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          rgblight_mode(RGB_current_mode);
          rgblight_step();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      return false;
      break;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      break;
    case ONESHOT_CLEAR: set_oneshot_clear(); break;
    case ONESHOT_SHIFT: set_oneshot_shift(); break;
    case ONESHOT_CTRL:  set_oneshot_ctrl(); break;
    case ONESHOT_ALT:   set_oneshot_alt(); break;
    case ONESHOT_GUI:   set_oneshot_gui(); break;
  }
  return true;
}

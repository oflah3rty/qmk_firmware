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

#define _BASE 0
#define _LOWER 1
#define _RAISE 2
#define _EXTEND 3
#define _FUNC 4
#define _MOUSE 5
#define _ADJUST 6

enum custom_keycodes {
  BASE = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  BACKLIT,
  RGBRST
};

enum macro_keycodes {
  KC_SAMPLEMACRO,
};

#define _______ KC_TRNS

#define KC_CSPC LCTL_T(KC_SPACE)
#define KC_SENT LSFT_T(KC_ENTER)
#define KC_VGUI GUI_T(KC_V)
#define KC_MGUI GUI_T(KC_M)
#define KC_BALT LALT_T(KC_B)
#define KC_CALT LALT_T(KC_C)
#define KC_ZADJ LT(_ADJUST, KC_Z)
#define KC_XADJ LT(_ADJUST, KC_X)

#define KC_DFNC LT(_FUNC, KC_D)
#define KC_GMOU LT(_MOUSE, KC_G)
#define KC_FEXT LT(_EXTEND, KC_F)

#define KC_RST  RESET
#define KC_LOW  LT(_LOWER, KC_ESC)
#define KC_RAI  LT(_RAISE, KC_BSPC)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT( /* Base */
//'--------+--------+--------+--------+--------+--------+  '-------+--------+--------+--------+--------+--------'
    KC_VGUI, KC_Q   , KC_W   , KC_E   , KC_R   , KC_T   ,   KC_Y   , KC_U   , KC_I   , KC_O   , KC_P   , KC_MGUI, \
    KC_CALT, KC_A   , KC_S   , KC_DFNC, KC_FEXT, KC_GMOU,   KC_H   , KC_J   , KC_K   , KC_L   , KC_N   , KC_BALT, \
                               KC_ZADJ, KC_LOW , KC_CSPC,   KC_SENT, KC_RAI , KC_XADJ                             \
//                           '--------'--------+--------+  --------+--------'--------'
  ),
  [_LOWER] = LAYOUT(
//'--------+--------+--------+--------+--------+--------+  '-------+--------+--------+--------+--------+--------'
    KC_LABK, KC_TILD, KC_BSLS, _______, _______, KC_TAB ,   KC_QUOT, KC_DQT , KC_UNDS, KC_PIPE, KC_COLN, KC_QUES, \
    KC_RABK, KC_GRV , KC_EQL , KC_PLUS, KC_MINS, KC_APP ,   KC_LBRC, KC_RBRC, KC_LCBR, KC_RCBR, KC_SCLN, KC_QUES, \
                               _______, _______, _______,   _______, _______, _______                             \
//                           '--------'--------+--------+  --------+--------'--------'
  ),
  [_RAISE] = LAYOUT(
//'--------+--------+--------+--------+--------+--------+  '-------+--------+--------+--------+--------+--------'
    KC_COMM, KC_EXLM, KC_AT  , KC_HASH, KC_DLR , KC_PERC,   KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_SLSH, \
    KC_DOT , KC_1   , KC_2   , KC_3   , KC_4   , KC_5   ,   KC_6   , KC_7   , KC_8   , KC_9   , KC_0   , KC_SLSH, \
                               _______, _______, _______,   _______, _______, _______                             \
//                           '--------'--------+--------+  --------+--------'--------'
  ),
  [_EXTEND] = LAYOUT(
//'--------+--------+--------+--------+--------+--------+  '-------+--------+--------+--------+--------+--------'
    _______, _______, _______, KC_ESC , _______, _______,   KC_COLN, KC_SCLN, KC_LABK, KC_RABK, KC_QUES, _______, \
    _______, _______, _______, KC_BSPC, _______, _______,   KC_ENT , KC_SPC , KC_COMM, KC_DOT , KC_SLSH, _______, \
                               _______, _______, _______,   _______, _______, _______                             \
//                           '--------'--------+--------+  --------+--------'--------'
  ),
  [_FUNC] = LAYOUT(
//'--------+--------+--------+--------+--------+--------+  '-------+--------+--------+--------+--------+--------'
    KC_HOME, KC_F1  , KC_F2  , KC_F3  , KC_F4  , KC_F5  ,   KC_F6  , KC_F7  , KC_F8  , KC_F9  , KC_F10 , _______, \
    KC_END , KC_F11 , KC_F12 , _______, KC_PGUP, KC_PGDN,   KC_LEFT, KC_DOWN, KC_UP  , KC_RGHT, KC_PSCR, _______, \
                               _______, _______, _______,   _______, _______, _______                             \
//                           '--------'--------+--------+  --------+--------'--------'
  ),
  [_MOUSE] = LAYOUT(
//'--------+--------+--------+--------+--------+--------+  '-------+--------+--------+--------+--------+--------'
    KC_WH_U, _______, _______, KC_ESC , _______, _______,   KC_BTN1, KC_BTN2, KC_BTN3, KC_BTN4, KC_BTN5, KC_WH_L, \
    KC_WH_D, _______, _______, KC_BSPC, _______, _______,   KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, _______, KC_WH_R, \
                               _______, _______, _______,   _______, _______, _______                             \
//                           '--------'--------+--------+  --------+--------'--------'
  ),
  [_ADJUST] = LAYOUT(
//'--------+--------+--------+--------+--------+--------+  '-------+--------+--------+--------+--------+--------'
    _______, KC_RST , KC_LCTL, KC_LALT, KC_DEL , RGB_TOG,   RGB_HUI, RGB_SAI, RGB_VAI, RGBRST , KC_RST , _______, \
    _______, _______, _______, _______,RGB_MOD ,RGB_RMOD,   RGB_HUD, RGB_SAD, RGB_VAD, RGB_TOG, _______, _______, \
                               _______, _______, _______,   _______, _______, _______                             \
//                           '--------'--------+--------+  --------+--------'--------'
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef SSD1306OLED
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }

  switch (keycode) {
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
  }
  return true;
}

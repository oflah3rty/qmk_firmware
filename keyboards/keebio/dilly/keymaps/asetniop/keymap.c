#include QMK_KEYBOARD_H
#include "keytable.h"

extern rgblight_config_t rgblight_config;
extern keymap_config_t keymap_config;

#define _BASE 0

#define _______ KC_TRNS

// Tap-Hold keys
#define KC_RST RESET

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT_ortho_3x10(
  //,-------+-------+-------+-------+-------+  -------+-------+-------+-------+-------.
     BIT8   ,BIT7   ,BIT6   ,BIT5   ,XXXXXXX,  XXXXXXX,BIT4   ,BIT3   ,BIT2   ,BIT1   ,
     XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,  XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,
     XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,KC_RST ,  XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX,XXXXXXX
  //`-------+-------+-------+-------+-------+  -------+-------+-------+-------+-------'
  )
};

// LED 初期化
void led_init(void) {
#ifdef RGBLIGHT_ENABLE
  rgblight_setrgb_at(  0,   0,   0, 0);
  rgblight_setrgb_at(  0,   0,   0, 1);
  rgblight_setrgb_at(  0,   0,   0, 2);
#endif
}

// 入力に対する LED アクション
uint16_t hue = 0;
bool isFirstBoot = true;
void input_action_led(keyrecord_t *record) {
  if (isFirstBoot) {
    isFirstBoot = false;
    led_init();
  }
  if (record->event.pressed) {
    return;
  }
  hue = (hue + 5) % 360;
  rgblight_sethsv(hue, rgblight_config.sat, rgblight_config.val);
  // 下はとりあえず GUI のワンショット状態のインジケーターに使用する
  if (isGuiOneshot) {
    return;
  }
  //rgblight_sethsv_at(hue, rgblight_config.sat, rgblight_config.val, 0);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  input_action_led(record);

  switch (keycode) {
    case BIT1: update_code_by(KEYBIT1, record); break;
    case BIT2: update_code_by(KEYBIT2, record); break;
    case BIT3: update_code_by(KEYBIT3, record); break;
    case BIT4: update_code_by(KEYBIT4, record); break;
    case BIT5: update_code_by(KEYBIT5, record); break;
    case BIT6: update_code_by(KEYBIT6, record); break;
    case BIT7: update_code_by(KEYBIT7, record); break;
    case BIT8: update_code_by(KEYBIT8, record); break;
    default:
      break;
  }
  return true;
}

void matrix_init_user(void) {
/*
  debug_enable = true;
  debug_matrix = true;
  debug_mouse  = true;
*/
}

void led_set_user(uint8_t usb_led) {
  led_init();
}

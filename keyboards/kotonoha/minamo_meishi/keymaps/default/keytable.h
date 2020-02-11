#ifndef KEYTABLE_H
#define KEYTABLE_H
#include QMK_KEYBOARD_H

#define KEYBIT1 (1<<0)
#define KEYBIT2 (1<<1)
#define KEYBIT3 (1<<2)
#define KEYBIT4 (1<<3)
#define KEYBIT5 (1<<4)
#define KEYBIT6 (1<<5)
#define KEYBIT7 (1<<6)
#define KEYBIT8 (1<<7)
#define KEYBIT9 (1<<8)

// モディファイアフラグ
// 必要に応じて拡張する
typedef enum _modifier_flag {
  None  = 0,
  Shift = 1,
  Ctrl  = 2,
  Alt   = 4,
  Gui   = 8
} KeyModifier;

// 独自のキーコード
enum custom_keycodes {
  BIT1 = SAFE_RANGE,
  BIT2, BIT3, BIT4, BIT5,
  BIT6, BIT7, BIT8, BIT9,

  // 機能キー
  BOOST,
  PAIR_BRACKETS,
  PAIR_BRACE,
  PAIR_ANGLE_BRACKETS,
  PAIR_PARENTHESIS,

  // モディファイアキー
  ONESHOT_SHIFT,
  ONESHOT_CTRL,
  ONESHOT_ALT,
  ONESHOT_GUI,
  ONESHOT_CLEAR,
  CAPSKEEP,

  // メンテキー
  KEYBOARDRESET,
  RGBRST,
  RGBTOG,
  //DEBUG_MODE,
};

// カスタムキーコード管理構造体
typedef struct _custom {
  uint16_t    key_code;      // キーコード
  KeyModifier modifier_flag; // 一緒に押したい修飾キー
} CustomKeyCode;

// キーテーブル
extern const CustomKeyCode keycode_table[];

// GUI キーのワンショット状態の保持
extern bool isGuiOneshot;

// 各 bit の 押下/離し 時の更新処理
extern void update_code_by(uint16_t bit, keyrecord_t *record);

#endif

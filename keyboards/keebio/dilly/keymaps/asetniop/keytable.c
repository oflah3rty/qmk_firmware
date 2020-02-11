#include QMK_KEYBOARD_H
#include "keytable.h"

// 最後に入力したキーコード
uint16_t last_keycode = 0;

// 最後に入力したキーが Shift を含むか
bool last_shift = false;

// 現在の bit の組み合わせ
uint16_t code = 0;

// Capslock 状態の保持
bool isCapslock = false;

// GUI キーのワンショット状態の保持
bool isGuiOneshot = false;

// 組み合わせの押下が終わった後の最初の取り出しか
// ※ 複数キーを押した後、離す度にキーが入力されないために必要
bool isPicked = false;

// モード
uint8_t mode_index = 0;

// 独自キー
// -----------------------------------------------------------------------------
// ブースト機能 (最後のコードを繰り返して入力する)
void exec_boost(void) {
  for (uint8_t count = 0; count < 5; count ++) {
    if (last_shift) register_code(KC_LSFT);
    register_code(last_keycode);
    unregister_code(last_keycode);
    if (last_shift) unregister_code(KC_LSFT);
  }
}

// ブラケットペア入力
void input_pair_brackets(void) {
    register_code(KC_LBRC);
    unregister_code(KC_LBRC);
    register_code(KC_RBRC);
    unregister_code(KC_RBRC);
}

// ブレースペア入力
void input_pair_brace(void) {
    register_code(KC_LSFT);
    register_code(KC_LBRC);
    unregister_code(KC_LBRC);
    register_code(KC_RBRC);
    unregister_code(KC_RBRC);
    unregister_code(KC_LSFT);
}

// アングルブラケットペア入力
// ※ 単品が欲しい人は Shift + dot や Shift + comma で代用
void input_pair_angle_brackets(void) {
    register_code(KC_LSFT);
    register_code(KC_COMM);
    unregister_code(KC_COMM);
    register_code(KC_DOT);
    unregister_code(KC_DOT);
    unregister_code(KC_LSFT);
}

// パーレンペア入力
// ※ 単品が欲しい人は Shift + 9 や Shift + 0 で代用
void input_pair_parenthesis(void) {
    register_code(KC_LSFT);
    register_code(KC_9);
    unregister_code(KC_9);
    register_code(KC_0);
    unregister_code(KC_0);
    unregister_code(KC_LSFT);
}

/**
// デバッグモード
void exec_debug_mode(void) {
    register_code(KC_LSFT);
    register_code(KC_RSFT);
    register_code(KC_D);
    unregister_code(KC_D);
    unregister_code(KC_RSFT);
    unregister_code(KC_LSFT);
}
*/

// LED 関連
// -----------------------------------------------------------------------------
// LED のリセット
void reset_led(void) {
#ifdef RGBLIGHT_ENABLE
  eeconfig_update_rgblight_default();
  rgblight_enable();
#endif
}

void led_modifier(void) {
#ifdef RGBLIGHT_ENABLE
  if (isCapslock) {
      //rgblight_setrgb_at(255,  64,   0, 2);
      return;
  }

  uint8_t led_index = 0;
  uint8_t modkeys = get_oneshot_mods();
  if (modkeys & MOD_LSFT) led_index += 1;
  if (modkeys & MOD_LCTL) led_index += 2;
  if (modkeys & MOD_LALT) led_index += 4;
  isGuiOneshot = modkeys & MOD_LGUI;
  if (isGuiOneshot) {
    //rgblight_setrgb_at(255, 255, 255, 0);
  }
  switch(led_index) {
    case 1: rgblight_setrgb_at(  0,   0, 255, 2); break;
    case 2: rgblight_setrgb_at(  0, 255,   0, 2); break;
    case 3: rgblight_setrgb_at(  0, 255, 255, 2); break;
    case 4: rgblight_setrgb_at(255,   0,   0, 2); break;
    case 5: rgblight_setrgb_at(255,   0, 255, 2); break;
    case 6: rgblight_setrgb_at(255, 255,   0, 2); break;
    case 7: rgblight_setrgb_at(255, 255, 255, 2); break;
    default:
      //rgblight_setrgb_at(  0,   0,   0, 2);
      break;
  }

#endif
}

// モディファイア 関連
// -----------------------------------------------------------------------------
// Capslock の設定
void set_capslock(void) {
  register_code(KC_CAPS);
  unregister_code(KC_CAPS);
  isCapslock = !isCapslock;
}

// ワンショットモディファイアの追加
// ※ 各モディファイアは合成、保持される
void append_onshot_modifier(uint8_t newkey) {
  uint8_t modkeys = get_oneshot_mods() | newkey;
  set_oneshot_mods(modkeys);
  led_modifier();
}
void set_oneshot_shift(void) { append_onshot_modifier(MOD_LSFT); }
void set_oneshot_ctrl(void)  { append_onshot_modifier(MOD_LCTL); }
void set_oneshot_alt(void)   { append_onshot_modifier(MOD_LALT); }
void set_oneshot_gui(void)   { append_onshot_modifier(MOD_LGUI); }
void set_oneshot_clear(void) {
  clear_oneshot_mods();
  led_modifier();
}

// 以下、本キーボードの心臓部
// -----------------------------------------------------------------------------
// コードから該当するキーを取り出す
void pickup_key(void) {
  if(isPicked) {
    return;
  }
  isPicked = true;

  code = code & 0b0000000111111111; // ゴミ防止に一応マスク
  CustomKeyCode picked = keycode_table[code];
  uint16_t picked_code = 0;
  if (mode_index == ALPHA_MODE) {
    picked_code = picked.key_code;
  } else if(mode_index == NUMBER_MODE) {
    picked_code = picked.number_code;
  } else {
    picked_code = picked.key_code;
  }
  bool isShifted = (get_oneshot_mods() & MOD_LSFT) || (picked.modifier_flag & Shift);
  bool isCtrl = (picked.modifier_flag & Ctrl);
  bool isGui = (picked.modifier_flag & Gui);

  switch(picked_code) {
    case MODE_ALPHA: mode_index = ALPHA_MODE; return;
    case MODE_NUMBER: mode_index = NUMBER_MODE; return;
    case BOOST:         exec_boost(); return;
    case PAIR_BRACKETS:       input_pair_brackets(); break;
    case PAIR_BRACE:          input_pair_brace(); break;
    case PAIR_ANGLE_BRACKETS: input_pair_angle_brackets(); break;
    case PAIR_PARENTHESIS:    input_pair_parenthesis(); break;
    case KEYBOARDRESET: reset_keyboard(); return;
    case ONESHOT_SHIFT: set_oneshot_shift(); return;
    case ONESHOT_CTRL:  set_oneshot_ctrl(); return;
    case ONESHOT_ALT:   set_oneshot_alt(); return;
    case ONESHOT_GUI:   set_oneshot_gui(); return;
    case ONESHOT_CLEAR: set_oneshot_clear(); return;
    case CAPSKEEP:      set_capslock(); return;
    case RGBRST:        reset_led(); return;
    // case DEBUG_MODE: exec_debug_mode(); return;
  }
  last_keycode = picked_code;
  last_shift = isShifted;
  if (isShifted) register_code(KC_LSFT);
  if (isCtrl)    register_code(KC_LCTL);
  if (isGui)     register_code(KC_LGUI);
  register_code(picked_code);
  unregister_code(picked_code);
  if (isShifted) unregister_code(KC_LSFT);
  if (isCtrl)    unregister_code(KC_LCTL);
  if (isGui)     unregister_code(KC_LGUI);
  led_modifier();
}

// 指定 bit でコードを更新する
void update_code_by(uint16_t bit, keyrecord_t *record) {
  if (record->event.pressed) {
    code = code | bit;
    isPicked = false;
    return;
  }
  pickup_key();
  code = code & ~bit;
}

// このキーボードのすべて
// * データ構造の詳細は .h ファイルを参照
// * 記号によっては Shift を付けないと送れないものもあるので注意
// * USB の制約で 6 キーまで同時押し可能だが、安全のため 6 キー以上は OUTとした
const CustomKeyCode keycode_table[] = {
  // 親指無し
  /*     0 ____ ____ */ {KC_NO              ,KC_NO               ,None},
  /*     1 ____ ___* */ {KC_P               ,KC_0                ,None},
  /*     2 ____ __*_ */ {KC_O               ,KC_9                ,None},
  /*     3 ____ __** */ {KC_SCLN            ,KC_NO               ,None},
  /*     4 ____ _*__ */ {KC_I               ,KC_8                ,None},
  /*     5 ____ _*_* */ {KC_EXLM            ,KC_NO               ,Shift},
  /*     6 ____ _**_ */ {KC_L               ,KC_NO               ,None},
  /*     7 ____ _*** */ {KC_SPC             ,KC_SPC              ,None},
  /*     8 ____ *___ */ {KC_N               ,KC_7                ,None},
  /*     9 ____ *__* */ {KC_M               ,KC_NO               ,None},
  /*    10 ____ *_*_ */ {KC_U               ,KC_NO               ,None},
  /*    11 ____ *_** */ {KC_ESC             ,KC_ESC              ,None},
  /*    12 ____ **__ */ {KC_H               ,KC_6                ,None},
  /*    13 ____ **_* */ {KC_NO              ,KC_NO               ,None},
  /*    14 ____ ***_ */ {KC_NO              ,KC_NO               ,None},
  /*    15 ____ **** */ {KC_ENT             ,KC_ENT              ,None},
  /*    16 ___* ____ */ {KC_T               ,KC_4                ,None},
  /*    17 ___* ___* */ {KC_BSPC            ,KC_BSPC             ,None},
  /*    18 ___* __*_ */ {KC_G               ,KC_RGHT             ,None},
  /*    19 ___* __** */ {KC_NO              ,KC_END              ,None},
  /*    20 ___* _*__ */ {KC_V               ,KC_DOWN             ,None},
  /*    21 ___* _*_* */ {KC_NO              ,KC_NO               ,None},
  /*    22 ___* _**_ */ {KC_NO              ,KC_UP               ,None},
  /*    23 ___* _*** */ {KC_NO              ,KC_PGDN             ,None},
  /*    24 ___* *___ */ {KC_B               ,KC_LEFT             ,None},
  /*    25 ___* *__* */ {MODE_NUMBER        ,MODE_ALPHA          ,None},
  /*    26 ___* *_*_ */ {KC_NO              ,KC_NO               ,None},
  /*    27 ___* *_** */ {KC_NO              ,KC_NO               ,None},
  /*    28 ___* **__ */ {KC_NO              ,KC_HOME             ,None},
  /*    29 ___* **_* */ {KC_NO              ,KC_NO               ,None},
  /*    30 ___* ***_ */ {KC_NO              ,KC_PGUP             ,None},
  /*    31 ___* **** */ {KC_NO              ,KC_NO               ,None},
  /*    32 __*_ ____ */ {KC_E               ,KC_3                ,None},
  /*    33 __*_ ___* */ {KC_QUOT            ,PAIR_PARENTHESIS    ,None},
  /*    34 __*_ __*_ */ {KC_MINS            ,PAIR_ANGLE_BRACKETS ,None},
  /*    35 __*_ __** */ {KC_NO              ,KC_RBRC             ,None},
  /*    36 __*_ _*__ */ {KC_COMM            ,PAIR_BRACE          ,None},
  /*    37 __*_ _*_* */ {KC_NO              ,KC_NO               ,None},
  /*    38 __*_ _**_ */ {KC_NO              ,KC_NO               ,None},
  /*    39 __*_ _*** */ {KC_NO              ,KC_NO               ,None},
  /*    40 __*_ *___ */ {KC_Y               ,PAIR_BRACKETS       ,None},
  /*    41 __*_ *__* */ {KC_NO              ,KC_NO               ,None},
  /*    42 __*_ *_*_ */ {KC_NO              ,KC_NO               ,None},
  /*    43 __*_ *_** */ {KC_NO              ,KC_NO               ,None},
  /*    44 __*_ **__ */ {KC_NO              ,KC_LBRC             ,None},
  /*    45 __*_ **_* */ {KC_NO              ,KC_NO               ,None},
  /*    46 __*_ ***_ */ {KC_NO              ,KC_NO               ,None},
  /*    47 __*_ **** */ {KC_NO              ,KC_NO               ,None},
  /*    48 __** ____ */ {KC_R               ,KC_5                ,None},
  /*    49 __** ___* */ {ONESHOT_ALT        ,ONESHOT_ALT         ,None},
  /*    50 __** __*_ */ {ONESHOT_CTRL       ,ONESHOT_CTRL        ,None},
  /*    51 __** __** */ {KC_NO              ,KC_NO               ,None},
  /*    52 __** _*__ */ {ONESHOT_SHIFT      ,ONESHOT_SHIFT       ,None},
  /*    53 __** _*_* */ {KC_NO              ,KC_NO               ,None},
  /*    54 __** _**_ */ {KC_NO              ,KC_NO               ,None},
  /*    55 __** _*** */ {ONESHOT_CLEAR      ,ONESHOT_CLEAR       ,None},
  /*    56 __** *___ */ {ONESHOT_GUI        ,ONESHOT_GUI         ,None},
  /*    57 __** *__* */ {KC_NO              ,KC_NO               ,None},
  /*    58 __** *_*_ */ {KC_NO              ,KC_NO               ,None},
  /*    59 __** *_** */ {KC_NO              ,KC_NO               ,None},
  /*    60 __** **__ */ {KC_NO              ,KC_NO               ,None},
  /*    61 __** **_* */ {KC_NO              ,KC_NO               ,None},
  /*    62 __** ***_ */ {KC_NO              ,KC_NO               ,None},
  /*    63 __** **** */ {KC_NO              ,KC_NO               ,None},
  /*    64 _*__ ____ */ {KC_S               ,KC_2                ,None},
  /*    65 _*__ ___* */ {KC_0               ,KC_NO               ,Shift},
  /*    66 _*__ __*_ */ {KC_DOT             ,KC_NO               ,None},
  /*    67 _*__ __** */ {KC_NO              ,KC_NO               ,None},
  /*    68 _*__ _*__ */ {KC_K               ,KC_NO               ,None},
  /*    69 _*__ _*_* */ {KC_NO              ,KC_NO               ,None},
  /*    70 _*__ _**_ */ {KC_NO              ,KC_NO               ,None},
  /*    71 _*__ _*** */ {KC_NO              ,KC_NO               ,None},
  /*    72 _*__ *___ */ {KC_J               ,KC_NO               ,None},
  /*    73 _*__ *__* */ {KC_NO              ,KC_NO               ,None},
  /*    74 _*__ *_*_ */ {KC_NO              ,KC_NO               ,None},
  /*    75 _*__ *_** */ {KC_NO              ,KC_NO               ,None},
  /*    76 _*__ **__ */ {KC_NO              ,KC_NO               ,None},
  /*    77 _*__ **_* */ {KC_NO              ,KC_NO               ,None},
  /*    78 _*__ ***_ */ {KC_NO              ,KC_NO               ,None},
  /*    79 _*__ **** */ {KC_NO              ,KC_NO               ,None},
  /*    80 _*_* ____ */ {KC_C               ,KC_NO               ,None},
  /*    81 _*_* ___* */ {PAIR_PARENTHESIS   ,PAIR_PARENTHESIS    ,None},
  /*    82 _*_* __*_ */ {PAIR_ANGLE_BRACKETS,PAIR_ANGLE_BRACKETS ,None},
  /*    83 _*_* __** */ {KC_RBRC            ,KC_RBRC             ,None},
  /*    84 _*_* _*__ */ {PAIR_BRACE         ,PAIR_BRACE          ,None},
  /*    85 _*_* _*_* */ {KC_NO              ,KC_NO               ,None},
  /*    86 _*_* _**_ */ {KC_NO              ,KC_NO               ,None},
  /*    87 _*_* _*** */ {KC_NO              ,KC_NO               ,None},
  /*    88 _*_* *___ */ {PAIR_BRACKETS      ,PAIR_BRACKETS       ,None},
  /*    89 _*_* *__* */ {KC_NO              ,KC_NO               ,None},
  /*    90 _*_* *_*_ */ {KC_NO              ,KC_NO               ,None},
  /*    91 _*_* *_** */ {KC_NO              ,KC_NO               ,None},
  /*    92 _*_* **__ */ {KC_LBRC            ,KC_LBRC             ,None},
  /*    93 _*_* **_* */ {KC_NO              ,KC_NO               ,None},
  /*    94 _*_* ***_ */ {KC_NO              ,KC_NO               ,None},
  /*    95 _*_* **** */ {KC_NO              ,KC_NO               ,None},
  /*    96 _**_ ____ */ {KC_D               ,KC_NO               ,None},
  /*    97 _**_ ___* */ {KC_NO              ,KC_NO               ,None},
  /*    98 _**_ __*_ */ {KC_RGHT            ,KC_NO               ,None},
  /*    99 _**_ __** */ {KC_END             ,KC_NO               ,None},
  /*   100 _**_ _*__ */ {KC_DOWN            ,KC_NO               ,None},
  /*   101 _**_ _*_* */ {KC_NO              ,KC_NO               ,None},
  /*   102 _**_ _**_ */ {KC_UP              ,KC_NO               ,None},
  /*   103 _**_ _*** */ {KC_NO              ,KC_NO               ,None},
  /*   104 _**_ *___ */ {KC_LEFT            ,KC_NO               ,None},
  /*   105 _**_ *__* */ {KC_NO              ,KC_NO               ,None},
  /*   106 _**_ *_*_ */ {KC_NO              ,KC_NO               ,None},
  /*   107 _**_ *_** */ {KC_NO              ,KC_NO               ,None},
  /*   108 _**_ **__ */ {KC_HOME            ,KC_NO               ,None},
  /*   109 _**_ **_* */ {KC_NO              ,KC_NO               ,None},
  /*   110 _**_ ***_ */ {KC_NO              ,KC_NO               ,None},
  /*   111 _**_ **** */ {KC_NO              ,KC_NO               ,None},
  /*   112 _*** ____ */ {BOOST              ,BOOST               ,None},
  /*   113 _*** ___* */ {KC_NO              ,KC_NO               ,None},
  /*   114 _*** __*_ */ {KC_NO              ,KC_NO               ,None},
  /*   115 _*** __** */ {KC_NO              ,KC_NO               ,None},
  /*   116 _*** _*__ */ {KC_NO              ,KC_NO               ,None},
  /*   117 _*** _*_* */ {KC_NO              ,KC_NO               ,None},
  /*   118 _*** _**_ */ {KC_NO              ,KC_NO               ,None},
  /*   119 _*** _*** */ {KC_NO              ,KC_NO               ,None},
  /*   120 _*** *___ */ {KC_NO              ,KC_NO               ,None},
  /*   121 _*** *__* */ {KC_NO              ,KC_NO               ,None},
  /*   122 _*** *_*_ */ {KC_NO              ,KC_NO               ,None},
  /*   123 _*** *_** */ {KC_NO              ,KC_NO               ,None},
  /*   124 _*** **__ */ {KC_NO              ,KC_NO               ,None},
  /*   125 _*** **_* */ {KC_NO              ,KC_NO               ,None},
  /*   126 _*** ***_ */ {KC_NO              ,KC_NO               ,None},
  /*   127 _*** **** */ {KC_NO              ,KC_NO               ,None},
  /*   128 *___ ____ */ {KC_A               ,KC_1                ,None},
  /*   129 *___ ___* */ {KC_SLSH            ,KC_NO               ,None},
  /*   130 *___ __*_ */ {KC_9               ,KC_NO               ,Shift},
  /*   131 *___ __** */ {KC_NO              ,KC_NO               ,None},
  /*   132 *___ _*__ */ {KC_Z               ,KC_NO               ,None},
  /*   133 *___ _*_* */ {KC_NO              ,KC_NO               ,None},
  /*   134 *___ _**_ */ {KC_NO              ,KC_NO               ,None},
  /*   135 *___ _*** */ {KC_NO              ,KC_NO               ,None},
  /*   136 *___ *___ */ {KC_Q               ,KC_NO               ,None},
  /*   137 *___ *__* */ {KC_NO              ,KC_NO               ,None},
  /*   138 *___ *_*_ */ {KC_NO              ,KC_NO               ,None},
  /*   139 *___ *_** */ {KC_NO              ,KC_NO               ,None},
  /*   140 *___ **__ */ {KC_NO              ,KC_NO               ,None},
  /*   141 *___ **_* */ {KC_NO              ,KC_NO               ,None},
  /*   142 *___ ***_ */ {KC_NO              ,KC_NO               ,None},
  /*   143 *___ **** */ {KC_NO              ,KC_NO               ,None},
  /*   144 *__* ____ */ {KC_F               ,KC_NO               ,None},
  /*   145 *__* ___* */ {KC_NO              ,KC_NO               ,None},
  /*   146 *__* __*_ */ {KC_NO              ,KC_NO               ,None},
  /*   147 *__* __** */ {KC_NO              ,KC_NO               ,None},
  /*   148 *__* _*__ */ {KC_NO              ,KC_NO               ,None},
  /*   149 *__* _*_* */ {KC_NO              ,KC_NO               ,None},
  /*   150 *__* _**_ */ {KC_NO              ,KC_NO               ,None},
  /*   151 *__* _*** */ {KC_NO              ,KC_NO               ,None},
  /*   152 *__* *___ */ {KC_NO              ,KC_NO               ,None},
  /*   153 *__* *__* */ {KC_NO              ,KC_NO               ,None},
  /*   154 *__* *_*_ */ {KC_NO              ,KC_NO               ,None},
  /*   155 *__* *_** */ {KC_NO              ,KC_NO               ,None},
  /*   156 *__* **__ */ {KC_NO              ,KC_NO               ,None},
  /*   157 *__* **_* */ {KC_NO              ,KC_NO               ,None},
  /*   158 *__* ***_ */ {KC_NO              ,KC_NO               ,None},
  /*   159 *__* **** */ {KC_NO              ,KC_NO               ,None},
  /*   160 *_*_ ____ */ {KC_X               ,KC_NO               ,None},
  /*   161 *_*_ ___* */ {KC_NO              ,KC_NO               ,None},
  /*   162 *_*_ __*_ */ {KC_NO              ,KC_NO               ,None},
  /*   163 *_*_ __** */ {KC_NO              ,KC_NO               ,None},
  /*   164 *_*_ _*__ */ {KC_NO              ,KC_NO               ,None},
  /*   165 *_*_ _*_* */ {KC_NO              ,KC_NO               ,None},
  /*   166 *_*_ _**_ */ {KC_NO              ,KC_NO               ,None},
  /*   167 *_*_ _*** */ {KC_NO              ,KC_NO               ,None},
  /*   168 *_*_ *___ */ {KC_NO              ,KC_NO               ,None},
  /*   169 *_*_ *__* */ {KC_NO              ,KC_NO               ,None},
  /*   170 *_*_ *_*_ */ {KC_NO              ,KC_NO               ,None},
  /*   171 *_*_ *_** */ {KC_NO              ,KC_NO               ,None},
  /*   172 *_*_ **__ */ {KC_NO              ,KC_NO               ,None},
  /*   173 *_*_ **_* */ {KC_NO              ,KC_NO               ,None},
  /*   174 *_*_ ***_ */ {KC_NO              ,KC_NO               ,None},
  /*   175 *_*_ **** */ {KC_NO              ,KC_NO               ,None},
  /*   176 *_** ____ */ {KC_NO              ,KC_NO               ,None},
  /*   177 *_** ___* */ {KC_NO              ,KC_NO               ,None},
  /*   178 *_** __*_ */ {KC_NO              ,KC_NO               ,None},
  /*   179 *_** __** */ {KC_NO              ,KC_NO               ,None},
  /*   180 *_** _*__ */ {KC_NO              ,KC_NO               ,None},
  /*   181 *_** _*_* */ {KC_NO              ,KC_NO               ,None},
  /*   182 *_** _**_ */ {KC_NO              ,KC_NO               ,None},
  /*   183 *_** _*** */ {KC_NO              ,KC_NO               ,None},
  /*   184 *_** *___ */ {KC_NO              ,KC_NO               ,None},
  /*   185 *_** *__* */ {KC_NO              ,KC_NO               ,None},
  /*   186 *_** *_*_ */ {KC_NO              ,KC_NO               ,None},
  /*   187 *_** *_** */ {KC_NO              ,KC_NO               ,None},
  /*   188 *_** **__ */ {KC_NO              ,KC_NO               ,None},
  /*   189 *_** **_* */ {KC_NO              ,KC_NO               ,None},
  /*   190 *_** ***_ */ {KC_NO              ,KC_NO               ,None},
  /*   191 *_** **** */ {KC_NO              ,KC_NO               ,None},
  /*   192 **__ ____ */ {KC_W               ,KC_NO               ,None},
  /*   193 **__ ___* */ {KC_NO              ,KC_NO               ,None},
  /*   194 **__ __*_ */ {KC_NO              ,KC_NO               ,None},
  /*   195 **__ __** */ {KEYBOARDRESET      ,KEYBOARDRESET       ,None},
  /*   196 **__ _*__ */ {KC_NO              ,KC_NO               ,None},
  /*   197 **__ _*_* */ {KC_NO              ,KC_NO               ,None},
  /*   198 **__ _**_ */ {KC_NO              ,KC_NO               ,None},
  /*   199 **__ _*** */ {KC_NO              ,KC_NO               ,None},
  /*   200 **__ *___ */ {KC_NO              ,KC_NO               ,None},
  /*   201 **__ *__* */ {KC_NO              ,KC_NO               ,None},
  /*   202 **__ *_*_ */ {KC_NO              ,KC_NO               ,None},
  /*   203 **__ *_** */ {KC_NO              ,KC_NO               ,None},
  /*   204 **__ **__ */ {RGBRST             ,RGBRST              ,None},
  /*   205 **__ **_* */ {KC_NO              ,KC_NO               ,None},
  /*   206 **__ ***_ */ {KC_NO              ,KC_NO               ,None},
  /*   207 **__ **** */ {KC_NO              ,KC_NO               ,None},
  /*   208 **_* ____ */ {KC_NO              ,KC_NO               ,None},
  /*   209 **_* ___* */ {KC_NO              ,KC_NO               ,None},
  /*   210 **_* __*_ */ {KC_NO              ,KC_NO               ,None},
  /*   211 **_* __** */ {KC_NO              ,KC_NO               ,None},
  /*   212 **_* _*__ */ {KC_NO              ,KC_NO               ,None},
  /*   213 **_* _*_* */ {KC_NO              ,KC_NO               ,None},
  /*   214 **_* _**_ */ {KC_NO              ,KC_NO               ,None},
  /*   215 **_* _*** */ {KC_NO              ,KC_NO               ,None},
  /*   216 **_* *___ */ {KC_NO              ,KC_NO               ,None},
  /*   217 **_* *__* */ {KC_NO              ,KC_NO               ,None},
  /*   218 **_* *_*_ */ {KC_NO              ,KC_NO               ,None},
  /*   219 **_* *_** */ {KC_NO              ,KC_NO               ,None},
  /*   220 **_* **__ */ {KC_NO              ,KC_NO               ,None},
  /*   221 **_* **_* */ {KC_NO              ,KC_NO               ,None},
  /*   222 **_* ***_ */ {KC_NO              ,KC_NO               ,None},
  /*   223 **_* **** */ {KC_NO              ,KC_NO               ,None},
  /*   224 ***_ ____ */ {KC_NO              ,KC_NO               ,None},
  /*   225 ***_ ___* */ {KC_NO              ,KC_NO               ,None},
  /*   226 ***_ __*_ */ {KC_NO              ,KC_NO               ,None},
  /*   227 ***_ __** */ {KC_NO              ,KC_NO               ,None},
  /*   228 ***_ _*__ */ {KC_NO              ,KC_NO               ,None},
  /*   229 ***_ _*_* */ {KC_NO              ,KC_NO               ,None},
  /*   230 ***_ _**_ */ {KC_NO              ,KC_NO               ,None},
  /*   231 ***_ _*** */ {KC_NO              ,KC_NO               ,None},
  /*   232 ***_ *___ */ {KC_NO              ,KC_NO               ,None},
  /*   233 ***_ *__* */ {KC_NO              ,KC_NO               ,None},
  /*   234 ***_ *_*_ */ {KC_NO              ,KC_NO               ,None},
  /*   235 ***_ *_** */ {KC_NO              ,KC_NO               ,None},
  /*   236 ***_ **__ */ {KC_NO              ,KC_NO               ,None},
  /*   237 ***_ **_* */ {KC_NO              ,KC_NO               ,None},
  /*   238 ***_ ***_ */ {KC_NO              ,KC_NO               ,None},
  /*   239 ***_ **** */ {KC_NO              ,KC_NO               ,None},
  /*   240 **** ____ */ {KC_TAB             ,KC_TAB              ,None},
  /*   241 **** ___* */ {KC_NO              ,KC_NO               ,None},
  /*   242 **** __*_ */ {KC_NO              ,KC_NO               ,None},
  /*   243 **** __** */ {KC_NO              ,KC_NO               ,None},
  /*   244 **** _*__ */ {KC_NO              ,KC_NO               ,None},
  /*   245 **** _*_* */ {KC_NO              ,KC_NO               ,None},
  /*   246 **** _**_ */ {KC_NO              ,KC_NO               ,None},
  /*   247 **** _*** */ {KC_NO              ,KC_NO               ,None},
  /*   248 **** *___ */ {KC_NO              ,KC_NO               ,None},
  /*   249 **** *__* */ {KC_NO              ,KC_NO               ,None},
  /*   250 **** *_*_ */ {KC_NO              ,KC_NO               ,None},
  /*   251 **** *_** */ {KC_NO              ,KC_NO               ,None},
  /*   252 **** **__ */ {KC_NO              ,KC_NO               ,None},
  /*   253 **** **_* */ {KC_NO              ,KC_NO               ,None},
  /*   254 **** ***_ */ {KC_NO              ,KC_NO               ,None},
  /*   255 **** **** */ {KC_NO              ,KC_NO               ,None},
};

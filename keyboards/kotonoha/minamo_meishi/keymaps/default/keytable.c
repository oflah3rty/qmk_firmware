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

void led_toggle(void) {
#ifdef RGBLIGHT_ENABLE
  rgblight_toggle();
#endif
}

void led_modifier(void) {
#ifdef RGBLIGHT_ENABLE
  if (isCapslock) {
      rgblight_setrgb_at(255,  64,   0, 2);
      return;
  }

  uint8_t led_index = 0;
  uint8_t modkeys = get_oneshot_mods();
  if (modkeys & MOD_LSFT) led_index += 1;
  if (modkeys & MOD_LCTL) led_index += 2;
  if (modkeys & MOD_LALT) led_index += 4;
  isGuiOneshot = modkeys & MOD_LGUI;
  if (isGuiOneshot) {
    rgblight_setrgb_at(255, 255, 255, 0);
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
      rgblight_setrgb_at(  0,   0,   0, 2);
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
  uint16_t picked_code = picked.key_code;
  bool isShifted = (get_oneshot_mods() & MOD_LSFT) || (picked.modifier_flag & Shift);
  bool isCtrl = (picked.modifier_flag & Ctrl);
  bool isGui = (picked.modifier_flag & Gui);

  switch(picked_code) {
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
    case RGBTOG:        led_toggle(); return;
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
const CustomKeyCode keycode_table[] = {
  // 親指無し
  /*   0 _ ____ ____ */ {KC_NO         ,None},
  /*   1 _ ____ ___* */ {KC_U          ,None},
  /*   2 _ ____ __*_ */ {KC_S          ,None},
  /*   3 _ ____ __** */ {KC_G          ,None},
  /*   4 _ ____ _*__ */ {KC_O          ,None},
  /*   5 _ ____ _*_* */ {KC_Q          ,None},
  /*   6 _ ____ _**_ */ {KC_N          ,None},
  /*   7 _ ____ _*** */ {KC_B          ,None},
  /*   8 _ ____ *___ */ {KC_E          ,None},
  /*   9 _ ____ *__* */ {KC_V          ,None},
  /*  10 _ ____ *_*_ */ {KC_T          ,None},
  /*  11 _ ____ *_** */ {KC_COMM       ,None},
  /*  12 _ ____ **__ */ {KC_A          ,None},
  /*  13 _ ____ **_* */ {KC_MINS       ,None},
  /*  14 _ ____ ***_ */ {KC_DOT        ,None},
  /*  15 _ ____ **** */ {KC_M          ,None},
  // 通常の親指位置
  /*  16 _ ___* ____ */ {KC_SPACE      ,None},
  /*  17 _ ___* ___* */ {KC_H          ,None},
  /*  18 _ ___* __*_ */ {KC_K          ,None},
  /*  19 _ ___* __** */ {KC_J          ,None},
  /*  20 _ ___* _*__ */ {KC_C          ,None},
  /*  21 _ ___* _*_* */ {KC_Z          ,None},
  /*  22 _ ___* _**_ */ {KC_Y          ,None},
  /*  23 _ ___* _*** */ {KC_X          ,None},
  /*  24 _ ___* *___ */ {KC_I          ,None},
  /*  25 _ ___* *__* */ {KC_L          ,None},
  /*  26 _ ___* *_*_ */ {KC_R          ,None},
  /*  27 _ ___* *_** */ {KC_W          ,None},
  /*  28 _ ___* **__ */ {KC_D          ,None},
  /*  29 _ ___* **_* */ {KC_QUOT       ,None},
  /*  30 _ ___* ***_ */ {KC_F          ,None},
  /*  31 _ ___* **** */ {KC_P          ,None},
  // １つ内側の親指
  /*  32 _ __*_ ____ */ {KC_BSPC       ,None},
  /*  33 _ __*_ ___* */ {KC_SLSH       ,None},
  /*  34 _ __*_ __*_ */ {KC_RGHT       ,None},
  /*  35 _ __*_ __** */ {KC_END        ,None},
  /*  36 _ __*_ _*__ */ {KC_UP         ,None},
  /*  37 _ __*_ _*_* */ {KC_NO         ,None},
  /*  38 _ __*_ _**_ */ {KC_COLN       ,Shift},
  /*  39 _ __*_ _*** */ {KC_PGDN       ,None},
  /*  40 _ __*_ *___ */ {KC_DOWN       ,None},
  /*  41 _ __*_ *__* */ {KC_SCLN       ,None},
  /*  42 _ __*_ *_*_ */ {KC_NO         ,None},
  /*  43 _ __*_ *_** */ {KC_NO         ,None},
  /*  44 _ __*_ **__ */ {KC_HOME       ,None},
  /*  45 _ __*_ **_* */ {KC_NO         ,None},
  /*  46 _ __*_ ***_ */ {KC_PGUP       ,None},
  /*  47 _ __*_ **** */ {KC_QUES       ,Shift},
  // 親指２個同時押し
  /*  48 _ __** ____ */ {KC_ESC        ,None},
  /*  49 _ __** ___* */ {KC_1          ,None},
  /*  50 _ __** __*_ */ {KC_2          ,None},
  /*  51 _ __** __** */ {KC_3          ,None},
  /*  52 _ __** _*__ */ {KC_4          ,None},
  /*  53 _ __** _*_* */ {KC_5          ,None},
  /*  54 _ __** _**_ */ {KC_6          ,None},
  /*  55 _ __** _*** */ {KC_7          ,None},
  /*  56 _ __** *___ */ {KC_8          ,None},
  /*  57 _ __** *__* */ {KC_9          ,None},
  /*  58 _ __** *_*_ */ {KC_0          ,None},
  /*  59 _ __** *_** */ {KC_EQL        ,None},
  /*  60 _ __** **__ */ {KC_PLUS       ,Shift},
  /*  61 _ __** **_* */ {KC_MINS       ,None},
  /*  62 _ __** ***_ */ {KC_SLSH       ,None},
  /*  63 _ __** **** */ {KC_ASTR       ,Shift},
  // 追加の人差し指キー
  /*  64 _ _*__ ____ */ {KC_ENT        ,None},
  /*  65 _ _*__ ___* */ {ONESHOT_ALT   ,None},
  /*  66 _ _*__ __*_ */ {ONESHOT_CTRL  ,None},
  /*  67 _ _*__ __** */ {KC_NO         ,None},
  /*  68 _ _*__ _*__ */ {ONESHOT_SHIFT ,None},
  /*  69 _ _*__ _*_* */ {KC_NO         ,None},
  /*  70 _ _*__ _**_ */ {KC_NO         ,None},
  /*  71 _ _*__ _*** */ {ONESHOT_CLEAR ,None},
  /*  72 _ _*__ *___ */ {ONESHOT_GUI   ,None},
  /*  73 _ _*__ *__* */ {KC_NO         ,None},
  /*  74 _ _*__ *_*_ */ {KC_NO         ,None},
  /*  75 _ _*__ *_** */ {KC_NO         ,None},
  /*  76 _ _*__ **__ */ {CAPSKEEP      ,None},
  /*  77 _ _*__ **_* */ {KC_NO         ,None},
  /*  78 _ _*__ ***_ */ {KC_TAB        ,None},
  /*  79 _ _*__ **** */ {KC_NO         ,None},
  // 基板端の上下同時押し
  /*  80 _ _*_* ____ */ {KC_LGUI             ,None},
  /*  81 _ _*_* ___* */ {PAIR_PARENTHESIS    ,None},
  /*  82 _ _*_* __*_ */ {PAIR_ANGLE_BRACKETS ,None},
  /*  83 _ _*_* __** */ {KC_RBRC             ,None},
  /*  84 _ _*_* _*__ */ {PAIR_BRACE          ,None},
  /*  85 _ _*_* _*_* */ {KC_NO               ,None},
  /*  86 _ _*_* _**_ */ {KC_NO               ,None},
  /*  87 _ _*_* _*** */ {KC_RBRC             ,Shift},
  /*  88 _ _*_* *___ */ {PAIR_BRACKETS       ,None},
  /*  89 _ _*_* *__* */ {KC_NO               ,None},
  /*  90 _ _*_* *_*_ */ {KC_NO               ,None},
  /*  91 _ _*_* *_** */ {KC_NO               ,None},
  /*  92 _ _*_* **__ */ {KC_LBRC             ,None},
  /*  93 _ _*_* **_* */ {KC_NO               ,None},
  /*  94 _ _*_* ***_ */ {KC_LBRC             ,Shift},
  /*  95 _ _*_* **** */ {KC_NO               ,None},
  // 親指内側と追加の人差し指同時押し
  /*  96 _ _**_ ____ */ {KC_LEFT       ,None},
  /*  97 _ _**_ ___* */ {KC_SCLN       ,None},
  /*  98 _ _**_ __*_ */ {KC_COLN       ,Shift},
  /*  99 _ _**_ __** */ {KC_PIPE       ,Shift},
  /* 100 _ _**_ _*__ */ {KC_BSLS       ,None},
  /* 101 _ _**_ _*_* */ {KC_NO         ,None},
  /* 102 _ _**_ _**_ */ {KC_NO         ,None},
  /* 103 _ _**_ _*** */ {KC_NO         ,None},
  /* 104 _ _**_ *___ */ {KC_GRV        ,None},
  /* 105 _ _**_ *__* */ {KC_NO         ,None},
  /* 106 _ _**_ *_*_ */ {KC_NO         ,None},
  /* 107 _ _**_ *_** */ {KC_NO         ,None},
  /* 108 _ _**_ **__ */ {KC_TILD       ,Shift},
  /* 109 _ _**_ **_* */ {KC_NO         ,None},
  /* 110 _ _**_ ***_ */ {KC_NO         ,None},
  /* 111 _ _**_ **** */ {KC_NO         ,None},
  // 親指２つと追加の人差し指の３キー同時
  /* 112 _ _*** ____ */ {KC_APP        ,None},
  /* 113 _ _*** ___* */ {KC_TAB        ,Ctrl},
  /* 114 _ _*** __*_ */ {KC_TAB        ,Ctrl | Shift},
  /* 115 _ _*** __** */ {KC_NO         ,None},
  /* 116 _ _*** _*__ */ {KC_NO         ,None},
  /* 117 _ _*** _*_* */ {KC_NO         ,None},
  /* 118 _ _*** _**_ */ {KC_NO         ,None},
  /* 119 _ _*** _*** */ {KC_NO         ,None},
  /* 120 _ _*** *___ */ {KC_NO         ,None},
  /* 121 _ _*** *__* */ {KC_NO         ,None},
  /* 122 _ _*** *_*_ */ {KC_NO         ,None},
  /* 123 _ _*** *_** */ {KC_NO         ,None},
  /* 124 _ _*** **__ */ {KC_NO         ,None},
  /* 125 _ _*** **_* */ {KC_NO         ,None},
  /* 126 _ _*** ***_ */ {KC_NO         ,None},
  /* 127 _ _*** **** */ {KC_NO         ,None},
  // 薬指下の親指キー
  /* 128 _ *___ ____ */ {KC_NO         ,None},
  /* 129 _ *___ ___* */ {KC_NO         ,None},
  /* 130 _ *___ __*_ */ {KC_NO         ,None},
  /* 131 _ *___ __** */ {KC_NO         ,None},
  /* 132 _ *___ _*__ */ {KC_NO         ,None},
  /* 133 _ *___ _*_* */ {KC_NO         ,None},
  /* 134 _ *___ _**_ */ {KC_NO         ,None},
  /* 135 _ *___ _*** */ {KC_NO         ,None},
  /* 136 _ *___ *___ */ {KC_NO         ,None},
  /* 137 _ *___ *__* */ {KC_NO         ,None},
  /* 138 _ *___ *_*_ */ {KC_NO         ,None},
  /* 139 _ *___ *_** */ {KC_NO         ,None},
  /* 140 _ *___ **__ */ {KC_NO         ,None},
  /* 141 _ *___ **_* */ {KC_NO         ,None},
  /* 142 _ *___ ***_ */ {KC_NO         ,None},
  /* 143 _ *___ **** */ {KC_NO         ,None},
  // 通常親指と薬指下親指の同時押し
  /* 144 _ *__* ____ */ {RGBRST        ,None},
  /* 145 _ *__* ___* */ {KC_NO         ,None},
  /* 146 _ *__* __*_ */ {KC_NO         ,None},
  /* 147 _ *__* __** */ {KC_NO         ,None},
  /* 148 _ *__* _*__ */ {KC_NO         ,None},
  /* 149 _ *__* _*_* */ {KC_NO         ,None},
  /* 150 _ *__* _**_ */ {KC_NO         ,None},
  /* 151 _ *__* _*** */ {KC_NO         ,None},
  /* 152 _ *__* *___ */ {KC_NO         ,None},
  /* 153 _ *__* *__* */ {KC_NO         ,None},
  /* 154 _ *__* *_*_ */ {KC_NO         ,None},
  /* 155 _ *__* *_** */ {KC_NO         ,None},
  /* 156 _ *__* **__ */ {KC_NO         ,None},
  /* 157 _ *__* **_* */ {KC_NO         ,None},
  /* 158 _ *__* ***_ */ {KC_NO         ,None},
  /* 159 _ *__* **** */ {KC_NO         ,None},
  // 親指内側と薬指下の同時押し
  /* 160 _ *_*_ ____ */ {KEYBOARDRESET ,None},
  /* 161 _ *_*_ ___* */ {KC_NO         ,None},
  /* 162 _ *_*_ __*_ */ {KC_NO         ,None},
  /* 163 _ *_*_ __** */ {KC_NO         ,None},
  /* 164 _ *_*_ _*__ */ {KC_NO         ,None},
  /* 165 _ *_*_ _*_* */ {KC_NO         ,None},
  /* 166 _ *_*_ _**_ */ {KC_NO         ,None},
  /* 167 _ *_*_ _*** */ {KC_NO         ,None},
  /* 168 _ *_*_ *___ */ {KC_NO         ,None},
  /* 169 _ *_*_ *__* */ {KC_NO         ,None},
  /* 170 _ *_*_ *_*_ */ {KC_NO         ,None},
  /* 171 _ *_*_ *_** */ {KC_NO         ,None},
  /* 172 _ *_*_ **__ */ {KC_NO         ,None},
  /* 173 _ *_*_ **_* */ {KC_NO         ,None},
  /* 174 _ *_*_ ***_ */ {KC_NO         ,None},
  /* 175 _ *_*_ **** */ {KC_NO         ,None},
  // 親指２種と薬指下の３キー同時
  /* 176 _ *_** ____ */ {KC_NO         ,None},
  /* 177 _ *_** ___* */ {KC_NO         ,None},
  /* 178 _ *_** __*_ */ {KC_NO         ,None},
  /* 179 _ *_** __** */ {KC_NO         ,None},
  /* 180 _ *_** _*__ */ {KC_NO         ,None},
  /* 181 _ *_** _*_* */ {KC_NO         ,None},
  /* 182 _ *_** _**_ */ {KC_NO         ,None},
  /* 183 _ *_** _*** */ {KC_NO         ,None},
  /* 184 _ *_** *___ */ {KC_NO         ,None},
  /* 185 _ *_** *__* */ {KC_NO         ,None},
  /* 186 _ *_** *_*_ */ {KC_NO         ,None},
  /* 187 _ *_** *_** */ {KC_NO         ,None},
  /* 188 _ *_** **__ */ {KC_NO         ,None},
  /* 189 _ *_** **_* */ {KC_NO         ,None},
  /* 190 _ *_** ***_ */ {KC_NO         ,None},
  /* 191 _ *_** **** */ {KC_NO         ,None},
  // 薬指下と追加の人差し指キー
  /* 192 _ **__ ____ */ {KC_NO         ,None},
  /* 193 _ **__ ___* */ {KC_NO         ,None},
  /* 194 _ **__ __*_ */ {KC_NO         ,None},
  /* 195 _ **__ __** */ {KC_NO         ,None},
  /* 196 _ **__ _*__ */ {KC_NO         ,None},
  /* 197 _ **__ _*_* */ {KC_NO         ,None},
  /* 198 _ **__ _**_ */ {KC_NO         ,None},
  /* 199 _ **__ _*** */ {KC_NO         ,None},
  /* 200 _ **__ *___ */ {KC_NO         ,None},
  /* 201 _ **__ *__* */ {KC_NO         ,None},
  /* 202 _ **__ *_*_ */ {KC_NO         ,None},
  /* 203 _ **__ *_** */ {KC_NO         ,None},
  /* 204 _ **__ **__ */ {KC_NO         ,None},
  /* 205 _ **__ **_* */ {KC_NO         ,None},
  /* 206 _ **__ ***_ */ {KC_NO         ,None},
  /* 207 _ **__ **** */ {KC_NO         ,None},
  // 通常親指、薬指下、追加人差し指の３キー同時押し
  /* 208 _ **_* ____ */ {KC_NO         ,None},
  /* 209 _ **_* ___* */ {KC_NO         ,None},
  /* 210 _ **_* __*_ */ {KC_NO         ,None},
  /* 211 _ **_* __** */ {KC_NO         ,None},
  /* 212 _ **_* _*__ */ {KC_NO         ,None},
  /* 213 _ **_* _*_* */ {KC_NO         ,None},
  /* 214 _ **_* _**_ */ {KC_NO         ,None},
  /* 215 _ **_* _*** */ {KC_NO         ,None},
  /* 216 _ **_* *___ */ {KC_NO         ,None},
  /* 217 _ **_* *__* */ {KC_NO         ,None},
  /* 218 _ **_* *_*_ */ {KC_NO         ,None},
  /* 219 _ **_* *_** */ {KC_NO         ,None},
  /* 220 _ **_* **__ */ {KC_NO         ,None},
  /* 221 _ **_* **_* */ {KC_NO         ,None},
  /* 222 _ **_* ***_ */ {KC_NO         ,None},
  /* 223 _ **_* **** */ {KC_NO         ,None},
  // 親指内側、薬指下、追加の人差し指の３キー同時
  /* 224 _ ***_ ____ */ {KC_NO         ,None},
  /* 225 _ ***_ ___* */ {KC_NO         ,None},
  /* 226 _ ***_ __*_ */ {KC_NO         ,None},
  /* 227 _ ***_ __** */ {KC_NO         ,None},
  /* 228 _ ***_ _*__ */ {KC_NO         ,None},
  /* 229 _ ***_ _*_* */ {KC_NO         ,None},
  /* 230 _ ***_ _**_ */ {KC_NO         ,None},
  /* 231 _ ***_ _*** */ {KC_NO         ,None},
  /* 232 _ ***_ *___ */ {KC_NO         ,None},
  /* 233 _ ***_ *__* */ {KC_NO         ,None},
  /* 234 _ ***_ *_*_ */ {KC_NO         ,None},
  /* 235 _ ***_ *_** */ {KC_NO         ,None},
  /* 236 _ ***_ **__ */ {KC_NO         ,None},
  /* 237 _ ***_ **_* */ {KC_NO         ,None},
  /* 238 _ ***_ ***_ */ {KC_NO         ,None},
  /* 239 _ ***_ **** */ {KC_NO         ,None},
  // 親指２種、薬指下、人差し指の４キー同時
  /* 240 _ **** ____ */ {KC_NO         ,None},
  /* 241 _ **** ___* */ {KC_NO         ,None},
  /* 242 _ **** __*_ */ {KC_NO         ,None},
  /* 243 _ **** __** */ {KC_NO         ,None},
  /* 244 _ **** _*__ */ {KC_NO         ,None},
  /* 245 _ **** _*_* */ {KC_NO         ,None},
  /* 246 _ **** _**_ */ {KC_NO         ,None},
  /* 247 _ **** _*** */ {KC_NO         ,None},
  /* 248 _ **** *___ */ {KC_NO         ,None},
  /* 249 _ **** *__* */ {KC_NO         ,None},
  /* 250 _ **** *_*_ */ {KC_NO         ,None},
  /* 251 _ **** *_** */ {KC_NO         ,None},
  /* 252 _ **** **__ */ {KC_NO         ,None},
  /* 253 _ **** **_* */ {KC_NO         ,None},
  /* 254 _ **** ***_ */ {KC_NO         ,None},
  /* 255 _ **** **** */ {KC_NO         ,None},
  // 小指付け根
  /* 256 * ____ ____ */ {KC_DEL        ,None},
  /* 257 * ____ ___* */ {KC_F1         ,None},
  /* 258 * ____ __*_ */ {KC_F2         ,None},
  /* 259 * ____ __** */ {KC_F3         ,None},
  /* 260 * ____ _*__ */ {KC_F4         ,None},
  /* 261 * ____ _*_* */ {KC_F5         ,None},
  /* 262 * ____ _**_ */ {KC_F6         ,None},
  /* 263 * ____ _*** */ {KC_F7         ,None},
  /* 264 * ____ *___ */ {KC_F8         ,None},
  /* 265 * ____ *__* */ {KC_F9         ,None},
  /* 266 * ____ *_*_ */ {KC_F10        ,None},
  /* 267 * ____ *_** */ {KC_F11        ,None},
  /* 268 * ____ **__ */ {KC_F12        ,None},
  /* 269 * ____ **_* */ {KC_NO         ,None},
  /* 270 * ____ ***_ */ {KC_NO         ,None},
  /* 271 * ____ **** */ {KC_NO         ,None},
  // 小指付け根と通常親指
  /* 272 * ___* ____ */ {BOOST         ,None},
  /* 273 * ___* ___* */ {KC_INS        ,None},
  /* 274 * ___* __*_ */ {KC_PSCR       ,None},
  /* 275 * ___* __** */ {KC_NO         ,None},
  /* 276 * ___* _*__ */ {KC_NO         ,None},
  /* 277 * ___* _*_* */ {KC_NO         ,None},
  /* 278 * ___* _**_ */ {KC_NO         ,None},
  /* 279 * ___* _*** */ {KC_NO         ,None},
  /* 280 * ___* *___ */ {KC_TAB        ,None},
  /* 281 * ___* *__* */ {KC_NO         ,None},
  /* 282 * ___* *_*_ */ {KC_NO         ,None},
  /* 283 * ___* *_** */ {KC_NO         ,None},
  /* 284 * ___* **__ */ {KC_NO         ,None},
  /* 285 * ___* **_* */ {KC_NO         ,None},
  /* 286 * ___* ***_ */ {KC_NO         ,None},
  /* 287 * ___* **** */ {KC_NO         ,None},
  // 小指付け根と親指内側
  /* 288 * __*_ ____ */ {KC_J          ,Gui},
  /* 289 * __*_ ___* */ {KC_ENT        ,Gui},
  /* 290 * __*_ __*_ */ {KC_P          ,Gui},
  /* 291 * __*_ __** */ {KC_ENT        ,Gui | Shift},
  /* 292 * __*_ _*__ */ {KC_NO         ,None},
  /* 293 * __*_ _*_* */ {KC_NO         ,None},
  /* 294 * __*_ _**_ */ {KC_NO         ,None},
  /* 295 * __*_ _*** */ {KC_NO         ,None},
  /* 296 * __*_ *___ */ {KC_SPC        ,Gui},
  /* 297 * __*_ *__* */ {KC_NO         ,None},
  /* 298 * __*_ *_*_ */ {KC_NO         ,None},
  /* 299 * __*_ *_** */ {KC_NO         ,None},
  /* 300 * __*_ **__ */ {KC_C          ,Gui | Shift},
  /* 301 * __*_ **_* */ {KC_NO         ,None},
  /* 302 * __*_ ***_ */ {KC_Q          ,Gui | Shift},
  /* 303 * __*_ **** */ {KC_NO         ,None},
  // 小指付け根と親指２種の３キー同時
  /* 304 * __** ____ */ {KC_NO         ,None},
  /* 305 * __** ___* */ {KC_NO         ,None},
  /* 306 * __** __*_ */ {KC_NO         ,None},
  /* 307 * __** __** */ {KC_NO         ,None},
  /* 308 * __** _*__ */ {KC_NO         ,None},
  /* 309 * __** _*_* */ {KC_NO         ,None},
  /* 310 * __** _**_ */ {KC_NO         ,None},
  /* 311 * __** _*** */ {KC_NO         ,None},
  /* 312 * __** *___ */ {KC_NO         ,None},
  /* 313 * __** *__* */ {KC_NO         ,None},
  /* 314 * __** *_*_ */ {KC_NO         ,None},
  /* 315 * __** *_** */ {KC_NO         ,None},
  /* 316 * __** **__ */ {KC_NO         ,None},
  /* 317 * __** **_* */ {KC_NO         ,None},
  /* 318 * __** ***_ */ {KC_NO         ,None},
  /* 319 * __** **** */ {KC_NO         ,None},
  // 小指付け根と追加の人差し指
  /* 320 * _*__ ____ */ {KC_NO         ,None},
  /* 321 * _*__ ___* */ {KC_NO         ,None},
  /* 322 * _*__ __*_ */ {KC_NO         ,None},
  /* 323 * _*__ __** */ {KC_NO         ,None},
  /* 324 * _*__ _*__ */ {KC_NO         ,None},
  /* 325 * _*__ _*_* */ {KC_NO         ,None},
  /* 326 * _*__ _**_ */ {KC_NO         ,None},
  /* 327 * _*__ _*** */ {KC_NO         ,None},
  /* 328 * _*__ *___ */ {KC_NO         ,None},
  /* 329 * _*__ *__* */ {KC_NO         ,None},
  /* 330 * _*__ *_*_ */ {KC_NO         ,None},
  /* 331 * _*__ *_** */ {KC_NO         ,None},
  /* 332 * _*__ **__ */ {KC_NO         ,None},
  /* 333 * _*__ **_* */ {KC_NO         ,None},
  /* 334 * _*__ ***_ */ {KC_NO         ,None},
  /* 335 * _*__ **** */ {KC_NO         ,None},
  // 小指付け根と通常親指、追加の人差し指の３キー同時
  /* 336 * _*_* ____ */ {KC_NO         ,None},
  /* 337 * _*_* ___* */ {KC_NO         ,None},
  /* 338 * _*_* __*_ */ {KC_NO         ,None},
  /* 339 * _*_* __** */ {KC_NO         ,None},
  /* 340 * _*_* _*__ */ {KC_NO         ,None},
  /* 341 * _*_* _*_* */ {KC_NO         ,None},
  /* 342 * _*_* _**_ */ {KC_NO         ,None},
  /* 343 * _*_* _*** */ {KC_NO         ,None},
  /* 344 * _*_* *___ */ {KC_NO         ,None},
  /* 345 * _*_* *__* */ {KC_NO         ,None},
  /* 346 * _*_* *_*_ */ {KC_NO         ,None},
  /* 347 * _*_* *_** */ {KC_NO         ,None},
  /* 348 * _*_* **__ */ {KC_NO         ,None},
  /* 349 * _*_* **_* */ {KC_NO         ,None},
  /* 350 * _*_* ***_ */ {KC_NO         ,None},
  /* 351 * _*_* **** */ {KC_NO         ,None},
  // 小指付け根、親指内側、追加の人差し指
  /* 352 * _**_ ____ */ {KC_NO         ,None},
  /* 353 * _**_ ___* */ {KC_NO         ,None},
  /* 354 * _**_ __*_ */ {KC_NO         ,None},
  /* 355 * _**_ __** */ {KC_NO         ,None},
  /* 356 * _**_ _*__ */ {KC_NO         ,None},
  /* 357 * _**_ _*_* */ {KC_NO         ,None},
  /* 358 * _**_ _**_ */ {KC_NO         ,None},
  /* 359 * _**_ _*** */ {KC_NO         ,None},
  /* 360 * _**_ *___ */ {KC_NO         ,None},
  /* 361 * _**_ *__* */ {KC_NO         ,None},
  /* 362 * _**_ *_*_ */ {KC_NO         ,None},
  /* 363 * _**_ *_** */ {KC_NO         ,None},
  /* 364 * _**_ **__ */ {KC_NO         ,None},
  /* 365 * _**_ **_* */ {KC_NO         ,None},
  /* 366 * _**_ ***_ */ {KC_NO         ,None},
  /* 367 * _**_ **** */ {KC_NO         ,None},
  // 小指付け根と親指２種、追加の人差し指の４キー同時
  /* 368 * _*** ____ */ {KC_NO         ,None},
  /* 369 * _*** ___* */ {KC_NO         ,None},
  /* 370 * _*** __*_ */ {KC_NO         ,None},
  /* 371 * _*** __** */ {KC_NO         ,None},
  /* 372 * _*** _*__ */ {KC_NO         ,None},
  /* 373 * _*** _*_* */ {KC_NO         ,None},
  /* 374 * _*** _**_ */ {KC_NO         ,None},
  /* 375 * _*** _*** */ {KC_NO         ,None},
  /* 376 * _*** *___ */ {KC_NO         ,None},
  /* 377 * _*** *__* */ {KC_NO         ,None},
  /* 378 * _*** *_*_ */ {KC_NO         ,None},
  /* 379 * _*** *_** */ {KC_NO         ,None},
  /* 380 * _*** **__ */ {KC_NO         ,None},
  /* 381 * _*** **_* */ {KC_NO         ,None},
  /* 382 * _*** ***_ */ {KC_NO         ,None},
  /* 383 * _*** **** */ {KC_NO         ,None},
  // 小指付け根と薬指下
  /* 384 * *___ ____ */ {KC_NO         ,None},
  /* 385 * *___ ___* */ {RGBTOG        ,None},
  /* 386 * *___ __*_ */ {KC_NO         ,None},
  /* 387 * *___ __** */ {KC_NO         ,None},
  /* 388 * *___ _*__ */ {KC_NO         ,None},
  /* 389 * *___ _*_* */ {KC_NO         ,None},
  /* 390 * *___ _**_ */ {KC_NO         ,None},
  /* 391 * *___ _*** */ {KC_NO         ,None},
  /* 392 * *___ *___ */ {KC_NO         ,None},
  /* 393 * *___ *__* */ {KC_NO         ,None},
  /* 394 * *___ *_*_ */ {KC_NO         ,None},
  /* 395 * *___ *_** */ {KC_NO         ,None},
  /* 396 * *___ **__ */ {KC_NO         ,None},
  /* 397 * *___ **_* */ {KC_NO         ,None},
  /* 398 * *___ ***_ */ {KC_NO         ,None},
  /* 399 * *___ **** */ {KC_NO         ,None},
  // 小指付け根と薬指下、通常親指
  /* 400 * *__* ____ */ {KC_NO         ,None},
  /* 401 * *__* ___* */ {KC_NO         ,None},
  /* 402 * *__* __*_ */ {KC_NO         ,None},
  /* 403 * *__* __** */ {KC_NO         ,None},
  /* 404 * *__* _*__ */ {KC_NO         ,None},
  /* 405 * *__* _*_* */ {KC_NO         ,None},
  /* 406 * *__* _**_ */ {KC_NO         ,None},
  /* 407 * *__* _*** */ {KC_NO         ,None},
  /* 408 * *__* *___ */ {KC_NO         ,None},
  /* 409 * *__* *__* */ {KC_NO         ,None},
  /* 410 * *__* *_*_ */ {KC_NO         ,None},
  /* 411 * *__* *_** */ {KC_NO         ,None},
  /* 412 * *__* **__ */ {KC_NO         ,None},
  /* 413 * *__* **_* */ {KC_NO         ,None},
  /* 414 * *__* ***_ */ {KC_NO         ,None},
  /* 415 * *__* **** */ {KC_NO         ,None},
  // 小指付け根と薬指下、親指内側
  /* 416 * *_*_ ____ */ {KC_NO         ,None},
  /* 417 * *_*_ ___* */ {KC_NO         ,None},
  /* 418 * *_*_ __*_ */ {KC_NO         ,None},
  /* 419 * *_*_ __** */ {KC_NO         ,None},
  /* 420 * *_*_ _*__ */ {KC_NO         ,None},
  /* 421 * *_*_ _*_* */ {KC_NO         ,None},
  /* 422 * *_*_ _**_ */ {KC_NO         ,None},
  /* 423 * *_*_ _*** */ {KC_NO         ,None},
  /* 424 * *_*_ *___ */ {KC_NO         ,None},
  /* 425 * *_*_ *__* */ {KC_NO         ,None},
  /* 426 * *_*_ *_*_ */ {KC_NO         ,None},
  /* 427 * *_*_ *_** */ {KC_NO         ,None},
  /* 428 * *_*_ **__ */ {KC_NO         ,None},
  /* 429 * *_*_ **_* */ {KC_NO         ,None},
  /* 430 * *_*_ ***_ */ {KC_NO         ,None},
  /* 431 * *_*_ **** */ {KC_NO         ,None},
  // 小指付け根と親指２種、薬指下
  /* 432 * *_** ____ */ {KC_NO         ,None},
  /* 433 * *_** ___* */ {KC_NO         ,None},
  /* 434 * *_** __*_ */ {KC_NO         ,None},
  /* 435 * *_** __** */ {KC_NO         ,None},
  /* 436 * *_** _*__ */ {KC_NO         ,None},
  /* 437 * *_** _*_* */ {KC_NO         ,None},
  /* 438 * *_** _**_ */ {KC_NO         ,None},
  /* 439 * *_** _*** */ {KC_NO         ,None},
  /* 440 * *_** *___ */ {KC_NO         ,None},
  /* 441 * *_** *__* */ {KC_NO         ,None},
  /* 442 * *_** *_*_ */ {KC_NO         ,None},
  /* 443 * *_** *_** */ {KC_NO         ,None},
  /* 444 * *_** **__ */ {KC_NO         ,None},
  /* 445 * *_** **_* */ {KC_NO         ,None},
  /* 446 * *_** ***_ */ {KC_NO         ,None},
  /* 447 * *_** **** */ {KC_NO         ,None},
  // 小指付け根と薬指下、追加の人差し指
  /* 448 * **__ ____ */ {KC_NO         ,None},
  /* 449 * **__ ___* */ {KC_NO         ,None},
  /* 450 * **__ __*_ */ {KC_NO         ,None},
  /* 451 * **__ __** */ {KC_NO         ,None},
  /* 452 * **__ _*__ */ {KC_NO         ,None},
  /* 453 * **__ _*_* */ {KC_NO         ,None},
  /* 454 * **__ _**_ */ {KC_NO         ,None},
  /* 455 * **__ _*** */ {KC_NO         ,None},
  /* 456 * **__ *___ */ {KC_NO         ,None},
  /* 457 * **__ *__* */ {KC_NO         ,None},
  /* 458 * **__ *_*_ */ {KC_NO         ,None},
  /* 459 * **__ *_** */ {KC_NO         ,None},
  /* 460 * **__ **__ */ {KC_NO         ,None},
  /* 461 * **__ **_* */ {KC_NO         ,None},
  /* 462 * **__ ***_ */ {KC_NO         ,None},
  /* 463 * **__ **** */ {KC_NO         ,None},
  // 小指付け根と薬指下、通常親指と追加の人差し指
  /* 464 * **_* ____ */ {KC_NO         ,None},
  /* 465 * **_* ___* */ {KC_NO         ,None},
  /* 466 * **_* __*_ */ {KC_NO         ,None},
  /* 467 * **_* __** */ {KC_NO         ,None},
  /* 468 * **_* _*__ */ {KC_NO         ,None},
  /* 469 * **_* _*_* */ {KC_NO         ,None},
  /* 470 * **_* _**_ */ {KC_NO         ,None},
  /* 471 * **_* _*** */ {KC_NO         ,None},
  /* 472 * **_* *___ */ {KC_NO         ,None},
  /* 473 * **_* *__* */ {KC_NO         ,None},
  /* 474 * **_* *_*_ */ {KC_NO         ,None},
  /* 475 * **_* *_** */ {KC_NO         ,None},
  /* 476 * **_* **__ */ {KC_NO         ,None},
  /* 477 * **_* **_* */ {KC_NO         ,None},
  /* 478 * **_* ***_ */ {KC_NO         ,None},
  /* 479 * **_* **** */ {KC_NO         ,None},
  // 通常親指以外
  /* 480 * ***_ ____ */ {KC_NO         ,None},
  /* 481 * ***_ ___* */ {KC_NO         ,None},
  /* 482 * ***_ __*_ */ {KC_NO         ,None},
  /* 483 * ***_ __** */ {KC_NO         ,None},
  /* 484 * ***_ _*__ */ {KC_NO         ,None},
  /* 485 * ***_ _*_* */ {KC_NO         ,None},
  /* 486 * ***_ _**_ */ {KC_NO         ,None},
  /* 487 * ***_ _*** */ {KC_NO         ,None},
  /* 488 * ***_ *___ */ {KC_NO         ,None},
  /* 489 * ***_ *__* */ {KC_NO         ,None},
  /* 490 * ***_ *_*_ */ {KC_NO         ,None},
  /* 491 * ***_ *_** */ {KC_NO         ,None},
  /* 492 * ***_ **__ */ {KC_NO         ,None},
  /* 493 * ***_ **_* */ {KC_NO         ,None},
  /* 494 * ***_ ***_ */ {KC_NO         ,None},
  /* 495 * ***_ **** */ {KC_NO         ,None},
  // 追加系のキー全て
  /* 496 * **** ____ */ {KC_NO         ,None},
  /* 497 * **** ___* */ {KC_NO         ,None},
  /* 498 * **** __*_ */ {KC_NO         ,None},
  /* 499 * **** __** */ {KC_NO         ,None},
  /* 500 * **** _*__ */ {KC_NO         ,None},
  /* 501 * **** _*_* */ {KC_NO         ,None},
  /* 502 * **** _**_ */ {KC_NO         ,None},
  /* 503 * **** _*** */ {KC_NO         ,None},
  /* 504 * **** *___ */ {KC_NO         ,None},
  /* 505 * **** *__* */ {KC_NO         ,None},
  /* 506 * **** *_*_ */ {KC_NO         ,None},
  /* 507 * **** *_** */ {KC_NO         ,None},
  /* 508 * **** **__ */ {KC_NO         ,None},
  /* 509 * **** **_* */ {KC_NO         ,None},
  /* 510 * **** ***_ */ {KC_NO         ,None},
  /* 511 * **** **** */ {KC_NO         ,None},
};

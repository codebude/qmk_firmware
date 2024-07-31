#include QMK_KEYBOARD_H
#include "keymap_german.h"
#include "layers.h"
#include "oled.h"


enum custom_keycodes {
    DELWORD = SAFE_RANGE // Delete last word via S-Opt-Left Del combo
};

// Left-hand home row mods
#define _GUI_A LGUI_T(DE_A)
#define _ALT_R LALT_T(DE_R)
#define _SFT_S LSFT_T(DE_S)
#define _CTL_T LCTL_T(DE_T)

// Right-hand home row mods
#define _CTL_N RCTL_T(DE_N)
#define _SFT_E RSFT_T(DE_E)
#define _ALT_I LALT_T(DE_I)
#define _GUI_O RGUI_T(DE_O)

//*********************************************************
//          KEYMAP
//*********************************************************

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    DE_Q,    DE_W,    DE_F,    DE_P,    DE_B,            DE_J,    DE_L,    DE_U,    DE_Y,    DE_SCLN,
    _GUI_A,  _ALT_R,  _SFT_S,  _CTL_T,   DE_G,           DE_M,    _CTL_N,  _SFT_E,  _ALT_I,  _GUI_O,
    DE_Z,    DE_X,    DE_C,    DE_D,    DE_V,            DE_K,    DE_H,    DE_COMM, DE_DOT,  DE_SLSH,
                                 MO(1), KC_SPC, KC_BSPC, LT(2, KC_ESC)
  ),

  [_NUM] = LAYOUT(
    DE_1,    DE_2,    DE_3,     DE_4,     DE_5,            DE_6,    DE_7,    DE_8,    DE_9,    DE_0,
    KC_LWIN, KC_LALT, KC_LSFT,  KC_LCTL,  KC_GRV,          KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_ESC,
    KC_LSFT, KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,         KC_HOME,  KC_END, KC_TAB,  KC_DEL,  KC_LSFT,
                                    KC_TRNS, TG(4), DELWORD, LT(3, KC_ENT)
  ),

  [_SYM] = LAYOUT(
    KC_EXLM, KC_QUES, KC_LPRN, KC_RPRN, KC_ASTR,         KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    KC_LWIN, KC_LALT, KC_LSFT,  KC_LCTL,   KC_BSLS,         KC_TRNS, KC_EQL,  KC_LCBR, KC_RCBR, KC_SCLN,
    KC_LSFT, KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,         KC_UNDS, KC_MINS, KC_LBRC, KC_RBRC, KC_LSFT,
                                    MO(3), KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [_NAV] = LAYOUT(
    KC_TRNS, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE,         QK_BOOT, KC_F9,   KC_F10,  KC_F11,  KC_F12,
    KC_LWIN, KC_LALT, KC_LSFT,  KC_LCTL,   KC_VOLU,         KC_BRIU, KC_F5,   KC_F6,   KC_F7,   KC_F8,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_VOLD,         KC_BRID, KC_F1,   KC_F2,   KC_F3,   KC_F4,
                                    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [_NUMBLK] = LAYOUT(
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, DE_7, DE_8, DE_9, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, DE_4, DE_5, DE_6, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,         KC_TRNS, DE_1, DE_2, DE_3, KC_TRNS,
                                    TG(4), KC_TRNS, KC_TRNS, DE_0
  )
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case DELWORD:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(KC_LSFT);
                tap_code(KC_LEFT);
                unregister_code(KC_LSFT);
                unregister_code(KC_LCTL);
                tap_code(KC_DEL);
            }
            break;       
    }
    if (record->event.pressed) {
        set_keylog(keycode, record);
    }
    return true;
};


void keyboard_pre_init_user(void) {
  // Set our LED pin as output
  setPinOutput(24);
  // Turn the LED off
  // (Due to technical reasons, high is off and low is on)
  writePinHigh(24);
}



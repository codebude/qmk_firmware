#include QMK_KEYBOARD_H
#include "keymap_german.h"
#include "layers.h"
#include "oled.h"


enum custom_keycodes {
    DELWORD = SAFE_RANGE, // Delete last word via S-Opt-Left Del combo
    // German umlaute    
    CLR_MOD,
};

// One shot modifiers used on all upper layers
#define M_GUI OSM(MOD_LGUI)
#define M_SHFT OSM(MOD_LSFT)
#define M_ALT OSM(MOD_LALT)
#define M_CTRL OSM(MOD_LCTL)

// Mod tap shift keys used on base layer
#define T_SFT_Z LSFT_T(KC_Z)
#define T_SFT_SLH LSFT_T(KC_SLSH)
#define T_SFT_A LSFT_T(KC_A)
#define T_SFT_O LSFT_T(KC_O)
#define T_GUI_SPC LGUI_T(KC_SPC)
#define T_CTL_BSPC LCTL_T(KC_BSPC)



//*********************************************************
//          KEYMAP
//*********************************************************

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    DE_Q,    DE_W,    DE_F,    DE_P,    DE_B,            DE_J,    DE_L,    DE_U,    DE_Y,    DE_SCLN,
    DE_A,    DE_R,    DE_S,    DE_T,    DE_G,            DE_M,    DE_N,    DE_E,    DE_I,    DE_O,
    DE_Z,    DE_X,    DE_C,    DE_D,    DE_V,            DE_K,    DE_H,    DE_COMM, DE_DOT,  DE_SLSH,
                                 MO(1), T_GUI_SPC, T_CTL_BSPC, LT(2, KC_ESC)
  ),

  [_NUM] = LAYOUT(
    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,            KC_6,    KC_7,    KC_8,    KC_9,    KC_0,
    M_SHFT,  M_ALT,   M_CTRL,  M_GUI,   KC_GRV,          KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, KC_ESC,
    KC_LSFT, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,         KC_TRNS, KC_ENT,  KC_TAB,  KC_DEL,  KC_LSFT,
                                    KC_TRNS, TG(4), DELWORD, MO(3)
  ),

  [_SYM] = LAYOUT(
    KC_EXLM, KC_QUES, KC_LPRN, KC_RPRN, KC_ASTR,         KC_TRNS, KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
    M_SHFT,  M_ALT,   M_CTRL,  M_GUI,   KC_BSLS,         KC_TRNS, KC_EQL,  KC_LCBR, KC_RCBR, KC_SCLN,
    KC_LSFT, KC_TRNS, KC_TRNS,    KC_TRNS,    KC_TRNS,         KC_UNDS, KC_MINS, KC_LBRC, KC_RBRC, KC_LSFT,
                                    MO(3), KC_TRNS, KC_TRNS, KC_TRNS
  ),

  [_NAV] = LAYOUT(
    KC_TRNS, KC_MPRV, KC_MPLY, KC_MNXT, KC_MUTE,         QK_BOOT, KC_F9,   KC_F10,  KC_F11,  KC_F12,
    M_SHFT,  M_ALT,   M_CTRL,  M_GUI,   KC_VOLU,         KC_BRIU, KC_F5,   KC_F6,   KC_F7,   KC_F8,
    KC_TRNS, KC_TRNS, CLR_MOD, KC_TRNS, KC_VOLD,         KC_BRID, KC_F1,   KC_F2,   KC_F3,   KC_F4,
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
                register_code(KC_LSFT);
                register_code(KC_LALT);
                tap_code(KC_LEFT);
                unregister_code(KC_LSFT);
                unregister_code(KC_LALT);
                tap_code(KC_DEL);
            }
            break;
        case CLR_MOD:
            if (record->event.pressed) {
                clear_mods();
                clear_oneshot_mods();
                return false;
            }
            break;
    }
    if (record->event.pressed) {
        set_keylog(keycode, record);
    }
    return true;
};

//*********************************************************
//          CUSTOM HOLD ON KEY PRESS
//*********************************************************

bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case T_GUI_SPC:
            return false;
        case T_CTL_BSPC:
            return false;
		case T_SFT_Z:
            return false;
        default:
            return true;
    }
}

//*********************************************************
//          CUSTOM TAPPING TERM
//*********************************************************

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case M_GUI:
    case M_CTRL:
    case M_ALT:
    case M_SHFT:
        return ONESHOT_TAPPING_TERM;
    default:
        return TAPPING_TERM;
    }
}


void keyboard_pre_init_user(void) {
  // Set our LED pin as output
  setPinOutput(24);
  // Turn the LED off
  // (Due to technical reasons, high is off and low is on)
  writePinHigh(24);
}



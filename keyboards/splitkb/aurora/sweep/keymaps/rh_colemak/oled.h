#pragma once

#if defined(OLED_ENABLE) && defined(WPM_ENABLE)

char wpm_str[12];
char mod_str[12];
char keylog_str[24] = {};
char timer_str[24] = {};
uint16_t wpm_graph_timer = 0;
static uint32_t last_oled_timer = 0;
bool idle_cleared = false;
/*
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;
}
*/

void oled_render_separator(void) {
    oled_write_ln("_____", false);
}

void oled_render_space(void) {
    oled_write_ln("     ", false);
}

void oled_render_layer_state(void) {
    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write("[CMK]", false);
            break;
        case _NUM:
            oled_write("[NUM]", true);
            break;
        case _SYM:
            oled_write("[SYM]", true);
            break;
        case _NAV:
            oled_write("[NAV]", true);
            break;
        case _NUMBLK:
            oled_write("[BLK]", true);
            break;       
        default:
            oled_write("[NOP]", true);
            break;
    }
}

void set_keylog(uint16_t keycode, keyrecord_t *record) {
    if ((keycode >= QK_MOD_TAP && keycode <= QK_MOD_TAP_MAX) ||
        (keycode >= QK_LAYER_TAP && keycode <= QK_LAYER_TAP_MAX)) {
        keycode = keycode & 0xFF;
    } else if (keycode > 0xFF) {
        keycode = 0;
    }

    // update keylog
    snprintf(keylog_str, sizeof(keylog_str), "[MAT] %dx%d [KYC] %03d ",
        record->event.key.row, record->event.key.col,
        keycode); 
}

void oled_render_keylog(void) {
    if (strlen(keylog_str) == 0) {
        snprintf(keylog_str, sizeof(keylog_str), "[MAT] 0x0 [KYC] 000 ");
    }
    oled_write(keylog_str, false);
}


void oled_render_keymods(void) {
    led_t led_usb_state = host_keyboard_led_state();
    sprintf(mod_str, "num %scap %s",
        led_usb_state.num_lock ? "+" : "-",
        led_usb_state.caps_lock ? "+" : "-"
    );
    oled_write(mod_str, false);
}

void oled_render_wpm(void) {
    sprintf(wpm_str, "[WPM] %03d ", get_current_wpm());
    oled_write(wpm_str, false);
}

// Inspired from brickbots' Kyria keymap
// - https://github.com/brickbots/qmk_firmware/tree/brickbots_dev/keyboards/kyria/keymaps/brickbots
// - https://www.reddit.com/r/MechanicalKeyboards/comments/evimyg/kyria_is_kool_onboard_wpm_calc_oled_graph/
static void oled_render_wpm_graph(void) {
    static uint8_t bar_count = 0;
    uint8_t bar_height = 0;
    uint8_t bar_segment = 0;

    if (wpm_graph_timer == 0) {
        wpm_graph_timer = timer_read();
        return;
    }
    if(timer_elapsed(wpm_graph_timer) > 500) {
        wpm_graph_timer = timer_read();
        bar_height = get_current_wpm() / 20;

        oled_pan(false);
        bar_count++;
        for (uint8_t i = (OLED_DISPLAY_WIDTH / 8); i > 0; i--) {
            switch (bar_height) {
                case 0:
                    bar_segment = 128;
                    break;

                case 1:
                    bar_segment = 128;
                    break;

                case 2:
                    bar_segment = 192;
                    break;

                case 3:
                    bar_segment = 224;
                    break;

                case 4:
                    bar_segment = 240;
                    break;

                case 5:
                    bar_segment = 248;
                    break;

                case 6:
                    bar_segment = 252;
                    break;

                case 7:
                    bar_segment = 254;
                    break;
            }
            bar_height = 0;

            if (i % 2 == 1 && bar_count % 3 == 0)
                bar_segment++;

            oled_write_raw_byte(bar_segment, (i-1) * OLED_DISPLAY_HEIGHT);
        }
    }
}

// 5x3 Logos
void oled_render_mario_logo(void) {
    static const char PROGMEM font_logo[16] = {0x80, 0x81, 0x82, 0x83, 0x84, 0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0};
    oled_write_P(font_logo, false);
};

void oled_render_kapi_logo(void) {
    static const char PROGMEM font_kapi_logo[2][16] = {
        {0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0},
        {0x85, 0x86, 0x87, 0x88, 0x89, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0}
    };
    oled_write_P(font_kapi_logo[get_current_wpm() % 2], false);
};

void oled_render_big_num(uint8_t idx) {
    static const char PROGMEM font_big_num[5][11] = {
        {0x8f, 0xB0, 0xB1, 0xAF, 0x8f, 0x8f, 0xD0, 0xD1, 0xCF, 0x8f, 0},
        {0x8f, 0xB2, 0xB3, 0xAF, 0x8f, 0x8f, 0xD2, 0xD3, 0xCF, 0x8f, 0},
        {0x8f, 0xB4, 0xB5, 0xAF, 0x8f, 0x8f, 0xD4, 0xD5, 0xCF, 0x8f, 0},
        {0x8f, 0xB6, 0xB7, 0xAF, 0x8f, 0x8f, 0xD6, 0xD7, 0xCF, 0x8f, 0},
        {0x8f, 0xB8, 0xB9, 0xAF, 0x8f, 0x8f, 0xD8, 0xD9, 0xCF, 0x8f, 0}
    };
    oled_write_P(font_big_num[idx], false);
}

void oled_render_status_bar(uint8_t idx) {
    static const char PROGMEM font_status_bar[5][11] = {
        {0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0xDA, 0xDB, 0xDC, 0x8f, 0},
        {0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0xBA, 0xBB, 0xDC, 0x8f, 0},
        {0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0xBA, 0xBC, 0xDC, 0x8f, 0},
        {0x8f, 0x8f, 0x8f, 0x9E, 0x8f, 0x8f, 0xBA, 0xBD, 0xBE, 0x8f, 0},
        {0x8f, 0x8f, 0x8f, 0x9F, 0x8f, 0x8f, 0xBA, 0xBD, 0xBF, 0x8f, 0}
    };
    oled_write_P(font_status_bar[idx], false);
}

void oled_render_big_layer_status(uint8_t idx) {
    static const char PROGMEM font_status_big[5][11] = {
        {0x8f, 0x8f, 0x8f, 0xB0, 0xB1, 0xDA, 0xDB, 0xDC, 0xD0, 0xD1, 0},
        {0x8f, 0x8f, 0x8f, 0xB2, 0xB3, 0xBA, 0xBB, 0xDC, 0xD2, 0xD3, 0},
        {0x8f, 0x8f, 0x8f, 0xB4, 0xB5, 0xBA, 0xBC, 0xDC, 0xD4, 0xD5, 0},
        {0x8f, 0x8f, 0x9E, 0xB6, 0xB7, 0xBA, 0xBD, 0xBE, 0xD6, 0xD7, 0},
        {0x8f, 0x8f, 0x9F, 0xB8, 0xB9, 0xBA, 0xBD, 0xBF, 0xD8, 0xD9, 0}
    };
    oled_write_P(font_status_big[idx], false);
}

void oled_render_big_layer_status_dotted(uint8_t idx) {
    static const char PROGMEM font_status_big_dot[5][26] = {
        {0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0},
        {0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0},
        {0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0},
        {0x8f, 0x8f, 0x8f, 0x8f, 0x8f, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0},
        {0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0xDF, 0}
    };
    oled_write_P(font_status_big_dot[idx], false);
}

void oled_render_master(void) {
    oled_render_layer_state();
    oled_render_separator();

    oled_render_keylog();
    oled_render_separator();

    oled_render_keymods();
    oled_render_separator();

    oled_render_wpm();
    oled_render_wpm_graph();
}

void oled_render_slave(void) {
    oled_render_mario_logo();    
    oled_render_space();
    uint8_t highest_layer = get_highest_layer(layer_state);
    oled_render_big_layer_status(highest_layer);
    oled_render_space();
    oled_render_space();
    oled_render_big_layer_status_dotted(highest_layer);
}

void oled_render_idle(void) {
    if (!idle_cleared) {
        idle_cleared = true;
        oled_clear();
    }    
    oled_render_space();
    oled_render_space();
    oled_render_mario_logo();
    oled_render_space();
    oled_write("Zzz..", false);
    oled_write("..zzz", false);
    oled_write("zzz..", false);
}

bool oled_task_user(void) {
    if (last_matrix_activity_elapsed() < sync_timer_elapsed32(last_oled_timer)) {
        idle_cleared = false;
    }
    last_oled_timer = last_matrix_activity_elapsed();
    if (last_matrix_activity_elapsed() > 30000 && last_matrix_activity_elapsed() < 45000) {       
        oled_render_idle();       
        return false;
    }
    else if (last_matrix_activity_elapsed() >= 45000) {
        oled_off();       
        return false;
    }
    else {             
        if (!is_oled_on()) {
            oled_on();
        }
        if (is_keyboard_master()) {
            oled_render_master();
        } else {
            oled_render_slave();
        }        
        return false;
    }
}


#endif
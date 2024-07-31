/* Copyright 2022 splitkb.com <support@splitkb.com>, 2024 Raffael Herrmann
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once


// Not yet available in `keymap.json` format
#ifdef MOUSEKEY_ENABLE
     // The default is 100
#    define MOUSEKEY_WHEEL_INTERVAL 50
     // The default is 40
#    define MOUSEKEY_WHEEL_TIME_TO_MAX 100
#endif

// Smaller values lead to mistriggered Shifts, especially /w z-w rolls
#define TAPPING_TERM 250


//#define PERMISSIVE_HOLD
//#define HOLD_ON_OTHER_KEY_PRESS
//#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY
//#define ONESHOT_TAP_TOGGLE 2


// increace debounce timeout to 30 ms
#define DEBOUNCE 30

// Split settings
//#define SPLIT_LED_STATE_ENABLE // Push LED state to slave
#define SPLIT_LAYER_STATE_ENABLE
//#define SPLIT_TRANSPORT_MIRROR
#define SPLIT_ACTIVITY_ENABLE
//#define SPLIT_WPM_ENABLE // Send WPM value to slave
#define OLED_DISPLAY_128X32
#define SPLIT_OLED_ENABLE
#define OLED_DISABLE_TIMEOUT
#define OLED_FONT_H "keyboards/splitkb/aurora/sweep/keymaps/rh_colemak/glcdfont_rh.c"
#define OLED_UPDATE_INTERVAL 0
/*
Copyright 2020 regalex

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
#define VENDOR_ID  0xFEED
#define PRODUCT_ID 0x0504
#define DEVICE_VER 0x0001
#define MANUFACTURER Regalex
#define PRODUCT mudnipadpro
#define DESCRIPTION A custom mini midi music pad

/* key matrix size */
#define MATRIX_ROWS 3
#define MATRIX_COLS 5
#define MATRIX_ROW_PINS {B2, B4, E6}
#define MATRIX_COL_PINS { F7, B1, B3, B6, B5}
#define DIODE_DIRECTION COL2ROW
#define ENCODERS_PAD_A { F5 }
#define ENCODERS_PAD_B { F4 }
#define C6_AUDIO
#define UNUSED_PINS
#define OLED_DISPLAY_ADDRESS 0x3C
#define OLED_TIMEOUT 30000
#define SSD1306OLED
#define DEBOUNCE 5


#ifdef AUDIO_ENABLE
    #define C6_AUDIO
    #define PITCH_STANDARD_A 432.0f
    #define STARTUP_SONG SONG(STARTUP_SOUND)
    #define MUSIC_MAP
#endif

/* disable these deprecated features by default */
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION


#ifndef NO_DEBUG
#define NO_DEBUG
#endif // !NO_DEBUG
#if !defined(NO_PRINT) && !defined(CONSOLE_ENABLE)
#define NO_PRINT
#endif // !NO_PRINT
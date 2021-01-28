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

#ifdef BACKLIGHT_ENABLE
    #define BACKLIGHT_PIN C6
    #define BACKLIGHT_LEVELS 12
    #define BACKLIGHT_BREATHING
    #define BREATHING_PERIOD 6
#endif

#ifdef OLED_DRIVER_ENABLE
    #define OLED_DISPLAY_ADDRESS 0x3C
    #define OLED_TIMEOUT 60000
    //#define OLED_DISABLE_TIMEOUT
    #define SSD1306OLED
#endif

#define DEBOUNCE 5
#define TAPPING_TERM 200

#define UNUSED_PINS

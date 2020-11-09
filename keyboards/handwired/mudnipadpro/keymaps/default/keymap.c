/* Copyright 2020 regalex
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

#include QMK_KEYBOARD_H

#ifdef POT_ENABLE
  #include "analog.h"
#endif
//#include "process_midi.h"
#include "midi.h"

extern MidiDevice midi_device;

// definitions
enum custom_keycodes {
    ENC_TG = SAFE_RANGE,
    SAVE,
    CUT,
    COPY,
    PASTE,
    UNDO,
    REDO,
    MIDI_CC1,
    MIDI_CC2,
    MIDI_CC3,
    MIDI_CC4,
    MIDI_CC5,
    MIDI_CC6,
    MIDI_CC7,
    MIDI_CC8,
    MIDI_CC9,
    MIDI_CC10,
    MIDI_CC11,
    MIDI_CC12
};


static char current_ltrm_alpha_oled = '\0';
static uint8_t current_MIDI_ccNumber         = 1;
static char    current_MIDI_ccNumber_char[3] = {'0', '1', '\0'};
static uint8_t current_layer;
static uint8_t next_layer;
int16_t pot_oldVal = 0;
int16_t pot_val    = 0;
int16_t pot_ccVal  = 0;
#define POT_TOLERANCE 12


// Defines names for use in layer keycodes and the keymap
enum custom_layers {
    _FUNC = 0,
    _MUSIC,
    _SYNTH,
    _MIDI
};



// Layers and keymaps

const uint8_t music_map[MATRIX_ROWS][MATRIX_COLS] = LAYOUT_NOENC(
    8,  9, 10, 11, \
    4,  5,  6,  7, \
    0,  1,  2,  3 \
);


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_FUNC] = LAYOUT(
            KC_ESC, AU_TOG, MU_TOG, MU_MOD, \
    ENC_TG, KC_TAB, SAVE,   KC_NO, UNDO, \
            CUT,    COPY,   PASTE,  REDO   \
    ), \
    [_MUSIC] = LAYOUT(
             KC_NO, KC_NO, KC_NO, KC_NO, \
    KC_TRNS, KC_NO, KC_NO, KC_NO, KC_NO, \
             KC_NO,  KC_NO, KC_NO, KC_NO  \
    ), \
    [_SYNTH] = LAYOUT(
             MI_C, MI_Cs, MI_D, MI_Eb, \
    KC_TRNS, MI_E, MI_F, MI_Gb, MI_G,  \
             MI_Ab, MI_A, MI_Bb, MI_B  \
    ), \
    [_MIDI]  = LAYOUT(
                MIDI_CC1, MIDI_CC2, MIDI_CC3, MIDI_CC4, \
    KC_TRNS,    MIDI_CC5, MIDI_CC6, MIDI_CC7, MIDI_CC8, \
                MIDI_CC9, MIDI_CC10,MIDI_CC11, MIDI_CC12 \
    )
};

#ifdef OLED_DRIVER_ENABLE
    //Main screen render definition
        void oled_render_layers(void){
            oled_write_P(PSTR("LAYER: "), false);
            switch (get_highest_layer(layer_state)) {
                case _FUNC:
                    oled_write_P(PSTR("FUNCTION\n"), false);
                    break;
                case _MUSIC:
                    oled_write_P(PSTR("MUSIC\n"), false);
                    break;
                case _SYNTH:
                    oled_write_P(PSTR("SYNTHETIZER\n"), false);
                    break;
                case _MIDI:
                    oled_write_P(PSTR("MIDI\n"), false);
                    break;
                default:
                    oled_write_P(PSTR("UNDEFINED\n"), false);
                    break;
            }
        }

    //Oled Render routine
        void oled_task_user(void) {
            static const char PROGMEM image[] = {0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94, 0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4, 0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4};
            oled_write_P(image, false);
            switch (biton32(layer_state)) {

            case _MIDI:
                oled_write_P(PSTR("CC "), false);
                oled_write(current_MIDI_ccNumber_char, false);
                oled_write_P(PSTR("    ["), false);
                if (current_ltrm_alpha_oled == '\0') {
                    oled_write_char('*', false);
                } else {
                    oled_write_char(current_ltrm_alpha_oled, false);
                }
                oled_write_P(PSTR("]   "), false);
                break;
                // case _MIDI:
                //     oled_write_P(PSTR("               "), false);
                //     // oled_write(itoa(midi_config.octave, vel, 10), false);
                //     break;
            }
            oled_render_layers();
        }
#endif


#ifdef ENCODER_ENABLE

    //Change Layer with encoder
    void encoder_update_user(uint8_t index, bool clockwise) {

        switch (biton32(layer_state)) {
            case _MIDI:
                if (clockwise) {
                    midi_send_cc(&midi_device, 0, current_MIDI_ccNumber, 65);
                } else {
                    midi_send_cc(&midi_device, 0, current_MIDI_ccNumber, 63);
                }
                break;
            default:
                if (clockwise) {
                    tap_code(KC_VOLU);
                } else {
                    tap_code(KC_VOLD);
                }
                break;
        }
    }
#endif

//Callbacks

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    #ifdef CONSOLE_ENABLE
    uprintf("KL= kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
    #endif
    switch (keycode) {
        case CUT:
            if (record->event.pressed) {
                tap_code16(LCTL(KC_X));
            }
            break;
        case COPY:
            if (record->event.pressed) {
                tap_code16(LCTL(KC_C));
            }
            break;
        case PASTE:
            if (record->event.pressed) {
                tap_code16(LCTL(KC_V));
            }
            break;
        case SAVE:
            if (record->event.pressed) {
                tap_code16(LCTL(KC_S));
            }
            break;
        case UNDO:
            if (record->event.pressed) {
                tap_code16(LCTL(KC_W));
            }
            break;
        case REDO:
            if (record->event.pressed) {
                tap_code16(LCTL(KC_Y));
            }
            break;
        case ENC_TG:
            if (record->event.pressed) {
                current_layer = biton32(layer_state);
                next_layer = current_layer+1;
                if (next_layer > _MIDI) {
                    next_layer = _FUNC;
                    layer_move(next_layer);
                    dprintf("current layer: %u", current_layer);
                } else {
                    layer_move(next_layer);
                    dprintf("current layer: %u", next_layer);
                }
            }
            break;
        case MIDI_CC1:
            if (record->event.pressed) {
                current_MIDI_ccNumber         = 1;
                current_ltrm_alpha_oled       = 'Q';
                current_MIDI_ccNumber_char[0] = '0';
                current_MIDI_ccNumber_char[1] = '1';
            }
            return false;
            break;
        case MIDI_CC2:
            if (record->event.pressed) {
                current_MIDI_ccNumber         = 2;
                current_ltrm_alpha_oled       = 'W';
                current_MIDI_ccNumber_char[0] = '0';
                current_MIDI_ccNumber_char[1] = '2';
            }
            return false;
            break;
        case MIDI_CC3:
            if (record->event.pressed) {
                current_MIDI_ccNumber         = 3;
                current_ltrm_alpha_oled       = 'E';
                current_MIDI_ccNumber_char[0] = '0';
                current_MIDI_ccNumber_char[1] = '3';
            }
            return false;
            break;
        case MIDI_CC4:
            if (record->event.pressed) {
                current_MIDI_ccNumber         = 4;
                current_ltrm_alpha_oled       = 'R';
                current_MIDI_ccNumber_char[0] = '0';
                current_MIDI_ccNumber_char[1] = '4';
            }
            return false;
            break;
        case MIDI_CC5:
            if (record->event.pressed) {
                current_MIDI_ccNumber         = 5;
                current_ltrm_alpha_oled       = 'T';
                current_MIDI_ccNumber_char[0] = '0';
                current_MIDI_ccNumber_char[1] = '5';
            }
            return false;
            break;
        case MIDI_CC6:
            if (record->event.pressed) {
                current_MIDI_ccNumber         = 6;
                current_ltrm_alpha_oled       = 'Y';
                current_MIDI_ccNumber_char[0] = '0';
                current_MIDI_ccNumber_char[1] = '6';
            }
            return false;
            break;
        case MIDI_CC7:
            if (record->event.pressed) {
                current_MIDI_ccNumber         = 7;
                current_ltrm_alpha_oled       = 'U';
                current_MIDI_ccNumber_char[0] = '0';
                current_MIDI_ccNumber_char[1] = '7';
            }
            return false;
            break;
        case MIDI_CC8:
            if (record->event.pressed) {
                current_MIDI_ccNumber         = 8;
                current_ltrm_alpha_oled       = 'I';
                current_MIDI_ccNumber_char[0] = '0';
                current_MIDI_ccNumber_char[1] = '8';
            }
            return false;
            break;
        case MIDI_CC9:
            if (record->event.pressed) {
                current_MIDI_ccNumber         = 9;
                current_ltrm_alpha_oled       = 'O';
                current_MIDI_ccNumber_char[0] = '0';
                current_MIDI_ccNumber_char[1] = '9';
            }
            return false;
            break;
        case MIDI_CC10:
            if (record->event.pressed) {
                current_MIDI_ccNumber         = 10;
                current_ltrm_alpha_oled       = 'P';
                current_MIDI_ccNumber_char[0] = '1';
                current_MIDI_ccNumber_char[1] = '0';
            }
            return false;
            break;
        case MIDI_CC11:
            if (record->event.pressed) {
                current_MIDI_ccNumber         = 11;
                current_ltrm_alpha_oled       = 'A';
                current_MIDI_ccNumber_char[0] = '1';
                current_MIDI_ccNumber_char[1] = '1';
            }
            return false;
            break;
        case MIDI_CC12:
            if (record->event.pressed) {
                current_MIDI_ccNumber         = 12;
                current_ltrm_alpha_oled       = 'S';
                current_MIDI_ccNumber_char[0] = '1';
                current_MIDI_ccNumber_char[1] = '2';
            }
            return false;
            break;
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    #ifdef CONSOLE_ENABLE
        uprintf("layer: %u\n", biton32(state));
    #endif
    return state;
}


void keyboard_post_init_user(void) {
    #ifdef CONSOLE_ENABLE
        debug_enable=true;
        debug_matrix=true;
    #endif
}

void matrix_init_user(void) {
    #ifdef POT_ENABLE
        analogReference(ADC_REF_POWER);
    #endif
    return;
}

void matrix_scan_user(void) {
#ifdef POT_ENABLE
    pot_val   = (analogReadPin(D4));
    pot_ccVal = pot_val / 8;
    if (abs(pot_val - pot_oldVal) > POT_TOLERANCE) {
        pot_oldVal = pot_val;
        midi_send_cc(&midi_device, 0, 27, pot_ccVal);
    }
#endif
}

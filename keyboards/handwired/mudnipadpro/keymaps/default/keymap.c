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

// Defines names for use in layer keycodes and the keymap
enum custom_layers {
    _KPAD = 0,
    _FN,
    _FPS
};

#ifdef AUDIO_ENABLE
    #undef ZELDA_TREASURE
    #define ZELDA_TREASURE \
        Q__NOTE(_A4), \
        Q__NOTE(_AS4), \
        Q__NOTE(_B4), \
        HD_NOTE(_C5), \

#endif



#ifdef TAP_DANCE_ENABLE
    #define KC_PLENT    TD(TD_PLENT)
    #define KC_MDIV     TD(TD_MULT_DIV)

/*
    typedef struct {
        bool is_press_action;
        uint8_t state;
    } tap;

    enum {
        SINGLE_TAP = 1,
        SINGLE_HOLD,
        DOUBLE_TAP,
        DOUBLE_HOLD,
        DOUBLE_SINGLE_TAP, // Send two single taps
    };
 */
    //tapdance  Keycode definition
    enum {
        TD_PLENT,
        TD_MULT_DIV
    };

    qk_tap_dance_action_t tap_dance_actions[] = {
        [TD_PLENT] = ACTION_TAP_DANCE_DOUBLE(KC_PPLS, KC_PENT),
        [TD_MULT_DIV] = ACTION_TAP_DANCE_DOUBLE(KC_PAST, KC_PSLS)
    }

#else
    #define KC_PLENT    KC_PPLS
    #define KC_MDIV     KC_PAST
#endif



// definitions
enum custom_keycodes {
    SAVE = SAFE_RANGE,
    CUT,
    COPY,
    PASTE
};


// Layers and keymaps


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_KPAD] = LAYOUT(
    /*            ┌──────────┬──────────┬─────────┬─────────┬──────────┐ */
                    KC_NLCK,    KC_P7,     KC_P8,    KC_P9,   KC_PMNS, \
    /*            ├──────────┼──────────┼─────────┼─────────┼──────────┤ */
        MO(_FN),    KC_MDIV,    KC_P4,     KC_P5,    KC_P6,   KC_PLENT, \
    /*┌───────────┼──────────┼──────────┼─────────┼─────────┤          | */
        KC_PDOT,    KC_P0,      KC_P1,     KC_P2,    KC_P3 \
    /*└───────────┴──────────┴──────────┴─────────┴─────────┴──────────┘ */
    ),
        [_FN] = LAYOUT(
    /*            ┌──────────┬──────────┬─────────┬─────────┬──────────┐ */
                    TG(_FPS),  CG_SWAP,    KC_F13,   KC_F14,    KC_F15, \
    /*            ├──────────┼──────────┼─────────┼─────────┼──────────┤ */
        KC_TRNS,   RGB_TOG,  RGB_MOD,   RGB_VAI,  RGB_SAI,   KC_ENT, \
    /*┌───────────┼──────────┼──────────┼─────────┼─────────┤          | */
        AU_TOG,       SAVE,       CUT,     COPY,    PASTE \
    /*└───────────┴──────────┴──────────┴─────────┴─────────┴──────────┘ */
    ),
        [_FPS] = LAYOUT(
    /*            ┌──────────┬──────────┬─────────┬─────────┬──────────┐ */
                     KC_ESC,     KC_Q,      KC_W,     KC_E,    KC_R, \
    /*            ├──────────┼──────────┼─────────┼─────────┼──────────┤ */
        TG(_KPAD),   KC_TAB,     KC_A,      KC_S,     KC_D,    KC_SPC, \
    /*┌───────────┼──────────┼──────────┼─────────┼─────────┤          | */
        KC_LSHIFT,    KC_Z,      KC_X,     KC_C,    KC_LCTL \
    /*└───────────┴──────────┴──────────┴─────────┴─────────┴──────────┘ */
    )
};


#ifdef ENCODER_ENABLE

    //Change Layer with encoder
    void encoder_update_user(uint8_t index, bool clockwise) {

        if (clockwise) {
            tap_code16(LCTL(KC_Y));
        } else {
            tap_code16(LCTL(KC_Z));
        }
                    //weirdly enough, this combination control the screen brightness level in OSX
            /*
            uint8_t current_layer;
            uint8_t next_layer;
            switch (mytoggle) {
            case BACKLIGHT:
                    if (clockwise) {tap_code16(BL_INC);}
                    else tap_code16(BL_DEC);
                break; */
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

}

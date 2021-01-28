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
#include "keymap_french.h"
#include "string.h"
#include "mylogo.h"

#ifdef ENCODER_ENABLE

    // encoder statre for function rotation
    enum custom_state {
        DEFAULT = 0,
        VOLUME,
        ZEEWHY
//        BACKLIGHT
        };

    static uint8_t mytoggle = DEFAULT;
#endif

static uint8_t strcount = 0;

#ifdef AUDIO_ENABLE
    #define KC_AUDIO AU_TOG
    float my_song[][2] = SONG(AG_NORM_SOUND);
    float my_song2[][2] = SONG(UNICODE_LINUX);
#else
    #define KC_AUDIO KC_NO
#endif

#ifdef RGBLIGHT_ENABLE
    #define  LGT_TOG    RGB_TOG
    #define  LGT_MOD    RGB_MOD
    #define  LGT_INC    RGB_VAI
    #define  LGT_DEC    RGB_SAI
#elif BACKLIGHT_ENABLE
    #define  LGT_TOG    BL_TOGG
    #define  LGT_MOD    BL_BRTG
    #define  LGT_INC    BL_INC
    #define  LGT_DEC    BL_DEC
#else
    #define  LGT_TOG    KC_NO
    #define  LGT_MOD    KC_NO
    #define  LGT_INC    KC_NO
    #define  LGT_DEC    KC_NO
#endif

#ifdef TAP_DANCE_ENABLE
    #define KC_RESET    TD(X_RESET)
    #define KC_COPY     TD(X_ALLCOPY)
    #define KC_SEGMENT  TD(X_SEGMENT)
    #define KC_FITT     TD(X_FITT)
    #define KC_ACC      TD(X_ACC)
    #define KC_PASTE    TD(X_COLLER)
    #define KC_TABUL    TD(X_TABUL)
    #define KC_ALIGN    TD(X_ALIGN)
    #define KC_BACKDL   TD(X_BCKDEL)
    #define KC_TRTY     TD(X_TRTY)
    #define KC_VIEW     TD(X_VIEW)
    #define KC_MENT     MT(MOD_LCTL, KC_ENT)
    #define KC_MSPC     MT(MOD_LCTL, KC_SPC)
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

static char *current_alpha_oled = "****";

    //tapdance  Keycode definition
    enum {
        X_RESET,
        X_ALLCOPY,
        X_SEGMENT,
        X_ACC,
        X_FITT,
        X_COLLER,
        X_TABUL,
        X_ALIGN,
        X_ECHAP,
        X_TRTY,
        X_VIEW,
        DEL_LINE,
    };

    uint8_t cur_dance(qk_tap_dance_state_t *state);
    uint8_t cpx_dance(qk_tap_dance_state_t *state);
    void x_finished(qk_tap_dance_state_t *state, void *user_data);
    void x_reset(qk_tap_dance_state_t *state, void *user_data);
    void paste_finished(qk_tap_dance_state_t *state, void *user_data);
    void paste_reset(qk_tap_dance_state_t *state, void *user_data);
    void seg_finished(qk_tap_dance_state_t *state, void *user_data);
    void seg_reset(qk_tap_dance_state_t *state, void *user_data);
    void fit_finished(qk_tap_dance_state_t *state, void *user_data);
    void fit_reset(qk_tap_dance_state_t *state, void *user_data);
    void acc_finished(qk_tap_dance_state_t *state, void *user_data);
    void acc_reset(qk_tap_dance_state_t *state, void *user_data);
    void esc_finished(qk_tap_dance_state_t *state, void *user_data);
    void esc_reset(qk_tap_dance_state_t *state, void *user_data);
    void align_finished(qk_tap_dance_state_t *state, void *user_data);
    void align_reset(qk_tap_dance_state_t *state, void *user_data);
    void view_finished(qk_tap_dance_state_t *state, void *user_data);
    void view_reset(qk_tap_dance_state_t *state, void *user_data);
    void trty_finished(qk_tap_dance_state_t *state, void *user_data);
    void trty_reset(qk_tap_dance_state_t *state, void *user_data);
    size_t strlen(const char *str);
#else
    #define KC_RESET RESET
    #define KC_COPY  COPY
    #define KC_ECHAP KC_NLCK
    #define KC_PASTE PASTE
    #define KC_TABUL KC_TAB
    #define KC_MENT  KC_ENT
    #define KC_MSPC  KC_SPC
#endif


// Defines names for use in layer keycodes and the keymap
enum custom_layers {
    _RVT = 0,
    _KPAD,
    _FN,
    _FPS
};

//uint8_t dancing = 0;
//static uint16_t key_timer;

// Defines and name the custom keycodes
enum custom_keycodes {
    RVT_VG = SAFE_RANGE,
    RVT_TG,
    RVT_TY,
    RVT_CAD,
    RVT_ME,
    SAVE,
    RVT_HIDE,
    CUT,
    COPY,
    PASTE,
    UNDO,
    REDO,
    SELECT,
    ENC_TG,
    TK_AUDIO
};

// Layers and keymaps

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_RVT] = LAYOUT(
    /*            ┌──────────┬──────────┬─────────┬─────────┬──────────┐ */
                     KC_ESC,  KC_SEGMENT, KC_FITT,  KC_ACC,    KC_DEL, \
    /*            ├──────────┼──────────┼─────────┼─────────┼──────────┤ */
         ENC_TG,    KC_TABUL,   KC_VIEW,  KC_TRTY,  KC_ALIGN,  KC_MENT, \
    /*┌───────────┼──────────┼──────────┼─────────┼─────────┤          | */
         RVT_ME,     KC_SPC,     CUT,     KC_COPY,  KC_PASTE  \
    /*└───────────┴──────────┴──────────┴─────────┴─────────┴──────────┘ */
    ), \
    [_KPAD] = LAYOUT(
    /*            ┌──────────┬──────────┬─────────┬─────────┬──────────┐ */
                     KC_ESC,    KC_P7,     KC_P8,    KC_P9,   KC_BSPC, \
    /*            ├──────────┼──────────┼─────────┼─────────┼──────────┤ */
         ENC_TG,     KC_TAB,    KC_P4,     KC_P5,    KC_P6,   KC_PENT, \
    /*┌───────────┼──────────┼──────────┼─────────┼─────────┤          | */
        KC_PDOT,    KC_P0,      KC_P1,     KC_P2,    KC_P3 \
    /*└───────────┴──────────┴──────────┴─────────┴─────────┴──────────┘ */
    ), \
    [_FN] = LAYOUT(
    /*            ┌──────────┬──────────┬─────────┬─────────┬──────────┐ */
                     KC_ESC,    KC_F13,    KC_F14,  KC_F15,    KC_F16, \
    /*            ├──────────┼──────────┼─────────┼─────────┼──────────┤ */
         ENC_TG,    LGT_TOG,   LGT_INC,   LGT_DEC,  LGT_MOD,   KC_ENT, \
    /*┌───────────┼──────────┼──────────┼─────────┼─────────┤          | */
        KC_AUDIO,     SAVE,       CUT,     COPY,    PASTE \
    /*└───────────┴──────────┴──────────┴─────────┴─────────┴──────────┘ */
    ), \
    [_FPS] = LAYOUT(
    /*            ┌──────────┬──────────┬─────────┬─────────┬──────────┐ */
                      KC_Q,      KC_W,      KC_E,    KC_R,      KC_M,  \
    /*            ├──────────┼──────────┼─────────┼─────────┼──────────┤ */
         ENC_TG,      KC_A,      KC_S,      KC_D,    KC_F,    KC_MSPC, \
    /*┌───────────┼──────────┼──────────┼─────────┼─────────┤          | */
        KC_LSHIFT,    KC_Z,      KC_X,      KC_C,    KC_V \
    /*└───────────┴──────────┴──────────┴─────────┴─────────┴──────────┘ */
    ) \
};

#ifdef OLED_DRIVER_ENABLE

    uint16_t oled_timer;

    //Main screen render definition
        void oled_render_layers(void){
            oled_write_P(PSTR("LAYER: "), false);
            switch (get_highest_layer(layer_state)) {
                case _FN:
                    oled_write_P(PSTR("FUNCTION\n"), false);
                    break;
                case _KPAD:
                    oled_write_P(PSTR("KEYPAD\n"), false);
                    break;
                case _RVT:
                    oled_write_P(PSTR("REVIT\n"), false);
                    break;
                case _FPS:
                    oled_write_P(PSTR("GAMING\n"), false);
                    break;
                default:
                    oled_write_P(PSTR("UNDEFINED\n"), false);
                    break;
            }
        }

        void oled_render_locks(void){
            led_t led_state = host_keyboard_led_state();
            oled_write_P(PSTR("LOCKS: "), false);
            oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false);
            oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);
            oled_write_P(led_state.scroll_lock ? PSTR("SCR \n") : PSTR("    \n"), false);
        }

        void oled_render_keys(void){
            unsigned int i;
            strcount = strlen(current_alpha_oled);
            oled_write_P(PSTR("["), false);
            oled_write(current_alpha_oled, false);
            if (strcount < 12){
                strcount = 12 - strcount;
                for(i = 0;i < strcount;i++) {
                    oled_write_char(' ',false);
                }
            }
            oled_write_P(PSTR("]"), false);
        }

    //undo redo logo render definition
        static void render_zeewye_logo(void) {
            oled_write_raw_P(zeewye_logo, sizeof(zeewye_logo));
        }

    //volume logo render definition
        static void render_volume_logo(void) {
            oled_write_raw_P(volume_logo, sizeof(volume_logo));
        }

    //backlight logo render definition
 /*     static void render_backlight_logo(void) {
            oled_write_raw_P(backlight_logo, sizeof(backlight_logo));
        }
 */

    //Oled Render routine
        void oled_task_user(void) {
             switch (mytoggle) {
                case VOLUME:
                    render_volume_logo();
                    break;
                case ZEEWHY:
                    render_zeewye_logo();
                    break;
//                case BACKLIGHT:
//                    render_backlight_logo();
                    break;
                default:
                    oled_render_layers();
                    oled_render_locks();
                    oled_render_keys();
                    break;
            }
        }
#endif


#ifdef ENCODER_ENABLE

    //Change Layer with encoder

    void encoder_update_user(uint8_t index, bool clockwise) {
        uint8_t current_layer;
        uint8_t next_layer;
        switch (mytoggle) {
            case VOLUME:
                if (clockwise) tap_code16(KC_VOLU);
                else tap_code16(KC_VOLD);
                break;
            case ZEEWHY:
                if (clockwise) tap_code16(LCTL(FR_Y));
                else tap_code16(LCTL(FR_Z));
                break;
/*             case BACKLIGHT:
                if (clockwise) {
                    backlight_increase();
                    }
                else backlight_decrease();
                break;
            //weirdly enough, this combination control the screen brightness level in OSX
            //  case BACKLIGHT:
            //        if (clockwise) {tap_code16(BL_INC);}
            //        else tap_code16(BL_DEC);
            //    break; */
            default:
                if (clockwise) {
                    current_layer = biton32(layer_state);
                    next_layer = current_layer+1;
                    if (next_layer > _FPS) {
                        dprintf("current layer: %u", current_layer);
                    } else {
                        layer_move(next_layer);
                        dprintf("current layer: %u", next_layer);
                        #ifdef AUDIO_ENABLE
                            PLAY_SONG(my_song);
                        #endif
                    }
                } else {  // unsigned int =>  no need to check if layer < 0
                    current_layer = biton32(layer_state);
                    next_layer = current_layer - 1;
                    dprintf("layer: %u", next_layer);
                    layer_move(next_layer);
                    #ifdef AUDIO_ENABLE
                        PLAY_SONG(my_song2);
                    #endif
                }
                break;
        }
    }

#endif

#ifdef TAP_DANCE_ENABLE
    //Tapdancing state definition
        uint8_t cur_dance(qk_tap_dance_state_t *state) {
                if (state->count == 1) {
                    if (state->interrupted || !state->pressed) return SINGLE_TAP;
                    else return SINGLE_HOLD;
                }
                else if (state->count == 2) {
                    // DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
                    // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
                    // keystrokes of the key, and not the 'double tap' action/macro.
                        if (state->interrupted) {
                            return DOUBLE_SINGLE_TAP;
                        }
                        else if (state->pressed) {
                            return DOUBLE_HOLD;
                        }
                        else {
                            return DOUBLE_TAP;
                        }
                    }
                else {
                    return 8;
                }
            }

        static tap xtap_state = {
        .is_press_action = true,
                .state = 0
        };

    //safe_reset force to press key multiple times to reset mcu
        void safe_reset(qk_tap_dance_state_t *state, void *user_data) {
            if (state->count == 1) {
                tap_code16(KC_DEL);
            }
            else if (state->count > 4) {
                reset_keyboard();
                reset_tap_dance(state);
            }
        }

    //Copy OR select all & copy
        void x_finished(qk_tap_dance_state_t *state, void *user_data) {
            xtap_state.state = cur_dance(state);
            //dancing = xtap_state.state;
            switch (xtap_state.state) {
                case SINGLE_TAP:
                    register_code(KC_LCTL);
                    register_code(FR_C);
                    current_alpha_oled = "COPY";
                    break;
                case SINGLE_HOLD:
                    register_code(KC_LCTL);
                    register_code(FR_A);
                    unregister_code(FR_A);
                    register_code(FR_C);
                    current_alpha_oled = "CPYA";
                    break;
            }
        }

        void x_reset(qk_tap_dance_state_t *state, void *user_data) {
            unregister_code(FR_C);
            unregister_code(KC_LCTL);
            switch (xtap_state.state) {
                case SINGLE_HOLD:
                    register_code(KC_ESC);
                    unregister_code(KC_ESC);
            }
            xtap_state.state = 0;
        }

    // Simple Paste, Paste with coordinates OR Copy and paste
        void paste_finished(qk_tap_dance_state_t *state, void *user_data) {
            xtap_state.state = cur_dance(state);
            switch (xtap_state.state) {
                case SINGLE_TAP:
                    register_code(KC_LCTL);
                    register_code(FR_V);
                    current_alpha_oled = "PASTE";
                    break;
                case SINGLE_HOLD:
                    register_code(KC_LCTL);
                    register_code(KC_LSFT);
                    register_code(FR_V);
                    current_alpha_oled = "PASTE ON LOC";
                    break;
                case DOUBLE_TAP:
                    register_code(FR_C);
                    unregister_code(FR_C);
                    register_code(FR_S);
                    unregister_code(FR_S);
                    current_alpha_oled = "DUPLICATE";
                    break;
            }
        }

        void paste_reset(qk_tap_dance_state_t *state, void *user_data) {
            switch (xtap_state.state) {
                case SINGLE_TAP:
                    unregister_code(FR_V);
                    unregister_code(KC_LCTL);
                    break;
                case SINGLE_HOLD:
                    unregister_code(FR_V);
                    unregister_code(KC_LSFT);
                    unregister_code(KC_LCTL);
                    break;
            }
        }


    // Pipe or Duct segment
        void seg_finished(qk_tap_dance_state_t *state, void *user_data) {
            xtap_state.state = cur_dance(state);
            switch (xtap_state.state) {
                case SINGLE_TAP:
                    register_code(FR_P);
                    unregister_code(FR_P);
                    register_code(FR_I);
                    unregister_code(FR_I);
                    current_alpha_oled = "PIPE";
                    break;
                case SINGLE_HOLD:
                    register_code(FR_D);
                    unregister_code(FR_D);
                    register_code(FR_T);
                    unregister_code(FR_T);
                    current_alpha_oled = "DUCT";
                    break;
            }
        }

        void seg_reset(qk_tap_dance_state_t *state, void *user_data) {
            xtap_state.state = 0;
        }

    // Pipe or Duct fitting
        void fit_finished(qk_tap_dance_state_t *state, void *user_data) {
            xtap_state.state = cur_dance(state);
            switch (xtap_state.state) {
                case SINGLE_TAP:
                    register_code(FR_P);
                    unregister_code(FR_P);
                    current_alpha_oled = "PIPE FIT";
                    break;
                case SINGLE_HOLD:
                    register_code(FR_D);
                    unregister_code(FR_D);
                    current_alpha_oled = "DUCT FIT";
                    break;
            }
        }

        void fit_reset(qk_tap_dance_state_t *state, void *user_data) {
            register_code(FR_F);
            unregister_code(FR_F);
            xtap_state.state = 0;
        }

    // Pipe or Duct accessories
        void acc_finished(qk_tap_dance_state_t *state, void *user_data) {
            xtap_state.state = cur_dance(state);
            switch (xtap_state.state) {
                case SINGLE_TAP:
                    register_code(FR_P);
                    unregister_code(FR_P);
                    current_alpha_oled = "PIPE ACC";
                    break;
                case SINGLE_HOLD:
                    register_code(FR_D);
                    unregister_code(FR_D);
                    current_alpha_oled = "DUCT ACC";
                    break;
            }
        }

        void acc_reset(qk_tap_dance_state_t *state, void *user_data) {
            register_code(FR_A);
            unregister_code(FR_A);
            xtap_state.state = 0;
        }

    //ALIGN or SLICE pipe or duct
        void align_finished(qk_tap_dance_state_t *state, void *user_data) {
            xtap_state.state = cur_dance(state);
            switch (xtap_state.state) {
                case SINGLE_TAP:
                    register_code(FR_A);
                    unregister_code(FR_A);
                    current_alpha_oled = "ALIGN";
                    break;
                case SINGLE_HOLD:
                    register_code(FR_S);
                    unregister_code(FR_S);
                    current_alpha_oled = "SLICE";
                    break;
            }
        }

        void align_reset(qk_tap_dance_state_t *state, void *user_data) {
            register_code(FR_L);
            unregister_code(FR_L);
            xtap_state.state = 0;
        }

    //Trim & Ajust  Angle or single element
        void trty_finished(qk_tap_dance_state_t *state, void *user_data) {
            xtap_state.state = cur_dance(state);
            register_code(FR_T);
            unregister_code(FR_T);
        }

        void trty_reset(qk_tap_dance_state_t *state, void *user_data) {
            switch (xtap_state.state) {
                case SINGLE_TAP:
                    register_code(FR_R);
                    unregister_code(FR_R);
                    current_alpha_oled = "ANGLE";
                    break;
                case SINGLE_HOLD:
                    register_code(FR_Y);
                    unregister_code(FR_Y);
                    current_alpha_oled = "SINGLE";
                    break;
            }
            xtap_state.state = 0;
        }


    // Visibility Keydance
        void view_finished(qk_tap_dance_state_t *state, void *user_data) {
            xtap_state.state = cur_dance(state);
            switch (xtap_state.state) {
                case SINGLE_TAP:
                    register_code(FR_V);
                    unregister_code(FR_V);
                    register_code(FR_G);
                    unregister_code(FR_G);
                    current_alpha_oled = "VISIBILITY";
                    break;
                case SINGLE_HOLD:
                    register_code(FR_B);
                    unregister_code(FR_B);
                    register_code(FR_X);
                    unregister_code(FR_X);
                    current_alpha_oled = "BOX VIEW";
                    break;
                case DOUBLE_TAP:
                    register_code(FR_W);
                    unregister_code(FR_W);
                    register_code(FR_T);
                    unregister_code(FR_T);
                    current_alpha_oled = "TILE VIEW";
                    break;
            }
        }

        void view_reset(qk_tap_dance_state_t *state, void *user_data) {
            xtap_state.state = 0;
        }



    /*   //makeshift function layer with esc key tapdancing
        void esc_finished(qk_tap_dance_state_t *state, void *user_data) {
            uint8_t current_layer;
            xtap_state.state = cur_dance(state);
            current_layer = biton32(layer_state);
            switch (xtap_state.state) {
                case SINGLE_TAP:
                    register_code(KC_ESC);
                    //if (mytoggle != DEFAULT) mytoggle = DEFAULT;
                    break;
                case SINGLE_HOLD:
                    if (mytoggle == DEFAULT) mytoggle = VOLUME;
                    break;
                case DOUBLE_TAP:
                    if (current_layer == _KPAD) register_code(KC_NLCK);
                    break;
                case DOUBLE_HOLD:
                    if (mytoggle == DEFAULT) mytoggle = ZEEWHY;
                    break;
            }
        }

        void esc_reset(qk_tap_dance_state_t *state, void *user_data) {
            uint8_t current_layer;
            switch (xtap_state.state) {
                case SINGLE_TAP:
                    unregister_code(KC_ESC);
                    break;
                case DOUBLE_TAP:
                    current_layer = biton32(layer_state);
                    if (current_layer == _KPAD) unregister_code(KC_NLCK);
                    break;
        #ifdef OLED_DRIVER_ENABLE
                default:
                    oled_clear();
                    break;
        #endif
            }
            mytoggle = DEFAULT;
            xtap_state.state = 0;
        }
    */


    //tap dancing actions enumerations
        qk_tap_dance_action_t tap_dance_actions[] = {
            [X_RESET] = ACTION_TAP_DANCE_FN(safe_reset),
            [X_ALLCOPY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished, x_reset),
            [X_SEGMENT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, seg_finished, seg_reset),
            [X_FITT] =  ACTION_TAP_DANCE_FN_ADVANCED(NULL, fit_finished, fit_reset),
            [X_ACC] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, acc_finished, acc_reset),
            [X_COLLER] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,paste_finished,paste_reset),
            [X_TABUL] = ACTION_TAP_DANCE_DOUBLE(KC_TAB, LSFT(KC_TAB)),
            [X_ALIGN] = ACTION_TAP_DANCE_FN_ADVANCED(NULL,align_finished,align_reset),
            [X_TRTY] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, trty_finished, trty_reset),
            [X_VIEW] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, view_finished, view_reset)
        };

#endif

//Callbacks

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static uint16_t my_revit_timer;
    uint8_t rgbmode;
    #ifdef CONSOLE_ENABLE
    uprintf("KL= kc: %u, col: %u, row: %u, pressed: %u\n", keycode, record->event.key.col, record->event.key.row, record->event.pressed);
    #endif
    switch (keycode) {
        case RVT_TG:
            if (record->event.pressed) {
                register_code(FR_T);
                unregister_code(FR_T);
                register_code(FR_G);
                unregister_code(FR_G);
                //current_alpha_oled = "TAG";
            }
            break;
        case RVT_ME:
            if (record->event.pressed) {
                my_revit_timer = timer_read();
                register_code(KC_LSFT);
            } else {
                unregister_code(KC_LSFT);
                if (timer_elapsed(my_revit_timer) < TAPPING_TERM) {
                    tap_code16(FR_M);
                    tap_code16(FR_E);
                    //current_alpha_oled = "MECH";
                }
            }
            break;
        case RVT_HIDE:
            if (record->event.pressed) {
                register_code(FR_H);
                unregister_code(FR_H);
                register_code(FR_H);
                unregister_code(FR_H);
                //current_alpha_oled = "HIDE";
            }
            break;
        case CUT:
            if (record->event.pressed) {
                tap_code16(LCTL(FR_X));
                //current_alpha_oled = "CUT";
            }
            break;
        case COPY:
            if (record->event.pressed) {
                tap_code16(LCTL(FR_C));
                //current_alpha_oled = "COPY";
            }
            break;
        case PASTE:
            if (record->event.pressed) {
                tap_code16(LCTL(FR_V));
                //current_alpha_oled = "PASTE";
            }
            break;
        case SAVE:
            if (record->event.pressed) {
                tap_code16(LCTL(FR_S));
                //current_alpha_oled = "SAVE";
            }
            break;
        case UNDO:
            if (record->event.pressed) {
                tap_code16(LCTL(FR_Z));
                //current_alpha_oled = "UNDO";
            }
            break;
        case REDO:
            if (record->event.pressed) {
                tap_code16(LCTL(FR_Y));
                //current_alpha_oled = "REDO";
            }
            break;
        case SELECT:
            if (record->event.pressed) {
                register_code(KC_LCTL);
                register_code(FR_A);
                unregister_code(FR_A);
                unregister_code(KC_LCTL);
                //current_alpha_oled = "SELECT ALL";
            }
            break;
        case DEL_LINE:
            if (record->event.pressed) {
                register_code(KC_LSFT);
                register_code(KC_HOME);
                unregister_code(KC_HOME);
                unregister_code(KC_LSFT);
                register_code(KC_DEL);
                unregister_code(KC_DEL);
                //current_alpha_oled = "DEL LINE";
            }
            break;
        case ENC_TG:
            if (record->event.pressed) {
                if(mytoggle < ZEEWHY) {
                    mytoggle = mytoggle +1;
                } else {
                    oled_clear();
                    mytoggle = DEFAULT;
                }
                //current_alpha_oled = "****";
            }
            break;
        case KC_ENT:
            if (record->event.pressed) {
                //current_alpha_oled = "ENTER";
            }
            break;
        case KC_DEL:
            if (record->event.pressed) {
                //current_alpha_oled = "DEL";
            }
            break;
        case LGT_MOD:
            rgbmode = rgblight_get_mode();
                    switch (rgbmode) {
                    case 1:{
                        current_alpha_oled = "STATIC";
                        break;
                    }
                    case 2:{
                        current_alpha_oled = "BREATHING";
                        break;
                    }
                    case 3:{
                        current_alpha_oled = "BREATHING + 1";
                        break;
                    }
                    case 4:{
                        current_alpha_oled = "BREATHING + 2";
                        break;
                    }
                    case 5:{
                        current_alpha_oled = "BREATHING + 3";
                        break;
                    }
                    case 6:{
                        current_alpha_oled = "RAINBOW_MOOD";
                        break;
                    }
                    case 7:{
                        current_alpha_oled = "RAINBOW_MOOD + 1";
                        break;
                    }
                    case 8:{
                        current_alpha_oled = "RAINBOW_MOOD + 2";
                        break;
                    }
                    case 9:{
                        current_alpha_oled = "SWIRL";
                        break;
                    }
                    case 10:{
                        current_alpha_oled = "SWIRL + 1";
                        break;
                    }
                    case 11:{
                        current_alpha_oled = "SWIRL + 2";
                        break;
                    }
                    case 12:{
                        current_alpha_oled = "SWIRL + 3";
                        break;
                    }
                    case 13:{
                        current_alpha_oled = "SWIRL + 4";
                        break;
                    }
                    case 14:{
                        current_alpha_oled = "SWIRL + 5";
                        break;
                    }
                    case 15:{
                        current_alpha_oled = "SNAKE";
                        break;
                    }
                    case 16:{
                        current_alpha_oled = "SNAKE +1";
                        break;
                    }
                    case 17:{
                        current_alpha_oled = "SNAKE +2";
                        break;
                    }
                    case 18:{
                        current_alpha_oled = "SNAKE +3";
                        break;
                    }
                    case 19:{
                        current_alpha_oled = "SNAKE +4";
                        break;
                    }
                    case 20:{
                        current_alpha_oled = "SNAKE +5";
                        break;
                    }
                    case 21:{
                        current_alpha_oled = "KNIGHT";
                        break;
                    }
                    case 22:{
                        current_alpha_oled = "KNIGHT +1";
                        break;
                    }
                    case 23:{
                        current_alpha_oled = "KNIGHT +2";
                        break;
                    }
                    case 24:{
                        current_alpha_oled = "CHRISTMAS";
                        break;
                    }
                    case 25:{
                        current_alpha_oled = "GRADIENT";
                        break;
                    }
                    case 26:{
                        current_alpha_oled = "GRADIENT + 1";
                        break;
                    }
                    case 27:{
                        current_alpha_oled = "GRADIENT + 2";
                        break;
                    }
                    case 28:{
                        current_alpha_oled = "GRADIENT + 3";
                        break;
                    }
                    case 29:{
                        current_alpha_oled = "GRADIENT + 4";
                        break;
                    }
                    case 30:{
                        current_alpha_oled = "GRADIENT + 5";
                        break;
                    }
                    case 31:{
                        current_alpha_oled = "GRADIENT + 6";
                        break;
                    }
                    case 32:{
                        current_alpha_oled = "GRADIENT + 7";
                        break;
                    }
                    case 33:{
                        current_alpha_oled = "GRADIENT + 8";
                        break;
                    }
                    case 34:{
                        current_alpha_oled = "GRADIENT + 9";
                        break;
                    }
                    case 35:{
                        current_alpha_oled = "RGB_TEST";
                        break;
                    }
                    case 36:{
                        current_alpha_oled = "ALTERNATING";
                        break;
                    }
                    case 37:{
                        current_alpha_oled = "TWINKLE";
                        break;
                    }
                    case 38:{
                        current_alpha_oled = "TWINKLE + 1";
                        break;
                    }
                    case 39:{
                        current_alpha_oled = "TWINKLE + 2";
                        break;
                    }
                    case 40:{
                        current_alpha_oled = "TWINKLE + 3";
                        break;
                    }
                    case 41:{
                        current_alpha_oled = "TWINKLE + 4";
                        break;
                    }
                    case 42:{
                        current_alpha_oled = "TWINKLE + 5";
                        break;
                    }
                }
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
    return;
}

void matrix_scan_user(void) {
    return;
}

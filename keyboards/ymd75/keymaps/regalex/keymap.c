#include "keymap.h"

uint16_t action_timer = 0;

#ifdef RGBLIGHT_ENABLE

    /***** rgblight_mode(mode)/rgblight_mode_noeeprom(mode) ****

    old mode number (before 0.6.117) to new mode name table

    |-----------------|-----------------------------------|
    | old mode number | new mode name                     |
    |-----------------|-----------------------------------|
    |        1        | RGBLIGHT_MODE_STATIC_LIGHT        |
    |        2        | RGBLIGHT_MODE_BREATHING           |
    |        3        | RGBLIGHT_MODE_BREATHING + 1       |
    |        4        | RGBLIGHT_MODE_BREATHING + 2       |
    |        5        | RGBLIGHT_MODE_BREATHING + 3       |
    |        6        | RGBLIGHT_MODE_RAINBOW_MOOD        |
    |        7        | RGBLIGHT_MODE_RAINBOW_MOOD + 1    |
    |        8        | RGBLIGHT_MODE_RAINBOW_MOOD + 2    |
    |        9        | RGBLIGHT_MODE_RAINBOW_SWIRL       |
    |       10        | RGBLIGHT_MODE_RAINBOW_SWIRL + 1   |
    |       11        | RGBLIGHT_MODE_RAINBOW_SWIRL + 2   |
    |       12        | RGBLIGHT_MODE_RAINBOW_SWIRL + 3   |
    |       13        | RGBLIGHT_MODE_RAINBOW_SWIRL + 4   |
    |       14        | RGBLIGHT_MODE_RAINBOW_SWIRL + 5   |
    |       15        | RGBLIGHT_MODE_SNAKE               |
    |       16        | RGBLIGHT_MODE_SNAKE + 1           |
    |       17        | RGBLIGHT_MODE_SNAKE + 2           |
    |       18        | RGBLIGHT_MODE_SNAKE + 3           |
    |       19        | RGBLIGHT_MODE_SNAKE + 4           |
    |       20        | RGBLIGHT_MODE_SNAKE + 5           |
    |       21        | RGBLIGHT_MODE_KNIGHT              |
    |       22        | RGBLIGHT_MODE_KNIGHT + 1          |
    |       23        | RGBLIGHT_MODE_KNIGHT + 2          |
    |       24        | RGBLIGHT_MODE_CHRISTMAS           |
    |       25        | RGBLIGHT_MODE_STATIC_GRADIENT     |
    |       26        | RGBLIGHT_MODE_STATIC_GRADIENT + 1 |
    |       27        | RGBLIGHT_MODE_STATIC_GRADIENT + 2 |
    |       28        | RGBLIGHT_MODE_STATIC_GRADIENT + 3 |
    |       29        | RGBLIGHT_MODE_STATIC_GRADIENT + 4 |
    |       30        | RGBLIGHT_MODE_STATIC_GRADIENT + 5 |
    |       31        | RGBLIGHT_MODE_STATIC_GRADIENT + 6 |
    |       32        | RGBLIGHT_MODE_STATIC_GRADIENT + 7 |
    |       33        | RGBLIGHT_MODE_STATIC_GRADIENT + 8 |
    |       34        | RGBLIGHT_MODE_STATIC_GRADIENT + 9 |
    |       35        | RGBLIGHT_MODE_RGB_TEST            |
    |       36        | RGBLIGHT_MODE_ALTERNATING         |
    |       37        | RGBLIGHT_MODE_TWINKLE             |
    |       38        | RGBLIGHT_MODE_TWINKLE + 1         |
    |       39        | RGBLIGHT_MODE_TWINKLE + 2         |
    |       40        | RGBLIGHT_MODE_TWINKLE + 3         |
    |       41        | RGBLIGHT_MODE_TWINKLE + 4         |
    |       42        | RGBLIGHT_MODE_TWINKLE + 5         |
    |-----------------|-----------------------------------|
    *****/
    uint32_t previous_mode = 1;
    uint32_t base_mode = 1; // Unlocked animation (solid)
    //uint32_t lock_mode = 36; // Locked animation (rainbowswirl + 5)
    bool rgb_enabled = true;

    // How long (in milliseconds) to wait between animation steps for each of the "Twinkle" animations
    //const uint8_t RGBLED_TWINKLE_INTERVALS[] PROGMEM = {50, 25, 10};

    const rgblight_segment_t PROGMEM my_capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
        {0, 3, HSV_GREEN},
        {11 , 3, HSV_GREEN}
    );

    const rgblight_segment_t PROGMEM my_function_layer[] = RGBLIGHT_LAYER_SEGMENTS(
        {7, 4, HSV_GOLD}
    );

    const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
        my_capslock_layer,
        my_function_layer
    );

#endif



const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* 0: Main Layer */
        [_MAIN] = LAYOUT_75_iso(
    /* ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐ */
          KC_ESC,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,  KC_PSCR,  KC_INS,   KC_DEL, \
    /* ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┤ */
          KC_GRV,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,    KC_MINS,  KC_EQL,       KC_BSPC,        KC_HOME, \
    /* ├─────────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬──────────────┼─────────┤ */
          KC_TAB,        KC_Q,      KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,   KC_LBRC,  KC_RBRC,                 KC_PGUP, \
    /* ├──────────────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬           ├─────────┤ */
          KC_CAPS,           KC_A,    KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,    KC_SCLN,  KC_QUOT,  KC_NUHS,    KC_ENT,   KC_PGDN, \
    /* ├───────────┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴─────────┴─┬─────────┼─────────┤ */
          KC_LSFT,   KC_NUBS,   KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,    KC_COMM,  KC_DOT,   KC_SLSH,      KC_RSFT,       KC_UP,   KC_END, \
	/* ├───────────┼─────────┴─┬───────┴───┬─────┴─────────┴─────────┴─────────┴─────────┴─────────┴───────┬─┴───────┬─┴───────┬─┴───────┬─────────┼─────────┼─────────┤ */
          KC_LCTL,    KC_LGUI,   KC_LALT,                                KC_SPC,                             KC_RALT,  MO(_FN),  KC_RCTL,  KC_LEFT,  KC_DOWN,  KC_RGHT
    /* └───────────┴───────────┴───────────┴───────────────────────────────────────────────────────────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘ */
        ),
	[_FN] = LAYOUT_75_iso(
	/* ┌─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┐ */
		 RGB_TOG,  RGB_MOD,  RGB_HUI,  RGB_HUD,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  XBX_SC,   XBX_VID,  P_MACRO,
	/* ├─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┼─────────┴─────────┼─────────┤ */
		 BL_TOGG,  BL_INC,   BL_DEC,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,       _______,       KC_MUTE,
	/* ├─────────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬────┴────┬──────────────┼─────────┤ */
		  _______,      _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,                 KC_VOLU,
	/* ├──────────────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬──────┴──┬           ├─────────┤ */
		 _______,          _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,   _______,   KC_VOLD,
	/* ├───────────┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴───┬─────┴─────────┴─┬─────────┼─────────┤ */
		 _______,    _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,      _______,      _______,  _______,
	/* ├───────────┼─────────┴─┬───────┴───┬─────┴─────────┴─────────┴─────────┴─────────┴─────────┴───────┬─┴───────┬─┴───────┬─┴───────┬─────────┼─────────┼─────────┤ */
		   RESET,    _______,    _______,                                TO(_GAMING),                       _______,   _______,  _______,  KC_MPRV,  KC_MPLY,  KC_MNXT
	/* └───────────┴───────────┴───────────┴───────────────────────────────────────────────────────────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┘ */
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
     if (record->event.pressed) {
        switch(keycode) {
            case P_MACRO:
                register_code(KC_NLCK);
                unregister_code(KC_NLCK);
                tap_code(KC_P7);
                tap_code(KC_P3);
                tap_code(KC_P6);
                tap_code(KC_P2);
                tap_code(KC_P8);
                tap_code(KC_P3);
                register_code(KC_NLCK);
                unregister_code(KC_NLCK);
                tap_code(KC_ENT);
                break;
            case XBX_VID:
                register_code(KC_LGUI);
                register_code(KC_LALT);
                register_code(KC_G);
                unregister_code(KC_G);
                unregister_code(KC_LALT);
                unregister_code(KC_LGUI);
                break;
            case XBX_SC:
                register_code(KC_LGUI);
                register_code(KC_LALT);
                register_code(KC_R);
                unregister_code(KC_R);
                unregister_code(KC_LALT);
                unregister_code(KC_LGUI);
                break;
            case RGB_MOD:
                previous_mode = rgblight_get_mode();
                break;
            case RGB_TOG:
                if (rgblight_get_mode() == false ) {
                    rgb_enabled = false;
                } else {
                    rgb_enabled = true;
                }
                break;
        }
    }
    return true;
}



layer_state_t layer_state_set_user(layer_state_t state) {
    uint8_t layer = biton32(state);
    // led_t led_state = host_keyboard_led_state();

    #ifdef RGBLIGHT_ENABLE
        // Both layers will light up if both kb layers are active
        rgblight_set_layer_state(1, layer_state_cmp(state, 1));
        rgblight_set_layer_state(2, layer_state_cmp(state, 2));
    #endif
    return state;
}

void keyboard_post_init_user(void) {
    // Enable the LED layers
    backlight_enable();
    backlight_level(11);
    #ifdef RGBLIGHT_ENABLE
        rgblight_enable();
        rgblight_layers = my_rgb_layers;
    #endif
}

bool led_update_user(led_t led_state) {
    #ifdef RGBLIGHT_ENABLE
        rgblight_set_layer_state(0, led_state.caps_lock);
    #endif
    return true;
}


#pragma once

/*OLED*/
#ifdef OLED_DRIVER_ENABLE
    #define OLED_DISPLAY_ADDRESS 0x3C
    #define OLED_TIMEOUT 60000
    //#define OLED_DISABLE_TIMEOUT
    #define SSD1306OLED
#endif

/*RGB*/
#ifdef RGBLIGHT_ENABLE
    #define RGB_DI_PIN F6
    #define RGBLED_NUM 7
    #define RGBLIGHT_HUE_STEP 8
    #define RGBLIGHT_SAT_STEP 8
    #define RGBLIGHT_EFFECT_KNIGHT
    #define RGBLIGHT_EFFECT_RAINBOW_MOOD
    #define RGBLIGHT_EFFECT_KNIGHT_LED_NUM 7
    #define RGBLIGHT_EFFECT_KNIGHT_LENGTH 2
#endif

/*Audio*/
#define C6_AUDIO

#ifdef AUDIO_ENABLE
    #define PITCH_STANDARD_A 432.0f
    #undef ZELDA_TREASURE
    #define ZELDA_TREASURE \
        Q__NOTE(_A4), \
        Q__NOTE(_AS4), \
        Q__NOTE(_B4), \
        HD_NOTE(_C5), \

    #undef STARTUP_SONG
    #define STARTUP_SONG SONG(ZELDA_TREASURE)
    #define NO_MUSIC_MODE
#endif
#define UNUSED_PINS

#define DEBOUNCE 5
#define TAPPING_TERM 200

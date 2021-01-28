#pragma once

/*RGB*/
#ifdef OLED_DRIVER_ENABLE
    #define RGB_DI_PIN F6
    #define RGBLED_NUM 7
    #define RGBLIGHT_HUE_STEP 8
    #define RGBLIGHT_SAT_STEP 8
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
    #define STARTUP_SONG SONG(ZELDA_TREASURE)
    #define NO_MUSIC_MODE
#endif

#define UNUSED_PINS

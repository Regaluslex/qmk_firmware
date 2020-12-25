# MCU name
MCU = atmega32u4

# Bootloader selection
#   Teensy       halfkay
#   Pro Micro    caterina
#   Atmel DFU    atmel-dfu
#   LUFA DFU     lufa-dfu
#   QMK DFU      qmk-dfu
#   ATmega32A    bootloadHID
#   ATmega328P   USBasp
BOOTLOADER = caterina

# Build Options
#   change yes to no to disable
#

BOOTMAGIC_ENABLE = no      # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = no       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = no            # USB Nkey Rollover
AUDIO_ENABLE = yes           # Audio output on port C6
FAUXCLICKY_ENABLE = no      # Use buzzer to emulate clicky switches
HD44780_ENABLE = no 		# Enable support for HD44780 based LCDs
RGBLIGHT_ENABLE = yes       # Enable keyboard RGB underglow
MIDI_ENABLE = no
#Hardware options
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
OLED_DRIVER_ENABLE = no   # Enables the use of OLED displays
ENCODER_ENABLE = yes       # ENables the use of one or more encoders
CONSOLE_ENABLE = no       # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
TAP_DANCE_ENABLE = yes
LEADER_ENABLE = no
STENO_ENABLE = no
TERMINAL_ENABLE = no
BLUETOOTH_ENABLE = no
UNICODEMAP_ENABLE = no
UNICODE_ENABLE = no
EXTRAFLAGS += -flto

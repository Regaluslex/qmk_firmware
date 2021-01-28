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
SLEEP_LED_ENABLE = yes       # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
NKRO_ENABLE = no            # USB Nkey Rollover

#Hardware options
HD44780_ENABLE = no 		# Enable support for HD44780 based LCDs
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


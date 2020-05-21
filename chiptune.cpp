/* A brief program that plays a pre-written chiptune on an ATtiny10.
 * The music is played with a piezoelectric sensor (buzzer).
 *
 * Fits into 1024 bytes of flash and 32 bytes of SRAM, so it should work on
 *   virtually any AVR microprocesor with the same architecture.
 *
 * References: ATtiny4/5/9/10 Datasheet and avr-libc Linux package
 * - http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-8127-AVR-8-bit-Microcontroller-ATtiny4-ATtiny5-ATtiny9-ATtiny10_Datasheet.pdf
 *
 * Author: Olivier Lesage
 */

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/pgmspace.h>
#include <util/atomic.h>
#if !defined(F_CPU)
#   define F_CPU 1000000UL  /* 1 MHz */
#endif
#include <util/delay.h>
#include "pitches.h"

// #define TIMER0_TOP 1023  /* 10-bit PWM */
#define TIMER0_TOP 65535 /* 16-bit PWM */
#define CLKDIV1    0b001 /* clk prescaler setting for clk/1 */
#define CLKDIV8    0b010 /* clk prescaler setting for clk/8 */
#define CLKDIV64   0b011 /* clk prescaler setting for clk/64 */
#define CLKDIV256  0b100 /* clk prescaler setting for clk/128 */
#define CLKDIV1024 0b101 /* clk prescaler setting for clk/1024 */

/* note/rest durations */
#define SIXTYFOURTH  1 << 0 /* 1 */
#define THIRTYSECOND 1 << 1 /* 2 */
#define SIXTEENTH    1 << 2 /* 4 */
#define EIGHT        1 << 3 /* 8 */
#define QUARTER      1 << 4 /* 16 */
#define HALF         1 << 5 /* 32 */
#define FULL         1 << 6 /* 64 */

/* note/rest durations when a fermata is present */
#define SIXTYFOURTH_F  0b10 << 0 /* ~1.5 */
#define THIRTYSECOND_F 0b11 << 0 /* 3 */
#define SIXTEENTH_F    0b11 << 1 /* 6 */
#define EIGHT_F        0b11 << 2 /* 12 */
#define QUARTER_F      0b11 << 3 /* 24 */
#define HALF_F         0b11 << 4 /* 48 */
#define FULL_F         0b11 << 5 /* 96 */

#define NUM_NOTES 21 /* --> EEPROM usage is three times this number in bytes */
#define Q_NOTE 864
#define F_NOTE 3456
#define SIXT_NOTE 216
#define SIXT_FR_NOTE 54 /* most important */

static bool sleeping = true; /* in SRAM */

/* music data stored in EEPROM. One bar is 4 quarter notes, or one whole note.*/
const unsigned char music[NUM_NOTES] PROGMEM = {
    NOTE_A3,  NOTE_G3, NOTE_A3,  REST,
    NOTE_G3,  NOTE_F3, NOTE_E3,  NOTE_D3,
    NOTE_CS2, REST,    NOTE_D3,  REST,
    NOTE_A2,  NOTE_G2, NOTE_A2,  REST,
    NOTE_E2,  NOTE_F2, NOTE_CS1, NOTE_D2,
    REST
};
const unsigned char durations[NUM_NOTES] PROGMEM = {
    THIRTYSECOND, THIRTYSECOND, THIRTYSECOND, THIRTYSECOND,
    SIXTYFOURTH,  SIXTYFOURTH,  SIXTYFOURTH,  SIXTYFOURTH,
    SIXTEENTH,    THIRTYSECOND, EIGHT,        EIGHT,
    THIRTYSECOND, THIRTYSECOND, THIRTYSECOND, THIRTYSECOND,
    THIRTYSECOND, THIRTYSECOND, THIRTYSECOND, EIGHT,
    EIGHT
};
const bool fermatas[NUM_NOTES] PROGMEM = {
    false, false, true,  false,
    false, false, false, false,
    false, false, false, true,
    false, false, true,  false,
    false, false, false, false,
    true
};

/* an isr that will be called when Timer 0 hits compare match A */
ISR(TIM0_COMPA_vect) {
    /* WIP */
}

/* an isr for timer overflows */
ISR(TIM0_OVF_vect) {
    /* WIP */
}

/* an isr for external interrupts. Triggered when the push-button is pressed. */
ISR(INT0_vect) {
    /* WIP */
    sleeping = false;
}

/* sets up all configuration bits on chip reset */
void init(void) {
    /* disable interrupts to guarantee atomic 16-bit operations */
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        /* Configure I/O pins */
        DDRB = 0b00000001; /* PB0 as output */
        PUEB = 0b00000100; /* enable pull-up on PB2 to make it an input */

        /* Configure external interrupt */
        EICRA = 0b00000011;  /* rising edge triggered interrupt */
        PCMSK = _BV(PCINT2); /* enable interrupts on PB2 */

        /* Configure clock calibration. Trims the internal RC oscillator. */
        OSCCAL = 118; /* WIP. See Section 18.9 */

        /* Configure 16-bit PWM in Fast PWM mode (section 12.9.3) */
        TCCR0A = _BV(WGM00) | _BV(WGM01) | _BV(COM0A0);
        TCCR0B = CLKDIV1024 | _BV(WGM02) | _BV(WGM03); /* 1MHz/1024 --> ~1KHz */
        OCR0A = 0; /* set pwm output to 0 */
    }
}

/* Uses delays to play a certain frequency for a certain time.
 * The length of a quarter note in Adagio is 60s / 70 BPM = ~~864ms
 * The length of a measure/whole note in 4/4 Adagio is 4*864 = 3.456s
 * Duration is expressed as a multiple of the 64th note, i.e. 1,2,4,..32,64
 */
void play_note(unsigned char frequency, unsigned char duration) {
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        OCR0A = (short) frequency; /* cast to short for 16-bit assignemnt */
        for (int i = 0; i < duration; i++) { /* delay to hold the frequency */
            _delay_ms(SIXT_FR_NOTE);
        }
    }
}

int main(void) {
    unsigned char i = 0;
    unsigned char note;
    unsigned char duration;

    init();

    while(1) {
        while(sleeping) sleep_mode(); /* sleep until button is pressed */

        for (i = 0; i < NUM_NOTES; i++) {
            /* play one note after the other */
            note = pgm_read_byte(&music[i]);
            duration = pgm_read_byte(&durations[i]);

            if (pgm_read_byte(&fermatas[i])) {
                switch(duration) {
                    case SIXTYFOURTH:
                        duration = SIXTYFOURTH_F;
                        break;
                    case THIRTYSECOND:
                        duration = THIRTYSECOND_F;
                        break;
                    case SIXTEENTH:
                        duration = SIXTEENTH_F;
                        break;
                    case EIGHT:
                        duration = EIGHT_F;
                        break;
                    case QUARTER:
                        duration = QUARTER_F;
                        break;
                    case HALF:
                        duration = HALF_F;
                        break;
                    case FULL:
                        duration = FULL_F;
                        break;
                }
            }
            play_note(note, duration);
            /* i = ++i % NUM_NOTES; */
        }

        sleeping = true; /* go back to sleep after playing the melody once */
    }

    return 0;
}

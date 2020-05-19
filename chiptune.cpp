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
#if defined(F_CPU)
#   define F_CPU 1000000UL  /* 1 MHz */
#endif
#include <util/delay.h>
#include "pitches.h"

enum { UP, DOWN };

#define TIMER0_TOP 1023  /* 10-bit PWM */
#define TIMER0_TOP 65535 /* 16-bit PWM */
#define CLKDIV1    0b001 /* clk prescaler setting for clk/1 */
#define CLKDIV8    0b010 /* clk prescaler setting for clk/8 */
#define CLKDIV64   0b011 /* clk prescaler setting for clk/64 */
#define CLKDIV256  0b100 /* clk prescaler setting for clk/128 */
#define CLKDIV1024 0b101 /* clk prescaler setting for clk/1024 */

#define NUM_NOTES 16
#define Q_NOTE 860
#define F_NOTE 3440

/* music data stored in EEPROM */
const unsigned char music[NUM_NOTES] PROGMEM = {
    NOTE_A3, NOTE_G3, NOTE_A3,  NOTE_G3,
    NOTE_F3, NOTE_E3, NOTE_D3,  NOTE_CS2,
    NOTE_D3, NOTE_A2, NOTE_G2,  NOTE_A2,
    NOTE_E2, NOTE_F2, NOTE_CS1, NOTE_D2,
}
const unsigned char durations[NUM_NOTES] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, /* WIP*/
    0x00, 0x00, 0x00, 0x00, /* WIP*/
    0x00, 0x00, 0x00, 0x00, /* WIP*/
    0x00, 0x00, 0x00, 0x00  /* WIP*/
}

/* an isr that will be called when Timer 0 hits compare match A */
ISR(TIM0_COMPA) {
    /* WIP */
}

/* sets up all configuration bits on chip reset */
void ioinit(void) {
    /* disable interrupts to guarantee atomic 16-bit operations */
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        /* Configure pins */
        DDRB = 0b0001 /* PB0 as output */

        /* Configure 16-bit PWM in Fast PWM mode (section 12.9.3) */
        TCCR0A = _BV(WGM00) | _BV(WGM01) | _BV(COM0A0);
        TCCR0B = CLKDIV1024 | _BV(WGM02) | _BV(WGM03); /* 1MHz/1024 --> ~1KHz */
        OCR0A = 0; /* set pwm output to 0 */
    }
}

/* Uses delays to play a certain frequency for a certain time.
 * The length of a quarter note in Adagio is 60s / 70 BPM = ~857ms
 * Duration is expressed as the division of the note, i.e. 1,2,4,8, or 16
 */
void play_note(unsigned char frequency, unsigned char duration) {
    ATOMIC_BLOCK(ATOMIC_FORCEON) {
        OCR0A = (short) frequency; /* cast to short for 16-bit assignemnt */
        _delay_ms(F_NOTE/duration) /* delay to hold the frequency */
    }
}

int main(void) {
    unsigned char i = 0;

    ioinit();

    /* play one note after the other, and immediately repeat. */
    while(1) {
        play_note(pgm_read_byte(&music[i]), pgm_read_byte(&durations[i]));
        i = ++i % NUM_NOTES;
    }

    for (;;) sleep_mode();

    return 0;
}

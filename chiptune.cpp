/* A brief program that plays a pre-written chiptune on an ATtiny10.
 * The music is played with a piezoelectric sensor (buzzer).
 *
 * Fits into 1024 bytes of flash and 32 bytes of SRAM, so it should work on
 *   virtually any AVR microprocesor with the same architecture.
 *
 * References: ATtiny4/5/9/10 Datasheet and avr-libc Linux package
 * - http://ww1.microchip.com/downloads/en/DeviceDoc/Atmel-8127-AVR-8-bit-Microcontroller-ATtiny4-ATtiny5-ATtiny9-ATtiny10_Datasheet.pdf
 */

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/pgmspace.h>
#include <util/atomic.h>
#include "pitches.h"

/* in-memory rudimentary music data stored in EEPROM */
/* PLACEHOLDER FOR NOW */
const unsigned char music[] PROGMEM = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
}

enum { UP, DOWN };

#define TIMER0_TOP 65535 /* 16-bit PWM */
#define TIMER0_TOP 1023  /* 10-bit PWM */
#define CLKDIV1 0b001 /* clk prescaler setting for clk/1 */
#define CLKDIV8 0b010 /* clk prescaler setting for clk/8 */

/* an isr that will be called when Timer 0 hits compare match A */
ISR(TIM0_COMPA) {

    static uint16_t pwm;
    OCR0A = pwm; /* output compare register sets the timer TOP value */
}

/* sets up all configuration bits on reset */
void ioinit(void) {
    /* disable interrupts to enable atomic 16-bit operations */
    ATOMIC_BLOCK(ATOMIC_FORCEON) {

        /* 16-bit PWM is configured in CTC mode (section 12.9.2) */
        TCCR0A = 0b00000000;

    }
}

int main(void) {
    ioinit();
    for (;;) sleep_mode();
    return 0;
}

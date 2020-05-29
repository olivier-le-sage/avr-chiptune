
#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>
#include <util/atomic.h>

int main (void) {
    OSCCAL = 118;
    DDRB = 1; // PB0 output
    TCCR0A = _BV(COM0A0) | _BV(WGM01);
    TCCR0B = _BV(CS00); // clk/1
    OCR0A = 0; // start pwm at max frequency

    for (;;) {
        ATOMIC_BLOCK(ATOMIC_FORCEON) {
            OCR0A += 10; // gradually bring the frequency down (by ++ing period)
        }
        _delay_ms(10);
    }
}

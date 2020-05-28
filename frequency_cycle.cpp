
#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>
#include <util/atomic.h>

int main (void) {
    OSCCAL = 118;
    DDRB = 1; // PB0 output
    TCCR0A = _BV(WGM00) | _BV(WGM01) | _BV(COM0A0);
    TCCR0B = _BV(CS02)  | _BV(WGM02) | _BV(WGM03);
    OCR0A = 0; // start pwm at max

    for (;;) {
        ATOMIC_BLOCK(ATOMIC_FORCEON) {
            OCR0A += 10; // gradually bring the frequency down
        }
        _delay_ms(10);
    }
}

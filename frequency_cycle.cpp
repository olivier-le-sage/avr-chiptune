
#include <inttypes.h>
#include <avr/io.h>
#include <util/delay.h>
#include <util/atomic.h>

#define CLKDIV1    0b001 /* clk prescaler setting for clk/1 */
#define CLKDIV8    0b010 /* clk prescaler setting for clk/8 */
#define CLKDIV64   0b011 /* clk prescaler setting for clk/64 */
#define CLKDIV256  0b100 /* clk prescaler setting for clk/256 */
#define CLKDIV1024 0b101 /* clk prescaler setting for clk/1024 */

int main (void) {
    OSCCAL = 118;
    DDRB = 1; // PB0 output
    TCCR0A = _BV(WGM00) | _BV(WGM01) | _BV(COM0A0);
    TCCR0B = CLKDIV64 | _BV(WGM02) | _BV(WGM03);
    OCR0A = 0; // start pwm at max frequency

    for (;;) {
        ATOMIC_BLOCK(ATOMIC_FORCEON) {
            OCR0A += 10; // gradually bring the frequency down (by ++ing period)
        }
        _delay_ms(500);
    }
}

#define F_CPU 1000000L
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
    DDRC = (1 << 4); // Use PC4 for output

    for (;;) {
        PORTC |= (1 << 4); // Turn it on
        _delay_ms(200);
        PORTC &= ~(1 << 4); // Turn it off
        _delay_ms(200);
    }

    return 0;
}


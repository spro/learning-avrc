#define F_CPU 1000000L
#include <avr/io.h>
#include <util/delay.h>

#define LED_PIN 4

int main(void) {
    DDRC = (1 << LED_PIN); // Use PC4 for output

    for (;;) {
        PORTC |= (1 << LED_PIN); // Turn it on
        _delay_ms(200);
        PORTC &= ~(1 << LED_PIN); // Turn it off
        _delay_ms(200);
    }

    return 0;
}


#define F_CPU 1000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

void delay_ms(int n) {
    while (n--) {
        _delay_ms(1);
    }
}

int blinklen = 100;

int main(void) {
    DDRB = 0xFF; // PORTB is output, all pins
    PORTB = 0x00; // Make pins low to start

    // Setup ADC
    ADMUX = (1 << REFS0) | (1 << MUX0) | (1 << MUX2); // Using ADC pin 5
    ADCSRA = (1 << ADPS0) | (1 << ADPS1); // Scale ADC clock to 1mhz / 8

    // Enable and start going
    ADCSRA |= (1 << ADIE) | (1 << ADATE); // Free Running mode
    ADCSRA |= (1 << ADEN) | (1 << ADSC);

    // Disable digital input on pin 5
    DIDR0 = (1 << ADC5D);

    sei();

    for (;;) {
        PORTB ^= 0xFF; // invert all the pins */
        delay_ms(blinklen); // wait some time */
    }
    return 0;
}

ISR(ADC_vect) {
    blinklen = ADCW; // Set blink time to analog read
}

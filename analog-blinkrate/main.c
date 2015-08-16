#define F_CPU 1000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define output_low(port, pin) port &= ~(1<<pin)
#define output_high(port, pin) port |= (1<<pin)
#define set_input(portdir, pin) portdir &= ~(1<<pin)
#define set_output(portdir, pin) portdir |= (1<<pin)

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
    ADMUX = (1 << REFS0) | (1 << MUX0) | (1 << MUX2);
    ADCSRA = (1 << ADPS0) | (1 << ADPS1); // 1m / 8

    // Enable and start going
    ADCSRA |= (1 << ADIE) | (1 << ADATE); // Free Running mode
    ADCSRA |= (1 << ADEN) | (1 << ADSC);

    // Disable digital
    DIDR0 = (1 << ADC5D);

    sei();

    for (;;) {
        PORTB ^= 0xFF; // invert all the pins */
        delay_ms(blinklen); // wait some time */
    }
    return 0;
}

ISR(ADC_vect) {
    blinklen = ADCW;
    //if (ADCW > 28) {
        //PORTB = 0xFF;
        //blinklen = 100;
    //} else {
        //PORTB = 0x00;
        //blinklen = 300;
    //}
    //ADCSRA |= (1 << ADSC);
}

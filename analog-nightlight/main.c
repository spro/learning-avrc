#define F_CPU 1000000L
#include <avr/io.h>
#include <avr/interrupt.h>

// Brightness levels
// I think 0 - 1023 is the range
#define BRI 800
#define MID 600
#define DRK 400
#define BLK 200

int main(void) {
    DDRB = (1 << 0) | (1 << 1) | (1 << 2); // LED output pins
    PORTB = 0x00; // LEDs off to start 

    // Setup ADC
    ADMUX = (1 << REFS0); // AVCC for reference
    ADMUX |= (1 << MUX0) | (1 << MUX2); // Use ADC pin 5 
    ADCSRA = (1 << ADPS0) | (1 << ADPS1); // Scale ADC freq to 1mhz / 8

    // Enable and start ADC
    ADCSRA |= (1 << ADIE) | (1 << ADATE); // Turn on interrupts and free running mode
    ADCSRA |= (1 << ADEN) | (1 << ADSC); // Enable and start ADC

    DIDR0 = (1 << ADC5D); // Disable digital input for pin 5

    sei(); // Set enable interrupts

    for (;;) { }
    return 0;
}

ISR(ADC_vect) {
    if (ADCW < BLK) {
        PORTB = 0b111; // All LEDs on
    } else if (ADCW < DRK) {
        PORTB = 0b011; // Both yellow LEDs on
    } else if (ADCW < MID) {
        PORTB = 0b010; // One yellow LED on
    } else if (ADCW < BRI) {
        PORTB = 0b100; // Red LED on
    } else {
        PORTB = 0x0; // All off
    }
}

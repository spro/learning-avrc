#define F_CPU 1000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Toggles the blue pin every 500ms, and toggles the green pin whenever the
// logic state of INT0 (PB2) is changed.

#define G_PIN 3
#define B_PIN 4

int main(void) {
    DDRB = (1 << G_PIN) | (1 << B_PIN); // Use green and blue pins for output

    GIMSK |= (1 << INT0); // Enable INT0
    MCUCR |= (1 << 0); // On logic change

    sei(); // Enable interrupts

    for (;;) {
        PORTB ^= (1 << B_PIN); // Toggle blue
        _delay_ms(500);
    }

    return 0;
}

// INT0 handler
ISR(INT0_vect) {
    PORTB ^= (1 << G_PIN); // Toggle green
}


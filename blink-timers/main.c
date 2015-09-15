#define F_CPU 1000000L
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

// Using 2 timers to blink 2 LEDs at different rates

#define G_PIN 3
#define B_PIN 4

#define POSTSCALE0 2
#define POSTSCALE1 1

int ti0 = 0;
int ti1 = 0;

// Compare match 0 routine to blink green
ISR(TIM0_COMPA_vect) {
    if (++ti0 == POSTSCALE0) {
        PORTB ^= (1 << G_PIN); // Toggle green
        ti0 = 0;
    }
}

// Compare match 1 routine to blink blue
ISR(TIM1_COMPA_vect) {
    if (++ti1 == POSTSCALE1) {
        PORTB ^= (1 << B_PIN); // Toggle blue
        ti1 = 0;
    }
}

int main(void) {
    DDRB = (1 << G_PIN) | (1 << B_PIN); // Use green and blue pins for output
    PORTB |= (1 << 2);

    TCCR0A = (1 << WGM01); // CTC: Clear timer on compare match 0A
    TCCR0B = (1 << CS02) | (1 << CS00); // Clock divide by 1024 (1mhz / 1024 = ?)
    OCR0A = 200; // Compare match 0A value

    TCCR1 = (1 << CTC1); // Clear timer on compare match 1C
    TCCR1 |= (1 << CS13) | (1 << CS11) | (1 << CS10); // Clock divide by 1024 (1mhz / 1024 = ?)
    OCR1C = 200; // Compare match 1C value, same as above

    TIMSK |= (1 << OCIE0A) | (1 << OCIE1A); // Enable timer 0 and 1 compare matches

    sei(); // Enable interrupts

    for (;;) {
        _delay_ms(500); // Do nothing
    }

    return 0;
}


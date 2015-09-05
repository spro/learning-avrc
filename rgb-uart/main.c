#define F_CPU 1000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include "softuart.h"

#define R_PIN 0
#define G_PIN 3
#define B_PIN 4

int main(void) {
    DDRB |= (1 << R_PIN) | (1 << G_PIN) | (1 << B_PIN); // Set RGB pins as output

    // Start softuart
    softuart_init();
    sei();

    for (;;) {
        // Read input character
        char c = softuart_getchar();

        // Interpret input character
        if (c == '0')
            PORTB = 0; // Clear
        else if (c == 'r')
            PORTB = (1 << R_PIN);
        else if (c == 'g')
            PORTB = (1 << G_PIN);
        else if (c == 'b')
            PORTB = (1 << B_PIN);
        else if (c == 'y')
            PORTB = (1 << R_PIN) | (1 << G_PIN);
        else if (c == 'p')
            PORTB = (1 << R_PIN) | (1 << B_PIN);
        else if (c == 'a')
            PORTB = (1 << G_PIN) | (1 << B_PIN);
        else if (c == 'w')
            PORTB = (1 << R_PIN) | (1 << G_PIN) | (1 << B_PIN);

    }

    return 0;
}


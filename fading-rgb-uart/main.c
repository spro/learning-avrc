#define F_CPU 1000000UL

#define R_PIN 0
#define G_PIN 3
#define B_PIN 4

#define R (1 << R_PIN)
#define G (1 << G_PIN)
#define B (1 << B_PIN)
#define W (R | G | B)
#define Y (R | G)
#define P (R | B)
#define A (G | B)

#include <avr/io.h>
#include <avr/interrupt.h>
#include "softuart.h"
#include "fading.h"

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
            pwmdown(PORTB); // Clear
        else if (c == 'r') {
            if (!(PORTB & R)) pwmup(R);
            if (PORTB & ~R) pwmdown(PORTB & ~R);
        }
        else if (c == 'g') {
            if (!(PORTB & G)) pwmup(G);
            if (PORTB & ~G) pwmdown(PORTB & ~G);
        }
        else if (c == 'b') {
            if (!(PORTB & B)) pwmup(B);
            if (PORTB & ~B) pwmdown(PORTB & ~B);
        }
        else if (c == 'y') {
            if (!(PORTB & Y)) pwmup(Y);
            else if (!(PORTB & R)) pwmup(R);
            else if (!(PORTB & G)) pwmup(G);
            if (PORTB & ~Y) pwmdown(PORTB & ~Y);
        }
        else if (c == 'p') {
            if (!(PORTB & P)) pwmup(P);
            else if (!(PORTB & R)) pwmup(R);
            else if (!(PORTB & B)) pwmup(B);
            if (PORTB & ~P) pwmdown(PORTB & ~P);
        }
        else if (c == 'a') {
            if (!(PORTB & A)) pwmup(A);
            else if (!(PORTB & B)) pwmup(B);
            else if (!(PORTB & G)) pwmup(G);
            if (PORTB & ~A) pwmdown(PORTB & ~A);
        }
        else if (c == 'w') {
            if (!(PORTB & W)) pwmup(W);
            else if (!(PORTB & Y)) pwmup(Y);
            else if (!(PORTB & P)) pwmup(P);
            else if (!(PORTB & A)) pwmup(A);
            else if (!(PORTB & R)) pwmup(R);
            else if (!(PORTB & G)) pwmup(G);
            else if (!(PORTB & B)) pwmup(B);
        }

    }

    return 0;
}


#define F_CPU 1000000L
#include <avr/io.h>
#include <util/delay.h>

#define R_PIN 0
#define G_PIN 1
#define B_PIN 4

int main(void) {
    DDRB = (1 << R_PIN) | (1 << G_PIN) | (1 << B_PIN); // Use RGB pins for output

    // Configure counter/timer0 for fast PWM on PB0 and PB1
    TCCR0A = 3<<COM0A0 | 3<<COM0B0 | 3<<WGM00;
    TCCR0B = 0<<WGM02 | 3<<CS00; // Optional; already set
    // Configure counter/timer1 for fast PWM on PB4
    GTCCR = 1<<PWM1B | 3<<COM1B0;
    TCCR1 = 3<<COM1A0 | 7<<CS10;

    // Stagger the starting values and directions to get a rainbow fading effect, starting with:
    // * R: 0 up
    // * G: 2/3 up
    // * B: 2/3 down

    int r = 0;
    char rd = 1;
    int g = 255*2/3;
    char gd = 1;
    int b = 255*2/3;
    char bd = 0;

    OCR0B = 255;
    OCR1B = 255;

    for (;;) {
        if (rd) {
            if (++r == 255) rd = 0;
        } else if (--r == 0) rd = 1;
        if (gd) {
            if (++g == 255) gd = 0;
        } else if (--g == 0) gd = 1;
        if (bd) {
            if (++b == 255) bd = 0;
        } else if (--b == 0) bd = 1;

        OCR0A = r;
        OCR0B = g;
        OCR1B = b;

        _delay_ms(10);
    }

    return 0;
}


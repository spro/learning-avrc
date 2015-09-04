#define F_CPU 16500000L
#include <avr/io.h>
#include <util/delay.h>

void delay_ms(int ms) {
    while (ms-- > 0)
        _delay_us(1);
}

int cycle = 5500; // Total period in us of one on -> off cycle of LED
float dd = 0.0015; // Increment of duty cycle (from 0.0 -> 1.0)

// Fade in
void pwmup(int pin) {
    pwm(pin, 1);
}

// Fade out
void pwmdown(int pin) {
    pwm(pin, 0);
}

// Fade in or out (dir == 1: in, 0: out)
void pwm(int pin, int dir) {
    float duty = 0.0;
    if (dir == 0) duty = 1.0;
    int going = 1;

    // Turn the light on for duty * cycle us and off for (1-duty) * cycle us
    while (going) {
        if (dir == 0) duty -= dd;
        else duty += dd;

        PORTB |= (1 << pin); // Turn it on
        delay_ms(cycle*duty);

        PORTB &= ~(1 << pin); // Turn it off
        delay_ms(cycle*(1-duty));

        // Stop at threshold
        if ((dir == 1) && (duty >= 0.999)) {
            going = 0; // Stop now
        }
        else if ((dir == 0) && (duty <= 0.001)) {
            going = 0; // Stop now
        }
    }

    // Leave pin in a final state
    if (dir == 1)
        PORTB |= (1 << pin); // Turn it on
    else
        PORTB &= ~(1 << pin); // Turn it off
}

int main(void) {
    DDRB = (1 << 0) | (1 << 3) | (1 << 4); // Use LED_PIN for output

    // Cycle green -> yellow -> red -> purple -> blue -> aque -> green

    PORTB |= (1 << 4); // Start green
    for (;;) {
        pwmup(0); // Fade in red (-> yellow)
        pwmdown(4); // Fade out green (-> red)
        pwmup(3); // Fade in blue (-> purple)
        pwmdown(0); // Fade out red (-> blue)
        pwmup(4); // Fade in green (-> aqua)
        pwmdown(3); // Fade out blue (-> green)
    }

    return 0;
}


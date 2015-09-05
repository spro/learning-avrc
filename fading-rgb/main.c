#define F_CPU 1000000L
#include <avr/io.h>
#include <util/delay.h>

#define R_PIN 0
#define G_PIN 1
#define B_PIN 4

void delay_ms(int ms) {
    while (ms-- > 0)
        _delay_us(1);
}

int cycle = 1000; // Total period in us of one on -> off cycle of LED
float dd = 0.00515; // Increment of duty cycle (from 0.0 -> 1.0)

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
        if ((dir == 1) && (duty >= 0.9999)) {
            going = 0; // Stop now
        }
        else if ((dir == 0) && (duty <= 0.0001)) {
            going = 0; // Stop now
        }
    }

    // Leave pin in a final state
    if (dir == 1)
        PORTB |= (1 << pin); // Turn it on
    else
        PORTB &= ~(1 << pin); // Turn it off
}

void blink(int pin) {
    PORTB ^= (1 << pin);
    _delay_ms(1000);
    PORTB ^= (1 << pin);
    _delay_ms(1000);
}

int main(void) {
    DDRB = (1 << R_PIN) | (1 << G_PIN) | (1 << B_PIN); // Use LED_PIN for output

    // Cycle green -> yellow -> red -> purple -> blue -> aque -> green

    blink(R_PIN);
    blink(G_PIN);
    blink(B_PIN);

    PORTB = (1 << G_PIN); // Start green

    for (;;) {
        pwmup(R_PIN); // Fade in red (-> yellow)
        pwmdown(G_PIN); // Fade out green (-> red)
        pwmup(B_PIN); // Fade in blue (-> purple)
        pwmdown(R_PIN); // Fade out red (-> blue)
        pwmup(G_PIN); // Fade in green (-> aqua)
        pwmdown(B_PIN); // Fade out blue (-> green)
    }

    return 0;
}


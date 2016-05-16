#define F_CPU 1000000L
#include <avr/io.h>
#include <util/delay.h>
#include <mirf.h>

void delay_ms(int ms) {
    while (ms-- > 0)
        _delay_us(1);
}

void blink(int pin, int n) {
    while (n--) {
        PORTB |= (1 << pin); // Turn it on
        _delay_ms(50);
        PORTB &= ~(1 << pin); // Turn it off
        _delay_ms(100);
    }
    _delay_ms(1000);
}

#define WAIT _delay_ms(1250)
#define LED_PIN 3

void setup_mirf() {
    spi_init();
    mirf_init();
    _delay_ms(50);
    mirf_config("testr", "other", 10, 2);
    _delay_ms(50);
}

static uint8_t buf[2] = {0x73, 0x70};

int main(void) {
    //DDRB = (1 << LED_PIN); // Use LED_PIN for output

    setup_mirf();

    uint8_t status = mirf_status();
    //blink(LED_PIN, status);

    for (;;) {

        mirf_send(buf, 2);
        _delay_ms(100);

        //PORTB |= (1 << LED_PIN);
        _delay_ms(100);
        //PORTB &= ~(1 << LED_PIN);
        _delay_ms(100);
    }

    return 0;
}


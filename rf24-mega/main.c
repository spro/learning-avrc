#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <mirf.h>
#include "softuart.h"
#include "nRF24L01.h"

void delay_ms(int ms) {
    while (ms-- > 0)
        _delay_us(1);
}

void blink(int pin, int n) {
    while (n--) {
        PORTB |= (1 << pin); // Turn it on
        _delay_ms(100);
        PORTB &= ~(1 << pin); // Turn it off
        _delay_ms(300);
    }
    _delay_ms(1000);
}

#define WAIT _delay_ms(200);
#define WAIT2 _delay_ms(50);
#define LED_PIN 6
#define led_on  {PORTD |=  (1 << LED_PIN);}
#define led_off {PORTD &= ~(1 << LED_PIN);}
#define blink {led_on WAIT led_off WAIT}
#define blink2 {led_on WAIT2 led_off WAIT2}

void setup_mirf() {
    DDRD |= (1 << LED_PIN);
    spi_init();
    mirf_init();
    mirf_config();

    blink
    blink
}

uint8_t buf[2];

void main_loop() {
    _delay_ms(500);
    uint8_t pktReceived = 0;
    while (1){
        blink
        pktReceived = mirf_data_ready();
        /* tie LED to CSN for diag */
        if (!pktReceived) {
            //blink2 blink2 blink blink2
            //_delay_ms(100);
            say("NO");
        } else {
            mirf_get_data(buf);
            mirf_CSN_lo;
            char st[100];
            sprintf(st, "got: %s\r\n", buf);
            say(st);
            mirf_CSN_hi;
        }
        _delay_ms(500);
        say(".");
    }
}

int say(char *s) {
    // Turn on UART
    softuart_init();
    softuart_turn_rx_off();
    sei(); 

    _delay_ms(100);
    softuart_puts(s); // Send reading to ESP
    _delay_ms(100);

    // Turn off UART
    cli();
}

static void
num2hexstr(uint8_t *num, uint8_t size, uint8_t *str, uint8_t len);

int main(void) {
    // Start softuart

    setup_mirf();
    mirf_set_TADDR("testr");
    mirf_set_RADDR("other");

    /* Read TX_ADDR */
    uint8_t str[10+1];
    uint8_t tx_addr_reg[5];
    mirf_read_register(TX_ADDR, tx_addr_reg, sizeof(tx_addr_reg));
    num2hexstr(tx_addr_reg, sizeof(tx_addr_reg), str, sizeof(str));

    say("\ntx:");
    say(str);

    //uint8_t rx_addr_reg[5];
    //mirf_read_register(RX_ADDR_P0, rx_addr_reg, sizeof(rx_addr_reg));
    //num2hexstr(rx_addr_reg, sizeof(rx_addr_reg), str, sizeof(str));

    //say("\nrx:");
    //say(str);
    say("\n");

    main_loop();

    for (;;) {
        //say("ok...\r\n");
        _delay_ms(100);
    }

    return 0;
}

static void
num2hexstr(uint8_t *num, uint8_t size, uint8_t *str, uint8_t len)
{
    const static uint8_t HEXADECIMAL_LOWER[] = "0123456789abcdef";
    
    uint8_t     tmp;                        /* temporaere variable fuer den num-array */
    uint8_t    *reverse = &(str[len - 1]);  /* pointer auf das letzte zeichen */
    uint16_t    i = 0;
    
    str[len - 1] = '\0';
    
    /* uebersetze array von 8-bit nummer in zwei zeichen pro nummer */
    for (i = 0; size > 0; i++, size--) {
        tmp = num[i];
        *--reverse = HEXADECIMAL_LOWER[tmp & 0x0f];
        tmp >>= 4;
        *--reverse = HEXADECIMAL_LOWER[tmp & 0x0f];
    }
    
    /* fuelle mit nullen auf am linken rand: ex. 000001234\0 */
    for (;i < len; i++) {
        *--reverse = '0';
    }
}

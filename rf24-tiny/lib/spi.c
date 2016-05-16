#include "spi.h"

/* slow down little bit if F_CPU is set to 8000000L */
#if F_CPU == 8000000L
#define MS 8
#else
#define MS 1
#endif

// SPI transfer 1 byte and return the result
uint8_t spi_transfer(uint8_t data) {
	_delay_us(MS);
	USIDR = data;
	USISR = _BV(USIOIF); // clear flag

	while ((USISR & _BV(USIOIF)) == 0) { // in three-wire mode USIOIF determines when the transfer is completed
		USICR = (1 << USIWM0) | (1 << USICS1) | (1 << USICLK) | (1 << USITC);
	}
	return USIDR;
}

// Write data using SPI
void spi_write_data(uint8_t * dataout, uint8_t len) {
	_delay_us(MS);
	uint8_t i;
	for (i = 0; i < len; i++) {
		spi_transfer(dataout[i]);
	}
}

// Read data using SPI
void spi_read_data(uint8_t * datain, uint8_t len) {
	_delay_us(MS);
	uint8_t i;
	for (i = 0; i < len; i++) {
		datain[i] = spi_transfer(0x00);
	}
}

// Initialise the SPI
void spi_init(void) {

#ifdef __AVR_ATtiny85__
	DDRB |= (1 << PB2); // SPI CLK
	DDRB |= (1 << PB1); // SPI DO
	DDRB &= ~(1 << PB0); // SPI DI
	PORTB |= (1 << PB0); // SPI DI
#endif

#ifdef __AVR_ATtiny84__
	DDRA |= (1<<PINA4); // SPI CLK
	DDRA |= (1<<PINA5);// SPI DO
	DDRA &= ~(1<<PINA6);// SPI DI
	PORTA |= (1<<PINA6);// SPI DI
#endif

#ifdef __AVR_ATtiny861A__
	/* USI selection register */
	USIPP = 0;
	DDRB |= (1<<PINB2); // SPI CLK
	DDRB |= (1<<PINB1);// SPI DO
	DDRB &= ~(1<<PINB0);// SPI DI
	PORTB |= (1<<PINB0);// SPI DI
#endif
}


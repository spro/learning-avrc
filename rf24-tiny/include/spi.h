#ifndef SETUP_H_
#define SETUP_H_

#include <avr/io.h>
#include <util/delay.h>
#include "util.h"

extern void spi_write_data(uint8_t * dataout, uint8_t len);
extern void spi_read_data(uint8_t * datain, uint8_t len);
extern uint8_t spi_transfer(uint8_t data);
extern void spi_init(void);

#endif /* SETUP_H_ */

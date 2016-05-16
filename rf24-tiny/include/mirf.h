/*
	Copyright (c) 2007 Stefan Engelke <mbox@stefanengelke.de>
	
	Permission is hereby granted, free of charge, to any person 
	obtaining a copy of this software and associated documentation 
	files (the "Software"), to deal in the Software without 
	restriction, including without limitation the rights to use, copy, 
	modify, merge, publish, distribute, sublicense, and/or sell copies 
	of the Software, and to permit persons to whom the Software is 
	furnished to do so, subject to the following conditions:
	
	The above copyright notice and this permission notice shall be 
	included in all copies or substantial portions of the Software.
	
	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
	EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
	MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
	NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
	WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER 
	DEALINGS IN THE SOFTWARE.
	
	$Id$
*/

#ifndef _MIRF_H_
#define _MIRF_H_

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


#include "util.h"
#include "spi.h"
#include "nRF24L01.h"

// Mirf settings
#define RXMODE 1
#define TXMODE 0

/* mask interrupts, enable crc16 */
#define mirf_CONFIG		( (1<<EN_CRC) | (1<<CRCO) | (1 << MASK_TX_DS) | (1 << MASK_RX_DR) | (1 << MASK_MAX_RT) )

// Pin definitions for chip select and chip enabled of the MiRF module
#ifdef __AVR_ATtiny85__
#define CE  PB3
#define CSN PB4
#endif // __AVR_ATtiny85__

#ifdef __AVR_ATtiny84__
#define CE  PB0
#define CSN PB1
#endif // __AVR_ATtiny84__

#ifdef __AVR_ATtiny861A__
#define CE PB4
#define CSN PB5
#endif

// Definitions for selecting and enabling MiRF module
#define mirf_CSN_hi	PORTB |=  (1<<CSN);
#define mirf_CSN_lo	PORTB &= ~(1<<CSN);
#define mirf_CE_hi	PORTB |=  (1<<CE);
#define mirf_CE_lo	PORTB &= ~(1<<CE);

// Public standard functions
extern void mirf_init(void);
extern void mirf_config(uint8_t * txaddr, uint8_t * rxaddr, uint8_t mirf_CH, uint8_t mirf_PAYLOAD);
extern void mirf_powerdown(void);
extern void mirf_flush_rx_tx(void);
extern uint8_t mirf_status(void);
extern void mirf_send(uint8_t * value, uint8_t len);
extern uint8_t mirf_data_ready(void);
extern uint8_t mirf_max_rt_reached(void);
extern void mirf_get_data(uint8_t * data, uint8_t mirf_PAYLOAD);

// Public extended functions
extern void mirf_config_register(uint8_t reg, uint8_t value);
extern void mirf_read_register(uint8_t reg, uint8_t * value, uint8_t len);
extern void mirf_write_register(uint8_t reg, uint8_t * value, uint8_t len);

#endif /* _MIRF_H_ */

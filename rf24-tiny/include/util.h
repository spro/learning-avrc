/*
 * util.h
 *
 *  Created on: Feb 1, 2014
 *      Author: dnezic
 */

#ifndef UTIL_H_
#define UTIL_H_

#ifndef boolean
typedef uint8_t boolean;
#endif
#ifndef bool
typedef uint8_t bool;
#endif
#ifndef byte
typedef uint8_t byte;
#endif

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

#define LOW 0
#define HIGH 1
#define false 0
#define true 1

#endif /* UTIL_H_ */

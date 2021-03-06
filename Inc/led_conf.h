/*
 * led_conf.h
 *
 *  Created on: 2 okt. 2017
 *      Author: ASW-MNO-Admin
 */

#include "stdint.h"

#ifndef LED_CONF_H_
#define LED_CONF_H_

/* Configure the number of Pixels used in your LED-strip */
#define NR_OF_PIXELS_IN_LED_STRIP 10

#define SPI_TIMEOUT
/*  */

uint8_t SPIBufGreen[9] = {
		0b11011011, /* G */
		0b01101101, /* G */
		0b10110110, /* G */
		0b10010010, /* R */
		0b01001001, /* R */
		0b00100100, /* R */
		0b10010010, /* B */
		0b01001001, /* B */
		0b00100100  /* B */
};

uint8_t SPIBufGreen50p[9] = {
		0b11010010, /* G */
		0b01001001, /* G */
		0b00100100, /* G */
		0b10010010, /* R */
		0b01001001, /* R */
		0b00100100, /* R */
		0b10010010, /* B */
		0b01001001, /* B */
		0b00100100  /* B */
};

uint8_t SPIBufRed[9] = {
		0b10010010, /* G */
		0b01001001, /* G */
		0b00100100, /* G */
		0b11011011, /* R */
		0b01101101, /* R */
		0b10110110, /* R */
		0b10010010, /* B */
		0b01001001, /* B */
		0b00100100  /* B */
};

uint8_t SPIBufBlue[9] = {
		0b10010010, /* G */
		0b01001001, /* G */
		0b00100100, /* G */
		0b10010010, /* R */
		0b01001001, /* R */
		0b00100100, /* R */
		0b11011011, /* B */
		0b01101101, /* B */
		0b10110110  /* B */
};

uint8_t SPIBufClear[9] = {
		0b10010010, /* G */
		0b01001001, /* G */
		0b00100100, /* G */
		0b10010010, /* R */
		0b01001001, /* R */
		0b00100100, /* R */
		0b10010010, /* B */
		0b01001001, /* B */
		0b00100100  /* B */
};

uint8_t SPIBufWhite[9] = {
		0b11011011, /* G */
		0b01101101, /* G */
		0b10110110, /* G */
		0b11011011, /* R */
		0b01101101, /* R */
		0b10110110, /* R */
		0b11011011, /* B */
		0b01101101, /* B */
		0b10110110  /* B */
};

uint8_t SPIBuf3White[27] = {
		0b11011011, /* G */
		0b01101101, /* G */
		0b10110110, /* G */
		0b11011011, /* R */
		0b01101101, /* R */
		0b10110110, /* R */
		0b11011011, /* B */
		0b01101101, /* B */
		0b10110110, /* B */
		0b11011011, /* G */
		0b01101101, /* G */
		0b10110110, /* G */
		0b11011011, /* R */
		0b01101101, /* R */
		0b10110110, /* R */
		0b11011011, /* B */
		0b01101101, /* B */
		0b10110110, /* B */
		0b11011011, /* G */
		0b01101101, /* G */
		0b10110110, /* G */
		0b11011011, /* R */
		0b01101101, /* R */
		0b10110110, /* R */
		0b11011011, /* B */
		0b01101101, /* B */
		0b10110110  /* B */
};


#define NROFSTATES 4

typedef enum
{
	RedState,
	GreenState,
	BlueState,
	OffState
} AllLEDStates;

#endif /* LED_CONF_H_ */

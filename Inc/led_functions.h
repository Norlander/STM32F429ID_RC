/*
 * led_functions.h
 *
 *  Created on: 2 okt. 2017
 *      Author: ASW-MNO-Admin
 */


#ifndef LED_FUNCTIONS_H_
#define LED_FUNCTIONS_H_

typedef enum
{
	RedState,
	GreenState,
	BlueState,
	OffState
} AllLEDStates;

#define NR_OF_PIXELS_IN_LED_STRIP 100
#define NROFSTATES 4
#define RGB_BUFFER_SIZE 9

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

uint8_t SPIBufReset = 0b1111101; // Reset package: Low voltage for 50us. 50us / 0.4us = 125bits of 0x0. --> 0b1111101.

void SetAllLedsColor(uint8_t *Color);
void SetAllLedsGreen();
void SetAllLeds10callsRed();
void SetAllLeds2();
void ClearAllLeds();
void LEDSiren();
//void SetAllLedsColor(uint8_t Color[9]);

#endif /* LED_FUNCTIONS_H_ */

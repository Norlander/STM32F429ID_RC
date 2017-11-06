/*
 * led_functions.c
 *
 *  Created on: 2 okt. 2017
 *      Author: ASW-MNO-Admin
 */


#include <stdint.h>
#include "stm32f4xx_hal.h"
#include "stm32f429i_discovery.h"
//#include "led_functions.h"

/* Configure the number of Pixels used in your LED-strip */
#define NR_OF_PIXELS_IN_LED_STRIP 100
#define SPI_TIMEOUT
#define NROFSTATES 4
#define RGB_BUFFER_SIZE 9

/*  */

extern SPI_HandleTypeDef hspi3;
extern uint8_t SPIBufRed[9];
extern uint8_t SPIBufGreen[9];
extern uint8_t SPIBufClear[9];
extern uint8_t SPIBufBlue[9];



void SetAllLeds10callsRed()
{
//	int i;
//	for (i = 0; i < NR_OF_PIXELS_IN_LED_STRIP; ++i) {
//		HAL_SPI_Transmit(hspi, pData, sizeof(pData), 10);
//	}
	HAL_SPI_Transmit(&hspi3, SPIBufRed, sizeof(SPIBufRed), 10);
	HAL_SPI_Transmit(&hspi3, SPIBufRed, sizeof(SPIBufRed), 10);
	HAL_SPI_Transmit(&hspi3, SPIBufRed, sizeof(SPIBufRed), 10);
	HAL_SPI_Transmit(&hspi3, SPIBufRed, sizeof(SPIBufRed), 10);
	HAL_SPI_Transmit(&hspi3, SPIBufRed, sizeof(SPIBufRed), 10);
	HAL_SPI_Transmit(&hspi3, SPIBufRed, sizeof(SPIBufRed), 10);
	HAL_SPI_Transmit(&hspi3, SPIBufRed, sizeof(SPIBufRed), 10);
	HAL_SPI_Transmit(&hspi3, SPIBufRed, sizeof(SPIBufRed), 10);
	HAL_SPI_Transmit(&hspi3, SPIBufRed, sizeof(SPIBufRed), 10);
	HAL_SPI_Transmit(&hspi3, SPIBufRed, sizeof(SPIBufRed), 10);
}

void SetAllLedsGreen()
{
	int i;
	for (i = 0; i < NR_OF_PIXELS_IN_LED_STRIP; ++i) {
		HAL_SPI_Transmit(&hspi3, SPIBufGreen, sizeof(SPIBufGreen), 10);
	}

}

void SetAllLedsBlue()
{
	int i;
	for (i = 0; i < NR_OF_PIXELS_IN_LED_STRIP; ++i) {
		HAL_SPI_Transmit(&hspi3, SPIBufBlue, sizeof(SPIBufBlue), 10);
	}

}

void SetAllLedsRed()
{
	int i;
	for (i = 0; i < NR_OF_PIXELS_IN_LED_STRIP; ++i) {
		HAL_SPI_Transmit(&hspi3, SPIBufRed, sizeof(SPIBufRed), 10);
	}

}

void ClearAllLeds()
{
	int i;
	for (i = 0; i < NR_OF_PIXELS_IN_LED_STRIP; ++i) {
		HAL_SPI_Transmit(&hspi3, SPIBufClear, 9, 10);
	}

}

void SetAllLedsColor(uint8_t *Color)
{
	int i;
	for (i = 0; i < NR_OF_PIXELS_IN_LED_STRIP; ++i) {
		HAL_SPI_Transmit(&hspi3, (uint8_t *) Color, RGB_BUFFER_SIZE, 10);
	}
}

void LEDSiren()
{
	int i, counter = 0;

	while(1)
	{
		while( 1 == BSP_PB_GetState(BUTTON_KEY) )
				{
					HAL_GPIO_DeInit(GPIOB, GPIO_PIN_4);
				}
		for (i = 0; i < NR_OF_PIXELS_IN_LED_STRIP; ++i) {

			if (counter == i)
			{
				HAL_SPI_Transmit(&hspi3, SPIBufRed, RGB_BUFFER_SIZE, 10);
			}
			else
			{
				HAL_SPI_Transmit(&hspi3, SPIBufClear, RGB_BUFFER_SIZE, 10);
			}
		}

		HAL_Delay(100);

		if (counter < 9) {
			counter++;
		}
		else
		{
			counter = 0;
		}
	}

}

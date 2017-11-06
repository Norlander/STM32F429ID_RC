/*
 * rc_low_level_config.c
 *
 *  Created on: 1 nov. 2017
 *      Author: ASW-MNO-Admin
 */

#include "rc_config.h"



/*	The following functions for the timer TIM4 are needed...
 *	This is under the assumption that two channels are used for rising resp. falling edge.
 *	That we use interrupts but not DMA.
 *
 *           + Time Input Capture Initialization
 *           	HAL_TIM_IC_Init()
 *           + Time Input Capture Channel Configuration
 *           	HAL_TIM_IC_ConfigChannel()
 *           + Time Slave synchronization
 *				HAL_TIM_SlaveConfigSynchronization()
 *           + Time Input Capture Start
 *           	Not relevant...
 *           + Time Input Capture Start Interruption
 *	           HAL_TIM_IC_Start_IT()
 *           + Time Input Capture Start DMA
 *           	Relevant?
 */

/* How does the RC-controller work?
 * Each of the three channels send out a pulse with a PWM duty-cycle between 1-2ms active length. 1.5ms means "neutral"
 *	 GAS / Throttle:
 * 		1ms Full speed forward (trigger in)
 * 		2m: Full speed backwards (trigger out)
 * 	TURN:
 * 		1ms: Maximum left turn
 * 		2ms: Maximum right turn
 * 	CH3:
 * 		Toggles between 1ms and 2 ms. Difficult to know which one it is... Need LED to indicate?
 * The signal has T= 21,47ms --> f= 46,59Hz
 *
 * If each signal can go between 1,0 --> 2,0ms then a desired resolution to be able to measure is perhaps 0,01ms.
 * In theory this would give [0, 100] steps on each channel, 50 in each direction.
 * Additionally the timer must be able to count for ~25ms before the counter overflows.
 * 	--> So the timer can be set to tick at 0,01ms --> f = 100 kHz
 * 	--> How many ticks for 25ms? 25ms / 0,01ms = 2500 ticks. Period = 2500!
 * 	How to obtain f = 100 kHz?
 * 	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4 --> APB1 fed with 45MHz. Then x2 multiplies for timers --> 90MHz
 * 	TIM_CLOCKDIVISION_DIVx does not seem to work for TIM4. Hence use prescaler instead.
 * 	90MHz / 100kHz --> 900. Prescaler = 899.
 */
uint32_t setup_RC_PWM_Input_timers(void)
{

	__HAL_RCC_TIM4_CLK_ENABLE();

	setup_TIM4_GPIO();

	HAL_NVIC_SetPriority(TIM4_IRQn, 0, 1);
	HAL_NVIC_EnableIRQ(TIM4_IRQn);

	TIM4Handle.Instance = TIM4;
	//TIM4Handle.Init.ClockDivision = TIM_CLOCKDIVISION_DIV4;	//CLOCKDIVISION IS NOT DOING SHIT ON TIM4...
	TIM4Handle.Init.CounterMode = TIM_COUNTERMODE_UP;
	TIM4Handle.Init.Period = 2499;
	TIM4Handle.Init.Prescaler = 899;

#ifdef TEST_TIME_BASE
	HAL_TIM_Base_Init(&TIM4Handle);
	HAL_TIM_Base_Start_IT(&TIM4Handle);
#endif //TEST_TIME_BASE

	HAL_TIM_IC_Init(&TIM4Handle);

	TIM4ICInitStruct.ICFilter = 0;
	TIM4ICInitStruct.ICPolarity = TIM_ICPOLARITY_RISING;
	TIM4ICInitStruct.ICPrescaler = TIM_ICPSC_DIV1;
	TIM4ICInitStruct.ICSelection = TIM_ICSELECTION_DIRECTTI;

	HAL_TIM_IC_ConfigChannel(&TIM4Handle, &TIM4ICInitStruct, TIM_CHANNEL_1);

	TIM4ICInitStruct.ICFilter = 0;
	TIM4ICInitStruct.ICPolarity = TIM_ICPOLARITY_FALLING;
	TIM4ICInitStruct.ICPrescaler = TIM_ICPSC_DIV1;
	TIM4ICInitStruct.ICSelection = TIM_ICSELECTION_INDIRECTTI;

	HAL_TIM_IC_ConfigChannel(&TIM4Handle, &TIM4ICInitStruct, TIM_CHANNEL_2);

	TIM4ICSlaveStruct.InputTrigger = TIM_TS_TI2FP2;
	TIM4ICSlaveStruct.SlaveMode = TIM_SLAVEMODE_RESET;

	HAL_TIM_SlaveConfigSynchronization_IT(&TIM4Handle, &TIM4ICSlaveStruct);

	HAL_TIM_IC_Start_IT(&TIM4Handle, TIM_CHANNEL_1);
	HAL_TIM_IC_Start_IT(&TIM4Handle, TIM_CHANNEL_2);

	return 0;

}

uint32_t setup_TIM4_GPIO(void) {
	__HAL_RCC_GPIOD_CLK_ENABLE();

	GPIO_InitTypeDef GPIOInitStruct;
	GPIOInitStruct.Speed = GPIO_SPEED_FAST;
	GPIOInitStruct.Mode = GPIO_MODE_AF_PP;
	GPIOInitStruct.Pin = GPIO_PIN_12;
	GPIOInitStruct.Pull = GPIO_NOPULL;
	GPIOInitStruct.Alternate = GPIO_AF2_TIM4;

	HAL_GPIO_Init(GPIOD, &GPIOInitStruct);
	return 0;
}

void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
//	  if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
//	  {
//	    /* Get the Input Capture value */
//	    uhIC2Value = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
//
//	    if (uhIC2Value != 0)
//	    {
//	      /* Duty cycle computation */
//	      uhDutyCycle = ((HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2)) * 100) / uhIC2Value;
//
//	      /* uwFrequency computation
//	      TIM4 counter clock = (RCC_Clocks.HCLK_Frequency)/2 */
//	      uwFrequency = (HAL_RCC_GetHCLKFreq())/2 / uhIC2Value;
//	    }
//	    else
//	    {
//	      uhDutyCycle = 0;
//	      uwFrequency = 0;
//	    }
//	  }
	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
	{
		u1Ch1Value = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_1);
	}

	if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
		{
		u1Ch2Value = HAL_TIM_ReadCapturedValue(htim, TIM_CHANNEL_2);
			uhDutyCycle = u1Ch2Value - u1Ch1Value;
		}
}

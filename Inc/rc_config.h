/*
 * rc_low_level_config.h
 *
 *  Created on: 1 nov. 2017
 *      Author: ASW-MNO-Admin
 */

#ifndef RC_CONFIG_H_
#define RC_CONFIG_H_

#include <stdint.h>
#include "stm32f4xx_hal.h"

TIM_HandleTypeDef TIM4Handle;
TIM_IC_InitTypeDef TIM4ICInitStruct;
TIM_SlaveConfigTypeDef TIM4ICSlaveStruct;

/* Captured Value */
__IO uint32_t            u1Ch1Value = 0;
__IO uint32_t            u2Ch1Value = 0;
__IO uint32_t            u1Ch2Value = 0;
__IO uint32_t            u2Ch2Value = 0;
/* Duty Cycle Value */
__IO uint32_t            uhDutyCycle = 0;
/* Frequency Value */
__IO uint32_t            uwFrequency = 0;

uint32_t setup_RC_PWM_Input_timers(void);
uint32_t setup_TIM4_GPIO(void);
#endif /* RC_CONFIG_H_ */

/*
 * stm32f407xx_RTC_driver.h
 *
 *  Created on: Feb 17, 2023
 *      Author: gianl
 */

#ifndef INC_STM32F407XX_RTC_DRIVER_H_
#define INC_STM32F407XX_RTC_DRIVER_H_

#include "stm32f407xx.h"


typedef struct
{
	uint8_t GPIO_PinNumber;
	uint8_t GPIO_PinMode;
	uint8_t GPIO_PinSpeed;
	uint8_t GPIO_pinPuPdControl;
	uint8_t GPIO_PinOPType;
	uint8_t GPIO_PinAltFunMode;

}RTC_PinConfig_t;






typedef struct
{
	RTC_RegDef_t *pRTCx;
	RTC_PinConfig_t RTC_PinConfig;

}RTC_Handler_t;

#endif /* INC_STM32F407XX_RTC_DRIVER_H_ */

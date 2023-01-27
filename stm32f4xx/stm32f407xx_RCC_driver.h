/*
 * stm32f407xx_RCC_driver.h
 *
 *  Created on: Jan 26, 2023
 *      Author: gianl
 */

#ifndef INC_STM32F407XX_RCC_DRIVER_H_
#define INC_STM32F407XX_RCC_DRIVER_H_

#include "stm32f407xx.h"


//this is a configureation structure  for a gpio pin
typedef struct
{
	uint32_t PLL_M;
	uint32_t PLL_N;
	uint32_t PLL_P;
	uint32_t PLL_Q;

}RCC_PinConfig_t;





//handler structure for a GPIO pin
typedef struct
{
	//pointer to hold the base address for the GPIO peripheral
	RCC_RegDef_t *pRCCx;
	RCC_PinConfig_t RCC_Config;

}RCC_Handler_t;

#define PLL_P_2		0
#define PLL_P_4		1
#define PLL_P_6		2
#define PLL_P_8		3

void PLL_Init(RCC_Handler_t *pRCCHandle);

#endif /* INC_STM32F407XX_RCC_DRIVER_H_ */

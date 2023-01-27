/*
 * stm32f407xx_RNG_driver.h
 *
 *  Created on: Jan 19, 2023
 *      Author: gianl
 */

#ifndef INC_STM32F407XX_RNG_DRIVER_H_
#define INC_STM32F407XX_RNG_DRIVER_H_

#include "stm32f407xx.h"

typedef struct
{
	uint8_t RNG_Interrupt;

}RNG_Config_t;

#define RNG_INTERRUPT_ENABLE		1
#define RNG_INTERRUPT_DISABLE		0

typedef struct
{
	RNG_RegDef_t *pRNGx;
	RNG_Config_t I2C_Config;
}RNG_Handle_t;

void RNG_PLCK_Control(uint8_t EnorDi);
uint32_t Random_Num(void);

#endif /* INC_STM32F407XX_RNG_DRIVER_H_ */

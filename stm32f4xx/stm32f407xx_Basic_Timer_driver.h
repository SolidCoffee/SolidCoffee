/* stm32f407xx_Basic_Timer_driver.h
 *
 *  Created on: Apr 5, 2022
 *      Author: gianl
 */

#ifndef INC_STM32F407XX_BASIC_TIMER_DRIVER_H_
#define INC_STM32F407XX_BASIC_TIMER_DRIVER_H_

#include "stm32f407xx.h"

typedef struct
{
	uint8_t Mode;
	uint8_t Buffer;
	uint16_t Prescaler;
	uint8_t Interrupt;
	uint8_t MMS;

}BasicTIM_PinConfig_t;

typedef struct
{
	//pointer to hold the base address for the GPIO peripheral
	BasicTIM_RegDef_t *pTIMx;
	BasicTIM_PinConfig_t TIM_Config;

}BasicTIM_Handler_t;

void BASIC_TIMCLKEnable(BasicTIM_RegDef_t *pTIMx, uint8_t EnorDi);
void BasicTIM_INIT(BasicTIM_Handler_t *pTIMHandle);
void TimerStart(BasicTIM_RegDef_t *pTIMx, uint32_t value);
void TimerStop(BasicTIM_RegDef_t *pTIMx);
//void SR_clearer(uint32_t Timer);
void SR_clearer(BasicTIM_RegDef_t *pTIMx);
void StopTimerDelay(BasicTIM_RegDef_t *pTIMx, uint32_t value);
uint32_t RunningTimerDelay(BasicTIM_RegDef_t *pTIMx, uint32_t value, uint8_t Clearer);

__attribute__((__common__)) uint32_t Running_timer_counter6;
__attribute__((__common__)) uint32_t Running_timer_counter7;


#endif /* INC_STM32F407XX_BASIC_TIMER_DRIVER_H_ */

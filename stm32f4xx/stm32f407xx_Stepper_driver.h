/*
 * stm32f407xx_Stepper_driver.h
 *
 *  Created on: Mar 7, 2022
 *      Author: gianl
 */

#ifndef INC_STM32F407XX_STEPPER_DRIVER_H_
#define INC_STM32F407XX_STEPPER_DRIVER_H_

#include "stm32f407xx.h"

void Stepperdelay(void);
void StepperStepsInc(uint32_t steps);
void StepperStepsDec(uint32_t steps);
void LeadStepsInc(uint32_t steps);
void LeadStepsDec(uint32_t steps);

#define BLUE 		10
#define RED			14
#define YELLOW		15
#define GREEN		12

#endif /* INC_STM32F407XX_STEPPER_DRIVER_H_ */

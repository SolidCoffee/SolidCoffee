/*
 * Microstepping.c
 *
 *  Created on: Nov 14, 2022
 *      Author: gianl
 */

#include "stm32f407xx.h"

int main(void)
{
	stepperInit();

	while(1)
	{

		if(RunningTimerDelay(TIM6,1000,RUN))  //800 seems to be best fastest. Probably ailiasing but IDK how
		{
			MicrostepsInc(50);
			RunningTimerDelay(TIM6,40,CLEAR);
		}







		/*StepperStepsInc(10);

		uint32_t waiter_seconds = RunningTimerDelay(TIM6,10000,RUN);

		if(waiter_seconds == 5)
		{
			StepperStepsDec(10);
			waiter_seconds = 0;
			RunningTimerDelay(TIM6, 10000, CLEAR);
		}*/
	}

}

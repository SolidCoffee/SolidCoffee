/*
 * Lead_Screw_Positioning.c
 *
 *  Created on: Mar 13, 2022
 *      Author: gianl
 */


#include "stm32f407xx.h"





void LeadScrew_GPIOInits(void)
{
	GPIO_Handler_t LeadPins;

	LeadPins.pGPIOx = GPIOB;

	LeadPins.GPIO_PinConfig.GPIO_PinMode = OUTPUT;
	LeadPins.GPIO_PinConfig.GPIO_PinAltFunMode = AF0;
	LeadPins.GPIO_PinConfig.GPIO_PinOPType = PUSHPULL;
	LeadPins.GPIO_PinConfig.GPIO_pinPuPdControl = PULLDOWN;
	LeadPins.GPIO_PinConfig.GPIO_PinSpeed = SPEEDHIGH;  //might need to look into this

	//PWM Pin config
	LeadPins.GPIO_PinConfig.GPIO_PinNumber = 10; //green=A-
	GPIO_Init(&LeadPins);

	LeadPins.GPIO_PinConfig.GPIO_PinNumber = 12; //Black=A+
	GPIO_Init(&LeadPins);

	LeadPins.GPIO_PinConfig.GPIO_PinNumber = 14;  //Red=B+
	GPIO_Init(&LeadPins);

	LeadPins.GPIO_PinConfig.GPIO_PinNumber = 15; //Blue=B-
	GPIO_Init(&LeadPins);
}


int main(void)
{
	LeadScrew_GPIOInits();

	while(1)
	{
		LeadStepsInc(1000);

		LeadStepsDec(1000);
	}

}

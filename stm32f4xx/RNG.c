/*
 * RNG.c
 *
 *  Created on: Jan 19, 2023
 *      Author: gianl
 */


#include "stm32f407xx.h"

void MCO1_GPIOInits(void)
{
	GPIO_Handler_t MCOPin;

	MCOPin.pGPIOx = GPIOA;

	MCOPin.GPIO_PinConfig.GPIO_PinMode = ALTFUNC;
	MCOPin.GPIO_PinConfig.GPIO_PinAltFunMode = AF0;
	MCOPin.GPIO_PinConfig.GPIO_PinOPType = PUSHPULL;
	MCOPin.GPIO_PinConfig.GPIO_pinPuPdControl = NOPUPD;
	MCOPin.GPIO_PinConfig.GPIO_PinSpeed = SPEEDHIGH;  //might need to look into this

	//PWM Pin config
	MCOPin.GPIO_PinConfig.GPIO_PinNumber = 8;//mid
	GPIO_Init(&MCOPin);
}

void RCC_PLL_Init(void)
{
	RCC_Handler_t PLLConfig;

	PLLConfig.pRCCx = RCC;

	PLLConfig.RCC_Config.PLL_M = 8;
	PLLConfig.RCC_Config.PLL_N = 158;
	PLLConfig.RCC_Config.PLL_P = PLL_P_2;
	PLLConfig.RCC_Config.PLL_Q = 7;

	PLL_Init(&PLLConfig);
}

int main(void)
{
	RCC_PLL_Init();
	RNG_PLCK_Control(ENABLE);
	lcd_init();
	//MCO1_GPIOInits();

	char str[10];

	//GPIO_WriteToOutputPin(GPIOA, 8, ENABLE);

	uint32_t Number = 0;
	while(1)
	{
		Number = Random_Num();

		sprintf(str, "%ld", Number);

		lcd_print_string(str);

		for(uint32_t i=0;i<1000000;i++);

		lcd_display_clear();
		for(uint32_t i=0;i<100000;i++);
	}

}

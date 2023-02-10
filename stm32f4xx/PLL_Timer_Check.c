/*
 * PLL_Timer_Check.c
 *
 *  Created on: Feb 3, 2023
 *      Author: gianl
 */


#include "stm32f407xx.h"

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

void Timer_init(void)
{
	BasicTIM_Handler_t LCD_timer;

	LCD_timer.pTIMx = TIM6;
	LCD_timer.TIM_Config.Buffer=0;
	LCD_timer.TIM_Config.Interrupt=0;
	LCD_timer.TIM_Config.MMS=2;
	LCD_timer.TIM_Config.Mode=0;
	LCD_timer.TIM_Config.Prescaler=16000-1;

	BASIC_TIMCLKEnable(TIM6, ENABLE);

	BasicTIM_INIT(&LCD_timer);

	StopTimerDelay(TIM6, 50000);
}

int main(void)
{
	RCC_PLL_Init();
	Timer_init();
	RNG_PLCK_Control(ENABLE);

	uint8_t Number = 0;

	while(1)
	{
		StopTimerDelay(TIM6, 5000);

		Number = Random_Num();
	}
}

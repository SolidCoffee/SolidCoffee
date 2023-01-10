/*
 * LCD.c
 *
 *  Created on: Jan 9, 2023
 *      Author: gianl
 */


#include "stm32f407xx.h"
void LCD_timer_init(void)
{
	BasicTIM_Handler_t LCD_timer;

	LCD_timer.pTIMx = TIM6;
	LCD_timer.TIM_Config.Buffer=0;
	LCD_timer.TIM_Config.Interrupt=0;
	LCD_timer.TIM_Config.MMS=2;
	LCD_timer.TIM_Config.Mode=0;
	LCD_timer.TIM_Config.Prescaler=1600-1;

	BASIC_TIMCLKEnable(TIM6, ENABLE);

	BasicTIM_INIT(&LCD_timer);
}



int main(void)
{




	while(1)
	{

	}

}

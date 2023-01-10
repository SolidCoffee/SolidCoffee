/*
 * stm32f407xx_LCD_driver.c
 *
 *  Created on: Jan 9, 2023
 *      Author: gianl
 */

#include "stm32f407xx_LCD_driver.h"

void lcd_init(void)
{
	//configure the gpio pins which are used for LCD connections
	GPIO_Handler_t lcd_signal;

	lcd_signal.pGPIOx = LCD_GPIO_PORT;
	lcd_signal.GPIO_PinConfig.GPIO_PinMode = OUTPUT;
	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_RS;
	lcd_signal.GPIO_PinConfig.GPIO_PinSpeed = FAST;
	lcd_signal.GPIO_PinConfig.GPIO_pinPuPdControl = NOPUPD;
	lcd_signal.GPIO_PinConfig.GPIO_PinOPType = PUSHPULL;
	GPIO_Init(&lcd_signal);

	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_RW;
	GPIO_Init(&lcd_signal);

	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_E;
	GPIO_Init(&lcd_signal);

	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D4;
	GPIO_Init(&lcd_signal);

	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D5;
	GPIO_Init(&lcd_signal);

	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D6;
	GPIO_Init(&lcd_signal);

	lcd_signal.GPIO_PinConfig.GPIO_PinNumber = LCD_GPIO_D7;
	GPIO_Init(&lcd_signal);

	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RS, DISABLE);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RW, DISABLE);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_E, DISABLE);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D4, DISABLE);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D5, DISABLE);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D6, DISABLE);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D7, DISABLE);


	//LCD initialization
	StopTimerDelay(TIM6, 500); // 50 ms > 40ms

	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RS, DISABLE);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_RW, DISABLE);

	Write_4_bits(LCD_4_BIT_FUNCTION_SET);

	StopTimerDelay(TIM6, 50); // 5 ms > 4.1 ms

	Write_4_bits(LCD_4_BIT_FUNCTION_SET);

	StopTimerDelay(TIM6, 2); // 200 microsecond > 100 microsecond

	Write_4_bits(LCD_4_BIT_FUNCTION_SET);

	Write_4_bits(0x2);



}

void Write_4_bits(uint8_t value)
{
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D4, (value >> 0)& 0x1);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D5, (value >> 1)& 0x1);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D6, (value >> 2)& 0x1);
	GPIO_WriteToOutputPin(LCD_GPIO_PORT, LCD_GPIO_D7, (value >> 3)& 0x1);
}

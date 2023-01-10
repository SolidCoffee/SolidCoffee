/*
 * LCD.h
 *
 *  Created on: Jan 9, 2023
 *      Author: gianl
 */

#ifndef INC_STM32F407XX_LCD_DRIVER_H_
#define INC_STM32F407XX_LCD_DRIVER_H_

#include "stm32f407xx.h"

#define LCD_GPIO_PORT	GPIOD
#define LCD_GPIO_RS		0
#define LCD_GPIO_RW		1
#define LCD_GPIO_E		2
#define LCD_GPIO_D4		3
#define LCD_GPIO_D5		4
#define LCD_GPIO_D6		5
#define LCD_GPIO_D7		6

#define LCD_4_BIT_FUNCTION_SET	3

void lcd_init(void);
void Write_4_bits(uint8_t value);


#endif /* INC_STM32F407XX_LCD_DRIVER_H_ */

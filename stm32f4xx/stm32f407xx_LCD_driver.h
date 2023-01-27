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
//#define LCD_CONTROL_PORT	GPIOB
#define LCD_GPIO_RS		0
#define LCD_GPIO_RW		1
#define LCD_GPIO_E		2
//#define LCD_GPIO_D0		0
//#define LCD_GPIO_D1		1
//#define LCD_GPIO_D2		2
//#define LCD_GPIO_D3		3
#define LCD_GPIO_D4		3
#define LCD_GPIO_D5		4
#define LCD_GPIO_D6		5
#define LCD_GPIO_D7		6

#define LCD_4_BIT_INIT	0x3
#define LCD_8_BIT_INIT	0x30

#define LCD_CMD_4DL_2N_5X8F		0x28
#define LCD_CMD_DON_CURON		0x0E
#define LCD_CMD_INCADD			0x06
#define LCD_CMD_ENTRY_SET		0x06
#define LCD_CMD_DIS_CLEAR		0x01
#define LCD_CMD_DIS_RETURN_HOME	0x02



void lcd_init(void);
void lcd_init_8_bit(void);
void lcd_print_data(uint8_t data);
void lcd_send_command(uint8_t cmd);
void lcd_display_clear(void);
void lcd_return_home(void);
void lcd_send_data_8_bit(uint8_t data);
void lcd_print_string(char *message);
void lcd_print_string_8_bit(char *message);
void lcd_send_string (char *str);

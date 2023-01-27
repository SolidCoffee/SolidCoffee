/*
 * LCD.c
 *
 *  Created on: Jan 9, 2023
 *      Author: gianl
 */


#include "stm32f407xx.h"



int main(void)
{
	lcd_init();

	char str[10];

	uint8_t num = 39;

	sprintf(str, "%d", num);

	lcd_print_string(str);

	while(1)
	{

	}

}

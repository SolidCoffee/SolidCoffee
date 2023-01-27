/*
 * stm32f407xx_RNG_driver.c
 *
 *  Created on: Jan 19, 2023
 *      Author: gianl
 */


#include "stm32f407xx_RNG_driver.h"

void RNG_PLCK_Control(uint8_t EnorDi)
{
	//RCC->CFGR |= (12 << 4);
	if(EnorDi){RNG_PLCK_EN();} else{RNG_PLCK_DI();}
}


uint32_t Random_Num(void)
{
	RNG1->CR |= (1 << 2);

	while(!(RNG1->SR & 0x01))
	{
		/*if(RNG1->SR | 0x01)
		{
			return 0;
		}*/

		RNG1->SR |= (1 << 0);
		RNG1->SR &= ~(1 << 5);
		//lcd_print_string("waiting");
	}

	return RNG1->DR;
}

/*
 * stm32f407xx_RCC_driver.c
 *
 *  Created on: Jan 26, 2023
 *      Author: gianl
 */


#include "stm32f407xx_RCC_driver.h"

void PLL_Init(RCC_Handler_t *pRCCHandle)
{
	pRCCHandle->pRCCx->PLLCFGR |= (pRCCHandle->RCC_Config.PLL_M << 0);
	pRCCHandle->pRCCx->PLLCFGR |= (pRCCHandle->RCC_Config.PLL_N << 6);
	pRCCHandle->pRCCx->PLLCFGR |= (pRCCHandle->RCC_Config.PLL_P << 16);
	pRCCHandle->pRCCx->PLLCFGR |= (pRCCHandle->RCC_Config.PLL_Q << 24);

	pRCCHandle->pRCCx->CR |= (1 << 24);

	while(!(pRCCHandle->pRCCx->CR & (1 << 24)));
}

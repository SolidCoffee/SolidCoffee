/*
 * stm32f407xx_Basic_Timer_driver.c
 *
 *  Created on: Apr 5, 2022
 *      Author: gianl
 */


#include "stm32f407xx_Basic_Timer_driver.h"

void BASIC_TIMCLKEnable(BasicTIM_RegDef_t *pTIMx, uint8_t EnorDi)
{
	RCC->AHB1ENR |= (1 << 0); // setting HSI on
	if(EnorDi == ENABLE)
	{
		if(pTIMx == TIM6)
		{
			TIM6_CLK_EN(); //Enabling the TIM3 peripheral clock
		}
		else if(pTIMx == TIM7)
		{
			TIM7_CLK_EN();
		}
	}
	else
	{
		if(pTIMx == TIM6)
		{
			TIM6_CLK_DI(); //Disabling the TIM3 peripheral clock
		}
		else if(pTIMx == TIM7)
		{
			TIM7_CLK_DI();
		}
	}
}

void BasicTIM_INIT(BasicTIM_Handler_t *pTIMHandle)
{
	pTIMHandle->pTIMx->CR1 |= (pTIMHandle->TIM_Config.Mode << 3);
	pTIMHandle->pTIMx->CR1 |= (pTIMHandle->TIM_Config.Buffer << 7);

	pTIMHandle->pTIMx->DIER |= (pTIMHandle->TIM_Config.Interrupt << 0);

	pTIMHandle->pTIMx->CR2 |= (pTIMHandle->TIM_Config.MMS << 4);

	pTIMHandle->pTIMx->PSC =pTIMHandle->TIM_Config.Prescaler;
}


void TimerStart(BasicTIM_RegDef_t *pTIMx, uint32_t value)
{
	pTIMx->ARR = value;
	pTIMx->CR1 |= (1 << 0);
}

void TimerStop(BasicTIM_RegDef_t *pTIMx)
{
	pTIMx->CR1 &= ~(1 << 0);
}

/*void SR_clearer(uint32_t Timer)
{
	if(Timer == 6)
	{
		TIM6->SR &= ~(1 << 0);
	}
	else if(Timer == 7)
	{
		TIM7->SR &= ~(1 << 0);
	}

}*/

void SR_clearer(BasicTIM_RegDef_t *pTIMx)
{
	pTIMx->SR &= ~(1 << 0);
}

/*void StopTimerDelay(BasicTIM_RegDef_t *pTIMx, uint32_t value)
{
	uint32_t clearer_flg=0;
	pTIMx->ARR &= ~(0xFFFF);
	pTIMx->ARR = value;
	pTIMx->CR1 |= (1 << 0);

	if(pTIMx == TIM6)
	{
		pTIMx->CNT = 0;
		SR_clearer(6);
		while(!TIM6->SR)
		{
			clearer_flg=1;
		}
	}
	else if(pTIMx == TIM7)
	{
		pTIMx->CNT = 0;
		SR_clearer(7);
		while(!TIM7->SR)
		{
			clearer_flg=1;
		}
	}

	if(clearer_flg)
	{
		if(pTIMx == TIM6)
		{
			pTIMx->CR1 &= ~(1 << 0);
			pTIMx->ARR &= ~(0xFFFF);
			pTIMx->CNT = 0;
			SR_clearer(6);
		}
		else if(pTIMx == TIM7)
		{
			pTIMx->CR1 &= ~(1 << 0);
			pTIMx->ARR &= ~(0xFFFF);
			pTIMx->CNT = 0;
			SR_clearer(7);
		}
		clearer_flg=0;
	}



}*/

void StopTimerDelay(BasicTIM_RegDef_t *pTIMx, uint32_t value)
{
	uint32_t clearer_flg=0;
	pTIMx->ARR &= ~(0xFFFF);
	pTIMx->ARR = value;
	pTIMx->CR1 |= (1 << 0);

	pTIMx->CNT = 0;
	SR_clearer(pTIMx);
	while(!pTIMx->SR)
	{
		clearer_flg=1;
	}

	if(clearer_flg)
	{
		pTIMx->CR1 &= ~(1 << 0);
		pTIMx->ARR &= ~(0xFFFF);
		pTIMx->CNT = 0;
		SR_clearer(pTIMx);
		clearer_flg=0;
	}
}

/*uint32_t RunningTimerDelay(BasicTIM_RegDef_t *pTIMx, uint32_t value, uint8_t Clearer)
{
	pTIMx->ARR = value;
	pTIMx->CR1 |= (1 << 0);


	if(pTIMx == TIM6)
	{
		//SR_clearer(6);
		if(Clearer)
		{
			Running_timer_counter6 = 0;
		}
		else if(TIM6->SR)
		{
			Running_timer_counter6++;
			SR_clearer(6);
		}
		return Running_timer_counter6;
	}
	else if(pTIMx == TIM7)
	{
		//SR_clearer(7);
		if(Clearer)
		{
			Running_timer_counter7 = 0;
		}
		else if(TIM6->SR)
		{
			Running_timer_counter7++;
			SR_clearer(7);
		}
		return Running_timer_counter7;
	}
	return 0;
}*/

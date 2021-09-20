
#include "stm32f407xx_timer.h"

void TIM_CLKEnable(TIM2_5_RegDef_t *pTIMx, uint8_t EnorDi)
{
	RCC->AHB1ENR |= (1 << 0); // setting HSI on
	if(EnorDi == ENABLE)
	{
		if(pTIMx == TIM3)
		{
			TIM3_CLK_EN(); //Enabling the TIM3 peripheral clock
		}
		else if(pTIMx == TIM4)
		{
			TIM4_CLK_EN();
		}
	}

}

void PWMInit(TIM_Handler_t *pTIMHandle)
{
	//CR1 peripheral setting
	uint32_t temp=0;

	pTIMHandle->pTIMx->CR1 |= (0 << 3); //clears the one pulse mode bit
	pTIMHandle->pTIMx->CR1 |= (pTIMHandle->TIM_Config.TIM_Mode << 5); //clears the one pulse mode bit
	pTIMHandle->pTIMx->CR1 |= (pTIMHandle->TIM_Config.TIM_Direction << 4); //sets direction
	pTIMHandle->pTIMx->CR1 |= (1 << 7); // ARR register is buffered

	//CCRM1
	temp |= (pTIMHandle->TIM_Config.PWM_Mode << 4);  //pwm mode config
	temp |= (1 << 3); //Preload register on TIMx_CCR1 enabled.
	pTIMHandle->pTIMx->CCMR1 = temp;

	//CCER
	temp=0;
	temp |= (pTIMHandle->TIM_Config.TIM_Polarity << 1);
	temp |= (1 << 0); //output enable
	pTIMHandle->pTIMx->CCER = temp;

	//Prescelar setting and ARR
	pTIMHandle->pTIMx->PSC = pTIMHandle->TIM_Config.TIM_Prescaler;
	pTIMHandle->pTIMx->ARR = pTIMHandle->TIM_Config.TIM_ARR;

	pTIMHandle->pTIMx->CCR1 = pTIMHandle->TIM_Config.TIM_DutyCycle;

	pTIMHandle->pTIMx->EGR |= (1 << 0);//enables the UG bit

	pTIMHandle->pTIMx->CR1 |= (1 << 0); //enables the Counter

}

void ServoAngle(TIM2_5_RegDef_t *pTIMx, uint32_t Angle)
{
	uint32_t DutyCycle = (Angle*1.188)+77;
	pTIMx->CCR1 = DutyCycle;
}

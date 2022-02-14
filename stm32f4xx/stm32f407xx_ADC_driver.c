#include "stm32f407xx_ADC_driver.h"

void delay2(void)
{
	for(uint32_t i = 0 ; i < 5000 ; i ++);
}

void ADC_Clk_EnorDi(ADC_RegDef_t *pADCx, uint8_t EnorDi)
{
	if(EnorDi==ENABLE)
	{
		if(pADCx == ADC1)
		{
			ADC1_CLK_EN();
		}
		else if(pADCx == ADC2)
		{
			ADC2_CLK_EN();
		}
		else if(pADCx == ADC3)
		{
			ADC3_CLK_EN();
		}
	}
	else if(EnorDi==DISABLE)
	{
		if(pADCx == ADC1)
		{
			ADC1_CLK_DI();
		}
		else if(pADCx == ADC2)
		{
			ADC2_CLK_DI();
		}
		else if(pADCx == ADC3)
		{
			ADC3_CLK_DI();
		}
	}
}


void ADC_Init(ADC_RegDef_t *pADCHandle) //example
{
	//Enable ADC
	pADCHandle->CR2 |= (1 << 0);

	//continous conversion setting
	pADCHandle->CR2 |= (1 << 1);

	//clearing channel
	pADCHandle->SQR3 &= ~(31 << 0);

	//Selecting channel
	pADCHandle->SQR3 |= (1 << 0);

	//cycle edit
	pADCHandle->SMPR2 |= (0 << 4);

	//resolution
	pADCHandle->CR1 |= (1 << 24);

	//start conversion of regular channels
	pADCHandle->CR2 |= (1 << 30);

	delay2();

	if(pADCHandle->DR > 600)
	{

	}
	else if(pADCHandle->DR < 500)
	{

	}
	//Disable ADC
	pADCHandle->CR2 &= ~(1 << 0);
}

void ADC_Init_LR(ADC_RegDef_t *pADCHandle)
{
	//Enable ADC
	pADCHandle->CR2 |= (1 << 0);

	//continous conversion setting
	pADCHandle->CR2 |= (1 << 1);

	//clearing channel
	pADCHandle->SQR3 &= ~(31 << 0);

	//Selecting channel
	pADCHandle->SQR3 |= (1 << 0);

	//cycle edit
	pADCHandle->SMPR2 |= (0 << 4);

	//resolution
	pADCHandle->CR1 |= (1 << 24);

	//start conversion of regular channels
	pADCHandle->CR2 |= (1 << 30);

	delay2();

	if(pADCHandle->DR > 700)
	{
		LR_Inc_Flg=1;
	}
	else if(pADCHandle->DR < 400)
	{
		LR_Dec_Flg=1;
	}
	//Disable ADC
	pADCHandle->CR2 &= ~(1 << 0);
}

void ADC_Init_UD(ADC_RegDef_t *pADCHandle)
{
	//Enable ADC
	pADCHandle->CR2 |= (1 << 0);

	//continous conversion setting
	pADCHandle->CR2 |= (1 << 1);

	//clearing channel
	pADCHandle->SQR3 &= ~(31 << 0);

	//Selecting channel
	pADCHandle->SQR3 |= (3 << 0);

	//cycle edit
	pADCHandle->SMPR2 |= (0 << 4);

	//resolution
	pADCHandle->CR1 |= (1 << 24);

	//start conversion of regular channels
	pADCHandle->CR2 |= (1 << 30);

	delay2();

	if(pADCHandle->DR > 700)
	{
		UD_Inc_Flg=1;
	}
	else if(pADCHandle->DR < 400)
	{
		UD_Dec_Flg=1;
	}
	//Disable ADC
	pADCHandle->CR2 &= ~(1 << 0);
}



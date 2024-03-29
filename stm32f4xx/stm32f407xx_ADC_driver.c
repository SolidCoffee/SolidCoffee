#include "stm32f407xx_ADC_driver.h"

void delay2(void)
{
	for(uint32_t i = 0 ; i < 25000 ; i ++);
}

void delay1(void)
{
	for(uint32_t i = 0 ; i < 13000 ; i ++);
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

	if(pADCHandle->DR > 900)
	{
		LR_Inc_Flg=1;
	}
	else if(pADCHandle->DR < 110)
	{
		LR_Dec_Flg=1;
	}
	else if((pADCHandle->DR < 400) && (pADCHandle->DR >= 200))
	{
		LR_Dec_Flg=1;
		delay1();
	}
	else if((pADCHandle->DR > 700) && (pADCHandle->DR <= 900))
	{
		LR_Inc_Flg=1;
		delay1();
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

	if(pADCHandle->DR > 900)
	{
		UD_Inc_Flg=1;
	}
	else if(pADCHandle->DR < 110)
	{
		UD_Dec_Flg=1;
	}
	else if((pADCHandle->DR < 400) && (pADCHandle->DR >= 200))
	{
		UD_Dec_Flg=1;
		delay1();
	}
	else if((pADCHandle->DR > 700) && (pADCHandle->DR <= 900))
	{
		UD_Inc_Flg=1;
		delay1();
	}
	//Disable ADC
	pADCHandle->CR2 &= ~(1 << 0);
}

void ADC_Top(ADC_RegDef_t *pADCHandle)
{
	//Enable ADC
	pADCHandle->CR2 |= (1 << 0);

	//continous conversion setting
	pADCHandle->CR2 |= (1 << 1);

	//clearing channel
	pADCHandle->SQR3 &= ~(31 << 0);

	//Selecting channel
	pADCHandle->SQR3 |= (5 << 0);

	//cycle edit
	pADCHandle->SMPR2 |= (0 << 4);

	//resolution
	pADCHandle->CR1 |= (1 << 24);

	//start conversion of regular channels
	pADCHandle->CR2 |= (1 << 30);

	delay2();

	if((pADCHandle->DR > 700) && (pADCHandle->DR <= 900))
	{
		Top_Inc_Flg=1;
		delay1();
	}
	else if((pADCHandle->DR < 400) && (pADCHandle->DR >= 200))
	{
		Top_Dec_Flg=1;
		delay1();
	}
	else if(pADCHandle->DR < 110)
	{
		Top_Dec_Flg=1;
	}
	else if(pADCHandle->DR > 900)
	{
		Top_Inc_Flg=1;
	}
	//Disable ADC
	pADCHandle->CR2 &= ~(1 << 0);
}

void ADC_Hand(ADC_RegDef_t *pADCHandle)
{
	//Enable ADC
	pADCHandle->CR2 |= (1 << 0);

	//continous conversion setting
	pADCHandle->CR2 |= (1 << 1);

	//clearing channel
	pADCHandle->SQR3 &= ~(31 << 0);

	//Selecting channel
	pADCHandle->SQR3 |= (7 << 0);

	//cycle edit
	pADCHandle->SMPR2 |= (0 << 4);

	//resolution
	pADCHandle->CR1 |= (1 << 24);

	//start conversion of regular channels
	pADCHandle->CR2 |= (1 << 30);

	delay2();

	if((pADCHandle->DR > 700) && (pADCHandle->DR <= 900))
	{
		Hand_Inc_Flg=1;
		delay1();
	}
	else if((pADCHandle->DR < 400) && (pADCHandle->DR >= 200))
	{
		Hand_Dec_Flg=1;
		delay1();
	}
	else if(pADCHandle->DR < 110)
	{
		Hand_Dec_Flg=1;
	}
	else if(pADCHandle->DR > 900)
	{
		Hand_Inc_Flg=1;
	}
	//Disable ADC
	pADCHandle->CR2 &= ~(1 << 0);
}

void ADC_Wrist(ADC_RegDef_t *pADCHandle)
{
	//Enable ADC
	pADCHandle->CR2 |= (1 << 0);

	//continous conversion setting
	pADCHandle->CR2 |= (1 << 1);

	//clearing channel
	pADCHandle->SQR3 &= ~(31 << 0);

	//Selecting channel
	pADCHandle->SQR3 |= (7 << 0);

	//cycle edit
	pADCHandle->SMPR2 |= (0 << 4);

	//resolution
	pADCHandle->CR1 |= (1 << 24);

	//start conversion of regular channels
	pADCHandle->CR2 |= (1 << 30);

	delay2();

	if((pADCHandle->DR > 700) && (pADCHandle->DR <= 900))
	{
		Wrist_Inc_Flg=1;
		delay1();
	}
	else if((pADCHandle->DR < 400) && (pADCHandle->DR >= 200))
	{
		Wrist_Dec_Flg=1;
		delay1();
	}
	else if(pADCHandle->DR < 110)
	{
		Wrist_Dec_Flg=1;
	}
	else if(pADCHandle->DR > 900)
	{
		Wrist_Inc_Flg=1;
	}
	//Disable ADC
	pADCHandle->CR2 &= ~(1 << 0);
}

uint32_t ADC_Read(ADC_RegDef_t *pADCHandle, uint8_t Channel)
{
	//Enable ADC
	pADCHandle->CR2 |= (1 << 0);

	//continous conversion setting
	pADCHandle->CR2 |= (1 << 1);

	//clearing channel
	pADCHandle->SQR3 &= ~(31 << 0);

	//Selecting channel
	pADCHandle->SQR3 |= (Channel << 0);

	//cycle edit
	pADCHandle->SMPR2 |= (0 << 4);

	//resolution
	pADCHandle->CR1 |= (1 << 24);

	//start conversion of regular channels
	pADCHandle->CR2 |= (1 << 30);

	delay2();


	return pADCHandle->DR;

	//Disable ADC
	pADCHandle->CR2 &= ~(1 << 0);
}

uint32_t EdgeCondition(uint32_t val, uint8_t Hand_or_No)
{
	if(Hand_or_No == NOTHAND)
	{
		if(val >= 180){val=180;}
		else if(val <= 10){val=10;}
	}
	else if(Hand_or_No == HAND)
	{
		if(val >= 100){val=100;}
		else if(val <= 30){val=30;}
	}
	return val;
}


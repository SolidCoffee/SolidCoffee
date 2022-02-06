#include "stm32f407xx.h"
#include "stm32f407xx_gpio_driver.h"
#include "stm32f407xx_timer.h"
#include "stm32f407xx_ADC_driver.h"
#include<stdio.h>
#include<string.h>

void delay2(void)
{
	for(uint32_t i = 0 ; i < 10000000 ; i ++);
}

void delay(void)
{
	for(uint32_t i = 0 ; i < 80000; i ++);
}

uint32_t x=10;
uint32_t y=10;

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

	if(pADCHandle->DR > 600)
	{
		x++;
		ServoAngle(TIM4, x, 2);
	}
	else if(pADCHandle->DR < 500)
	{
		x--;
		ServoAngle(TIM4, x, 2);
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

	if(pADCHandle->DR > 600)
	{
		y++;
		ServoAngle(TIM4, y, 1);
	}
	else if(pADCHandle->DR < 500)
	{
		y--;
		ServoAngle(TIM4, y, 1);
	}
	//Disable ADC
	pADCHandle->CR2 &= ~(1 << 0);
}

void GPIOInits(void)
{
	GPIO_Handler_t ADCPins;

	ADCPins.pGPIOx = GPIOA;

	ADCPins.GPIO_PinConfig.GPIO_PinMode = ANALOG;
	ADCPins.GPIO_PinConfig.GPIO_PinAltFunMode = AF0;
	ADCPins.GPIO_PinConfig.GPIO_PinOPType = PUSHPULL;
	ADCPins.GPIO_PinConfig.GPIO_pinPuPdControl = NOPUPD;
	ADCPins.GPIO_PinConfig.GPIO_PinSpeed = SPEEDHIGH;

	//PWM Pin config
	ADCPins.GPIO_PinConfig.GPIO_PinNumber = 1;
	GPIO_Init(&ADCPins);

	ADCPins.GPIO_PinConfig.GPIO_PinNumber = 3;
	GPIO_Init(&ADCPins);

	ADCPins.GPIO_PinConfig.GPIO_PinNumber = 5;
	ADCPins.GPIO_PinConfig.GPIO_PinMode = OUTPUT;
	GPIO_Init(&ADCPins);

	ADCPins.GPIO_PinConfig.GPIO_PinNumber = 7;
	ADCPins.GPIO_PinConfig.GPIO_PinMode = OUTPUT;
	GPIO_Init(&ADCPins);
}

void PWM_GPIOInits(void)
{
	GPIO_Handler_t PWMPins;

	PWMPins.pGPIOx = GPIOB;

	PWMPins.GPIO_PinConfig.GPIO_PinMode = ALTFUNC;
	PWMPins.GPIO_PinConfig.GPIO_PinAltFunMode = AF2;
	PWMPins.GPIO_PinConfig.GPIO_PinOPType = PUSHPULL;
	PWMPins.GPIO_PinConfig.GPIO_pinPuPdControl = NOPUPD;
	PWMPins.GPIO_PinConfig.GPIO_PinSpeed = SPEEDHIGH;  //might need to look into this

	//PWM Pin config
	PWMPins.GPIO_PinConfig.GPIO_PinNumber = 6;
	GPIO_Init(&PWMPins);

	PWMPins.GPIO_PinConfig.GPIO_PinNumber = 7;
	GPIO_Init(&PWMPins);

	PWMPins.GPIO_PinConfig.GPIO_PinNumber = 8;
	GPIO_Init(&PWMPins);
}

void PWMTIM(void)
{
	TIM_Handler_t TIMPWM;

	TIMPWM.pTIMx = TIM4;
	TIMPWM.TIM_Config.TIM_Direction = UPCNT;
	TIMPWM.TIM_Config.TIM_ARR = 479;
	TIMPWM.TIM_Config.TIM_Prescaler = 99;
	TIMPWM.TIM_Config.TIM_Mode = EDGE;
	TIMPWM.TIM_Config.PWM_Mode = PWM1;
	TIMPWM.TIM_Config.TIM_RestPostion = DISABLE;
	TIMPWM.TIM_Config.TIM_Polarity = POLHIGH;
	TIMPWM.TIM_Config.PWM_Channel = 1;

	PWM2_5_Init(&TIMPWM);

	TIMPWM.TIM_Config.PWM_Channel = 2;

	PWM2_5_Init(&TIMPWM);

	TIMPWM.TIM_Config.PWM_Channel = 3;

	PWM2_5_Init(&TIMPWM);
}

void GPIO_ButtonInit()
{
	GPIO_Handler_t GPIOBtn;

	GPIOBtn.pGPIOx = GPIOA;
	GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = 0;
	GPIOBtn.GPIO_PinConfig.GPIO_PinMode = INPUT;
	GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = SPEEDHIGH;
	GPIOBtn.GPIO_PinConfig.GPIO_pinPuPdControl =NOPUPD;

	GPIO_Init(&GPIOBtn);

}

int main(void)
{
	GPIOInits();
	ADC_Clk_EnorDi(ADC1, ENABLE);
	PWM_GPIOInits();
	TIM2_5_CLKEnable(TIM4, ENABLE); //Enables HSI and TIM3 peripheral clock

	GPIO_ButtonInit();

	PWMTIM();

	//delay2();
	while(1)
	{
		//ADC_Init_LR(ADC1);

		///ADC_Init_UD(ADC1);

		//ServoAngle(TIM4, 100, 3);
		//ServoAngle(TIM4, 100, 1);
		//ServoAngle(TIM4, 180, 2);
	}


	/*ServoAngle(TIM4, 100, 3);
	ServoAngle(TIM4, 10, 1);
	ServoAngle(TIM4, 180, 2);
	while(1)
		{
			for(uint32_t i = 15; i < 180; i++)
			{
				ServoAngle(TIM4, i, 1);
				ServoAngle(TIM4, i, 2);
				ServoAngle(TIM4, i, 3);
				delay();
			}
			for(uint32_t i = 180; i > 15; i--)
			{
				ServoAngle(TIM4, i, 1);
				ServoAngle(TIM4, i, 2);
				ServoAngle(TIM4, i, 3);
				delay();
			}
		}*/

	/*while(1)
	{
		ServoAngle(TIM4, 1, 1);
		while(! GPIO_ReadFromInputPin(GPIOA,0));
		delay();
		ServoAngle(TIM4, 270, 1);
		while(! GPIO_ReadFromInputPin(GPIOA,0));
		delay();
	}*/



}

/*while(1)
	{
		for(uint32_t i = 1; i < 270; i++)
		{
			ServoAngle(TIM4, i, 1);
			ServoAngle(TIM4, i, 2);
			delay();
		}
		for(uint32_t i = 270; i > 1; i--)
		{
			ServoAngle(TIM4, i, 1);
			ServoAngle(TIM4, i, 2);
			delay();
		}
	}*/

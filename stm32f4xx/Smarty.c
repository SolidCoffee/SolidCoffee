/*
 * Smarty.c
 *
 *  Created on: Mar 22, 2022
 *      Author: gianl
 */


#include "stm32f407xx.h"

void StartUpDelay(void)
{
	for(uint32_t i =0; i<90000;i++);
}

void TestDelay(void)
{
	for(uint32_t i =0; i<50000;i++);
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
	PWMPins.GPIO_PinConfig.GPIO_PinNumber = 6;//mid
	GPIO_Init(&PWMPins);

	PWMPins.GPIO_PinConfig.GPIO_PinNumber = 7; //bottom
	GPIO_Init(&PWMPins);

	PWMPins.GPIO_PinConfig.GPIO_PinNumber = 8;//top
	GPIO_Init(&PWMPins);

	PWMPins.GPIO_PinConfig.GPIO_PinNumber = 9;//grip
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

	TIMPWM.TIM_Config.PWM_Channel = 4;

	PWM2_5_Init(&TIMPWM);
}

void ServoBegin(void)
{
	for(uint32_t i=10; i<=70;i++)
	{
		ServoAngle(TIM4, i, MID);
		ServoAngle(TIM4, i, BOTTOM);
		ServoAngle(TIM4, i, TOP);
		ServoAngle(TIM4, i+20, GRIP);
		StartUpDelay();
	}
	for(uint32_t i=70; i>10;i--)
	{
		ServoAngle(TIM4, i, MID);
		ServoAngle(TIM4, i, BOTTOM);
		ServoAngle(TIM4, i, TOP);
		ServoAngle(TIM4, i+20, GRIP);
		StartUpDelay();
	}

}

int main(void)
{
	TIM2_5_CLKEnable(TIM4, ENABLE); //Enables HSI and TIM3 peripheral clock
	PWMTIM();
	for(uint32_t i=0;i<1000;i++);
	PWM_GPIOInits();


	//ServoBegin();

	while(1)
	{
		ServoAngle(TIM4, 50, MID);
		ServoAngle(TIM4, 50, BOTTOM);
		ServoAngle(TIM4, 100, TOP);
		ServoAngle(TIM4, 50, GRIP);

		for(uint32_t i=50;i < 150;i++)
		{
			ServoAngle(TIM4, i, MID);
			TestDelay();
		}
		for(uint32_t i=150;i >50;i--)
		{
			ServoAngle(TIM4, i, MID);
			TestDelay();
		}
	}
}

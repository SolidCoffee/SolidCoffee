/*
 * Microstepping.c
 *
 *  Created on: Nov 14, 2022
 *      Author: gianl
 */

#include "stm32f407xx.h"


void BasicTimer_init(void)
{
	BasicTIM_Handler_t TenMin;

	TenMin.pTIMx = TIM6;
	TenMin.TIM_Config.Buffer=0;
	TenMin.TIM_Config.Interrupt=0;
	TenMin.TIM_Config.MMS=2;
	TenMin.TIM_Config.Mode=0;
	TenMin.TIM_Config.Prescaler=1600-1;

	BASIC_TIMCLKEnable(TIM6, ENABLE);

	BasicTIM_INIT(&TenMin);

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

void LeadScrew_GPIOInits(void)
{
	GPIO_Handler_t LeadPins;

	LeadPins.pGPIOx = GPIOB;

	LeadPins.GPIO_PinConfig.GPIO_PinMode = OUTPUT;
	LeadPins.GPIO_PinConfig.GPIO_PinAltFunMode = AF0;
	LeadPins.GPIO_PinConfig.GPIO_PinOPType = PUSHPULL;
	LeadPins.GPIO_PinConfig.GPIO_pinPuPdControl = PULLDOWN;
	LeadPins.GPIO_PinConfig.GPIO_PinSpeed = SPEEDHIGH;  //might need to look into this

	//PWM Pin config
	LeadPins.GPIO_PinConfig.GPIO_PinNumber = 10; //green=A-
	GPIO_Init(&LeadPins);

	LeadPins.GPIO_PinConfig.GPIO_PinNumber = 12; //Black=A+
	GPIO_Init(&LeadPins);

	LeadPins.GPIO_PinConfig.GPIO_PinNumber = 14;  //Red=B+
	GPIO_Init(&LeadPins);

	LeadPins.GPIO_PinConfig.GPIO_PinNumber = 15; //Blue=B-
	GPIO_Init(&LeadPins);
}


int main(void)
{
	LeadScrew_GPIOInits();
	BasicTimer_init();

	while(1)
	{
		StepperStepsInc(10,Stepper_Stop_Code);

		uint32_t waiter_seconds = RunningTimerDelay(TIM6,10000);

		if(waiter_seconds == 10)
		{
			StepperStepsDec(10,Stepper_Stop_Code);
			waiter_seconds = 0;
		}
	}

}

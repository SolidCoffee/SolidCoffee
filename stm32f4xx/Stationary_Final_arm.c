/*
 * Stationary_Final_Arm.c
 *
 *  Created on: Mar 11, 2022
 *      Author: gianl
 */


#include "stm32f407xx.h"


uint32_t x=10;
uint32_t y=10;
uint32_t j=10;
uint32_t s=30;
uint32_t checker=0;

void StartUpDelay(void)
{
	for(uint32_t i =0; i<10000;i++);
}

void ServoHandle(void)
{

	if(UD_Inc_Flg)
	{
		x++;
		x=EdgeCondition(x,NOTHAND);
		ServoAngle(TIM4, x, MID);
	}
	else if(UD_Dec_Flg)
	{
		x--;
		x=EdgeCondition(x,NOTHAND);
		ServoAngle(TIM4, x, MID);
	}
	UD_Inc_Flg=0; UD_Dec_Flg=0;

	if(LR_Inc_Flg)
	{
		y++;
		y=EdgeCondition(y,NOTHAND);
		ServoAngle(TIM4, y, BOTTOM);
	}
	else if(LR_Dec_Flg)
	{
		y--;
		y=EdgeCondition(y,NOTHAND);
		ServoAngle(TIM4, y, BOTTOM);
	}
	LR_Inc_Flg=0; LR_Dec_Flg=0;

	if(Top_Inc_Flg)
	{
		j++;
		j=EdgeCondition(j,NOTHAND);
		ServoAngle(TIM4, j,TOP);
	}
	else if(Top_Dec_Flg)
	{
		j--;
		j=EdgeCondition(j,NOTHAND);
		ServoAngle(TIM4, j,TOP);
	}
	Top_Inc_Flg=0; Top_Dec_Flg=0;
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
	ADCPins.GPIO_PinConfig.GPIO_PinNumber = 1;//bottom control
	GPIO_Init(&ADCPins);

	ADCPins.GPIO_PinConfig.GPIO_PinNumber = 3;//mid control
	GPIO_Init(&ADCPins);

	ADCPins.GPIO_PinConfig.GPIO_PinNumber = 5;//top control
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
	PWMPins.GPIO_PinConfig.GPIO_PinNumber = 6;//mid
	GPIO_Init(&PWMPins);

	PWMPins.GPIO_PinConfig.GPIO_PinNumber = 7; //bottom
	GPIO_Init(&PWMPins);

	PWMPins.GPIO_PinConfig.GPIO_PinNumber = 8;//top
	GPIO_Init(&PWMPins);

	PWMPins.GPIO_PinConfig.GPIO_PinNumber = 9;//grip
	GPIO_Init(&PWMPins);
}

void Button_GPIOInits(void)
{
	GPIO_Handler_t ButtonPins;

	ButtonPins.pGPIOx = GPIOB;

	ButtonPins.GPIO_PinConfig.GPIO_PinMode = OUTPUT;
	ButtonPins.GPIO_PinConfig.GPIO_PinAltFunMode = AF0;
	ButtonPins.GPIO_PinConfig.GPIO_PinOPType = PUSHPULL;
	ButtonPins.GPIO_PinConfig.GPIO_pinPuPdControl = PULLDOWN;
	ButtonPins.GPIO_PinConfig.GPIO_PinSpeed = SPEEDHIGH;  //might need to look into this


	ButtonPins.GPIO_PinConfig.GPIO_PinNumber = 11;
	GPIO_Init(&ButtonPins);

	ButtonPins.GPIO_PinConfig.GPIO_PinNumber = 13;
	GPIO_Init(&ButtonPins);
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

void ButtonHandle(void)
{
	uint8_t Button_Inc_Val=GPIO_ReadFromInputPin(GPIOB, 11);
	uint8_t Button_Dec_Val=GPIO_ReadFromInputPin(GPIOB, 13);

	if(Button_Inc_Val && Button_Dec_Val)
	{

	}
	else if(Button_Dec_Val)
	{
		s--;
		s=EdgeCondition(s,HAND);
		ServoAngle(TIM4, s, GRIP);
	}
	else if(Button_Inc_Val)
	{
		s++;
		s=EdgeCondition(s,HAND);
		ServoAngle(TIM4, s, GRIP);
	}

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
	GPIOInits();
	Button_GPIOInits();
	ADC_Clk_EnorDi(ADC1, ENABLE);
	PWM_GPIOInits();
	TIM2_5_CLKEnable(TIM4, ENABLE); //Enables HSI and TIM3 peripheral clock
	PWMTIM();
	ServoBegin();

	while(1)
	{
		ADC_Init_LR(ADC1);

		ADC_Init_UD(ADC1);

		ADC_Top(ADC1);

		ButtonHandle();

		ServoHandle();
	}

}

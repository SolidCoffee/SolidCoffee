#include "stm32f407xx.h"
#include "stm32f407xx_gpio_driver.h"
#include "stm32f407xx_timer.h"
#include<stdio.h>
#include<string.h>

void delay2(void)
{
	for(uint32_t i = 0 ; i < 10000000 ; i ++);
}

void delay(void)
{
	for(uint32_t i = 0 ; i < 10000; i ++);
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
	TIMPWM.TIM_Config.TIM_DutyCycle = 479*.20;
	TIMPWM.TIM_Config.TIM_Polarity = POLHIGH;
	TIMPWM.TIM_Config.PWM_Channel = 1;

	PWM2_5_Init(&TIMPWM);

	TIMPWM.TIM_Config.PWM_Channel = 2;

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
	PWM_GPIOInits();
	TIM2_5_CLKEnable(TIM4, ENABLE); //Enables HSI and TIM3 peripheral clock

	GPIO_ButtonInit();

	PWMTIM();

	while(1)
	{

		ServoAngle(TIM4, 1, 1);
		while(! GPIO_ReadFromInputPin(GPIOA,0));
		delay();
		ServoAngle(TIM4, 270, 1);
		while(! GPIO_ReadFromInputPin(GPIOA,0));
		delay();
	}



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

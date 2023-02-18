/*
 * bedside_clock.c
 *
 *  Created on: Feb 16, 2023
 *      Author: gianl
 */

#include "stm32f407xx.h"

uint8_t readval = 0;
uint32_t DHT11_Counter=0;
uint32_t DHT11[42];
uint8_t break_flg=0;
uint32_t DHT11_time[42];

void GPIOInits(void)
{
	GPIO_Handler_t DHT11Pins;

	DHT11Pins.pGPIOx = GPIOB;

	DHT11Pins.GPIO_PinConfig.GPIO_PinMode = OUTPUT;
	DHT11Pins.GPIO_PinConfig.GPIO_PinAltFunMode = AF0;
	DHT11Pins.GPIO_PinConfig.GPIO_PinOPType = PUSHPULL;
	DHT11Pins.GPIO_PinConfig.GPIO_pinPuPdControl = PULLDOWN;
	DHT11Pins.GPIO_PinConfig.GPIO_PinSpeed = SPEEDHIGH;

	//PWM Pin config
	DHT11Pins.GPIO_PinConfig.GPIO_PinNumber = 5;
	GPIO_Init(&DHT11Pins);
}

void InputGPIOInits(void)
{
	GPIO_Handler_t ButtonPins;

		ButtonPins.pGPIOx = GPIOB;

		ButtonPins.GPIO_PinConfig.GPIO_PinMode = INPUT;
		ButtonPins.GPIO_PinConfig.GPIO_PinAltFunMode = AF0;
		ButtonPins.GPIO_PinConfig.GPIO_PinOPType = PUSHPULL;
		ButtonPins.GPIO_PinConfig.GPIO_pinPuPdControl = NOPUPD;
		ButtonPins.GPIO_PinConfig.GPIO_PinSpeed = SPEEDHIGH;  //might need to look into this

		ButtonPins.GPIO_PinConfig.GPIO_PinNumber = 5;
		GPIO_Init(&ButtonPins);

}

void Tim6Init(void)
{
	BasicTIM_Handler_t TIM6_timer;

		TIM6_timer.pTIMx = TIM6;
		TIM6_timer.TIM_Config.Buffer=0;
		TIM6_timer.TIM_Config.Interrupt=0;
		TIM6_timer.TIM_Config.MMS=2;
		TIM6_timer.TIM_Config.Mode=0;
		TIM6_timer.TIM_Config.Prescaler=16-1;

		BASIC_TIMCLKEnable(TIM6, ENABLE);

		BasicTIM_INIT(&TIM6_timer);

		StopTimerDelay(TIM6, 50000);
}

void DHT11Init(void)
{
	GPIOInits();

	GPIO_WriteToOutputPin(GPIOB,5,ENABLE);

	StopTimerDelay(TIM6, 50000); // arbitrary high period

	GPIO_WriteToOutputPin(GPIOB,5,DISABLE);

	//timer hold low for >18ms
	StopTimerDelay(TIM6, 20000); // 20 ms > 18ms

	GPIO_WriteToOutputPin(GPIOB,5,ENABLE);

	//timer to pull higher for 20-40 us
	StopTimerDelay(TIM6, 30);

	GPIO_WriteToOutputPin(GPIOB,5,DISABLE);

	//function to turn to input pin
	InputGPIOInits();
}


int main(void)
{
	Tim6Init();

	while(1)
	{

		DHT11Init();

		for(uint8_t i = 0; i <= 41; i++)
		{
			while(!GPIO_ReadFromInputPin(GPIOB, 5));
			while(GPIO_ReadFromInputPin(GPIOB, 5))
			{
				DHT11_Counter=RunningTimerDelay(TIM6, 1, 0);
				if(DHT11_Counter >200)
				{
					break_flg=1;
					break;
				}
			}

			DHT11_time[i]=DHT11_Counter;

			RunningTimerDelay(TIM6, 1, 1);

			if(break_flg)
			{
				break_flg=0;
				DHT11[i]=2;
				DHT11_Counter =0;
				break;
			}

			if(DHT11_Counter > 5)
			{
				DHT11[i]=1;
			}
			else
			{
				DHT11[i]=0;
			}
			DHT11_Counter =0;
		}
	}
}

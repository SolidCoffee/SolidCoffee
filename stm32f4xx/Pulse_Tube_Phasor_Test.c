/*
 * Pulse_Tube_Testing.c
 *
 *  Created on: Mar 6, 2022
 *      Author: gianl
 */
#include "stm32f407xx.h"
#include "stm32f407xx_gpio_driver.h"
#include "stm32f407xx_timer.h"
#include "stm32f407xx_ADC_driver.h"
#include "stm32f407xx_DAC_driver.h"
#include<stdio.h>
#include<string.h>



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
	ADCPins.GPIO_PinConfig.GPIO_PinNumber = 4;
	GPIO_Init(&ADCPins);

	ADCPins.GPIO_PinConfig.GPIO_PinNumber = 5;
	GPIO_Init(&ADCPins);
}

void DACInits(void)
{
	DAC_Handler_t DACsets;

	DACsets.pDACx = DAC;


	DACsets.DAC_Config.Buffer=BUFFER;
	DACsets.DAC_Config.Trigger=DISABLE;
	DACsets.DAC_Config.DMAUnderRn =0;

	DACsets.DAC_Config.Channel=1;
	DACInit(&DACsets);

	DACsets.DAC_Config.Channel=2;
	DACInit(&DACsets);

}


int main(void)
{
	GPIOInits();
	DAC_Clk_EnorDi(ENABLE);
	DACInits();
	uint32_t Phase=10;
	uint32_t x=0;

	while(1)
	{
  		if(x < 4000000000)
		{
			DualOpposeSineWaveGen(Phase);
			x++;
		}
		else if(x >= 4000000000)
		{
			Phase++;
			x=0;
		}
	}


}

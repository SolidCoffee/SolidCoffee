/*
 * stm32f407xx_stepper_driver.c
 *
 *  Created on: Mar 7, 2022
 *      Author: gianl
 */
#include "stm32f407xx_Stepper_driver.h"

void Stepperdelay(void)
{
	for(uint32_t i = 0 ; i < 5000; i ++);
}

void StepperStepsInc(uint32_t steps)
{
	for(uint32_t i=0; i <= steps; i++)
	{
		GPIO_WriteToOutputPin(GPIOB,12,HIGH);
		GPIO_WriteToOutputPin(GPIOB,10,LOW);
		GPIO_WriteToOutputPin(GPIOB,14,LOW);
		GPIO_WriteToOutputPin(GPIOB,15,LOW);

		Stepperdelay();
		//if(i>= steps) {break;}

		GPIO_WriteToOutputPin(GPIOB,12,HIGH);
		GPIO_WriteToOutputPin(GPIOB,10,LOW);
		GPIO_WriteToOutputPin(GPIOB,14,HIGH);
		GPIO_WriteToOutputPin(GPIOB,15,LOW);

		Stepperdelay();
		//if(i>= steps) {break;}

		GPIO_WriteToOutputPin(GPIOB,12,LOW);
		GPIO_WriteToOutputPin(GPIOB,10,LOW);
		GPIO_WriteToOutputPin(GPIOB,14,HIGH);
		GPIO_WriteToOutputPin(GPIOB,15,LOW);

		Stepperdelay();
		//if(i>= steps) {break;}

		GPIO_WriteToOutputPin(GPIOB,12,LOW);
		GPIO_WriteToOutputPin(GPIOB,10,HIGH);
		GPIO_WriteToOutputPin(GPIOB,14,HIGH);
		GPIO_WriteToOutputPin(GPIOB,15,LOW);

		Stepperdelay();
		//if(i>= steps) {break;}

		GPIO_WriteToOutputPin(GPIOB,12,LOW);
		GPIO_WriteToOutputPin(GPIOB,10,HIGH);
		GPIO_WriteToOutputPin(GPIOB,14,LOW);
		GPIO_WriteToOutputPin(GPIOB,15,LOW);

		Stepperdelay();
		//if(i>= steps) {break;}

		GPIO_WriteToOutputPin(GPIOB,12,LOW);
		GPIO_WriteToOutputPin(GPIOB,10,HIGH);
		GPIO_WriteToOutputPin(GPIOB,14,LOW);
		GPIO_WriteToOutputPin(GPIOB,15,HIGH);

		Stepperdelay();
		//if(i>= steps) {break;}

		GPIO_WriteToOutputPin(GPIOB,12,LOW);
		GPIO_WriteToOutputPin(GPIOB,10,LOW);
		GPIO_WriteToOutputPin(GPIOB,14,LOW);
		GPIO_WriteToOutputPin(GPIOB,15,HIGH);

		Stepperdelay();
		//if(i>= steps) {break;}

		GPIO_WriteToOutputPin(GPIOB,12,HIGH);
		GPIO_WriteToOutputPin(GPIOB,10,LOW);
		GPIO_WriteToOutputPin(GPIOB,14,LOW);
		GPIO_WriteToOutputPin(GPIOB,15,HIGH);

		Stepperdelay();
		//if(i>= steps) {break;}
	}
}

void StepperStepsDec(uint32_t steps)
{
	for(uint32_t i=0; i <= steps; i++)
	{
		GPIO_WriteToOutputPin(GPIOB,12,HIGH);
		GPIO_WriteToOutputPin(GPIOB,10,LOW);
		GPIO_WriteToOutputPin(GPIOB,14,LOW);
		GPIO_WriteToOutputPin(GPIOB,15,HIGH);

		Stepperdelay();

		GPIO_WriteToOutputPin(GPIOB,12,LOW);
		GPIO_WriteToOutputPin(GPIOB,10,LOW);
		GPIO_WriteToOutputPin(GPIOB,14,LOW);
		GPIO_WriteToOutputPin(GPIOB,15,HIGH);

		Stepperdelay();

		GPIO_WriteToOutputPin(GPIOB,12,LOW);
		GPIO_WriteToOutputPin(GPIOB,10,HIGH);
		GPIO_WriteToOutputPin(GPIOB,14,LOW);
		GPIO_WriteToOutputPin(GPIOB,15,HIGH);

		Stepperdelay();


		GPIO_WriteToOutputPin(GPIOB,12,LOW);
		GPIO_WriteToOutputPin(GPIOB,10,HIGH);
		GPIO_WriteToOutputPin(GPIOB,14,LOW);
		GPIO_WriteToOutputPin(GPIOB,15,LOW);

		Stepperdelay();

		GPIO_WriteToOutputPin(GPIOB,12,LOW);
		GPIO_WriteToOutputPin(GPIOB,10,HIGH);
		GPIO_WriteToOutputPin(GPIOB,14,HIGH);
		GPIO_WriteToOutputPin(GPIOB,15,LOW);

		Stepperdelay();

		GPIO_WriteToOutputPin(GPIOB,12,LOW);
		GPIO_WriteToOutputPin(GPIOB,10,LOW);
		GPIO_WriteToOutputPin(GPIOB,14,HIGH);
		GPIO_WriteToOutputPin(GPIOB,15,LOW);

		Stepperdelay();

		GPIO_WriteToOutputPin(GPIOB,12,HIGH);
		GPIO_WriteToOutputPin(GPIOB,10,LOW);
		GPIO_WriteToOutputPin(GPIOB,14,HIGH);
		GPIO_WriteToOutputPin(GPIOB,15,LOW);

		Stepperdelay();

		GPIO_WriteToOutputPin(GPIOB,12,HIGH);
		GPIO_WriteToOutputPin(GPIOB,10,LOW);
		GPIO_WriteToOutputPin(GPIOB,14,LOW);
		GPIO_WriteToOutputPin(GPIOB,15,LOW);

		Stepperdelay();

	}
}

void LeadStepsInc(uint32_t steps)
{
	for(uint32_t i=0; i <= steps; i++)
	{

		GPIO_WriteToOutputPin(GPIOB,YELLOW,LOW);
		GPIO_WriteToOutputPin(GPIOB,BLUE,LOW);
		GPIO_WriteToOutputPin(GPIOB,GREEN,LOW);
		GPIO_WriteToOutputPin(GPIOB,RED,HIGH);

		Stepperdelay();

		GPIO_WriteToOutputPin(GPIOB,YELLOW,HIGH);
		GPIO_WriteToOutputPin(GPIOB,BLUE,LOW);
		GPIO_WriteToOutputPin(GPIOB,GREEN,LOW);
		GPIO_WriteToOutputPin(GPIOB,RED,HIGH);

		Stepperdelay();

		GPIO_WriteToOutputPin(GPIOB,GREEN,LOW);
		GPIO_WriteToOutputPin(GPIOB,RED,LOW);
		GPIO_WriteToOutputPin(GPIOB,BLUE,LOW);
		GPIO_WriteToOutputPin(GPIOB,YELLOW,HIGH);

		Stepperdelay();

		GPIO_WriteToOutputPin(GPIOB,GREEN,HIGH);
		GPIO_WriteToOutputPin(GPIOB,RED,LOW);
		GPIO_WriteToOutputPin(GPIOB,BLUE,LOW);
		GPIO_WriteToOutputPin(GPIOB,YELLOW,HIGH);

		Stepperdelay();


		GPIO_WriteToOutputPin(GPIOB,YELLOW,LOW);
		GPIO_WriteToOutputPin(GPIOB,RED,LOW);
		GPIO_WriteToOutputPin(GPIOB,BLUE,LOW);
		GPIO_WriteToOutputPin(GPIOB,GREEN,HIGH);

		Stepperdelay();

		GPIO_WriteToOutputPin(GPIOB,YELLOW,LOW);
		GPIO_WriteToOutputPin(GPIOB,RED,HIGH);
		GPIO_WriteToOutputPin(GPIOB,BLUE,LOW);
		GPIO_WriteToOutputPin(GPIOB,GREEN,HIGH);

		Stepperdelay();


		GPIO_WriteToOutputPin(GPIOB,YELLOW,LOW);
		GPIO_WriteToOutputPin(GPIOB,GREEN,LOW);
		GPIO_WriteToOutputPin(GPIOB,RED,LOW);
		GPIO_WriteToOutputPin(GPIOB,BLUE,HIGH);

		Stepperdelay();

		GPIO_WriteToOutputPin(GPIOB,YELLOW,LOW);
		GPIO_WriteToOutputPin(GPIOB,GREEN,LOW);
		GPIO_WriteToOutputPin(GPIOB,RED,HIGH);
		GPIO_WriteToOutputPin(GPIOB,BLUE,HIGH);

		Stepperdelay();
	}
}

void LeadStepsDec(uint32_t steps)
{
	for(uint32_t i=0; i <= steps; i++)
	{

		GPIO_WriteToOutputPin(GPIOB,YELLOW,LOW);
		GPIO_WriteToOutputPin(GPIOB,GREEN,LOW);
		GPIO_WriteToOutputPin(GPIOB,RED,LOW);
		GPIO_WriteToOutputPin(GPIOB,BLUE,HIGH);

		Stepperdelay();

		GPIO_WriteToOutputPin(GPIOB,YELLOW,LOW);
		GPIO_WriteToOutputPin(GPIOB,GREEN,HIGH);
		GPIO_WriteToOutputPin(GPIOB,RED,LOW);
		GPIO_WriteToOutputPin(GPIOB,BLUE,HIGH);

		Stepperdelay();

		GPIO_WriteToOutputPin(GPIOB,YELLOW,LOW);
		GPIO_WriteToOutputPin(GPIOB,RED,LOW);
		GPIO_WriteToOutputPin(GPIOB,BLUE,LOW);
		GPIO_WriteToOutputPin(GPIOB,GREEN,HIGH);

		Stepperdelay();

		GPIO_WriteToOutputPin(GPIOB,YELLOW,HIGH);
		GPIO_WriteToOutputPin(GPIOB,RED,LOW);
		GPIO_WriteToOutputPin(GPIOB,BLUE,LOW);
		GPIO_WriteToOutputPin(GPIOB,GREEN,HIGH);

		Stepperdelay();

		GPIO_WriteToOutputPin(GPIOB,GREEN,LOW);
		GPIO_WriteToOutputPin(GPIOB,RED,LOW);
		GPIO_WriteToOutputPin(GPIOB,BLUE,LOW);
		GPIO_WriteToOutputPin(GPIOB,YELLOW,HIGH);

		Stepperdelay();

		GPIO_WriteToOutputPin(GPIOB,GREEN,LOW);
		GPIO_WriteToOutputPin(GPIOB,RED,HIGH);
		GPIO_WriteToOutputPin(GPIOB,BLUE,LOW);
		GPIO_WriteToOutputPin(GPIOB,YELLOW,HIGH);

		Stepperdelay();

		GPIO_WriteToOutputPin(GPIOB,YELLOW,LOW);
		GPIO_WriteToOutputPin(GPIOB,BLUE,LOW);
		GPIO_WriteToOutputPin(GPIOB,GREEN,LOW);
		GPIO_WriteToOutputPin(GPIOB,RED,HIGH);

		Stepperdelay();

		GPIO_WriteToOutputPin(GPIOB,YELLOW,LOW);
		GPIO_WriteToOutputPin(GPIOB,BLUE,BLUE);
		GPIO_WriteToOutputPin(GPIOB,GREEN,LOW);
		GPIO_WriteToOutputPin(GPIOB,RED,HIGH);

		Stepperdelay();

	}
}

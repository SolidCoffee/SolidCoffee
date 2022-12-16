/*
 * stm32f407xx_stepper_driver.c
 *
 *  Created on: Mar 7, 2022
 *      Author: gianl
 */
#include "stm32f407xx_Stepper_driver.h"

uint16_t counter_black = 0;
uint16_t counter_red = 0;
uint16_t counter_green=0;
uint16_t counter_blue=0;
uint8_t black_flg = 1;
uint8_t red_flg=0;
uint8_t green_flg=0;
uint8_t blue_flg=0;
uint8_t black_flg_dec = 0;
uint8_t red_flg_dec=0;
uint8_t green_flg_dec=0;
uint8_t blue_flg_dec=1;
uint32_t step_counter= 0;

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

__attribute__((__common__)) uint32_t MicrostepSineWave[] = {0,
		2,
		3,
		5,
		6,
		8,
		9,
		11,
		12,
		14,
		15,
		17,
		18,
		20,
		21,
		23,
		24,
		25,
		27,
		28,
		29,
		31,
		32,
		33,
		34,
		35,
		36,
		38,
		39,
		40,
		40,
		41,
		42,
		43,
		44,
		45,
		45,
		46,
		46,
		47,
		48,
		48,
		48,
		49,
		49,
		49,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		50,
		49,
		49,
		49,
		48,
		48,
		48,
		47,
		46,
		46,
		45,
		45,
		44,
		43,
		42,
		41,
		40,
		40,
		39,
		38,
		36,
		35,
		34,
		33,
		32,
		31,
		29,
		28,
		27,
		25,
		24,
		23,
		21,
		20,
		18,
		17,
		15,
		14,
		12,
		11,
		9,
		8,
		6,
		5,
		3,
		2,
		0,
};

uint32_t Full_sine_wave_count_MStep = 100;
uint32_t Half_sine_wave_count_MStep = 100/2;
uint32_t Max_Duty_Cycle = 50;

void MicrostepsInc(uint32_t steps)
{
	if(step_counter < steps)
	{
		if(black_flg)
		{
			GPIO_WriteToOutputPin(GPIOC,8,LOW);
			PWMOutput(TIM3,MicrostepSineWave[counter_black],BLACK_A_PLUS);
			counter_black++;
			if(counter_black > Full_sine_wave_count_MStep)
			{
				black_flg=0;
				counter_black = 0;
			}
			else if(counter_black == Half_sine_wave_count_MStep)
			{
				step_counter++;
				red_flg=1;
			}
		}

		if(red_flg)
		{
			GPIO_WriteToOutputPin(GPIOC,9,LOW);
			PWMOutput(TIM3,MicrostepSineWave[counter_red],RED_B_PLUS);
			counter_red++;
			if(counter_red > Full_sine_wave_count_MStep)
			{
				red_flg=0;
				counter_red = 0;
			}
			else if(counter_red == Half_sine_wave_count_MStep)
			{
				step_counter++;
				green_flg=1;
			}
		}

		if(green_flg)
		{
			GPIO_WriteToOutputPin(GPIOC,6,LOW);
			PWMOutput(TIM3,MicrostepSineWave[counter_green],GREEN_A_MINUS);
			counter_green++;
			if(counter_green > Full_sine_wave_count_MStep)
			{
				green_flg=0;
				counter_green = 0;
			}
			else if(counter_green == Half_sine_wave_count_MStep)
			{
				step_counter++;
				blue_flg=1;
			}
		}

		if(blue_flg)
		{
			GPIO_WriteToOutputPin(GPIOC,7,LOW);
			PWMOutput(TIM3,MicrostepSineWave[counter_blue],BLUE_B_MINUS);
			counter_blue++;
			if(counter_blue > Full_sine_wave_count_MStep)
			{
				blue_flg=0;
				counter_blue = 0;
			}
			else if(counter_blue == Half_sine_wave_count_MStep)
			{
				step_counter++;
				black_flg=1;
			}
		}
	}
	else
	{
		step_counter = 0;
		black_flg = 1;
	}
}

void MicrostepsDec(uint32_t steps)
{
	if(step_counter < steps)
	{
		if(blue_flg_dec)
		{
			GPIO_WriteToOutputPin(GPIOC,7,LOW);
			PWMOutput(TIM3,MicrostepSineWave[counter_blue],BLUE_B_MINUS);
			counter_blue++;
			if(counter_blue > Full_sine_wave_count_MStep)
			{
				blue_flg_dec=0;
				counter_blue = 0;
			}
			else if(counter_blue == Half_sine_wave_count_MStep)
			{
				step_counter++;
				green_flg_dec=1;
			}
		}

		if(green_flg_dec)
		{
			GPIO_WriteToOutputPin(GPIOC,6,LOW);
			PWMOutput(TIM3,MicrostepSineWave[counter_green],GREEN_A_MINUS);
			counter_green++;
			if(counter_green > Full_sine_wave_count_MStep)
			{
				green_flg_dec=0;
				counter_green = 0;
			}
			else if(counter_green == Half_sine_wave_count_MStep)
			{
				step_counter++;
				red_flg_dec=1;
			}
		}

		if(red_flg_dec)
		{
			GPIO_WriteToOutputPin(GPIOC,9,LOW);
			PWMOutput(TIM3,MicrostepSineWave[counter_red],RED_B_PLUS);
			counter_red++;
			if(counter_red > Full_sine_wave_count_MStep)
			{
				red_flg_dec=0;
				counter_red = 0;
			}
			else if(counter_red == Half_sine_wave_count_MStep)
			{
				step_counter++;
				black_flg_dec=1;
			}
		}

		if(black_flg_dec)
		{
			GPIO_WriteToOutputPin(GPIOC,8,LOW);
			PWMOutput(TIM3,MicrostepSineWave[counter_black],BLACK_A_PLUS);
			counter_black++;
			if(counter_black > Full_sine_wave_count_MStep)
			{
				black_flg_dec=0;
				counter_black = 0;
			}
			else if(counter_black == Half_sine_wave_count_MStep)
			{
				step_counter++;
				blue_flg_dec=1;
			}
		}
	}
	else
	{
		step_counter = 0;
		blue_flg_dec = 1;
	}
}

void StepperBasicTimer_init(void)
{
	BasicTIM_Handler_t TenMin;

	TenMin.pTIMx = TIM6;
	TenMin.TIM_Config.Buffer=0;
	TenMin.TIM_Config.Interrupt=0;
	TenMin.TIM_Config.MMS=2;
	TenMin.TIM_Config.Mode=0;
	TenMin.TIM_Config.Prescaler=0;

	BASIC_TIMCLKEnable(TIM6, ENABLE);

	BasicTIM_INIT(&TenMin);

}
void StepperPWM_GPIOInits(void)
{
	GPIO_Handler_t PWMPins;

	PWMPins.pGPIOx = GPIOC;

	PWMPins.GPIO_PinConfig.GPIO_PinMode = ALTFUNC;
	PWMPins.GPIO_PinConfig.GPIO_PinAltFunMode = AF2;
	PWMPins.GPIO_PinConfig.GPIO_PinOPType = PUSHPULL;
	PWMPins.GPIO_PinConfig.GPIO_pinPuPdControl = PULLDOWN;
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

void PWMStepperTIM(void)
{
	TIM_Handler_t TIMPWM;

	TIMPWM.pTIMx = TIM3;
	TIMPWM.TIM_Config.TIM_Direction = UPCNT;
	TIMPWM.TIM_Config.TIM_ARR = Max_Duty_Cycle;		//new frequency divided by this to get max freq
	TIMPWM.TIM_Config.TIM_Prescaler = 0; //divides 16 Mhz by the number being subtracted
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

void stepperInit(void)
{
	TIM2_5_CLKEnable(TIM3,ENABLE);
	StepperBasicTimer_init();
	PWMStepperTIM();
	StepperPWM_GPIOInits();

}

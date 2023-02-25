/*
 * bedside_clock.c
 *
 *  Created on: Feb 16, 2023
 *      Author: gianl
 */

#include "stm32f407xx.h"

uint8_t C_to_F(uint8_t temp_c);

uint8_t readval = 0;
uint32_t DHT11_Counter=0;
uint32_t DHT11[42];
uint8_t break_flg=0;
uint32_t DHT11_time[42];
uint8_t Humidity_i=0;
uint8_t Humidity_d=0;
uint8_t Temp_i=0;
uint8_t Temp_d=0;
char Temp[10];
char Temp_D[10];
char Humidity[10];
char Humidity_D[10];
uint8_t screen_on_flg=0;
uint8_t screen_timer=0;
char Temp_C[10];
char Temp_C_D[10];

void GPIOInits(void)
{
	GPIO_Handler_t DHT11Pins;

	DHT11Pins.pGPIOx = GPIOB;

	DHT11Pins.GPIO_PinConfig.GPIO_PinMode = OUTPUT;
	DHT11Pins.GPIO_PinConfig.GPIO_PinAltFunMode = AF0;
	DHT11Pins.GPIO_PinConfig.GPIO_PinOPType = PUSHPULL;
	DHT11Pins.GPIO_PinConfig.GPIO_pinPuPdControl = PULLDOWN;
	DHT11Pins.GPIO_PinConfig.GPIO_PinSpeed = SPEEDHIGH;

	DHT11Pins.GPIO_PinConfig.GPIO_PinNumber = 5;
	GPIO_Init(&DHT11Pins);

	DHT11Pins.GPIO_PinConfig.GPIO_PinNumber = 1;
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

void MovementSensorGPIOInits(void)
{
	GPIO_Handler_t ButtonPins;

		ButtonPins.pGPIOx = GPIOB;

		ButtonPins.GPIO_PinConfig.GPIO_PinMode = INPUT;
		ButtonPins.GPIO_PinConfig.GPIO_PinAltFunMode = AF0;
		ButtonPins.GPIO_PinConfig.GPIO_PinOPType = PUSHPULL;
		ButtonPins.GPIO_PinConfig.GPIO_pinPuPdControl = NOPUPD;
		ButtonPins.GPIO_PinConfig.GPIO_PinSpeed = SPEEDHIGH;  //might need to look into this

		ButtonPins.GPIO_PinConfig.GPIO_PinNumber = 6;
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

void Tim7Init(void)
{
	BasicTIM_Handler_t TIM7_timer;

		TIM7_timer.pTIMx = TIM7;
		TIM7_timer.TIM_Config.Buffer=0;
		TIM7_timer.TIM_Config.Interrupt=0;
		TIM7_timer.TIM_Config.MMS=2;
		TIM7_timer.TIM_Config.Mode=0;
		TIM7_timer.TIM_Config.Prescaler=16000-1;

		BASIC_TIMCLKEnable(TIM7, ENABLE);

		BasicTIM_INIT(&TIM7_timer);

		StopTimerDelay(TIM7, 50000);
}

void DHT11_GetValues(void)
{

	Humidity_i=0;
	Humidity_d=0;
	Temp_i=0;
	Temp_d=0;

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

	for(uint8_t i = 40; i > 0; i--)
			{
				while(!GPIO_ReadFromInputPin(GPIOB, 5));
				while(GPIO_ReadFromInputPin(GPIOB, 5))
				{
					DHT11_Counter=RunningTimerDelay(TIM6, 1, RUN);
					if(DHT11_Counter >200)
					{
						break_flg=1;
						break;
					}
				}

				DHT11_time[i]=DHT11_Counter; //array to check the time for each counter

				RunningTimerDelay(TIM6, 1, CLEAR);

				if(i == 40)
				{
					DHT11_Counter =0;
					DHT11[i]=2;
				}
				else if(i <40 && i >= 32)
				{
					if(DHT11_Counter > 5)
					{
						Humidity_i |= ( 1 << (i-32));
						DHT11[i]=1;
					}
					else
					{
						Humidity_i |= ( 0 << (i-32));
						DHT11[i]=0;
					}
					DHT11_Counter =0;
				}
				else if(i < 32 && i>=24)
				{
					if(DHT11_Counter > 5)
					{
						Humidity_d |= ( 1 << (i-24));
						DHT11[i]=1;
					}
					else
					{
						Humidity_d |= ( 0 << (i-24));
						DHT11[i]=0;
					}
					DHT11_Counter =0;
				}
				else if(i < 24 && i >= 16)
				{
					if(DHT11_Counter > 5)
					{
						Temp_i |= ( 1 << (i-16));
						DHT11[i]=1;
					}
					else
					{
						Temp_i |= ( 0 << (i-16));
						DHT11[i]=0;
					}
					DHT11_Counter =0;
				}
				else if(i <16 && i >= 8)
				{
					if(DHT11_Counter > 5)
					{
						Temp_d |= ( 1 << (i-8));
						DHT11[i]=1;
					}
					else
					{
						Temp_d |= ( 0 << (i-8));
						DHT11[i]=0;
					}
					DHT11_Counter =0;
				}
				else
				{
					DHT11_Counter =0;
				}

				DHT11_Counter =0;
			}
	uint8_t Temp_i_c=Temp_i;
	uint8_t Temp_i_d_c=Temp_d;
	Temp_i=C_to_F(Temp_i);
	Temp_d=C_to_F(Temp_d);

	sprintf(Humidity, "%d", Humidity_i);
	sprintf(Humidity_D, "%d", Humidity_d);
	sprintf(Temp, "%d", Temp_i);
	sprintf(Temp_D, "%d", Temp_d);
	sprintf(Temp_C, "%d", Temp_i_c);
	sprintf(Temp_C_D,"%d", Temp_i_d_c);
}

uint8_t C_to_F(uint8_t temp_c)
{
	uint8_t temp_f=(temp_c*1.8)+32;

	return temp_f;
}

void LCD_Screen_Movement(void)
{
	if(GPIO_ReadFromInputPin(GPIOB, 6))
	{
		screen_on_flg=1;
	}

	if(screen_on_flg && screen_timer >9)
	{
		if(GPIO_ReadFromInputPin(GPIOB, 6))
		{
		}
		else
		{
			GPIO_WriteToOutputPin(GPIOB,1,DISABLE);
			screen_on_flg=0;
			screen_timer=RunningTimerDelay(TIM7, 1000, CLEAR);
		}

	}
	else if(screen_on_flg)
	{
		GPIO_WriteToOutputPin(GPIOB,1,ENABLE);
		screen_timer=RunningTimerDelay(TIM7, 1000, RUN);
	}
	else  //redundant
	{
		GPIO_WriteToOutputPin(GPIOB,1,DISABLE);
		screen_on_flg=0;
	}

}


int main(void)
{
	Tim6Init();
	lcd_init();
	MovementSensorGPIOInits();
	Tim7Init();


	while(1)
	{
		DHT11_GetValues();

		lcd_print_string(Temp_C);
		lcd_print_string(".");
		lcd_print_string(Temp_C_D);

		lcd_set_cursor(2, 1);
		lcd_print_string("T:");
		lcd_print_string(Temp);
		lcd_print_string(".");
		lcd_print_string(Temp_D);
		lcd_print_string("F");
		lcd_set_cursor(2, 10);
		lcd_print_string("H:");
		lcd_print_string(Humidity);
		lcd_print_string(".");
		lcd_print_string(Humidity_D);
		lcd_print_string("%");
		for(uint32_t i=0;i<1000000;i++);

		lcd_display_clear();  //also resets cursor to start
		for(uint32_t i=0;i<100000;i++);

		LCD_Screen_Movement();


	}
}

/*DHT11Init();

		for(uint8_t i = 0; i <= 41; i++)
		{
			while(!GPIO_ReadFromInputPin(GPIOB, 5));
			while(GPIO_ReadFromInputPin(GPIOB, 5))
			{
				DHT11_Counter=RunningTimerDelay(TIM6, 1, RUN);
				if(DHT11_Counter >200)
				{
					break_flg=1;
					break;
				}
			}

			DHT11_time[i]=DHT11_Counter; //array to check the time for each counter

			RunningTimerDelay(TIM6, 1, CLEAR);  //clears the internal

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
		}*/


/*for(uint8_t i = 0; i <= 40; i++)
		{
			while(!GPIO_ReadFromInputPin(GPIOB, 5));
			while(GPIO_ReadFromInputPin(GPIOB, 5))
			{
				DHT11_Counter=RunningTimerDelay(TIM6, 1, RUN);
				if(DHT11_Counter >200)
				{
					break_flg=1;
					break;
				}
			}

			DHT11_time[i]=DHT11_Counter; //array to check the time for each counter

			RunningTimerDelay(TIM6, 1, CLEAR);

			if(i == 0)
			{
				DHT11_Counter =0;
				DHT11[i]=2;
			}
			else if(i >0 && i <= 8)
			{
				if(DHT11_Counter > 5)
				{
					Humidity_i |= ( 1 << (i-1));
					DHT11[i]=1;
				}
				else
				{
					Humidity_i |= ( 0 << (i-1));
					DHT11[i]=0;
				}
				DHT11_Counter =0;
			}
			else if(i >8 && i<=16)
			{
				if(DHT11_Counter > 5)
				{
					Humidity_d |= ( 1 << (i-9));
					DHT11[i]=1;
				}
				else
				{
					Humidity_d |= ( 0 << (i-9));
					DHT11[i]=0;
				}
				DHT11_Counter =0;
			}
			else if(i > 16 && i <= 24)
			{
				if(DHT11_Counter > 5)
				{
					Temp_i |= ( 1 << (i-17));
					DHT11[i]=1;
				}
				else
				{
					Temp_i |= ( 0 << (i-17));
					DHT11[i]=0;
				}
				DHT11_Counter =0;
			}
			else if(i >24 && i <= 32)
			{
				if(DHT11_Counter > 5)
				{
					Temp_d |= ( 1 << (i-25));
					DHT11[i]=1;
				}
				else
				{
					Temp_d |= ( 0 << (i-25));
					DHT11[i]=0;
				}
				DHT11_Counter =0;
			}
			else
			{
				DHT11_Counter =0;
			}

			DHT11_Counter =0;
		}*/

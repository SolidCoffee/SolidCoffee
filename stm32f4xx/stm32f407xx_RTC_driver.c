/*
 * stm32f407xx_RTC_driver.c
 *
 *  Created on: Feb 17, 2023
 *      Author: gianl
 */


#include "stm32f407xx_RTC_driver.h"

void RTC_Init(RTC_Handler_t *pRTCHandle)
{

	RCC->BDCR &= ~(1 << 16);; //resets backup register

	//pwr on
	RCC->APB1ENR |= (1 << 28);

	//turn on power to RTC
	PWR->CR |= (1 << 8);

	//enable LSI
	RCC->CSR |= (1 << 0);

	//Choose RTC clock source
	RCC->BDCR |= (2 << 8);
	//enable RTC in RCC
	RCC->BDCR |= (1 << 15);

	//unlock RTC by writing key into WPR
	RTC->WPR = 0xCA;
	RTC->WPR = 0x53;

	//begin initialization
	RTC->ISR |= (1 << 7);

	//wait for mode to be entered
	while(!(RTC->ISR & (1 << 6)));

	//clears time register
	RTC->TR &= ~(127 << 16);
	RTC->TR &= ~(127 << 8);
	RTC->TR &= ~(127);

	//set am or pm
	RTC->TR |= (pRTCHandle->RTC_PinConfig.AmOrPm << 22);

	//set hour
	RTC->TR |=(Dec_to_BCD(pRTCHandle->RTC_PinConfig.Hour) << 16);

	//set minute
	RTC->TR |=(Dec_to_BCD(pRTCHandle->RTC_PinConfig.Minute) << 8);

	//set second
	RTC->TR |=(Dec_to_BCD(pRTCHandle->RTC_PinConfig.Second) << 0);

	//clears Date register
	RTC->DR &= ~(0xFFFF << 8);
	RTC->DR &= ~(0x3F);


	RTC->DR |=(Dec_to_BCD(pRTCHandle->RTC_PinConfig.Year) << 16);

	RTC->DR &=~(7 << 13);

	RTC->DR |=(pRTCHandle->RTC_PinConfig.Day_Name << 13);

	RTC->DR |=(Dec_to_BCD(pRTCHandle->RTC_PinConfig.Month) << 8);

	RTC->DR |=(Dec_to_BCD(pRTCHandle->RTC_PinConfig.Date_Num) << 0);

	//bypshad bit in cr
	RTC->CR |=(1 << 5);

	//12 hour mode
	RTC->CR |=(1 << 6);

	//end initialization
	RTC->ISR &= ~(1 << 7);
}

uint8_t Dec_to_BCD(uint8_t Dec)
{
	uint8_t BCDval = 0;

	BCDval = Dec % 10;
	Dec /= 10;
	BCDval |= (Dec << 4);

	return BCDval;

}

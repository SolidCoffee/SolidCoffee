/*
 * stm32f407xx_RTC_driver.h
 *
 *  Created on: Feb 17, 2023
 *      Author: gianl
 */

#ifndef INC_STM32F407XX_RTC_DRIVER_H_
#define INC_STM32F407XX_RTC_DRIVER_H_

#include "stm32f407xx.h"


typedef struct
{
	uint8_t Hour;
	uint8_t Minute;
	uint8_t Second;
	uint8_t Year;  //23
	uint8_t Day_Name;  //ex mon
	uint8_t Date_Num;  //ex 16
	uint8_t Month;
	uint8_t AmOrPm;

}RTC_PinConfig_t;

//months of the year
#define JANUARY		1
#define FEBRUARY		2
#define MARCH		3
#define APRIL		4
#define MAY			5
#define JUNE		6
#define JULY		7
#define AUGUST		8
#define SEPTEMBER	9
#define OCTOBER		10
#define NOVEMBER	11
#define DECEMBER	12

//days of the week
#define MONDAY		1
#define TUESDAY		2
#define WEDNESDAY	3
#define THURSDAY	4
#define FRIDAY		5
#define SATURDAY	6
#define SUNDAY		7

#define AM			0
#define PM			1


typedef struct
{
	RTC_RegDef_t *pRTCx;
	RTC_PinConfig_t RTC_PinConfig;

}RTC_Handler_t;


void RTC_Init(RTC_Handler_t *pRTCHandle);
uint8_t Dec_to_BCD(uint8_t Dec);


#endif /* INC_STM32F407XX_RTC_DRIVER_H_ */

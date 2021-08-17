/*
 * spi_cmd_handling.c
 *
 *  Created on: Aug 15, 2021
 *      Author: gianl
 */

/*
PB15--MOSI
PB14--MISO
PB13--SCLK
PB9--NSS
alt functionality mode will be 5
*/

#include "stm32f407xx.h"
#include "stm32f407xx_gpio_driver.h"
#include "stm32f407xx_spi_driver.h"
#include<stdio.h>
#include<string.h>

#define COMMAND_LED_CTRL			0x50
#define COMMAND_SENSOR_READ			0x51
#define COMMAND_LED_READ			0x52
#define COMMAND_PRINT				0x52
#define COMMAND_ID_READ				0x54

#define LED_ON						1
#define LED_OFF						0

#define A0							0
#define A1							1
#define A2							2
#define A3							3
#define A4							4
#define A5							5

#define LED_PIN						9




void SPI_GPIOInits(void)
{
	GPIO_Handler_t SPIPins;

	SPIPins.pGPIOx = GPIOB;

	SPIPins.GPIO_PinConfig.GPIO_PinMode = ALTFUNC;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = AF5;
	SPIPins.GPIO_PinConfig.GPIO_PinOPType = PUSHPULL;
	SPIPins.GPIO_PinConfig.GPIO_pinPuPdControl = NOPUPD;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = FAST;

	//SCLK config
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = 10;
	GPIO_Init(&SPIPins);

	//MOSI
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = 15;
	GPIO_Init(&SPIPins);

	//MISO
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = 14;
	GPIO_Init(&SPIPins);

	//NSS
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = 12;
	GPIO_Init(&SPIPins);

}

void SPI_Inits(void)
{
	SPI_Handler_t SPIHandle;

	SPIHandle.pSPIx = SPI2;
	SPIHandle.SPI_Config.SPI_BusConfig = FULLDUPLEX;
	SPIHandle.SPI_Config.SPI_DeviceMode = MASTER;
	SPIHandle.SPI_Config.SPI_SclkSpeed = BAUDDIV32;//clock of 8  MHz
	SPIHandle.SPI_Config.SPI_DFF = EIGHTBIT;
	SPIHandle.SPI_Config.SPI_CPHA = LOW;
	SPIHandle.SPI_Config.SPI_CPOL = LOW;
	SPIHandle.SPI_Config.SPI_SSM = HARDWARE;

	SPI_Init(&SPIHandle);

	//enable the SPI2 clock
	//SPI_PeripheralControlTest(&SPIHandle,ENABLE);
}

void GPIO_ButtonInit()
{
	GPIO_Handler_t GPIOBtn;

	GPIOBtn.pGPIOx = GPIOA;
	GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = 0;
	GPIOBtn.GPIO_PinConfig.GPIO_PinMode = INPUT;
	GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = FAST;
	GPIOBtn.GPIO_PinConfig.GPIO_pinPuPdControl =NOPUPD;

	GPIO_Init(&GPIOBtn);

}

uint8_t SPI_VerifyResponse(uint8_t ackbyte)
{
	if(ackbyte == (uint8_t)0xF5)
	{
		return 1;
	}

	return 0;
}



int main(void)
{
	uint8_t dummy_write = 0xff;
	uint8_t dummy_read;

	GPIO_ButtonInit();

	SPI_GPIOInits();
	SPI_Inits();

	SPI_SSOEConfig(SPI2, ENABLE);

	while(1)
	{

		while(! GPIO_ReadFromInputPin(GPIOA,0));

		delay();

		SPI_PeripheralControl(SPI2, ENABLE);

		//command 1 COMMAND LED CONTROL
		uint8_t command= COMMAND_LED_CTRL;
		uint8_t ackbyte;
		uint8_t args[2];

		//send command
		SPI_SendData(SPI2,&command,1);

		//do dummy read to clear off the RXNE
		SPI_ReceiveData(SPI2,&dummy_read,1);


		//Send some dummy bits (1 byte) fetch the response from the slave
		SPI_SendData(SPI2,&dummy_write,1);

		//read the ack byte received
		SPI_ReceiveData(SPI2, &ackbyte,1);

		if(SPI_VerifyResponse(ackbyte))
		{
			//send arguments
			args[0] = LED_PIN;
			args[1] = LED_ON;
			SPI_SendData(SPI2, args, 2);

//DUMMY READ******************************************//////***********
			SPI_ReceiveData(SPI2,args,2);
		}

		//CMD_SENSOR_READ**********************************
		while(! GPIO_ReadFromInputPin(GPIOA,0));
		delay();

		command = COMMAND_SENSOR_READ;

		//send command
		SPI_SendData(SPI2, &command, 1);

		Clear_and_Push(SPI2, 1);

		//read the ack byte received
		SPI_ReceiveData(SPI2, &ackbyte,1);

		if(SPI_VerifyResponse(ackbyte))
		{
			//send arguments
			args[0] = A0;
			SPI_SendData(SPI2, args, 1);

			SPI_ReceiveData(SPI2, &dummy_read, 1);

			delay();

			SPI_SendData(SPI2, &dummy_write, 1);

			uint8_t analog_read;

			//receive data
			SPI_ReceiveData(SPI2, &analog_read, 1);
			printf("COMMAND_SENSOR_READ %d\n",analog_read);
		}


		while(Busy_Check(SPI2) == BUSY);

		SPI_PeripheralControl(SPI2, DISABLE);
	}

	return  0;
}

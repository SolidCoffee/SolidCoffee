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

void delay(void)
{
	for(uint32_t i = 0; i < 500000 ; i++);
}

void SPI_GPIOInits(void)
{
	GPIO_Handler_t SPIPins;

	SPIPins.pGPIOX = GPIOB;

	SPIPins.GPIO_PinConfig.GPIO_PinMode = ALTFUNC;
	SPIPins.GPIO_PinConfig.GPIO_PinAltFunMode = AF5;
	SPIPins.GPIO_PinConfig.GPIO_PinOPType = PUSHPULL;
	SPIPins.GPIO_PinConfig.GPIO_pinPuPdControl = NOPUPD;
	SPIPins.GPIO_PinConfig.GPIO_PinSpeed = FAST;

	//SCLK config
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = 13;
	GPIO_Init(&SPIPins);

	//MOSI
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = 15;
	GPIO_Init(&SPIPins);

	//MISO
	//SPIPins.GPIO_PinConfig.GPIO_PinNumber = 14;
	//GPIO_Init(&SPIPins);

	//NSS
	SPIPins.GPIO_PinConfig.GPIO_PinNumber = 9;
	GPIO_Init(&SPIPins);

}

void SPI_Inits(void)
{
	SPI_Handler_t SPIHandle;

	SPIHandle.pSPIx = SPI2;
	SPIHandle.SPI_Config.SPI_BusConfig = FULLDUPLEX;
	SPIHandle.SPI_Config.SPI_DeviceMode = MASTER;
	SPIHandle.SPI_Config.SPI_SclkSpeed = BAUDDIV8;//clock of 8  MHz
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

	GPIOBtn.pGPIOX = GPIOA;
	GPIOBtn.GPIO_PinConfig.GPIO_PinNumber = 0;
	GPIOBtn.GPIO_PinConfig.GPIO_PinMode = INPUT;
	GPIOBtn.GPIO_PinConfig.GPIO_PinSpeed = FAST;
	GPIOBtn.GPIO_PinConfig.GPIO_pinPuPdControl =NOPUPD;

	GPIO_PLCK_Control(GPIOA,ENABLE);

	GPIO_Init(&GPIOBtn);

}

int main(void)
{
	char user_data[]="Hello world";

	SPI_GPIOInits();
	SPI_Inits();

	GPIO_ButtonInit();

	SPI_SSOEConfig(SPI2, ENABLE);

	while(1)
	{

		while(! GPIO_ReadFromInputPin(GPIOA,0));

		delay();

		SPI_PeripheralControl(SPI2, ENABLE);

		uint8_t dataLen= strlen(user_data);

		SPI_SendData(SPI2, &dataLen, 1);

		SPI_SendData(SPI2,(uint8_t*)user_data, strlen(user_data));

		while(Busy_Check(SPI2) == BUSY);

		SPI_PeripheralControl(SPI2, DISABLE);
	}

	return  0;
}

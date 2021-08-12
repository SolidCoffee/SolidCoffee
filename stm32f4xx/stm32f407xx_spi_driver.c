#include "stm32f407xx_spi_driver.h"

//peripheral clock settup
void SPI_PLCK_Control(SPI_RegDef_t *pSPIx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pSPIx == SPI1)
		{
			SPI1_PCLK_EN();
		}
		else if(pSPIx == SPI2)
		{
			SPI2_PCLK_EN();
		}
		else if(pSPIx == SPI3)
		{
			SPI3_PCLK_EN();
		}
	}
	else
	{
		if(pSPIx == SPI1)
			{
				SPI1_PCLK_DI();
			}
			else if(pSPIx == SPI2)
			{
				SPI2_PCLK_DI();
			}
			else if(pSPIx == SPI3)
			{
				SPI3_PCLK_DI();
			}
	}
}

//init and deinit
void SPI_Init(SPI_Handler_t *pSPIHandle)
{

}


void SPI_DeInit(SPI_RegDef_t *pSPIx)
{
	if(pSPIx == SPI1)
			{
				SPI1_REG_RESET();
			}
			else if(pSPIx == SPI2)
			{
				SPI2_REG_RESET();
			}
			else if(pSPIx == SPI3)
			{
				SPI3_REG_RESET();
			}
}


//data send and receive
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len);

//IRQ config and ISR handling
void SPI_ITConfig(uint8_t IRQNumber, uint8_t Enordi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void SPI_IRQHandling(SPI_Handler_t *pHandle);

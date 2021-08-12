#ifndef INC_STM32F407XX_SPI_DRIVER_H_
#define INC_STM32F407XX_SPI_DRIVER_H_

#include "stm32f407xx.h"

#include<stdint.h>

typedef struct
{
	uint8_t SPI_DeviceMode;
	uint8_t SPI_BusConfig;
	uint8_t SPI_SclkSpeed;
	uint8_t SPI_DFF;
	uint8_t SPI_CPOL;
	uint8_t SPI_CPHA;
	uint8_t SPI_SSM;

}SPI_Config_t;


typedef struct
{
	SPI_RegDef_t *pSPIx;
	SPI_Config_t SPI_Config;
}SPI_Handler_t;

//peripheral clock settup
void SPI_PLCK_Control(SPI_RegDef_t *pSPIx, uint8_t EnorDi);

//init and deinit
void SPI_Init(SPI_Handler_t *pSPIHandle);
void SPI_DeInit(SPI_RegDef_t *pSPIx);

//data send and receive
void SPI_SendData(SPI_RegDef_t *pSPIx, uint8_t *pTxBuffer, uint32_t Len);
void SPI_ReceiveData(SPI_RegDef_t *pSPIx, uint8_t *pRxBuffer, uint32_t Len);

//IRQ config and ISR handling
void SPI_ITConfig(uint8_t IRQNumber, uint8_t Enordi);
void SPI_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void SPI_IRQHandling(SPI_Handler_t *pHandle);

//other peripheral control API



#endif /* INC_STM32F407XX_SPI_DRIVER_H_ */

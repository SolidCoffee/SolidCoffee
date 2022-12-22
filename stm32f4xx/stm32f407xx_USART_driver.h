/*
 * stm32f407xx_USART_driver.h
 *
 *  Created on: Dec 17, 2022
 *      Author: gianl
 */

#ifndef INC_STM32F407XX_USART_DRIVER_H_
#define INC_STM32F407XX_USART_DRIVER_H_

#include "stm32f407xx.h"

typedef struct
{
	uint8_t USART_Mode;
	uint32_t USART_Baud;
	uint8_t USART_OverSampling;
	uint8_t USART_NumOfStopBits;
	uint8_t USART_WordLength;
	uint8_t USART_ParityControl;
	uint8_t USART_HWFlowControl;
}USART_Config_t;

typedef struct
{
	USART_RegDef_t *pUSARTx;
	USART_Config_t USART_Config;
}USART_Handle_t;


//mode macros
#define USART_MODE_TX_ONLY		0
#define USART_MODE_RX_ONLY		1
#define USART_MODE_TXRX			2

//baud rate macros
#define USART_BAUD_1200			1200
#define USART_BAUD_2400			2400
#define USART_BAUD_9600			9600
#define USART_BAUD_19200		19200
#define USART_BAUD_38400		38400
#define USART_BAUD_57600		57600
#define USART_BAUD_115200		115200
#define USART_BAUD_230400		230400
#define USART_BAUD_460800		460800
#define USART_BAUD_921600		921600
#define USART_BAUD_2000000		2000000
#define USART_BAUD_3000000		3000000

//oversamplig macros
#define USART_OVERSAMP_8_BIT	1
#define USART_OVERSAMP_16_BIT	0

//Number of stop bits
#define USART_NumStopBit_HALF	1
#define USART_NumStopBit_1		0
#define USART_NumStopBit_2		2
#define USART_NumStopBit_3		3

//word length macros
#define USART_WordLength_8		0
#define USART_WordLength_9		1

//ParityControl
#define USART_NO_PARITY			0
#define USART_EVEN_PARITY		1
#define USART_ODD_PARITY		2

//Hardware flow control configurations
#define USART_HW_FLOW_CTRL_NONE    	0
#define USART_HW_FLOW_CTRL_CTS    	1
#define USART_HW_FLOW_CTRL_RTS    	2
#define USART_HW_FLOW_CTRL_CTS_RTS	3

//USART flags
#define USART_FLAG_TXE			(1 << 7)
#define USART_FLAG_RXNE			(1 << 5)
#define USART_FLAG_TC			(1 << 6)


void USART_PLCK_Control(USART_RegDef_t *pUSARTx, uint8_t EnorDi);
void USART_Init(USART_Handle_t *pUSARTHandle);
uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx, uint8_t flagname);
void USART_SendData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len);
void USART_ReceiveData(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len);


#endif /* INC_STM32F407XX_USART_DRIVER_H_ */

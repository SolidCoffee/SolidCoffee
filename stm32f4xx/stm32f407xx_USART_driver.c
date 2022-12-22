/*
 * stm32f407xx_USART_driver.c
 *
 *  Created on: Dec 17, 2022
 *      Author: gianl
 */

#include "stm32f407xx_USART_driver.h"

void USART_PLCK_Control(USART_RegDef_t *pUSARTx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		if(pUSARTx == USART1)
		{
			USART1_CLK_EN();
		}
		else if(pUSARTx == USART2)
		{
			USART2_CLK_EN();
		}
		else if(pUSARTx == USART3)
		{
			USART3_CLK_EN();
		}
		else if(pUSARTx == UART4)
		{
			UART4_CLK_EN();
		}
		else if(pUSARTx == UART5)
		{
			UART5_CLK_EN();
		}
		else if(pUSARTx == USART6)
		{
			USART6_CLK_EN();
		}
	}
	else
	{
		if(pUSARTx == USART1)
		{
			USART1_CLK_DI();
		}
		else if(pUSARTx == USART2)
		{
			USART2_CLK_DI();
		}
		else if(pUSARTx == USART3)
		{
			USART3_CLK_DI();
		}
		else if(pUSARTx == UART4)
		{
			UART4_CLK_DI();
		}
		else if(pUSARTx == UART5)
		{
			UART5_CLK_DI();
		}
		else if(pUSARTx == USART6)
		{
			USART6_CLK_DI();
		}
	}
}

void USART_Init(USART_Handle_t *pUSARTHandle)
{
	//turn on peripheral clock
	USART_PLCK_Control(pUSARTHandle->pUSARTx, ENABLE);

	//configure mode
	if(pUSARTHandle->USART_Config.USART_Mode == USART_MODE_TX_ONLY)
	{
		pUSARTHandle->pUSARTx->CR1 |= (1 << 3);
	}
	else if(pUSARTHandle->USART_Config.USART_Mode == USART_MODE_RX_ONLY)
	{
		pUSARTHandle->pUSARTx->CR1 |= (1 << 2);
	}
	else if(pUSARTHandle->USART_Config.USART_Mode == USART_MODE_TXRX)
	{
		pUSARTHandle->pUSARTx->CR1 |= (3 << 2);
	}

	//word length config
	pUSARTHandle->pUSARTx->CR1 |= (pUSARTHandle->USART_Config.USART_WordLength << 12);

	//Parity Config
	if(pUSARTHandle->USART_Config.USART_ParityControl == USART_NO_PARITY)
	{
		pUSARTHandle->pUSARTx->CR1 |= (0 << 10);
	}
	else if(pUSARTHandle->USART_Config.USART_ParityControl == USART_EVEN_PARITY)
	{
		pUSARTHandle->pUSARTx->CR1 |= (1 << 10);
		pUSARTHandle->pUSARTx->CR1 |= (0 << 9);
	}
	else if(pUSARTHandle->USART_Config.USART_ParityControl == USART_ODD_PARITY)
	{
		pUSARTHandle->pUSARTx->CR1 |= (1 << 10);
		pUSARTHandle->pUSARTx->CR1 |= (1 << 9);
	}

	//stop bits config
	pUSARTHandle->pUSARTx->CR2 |= (pUSARTHandle->USART_Config.USART_NumOfStopBits << 12);

	//hardware control flow
	if(pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS_RTS)
	{
		pUSARTHandle->pUSARTx->CR3 |= (3 << 8);
	}
	else if(pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_NONE)
	{
		pUSARTHandle->pUSARTx->CR3 |= (0 << 8);
		pUSARTHandle->pUSARTx->CR3 |= (0 << 9);
	}
	else if(pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS)
	{
		pUSARTHandle->pUSARTx->CR3 |= (1 << 9);
	}
	else if(pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_RTS)
	{
		pUSARTHandle->pUSARTx->CR3 |= (1 << 8);
	}

	//oversampling
	pUSARTHandle->pUSARTx->CR1 |= (pUSARTHandle->USART_Config.USART_OverSampling << 15);

	uint32_t UDIV = 0;
	uint32_t MENT = 0;
	uint32_t FRAC = 0;

	//Baud rate config
	if(pUSARTHandle->USART_Config.USART_OverSampling == USART_OVERSAMP_8_BIT)
	{
		UDIV=16000000/(8*pUSARTHandle->USART_Config.USART_Baud)*100;

		MENT= UDIV/100;

		FRAC = ((UDIV-(MENT*100))*8+50)/100;
	}
	else if(pUSARTHandle->USART_Config.USART_OverSampling == USART_OVERSAMP_16_BIT)
	{
		UDIV=16000000/(16*pUSARTHandle->USART_Config.USART_Baud)*100;

		MENT= UDIV/100;

		FRAC = ((UDIV-(MENT*100))*16+50)/100;
	}

	pUSARTHandle->pUSARTx->BRR |= (MENT << 4);
	pUSARTHandle->pUSARTx->BRR |= (FRAC << 0);
}

uint8_t USART_GetFlagStatus(USART_RegDef_t *pUSARTx, uint8_t flagname)
{
	if(pUSARTx->SR & flagname)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}


void USART_SendData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len)
{

	uint16_t *pdata; //don't think this extra step is needed
   //Loop over until "Len" number of bytes are transferred
	for(uint32_t i = 0 ; i < Len; i++)
	{
		//Implement the code to wait until TXE flag is set in the SR
		while(! USART_GetFlagStatus(pUSARTHandle->pUSARTx,USART_FLAG_TXE));

         //Check the USART_WordLength item for 9BIT or 8BIT in a frame
		if(pUSARTHandle->USART_Config.USART_WordLength == USART_WordLength_9)
		{
			//if 9BIT, load the DR with 2bytes masking the bits other than first 9 bits
			pdata = (uint16_t*) pTxBuffer;  //I think this can be ignored at the pTxBuffer can just be put in the equation bellow as a pointer
			pUSARTHandle->pUSARTx->DR = (*pdata & (uint16_t)0x01FF);

			//check for USART_ParityControl
			if(pUSARTHandle->USART_Config.USART_ParityControl == USART_NO_PARITY)
			{
				//No parity is used in this transfer. so, 9bits of user data will be sent
				//Implement the code to increment pTxBuffer twice
				pTxBuffer++;
				pTxBuffer++;
				//(uint16_t*)pTxBuffer   //could also do this instead of the twice above
			}
			else
			{
				//Parity bit is used in this transfer . so , 8bits of user data will be sent
				//The 9th bit will be replaced by parity bit by the hardware
				pTxBuffer++;
			}
		}
		else  //will mostly be doing this. Will load a byte into the buffer. Buffer size is 32 bits with only 9 usable so mask is just a safety
		{
			//This is 8bit data transfer
			pUSARTHandle->pUSARTx->DR = (*pTxBuffer  & (uint8_t)0xFF);

			//Implement the code to increment the buffer address
			pTxBuffer++;
		}
	}

	//Implement the code to wait till TC flag is set in the SR
	while( ! USART_GetFlagStatus(pUSARTHandle->pUSARTx,USART_FLAG_TC));
}


/*********************************************************************
 * @fn      		  - USART_ReceiveData
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              -

 */

void USART_ReceiveData(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len)
{
   //Loop over until "Len" number of bytes are transferred
	for(uint32_t i = 0 ; i < Len; i++)
	{
		//Implement the code to wait until RXNE flag is set in the SR
		while(! USART_GetFlagStatus(pUSARTHandle->pUSARTx,USART_FLAG_RXNE));

		//Check the USART_WordLength to decide whether we are going to receive 9bit of data in a frame or 8 bit
		if(pUSARTHandle->USART_Config.USART_WordLength == USART_WordLength_9)
		{
			//We are going to receive 9bit data in a frame

			//check are we using USART_ParityControl control or not
			if(pUSARTHandle->USART_Config.USART_ParityControl == USART_NO_PARITY)
			{
				//No parity is used. so, all 9bits will be of user data

				//read only first 9 bits. so, mask the DR with 0x01FF
				*((uint16_t*) pRxBuffer) = (pUSARTHandle->pUSARTx->DR  & (uint16_t)0x01FF);

				//Now increment the pRxBuffer two times
				pRxBuffer++;
				pRxBuffer++;
			}
			else
			{
				//Parity is used, so, 8bits will be of user data and 1 bit is parity
				 *pRxBuffer = (pUSARTHandle->pUSARTx->DR  & (uint8_t)0xFF);

				 //Increment the pRxBuffer
				 pRxBuffer++;
			}
		}
		else
		{
			//We are going to receive 8bit data in a frame

			//check are we using USART_ParityControl control or not
			if(pUSARTHandle->USART_Config.USART_ParityControl == USART_NO_PARITY)
			{
				//No parity is used , so all 8bits will be of user data

				//read 8 bits from DR
				 *pRxBuffer = (pUSARTHandle->pUSARTx->DR  & (uint16_t)0x0FF);
			}

			else
			{
				//Parity is used, so , 7 bits will be of user data and 1 bit is parity

				//read only 7 bits , hence mask the DR with 0X7F
				 *pRxBuffer = (uint8_t) 0x7F;

			}

			//increment the pRxBuffer
			pRxBuffer++;
		}
	}

}

/**********************************************************************
 * @fn      		  - USART_SendDataWithIT
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              - Resolve all the TODOs


uint8_t USART_SendDataIT(USART_Handle_t *pUSARTHandle,uint8_t *pTxBuffer, uint32_t Len)
{
	uint8_t txstate = pUSARTHandle->TODO;

	if(txstate != USART_BUSY_IN_TX)
	{
		pUSARTHandle->TODO = Len;
		pUSARTHandle->pTxBuffer = TODO;
		pUSARTHandle->TxBusyState = TODO;

		//Implement the code to enable interrupt for TXE
		TODO


		//Implement the code to enable interrupt for TC
		TODO


	}

	return txstate;

}



 * @fn      		  - USART_ReceiveDataIT
 *
 * @brief             -
 *
 * @param[in]         -
 * @param[in]         -
 * @param[in]         -
 *
 * @return            -
 *
 * @Note              - Resolve all the TODOs


uint8_t USART_ReceiveDataIT(USART_Handle_t *pUSARTHandle,uint8_t *pRxBuffer, uint32_t Len)
{
	uint8_t rxstate = pUSARTHandle->TODO;

	if(rxstate != TODO)
	{
		pUSARTHandle->RxLen = Len;
		pUSARTHandle->pRxBuffer = TODO;
		pUSARTHandle->RxBusyState = TODO;

		//Implement the code to enable interrupt for RXNE
		TODO

	}

	return rxstate;

}*/

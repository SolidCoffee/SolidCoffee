#include "stm32f407xx_I2C_driver.h"

uint16_t AHB_PreScaler[8] = {2,4,8,16,64,128,256,512};
uint16_t APB1_PreScaler[4] = {2,4,8,16};

static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx);
static void I2C_ExecuteAddressPhase(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr);
static void I2C_ClearADDRFlag(I2C_RegDef_t *pI2Cx);
static void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx);

void I2C_PeriClockControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
		{
			if(pI2Cx == I2C1)
			{
				I2C1_PCLK_EN();
			}
			else if(pI2Cx == I2C2)
			{
				I2C2_PCLK_EN();
			}
			else if(pI2Cx == I2C3)
			{
				I2C3_PCLK_EN();
			}
		}
		else
		{
			if(pI2Cx == I2C1)
			{
				I2C1_PCLK_DI();
			}
			else if(pI2Cx == I2C2)
			{
				I2C2_PCLK_DI();
			}
			else if(pI2Cx == I2C3)
			{
				I2C3_PCLK_DI();
			}
		}
}

uint32_t RCC_GetPLLOutputClock(void)
{
	return 0;//we dont use this function 
}

uint32_t RCC_GetPCLK1Value(void)
{
	uint32_t pclk1,SystemClk;
	uint8_t clksrc, temp, ahbp, apb1;

	clksrc = (RCC->CFGR >> 2) & 0x3;

	if(clksrc == 0)
	{
		SystemClk = 16000000;
	}
	else if(clksrc == 1)
	{
		SystemClk = 8000000;
	}
	else if(clksrc == 2)
	{
		SystemClk = RCC_GetPLLOutputClock();
	}

	temp = ((RCC->CFGR >> 4) & 0xF);

	if(temp < 8)
	{
		ahbp = 1;
	}
	else
	{
		ahbp = AHB_PreScaler[temp-8];
	}

	temp = ((RCC->CFGR >> 10) & 0x7);

	if(temp < 4)
	{
		apb1 = 1;
	}
	else
	{
		apb1 = APB1_PreScaler[temp-4];
	}

	pclk1 = (SystemClk / ahbp) / apb1;

	return pclk1;
}

void I2C_init(I2C_Handle_t *pI2CHandle)
{
	uint32_t tempreg = 0;

	//ack control bit
	pI2CHandle->pI2Cx->CR1 |= (pI2CHandle->I2C_Config.I2C_ACKControl << 10);

	//configure the FREQ field of CR2
	tempreg = 0;
	tempreg |= RCC_GetPCLK1Value() / 1000000U;
	pI2CHandle->pI2Cx->CR2 = (tempreg & 0x3F);

	//storing slave address
	tempreg |= (pI2CHandle->I2C_Config.I2C_DeviceAddress << 1);
	tempreg |= (1 << 14);
	pI2CHandle->pI2Cx->OAR1 = tempreg;

	//CCR
	uint16_t ccr_value = 0;
	tempreg = 0;
	if(pI2CHandle->I2C_Config.I2C_SCLSpeed <= I2C_SM)
	{
		//standard mode
		ccr_value = (RCC_GetPCLK1Value() / (2*pI2CHandle->I2C_Config.I2C_SCLSpeed));
		tempreg |= (ccr_value & 0xFFF);
	}
	else
	{
		//fast mode
		tempreg |= (1 << 15); //setting the mode to fast mode since it is in SM by default
		tempreg |= (pI2CHandle->I2C_Config.I2C_FMDutyCycle << 14); //setting the duty to the duty bit in the CCR register

		//calcuate the CCR value
		if(pI2CHandle->I2C_Config.I2C_FMDutyCycle == DUTY2)
		{
			ccr_value = (RCC_GetPCLK1Value() / (3*pI2CHandle->I2C_Config.I2C_SCLSpeed));
		}
		else
		{
			ccr_value = (RCC_GetPCLK1Value() / (25*pI2CHandle->I2C_Config.I2C_SCLSpeed));
		}
		tempreg |= (ccr_value & 0xFFF);
	}
	pI2CHandle->pI2Cx->CCR = tempreg;
}

//Sending the data****************************************************************************************************************
static void I2C_GenerateStartCondition(I2C_RegDef_t *pI2Cx)
{
	pI2Cx->CR1 |= (1 << 8);
}

uint8_t I2C_GetFlagStatus(I2C_RegDef_t *pI2Cx, uint32_t FlagName)
{
	if(pI2Cx->SR1 & FlagName)
	{
		return FLAG_SET;
	}
	return FLAG_RESET;
}

static void I2C_ExecuteAddressPhase(I2C_RegDef_t *pI2Cx, uint8_t SlaveAddr)
{
	SlaveAddr = SlaveAddr << 1; //moving the 7 bit address to the left by 1
	SlaveAddr &= ~(1 << 0); // clearing the first bit (read write bit)
	pI2Cx->DR = SlaveAddr; //writing the data to the DR which will send it to the slave

}

static void I2C_ClearADDRFlag(I2C_RegDef_t *pI2Cx)
{
	uint32_t dummyRead;
	dummyRead = pI2Cx->SR1;
	dummyRead = pI2Cx->SR2;
	(void)dummyRead;
}

static void I2C_GenerateStopCondition(I2C_RegDef_t *pI2Cx)
{
	pI2Cx->CR1 |= (1 << 9);
}

void I2C_MasterSendData(I2C_Handle_t *pI2CHandle, uint8_t *pTxBuffer, uint32_t Len, uint8_t SlaveAddr)
{
	//create the start condition
	I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

	//Check the SB flag
	while(! (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_SB)));

	//Send the addres of the slaev with R/W bit set to 0 (write)
	I2C_ExecuteAddressPhase(pI2CHandle->pI2Cx, SlaveAddr);

	//confirm the address phase is completed by checking the ADDr flag in the SR1
	while(! (I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_ADDR)));

	//confirm the ADDR flag accoridng to its software sequence
	I2C_ClearADDRFlag(pI2CHandle->pI2Cx);

	while(Len > 0)
	{
		while(!(I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_TXE_FLAG))); //waiting to see if TXE flag is set
		pI2CHandle->pI2Cx->DR = *pTxBuffer;
		pTxBuffer++;
		Len--;
	}

	//Wait for TXE and BTF
	while(!(I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_TXE_FLAG)));
	while(!(I2C_GetFlagStatus(pI2CHandle->pI2Cx, I2C_BTF)));

	//generate the STOP conditon
	I2C_GenerateStopCondition(pI2CHandle->pI2Cx);

}

//**********************************************************************************************************************************

void I2C_DeInit(I2C_RegDef_t *pI2Cx)
{
	if(pI2Cx == I2C1)
	{
		I2C1_REG_RESET();
	}
	else if(pI2Cx == I2C2)
	{
		I2C2_REG_RESET();
	}
	else if(pI2Cx == I2C3)
	{
		I2C3_REG_RESET();
	}

}

void I2C_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
			{
				if(IRQNumber <= 31)
				{
					//program ISER0 register
					*NVIC_ISER0 |= ( 1 << IRQNumber );

				}else if(IRQNumber > 31 && IRQNumber < 64 ) //32 to 63
				{
					//program ISER1 register
					*NVIC_ISER1 |= ( 1 << (IRQNumber % 32) );
				}
				else if(IRQNumber >= 64 && IRQNumber < 96 )
				{
					//program ISER2 register //64 to 95
					*NVIC_ISER3 |= ( 1 << (IRQNumber % 64) );
				}
			}else
			{
				if(IRQNumber <= 31)
				{
					//program ICER0 register
					*NVIC_ICER0 |= ( 1 << IRQNumber );
				}else if(IRQNumber > 31 && IRQNumber < 64 )
				{
					//program ICER1 register
					*NVIC_ICER1 |= ( 1 << (IRQNumber % 32) );
				}
				else if(IRQNumber >= 6 && IRQNumber < 96 )
				{
					//program ICER2 register
					*NVIC_ICER3 |= ( 1 << (IRQNumber % 64) );
				}
			}
}

void I2C_IRQPriorityConfig(uint8_t IRQNumber, uint8_t IRQPriority)
{
	//fin the ipr register
	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;

	uint8_t shift_amount = (8 * iprx_section) + (8- NO_PR_BITS_IMPLEMENTED);
	*(NVIC_PR_BASE_ADDR + iprx) |= (IRQPriority << shift_amount);
}

void I2C_PeripheralControl(I2C_RegDef_t *pI2Cx, uint8_t EnorDi)
{
	if(EnorDi == ENABLE)
	{
		pI2Cx->CR1 |= (1 << 0);
	}
	else if(EnorDi == DISABLE)
	{
		pI2Cx->CR1 &= ~(1 << 0);
	}
}

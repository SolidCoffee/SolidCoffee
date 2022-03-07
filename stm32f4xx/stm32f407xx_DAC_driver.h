/*
 * stm32f407xx_DAC_driver.h
 *
 *  Created on: Mar 5, 2022
 *      Author: gianl
 */

#ifndef INC_STM32F407XX_DAC_DRIVER_H_
#define INC_STM32F407XX_DAC_DRIVER_H_

#include "stm32f407xx.h"

typedef struct
{
	uint8_t Channel;
	uint8_t Buffer;  //0=enabled by default
	uint8_t Trigger;
	uint8_t TrigSelect;
	uint8_t WaveGen;
	uint8_t MaskAmpSelect;
	uint8_t DMAEn;
	uint8_t DMAUnderRn;

}DAC_Config_t;

#define BUFFER		0
#define NOBUFFER	1



typedef struct
{
	//pointer to hold the base address for the GPIO peripheral
	DAC_RegDef_t *pDACx;
	DAC_Config_t DAC_Config;

}DAC_Handler_t;

void DAC_Clk_EnorDi(uint8_t EnorDi);
void DACInit(DAC_Handler_t *DAC_Handle);
void DAC_SoftwareTrigger(uint8_t Channel);
void analogWrite(uint8_t Channel, uint32_t Val);
void SineWaveGen(uint8_t Channel);
void analogDualWrite(uint32_t Val_1, uint32_t Val_2);
void DualSineWaveGen(void);
void DualOpposeSineWaveGen(uint32_t offset);




#endif /* INC_STM32F407XX_DAC_DRIVER_H_ */

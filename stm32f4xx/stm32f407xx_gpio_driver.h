//this header file is a driver specific header
#ifndef INC_STM32F407XX_GPIO_DRIVER_H_
#define INC_STM32F407XX_GPIO_DRIVER_H_

#include "stm32f407xx.h" //MCU specific data,

//this is a configureation structure  for a gpio pin
typedef struct
{
	uint8_t GPIO_PinNumber;
	uint8_t GPIO_PinMode;
	uint8_t GPIO_PinSpeed;
	uint8_t GPIO_pinPuPdControl;
	uint8_t GPIO_PinOPType;
	uint8_t GPIO_PinAltFunMode;

}GPIO_PinConfig_t;





//handler structure for a GPIO pin
typedef struct
{
	//pointer to hold the base address for the GPIO peripheral
	GPIO_RegDef_t *pGPIOx;
	GPIO_PinConfig_t GPIO_PinConfig;

}GPIO_Handler_t;


#define FALLEDGE		4
#define RISEEDGE		5
#define RFT				6


#define PUSHPULL		0
#define OPENDRAIN		1


#define LOW				0
#define MEDIUM			1
#define FAST			2
#define SPEEDHIGH			3

#define NOPUPD			0
#define PULLUP			1
#define PULLDOWN		2

#define AF0				0
#define AF1				1
#define AF2				2
#define AF3				3
#define AF4				4
#define AF5				5
#define AF6				6
#define AF7				7
#define AF8				8
#define AF9				9
#define AF10			10
#define AF11			11
#define AF12			12
#define AF13			13
#define AF14			14
#define AF15			15

void GPIO_PLCK_Control(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);
void GPIO_Init(GPIO_Handler_t *pGPIOHandle);
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber, uint16_t Value);
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value);
void GPIO_ToggleOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);
void GPIO_IRQITConfig(uint8_t IRQNumber, uint8_t EnorDi);
void GPIO_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void GPIO_IRQHandling(uint8_t PinNumber);



//prototypes for API supported by this driver





#endif /* INC_STM32F407XX_GPIO_DRIVER_H_ */

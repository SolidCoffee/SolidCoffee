#ifndef INC_STM32F407XX_H_
#define INC_STM32F407XX_H_

#include<stdint.h>

#define __vo volatile

/******************************************************************************
Processor specific details
*/

//interrupt set enable registers
#define NVIC_ISER0			((__vo uint32_t*)0xE000E100)
#define NVIC_ISER1			((__vo uint32_t*)0xE000E104)
#define NVIC_ISER2			((__vo uint32_t*)0xE000E108)
#define NVIC_ISER3			((__vo uint32_t*)0xE000E10C)

//Interrupt clear enable register
#define NVIC_ICER0			((__vo uint32_t*)0xE000E180)
#define NVIC_ICER1			((__vo uint32_t*)0xE000E184)
#define NVIC_ICER2			((__vo uint32_t*)0xE000E188)
#define NVIC_ICER3			((__vo uint32_t*)0xE000E18C)

//priority register interrupts
#define NVIC_PR_BASE_ADDR	((__vo uint32_t*)0xE0004000)

#define NO_PR_BITS_IMPLEMENTED		4



//memory addresses
#define FLASH_BASEADDR		0x08000000U  //THis is the base address of the flash
#define SRAM1_BASEADDR		0x20000000U //this is the base address of the SRAM1
#define SRAM2_BASEADDR		0x20001C00U  // this is the base address of the SRAM2
#define SRAM 				SRAM1_BASEADDR  //this is the base address of the SRAM which is equal to the SRAM1 base address
#define ROM					0x1fff0000U //this is the ROM base address

//bus addresses
#define PERIPH_BASE 		0x40000000U
#define APB1PERIPH_BASE 	PERIPH_BASE
#define APB2PERIPH_BASE		0x40010000U
#define AHB1PERIPH_BASE		0x40020000U
#define AHB2PERIPH_BASE		0x50000000U

//AHB1 peripheral addresses
#define GPIOA_BASE			((AHB1PERIPH_BASE)+(0x00))
#define GPIOB_BASE			((AHB1PERIPH_BASE)+(0x0400))
#define GPIOC_BASE			((AHB1PERIPH_BASE)+(0x0800))
#define GPIOD_BASE			((AHB1PERIPH_BASE)+(0x0C00))
#define GPIOE_BASE			((AHB1PERIPH_BASE)+(0x1000))
#define GPIOF_BASE			((AHB1PERIPH_BASE)+(0x1400))
#define GPIOG_BASE			((AHB1PERIPH_BASE)+(0x1800))
#define GPIOH_BASE			((AHB1PERIPH_BASE)+(0x1C00))
#define GPIOI_BASE			((AHB1PERIPH_BASE)+(0x2000))
#define GPIOJ_BASE			((AHB1PERIPH_BASE)+(0x2400))
#define GPIOK_BASE			((AHB1PERIPH_BASE)+(0x2800))
#define CRC_BASE			((AHB1PERIPH_BASE)+(0x3000))
#define RCC_BASE			((AHB1PERIPH_BASE)+(0x3800))
#define FLASH_INTERFACE_REG_BASE			((AHB1PERIPH_BASE)+(0x3C00))
#define BKPSRAM_BASE		((AHB1PERIPH_BASE)+(0x4000))
#define DMA1_BASE			((AHB1PERIPH_BASE)+(0x6000))
#define DMA2_BASE			((AHB1PERIPH_BASE)+(0x6400))
#define ETHERNET_MAC_BASE	((AHB1PERIPH_BASE)+(0x8000))
#define DMA2D_BASE			((AHB1PERIPH_BASE)+(0xB000))
#define USB_OTG_HS_BASE		0x40040000


//APB1 peripheral addresses
#define I2C1_BASE			((APB1PERIPH_BASE)+(0x5400))
#define I2C2_BASE			((APB1PERIPH_BASE)+(0x5800))
#define I2C3_BASE			((APB1PERIPH_BASE)+(0x5C00))
#define SPI2_BASE			((APB1PERIPH_BASE)+(0x3800))
#define SPI3_BASE			((APB1PERIPH_BASE)+(0x3C00))
#define USART2_BASE			((APB1PERIPH_BASE)+(0x4400))
#define USART3_BASE			((APB1PERIPH_BASE)+(0x4800))
#define UART4_BASE			((APB1PERIPH_BASE)+(0x4C00))
#define UART5_BASE			((APB1PERIPH_BASE)+(0x5000))


//APB2 peripheral addresses
#define SPI1_BASE			((APB2PERIPH_BASE)+(0X3000))
#define USART1_BASE			((APB2PERIPH_BASE)+(0X1000))
#define USART6_BASE			((APB2PERIPH_BASE)+(0X1400))
#define EXTI_BASE			((APB2PERIPH_BASE)+(0X3C00))
#define SYSCFG_BASE			((APB2PERIPH_BASE)+(0X3800))



typedef struct
{
	__vo uint32_t MODER;
	__vo uint32_t OTYPER;
	__vo uint32_t OSPEEDR;
	__vo uint32_t PUPDR;
	__vo uint32_t IDR;
	__vo uint32_t ODR;
	__vo uint32_t BSRR;
	__vo uint32_t LCKR;
	__vo uint32_t AFR[2];  //AFR[0] is "GPIO alternate function low register, AFR[1] is "GPIO alternate function high register

}GPIO_RegDef_t;

#define GPIOA				((GPIO_RegDef_t*)GPIOA_BASE)
#define GPIOB				((GPIO_RegDef_t*)GPIOB_BASE)
#define GPIOC				((GPIO_RegDef_t*)GPIOC_BASE)
#define GPIOD				((GPIO_RegDef_t*)GPIOD_BASE)
#define GPIOE				((GPIO_RegDef_t*)GPIOE_BASE)
#define GPIOF				((GPIO_RegDef_t*)GPIOF_BASE)
#define GPIOG				((GPIO_RegDef_t*)GPIOG_BASE)
#define GPIOH				((GPIO_RegDef_t*)GPIOH_BASE)
#define GPIOI				((GPIO_RegDef_t*)GPIOI_BASE)


typedef struct
{
	__vo uint32_t CR;
	__vo uint32_t PLLCFGR;
	__vo uint32_t CFGR;
	__vo uint32_t CIR;
	__vo uint32_t AHB1RSTR;
	__vo uint32_t AHB2RSTR;
	__vo uint32_t AHB3RSTR;
	__vo uint32_t Reserved1;
	__vo uint32_t APB1RSTR;
	__vo uint32_t APB2RSTR;
	__vo uint32_t Reserved2;
	__vo uint32_t Reserved3;
	__vo uint32_t AHB1ENR;
	__vo uint32_t AHB2ENR;
	__vo uint32_t AHB3ENR;
	__vo uint32_t Reserved4;
	__vo uint32_t APB1ENR;
	__vo uint32_t APB2ENR;
	__vo uint32_t Reserved5;
	__vo uint32_t Reserved6;
	__vo uint32_t AHB1LP_ENR;
	__vo uint32_t AHB2LP_ENR;
	__vo uint32_t AHB3LP_ENR;
	__vo uint32_t Reserved7;
	__vo uint32_t APB1LP_ENR;
	__vo uint32_t APB2LP_ENR;
	__vo uint32_t Reserved8;
	__vo uint32_t Reserved9;
	__vo uint32_t BDCR;
	__vo uint32_t CSR;
	__vo uint32_t Reserved10;
	__vo uint32_t Reserved11;
	__vo uint32_t SSCGR;
	__vo uint32_t PLLI2SC_FGR;
}RCC_RegDef_t;

#define RCC					((RCC_RegDef_t*)RCC_BASE)

typedef struct
{
	__vo uint32_t MEMRWP;
	__vo uint32_t PMC;
	__vo uint32_t EXTICR[4];
	__vo uint32_t RESERVED[2];
	__vo uint32_t CMPCR;
	__vo uint32_t RESERVED2[2];
	__vo uint32_t CFGR;
}SYSCFG_RegDef_t;

#define SYSCFG				((SYSCFG_RegDef_t*)SYSCFG_BASE)

//Peripheral register definition structure for EXTI
typedef struct
{
	__vo uint32_t IMR;
	__vo uint32_t EMR;
	__vo uint32_t FTSR;
	__vo uint32_t RTSR;
	__vo uint32_t SWIER;
	__vo uint32_t PR;
}EXTI_RegDef_t;


#define EXTI				((EXTI_RegDef_t*)EXTI_BASE)

typedef struct
{
	__vo uint32_t CR1;
	__vo uint32_t CR2;
	__vo uint32_t SR;
	__vo uint32_t DR;
	__vo uint32_t CRCPR;
	__vo uint32_t RXCRCR;
	__vo uint32_t TXCRCR;
	__vo uint32_t I2SCFGR;
	__vo uint32_t I2SPR;

}SPI_RegDef_t;

#define SPI1					((SPI_RegDef_t*)SPI1_BASE)
#define SPI2					((SPI_RegDef_t*)SPI2_BASE)
#define SPI3					((SPI_RegDef_t*)SPI3_BASE)


//IRQ interupt request
#define IRQ_NO_EXTI0		6
#define IRQ_NO_EXTI1		7
#define IRQ_NO_EXTI2		8
#define IRQ_NO_EXTI3		9
#define IRQ_NO_EXTI4		10
#define IRQ_NO_EXTI9_5		23
#define IRQ_NO_EXTI15_10	40


//enable clock for GPIOx peripherals
#define GPIOA_PCLK_EN()	(RCC->AHB1ENR |= (1 << 0))
#define GPIOB_PCLK_EN()	(RCC->AHB1ENR |= (1 << 1))
#define GPIOC_PCLK_EN()	(RCC->AHB1ENR |= (1 << 2))
#define GPIOD_PCLK_EN()	(RCC->AHB1ENR |= (1 << 3))
#define GPIOE_PCLK_EN()	(RCC->AHB1ENR |= (1 << 4))
#define GPIOF_PCLK_EN()	(RCC->AHB1ENR |= (1 << 5))
#define GPIOG_PCLK_EN()	(RCC->AHB1ENR |= (1 << 6))
#define GPIOH_PCLK_EN()	(RCC->AHB1ENR |= (1 << 7))
#define GPIOI_PCLK_EN()	(RCC->AHB1ENR |= (1 << 8))


//enable macros for I2Cx clock peripherals
#define I2C1_PLCLK_EN()	(RCC->APB1ENR |= (1 << 21))


//CLOCK ENABLE MACROS FOR spiX PERIPHERALS
#define	SPI1_PCLK_EN()	(RCC->APB2ENR |= (1 << 12))
#define	SPI2_PCLK_EN()	(RCC->APB1ENR |= (1 << 14))
#define SPI3_PCLK_EN()	(RCC->APB1ENR |= (1 << 15))

//Clock enable macros for SYSCFG peripheral
#define SYSCFG_PCLK_EN()	(RCC->APB2ENR |= (1 <<14))

//Clock disable macros for GPIOx peripherals
#define GPIOA_PCLK_DI()	(RCC->AHB1ENR &= ~(1 << 0))
#define GPIOB_PCLK_DI()	(RCC->AHB1ENR &= ~(1 << 1))
#define GPIOC_PCLK_DI()	(RCC->AHB1ENR &= ~(1 << 2))
#define GPIOD_PCLK_DI()	(RCC->AHB1ENR &= ~(1 << 3))
#define GPIOE_PCLK_DI()	(RCC->AHB1ENR &= ~(1 << 4))
#define GPIOF_PCLK_DI()	(RCC->AHB1ENR &= ~(1 << 5))
#define GPIOG_PCLK_DI()	(RCC->AHB1ENR &= ~(1 << 6))
#define GPIOH_PCLK_DI()	(RCC->AHB1ENR &= ~(1 << 7))
#define GPIOI_PCLK_DI()	(RCC->AHB1ENR &= ~(1 << 8))


//SPI clock disable
#define	SPI1_PCLK_DI()	(RCC->APB2ENR &= ~(1 << 12))
#define	SPI2_PCLK_DI()	(RCC->APB1ENR &= ~(1 << 14))
#define SPI3_PCLK_DI()	(RCC->APB1ENR &= ~(1 << 15))


//GPIO reset maco's
#define GPIOA_REG_RESET()		do{ (RCC->AHB1RSTR |= (1 << 0)); (RCC->AHB1RSTR &= ~(1 <<  0)); }while(0)
#define GPIOB_REG_RESET()		do{ (RCC->AHB1RSTR |= (1 << 1)); (RCC->AHB1RSTR &= ~(1 <<  1)); }while(0)
#define GPIOC_REG_RESET()		do{ (RCC->AHB1RSTR |= (1 << 2)); (RCC->AHB1RSTR &= ~(1 <<  2)); }while(0)
#define GPIOD_REG_RESET()		do{ (RCC->AHB1RSTR |= (1 << 3)); (RCC->AHB1RSTR &= ~(1 <<  3)); }while(0)
#define GPIOE_REG_RESET()		do{ (RCC->AHB1RSTR |= (1 << 4)); (RCC->AHB1RSTR &= ~(1 <<  4)); }while(0)
#define GPIOF_REG_RESET()		do{ (RCC->AHB1RSTR |= (1 << 5)); (RCC->AHB1RSTR &= ~(1 <<  5)); }while(0)
#define GPIOG_REG_RESET()		do{ (RCC->AHB1RSTR |= (1 << 6)); (RCC->AHB1RSTR &= ~(1 <<  6)); }while(0)
#define GPIOH_REG_RESET()		do{ (RCC->AHB1RSTR |= (1 << 7)); (RCC->AHB1RSTR &= ~(1 <<  7)); }while(0)
#define GPIOI_REG_RESET()		do{ (RCC->AHB1RSTR |= (1 << 8)); (RCC->AHB1RSTR &= ~(1 <<  8)); }while(0)

#define SPI1_REG_RESET()		do{ (RCC->APB1RSTR |= (1 << 12)); (RCC->APB1RSTR &= ~(1 << 12)); }while(0)
#define SPI2_REG_RESET()		do{ (RCC->APB2RSTR |= (1 << 14)); (RCC->APB2RSTR &= ~(1 << 14)); }while(0)
#define SPI3_REG_RESET()		do{ (RCC->APB2RSTR |= (1 << 15)); (RCC->APB2RSTR &= ~(1 << 15)); }while(0)


//base configuration number for EXTICR bit setting
#define GPIO_BASEADDR_TO_CODE(x)		((x == GPIOA) ? 0 :\
										(x == GPIOB) ? 1 :\
										(x == GPIOC) ? 2 :\
										(x == GPIOD) ? 3 :\
										(x == GPIOE) ? 4 :\
										(x == GPIOF) ? 5 :\
										(x == GPIOG) ? 6 :\
										(x == GPIOH) ? 7 :\
										(x == GPIOI) ? 8 :0)


#define ENABLE			1
#define DISABLE			0
#define SET				ENABLE
#define RESET			DISABLE

#define INPUT			0
#define OUTPUT			1
#define ALTFUNC			2
#define ANALOG			3

//bit positoin macros for SPI
#define CPHA			0
#define CPOL			1

#define FLAG_RESET		RESET
#define FLAG_SET		SET

#define BUSY			1
#define FREE			0

#endif /* INC_STM32F407XX_H_ */


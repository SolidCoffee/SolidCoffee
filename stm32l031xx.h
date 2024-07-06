/*
 * stm32l031xx.h
 *
 *  Created on: Jul 4, 2024
 *      Author: 18604
 */

#ifndef INC_STM32L031XX_H_
#define INC_STM32L031XX_H_

#include<stdint.h>
#include<stddef.h>
#include<stdio.h>
#include<string.h>

#define __vo volatile

//memory addresses
#define NVM_BASEADDR		0x08000000U
#define SRAM_BASEADDR		0x20000000U

//bus addresses
#define APB1_BASEADDR		0x40000000U
#define APB2_BASEADDR		0x40010000U
#define AHB_BASEADDR		0x40020000U
#define IOPORT_BASEADDR		0x50000000U

//APB1 bus
#define TIMER2_BASE			((APB1_BASEADDR)+(0x00))
#define TIMER3_BASE			((APB1_BASEADDR)+(0x0400))
#define TIMER6_BASE			((APB1_BASEADDR)+(0x1000))
#define TIMER7_BASE			((APB1_BASEADDR)+(0x1400))
#define RTC_BKP_REG_BASE	((APB1_BASEADDR)+(0x2800))
#define WWWDG_BASE			((APB1_BASEADDR)+(0x2C00))
#define IWDG_BASE			((APB1_BASEADDR)+(0x3000))
#define SPI2_BASE			((APB1_BASEADDR)+(0x3800))
#define USART2_BASE			((APB1_BASEADDR)+(0x4400))
#define LPUART1_BASE		((APB1_BASEADDR)+(0x4800))
#define USART4_BASE			((APB1_BASEADDR)+(0x4C00))
#define USART5_BASE			((APB1_BASEADDR)+(0x5000))
#define I2C1_BASE           ((APB1_BASEADDR)+(0x5400))
#define I2C2_BASE           ((APB1_BASEADDR)+(0x5800))
#define PWR_BASE            ((APB1_BASEADDR)+(0x7000))
#define	I2C3_BASE			((APB1_BASEADDR)+(0x7800))
#define LPTIM1_BASE         ((APB1_BASEADDR)+(0x7C00))

//APB2 buss
#define SYSCFG_BASE         ((APB2_BASEADDR)+(0x0000))
#define EXTI_BASE           ((APB2_BASEADDR)+(0x0400))
#define TIM21_BASE          ((APB2_BASEADDR)+(0x0800))
#define TIM22_BASE          ((APB2_BASEADDR)+(0x1400))
#define ADC1_BASE           ((APB2_BASEADDR)+(0x2400))
#define SPI1_BASE           ((APB2_BASEADDR)+(0x3000))
#define USART1_BASE         ((APB2_BASEADDR)+(0x3800))
#define DBG_BASE			((APB2_BASEADDR)+(0x5800))

// AHB bus
#define DMA1_BASE           ((AHB_BASEADDR)+(0x0000))
#define RCC_BASE            ((AHB_BASEADDR)+(0x1000))
#define FLASH_R_BASE        ((AHB_BASEADDR)+(0x2000))
#define CRC_BASE            ((AHB_BASEADDR)+(0x3000))
#define AES_BASE			((AHB_BASEADDR)+(0x6000))

//IOPORT
#define GPIOA_BASE          ((IOPORT_BASEADDR)+(0x0000))
#define GPIOB_BASE          ((IOPORT_BASEADDR)+(0x0400))
#define GPIOC_BASE          ((IOPORT_BASEADDR)+(0x0800))
#define GPIOD_BASE          ((IOPORT_BASEADDR)+(0x0C00))
#define GPIOE_BASE          ((IOPORT_BASEADDR)+(0x1000))
#define GPIOH_BASE          ((IOPORT_BASEADDR)+(0x1C00))

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
	__vo uint32_t BRR;

}GPIO_RegDef_t;

#define GPIOA			((GPIO_RegDef_t*)GPIOA_BASE)
#define GPIOB			((GPIO_RegDef_t*)GPIOB_BASE)
#define GPIOC			((GPIO_RegDef_t*)GPIOC_BASE)
#define GPIOD			((GPIO_RegDef_t*)GPIOD_BASE)
#define GPIOE			((GPIO_RegDef_t*)GPIOE_BASE)
#define GPIOH			((GPIO_RegDef_t*)GPIOH_BASE)

typedef struct
{
	__vo uint32_t CR;
	__vo uint32_t ICSCR;
	__vo uint32_t Reserved1;
	__vo uint32_t CFGR;
	__vo uint32_t CIER;
	__vo uint32_t CIFR;
	__vo uint32_t CICR;
	__vo uint32_t IOPRSTR;
	__vo uint32_t AHBRSTR;
	__vo uint32_t APB2RSTR;
	__vo uint32_t APB1RSTR;
	__vo uint32_t IOPENR;
	__vo uint32_t AHBENR;
	__vo uint32_t APB2ENR;
	__vo uint32_t APB1ENR;
	__vo uint32_t IOPSMEN;
	__vo uint32_t AHBSMENR;
	__vo uint32_t APB2SMENR;
	__vo uint32_t APB1SMENR;
	__vo uint32_t CCIPR;
	__vo uint32_t CSR;
}RCC_RegDef_t;

#define RCC					((RCC_RegDef_t*)RCC_BASE)

typedef struct
{
	__vo uint32_t CFGR1;
	__vo uint32_t CFGR2;
	__vo uint32_t EXTICR[4];
	__vo uint32_t COMP[2];
	__vo uint32_t CFGR3;

}SYSCFG_RegDef_t;

#define SYSCFG				((SYSCFG_RegDef_t*)SYSCFG_BASE)



//enable clock for GPIOx peripherals
#define GPIOA_PCLK_EN()  (RCC->IOPENR |= (1 << 0))
#define GPIOB_PCLK_EN()  (RCC->IOPENR |= (1 << 1))
#define GPIOC_PCLK_EN()  (RCC->IOPENR |= (1 << 2))
#define GPIOD_PCLK_EN()  (RCC->IOPENR |= (1 << 3))
#define GPIOE_PCLK_EN()  (RCC->IOPENR |= (1 << 4))
#define GPIOH_PCLK_EN()  (RCC->IOPENR |= (1 << 7))

//disable clock for GPIOx peripherals
#define GPIOA_PCLK_DI()  (RCC->IOPENR &= ~(1 << 0))
#define GPIOB_PCLK_DI()  (RCC->IOPENR &= ~(1 << 1))
#define GPIOC_PCLK_DI()  (RCC->IOPENR &= ~(1 << 2))
#define GPIOD_PCLK_DI()  (RCC->IOPENR &= ~(1 << 3))
#define GPIOE_PCLK_DI()  (RCC->IOPENR &= ~(1 << 4))
#define GPIOH_PCLK_DI()  (RCC->IOPENR &= ~(1 << 7))

//GPIO reset maco's
#define GPIOA_REG_RESET()      do { (RCC->IOPRSTR |= (1 << 0)); (RCC->IOPRSTR &= ~(1 <<  0)); } while(0)
#define GPIOB_REG_RESET()      do { (RCC->IOPRSTR |= (1 << 1)); (RCC->IOPRSTR &= ~(1 <<  1)); } while(0)
#define GPIOC_REG_RESET()      do { (RCC->IOPRSTR |= (1 << 2)); (RCC->IOPRSTR &= ~(1 <<  2)); } while(0)
#define GPIOD_REG_RESET()      do { (RCC->IOPRSTR |= (1 << 3)); (RCC->IOPRSTR &= ~(1 <<  3)); } while(0)
#define GPIOE_REG_RESET()      do { (RCC->IOPRSTR |= (1 << 4)); (RCC->IOPRSTR &= ~(1 <<  4)); } while(0)
#define GPIOH_REG_RESET()      do { (RCC->IOPRSTR |= (1 << 7)); (RCC->IOPRSTR &= ~(1 <<  7)); } while(0)

#define ENABLE			1
#define DISABLE			0
#define SET				ENABLE
#define RESET			DISABLE
#define HIGH			1

#define INPUT			0
#define OUTPUT			1
#define ALTFUNC			2
#define ANALOG			3
#define INTERRUPT		4

#include "stm32l031xx_GPIO_driver.h"



#endif /* INC_STM32L031XX_H_ */

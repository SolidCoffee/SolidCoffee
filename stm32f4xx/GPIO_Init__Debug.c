void GPIO_Init(GPIO_Handler_t *pGPIOHandle)
{
	uint32_t temp=0;

	//enable the peripheral clock

	GPIO_PLCK_Control(pGPIOHandle->pGPIOX, ENABLE);

	//configure the mode of the gpio pin
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode <= ANALOG)
	{
		//non interrupt mode
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOX->MODER &= ~(3 << (2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOX->MODER |=temp;
		temp=0;
	}
	else
	{
		if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == FALLEDGE)
		{
			// configure the FTSR
			EXTI->FTSR |= (1  << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			//clear the RTSR bit
			EXTI->RTSR &= ~(1  << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == RISEEDGE)
		{
			//configure the RTSR
			EXTI->RTSR |= (1  << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			//clear the FTSR bit
			EXTI->FTSR &= ~(1  << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}
		else if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == RFT)
		{
			//configure  both the RTSR and FTSR
			EXTI->RTSR |= (1  << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			EXTI->FTSR |= (1  << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
		}

		// configure the GPIO port selection in SYSCFG_EXTICR
		uint8_t temp1 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber /  4;
		uint8_t temp2 = pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber % 4;
		uint8_t portcode = GPIO_BASEADDR_TO_CODE(pGPIOHandle->pGPIOX);
		SYSCFG_PCLK_EN();
		SYSCFG->EXTICR[temp1] = (portcode << (4* temp2));

		//Enable the exti interrupt delivery
		EXTI->IMR |= (1  << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
	}

	//configure the  speed
	temp=0;

	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinSpeed<< (2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
			pGPIOHandle->pGPIOX->OSPEEDR &= (3 << (2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
			pGPIOHandle->pGPIOX->OSPEEDR |= temp;

	//configure the pupd settings
	temp=0;

	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_pinPuPdControl << (2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
			pGPIOHandle->pGPIOX->PUPDR &= ~(3 << (2*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
			pGPIOHandle->pGPIOX->PUPDR |= temp;

	//configure  the optype
	temp=0;

	temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinOPType << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			pGPIOHandle->pGPIOX->OTYPER &= ~(1 << pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber);
			pGPIOHandle->pGPIOX->OTYPER |= temp;

	//configure the alt functionality
	temp =0;
	if(pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == ALTFUNC)
	{
		//configure the alt function registers
		if(pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber <= 7)
		{
			temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
			pGPIOHandle->pGPIOX->AFR[0] &= ~(0xF << (4*pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
			pGPIOHandle->pGPIOX->AFR[0] |=temp;
		}
		else
		{
			temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinAltFunMode << (4*(pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber%8)));
				pGPIOHandle->pGPIOX->AFR[1] &= ~(0xF << (4*(pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber%8)));
				pGPIOHandle->pGPIOX->AFR[1] |= temp;
		}
	}
}

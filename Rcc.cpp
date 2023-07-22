/***************************************************************************************/
/*************             Author: Mohamed Hussein              ************************/
/*************             Layer: MCAL                          ************************/
/*************             Peripheral: RCC                      ************************/
/*************             Version: V1.0 - 19/07/2023           ************************/
/*************             MC: STM32F103C8T6 | ARM Cortex M3    ************************/
/***************************************************************************************/

#include "Rcc.h"
#include "Rcc_Pri.h"
#include "Rcc_Cfg.h"

RCC_TypeDef* Rcc_MemoryBase = (RCC_TypeDef*) RCC_BASE;

Rcc::Rcc()
{
	u32 Local_u32Timeout = 0;
	Rcc_ErrorType_t Error = Rcc_Default;

#if Rcc_Clock_Type == Rcc_Hsi
	/*choose HSI as system clock*/
	Rcc_MemoryBase->CFGR |= RCC_CFGR_SW_HSI;
	/*Enable HSI + default Trimming = 16*/
	Rcc_MemoryBase->CR |= RCC_CR_HSION; 
	Rcc_MemoryBase->CR |= (RCC_CR_HSITRIM & 0x80); 
	/*check if HSI clock is stable or not*/
	while( ((Rcc_MemoryBase->CR & RCC_CR_HSIRDY )== 0) && (Local_u32Timeout < 10000) )
	{
		Local_u32Timeout++;
	}

	if(Local_u32Timeout >= 10000)
	{
		Error = Rcc_HsiNotReady;
	}
#elif Rcc_Clock_Type == Rcc_Hse_Crystal
	/*choose HSE as system clock*/
	Rcc_MemoryBase->CFGR |= RCC_CFGR_SWS_HSE;
	/*Enable HSE with no bypass */
	SET_BIT(M_RCC->CR, 16);
	CLR_BIT(M_RCC->CR, 18);
	while( (GET_BIT(M_RCC->CR, 17) == 0) && (Local_u32Timeout < 10000) )
	{
		Local_u32Timeout++;
	}
	if(Local_u32Timeout >= 10000)
	{
		/*Timeout*/
	}
#elif RCC_CLOCK_TYPE == RCC_HSE_RC
	/*to choose bypass, HSE must be disabled first so it can be written*/
	CLR_BIT(M_RCC->CR, 16);
	/*choose bypass */
	SET_BIT(M_RCC->CR, 18);
	/*choose HSE as system clock*/
	SET_BIT(M_RCC->CFGR, 0);
	CLR_BIT(M_RCC->CFGR, 1);
	/*Enable HSE*/
	SET_BIT(M_RCC->CR, 16);
	while( (GET_BIT(M_RCC->CR, 17) == 0) && (Local_u32Timeout < 10000) )
	{
		Local_u32Timeout++;
	}
	if(Local_u32Timeout >= 10000)
	{
		/*Timeout*/
	}
#elif RCC_CLOCK_TYPE == RCC_PLL
	/*choose PLL as system clock*/
	CLR_BIT(M_RCC->CFGR, 0);
	SET_BIT(M_RCC->CFGR, 1);

	/* Choosing The Multiplication Factor For PLL */
#if (RCC_PLL_MUL_VAL >= RCC_PLL_MUL_BY_2) && (RCC_PLL_MUL_VAL <= RCC_PLL_MUL_BY_16)
	M_RCC->CFGR &= RCC_PLL_MUL_MASK;
	M_RCC->CFGR |= (RCC_PLL_MUL_VAL << 18);
#else
#error ("Wrong Multiplication Factor For PLL.")
#endif  //end if for PLL clock

	/*choose HSI or HSE as PLL input source*/
#if RCC_PLL_IN_CLOCK == RCC_PLL_IN_HSI_DIV_BY_2
	/*Enable HSI*/
	SET_BIT(M_RCC->CR, 0);
	/* PLL Entery Clock Source Is HSI Divided By 2 */
	CLR_BIT(M_RCC->CFGR, 16);
#elif RCC_PLL_IN_CLOCK == RCC_PLL_IN_HSE_DIV_BY_2
	/*Enable HSE*/
	SET_BIT(M_RCC->CR, 16);
	/*HSE is divided by 2*/
	SET_BIT(M_RCC->CFGR, 17);
	/* PLL Entery Clock Source Is HSE*/
	SET_BIT(M_RCC->CFGR, 16);
#elif RCC_PLL_IN_CLOCK == RCC_PLL_IN_HSE
	/*Enable HSE*/
	SET_BIT(M_RCC->CR, 16);
	/*HSE is divided by 2*/
	CLR_BIT(M_RCC->CFGR, 17);
	/* PLL Entery Clock Source Is HSE*/
	SET_BIT(M_RCC->CFGR, 16);
#else
#error ("Wrong PLL input source.")
#endif //end if for PLL input source

	/*Enable PLL*/
	SET_BIT(M_RCC->CR, 24);
	while( (GET_BIT(M_RCC->CR, 25) == 0) && (Local_u32Timeout < 10000) )
	{
		Local_u32Timeout++;
	}
	if(Local_u32Timeout >= 10000)
	{
		/*Timeout*/
	}

#else
#error ("Wrong System Clock choice.")
#endif     //end if for RCC clock type

	/*for Clock security system*/
#if RCC_CLOCK_SECURITY == RCC_CSS_DISABLE
	CLR_BIT(M_RCC->CR, 19);
#elif RCC_CLOCK_SECURITY == RCC_CSS_ENABLE
	SET_BIT(M_RCC->CR, 19);
#else
#error ("Wrong Clock security system choice.")
#endif

	/*for AHB prescaler*/
#if (RCC_AHB_PRESCALER >= RCC_AHB_NOT_DIVIDED) &&  (RCC_AHB_PRESCALER <= RCC_AHB_DIV_BY_512)
	M_RCC->CFGR &= RCC_AHB_PRESCALER_MASK;
	M_RCC->CFGR |= (RCC_AHB_PRESCALER << 4);
#else
#error ("Wrong AHB prescaler choice.")
#endif

	/*for APB1 prescaler*/
#if (RCC_APB1_PRESCALER >= RCC_APB1_NOT_DIVIDED) &&  (RCC_APB1_PRESCALER <= RCC_APB1_DIV_BY_16)
	M_RCC->CFGR &= RCC_APB1_PRESCALER_MASK;
	M_RCC->CFGR |= (RCC_APB1_PRESCALER << 8);
#else
#error ("Wrong APB1 prescaler choice.")
#endif

	/*for APB2 prescaler*/
#if (RCC_APB2_PRESCALER >= RCC_APB2_NOT_DIVIDED) &&  (RCC_APB2_PRESCALER <= RCC_APB2_DIV_BY_16)
	M_RCC->CFGR &= RCC_APB2_PRESCALER_MASK;
	M_RCC->CFGR |= (RCC_APB2_PRESCALER << 11);
#else
#error ("Wrong APB2 prescaler choice.")
#endif

	/*for ADC prescaler*/
#if (RCC_ADC_PRESCALER >= RCC_ADC_DIV_BY_2) &&  (RCC_ADC_PRESCALER <= RCC_ADC_DIV_BY_8)
	M_RCC->CFGR &= RCC_ADC_PRESCALER_MASK;
	M_RCC->CFGR |= (RCC_ADC_PRESCALER << 14);
#else
#error ("Wrong APB1 prescaler choice.")
#endif
}

Rcc_ErrorType_t Rcc::Rcc_EnablePeripheral (Rcc_BusName_t Bus, Rcc_PeripheralName_t Peripheral)
{
	Rcc_ErrorType_t Error = Rcc_Default;
	
	if(Bus == Rcc_Ahb)
	{
		switch(Peripheral)
		{
			case Rcc_Dma1: Rcc_MemoryBase->AHBENR |= RCC_AHBENR_DMA1EN;		Error = Rcc_Ok;  break;
			case Rcc_Sram: Rcc_MemoryBase->AHBENR |= RCC_AHBENR_SRAMEN;		Error = Rcc_Ok;  break;
			case Rcc_Flitf: Rcc_MemoryBase->AHBENR |= RCC_AHBENR_FLITFEN;		Error = Rcc_Ok;  break;
			case Rcc_Crc: Rcc_MemoryBase->AHBENR |= RCC_AHBENR_CRCEN;		Error = Rcc_Ok;  break;
			
			default: Error = Rcc_WrongPeripheral;				break;
		}
	}
	else if(Bus == Rcc_Apb2)
	{
		switch(Peripheral)
		{
			case Rcc_Afio: Rcc_MemoryBase->APB2ENR |= RCC_APB2ENR_AFIOEN;		Error = Rcc_Ok;  break;
			case Rcc_Gpioa: Rcc_MemoryBase->APB2ENR |= RCC_APB2ENR_IOPAEN;		Error = Rcc_Ok;  break;
			case Rcc_Gpiob: Rcc_MemoryBase->APB2ENR |= RCC_APB2ENR_IOPBEN;		Error = Rcc_Ok;  break;
			case Rcc_Gpioc: Rcc_MemoryBase->APB2ENR |= RCC_APB2ENR_IOPCEN;		Error = Rcc_Ok;  break;
			case Rcc_Gpiod: Rcc_MemoryBase->APB2ENR |= RCC_APB2ENR_IOPDEN;		Error = Rcc_Ok;  break;
			case Rcc_Gpioe: Rcc_MemoryBase->APB2ENR |= RCC_APB2ENR_IOPEEN;		Error = Rcc_Ok;  break;
			case Rcc_Adc1: Rcc_MemoryBase->APB2ENR |= RCC_APB2ENR_ADC1EN;		Error = Rcc_Ok;  break;
			case Rcc_Adc2: Rcc_MemoryBase->APB2ENR |= RCC_APB2ENR_ADC2EN;		Error = Rcc_Ok;  break;
			case Rcc_Spi1: Rcc_MemoryBase->APB2ENR |= RCC_APB2ENR_SPI1EN;		Error = Rcc_Ok;  break;
			case Rcc_Tim1: Rcc_MemoryBase->APB2ENR |= RCC_APB2ENR_TIM1EN;		Error = Rcc_Ok;  break;
			case Rcc_Usart1: Rcc_MemoryBase->APB2ENR |= RCC_APB2ENR_USART1EN;		Error = Rcc_Ok;  break;
			
			default: Error = Rcc_WrongPeripheral;				break;
		}
	}
	else if(Bus == Rcc_Apb1)
	{
		switch(Peripheral)
		{
			case Rcc_Tim2: Rcc_MemoryBase->APB1ENR |= RCC_APB1ENR_TIM2EN;		Error = Rcc_Ok;  break;
			case Rcc_Tim3: Rcc_MemoryBase->APB1ENR |= RCC_APB1ENR_TIM3EN;		Error = Rcc_Ok;  break;
			case Rcc_Tim4: Rcc_MemoryBase->APB1ENR |= RCC_APB1ENR_TIM4EN;		Error = Rcc_Ok;  break;
			case Rcc_Wwd: Rcc_MemoryBase->APB1ENR |= RCC_APB1ENR_WWDGEN;		Error = Rcc_Ok;  break;
			case Rcc_Spi2: Rcc_MemoryBase->APB1ENR |= RCC_APB1ENR_SPI2EN;		Error = Rcc_Ok;  break;
			case Rcc_Usart2: Rcc_MemoryBase->APB1ENR |= RCC_APB1ENR_USART2EN;		Error = Rcc_Ok;  break;
			case Rcc_Usart3: Rcc_MemoryBase->APB1ENR |= RCC_APB1ENR_USART3EN;		Error = Rcc_Ok;  break;
			case Rcc_I2c1: Rcc_MemoryBase->APB1ENR |= RCC_APB1ENR_I2C1EN;		Error = Rcc_Ok;  break;
			case Rcc_I2c2: Rcc_MemoryBase->APB1ENR |= RCC_APB1ENR_I2C2EN;		Error = Rcc_Ok;  break;
			case Rcc_Usb: Rcc_MemoryBase->APB1ENR |= RCC_APB1ENR_USBEN;		Error = Rcc_Ok;  break;
			case Rcc_Can: Rcc_MemoryBase->APB1ENR |= RCC_APB1ENR_CAN1EN;		Error = Rcc_Ok;  break;
			case Rcc_Bkp: Rcc_MemoryBase->APB1ENR |= RCC_APB1ENR_BKPEN;		Error = Rcc_Ok;  break;
			case Rcc_Pwr: Rcc_MemoryBase->APB1ENR |= RCC_APB1ENR_PWREN;		Error = Rcc_Ok;  break;
			
			default: Error = Rcc_WrongPeripheral;				break;
		}
	}
	else
		Error = Rcc_WrongBus;
	
	
	return Error;
}

Rcc_ErrorType_t Rcc::Rcc_DisablePeripheral (Rcc_BusName_t Bus, Rcc_PeripheralName_t Peripheral)
{
	Rcc_ErrorType_t Error = Rcc_Default;
	
	if(Bus == Rcc_Ahb)
	{
		switch(Peripheral)
		{
			case Rcc_Dma1: Rcc_MemoryBase->AHBENR &= ~RCC_AHBENR_DMA1EN;		Error = Rcc_Ok;  break;
			case Rcc_Sram: Rcc_MemoryBase->AHBENR &= ~RCC_AHBENR_SRAMEN;		Error = Rcc_Ok;  break;
			case Rcc_Flitf: Rcc_MemoryBase->AHBENR &= ~RCC_AHBENR_FLITFEN;		Error = Rcc_Ok;  break;
			case Rcc_Crc: Rcc_MemoryBase->AHBENR &= ~RCC_AHBENR_CRCEN;		Error = Rcc_Ok;  break;
			
			default: Error = Rcc_WrongPeripheral;				break;
		}
	}
	else if(Bus == Rcc_Apb2)
	{
		switch(Peripheral)
		{
			case Rcc_Afio: Rcc_MemoryBase->APB2ENR &= ~RCC_APB2ENR_AFIOEN;		Error = Rcc_Ok;  break;
			case Rcc_Gpioa: Rcc_MemoryBase->APB2ENR &= ~RCC_APB2ENR_IOPAEN;		Error = Rcc_Ok;  break;
			case Rcc_Gpiob: Rcc_MemoryBase->APB2ENR &= ~RCC_APB2ENR_IOPBEN;		Error = Rcc_Ok;  break;
			case Rcc_Gpioc: Rcc_MemoryBase->APB2ENR &= ~RCC_APB2ENR_IOPCEN;		Error = Rcc_Ok;  break;
			case Rcc_Gpiod: Rcc_MemoryBase->APB2ENR &= ~RCC_APB2ENR_IOPDEN;		Error = Rcc_Ok;  break;
			case Rcc_Gpioe: Rcc_MemoryBase->APB2ENR &= ~RCC_APB2ENR_IOPEEN;		Error = Rcc_Ok;  break;
			case Rcc_Adc1: Rcc_MemoryBase->APB2ENR &= ~RCC_APB2ENR_ADC1EN;		Error = Rcc_Ok;  break;
			case Rcc_Adc2: Rcc_MemoryBase->APB2ENR &= ~RCC_APB2ENR_ADC2EN;		Error = Rcc_Ok;  break;
			case Rcc_Spi1: Rcc_MemoryBase->APB2ENR &= ~RCC_APB2ENR_SPI1EN;		Error = Rcc_Ok;  break;
			case Rcc_Tim1: Rcc_MemoryBase->APB2ENR &= ~RCC_APB2ENR_TIM1EN;		Error = Rcc_Ok;  break;
			case Rcc_Usart1: Rcc_MemoryBase->APB2ENR &= ~RCC_APB2ENR_USART1EN;		Error = Rcc_Ok;  break;
			
			default: Error = Rcc_WrongPeripheral;				break;
		}
	}
	else if(Bus == Rcc_Apb1)
	{
		switch(Peripheral)
		{
			case Rcc_Tim2: Rcc_MemoryBase->APB1ENR &= ~RCC_APB1ENR_TIM2EN;		Error = Rcc_Ok;  break;
			case Rcc_Tim3: Rcc_MemoryBase->APB1ENR &= ~RCC_APB1ENR_TIM3EN;		Error = Rcc_Ok;  break;
			case Rcc_Tim4: Rcc_MemoryBase->APB1ENR &= ~RCC_APB1ENR_TIM4EN;		Error = Rcc_Ok;  break;
			case Rcc_Wwd: Rcc_MemoryBase->APB1ENR &= ~RCC_APB1ENR_WWDGEN;		Error = Rcc_Ok;  break;
			case Rcc_Spi2: Rcc_MemoryBase->APB1ENR &= ~RCC_APB1ENR_SPI2EN;		Error = Rcc_Ok;  break;
			case Rcc_Usart2: Rcc_MemoryBase->APB1ENR &= ~RCC_APB1ENR_USART2EN;		Error = Rcc_Ok;  break;
			case Rcc_Usart3: Rcc_MemoryBase->APB1ENR &= ~RCC_APB1ENR_USART3EN;		Error = Rcc_Ok;  break;
			case Rcc_I2c1: Rcc_MemoryBase->APB1ENR &= ~RCC_APB1ENR_I2C1EN;		Error = Rcc_Ok;  break;
			case Rcc_I2c2: Rcc_MemoryBase->APB1ENR &= ~RCC_APB1ENR_I2C2EN;		Error = Rcc_Ok;  break;
			case Rcc_Usb: Rcc_MemoryBase->APB1ENR &= ~RCC_APB1ENR_USBEN;		Error = Rcc_Ok;  break;
			case Rcc_Can: Rcc_MemoryBase->APB1ENR &= ~RCC_APB1ENR_CAN1EN;		Error = Rcc_Ok;  break;
			case Rcc_Bkp: Rcc_MemoryBase->APB1ENR &= ~RCC_APB1ENR_BKPEN;		Error = Rcc_Ok;  break;
			case Rcc_Pwr: Rcc_MemoryBase->APB1ENR &= ~RCC_APB1ENR_PWREN;		Error = Rcc_Ok;  break;
			
			default: Error = Rcc_WrongPeripheral;				break;
		}
	}
	else
		Error = Rcc_WrongBus;
	
	
	return Error;
}
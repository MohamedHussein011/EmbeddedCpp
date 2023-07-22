/***************************************************************************************/
/*************             Author: Mohamed Hussein              ************************/
/*************             Layer: MCAL                          ************************/
/*************             Peripheral: RCC                      ************************/
/*************             Version: V1.0 - 19/07/2023           ************************/
/*************             MC: STM32F103C8T6 | ARM Cortex M3    ************************/
/***************************************************************************************/

#ifndef RCC_H
#define RCC_H

#include "stm32f10x.h"

//Note: this driver for STM32F103C8T6

enum Rcc_BusName_t
{
	Rcc_Ahb,
	Rcc_Apb2,
	Rcc_Apb1
};

enum Rcc_PeripheralName_t
{
	//AHB Peripherals
	Rcc_Dma1,
	Rcc_Dma2,
	Rcc_Sram,
	Rcc_Flitf=4,
	Rcc_Crc=6,
	Rcc_Fsmc=8,
	Rcc_Sdio=10,
	
	//APB2 Peripherals
	Rcc_Afio=0,
	Rcc_Gpioa=2,
	Rcc_Gpiob,
	Rcc_Gpioc,
	Rcc_Gpiod,
	Rcc_Gpioe,
	Rcc_Gpiof,
	Rcc_Gpiog,
	Rcc_Adc1,
	Rcc_Adc2,
	Rcc_Tim1,
	Rcc_Spi1,
	Rcc_Tim8,
	Rcc_Usart1,
	Rcc_Adc3,
	Rcc_Tim9=19,
	Rcc_Tim10,
	Rcc_Tim11,
	
	//APB1 Peripherals
	Rcc_Tim2=0,
	Rcc_Tim3,
	Rcc_Tim4,
	Rcc_Tim5,
	Rcc_Tim6,
	Rcc_Tim7,
	Rcc_Tim12,
	Rcc_Tim13,
	Rcc_Tim14,
	Rcc_Wwd=11,
	Rcc_Spi2=14,
	Rcc_Spi3,
	Rcc_Usart2=17,
	Rcc_Usart3,
	Rcc_Usart4,
	Rcc_Usart5,
	Rcc_I2c1,
	Rcc_I2c2,
	Rcc_Usb,
	Rcc_Can=25,
	Rcc_Bkp=27,
	Rcc_Pwr,
	Rcc_Dac,
};

enum Rcc_ErrorType_t
{
	Rcc_Ok,
	Rcc_HsiNotReady,
	Rcc_WrongBus,
	Rcc_WrongPeripheral,
	Rcc_Default = 0xff
};


class Rcc
{
	private:
		
	public:
		Rcc ();		//constructor called when creating an object
		Rcc_ErrorType_t Rcc_EnablePeripheral (Rcc_BusName_t Bus, Rcc_PeripheralName_t Peripheral);
		Rcc_ErrorType_t Rcc_DisablePeripheral (Rcc_BusName_t Bus, Rcc_PeripheralName_t Peripheral);
	
};

#endif
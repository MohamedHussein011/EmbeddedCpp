/***************************************************************************************/
/*************             Author: Mohamed HusseIn              ************************/
/*************             Layer: MCAL                          ************************/
/*************             Peripheral: RCC                      ************************/
/*************             Version: V1.0 - 19/07/2023           ************************/
/*************             MC: STM32F103C8T6 | ARM Cortex M3    ************************/
/***************************************************************************************/

#ifndef RCC_CFG_H
#define RCC_CFG_H

/* Rcc Clock Type
   Options: 
		1: Rcc_Hsi
		2: Rcc_Hse_Crystal
		3: Rcc_Hse_RC
		4: Rcc_Pll
*/
#define Rcc_Clock_Type        Rcc_Hse_Crystal
 
/* Rcc Clock Security system Enable
   Options: 
		1: Rcc_Css_Enable
		2: Rcc_Css_Disable
*/
#define Rcc_Clock_Security        Rcc_Css_Disable

/* Rcc Ahb Clock Prescaler
   Options: 
		1: Rcc_Ahb_Not_Divided
		2: Rcc_Ahb_Div_By_2
		3: Rcc_Ahb_Div_By_4
		4: Rcc_Ahb_Div_By_8
		5: Rcc_Ahb_Div_By_16
		6: Rcc_Ahb_Div_By_64
		7: Rcc_Ahb_Div_By_128
		8: Rcc_Ahb_Div_By_256
		9: Rcc_Ahb_Div_By_512
*/
#define Rcc_Ahb_Prescaler        Rcc_Ahb_Not_Divided

/* Rcc Apb1 Clock Prescaler
   Options: 
		1: Rcc_Apb1_Not_Divided
		2: Rcc_Apb1_Div_By_2
		3: Rcc_Apb1_Div_By_4
		4: Rcc_Apb1_Div_By_8
		5: Rcc_Apb1_Div_By_16
*/
#define Rcc_Apb1_Prescaler        Rcc_Apb1_Not_Divided

/* Rcc Apb2 Clock Prescaler
   Options: 
		1: Rcc_Apb2_Not_Divided
		2: Rcc_Apb2_Div_By_2
		3: Rcc_Apb2_Div_By_4
		4: Rcc_Apb2_Div_By_8
		5: Rcc_Apb2_Div_By_16
*/
#define Rcc_Apb2_Prescaler        Rcc_Apb2_Not_Divided

/* Rcc Adc Clock Prescaler
   Options: 
		1: Rcc_Adc_Div_By_2
		2: Rcc_Adc_Div_By_4
		3: Rcc_Adc_Div_By_6
		4: Rcc_Adc_Div_By_8
*/
#define Rcc_Adc_Prescaler        Rcc_Adc_Div_By_6

/* Rcc Pll entry Clock source
   Options: 
		1: Rcc_Pll_In_Hsi_Div_By_2
		2: Rcc_Pll_In_Hse_Div_By_2
		3: Rcc_Pll_In_Hse
*/
/* Note: Select Value only if you have Pll as Input Clock source */
#if Rcc_Clock_Type == Rcc_Pll
#define Rcc_Pll_In_Clock       Rcc_Pll_In_Hse_Div_By_2
#endif

/* Rcc Pll Multiplication factor
   Options: 
		1:  Rcc_Pll_Mul_By_2
		2:  Rcc_Pll_Mul_By_3
		3:  Rcc_Pll_Mul_By_4
		4:  Rcc_Pll_Mul_By_5
		5:  Rcc_Pll_Mul_By_6
		6:  Rcc_Pll_Mul_By_7
		7:  Rcc_Pll_Mul_By_8
		8:  Rcc_Pll_Mul_By_9
		9:  Rcc_Pll_Mul_By_10
		10: Rcc_Pll_Mul_By_11
		11: Rcc_Pll_Mul_By_12
		12: Rcc_Pll_Mul_By_13
		13: Rcc_Pll_Mul_By_14
		14: Rcc_Pll_Mul_By_15
		15: Rcc_Pll_Mul_By_16
*/
/* Note: Select Value only if you have Pll as Input Clock source */
#if Rcc_Clock_Type == Rcc_Pll
#define Rcc_Pll_Mul_Val        Rcc_Pll_Mul_By_8
#endif


#endif
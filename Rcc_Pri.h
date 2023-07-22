/***************************************************************************************/
/*************             Author: Mohamed HusseIn              ************************/
/*************             Layer: MCAL                          ************************/
/*************             Peripheral: RCC                      ************************/
/*************             Version: V1.0 - 19/07/2023           ************************/
/*************             MC: STM32F103C8T6 | ARM Cortex M3    ************************/
/***************************************************************************************/

#ifndef RCC_PRI_H
#define RCC_PRI_H

/*Rcc clock type*/
#define Rcc_Hsi            0
#define Rcc_Hse_Crystal    1
#define Rcc_Hse_Rc         2
#define Rcc_Pll            3

/* Rcc clock security system enable*/
#define Rcc_Css_Enable        0
#define Rcc_Css_Disable       1

/* Rcc Ahb clock Prescaler*/
#define Rcc_Ahb_Prescaler_Mask       0xFFFFFF0F
#define Rcc_Ahb_Not_Divided          0b0000
#define Rcc_Ahb_Div_By_2             0b1000
#define Rcc_Ahb_Div_By_4             0b1001
#define Rcc_Ahb_Div_By_8             0b1010
#define Rcc_Ahb_Div_By_16            0b1011
#define Rcc_Ahb_Div_By_64            0b1100
#define Rcc_Ahb_Div_By_128           0b1101
#define Rcc_Ahb_Div_By_256           0b1110
#define Rcc_Ahb_Div_By_512           0b1111

/* Rcc Apb1 clock Prescaler*/
#define Rcc_Apb1_Prescaler_Mask       0xFFFFF8FF
#define Rcc_Apb1_Not_Divided          0b000
#define Rcc_Apb1_Div_By_2             0b100
#define Rcc_Apb1_Div_By_4             0b101
#define Rcc_Apb1_Div_By_8             0b110
#define Rcc_Apb1_Div_By_16            0b111

/* Rcc Apb2 clock Prescaler*/
#define Rcc_Apb2_Prescaler_Mask       0xFFFFC7FF
#define Rcc_Apb2_Not_Divided          0b000
#define Rcc_Apb2_Div_By_2             0b100
#define Rcc_Apb2_Div_By_4             0b101
#define Rcc_Apb2_Div_By_8             0b110
#define Rcc_Apb2_Div_By_16            0b111

/* Rcc Adc clock Prescaler*/
#define Rcc_Adc_Prescaler_Mask       0xFFFF3FFF
#define Rcc_Adc_Div_By_2             0b00
#define Rcc_Adc_Div_By_4             0b01
#define Rcc_Adc_Div_By_6             0b10
#define Rcc_Adc_Div_By_8             0b11

/* Rcc Pll entry clock source*/

#define Rcc_Pll_In_Hsi_Div_By_2             0
#define Rcc_Pll_In_Hse_Div_By_2             1
#define Rcc_Pll_In_Hse                      2

/* Rcc Pll Multiplication factor*/
#define Rcc_Pll_Mul_Mask               0xFFC3FFFF
#define Rcc_Pll_Mul_By_2               0b0000
#define Rcc_Pll_Mul_By_3               0b0001
#define Rcc_Pll_Mul_By_4               0b0010
#define Rcc_Pll_Mul_By_5               0b0011
#define Rcc_Pll_Mul_By_6               0b0100
#define Rcc_Pll_Mul_By_7               0b0101
#define Rcc_Pll_Mul_By_8               0b0110
#define Rcc_Pll_Mul_By_9               0b0111
#define Rcc_Pll_Mul_By_10              0b1000
#define Rcc_Pll_Mul_By_11              0b1001
#define Rcc_Pll_Mul_By_12              0b1010
#define Rcc_Pll_Mul_By_13              0b1011
#define Rcc_Pll_Mul_By_14              0b1100
#define Rcc_Pll_Mul_By_15              0b1101
#define Rcc_Pll_Mul_By_16              0b1110

#endif
#ifndef _MDRB_1923VK014_H
#define _MDRB_1923VK014_H

#ifdef USE_BOARD_VK014 

#include <MDR_CPU_ClockSelect.h>

//===================================    Частота тактирования    ========================================

#define MDRB_HAS_NO_LCD

#define MDRB_CLK_PLL_HSE_RES_MAX     MDR_CLK_PLL_HSE_RES_DEF(MDRB_PLL_8MHz_TO_40MHz, MDRB_CPU_FREQ_SUPP_40MHz)

//  Переопределение пинов для удобства поиска конфликтов

    //  Port_C
    #define PIN_PC0     MDR_Pin_0   //  LED1,
    #define PIN_PC1     MDR_Pin_1   //  LED2,
    #define PIN_PC2     MDR_Pin_2   //  LED3,
    #define PIN_PC3     MDR_Pin_3   //  LED4,
    #define PIN_PC4     MDR_Pin_4   //  LED5,
    #define PIN_PC5     MDR_Pin_5   //  LED6,
    #define PIN_PC6     MDR_Pin_6   //  LED7,
    #define PIN_PC7     MDR_Pin_7   //  LED8,

    //  Port_D
    #define PIN_PD3     MDR_Pin_3   //      SSP4_TX
    #define PIN_PD4     MDR_Pin_4   //      SSP4_CLK
    #define PIN_PD5     MDR_Pin_5   //      SSP4_FSS
    #define PIN_PD6     MDR_Pin_6   //      SSP4_RX
    #define PIN_PD7     MDR_Pin_7   //      SSP1_TX
    #define PIN_PD8     MDR_Pin_8   //      SSP1_CLK
    #define PIN_PD9     MDR_Pin_9   //      SSP1_FSS
    #define PIN_PD10    MDR_Pin_10  //      SSP1_RX
    #define PIN_PD11    MDR_Pin_11  //      SSP2_TX
    #define PIN_PD12    MDR_Pin_12  //      SSP2_CLK
    #define PIN_PD13    MDR_Pin_13  //      SSP2_FSS
    #define PIN_PD14    MDR_Pin_14  //      SSP2_RX

    //  Port_E
    #define PIN_PE15    MDR_Pin_15  //   UART1_TX
    #define PIN_PE16    MDR_Pin_16  //   UART1_RX
    #define PIN_PE17    MDR_Pin_17  //      
    #define PIN_PE18    MDR_Pin_18  //
    #define PIN_PE19    MDR_Pin_19  //  
    #define PIN_PE20    MDR_Pin_20  //  
    #define PIN_PE21    MDR_Pin_21  //
    #define PIN_PE22    MDR_Pin_22  //


//  ----------    LEDs Definition -------------
    #define MDRB_LED_1 	              PIN_PC0
    #define MDRB_LED_2 	              PIN_PC1
    #define MDRB_LED_3 	              PIN_PC2
    #define MDRB_LED_4 	              PIN_PC3
    #define MDRB_LED_5 	              PIN_PC4
    #define MDRB_LED_6 	              PIN_PC5
    #define MDRB_LED_7 	              PIN_PC6
    #define MDRB_LED_8 	              PIN_PC7

    #define MDRB_LED_GPIO             MDR_GPIO_C    
    #define MDRB_LED_PinAll          (MDRB_LED_1 | MDRB_LED_2 | MDRB_LED_3 | MDRB_LED_4 | MDRB_LED_5 | MDRB_LED_6 | MDRB_LED_7 | MDRB_LED_8)


    //  --------------  Buttons Definition  ------------
    //  NO BUTTONS AVAILABLE by DEFAULT!!!
    
//  ---------------  UART1 Pin Definition ----------------
    //  PORT_F: PF0, PF1 - Main
    #define MDRB_UART1_TX_PE15_Ind	    15
    #define MDRB_UART1_RX_PE16_Ind	    16

    #define MDRB_UART1_TX_PE15_Msk	    MDR_Pin_15
    #define MDRB_UART1_RX_PE16_Msk		  MDR_Pin_16

    #define MDRB_UART1_TX_PE15_Port	    MDR_GPIO_E
    #define MDRB_UART1_RX_PE16_Port		  MDR_GPIO_E
    
    #define MDRB_UART1_TX_PE15_Func	    MDR_PIN_FUNC_5
    #define MDRB_UART1_RX_PE16_Func	    MDR_PIN_FUNC_5    

//  ---------------  SPI1 Pin Definition ----------------
    #define MDRB_SPI1_FSS_PD9_Ind	       9
    #define MDRB_SPI1_CLK_PD8_Ind	       8
    #define MDRB_SPI1_RX_PD10_Ind 	     10
    #define MDRB_SPI1_TX_PD7_Ind		     7

    #define MDRB_SPI1_FSS_PD9_Msk	       PIN_PD9
    #define MDRB_SPI1_CLK_PD8_Msk		     PIN_PD8
    #define MDRB_SPI1_RX_PD10_Msk 		   PIN_PD10
    #define MDRB_SPI1_TX_PD7_Msk		     PIN_PD7

    #define MDRB_SPI1_FSS_PD9_Port	     MDR_GPIO_D
    #define MDRB_SPI1_CLK_PD8_Port		   MDR_GPIO_D
    #define MDRB_SPI1_RX_PD10_Port 		   MDR_GPIO_D
    #define MDRB_SPI1_TX_PD7_Port		     MDR_GPIO_D
    
    #define MDRB_SPI1_FSS_PD9_Func	     MDR_PIN_FUNC_6
    #define MDRB_SPI1_CLK_PD8_Func		   MDR_PIN_FUNC_6
    #define MDRB_SPI1_RX_PD10_Func 		   MDR_PIN_FUNC_6
    #define MDRB_SPI1_TX_PD7_Func		     MDR_PIN_FUNC_6

//  ---------------  SPI2 Pin Definition ----------------
    #define MDRB_SPI2_FSS_PD13_Ind	     13
    #define MDRB_SPI2_CLK_PD12_Ind	     12
    #define MDRB_SPI2_RX_PD14_Ind 	     14
    #define MDRB_SPI2_TX_PD11_Ind		     11

    #define MDRB_SPI2_FSS_PD13_Msk	     PIN_PD13
    #define MDRB_SPI2_CLK_PD12_Msk		   PIN_PD12
    #define MDRB_SPI2_RX_PD14_Msk 		   PIN_PD14
    #define MDRB_SPI2_TX_PD11_Msk		     PIN_PD11

    #define MDRB_SPI2_FSS_PD13_Port	     MDR_GPIO_D
    #define MDRB_SPI2_CLK_PD12_Port		   MDR_GPIO_D
    #define MDRB_SPI2_RX_PD14_Port 		   MDR_GPIO_D
    #define MDRB_SPI2_TX_PD11_Port		   MDR_GPIO_D
    
    #define MDRB_SPI2_FSS_PD13_Func	     MDR_PIN_FUNC_6
    #define MDRB_SPI2_CLK_PD12_Func		   MDR_PIN_FUNC_6
    #define MDRB_SPI2_RX_PD14_Func 		   MDR_PIN_FUNC_6
    #define MDRB_SPI2_TX_PD11_Func		   MDR_PIN_FUNC_6

//  ---------------  SPI4 Pin Definition ----------------
    #define MDRB_SPI4_FSS_PD5_Ind	       5
    #define MDRB_SPI4_CLK_PD4_Ind	       4
    #define MDRB_SPI4_RX_PD6_Ind 	       6
    #define MDRB_SPI4_TX_PD3_Ind		     3

    #define MDRB_SPI4_FSS_PD5_Msk	       PIN_PD5
    #define MDRB_SPI4_CLK_PD4_Msk		     PIN_PD4
    #define MDRB_SPI4_RX_PD6_Msk 		     PIN_PD6
    #define MDRB_SPI4_TX_PD3_Msk		     PIN_PD3

    #define MDRB_SPI4_FSS_PD5_Port	     MDR_GPIO_D
    #define MDRB_SPI4_CLK_PD4_Port		   MDR_GPIO_D
    #define MDRB_SPI4_RX_PD6_Port 		   MDR_GPIO_D
    #define MDRB_SPI4_TX_PD3_Port		     MDR_GPIO_D
    
    #define MDRB_SPI4_FSS_PD5_Func	     MDR_PIN_FUNC_6
    #define MDRB_SPI4_CLK_PD4_Func		   MDR_PIN_FUNC_6
    #define MDRB_SPI4_RX_PD6_Func 		   MDR_PIN_FUNC_6
    #define MDRB_SPI4_TX_PD3_Func		     MDR_PIN_FUNC_6

#else
   Please, select board in MDRB_BoardSelect.h!

#endif // USE_BOARD_VK014


#endif // _MDRB_1923VK014_H

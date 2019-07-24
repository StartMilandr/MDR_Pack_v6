#ifndef _MDRB_1923VK014_H
#define _MDRB_1923VK014_H

#ifdef USE_BOARD_VK014 

#include <MDR_CPU_ClockSelect.h>

//===================================    Частота тактирования    ========================================

#define MDRB_CLK_PLL_HSE_RES_MAX     MDR_CLK_PLL_HSE_RES_DEF(MDRB_PLL_8MHz_TO_40MHz, MDRB_CPU_FREQ_SUPP_40MHz);

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

    //  Port_E
    #define PIN_PE18     MDR_Pin_18   //
    #define PIN_PE19     MDR_Pin_19   //  
    #define PIN_PE20     MDR_Pin_20   //  
    #define PIN_PE21     MDR_Pin_21   //
    #define PIN_PE22     MDR_Pin_22   //


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



#else
   Please, select board in MDRB_BoardSelect.h!

#endif // USE_BOARD_VK014


#endif // _MDRB_1923VK014_H

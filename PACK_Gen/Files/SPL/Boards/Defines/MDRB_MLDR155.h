#ifndef _MDRB_ESILA_H
#define _MDRB_ESILA_H

#ifdef USE_BOARD_MLDR155 

//#include <MDR_CPU_ClockSelect.h>
    #define MDR_MLDR155_FPGA_CPU_HZ     50E+6
    #define MDR_RST_ASYNC_IN_FPGA       MDR_RST_ASYNC_IN_HSI

//  КНОПКА DOWN переключает сразу несколько бит в регистре - ломает подключенный PHY3!

    #define PIN_PC0     MDR_Pin_0    //  LED_1
    #define PIN_PC1     MDR_Pin_1    //  LED_2
    #define PIN_PC2     MDR_Pin_2    //  LED_3
    #define PIN_PC3     MDR_Pin_3    //  LED_4
    #define PIN_PC4     MDR_Pin_4    //  LED_5
    #define PIN_PC5     MDR_Pin_5    //  LED_6
    #define PIN_PC6     MDR_Pin_6    //  LED_7
    #define PIN_PC7     MDR_Pin_7    //  LED_8

    #define PIN_PC8     MDR_Pin_8    //  Left
    #define PIN_PC9     MDR_Pin_9    //  Select       
    #define PIN_PC10    MDR_Pin_10   //  Right
    #define PIN_PC11    MDR_Pin_11   //  Down
    #define PIN_PC12    MDR_Pin_12   //  UP


////  ----------    LEDs Definition -------------
    #define MDRB_LED_1 	              PIN_PC0
    #define MDRB_LED_2 	              PIN_PC1
    #define MDRB_LED_3 	              PIN_PC2
    #define MDRB_LED_4 	              PIN_PC3
    #define MDRB_LED_5 	              PIN_PC4
    #define MDRB_LED_6 	              PIN_PC5
    #define MDRB_LED_7 	              PIN_PC6
    #define MDRB_LED_8 	              PIN_PC7

    #define MDRB_LED_GPIO             MDR_GPIO_C    
    #define MDRB_LED_PinAll          (MDRB_LED_1 | MDRB_LED_2 | MDRB_LED_3 | MDRB_LED_4 | \
                                      MDRB_LED_5 | MDRB_LED_6 | MDRB_LED_7 | MDRB_LED_8  )


//  --------------  Buttons Definition  ------------
    #define MDRB_BTN_PORT_KEY1        MDR_GPIO_C
    #define MDRB_BTN_PIN_KEY1         PIN_PC8  // Up
	
    #define MDRB_BTN_PORT_KEY2        MDR_GPIO_C
    #define MDRB_BTN_PIN_KEY2         PIN_PC9  // Right
	
    #define MDRB_BTN_PORT_KEY3        MDR_GPIO_C
    #define MDRB_BTN_PIN_KEY3         PIN_PC10  // Down
    
    #define MDRB_BTN_PORT_KEY4        MDR_GPIO_C
    #define MDRB_BTN_PIN_KEY4         PIN_PC11  // Left
    
    #define MDRB_BTN_PORT_KEY5        MDR_GPIO_C
    #define MDRB_BTN_PIN_KEY5         PIN_PC12  // Select
    	
    // for Initialization
    #define MDRB_BTN_GPIO             MDR_GPIO_C
    #define MDRB_BTN_PinSel           (MDRB_BTN_PIN_KEY1 | MDRB_BTN_PIN_KEY2 | MDRB_BTN_PIN_KEY3 | MDRB_BTN_PIN_KEY4 | MDRB_BTN_PIN_KEY5)
    
    // Active buttons Level
    //#define MDRB_BTNs_PUSH_TO_GND



//  ---------------  UART1 Pin Definition ----------------
    //  PORT_F: PF0, PF1 - Main
    #define MDRB_UART1_TX_PB1_Ind	      1
    #define MDRB_UART1_RX_PB0_Ind	      0

    #define MDRB_UART1_TX_PB1_Msk	      MDR_Pin_1
    #define MDRB_UART1_RX_PB0_Msk		    MDR_Pin_0

    #define MDRB_UART1_TX_PB1_Port	    MDR_GPIO_B
    #define MDRB_UART1_RX_PB0_Port		  MDR_GPIO_B
    
    #define MDRB_UART1_TX_PB1_Func	    MDR_PIN_FUNC_5
    #define MDRB_UART1_RX_PB0_Func	    MDR_PIN_FUNC_5 




#else
   Please, select board in MDRB_BoardSelect.h!

#endif // USE_BOARD_ESila


#endif // _MDRB_ESILA_H

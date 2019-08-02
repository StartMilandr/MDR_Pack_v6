#ifndef _MDRB_ESILA_H
#define _MDRB_ESILA_H

#ifdef USE_BOARD_ESila 

#include <MDR_CPU_ClockSelect.h>

//===================================    Частота тактирования    ========================================

#define MDRB_CLK_PLL_HSE_RES_MAX     MDR_CLK_PLL_HSE_RES_DEF(MDRB_PLL_8MHz_TO_120MHz, MDRB_CPU_FREQ_SUPP_120MHz);


//  Переопределение пинов для удобства поиска конфликтов
    //  Port_A    
    #define PIN_PA16     MDR_Pin_16  //          LCD_A0
    #define PIN_PA22     MDR_Pin_22  //          LCD_E2    
    #define PIN_PA23     MDR_Pin_23  //          LCD_E1        

    //  Port_B
    #define PIN_PB0      MDR_Pin_0   //             UART1_RX
    #define PIN_PB1      MDR_Pin_1   //             UART1_TX
    
    #define PIN_PB10     MDR_Pin_10  //          LCD_RES
    #define PIN_PB14     MDR_Pin_14  //          LCD_RW
    #define PIN_PB19     MDR_Pin_19  //          LCD_??

    //  Port_C
    #define PIN_PC0      MDR_Pin_0   //          LCD_D0
    #define PIN_PC1      MDR_Pin_1   //          LCD_D1
    #define PIN_PC2      MDR_Pin_2   //          LCD_D2
    #define PIN_PC3      MDR_Pin_3   //          LCD_D3
    #define PIN_PC4      MDR_Pin_4   //          LCD_D4
    #define PIN_PC5      MDR_Pin_5   //          LCD_D5
    #define PIN_PC6      MDR_Pin_6   //          LCD_D6
    #define PIN_PC7      MDR_Pin_7   //          LCD_D7   
    
    #define PIN_PC16     MDR_Pin_16   //  LED_G, LCD_E
    #define PIN_PC17     MDR_Pin_17   //         
    #define PIN_PC18     MDR_Pin_18   //  LED_B,
    #define PIN_PC19     MDR_Pin_19   //  
    #define PIN_PC20     MDR_Pin_20   //  LED_R,
    #define PIN_PC21     MDR_Pin_21   //  
    #define PIN_PC22     MDR_Pin_22   //  
    #define PIN_PC23     MDR_Pin_23   //  
    #define PIN_PC24     MDR_Pin_24   //  
    #define PIN_PC25     MDR_Pin_25   //  
    #define PIN_PC26     MDR_Pin_26   //  
    #define PIN_PC27     MDR_Pin_27   //    KEY_Left
    #define PIN_PC28     MDR_Pin_28   //    KEY_Up,
    #define PIN_PC29     MDR_Pin_29   //    KET_Right
    #define PIN_PC30     MDR_Pin_30   //    KEY_Down
    #define PIN_PC31     MDR_Pin_31   //    KEY_Sel,


//  ----------    LEDs Definition -------------
    #define MDRB_LED_1 	              PIN_PC20
    #define MDRB_LED_2 	              PIN_PC18
    #define MDRB_LED_3 	              PIN_PC16

    #define MDRB_LED_GPIO             MDR_GPIO_C    
    #define MDRB_LED_PinAll          (MDRB_LED_1 | MDRB_LED_2 | MDRB_LED_3)


//  --------------  Buttons Definition  ------------
    #define MDRB_BTN_PORT_KEY1        MDR_GPIO_C
    #define MDRB_BTN_PIN_KEY1         PIN_PC28  // Up
	
    #define MDRB_BTN_PORT_KEY2        MDR_GPIO_C
    #define MDRB_BTN_PIN_KEY2         PIN_PC29  // Right
	
    #define MDRB_BTN_PORT_KEY3        MDR_GPIO_C
    #define MDRB_BTN_PIN_KEY3         PIN_PC30  // Down
    
    #define MDRB_BTN_PORT_KEY4        MDR_GPIO_C
    #define MDRB_BTN_PIN_KEY4         PIN_PC27  // Left
    
    #define MDRB_BTN_PORT_KEY5        MDR_GPIO_C
    #define MDRB_BTN_PIN_KEY5         PIN_PC31  // Select
    	
    // for Initialization
    #define MDRB_BTN_GPIO             MDR_GPIO_C
    #define MDRB_BTN_PinSel           (PIN_PC27 | PIN_PC28 | PIN_PC29 | PIN_PC30 | PIN_PC31)
    
    // Active buttons Level
    #define MDRB_BTNs_PUSH_TO_GND

//  ----------  LCD Definition (Conflict with LEDs) ----------
    // Initialization                   //  D0 .. D5
    #define MDRB_LCD_IN_PORT            MDR_GPIO_C
    #define MDRB_LCD_IN_PINS           (PIN_PC0 | PIN_PC1 | PIN_PC2 | PIN_PC3 | PIN_PC4 | PIN_PC5 | PIN_PC6 | PIN_PC7)
    
                                        // E1, E2, A0
    #define MDRB_LCD_OUT_PORT           MDR_GPIO_A
    #define MDRB_LCD_OUT_PINS          (PIN_PA23 | PIN_PA22 | PIN_PA16)
                                        // RES, RW
    #define MDRB_LCD_OUT_PORT_EX1       MDR_GPIO_B
    #define MDRB_LCD_OUT_PINS_EX1      (PIN_PB10 | PIN_PB14 | PIN_PB19)    
                                        // E
    #define MDRB_LCD_OUT_PORT_EX2       MDR_GPIO_C
    #define MDRB_LCD_OUT_PINS_EX2      (PIN_PC16)

    //  Control Pins
    #define MDRB_LCD_E1_PORT            MDR_GPIO_A
    #define MDRB_LCD_E1_PIN             PIN_PA23

    #define MDRB_LCD_E2_PORT            MDR_GPIO_A
    #define MDRB_LCD_E2_PIN             PIN_PA22

    #define MDRB_LCD_RES_PORT           MDR_GPIO_B
    #define MDRB_LCD_RES_PIN            PIN_PB10

    #define MDRB_LCD_RW_PORT            MDR_GPIO_B
    #define MDRB_LCD_RW_PIN             PIN_PB14

    #define MDRB_LCD_A0_PORT            MDR_GPIO_A
    #define MDRB_LCD_A0_PIN             PIN_PA16

    #define MDRB_LCD_E_PORT             MDR_GPIO_C
    #define MDRB_LCD_E_PIN              PIN_PC16

    #define MDRB_LCD_CONFLICT_PORT      MDR_GPIO_B
    #define MDRB_LCD_CONFLICT_PIN       PIN_PB19

    //  Bus Commands
    #define MDRB_LCD_BusSetOUT()        MDR_PORTC->OE_Set = 0x00FFUL
    
    #define MDRB_LCD_BusSetIN()         MDR_PORTC->OE_Clr = 0x00FFUL
                                
    #define MDRB_LCD_BusWrite(value)    MDR_PORTC->RXTX_Clr = 0xFFUL; \
                                        MDR_PORTC->RXTX_Set = (value & 0xFFUL)
                                        
    #define MDRB_LCD_BusRead()          (uint8_t)(MDR_PORTC->RXTX & 0xFFUL)
    

    #define MDRB_LCD_CONFLICT_LED


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

#ifndef _MDRB_1986VE91_H
#define _MDRB_1986VE91_H

#ifdef USE_MDR1986VE91

//===================================    Заметки по плате    ========================================
// -  Светодиоды подключены к порту D, который содержит пины Jtag_B. Необходимо выставлять USE_JTAG_B в MDR_Congif.h чтобы запись в порт D не портила связь по Jtag.


#include "MDRB_1986VE9x.h"

//  --------------  Buttons Definition  ------------
    #define MDRB_BTN_PORT_KEY1      MDR_GPIO_C
    #define MDRB_BTN_PIN_KEY1       MDR_Pin_11   //  Up

    #define MDRB_BTN_PORT_KEY2      MDR_GPIO_C
    #define MDRB_BTN_PIN_KEY2       MDR_Pin_14   //  Right

    #define MDRB_BTN_PORT_KEY3      MDR_GPIO_C
    #define MDRB_BTN_PIN_KEY3       MDR_Pin_12   //  Down
	
    #define MDRB_BTN_PORT_KEY4      MDR_GPIO_C
    #define MDRB_BTN_PIN_KEY4       MDR_Pin_13   //  Left

    #define MDRB_BTN_PORT_KEY5      MDR_GPIO_C
    #define MDRB_BTN_PIN_KEY5       MDR_Pin_10   //  Select
	
    // for Initialization
    #define MDRB_BTN_GPIO           MDR_GPIO_C
    #define MDRB_BTN_PinSel        (MDRB_BTN_PIN_KEY1 | MDRB_BTN_PIN_KEY2 | MDRB_BTN_PIN_KEY3 | MDRB_BTN_PIN_KEY4 | MDRB_BTN_PIN_KEY5)

    // Active buttons Level
    #define MDRB_BTNs_PUSH_TO_GND 

//  ----------    LEDs Definition -------------
    #define MDRB_LED_1 	           MDR_Pin_10   //  VD5
    #define MDRB_LED_2 	           MDR_Pin_11   //  VD6
    #define MDRB_LED_3 	           MDR_Pin_12   //  VD7
    #define MDRB_LED_4 	           MDR_Pin_13   //  VD8
    #define MDRB_LED_5 	           MDR_Pin_14   //  VD9

    #define MDRB_LED_GPIO          MDR_GPIO_D
    #define MDRB_LED_PinAll       (MDRB_LED_1 | MDRB_LED_2 | MDRB_LED_3 | MDRB_LED_4 | MDRB_LED_5)

//  ----------  LCD Definition ---------------
    #define MDRB_LCD_E1_PORT     MDR_PORTE
    #define MDRB_LCD_E1_PIN      PORT_Pin_4

    #define MDRB_LCD_E2_PORT     MDR_PORTE
    #define MDRB_LCD_E2_PIN      PORT_Pin_5

    #define MDRB_LCD_RES_PORT    MDR_PORTE
    #define MDRB_LCD_RES_PIN     PORT_Pin_10

    #define MDRB_LCD_RW_PORT     MDR_PORTC
    #define MDRB_LCD_RW_PIN      PORT_Pin_2

    #define MDRB_LCD_A0_PORT     MDR_PORTE
    #define MDRB_LCD_A0_PIN      PORT_Pin_11

    #define MDRB_LCD_E_PORT      MDR_PORTC
    #define MDRB_LCD_E_PIN       PORT_Pin_7

    // Initialization
    #define MDRB_LCD_CLOCK     (RST_CLK_PCLK_PORTA | RST_CLK_PCLK_PORTC | RST_CLK_PCLK_PORTE)

    #define MDRB_LCD_IN_PORT         MDR_PORTA
    #define MDRB_LCD_IN_PINS        (PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2 | PORT_Pin_3 | PORT_Pin_4 | PORT_Pin_5| PORT_Pin_6| PORT_Pin_7) 

    #define MDRB_LCD_OUT_PORT        MDR_PORTE
    #define MDRB_LCD_OUT_PINS       (PORT_Pin_4 | PORT_Pin_5 | PORT_Pin_10 | PORT_Pin_11) 

    #define MDRB_LCD_OUT_PORT_EX1    MDR_PORTC
    #define MDRB_LCD_OUT_PINS_EX1   (PORT_Pin_2 | PORT_Pin_7)
    
    //  Commands
    #define LCD_CODE_BUS_OUT        MDR_PORTA->OE |= 0x00FF;
    
    #define LCD_CODE_BUS_IN         MDR_PORTA->OE &= 0xFF00;
                                
    #define LCD_CODE_WRITE(value)   MDR_PORTA->RXTX &= 0xFF00;          \
                                    MDR_PORTA->RXTX |= (value & 0xFF);
                                    
    #define LCD_CODE_READ     (uint8_t)(MDR_PORTA->RXTX & 0xFF);

#else
   Please, select board in MDRB_BoardSelect.h!

#endif // USE_MDR1986VE91

#endif // _MDRB_1986VE91_H

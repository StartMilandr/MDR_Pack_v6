#ifndef _MDRB_1986VE91_H
#define _MDRB_1986VE91_H

#ifdef USE_MDR1986VE91

//===================================    Заметки по плате    ========================================
// -  Светодиоды подключены к порту D, который содержит пины Jtag_B. Необходимо выставлять USE_JTAG_B в MDR_Congif.h чтобы запись в порт D не портила связь по Jtag.

//  MDR_JTAG_A_PORT   MDR_PORTB [pin0..pin4]
//  MDR_JTAG_B_PORT   MDR_PORTD [pin0..pin4]

//  Переопределение пинов для удобства поиска конфликтов
    #define PIN_PA0       MDR_Pin_0   //          LCD_D0
    #define PIN_PA1       MDR_Pin_1   //          LCD_D1
    #define PIN_PA2       MDR_Pin_2   //          LCD_D2
    #define PIN_PA3       MDR_Pin_3   //          LCD_D3
    #define PIN_PA4       MDR_Pin_4   //          LCD_D4
    #define PIN_PA5       MDR_Pin_5   //          LCD_D5
    #define PIN_PA6       MDR_Pin_6   //          LCD_D6
    #define PIN_PA7       MDR_Pin_7   //          LCD_D7    

    #define PIN_PB0       MDR_Pin_0   //                    JTAG_A
    #define PIN_PB1       MDR_Pin_1   //                    JTAG_A
    #define PIN_PB2       MDR_Pin_2   //                    JTAG_A
    #define PIN_PB3       MDR_Pin_3   //                    JTAG_A
    #define PIN_PB4       MDR_Pin_4   //                    JTAG_A      

    #define PIN_PC2       MDR_Pin_2   //          LCD_RW
    #define PIN_PC7       MDR_Pin_7   //          LCD_E
    #define PIN_PC10      MDR_Pin_10  //  Select
    #define PIN_PC11      MDR_Pin_11  //  Up
    #define PIN_PC12      MDR_Pin_12  //  Down
    #define PIN_PC13      MDR_Pin_13  //  Left
    #define PIN_PC14      MDR_Pin_14  //  Right

    #define PIN_PD0       MDR_Pin_0   //                    JTAG_B
    #define PIN_PD1       MDR_Pin_1   //                    JTAG_B
    #define PIN_PD2       MDR_Pin_2   //                    JTAG_B
    #define PIN_PD3       MDR_Pin_3   //                    JTAG_B
    #define PIN_PD4       MDR_Pin_4   //                    JTAG_B
    #define PIN_PD10      MDR_Pin_10  //  LED_1
    #define PIN_PD11      MDR_Pin_11  //  LED_2
    #define PIN_PD12      MDR_Pin_12  //  LED_3
    #define PIN_PD13      MDR_Pin_13  //  LED_4
    #define PIN_PD14      MDR_Pin_14  //  LED_5

    #define PIN_PE4       MDR_Pin_4   //          LCD_E1
    #define PIN_PE5       MDR_Pin_5   //          LCD_E2
    #define PIN_PE10      MDR_Pin_10  //          LCD_RES
    #define PIN_PE11      MDR_Pin_11  //          LCD_A0


#include "MDRB_1986VE9x.h"

//  --------------  Buttons Definition  ------------
    #define MDRB_BTN_PORT_KEY1      MDR_GPIO_C
    #define MDRB_BTN_PIN_KEY1       PIN_PC11   //  Up

    #define MDRB_BTN_PORT_KEY2      MDR_GPIO_C
    #define MDRB_BTN_PIN_KEY2       PIN_PC14   //  Right

    #define MDRB_BTN_PORT_KEY3      MDR_GPIO_C
    #define MDRB_BTN_PIN_KEY3       PIN_PC12   //  Down
	
    #define MDRB_BTN_PORT_KEY4      MDR_GPIO_C
    #define MDRB_BTN_PIN_KEY4       PIN_PC13   //  Left

    #define MDRB_BTN_PORT_KEY5      MDR_GPIO_C
    #define MDRB_BTN_PIN_KEY5       PIN_PC10   //  Select

    #define MDRB_BTN_PORT_KEY_P1    MDR_GPIO_C
    #define MDRB_BTN_PIN_KEY_P1     (PIN_PC11 | PIN_PC14)   //  Up + Right

    // for Initialization
    #define MDRB_BTN_GPIO           MDR_GPIO_C
    #define MDRB_BTN_PinSel        (MDRB_BTN_PIN_KEY1 | MDRB_BTN_PIN_KEY2 | MDRB_BTN_PIN_KEY3 | MDRB_BTN_PIN_KEY4 | MDRB_BTN_PIN_KEY5)

    // Active buttons Level
    #define MDRB_BTNs_PUSH_TO_GND 

//  ----------    LEDs Definition -------------
    #define MDRB_LED_1 	           PIN_PD10   //  VD5
    #define MDRB_LED_2 	           PIN_PD11   //  VD6
    #define MDRB_LED_3 	           PIN_PD12   //  VD7
    #define MDRB_LED_4 	           PIN_PD13   //  VD8
    #define MDRB_LED_5 	           PIN_PD14   //  VD9

    #define MDRB_LED_GPIO          MDR_GPIO_D
    #define MDRB_LED_PinAll       (MDRB_LED_1 | MDRB_LED_2 | MDRB_LED_3 | MDRB_LED_4 | MDRB_LED_5)

//  ----------  LCD Definition ---------------
    // Initialization                 //  D0 .. D7
    #define MDRB_LCD_IN_PORT          MDR_GPIO_A
    #define MDRB_LCD_IN_PINS          (PIN_PA0 | PIN_PA1 | PIN_PA2 | PIN_PA3 | PIN_PA4 | PIN_PA5 | PIN_PA6 | PIN_PA7)
                                      // E1, E2, RES, A0
    #define MDRB_LCD_OUT_PORT         MDR_GPIO_E
    #define MDRB_LCD_OUT_PINS         (PIN_PE4 | PIN_PE5 | PIN_PE10 | PIN_PE11)
                                      // RW, E
    #define MDRB_LCD_OUT_PORT_EX1     MDR_GPIO_C
    #define MDRB_LCD_OUT_PINS_EX1     (PIN_PC2 | PIN_PC7)
    
    //  Control Pins
    #define MDRB_LCD_E1_PORT          MDR_GPIO_E
    #define MDRB_LCD_E1_PIN           PIN_PE4

    #define MDRB_LCD_E2_PORT          MDR_GPIO_E
    #define MDRB_LCD_E2_PIN           PIN_PE5

    #define MDRB_LCD_RES_PORT         MDR_GPIO_E
    #define MDRB_LCD_RES_PIN          PIN_PE10

    #define MDRB_LCD_RW_PORT          MDR_GPIO_C
    #define MDRB_LCD_RW_PIN           PIN_PC2

    #define MDRB_LCD_A0_PORT          MDR_GPIO_E
    #define MDRB_LCD_A0_PIN           PIN_PE11

    #define MDRB_LCD_E_PORT           MDR_GPIO_C
    #define MDRB_LCD_E_PIN            PIN_PC7
    
    //  Bus Commands
    #define MDRB_LCD_BusSetOUT()        MDR_PORTA->OE |= 0x00FF;
    
    #define MDRB_LCD_BusSetIN()         MDR_PORTA->OE &= 0xFF00;
                                
    #define MDRB_LCD_BusWrite(value)    MDR_PORTA->RXTX &= 0xFF00;          \
                                        MDR_PORTA->RXTX |= (value & 0xFF);
                                    
    #define MDRB_LCD_BusRead()          (uint8_t)(MDR_PORTA->RXTX & 0xFF);

#else
   Please, select board in MDRB_BoardSelect.h!

#endif // USE_MDR1986VE91

#endif // _MDRB_1986VE91_H

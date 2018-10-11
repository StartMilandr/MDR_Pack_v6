#ifndef _MDRB_1986VE92_H
#define _MDRB_1986VE92_H


#ifdef USE_MDR1986VE92

//===================================    Заметки по плате    ========================================
//  MDR_JTAG_A_PORT   MDR_PORTB [pin0..pin4]
//  MDR_JTAG_B_PORT   MDR_PORTD [pin0..pin4]

//  Переопределение пинов для удобства поиска конфликтов
    #define PIN_PA0     MDR_Pin_0   //          LCD_D0
    #define PIN_PA1     MDR_Pin_1   //          LCD_D1
    #define PIN_PA2     MDR_Pin_2   //          LCD_D2
    #define PIN_PA3     MDR_Pin_3   //          LCD_D3
    #define PIN_PA4     MDR_Pin_4   //          LCD_D4
    #define PIN_PA5     MDR_Pin_5   //          LCD_D5

    #define PIN_PB0     MDR_Pin_0   //                    JTAG_A
    #define PIN_PB1     MDR_Pin_1   //                    JTAG_A
    #define PIN_PB2     MDR_Pin_2   //                    JTAG_A
    #define PIN_PB3     MDR_Pin_3   //                    JTAG_A
    #define PIN_PB4     MDR_Pin_4   //                    JTAG_A    
    #define PIN_PB5     MDR_Pin_5   //  UP
    #define PIN_PB6     MDR_Pin_6   //  Right
    #define PIN_PB7     MDR_Pin_7   //          LCD_E1
    #define PIN_PB8     MDR_Pin_8   //          LCD_E2
    #define PIN_PB9     MDR_Pin_9   //          LCD_RES
    #define PIN_PB10    MDR_Pin_10  //          LCD_RW

    #define PIN_PC0     MDR_Pin_0   //  LED_1   LCD_A0
    #define PIN_PC1     MDR_Pin_1   //  LED_2   LCD_E
    #define PIN_PC2     MDR_Pin_2   //  Select

    #define PIN_PD0     MDR_Pin_0   //                    JTAG_B
    #define PIN_PD1     MDR_Pin_1   //                    JTAG_B
    #define PIN_PD2     MDR_Pin_2   //                    JTAG_B
    #define PIN_PD3     MDR_Pin_3   //          LCD_E     JTAG_B
    #define PIN_PD4     MDR_Pin_4   //                    JTAG_B
    
    #define PIN_PE1     MDR_Pin_1   //  Down
    #define PIN_PE3     MDR_Pin_3   //  Left

    #define PIN_PF2     MDR_Pin_2   //          LCD_D6
    #define PIN_PF3     MDR_Pin_3   //          LCD_D7



#include "MDRB_1986VE9x.h"

//  --------------  Buttons Definition  ------------
    #define MDRB_BTN_PORT_KEY1          MDR_GPIO_B
    #define MDRB_BTN_PIN_KEY1           PIN_PB5   // Up
	
    #define MDRB_BTN_PORT_KEY2          MDR_GPIO_B
    #define MDRB_BTN_PIN_KEY2           PIN_PB6   // Right
	
    #define MDRB_BTN_PORT_KEY3          MDR_GPIO_E
    #define MDRB_BTN_PIN_KEY3           PIN_PE1   // Down
	
    #define MDRB_BTN_PORT_KEY4          MDR_GPIO_E
    #define MDRB_BTN_PIN_KEY4           PIN_PE3   // Left

    #define MDRB_BTN_PORT_KEY5          MDR_GPIO_C
    #define MDRB_BTN_PIN_KEY5           PIN_PC2   // Select

    #define MDRB_BTN_PORT_KEY_P1        MDR_GPIO_B
    #define MDRB_BTN_PIN_KEY_P1        (PIN_PB5 | PIN_PB6)   //  Up + Right

    // for Initialization
    #define MDRB_BTN_GPIO               MDR_GPIO_C
    #define MDRB_BTN_PinSel             PIN_PC2

    #define MDRB_BTN_GPIO_Ex1           MDR_GPIO_B
    #define MDRB_BTN_PinSel_Ex1        (PIN_PB5 | PIN_PB6)

    #define MDRB_BTN_GPIO_Ex2           MDR_GPIO_E
    #define MDRB_BTN_PinSel_Ex2        (PIN_PE1 | PIN_PE3)
    
    // Active buttons Level
    #define MDRB_BTNs_PUSH_TO_GND     

//  ----------    LEDs Definition -------------
    #define MDRB_LED_1 	                PIN_PC0
    #define MDRB_LED_2 	                PIN_PC1

    #define MDRB_LED_GPIO               MDR_GPIO_C    
    #define MDRB_LED_PinAll            (PIN_PC0 | PIN_PC1)

//  ----------  LCD Definition (Conflict with LEDs) ----------
    // Initialization                   //  D0 .. D5
    #define MDRB_LCD_IN_PORT            MDR_GPIO_A
    #define MDRB_LCD_IN_PINS           (PIN_PA0 | PIN_PA1 | PIN_PA2 | PIN_PA3 | PIN_PA4 | PIN_PA5)
                                        //  D6, D7
    #define MDRB_LCD_IN_PORT_EX1        MDR_GPIO_F
    #define MDRB_LCD_IN_PINS_EX1       (PIN_PF2 | PIN_PF3)
                                        // E1, E2, RES, RW
    #define MDRB_LCD_OUT_PORT           MDR_GPIO_B
    #define MDRB_LCD_OUT_PINS          (PIN_PB7 | PIN_PB8 | PIN_PB9 | PIN_PB10)
                                        // A0, E
    #define MDRB_LCD_OUT_PORT_EX1       MDR_GPIO_C
    #define MDRB_LCD_OUT_PINS_EX1      (PIN_PC0 | PIN_PC1)

    //  Control Pins
    #define MDRB_LCD_E1_PORT            MDR_GPIO_B
    #define MDRB_LCD_E1_PIN             PIN_PB7

    #define MDRB_LCD_E2_PORT            MDR_GPIO_B
    #define MDRB_LCD_E2_PIN             PIN_PB8

    #define MDRB_LCD_RES_PORT           MDR_GPIO_B
    #define MDRB_LCD_RES_PIN            PIN_PB9

    #define MDRB_LCD_RW_PORT            MDR_GPIO_B
    #define MDRB_LCD_RW_PIN             PIN_PB10

    #define MDRB_LCD_A0_PORT            MDR_GPIO_C
    #define MDRB_LCD_A0_PIN             PIN_PC0       //  conflicts with LEDs!

    #define MDRB_LCD_E_PORT             MDR_GPIO_C
    #define MDRB_LCD_E_PIN              PIN_PC1       //  conflicts with LEDs!
    
    //  Bus Commands
    #define MDRB_LCD_BusSetOUT()        MDR_PORTA->OE |= 0x003F; \
                                        MDR_PORTF->OE |= 0x000C;
    
    #define MDRB_LCD_BusSetIN()         MDR_PORTA->OE &= 0xFFC0;  \
                                        MDR_PORTF->OE &= 0xFFF3;
                                
    #define MDRB_LCD_BusWrite(value)    MDR_PORTA->RXTX &= 0xFFC0;          \
                                        MDR_PORTA->RXTX |= (value & 0x3F);  \
                                        MDR_PORTF->RXTX &= 0xFFF3;          \
                                        MDR_PORTF->RXTX |= ((value >> 4) & 0x0C);
                                    
    #define MDRB_LCD_BusRead()   (uint8_t)(MDR_PORTA->RXTX & 0x3F) | (uint8_t)((MDR_PORTF->RXTX << 4) & 0xC0)


    #define MDRB_LCD_CONFLICT_LED

#else
   Please, select board in MDRB_BoardSelect.h!

#endif // USE_MDR1986VE92


#endif // _MDRB_1986VE92_H

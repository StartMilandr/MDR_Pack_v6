#ifndef _MDRB_1986VE92_H
#define _MDRB_1986VE92_H


#ifdef USE_MDR1986VE92

#include "MDRB_1986VE9x.h"

//  --------------  Buttons Definition  ------------
    #define MDRB_BTN_PORT_KEY1          MDR_GPIO_B
    #define MDRB_BTN_PIN_KEY1           MDR_Pin_5   // Up
	
    #define MDRB_BTN_PORT_KEY2          MDR_GPIO_B
    #define MDRB_BTN_PIN_KEY2           MDR_Pin_6   // Right
	
    #define MDRB_BTN_PORT_KEY3          MDR_GPIO_E
    #define MDRB_BTN_PIN_KEY3           MDR_Pin_1   // Down
	
    #define MDRB_BTN_PORT_KEY4          MDR_GPIO_E
    #define MDRB_BTN_PIN_KEY4           MDR_Pin_3   // Left

    #define MDRB_BTN_PORT_KEY5          MDR_GPIO_C
    #define MDRB_BTN_PIN_KEY5           MDR_Pin_2   // Select

    // for Initialization
    #define MDRB_BTN_GPIO               MDR_GPIO_C
    #define MDRB_BTN_PinSel             MDR_Pin_2

    #define MDRB_BTN_GPIO_Ex1           MDR_GPIO_B
    #define MDRB_BTN_PinSel_Ex1        (MDR_Pin_5 | MDR_Pin_6)

    #define MDRB_BTN_GPIO_Ex2           MDR_GPIO_E
    #define MDRB_BTN_PinSel_Ex2        (MDR_Pin_1 | MDR_Pin_3)
    
    // Active buttons Level
    #define MDRB_BTNs_PUSH_TO_GND     

//  ----------    LEDs Definition -------------
    #define MDRB_LED_1 	                MDR_Pin_0
    #define MDRB_LED_2 	                MDR_Pin_1

    #define MDRB_LED_GPIO               MDR_GPIO_C    
    #define MDRB_LED_PinAll            (MDRB_LED_1 | MDRB_LED_2)

//  ----------  LCD Definition ---------------
//  conflicts with LEDs!
    #define MDRB_LCD_E1_PORT     MDR_PORTB
    #define MDRB_LCD_E1_PIN      PORT_Pin_7

    #define MDRB_LCD_E2_PORT     MDR_PORTB
    #define MDRB_LCD_E2_PIN      PORT_Pin_8

    #define MDRB_LCD_RES_PORT    MDR_PORTB
    #define MDRB_LCD_RES_PIN     PORT_Pin_9

    #define MDRB_LCD_RW_PORT     MDR_PORTB
    #define MDRB_LCD_RW_PIN      PORT_Pin_10

    #define MDRB_LCD_A0_PORT     MDR_PORTC
    #define MDRB_LCD_A0_PIN      PORT_Pin_0

    #define MDRB_LCD_E_PORT      MDR_PORTC
    #define MDRB_LCD_E_PIN       PORT_Pin_1

    // Initialization
    #define MDRB_LCD_CLOCK     (RST_CLK_PCLK_PORTA | RST_CLK_PCLK_PORTB | RST_CLK_PCLK_PORTC | RST_CLK_PCLK_PORTF)

    #define MDRB_LCD_IN_PORT         MDR_PORTA
    #define MDRB_LCD_IN_PINS        (PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2 | PORT_Pin_3 | PORT_Pin_4 | PORT_Pin_5) 

    #define MDRB_LCD_IN_PORT_EX1     MDR_PORTF
    #define MDRB_LCD_IN_PINS_EX1    (PORT_Pin_2 | PORT_Pin_3)

    #define MDRB_LCD_OUT_PORT        MDR_PORTB
    #define MDRB_LCD_OUT_PINS       (PORT_Pin_7 | PORT_Pin_8 | PORT_Pin_9 | PORT_Pin_10) 

    #define MDRB_LCD_OUT_PORT_EX1    MDR_PORTC
    #define MDRB_LCD_OUT_PINS_EX1   (PORT_Pin_0 | PORT_Pin_1)
    
    //  Commands
    #define MDRB_LCD_CODE_BUS_OUT        MDR_PORTA->OE |= 0x003F; \
                                    MDR_PORTF->OE |= 0x000C;
    
    #define MDRB_LCD_CODE_BUS_IN         MDR_PORTA->OE &= 0xFFC0;  \
                                    MDR_PORTF->OE &= 0xFFF3;
                                
    #define MDRB_LCD_CODE_WRITE(value)   MDR_PORTA->RXTX &= 0xFFC0;          \
                                    MDR_PORTA->RXTX |= (value & 0x3F);  \
                                    MDR_PORTF->RXTX &= 0xFFF3;          \
                                    MDR_PORTF->RXTX |= ((value >> 4) & 0x0C);
                                    
    #define MDRB_LCD_CODE_READ     (uint8_t)(MDR_PORTA->RXTX & 0x3F) | (uint8_t)((MDR_PORTF->RXTX << 4) & 0xC0);


#else
   Please, select board in MDRB_BoardSelect.h!

#endif // USE_MDR1986VE92


#endif // _MDRB_1986VE92_H

#ifndef _MDRB_1986VK234_H
#define _MDRB_1986VK234_H

#ifdef USE_MDR1986VK234

//  Временно из ВЕ4 для проверки компиляции.

#define TEST_COMPILE_VE4  1

#if TEST_COMPILE_VE4
//  --------------  Buttons Definition  ------------
    #define MDRB_BTN_PORT_KEY1      MDR_GPIO_B
    #define MDRB_BTN_PIN_KEY1       MDR_Pin_11   // Up

    #define MDRB_BTN_PORT_KEY2      MDR_GPIO_B
    #define MDRB_BTN_PIN_KEY2       MDR_Pin_10   // Right

    #define MDRB_BTN_PORT_KEY3      MDR_GPIO_B
    #define MDRB_BTN_PIN_KEY3       MDR_Pin_9    // Down
	
    #define MDRB_BTN_PORT_KEY4      MDR_GPIO_B
    #define MDRB_BTN_PIN_KEY4       MDR_Pin_12   // Left

    #define MDRB_BTN_PORT_KEY_P1    MDR_GPIO_B
    #define MDRB_BTN_PIN_KEY_P1     (MDR_Pin_11 | MDR_Pin_10)   //  Up + Right

    #define MDRB_BTN_PORT_KEY_P2    MDR_GPIO_B
    #define MDRB_BTN_PIN_KEY_P2     (MDR_Pin_11 | MDR_Pin_12)    //  Up + Left 	
  
    // for Initialization
    #define MDRB_BTN_GPIO           MDR_GPIO_B
    #define MDRB_BTN_PinSel         (MDRB_BTN_PIN_KEY1 | MDRB_BTN_PIN_KEY2 | MDRB_BTN_PIN_KEY3 | MDRB_BTN_PIN_KEY4)

    // Active buttons Level
    #define MDRB_BTNs_PUSH_TO_GND 

//  ----------    LEDs Definition -------------
    #define MDRB_LED_1 	           MDR_Pin_11    // VD3

    #define MDRB_LED_GPIO          MDR_GPIO_A
    #define MDRB_LED_PinAll        MDRB_LED_1
    
//  ----------  LCD Definition ---------------
    // Initialization                 //  D0 .. D3, A0, WR1, WR2
    #define MDRB_LCD_PORT             MDR_GPIO_A
    #define MDRB_LCD_PINS            (MDR_Pin_0 | MDR_Pin_1 | MDR_Pin_2 | MDR_Pin_3 | MDR_Pin_4 | MDR_Pin_14 | MDR_Pin_15)
    
    //  Control Pins
    #define MDRB_LCD_WR1_PORT         MDR_GPIO_A
    #define MDRB_LCD_WR1_PIN          MDR_Pin_14

    #define MDRB_LCD_WR2_PORT         MDR_GPIO_A
    #define MDRB_LCD_WR2_PIN          MDR_Pin_15

    #define MDRB_LCD_A0_PORT          MDR_GPIO_A
    #define MDRB_LCD_A0_PIN           MDR_Pin_4

    
    //  Bus Commands                              
    #define MDRB_LCD_BusWrite(value)    MDR_PORTA->RXTX &= 0xFFF0;          \
                                        MDR_PORTA->RXTX |= ((value) & 0x0FUL);
    
    #define LCD_IS_7SEG_DISPLAY    
    
#endif

#else
   Please, select board in MDRB_BoardSelect.h!

#endif // USE_MDR1986VK234

#endif // _MDRB_1986VK234_H


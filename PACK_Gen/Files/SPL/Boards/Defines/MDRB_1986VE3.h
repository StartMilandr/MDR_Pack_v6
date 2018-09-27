#ifndef _MDRB_1986VE3_H
#define _MDRB_1986VE3_H

#ifdef USE_MDR1986VE3

//  --------------  Buttons Definition  ------------
    #define MDRB_BTN_PORT_KEY1      MDR_GPIO_G
    #define MDRB_BTN_PIN_KEY1       MDR_Pin_12   // Up
	
    #define MDRB_BTN_PORT_KEY2      MDR_GPIO_G    
    #define MDRB_BTN_PIN_KEY2       MDR_Pin_11   // Right
	
    #define MDRB_BTN_PORT_KEY3      MDR_GPIO_G   
    #define MDRB_BTN_PIN_KEY3       MDR_Pin_15	 // Down
	
    #define MDRB_BTN_PORT_KEY4      MDR_GPIO_G  
    #define MDRB_BTN_PIN_KEY4       MDR_Pin_7    // Left

    #define MDRB_BTN_PORT_KEY5      MDR_GPIO_G 
    #define MDRB_BTN_PIN_KEY5       MDR_Pin_14   // Select 

    #define MDRB_BTN_PORT_KEY6      MDR_GPIO_G  
    #define MDRB_BTN_PIN_KEY6       MDR_Pin_13   // Back

    // for Initialization
    #define MDRB_BTN_GPIO           MDR_GPIO_G
    #define MDRB_BTN_PinSel        (MDRB_BTN_PIN_KEY1 | MDRB_BTN_PIN_KEY2 | MDRB_BTN_PIN_KEY3 | MDRB_BTN_PIN_KEY4 | MDRB_BTN_PIN_KEY5 | MDRB_BTN_PIN_KEY6)
    
    // Active buttons Level
    #define MDRB_BTNs_PUSH_TO_GND 

//  ----------    LEDs Definition -------------
    #define MDRB_LED_1              MDR_Pin_0   //  VD5
    #define MDRB_LED_2              MDR_Pin_1   //  VD6
    #define MDRB_LED_3              MDR_Pin_2   //  VD7
    #define MDRB_LED_4              MDR_Pin_3   //  VD8
    #define MDRB_LED_5              MDR_Pin_4   //  VD9
    #define MDRB_LED_6              MDR_Pin_5   //  VD10
    #define MDRB_LED_7              MDR_Pin_6   //  VD11
    #define MDRB_LED_8              MDR_Pin_7   //  VD12

    #define MDRB_LED_GPIO           MDR_GPIO_B
    #define MDRB_LED_PinAll        (MDRB_LED_1 | MDRB_LED_2 | MDRB_LED_3 | MDRB_LED_4  \
                                  | MDRB_LED_5 | MDRB_LED_6 | MDRB_LED_7 | MDRB_LED_8)

#else
   Please, select board in MDRB_BoardSelect.h!

#endif // USE_MDR1986VE3

#endif // _MDRB_1986VE3_H

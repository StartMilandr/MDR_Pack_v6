#ifndef _MDRB_1986VE4_H
#define _MDRB_1986VE4_H

#ifdef USE_MDR1986VE4

//  --------------  Buttons Definition  ------------
    #define MDRB_BTN_PORT_KEY1      MDR_GPIO_B
    #define MDRB_BTN_PIN_KEY1       MDR_Pin_11   //  Up

    #define MDRB_BTN_PORT_KEY2      MDR_GPIO_B
    #define MDRB_BTN_PIN_KEY2       MDR_Pin_10   //  Right

    #define MDRB_BTN_PORT_KEY3      MDR_GPIO_B
    #define MDRB_BTN_PIN_KEY3       MDR_Pin_9    //  Down
	
    #define MDRB_BTN_PORT_KEY4      MDR_GPIO_B
    #define MDRB_BTN_PIN_KEY4       MDR_Pin_12   //  Left

	
    // for Initialization
    #define MDRB_BTN_GPIO           MDR_GPIO_B
    #define MDRB_BTN_PinSel         (MDRB_BTN_PIN_KEY1 | MDRB_BTN_PIN_KEY2 | MDRB_BTN_PIN_KEY3 | MDRB_BTN_PIN_KEY4)

    // Active buttons Level
    #define MDRB_BTNs_PUSH_TO_GND 

//  ----------    LEDs Definition -------------
    #define MDRB_LED_1 	           MDR_Pin_11    // VD3

    #define MDRB_LED_GPIO          MDR_GPIO_A
    #define MDRB_LED_PinAll        MDRB_LED_1

#else
   Please, select board in MDRB_BoardSelect.h!

#endif // USE_MDR1986VE4 

#endif // _MDRB_1986VE4_H


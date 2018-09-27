#ifndef _MDRB_1986VE93_H
#define _MDRB_1986VE93_H


#ifdef USE_MDR1986VE93

//===================================    Заметки по плате    ========================================
// -  Кнопки Up и Down совпадают в выводами JTAG. Поэтому, при работе с кнопками необходимо подключаться по Jtag_А. В файле MDR_Congif.h выбрать USE_JTAG_А.
//    Для работы кнопок Up и Down необходимо установить перемычки X33, X34. При этом Jtag_В становится недоступен.


#include "MDRB_1986VE9x.h"

//  --------------  Buttons Definition  ------------
    #define MDRB_BTN_PORT_KEY1        MDR_GPIO_D
    #define MDRB_BTN_PIN_KEY1         MDR_Pin_0  // Up
	
    #define MDRB_BTN_PORT_KEY2        MDR_GPIO_E
    #define MDRB_BTN_PIN_KEY2         MDR_Pin_6  // Right
	
    #define MDRB_BTN_PORT_KEY3        MDR_GPIO_D
    #define MDRB_BTN_PIN_KEY3         MDR_Pin_1  // Down
	
    #define MDRB_BTN_PORT_KEY4        MDR_GPIO_E
    #define MDRB_BTN_PIN_KEY4         MDR_Pin_3  // Left

    #define MDRB_BTN_PORT_KEY5        MDR_GPIO_C
    #define MDRB_BTN_PIN_KEY5         MDR_Pin_0  // Select


    // for Initialization
    #define MDRB_BTN_GPIO             MDR_GPIO_C
    #define MDRB_BTN_PinSel           MDR_Pin_0

    #define MDRB_BTN_GPIO_Ex1         MDR_GPIO_D
    #define MDRB_BTN_PinSel_Ex1      (MDR_Pin_0 | MDR_Pin_1)

    #define MDRB_BTN_GPIO_Ex2         MDR_GPIO_E
    #define MDRB_BTN_PinSel_Ex2      (MDR_Pin_3 | MDR_Pin_6)
    
    // Active buttons Level
    #define MDRB_BTNs_PUSH_TO_GND    

//  ----------    LEDs Definition -------------
    #define MDRB_LED_1 	              MDR_Pin_0
    #define MDRB_LED_2 	              MDR_Pin_1

    #define MDRB_LED_GPIO             MDR_GPIO_F    
    #define MDRB_LED_PinAll          (MDRB_LED_1 | MDRB_LED_2)


#else
   Please, select board in MDRB_BoardSelect.h!

#endif // USE_MDR1986VE93

#endif // _MDRB_1986VE93_H

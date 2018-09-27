#ifndef _MDRB_1986VE8_H
#define _MDRB_1986VE8_H

#ifdef USE_BOARD_VE8 

//  UNLOCK KEY
    #define _KEY_ 				         0x8555AAA1

//  --------------  Buttons Definition  ------------
    #define MDRB_BTN_PORT_KEY1     PORTE
    #define MDRB_BTN_PIN_KEY1      PORT_Pin_18

    #define MDRB_BTN_PORT_KEY2     PORTE
    #define MDRB_BTN_PIN_KEY2      PORT_Pin_21
	
    #define MDRB_BTN_PORT_KEY3     PORTE
    #define MDRB_BTN_PIN_KEY3      PORT_Pin_22
	
    // for Initialization
    #define MDRB_BTNs_PORT_CLK      CLKCTRL_PER0_CLK_MDR_PORTE_EN
    #define MDRB_BTNs_PORT          PORTE
    #define MDRB_BTNs_PIN_MASK      (MDRB_BTN_PIN_KEY1 | MDRB_BTN_PIN_KEY2 | MDRB_BTN_PIN_KEY3)
    
    //  for Is_BtnAct_...
    #define MDRB_BTNs_PUSH_TO_GND  // use if connected to power!

    #define MDRB_BTN_PORT_SEL    MDRB_BTN_PORT_KEY1
    #define MDRB_BTN_PORT_UP     MDRB_BTN_PORT_KEY2
    #define MDRB_BTN_PORT_DOWN   MDRB_BTN_PORT_KEY3

    #define MDRB_BTN_PIN_SEL     MDRB_BTN_PIN_KEY1
    #define MDRB_BTN_PIN_UP      MDRB_BTN_PIN_KEY2
    #define MDRB_BTN_PIN_DOWN    MDRB_BTN_PIN_KEY3


//  ----------    LEDs Definition -------------
    #define MDRB_LED_PORT_CLK       CLKCTRL_PER0_CLK_MDR_PORTC_EN
    #define MDRB_LED_PORT           PORTC
  
    #define MDRB_LED_1              PORT_Pin_16
    #define MDRB_LED_2              PORT_Pin_17
    #define MDRB_LED_3              PORT_Pin_18
    #define MDRB_LED_4              PORT_Pin_19	
    #define MDRB_LED_5              PORT_Pin_20	
    #define MDRB_LED_6              PORT_Pin_21	
    #define MDRB_LED_7              PORT_Pin_22	
    #define MDRB_LED_8              PORT_Pin_23	
  
    #define MDRB_LED_Pins        (MDRB_LED_1 | MDRB_LED_2 | MDRB_LED_3 | MDRB_LED_4  \
                               | MDRB_LED_5 | MDRB_LED_6 | MDRB_LED_7 | MDRB_LED_8)

//  ----------    DMA Definition -------------
    #define MDRB_DMA_CLOCK_SELECT  (CLKCTRL_PER0_CLK_MDR_DMA0_EN)

#else
   Please, select board in MDRB_BoardSelect.h!

#endif // USE_BOARD_VE8


#endif // _MDRB_1986VE8_H

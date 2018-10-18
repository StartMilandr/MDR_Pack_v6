#ifndef _MDRB_1986VE3_H
#define _MDRB_1986VE3_H

#ifdef USE_MDR1986VE3

//===================================    Частота тактирования    ========================================
#define HSE_PLL_MUL_MAX     MDR_x10   //  HSE_max = 8MHz * 10 = 80MHz

//===================================    Заметки по плате    ========================================

//  Переопределение пинов для удобства поиска конфликтов
    #define PIN_PA0       MDR_Pin_0   //          LCD_D0
    #define PIN_PA1       MDR_Pin_1   //          LCD_D1
    #define PIN_PA2       MDR_Pin_2   //          LCD_D2
    #define PIN_PA3       MDR_Pin_3   //          LCD_D3
    #define PIN_PA4       MDR_Pin_4   //          LCD_D4
    #define PIN_PA5       MDR_Pin_5   //          LCD_D5
    #define PIN_PA6       MDR_Pin_6   //          LCD_D6
    #define PIN_PA7       MDR_Pin_7   //          LCD_D7    

    #define PIN_PB0       MDR_Pin_0   //  LED_1
    #define PIN_PB1       MDR_Pin_1   //  LED_2
    #define PIN_PB2       MDR_Pin_2   //  LED_3
    #define PIN_PB3       MDR_Pin_3   //  LED_4
    #define PIN_PB4       MDR_Pin_4   //  LED_5
    #define PIN_PB5       MDR_Pin_5   //  LED_6
    #define PIN_PB6       MDR_Pin_6   //  LED_7
    #define PIN_PB7       MDR_Pin_7   //  LED_8

    #define PIN_PC0       MDR_Pin_0   //          LCD_RW
    #define PIN_PC2       MDR_Pin_2   //          LCD_E
    
    #define PIN_PD12      MDR_Pin_12  //          LCD_RES

    #define PIN_PE12      MDR_Pin_12  //          LCD_A0
    #define PIN_PE13      MDR_Pin_13  //          LCD_E1
    #define PIN_PE14      MDR_Pin_14  //          LCD_E2

    #define PIN_PG12      MDR_Pin_12  //  Up
    #define PIN_PG11      MDR_Pin_11  //  Right
    #define PIN_PG15      MDR_Pin_15  //  Down
    #define PIN_PG7       MDR_Pin_7   //  Left
    #define PIN_PG14      MDR_Pin_14  //  Select
    #define PIN_PG13      MDR_Pin_13  //  Back


//  --------------  Buttons Definition  ------------
    #define MDRB_BTN_PORT_KEY1      MDR_GPIO_G
    #define MDRB_BTN_PIN_KEY1       PIN_PG12    // Up
	
    #define MDRB_BTN_PORT_KEY2      MDR_GPIO_G    
    #define MDRB_BTN_PIN_KEY2       PIN_PG11    // Right
	
    #define MDRB_BTN_PORT_KEY3      MDR_GPIO_G   
    #define MDRB_BTN_PIN_KEY3       PIN_PG15	  // Down
	
    #define MDRB_BTN_PORT_KEY4      MDR_GPIO_G  
    #define MDRB_BTN_PIN_KEY4       PIN_PG7     // Left

    #define MDRB_BTN_PORT_KEY5      MDR_GPIO_G 
    #define MDRB_BTN_PIN_KEY5       PIN_PG14    // Select 

    #define MDRB_BTN_PORT_KEY6      MDR_GPIO_G  
    #define MDRB_BTN_PIN_KEY6       PIN_PG13    // Back

    // for Initialization
    #define MDRB_BTN_GPIO           MDR_GPIO_G
    #define MDRB_BTN_PinSel        (MDRB_BTN_PIN_KEY1 | MDRB_BTN_PIN_KEY2 | MDRB_BTN_PIN_KEY3 | MDRB_BTN_PIN_KEY4 | MDRB_BTN_PIN_KEY5 | MDRB_BTN_PIN_KEY6)
    
    // Active buttons Level
    #define MDRB_BTNs_PUSH_TO_Ucc 

//  ----------    LEDs Definition -------------
    #define MDRB_LED_1              PIN_PB0   //  VD5
    #define MDRB_LED_2              PIN_PB1   //  VD6
    #define MDRB_LED_3              PIN_PB2   //  VD7
    #define MDRB_LED_4              PIN_PB3   //  VD8
    #define MDRB_LED_5              PIN_PB4   //  VD9
    #define MDRB_LED_6              PIN_PB5   //  VD10
    #define MDRB_LED_7              PIN_PB6   //  VD11
    #define MDRB_LED_8              PIN_PB7   //  VD12

    #define MDRB_LED_GPIO           MDR_GPIO_B
    #define MDRB_LED_PinAll        (MDRB_LED_1 | MDRB_LED_2 | MDRB_LED_3 | MDRB_LED_4  \
                                  | MDRB_LED_5 | MDRB_LED_6 | MDRB_LED_7 | MDRB_LED_8)

//  ----------    LCD Definition -------------
    // Initialization                 //  D0 .. D7
    #define MDRB_LCD_IN_PORT          MDR_GPIO_A
    #define MDRB_LCD_IN_PINS         (PIN_PA0 | PIN_PA1 | PIN_PA2 | PIN_PA3 | PIN_PA4 | PIN_PA5 | PIN_PA6 | PIN_PA7)
                                      // A0, E1, E2
    #define MDRB_LCD_OUT_PORT         MDR_GPIO_E
    #define MDRB_LCD_OUT_PINS        (PIN_PE12 | PIN_PE13 | PIN_PE14) 
                                      // RW, E
    #define MDRB_LCD_OUT_PORT_EX1     MDR_GPIO_C
    #define MDRB_LCD_OUT_PINS_EX1    (PIN_PC0 | PIN_PC2)
                                      // RES
    #define MDRB_LCD_OUT_PORT_EX2     MDR_GPIO_D
    #define MDRB_LCD_OUT_PINS_EX2    (PIN_PD12)

    //  Control Pins
    #define MDRB_LCD_E1_PORT          MDR_GPIO_E
    #define MDRB_LCD_E1_PIN           PIN_PE13

    #define MDRB_LCD_E2_PORT          MDR_GPIO_E
    #define MDRB_LCD_E2_PIN           PIN_PE14

    #define MDRB_LCD_A0_PORT          MDR_GPIO_E
    #define MDRB_LCD_A0_PIN           PIN_PE12

    #define MDRB_LCD_RW_PORT          MDR_GPIO_C
    #define MDRB_LCD_RW_PIN           PIN_PC0

    #define MDRB_LCD_E_PORT           MDR_GPIO_C
    #define MDRB_LCD_E_PIN            PIN_PC2

    #define MDRB_LCD_RES_PORT         MDR_GPIO_D
    #define MDRB_LCD_RES_PIN          PIN_PD12

    //  Bus Commands
    #define MDRB_LCD_BusSetOUT()        MDR_PORTA->OE |= 0x00FF;
    
    #define MDRB_LCD_BusSetIN()         MDR_PORTA->OE &= 0xFF00;
                                
    #define MDRB_LCD_BusWrite(value)    MDR_PORTA->RXTX &= 0xFF00;          \
                                        MDR_PORTA->RXTX |= (value & 0xFF);
                                    
    #define MDRB_LCD_BusRead()          (uint8_t)(MDR_PORTA->RXTX & 0xFF);


#else
   Please, select board in MDRB_BoardSelect.h!

#endif // USE_MDR1986VE3

#endif // _MDRB_1986VE3_H

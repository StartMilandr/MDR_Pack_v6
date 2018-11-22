#ifndef _MDRB_1901VC1_H
#define _MDRB_1901VC1_H

#ifdef USE_MDR1901VC1

//===================================    Частота тактирования    ========================================
#define HSE_PLL_MUL_MAX         MDR_x12                 //  HSE_max = 8MHz * 12 = 96MHz  (100MHz по спецификации)
#define HSE_LOW_SELRI_MAX       MDR_LOWRI_gt80MHz
#define HSE_EEPROM_DELAY_MAX    EEPROM_Delay_le100MHz

#define MDR_CPU_SetClock_HSE_Max(bypass)  MDR_CPU_SetClock_HSE_PLL((bypass), HSE_PLL_MUL_MAX, HSE_LOW_SELRI_MAX, HSE_EEPROM_DELAY_MAX, MDR_CLK_div1, HSE_TIMEOUT)

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
    #define PIN_PA6     MDR_Pin_6   //          LCD_D6
    #define PIN_PA7     MDR_Pin_7   //          LCD_D7    

    #define PIN_PB0     MDR_Pin_0   //                    JTAG_A
    #define PIN_PB1     MDR_Pin_1   //                    JTAG_A
    #define PIN_PB2     MDR_Pin_2   //                    JTAG_A
    #define PIN_PB3     MDR_Pin_3   //                    JTAG_A
    #define PIN_PB4     MDR_Pin_4   //                    JTAG_A      
    #define PIN_PB11    MDR_Pin_11  //  LED_5
    #define PIN_PB12    MDR_Pin_12  //  LED_4
    #define PIN_PB13    MDR_Pin_13  //  LED_3
    #define PIN_PB14    MDR_Pin_14  //  LED_2
    #define PIN_PB15    MDR_Pin_15  //  LED_1

    #define PIN_PC0     MDR_Pin_0   //  Select
    #define PIN_PC2     MDR_Pin_2   //          LCD_RW    
    #define PIN_PC3     MDR_Pin_3   //  Up
    #define PIN_PC4     MDR_Pin_4   //  Down
    #define PIN_PC5     MDR_Pin_5   //  Left
    #define PIN_PC6     MDR_Pin_6   //  Right
    #define PIN_PC7     MDR_Pin_7   //          LCD_E

    #define PIN_PD0     MDR_Pin_0   //                    JTAG_B                ADC_Ch0/ref+
    #define PIN_PD1     MDR_Pin_1   //                    JTAG_B                ADC_Ch1/ref-
    #define PIN_PD2     MDR_Pin_2   //                    JTAG_B                ADC_Ch2
    #define PIN_PD3     MDR_Pin_3   //                    JTAG_B                ADC_Ch3
    #define PIN_PD4     MDR_Pin_4   //                    JTAG_B                ADC_Ch4
    #define PIN_PD5     MDR_Pin_5   //                                          ADC_Ch5
    #define PIN_PD6     MDR_Pin_6   //                                          ADC_Ch6
    #define PIN_PD7     MDR_Pin_7   //                                          ADC_Ch7
    #define PIN_PD8     MDR_Pin_8   //                              ExtMem_CE   ADC_Ch8
    #define PIN_PD9     MDR_Pin_9   //          LCD_RES                         ADC_Ch9    
    #define PIN_PD10    MDR_Pin_10  //                                          ADC_Ch10
    #define PIN_PD11    MDR_Pin_11  //                                          ADC_Ch11
    #define PIN_PD12    MDR_Pin_12  //                                          ADC_Ch12
    #define PIN_PD13    MDR_Pin_13  //                                          ADC_Ch13
    #define PIN_PD14    MDR_Pin_14  //                                          ADC_Ch14
    #define PIN_PD15    MDR_Pin_15  //                                          ADC_Ch15

    #define PIN_PE4     MDR_Pin_4   //          LCD_E1
    #define PIN_PE5     MDR_Pin_5   //          LCD_E2
    #define PIN_PE11    MDR_Pin_11  //          LCD_A0



//  --------------  ADC Definition  ------------
    #define MDRB_ADC_CH_IN1            ADC_Signal_Ch6
    #define MDRB_ADC_CH_IN2            ADC_Signal_Ch7

    #define MDRB_ADC_PIN_ALL          0xFFFFUL
    #define MDRB_ADC_PIN_ALL_JTAG_B   0xFFE0UL
    #define MDRB_ADC_PIN_ALL_LCD      0xFCFFUL    


//  --------------  Buttons Definition  ------------
    #define MDRB_BTN_PORT_KEY1      MDR_GPIO_C    // UP
    #define MDRB_BTN_PIN_KEY1       PIN_PC3
	
    #define MDRB_BTN_PORT_KEY2      MDR_GPIO_C    // Right
    #define MDRB_BTN_PIN_KEY2       PIN_PC6
	
    #define MDRB_BTN_PORT_KEY3      MDR_GPIO_C    // Down
    #define MDRB_BTN_PIN_KEY3       PIN_PC4
	
    #define MDRB_BTN_PORT_KEY4      MDR_GPIO_C    // Left
    #define MDRB_BTN_PIN_KEY4       PIN_PC5

    #define MDRB_BTN_PORT_KEY5      MDR_GPIO_C    // Select
    #define MDRB_BTN_PIN_KEY5       PIN_PC0

    #define MDRB_BTN_PORT_KEY_P1    MDR_GPIO_C
    #define MDRB_BTN_PIN_KEY_P1     (PIN_PC3 | PIN_PC6)   //  Up + Right

    // for Initialization
    #define MDRB_BTN_GPIO           MDR_GPIO_C
    #define MDRB_BTN_PinSel         (MDRB_BTN_PIN_KEY1 | MDRB_BTN_PIN_KEY2 | MDRB_BTN_PIN_KEY3 | MDRB_BTN_PIN_KEY4 | MDRB_BTN_PIN_KEY5)
    
    // Active buttons Level
    #define MDRB_BTNs_PUSH_TO_GND

//  ----------    LEDs Definition -------------
    #define MDRB_LED_1 	            PIN_PB15    // VD3
    #define MDRB_LED_2 	            PIN_PB14    // VD4
    #define MDRB_LED_3 	            PIN_PB13    // VD5
    #define MDRB_LED_4 	            PIN_PB12    // VD6
    #define MDRB_LED_5 	            PIN_PB11    // VD7

    #define MDRB_LED_GPIO           MDR_GPIO_B
    #define MDRB_LED_PinAll         MDRB_LED_1 | MDRB_LED_2 | MDRB_LED_3 | MDRB_LED_4 | MDRB_LED_5

//  ----------  LCD Definition ---------------
    // Initialization                 //  D0 .. D7
    #define MDRB_LCD_IN_PORT          MDR_GPIO_A
    #define MDRB_LCD_IN_PINS         (PIN_PA0 | PIN_PA1 | PIN_PA2 | PIN_PA3 | PIN_PA4 | PIN_PA5 | PIN_PA6 | PIN_PA7)
                                      //  E1, E2, A0
    #define MDRB_LCD_OUT_PORT         MDR_GPIO_E
    #define MDRB_LCD_OUT_PINS        (PIN_PE4 | PIN_PE5 | PIN_PE11) 
                                      //  RW, E
    #define MDRB_LCD_OUT_PORT_EX1     MDR_GPIO_C
    #define MDRB_LCD_OUT_PINS_EX1    (PIN_PC2 | PIN_PC7)
                                      // RES
    #define MDRB_LCD_OUT_PORT_EX2     MDR_GPIO_D
    #define MDRB_LCD_OUT_PINS_EX2    (PIN_PD9 | PIN_PD8)  // PIN_PD8 - для отключения микросхемы памяти при работе с LCD
    
    #define MDRB_LCD_CONFLICT_PORT    MDR_GPIO_D
    #define MDRB_LCD_CONFLICT_PIN     PIN_PD8
    
    //  Control Pins
    #define MDRB_LCD_E1_PORT          MDR_GPIO_E
    #define MDRB_LCD_E1_PIN           PIN_PE4

    #define MDRB_LCD_E2_PORT          MDR_GPIO_E
    #define MDRB_LCD_E2_PIN           PIN_PE5

    #define MDRB_LCD_RES_PORT         MDR_GPIO_D
    #define MDRB_LCD_RES_PIN          PIN_PD9

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


//  ----------  SDIO Definition ---------------
    #define MDRB_SDIO_PIN_CLK      PORT_Pin_8       // PC8
    #define MDRB_SDIO_PIN_CMD      PORT_Pin_1       // PC1
    #define MDRB_SDIO_PIN_D0       PORT_Pin_10      // PC10
    #define MDRB_SDIO_PIN_D1       PORT_Pin_11      // PC11
    #define MDRB_SDIO_PIN_D2       PORT_Pin_12      // PC12
    #define MDRB_SDIO_PIN_D3       PORT_Pin_13      // PC13

    #define MDRB_SDIO_PORT_CLK       RST_CLK_PCLK_PORTC
    #define MDRB_SDIO_PORT           MDR_PORTC
    
    #define MDRB_SDIO_PORT_D0        MDR_PORTC //  for Write ack
    
    #define MDRB_SDIO_INIT_PORT           MDR_PORTC
    #define MDRB_SDIO_INIT_PIN            MDRB_SDIO_PIN_D0 | MDRB_SDIO_PIN_D1 | MDRB_SDIO_PIN_D2 | MDRB_SDIO_PIN_D3
    #define MDRB_SDIO_INIT_FUNC           PORT_FUNC_MAIN
    #define MDRB_SDIO_INIT_PULLUP         PORT_PULL_UP_ON

    #define MDRB_SDIO_INIT_PORT_1         MDR_PORTC
    #define MDRB_SDIO_INIT_PIN_1          MDRB_SDIO_PIN_CMD
    #define MDRB_SDIO_INIT_FUNC_1         PORT_FUNC_OVERRID
    #define MDRB_SDIO_INIT_PULLUP_1       PORT_PULL_UP_ON
    
    #define MDRB_SDIO_INIT_PORT_2         MDR_PORTC
    #define MDRB_SDIO_INIT_PIN_2          MDRB_SDIO_PIN_CLK
    #define MDRB_SDIO_INIT_FUNC_2         PORT_FUNC_MAIN
    #define MDRB_SDIO_INIT_PULLUP_2       PORT_PULL_UP_OFF    

//  ---------------  ExtBUS Definition ----------------
    //  Data: [PA0 .. PA15] = [D0 .. D15]    
    #define MDRB_EBC_DATA_PORT_LO8         MDR_PORTA
    #define MDRB_EBC_DATA_PORT_LO8_CLK     RST_CLK_PCLK_PORTA
    #define MDRB_EBC_DATA_PORT_LO8_PINS    (PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2 | PORT_Pin_3  | PORT_Pin_4  | PORT_Pin_5 | PORT_Pin_6 | PORT_Pin_7)
    #define MDRB_EBC_DATA_PORT_LO8_FUNC    PORT_FUNC_MAIN

    //  Data: [PA0 .. PA15] = [D0 .. D15]    
    #define MDRB_EBC_DATA_PORT_LO16        MDR_PORTA
    #define MDRB_EBC_DATA_PORT_LO16_CLK    RST_CLK_PCLK_PORTA
    #define MDRB_EBC_DATA_PORT_LO16_PINS   PORT_Pin_All
    #define MDRB_EBC_DATA_PORT_LO16_FUNC   PORT_FUNC_MAIN

    //  Data: [PB0 .. PB15] = [D16 .. D31]
    #define MDRB_EBC_DATA_PORT_HI16        MDR_PORTB
    #define MDRB_EBC_DATA_PORT_HI16_CLK    RST_CLK_PCLK_PORTB
    #define MDRB_EBC_DATA_PORT_HI16_PINS   PORT_Pin_All
    #define MDRB_EBC_DATA_PORT_HI16_FUNC   PORT_FUNC_MAIN   

    //  Ctrl: PC1 - OE, PC2 - WE, [PC3 .. PC6] = [BE0 - BE3]
    #define MDRB_EBC_PORT_CTRL             MDR_PORTC
    #define MDRB_EBC_PORT_CTRL_CLK         RST_CLK_PCLK_PORTC
    #define MDRB_EBC_PORT_CTRL_PINS        (PORT_Pin_1 | PORT_Pin_2 | PORT_Pin_3 | PORT_Pin_4 | PORT_Pin_5 | PORT_Pin_6)
    #define MDRB_EBC_PORT_CTRL_FUNC        PORT_FUNC_MAIN

    //  Addr: [PF0 .. PF15] = [A0 - A15]    
    #define MDRB_EBC_PORT_ADDR20           MDR_PORTF
    #define MDRB_EBC_PORT_ADDR20_CLK       RST_CLK_PCLK_PORTF
    #define MDRB_EBC_PORT_ADDR20_PINS      PORT_Pin_All
    #define MDRB_EBC_PORT_ADDR20_FUNC      PORT_FUNC_MAIN

    //  Addr: [PE0 .. RE3] = [A16 .. A19]
    #define MDRB_EBC_PORT_ADDR20_1_USED
    #define MDRB_EBC_PORT_ADDR20_1         MDR_PORTE
    #define MDRB_EBC_PORT_ADDR20_1_CLK     RST_CLK_PCLK_PORTE
    #define MDRB_EBC_PORT_ADDR20_1_PINS    (PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2 | PORT_Pin_3)
    #define MDRB_EBC_PORT_ADDR20_1_FUNC    PORT_FUNC_MAIN

    #define MDRB_EBC_START_ADDR	    0x10000000
    #define MDRB_EBC_A20_D32_CLK     (MDRB_EBC_DATA_PORT_LO8_CLK | MDRB_EBC_DATA_PORT_LO16_CLK | MDRB_EBC_DATA_PORT_HI16_CLK | MDRB_EBC_PORT_CTRL_CLK | MDRB_EBC_PORT_ADDR20_CLK | MDRB_EBC_PORT_ADDR20_1_CLK)



#else
   Please, select board in MDRB_BoardSelect.h!

#endif // USE_MDR1901VC1

#endif // _MDRB_1901VC1_H


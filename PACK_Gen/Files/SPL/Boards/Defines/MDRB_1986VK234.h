#ifndef _MDRB_1986VK234_H
#define _MDRB_1986VK234_H

#ifdef USE_MDR1986VK234

//===================================    Частота тактирования    ========================================
#define HSE_PLL_MUL_MAX         MDR_x4   //  HSE_max = 8MHz * 4 = 32MHz (36MHz max)
#define HSE_LOW_SELRI_MAX       MDR_LOWRI_le40MHz
#define HSE_EEPROM_DELAY_MAX    EEPROM_Delay_le36MHz

#define MDR_CPU_SetClock_HSE_Max(bypass)  MDR_CPU_SetClock_HSE_PLL((bypass), HSE_PLL_MUL_MAX, HSE_LOW_SELRI_MAX, HSE_EEPROM_DELAY_MAX, MDR_CLK_div1, HSE_TIMEOUT)

//===================================    Заметки по плате    ========================================

//  Переопределение пинов для удобства поиска конфликтов
    #define PIN_PA0       MDR_Pin_0   // KEY1 UP                                    T1_CH1
    #define PIN_PA1       MDR_Pin_1   // KEY2 Right                                 T1_nCH1
    #define PIN_PA2       MDR_Pin_2   // KEY3 Down                                  T1_CH2
    #define PIN_PA3       MDR_Pin_3   // KEY4 Left                                  T1_nCH2
    #define PIN_PA4       MDR_Pin_4   // NC                                         T1_CH3
    #define PIN_PA5       MDR_Pin_5   // NC                                         T1_nCH3
    #define PIN_PA6       MDR_Pin_6   //              JTAG_A SWCLK                  T1_CH4
    #define PIN_PA7       MDR_Pin_7   //              JTAG_A SWDIO                  T1_nCH4
    #define PIN_PA8       MDR_Pin_8   // NC                                         T1_ETR
    #define PIN_PA9       MDR_Pin_9   // NC                                         T1_BRK
    #define PIN_PA10      MDR_Pin_10  // NC
    #define PIN_PA11      MDR_Pin_11  //                      LCD_DIN
    #define PIN_PA12      MDR_Pin_12  //          SSP1_FSS    LCD_DCLK
    #define PIN_PA13      MDR_Pin_13  //          SSP1_CLK
    #define PIN_PA14      MDR_Pin_14  //          SSP1_RX
    #define PIN_PA15      MDR_Pin_15  //          SSP1_TX

    #define PIN_PB0       MDR_Pin_0   //                   UART1_TX
    #define PIN_PB1       MDR_Pin_1   //                   UART1_RX
    #define PIN_PB2       MDR_Pin_2   //
    #define PIN_PB3       MDR_Pin_3   //
    #define PIN_PB4       MDR_Pin_4   //
    #define PIN_PB5       MDR_Pin_5   //
    #define PIN_PB6       MDR_Pin_6   // NC                          ADC_Ch7  
    #define PIN_PB7       MDR_Pin_7   // NC                          ADC_Ch6
    #define PIN_PB8       MDR_Pin_8   //                             ADC_Ch5   
    #define PIN_PB9       MDR_Pin_9   //                             ADC_Ch4 - TuneResistor
    #define PIN_PB10      MDR_Pin_10  // NC                                         T2_CH2
    #define PIN_PB11      MDR_Pin_11  //                      LCD_LOAD              T2_nCH2
    #define PIN_PB12      MDR_Pin_12  //                                            T2_CH3    Mem_CS
    #define PIN_PB13      MDR_Pin_13  // NC                                         T2_nCH3
    #define PIN_PB14      MDR_Pin_14  // NC                                         T2_CH4

    #define PIN_PC0       MDR_Pin_0   //                   UART2_TX                           RS485_DI
    #define PIN_PC1       MDR_Pin_1   //                   UART2_RX  ADC_Ch3                  RS485_RO
    #define PIN_PC2       MDR_Pin_2   //                             ADC_Ch2        T2_CH1    RS485_DE_nRE
    #define PIN_PC3       MDR_Pin_3   // NC                          ADC_Ch1/Ref+   T2_nCH1
    #define PIN_PC4       MDR_Pin_4   //    LED1                     ADC_Ch0/Ref- 
    #define PIN_PC5       MDR_Pin_5   //    LED2 
    #define PIN_PC6       MDR_Pin_6   //    LED3                                    T2_ETR
    #define PIN_PC7       MDR_Pin_7   //    LED4                                    T2_BRK
    
//  --------------  ADC Definition  ------------
    #define MDRB_ADC_CH_IN1            ADC_Signal_Ch4   //  PIN_PB8    
    #define MDRB_ADC_CH_IN2            ADC_Signal_Ch5   //  PIN_PB6
    
    #define MDRB_ADC_CH_TUNE           ADC_Signal_Ch4

    #define MDRB_ADC_PORT_ALL1          MDR_GPIO_C
    #define MDRB_ADC_PINS_ALL1          0x001EUL    
    #define MDRB_ADC_PORT_ALL2          MDR_GPIO_B
    #define MDRB_ADC_PINS_ALL2          0x03C0UL
    
    //#define MDRB_ADC_PIN_KEY_PROTECT2   0x01C0UL

//  --------------  Jtag protection  ------------
    #define MDRB_Jtag_ClrPinsPA    (~MDR_JTAG_A_PINS)
    
//  --------------  Buttons Definition  ------------
    #define MDRB_BTN_PORT_KEY1      MDR_GPIO_A
    #define MDRB_BTN_PIN_KEY1       PIN_PA0   // Up

    #define MDRB_BTN_PORT_KEY2      MDR_GPIO_A
    #define MDRB_BTN_PIN_KEY2       PIN_PA1   // Right

    #define MDRB_BTN_PORT_KEY3      MDR_GPIO_A
    #define MDRB_BTN_PIN_KEY3       PIN_PA2    // Down
	
    #define MDRB_BTN_PORT_KEY4      MDR_GPIO_A
    #define MDRB_BTN_PIN_KEY4       PIN_PA3   // Left

    #define MDRB_BTN_PORT_KEY_P1    MDR_GPIO_A
    #define MDRB_BTN_PIN_KEY_P1     (MDRB_BTN_PIN_KEY1 | MDRB_BTN_PIN_KEY2)   //  Up + Right

    #define MDRB_BTN_PORT_KEY_P2    MDR_GPIO_A
    #define MDRB_BTN_PIN_KEY_P2     (MDRB_BTN_PIN_KEY3 | MDRB_BTN_PIN_KEY4)    //  Up + Left 	
  
    // for Initialization
    #define MDRB_BTN_GPIO           MDR_GPIO_A
    #define MDRB_BTN_PinSel         (MDRB_BTN_PIN_KEY1 | MDRB_BTN_PIN_KEY2 | MDRB_BTN_PIN_KEY3 | MDRB_BTN_PIN_KEY4)

    // Active buttons Level
    #define MDRB_BTNs_PUSH_TO_GND 

//  ----------    LEDs Definition -------------
    #define MDRB_LED_1 	           PIN_PC4    // VD5
    #define MDRB_LED_2 	           PIN_PC5    // VD6
    #define MDRB_LED_3 	           PIN_PC6    // VD7
    #define MDRB_LED_4 	           PIN_PC7    // VD8

    #define MDRB_LED_GPIO          MDR_GPIO_C
    #define MDRB_LED_PinAll        (MDRB_LED_1 | MDRB_LED_2 | MDRB_LED_3 | MDRB_LED_4)


//  ---------------  SPI1 Pin Definition ----------------
  //  PORT_A: SSP1_PA12,PC13,PC14,PC15 - Main
  #define MDRB_SPI1_FSS_PA12_Ind	     12
	#define MDRB_SPI1_CLK_PA13_Ind	     13
	#define MDRB_SPI1_RX_PA14_Ind 	     14
	#define MDRB_SPI1_TX_PA15_Ind		     15

  #define MDRB_SPI1_FSS_PA12_Msk	     MDR_Pin_12
	#define MDRB_SPI1_CLK_PA13_Msk		   MDR_Pin_13
	#define MDRB_SPI1_RX_PA14_Msk 		   MDR_Pin_14
	#define MDRB_SPI1_TX_PA15_Msk		     MDR_Pin_15

  #define MDRB_SPI1_FSS_PA12_Port	     MDR_GPIO_A
	#define MDRB_SPI1_CLK_PA13_Port		   MDR_GPIO_A
	#define MDRB_SPI1_RX_PA14_Port 		   MDR_GPIO_A
	#define MDRB_SPI1_TX_PA15_Port		   MDR_GPIO_A
  
  #define MDRB_SPI1_FSS_PA12_Func	     MDR_PIN_MAIN
	#define MDRB_SPI1_CLK_PA13_Func		   MDR_PIN_MAIN
	#define MDRB_SPI1_RX_PA14_Func 		   MDR_PIN_MAIN
	#define MDRB_SPI1_TX_PA15_Func		   MDR_PIN_MAIN


//  ----------  LCD Definition ---------------
    // Initialization                 //  
    #define MDRB_LCD_PORT             MDR_GPIO_A
    #define MDRB_LCD_DIN              PIN_PA11
    #define MDRB_LCD_DCLK             PIN_PA12
    #define MDRB_LCD_PINS            (MDRB_LCD_DIN | MDRB_LCD_DCLK)
    
    #define MDRB_LCD_PORT_LD          MDR_GPIO_B
    #define MDRB_LCD_PINS_LD          PIN_PB11
    
    #define LCD_HTD_B083_DISPLAY

//  ---------------  UART1 Pin Definition ----------------
  //  PORT_B: PB0, PB1 - Main
  #define MDRB_UART1_TX_PB0_Ind	     0
  #define MDRB_UART1_RX_PB1_Ind	     1

  #define MDRB_UART1_TX_PB0_Msk	     MDR_Pin_0
	#define MDRB_UART1_RX_PB1_Msk		   MDR_Pin_1

  #define MDRB_UART1_TX_PB0_Port	   MDR_GPIO_B
	#define MDRB_UART1_RX_PB1_Port		 MDR_GPIO_B
  
  #define MDRB_UART1_TX_PB0_Func	   MDR_PIN_MAIN
	#define MDRB_UART1_RX_PB1_Func	   MDR_PIN_MAIN

//  ---------------  UART2 Pin Definition ----------------
  //  PORT_C: PC0, PC1 - Main
  #define MDRB_UART2_TX_PC0_Ind	     0
  #define MDRB_UART2_RX_PC1_Ind	     1

  #define MDRB_UART2_TX_PC0_Msk	     MDR_Pin_0
	#define MDRB_UART2_RX_PC1_Msk		   MDR_Pin_1

  #define MDRB_UART2_TX_PC0_Port	   MDR_GPIO_C
	#define MDRB_UART2_RX_PC1_Port		 MDR_GPIO_C
  
  #define MDRB_UART2_TX_PC0_Func	   MDR_PIN_MAIN
	#define MDRB_UART2_RX_PC1_Func	   MDR_PIN_MAIN


#else
   Please, select board in MDRB_BoardSelect.h!

#endif // USE_MDR1986VK234

#endif // _MDRB_1986VK234_H


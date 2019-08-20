#ifndef _MDRB_1986VE4_H
#define _MDRB_1986VE4_H

#ifdef USE_MDR1986VE4

//===================================    Частота тактирования    ========================================
#define HSE_PLL_MUL_MAX         MDR_x4   //  HSE_max = 8MHz * 4 = 32MHz (36MHz max)
#define HSE_LOW_SELRI_MAX       MDR_LOWRI_le40MHz
#define HSE_EEPROM_DELAY_MAX    EEPROM_Delay_le36MHz

#define MDRB_CLK_PLL_HSE_RES_MAX     MDR_CPU_CFG_PLL_HSE_RES_DEF(HSE_PLL_MUL_MAX, HSE_EEPROM_DELAY_MAX, HSE_LOW_SELRI_MAX)

//===================================    Заметки по плате    ========================================

//  Переопределение пинов для удобства поиска конфликтов
    #define PIN_PA0       MDR_Pin_0   //          LCD_D0                    T1_CH1
    #define PIN_PA1       MDR_Pin_1   //          LCD_D1                    T1_nCH1
    #define PIN_PA2       MDR_Pin_2   //          LCD_D2                    T1_CH2
    #define PIN_PA3       MDR_Pin_3   //          LCD_D3                    T1_nCH2
    #define PIN_PA4       MDR_Pin_4   //          LCD_A0                    T1_CH3
    #define PIN_PA5       MDR_Pin_5   //                                    T1_nCH3
    #define PIN_PA6       MDR_Pin_6   //                  JTAG_A            T1_CH4
    #define PIN_PA7       MDR_Pin_7   //                  JTAG_A            T1_nCH4
    #define PIN_PA8       MDR_Pin_8   //                                    T1_ETR
    #define PIN_PA9       MDR_Pin_9   //                                    T1_BRK
    #define PIN_PA10      MDR_Pin_10  //
    #define PIN_PA11      MDR_Pin_11  //  LED_1    
    #define PIN_PA12      MDR_Pin_12  //                       SSP1_FSS
    #define PIN_PA13      MDR_Pin_13  //                       SSP1_CLK
    #define PIN_PA14      MDR_Pin_14  //          LCD_WR1      SSP1_RX
    #define PIN_PA15      MDR_Pin_15  //          LCD_WR2      SSP1_TX

    #define PIN_PB0       MDR_Pin_0   //                   UART1_TX
    #define PIN_PB1       MDR_Pin_1   //                   UART1_RX
    #define PIN_PB2       MDR_Pin_2   //
    #define PIN_PB3       MDR_Pin_3   //
    #define PIN_PB4       MDR_Pin_4   //
    #define PIN_PB5       MDR_Pin_5   //
    #define PIN_PB6       MDR_Pin_6   //                                              ADC_Ch7  - TuneResistor
    #define PIN_PB7       MDR_Pin_7   //                                              ADC_Ch6
    #define PIN_PB8       MDR_Pin_8   //                                              ADC_Ch5   
    #define PIN_PB9       MDR_Pin_9   //  Down                                        ADC_Ch4
    #define PIN_PB10      MDR_Pin_10  //  Right                             T2_CH2
    #define PIN_PB11      MDR_Pin_11  //  Up                                T2_nCH2
    #define PIN_PB12      MDR_Pin_12  //  Left                              T2_CH3
    #define PIN_PB13      MDR_Pin_13  //                                    T2_nCH3
    #define PIN_PB14      MDR_Pin_14  //                                    T2_CH4

    #define PIN_PC0       MDR_Pin_0   //                   UART2_TX
    #define PIN_PC1       MDR_Pin_1   //                   UART2_RX                   ADC_Ch3
    #define PIN_PC2       MDR_Pin_2   //                                    T2_CH1    ADC_Ch2  - TuneResistor (CMP)
    #define PIN_PC3       MDR_Pin_3   //                                    T2_nCH1   ADC_Ch1/Ref+
    #define PIN_PC4       MDR_Pin_4   //                                              ADC_Ch0/Ref-
    #define PIN_PC5       MDR_Pin_5   //                                              
    #define PIN_PC6       MDR_Pin_6   //                                    T2_ETR          
    #define PIN_PC7       MDR_Pin_7   //                                    T2_BRK    
    
    
//  --------------  ADC Definition  ------------
    #define MDRB_ADC_CH_IN1            ADC_Signal_Ch5   //  PIN_PB8    
    #define MDRB_ADC_CH_IN2            ADC_Signal_Ch7   //  PIN_PB6
    #define MDRB_ADC_CH_IN3            ADC_Signal_Ch2   //  PIN_PC2
    
    #define MDRB_ADC_CH_TUNE           ADC_Signal_Ch2   //  and ADC_Signal_Ch7

    #define MDRB_ADC_PORT_ALL1          MDR_GPIO_C
    #define MDRB_ADC_PINS_ALL1          0x001EUL    
    #define MDRB_ADC_PORT_ALL2          MDR_GPIO_B
    #define MDRB_ADC_PINS_ALL2          0x03C0UL
    
    #define MDRB_ADC_PIN_KEY_PROTECT2   0x01C0UL

    #define MDRB_ADC_TUNE_PORT          MDR_GPIO_C
    #define MDRB_ADC_TUNE_PIN           PIN_PC2


//  --------------  Buttons Definition  ------------
    #define MDRB_BTN_PORT_KEY1      MDR_GPIO_B
    #define MDRB_BTN_PIN_KEY1       PIN_PB11   //  Up

    #define MDRB_BTN_PORT_KEY2      MDR_GPIO_B
    #define MDRB_BTN_PIN_KEY2       PIN_PB10   //  Right

    #define MDRB_BTN_PORT_KEY3      MDR_GPIO_B
    #define MDRB_BTN_PIN_KEY3       PIN_PB9    //  Down
	
    #define MDRB_BTN_PORT_KEY4      MDR_GPIO_B
    #define MDRB_BTN_PIN_KEY4       PIN_PB12   //  Left
    
    #define MDRB_BTN_PORT_KEY_P1    MDR_GPIO_B
    #define MDRB_BTN_PIN_KEY_P1     (PIN_PB11 | PIN_PB10)   //  Up + Right

    #define MDRB_BTN_PORT_KEY_P2    MDR_GPIO_B
    #define MDRB_BTN_PIN_KEY_P2     (PIN_PB11 | PIN_PB12)    //  Up + Left

	
    // for Initialization
    #define MDRB_BTN_GPIO           MDR_GPIO_B
    #define MDRB_BTN_PinSel         (MDRB_BTN_PIN_KEY1 | MDRB_BTN_PIN_KEY2 | MDRB_BTN_PIN_KEY3 | MDRB_BTN_PIN_KEY4)

    // Active buttons Level
    #define MDRB_BTNs_PUSH_TO_GND 

//  ----------    LEDs Definition -------------
    #define MDRB_LED_1 	           PIN_PA11    // VD3

    #define MDRB_LED_GPIO          MDR_GPIO_A
    #define MDRB_LED_PinAll        MDRB_LED_1

//  ----------  LCD Definition ---------------
    // Initialization                 //  D0 .. D3, A0, WR1, WR2
    #define MDRB_LCD_PORT             MDR_GPIO_A
    #define MDRB_LCD_PINS            (PIN_PA0 | PIN_PA1 | PIN_PA2 | PIN_PA3 | PIN_PA4 | PIN_PA14 | PIN_PA15)
    
    //  Control Pins
    #define MDRB_LCD_WR1_PORT         MDR_GPIO_A
    #define MDRB_LCD_WR1_PIN          PIN_PA14

    #define MDRB_LCD_WR2_PORT         MDR_GPIO_A
    #define MDRB_LCD_WR2_PIN          PIN_PA15

    #define MDRB_LCD_A0_PORT          MDR_GPIO_A
    #define MDRB_LCD_A0_PIN           PIN_PA4

    
    //  Bus Commands                              
    #define MDRB_LCD_BusWrite(value)    MDR_PORTA->RXTX &= 0xFFF0;          \
                                        MDR_PORTA->RXTX |= ((value) & 0x0FUL)
    
    #define LCD_MT_10T7_DISPLAY
    #define MDRB_HAS_LCD


//  ---------------  SPI1 Pin Definition ----------------
  //  PORT_A: SSP1_PA12,PC13,PC14,PC15 - Main
  #define MDRB_SPI1_FSS_PA12_Ind	     12
	#define MDRB_SPI1_CLK_PA13_Ind	     13
	#define MDRB_SPI1_RX_PA14_Ind 	     14
	#define MDRB_SPI1_TX_PA15_Ind		     15

  #define MDRB_SPI1_FSS_PA12_Msk	     PORT_Pin_12
	#define MDRB_SPI1_CLK_PA13_Msk		   PORT_Pin_13
	#define MDRB_SPI1_RX_PA14_Msk 		   PORT_Pin_14
	#define MDRB_SPI1_TX_PA15_Msk		     PORT_Pin_15

  #define MDRB_SPI1_FSS_PA12_Port	     MDR_GPIO_A
	#define MDRB_SPI1_CLK_PA13_Port		   MDR_GPIO_A
	#define MDRB_SPI1_RX_PA14_Port 		   MDR_GPIO_A
	#define MDRB_SPI1_TX_PA15_Port		   MDR_GPIO_A
  
  #define MDRB_SPI1_FSS_PA12_Func	     MDR_PIN_MAIN
	#define MDRB_SPI1_CLK_PA13_Func		   MDR_PIN_MAIN
	#define MDRB_SPI1_RX_PA14_Func 		   MDR_PIN_MAIN
	#define MDRB_SPI1_TX_PA15_Func		   MDR_PIN_MAIN

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

#endif // USE_MDR1986VE4 

#endif // _MDRB_1986VE4_H


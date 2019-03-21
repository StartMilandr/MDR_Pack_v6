#ifndef _MDRB_1986VE1_H
#define _MDRB_1986VE1_H

#ifdef USE_MDR1986VE1


//===================================    Частота тактирования    ========================================
#define HSE_PLL_MUL_MAX         MDR_x16   //  HSE_max = 8MHz * 16 = 128MHz
#define HSE_LOW_SELRI_MAX       MDR_LOWRI_gt80MHz
#define HSE_EEPROM_DELAY_MAX    EEPROM_Delay_le150MHz

#define MDR_CPU_SetClock_HSE_Max(bypass)  MDR_CPU_SetClock_HSE_PLL((bypass), HSE_PLL_MUL_MAX, HSE_LOW_SELRI_MAX, HSE_EEPROM_DELAY_MAX, MDR_CLK_div1, HSE_TIMEOUT)

//===================================    Заметки по плате    ========================================
// -  Кнопки Up и Down совпадают в выводами JTAG. Поэтому, при работе с кнопками необходимо подключаться по Jtag_А. В файле MDR_Congif.h выбрать USE_JTAG_А.
//    Для работы кнопок Up и Down необходимо установить перемычки X33, X34. При этом Jtag_В становится недоступен.


//  Переопределение пинов для удобства поиска конфликтов
    #define PIN_PA0     MDR_Pin_0   //          LCD_D0
    #define PIN_PA1     MDR_Pin_1   //          LCD_D1
    #define PIN_PA2     MDR_Pin_2   //          LCD_D2
    #define PIN_PA3     MDR_Pin_3   //          LCD_D3
    #define PIN_PA4     MDR_Pin_4   //          LCD_D4
    #define PIN_PA5     MDR_Pin_5   //          LCD_D5
    #define PIN_PA6     MDR_Pin_6   //          LCD_D6    T4_CH1
    #define PIN_PA7     MDR_Pin_7   //          LCD_D7    T4_nCH1
    #define PIN_PA8     MDR_Pin_8   //                    T4_CH2
    #define PIN_PA9     MDR_Pin_9   //                    T4_nCH2
    #define PIN_PA10    MDR_Pin_10  //                    T4_CH3
    #define PIN_PA11    MDR_Pin_11  //                    T4_nCH3
    #define PIN_PA12    MDR_Pin_12  //                    T4_CH4
    #define PIN_PA13    MDR_Pin_13  //                    T4_nCH4
    #define PIN_PA14    MDR_Pin_14  //                    T4_ETR
    #define PIN_PA15    MDR_Pin_15  //                    T4_BRK

    #define PIN_PB0     MDR_Pin_0   //                    T3_CH1
    #define PIN_PB1     MDR_Pin_1   //                    T3_nCH1
    #define PIN_PB2     MDR_Pin_2   //                    T3_CH2
    #define PIN_PB3     MDR_Pin_3   //                    T3_nCH2
    #define PIN_PB4     MDR_Pin_4   //                    T3_CH3
    #define PIN_PB5     MDR_Pin_5   //                    T3_nCH3
    #define PIN_PB6     MDR_Pin_6   //                    T3_CH4
    #define PIN_PB7     MDR_Pin_7   //                    T3_nCH4
    #define PIN_PB8     MDR_Pin_8   //                    T1_nCH1
    #define PIN_PB9     MDR_Pin_9   //                    T2_nCH1
    #define PIN_PB10    MDR_Pin_10  //                    T1_nCH2
    #define PIN_PB11    MDR_Pin_11  //                    T2_nCH2
    #define PIN_PB12    MDR_Pin_12  //                    T1_nCH3
    #define PIN_PB13    MDR_Pin_13  //                    T2_nCH3
    #define PIN_PB14    MDR_Pin_14  //                    T1_nCH4
    #define PIN_PB15    MDR_Pin_15  //                    T2_nCH4


    #define PIN_PC0     MDR_Pin_0   //          LCD_RW
    #define PIN_PC1     MDR_Pin_1   //          
    #define PIN_PC2     MDR_Pin_2   //          LCD_E    
    #define PIN_PC3     MDR_Pin_3   //                                                    UART1_TX
    #define PIN_PC4     MDR_Pin_4   //                                                    UART1_RX
    #define PIN_PC5     MDR_Pin_5   //                  SSP1_TX/RX
    #define PIN_PC6     MDR_Pin_6   //                  SSP1_RX/TX
    #define PIN_PC7     MDR_Pin_7   //                  SSP1_CLK
    #define PIN_PC8     MDR_Pin_8   //                  SSP1_FSS
    #define PIN_PC9     MDR_Pin_9   //                       SSP2_TX
    #define PIN_PC10    MDR_Pin_10  //                       SSP2_RX
    #define PIN_PC11    MDR_Pin_11  //                       SSP2_CLK
    #define PIN_PC12    MDR_Pin_12  //                       SSP2_FSS

    #define PIN_PD2     MDR_Pin_2   //                  SSP1_TX/RX
    #define PIN_PD3     MDR_Pin_3   //                  SSP1_RX/TX
    #define PIN_PD4     MDR_Pin_4   //                  SSP1_CLK
    #define PIN_PD5     MDR_Pin_5   //                  SSP1_FSS
    #define PIN_PD6     MDR_Pin_6   //                  
    #define PIN_PD7     MDR_Pin_7   //  LED_1                SSP2_TX          ADC_Ch0/Ref+
    #define PIN_PD8     MDR_Pin_8   //  LED_2                SSP2_RX          ADC_Ch1/Ref-
    #define PIN_PD9     MDR_Pin_9   //  LED_3                SSP2_CLK         ADC_Ch2
    #define PIN_PD10    MDR_Pin_10  //  LED_4                SSP2_FSS         ADC_Ch3
    #define PIN_PD11    MDR_Pin_11  //  LED_5                                 ADC_Ch4
    #define PIN_PD12    MDR_Pin_12  //  LED_6                     SSP3_TX/RX  ADC_Ch5
    #define PIN_PD13    MDR_Pin_13  //  LED_7                                 ADC_Ch6     UART2_TX
    #define PIN_PD14    MDR_Pin_14  //  LED_8                                 ADC_Ch7     UART2_RX

    #define PIN_PE0     MDR_Pin_0   //                    
    #define PIN_PE1     MDR_Pin_1   //                    
    #define PIN_PE2     MDR_Pin_2   //                    
    #define PIN_PE3     MDR_Pin_3   //                    T1_CH1
    #define PIN_PE4     MDR_Pin_4   //                    T1_CH2
    #define PIN_PE5     MDR_Pin_5   //  Down              T1_CH3
    #define PIN_PE6     MDR_Pin_6   //                    T1_CH4
    #define PIN_PE7     MDR_Pin_7   //                    T2_CH1
    #define PIN_PE8     MDR_Pin_8   //  Up                T2_CH2
    #define PIN_PE9     MDR_Pin_9   //  Select            T2_CH3
    #define PIN_PE10    MDR_Pin_10  //  Left              T2_CH4
    #define PIN_PE11    MDR_Pin_11  //  Back
    #define PIN_PE12    MDR_Pin_12  //          LCD_A0
    #define PIN_PE13    MDR_Pin_13  //          LCD_E1
    #define PIN_PE14    MDR_Pin_14  //          LCD_E2
    #define PIN_PE15    MDR_Pin_15  //  Down    
    
    #define PIN_PF13    MDR_Pin_13  //                            SSP3_FSS
    #define PIN_PF14    MDR_Pin_14  //                            SSP3_CLK
    #define PIN_PF15    MDR_Pin_15  //                            SSP3_RX/TX
    


//  --------------  ADC Definition  ------------
    #define MDRB_ADC_CH_IN1            ADC_Signal_Ch2
    #define MDRB_ADC_CH_IN2            ADC_Signal_Ch3
    #define MDRB_ADC_CH_IN3            ADC_Signal_Ch4
    #define MDRB_ADC_CH_IN4            ADC_Signal_Ch5

    #define MDRB_ADC_CH_TUNE           MDRB_ADC_CH_IN1

    #define MDRB_ADC_PIN_ALL          0x7F80UL
    #define MDRB_ADC_PIN_ALL_LED      0x7F80UL 
    

//  --------------  Buttons Definition  ------------
    #define MDRB_BTN_PORT_KEY1     MDR_GPIO_E
    #define MDRB_BTN_PIN_KEY1      PIN_PE8    //  UP
	
    #define MDRB_BTN_PORT_KEY2     MDR_GPIO_E
    #define MDRB_BTN_PIN_KEY2      PIN_PE5    //  Right
	
    #define MDRB_BTN_PORT_KEY3     MDR_GPIO_E
    #define MDRB_BTN_PIN_KEY3      PIN_PE15   //  Down
	
    #define MDRB_BTN_PORT_KEY4     MDR_GPIO_E
    #define MDRB_BTN_PIN_KEY4      PIN_PE10   //  Left

    #define MDRB_BTN_PORT_KEY5     MDR_GPIO_E
    #define MDRB_BTN_PIN_KEY5      PIN_PE9    //  Select
	
    #define MDRB_BTN_PORT_KEY6     MDR_GPIO_E
    #define MDRB_BTN_PIN_KEY6      PIN_PE11	  //  Back

    // for Initialization
    #define MDRB_BTN_GPIO          MDR_GPIO_E
    #define MDRB_BTN_PinSel       (MDRB_BTN_PIN_KEY1 | MDRB_BTN_PIN_KEY2 | MDRB_BTN_PIN_KEY3 | MDRB_BTN_PIN_KEY4 | MDRB_BTN_PIN_KEY5 | MDRB_BTN_PIN_KEY6)
    
    // Active buttons Level
    #define MDRB_BTNs_PUSH_TO_GND


//  ----------    LEDs Definition ------------- 
    #define MDRB_LED_1              PIN_PD7    // VD6
    #define MDRB_LED_2              PIN_PD8    // VD7
    #define MDRB_LED_3              PIN_PD9    // VD8
    #define MDRB_LED_4              PIN_PD10   // VD9
    #define MDRB_LED_5              PIN_PD11   // VD10
    #define MDRB_LED_6              PIN_PD12   // VD11
    #define MDRB_LED_7              PIN_PD13   // VD12
    #define MDRB_LED_8              PIN_PD14   // VD13
  
    #define MDRB_LED_GPIO           MDR_GPIO_D
    #define MDRB_LED_PinAll        (MDRB_LED_1 | MDRB_LED_2 | MDRB_LED_3 | MDRB_LED_4  \
                                  | MDRB_LED_5 | MDRB_LED_6 | MDRB_LED_7 | MDRB_LED_8)


//  ----------    LCD Definition -------------
    // Initialization                 //  D0 .. D7
    #define MDRB_LCD_IN_PORT          MDR_GPIO_A
    #define MDRB_LCD_IN_PINS         (PIN_PA0 | PIN_PA1 | PIN_PA2 | PIN_PA3 | PIN_PA4 | PIN_PA5| PIN_PA6 | PIN_PA7) 

                                      // A0, E1, E2
    #define MDRB_LCD_OUT_PORT         MDR_GPIO_E
    #define MDRB_LCD_OUT_PINS        (PIN_PE12 | PIN_PE13 | PIN_PE14) 
                                      // RW, E
    #define MDRB_LCD_OUT_PORT_EX1     MDR_GPIO_C
    #define MDRB_LCD_OUT_PINS_EX1    (PIN_PC0 | PIN_PC2)
    
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

    //  Reset pin - jumper XP10

    //  Bus Commands
    #define MDRB_LCD_BusSetOUT()        MDR_PORTA->OE |= 0x00FF;
    
    #define MDRB_LCD_BusSetIN()         MDR_PORTA->OE &= 0xFF00;
                                
    #define MDRB_LCD_BusWrite(value)    MDR_PORTA->RXTX &= 0xFF00;          \
                                        MDR_PORTA->RXTX |= (value & 0xFF);
                                    
    #define MDRB_LCD_BusRead()          (uint8_t)(MDR_PORTA->RXTX & 0xFF);
                                          

//  ----------    DMA Definition -------------
    #define MDRB_DMA_CLOCK_SELECT  (RST_CLK_PCLK_SSP1 | RST_CLK_PCLK_SSP2 | RST_CLK_PCLK_SSP3 |RST_CLK_PCLK_DMA)


//  ----------    ExtBUS Definition -------------
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
  
    //  Ctrl: PC0 - nWR, PC1 - nRD, //PC2 - ALE
    #define MDRB_EBC_PORT_CTRL             MDR_PORTC
    #define MDRB_EBC_PORT_CTRL_CLK         RST_CLK_PCLK_PORTC
    #define MDRB_EBC_PORT_CTRL_PINS        (PORT_Pin_0 | PORT_Pin_1) //| PORT_Pin_2
    #define MDRB_EBC_PORT_CTRL_FUNC        PORT_FUNC_MAIN

    //  Ctrl1: [PC9 .. PC12] = [BE0 .. BE3]
    #define MDRB_EBC_PORT_CTRL_1_USED
    #define MDRB_EBC_PORT_CTRL_1            MDR_PORTC
    #define MDRB_EBC_PORT_CTRL_1_CLK        RST_CLK_PCLK_PORTC
    #define MDRB_EBC_PORT_CTRL_1_PINS       (PORT_Pin_9 | PORT_Pin_10 | PORT_Pin_11 | PORT_Pin_12)
    #define MDRB_EBC_PORT_CTRL_1_FUNC       PORT_FUNC_ALTER

    //  Addr: [PF3 .. PF15] = [A0 - A12]    
    #define MDRB_EBC_PORT_ADDR20           MDR_PORTF
    #define MDRB_EBC_PORT_ADDR20_CLK       RST_CLK_PCLK_PORTF
    #define MDRB_EBC_PORT_ADDR20_PINS      (PORT_Pin_3  | PORT_Pin_4  | PORT_Pin_5  | PORT_Pin_6  | PORT_Pin_7  | PORT_Pin_8 | PORT_Pin_9 | \
                                           PORT_Pin_10 | PORT_Pin_11 | PORT_Pin_12 | PORT_Pin_13 | PORT_Pin_14 | PORT_Pin_15)
    #define MDRB_EBC_PORT_ADDR20_FUNC      PORT_FUNC_ALTER

    //  Addr: [PD15] = [A13]
    #define MDRB_EBC_PORT_ADDR20_1_USED
    #define MDRB_EBC_PORT_ADDR20_1         MDR_PORTD
    #define MDRB_EBC_PORT_ADDR20_1_CLK     RST_CLK_PCLK_PORTD
    #define MDRB_EBC_PORT_ADDR20_1_PINS    PORT_Pin_15
    #define MDRB_EBC_PORT_ADDR20_1_FUNC    PORT_FUNC_ALTER
  
    //  Addr: [PE0 .. PE5] = [A14 - A19]
    #define MDRB_EBC_PORT_ADDR20_2_USED
    #define MDRB_EBC_PORT_ADDR20_2         MDR_PORTE
    #define MDRB_EBC_PORT_ADDR20_2_CLK     RST_CLK_PCLK_PORTE
    #define MDRB_EBC_PORT_ADDR20_2_PINS    (PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2 | PORT_Pin_3  | PORT_Pin_4  | PORT_Pin_5 )
    #define MDRB_EBC_PORT_ADDR20_2_FUNC    PORT_FUNC_ALTER    
    
    //  CtrlReady: [PF0] = [Ready]
    #define MDRB_EBC_PORT_READY            MDR_PORTF
    #define MDRB_EBC_PORT_READY_CLK        RST_CLK_PCLK_PORTF
    #define MDRB_EBC_PORT_READY_PINS       PORT_Pin_0
    #define MDRB_EBC_PORT_READY_FUNC       PORT_FUNC_ALTER    

    
    //  EBC SUMMARY
    #define MDRB_EBC_A20_D32_CLK  (MDRB_EBC_PORT_ADDR20_CLK | MDRB_EBC_PORT_ADDR20_1_CLK | MDRB_EBC_PORT_ADDR20_2_CLK | \
                                  MDRB_EBC_DATA_PORT_LO16_CLK | MDRB_EBC_DATA_PORT_HI16_CLK | \
                                  MDRB_EBC_PORT_CTRL_CLK | MDRB_EBC_PORT_CTRL_1_CLK)
                                  
    #define MDRB_EBC_START_ADDR	    0x50000000
    #define MDRB_EBC_REGION          EBC_MEM_REGION_50000000


//  ----------    DAC Definition -------------
    #define MDRB_DAC1_CLOCK    RST_CLK_PCLK_PORTE
    #define MDRB_DAC1_PORT     MDR_PORTE
    #define MDRB_DAC1_PIN      PORT_Pin_1
    
    #define MDRB_DAC2_CLOCK    RST_CLK_PCLK_PORTE
    #define MDRB_DAC2_PORT     MDR_PORTE
    #define MDRB_DAC2_PIN      PORT_Pin_2


//  ---------------  SPI1 Pin Definition ----------------
  //  PORT_C: SSP1_PC5,PC6,PC7,PC8 - Alter
  #define MDRB_SPI1_FSS_PC8_Ind	       8
	#define MDRB_SPI1_CLK_PC7_Ind	       7
	#define MDRB_SPI1_RX_PC6_Ind 	       6
	#define MDRB_SPI1_TX_PC5_Ind		     5

  #define MDRB_SPI1_FSS_PC8_Msk	       PORT_Pin_8
	#define MDRB_SPI1_CLK_PC7_Msk		     PORT_Pin_7
	#define MDRB_SPI1_RX_PC6_Msk 		     PORT_Pin_6
	#define MDRB_SPI1_TX_PC5_Msk		     PORT_Pin_5

  #define MDRB_SPI1_FSS_PC8_Port	     MDR_GPIO_C
	#define MDRB_SPI1_CLK_PC7_Port		   MDR_GPIO_C
	#define MDRB_SPI1_RX_PC6_Port 		   MDR_GPIO_C
	#define MDRB_SPI1_TX_PC5_Port		     MDR_GPIO_C
  
  #define MDRB_SPI1_FSS_PC8_Func	     MDR_PIN_ALT
	#define MDRB_SPI1_CLK_PC7_Func		   MDR_PIN_ALT
	#define MDRB_SPI1_RX_PC6_Func 		   MDR_PIN_ALT
	#define MDRB_SPI1_TX_PC5_Func		     MDR_PIN_ALT
  
  //  PORT_C: SSP1_PC5,PC6 - Over
	#define MDRB_SPI1_RX_PC5_Ind 	       5
	#define MDRB_SPI1_TX_PC6_Ind		     6

	#define MDRB_SPI1_RX_PC5_Msk 		     PORT_Pin_5
	#define MDRB_SPI1_TX_PC6_Msk		     PORT_Pin_6

	#define MDRB_SPI1_RX_PC5_Port 		   MDR_GPIO_C
	#define MDRB_SPI1_TX_PC6_Port		     MDR_GPIO_C
  
	#define MDRB_SPI1_RX_PC5_Func 		   MDR_PIN_OVER
	#define MDRB_SPI1_TX_PC6_Func		     MDR_PIN_OVER  

  //  PORT_D: SSP1_PD2,PD3,PD4,PD5 - Alter
  #define MDRB_SPI1_FSS_PD5_Ind	       5
	#define MDRB_SPI1_CLK_PD4_Ind	       4
	#define MDRB_SPI1_RX_PD3_Ind 	       3
	#define MDRB_SPI1_TX_PD2_Ind		     2

  #define MDRB_SPI1_FSS_PD5_Msk	       PORT_Pin_5
	#define MDRB_SPI1_CLK_PD4_Msk		     PORT_Pin_4
	#define MDRB_SPI1_RX_PD3_Msk 		     PORT_Pin_3
	#define MDRB_SPI1_TX_PD2_Msk		     PORT_Pin_2

  #define MDRB_SPI1_FSS_PD5_Port	     MDR_GPIO_D
	#define MDRB_SPI1_CLK_PD4_Port		   MDR_GPIO_D
	#define MDRB_SPI1_RX_PD3_Port 		   MDR_GPIO_D
	#define MDRB_SPI1_TX_PD2_Port		     MDR_GPIO_D
  
  #define MDRB_SPI1_FSS_PD5_Func	     MDR_PIN_ALT
	#define MDRB_SPI1_CLK_PD4_Func		   MDR_PIN_ALT
	#define MDRB_SPI1_RX_PD3_Func 		   MDR_PIN_ALT
	#define MDRB_SPI1_TX_PD2_Func		     MDR_PIN_ALT


//  ---------------  SPI2 Pin Definition ----------------
  //  PORT_C: SSP1_PC9,PC10,PC11,PC12 - Main
  #define MDRB_SPI2_FSS_PC12_Ind	     12
	#define MDRB_SPI2_CLK_PC11_Ind	     11
	#define MDRB_SPI2_RX_PC10_Ind 	     10
	#define MDRB_SPI2_TX_PC9_Ind		     9

  #define MDRB_SPI2_FSS_PC12_Msk	     PORT_Pin_12
	#define MDRB_SPI2_CLK_PC11_Msk		   PORT_Pin_11
	#define MDRB_SPI2_RX_PC10_Msk 		   PORT_Pin_10
	#define MDRB_SPI2_TX_PC9_Msk		     PORT_Pin_9

  #define MDRB_SPI2_FSS_PC12_Port	     MDR_GPIO_C
	#define MDRB_SPI2_CLK_PC11_Port		   MDR_GPIO_C
	#define MDRB_SPI2_RX_PC10_Port 		   MDR_GPIO_C
	#define MDRB_SPI2_TX_PC9_Port		     MDR_GPIO_C
  
  #define MDRB_SPI2_FSS_PC12_Func	     MDR_PIN_MAIN
	#define MDRB_SPI2_CLK_PC11_Func		   MDR_PIN_MAIN
	#define MDRB_SPI2_RX_PC10_Func 		   MDR_PIN_MAIN
	#define MDRB_SPI2_TX_PC9_Func		     MDR_PIN_MAIN
  
  //  PORT_D: SSP1_PD10,PD9,PD8,PD7 - Main
  #define MDRB_SPI2_FSS_PD10_Ind	     10
	#define MDRB_SPI2_CLK_PD9_Ind	       9
	#define MDRB_SPI2_RX_PD8_Ind 	       8
	#define MDRB_SPI2_TX_PD7_Ind		     7

  #define MDRB_SPI2_FSS_PD10_Msk	     PORT_Pin_10
	#define MDRB_SPI2_CLK_PD9_Msk		     PORT_Pin_9
	#define MDRB_SPI2_RX_PD8_Msk 		     PORT_Pin_8
	#define MDRB_SPI2_TX_PD7_Msk		     PORT_Pin_7

  #define MDRB_SPI2_FSS_PD10_Port	     MDR_GPIO_D
	#define MDRB_SPI2_CLK_PD9_Port		   MDR_GPIO_D
	#define MDRB_SPI2_RX_PD8_Port 		   MDR_GPIO_D
	#define MDRB_SPI2_TX_PD7_Port		     MDR_GPIO_D
  
  #define MDRB_SPI2_FSS_PD10_Func	     MDR_PIN_MAIN
	#define MDRB_SPI2_CLK_PD9_Func		   MDR_PIN_MAIN
	#define MDRB_SPI2_RX_PD8_Func 		   MDR_PIN_MAIN
	#define MDRB_SPI2_TX_PD7_Func		     MDR_PIN_MAIN  

//  ---------------  SPI3 Pin Definition ----------------
//  PORT_D: SSP3_PD12,PD12 - OVER
	#define MDRB_SPI3_RX_PD12_Ind	       12
	#define MDRB_SPI3_TX_PD12_Ind		     12

	#define MDRB_SPI3_RX_PD12_Msk 		   PORT_Pin_12
	#define MDRB_SPI3_TX_PD12_Msk		     PORT_Pin_12

	#define MDRB_SPI3_RX_PD12_Port 		   MDR_GPIO_D
	#define MDRB_SPI3_TX_PD12_Port		   MDR_GPIO_D
  
	#define MDRB_SPI3_RX_PD12_Func 		   MDR_PIN_OVER
	#define MDRB_SPI3_TX_PD12_Func		   MDR_PIN_OVER

  //  PORT_F: SSP3_PF13,PF14,PF15 - OVER
  #define MDRB_SPI3_FSS_PF13_Ind	     13
	#define MDRB_SPI3_CLK_PF14_Ind	     14
	#define MDRB_SPI3_RX_PF15_Ind 	     15
	#define MDRB_SPI3_TX_PF15_Ind		     15

  #define MDRB_SPI3_FSS_PF10_Msk	     PORT_Pin_13
	#define MDRB_SPI3_CLK_PF9_Msk		     PORT_Pin_14
	#define MDRB_SPI3_RX_PF8_Msk 		     PORT_Pin_15
	#define MDRB_SPI3_TX_PF7_Msk		     PORT_Pin_15

  #define MDRB_SPI3_FSS_PF10_Port	     MDR_GPIO_F
	#define MDRB_SPI3_CLK_PF9_Port		   MDR_GPIO_F
	#define MDRB_SPI3_RX_PF8_Port 		   MDR_GPIO_F
	#define MDRB_SPI3_TX_PF7_Port		     MDR_GPIO_F
  
  #define MDRB_SPI3_FSS_PF10_Func	     MDR_PIN_OVER
	#define MDRB_SPI3_CLK_PF9_Func		   MDR_PIN_OVER
	#define MDRB_SPI3_RX_PF8_Func 		   MDR_PIN_MAIN
	#define MDRB_SPI3_TX_PF7_Func		     MDR_PIN_OVER


//  ---------------  UART1 Pin Definition ----------------
  //  PORT_C: PC3, PC4 - Main
  #define MDRB_UART1_TX_PC3_Ind	     3
  #define MDRB_UART1_RX_PC4_Ind	     4

  #define MDRB_UART1_TX_PC3_Msk	     MDR_Pin_3
	#define MDRB_UART1_RX_PC4_Msk		   MDR_Pin_4

  #define MDRB_UART1_TX_PC3_Port	   MDR_GPIO_C
	#define MDRB_UART1_RX_PC4_Port		 MDR_GPIO_C
  
  #define MDRB_UART1_TX_PC3_Func	   MDR_PIN_MAIN
	#define MDRB_UART1_RX_PC4_Func	   MDR_PIN_MAIN

//  ---------------  UART2 Pin Definition ----------------
  //  PORT_D: PD13, PD14 - Main
  #define MDRB_UART2_TX_PD13_Ind	   13
  #define MDRB_UART2_RX_PD14_Ind	   14

  #define MDRB_UART2_TX_PD13_Msk	   MDR_Pin_13
	#define MDRB_UART2_RX_PD14_Msk		 MDR_Pin_14

  #define MDRB_UART2_TX_PD13_Port	   MDR_GPIO_D
	#define MDRB_UART2_RX_PD14_Port		 MDR_GPIO_D
  
  #define MDRB_UART2_TX_PD13_Func	   MDR_PIN_MAIN
	#define MDRB_UART2_RX_PD14_Func	   MDR_PIN_MAIN



#else
   Please, select board in MDRB_BoardSelect.h!

#endif //  USE_MDR1986VE1

#endif // _MDRB_1986VE1_H

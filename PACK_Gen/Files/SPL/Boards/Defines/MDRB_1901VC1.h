#ifndef _MDRB_1901VC1_H
#define _MDRB_1901VC1_H

#ifdef USE_MDR1901VC1

//===================================    Частота тактирования    ========================================
#define HSE_PLL_MUL_MAX         MDR_x12                 //  HSE_max = 8MHz * 12 = 96MHz  (100MHz по спецификации)
#define HSE_LOW_SELRI_MAX       MDR_LOWRI_gt80MHz
#define HSE_EEPROM_DELAY_MAX    EEPROM_Delay_le100MHz

#define MDRB_CLK_PLL_HSE_RES_MAX     MDR_CPU_CFG_PLL_HSE_RES_DEF(HSE_PLL_MUL_MAX, HSE_EEPROM_DELAY_MAX, HSE_LOW_SELRI_MAX)

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
    #define PIN_PA8     MDR_Pin_8   //                              SSP2_CLK
    #define PIN_PA9     MDR_Pin_9   //                              SSP2_FSS
    #define PIN_PA10    MDR_Pin_10  //                              SSP2_TX
    #define PIN_PA11    MDR_Pin_11  //                              SSP2_RS
    #define PIN_PA12    MDR_Pin_12  //                            SSP1_RX           T1_ETR
    #define PIN_PA13    MDR_Pin_13  //                            SSP1_TX           T1_BRK
    #define PIN_PA14    MDR_Pin_14  //                            SSP1_CLK
    #define PIN_PA15    MDR_Pin_15  //                            SSP1_FSS

    #define PIN_PB0     MDR_Pin_0   //                    JTAG_A                    T2_nCH1
    #define PIN_PB1     MDR_Pin_1   //                    JTAG_A                    T2_CH2
    #define PIN_PB2     MDR_Pin_2   //                    JTAG_A                    T2_nCH2
    #define PIN_PB3     MDR_Pin_3   //                    JTAG_A                    T2_CH3
    #define PIN_PB4     MDR_Pin_4   //                    JTAG_A                    T1_CH1/T2_nCH3
    #define PIN_PB5     MDR_Pin_5   //                                SSP3_TX
    #define PIN_PB6     MDR_Pin_6   //                                SSP3_FSS
    #define PIN_PB7     MDR_Pin_7   //                                SSP3_RX
    #define PIN_PB8     MDR_Pin_8   //                                SSP3_CLK      
    #define PIN_PB9     MDR_Pin_9   //                                              T1_nCH1/T2_ETR
    #define PIN_PB10    MDR_Pin_10  //                                              T1_CH2
    #define PIN_PB11    MDR_Pin_11  //  LED_5                                       T1_nCH2
    #define PIN_PB12    MDR_Pin_12  //  LED_4                       SSP2_CLK
    #define PIN_PB13    MDR_Pin_13  //  LED_3                       SSP2_FSS
    #define PIN_PB14    MDR_Pin_14  //  LED_2                       SSP2_TX
    #define PIN_PB15    MDR_Pin_15  //  LED_1                       SSP2_RX

    #define PIN_PC0     MDR_Pin_0   //  Select                          SSP4_FSS
    #define PIN_PC2     MDR_Pin_2   //          LCD_RW    
    #define PIN_PC3     MDR_Pin_3   //  Up                              SSP4_RX
    #define PIN_PC4     MDR_Pin_4   //  Down                            SSP4_TX
    #define PIN_PC5     MDR_Pin_5   //  Left                            SSP4_CLK
    #define PIN_PC6     MDR_Pin_6   //  Right
    #define PIN_PC7     MDR_Pin_7   //          LCD_E
    #define PIN_PC8     MDR_Pin_8   //                                SSP3_TX
    #define PIN_PC9     MDR_Pin_9   //                                SSP3_FSS
    #define PIN_PC10    MDR_Pin_10  //                                SSP3_RX
    #define PIN_PC11    MDR_Pin_11  //                                SSP3_CLK
    #define PIN_PC12    MDR_Pin_12  //                                  SSP4_FSS
    #define PIN_PC13    MDR_Pin_13  //                                  SSP4_CLK
    #define PIN_PC14    MDR_Pin_14  //                                  SSP4_TX                   I2C_SCK
    #define PIN_PC15    MDR_Pin_15  //                                  SSP4_RX                   I2C_SDA

    #define PIN_PD0     MDR_Pin_0   //                    JTAG_B                  ADC_Ch0/ref+    I2C_SCK
    #define PIN_PD1     MDR_Pin_1   //                    JTAG_B                  ADC_Ch1/ref-    I2C_SDA
    #define PIN_PD2     MDR_Pin_2   //                    JTAG_B  SSP1_TX         ADC_Ch2
    #define PIN_PD3     MDR_Pin_3   //                    JTAG_B  SSP1_FSS        ADC_Ch3
    #define PIN_PD4     MDR_Pin_4   //                    JTAG_B  SSP1_RX         ADC_Ch4
    #define PIN_PD5     MDR_Pin_5   //                            SSP1_CLK        ADC_Ch5
    #define PIN_PD6     MDR_Pin_6   //                                            ADC_Ch6
    #define PIN_PD7     MDR_Pin_7   //                                            ADC_Ch7
    #define PIN_PD8     MDR_Pin_8   //          ExtMem_CE                         ADC_Ch8
    #define PIN_PD9     MDR_Pin_9   //          LCD_RES                           ADC_Ch9    
    #define PIN_PD10    MDR_Pin_10  //                                            ADC_Ch10
    #define PIN_PD11    MDR_Pin_11  //                                            ADC_Ch11
    #define PIN_PD12    MDR_Pin_12  //                              SSP2_FSS      ADC_Ch12
    #define PIN_PD13    MDR_Pin_13  //                              SSP2_RX       ADC_Ch13
    #define PIN_PD14    MDR_Pin_14  //                              SSP2_CLK      ADC_Ch14
    #define PIN_PD15    MDR_Pin_15  //                              SSP2_TX       ADC_Ch15

    #define PIN_PE0     MDR_Pin_0   //                                  SSP4_FSS
    #define PIN_PE1     MDR_Pin_1   //                                  SSP4_CLK
    #define PIN_PE2     MDR_Pin_2   //                                  SSP4_TX
    #define PIN_PE3     MDR_Pin_3   //                                  SSP4_RX
    #define PIN_PE4     MDR_Pin_4   //          LCD_E1              SSP2_TX
    #define PIN_PE5     MDR_Pin_5   //          LCD_E2              SSP2_FSS
    #define PIN_PE6     MDR_Pin_6   //                              SSP2_RX
    #define PIN_PE7     MDR_Pin_7   //                              SSP2_CLK
    #define PIN_PE11    MDR_Pin_11  //          LCD_A0
    #define PIN_PE12    MDR_Pin_12  //                            SSP1_RX
    #define PIN_PE13    MDR_Pin_13  //                            SSP1_TX
    #define PIN_PE14    MDR_Pin_14  //                            SSP1_CLK
    #define PIN_PE15    MDR_Pin_15  //                            SSP1_FSS

    #define PIN_PF0     MDR_Pin_0   //                                                      UART3_RX
    #define PIN_PF1     MDR_Pin_1   //                                                      UART3_TX
    #define PIN_PF2     MDR_Pin_2   //                                  SSP4_RX
    #define PIN_PF3     MDR_Pin_3   //                                  SSP4_TX
    #define PIN_PF4     MDR_Pin_4   //                                  SSP4_CLK
    #define PIN_PF5     MDR_Pin_5   //                                  SSP4_FSS
    #define PIN_PB6     MDR_Pin_6   //
    #define PIN_PB7     MDR_Pin_7   //                                              T3_CH3
    #define PIN_PB8     MDR_Pin_8   //                                              T3_nCH3
    #define PIN_PB9     MDR_Pin_9   //
    #define PIN_PF12    MDR_Pin_12  //                                SSP3_TX
    #define PIN_PF13    MDR_Pin_13  //                                SSP3_FSS
    #define PIN_PF14    MDR_Pin_14  //                                SSP3_RX
    #define PIN_PF15    MDR_Pin_15  //                                SSP3_CLK


//  --------------  ADC Definition  ------------
    #define MDRB_ADC_CH_IN1            ADC_Signal_Ch6
    #define MDRB_ADC_CH_IN2            ADC_Signal_Ch7

    #define MDRB_ADC_PIN_ALL          0xFFFFUL
    #define MDRB_ADC_PIN_ALL_JTAG_B   0xFFE0UL
    #define MDRB_ADC_PIN_ALL_LCD      0xFCFFUL    

//  На плате нет подстроечного резистора, для определенности будем считать таковым 6-й канал
    #define MDRB_ADC_CH_TUNE            MDRB_ADC_CH_IN1
    #define MDRB_ADC_TUNE_PORT          MDR_GPIO_D
    #define MDRB_ADC_TUNE_PIN           PIN_PD7


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

    #define MDRB_HAS_LCD
    
    //  Bus Commands
    #define MDRB_LCD_BusSetOUT()        MDR_PORTA->OE |= 0x00FF
    
    #define MDRB_LCD_BusSetIN()         MDR_PORTA->OE &= 0xFF00
                                
    #define MDRB_LCD_BusWrite(value)    MDR_PORTA->RXTX &= 0xFF00;          \
                                        MDR_PORTA->RXTX |= (value & 0xFF)
                                    
    #define MDRB_LCD_BusRead()          (uint8_t)(MDR_PORTA->RXTX & 0xFF)


//  ---------------  SPI1 Pin Definition ----------------
  //  PORT_A: SSP1_PA[12,13,14,15] - Alter
  #define MDRB_SPI1_FSS_PA15_Ind	     15
	#define MDRB_SPI1_CLK_PA14_Ind	     14
	#define MDRB_SPI1_RX_PA12_Ind 	     12
	#define MDRB_SPI1_TX_PA13_Ind		     13

  #define MDRB_SPI1_FSS_PA15_Msk	     PORT_Pin_15
	#define MDRB_SPI1_CLK_PA14_Msk		   PORT_Pin_14
	#define MDRB_SPI1_RX_PA12_Msk 		   PORT_Pin_12
	#define MDRB_SPI1_TX_PA13_Msk		     PORT_Pin_13

  #define MDRB_SPI1_FSS_PA15_Port	     MDR_GPIO_A
	#define MDRB_SPI1_CLK_PA14_Port		   MDR_GPIO_A
	#define MDRB_SPI1_RX_PA12_Port 		   MDR_GPIO_A
	#define MDRB_SPI1_TX_PA13_Port		   MDR_GPIO_A
  
  #define MDRB_SPI1_FSS_PA15_Func	     MDR_PIN_ALT
	#define MDRB_SPI1_CLK_PA14_Func		   MDR_PIN_ALT
	#define MDRB_SPI1_RX_PA12_Func 		   MDR_PIN_ALT
	#define MDRB_SPI1_TX_PA13_Func		   MDR_PIN_ALT

  //  PORT_D: SSP1_PD[2,3,4,5] - Alter
  #define MDRB_SPI1_FSS_PD3_Ind	       3
	#define MDRB_SPI1_CLK_PD5_Ind	       5
	#define MDRB_SPI1_RX_PD4_Ind 	       4
	#define MDRB_SPI1_TX_PD2_Ind		     2

  #define MDRB_SPI1_FSS_PD3_Msk	       PORT_Pin_3
	#define MDRB_SPI1_CLK_PD5_Msk		     PORT_Pin_5
	#define MDRB_SPI1_RX_PD4_Msk 		     PORT_Pin_4
	#define MDRB_SPI1_TX_PD2_Msk		     PORT_Pin_2

  #define MDRB_SPI1_FSS_PD3_Port	     MDR_GPIO_D
	#define MDRB_SPI1_CLK_PD5_Port		   MDR_GPIO_D
	#define MDRB_SPI1_RX_PD4_Port 		   MDR_GPIO_D
	#define MDRB_SPI1_TX_PD2_Port		     MDR_GPIO_D
  
  #define MDRB_SPI1_FSS_PD3_Func	     MDR_PIN_ALT
	#define MDRB_SPI1_CLK_PD5_Func		   MDR_PIN_ALT
	#define MDRB_SPI1_RX_PD4_Func 		   MDR_PIN_ALT
	#define MDRB_SPI1_TX_PD2_Func		     MDR_PIN_ALT

  //  PORT_E: SSP1_PE[12,13,14,15] - Alter
  #define MDRB_SPI1_FSS_PE15_Ind	     15
	#define MDRB_SPI1_CLK_PE14_Ind	     14
	#define MDRB_SPI1_RX_PE12_Ind 	     12
	#define MDRB_SPI1_TX_PE13_Ind		     13

  #define MDRB_SPI1_FSS_PE15_Msk	     PORT_Pin_15
	#define MDRB_SPI1_CLK_PE14_Msk		   PORT_Pin_14
	#define MDRB_SPI1_RX_PE12_Msk 		   PORT_Pin_12
	#define MDRB_SPI1_TX_PE13_Msk		     PORT_Pin_13

  #define MDRB_SPI1_FSS_PE15_Port	     MDR_GPIO_E
	#define MDRB_SPI1_CLK_PE14_Port		   MDR_GPIO_E
	#define MDRB_SPI1_RX_PE12_Port 		   MDR_GPIO_E
	#define MDRB_SPI1_TX_PE13_Port		   MDR_GPIO_E
  
  #define MDRB_SPI1_FSS_PE15_Func	     MDR_PIN_ALT
	#define MDRB_SPI1_CLK_PE14_Func		   MDR_PIN_ALT
	#define MDRB_SPI1_RX_PE12_Func 		   MDR_PIN_ALT
	#define MDRB_SPI1_TX_PE13_Func       MDR_PIN_ALT
  

//  ---------------  SPI2 Pin Definition ----------------
  //  PORT_A: SSP2_PA[8,9,10,11] - Alter
  #define MDRB_SPI2_FSS_PA9_Ind	       9
	#define MDRB_SPI2_CLK_PA8_Ind	       8
	#define MDRB_SPI2_RX_PA11_Ind 	     11
	#define MDRB_SPI2_TX_PA10_Ind		     10
  
  #define MDRB_SPI2_FSS_PA9_Msk	       PORT_Pin_9
	#define MDRB_SPI2_CLK_PA8_Msk		     PORT_Pin_8
	#define MDRB_SPI2_RX_PA11_Msk 		   PORT_Pin_11
	#define MDRB_SPI2_TX_PA10_Msk		     PORT_Pin_10

  #define MDRB_SPI2_FSS_PA9_Port	     MDR_GPIO_A
	#define MDRB_SPI2_CLK_PA8_Port		   MDR_GPIO_A
	#define MDRB_SPI2_RX_PA11_Port 		   MDR_GPIO_A
	#define MDRB_SPI2_TX_PA10_Port		   MDR_GPIO_A
  
  #define MDRB_SPI2_FSS_PA9_Func	     MDR_PIN_ALT
	#define MDRB_SPI2_CLK_PA8_Func		   MDR_PIN_ALT
	#define MDRB_SPI2_RX_PA11_Func 		   MDR_PIN_ALT
	#define MDRB_SPI2_TX_PA10_Func		   MDR_PIN_ALT


  //  PORT_B: SSP2_PB[12,13,14,15] - Alter
  #define MDRB_SPI2_FSS_PB13_Ind	     13
	#define MDRB_SPI2_CLK_PB12_Ind	     12
	#define MDRB_SPI2_RX_PB15_Ind 	     15
	#define MDRB_SPI2_TX_PB14_Ind		     14

  #define MDRB_SPI2_FSS_PB13_Msk	     PORT_Pin_13
	#define MDRB_SPI2_CLK_PB12_Msk		   PORT_Pin_12
	#define MDRB_SPI2_RX_PB15_Msk 		   PORT_Pin_15
	#define MDRB_SPI2_TX_PB14_Msk		     PORT_Pin_14

  #define MDRB_SPI2_FSS_PB13_Port	     MDR_GPIO_B
	#define MDRB_SPI2_CLK_PB12_Port		   MDR_GPIO_B
	#define MDRB_SPI2_RX_PB15_Port 		   MDR_GPIO_B
	#define MDRB_SPI2_TX_PB14_Port		   MDR_GPIO_B
  
  #define MDRB_SPI2_FSS_PB13_Func	     MDR_PIN_ALT
	#define MDRB_SPI2_CLK_PB12_Func		   MDR_PIN_ALT
	#define MDRB_SPI2_RX_PB15_Func 		   MDR_PIN_ALT
	#define MDRB_SPI2_TX_PB14_Func		   MDR_PIN_ALT

  //  PORT_D: SSP2_PD[12,13,14,15] - Alter
  #define MDRB_SPI2_FSS_PD12_Ind	     12
	#define MDRB_SPI2_CLK_PD14_Ind	     14
	#define MDRB_SPI2_RX_PD13_Ind 	     13
	#define MDRB_SPI2_TX_PD15_Ind		     15

  #define MDRB_SPI2_FSS_PD12_Msk	     PORT_Pin_12
	#define MDRB_SPI2_CLK_PD14_Msk		   PORT_Pin_14
	#define MDRB_SPI2_RX_PD13_Msk 		   PORT_Pin_13
	#define MDRB_SPI2_TX_PD15_Msk		     PORT_Pin_15

  #define MDRB_SPI2_FSS_PD12_Port	     MDR_GPIO_D
	#define MDRB_SPI2_CLK_PD14_Port		   MDR_GPIO_D
	#define MDRB_SPI2_RX_PD13_Port 		   MDR_GPIO_D
	#define MDRB_SPI2_TX_PD15_Port		   MDR_GPIO_D
  
  #define MDRB_SPI2_FSS_PD12_Func	     MDR_PIN_ALT
	#define MDRB_SPI2_CLK_PD14_Func		   MDR_PIN_ALT
	#define MDRB_SPI2_RX_PD13_Func 		   MDR_PIN_ALT
	#define MDRB_SPI2_TX_PD15_Func		   MDR_PIN_ALT

  //  PORT_E: SSP2_PE[4,5,6,7] - Alter
  #define MDRB_SPI2_FSS_PE5_Ind	       5
	#define MDRB_SPI2_CLK_PE7_Ind	       7
	#define MDRB_SPI2_RX_PE6_Ind 	       6
	#define MDRB_SPI2_TX_PE4_Ind		     4

  #define MDRB_SPI2_FSS_PE5_Msk	       PORT_Pin_5
	#define MDRB_SPI2_CLK_PE7_Msk		     PORT_Pin_7
	#define MDRB_SPI2_RX_PE6_Msk 		     PORT_Pin_6
	#define MDRB_SPI2_TX_PE4_Msk		     PORT_Pin_4

  #define MDRB_SPI2_FSS_PE5_Port	     MDR_GPIO_E
	#define MDRB_SPI2_CLK_PE7_Port		   MDR_GPIO_E
	#define MDRB_SPI2_RX_PE6_Port 		   MDR_GPIO_E
	#define MDRB_SPI2_TX_PE4_Port	  	   MDR_GPIO_E
  
  #define MDRB_SPI2_FSS_PE5_Func	     MDR_PIN_ALT
	#define MDRB_SPI2_CLK_PE7_Func		   MDR_PIN_ALT
	#define MDRB_SPI2_RX_PE6_Func 		   MDR_PIN_ALT
	#define MDRB_SPI2_TX_PE4_Func		     MDR_PIN_ALT


//  ---------------  SPI3 Pin Definition ----------------
  //  PORT_B: SSP3_PB[5,6,7,8] - Alter
  #define MDRB_SPI3_FSS_PB6_Ind	       6
	#define MDRB_SPI3_CLK_PB8_Ind	       8
	#define MDRB_SPI3_RX_PB7_Ind 	       7
	#define MDRB_SPI3_TX_PB5_Ind		     5

  #define MDRB_SPI3_FSS_PB6_Msk	     PORT_Pin_6
	#define MDRB_SPI3_CLK_PB8_Msk		   PORT_Pin_8
	#define MDRB_SPI3_RX_PB7_Msk 		   PORT_Pin_7
	#define MDRB_SPI3_TX_PB5_Msk		   PORT_Pin_5

  #define MDRB_SPI3_FSS_PB6_Port	   MDR_GPIO_B
	#define MDRB_SPI3_CLK_PB8_Port		 MDR_GPIO_B
	#define MDRB_SPI3_RX_PB7_Port 		 MDR_GPIO_B
	#define MDRB_SPI3_TX_PB5_Port		   MDR_GPIO_B
  
  #define MDRB_SPI3_FSS_PB6_Func	   MDR_PIN_ALT
	#define MDRB_SPI3_CLK_PB8_Func		 MDR_PIN_ALT
	#define MDRB_SPI3_RX_PB7_Func 		 MDR_PIN_ALT
	#define MDRB_SPI3_TX_PB5_Func		   MDR_PIN_ALT

  //  PORT_C: SSP3_PC[8,9,10,11] - Alter
  #define MDRB_SPI3_FSS_PC9_Ind	     9
	#define MDRB_SPI3_CLK_PC11_Ind	   11
	#define MDRB_SPI3_RX_PC10_Ind 	   10
	#define MDRB_SPI3_TX_PC8_Ind		   8

  #define MDRB_SPI3_FSS_PC9_Msk	     PORT_Pin_9
	#define MDRB_SPI3_CLK_PC11_Msk		 PORT_Pin_11
	#define MDRB_SPI3_RX_PC10_Msk 		 PORT_Pin_10
	#define MDRB_SPI3_TX_PC8_Msk		   PORT_Pin_8

  #define MDRB_SPI3_FSS_PC9_Port	   MDR_GPIO_C
	#define MDRB_SPI3_CLK_PC11_Port		 MDR_GPIO_C
	#define MDRB_SPI3_RX_PC10_Port 		 MDR_GPIO_C
	#define MDRB_SPI3_TX_PC8_Port		   MDR_GPIO_C
  
  #define MDRB_SPI3_FSS_PC9_Func	   MDR_PIN_ALT
	#define MDRB_SPI3_CLK_PC11_Func		 MDR_PIN_ALT
	#define MDRB_SPI3_RX_PC10_Func 		 MDR_PIN_ALT
	#define MDRB_SPI3_TX_PC8_Func		   MDR_PIN_ALT
  
  //  PORT_F: SSP3_PF[12,13,14,15] - Alter
  #define MDRB_SPI3_FSS_PF13_Ind	   13
	#define MDRB_SPI3_CLK_PF15_Ind	   15
	#define MDRB_SPI3_RX_PF14_Ind 	   14
	#define MDRB_SPI3_TX_PF12_Ind		   12

  #define MDRB_SPI3_FSS_PF13_Msk	   PORT_Pin_13
	#define MDRB_SPI3_CLK_PF15_Msk		 PORT_Pin_15
	#define MDRB_SPI3_RX_PF14_Msk 		 PORT_Pin_14
	#define MDRB_SPI3_TX_PF12_Msk		   PORT_Pin_12

  #define MDRB_SPI3_FSS_PF13_Port	   MDR_GPIO_F
	#define MDRB_SPI3_CLK_PF15_Port		 MDR_GPIO_F
	#define MDRB_SPI3_RX_PF14_Port 		 MDR_GPIO_F
	#define MDRB_SPI3_TX_PF12_Port		 MDR_GPIO_F
  
  #define MDRB_SPI3_FSS_PF13_Func	   MDR_PIN_ALT
	#define MDRB_SPI3_CLK_PF15_Func		 MDR_PIN_ALT
	#define MDRB_SPI3_RX_PF14_Func 		 MDR_PIN_ALT
	#define MDRB_SPI3_TX_PF12_Func		 MDR_PIN_ALT  
  
  

//  ---------------  SPI4 Pin Definition ----------------
  //  PORT_C: SSP4_PC[0,3,4,5] - Alter
  #define MDRB_SPI4_FSS_PC0_Ind	     0
	#define MDRB_SPI4_CLK_PC5_Ind	     5
	#define MDRB_SPI4_RX_PC3_Ind 	     3
	#define MDRB_SPI4_TX_PC4_Ind		   4

  #define MDRB_SPI4_FSS_PC0_Msk	     PORT_Pin_0
	#define MDRB_SPI4_CLK_PC5_Msk		   PORT_Pin_5
	#define MDRB_SPI4_RX_PC3_Msk 		   PORT_Pin_3
	#define MDRB_SPI4_TX_PC4_Msk		   PORT_Pin_4

  #define MDRB_SPI4_FSS_PC0_Port	   MDR_GPIO_C
	#define MDRB_SPI4_CLK_PC5_Port		 MDR_GPIO_C
	#define MDRB_SPI4_RX_PC3_Port 		 MDR_GPIO_C
	#define MDRB_SPI4_TX_PC4_Port		   MDR_GPIO_C
  
  #define MDRB_SPI4_FSS_PC0_Func	   MDR_PIN_ALT
	#define MDRB_SPI4_CLK_PC5_Func		 MDR_PIN_ALT
	#define MDRB_SPI4_RX_PC3_Func 		 MDR_PIN_ALT
	#define MDRB_SPI4_TX_PC4_Func		   MDR_PIN_ALT

  //  PORT_C: SSP4_PC[12,13,14,15] - Alter
  #define MDRB_SPI4_FSS_PC12_Ind	   12
	#define MDRB_SPI4_CLK_PC13_Ind	   13
	#define MDRB_SPI4_RX_PC15_Ind      15
	#define MDRB_SPI4_TX_PC14_Ind		   14

  #define MDRB_SPI4_FSS_PC12_Msk	   PORT_Pin_12
	#define MDRB_SPI4_CLK_PC13_Msk		 PORT_Pin_13
	#define MDRB_SPI4_RX_PC15_Msk 		 PORT_Pin_15
	#define MDRB_SPI4_TX_PC14_Msk		   PORT_Pin_14

  #define MDRB_SPI4_FSS_PC12_Port	   MDR_GPIO_C
	#define MDRB_SPI4_CLK_PC13_Port		 MDR_GPIO_C
	#define MDRB_SPI4_RX_PC15_Port 		 MDR_GPIO_C
	#define MDRB_SPI4_TX_PC14_Port		 MDR_GPIO_C
  
  #define MDRB_SPI4_FSS_PC12_Func	   MDR_PIN_ALT
	#define MDRB_SPI4_CLK_PC13_Func		 MDR_PIN_ALT
	#define MDRB_SPI4_RX_PC15_Func 		 MDR_PIN_ALT
	#define MDRB_SPI4_TX_PC14_Func		 MDR_PIN_ALT

  //  PORT_E: SSP4_PE[0,1,2,3] - Alter
  #define MDRB_SPI4_FSS_PE0_Ind	     0
	#define MDRB_SPI4_CLK_PE1_Ind	     1
	#define MDRB_SPI4_RX_PE3_Ind 	     3
	#define MDRB_SPI4_TX_PE2_Ind		   2

  #define MDRB_SPI4_FSS_PE0_Msk	     PORT_Pin_0
	#define MDRB_SPI4_CLK_PE1_Msk		   PORT_Pin_1
	#define MDRB_SPI4_RX_PE3_Msk 		   PORT_Pin_3
	#define MDRB_SPI4_TX_PE2_Msk		   PORT_Pin_2

  #define MDRB_SPI4_FSS_PE0_Port	   MDR_GPIO_E
	#define MDRB_SPI4_CLK_PE1_Port		 MDR_GPIO_E
	#define MDRB_SPI4_RX_PE3_Port 		 MDR_GPIO_E
	#define MDRB_SPI4_TX_PE2_Port		   MDR_GPIO_E
  
  #define MDRB_SPI4_FSS_PE0_Func	   MDR_PIN_ALT
	#define MDRB_SPI4_CLK_PE1_Func		 MDR_PIN_ALT
	#define MDRB_SPI4_RX_PE3_Func 		 MDR_PIN_ALT
	#define MDRB_SPI4_TX_PE2_Func		   MDR_PIN_ALT

  //  PORT_F: SSP4_PF[2,3,4,5] - Alter
  #define MDRB_SPI4_FSS_PF5_Ind	     5
	#define MDRB_SPI4_CLK_PF4_Ind	     4
	#define MDRB_SPI4_RX_PF2_Ind 	     2
	#define MDRB_SPI4_TX_PF3_Ind		   3

  #define MDRB_SPI4_FSS_PF5_Msk	     PORT_Pin_5
	#define MDRB_SPI4_CLK_PF4_Msk		   PORT_Pin_4
	#define MDRB_SPI4_RX_PF2_Msk 		   PORT_Pin_2
	#define MDRB_SPI4_TX_PF3_Msk		   PORT_Pin_3

  #define MDRB_SPI4_FSS_PF5_Port	   MDR_GPIO_F
	#define MDRB_SPI4_CLK_PF4_Port		 MDR_GPIO_F
	#define MDRB_SPI4_RX_PF2_Port 		 MDR_GPIO_F
	#define MDRB_SPI4_TX_PF3_Port		   MDR_GPIO_F
  
  #define MDRB_SPI4_FSS_PF5_Func	   MDR_PIN_ALT
	#define MDRB_SPI4_CLK_PF4_Func		 MDR_PIN_ALT
	#define MDRB_SPI4_RX_PF2_Func 		 MDR_PIN_ALT
	#define MDRB_SPI4_TX_PF3_Func		   MDR_PIN_ALT


//  ---------------  UART2 Pin Definition ----------------
  //  PORT_F: PF0, PF1 - Main
  #define MDRB_UART3_TX_PF1_Ind	      1
  #define MDRB_UART3_RX_PF0_Ind	      0

  #define MDRB_UART3_TX_PF1_Msk	      MDR_Pin_1
	#define MDRB_UART3_RX_PF0_Msk		    MDR_Pin_0

  #define MDRB_UART3_TX_PF1_Port	    MDR_GPIO_F
	#define MDRB_UART3_RX_PF0_Port		  MDR_GPIO_F
  
  #define MDRB_UART3_TX_PF1_Func	    MDR_PIN_ALT
	#define MDRB_UART3_RX_PF0_Func	    MDR_PIN_ALT

//  ---------------  I2C Pin Definition ---------------- 
  #define MDRB_I2C_SCL_PC14_Ind	      14
  #define MDRB_I2C_SDA_PC15_Ind	      15

  #define MDRB_I2C_SCL_PC14_Msk	      PIN_PC14
	#define MDRB_I2C_SDA_PC15_Msk		    PIN_PC15

  #define MDRB_I2C_SCL_PC14_Port	    MDR_GPIO_C
	#define MDRB_I2C_SDA_PC15_Port		  MDR_GPIO_C
  
  #define MDRB_I2C_SCL_PC14_Func	    MDR_PIN_MAIN
	#define MDRB_I2C_SDA_PC15_Func	    MDR_PIN_MAIN


  #define MDRB_I2C_SCL_PD0_Ind	      0
  #define MDRB_I2C_SDA_PD1_Ind	      1

  #define MDRB_I2C_SCL_PD0_Msk	      PIN_PC0
	#define MDRB_I2C_SDA_PD1_Msk		    PIN_PC1

  #define MDRB_I2C_SCL_PD0_Port	      MDR_GPIO_D
	#define MDRB_I2C_SDA_PD1_Port		    MDR_GPIO_D
  
  #define MDRB_I2C_SCL_PD0_Func	      MDR_PIN_ALT
	#define MDRB_I2C_SDA_PD1_Func	      MDR_PIN_ALT


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


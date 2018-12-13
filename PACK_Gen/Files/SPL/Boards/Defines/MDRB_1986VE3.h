#ifndef _MDRB_1986VE3_H
#define _MDRB_1986VE3_H

#ifdef USE_MDR1986VE3

//===================================    Частота тактирования    ========================================
#define HSE_PLL_MUL_MAX         MDR_x10   //  HSE_max = 8MHz * 10 = 80MHz
#define HSE_LOW_SELRI_MAX       MDR_LOWRI_gt80MHz
#define HSE_EEPROM_DELAY_MAX    EEPROM_Delay_le100MHz

#define MDR_CPU_SetClock_HSE_Max(bypass)  MDR_CPU_SetClock_HSE_PLL((bypass), HSE_PLL_MUL_MAX, HSE_LOW_SELRI_MAX, HSE_EEPROM_DELAY_MAX, MDR_CLK_div1, HSE_TIMEOUT)

//===================================    Заметки по плате    ========================================

//  Переопределение пинов для удобства поиска конфликтов
    #define PIN_PA0     MDR_Pin_0   //          LCD_D0
    #define PIN_PA1     MDR_Pin_1   //          LCD_D1
    #define PIN_PA2     MDR_Pin_2   //          LCD_D2
    #define PIN_PA3     MDR_Pin_3   //          LCD_D3
    #define PIN_PA4     MDR_Pin_4   //          LCD_D4
    #define PIN_PA5     MDR_Pin_5   //          LCD_D5
    #define PIN_PA6     MDR_Pin_6   //          LCD_D6
    #define PIN_PA7     MDR_Pin_7   //          LCD_D7    

    #define PIN_PB0     MDR_Pin_0   //  LED_1
    #define PIN_PB1     MDR_Pin_1   //  LED_2
    #define PIN_PB2     MDR_Pin_2   //  LED_3
    #define PIN_PB3     MDR_Pin_3   //  LED_4
    #define PIN_PB4     MDR_Pin_4   //  LED_5
    #define PIN_PB5     MDR_Pin_5   //  LED_6
    #define PIN_PB6     MDR_Pin_6   //  LED_7
    #define PIN_PB7     MDR_Pin_7   //  LED_8

    #define PIN_PC0     MDR_Pin_0   //          LCD_RW
    #define PIN_PC1     MDR_Pin_1   //          
    #define PIN_PC2     MDR_Pin_2   //          LCD_E    
    #define PIN_PC3     MDR_Pin_3   //          
    #define PIN_PC4     MDR_Pin_4   //          
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
    #define PIN_PD7     MDR_Pin_7   //                       SSP2_TX          ADC_Ch0/Ref+
    #define PIN_PD8     MDR_Pin_8   //                       SSP2_RX          ADC_Ch1/Ref-
    #define PIN_PD9     MDR_Pin_9   //                       SSP2_CLK         ADC_Ch2
    #define PIN_PD10    MDR_Pin_10  //                       SSP2_FSS         ADC_Ch3    
    #define PIN_PD11    MDR_Pin_11  //                                        ADC_Ch4
    #define PIN_PD12    MDR_Pin_12  //          LCD_RES           SSP3_TX/RX  ADC_Ch5
    #define PIN_PD13    MDR_Pin_13  //                                        ADC_Ch6
    #define PIN_PD14    MDR_Pin_14  //                                        ADC_Ch7


    #define PIN_PE12    MDR_Pin_12  //          LCD_A0
    #define PIN_PE13    MDR_Pin_13  //          LCD_E1
    #define PIN_PE14    MDR_Pin_14  //          LCD_E2

    #define PIN_PF13    MDR_Pin_13  //                            SSP3_FSS
    #define PIN_PF14    MDR_Pin_14  //                            SSP3_CLK
    #define PIN_PF15    MDR_Pin_15  //                            SSP3_RX/TX

    #define PIN_PG0     MDR_Pin_0   //                                SSP4_FSS
    #define PIN_PG1     MDR_Pin_1   //                                SSP4_CLK
    #define PIN_PG2     MDR_Pin_2   //                                SSP4_TX
    #define PIN_PG3     MDR_Pin_3   //                                SSP4_RX
    #define PIN_PG7     MDR_Pin_7   //  Left
    #define PIN_PG11    MDR_Pin_11  //  Right
    #define PIN_PG12    MDR_Pin_12  //  Up
    #define PIN_PG13    MDR_Pin_13  //  Back    
    #define PIN_PG14    MDR_Pin_14  //  Select    
    #define PIN_PG15    MDR_Pin_15  //  Down

    #define PIN_PI11    MDR_Pin_11  //                                SSP4_FSS
    #define PIN_PI12    MDR_Pin_12  //                                SSP4_CLK
    #define PIN_PI13    MDR_Pin_13  //                                SSP4_TX
    #define PIN_PI14    MDR_Pin_14  //                                SSP4_RX

    

//  --------------  ADC Definition  ------------
    #define MDRB_ADC_CH_IN1            ADC_Signal_Ch0
    #define MDRB_ADC_CH_IN2            ADC_Signal_Ch1
    #define MDRB_ADC_CH_IN3            ADC_Signal_Ch2
    #define MDRB_ADC_CH_IN4            ADC_Signal_Ch3

    #define MDRB_ADC_CH_TUNE           MDRB_ADC_CH_IN1

    #define MDRB_ADC_PIN_ALL          0x7F80UL
    #define MDRB_ADC_PIN_ALL_LCD      0x6F80UL 

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

//  ---------------  SPI4 Pin Definition ----------------
  //  PORT_G: SSP4_PG0,PG1,PG2,PG3 - OVER
  #define MDRB_SPI4_FSS_PG0_Ind	     0
	#define MDRB_SPI4_CLK_PG1_Ind	     1
	#define MDRB_SPI4_RX_PG3_Ind 	     3
	#define MDRB_SPI4_TX_PG2_Ind		   2

  #define MDRB_SPI4_FSS_PG0_Msk	       PORT_Pin_0
	#define MDRB_SPI4_CLK_PG1_Msk		     PORT_Pin_1
	#define MDRB_SPI4_RX_PG3_Msk 		     PORT_Pin_3
	#define MDRB_SPI4_TX_PG2_Msk		     PORT_Pin_2

  #define MDRB_SPI4_FSS_PG0_Port	     MDR_GPIO_G
	#define MDRB_SPI4_CLK_PG1_Port		   MDR_GPIO_G
	#define MDRB_SPI4_RX_PG3_Port 		   MDR_GPIO_G
	#define MDRB_SPI4_TX_PG2_Port		     MDR_GPIO_G
  
  #define MDRB_SPI4_FSS_PG0_Func	     MDR_PIN_OVER
	#define MDRB_SPI4_CLK_PG1_Func		   MDR_PIN_OVER
	#define MDRB_SPI4_RX_PG3_Func 		   MDR_PIN_OVER
	#define MDRB_SPI4_TX_PG2_Func		     MDR_PIN_OVER

  //  PORT_I: SSP4_PI11,PI12,PI13,PI14 - OVER
  #define MDRB_SPI4_FSS_PI11_Ind	     11
	#define MDRB_SPI4_CLK_PI12_Ind	     12
	#define MDRB_SPI4_RX_PI14_Ind 	     14
	#define MDRB_SPI4_TX_PI13_Ind		     13

  #define MDRB_SPI4_FSS_PI11_Msk	     PORT_Pin_11
	#define MDRB_SPI4_CLK_PI12_Msk		   PORT_Pin_12
	#define MDRB_SPI4_RX_PI14_Msk 		   PORT_Pin_14
	#define MDRB_SPI4_TX_PI13_Msk		     PORT_Pin_13

  #define MDRB_SPI4_FSS_PI11_Port	     MDR_GPIO_I
	#define MDRB_SPI4_CLK_PI12_Port		   MDR_GPIO_I
	#define MDRB_SPI4_RX_PI14_Port 		   MDR_GPIO_I
	#define MDRB_SPI4_TX_PI13_Port		   MDR_GPIO_I
  
  #define MDRB_SPI4_FSS_PI11_Func	     MDR_PIN_ALT
	#define MDRB_SPI4_CLK_PI12_Func		   MDR_PIN_ALT
	#define MDRB_SPI4_RX_PI14_Func 		   MDR_PIN_ALT
	#define MDRB_SPI4_TX_PI13_Func		   MDR_PIN_ALT

#else
   Please, select board in MDRB_BoardSelect.h!

#endif // USE_MDR1986VE3

#endif // _MDRB_1986VE3_H

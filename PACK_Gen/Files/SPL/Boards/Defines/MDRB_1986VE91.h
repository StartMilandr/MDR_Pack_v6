#ifndef _MDRB_1986VE91_H
#define _MDRB_1986VE91_H

#ifdef USE_MDR1986VE91

#include "MDRB_1986VE9x.h"

//===================================    Заметки по плате    ========================================
// -  Светодиоды подключены к порту D, который содержит пины Jtag_B. Необходимо выставлять USE_JTAG_B в MDR_Congif.h чтобы запись в порт D не портила связь по Jtag.

//  MDR_JTAG_A_PORT   MDR_PORTB [pin0..pin4]
//  MDR_JTAG_B_PORT   MDR_PORTD [pin0..pin4]

//  Переопределение пинов для удобства поиска конфликтов
    #define PIN_PA0       MDR_Pin_0   //          LCD_D0
    #define PIN_PA1       MDR_Pin_1   //          LCD_D1
    #define PIN_PA2       MDR_Pin_2   //          LCD_D2
    #define PIN_PA3       MDR_Pin_3   //          LCD_D3
    #define PIN_PA4       MDR_Pin_4   //          LCD_D4
    #define PIN_PA5       MDR_Pin_5   //          LCD_D5
    #define PIN_PA6       MDR_Pin_6   //          LCD_D6
    #define PIN_PA7       MDR_Pin_7   //          LCD_D7    

    #define PIN_PB0       MDR_Pin_0   //                    JTAG_A
    #define PIN_PB1       MDR_Pin_1   //                    JTAG_A
    #define PIN_PB2       MDR_Pin_2   //                    JTAG_A
    #define PIN_PB3       MDR_Pin_3   //                    JTAG_A
    #define PIN_PB4       MDR_Pin_4   //                    JTAG_A          
    #define PIN_PB12      MDR_Pin_12  //                              SSP1_FSS  SSP2_FSS
    #define PIN_PB13      MDR_Pin_13  //                              SSP1_CLK  SSP2_CLK
    #define PIN_PB14      MDR_Pin_14  //                              SSP1_RX   SSP2_RX
    #define PIN_PB15      MDR_Pin_15  //                              SSP1_TX   SSP2_TX

    #define PIN_PC0       MDR_Pin_0   //                                        SSP2_FSS
    #define PIN_PC1       MDR_Pin_1   //                                        SSP2_CLK
    #define PIN_PC2       MDR_Pin_2   //          LCD_RW                        SSP2_RX
    #define PIN_PC3       MDR_Pin_3   //                                        SSP2_TX
    #define PIN_PC7       MDR_Pin_7   //          LCD_E
    #define PIN_PC10      MDR_Pin_10  //  Select
    #define PIN_PC11      MDR_Pin_11  //  Up
    #define PIN_PC12      MDR_Pin_12  //  Down
    #define PIN_PC13      MDR_Pin_13  //  Left
    #define PIN_PC14      MDR_Pin_14  //  Right                                 SSP2_FSS
    #define PIN_PC15      MDR_Pin_15  //                                        SSP2_RX

    #define PIN_PD0       MDR_Pin_0   //                    JTAG_B                          ADC_Ch0/ref+
    #define PIN_PD1       MDR_Pin_1   //                    JTAG_B                          ADC_Ch1/ref-
    #define PIN_PD2       MDR_Pin_2   //                    JTAG_B              SSP2_RX     ADC_Ch2
    #define PIN_PD3       MDR_Pin_3   //                    JTAG_B              SSP2_FSS    ADC_Ch3
    #define PIN_PD4       MDR_Pin_4   //                    JTAG_B                          ADC_Ch4
    #define PIN_PD5       MDR_Pin_5   //                                        SSP2_CLK    ADC_Ch5
    #define PIN_PD6       MDR_Pin_6   //                                        SSP2_TX     ADC_Ch6
    #define PIN_PD7       MDR_Pin_7   //                                                    ADC_Ch7 - TuneResistor
    #define PIN_PD8       MDR_Pin_8   //                                                    ADC_Ch8
    #define PIN_PD9       MDR_Pin_9   //                              SSP1_FSS              ADC_Ch9    
    #define PIN_PD10      MDR_Pin_10  //  LED_1                       SSP1_CLK              ADC_Ch10
    #define PIN_PD11      MDR_Pin_11  //  LED_2                       SSP1_RX               ADC_Ch11
    #define PIN_PD12      MDR_Pin_12  //  LED_3                       SSP1_TX               ADC_Ch12
    #define PIN_PD13      MDR_Pin_13  //  LED_4                                             ADC_Ch13
    #define PIN_PD14      MDR_Pin_14  //  LED_5                                             ADC_Ch14
    #define PIN_PD15      MDR_Pin_15  //                                                    ADC_Ch15    

    #define PIN_PE4       MDR_Pin_4   //          LCD_E1
    #define PIN_PE5       MDR_Pin_5   //          LCD_E2
    #define PIN_PE10      MDR_Pin_10  //          LCD_RES
    #define PIN_PE11      MDR_Pin_11  //          LCD_A0    
    #define PIN_PE12      MDR_Pin_12  //                              SSP1_RX
    #define PIN_PE13      MDR_Pin_13  //                              SSP1_FSS

    //  Port_F[6..0]
    #define PIN_PF0     MDR_Pin_0   //                                SSP1_TX
    #define PIN_PF1     MDR_Pin_1   //                                SSP1_CLK
    #define PIN_PF2     MDR_Pin_2   //                                SSP1_FSS
    #define PIN_PF3     MDR_Pin_3   //                                SSP1_RX
    #define PIN_PF12    MDR_Pin_12  //                                          SSP2_FSS
    #define PIN_PF13    MDR_Pin_13  //                                          SSP2_CLK
    #define PIN_PF14    MDR_Pin_14  //                                          SSP2_RX
    #define PIN_PF15    MDR_Pin_15  //                                          SSP2_TX



//  --------------  ADC Definition  ------------
    #define MDRB_ADC_CH_IN1            ADC_Signal_Ch7
    #define MDRB_ADC_CH_IN2            ADC_Signal_Ch8
    
    #define MDRB_ADC_CH_TUNE           MDRB_ADC_CH_IN1
    
    #define MDRB_ADC_PIN_ALL          0xFFFFUL
    #define MDRB_ADC_PIN_ALL_JTAG_B   0xFFE0UL        
    #define MDRB_ADC_PIN_ALL_LED      0x83FFUL

//  --------------  Buttons Definition  ------------
    #define MDRB_BTN_PORT_KEY1      MDR_GPIO_C
    #define MDRB_BTN_PIN_KEY1       PIN_PC11   //  Up

    #define MDRB_BTN_PORT_KEY2      MDR_GPIO_C
    #define MDRB_BTN_PIN_KEY2       PIN_PC14   //  Right

    #define MDRB_BTN_PORT_KEY3      MDR_GPIO_C
    #define MDRB_BTN_PIN_KEY3       PIN_PC12   //  Down
	
    #define MDRB_BTN_PORT_KEY4      MDR_GPIO_C
    #define MDRB_BTN_PIN_KEY4       PIN_PC13   //  Left

    #define MDRB_BTN_PORT_KEY5      MDR_GPIO_C
    #define MDRB_BTN_PIN_KEY5       PIN_PC10   //  Select

    #define MDRB_BTN_PORT_KEY_P1    MDR_GPIO_C
    #define MDRB_BTN_PIN_KEY_P1     (PIN_PC11 | PIN_PC14)   //  Up + Right

    // for Initialization
    #define MDRB_BTN_GPIO           MDR_GPIO_C
    #define MDRB_BTN_PinSel        (MDRB_BTN_PIN_KEY1 | MDRB_BTN_PIN_KEY2 | MDRB_BTN_PIN_KEY3 | MDRB_BTN_PIN_KEY4 | MDRB_BTN_PIN_KEY5)

    // Active buttons Level
    #define MDRB_BTNs_PUSH_TO_GND 

//  ----------    LEDs Definition -------------
    #define MDRB_LED_1 	           PIN_PD10   //  VD5
    #define MDRB_LED_2 	           PIN_PD11   //  VD6
    #define MDRB_LED_3 	           PIN_PD12   //  VD7
    #define MDRB_LED_4 	           PIN_PD13   //  VD8
    #define MDRB_LED_5 	           PIN_PD14   //  VD9

    #define MDRB_LED_GPIO          MDR_GPIO_D
    #define MDRB_LED_PinAll       (MDRB_LED_1 | MDRB_LED_2 | MDRB_LED_3 | MDRB_LED_4 | MDRB_LED_5)

//  ----------  LCD Definition ---------------
    // Initialization                 //  D0 .. D7
    #define MDRB_LCD_IN_PORT          MDR_GPIO_A
    #define MDRB_LCD_IN_PINS          (PIN_PA0 | PIN_PA1 | PIN_PA2 | PIN_PA3 | PIN_PA4 | PIN_PA5 | PIN_PA6 | PIN_PA7)
                                      // E1, E2, RES, A0
    #define MDRB_LCD_OUT_PORT         MDR_GPIO_E
    #define MDRB_LCD_OUT_PINS         (PIN_PE4 | PIN_PE5 | PIN_PE10 | PIN_PE11)
                                      // RW, E
    #define MDRB_LCD_OUT_PORT_EX1     MDR_GPIO_C
    #define MDRB_LCD_OUT_PINS_EX1     (PIN_PC2 | PIN_PC7)
    
    //  Control Pins
    #define MDRB_LCD_E1_PORT          MDR_GPIO_E
    #define MDRB_LCD_E1_PIN           PIN_PE4

    #define MDRB_LCD_E2_PORT          MDR_GPIO_E
    #define MDRB_LCD_E2_PIN           PIN_PE5

    #define MDRB_LCD_RES_PORT         MDR_GPIO_E
    #define MDRB_LCD_RES_PIN          PIN_PE10

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
    
    
//  ---------------  SPI1 Pin Definition ----------------
  //  PORT_B: SSP1_PB12,PB13,PB14,PB15 - Alter
  #define MDRB_SPI1_FSS_PB12_Ind	     12
	#define MDRB_SPI1_CLK_PB13_Ind	     13
	#define MDRB_SPI1_RX_PB14_Ind 	     14
	#define MDRB_SPI1_TX_PB16_Ind		     15

  #define MDRB_SPI1_FSS_PB12_Msk	     PORT_Pin_12
	#define MDRB_SPI1_CLK_PB13_Msk		   PORT_Pin_13
	#define MDRB_SPI1_RX_PB14_Msk 		   PORT_Pin_14
	#define MDRB_SPI1_TX_PB16_Msk		     PORT_Pin_15

  #define MDRB_SPI1_FSS_PB12_Port	     MDR_GPIO_B
	#define MDRB_SPI1_CLK_PB13_Port		   MDR_GPIO_B
	#define MDRB_SPI1_RX_PB14_Port 		   MDR_GPIO_B
	#define MDRB_SPI1_TX_PB16_Port		   MDR_GPIO_B
  
  #define MDRB_SPI1_FSS_PB12_Func	     MDR_PIN_ALT
	#define MDRB_SPI1_CLK_PB13_Func		   MDR_PIN_ALT
	#define MDRB_SPI1_RX_PB14_Func 		   MDR_PIN_ALT
	#define MDRB_SPI1_TX_PB16_Func		   MDR_PIN_ALT


  //  PORT_D: SSP1_PD9,PD10,PD11,PD12 - Over
  #define MDRB_SPI1_FSS_PD9_Ind	       9
	#define MDRB_SPI1_CLK_PD10_Ind	     10
	#define MDRB_SPI1_RX_PD11_Ind 	     11
	#define MDRB_SPI1_TX_PD12_Ind		     12

  #define MDRB_SPI1_FSS_PD9_Msk	       PORT_Pin_9
	#define MDRB_SPI1_CLK_PD10_Msk		   PORT_Pin_10
	#define MDRB_SPI1_RX_PD11_Msk 		   PORT_Pin_11
	#define MDRB_SPI1_TX_PD12_Msk		     PORT_Pin_12

  #define MDRB_SPI1_FSS_PD9_Port	     MDR_GPIO_D
	#define MDRB_SPI1_CLK_PD10_Port		   MDR_GPIO_D
	#define MDRB_SPI1_RX_PD11_Port 		   MDR_GPIO_D
	#define MDRB_SPI1_TX_PD12_Port		   MDR_GPIO_D
  
  #define MDRB_SPI1_FSS_PD9_Func	     MDR_PIN_OVER
	#define MDRB_SPI1_CLK_PD10_Func		   MDR_PIN_OVER
	#define MDRB_SPI1_RX_PD11_Func 		   MDR_PIN_OVER
	#define MDRB_SPI1_TX_PD12_Func		   MDR_PIN_OVER

  //  PORT_E: SSP1_PE12,PE13 - Alter
  #define MDRB_SPI1_FSS_PE13_Ind	     13
	#define MDRB_SPI1_RX_PE12_Ind 	     12

  #define MDRB_SPI1_FSS_PE13_Msk	     PORT_Pin_13
	#define MDRB_SPI1_RX_PE12_Msk 		   PORT_Pin_12

  #define MDRB_SPI1_FSS_PE13_Port	     MDR_GPIO_E
	#define MDRB_SPI1_RX_PE12_Port 		   MDR_GPIO_E
  
  #define MDRB_SPI1_FSS_PE13_Func	     MDR_PIN_ALT
	#define MDRB_SPI1_RX_PE12_Func 		   MDR_PIN_ALT


  //  PORT_F: SSP1_PF0,PF1,PF2,PF3 - Alter
  #define MDRB_SPI1_FSS_PF2_Ind	       2
	#define MDRB_SPI1_CLK_PF1_Ind	       1
	#define MDRB_SPI1_RX_PF3_Ind 	       3
	#define MDRB_SPI1_TX_PF0_Ind		     0

  #define MDRB_SPI1_FSS_PF2_Msk	       PORT_Pin_2
	#define MDRB_SPI1_CLK_PF1_Msk		     PORT_Pin_1
	#define MDRB_SPI1_RX_PF3_Msk 		     PORT_Pin_3
	#define MDRB_SPI1_TX_PF0_Msk		     PORT_Pin_0

  #define MDRB_SPI1_FSS_PF2_Port	     MDR_GPIO_F
	#define MDRB_SPI1_CLK_PF1_Port		   MDR_GPIO_F
	#define MDRB_SPI1_RX_PF3_Port 		   MDR_GPIO_F
	#define MDRB_SPI1_TX_PF0_Port		     MDR_GPIO_F
  
  #define MDRB_SPI1_FSS_PF2_Func	     MDR_PIN_ALT
	#define MDRB_SPI1_CLK_PF1_Func		   MDR_PIN_ALT
	#define MDRB_SPI1_RX_PF3_Func 		   MDR_PIN_ALT
	#define MDRB_SPI1_TX_PF0_Func		     MDR_PIN_ALT

//  ---------------  SPI2 Pin Definition ----------------
  //  PORT_B: SSP1_PB12,PB13,PB14,PB15 - Alter
  #define MDRB_SPI2_FSS_PB12_Ind	     12
	#define MDRB_SPI2_CLK_PB13_Ind	     13
	#define MDRB_SPI2_RX_PB14_Ind 	     14
	#define MDRB_SPI2_TX_PB16_Ind		     15

  #define MDRB_SPI2_FSS_PB12_Msk	     PORT_Pin_12
	#define MDRB_SPI2_CLK_PB13_Msk		   PORT_Pin_13
	#define MDRB_SPI2_RX_PB14_Msk 		   PORT_Pin_14
	#define MDRB_SPI2_TX_PB16_Msk		     PORT_Pin_15

  #define MDRB_SPI2_FSS_PB12_Port	     MDR_GPIO_B
	#define MDRB_SPI2_CLK_PB13_Port		   MDR_GPIO_B
	#define MDRB_SPI2_RX_PB14_Port 		   MDR_GPIO_B
	#define MDRB_SPI2_TX_PB16_Port		   MDR_GPIO_B
  
  #define MDRB_SPI2_FSS_PB12_Func	     MDR_PIN_OVER
	#define MDRB_SPI2_CLK_PB13_Func		   MDR_PIN_OVER
	#define MDRB_SPI2_RX_PB14_Func 		   MDR_PIN_OVER
	#define MDRB_SPI2_TX_PB16_Func		   MDR_PIN_OVER

  
  //  PORT_C: PC0,PC1,PC2,PC3 - Over
  #define MDRB_SPI2_FSS_PC0_Ind	       0
	#define MDRB_SPI2_CLK_PC1_Ind	       1
	#define MDRB_SPI2_RX_PC2_Ind 	       2
	#define MDRB_SPI2_TX_PC3_Ind		     3

  #define MDRB_SPI2_FSS_PC0_Msk	       PORT_Pin_0
	#define MDRB_SPI2_CLK_PC1_Msk		     PORT_Pin_1
	#define MDRB_SPI2_RX_PC2_Msk 		     PORT_Pin_2
	#define MDRB_SPI2_TX_PC3_Msk		     PORT_Pin_3

  #define MDRB_SPI2_FSS_PC0_Port	     MDR_GPIO_C
	#define MDRB_SPI2_CLK_PC1_Port		   MDR_GPIO_C
	#define MDRB_SPI2_RX_PC2_Port 		   MDR_GPIO_C
	#define MDRB_SPI2_TX_PC3_Port		     MDR_GPIO_C
  
  #define MDRB_SPI2_FSS_PC0_Func	     MDR_PIN_OVER
	#define MDRB_SPI2_CLK_PC1_Func		   MDR_PIN_OVER
	#define MDRB_SPI2_RX_PC2_Func 		   MDR_PIN_OVER
	#define MDRB_SPI2_TX_PC3_Func		     MDR_PIN_OVER


  //  PORT_C: SSP2_PC14,PC15 - Alter, PC0,PC1 - Over
  #define MDRB_SPI2_FSS_PC14_Ind	     14
	#define MDRB_SPI2_RX_PC15_Ind 	     15

  #define MDRB_SPI2_FSS_PC14_Msk	     PORT_Pin_14
	#define MDRB_SPI2_RX_PC15_Msk 		   PORT_Pin_15

  #define MDRB_SPI2_FSS_PC14_Port	     MDR_GPIO_C
	#define MDRB_SPI2_RX_PC15_Port 		   MDR_GPIO_C
  
  #define MDRB_SPI2_FSS_PC14_Func	     MDR_PIN_ALT
	#define MDRB_SPI2_RX_PC15_Func 		   MDR_PIN_ALT

  
  //  PORT_D: PD3,PD5,PD2,PD6 - Alter
  #define MDRB_SPI2_FSS_PD3_Ind	       3
	#define MDRB_SPI2_CLK_PD5_Ind	       5
	#define MDRB_SPI2_RX_PD2_Ind 	       2
	#define MDRB_SPI2_TX_PD6_Ind		     6

  #define MDRB_SPI2_FSS_PD3_Msk	       PORT_Pin_3
	#define MDRB_SPI2_CLK_PD5_Msk		     PORT_Pin_5
	#define MDRB_SPI2_RX_PD2_Msk 		     PORT_Pin_2
	#define MDRB_SPI2_TX_PD6_Msk		     PORT_Pin_6

  #define MDRB_SPI2_FSS_PD3_Port	     MDR_GPIO_D
	#define MDRB_SPI2_CLK_PD5_Port		   MDR_GPIO_D
	#define MDRB_SPI2_RX_PD2_Port 		   MDR_GPIO_D
	#define MDRB_SPI2_TX_PD6_Port		     MDR_GPIO_D
  
  #define MDRB_SPI2_FSS_PD3_Func	     MDR_PIN_ALT
	#define MDRB_SPI2_CLK_PD5_Func		   MDR_PIN_ALT
	#define MDRB_SPI2_RX_PD2_Func 		   MDR_PIN_ALT
	#define MDRB_SPI2_TX_PD6_Func		     MDR_PIN_ALT


  //  PORT_B: SSP1_PF12,PF13,PF14,PF15 - Over
  #define MDRB_SPI2_FSS_PF12_Ind	     12
	#define MDRB_SPI2_CLK_PF13_Ind	     13
	#define MDRB_SPI2_RX_PF14_Ind 	     14
	#define MDRB_SPI2_TX_PF16_Ind		     15

  #define MDRB_SPI2_FSS_PF12_Msk	     PORT_Pin_12
	#define MDRB_SPI2_CLK_PF13_Msk		   PORT_Pin_13
	#define MDRB_SPI2_RX_PF14_Msk 		   PORT_Pin_14
	#define MDRB_SPI2_TX_PF16_Msk		     PORT_Pin_15

  #define MDRB_SPI2_FSS_PF12_Port	     MDR_GPIO_F
	#define MDRB_SPI2_CLK_PF13_Port		   MDR_GPIO_F
	#define MDRB_SPI2_RX_PF14_Port 		   MDR_GPIO_F
	#define MDRB_SPI2_TX_PF16_Port		   MDR_GPIO_F
  
  #define MDRB_SPI2_FSS_PF12_Func	     MDR_PIN_OVER
	#define MDRB_SPI2_CLK_PF13_Func		   MDR_PIN_OVER
	#define MDRB_SPI2_RX_PF14_Func 		   MDR_PIN_OVER
	#define MDRB_SPI2_TX_PF16_Func		   MDR_PIN_OVER    
    

#else
   Please, select board in MDRB_BoardSelect.h!

#endif // USE_MDR1986VE91

#endif // _MDRB_1986VE91_H

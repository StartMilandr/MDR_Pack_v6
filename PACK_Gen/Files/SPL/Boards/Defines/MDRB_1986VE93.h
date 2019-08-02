#ifndef _MDRB_1986VE93_H
#define _MDRB_1986VE93_H


#ifdef USE_MDR1986VE93

#include "MDRB_1986VE9x.h"

//===================================    Заметки по плате    ========================================
// -  Кнопки Up и Down совпадают в выводами JTAG_B. Поэтому, при работе с кнопками необходимо подключаться по Jtag_А. В файле MDR_Congif.h выбрать USE_JTAG_А.
//    Для работы кнопок Up и Down необходимо установить перемычки X33, X34. При этом Jtag_В становится недоступен.

//  MDR_JTAG_A_PORT   MDR_PORTB [pin0..pin4]
//  MDR_JTAG_B_PORT   MDR_PORTD [pin0..pin4]

//  Переопределение пинов для удобства поиска конфликтов
    //  Корпус H16.48-1B:
    //  Port_A[7..0]: 8 Pins available only
    #define PIN_PA0     MDR_Pin_0   //          LCD_D0
    #define PIN_PA1     MDR_Pin_1   //          LCD_D1                      T1_CH1 /T2_CH1
    #define PIN_PA2     MDR_Pin_2   //          LCD_D2                      T1_nCH1/T2_nCH1
    #define PIN_PA3     MDR_Pin_3   //          LCD_D3                      T1_CH2 /T2_CH1
    #define PIN_PA4     MDR_Pin_4   //          LCD_D4                      T1_nCH2/T2_nCH1
    #define PIN_PA5     MDR_Pin_5   //          LCD_D5                      T1_CH3 /T2_CH1
    #define PIN_PA6     MDR_Pin_6   //          LCD_D6
    #define PIN_PA7     MDR_Pin_7   //          LCD_D7

    //  Port_B[6..0]
    #define PIN_PB0     MDR_Pin_0   //                    JTAG_A            T3_CH1
    #define PIN_PB1     MDR_Pin_1   //                    JTAG_A/TMS        T3_nCH1
    #define PIN_PB2     MDR_Pin_2   //                    JTAG_A/TCK        T3_CH2
    #define PIN_PB3     MDR_Pin_3   //                    JTAG_A            T3_nCH2
    #define PIN_PB4     MDR_Pin_4   //                    JTAG_A            T3_BRK/T3_ETR
    #define PIN_PB5     MDR_Pin_5   //                                      T3_CH3             UART1_TX
    #define PIN_PB6     MDR_Pin_6   //                                      T3_nCH3            UART1_RX
    

    //  Port_C[0..0]: 1 Pin available only!
    #define PIN_PC0     MDR_Pin_0   //  Select                    SSP2_FSS
    
    //  Port_D[3..0]
    #define PIN_PD0     MDR_Pin_0   //  UP                JTAG_B            T1_CH1 /T3_CH1    ADC_Ch0/ref+
    #define PIN_PD1     MDR_Pin_1   //  Down              JTAG_B            T1_nCH1/T3_nCH1   ADC_Ch1/ref-
    #define PIN_PD2     MDR_Pin_2   //                    JTAG_B  SSP2_RX           T3_CH2    ADC_Ch2 - TuneResistor
    #define PIN_PD3     MDR_Pin_3   //          LCD_E     JTAG_B  SSP2_FSS          T3_nCH2   ADC_Ch3
    
    //  Port_E[6,3,2,0]
    #define PIN_PE0     MDR_Pin_0   //                                      T2_CH1
    #define PIN_PE2     MDR_Pin_2   //                                      T2_CH3 /T3_CH1
    #define PIN_PE3     MDR_Pin_3   //  Left
    #define PIN_PE6     MDR_Pin_6   //  Right                               T3_CH3

    //  Port_F[5..0]
    #define PIN_PF0     MDR_Pin_0   //  LED1,   LCD_E1            SSP1_TX
    #define PIN_PF1     MDR_Pin_1   //  LED2,   LCD_E2            SSP1_CLK
    #define PIN_PF2     MDR_Pin_2   //          LCD_RES           SSP1_FSS
    #define PIN_PF3     MDR_Pin_3   //          LCD_RW            SSP1_RX
    #define PIN_PF4     MDR_Pin_4   //          LCD_A0  

//  --------------  ADC Definition  ------------
    #define MDRB_ADC_CH_IN1            ADC_Signal_Ch2
    
    #define MDRB_ADC_CH_TUNE           MDRB_ADC_CH_IN1
    
    #define MDRB_ADC_PIN_ALL          0x000FUL
    //#define MDRB_ADC_PIN_ALL_JTAG_B   0x0000UL        
    #define MDRB_ADC_PIN_ALL_LCD      0x0007UL
    
    #define MDRB_ADC_TUNE_PORT          MDR_GPIO_D
    #define MDRB_ADC_TUNE_PIN           PIN_PD2    


//  --------------  Buttons Definition  ------------
    #define MDRB_BTN_PORT_KEY1        MDR_GPIO_D
    #define MDRB_BTN_PIN_KEY1         PIN_PD0  // Up
	
    #define MDRB_BTN_PORT_KEY2        MDR_GPIO_E
    #define MDRB_BTN_PIN_KEY2         PIN_PE6  // Right
	
    #define MDRB_BTN_PORT_KEY3        MDR_GPIO_D
    #define MDRB_BTN_PIN_KEY3         PIN_PD1  // Down
	
    #define MDRB_BTN_PORT_KEY4        MDR_GPIO_E
    #define MDRB_BTN_PIN_KEY4         PIN_PE3  // Left

    #define MDRB_BTN_PORT_KEY5        MDR_GPIO_C
    #define MDRB_BTN_PIN_KEY5         PIN_PC0  // Select

    #define MDRB_BTN_PORT_KEY_P1      MDR_GPIO_D
    #define MDRB_BTN_PIN_KEY_P1      (PIN_PD0 | PIN_PD1)   //  Up + Down

    // for Initialization
    #define MDRB_BTN_GPIO             MDR_GPIO_C
    #define MDRB_BTN_PinSel           PIN_PC0

    #define MDRB_BTN_GPIO_Ex1         MDR_GPIO_D
    #define MDRB_BTN_PinSel_Ex1      (PIN_PD0 | PIN_PD1)

    #define MDRB_BTN_GPIO_Ex2         MDR_GPIO_E
    #define MDRB_BTN_PinSel_Ex2      (PIN_PE3 | PIN_PE6)
    
    // Active buttons Level
    #define MDRB_BTNs_PUSH_TO_GND    


//  ----------    LEDs Definition -------------
    #define MDRB_LED_1 	              PIN_PF0
    #define MDRB_LED_2 	              PIN_PF1

    #define MDRB_LED_GPIO             MDR_GPIO_F    
    #define MDRB_LED_PinAll          (MDRB_LED_1 | MDRB_LED_2)


//  ----------  LCD Definition ---------------
    // Initialization                 //  D0 .. D7
    #define MDRB_LCD_IN_PORT          MDR_GPIO_A
    #define MDRB_LCD_IN_PINS         (PIN_PA0 | PIN_PA1 | PIN_PA2 | PIN_PA3 | PIN_PA4 | PIN_PA5 | PIN_PA6 | PIN_PA7)
                                      //  E1, E2, RES, RW, A0
    #define MDRB_LCD_OUT_PORT         MDR_GPIO_F
    #define MDRB_LCD_OUT_PINS        (PIN_PF0 | PIN_PF1 | PIN_PF2 | PIN_PF3 | PIN_PF4)
                                      //  E
    #define MDRB_LCD_OUT_PORT_EX1     MDR_GPIO_D
    #define MDRB_LCD_OUT_PINS_EX1    (PIN_PD3)
    
    //  Control Pins
    #define MDRB_LCD_E1_PORT          MDR_GPIO_F
    #define MDRB_LCD_E1_PIN           PIN_PF0

    #define MDRB_LCD_E2_PORT          MDR_GPIO_F
    #define MDRB_LCD_E2_PIN           PIN_PF1

    #define MDRB_LCD_RES_PORT         MDR_GPIO_F
    #define MDRB_LCD_RES_PIN          PIN_PF2

    #define MDRB_LCD_RW_PORT          MDR_GPIO_F 
    #define MDRB_LCD_RW_PIN           PIN_PF3

    #define MDRB_LCD_A0_PORT          MDR_GPIO_F
    #define MDRB_LCD_A0_PIN           PIN_PF4

    #define MDRB_LCD_E_PORT           MDR_GPIO_D
    #define MDRB_LCD_E_PIN            PIN_PD3

    
    //  Bus Commands
    #define MDRB_LCD_BusSetOUT()        MDR_PORTA->OE |= 0x00FF
    
    #define MDRB_LCD_BusSetIN()         MDR_PORTA->OE &= 0xFF00
                                
    #define MDRB_LCD_BusWrite(value)    MDR_PORTA->RXTX &= 0xFF00;          \
                                        MDR_PORTA->RXTX |= (value & 0xFF)
                                    
    #define MDRB_LCD_BusRead()          (uint8_t)(MDR_PORTA->RXTX & 0xFF)


    #define MDRB_LCD_CONFLICT_LED

//  ---------------  SPI1 Pin Definition ----------------
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

//  ---------------  UART1 Pin Definition ----------------
  //  PORT_B: PB5, PB6 - Main
  #define MDRB_UART1_TX_PB5_Ind	     5
  #define MDRB_UART1_RX_PB6_Ind	     6

  #define MDRB_UART1_TX_PB5_Msk	     MDR_Pin_5
	#define MDRB_UART1_RX_PB6_Msk		   MDR_Pin_6

  #define MDRB_UART1_TX_PB5_Port	   MDR_GPIO_B
	#define MDRB_UART1_RX_PB6_Port		 MDR_GPIO_B
  
  #define MDRB_UART1_TX_PB5_Func	   MDR_PIN_ALT
	#define MDRB_UART1_RX_PB6_Func	   MDR_PIN_ALT

#else
   Please, select board in MDRB_BoardSelect.h!

#endif // USE_MDR1986VE93

#endif // _MDRB_1986VE93_H

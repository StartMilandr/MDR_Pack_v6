#ifndef _MDRB_1986VK214_H
#define _MDRB_1986VK214_H

#ifdef USE_MDR1986VK214

//===================================    Частота тактирования    ========================================
#define HSE_PLL_MUL_MAX         MDR_x4   //  HSE_max = 8MHz * 4 = 32MHz (36MHz max)
#define HSE_LOW_SELRI_MAX       MDR_LOWRI_le40MHz
#define HSE_EEPROM_DELAY_MAX    EEPROM_Delay_le36MHz

#define MDRB_CLK_PLL_HSE_RES_MAX     MDR_CPU_CFG_PLL_HSE_RES_DEF(HSE_PLL_MUL_MAX, HSE_EEPROM_DELAY_MAX, HSE_LOW_SELRI_MAX)

//===================================    Заметки по плате    ========================================

//  Переопределение пинов для удобства поиска конфликтов
    #define PIN_PA0       MDR_Pin_0   //      LCD_S0                                T1_CH1
    #define PIN_PA1       MDR_Pin_1   //      LCD_S1                                T1_nCH1
    #define PIN_PA2       MDR_Pin_2   //      LCD_S2
    #define PIN_PA3       MDR_Pin_3   //      LCD_S3
    #define PIN_PA4       MDR_Pin_4   //      LCD_S4  
    #define PIN_PA5       MDR_Pin_5   //      LCD_S5   
    #define PIN_PA6       MDR_Pin_6   //      LCD_S6      JTAG_A SWCLK
    #define PIN_PA7       MDR_Pin_7   //      LCD_S7      JTAG_A SWDIO
    #define PIN_PA8       MDR_Pin_8   //      LCD_S8                                T1_ETR
    #define PIN_PA9       MDR_Pin_9   //      LCD_S9                                T1_BRK
    #define PIN_PA10      MDR_Pin_10  //      LCD_S10
    #define PIN_PA11      MDR_Pin_11  //      LCD_S11          
    #define PIN_PA12      MDR_Pin_12  //      LCD_S12  SSP1_FSS
    #define PIN_PA13      MDR_Pin_13  //      LCD_S13  SSP1_CLK
    #define PIN_PA14      MDR_Pin_14  //      LCD_S14  SSP1_RX
    #define PIN_PA15      MDR_Pin_15  //      LCD_S15  SSP1_TX

    #define PIN_PB0       MDR_Pin_0   //                   UART1_TX
    #define PIN_PB1       MDR_Pin_1   //                   UART1_RX
    #define PIN_PB2       MDR_Pin_2   //
    #define PIN_PB3       MDR_Pin_3   //
    #define PIN_PB4       MDR_Pin_4   //
    #define PIN_PB5       MDR_Pin_5   //
    #define PIN_PB6       MDR_Pin_6   //      LCD_COM1               ADC_Ch7  
    #define PIN_PB7       MDR_Pin_7   //      LCD_COM2               ADC_Ch6
    #define PIN_PB8       MDR_Pin_8   //      LCD_COM3               ADC_Ch5   
    #define PIN_PB9       MDR_Pin_9   //      LCD_COM4               ADC_Ch4 - TuneResistor
    #define PIN_PB10      MDR_Pin_10  //      LCD_S16
    #define PIN_PB11      MDR_Pin_11  //      LCD_S17
    #define PIN_PB12      MDR_Pin_12  //      LCD_S18
    #define PIN_PB13      MDR_Pin_13  //      LCD_S19
    #define PIN_PB14      MDR_Pin_14  //      LCD_S20

    #define PIN_PC0       MDR_Pin_0   //                   UART2_TX
    #define PIN_PC1       MDR_Pin_1   //                   UART2_RX  ADC_Ch3
    #define PIN_PC2       MDR_Pin_2   //                             ADC_Ch2        T2_CH1
    #define PIN_PC3       MDR_Pin_3   //                             ADC_Ch1/Ref+   T2_nCH1
    #define PIN_PC4       MDR_Pin_4   //                             ADC_Ch0/Ref-     
    #define PIN_PC5       MDR_Pin_5   //      LCD_S21                               T2_ETR
    #define PIN_PC6       MDR_Pin_6   //      LCD_S22                               T2_BRK
    #define PIN_PC7       MDR_Pin_7   //      LCD_S23
    #define PIN_PC8       MDR_Pin_8   // KEY1
    #define PIN_PC9       MDR_Pin_9   // KEY2
    #define PIN_PC14      MDR_Pin_14  //    LED1    I2C_SCL
    #define PIN_PC15      MDR_Pin_15  //    LED2    I2C_SDA

   
////  --------------  ADC Definition  ------------
//    #define MDRB_ADC_CH_IN1            ADC_Signal_Ch4   //  PIN_PB8    
//    #define MDRB_ADC_CH_IN2            ADC_Signal_Ch5   //  PIN_PB6
//    
//    #define MDRB_ADC_CH_TUNE           ADC_Signal_Ch4

//    #define MDRB_ADC_PORT_ALL1          MDR_GPIO_C
//    #define MDRB_ADC_PINS_ALL1          0x001EUL    
//    #define MDRB_ADC_PORT_ALL2          MDR_GPIO_B
//    #define MDRB_ADC_PINS_ALL2          0x03C0UL
//    
//    //#define MDRB_ADC_PIN_KEY_PROTECT2   0x01C0UL

//  --------------  Jtag protection  ------------
    #define MDRB_Jtag_ClrPinsPA    (~MDR_JTAG_A_PINS)
    
//  --------------  Buttons Definition  ------------
    #define MDRB_BTN_PORT_KEY1      MDR_GPIO_C
    #define MDRB_BTN_PIN_KEY1       PIN_PC8   // Up

    #define MDRB_BTN_PORT_KEY2      MDR_GPIO_C
    #define MDRB_BTN_PIN_KEY2       PIN_PC9   // Right

    #define MDRB_BTN_PORT_KEY_P1    MDR_GPIO_C 
    #define MDRB_BTN_PIN_KEY_P1     (MDRB_BTN_PIN_KEY1 | MDRB_BTN_PIN_KEY2)   //  Up + Right
  
    // for Initialization
    #define MDRB_BTN_GPIO           MDR_GPIO_C
    #define MDRB_BTN_PinSel         (MDRB_BTN_PIN_KEY1 | MDRB_BTN_PIN_KEY2)

    // Active buttons Level
    #define MDRB_BTNs_PUSH_TO_GND 

//  ----------    LEDs Definition -------------
    #define MDRB_LED_1 	           PIN_PC14    // VD5
    #define MDRB_LED_2 	           PIN_PC15    // VD6

    #define MDRB_LED_GPIO          MDR_GPIO_C
    #define MDRB_LED_PinAll       (MDRB_LED_1 | MDRB_LED_2)


//  ---------------  SPI1 Pin Definition ----------------
  //  PORT_C: SSP1_PC10,PC11,PC12,PC13 - Main
  #define MDRB_SPI1_FSS_PC10_Ind	     10
	#define MDRB_SPI1_CLK_PC11_Ind	     11
	#define MDRB_SPI1_RX_PC12_Ind 	     12
	#define MDRB_SPI1_TX_PC13_Ind		     13

  #define MDRB_SPI1_FSS_PC10_Msk	     MDR_Pin_10
	#define MDRB_SPI1_CLK_PC11_Msk		   MDR_Pin_11
	#define MDRB_SPI1_RX_PC12_Msk 		   MDR_Pin_12
	#define MDRB_SPI1_TX_PC13_Msk		     MDR_Pin_13

  #define MDRB_SPI1_FSS_PC10_Port	     MDR_GPIO_C
	#define MDRB_SPI1_CLK_PC11_Port		   MDR_GPIO_C
	#define MDRB_SPI1_RX_PC12_Port 		   MDR_GPIO_C
	#define MDRB_SPI1_TX_PC13_Port		   MDR_GPIO_C
  
  #define MDRB_SPI1_FSS_PC10_Func	     MDR_PIN_MAIN
	#define MDRB_SPI1_CLK_PC11_Func		   MDR_PIN_MAIN
	#define MDRB_SPI1_RX_PC12_Func 		   MDR_PIN_MAIN
	#define MDRB_SPI1_TX_PC13_Func		   MDR_PIN_MAIN

//  ----------  LCD Definition ---------------
  // Initialization                 //  seg0-seg15
  #define MDRB_LCD_PORT             MDR_GPIO_A
  #define MDRB_LCD_PINs             MDR_Pin_All
                                    //  PB6-PB9: COM1 - COM4, PB10-PB14: seg16 - seg20
  #define MDRB_LCD_PORT_EX1         MDR_GPIO_B
  #define MDRB_LCD_PINs_EX1         (PIN_PB6 | PIN_PB7 | PIN_PB8 | PIN_PB9 | PIN_PB10 | PIN_PB11 | PIN_PB12 | PIN_PB13 | PIN_PB14)
                                    //  seg21-seg23
  #define MDRB_LCD_PORT_EX2         MDR_GPIO_C
  #define MDRB_LCD_PINs_EX2         (PIN_PC5 | PIN_PC6 | PIN_PC7)

  #define LCD_XT13468PSPA_DISPLAY
  

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

//  ---------------  I2C Pin Definition ---------------- 
  #define MDRB_I2C_SCL_PC14_Ind	     14
  #define MDRB_I2C_SDA_PC15_Ind	     15

  #define MDRB_I2C_SCL_PC14_Msk	     PIN_PC14
	#define MDRB_I2C_SDA_PC15_Msk		   PIN_PC15

  #define MDRB_I2C_SCL_PC14_Port	   MDR_GPIO_C
	#define MDRB_I2C_SDA_PC15_Port		 MDR_GPIO_C
  
  #define MDRB_I2C_SCL_PC14_Func	   MDR_PIN_MAIN
	#define MDRB_I2C_SDA_PC15_Func	   MDR_PIN_MAIN  


#else
   Please, select board in MDRB_BoardSelect.h!

#endif // USE_MDR1986VK214

#endif // _MDRB_1986VK214_H

#ifndef _MDRB_1986VE1_H
#define _MDRB_1986VE1_H

#ifdef USE_MDR1986VE1

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
    #define PIN_PA6     MDR_Pin_6   //          LCD_D6
    #define PIN_PA7     MDR_Pin_7   //          LCD_D7

    #define PIN_PD7     MDR_Pin_7   //  LED_1
    #define PIN_PD8     MDR_Pin_8   //  LED_2
    #define PIN_PD9     MDR_Pin_9   //  LED_3
    #define PIN_PD10    MDR_Pin_10  //  LED_4
    #define PIN_PD11    MDR_Pin_11  //  LED_5
    #define PIN_PD12    MDR_Pin_12  //  LED_6
    #define PIN_PD13    MDR_Pin_13  //  LED_7
    #define PIN_PD14    MDR_Pin_14  //  LED_8

    #define PIN_PE5     MDR_Pin_5   //  Down
    #define PIN_PE8     MDR_Pin_8   //  Up
    #define PIN_PE9     MDR_Pin_9   //  Select
    #define PIN_PE10    MDR_Pin_10  //  Left
    #define PIN_PE11    MDR_Pin_11  //  Back
    #define PIN_PE12    MDR_Pin_12  //          LCD_A0
    #define PIN_PE13    MDR_Pin_13  //          LCD_E1
    #define PIN_PE14    MDR_Pin_14  //          LCD_E2
    #define PIN_PE15    MDR_Pin_15  //  Down    
    
    #define PIN_PC0     MDR_Pin_0   //          LCD_RW
    #define PIN_PC2     MDR_Pin_2   //          LCD_E

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
    

//  ----------    SPI Definition -------------
    //  SPI 1
	  #define MDRB_SPI1_D_PIN_CLK	     PORT_Pin_4
	  #define MDRB_SPI1_D_PIN_TX		   PORT_Pin_2
	  #define MDRB_SPI1_D_PIN_RX		   PORT_Pin_3
	  #define MDRB_SPI1_D_PIN_CS		   PORT_Pin_5    

	  #define MDRB_SPI1_D_PORT_CLK     RST_CLK_PCLK_PORTD
	  #define MDRB_SPI1_D_PORT			    MDR_PORTD
    #define MDRB_SPI1_D_PINS         (MDRB_SPI1_D_PIN_CLK | MDRB_SPI1_D_PIN_TX | MDRB_SPI1_D_PIN_RX | MDRB_SPI1_D_PIN_CS)
    #define MDRB_SPI1_D_PINS_FUNC    PORT_FUNC_ALTER
    
    #define MDRB_SPI1_D_PINS_FUNC_CLEAR  (~ ((3 << (4 * 2)) | \
                                            (3 << (2 * 2)) | \
                                            (3 << (3 * 2)) | \
                                            (3 << (5 * 2))   \
                                        ))
                                        
    //  SPI 2
	  #define MDRB_SPI2_D_PIN_CLK	    PORT_Pin_9
	  #define MDRB_SPI2_D_PIN_TX		    PORT_Pin_7
	  #define MDRB_SPI2_D_PIN_RX		    PORT_Pin_8
	  #define MDRB_SPI2_D_PIN_CS		    PORT_Pin_10    

	  #define MDRB_SPI2_D_PORT_CLK     RST_CLK_PCLK_PORTD
	  #define MDRB_SPI2_D_PORT			    MDR_PORTD
    #define MDRB_SPI2_D_PINS         (MDRB_SPI2_D_PIN_CLK | MDRB_SPI2_D_PIN_TX | MDRB_SPI2_D_PIN_RX | MDRB_SPI2_D_PIN_CS)
    #define MDRB_SPI2_D_PINS_FUNC    PORT_FUNC_MAIN
    
    #define MDRB_SPI2_D_PINS_FUNC_CLEAR  (~ ((3 << (9 * 2)) | \
                                            (3 << (7 * 2)) | \
                                            (3 << (8 * 2)) | \
                                            (3 << (10 * 2))  \
                                        ))                                        

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


#else
   Please, select board in MDRB_BoardSelect.h!

#endif //  USE_MDR1986VE1

#endif // _MDRB_1986VE1_H

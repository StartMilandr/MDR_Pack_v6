#ifndef _MDRB_1901VC1_H
#define _MDRB_1901VC1_H

#ifdef USE_MDR1901VC1

//  --------------  Buttons Definition  ------------
    #define MDRB_BTN_PORT_KEY1      MDR_GPIO_C    // UP
    #define MDRB_BTN_PIN_KEY1       MDR_Pin_3
	
    #define MDRB_BTN_PORT_KEY2      MDR_GPIO_C    // Right
    #define MDRB_BTN_PIN_KEY2       MDR_Pin_6
	
    #define MDRB_BTN_PORT_KEY3      MDR_GPIO_C    // Down
    #define MDRB_BTN_PIN_KEY3       MDR_Pin_4
	
    #define MDRB_BTN_PORT_KEY4      MDR_GPIO_C    // Left
    #define MDRB_BTN_PIN_KEY4       MDR_Pin_5

    #define MDRB_BTN_PORT_KEY5      MDR_GPIO_C    // Select
    #define MDRB_BTN_PIN_KEY5       MDR_Pin_0

    // for Initialization
    #define MDRB_BTN_GPIO           MDR_GPIO_C
    #define MDRB_BTN_PinSel         (MDRB_BTN_PIN_KEY1 | MDRB_BTN_PIN_KEY2 | MDRB_BTN_PIN_KEY3 | MDRB_BTN_PIN_KEY4 | MDRB_BTN_PIN_KEY5)
    
    // Active buttons Level
    #define MDRB_BTNs_PUSH_TO_GND     

//  ----------    LEDs Definition -------------
    #define MDRB_LED_1 	            MDR_Pin_15    // VD3
    #define MDRB_LED_2 	            MDR_Pin_14    // VD4
    #define MDRB_LED_3 	            MDR_Pin_13    // VD5
    #define MDRB_LED_4 	            MDR_Pin_12    // VD6
    #define MDRB_LED_5 	            MDR_Pin_11    // VD7

    #define MDRB_LED_GPIO           MDR_GPIO_B
    #define MDRB_LED_PinAll         MDRB_LED_1 | MDRB_LED_2 | MDRB_LED_3 | MDRB_LED_4 | MDRB_LED_5

//  ----------  LCD Definition ---------------
//    #define MDRB_LCD_E1_PORT     MDR_PORTE     // PE4
//    #define MDRB_LCD_E1_PIN      PORT_Pin_4

//    #define MDRB_LCD_E2_PORT     MDR_PORTE     // PE5
//    #define MDRB_LCD_E2_PIN      PORT_Pin_5

//    #define MDRB_LCD_RES_PORT    MDR_PORTD     // PD9
//    #define MDRB_LCD_RES_PIN     PORT_Pin_9

//    #define MDRB_LCD_RW_PORT     MDR_PORTC     // PC2
//    #define MDRB_LCD_RW_PIN      PORT_Pin_2

//    #define MDRB_LCD_A0_PORT     MDR_PORTE     // PE11
//    #define MDRB_LCD_A0_PIN      PORT_Pin_11

//    #define MDRB_LCD_E_PORT      MDR_PORTC     // PC7
//    #define MDRB_LCD_E_PIN       PORT_Pin_7

//    // Initialization
//    #define MDRB_LCD_CLOCK     (RST_CLK_PCLK_PORTA | RST_CLK_PCLK_PORTB | RST_CLK_PCLK_PORTC | RST_CLK_PCLK_PORTF)

//    #define MDRB_LCD_IN_PORT         MDR_PORTA
//    #define MDRB_LCD_IN_PINS        (PORT_Pin_0 | PORT_Pin_1 | PORT_Pin_2 | PORT_Pin_3 | PORT_Pin_4 | PORT_Pin_5) 

//    #define MDRB_LCD_IN_PORT_EX1     MDR_PORTF
//    #define MDRB_LCD_IN_PINS_EX1    (PORT_Pin_2 | PORT_Pin_3)

//    #define MDRB_LCD_OUT_PORT        MDR_PORTB
//    #define MDRB_LCD_OUT_PINS       (PORT_Pin_7 | PORT_Pin_8 | PORT_Pin_9 | PORT_Pin_10) 

//    #define MDRB_LCD_OUT_PORT_EX1    MDR_PORTC
//    #define MDRB_LCD_OUT_PINS_EX1   (PORT_Pin_0 | PORT_Pin_1)
//    
//    //  Commands
//    #define LCD_CODE_BUS_OUT        MDR_PORTA->OE |= 0x003F; \
//                                    MDR_PORTF->OE |= 0x000C;
//    
//    #define LCD_CODE_BUS_IN         MDR_PORTA->OE &= 0xFFC0;  \
//                                    MDR_PORTF->OE &= 0xFFF3;
//                                
//    #define LCD_CODE_WRITE(value)   MDR_PORTA->RXTX &= 0xFFC0;          \
//                                    MDR_PORTA->RXTX |= (value & 0x3F);  \
//                                    MDR_PORTF->RXTX &= 0xFFF3;          \
//                                    MDR_PORTF->RXTX |= ((value >> 4) & 0x0C);
//                                    
//    #define LCD_CODE_READ     (uint8_t)(MDR_PORTA->RXTX & 0x3F) | (uint8_t)((MDR_PORTF->RXTX << 4) & 0xC0);


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


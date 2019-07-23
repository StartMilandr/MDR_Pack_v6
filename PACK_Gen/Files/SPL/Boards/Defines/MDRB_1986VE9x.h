#ifndef _MDRB_1986VE9x_H
#define _MDRB_1986VE9x_H


#if defined (USE_BOARD_VE91)  || defined (USE_BOARD_VE92) || defined (USE_BOARD_VE93) || defined (USE_BOARD_VE94)

//===================================    Частота тактирования    ========================================
  #define HSE_PLL_MUL_MAX         MDR_x10   //  HSE_max = 8MHz * 10 = 80MHz
  #define HSE_LOW_SELRI_MAX       MDR_LOWRI_gt80MHz
  #define HSE_EEPROM_DELAY_MAX    EEPROM_Delay_le100MHz

  #define MDRB_CLK_PLL_HSE_RES_MAX     MDR_CPU_CFG_PLL_HSE_RES_DEF(HSE_PLL_MUL_MAX, HSE_EEPROM_DELAY_MAX, HSE_LOW_SELRI_MAX)


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

    //  CtrlReady: [PF0] = [Ready]
    #define MDRB_EBC_PORT_READY            MDR_PORTC
    #define MDRB_EBC_PORT_READY_CLK        RST_CLK_PCLK_PORTC
    #define MDRB_EBC_PORT_READY_PINS       PORT_Pin_0
    #define MDRB_EBC_PORT_READY_FUNC       PORT_FUNC_MAIN

    #define MDRB_EBC_START_ADDR	    0x10000000
    #define MDRB_EBC_A20_D32_CLK     (MDRB_EBC_DATA_PORT_LO8_CLK | MDRB_EBC_DATA_PORT_LO16_CLK | MDRB_EBC_DATA_PORT_HI16_CLK | MDRB_EBC_PORT_CTRL_CLK | MDRB_EBC_PORT_ADDR20_CLK | MDRB_EBC_PORT_ADDR20_1_CLK)

//  ---------------  UART1 Definition ----------------
    //  Uart1 TX - PB0
    #define MDRB_UART1_TX_PB0_PORT        MDR_PORTB
    #define MDRB_UART1_TX_PB0_CLK         RST_CLK_PCLK_PORTB
    #define MDRB_UART1_TX_PB0_PINS        PORT_Pin_0
    #define MDRB_UART1_TX_PB0_FUNC        PORT_FUNC_OVERRID
    
    //  Uart1 RX - PB6
    #define MDRB_UART1_RX_PB6_PORT         MDR_PORTB
    #define MDRB_UART1_RX_PB6_CLK          RST_CLK_PCLK_PORTB
    #define MDRB_UART1_RX_PB6_PINS         PORT_Pin_6
    #define MDRB_UART1_RX_PB6_FUNC         PORT_FUNC_ALTER
    
//  ---------------  UART2 Definition ----------------    
    //  Uart2 TX - PD1 - It Overrides JTAG_B!
    #define MDRB_UART2_TX_PD1_PORT        MDR_PORTD
    #define MDRB_UART2_TX_PD1_CLK         RST_CLK_PCLK_PORTD
    #define MDRB_UART2_TX_PD1_PINS        PORT_Pin_1
    #define MDRB_UART2_TX_PD1_FUNC        PORT_FUNC_ALTER
    
    //  Uart2 TX - PD1
    #define MDRB_UART2_TX_PF1_PORT        MDR_PORTF
    #define MDRB_UART2_TX_PF1_CLK         RST_CLK_PCLK_PORTF
    #define MDRB_UART2_TX_PF1_PINS        PORT_Pin_1
    #define MDRB_UART2_TX_PF1_FUNC        PORT_FUNC_OVERRID    
    
    //  Uart2 RX - PB1
    #define MDRB_UART2_RX_PB1_PORT        MDR_PORTB
    #define MDRB_UART2_RX_PB1_CLK         RST_CLK_PCLK_PORTB
    #define MDRB_UART2_RX_PB1_PINS        PORT_Pin_1
    #define MDRB_UART2_RX_PB1_FUNC        PORT_FUNC_OVERRID
    
//  ---------------  ADC Definition ---------------- 
    #define MDRB_ADC_7_PIN           PORT_Pin_7
    #define MDRB_ADC_7_PORT          MDR_PORTD
    #define MDRB_ADC_7_CLOCK         RST_CLK_PCLK_PORTD
   
//  ----------    DMA Definition -------------
    #define MDRB_DMA_CLOCK_SELECT  (RST_CLK_PCLK_SSP1 | RST_CLK_PCLK_SSP2 | RST_CLK_PCLK_DMA)

//  ----------    DAC Definition -------------
    #define MDRB_DAC1_CLOCK    RST_CLK_PCLK_PORTE
    #define MDRB_DAC1_PORT     MDR_PORTE
    #define MDRB_DAC1_PIN      PORT_Pin_9
    
    #define MDRB_DAC2_CLOCK    RST_CLK_PCLK_PORTE
    #define MDRB_DAC2_PORT     MDR_PORTE
    #define MDRB_DAC2_PIN      PORT_Pin_0

#else
   Please, select board in MDRB_BoardSelect.h!

#endif 

#endif // _MDRB_1986VE9x_H

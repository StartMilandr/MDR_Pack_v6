#include "MDRB_Timer_PinSelect.h"

//======================  Выбор пинов ======================
#if   defined(USE_BOARD_VE1)
  //  см. MDRB_1986VE1.h
  const MDR_Timer_CfgPinGPIO _pinTX_UART1 = {MDRB_UART1_TX_PC3_Port, MDRB_UART1_TX_PC3_Ind, MDRB_UART1_TX_PC3_Func};
  
                                       
#elif defined(USE_BOARD_VE3)
  //  см. MDRB_1986VE3.h
  const MDR_UART_CfgPinGPIO _pinTX_UART1 = {MDRB_UART1_TX_PC3_Port, MDRB_UART1_TX_PC3_Ind, MDRB_UART1_TX_PC3_Func};
  const MDR_UART_CfgPinGPIO _pinRX_UART1 = {MDRB_UART1_RX_PC4_Port, MDRB_UART1_RX_PC4_Ind, MDRB_UART1_RX_PC4_Func};    
                                                                           
  const MDR_UART_CfgPinGPIO _pinTX_UART2 = {MDRB_UART2_TX_PD13_Port, MDRB_UART2_TX_PD13_Ind, MDRB_UART2_TX_PD13_Func};
  const MDR_UART_CfgPinGPIO _pinRX_UART2 = {MDRB_UART2_RX_PD14_Port, MDRB_UART2_RX_PD14_Ind, MDRB_UART2_RX_PD14_Func};    
  
#elif defined(USE_BOARD_VE91) || defined(USE_BOARD_VE94)
  const MDR_Timer_CfgPinGPIO _pinTim1_CH1  = {MDR_GPIO_F, 6,  MDR_PIN_ALT};
  const MDR_Timer_CfgPinGPIO _pinTim1_nCH1 = {MDR_GPIO_F, 7,  MDR_PIN_ALT};
  const MDR_Timer_CfgPinGPIO _pinTim1_CH2  = {MDR_GPIO_F, 8,  MDR_PIN_ALT};
  const MDR_Timer_CfgPinGPIO _pinTim1_nCH2 = {MDR_GPIO_F, 9,  MDR_PIN_ALT};
  const MDR_Timer_CfgPinGPIO _pinTim1_CH3  = {MDR_GPIO_F, 10, MDR_PIN_ALT};
  const MDR_Timer_CfgPinGPIO _pinTim1_nCH3 = {MDR_GPIO_F, 11, MDR_PIN_ALT};
  const MDR_Timer_CfgPinGPIO _pinTim1_CH4  = {MDR_GPIO_F, 12, MDR_PIN_ALT};
  const MDR_Timer_CfgPinGPIO _pinTim1_nCH4 = {MDR_GPIO_F, 13, MDR_PIN_ALT};
  const MDR_Timer_CfgPinGPIO _pinTim1_ETR  = {MDR_GPIO_F, 14, MDR_PIN_ALT};
  const MDR_Timer_CfgPinGPIO _pinTim1_BRK  = {MDR_GPIO_F, 15, MDR_PIN_ALT};


  const MDR_Timer_CfgPinGPIO _pinTim2_CH1  = {MDR_GPIO_A, 1,  MDR_PIN_OVER};
  const MDR_Timer_CfgPinGPIO _pinTim2_nCH1 = {MDR_GPIO_A, 2,  MDR_PIN_OVER};
  const MDR_Timer_CfgPinGPIO _pinTim2_CH2  = {MDR_GPIO_A, 3,  MDR_PIN_OVER};
  const MDR_Timer_CfgPinGPIO _pinTim2_nCH2 = {MDR_GPIO_A, 4,  MDR_PIN_OVER};
  const MDR_Timer_CfgPinGPIO _pinTim2_CH3  = {MDR_GPIO_A, 5,  MDR_PIN_OVER};
  const MDR_Timer_CfgPinGPIO _pinTim2_nCH3 = {MDR_GPIO_A, 8,  MDR_PIN_OVER};
  const MDR_Timer_CfgPinGPIO _pinTim2_CH4  = {MDR_GPIO_A, 9,  MDR_PIN_OVER};
  const MDR_Timer_CfgPinGPIO _pinTim2_nCH4 = {MDR_GPIO_A, 10, MDR_PIN_OVER};
  const MDR_Timer_CfgPinGPIO _pinTim2_ETR  = {MDR_GPIO_A, 15, MDR_PIN_OVER};
  const MDR_Timer_CfgPinGPIO _pinTim2_BRK  = {MDR_GPIO_A, 14, MDR_PIN_OVER};

  const MDR_Timer_CfgPinGPIO _pinTim3_CH1  = {MDR_GPIO_C, 2,  MDR_PIN_ALT};     // nWE - PC2  - PX11_12
  const MDR_Timer_CfgPinGPIO _pinTim3_nCH1 = {MDR_GPIO_C, 3,  MDR_PIN_ALT};     // BE0 - PC3  - PX11_5
  const MDR_Timer_CfgPinGPIO _pinTim3_CH2  = {MDR_GPIO_C, 4,  MDR_PIN_ALT};     // BE1 - PC4  - PX11_6
  const MDR_Timer_CfgPinGPIO _pinTim3_nCH2 = {MDR_GPIO_C, 5,  MDR_PIN_ALT};     // BE2 - PC5  - PX11_7
  const MDR_Timer_CfgPinGPIO _pinTim3_CH3  = {MDR_GPIO_C, 6,  MDR_PIN_ALT};     // BE3 - PC6  - PX11_8
  const MDR_Timer_CfgPinGPIO _pinTim3_nCH3 = {MDR_GPIO_C, 7,  MDR_PIN_ALT};     // CLOCK - PC7  - PX11_9
  const MDR_Timer_CfgPinGPIO _pinTim3_CH4  = {MDR_GPIO_B, 7,  MDR_PIN_OVER};    // D23  - PB7  - PX10_11
  const MDR_Timer_CfgPinGPIO _pinTim3_nCH4 = {MDR_GPIO_B, 8,  MDR_PIN_OVER};    // D24  - PB8  - PX10_12
  const MDR_Timer_CfgPinGPIO _pinTim3_ETR  = {MDR_GPIO_C, 10, MDR_PIN_ALT};     //        PC10 - PX11_30
  const MDR_Timer_CfgPinGPIO _pinTim3_BRK  = {MDR_GPIO_C, 11, MDR_PIN_ALT};     //        PC11 - PX11_29
  
#elif defined(USE_BOARD_VE92)
  //  см. MDRB_1986VE92.h
  const MDR_UART_CfgPinGPIO _pinTX_UART2 = {MDRB_UART2_TX_PF1_Port, MDRB_UART2_TX_PF1_Ind, MDRB_UART2_TX_PF1_Func};
  const MDR_UART_CfgPinGPIO _pinRX_UART2 = {MDRB_UART2_RX_PF0_Port, MDRB_UART2_RX_PF0_Ind, MDRB_UART2_RX_PF0_Func};
  
  
#elif defined(USE_BOARD_VE93)
  //  см. MDRB_1986VE93.h
  const MDR_UART_CfgPinGPIO _pinTX_UART1 = {MDRB_UART1_TX_PB5_Port, MDRB_UART1_TX_PB5_Ind, MDRB_UART1_TX_PB5_Func};
  const MDR_UART_CfgPinGPIO _pinRX_UART1 = {MDRB_UART1_RX_PB6_Port, MDRB_UART1_RX_PB6_Ind, MDRB_UART1_RX_PB6_Func};  

  
#elif defined(USE_BOARD_VC1)
  //  см. MDRB_1901VС1.h
  const MDR_UART_CfgPinGPIO _pinTX_UART3 = {MDRB_UART3_TX_PF1_Port, MDRB_UART3_TX_PF1_Ind, MDRB_UART3_TX_PF1_Func};
  const MDR_UART_CfgPinGPIO _pinRX_UART3 = {MDRB_UART3_RX_PF0_Port, MDRB_UART3_RX_PF0_Ind, MDRB_UART3_RX_PF0_Func};

  
#elif defined (USE_MDR1986VE4) || defined (USE_MDR1986VK214) || defined (USE_MDR1986VK234)
  //  см. MDRB_1986VE4.h / MDRB_1986VK214.h / MDRB_1986VK234.h  
  const MDR_UART_CfgPinGPIO _pinTX_UART1 = {MDRB_UART1_TX_PB0_Port, MDRB_UART1_TX_PB0_Ind, MDRB_UART1_TX_PB0_Func};
  const MDR_UART_CfgPinGPIO _pinRX_UART1 = {MDRB_UART1_RX_PB1_Port, MDRB_UART1_RX_PB1_Ind, MDRB_UART1_RX_PB1_Func};    
                                                                           
  const MDR_UART_CfgPinGPIO _pinTX_UART2 = {MDRB_UART2_TX_PC0_Port, MDRB_UART2_TX_PC0_Ind, MDRB_UART2_TX_PC0_Func};
  const MDR_UART_CfgPinGPIO _pinRX_UART2 = {MDRB_UART2_RX_PC1_Port, MDRB_UART2_RX_PC1_Ind, MDRB_UART2_RX_PC1_Func};
    

#endif


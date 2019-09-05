#include "MDRB_UART_PinSelect.h"

//======================  Выбор пинов ======================
#if   defined(USE_BOARD_VE1)
  //  см. MDRB_1986VE1.h
  const MDR_UART_CfgPinGPIO _pinTX_UART1 = {MDRB_UART1_TX_PC3_Port, MDRB_UART1_TX_PC3_Ind, MDRB_UART1_TX_PC3_Func};
  const MDR_UART_CfgPinGPIO _pinRX_UART1 = {MDRB_UART1_RX_PC4_Port, MDRB_UART1_RX_PC4_Ind, MDRB_UART1_RX_PC4_Func};    
                                                                           
  const MDR_UART_CfgPinGPIO _pinTX_UART2 = {MDRB_UART2_TX_PD13_Port, MDRB_UART2_TX_PD13_Ind, MDRB_UART2_TX_PD13_Func};
  const MDR_UART_CfgPinGPIO _pinRX_UART2 = {MDRB_UART2_RX_PD14_Port, MDRB_UART2_RX_PD14_Ind, MDRB_UART2_RX_PD14_Func};  
  
                                       
#elif defined(USE_BOARD_VE3)
  //  см. MDRB_1986VE3.h
  const MDR_UART_CfgPinGPIO _pinTX_UART1 = {MDRB_UART1_TX_PC3_Port, MDRB_UART1_TX_PC3_Ind, MDRB_UART1_TX_PC3_Func};
  const MDR_UART_CfgPinGPIO _pinRX_UART1 = {MDRB_UART1_RX_PC4_Port, MDRB_UART1_RX_PC4_Ind, MDRB_UART1_RX_PC4_Func};    
                                                                           
  const MDR_UART_CfgPinGPIO _pinTX_UART2 = {MDRB_UART2_TX_PD13_Port, MDRB_UART2_TX_PD13_Ind, MDRB_UART2_TX_PD13_Func};
  const MDR_UART_CfgPinGPIO _pinRX_UART2 = {MDRB_UART2_RX_PD14_Port, MDRB_UART2_RX_PD14_Ind, MDRB_UART2_RX_PD14_Func};    
  
#elif defined(USE_BOARD_VE91) || defined(USE_BOARD_VE94)
  //  см. MDRB_1986VE91.h
  const MDR_UART_CfgPinGPIO _pinTX_UART2 = {MDRB_UART2_TX_PF1_Port, MDRB_UART2_TX_PF1_Ind, MDRB_UART2_TX_PF1_Func};
  const MDR_UART_CfgPinGPIO _pinRX_UART2 = {MDRB_UART2_RX_PF0_Port, MDRB_UART2_RX_PF0_Ind, MDRB_UART2_RX_PF0_Func};
    
  
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

#elif defined(USE_BOARD_VE8)
  //  см. MDRB_1986VE8.h  
  const MDR_UART_CfgPinGPIO _pinTX_UART1 = {MDRB_UART1_TX_PE15_Port, MDRB_UART1_TX_PE15_Ind, MDRB_UART1_TX_PE15_Func};
  const MDR_UART_CfgPinGPIO _pinRX_UART1 = {MDRB_UART1_RX_PE16_Port, MDRB_UART1_RX_PE16_Ind, MDRB_UART1_RX_PE16_Func};
    
#elif defined(USE_BOARD_VK014)
  //  см. MDRB_1986VE8.h
  const MDR_UART_CfgPinGPIO _pinTX_UART1 = {MDRB_UART1_TX_PE15_Port, MDRB_UART1_TX_PE15_Ind, MDRB_UART1_TX_PE15_Func};
  const MDR_UART_CfgPinGPIO _pinRX_UART1 = {MDRB_UART1_RX_PE16_Port, MDRB_UART1_RX_PE16_Ind, MDRB_UART1_RX_PE16_Func};  
  
#elif defined(USE_BOARD_ESila)
  //  см. MDRB_ESila.h
  const MDR_UART_CfgPinGPIO _pinTX_UART1 = {MDRB_UART1_TX_PB1_Port, MDRB_UART1_TX_PB1_Ind, MDRB_UART1_TX_PB1_Func};
  const MDR_UART_CfgPinGPIO _pinRX_UART1 = {MDRB_UART1_RX_PB0_Port, MDRB_UART1_RX_PB0_Ind, MDRB_UART1_RX_PB0_Func}; 

#endif


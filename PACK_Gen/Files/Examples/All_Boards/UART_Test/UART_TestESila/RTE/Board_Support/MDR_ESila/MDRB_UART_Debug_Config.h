#ifndef _MDRB_UART_DBG_CONFIG_H
#define _MDRB_UART_DBG_CONFIG_H

#include <MDRB_BoardSelect.h>
#include <stdio.h>


//======================  Выбор пинов ======================
#if defined(USE_BOARD_VE1) || defined(USE_BOARD_VE3)
  //  см. MDRB_1986VE1.h  / MDRB_1986VE3.h
  #if UART_DEBUG_IND == 1
    #define CFG_UART_DBG      MDR_UART1ex
  
    #define CFG_PIN_TX_UART  {.portGPIO = MDRB_UART1_TX_PC3_Port, .pinIndex = MDRB_UART1_TX_PC3_Ind, .pinFunc = MDRB_UART1_TX_PC3_Func}
    #define CFG_PIN_RX_UART  {.portGPIO = MDRB_UART1_RX_PC4_Port, .pinIndex = MDRB_UART1_RX_PC4_Ind, .pinFunc = MDRB_UART1_RX_PC4_Func}    
    

  #elif UART_DEBUG_IND == 2
    #define CFG_UART_DBG      MDR_UART2ex
                                       
    #define CFG_PIN_TX_UART  {.portGPIO = MDRB_UART2_TX_PD13_Port, .pinIndex = MDRB_UART2_TX_PD13_Ind, .pinFunc = MDRB_UART2_TX_PD13_Func}
    #define CFG_PIN_RX_UART  {.portGPIO = MDRB_UART2_RX_PD14_Port, .pinIndex = MDRB_UART2_RX_PD14_Ind, .pinFunc = MDRB_UART2_RX_PD14_Func}
  #endif

    
#elif defined(USE_BOARD_VE91) || defined(USE_BOARD_VE94)
  //  см. MDRB_1986VE91.h
  #define CFG_UART_DBG      MDR_UART2ex

  #define CFG_PIN_TX_UART  {.portGPIO = MDRB_UART2_TX_PF1_Port, MDRB_UART2_TX_PF1_Ind, MDRB_UART2_TX_PF1_Func};
  #define CFG_PIN_RX_UART  {.portGPIO = MDRB_UART2_RX_PF0_Port, MDRB_UART2_RX_PF0_Ind, MDRB_UART2_RX_PF0_Func};
  
#elif defined(USE_BOARD_BASIS)
  //  см. MDRB_Basis_v2.h
  #define CFG_UART_DBG      MDR_UART2ex

  #define CFG_PIN_TX_UART  {.portGPIO = MDRB_UART2_TX_PD1_Port, MDRB_UART2_TX_PD1_Ind, MDRB_UART2_TX_PD1_Func};
  #define CFG_PIN_RX_UART  {.portGPIO = MDRB_UART2_RX_PD0_Port, MDRB_UART2_RX_PD0_Ind, MDRB_UART2_RX_PD0_Func};  
  
#elif defined(USE_BOARD_VE92)
  //  см. MDRB_1986VE92.h
  #define CFG_UART_DBG      MDR_UART2ex

  #define CFG_PIN_TX_UART  {.portGPIO = MDRB_UART2_TX_PF1_Port, MDRB_UART2_TX_PF1_Ind, MDRB_UART2_TX_PF1_Func};
  #define CFG_PIN_RX_UART  {.portGPIO = MDRB_UART2_RX_PF0_Port, MDRB_UART2_RX_PF0_Ind, MDRB_UART2_RX_PF0_Func};
  
#elif defined(USE_BOARD_VE93)
  //  см. MDRB_1986VE93.h
  #define CFG_UART_DBG      MDR_UART1ex

  #define CFG_PIN_TX_UART  {.portGPIO = MDRB_UART1_TX_PB5_Port, MDRB_UART1_TX_PB5_Ind, MDRB_UART1_TX_PB5_Func};
  #define CFG_PIN_RX_UART  {.portGPIO = MDRB_UART1_RX_PB6_Port, MDRB_UART1_RX_PB6_Ind, MDRB_UART1_RX_PB6_Func};
  
#elif defined(USE_BOARD_VC1)
  //  см. MDRB_1901VС1.h
  #define CFG_UART_DBG      MDR_UART3ex

  #define CFG_PIN_TX_UART  {.portGPIO = MDRB_UART3_TX_PF1_Port, MDRB_UART3_TX_PF1_Ind, MDRB_UART3_TX_PF1_Func};
  #define CFG_PIN_RX_UART  {.portGPIO = MDRB_UART3_RX_PF0_Port, MDRB_UART3_RX_PF0_Ind, MDRB_UART3_RX_PF0_Func};                                      

#elif defined (USE_MDR1986VE4) || defined (USE_MDR1986VK214) || defined (USE_MDR1986VK234)
  //  см. MDRB_1986VE4.h / MDRB_1986VK214.h / MDRB_1986VK234.h
  #define CFG_UART_DBG      MDR_UART1ex

  #define CFG_PIN_TX_UART  {.portGPIO = MDRB_UART1_TX_PB0_Port, MDRB_UART1_TX_PB0_Ind, MDRB_UART1_TX_PB0_Func};
  #define CFG_PIN_RX_UART  {.portGPIO = MDRB_UART1_RX_PB1_Port, MDRB_UART1_RX_PB1_Ind, MDRB_UART1_RX_PB1_Func};    

#elif defined(USE_BOARD_VE8)
  //  см. MDRB_1986VE8.h
  #define CFG_UART_DBG      MDR_UART1ex

  #define CFG_PIN_TX_UART  {.portGPIO = MDRB_UART1_TX_PE15_Port, MDRB_UART1_TX_PE15_Ind, MDRB_UART1_TX_PE15_Func};
  #define CFG_PIN_RX_UART  {.portGPIO = MDRB_UART1_RX_PE16_Port, MDRB_UART1_RX_PE16_Ind, MDRB_UART1_RX_PE16_Func};
    
#elif defined(USE_BOARD_VK014)
  //  см. MDRB_1986VE8.h
  #define CFG_UART_DBG      MDR_UART1ex

  #define CFG_PIN_TX_UART  {.portGPIO = MDRB_UART1_TX_PE15_Port, MDRB_UART1_TX_PE15_Ind, MDRB_UART1_TX_PE15_Func};
  #define CFG_PIN_RX_UART  {.portGPIO = MDRB_UART1_RX_PE16_Port, MDRB_UART1_RX_PE16_Ind, MDRB_UART1_RX_PE16_Func};  
  
#elif defined(USE_MLDR_155)
  //  см. MDRB_ESila.h
  #define CFG_UART_DBG      MDR_UART1ex

  #define CFG_PIN_TX_UART  {.portGPIO = MDRB_UART1_TX_PB1_Port, MDRB_UART1_TX_PB1_Ind, MDRB_UART1_TX_PB1_Func};
  #define CFG_PIN_RX_UART  {.portGPIO = MDRB_UART1_RX_PB0_Port, MDRB_UART1_RX_PB0_Ind, MDRB_UART1_RX_PB0_Func};    
  
#elif defined(USE_BOARD_ESila)
  //  см. MDRB_ESila.h
  #define CFG_UART_DBG      MDR_UART1ex

  #define CFG_PIN_TX_UART  {.portGPIO = MDRB_UART1_TX_PB1_Port, MDRB_UART1_TX_PB1_Ind, MDRB_UART1_TX_PB1_Func};
  #define CFG_PIN_RX_UART  {.portGPIO = MDRB_UART1_RX_PB0_Port, MDRB_UART1_RX_PB0_Ind, MDRB_UART1_RX_PB0_Func};      
#endif

  
#define CFG_UART_DBG_DEF_EX(opt, irq)  { .cfgBase.WordLength    = MDR_UART_WordLen8,  \
                                          .cfgBase.Parity        = UART_Parity_Off,    \
                                          .cfgBase.useFIFO       = MDR_On,             \
                                          .cfgBase.Options.Value = opt,                \
                                          .pCfgIRQ     = irq,                          \
                                          .pCfgDMA     = NULL,                         \
                                          .pCfgIrDA    = NULL,                         \
                                          .pCfgModem  = NULL                          \
                                          }


#define CFG_UART_DBG_DEF       CFG_UART_DBG_DEF_EX(0, NULL)  
  


#endif // _MDRB_UART_DBG_CONFIG_H

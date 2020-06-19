#ifndef _MDRB_UART_PINSELECT_H
#define _MDRB_UART_PINSELECT_H

#include <MDR_UART.h>
#include <MDRB_BoardSelect.h>


//======================  Доступные наборы пинов для плат ======================
#if   defined(USE_BOARD_VE1)
  //  см. MDRB_1986VE1.h
  extern const MDR_UART_CfgPinGPIO _pinTX_UART1;
  extern const MDR_UART_CfgPinGPIO _pinRX_UART1;
                                                                           
  extern const MDR_UART_CfgPinGPIO _pinTX_UART2;
  extern const MDR_UART_CfgPinGPIO _pinRX_UART2;  
  
                                       
#elif defined(USE_BOARD_VE3)
  //  см. MDRB_1986VE3.h
  extern const MDR_UART_CfgPinGPIO _pinTX_UART1;
  extern const MDR_UART_CfgPinGPIO _pinRX_UART1;
                                                                           
  extern const MDR_UART_CfgPinGPIO _pinTX_UART2;
  extern const MDR_UART_CfgPinGPIO _pinRX_UART2;


#elif defined(USE_BOARD_VE91) || defined(USE_BOARD_VE94)
  //  см. MDRB_1986VE91.h
  extern const MDR_UART_CfgPinGPIO _pinTX_UART2;
  extern const MDR_UART_CfgPinGPIO _pinRX_UART2;
    
  
#elif defined(USE_BOARD_VE92)
  //  см. MDRB_1986VE92.h
  extern const MDR_UART_CfgPinGPIO _pinTX_UART2;
  extern const MDR_UART_CfgPinGPIO _pinRX_UART2;
  
  
#elif defined(USE_BOARD_VE93)
  //  см. MDRB_1986VE93.h
  extern const MDR_UART_CfgPinGPIO _pinTX_UART1;
  extern const MDR_UART_CfgPinGPIO _pinRX_UART1;  

  
#elif defined(USE_BOARD_VC1)
  //  см. MDRB_1901VС1.h
  extern const MDR_UART_CfgPinGPIO _pinTX_UART3;
  extern const MDR_UART_CfgPinGPIO _pinRX_UART3;

  
#elif defined (USE_MDR1986VE4) || defined (USE_MDR1986VK214) || defined (USE_MDR1986VK234)
  //  см. MDRB_1986VE4.h / MDRB_1986VK214.h / MDRB_1986VK234.h  
  extern const MDR_UART_CfgPinGPIO _pinTX_UART1;
  extern const MDR_UART_CfgPinGPIO _pinRX_UART1;    
                                                                           
  extern const MDR_UART_CfgPinGPIO _pinTX_UART2;
  extern const MDR_UART_CfgPinGPIO _pinRX_UART2;

#elif defined(USE_BOARD_VE8)
  //  см. MDRB_1986VE8.h  
  extern const MDR_UART_CfgPinGPIO _pinTX_UART1;
  extern const MDR_UART_CfgPinGPIO _pinRX_UART1;
    
#elif defined(USE_BOARD_VK014)
  //  см. MDRB_1986VE8.h
  extern const MDR_UART_CfgPinGPIO _pinTX_UART1;
  extern const MDR_UART_CfgPinGPIO _pinRX_UART1;  
  
#elif defined(USE_BOARD_ESila)
  //  см. MDRB_ESila.h
  extern const MDR_UART_CfgPinGPIO _pinTX_UART1;
  extern const MDR_UART_CfgPinGPIO _pinRX_UART1; 

#endif

//======================  Выбор пинов для плат по умолчанию ======================
#if defined(USE_BOARD_VE1) || defined(USE_BOARD_VE3)
  //  см. MDRB_1986VE1.h  / MDRB_1986VE3.h
  #if UART_DEBUG_IND == 1  
    #define MDRB_UART_PinTX     _pinTX_UART1
    #define MDRB_UART_PinRX     _pinRX_UART1
                                     
  #elif UART_DEBUG_IND == 2                                       
    #define  MDRB_UART_PinTX    _pinTX_UART2
    #define  MDRB_UART_PinRX    _pinRX_UART2
  #endif

#elif defined(USE_BOARD_VE91) || defined(USE_BOARD_VE94)
  //  см. MDRB_1986VE91.h
  #define  MDRB_UART_PinTX    _pinTX_UART2
  #define  MDRB_UART_PinRX    _pinRX_UART2
    
#elif defined(USE_BOARD_BASIS)
  //  см. MDRB_Basis_v2.h
  #define  MDRB_UART_PinTX    _pinTX_UART2
  #define  MDRB_UART_PinRX    _pinRX_UART2
  
#elif defined(USE_BOARD_VE92)
  //  см. MDRB_1986VE92.h
  #define  MDRB_UART_PinTX    _pinTX_UART2
  #define  MDRB_UART_PinRX    _pinRX_UART2
    
#elif defined(USE_BOARD_VE93)
  //  см. MDRB_1986VE93.h
  #define  MDRB_UART_PinTX    _pinTX_UART1
  #define  MDRB_UART_PinRX    _pinRX_UART1
  
#elif defined(USE_BOARD_VC1)
  //  см. MDRB_1901VС1.h
  #define  MDRB_UART_PinTX    _pinTX_UART3
  #define  MDRB_UART_PinRX    _pinRX_UART3
  
#elif defined (USE_MDR1986VE4) || defined (USE_MDR1986VK214) || defined (USE_MDR1986VK234)
  //  см. MDRB_1986VE4.h / MDRB_1986VK214.h / MDRB_1986VK234.h
  #define  MDRB_UART_PinTX    _pinTX_UART1
  #define  MDRB_UART_PinRX    _pinRX_UART1

#elif defined(USE_BOARD_VE8)
  //  см. MDRB_1986VE8.h
  #define  MDRB_UART_PinTX    _pinTX_UART1
  #define  MDRB_UART_PinRX    _pinRX_UART1
    
#elif defined(USE_BOARD_VK014)
  //  см. MDRB_1986VE8.h
  #define  MDRB_UART_PinTX    _pinTX_UART1
  #define  MDRB_UART_PinRX    _pinRX_UART1
  
#elif defined(USE_MLDR_155)
  //  см. MDRB_ESila.h
  #define  MDRB_UART_PinTX    _pinTX_UART1
  #define  MDRB_UART_PinRX    _pinRX_UART1
  
#elif defined(USE_BOARD_ESila)
  //  см. MDRB_ESila.h
  #define  MDRB_UART_PinTX    _pinTX_UART1
  #define  MDRB_UART_PinRX    _pinRX_UART1
    
#endif


#endif  //_MDRB_UART_PINSELECT_H


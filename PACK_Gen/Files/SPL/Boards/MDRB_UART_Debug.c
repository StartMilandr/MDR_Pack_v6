#include "MDRB_UART_Debug.h"

#include <stdio.h>

//======================  Выбор пинов ======================
#if defined(USE_BOARD_VE1) || defined(USE_BOARD_VE3)
  //  см. MDRB_1986VE1.h  / MDRB_1986VE3.h
  #if UART_DEBUG_IND == 1
    const MDR_UART_TypeEx * UART_DBG = MDR_UART1ex;
  
    static const MDR_UART_CfgPinGPIO _pinTX_UART = {MDRB_UART1_TX_PC3_Port, MDRB_UART1_TX_PC3_Ind, MDRB_UART1_TX_PC3_Func};
    static const MDR_UART_CfgPinGPIO _pinRX_UART = {MDRB_UART1_RX_PC4_Port, MDRB_UART1_RX_PC4_Ind, MDRB_UART1_RX_PC4_Func};    
                                     
  #elif UART_DEBUG_IND == 2
    const MDR_UART_TypeEx * UART_DBG = MDR_UART2ex;
                                       
    static const MDR_UART_CfgPinGPIO _pinTX_UART = {MDRB_UART2_TX_PD13_Port, MDRB_UART2_TX_PD13_Ind, MDRB_UART2_TX_PD13_Func};
    static const MDR_UART_CfgPinGPIO _pinRX_UART = {MDRB_UART2_RX_PD14_Port, MDRB_UART2_RX_PD14_Ind, MDRB_UART2_RX_PD14_Func};  
  #endif

    
#elif defined(USE_BOARD_VE91) || defined(USE_BOARD_VE94)
  //  см. MDRB_1986VE91.h
  const MDR_UART_TypeEx * UART_DBG = MDR_UART2ex;

  static const MDR_UART_CfgPinGPIO _pinTX_UART = {MDRB_UART2_TX_PF1_Port, MDRB_UART2_TX_PF1_Ind, MDRB_UART2_TX_PF1_Func};
  static const MDR_UART_CfgPinGPIO _pinRX_UART = {MDRB_UART2_RX_PF0_Port, MDRB_UART2_RX_PF0_Ind, MDRB_UART2_RX_PF0_Func};

  
#elif defined(USE_BOARD_VE92)
  //  см. MDRB_1986VE92.h
  const MDR_UART_TypeEx * UART_DBG = MDR_UART2ex;

  static const MDR_UART_CfgPinGPIO _pinTX_UART = {MDRB_UART2_TX_PF1_Port, MDRB_UART2_TX_PF1_Ind, MDRB_UART2_TX_PF1_Func};
  static const MDR_UART_CfgPinGPIO _pinRX_UART = {MDRB_UART2_RX_PF0_Port, MDRB_UART2_RX_PF0_Ind, MDRB_UART2_RX_PF0_Func};

  
#elif defined(USE_BOARD_VE93)
  //  см. MDRB_1986VE93.h
  const MDR_UART_TypeEx * UART_DBG = MDR_UART1ex;

  static const MDR_UART_CfgPinGPIO _pinTX_UART = {MDRB_UART1_TX_PB5_Port, MDRB_UART1_TX_PB5_Ind, MDRB_UART1_TX_PB5_Func};
  static const MDR_UART_CfgPinGPIO _pinRX_UART = {MDRB_UART1_RX_PB6_Port, MDRB_UART1_RX_PB6_Ind, MDRB_UART1_RX_PB6_Func};

  
#elif defined(USE_BOARD_VC1)
  //  см. MDRB_1901VС1.h
  const MDR_UART_TypeEx * UART_DBG = MDR_UART3ex;

  static const MDR_UART_CfgPinGPIO _pinTX_UART = {MDRB_UART3_TX_PF1_Port, MDRB_UART3_TX_PF1_Ind, MDRB_UART3_TX_PF1_Func};
  static const MDR_UART_CfgPinGPIO _pinRX_UART = {MDRB_UART3_RX_PF0_Port, MDRB_UART3_RX_PF0_Ind, MDRB_UART3_RX_PF0_Func};
                                       

#elif defined (USE_MDR1986VE4) || defined (USE_MDR1986VK214) || defined (USE_MDR1986VK234)
  //  см. MDRB_1986VE4.h / MDRB_1986VK214.h / MDRB_1986VK234.h
//  #if UART_DEBUG_IND == 1
    const MDR_UART_TypeEx * UART_DBG = MDR_UART1ex;
  
    static const MDR_UART_CfgPinGPIO _pinTX_UART = {MDRB_UART1_TX_PB0_Port, MDRB_UART1_TX_PB0_Ind, MDRB_UART1_TX_PB0_Func};
    static const MDR_UART_CfgPinGPIO _pinRX_UART = {MDRB_UART1_RX_PB1_Port, MDRB_UART1_RX_PB1_Ind, MDRB_UART1_RX_PB1_Func};    
                                     
//  #elif UART_DEBUG_IND == 2
//    const MDR_UART_TypeEx * UART_DBG = MDR_UART1ex;
//                                       
//    static const MDR_UART_CfgPinGPIO _pinTX_UART = {MDRB_UART2_TX_PC0_Port, MDRB_UART2_TX_PC0_Ind, MDRB_UART2_TX_PC0_Func};
//    static const MDR_UART_CfgPinGPIO _pinRX_UART = {MDRB_UART2_RX_PC1_Port, MDRB_UART2_RX_PC1_Ind, MDRB_UART2_RX_PC1_Func};
//  #endif
    
#endif
   
void MDR_UART_DBG_Init(void)
{
  MDR_UART_DBG_InitEx(UART_DEBUG_BAUD_DEF, false);
}

//  Настройки блока
static MDR_UART_Cfg _cfgUART = {
  //  Main Settings
  .cfgBase.WordLength    = UART_BITS_8,
  .cfgBase.Parity        = UART_Parity_Off,
  .cfgBase.useFIFO       = MDR_On,
  //  Some Options, инициализировать нулем если опции не нужны
  .cfgBase.Options.Value = MDR_UART_OPT_DisRX,  
  //  IRQ Disabled
  .pCfgIRQ = NULL,
  //  DMA Disabled
  .pCfgDMA = NULL,
  //  IrDA Disabled
  .pCfgIrDA = NULL,
  //  Modem Disabled
  .pCfgModem  = NULL
};

static MDR_UART_CfgEx _cfgUartEx = {
  //  Делитель частоты для Uart_Clock
  .ClockBRG = MDR_BRG_div1,
  //  Настройки блока
  .pCfgUART = &_cfgUART,  
  //  Инициализация прерываний в NVIC
  .priorityIRQ = 0,
  .activateNVIC_IRQ = false
};

void MDR_UART_DBG_InitEx(uint32_t baudRate, bool RX_Enable)
{
  uint32_t UART_ClockHz;
  MDR_UART_cfgBaud cfgBaud;
  MDR_UART_CfgPinsGPIO pinsGPIO;

#ifdef MDR_PER_CLOCK_SELF_TIM_UART_SSP  
//  #if UART_DEBUG_IND == 1  
    MDR_SetClock_Uart1(MDR_PER_PLLCPUo);
//  #elif UART_DEBUG_IND == 2
//    MDR_SetClock_Uart2(MDR_PER_PLLCPUo);
//  #endif
#elif defined (MDR_TIM_CLOCK_FROM_PER_CLOCK)
  MDR_SetClock_UartTimSSP(MDR_PER_PLLCPUo);
#endif  
  
  //  Baud Rate
  UART_ClockHz = MDR_UARTex_GetUartClockHz(UART_DBG);  
  MDR_UART_CalcBaudRate(&cfgBaud, baudRate, UART_ClockHz);
  
  //  Uart Init
  if (!RX_Enable)
    MDR_UARTex_InitByBaud(UART_DBG, &_cfgUartEx, &cfgBaud);
  else
  {
    MDR_UART_Cfg cfgUART = _cfgUART;
    MDR_UART_CfgEx cfgUartEx = _cfgUartEx;
    
    cfgUART.cfgBase.Options.Value = 0;
    cfgUartEx.pCfgUART = &cfgUART;
    
    MDR_UARTex_InitByBaud(UART_DBG, &cfgUartEx, &cfgBaud);
  }

  //  Init Pins
  pinsGPIO.pPinTX = &_pinTX_UART;
  if (RX_Enable)
    pinsGPIO.pPinRX = &_pinRX_UART;
  else
    pinsGPIO.pPinRX = NULL;
  MDR_UART_InitPinsGPIO(&pinsGPIO, MDR_PIN_FAST);
  
#if UART_DEBUG_SHOW_WELLCOME    
  float baudError = MDR_UART_CalcBaudError(&cfgBaud, baudRate, UART_ClockHz);
  //  Wellcome
  printf("Wellcome to UART DebugOut!\n");
  printf("BaudRate: %d\n",  baudRate);
  printf("BaudError: %f\n", baudError);
#endif
}

void MDR_UART_DBG_Finit(void)
{
  MDR_UARTex_DeInit(UART_DBG);
}

void MDR_UART_DBG_ChangeRate(uint32_t baudRate)
{
  uint32_t UART_ClockHz;
  MDR_UART_cfgBaud cfgBaud;

  //  Baud Rate
  UART_ClockHz = MDR_UARTex_GetUartClockHz(UART_DBG);  
  MDR_UART_CalcBaudRate(&cfgBaud, baudRate, UART_ClockHz);
  
#if UART_DEBUG_SHOW_WELLCOME
  float baudError = MDR_UART_CalcBaudError(&cfgBaud, baudRate, UART_ClockHz);
  
  //  Message 
  printf("BaudRate Changed: %d\n",  baudRate);
  printf("BaudError: %f\n", baudError);  
  
#endif
  
  MDR_UART_ChangeRateEx(UART_DBG->UARTx, &cfgBaud);    
}


struct __FILE
{
  int handle;
  /* Whatever you require here. If the only file you are using is */
  /* standard output using printf() for debugging, no file handling */
  /* is required. */
};

/* FILE is typedef’d in stdio.h. */
FILE __stdout;

int fputc(int ch, FILE *f)
{ 
  while(!MDR_UART_CanSend(UART_DBG->UARTx));
  MDR_UART_SendData(UART_DBG->UARTx, ch);
  
  return ch;
}
int ferror(FILE *f)
{
  /* Your implementation of ferror(). */
  return 0;
}

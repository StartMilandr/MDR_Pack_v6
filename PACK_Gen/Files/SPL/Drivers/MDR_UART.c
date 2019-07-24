#include <MDR_UART.h>

#include <MDR_Funcs.h>

const MDR_UART_TypeEx _MDR_UART1ex = {
  .UARTx = MDR_UART1,
  //  UartClock Enable
  .CfgClock.ClockEna_Addr = MDR_UART1_CLK_EN_ADDR,
  .CfgClock.ClockEna_Mask = MDR_UART1_CLK_EN_MSK,
  //  UartClock Gate On and BRG
  .CfgClock.ClockGate_Addr        = MDR_UART1_CLOCK_GATE_ADDR,
#ifndef MDR_CLK_LIKE_VE8  
  .CfgClock.ClockGate_ClockOn_Msk = MDR_UART1_CLOCK_GATE_ENA_MSK,
  .CfgClock.ClockGate_BRG_Pos     = MDR_UART1_CLOCK_GATE_BRG_POS,
#endif
   //  NVIC
  .UARTx_IRQn       = UART1_IRQn
};

const MDR_UART_TypeEx _MDR_UART2ex = {
  .UARTx = MDR_UART2,
  //  UartClock Enable
  .CfgClock.ClockEna_Addr = MDR_UART2_CLK_EN_ADDR,
  .CfgClock.ClockEna_Mask = MDR_UART2_CLK_EN_MSK,
  //  UartClock Gate On and BRG
  .CfgClock.ClockGate_Addr        = MDR_UART2_CLOCK_GATE_ADDR,
#ifndef MDR_CLK_LIKE_VE8  
  .CfgClock.ClockGate_ClockOn_Msk = MDR_UART2_CLOCK_GATE_ENA_MSK,
  .CfgClock.ClockGate_BRG_Pos     = MDR_UART2_CLOCK_GATE_BRG_POS,
#endif
   //  NVIC
  .UARTx_IRQn = UART2_IRQn
};

#ifdef MDR_UART3
  const MDR_UART_TypeEx _MDR_UART3ex = {
    .UARTx = MDR_UART3,
    //  UartClock Enable
    .CfgClock.ClockEna_Addr = MDR_UART3_CLK_EN_ADDR,
    .CfgClock.ClockEna_Mask = MDR_UART3_CLK_EN_MSK,
    //  UartClock Gate On and BRG
    .CfgClock.ClockGate_Addr        = MDR_UART3_CLOCK_GATE_ADDR,
#ifndef MDR_CLK_LIKE_VE8      
    .CfgClock.ClockGate_ClockOn_Msk = MDR_UART3_CLOCK_GATE_ENA_MSK,
    .CfgClock.ClockGate_BRG_Pos     = MDR_UART3_CLOCK_GATE_BRG_POS,
#endif
     //  NVIC
    .UARTx_IRQn = UART3_IRQn
  };
#endif

#ifdef MDR_UART4
  const MDR_UART_TypeEx _MDR_UART4ex = {
    .UARTx = MDR_UART4,
    //  UartClock Enable
    .CfgClock.ClockEna_Addr = MDR_UART4_CLK_EN_ADDR,
    .CfgClock.ClockEna_Mask = MDR_UART4_CLK_EN_MSK,
    //  UartClock Gate On and BRG
    .CfgClock.ClockGate_Addr        = MDR_UART4_CLOCK_GATE_ADDR,
#ifndef MDR_CLK_LIKE_VE8      
    .CfgClock.ClockGate_ClockOn_Msk = MDR_UART4_CLOCK_GATE_ENA_MSK,
    .CfgClock.ClockGate_BRG_Pos     = MDR_UART4_CLOCK_GATE_BRG_POS,
     //  NVIC
    .UARTx_IRQn = UART34_IRQn
#else    
    .UARTx_IRQn = UART4_IRQn
#endif
  };
#endif


//  Рассчет делителей cfgBaud для получения необходимой baudRate. 
void  MDR_UART_CalcBaudRate(MDR_UART_cfgBaud *cfgBaud, uint32_t baudRate, uint32_t UART_ClockHz)
{
  //     div = Fuart / (16 * Fbaud)
  // div_x64 = Fuart / (Fbaud / 4)
  uint32_t div_x64 = UART_ClockHz / (baudRate >> 2); 
  
	cfgBaud->BaudDivInt  = (uint16_t)div_x64 >> 6;
	cfgBaud->BaudDivFrac = (uint16_t)(div_x64 & 0x003FUL);  
}

//  Возвращает ошибку в % между реальной и заданной частотой.
double MDR_UART_CalcBaudError(const MDR_UART_cfgBaud *cfgBaud, uint32_t baudRate, uint32_t UART_ClockHz)
{
  //  Fbaud = Fuart / (16 * div)
  //  Fbaud = Fuart * 4 / div_x64
  uint32_t baudReal = (UART_ClockHz << 2) / ((cfgBaud->BaudDivInt * 64) + cfgBaud->BaudDivFrac);
  
  return ((baudReal - baudRate) * 100) / (double)baudRate;
}

//  Инициализация блока с высчитыванием cfgBaud по входным параметрам.
void MDR_UART_Init(MDR_UART_Type *UART, const MDR_UART_Cfg *cfg, uint32_t baudRate, uint32_t UART_ClockHz)
{
  MDR_UART_cfgBaud cfgBaud;
  
  MDR_UART_CalcBaudRate(&cfgBaud, baudRate, UART_ClockHz);
  MDR_UART_InitByBaud(UART, cfg, &cfgBaud);  
}

//  Аналог MDR_UART_Init, но с проверкой ошибки выставления baudRate
//  При превышении ошибки BaudErrMax функция вернет Fault, блок не будет инициализирован
bool MDR_UART_InitEx(MDR_UART_Type *UART, const MDR_UART_Cfg *cfg, uint32_t baudRate, uint32_t UART_ClockHz, double baudErrMax)
{
  bool result;
  MDR_UART_cfgBaud cfgBaud;
  
  MDR_UART_CalcBaudRate(&cfgBaud, baudRate, UART_ClockHz);
  result = MDR_UART_CalcBaudError(&cfgBaud, baudRate, UART_ClockHz) < baudErrMax;  
  if (result)
    MDR_UART_InitByBaud(UART, cfg, &cfgBaud);
  
  return result;
}

//  Деинициализация блока
void MDR_UART_DeInit(MDR_UART_Type *UART)
{
  MDR_UART_ClearRegs(UART);
}

//  Функции, полезные при регистровой настройке
void MDR_UART_ClearRegs(MDR_UART_Type *UART)
{
  //  Disable
  UART->CR = 0;
    
  //  Write Line Control
  UART->IBRD  = 0;
  UART->FBRD  = 0;
  UART->LCR_H = 0;
  
  //  Settings
  UART->ILPR  = 0;
  UART->IFLS  = 0;
  UART->IMSC  = 0;
  UART->DMACR = 0;

  //  Clear Flags
  UART->ICR = MDR_UART_EVENT_ClearAll;
}

//==================    CfgRegs - выборка только конфигурационных регистров ===============

//  Делители cfgBaud задаются вручную, рассчитываются пользователем заранее
void MDR_UART_InitByBaud(MDR_UART_Type *UART, const MDR_UART_Cfg *cfg, const MDR_UART_cfgBaud *cfgBaud)  
{
  MDR_UART_CfgRegs pCfgRegs;
  
  MDR_UART_CfgRegs_Clear(&pCfgRegs);
  MDR_UART_ToCfgRegs(cfg, cfgBaud, &pCfgRegs);
  
  MDR_UART_Init_ByCfgRegs(UART, &pCfgRegs);
}  


static const uint32_t _ParityToBits[] = {                                     // MDR_UART_Parity ENUM:
  0                                                                           //   UART_Parity_Off,
  , MDR_UART_LCR_H_PEN_Msk                                                    //   UART_Parity_Odd,
  , MDR_UART_LCR_H_PEN_Msk | MDR_UART_LCR_H_EPS_Msk                           //   UART_Parity_Even,
  , MDR_UART_LCR_H_PEN_Msk                          | MDR_UART_LCR_H_SPS_Msk  //   UART_Parity_1,
  , MDR_UART_LCR_H_PEN_Msk | MDR_UART_LCR_H_EPS_Msk | MDR_UART_LCR_H_SPS_Msk  //   UART_Parity_0
};

void MDR_UART_ToCfgRegs(const MDR_UART_Cfg *cfg, const MDR_UART_cfgBaud *cfgBaud, MDR_UART_CfgRegs *pCfgRegs)
{ 
  //  BaudRate
  pCfgRegs->IBRD = VAL2FLD(cfgBaud->BaudDivInt,  MDR_UART_IBRD_Baud_DivInt);  
  pCfgRegs->FBRD = VAL2FLD(cfgBaud->BaudDivFrac, MDR_UART_FBRD_Baud_DivFrac);
  
  // Enable All
  pCfgRegs->CR = MDR_UART_CR_TXE_Msk | MDR_UART_CR_RXE_Msk | MDR_UART_CR_EN_Msk;
  //  Main Settings
  pCfgRegs->LCR_H =  VAL2FLD_Pos(cfg->cfgBase.WordLength, MDR_UART_LCR_H_WLEN_Pos)
                   | VAL2FLD_Pos(cfg->cfgBase.useFIFO,    MDR_UART_LCR_H_FEN_Pos)
                   | _ParityToBits[(uint32_t) cfg->cfgBase.Parity];  
  
  //  Base Options
  if (cfg->cfgBase.Options.Value != 0)
  {
    //  Break and Stop2 Bits
    pCfgRegs->LCR_H |= (cfg->cfgBase.Options.Value & UART_SEL_BKR_STOP2);
    //  Disable Tx Rx
    if (cfg->cfgBase.Options.Value & MDR_UART_OPT_DisTX)
      pCfgRegs->CR &= ~MDR_UART_CR_TXE_Msk;
    if (cfg->cfgBase.Options.Value & MDR_UART_OPT_DisRX)
      pCfgRegs->CR &= ~MDR_UART_CR_RXE_Msk;
    //  Two Stop bits
    if (cfg->cfgBase.Options.Value & MDR_UART_OPT_LBM)
      pCfgRegs->CR |= MDR_UART_CR_LBE_Msk;
  }
    
  if (cfg->pCfgIRQ != NULL)
  {
    pCfgRegs->IMSC  = cfg->pCfgIRQ->SelEventIRQ.Value;
    pCfgRegs->IFLS  =  VAL2FLD(cfg->pCfgIRQ->Rx_FIFO_Event, MDR_UART_IFLS_RXIFLSES)
                     | VAL2FLD(cfg->pCfgIRQ->Tx_FIFO_Event, MDR_UART_IFLS_TXIFLSES);
  }   
  if (cfg->pCfgIrDA != NULL)
  {
    pCfgRegs->CR  |= MDR_UART_CR_EN_Msk | VAL2FLD_Pos(cfg->pCfgIrDA->LowPower, MDR_UART_CR_SIRLP_Pos);
    pCfgRegs->ILPR = VAL2FLD(cfg->pCfgIrDA->DivSampleRate, MDR_UART_ILPR_DVSR);
  }
  
  if (cfg->pCfgModem != NULL)
    pCfgRegs->CR |= VAL2FLD_Pos(cfg->pCfgModem->Value, MDR_UART_CR_DTR_Pos);
  
  if (cfg->pCfgDMA != NULL)
    pCfgRegs->DMACR = cfg->pCfgDMA->Value;
}


void MDR_UART_Init_ByCfgRegs(MDR_UART_Type *UART, MDR_UART_CfgRegs *pCfgRegs)
{  
  MDR_UART_CfgRegs_Apply(UART, pCfgRegs);
}

void MDR_UART_CfgRegs_Read(MDR_UART_Type *UART, MDR_UART_CfgRegs *pCfgRegs)
{
  pCfgRegs->ILPR  = UART->ILPR;
  pCfgRegs->IBRD  = UART->IBRD;
  pCfgRegs->FBRD  = UART->FBRD;
  pCfgRegs->LCR_H = UART->LCR_H;
  pCfgRegs->CR    = UART->CR;
  pCfgRegs->IFLS  = UART->IFLS;
  pCfgRegs->IMSC  = UART->IMSC;
  pCfgRegs->DMACR = UART->DMACR;
}

void MDR_UART_CfgRegs_Apply(MDR_UART_Type *UART, MDR_UART_CfgRegs *pCfgRegs)
{ 
  //  Write Line Control
  UART->IBRD  = pCfgRegs->IBRD;
  UART->FBRD  = pCfgRegs->FBRD;
  UART->LCR_H = pCfgRegs->LCR_H;
  
  //  Settings
  UART->ILPR  = pCfgRegs->ILPR;
  UART->IFLS  = pCfgRegs->IFLS;
  UART->IMSC  = pCfgRegs->IMSC;
  UART->DMACR = pCfgRegs->DMACR;
 
  //  Clear Flags
  UART->ICR = MDR_UART_EVENT_ClearAll;
  
  //  Settings and Enable
  UART->CR = pCfgRegs->CR;
}

void MDR_UART_CfgRegs_Clear(MDR_UART_CfgRegs *pCfgRegs)
{
  pCfgRegs->ILPR  = 0;
  pCfgRegs->IBRD  = 0;
  pCfgRegs->FBRD  = 0;
  pCfgRegs->LCR_H = 0;
  pCfgRegs->CR    = 0;
  pCfgRegs->IFLS  = 0;
  pCfgRegs->IMSC  = 0;
  pCfgRegs->DMACR = 0;
}


//===================   UART GPIO pins Init ==========================
void MDR_UART_InitPinsGPIO(const MDR_UART_CfgPinsGPIO *pinsCfg, MDR_PIN_PWR pinsPower)
{
  MDR_PinDig_PermRegs pinPermCfg;

#ifdef MDR_GPIO_HAS_GFEN_SCHMT  
  MDR_Port_InitDigGroupPinCfg(MDR_Off, pinsPower, MDR_Off, MDR_Off, &pinPermCfg);
#else
  MDR_Port_InitDigGroupPinCfg(MDR_Off, pinsPower, &pinPermCfg);  
#endif
  
  //  TX
  if (pinsCfg->pPinTX != NULL)
  {
    MDR_GPIO_Enable(pinsCfg->pPinTX->portGPIO);
    MDR_GPIO_InitDigPin(pinsCfg->pPinTX->portGPIO, pinsCfg->pPinTX->pinIndex, MDR_Pin_In, pinsCfg->pPinTX->pinFunc, &pinPermCfg);  
  }
  //  RX
  if (pinsCfg->pPinRX != NULL)
  {
    MDR_GPIO_Enable(pinsCfg->pPinRX->portGPIO);
    MDR_GPIO_InitDigPin(pinsCfg->pPinRX->portGPIO, pinsCfg->pPinRX->pinIndex, MDR_Pin_In, pinsCfg->pPinRX->pinFunc, &pinPermCfg);
  }
}


//==================    MDR_UART_TypeEx - Инициализация UART с тактированием и  прерваниями в NVIC  ===============

//  Возвращает частоту UART_CLOCK, определяется по значению ключей в схеме тактирования. 
//  Используется для подачи в функцию MDR_UART_Init, MDR_UART_AssignBaudRate и т.д.
//  Обычно частота задается в ПО, поэтому рациональней задать ее напрямую.
uint32_t  MDR_UARTex_GetUartClockHz(const MDR_UART_TypeEx *exUART, bool doUpdate)
{
  uint32_t regBRG; 
  uint32_t scrUartHz;

#if defined (MDR_PER_CLOCK_SELF_TIM_UART_SSP)
  //  VK214
  if (exUART == MDR_UART1ex)
    scrUartHz = MDR_GetFreqHz_UART1_C2();
  else
    scrUartHz = MDR_GetFreqHz_UART2_C2();

#elif defined (MDR_UART_CLOCK_FROM_PER_CLOCK)
  //  VK234, VE4
  scrUartHz = MDR_GetFreqHz_Per1_C2();    
   
#elif defined (MDR_CLK_LIKE_VE8)   
  // VE8
  MDR_PERCLK_ASYNC_REG regValue; 
  
  if (exUART == MDR_UART1ex)
    regValue.Value = REG32(_MDR_UART1ex.CfgClock.ClockGate_Addr); 
  else
    regValue.Value = REG32(_MDR_UART2ex.CfgClock.ClockGate_Addr);  
  scrUartHz = MDR_GetFreqHz_PerAsync(regValue, doUpdate);
  
#else  
  scrUartHz = MDR_CPU_GetFreqHz(doUpdate);
#endif  
  
  regBRG = REG32(exUART->CfgClock.ClockGate_Addr);    
#ifdef MDR_CLK_LIKE_VE8
  regBRG = FLD2VAL(regBRG, MDR_PER_CLK_DIV);
#else
  regBRG = (regBRG >> exUART->CfgClock.ClockGate_BRG_Pos) & MDR_RST_UART__UART1_BRG_Msk;
#endif
  
  scrUartHz = scrUartHz << regBRG;   
  return scrUartHz;
}

//  Инициализация блока с высчитыванием cfgBaud по входным параметрам.
void MDR_UARTex_Init(const MDR_UART_TypeEx *UARTex, const MDR_UART_CfgEx *cfgEx, uint32_t baudRate, uint32_t UART_ClockHz)
{
  MDR_UART_cfgBaud cfgBaud;
  
  MDR_UART_CalcBaudRate(&cfgBaud, baudRate, UART_ClockHz);
  MDR_UARTex_InitByBaud(UARTex, cfgEx, &cfgBaud);    
}

//  Аналог MDR_UART_Init, но с проверкой ошибки выставления BaudRate_Hz
//  При превышении ошибки BaudErrMax функция вернет Fault, блок не будет инициализирован
bool MDR_UARTex_InitEx(const MDR_UART_TypeEx *UARTex, const MDR_UART_CfgEx *cfgEx, uint32_t baudRate, uint32_t UART_ClockHz, double baudErrMax)
{
  bool result;
  MDR_UART_cfgBaud cfgBaud;
  
  MDR_UART_CalcBaudRate(&cfgBaud, baudRate, UART_ClockHz);
  result = MDR_UART_CalcBaudError(&cfgBaud, baudRate, UART_ClockHz) < baudErrMax;  
  if (result)
    MDR_UARTex_InitByBaud(UARTex, cfgEx, &cfgBaud);
  
  return result;
}

//  Делители cfgBaud задаются вручную, рассчитываются пользователем заранее
void MDR_UARTex_InitByBaud(const MDR_UART_TypeEx *UARTex, const MDR_UART_CfgEx *cfgEx, const MDR_UART_cfgBaud *cfgBaud)
{
  //  Включение тактирования блока
  MDR_PerClock_Enable(&UARTex->CfgClock);   
  
  //  Подача частоты
  MDR_PerClock_GateOpen(&UARTex->CfgClock, cfgEx->ClockBRG);
  //  Инициализация параметров UART
  MDR_UART_InitByBaud(UARTex->UARTx, cfgEx->pCfgUART, cfgBaud);
  //  Инициализация прерываний в NVIC, чтобы пользователь не забыл
  if (cfgEx->activateNVIC_IRQ)
  {
    NVIC_EnableIRQ(UARTex->UARTx_IRQn);
    NVIC_SetPriority(UARTex->UARTx_IRQn, cfgEx->priorityIRQ);
  }  
}

void MDR_UARTex_DeInit(const MDR_UART_TypeEx *UARTex)
{
  MDR_UART_DeInit(UARTex->UARTx);  
  
  MDR_PerClock_GateClose(&UARTex->CfgClock);  
  MDR_PerClock_Disable(&UARTex->CfgClock);
}


//==================    Функции работы с блоком UART ===============
void MDR_UART_ChangeRateEx(MDR_UART_Type *UART, const MDR_UART_cfgBaud *cfgBaud)
{
  uint32_t CR_tmp = UART->CR;
  uint32_t LCR_tmp = UART->LCR_H;
    
  //  Stop UART - Не работает!
  //UART->CR &= ~MDR_UART_CR_EN_Msk;  
  
  //  Wait active transfer completed
  while (UART->FR & MDR_UART_SFL_Busy); // wait BUSY
  
  //  Stop UART
  UART->CR &= ~MDR_UART_CR_EN_Msk;    
  
  //  Set New BaudRate and restore Enable
  UART->IBRD  = cfgBaud->BaudDivInt;
  UART->FBRD  = cfgBaud->BaudDivFrac;
  UART->LCR_H = LCR_tmp;
  UART->CR = CR_tmp; 
}

void MDR_UART_ChangeRate(MDR_UART_Type *UART, uint32_t baudRate, uint32_t UART_ClockHz)
{
  MDR_UART_cfgBaud cfgBaud;
  
  MDR_UART_CalcBaudRate(&cfgBaud, baudRate, UART_ClockHz);
  MDR_UART_ChangeRateEx(UART, &cfgBaud);
}

MDR_UART_Status MDR_UART_GetStatusEx(MDR_UART_Type *UART)
{
  MDR_UART_Status result;
  
  result.Value = UART->FR;
  return result;
}

MDR_UART_Data MDR_UART_ReadDataEx(MDR_UART_Type *UART) 
{
  MDR_UART_Data result;
  
  result.Value = (uint16_t)UART->DR;
  return result;
}

MDR_UART_EventFlags MDR_UART_GetEvents(MDR_UART_Type *UART) 
{
  MDR_UART_EventFlags result;
  
  result.Value = UART->RIS;
  return result;
}

// Разрешение/запрет прерываний
void MDR_UART_ChangeEventIRQ(MDR_UART_Type *UART, uint32_t eventsMask)
{
  uint32_t tmpCR = UART->CR;
  
  UART->CR &= ~MDR_UART_CR_EN_Msk;
  UART->IMSC = eventsMask;
  UART->CR = tmpCR;  
}

void MDR_UART_ChangeEventIRQEx(MDR_UART_Type *UART, MDR_UART_EventFlags selEventIRQ)
{
  MDR_UART_ChangeEventIRQ(UART, selEventIRQ.Value);
}

// Изменение уровней заполнения FIFO, при которых срабатывают флаги и прерывания (если разрешены)
void MDR_UART_ChangeEventTxFIFO(MDR_UART_Type *UART, MDR_UART_EventFIFO levelFIFO) 
{
  uint32_t tmpCR = UART->CR;
  
  UART->CR &= ~MDR_UART_CR_EN_Msk;  
  UART->IFLS = MDR_MaskClrSet(UART->IFLS, MDR_UART_IFLS_TXIFLSES_Msk, VAL2FLD_Pos(levelFIFO, MDR_UART_IFLS_TXIFLSES_Pos));
  UART->CR = tmpCR;   
}

void MDR_UART_ChangeEventRxFIFO(MDR_UART_Type *UART, MDR_UART_EventFIFO levelFIFO) 
{
  uint32_t tmpCR = UART->CR;
  
  UART->CR &= ~MDR_UART_CR_EN_Msk;  
  UART->IFLS = MDR_MaskClrSet(UART->IFLS, MDR_UART_IFLS_TXIFLSES_Msk, VAL2FLD_Pos(levelFIFO, MDR_UART_IFLS_RXIFLSES_Pos));
  UART->CR = tmpCR;
}

void MDR_UART_ClearTxFIFO(MDR_UART_Type *UART)
{
  uint32_t tmpCR = UART->CR;
  uint32_t tmpLCR_H = UART->LCR_H;
  //  Disable
  UART->CR = tmpLCR_H & (~MDR_UART_CR_EN_Msk);
  //  FIFO Off to clear
  UART->LCR_H = tmpLCR_H & (~MDR_UART_LCR_H_FEN_Msk);
  //  Restore 
  UART->LCR_H = tmpLCR_H;
  UART->CR = tmpCR;
}

void MDR_UART_ClearRxFIFO(MDR_UART_Type *UART)
{
  while (MDR_UART_CanRead(UART))
    MDR_UART_ReadData(UART);
}

bool MDR_UART_TrySend(MDR_UART_Type *UART, uint8_t data)
{
  if (!MDR_UART_CanSend(UART))
    return false;

  MDR_UART_SendData(UART, data);
  return true;
}




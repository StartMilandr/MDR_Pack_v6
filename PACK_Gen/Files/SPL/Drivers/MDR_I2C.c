#include <MDR_I2C.h>


//===================   I2C GPIO pins Init ==========================
void MDR_I2C_InitPinsGPIO(const MDR_I2C_CfgPinsGPIO *pinsCfg, MDR_PIN_PWR pinsPower, bool pullUpPins)
{
  MDR_PinDig_PermRegs pinPermCfg;
  MDR_Pin_IO pinModeIO;
  
  if (pullUpPins)
    pinModeIO = MDR_Pin_In_PU;
  else
    pinModeIO = MDR_Pin_In;
  
  MDR_Port_InitDigPermRegs(MDR_PIN_OpenDrain, pinsPower, MDR_Off, MDR_Off, &pinPermCfg);
  //  pPinSCL
  if (pinsCfg->pPinSCL != NULL)
  {
    MDR_GPIO_ClockOn(pinsCfg->pPinSCL->portGPIO);
    MDR_GPIO_InitDigPin(pinsCfg->pPinSCL->portGPIO, pinsCfg->pPinSCL->pinIndex, pinModeIO, pinsCfg->pPinSCL->pinFunc, &pinPermCfg);  
  }
  //  pPinSDA
  if (pinsCfg->pPinSDA != NULL)
  {
    MDR_GPIO_ClockOn(pinsCfg->pPinSDA->portGPIO);
    MDR_GPIO_InitDigPin(pinsCfg->pPinSDA->portGPIO, pinsCfg->pPinSDA->pinIndex, pinModeIO, pinsCfg->pPinSDA->pinFunc, &pinPermCfg);
  }
}


//===================   I2C ==========================

//  Простейшая инициализация, минимальная производительность.
//  Делитель будет высчитан по формуле
//  F_SCL = HCLK /(5 * (DIV + 1))
//  DIV = HCLK / (F_SCL * 5) - 1;

static MDR_I2C_CfgReg I2C_fillCfgReg(uint32_t freqHz, uint32_t freqCPU_Hz, uint32_t flags)
{
  MDR_I2C_CfgReg cfg;
  
  cfg.Value = flags;
  cfg.Bits.Clk_Div = (uint16_t) (freqCPU_Hz / (freqHz * 5) - 1);
  if (freqHz > 400000)
    cfg.Bits.speedRange = I2C_Speed_upto1MHz;
  
  return cfg;
}

void MDR_I2C_Init(uint32_t freqHz, uint32_t freqCPU_Hz)
{
  //  Настройка
  MDR_I2C_CfgReg cfg = I2C_fillCfgReg(freqHz, freqCPU_Hz, MDR_I2C_CTR_EN_I2C_Msk);
  //  Apply
  MDR_I2C_InitCfgReg(&cfg, false, 0);
}  

//  Инициализация через структуру, средняя производительность
void MDR_I2C_InitWithIRQ(uint32_t freqHz, uint32_t freqCPU_Hz, bool activateNVIC, uint32_t priority)
{
  //  Настройка
  MDR_I2C_CfgReg cfg = I2C_fillCfgReg(freqHz, freqCPU_Hz, MDR_I2C_CTR_EN_I2C_Msk | MDR_I2C_CTR_EN_INT_Msk);
  //  Apply
  MDR_I2C_InitCfgReg(&cfg, activateNVIC, priority);
}

void MDR_I2C_InitEx(MDR_I2C_Cfg *cfg)
{
  //	Clock Enable
  REG32(MDR_I2C_CLK_EN_ADDR) |= MDR_I2C_CLK_EN_MSK;  
  //  Apply
  MDR_I2C->PRL = (uint8_t)( cfg->Clk_Div & 0xFFUL);
  MDR_I2C->PRH = (uint8_t)((cfg->Clk_Div >> 8) & 0xFFUL);
  
  MDR_I2C->CTR =  MDR_I2C_CTR_EN_I2C_Msk
                | VAL2FLD_Pos(cfg->enableIRQ,  MDR_I2C_CTR_EN_INT_Pos)
                | VAL2FLD_Pos(cfg->speedRange, MDR_I2C_CTR_S_I2C_Pos);
  
  if (cfg->activateNVIC)
  {
    NVIC_SetPriority(I2C_IRQn, cfg->priority);
    NVIC_EnableIRQ(I2C_IRQn);
  }
}

//  Инициализация через унифицированный регистр, минимальный объем, максимальная производительность.
void MDR_I2C_InitCfgReg(MDR_I2C_CfgReg *cfg, bool activateNVIC, uint32_t priority)
{
  //	Clock Enable
  REG32(MDR_I2C_CLK_EN_ADDR) |= MDR_I2C_CLK_EN_MSK;  
  //  Apply
  MDR_I2C->PRL = (uint8_t)((cfg->Value >> MDR_I2C_CfgReg_DIV_LO_Pos) & 0xFFUL);
  MDR_I2C->PRH = (uint8_t)((cfg->Value >> MDR_I2C_CfgReg_DIV_HI_Pos) & 0xFFUL);
  MDR_I2C->CTR = cfg->Value & MDR_I2C_CTR_ExistBits_Mask;
  MDR_I2C_ClearIRQ();

  if (activateNVIC)
  {
    NVIC_SetPriority(I2C_IRQn, priority);
    NVIC_EnableIRQ(I2C_IRQn);
  }
}

void MDR_I2C_ClearRegs(void)
{
  MDR_I2C->CTR = 0;
  MDR_I2C->STA = 0;
  MDR_I2C->CMD = MDR_I2C_CMD_CLR_INT_Msk;  
  MDR_I2C->PRL = 0;
  MDR_I2C->PRH = 0;
}

void MDR_I2C_DeInit(void)
{
  MDR_I2C_ClearRegs(); 
  
  //	Clock Off
  REG32(MDR_I2C_CLK_EN_ADDR) &= ~MDR_I2C_CLK_EN_MSK;  
}

//  Transfers
__STATIC_INLINE void I2C_StartTransfer_loc(uint8_t addr_7bit, bool modeWrite)
{
  //  Запуск передачи адреса с флагом чтение или запись
  if (modeWrite)
    MDR_I2C->TXD = (addr_7bit << 1) | MDR_I2C_ADDR_WR_BIT;
  else
    MDR_I2C->TXD = (addr_7bit << 1) | MDR_I2C_ADDR_RD_BIT;
  MDR_I2C->CMD = MDR_I2C_CMD_Send_Start_Msk | MDR_I2C_CMD_Start_Write_Msk;
}


bool MDR_I2C_StartTransfer(uint8_t addr_7bit, bool modeWrite)
{
  //  Запуск передачи адреса с флагом чтение или запись
  I2C_StartTransfer_loc(addr_7bit, modeWrite);
  
  // Ожидание завершения передачи
  while (MDR_I2C_GetTransfering()) {};
    
  return MDR_I2C_GetAckOk();
}

bool MDR_I2C_SendByte(uint8_t data)
{
  //  Запуск передачи байта данных
  MDR_I2C->TXD = data;
  MDR_I2C->CMD = MDR_I2C_CMD_Start_Write_Msk;  
  
  // Ожидание завершения передачи
  while (MDR_I2C_GetTransfering()) {};
    
  return MDR_I2C_GetAckOk();
}

bool MDR_I2C_ReadByte(uint8_t *data, bool lastByte)
{
  //  Запуск передачи байта данных с подтверждением NACK для последнего байта
  if (!lastByte)
    MDR_I2C->CMD = MDR_I2C_CMD_Start_Read_Msk;
  else
    MDR_I2C->CMD = MDR_I2C_CMD_Start_Read_Msk | MDR_I2C_Send_NACK;
  
  // Ожидание завершения передачи
  while (MDR_I2C_GetTransfering()) {};
  // Чтение полученных данных  
  *data = (uint8_t)MDR_I2C->RXD;
    
  return MDR_I2C_GetAckOk();
}

uint32_t MDR_I2C_TransferWrite(uint8_t addr_7bit, uint32_t count, uint8_t *pData)
{ 
  uint16_t i = 0;
  uint32_t sentCount = 0;
  
  //  Ожидание освобождения шины - BUSY между стартом и стопом.
  while (!MDR_I2C_GetBusFree()){};

  // Start Transfer and send Address
  if (MDR_I2C_StartTransfer(addr_7bit, true))    
  {
    if ((count > 0) && (pData != NULL))
      for (i = 0; i < count; ++i)
      {
        if (MDR_I2C_SendByte(pData[i]))
          ++sentCount;
        else
          break;
      }
  } else
      sentCount = MDR_I2C_RESULT_ERROR_COUNT;

  //  Stop transfer
  MDR_I2C_StopTransfer();
  return sentCount;
}

uint32_t MDR_I2C_TransferRead (uint8_t addr_7bit, uint32_t count, uint8_t *pData)
{
  uint16_t i = 0;
  uint32_t readCount = 0;
  
  //  Ожидание освобождения шины - BUSY между стартом и стопом.
  while (!MDR_I2C_GetBusFree()){};

  // Start Transfer and send Address
  if (MDR_I2C_StartTransfer(addr_7bit, false))
  {
    for (i = 0; i < count; ++i)
    {
      if (MDR_I2C_ReadByte(&pData[i], i == 0))
        ++readCount;
      else
        break;
    }
  } else
      readCount = MDR_I2C_RESULT_ERROR_COUNT;

  //  Stop transfer
  MDR_I2C_StopTransfer();
  return readCount;
}

//======================    Реализация работы через IRQ    ===================
static uint8_t  _I2C_Addr;
static uint32_t _I2C_Count;
static uint32_t _I2C_Index;
static uint8_t *_I2C_pData;
static bool     _I2C_TransfOk;
static pVoidFunc_void _StopCallBack;

bool     _I2C_Started = false;

bool MDR_I2C_IRQ_GetCompleted(bool *success) 
{
  *success = _I2C_TransfOk;
  return !_I2C_Started;
}

pVoidFunc_void  pNextFuncI2C;

static void MDR_I2C_IRQ_WriteNext(void);
static void MDR_I2C_IRQ_ReadNext(void);
static void MDR_I2C_IRQ_ReadStart(void);

bool MDR_I2C_IRQ_TryStartTransfer(uint8_t addr_7bit, uint32_t count, uint8_t *pData, bool modeWrite, pVoidFunc_void stopCallBack)
{
  if ((_I2C_Started) || (!MDR_I2C_GetBusFree()))
    return false;

  _I2C_Addr = addr_7bit;
  _I2C_Count = count;
  _I2C_Index = 0;
  _I2C_pData = pData;  
  _I2C_TransfOk = true;
  _StopCallBack = stopCallBack;
  
  //  Разрешение прерываний
  MDR_I2C_ClearIRQ(); 
  MDR_I2C_EnableIRQ();
  //  Стирание флагов статуса
  MDR_I2C->STA = 0;
  
  //  В следующих прерываниях вызов - функция записи или чтения
  if (modeWrite)
    pNextFuncI2C = MDR_I2C_IRQ_WriteNext;
  else
    pNextFuncI2C = MDR_I2C_IRQ_ReadStart;
  
  //  Запуск передачи адреса с флагом чтения или запись
  I2C_StartTransfer_loc(_I2C_Addr, modeWrite);  
  
  _I2C_Started = true;
  return true;
}

static void MDR_I2C_IRQ_Stop(void)
{ 
  //  Запрет прерываний
  MDR_I2C_DisableIRQ();
  //  Запуск сигнала Stop
  MDR_I2C->CMD = MDR_I2C_CMD_Send_Stop_Msk | MDR_I2C_CMD_CLR_INT_Msk;
  
  //  Флаги остановки
  _I2C_Started = false;
  pNextFuncI2C = MDR_I2C_IRQ_Stop;  

  if (_StopCallBack != NULL)
    _StopCallBack();
}

static void MDR_I2C_IRQ_WriteNext(void)
{  
  if (_I2C_Index < _I2C_Count)
  {
    //  Запуск передачи байта данных
    MDR_I2C->TXD = _I2C_pData[_I2C_Index];
    MDR_I2C->CMD = MDR_I2C_CMD_Start_Write_Msk | MDR_I2C_CMD_CLR_INT_Msk;  
    
    ++_I2C_Index;
  }
  else
    MDR_I2C_IRQ_Stop();
}

static void I2C_IRQ_ReadNextStart_loc(void)
{
  if (_I2C_Index == _I2C_Count)
    MDR_I2C_IRQ_Stop();
  else
  {
    if (_I2C_Index < (_I2C_Count - 1))
      MDR_I2C->CMD = MDR_I2C_CMD_Start_Read_Msk | MDR_I2C_CMD_CLR_INT_Msk;
    else
      MDR_I2C->CMD = MDR_I2C_CMD_Start_Read_Msk | MDR_I2C_Send_NACK | MDR_I2C_CMD_CLR_INT_Msk;
  }
}

static void MDR_I2C_IRQ_ReadStart(void)
{ 
  //  Следующая функция чтение полученного слова и запуск следующего
  pNextFuncI2C = MDR_I2C_IRQ_ReadNext;
  
  //  Запуск цикла чтения
  I2C_IRQ_ReadNextStart_loc();
}

static void MDR_I2C_IRQ_ReadNext(void)
{ 
  //  Чтение полученного слова
  _I2C_pData[_I2C_Index] = MDR_I2C->RXD;
  ++_I2C_Index;
  
  //  Запуск седующего цикла чтения
  I2C_IRQ_ReadNextStart_loc();
}

void MDR_I2C_IRQ_HandlerProcess(void)
{
  uint32_t status = MDR_I2C->STA;
  
  //  Check transfer completed and ACK accepted
  if ((status & (MDR_I2C_STA_TR_Prog_Msk | MDR_I2C_STA_RX_ACK_Msk)) == MDR_I2C_STA_RX_ACK_Msk)
    pNextFuncI2C();
  else
  {
    _I2C_TransfOk = false;
    MDR_I2C_IRQ_Stop();
  }
}


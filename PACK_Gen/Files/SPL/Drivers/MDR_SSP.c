#include <MDR_SSP.h>

const MDR_SSP_TypeEx _MDR_SSP1ex = {
  .SSPx            = MDR_SSP1,
  .Addr_SSPClock   = MDR_SSP_CLOCK_ADDR_SSP1,
  .Msk_SSPClockEn  = MDR_SSP_CLOCK_ENA_MSK_SSP1,
  .Pos_SSPClockBRG = MDR_SSP_CLOCK_BRG_POS_SSP1,
  .Addr_ClockEn    = MDR_CLK_EN_ADDR_SSP1,
  .ClockEnaMask    = MDR_CLK_EN_MASK_SSP1,
  .SSPx_IRQn       = SSP1_IRQn
};

#ifdef MDR_SSP2
  const MDR_SSP_TypeEx _MDR_SSP2ex = {
    .SSPx            = MDR_SSP2,
    .Addr_SSPClock   = MDR_SSP_CLOCK_ADDR_SSP2,
    .Msk_SSPClockEn  = MDR_SSP_CLOCK_ENA_MSK_SSP2,
    .Pos_SSPClockBRG = MDR_SSP_CLOCK_BRG_POS_SSP2,
    .Addr_ClockEn    = MDR_CLK_EN_ADDR_SSP2,
    .ClockEnaMask    = MDR_CLK_EN_MASK_SSP2,
    .SSPx_IRQn       = SSP2_IRQn
  };
#endif

#ifdef MDR_SSP3
  const MDR_SSP_TypeEx _MDR_SSP3ex = {
    .SSPx            = MDR_SSP3,
    .Addr_SSPClock   = MDR_SSP_CLOCK_ADDR_SSP3,
    .Msk_SSPClockEn  = MDR_SSP_CLOCK_ENA_MSK_SSP3,
    .Pos_SSPClockBRG = MDR_SSP_CLOCK_BRG_POS_SSP3,
    .Addr_ClockEn    = MDR_CLK_EN_ADDR_SSP3,
    .ClockEnaMask    = MDR_CLK_EN_MASK_SSP3,
    .SSPx_IRQn       = SSP3_IRQn
  };
#endif

//  Одно прерывание на оба блока SSP3 и SSP4!
#ifdef MDR_SSP4
  const MDR_SSP_TypeEx _MDR_SSP4ex = {
    .SSPx            = MDR_SSP4,
    .Addr_SSPClock   = MDR_SSP_CLOCK_ADDR_SSP4,
    .Msk_SSPClockEn  = MDR_SSP_CLOCK_ENA_MSK_SSP4,
    .Pos_SSPClockBRG = MDR_SSP_CLOCK_BRG_POS_SSP4,
    .Addr_ClockEn    = MDR_CLK_EN_ADDR_SSP4,
    .ClockEnaMask    = MDR_CLK_EN_MASK_SSP4,
    .SSPx_IRQn       = SSP4_IRQn
  };  
#endif

void MDR_SSP_ClearFIFO_RX(MDR_SSP_Type *SSPx)
{
  //  While not empty
  while (SSPx->SR & MDR_SSP_SR_RNE_Msk)
    SSPx->DR;
}

void MDR_SSP_ClearFIFO_TX(MDR_SSP_Type *SSPx)
{
  typedef struct
  {
    __IO uint32_t SSPCR;
    __IO uint32_t SSPIP;
    __IO uint32_t SSPOP;
    __IO uint32_t SSPDR;
  } SSPHACK_Type;
	
  SSPHACK_Type* SSPHACKx;
  SSPHACKx = (SSPHACK_Type*) ((uint32_t)SSPx + 0x80);
	
  SSPHACKx->SSPCR = 0x2;
  while((SSPx->SR & MDR_SSP_SR_TFE_Msk) == 0)
    SSPHACKx->SSPDR;

  SSPHACKx->SSPCR = 0x0;
}

static void MDR_SSP_ClearRegs_loc(MDR_SSP_Type *SSPx)
{
  SSPx->CR1   = 0;
  SSPx->CR0   = 0; 
  SSPx->CPSR  = MDR_SSP_CPSDVSR_MIN;
  SSPx->IMSC  = 0;
  SSPx->ICR   = 0;
  SSPx->DMACR = 0;
} 

void MDR_SSP_DeInit(MDR_SSP_Type *SSPx)
{
  MDR_SSP_ClearRegs_loc(SSPx);
  
  MDR_SSP_ClearFIFO_TX(SSPx);
  MDR_SSP_ClearFIFO_RX(SSPx);   
} 

void MDR_SSP_Init(MDR_SSP_Type *SSPx, MDR_SSP_Config *cfg)
{  
  uint32_t regCR0;
  uint32_t regDMA;
  
  //  Forced Disable SSP
  SSPx->CR1 = 0;
  
  //  New config
  regCR0 = VAL2FLD_Pos(cfg->DataBits,     MDR_SSP_CR0_DSS_Pos)
         | VAL2FLD_Pos(cfg->FrameFormat,  MDR_SSP_CR0_FRF_Pos)
         | VAL2FLD_Pos(cfg->DivSCR_0_255, MDR_SSP_CR0_SCR_Pos);
  
  if (cfg->FrameFormat == SSP_Frame_SPI)
    regCR0 |= VAL2FLD_Pos(cfg->SPI_Mode, MDR_SSP_CR0_SPO_Pos);

  regDMA = VAL2FLD_Pos(cfg->DMA_TX_Enable, MDR_SSP_DMACR_TXDMAE_Pos)
         | VAL2FLD_Pos(cfg->DMA_RX_Enable, MDR_SSP_DMACR_RXDMAE_Pos);
  
//  if (cfg->pCfgIRQ == NULL)
//    regIrqMask = 0;
//  else
//  {
//    regIrqMask =  VAL2FLD_Pos(cfg->pCfgIRQ->OnRxOver_IRQEna,      MDR_SSP_IRQ_RxOver_Pos)
//                | VAL2FLD_Pos(cfg->pCfgIRQ->OnRxTimeout_IRQEna,   MDR_SSP_IRQ_RxTimeout_Pos)
//                | VAL2FLD_Pos(cfg->pCfgIRQ->OnRxHalfFull_IRQEna,  MDR_SSP_IRQ_RxHalfFull_Pos)
//                | VAL2FLD_Pos(cfg->pCfgIRQ->OnTxHalfEmpty_IRQEna, MDR_SSP_IRQ_TxHalfEmpty_Pos);
//  }  
  //  Apply
  SSPx->CR0   = regCR0;
  SSPx->CPSR  = (uint32_t)cfg->DivPSR_2_254;
  SSPx->IMSC  = 0;
  SSPx->DMACR = regDMA;
  
  SSPx->ICR   = MDR_SSP_ICR_RORIC_Msk | MDR_SSP_ICR_RTIC_Msk;  
  
  //  Clear FIFOs
  MDR_SSP_ClearFIFO_TX(SSPx);
  MDR_SSP_ClearFIFO_RX(SSPx);  
}

void MDR_SSP_ChangeSPIMode(MDR_SSP_Type *SSPx, MDR_SPI_CPHA_CPOL newMode)
{
  uint32_t regCR0;
  uint32_t regCR1 = SSPx->CR1;
  
  //  Disable CR1
  SSPx->CR1 = 0;
  //  Set New SPI Mode
  regCR0 = SSPx->CR0;
  regCR0 &= ~(MDR_SSP_CR0_SPO_Msk | MDR_SSP_CR0_SPH_Msk);
  SSPx->CR0 = regCR0 | VAL2FLD_Pos(newMode, MDR_SSP_CR0_SPO_Pos);
  // Restore CR1
  SSPx->CR1 = regCR1;
}

void MDR_SSP_ChangeDataBits(MDR_SSP_Type *SSPx, MDR_SSP_DataBits newDataBits)
{
  uint32_t regCR0 = SSPx->CR0;
  regCR0 &= ~(MDR_SSP_CR0_DSS_Msk);
  SSPx->CR0 = regCR0 | VAL2FLD_Pos(newDataBits, MDR_SSP_CR0_DSS_Pos);
}

void MDR_SSP_ChangeRate(MDR_SSP_Type *SSPx, uint8_t divSCR_0_255, uint8_t divPSR_2_254)
{
  uint32_t regCR0;
  uint32_t regCR1 = SSPx->CR1;
  
  //  Disable CR1
  SSPx->CR1 = 0;
  
  //  Set New SPI Mode
  regCR0 = SSPx->CR0;
  regCR0 &= ~(MDR_SSP_CR0_SCR_Msk);
  SSPx->CR0 = regCR0 | VAL2FLD_Pos(divSCR_0_255, MDR_SSP_CR0_SCR_Pos);
  
  SSPx->CPSR = (uint32_t)divPSR_2_254;
  
  // Restore CR1
  SSPx->CR1 = regCR1;
}

void MDR_SSP_ChangeFrameFormat(MDR_SSP_Type *SSPx, MDR_SSP_FrameFormat newFrameFormat)
{
  uint32_t regCR0;
  uint32_t regCR1 = SSPx->CR1;
  
  //  Disable CR1
  SSPx->CR1 = 0;
  
  //  Set New SPI Mode
  regCR0 = SSPx->CR0;
  regCR0 &= ~(MDR_SSP_CR0_FRF_Msk);
  if (newFrameFormat != SSP_Frame_SPI)
    regCR0 &= ~(MDR_SSP_CR0_SPO_Msk | MDR_SSP_CR0_SPH_Msk);
    
  SSPx->CR0 = regCR0 | VAL2FLD_Pos(newFrameFormat, MDR_SSP_CR0_FRF_Pos);
  
  // Restore CR1
  SSPx->CR1 = regCR1;
}

void MDR_SSP_EnableMaster(MDR_SSP_Type *SSPx, bool loopBackEnable)
{
  if (!loopBackEnable)
    SSPx->CR1 = MDR_SSP_CR1_SSE_Msk;  
  else
    SSPx->CR1 = MDR_SSP_CR1_SSE_Msk | MDR_SSP_CR1_LBM_Msk;
}

void MDR_SSP_EnableSlave(MDR_SSP_Type *SSPx, bool outputDisable)
{
  if (!outputDisable)
    SSPx->CR1 = MDR_SSP_CR1_SSE_Msk | MDR_SSP_CR1_MS_Msk;
  else
    SSPx->CR1 = MDR_SSP_CR1_SSE_Msk | MDR_SSP_CR1_MS_Msk| MDR_SSP_CR1_SOD_Msk;
}

void MDR_SSP_Disable(MDR_SSP_Type *SSPx)
{
  SSPx->CR1 = 0;
}

MDR_SSP_Status MDR_SSP_GetStatus(MDR_SSP_Type *SSPx)
{
  MDR_SSP_Status result;
  
  result.Status = SSPx->SR;
  return result;
}

void MDR_SSP_WaitAndSendData(MDR_SSP_Type *SSPx, uint16_t data)
{
  while (!MDR_SSP_CanWrite(SSPx)){};
  MDR_SSP_WriteData(SSPx, data);
}

uint16_t MDR_SSP_WaitAndReadData(MDR_SSP_Type *SSPx)
{
  // Wait
  while (MDR_SSP_GetStatus(SSPx).Flags.RX_NotEmpty == MDR_Off){};
  // Read
  return MDR_SSP_ReadData(SSPx);
}

uint16_t MDR_SSP_MasterTransfer(MDR_SSP_Type *SSPx, uint16_t data)
{
  MDR_SSP_WaitAndSendData(SSPx, data);
  return MDR_SSP_WaitAndReadData(SSPx);
}

MDR_SSP_Events MDR_SSP_GetEventsMasked(MDR_SSP_Type *SSPx)
{
  MDR_SSP_Events result;
  result.Events = SSPx->MIS;
  return result;
}

MDR_SSP_Events MDR_SSP_GetEventsAll(MDR_SSP_Type *SSPx)
{
  MDR_SSP_Events result;
  result.Events = SSPx->RIS;
  return result;
}


void MDR_SSP_EnableEventIRQ(MDR_SSP_Type *SSPx, MDR_SSP_Events eventIRQ)
{ 
  SSPx->IMSC = eventIRQ.Events;
}

MDR_SSP_Events MDR_SSP_GetEventIRQ(MDR_SSP_Type *SSPx)
{
  MDR_SSP_Events res;
  res.Events = SSPx->IMSC;
  return res;
}

//  ===============   Функции управления через расширенную структуру блока MDR_SSP_TypeEx ==================

static void MDR_SSPex_ClockOn(const MDR_SSP_TypeEx *exSSPx)
{
  REG32(exSSPx->Addr_ClockEn) |= exSSPx->ClockEnaMask;
}

static void MDR_SSPex_ClockOff(const MDR_SSP_TypeEx *exSSPx)
{
  REG32(exSSPx->Addr_ClockEn) &= ~exSSPx->ClockEnaMask;
}

static void MDR_SSPex_Clock_Enable(const MDR_SSP_TypeEx *exSSPx, MDR_BRG_DIV_128 divSSP_Clock)
{
  uint32_t regSSP_Clock = REG32(exSSPx->Addr_SSPClock);
  
  regSSP_Clock &= ~(uint32_t)(MDR_SSP_CLOCK_BRG_CLR_Mask << exSSPx->Pos_SSPClockBRG);
  regSSP_Clock |= (uint32_t)(divSSP_Clock << exSSPx->Pos_SSPClockBRG) | exSSPx->Msk_SSPClockEn;
  
  REG32(exSSPx->Addr_SSPClock) = regSSP_Clock;
}

static void MDR_SSPex_Clock_Disable(const MDR_SSP_TypeEx *exSSPx)
{
  REG32(exSSPx->Addr_SSPClock) &= ~exSSPx->Msk_SSPClockEn;
}

void MDR_SSPex_Init (const MDR_SSP_TypeEx *exSSPx, MDR_SSP_ConfigEx *cfgEx)
{
  //  Включение частоты SSP_Clock
  MDR_SSPex_Clock_Enable(exSSPx, cfgEx->divSSP_Clock);  
  //  Подача тактирования блока
  MDR_SSPex_ClockOn(exSSPx);  
  //  Инициализация параметров SSP
  MDR_SSP_Init(exSSPx->SSPx, cfgEx->cfgSSP);
  //  Инициализация прерываний в NVIC, чтобы пользователь не забыл
  if (cfgEx->activateNVIC_IRQ)
  {
    NVIC_EnableIRQ(exSSPx->SSPx_IRQn);
    NVIC_SetPriority(exSSPx->SSPx_IRQn, cfgEx->priorityIRQ);
  }     
}

void MDR_SSPex_DeInit(const MDR_SSP_TypeEx *exSSPx)
{
  MDR_SSP_DeInit(exSSPx->SSPx);  
  MDR_SSPex_ClockOff(exSSPx);
  
  MDR_SSPex_Clock_Disable(exSSPx);
} 

//===================   SSP GPIO pins Init ==========================
void MDR_SSP_InitPinsGPIO(const MDR_SSP_CfgPinsGPIO *pinsCfg, MDR_PIN_PWR pinsPower)
{
  MDR_PinDig_PermRegs pinPermCfg;
  
  MDR_Port_InitDigPermRegs(MDR_PIN_PullPush, pinsPower, MDR_Off, MDR_Off, &pinPermCfg);
  //  CLK
  MDR_GPIO_InitDigPin(pinsCfg->pPinCLK->portGPIO, pinsCfg->pPinCLK->pinIndex, MDR_Pin_In, pinsCfg->pPinCLK->pinFunc, &pinPermCfg);
  //  TX
  if (pinsCfg->pPinTX != NULL)    
    MDR_GPIO_InitDigPin(pinsCfg->pPinTX->portGPIO, pinsCfg->pPinTX->pinIndex, MDR_Pin_In, pinsCfg->pPinTX->pinFunc, &pinPermCfg);
  //  RX  
  if (pinsCfg->pPinRX != NULL)  
    MDR_GPIO_InitDigPin(pinsCfg->pPinRX->portGPIO, pinsCfg->pPinRX->pinIndex, MDR_Pin_In, pinsCfg->pPinRX->pinFunc, &pinPermCfg);
  //  FSS
  if (pinsCfg->pPinFSS != NULL)  
    MDR_GPIO_InitDigPin(pinsCfg->pPinFSS->portGPIO, pinsCfg->pPinFSS->pinIndex, MDR_Pin_In, pinsCfg->pPinFSS->pinFunc, &pinPermCfg);  
}


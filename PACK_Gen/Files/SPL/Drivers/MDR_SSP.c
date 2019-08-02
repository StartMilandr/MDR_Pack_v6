#include <MDR_SSP.h>

const MDR_SSP_TypeEx _MDR_SSP1ex = {
  .SSPx            = MDR_SSP1,
  //  SSPClock Enable
  .CfgClock.ClockEna_Addr = MDR_SSP1_CLK_EN_ADDR,
  .CfgClock.ClockEna_Mask = MDR_SSP1_CLK_EN_MSK,
  //  SSPClock Gate On and BRG
  .CfgClock.ClockGate_Addr        = MDR_SSP1_CLOCK_GATE_ADDR,
  .CfgClock.ClockGate_ClockOn_Msk = MDR_SSP1_CLOCK_GATE_ENA_MSK,
  .CfgClock.ClockGate_BRG_Pos     = MDR_SSP1_CLOCK_GATE_BRG_POS,
  
  .SSPx_IRQn       = SSP1_IRQn
};

#ifdef MDR_SSP2
  const MDR_SSP_TypeEx _MDR_SSP2ex = {
    .SSPx            = MDR_SSP2,
    //  SSPClock Enable
    .CfgClock.ClockEna_Addr = MDR_SSP2_CLK_EN_ADDR,
    .CfgClock.ClockEna_Mask = MDR_SSP2_CLK_EN_MSK,
    //  SSPClock Gate On and BRG
    .CfgClock.ClockGate_Addr        = MDR_SSP2_CLOCK_GATE_ADDR,
    .CfgClock.ClockGate_ClockOn_Msk = MDR_SSP2_CLOCK_GATE_ENA_MSK,
    .CfgClock.ClockGate_BRG_Pos     = MDR_SSP2_CLOCK_GATE_BRG_POS,
        
    .SSPx_IRQn       = SSP2_IRQn
  };
#endif

#ifdef MDR_SSP3
  const MDR_SSP_TypeEx _MDR_SSP3ex = {
    .SSPx            = MDR_SSP3,
    //  SSPClock Enable
    .CfgClock.ClockEna_Addr = MDR_SSP3_CLK_EN_ADDR,
    .CfgClock.ClockEna_Mask = MDR_SSP3_CLK_EN_MSK,
    //  SSPClock Gate On and BRG
    .CfgClock.ClockGate_Addr        = MDR_SSP3_CLOCK_GATE_ADDR,
    .CfgClock.ClockGate_ClockOn_Msk = MDR_SSP3_CLOCK_GATE_ENA_MSK,
    .CfgClock.ClockGate_BRG_Pos     = MDR_SSP3_CLOCK_GATE_BRG_POS,
    
    .SSPx_IRQn       = SSP3_IRQn
  };
#endif

//  Одно прерывание на оба блока SSP3 и SSP4!
#ifdef MDR_SSP4
  const MDR_SSP_TypeEx _MDR_SSP4ex = {
    .SSPx            = MDR_SSP4,
    //  SSPClock Enable
    .CfgClock.ClockEna_Addr = MDR_SSP4_CLK_EN_ADDR,
    .CfgClock.ClockEna_Mask = MDR_SSP4_CLK_EN_MSK,
    //  SSPClock Gate On and BRG
    .CfgClock.ClockGate_Addr        = MDR_SSP4_CLOCK_GATE_ADDR,
    .CfgClock.ClockGate_ClockOn_Msk = MDR_SSP4_CLOCK_GATE_ENA_MSK,
    .CfgClock.ClockGate_BRG_Pos     = MDR_SSP4_CLOCK_GATE_BRG_POS,
    
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
  
  //  Forced Disable SSP
  SSPx->CR1 = 0;
  
  //  New config
  regCR0 = VAL2FLD_Pos(cfg->DataBits,     MDR_SSP_CR0_DSS_Pos)
         | VAL2FLD_Pos(cfg->FrameFormat,  MDR_SSP_CR0_FRF_Pos)
         | VAL2FLD_Pos(cfg->DivSCR_0_255, MDR_SSP_CR0_SCR_Pos);
  
  if (cfg->FrameFormat == SSP_Frame_SPI)
    regCR0 |= VAL2FLD_Pos(cfg->SPI_Mode, MDR_SSP_CR0_SPO_Pos);

  //  Apply
  SSPx->CR0   = regCR0;
  SSPx->CPSR  = (uint32_t)cfg->DivPSR_2_254;
  SSPx->IMSC  = 0;
  SSPx->DMACR = 0;
  
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
  while (!MDR_SSP_CanWrite(SSPx));
  MDR_SSP_WriteData(SSPx, data);
}

uint16_t MDR_SSP_WaitAndReadData(MDR_SSP_Type *SSPx)
{
  // Wait
  while (MDR_SSP_GetStatus(SSPx).Flags.RX_NotEmpty == MDR_Off);
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

void MDR_SSPex_InitEx (const MDR_SSP_TypeEx *exSSPx, MDR_SSP_ConfigEx *cfgEx)
{
  //  Подача тактирования блока
  MDR_PerClock_Enable(&exSSPx->CfgClock);  
  //  Включение частоты SSP_Clock
  MDR_PerClock_GateOpen(&exSSPx->CfgClock, cfgEx->ClockBRG);      
  //  Инициализация параметров SSP
  MDR_SSP_Init(exSSPx->SSPx, cfgEx->cfgSSP);
  //  Инициализация прерываний в NVIC, чтобы пользователь не забыл
  if (cfgEx->activateNVIC_IRQ)
  {
    NVIC_EnableIRQ(exSSPx->SSPx_IRQn);
    NVIC_SetPriority(exSSPx->SSPx_IRQn, cfgEx->priorityIRQ);
  }     
}

void MDR_SSP_EnableNVIC_IRQ(const MDR_SSP_TypeEx *exSSPx, uint32_t priorityIRQ)
{
  NVIC_EnableIRQ(exSSPx->SSPx_IRQn);
  NVIC_SetPriority(exSSPx->SSPx_IRQn, priorityIRQ);
}

void MDR_SSP_DisableNVIC_IRQ(const MDR_SSP_TypeEx *exSSPx)
{
  NVIC_DisableIRQ(exSSPx->SSPx_IRQn);
}
  

void MDR_SSPex_Init  (const MDR_SSP_TypeEx *exSSPx, MDR_SSP_Config *cfgSSP, MDR_Div128P ClockBRG)
{
  //  Подача тактирования блока
  MDR_PerClock_Enable(&exSSPx->CfgClock);  
  //  Включение частоты SSP_Clock
  MDR_PerClock_GateOpen(&exSSPx->CfgClock, ClockBRG);      
  //  Инициализация параметров SSP
  MDR_SSP_Init(exSSPx->SSPx, cfgSSP);
}

void MDR_SSPex_DeInit(const MDR_SSP_TypeEx *exSSPx)
{
  MDR_SSP_DeInit(exSSPx->SSPx);  
  
  MDR_PerClock_GateClose(&exSSPx->CfgClock);  
  MDR_PerClock_Disable(&exSSPx->CfgClock);
} 

//===================   SSP GPIO pins Init ==========================
void MDR_SSP_InitPinsGPIO(const MDR_SSP_CfgPinsGPIO *pinsCfg, MDR_PIN_PWR pinsPower)
{
  MDR_PinDig_GroupPinCfg pinPermCfg;
  
  MDR_Port_InitDigGroupPinCfg(MDR_Off, pinsPower, MDR_Off, MDR_Off, &pinPermCfg);
  //  CLK
  MDR_GPIO_Enable(pinsCfg->pPinCLK->portGPIO);
  MDR_GPIO_InitDigPin(pinsCfg->pPinCLK->portGPIO, pinsCfg->pPinCLK->pinIndex, MDR_Pin_In, pinsCfg->pPinCLK->pinFunc, &pinPermCfg);
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
  //  FSS
  if (pinsCfg->pPinFSS != NULL)  
  {
    MDR_GPIO_Enable(pinsCfg->pPinFSS->portGPIO);
    MDR_GPIO_InitDigPin(pinsCfg->pPinFSS->portGPIO, pinsCfg->pPinFSS->pinIndex, MDR_Pin_In, pinsCfg->pPinFSS->pinFunc, &pinPermCfg);  
  }
}


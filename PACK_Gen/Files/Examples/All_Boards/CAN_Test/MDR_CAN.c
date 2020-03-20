#include <MDR_CAN.h>

// !!! ДРАЙВЕР НЕ РАБОЧИЙ, ЕЩЕ НИ РАЗУ НЕ ЗАПУСКАЛСЯ И НЕ ОТЛАЖИВАЛСЯ !!!

const MDR_CAN_TypeEx _MDR_CAN1ex = {
  .CANx = MDR_CAN1,
  
  //  CanClock Enable
  .CfgClock.ClockEna_Addr = MDR_CAN1_CLK_EN_ADDR,
  .CfgClock.ClockEna_Mask = MDR_CAN1_CLK_EN_MSK,
  
  //  UartClock Gate On and BRG
  .CfgClock.ClockGate_Addr        = MDR_CAN1_CLOCK_GATE_ADDR,
#ifndef MDR_CLK_LIKE_VE8  
  .CfgClock.ClockGate_ClockOn_Msk = MDR_CAN1_CLOCK_GATE_ENA_MSK,
  .CfgClock.ClockGate_BRG_Pos     = MDR_CAN1_CLOCK_GATE_BRG_POS,
#endif
   //  NVIC
  .CANx_IRQn       = CAN1_IRQn  
};



void MDR_CANex_ClearBuffs(MDR_CAN_Type *CAN)
{
  uint32_t i;
  for (i = 0; i < MDR_CAN_BUF_COUNT; i++)
  {
    CAN->BUF_CON[i].CTRL = 0;
    CAN->FILTER[i].FILTER = 0;
    CAN->FILTER[i].MASK = 0;
  }
}

void MDR_CAN_Init(MDR_CAN_Type *MDR_CANx, uint32_t regCtrl, MDR_CAN_TimingCfg *canTimeCfg)
{
  MDR_CANx->CONTROL = regCtrl;  
  MDR_CANx->BITTMNG =   VAL2FLD_Pos(canTimeCfg->BaudRatePresc,   MDR_CAN_BITTMNG_BRP_Pos)
                  | VAL2FLD_Pos(canTimeCfg->Delay_PSEG,      MDR_CAN_BITTMNG_PSEG_Pos)
                  | VAL2FLD_Pos(canTimeCfg->Delay_SEG1,      MDR_CAN_BITTMNG_SEG1_Pos)
                  | VAL2FLD_Pos(canTimeCfg->Delay_SEG2,      MDR_CAN_BITTMNG_SEG2_Pos)
                  | VAL2FLD_Pos(canTimeCfg->SyncJumpWidth,   MDR_CAN_BITTMNG_SJW_Pos)
                  | VAL2FLD_Pos(canTimeCfg->TrimpleSampling, MDR_CAN_BITTMNG_SB_Pos);
  
  MDR_CANx->INT_EN = 0;
  MDR_CANx->OVER = 255;
  MDR_CANx->INT_RX = 0;
  MDR_CANx->INT_TX = 0;

  MDR_CANex_ClearBuffs(MDR_CANx);  
  
  MDR_CANx->STATUS  = 0;  
  MDR_CANx->CONTROL |= MDR_CAN_CONTROL_CAN_EN_Msk;
}


MDR_CAN_BufType* MDR_CAN_BuffInitTX(MDR_CAN_Type *MDR_CANx, uint32_t bufInd, uint32_t ID, MDR_CAN_BuffCfgTX *cfgTX)
{
  MDR_CAN_BufType* resBuff = MDR_CAN_GET_BUFF(MDR_CANx, bufInd);
  
  resBuff->BUF.ID = ID;  
  if (cfgTX->isExtended)    
    resBuff->BUF.DLC = MDR_CAN_DLC_EXT_SEL | cfgTX->dataCount;
  else
    resBuff->BUF.DLC = MDR_CAN_DLC_STD_SEL | cfgTX->dataCount;

  resBuff->CON.CTRL = MDR_CAN_BUF_CON_EN_Msk | VAL2FLD_Pos(cfgTX->lowPrioity, MDR_CAN_BUF_CON_PRIOR_OFF_Pos);    
  return resBuff;
}

MDR_CAN_BufType* MDR_CAN_BuffInitRX(MDR_CAN_Type *MDR_CANx, uint32_t bufInd, bool enOverwrite, uint32_t filterMask, uint32_t RX_ID)
{
  MDR_CAN_BufType* resBuff = MDR_CAN_GET_BUFF(MDR_CANx, bufInd);
  
  //resBuff->BUF.ID = RX_ID;  - for TX Only
  resBuff->FILTER.FILTER = RX_ID;
  resBuff->FILTER.MASK = filterMask;  
  
  if (enOverwrite)
    resBuff->CON.CTRL = MDR_CAN_BUF_CON_RX_Msk | MDR_CAN_BUF_CON_EN_Msk | MDR_CAN_BUF_CON_OVER_EN_Msk;
  else
    resBuff->CON.CTRL = MDR_CAN_BUF_CON_RX_Msk | MDR_CAN_BUF_CON_EN_Msk;
  
  return resBuff;
}

void MDR_CAN_BuffDeInit(MDR_CAN_BufType* CAN_Buff)
{
  CAN_Buff->CON.CTRL = 0;
  CAN_Buff->FILTER.FILTER = 0;
  CAN_Buff->FILTER.MASK = 0;
}

void MDR_CAN_BuffSend(MDR_CAN_BufType* CAN_Buff, uint32_t dataLo, uint32_t dataHi)
{
  CAN_Buff->BUF.DATAL = dataLo;
  CAN_Buff->BUF.DATAH = dataHi;
  CAN_Buff->CON.CTRL |= MDR_CAN_BUF_CON_TX_REQ_Msk;
}

void MDR_CAN_BuffSendEx(MDR_CAN_BufType* CAN_Buff, MDR_CAN_Data *bufData)
{
  CAN_Buff->BUF.DATAL = bufData->DataLo;
  CAN_Buff->BUF.DATAH = bufData->DataHi;
  CAN_Buff->CON.CTRL |= MDR_CAN_BUF_CON_TX_REQ_Msk;  
}

void MDR_CAN_BuffSendEx_ID(MDR_CAN_BufType* CAN_Buff, MDR_CAN_Data *bufData, uint32_t ID)
{
  CAN_Buff->BUF.ID = ID;
  CAN_Buff->BUF.DATAL = bufData->DataLo;
  CAN_Buff->BUF.DATAH = bufData->DataHi;
  CAN_Buff->CON.CTRL |= MDR_CAN_BUF_CON_TX_REQ_Msk;  
}


MDR_CAN_BufType* MDR_CAN_BuffInit_RequestRTR(MDR_CAN_Type *MDR_CANx, uint32_t bufInd, uint32_t RTR_ID, bool isExtended, bool lowPrioity)
{
  MDR_CAN_BufType* resBuff = MDR_CAN_GET_BUFF(MDR_CANx, bufInd);
  
  resBuff->BUF.ID = RTR_ID;  
  if (isExtended)    
    resBuff->BUF.DLC = MDR_CAN_DLC_EXT_SEL | MDR_CAN_DLC_RTR_Msk;
  else
    resBuff->BUF.DLC = MDR_CAN_DLC_STD_SEL | MDR_CAN_DLC_RTR_Msk;

  resBuff->CON.CTRL = MDR_CAN_BUF_CON_EN_Msk | VAL2FLD_Pos(lowPrioity, MDR_CAN_BUF_CON_PRIOR_OFF_Pos);    
  return resBuff;
}

//MDR_CAN_BufType* MDR_CAN_BuffInit_RequestCustomRTR(MDR_CAN_Type *MDR_CANx, uint32_t bufInd)
//{

//}


MDR_CAN_BufType* MDR_CAN_BuffInit_AnswerRTR(MDR_CAN_Type *MDR_CANx, uint32_t bufInd, MDR_CAN_BuffCfgRTR *cfgRTR, MDR_CAN_Data *bufData)
{
  MDR_CAN_BufType* resBuff = MDR_CAN_GET_BUFF(MDR_CANx, bufInd);
  
  resBuff->BUF.DATAL = bufData->DataLo;
  resBuff->BUF.DATAH = bufData->DataHi;

  resBuff->BUF.ID = cfgRTR->ID;
  if (cfgRTR->answerCfg.isExtended)    
    resBuff->BUF.DLC = MDR_CAN_DLC_EXT_SEL | cfgRTR->answerCfg.dataCount;
  else
    resBuff->BUF.DLC = MDR_CAN_DLC_STD_SEL | cfgRTR->answerCfg.dataCount;

  resBuff->CON.CTRL = MDR_CAN_BUF_CON_EN_Msk | MDR_CAN_BUF_CON_RTR_EN_Msk
                    | VAL2FLD_Pos(cfgRTR->answerCfg.lowPrioity, MDR_CAN_BUF_CON_PRIOR_OFF_Pos);  
  
  return resBuff;
}

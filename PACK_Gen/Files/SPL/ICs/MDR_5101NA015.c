#include "MDR_5101NA015.h"

#define DEF_CPU_MAX_HZ    150E+6

static MDR_5101NA015_Delays _5101NA015_Delay = {
  .TicksCalibr  = US_TO_DELAY_LOOPS(MDR_5101NA015_CALIBR_DELAY_US, DEF_CPU_MAX_HZ),
  .TicksCS_10ns = NS_TO_DELAY_LOOPS(MDR_5101NA015_CS_DELAY_NS, DEF_CPU_MAX_HZ)
};

void MDR_5101NA015_InitDelays(const MDR_5101NA015_Delays *delays)
{
  _5101NA015_Delay = *delays;
}  

void MDR_5101NA015_InitDelaysDef(uint32_t CPU_FregHz)
{
  _5101NA015_Delay.TicksCalibr  = US_TO_DELAY_LOOPS(MDR_5101NA015_CALIBR_DELAY_US, CPU_FregHz);
  _5101NA015_Delay.TicksCS_10ns = NS_TO_DELAY_LOOPS(MDR_5101NA015_CS_DELAY_NS, CPU_FregHz);
}


//==================  Инициализация и управление SPI ======================

//  Вспомогательные функции
__STATIC_INLINE void MDR_5101NA015_CS_SetActive  (const MDR_5101NA015_Obj *pObjDAC)
{   
  MDR_Port_ClearPins(pObjDAC->CS_Port, pObjDAC->CS_PinSel);
  MDR_Delay(_5101NA015_Delay.TicksCS_10ns);
}

__STATIC_INLINE void MDR_5101NA015_CS_SetInactive(const MDR_5101NA015_Obj *pObjDAC)
{
  MDR_Port_SetPins(pObjDAC->CS_Port, pObjDAC->CS_PinSel);
  MDR_Delay(_5101NA015_Delay.TicksCS_10ns);
}


MDR_5101NA015_Obj MDR_5101NA015_Init(const MDR_SSP_TypeEx *exSSPx, const MDR_5101NA015_Cfg *cfgDAC)
{
  MDR_5101NA015_Obj result;
  
  //  SPI Init  
  MDR_SSP_Config cfgSSP = {
    .DataBits     = SSP_DataBits_8,
    .FrameFormat  = SSP_Frame_SPI,
    .SPI_Mode     = SPI_CPHA0_CPOL1,
    .DivSCR_0_255 = cfgDAC->rates.WR_DivSCR_0_255,
    .DivPSR_2_254 = cfgDAC->rates.WR_DivPSR_2_254,
  };  
  MDR_SSPex_Init(exSSPx, &cfgSSP);
  MDR_SSPex_EnableMaster(exSSPx, false);
  
  //  Init SPI Pins  
  MDR_SSP_CfgPinsGPIO cfgPins;  
  cfgPins.pPinCLK = cfgDAC->pPinCLK; 
  cfgPins.pPinRX  = cfgDAC->pPinRX; 
  cfgPins.pPinTX  = cfgDAC->pPinTX;   
  cfgPins.pPinFSS = NULL;
  MDR_SSP_InitPinsGPIO(&cfgPins, cfgDAC->pinsPower);  
  
  //  CS Manual pin init and fill result
  result.SSPx = exSSPx->SSPx;
  MDR_5101NA015_InitPinCS(cfgDAC->pPinManualCS, cfgDAC->pinsPower, &result);
 
  //  Set CS to inactive State
  MDR_5101NA015_CS_SetInactive(&result); 
  result.rates = cfgDAC->rates;
  
  return result;
}

void MDR_5101NA015_InitPinCS(const MDR_SSP_CfgPinGPIO  *pPinManualCS, MDR_PIN_PWR pinsPower, MDR_5101NA015_Obj *pObjDAC)
{
  MDR_PinDig_GroupPinCfg pinPermRegs;
  
  MDR_GPIO_Enable(pPinManualCS->portGPIO);
  MDR_Port_InitDigGroupPinCfg(MDR_Off, pinsPower, MDR_Off, MDR_Off, &pinPermRegs);
  MDR_GPIO_InitDigPin(pPinManualCS->portGPIO, pPinManualCS->pinIndex, MDR_Pin_Out, MDR_PIN_PORT, &pinPermRegs);  
  
  pObjDAC->CS_Port    = pPinManualCS->portGPIO->PORTx; 
  pObjDAC->CS_PinSel  = (uint32_t)(1UL << pPinManualCS->pinIndex);
}

void MDR_5101NA015_WriteTransfer(const MDR_5101NA015_Obj *pObjDAC, uint8_t comID, uint16_t value)
{  
  MDR_5101NA015_CS_SetActive(pObjDAC);    
  MDR_SSP_MasterTransfer(pObjDAC->SSPx, comID);
  MDR_SSP_MasterTransfer(pObjDAC->SSPx, (value >> 8) & 0xFF);
  MDR_SSP_MasterTransfer(pObjDAC->SSPx, value & 0xFF);
  MDR_5101NA015_CS_SetInactive(pObjDAC);
}

uint32_t MDR_5101NA015_ReadTransfer(const MDR_5101NA015_Obj *pObjDAC, uint8_t comID)
{   
  MDR_5101NA015_CS_SetActive(pObjDAC);    
  uint16_t rd1 = MDR_SSP_MasterTransfer(pObjDAC->SSPx, comID);
  uint16_t rd2 = MDR_SSP_MasterTransfer(pObjDAC->SSPx, 0);
  uint16_t rd3 = MDR_SSP_MasterTransfer(pObjDAC->SSPx, 0);
  MDR_5101NA015_CS_SetInactive(pObjDAC);
    
  return (rd3 & 0xFFUL) | ((rd2 & 0xFFUL) << 8) | ((rd1 & 0xFFUL) << 16);
}


void MDR_5101NA015_RunCalibr(const MDR_5101NA015_Obj *pObjDAC, uint16_t calibrFlags) 
{ 
  MDR_5101NA015_WriteTransfer(pObjDAC, MDR_5101NA015_CMD__WR_CALIBR, calibrFlags); 
  MDR_Delay(_5101NA015_Delay.TicksCalibr);
}



void MDR_5101NA015_ReadEnter(const MDR_5101NA015_Obj *pObjDAC)
{

  pObjDAC->SSPx->CR1 &= ~MDR_SSP_CR1_SSE_Msk;  
  
  pObjDAC->SSPx->CR0 = MDR_MaskClrSet(pObjDAC->SSPx->CR0, MDR_SSP_CR0_SCR_Msk | MDR_SSP_CR0_SPH_Msk, (pObjDAC->rates.RD_DivSCR_0_255 << MDR_SSP_CR0_SCR_Pos) | MDR_SSP_CR0_SPH_Msk);
  pObjDAC->SSPx->CPSR = pObjDAC->rates.RD_DivPSR_2_254;
  
  pObjDAC->SSPx->CR1 |= MDR_SSP_CR1_SSE_Msk;  
}


void MDR_5101NA015_ReadExit(const MDR_5101NA015_Obj *pObjDAC)
{  
  pObjDAC->SSPx->CR1 &= ~MDR_SSP_CR1_SSE_Msk;  
  
  pObjDAC->SSPx->CR0 = MDR_MaskClrSet(pObjDAC->SSPx->CR0, MDR_SSP_CR0_SCR_Msk | MDR_SSP_CR0_SPH_Msk, pObjDAC->rates.WR_DivSCR_0_255 << MDR_SSP_CR0_SCR_Pos);
  pObjDAC->SSPx->CPSR = pObjDAC->rates.WR_DivPSR_2_254;
  
  pObjDAC->SSPx->CR1 |= MDR_SSP_CR1_SSE_Msk;
}

uint32_t MDR_5101NA015_Read(const MDR_5101NA015_Obj *pObjDAC, uint8_t comID)
{
  MDR_5101NA015_ReadEnter(pObjDAC);
  uint32_t result = MDR_5101NA015_ReadTransfer(pObjDAC, comID);
  MDR_5101NA015_ReadExit(pObjDAC);
  
  return result;
}

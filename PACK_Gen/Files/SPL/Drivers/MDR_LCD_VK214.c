#include "MDR_LCD_VK214.h"


void MDR_LCD_ClearRegs(void)
{
  MDR_LCD->CR = 0;
  MDR_LCD->ROW1 = 0;
  MDR_LCD->ROW2 = 0;
  MDR_LCD->ROW3 = 0;
  MDR_LCD->ROW4 = 0;
  MDR_LCD->AROW1 = 0;
  MDR_LCD->AROW2 = 0;
  MDR_LCD->AROW3 = 0;
  MDR_LCD->AROW4 = 0;
}

void MDR_LCD_SetScreen(MDR_LCD_SreenData *pData)
{
  MDR_LCD->ROW1 = pData->SegmCom0;
  MDR_LCD->ROW2 = pData->SegmCom1;
  MDR_LCD->ROW3 = pData->SegmCom2;
  MDR_LCD->ROW4 = pData->SegmCom3;  
}

void MDR_LCD_SetScreenAlt(MDR_LCD_SreenData *pData)
{
  MDR_LCD->AROW1 = pData->SegmCom0;
  MDR_LCD->AROW2 = pData->SegmCom1;
  MDR_LCD->AROW3 = pData->SegmCom2;
  MDR_LCD->AROW4 = pData->SegmCom3;
}

void MDR_LCD_Init(const MDR_LCD_Cfg *pCfg)
{
  uint32_t regValue;
  
  //  Clock On
  MDR_CLOCK->PER2_CLOCK = MDR_MaskSet(MDR_CLOCK->PER2_CLOCK, MDR_RST_PER2__LCD_CLK_EN_Msk);    
  MDR_LCD_ClearRegs();
  
  //  Основные настройки - Static Control
  regValue = (uint32_t)( VAL2FLD_Pos(pCfg->clockSource,       MDR_LCD_CR_CLK_SEL_Pos)
                       | VAL2FLD_Pos(pCfg->frameDIV,          MDR_LCD_CR_DIV_Pos)
                       | VAL2FLD_Pos(pCfg->useExternalPower,  MDR_LCD_CR_VLCDOn_Pos)
                       | MDR_LCD_CR_EN_Msk);
  
  //  Мигание
  if (pCfg->pBlinkCfg != NULL)
    regValue |= (uint32_t)( VAL2FLD_Pos(pCfg->pBlinkCfg->blinkFreq,        MDR_LCD_CR_BF_Pos)
                          | VAL2FLD_Pos(pCfg->pBlinkCfg->blinkToAlterData, MDR_LCD_CR_AltFlicker_Pos));
  
  //  Мультиплексирование
  if (pCfg->pMuxCfg != NULL)
    regValue |= (uint32_t)( VAL2FLD_Pos(pCfg->pMuxCfg->multPlex, MDR_LCD_CR_Mux_Pos)
                          | VAL2FLD_Pos(pCfg->pMuxCfg->multBias, MDR_LCD_CR_Bias_Pos));

  MDR_LCD->CR = regValue;
}

void MDR_LCD_DeInit(void)
{
  MDR_LCD->CR = 0;
  MDR_CLOCK->PER2_CLOCK = MDR_MaskClr(MDR_CLOCK->PER2_CLOCK, MDR_RST_PER2__LCD_CLK_EN_Msk);
}

void MDR_LCD_BlinkyStart(MDR_LCD_BlinkFreq  blinkFreq, MDR_OnOff blinkToAlterData)
{
  uint32_t regValue = MDR_LCD->CR;
  
  regValue &= ~(MDR_LCD_CR_BF_Msk | MDR_LCD_CR_AltFlicker_Msk);
  regValue |= (uint32_t)( VAL2FLD_Pos(blinkFreq,        MDR_LCD_CR_BF_Pos)
                        | VAL2FLD_Pos(blinkToAlterData, MDR_LCD_CR_AltFlicker_Pos));    
  MDR_LCD->CR = regValue;
}

void MDR_LCD_BlinkyStop(void)
{
  uint32_t regValue = MDR_LCD->CR;  
  regValue &= ~(MDR_LCD_CR_BF_Msk | MDR_LCD_CR_AltFlicker_Msk);
  MDR_LCD->CR = regValue;
}

#include <MDR_ADCUI_VE4.h>
    
void MDR_ADCUI_InitByCfgRegs(MDR_ADCUI_CfgRegs *cfgRegs)
{
  //  Clock ON
  MDR_ADCUI_ClockEnable();
  
  //  Reset
	MDR_ADCUI->CTRL2	= MDR_ADCUI_CTRL2_Reset_Msk;
	MDR_ADCUI->CTRL2	= 0;
  //  Apply Regs
  MDR_ADCUI->CTRL2   = cfgRegs->regCTRL2;  
  MDR_ADCUI->TST     = MDR_ADCUI_TST_CONST_ONLY;
  MDR_ADCUI->DIGGAIN = MDR_ADCUI_DIGGAIN_CONST_ONLY;
  MDR_ADCUI->ANGAIN  = cfgRegs->regGAIN;
  MDR_ADCUI->CTRL1   = cfgRegs->regCTRL1;
  MDR_ADCUI->INTEN   = cfgRegs->regIRQ;  
  MDR_ADCUI->DMAEN   = cfgRegs->regDMA;    
  //  Clear Status
  MDR_ADCUI->STAT = MDR_ADCUI_EVENT_CLR_OV_ALL;     
}

//  Отключение блока
void MDR_ADCUI_DeInit(void)
{
  //  Reset
	MDR_ADCUI->CTRL2	= MDR_ADCUI_CTRL2_Reset_Msk;
	MDR_ADCUI->CTRL2	= 0;
  //  Apply Regs
  MDR_ADCUI->CTRL2   = 0;  
  MDR_ADCUI->TST     = 0;
  MDR_ADCUI->DIGGAIN = MDR_ADCUI_DIGGAIN_CONST_ONLY;
  MDR_ADCUI->ANGAIN  = 0;
  MDR_ADCUI->CTRL1   = 0;
  MDR_ADCUI->INTEN   = 0;  
  MDR_ADCUI->DMAEN   = 0;    
  //  Clear Status
  MDR_ADCUI->STAT = MDR_ADCUI_EVENT_CLR_OV_ALL;
  
  MDR_ADCUI_ClockDisable();
}

//  ВАРИАНТ1:
//  Настройка и запуск ADCUI по умолчанию - без DMA и усилений, прерывания для всех каналов одинаково.
//  Иначе использовать MDR_ADCUI_Init()
static MDR_ADCUI_CfgRegs ToCfgRegs(MDR_ADCUI_SelCH chanSelect, bool enaIrqOnReady, bool suppressDC, bool useExternalVRef)
{
  MDR_ADCUI_CfgRegs cfgReg;
  
  //  CTRL1  
  if (suppressDC)
    cfgReg.regCTRL1 = chanSelect.Value << MDR_ADCUI_CTRL1_CHP1_EN_Pos;
  else
    cfgReg.regCTRL1 = 0;
  
  //  CTRL2
  if (useExternalVRef)
  {
    cfgReg.regCTRL1 |= MDR_ADCUI_CTRL1_REF_EX_Msk;  
    cfgReg.regCTRL2 = MDR_ADCUI_CTRL2_DEF | MDR_ADCUI_CTRL2_BF_bp_Msk;
  }
  else
    cfgReg.regCTRL2 = MDR_ADCUI_CTRL2_DEF;
  
  //  IRQ
  if (enaIrqOnReady)
    cfgReg.regIRQ = chanSelect.Value << MDR_ADCUI_EVENT_NS1_Pos;
  else
    cfgReg.regIRQ = 0;
  
  cfgReg.regDMA = 0;  
  cfgReg.regGAIN = 0;
  
  return cfgReg;
}

void MDR_ADCUI_InitDef(MDR_ADCUI_SelCH chanSelect, bool enaIrqOnReady, bool SuppressDC, bool useExternalVRef)
{
  MDR_ADCUI_CfgRegs cfgReg = ToCfgRegs(chanSelect, enaIrqOnReady, SuppressDC, useExternalVRef);
  MDR_ADCUI_InitByCfgRegs(&cfgReg);
}

void MDR_ADCUI_InitDefAndStart(MDR_ADCUI_SelCH chanSelect, bool enaIrqOnReady, bool SuppressDC, bool useExternalVRef)
{
  MDR_ADCUI_CfgRegs cfgReg = ToCfgRegs(chanSelect, enaIrqOnReady, SuppressDC, useExternalVRef);
  cfgReg.regCTRL1 |= chanSelect.Value << MDR_ADCUI_CTRL1_ADC1_EN_Pos;
  MDR_ADCUI_InitByCfgRegs(&cfgReg);
}


//  ВАРИАНТ2:
//  Одинаковая настройка каналов, выбранных маской chanSelect
//  doStart - запуск каналов после инициализации
void MDR_ADCUI_Init(MDR_ADCUI_SelCH chanSelect, MDR_ADCUI_Cfg *Cfg, bool useExternalVRef, bool doStart)
{
  MDR_ADCUI_CfgRegs cfgReg;
  
  //  CTRL1  
  if (Cfg->suppressDC)
    cfgReg.regCTRL1 = chanSelect.Value << MDR_ADCUI_CTRL1_CHP1_EN_Pos;
  else
    cfgReg.regCTRL1 = 0;
  if (doStart)
    cfgReg.regCTRL1 |= chanSelect.Value << MDR_ADCUI_CTRL1_ADC1_EN_Pos;
  
  //  CTRL2
  if (useExternalVRef)
  {
    cfgReg.regCTRL1 |= MDR_ADCUI_CTRL1_REF_EX_Msk;  
    cfgReg.regCTRL2 = MDR_ADCUI_CTRL2_DEF | MDR_ADCUI_CTRL2_BF_bp_Msk;
  }
  else
    cfgReg.regCTRL2 = MDR_ADCUI_CTRL2_DEF;
  
  //  IRQ
  if (Cfg->enaIrqOnReady)
    cfgReg.regIRQ = chanSelect.Value << MDR_ADCUI_EVENT_NS1_Pos;
  else
    cfgReg.regIRQ = 0;
  if (Cfg->enaIrqOnOver)
    cfgReg.regIRQ |= chanSelect.Value << MDR_ADCUI_EVENT_OV1_Pos;
  
  //  DMA
  if (Cfg->enaDMA)
    cfgReg.regDMA = chanSelect.Value << MDR_ADCUI_DMAEN_DMA1_EN_Pos;
  else
    cfgReg.regDMA = 0;  
  
  cfgReg.regGAIN = 0;
  
  MDR_ADCUI_InitByCfgRegs(&cfgReg);
}

//  ВАРИАНТ3:
//  Настройка и запуск ADCUI - c заданием настроек для каждого канала
//  chSel_DoStart - запуск каналов после инициализации
void MDR_ADCUI_InitEx(MDR_ADCUI_CfgFull *cfg, MDR_ADCUI_CfgEx *cfgEx)
{
  MDR_ADCUI_CfgRegs cfgReg;
  
  //  CTRL1  
  cfgReg.regCTRL1 = VAL2FLD_Pos(cfg->chSel_DoStart.Value,    MDR_ADCUI_CTRL1_ADC1_EN_Pos)
                  | VAL2FLD_Pos(cfg->chSel_SuppressDC.Value, MDR_ADCUI_CTRL1_CHP1_EN_Pos);
  //  CTRL2
  if (cfgEx == NULL)
    cfgReg.regCTRL2 = MDR_ADCUI_CTRL2_DEF;
  else
    cfgReg.regCTRL2 = MDR_ADCUI_CTRL2_CHOP_Freq_CONST 
                    | VAL2FLD(cfgEx->SFF, MDR_ADCUI_CTRL2_SFF)
                    | VAL2FLD(cfgEx->SFC, MDR_ADCUI_CTRL2_SFC);
  if (cfg->useExternalVRef)
  {
    cfgReg.regCTRL1 |= MDR_ADCUI_CTRL1_REF_EX_Msk;  
    cfgReg.regCTRL2 |= MDR_ADCUI_CTRL2_BF_bp_Msk;
  }
  //  IRQ
  cfgReg.regIRQ =  VAL2FLD_Pos(cfg->chSel_EnaIRQ_OnReady.Value, MDR_ADCUI_EVENT_NS1_Pos)
                | VAL2FLD_Pos(cfg->chSel_EnaIRQ_OnOver.Value , MDR_ADCUI_EVENT_OV1_Pos);
  
  //  DMA
  cfgReg.regDMA = VAL2FLD_Pos(cfg->chSel_EnaDMA.Value, MDR_ADCUI_DMAEN_DMA1_EN_Pos);
  //  Gain
  cfgReg.regGAIN = cfg->gains.Value; 
}



#include <MDR_ADCUI_VK234.h>

//  -------------------   Обнуление регистров блока ------------------
void MDR_ADCUI_ClearRegs(void)
{
  // Global
  MDR_ADCUI->CTRL1 = 0;
  MDR_ADCUI->CTRL2 = 0;
  MDR_ADCUI->CTRL3 = 0;
  
  //  F0
  MDR_ADCUI->F0CTR = 0;
  MDR_ADCUI->F0WC = 0;
  MDR_ADCUI->F0VC = 0;
  MDR_ADCUI->F0AC = 0;
  MDR_ADCUI->F0MD0 = 0;  
  MDR_ADCUI->F0MD1 = 0;  
  MDR_ADCUI->F0VPEAK = 0;  
  MDR_ADCUI->F0IPEAK = 0;  
  MDR_ADCUI->F0STAT = 0;
  MDR_ADCUI->F0MASK = 0;
  //  F1
  MDR_ADCUI->F1CTR = 0;
  MDR_ADCUI->F1WC = 0;
  MDR_ADCUI->F1VC = 0;
  MDR_ADCUI->F1AC = 0;
  MDR_ADCUI->F1MD0 = 0;  
  MDR_ADCUI->F1MD1 = 0;  
  MDR_ADCUI->F1MD2 = 0;  
  MDR_ADCUI->F1VPEAK = 0;  
  MDR_ADCUI->F1IPEAK = 0;  
  MDR_ADCUI->F1STAT = 0;
  MDR_ADCUI->F1MASK = 0;  
  //  F2
  MDR_ADCUI->F2CTR = 0;
  MDR_ADCUI->F2WC = 0;
  MDR_ADCUI->F2VC = 0;
  MDR_ADCUI->F2AC = 0;
  MDR_ADCUI->F2MD0 = 0;  
  MDR_ADCUI->F2MD1 = 0;  
  MDR_ADCUI->F2MD2 = 0;  
  MDR_ADCUI->F2VPEAK = 0;  
  MDR_ADCUI->F2IPEAK = 0;  
  MDR_ADCUI->F2STAT = 0;
  MDR_ADCUI->F2MASK = 0;
  //  Calibrations
  MDR_ADCUI->CCAL1 = 0;
  MDR_ADCUI->CCAL2 = 0;
  MDR_ADCUI->CCAL3 = 0;
  MDR_ADCUI->CCAL4 = 0; 
}

//  -------------------   Запись - чтение регистров с настройками (CfgRegs) ------------------

void MDR_ADCUI_CfgRegs_Apply(const MDR_ADCUI_CfgRegs *pCfgRegs)
{   
  //  F0
  MDR_ADCUI->F0CTR   = pCfgRegs->F0.CTR;
  MDR_ADCUI->F0WC    = pCfgRegs->F0.WC;
  MDR_ADCUI->F0VC    = pCfgRegs->F0.VC;
  MDR_ADCUI->F0AC    = pCfgRegs->F0.AC;
  MDR_ADCUI->F0MD0   = pCfgRegs->F0.MD0;  
  MDR_ADCUI->F0MD1   = pCfgRegs->F0.MD1;  
  MDR_ADCUI->F0VPEAK = 0;  
  MDR_ADCUI->F0IPEAK = 0;  
  MDR_ADCUI->F0STAT  = MDR_ADCUI_STATUS_CLEAR;
  MDR_ADCUI->F0MASK  = pCfgRegs->F0.MASK;
  //  F1
  MDR_ADCUI->F1CTR    = pCfgRegs->F1.CTR;
  MDR_ADCUI->F1WC     = pCfgRegs->F1.WC;
  MDR_ADCUI->F1VC     = pCfgRegs->F1.VC;
  MDR_ADCUI->F1AC     = pCfgRegs->F1.AC;
  MDR_ADCUI->F1MD0    = pCfgRegs->F1.MD0;    
  MDR_ADCUI->F1MD1    = pCfgRegs->F1.MD1; 
  MDR_ADCUI->F1MD2    = pCfgRegs->F1.MD2;  
  MDR_ADCUI->F1VPEAK  = 0;  
  MDR_ADCUI->F1IPEAK  = 0;  
  MDR_ADCUI->F1STAT   = MDR_ADCUI_STATUS_CLEAR;
  MDR_ADCUI->F1MASK   = pCfgRegs->F1.MASK;  
  //  F2
  MDR_ADCUI->F2CTR    = pCfgRegs->F2.CTR;
  MDR_ADCUI->F2WC     = pCfgRegs->F2.WC;
  MDR_ADCUI->F2VC     = pCfgRegs->F2.VC;
  MDR_ADCUI->F2AC     = pCfgRegs->F2.AC;
  MDR_ADCUI->F2MD0    = pCfgRegs->F2.MD0;    
  MDR_ADCUI->F2MD1    = pCfgRegs->F2.MD1; 
  MDR_ADCUI->F2MD2    = pCfgRegs->F2.MD2;  
  MDR_ADCUI->F2VPEAK  = 0;  
  MDR_ADCUI->F2IPEAK  = 0;  
  MDR_ADCUI->F2STAT   = MDR_ADCUI_STATUS_CLEAR;
  MDR_ADCUI->F2MASK   = pCfgRegs->F2.MASK;
  //  Calibrations
  MDR_ADCUI->CCAL1 = pCfgRegs->Cal.CCAL1;
  MDR_ADCUI->CCAL2 = pCfgRegs->Cal.CCAL2;
  MDR_ADCUI->CCAL3 = pCfgRegs->Cal.CCAL3;
  MDR_ADCUI->CCAL4 = pCfgRegs->Cal.CCAL4;  
  
  // Global
  MDR_ADCUI->CTRL2 = pCfgRegs->Ctrl.CTRL2;
  MDR_ADCUI->CTRL3 = pCfgRegs->Ctrl.CTRL3;  
  MDR_ADCUI->CTRL1 = pCfgRegs->Ctrl.CTRL1;
}

void MDR_ADCUI_CfgRegs_Read(MDR_ADCUI_CfgRegs *pCfgRegs)
{  
  // Global
  pCfgRegs->Ctrl.CTRL1 = MDR_ADCUI->CTRL1;
  pCfgRegs->Ctrl.CTRL2 = MDR_ADCUI->CTRL2;
  pCfgRegs->Ctrl.CTRL3 = MDR_ADCUI->CTRL3;  
  //  F0
  pCfgRegs->F0.CTR  = MDR_ADCUI->F0CTR;
  pCfgRegs->F0.WC   = MDR_ADCUI->F0WC;
  pCfgRegs->F0.VC   = MDR_ADCUI->F0VC;
  pCfgRegs->F0.AC   = MDR_ADCUI->F0AC;
  pCfgRegs->F0.MD0  = MDR_ADCUI->F0MD0;
  pCfgRegs->F0.MD1  = MDR_ADCUI->F0MD1;
  pCfgRegs->F0.STAT = MDR_ADCUI->F0STAT;
  pCfgRegs->F0.MASK = MDR_ADCUI->F0MASK;
  //  F1
  pCfgRegs->F1.CTR  = MDR_ADCUI->F1CTR;
  pCfgRegs->F1.WC   = MDR_ADCUI->F1WC;
  pCfgRegs->F1.VC   = MDR_ADCUI->F1VC;
  pCfgRegs->F1.AC   = MDR_ADCUI->F1AC;
  pCfgRegs->F1.MD0  = MDR_ADCUI->F1MD0;
  pCfgRegs->F1.MD1  = MDR_ADCUI->F1MD1;
  pCfgRegs->F1.MD2  = MDR_ADCUI->F1MD2;
  pCfgRegs->F1.STAT = MDR_ADCUI->F1STAT;
  pCfgRegs->F1.MASK = MDR_ADCUI->F1MASK;    
  //  F2
  pCfgRegs->F2.CTR  = MDR_ADCUI->F2CTR;
  pCfgRegs->F2.WC   = MDR_ADCUI->F2WC;
  pCfgRegs->F2.VC   = MDR_ADCUI->F2VC;
  pCfgRegs->F2.AC   = MDR_ADCUI->F2AC;
  pCfgRegs->F2.MD0  = MDR_ADCUI->F2MD0;
  pCfgRegs->F2.MD1  = MDR_ADCUI->F2MD1;
  pCfgRegs->F2.MD2  = MDR_ADCUI->F2MD2;
  pCfgRegs->F2.STAT = MDR_ADCUI->F2STAT;
  pCfgRegs->F2.MASK = MDR_ADCUI->F2MASK;  
  //  Calibrations
  pCfgRegs->Cal.CCAL1 = MDR_ADCUI->CCAL1;
  pCfgRegs->Cal.CCAL2 = MDR_ADCUI->CCAL2;
  pCfgRegs->Cal.CCAL3 = MDR_ADCUI->CCAL3;
  pCfgRegs->Cal.CCAL4 = MDR_ADCUI->CCAL4;
}

void MDR_ADCUI_CfgRegs_Clear(MDR_ADCUI_CfgRegs *pCfgRegs)
{  
  pCfgRegs->Ctrl.CTRL1 = 0;
  pCfgRegs->Ctrl.CTRL2 = 0;
  pCfgRegs->Ctrl.CTRL3 = 0;
  
  pCfgRegs->F0.CTR  = 0;
  pCfgRegs->F0.WC   = 0;
  pCfgRegs->F0.VC   = 0;
  pCfgRegs->F0.AC   = 0;
  pCfgRegs->F0.MD0  = 0;
  pCfgRegs->F0.MD1  = 0;
  pCfgRegs->F0.STAT = 0;
  pCfgRegs->F0.MASK = 0;
    
  pCfgRegs->F1.CTR  = 0;
  pCfgRegs->F1.WC   = 0;
  pCfgRegs->F1.VC   = 0;
  pCfgRegs->F1.AC   = 0;
  pCfgRegs->F1.MD0  = 0;
  pCfgRegs->F1.MD1  = 0;
  pCfgRegs->F1.MD2  = 0;
  pCfgRegs->F1.STAT = 0;
  pCfgRegs->F1.MASK = 0;  
  
  pCfgRegs->F2.CTR  = 0;
  pCfgRegs->F2.WC   = 0;
  pCfgRegs->F2.VC   = 0;
  pCfgRegs->F2.AC   = 0;
  pCfgRegs->F2.MD0  = 0;
  pCfgRegs->F2.MD1  = 0;
  pCfgRegs->F2.MD2  = 0;
  pCfgRegs->F2.STAT = 0;
  pCfgRegs->F2.MASK = 0;    
  
  pCfgRegs->Cal.CCAL1 = 0;
  pCfgRegs->Cal.CCAL2 = 0;
  pCfgRegs->Cal.CCAL3 = 0;
  pCfgRegs->Cal.CCAL4 = 0;
  
  //  Не охота подключать внешние модули
// memset(pCfgRegs, 0, sizeof(MDR_ADCUI_CfgRegs));
  
  //  Ломает стек при вызове из MDR_ADCUI_ToCfgRegs()
//  uint32_t i;
//  uint32_t *pReg32 = (uint32_t *)pCfgRegs;
//  uint32_t cnt = sizeof(MDR_ADCUI_CfgRegs)/sizeof(uint32_t);
//  
//  for (i = 0; i < cnt; ++i)
//    pReg32[i] = 0;
}

//  -------------------   Конвертация настроечных структур в CfgRegs ------------------
//  В структурах параметры сгруппированы по назначению их легче задавать, но конвертация занимает время.

static void ADCUI_F0_ToCfgRegs_loc(const MDR_ADCUI_CfgF0 *cfgF0, MDR_ADCUI_CfgRegs *pCfgRegs)
{
  if (cfgF0->cfgI0 != NULL)
  {
    pCfgRegs->F0.CTR |= ( VAL2FLD_Pos(cfgF0->cfgI0->InpPGA,    MDR_ADCUI_F0CTR_I0GAIN_Pos)
                        | VAL2FLD_Pos(cfgF0->cfgI0->SumEnable, MDR_ADCUI_F0CTR_I0NTEN_Pos));
    pCfgRegs->F0.MD0 |=   VAL2FLD_Pos(cfgF0->cfgI0->ADC_x2,    MDR_ADCUI_F0MD0_I0GAIN_Pos);
  }
  if (cfgF0->cfgV0 != NULL)
  {
    pCfgRegs->F0.CTR |=   VAL2FLD_Pos(cfgF0->cfgV0->InpPGA,    MDR_ADCUI_F0CTR_V0GAIN_Pos);
    pCfgRegs->F0.MD0 |=   VAL2FLD_Pos(cfgF0->cfgV0->ADC_x2,    MDR_ADCUI_F0MD0_V0GAIN_Pos);
  }        
  if (cfgF0->cfgI3 != NULL)
  {
    pCfgRegs->F0.CTR |= ( VAL2FLD_Pos(cfgF0->cfgI3->InpPGA,    MDR_ADCUI_F0CTR_I3GAIN_Pos)
                        | VAL2FLD_Pos(cfgF0->cfgI3->SumEnable, MDR_ADCUI_F0CTR_I3NTEN_Pos));
    pCfgRegs->F0.MD0 |=   VAL2FLD_Pos(cfgF0->cfgI3->ADC_x2,    MDR_ADCUI_F0MD0_I3GAIN_Pos);
  }
  
  pCfgRegs->F0.MD0 |= ( VAL2FLD_Pos(cfgF0->srcVDAT,  MDR_ADCUI_F0MD0_V0SEL_Pos)
                      | VAL2FLD_Pos(cfgF0->srcIDAT,  MDR_ADCUI_F0MD0_I0SEL_Pos)
                      | VAL2FLD_Pos(cfgF0->srcI3DAT, MDR_ADCUI_F0MD0_I3SEL_Pos));
  
  if (cfgF0->cfgLims != NULL)
    pCfgRegs->F0.MD1 |= ( VAL2FLD(cfgF0->cfgLims->Imax, MDR_ADCUI_FxMD1_IPKLVL)
                        | VAL2FLD(cfgF0->cfgLims->Umax, MDR_ADCUI_FxMD1_VPKLVL));
  
  if (cfgF0->cfgPower != NULL)
  {
    pCfgRegs->F0.CTR |= ( VAL2FLD_Pos(cfgF0->cfgPower->dPhaseTune_V,      MDR_ADCUI_F0CTR_VPHASE_Pos)
                        | VAL2FLD_Pos(cfgF0->cfgPower->cfgRMS.RMStoEf,    MDR_ADCUI_F0CTR_VASEL_Pos)
                        |     VAL2FLD(cfgF0->cfgPower->cfgRMS.biasIRMS,   MDR_ADCUI_F0CTR_IRMSOS));
    
    pCfgRegs->F0.MD0 |=  VAL2FLD_Pos(cfgF0->cfgPower->selectI,      MDR_ADCUI_F0MD0_SEL_I_CH_Pos);
    pCfgRegs->F0.WC |= ( VAL2FLD_Pos(cfgF0->cfgPower->rescPa.bias,  MDR_ADCUI_FxWC_WATTOS_Pos)
                       | VAL2FLD_Pos(cfgF0->cfgPower->rescPa.gain,  MDR_ADCUI_FxWC_WGAIN_Pos)
                       );
    pCfgRegs->F0.VC |= ( VAL2FLD_Pos(cfgF0->cfgPower->rescPr.bias,  MDR_ADCUI_FxVC_VAROS_Pos)
                       | VAL2FLD_Pos(cfgF0->cfgPower->rescPr.gain,  MDR_ADCUI_FxVC_VARGAIN_Pos)
                        );
    pCfgRegs->F0.AC |= ( VAL2FLD(cfgF0->cfgPower->cfgRMS.biasVRMS,  MDR_ADCUI_FxAC_VRMSOS)
                       | VAL2FLD(cfgF0->cfgPower->cfgRMS.gainPf,    MDR_ADCUI_FxAC_VAGAIN));    
  }
}

static void ADCUI_Fx_ToCfgRegs_loc(const MDR_ADCUI_CfgFx *cfgFx, MDR_ADCUI_CfgRegs *pCfgRegs)
{
  if (cfgFx->cfgI != NULL)
  {
    pCfgRegs->F1.CTR |= ( VAL2FLD_Pos(cfgFx->cfgI->InpPGA,    MDR_ADCUI_FxCTR_IGAIN_Pos)
                        | VAL2FLD_Pos(cfgFx->cfgI->SumEnable, MDR_ADCUI_FxCTR_INTEN_Pos));
    pCfgRegs->F1.MD0 |=   VAL2FLD_Pos(cfgFx->cfgI->ADC_x2,    MDR_ADCUI_FxMD0_IGAIN_Pos);
  }
  if (cfgFx->cfgV != NULL)
  {
    pCfgRegs->F1.CTR |=   VAL2FLD_Pos(cfgFx->cfgV->InpPGA,    MDR_ADCUI_FxCTR_VGAIN_Pos);
    pCfgRegs->F1.MD0 |=   VAL2FLD_Pos(cfgFx->cfgV->ADC_x2,    MDR_ADCUI_FxMD0_VGAIN_Pos);    
  }
  
  pCfgRegs->F1.MD0 |= ( VAL2FLD_Pos(cfgFx->srcVDAT,  MDR_ADCUI_FxMD0_VSEL_Pos)
                      | VAL2FLD_Pos(cfgFx->srcIDAT,  MDR_ADCUI_FxMD0_ISEL_Pos));
  
  if (cfgFx->cfgLims != NULL)
    pCfgRegs->F1.MD1 |= ( VAL2FLD(cfgFx->cfgLims->Imax, MDR_ADCUI_FxMD1_IPKLVL)
                        | VAL2FLD(cfgFx->cfgLims->Umax, MDR_ADCUI_FxMD1_VPKLVL));
  
  if (cfgFx->cfgPower != NULL)
  {
    pCfgRegs->F1.CTR |= ( VAL2FLD_Pos(cfgFx->cfgPower->dPhaseTune_V,      MDR_ADCUI_FxCTR_VPHASE_Pos)
                        | VAL2FLD_Pos(cfgFx->cfgPower->cfgRMS.RMStoEf,    MDR_ADCUI_FxCTR_VASEL_Pos)
                        |     VAL2FLD(cfgFx->cfgPower->cfgRMS.biasIRMS,   MDR_ADCUI_FxCTR_IRMSOS));
    
    pCfgRegs->F1.WC |= ( VAL2FLD_Pos(cfgFx->cfgPower->rescPa.bias,  MDR_ADCUI_FxWC_WATTOS_Pos)
                       | VAL2FLD_Pos(cfgFx->cfgPower->rescPa.gain,  MDR_ADCUI_FxWC_WGAIN_Pos)
                       );
    pCfgRegs->F1.VC |= ( VAL2FLD_Pos(cfgFx->cfgPower->rescPr.bias,  MDR_ADCUI_FxVC_VAROS_Pos)
                       | VAL2FLD_Pos(cfgFx->cfgPower->rescPr.gain,  MDR_ADCUI_FxVC_VARGAIN_Pos)
                       );
    pCfgRegs->F1.AC |= ( VAL2FLD(cfgFx->cfgPower->cfgRMS.biasVRMS,  MDR_ADCUI_FxAC_VRMSOS)
                       | VAL2FLD(cfgFx->cfgPower->cfgRMS.gainPf,    MDR_ADCUI_FxAC_VAGAIN));    
  }
}

void MDR_ADCUI_ToCfgRegs(const MDR_ADCUI_Cfg *pCfg, MDR_ADCUI_CfgRegs *pCfgRegs)
{
  MDR_ADCUI_CfgRegs_Clear(pCfgRegs);
  
  // cfgBase
  pCfgRegs->Ctrl.CTRL1 = (  VAL2FLD_Pos(pCfg->cfgBase->sampleRate, MDR_ADCUI_CTRL1_OSR_CONF_Pos)
                          | VAL2FLD_Pos(pCfg->cfgBase->dataBits24, MDR_ADCUI_CTRL1_RESOL_Pos)
                          | VAL2FLD_Pos(pCfg->cfgBase->IBoost,     MDR_ADCUI_CTRL1_IBOOST_Pos)
                          | VAL2FLD_Pos(pCfg->cfgBase->updateRMS,  MDR_ADCUI_CTRL1_ZXRMS_Pos));
  
  if (pCfg->cfgBase->selectVref == ADCUI_Vref_External)
    pCfgRegs->Ctrl.CTRL1 |= MDR_ADCUI_CTRL1_VREF_SEL_Msk;
  else if (pCfg->cfgBase->selectVref == ADCUI_Vref_Internal)
    pCfgRegs->Ctrl.CTRL1 |= MDR_ADCUI_CTRL1_BUF_BYP_Msk;
  
  // cfgNoLoad
  if (pCfg->cfgNoLoad != NULL)
    pCfgRegs->Ctrl.CTRL1 |= ( VAL2FLD_Pos(pCfg->cfgNoLoad->noLoadPa, MDR_ADCUI_CTRL1_APNOLOAD_Pos)
                            | VAL2FLD_Pos(pCfg->cfgNoLoad->noLoadPr, MDR_ADCUI_CTRL1_VARNOLOAD_Pos)
                            | VAL2FLD_Pos(pCfg->cfgNoLoad->noLoadPf, MDR_ADCUI_CTRL1_VANOLOAD_Pos));
  // cfgV
  if (pCfg->cfgV != NULL)
  {
    pCfgRegs->Ctrl.CTRL1 |= ( VAL2FLD_Pos(pCfg->cfgV->Vcrs0_LFPEn,      MDR_ADCUI_CTRL1_ZXLPF_Pos)
                            | VAL2FLD_Pos(pCfg->cfgV->VPer_DetectOn,    MDR_ADCUI_CTRL1_FREQSEL_Pos)
                            | VAL2FLD_Pos(pCfg->cfgV->VPer_DetectAver,  MDR_ADCUI_CTRL1_PER_Length_Pos));
    
    pCfgRegs->Ctrl.CTRL2 =  ( VAL2FLD_Pos(pCfg->cfgV->Vmin_Level,       MDR_ADCUI_CTRL2_SAGLVL_Pos)
                            | VAL2FLD_Pos(pCfg->cfgV->Vmin_HalfPeriods, MDR_ADCUI_CTRL2_SAGCYC_Pos));
    
    pCfgRegs->Ctrl.CTRL3 =  (uint32_t)pCfg->cfgV->Vcrs0_Timeout;
  }
  
  // cfgChop
  if (pCfg->cfgChop != NULL)
    pCfgRegs->Ctrl.CTRL1 |= ( VAL2FLD_Pos(pCfg->cfgChop->chopEna, MDR_ADCUI_CTRL1_CHOP_EN_Pos)
                            | VAL2FLD_Pos(pCfg->cfgChop->chopDiv, MDR_ADCUI_CTRL1_CHOP_FREQ_Pos));
  
  //  cfgF0
  if (pCfg->cfgF0 != NULL)
    ADCUI_F0_ToCfgRegs_loc(pCfg->cfgF0, pCfgRegs);
  //  cfgF1
  if (pCfg->cfgF1 != NULL)
    ADCUI_Fx_ToCfgRegs_loc(pCfg->cfgF1, pCfgRegs);
  //  cfgF2
  if (pCfg->cfgF2 != NULL)
    ADCUI_Fx_ToCfgRegs_loc(pCfg->cfgF2, pCfgRegs);
    
  //  cfgCalibr
  if (pCfg->cfgCalibr != NULL)
  {
    pCfgRegs->Cal.CCAL1 |= ( VAL2FLD(pCfg->cfgCalibr->V0BGain, MDR_ADCUI_CCAL1_V0BGAIN)
                           | VAL2FLD(pCfg->cfgCalibr->I0BGain, MDR_ADCUI_CCAL1_I0BGAIN));
    pCfgRegs->Cal.CCAL2 |= ( VAL2FLD(pCfg->cfgCalibr->V1BGain, MDR_ADCUI_CCAL2_V1BGAIN)
                           | VAL2FLD(pCfg->cfgCalibr->I1BGain, MDR_ADCUI_CCAL2_I1BGAIN));
    pCfgRegs->Cal.CCAL3 |= ( VAL2FLD(pCfg->cfgCalibr->V2BGain, MDR_ADCUI_CCAL3_V2BGAIN)
                           | VAL2FLD(pCfg->cfgCalibr->I2BGain, MDR_ADCUI_CCAL3_I2BGAIN));
    pCfgRegs->Cal.CCAL4 |=   VAL2FLD(pCfg->cfgCalibr->I3BGain, MDR_ADCUI_CCAL4_I3BGAIN);    
  }
  
  //  Set Enable 
  pCfgRegs->Ctrl.CTRL1 |= pCfg->selFxEn.SelMask & MDR_ADCUI_FxMask;
}



//  -------------------   Инициализация блока ------------------
void MDR_ADCUI_DeInit(void)
{
  //  Включение тактирования
  MDR_ADCUI_ClockOn();  
  //  Обнуление регистров
  MDR_ADCUI_ClearRegs();    
  //  Включение тактирования
  MDR_ADCUI_ClockOff();  
}

void MDR_ADCUI_Reset(void)
{
  MDR_ADCUI->CTRL1 = MDR_ADCUI_CTRL1_RESET_DIG_Msk;  
  MDR_ADCUI->CTRL1 = 0;
}

void MDR_ADCUI_Init_ByCfgRegs(const MDR_ADCUI_CfgRegs *pCfg)
{
  //  Включение тактирования
  MDR_ADCUI_ClockOn();
  
  MDR_ADCUI_Reset();
  MDR_ADCUI_CfgRegs_Apply(pCfg);
}

void MDR_ADCUI_Init(const MDR_ADCUI_Cfg *pCfg)
{
  MDR_ADCUI_CfgRegs CfgRegs;
  
  MDR_ADCUI_ClockOn();
  MDR_ADCUI_ClearRegs();
  
  MDR_ADCUI_ToCfgRegs(pCfg, &CfgRegs);
  MDR_ADCUI_CfgRegs_Apply(&CfgRegs);
}


// ==============    Чтение данных с АЦП ===========

uint32_t MDR_ADCUI_WaitAndRead_V0(void)
{
  MDR_WaitFlagClear((uint32_t)&MDR_ADCUI->F0STAT, MDR_ADCUI_FxSTAT_VF_EMP_Msk);
  return MDR_ADCUI->F0VDAT;
}

uint32_t MDR_ADCUI_WaitAndRead_I0(void) 
{
  MDR_WaitFlagClear((uint32_t)&MDR_ADCUI->F0STAT, MDR_ADCUI_FxSTAT_IF_EMP_Msk);
  return MDR_ADCUI->F0I0DAT;  
}
uint32_t MDR_ADCUI_WaitAndRead_I3(void) 
{
  MDR_WaitFlagClear((uint32_t)&MDR_ADCUI->F0STAT, MDR_ADCUI_F0STAT_I3F_EMP_Msk);
  return MDR_ADCUI->F0I3DAT;  
}

uint32_t MDR_ADCUI_WaitAndRead_V1(void) 
{
  MDR_WaitFlagClear((uint32_t)&MDR_ADCUI->F1STAT, MDR_ADCUI_FxSTAT_VF_EMP_Msk);
  return MDR_ADCUI->F1VDAT;  
}
uint32_t MDR_ADCUI_WaitAndRead_I1(void) 
{
  MDR_WaitFlagClear((uint32_t)&MDR_ADCUI->F1STAT, MDR_ADCUI_FxSTAT_IF_EMP_Msk);
  return MDR_ADCUI->F1IDAT;
}
uint32_t MDR_ADCUI_WaitAndRead_V2(void) 
{
  MDR_WaitFlagClear((uint32_t)&MDR_ADCUI->F2STAT, MDR_ADCUI_FxSTAT_VF_EMP_Msk);
  return MDR_ADCUI->F2VDAT;    
}
uint32_t MDR_ADCUI_WaitAndRead_I2(void) 
{
  MDR_WaitFlagClear((uint32_t)&MDR_ADCUI->F2STAT, MDR_ADCUI_FxSTAT_IF_EMP_Msk);
  return MDR_ADCUI->F2IDAT;  
}

  



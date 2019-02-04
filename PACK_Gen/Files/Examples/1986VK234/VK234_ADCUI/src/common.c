#include "common.h"

//  Reg Address
static const volatile uint32_t * RegF0_Addr[] = {
    (&MDR_ADCUI->F0I0DAT)   // res_ADC_I,
  , (&MDR_ADCUI->F0VDAT)    // res_ADC_V,
  , (&MDR_ADCUI->F0I3DAT)   // res_ADC_I3,
  
  , (&MDR_ADCUI->F0IRMS)    // res_IRMS,
  , (&MDR_ADCUI->F0VRMS)    // res_VRMS,
  
  , (&MDR_ADCUI->F0I0DAT)   // res_Pa,
  , (&MDR_ADCUI->F0I0DAT)   // res_Pr,
  , (&MDR_ADCUI->F0I0DAT)   // res_Pf,

  , (&MDR_ADCUI->F0WATTP)   // res_Eap,
  , (&MDR_ADCUI->F0WATTN)   // res_Ean,
  , (&MDR_ADCUI->F0VARP)    // res_Erp,
  , (&MDR_ADCUI->F0VARN)    // res_Ern,
  , (&MDR_ADCUI->F0VR)      // res_Ef  
};

static const volatile uint32_t * RegF1_Addr[] = {
    (&MDR_ADCUI->F1IDAT)    // res_ADC_I,
  , (&MDR_ADCUI->F1VDAT)    // res_ADC_V,
  , (&MDR_ADCUI->F1IDAT)    // res_ADC_I3 - Not Used
  
  , (&MDR_ADCUI->F1IRMS)    // res_IRMS,
  , (&MDR_ADCUI->F1VRMS)    // res_VRMS,
  
  , (&MDR_ADCUI->F1IDAT)    // res_Pa,
  , (&MDR_ADCUI->F1IDAT)    // res_Pr,
  , (&MDR_ADCUI->F1IDAT)    // res_Pf,

  , (&MDR_ADCUI->F1WATTP)   // res_Eap,
  , (&MDR_ADCUI->F1WATTN)   // res_Ean,
  , (&MDR_ADCUI->F1VARP)    // res_Erp,
  , (&MDR_ADCUI->F1VARN)    // res_Ern,
  , (&MDR_ADCUI->F1VR)      // res_Ef  
};

static const volatile uint32_t * RegF2_Addr[] = {
    (&MDR_ADCUI->F2IDAT)    // res_ADC_I,
  , (&MDR_ADCUI->F2VDAT)    // res_ADC_V,
  , (&MDR_ADCUI->F2IDAT)    // res_ADC_I3 - Not Used
  
  , (&MDR_ADCUI->F2IRMS)    // res_IRMS,
  , (&MDR_ADCUI->F2VRMS)    // res_VRMS,
  
  , (&MDR_ADCUI->F2IDAT)    // res_Pa,
  , (&MDR_ADCUI->F2IDAT)    // res_Pr,
  , (&MDR_ADCUI->F2IDAT)    // res_Pf,

  , (&MDR_ADCUI->F2WATTP)   // res_Eap,
  , (&MDR_ADCUI->F2WATTN)   // res_Ean,
  , (&MDR_ADCUI->F2VARP)    // res_Erp,
  , (&MDR_ADCUI->F2VARN)    // res_Ern,
  , (&MDR_ADCUI->F2VR)      // res_Ef  
};

static const uint32_t MD0_SelDAT[13] = {
    VAL2FLD_Pos(ADCUI_IDAT_I,    MDR_ADCUI_F0MD0_I0SEL_Pos)    // res_ADC_I,
  , 0    // res_ADC_V,
  , 0    // res_ADC_I3  
  , 0    // res_IRMS,
  , 0    // res_VRMS,  
  , VAL2FLD_Pos(ADCUI_VDAT_Pact,    MDR_ADCUI_F0MD0_I0SEL_Pos)    // res_Pa,
  , VAL2FLD_Pos(ADCUI_VDAT_Prea,    MDR_ADCUI_F0MD0_I0SEL_Pos)    // res_Pr,
  , VAL2FLD_Pos(ADCUI_VDAT_Pfull,   MDR_ADCUI_F0MD0_I0SEL_Pos)    // res_Pf,
  , 0    // res_Eap,
  , 0    // res_Ean,
  , 0    // res_Erp,
  , 0    // res_Ern,
  , 0    // res_Ef  
};

void ADCUI_SwitchSelDAT(ADCUI_Ch ch, ADCUI_DataID dataID)
{
  switch (ch)
  {
    case ch_F0: 
      //  Выбор того, что будет сохраняться в регистр MDR_ADCUI->F1IDAT - I/V, Pact, Prea, Pfull
      if (MD0_SelDAT[dataID] != 0)
        MDR_ADCUI->F0MD0 = (MDR_ADCUI->F0MD0 & ~MDR_ADCUI_F0MD0_I0SEL_Msk) | MD0_SelDAT[dataID];
      return;
    case ch_F1: 
      if (MD0_SelDAT[dataID] != 0)
        MDR_ADCUI->F1MD0 = (MDR_ADCUI->F1MD0 & ~MDR_ADCUI_F0MD0_I0SEL_Msk) | MD0_SelDAT[dataID];
      return;
    case ch_F2: 
      if (MD0_SelDAT[dataID] != 0)
        MDR_ADCUI->F2MD0 = (MDR_ADCUI->F2MD0 & ~MDR_ADCUI_F0MD0_I0SEL_Msk) | MD0_SelDAT[dataID];
      return;
  }    
}

#define WRONG_RESULT    0xAAAAAUL

uint32_t ADCUI_GetResult(ADCUI_Ch ch, ADCUI_DataID dataID)
{
  switch (ch)
  {
    case ch_F0: return REG32_C(RegF0_Addr[dataID]);
    case ch_F1: return REG32_C(RegF1_Addr[dataID]);
    case ch_F2: return REG32_C(RegF2_Addr[dataID]);
  }
  return WRONG_RESULT;
}


//  Global Vars
ADCUI_Ch      Cfg_ActiveCh = CH_MIN;
ADCUI_DataID  Cfg_ActiveDataID = DataID_MIN;

ADCUI_Ch CfgChannel_Inc(void)
{
  if (Cfg_ActiveCh < CH_MAX)
  {
    ++Cfg_ActiveCh;
    if (Cfg_ActiveDataID == res_ADC_I3)
      Cfg_ActiveDataID = res_ADC_I;
  }
  else
    Cfg_ActiveCh = CH_MIN;
  
  return Cfg_ActiveCh;
}

ADCUI_Ch CfgChannel_Dec(void)
{
  if (Cfg_ActiveCh > CH_MIN)
    --Cfg_ActiveCh;
  else
    Cfg_ActiveCh = CH_MAX;
  
  if ((Cfg_ActiveCh != CH_MIN) && (Cfg_ActiveDataID == res_ADC_I3))
    Cfg_ActiveDataID = res_ADC_I;
  
  return Cfg_ActiveCh;
}

ADCUI_DataID CfgDataID_Inc(void)
{
  if (Cfg_ActiveDataID < DataID_MAX)
  {
    ++Cfg_ActiveDataID;
    if ((Cfg_ActiveCh != CH_MIN) && (Cfg_ActiveDataID == res_ADC_I3))
      ++Cfg_ActiveDataID;
  }
  else
    Cfg_ActiveDataID = DataID_MIN;
  
  return Cfg_ActiveDataID;
}

ADCUI_DataID CfgDataID_Dec(void)
{
  if (Cfg_ActiveDataID > DataID_MIN)
  {
    --Cfg_ActiveDataID;
    if ((Cfg_ActiveCh != CH_MIN) && (Cfg_ActiveDataID == res_ADC_I3))
      --Cfg_ActiveDataID;    
  }
  else
    Cfg_ActiveDataID = DataID_MAX;
  
  return Cfg_ActiveDataID;
}


static LCD_HTD_REG128 my_LCD_Reg128;

void LCD_ShowResult(uint32_t value, ADCUI_Ch ch, ADCUI_DataID dataID)
{
  char message[LCD_SCREEN_WIDTH];
  
  MDRB_HTD_RegClear(&my_LCD_Reg128);
  
  switch (ch)
  {
    case ch_F0: my_LCD_Reg128.LCD_REG2_b.s33_F1_A = 1; break;
    case ch_F1: my_LCD_Reg128.LCD_REG2_b.s34_F2_B = 1; break;
    case ch_F2: my_LCD_Reg128.LCD_REG2_b.s35_F3_C = 1; break;
  }

  switch (dataID)
  {    
  //  V (VRMS) or A (IRMS) + Circle for I3
  case res_ADC_I:
    my_LCD_Reg128.LCD_REG4  = LCD_R4_N6_A;
    break;
  case res_ADC_V:
    my_LCD_Reg128.LCD_REG4  = LCD_R4_V;
    break;
  case res_ADC_I3:
    my_LCD_Reg128.LCD_REG4  = LCD_R4_N6_A | LCD_R4_Circ;
    break;
  
  //  SUM (Ef) + V (VRMS) or A (IRMS)
  case res_IRMS:
    my_LCD_Reg128.LCD_REG2 |= LCD_R2_SUM;
    my_LCD_Reg128.LCD_REG4  = LCD_R4_N6_A;
    break;
  case res_VRMS:
    my_LCD_Reg128.LCD_REG2 |= LCD_R2_SUM;
    my_LCD_Reg128.LCD_REG4  = LCD_R4_V;
    break;
    
  // Power - A (Ea), R (Er), SUM (Ef)
  case res_Pa:    my_LCD_Reg128.LCD_REG1 |= LCD_R1_T1_A; break;
  case res_Pr:    my_LCD_Reg128.LCD_REG1 |= LCD_R1_T4_R; break;
  case res_Pf:    my_LCD_Reg128.LCD_REG2 |= LCD_R2_SUM; break;

  // Energy - Time + A (Ea), R (Er), SUM (Ef) + Pos (->), Neg (<-)
  //  Active Energy
  case res_Eap:   
    my_LCD_Reg128.LCD_REG1 |= LCD_R1_T1_A | LCD_R1_T2_Ar; 
    my_LCD_Reg128.LCD_REG2 |= LCD_R2_Time; 
    break;
  case res_Ean:   
    my_LCD_Reg128.LCD_REG1 |= LCD_R1_T1_A | LCD_R1_T3_Al; 
    my_LCD_Reg128.LCD_REG2 |= LCD_R2_Time; 
    break;
  //  Reactive Energy     
  case res_Erp:   
    my_LCD_Reg128.LCD_REG1 |= LCD_R1_T4_R | LCD_R1_T6_Rr; 
    my_LCD_Reg128.LCD_REG2 |= LCD_R2_Time; 
    break;
  case res_Ern:   
    my_LCD_Reg128.LCD_REG1 |= LCD_R1_T4_R | LCD_R1_T5_Rl; 
    my_LCD_Reg128.LCD_REG2 |= LCD_R2_Time; 
    break;
  //  Full Energy      
  case res_Ef:    my_LCD_Reg128.LCD_REG2 |= LCD_R2_SUM | LCD_R2_Time; break;
  }

  //  Print DATA
  sprintf(message , " %8d", value);  
  MDRB_HTD_RegPring(&my_LCD_Reg128, message);
  
  
  MDRB_HTD_RegApply(&my_LCD_Reg128);
}


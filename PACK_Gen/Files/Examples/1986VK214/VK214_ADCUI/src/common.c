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

void ADCUI_SwitchSelDAT(ADCUI_DataID dataID)
{
  //  Выбор того, что будет сохраняться в регистр MDR_ADCUI->F1IDAT - I/V, Pact, Prea, Pfull
  if (MD0_SelDAT[dataID] != 0)
    MDR_ADCUI->F0MD0 = (MDR_ADCUI->F0MD0 & ~MDR_ADCUI_F0MD0_I0SEL_Msk) | MD0_SelDAT[dataID];
}

uint32_t ADCUI_GetResult(ADCUI_DataID dataID)
{
  return REG32_C(RegF0_Addr[dataID]);
}

ADCUI_DataID  Cfg_ActiveDataID;

//  Global Vars
ADCUI_DataID CfgDataID_Inc(void)
{
  if (Cfg_ActiveDataID < DataID_MAX)
    ++Cfg_ActiveDataID;
  else
    Cfg_ActiveDataID = DataID_MIN;
  
  return Cfg_ActiveDataID;
}

ADCUI_DataID CfgDataID_Dec(void)
{
  if (Cfg_ActiveDataID > DataID_MIN)
    --Cfg_ActiveDataID;
  else
    Cfg_ActiveDataID = DataID_MAX;
  
  return Cfg_ActiveDataID;
}



static LCD_XT_DATA LCD_Data;

void LCD_ShowResult(uint32_t value, ADCUI_DataID dataID)
{
  char message[LCD_SCREEN_WIDTH];
  
  MDRB_XT_DataClear(&LCD_Data);

  switch (dataID)
  {    
  //  V (VRMS) or A (IRMS) + Circle for I3
  case res_ADC_I:
    LCD_Data.LCD_ROW1_b.s21_VA_A  = MDR_On;
    break;
  case res_ADC_V:
    LCD_Data.LCD_ROW2_b.s20_VA_V  = MDR_On;
    break;
  case res_ADC_I3:
    LCD_Data.LCD_ROW1_b.s21_VA_A  = MDR_On;
    LCD_Data.LCD_ROW3_b.s22_Circ_3 = MDR_On;
    break;
  //  SUM (Ef) + V (VRMS) or A (IRMS)
  case res_IRMS:
    LCD_Data.LCD_ROW1_b.s21_VA_A  = MDR_On;
    LCD_Data.LCD_ROW4_b.s3_Plus_H   = MDR_On;
    LCD_Data.LCD_ROW4_b.s23_Plus_V  = MDR_On;  
    break;
  case res_VRMS:
    LCD_Data.LCD_ROW2_b.s20_VA_V  = MDR_On;
    LCD_Data.LCD_ROW4_b.s3_Plus_H   = MDR_On;
    LCD_Data.LCD_ROW4_b.s23_Plus_V  = MDR_On;  
    break;
    
  // Power - A (Ea), R (Er), SUM (Ef)
  case res_Pa: LCD_Data.LCD_ROW1_b.s19_A_plus = MDR_On; break;
  case res_Pr: LCD_Data.LCD_ROW3_b.s19_R_Plus = MDR_On; break;
  case res_Pf:
    LCD_Data.LCD_ROW4_b.s3_Plus_H   = MDR_On;
    LCD_Data.LCD_ROW4_b.s23_Plus_V  = MDR_On;
    break;
  // Energy - Time + A (Ea), R (Er), SUM (Ef) + Pos (->), Neg (<-)
  //  Active Energy
  case res_Eap:
    LCD_Data.LCD_ROW1_b.s19_A_plus  = MDR_On;
    LCD_Data.LCD_ROW4_b.s18_Time    = MDR_On;
    break;
  case res_Ean:   
    LCD_Data.LCD_ROW2_b.s19_A_minus = MDR_On; 
    LCD_Data.LCD_ROW4_b.s18_Time    = MDR_On;
    break;
  //  Reactive Energy     
  case res_Erp:   
    LCD_Data.LCD_ROW3_b.s19_R_Plus  = MDR_On;
    LCD_Data.LCD_ROW4_b.s18_Time    = MDR_On;
    break;
  case res_Ern:   
    LCD_Data.LCD_ROW4_b.s19_R_Minus = MDR_On;
    LCD_Data.LCD_ROW4_b.s18_Time    = MDR_On;
    break;
  //  Full Energy      
  case res_Ef:    
    LCD_Data.LCD_ROW4_b.s3_Plus_H   = MDR_On;
    LCD_Data.LCD_ROW4_b.s23_Plus_V  = MDR_On;
    LCD_Data.LCD_ROW4_b.s18_Time    = MDR_On;
    break;
  }

  //  Print DATA
  sprintf(message , "%8d", value);  
  MDRB_XT_DataWriteStr(&LCD_Data, message);
  
  MDRB_XT_DataApply(&LCD_Data, MDR_Off);
}


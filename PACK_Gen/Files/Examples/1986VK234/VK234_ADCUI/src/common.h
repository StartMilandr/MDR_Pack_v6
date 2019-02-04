#ifndef COMMON_H
#define COMMON_H

#include <MDRB_LCD.h>

typedef enum {
  res_ADC_I,
  res_ADC_V,
  res_ADC_I3,
  
  res_IRMS,
  res_VRMS,
  
  res_Pa,
  res_Pr,
  res_Pf,

  res_Eap,
  res_Ean,
  res_Erp,
  res_Ern,
  res_Ef
} ADCUI_DataID;

#define DataID_MIN  res_ADC_I 
#define DataID_MAX  res_Ef 

typedef enum {
  ch_F0,
  ch_F1,
  ch_F2
} ADCUI_Ch;

#define CH_MIN    ch_F0 
#define CH_MAX    ch_F2 

extern ADCUI_Ch      Cfg_ActiveCh;
extern ADCUI_DataID  Cfg_ActiveDataID;

ADCUI_Ch      CfgChannel_Inc(void);
ADCUI_Ch      CfgChannel_Dec(void);
ADCUI_DataID  CfgDataID_Inc(void);
ADCUI_DataID  CfgDataID_Dec(void);

void     ADCUI_SwitchSelDAT(ADCUI_Ch ch, ADCUI_DataID dataID);
uint32_t ADCUI_GetResult   (ADCUI_Ch ch, ADCUI_DataID dataID);

void LCD_ShowResult(uint32_t value, ADCUI_Ch ch, ADCUI_DataID dataID);


#endif // COMMON_H

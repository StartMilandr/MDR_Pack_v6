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

extern ADCUI_DataID  Cfg_ActiveDataID;

ADCUI_DataID  CfgDataID_Inc(void);
ADCUI_DataID  CfgDataID_Dec(void);

void     ADCUI_SwitchSelDAT(ADCUI_DataID dataID);
uint32_t ADCUI_GetResult   (ADCUI_DataID dataID);

void LCD_ShowResult(uint32_t value, ADCUI_DataID dataID);


#endif // COMMON_H

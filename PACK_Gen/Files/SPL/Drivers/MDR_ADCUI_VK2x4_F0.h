#ifndef _MDR_ADCIU_VK2x4_F0_H
#define _MDR_ADCIU_VK2x4_F0_H

#include <MDR_ADCUI_VK2x4_defs.h>

//  =========   Settings for F0 (Fx) channels  ===========
typedef struct  {
  MDR_ADCUI_PGA InpPGA;               //  FxCTR.I0Gain, FxCTR.I3Gain - x2, x4, x8, x16  
  MDR_OnOff     ADC_x2;               //  FxMD0.I0Gain, FxMD0.I3Gain - x2 enable
  MDR_OnOff     SumEnable;            //  FxCTR.I0NTEn, FxCTR.I3NTEn
} MDR_ADCUI_CfgIx;

typedef struct  {
  MDR_ADCUI_PGA InpPGA;               //  FxCTR.VxGain - x2, x4, x8, x16
  MDR_OnOff     ADC_x2;               //  FxMD0.V0Gain - x2 enable
} MDR_ADCUI_CfgVx;

typedef struct  {
  uint16_t      bias;                 //  FxWC.WATTOS, FxVC.VAROS
  uint16_t      gain;                 //  FxWC.WGAIN,  FxVC.VARGain
} MDR_ADCUI_CfgRescale;

typedef struct  {
  MDR_OnOff     RMStoEf;           //  FxCTR.VASEL  
  uint16_t      biasIRMS;             //  FxCTR.IRMSOS
  uint16_t      biasVRMS;             //  FxAC.VRMSOS
  uint16_t      gainPf;               //  FxAC.VAGain
  uint16_t      reserved;
} MDR_ADCUI_CfgRMS;

typedef struct  {
  //  Input Adjust
  MDR_ADCUI_SelI        selectI;                //  FxMD0.Sel_I_Ch
  uint32_t              dPhaseTune_V;           //  FxCTR.VPhase
  //  Active and Resctive Power rescale
  MDR_ADCUI_CfgRescale  rescPa;
  MDR_ADCUI_CfgRescale  rescPr;
  //  RMS
  MDR_ADCUI_CfgRMS      cfgRMS;
} MDR_ADCUI_CfgPower;

typedef struct  {
  uint16_t  Imax;                       //  FxMD1.IPKLvl
  uint16_t  Umax;                       //  FxMD1.VPKLvl
} MDR_ADCUI_CfgLims;

typedef enum  {
  ADCUI_Vref_IntBuffered,  
  ADCUI_Vref_Internal,
  ADCUI_Vref_External
} MDR_ADCUI_SelVref;

//  Full channel F0 configuration
typedef struct  {
  //  Input channel settings
  MDR_ADCUI_CfgIx     *cfgI0;
  MDR_ADCUI_CfgVx     *cfgV0;
  MDR_ADCUI_CfgIx     *cfgI3;    
  //  Source for Data Registers
  MDR_ADCUI_VDAT_Sel  srcVDAT;              //  FxMD0.VSel  - V, Pa, Pr, Pf
  MDR_ADCUI_IDAT_Sel  srcIDAT;              //  FxMD0.ISel  - I, Pa, Pr, Pf
  MDR_ADCUI_I3DAT_Sel srcI3DAT;             //  FxMD0.I3Sel - I3_HPF, I3
  //  Max I and U Levels
  MDR_ADCUI_CfgLims   *cfgLims;  
  //  Power settings
  MDR_ADCUI_CfgPower  *cfgPower;
  
} MDR_ADCUI_CfgF0;

//  =========   Global settings for all channels  ===========
typedef struct  {
  //  V cross zero
  MDR_OnOff             Vcrs0_LFPEn;        //  FxCTRL1.ZXLPF
  uint32_t              Vcrs0_Timeout;      //  FxCTRL3.ZTXOUT  - 12 bits
  //  V period
  MDR_OnOff             VPer_DetectOn;      //  FxCTRL1.FreqSel
  MDR_ADCUI_Period      VPer_DetectAver;    //  FxCTRL1.Per_Length  
  //  V min level
  uint16_t              Vmin_Level;         //  FxCTRL2.SAGCYC
  uint16_t              Vmin_HalfPeriods;   //  FxCTRL2.SAGLVL  
} MDR_ADCUI_CfgV;

typedef struct  {
  MDR_ADCUI_SampleRate  sampleRate;         //  FxCTRL1.OSR_Conf
  MDR_ADCUI_SelVref     selectVref;         //  FxCTRL1.VrefSel, FxCTRL1.BUF_BYP,
  MDR_OnOff             dataBits24;         //  FxCTRL1.Resol
  MDR_OnOff             IBoost;             //  FxCTRL1.IBoost  
  MDR_ADCUI_RMS_Update  updateRMS;          //  FxCTRL1.ZXRMS  
} MDR_ADCUI_CfgBase;

typedef struct  {
  MDR_ADCUI_NoLoad  noLoadPa;               //  FxCTRL1.APNoLoad
  MDR_ADCUI_NoLoad  noLoadPr;               //  FxCTRL1.VARNoLoad
  MDR_ADCUI_NoLoad  noLoadPf;               //  FxCTRL1.VANoLoad  
} MDR_ADCUI_CfgNoLoad;

typedef struct  {
  uint16_t      V0BGain;                //  CCAL1.V0BGain  
  uint16_t      I0BGain;                //  CCAL1.I0BGain, CCAL4.I3BGain    
  uint16_t      I3BGain;                //  CCAL4.I3BGain    
  uint16_t      V1BGain;                //  CCAL2.V0BGain  
  uint16_t      I1BGain;                //  CCAL2.I0BGain
  uint16_t      V2BGain;                //  CCAL3.V0BGain  
  uint16_t      I2BGain;                //  CCAL3.I0BGain
  uint16_t      reserved;
} MDR_ADCUI_CfgCalibr;

#endif  // _MDR_ADCIU_VK2x4_F0_H


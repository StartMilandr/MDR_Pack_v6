#ifndef _MDR_ADCUI_VK234_H
#define _MDR_ADCUI_VK234_H

#include <MDR_Config.h>
#include <MDR_Funcs.h>
#include <MDR_GPIO.h>

#include <MDR_ADCUI_VK234_defs.h>
#include <MDR_ADCUI_VK2x4_F0.h>
#include <MDR_ADCUI_VK234_CfgRegs.h>


typedef struct  {
  MDR_OnOff           chopEna;              //  FxCTRL1.Chop_En
  MDR_ADCUI_ChopDiv   chopDiv;              //  FxCTRL1.Chop_Freq
} MDR_ADCUI_CfgChop;

//  Channel Fx configuration
typedef struct  {
  //  Input channel settings
  MDR_ADCUI_CfgIx     *cfgI;
  MDR_ADCUI_CfgVx     *cfgV;  
  //  Source for Data Registers
  MDR_ADCUI_VDAT_Sel  srcVDAT;              //  FxMD0.VSel  - V, Pa, Pr, Pf
  MDR_ADCUI_IDAT_Sel  srcIDAT;              //  FxMD0.ISel  - I, Pa, Pr, Pf  
  //  Max I and U Levels
  MDR_ADCUI_CfgLims   *cfgLims;  
  //  Power settings
  MDR_ADCUI_CfgPower  *cfgPower;
} MDR_ADCUI_CfgFx;


#define ADCUI_I0En    0x0001UL
#define ADCUI_V0En    0x0002UL
#define ADCUI_I1En    0x0004UL
#define ADCUI_V1En    0x0008UL
#define ADCUI_I2En    0x0010UL
#define ADCUI_V2En    0x0020UL
#define ADCUI_I3En    0x0040UL

#define MDR_ADCUI_FxMask  0x007FUL

typedef  union {
    uint32_t          SelMask;
    struct {
      MDR_OnOff I0En    : 1;
      MDR_OnOff V0En    : 1;
      MDR_OnOff I1En    : 1;
      MDR_OnOff V1En    : 1;
      MDR_OnOff I2En    : 1;
      MDR_OnOff V2En    : 1;
      MDR_OnOff I3En    : 1;
      uint32_t          : 25;
    } SelBits;  
} MDR_ADCUI_FxSelect;

typedef struct  {
  //  Select Enable channels
  MDR_ADCUI_FxSelect  selFxEn;
  
  //  Global settings
  MDR_ADCUI_CfgBase   *cfgBase;       //  Базовые настройки
  MDR_ADCUI_CfgNoLoad *cfgNoLoad;     //  Уровни не учитываемой энергии
  MDR_ADCUI_CfgV      *cfgV;          //  Отслеживание событий в каналах напряжения
  MDR_ADCUI_CfgCalibr *cfgCalibr;     //  Калибровки для каналов
  
  MDR_ADCUI_CfgChop   *cfgChop;       //  Режим чоппера (только для К234)
  
  //  Channels Fx settings
  MDR_ADCUI_CfgF0     *cfgF0;
  MDR_ADCUI_CfgFx     *cfgF1;
  MDR_ADCUI_CfgFx     *cfgF2;
} MDR_ADCUI_Cfg;



// ==============    Инициализация через структуру MDR_ADCUI_Cfg  ===========
// В MDR_ADCUI_Cfg настройки сгруппированы по назначению. Могут быть опущены (NULL), если опцию настраивать не надо. 
// тогда соответствующие биты в регистрах останутся по умолчанию - равны 0.

//  Инициализация блока с  включение тактирования
void MDR_ADCUI_Init(const MDR_ADCUI_Cfg *pCfg);
void MDR_ADCUI_DeInit(void);

//  Функции, полезные при регистровой настройке
void MDR_ADCUI_ClearRegs(void);
void MDR_ADCUI_Reset(void);

__STATIC_INLINE void MDR_ADCUI_ClockOn(void)  {MDR_CLOCK->MDR_CLK_EN_REG_PER_b.ADCIU_CLK_EN  = MDR_On;}
__STATIC_INLINE void MDR_ADCUI_ClockOff(void) {MDR_CLOCK->MDR_CLK_EN_REG_PER_b.ADCIU_CLK_EN  = MDR_Off;}


// ==============    Инициализация через структуру CfgRegs - выполняется быстрее ===========
//  В MDR_ADCUI_CfgRegs собраны только регистры, которые содержат настроки.
//  Если эти регистры задать напрямую, то инициализация выполняется быстрее, 
//  чем через MDR_ADCUI_Cfg, где настройки не привязаны к регистрам (типа HAL).
void MDR_ADCUI_Init_ByCfgRegs(const MDR_ADCUI_CfgRegs *pCfg);

//  Конвертация настроек MDR_ADCUI_Cfg в CfgRegs
void MDR_ADCUI_ToCfgRegs(const MDR_ADCUI_Cfg *pCfg, MDR_ADCUI_CfgRegs *pCfgRegs);

//  Чтение структуры pCfgRegs из блока и применение в блок.
void MDR_ADCUI_CfgRegs_Read(MDR_ADCUI_CfgRegs *pCfgRegs);
void MDR_ADCUI_CfgRegs_Apply(const MDR_ADCUI_CfgRegs *pCfgRegs);

//  Обнуление структуры pCfgRegs, если потребуется. Используется в MDR_ADCUI_ToCfgRegs.
void MDR_ADCUI_CfgRegs_Clear(MDR_ADCUI_CfgRegs *pCfgRegs);


// ==============    Чтение данных с АЦП ===========
__STATIC_INLINE bool MDR_ADCUI_F0_CheckFlagSet(uint32_t flagSel) {return (MDR_ADCUI->F0STAT & flagSel) == flagSel;}
__STATIC_INLINE bool MDR_ADCUI_F1_CheckFlagSet(uint32_t flagSel) {return (MDR_ADCUI->F1STAT & flagSel) == flagSel;}
__STATIC_INLINE bool MDR_ADCUI_F2_CheckFlagSet(uint32_t flagSel) {return (MDR_ADCUI->F2STAT & flagSel) == flagSel;}

__STATIC_INLINE bool MDR_ADCUI_CanRead_V0(void) {return !MDR_ADCUI_F0_CheckFlagSet(MDR_ADCUI_FxSTAT_VF_EMP_Msk);}
__STATIC_INLINE bool MDR_ADCUI_CanRead_I0(void) {return !MDR_ADCUI_F0_CheckFlagSet(MDR_ADCUI_FxSTAT_IF_EMP_Msk);}
__STATIC_INLINE bool MDR_ADCUI_CanRead_I3(void) {return !MDR_ADCUI_F0_CheckFlagSet(MDR_ADCUI_F0STAT_I3F_EMP_Msk);}

__STATIC_INLINE bool MDR_ADCUI_CanRead_V1(void) {return !MDR_ADCUI_F1_CheckFlagSet(MDR_ADCUI_FxSTAT_VF_EMP_Msk);}
__STATIC_INLINE bool MDR_ADCUI_CanRead_I1(void) {return !MDR_ADCUI_F1_CheckFlagSet(MDR_ADCUI_FxSTAT_IF_EMP_Msk);}
__STATIC_INLINE bool MDR_ADCUI_CanRead_V2(void) {return !MDR_ADCUI_F2_CheckFlagSet(MDR_ADCUI_FxSTAT_VF_EMP_Msk);}
__STATIC_INLINE bool MDR_ADCUI_CanRead_I2(void) {return !MDR_ADCUI_F2_CheckFlagSet(MDR_ADCUI_FxSTAT_IF_EMP_Msk);}

uint32_t MDR_ADCUI_WaitAndRead_V0(void);
uint32_t MDR_ADCUI_WaitAndRead_I0(void); 
uint32_t MDR_ADCUI_WaitAndRead_I3(void); 
uint32_t MDR_ADCUI_WaitAndRead_V1(void); 
uint32_t MDR_ADCUI_WaitAndRead_I1(void); 
uint32_t MDR_ADCUI_WaitAndRead_V2(void);
uint32_t MDR_ADCUI_WaitAndRead_I2(void); 



#endif  // _MDR_ADCUI_VK234_H


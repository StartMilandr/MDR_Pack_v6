#include <MDR_ADCUI_VK214.h>
#include "test_Defs.h"
#include "common.h"

//===============   ОПИСАНИЕ  ======================
//  Тесты инициализируют блок тремя способами
//  1 - напрямую через регистры
//  2 - Через конфигурационную структуру MDR_ADCUI_Cfg
//  3 - Через структуру регистров MDR_ADCUI_CfgRegs
//
//  Кнопки:
//    UP - смена теста
//    RIGHT - смена канала F0-F2
//    LEFT - смена данных отображаемых на дисплей
//    DOWN - вывод выбранных данных на дисплей


//  Interface functions
static void Test_InitByReg(void);
static void Test_InitByCfg(void);
static void Test_InitByCfgReg(void);

static void Test_Finit(void);
static void Test_ChangeData(void);
static void Test_Exec(void);


extern TestInterface TI_ADTUI_InitReg;
extern TestInterface TI_ADTUI_InitCfg;
extern TestInterface TI_ADTUI_InitCfgReg;

TestInterface TI_ADTUI_InitReg = {
  .funcInit       = Test_InitByReg,
  .funcFinit      = Test_Finit,
  .funcChangeData = Test_ChangeData,
  .funcExec       = Test_Exec,
};

TestInterface TI_ADTUI_InitCfg = {
  .funcInit       = Test_InitByCfg,
  .funcFinit      = Test_Finit, 
  .funcChangeData = Test_ChangeData,
  .funcExec       = Test_Exec,
};

TestInterface TI_ADTUI_InitCfgReg = {
  .funcInit       = Test_InitByCfgReg,
  .funcFinit      = Test_Finit,
  .funcChangeData = Test_ChangeData,
  .funcExec       = Test_Exec,
};

#define V_PERIOD_AVER   2
#define V_OK_LEVEL_MIN  0x2100UL

static void Test_InitByReg(void)
{  
  MDR_ADCUI_ClockOn();  
  //  Reset On
  MDR_ADCUI->CTRL1 = MDR_ADCUI_CTRL1_RESET_DIG_Msk;
  //  Reset Off
  MDR_ADCUI->CTRL1 = ( 0
                    //| MDR_ADCUI_CTRL1_ZXRMS_Msk       //  [27] RMS by V cross 0
                    //| MDR_ADCUI_CTRL1_FREQSEL_Msk     //  [19] Calc V period to MD0.PER_FREQ
                    //| MDR_ADCUI_CTRL1_RESOL_Msk       //  [7]  24bit
                    | MDR_ADCUI_CTRL1_I0EN_Msk
                    | MDR_ADCUI_CTRL1_V0EN_Msk
                    | MDR_ADCUI_CTRL1_I3EN_Msk);
    
  MDR_ADCUI->CTRL2 =  VAL2FLD_Pos(V_PERIOD_AVER,  MDR_ADCUI_CTRL2_SAGCYC_Pos)
                    | VAL2FLD_Pos(V_OK_LEVEL_MIN, MDR_ADCUI_CTRL2_SAGLVL_Pos);
  MDR_ADCUI->CTRL3 = 0;

  MDR_ADCUI->F0MD0 = VAL2FLD_Pos(ADCUI_UsedI_I0, MDR_ADCUI_F0MD0_SEL_I_CH_Pos);
  
  Test_Exec();
}

static void Test_InitByCfg(void)
{  
  MDR_ADCUI_Cfg Cfg;
  MDR_ADCUI_CfgBase CfgBase = {
    .sampleRate = ADCUI_SRate_8KHz,
    .selectVref = ADCUI_Vref_IntBuffered,
    .dataBits24 = MDR_On,
    .IBoost     = MDR_Off,
    .updateRMS  = ADCUI_RMS_VcrsZero
  };
  
  //  Select Enable channels
  Cfg.selFxEn.SelMask = 0
                      | ADCUI_I0En
                      | ADCUI_V0En
                      | ADCUI_I3En;
  
//  //  Global settings
//  CfgBase.sampleRate = ADCUI_SRate_8KHz;
//  CfgBase.selectVref = ADCUI_Vref_IntBuffered;
//  CfgBase.dataBits24 = MDR_On;
//  CfgBase.IBoost     = MDR_Off;
//  CfgBase.updateRMS  = ADCUI_RMS_VcrsZero;
  
  Cfg.pCfgBase = &CfgBase;  
  Cfg.pCfgNoLoad = NULL;     //  Уровни не учитываемой энергии
  Cfg.pCfgV      = NULL;     //  Отслеживание событий в каналах напряжения
  Cfg.pCfgCalibr = NULL;     //  Калибровки для каналов  
  
  //  Channels Fx settings
  Cfg.pCfgF0   = NULL;
  
  MDR_ADCUI_Init(&Cfg);
  
  Test_Exec();
}

static void Test_InitByCfgReg(void)
{
  MDR_ADCUI_CfgRegs CfgRegs;
  
  MDR_ADCUI_CfgRegs_Clear(&CfgRegs);
  
  CfgRegs.Ctrl.CTRL1 = 0
                      | ADCUI_I0En
                      | ADCUI_V0En
                      | ADCUI_I3En;
  
  CfgRegs.Ctrl.CTRL1_b.DataBit24    = MDR_On;
  CfgRegs.Ctrl.CTRL1_b.SampleRate   = ADCUI_SRate_4KHz;
  CfgRegs.Ctrl.CTRL1_b.Vcrs0_LPFEn  = MDR_Off;
  CfgRegs.Ctrl.CTRL1_b.VrefSel      = ADCUI_VrefInt;
  CfgRegs.Ctrl.CTRL1_b.VrefPassBuff = MDR_Off;
  CfgRegs.Ctrl.CTRL1_b.RMS_Update   = ADCUI_RMS_Continuous;
  
  // Выключение сумматоров
  CfgRegs.F0.CTR_b.I0_SumOff = MDR_On;
  CfgRegs.F0.CTR_b.I3_SumOff = MDR_On;
  
  MDR_ADCUI_Init_ByCfgRegs(&CfgRegs);
  
  Test_Exec();
}

static void Test_Finit(void)
{
  MDR_ADCUI_DeInit();
  MDRB_LCD_Clear();
}

static void Test_ChangeData(void)
{
  CfgDataID_Inc();
  ADCUI_SwitchSelDAT(Cfg_ActiveDataID);
  Test_Exec();
}

static void Test_Exec(void)
{
  uint32_t data = 0;
  data = ADCUI_GetResult(Cfg_ActiveDataID);
  LCD_ShowResult(data, Cfg_ActiveDataID);
}




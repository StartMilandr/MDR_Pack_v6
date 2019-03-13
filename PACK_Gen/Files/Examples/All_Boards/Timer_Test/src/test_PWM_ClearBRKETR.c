#include <MDR_Timer.h>
#include <MDRB_LEDs.h>
#include <MDRB_LCD.h>

#include <MDRB_Timer_PinSelect.h>
#include "test_Defs.h"


// ОПИСАНИЕ
//   При запуске теста на выводы Timer1 CH1 и CH2 выводятся два разных сигнала.
//   Выводы BRK и ETR настроены на выключение импульсов - уровень падает в 0.
//   Вход BRK выключает пульсации на CH1 - при BRK=Ucc импульсы идут, при BRK=GND нет.
//   Вход ETR выключает пульсации на CH2 - при ETR=GND импульсы идут, при BRK=Ucc нет.
//   Для проверки подключать данные выводы на землю и Ucc соответственно проводами.
//   ПИНЫ для ВЕ91:
//    CH1 - XP8_9
//    CH2 - XP8_11
//    BRK - XP8_20
//    ETR - XP8_19
//    Ucc - XP9_11
//    GND - XP11_2

//  Test Interface functions
static void  Test_Init(void);
static void  Test_Finit(void);
static void  Test_Change(void);
static void  Test_Exec(void);
static void  Test_MainLoop(void);
static void  Test_HandleTim1IRQ(void);
static void  Test_HandleTim2IRQ(void);
static void  Test_HandleTim3IRQ(void);

TestInterface TI_PWM_ClearBRKETR = {
  .funcInit       = Test_Init,
  .funcFinit      = Test_Finit,
  .funcChange     = Test_Change,
  .funcExec       = Test_Exec,
  .funcMainLoop   = Test_MainLoop,
  .funcHandlerTim1 = Test_HandleTim1IRQ,
  .funcHandlerTim2 = Test_HandleTim2IRQ,
  .funcHandlerTim3 = Test_HandleTim3IRQ,
  .funcHandlerTim4 = Test_HandleTim3IRQ,
};

#define BRG_VALUE      MDR_BRG_div4
#define PSC_VALUE1     100
#define PSC_VALUE2      50
#define PERIOD_VALUE   900

static const MDR_Timer_cfgBRKETR cfgBRKETR = {
  .Bits.BRK_INV = MDR_Off, 
  .Bits.ETR_INV = MDR_Off, 
  .Bits.ETR_PSC = MDR_TIM_BRKETR_ETR_div1,
  .Bits.ETR_Filter = MDR_TIM_FLTR_TIM_CLK
};

static void Test_Init(void)
{
  MDR_TimerCh_CfgOptionsPWM cfgOptions;
  MDR_TimerCh_CfgPWM        cfgPWM;
  
  //  Options settings
  cfgOptions.cfgPin_CH  = NULL;
  cfgOptions.cfgPin_nCH = NULL;  
  cfgOptions.cfgDTG     = NULL;
  cfgOptions.ClearRef_ByBRK = MDR_On;
  cfgOptions.ClearRef_ByETR = MDR_Off;
  // PWM Settings
  cfgPWM.use_nCH = true;
  cfgPWM.CCRs_UpdImmediately = MDR_On;
  cfgPWM.cfgOptions = &cfgOptions;
  
  MDRB_LCD_Print("Clear ETR & BRK", 3);
  MDRB_LCD_ClearLine(5);
  
  //  Timer1
  MDR_Timer_InitPeriodDir(MDR_TIMER1ex, BRG_VALUE, PSC_VALUE1, PERIOD_VALUE, false, TIM_CountUpDown);
  //  Channel1 PWM clear by BRK
  MDR_TimerCh_InitPWM (MDR_TIMER1_CH1, &cfgPWM, MDR_TIM_PWM_RefTgl_eqCCR,  PERIOD_VALUE / 3);
  
  //  Channel2 PWM clear by ETR
  cfgOptions.ClearRef_ByBRK = MDR_Off;
  cfgOptions.ClearRef_ByETR = MDR_On;
  MDR_TimerCh_InitPWM1(MDR_TIMER1_CH2, &cfgPWM, MDR_TIM_PWM1_RefTgl_eqCCRx, PERIOD_VALUE / 3, PERIOD_VALUE * 2 / 3);
  
  //  ETR and BRK Init
  MDR_Timer_InitBRKETR(MDR_TIMER1ex, cfgBRKETR);
  
  //  PinsInit
  MDR_TimerCh_InitPinGPIO(&_pinTim1_CH1,  MDR_PIN_FAST);
  MDR_TimerCh_InitPinGPIO(&_pinTim1_nCH1, MDR_PIN_FAST);
  MDR_TimerCh_InitPinGPIO(&_pinTim1_CH2,  MDR_PIN_FAST);
  MDR_TimerCh_InitPinGPIO(&_pinTim1_nCH2, MDR_PIN_FAST);
  
  MDR_TimerCh_InitPinGPIO(&_pinTim1_ETR, MDR_PIN_FAST);
  MDR_TimerCh_InitPinGPIO(&_pinTim1_BRK, MDR_PIN_FAST);
    
  // Sync Start
  MDR_Timer_Start(MDR_TIMER1ex);
}  

static void Test_Finit(void)
{
  MDR_TimerCh_DeInitPinGPIO(&_pinTim1_CH1);
  MDR_TimerCh_DeInitPinGPIO(&_pinTim1_nCH1);
  MDR_TimerCh_DeInitPinGPIO(&_pinTim1_CH2);
  MDR_TimerCh_DeInitPinGPIO(&_pinTim1_nCH2);
   
  MDR_Timer_Stop(MDR_TIMER1ex);
  MDR_Timer_DeInit(MDR_TIMER1ex);
}

static void Test_Change(void)
{

}

static void Test_Exec(void)
{

}

static void  Test_MainLoop(void)
{
}

static void Test_HandleTim1IRQ(void)
{
}

static void Test_HandleTim2IRQ(void)
{

}

static void Test_HandleTim3IRQ(void)
{

}

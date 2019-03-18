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
//   ПИНЫ для ВЕ91  BK214
//    CH1 - XP8_9    PA1
//   nCH1 - XP8_10   PA2
//    CH2 - XP8_11   
//   nCH2 - XP8_12   PA2
//    BRK - XP8_20   PA9          Ucc_PulsesOn
//    ETR - XP8_19   PA8          GND_PulsesOn
//    Ucc - XP9_11
//    GND - XP11_2
// (Для 1986ВК214 сбрасывается CH1 и по BRK и по ETR - т.к. в 1986ВК214 только один канал в таймере.)

//  Test Interface functions
static void  Test_Init(void);
static void  Test_Finit(void);
static void  Test_Empty(void);

TestInterface TI_PWM_ClearBRKETR = {
  .funcInit       = Test_Init,
  .funcFinit      = Test_Finit,
  .funcChange     = Test_Empty,
  .funcExec       = Test_Empty,
  .funcMainLoop   = Test_Empty,
  .funcHandlerTim1 = Test_Empty,
  .funcHandlerTim2 = Test_Empty,
  .funcHandlerTim3 = Test_Empty,
  .funcHandlerTim4 = Test_Empty,
};


//  Channel Select
#ifdef USE_MDR1986VE91
  #define TIM1_CH_SEL       MDR_TIMER1_CH1
  #define TIM1_PIN_CH       _pinTim1_CH1
  #define TIM1_PIN_nCH      _pinTim1_nCH1
  #define TIM1_PIN_ETR      _pinTim1_ETR
  #define TIM1_PIN_BRK      _pinTim1_BRK

#elif defined (USE_MDR1986VK214)
  #define TIM1_CH_SEL       MDR_TIMER1_CH1
  #define TIM1_PIN_CH       _pinTim1_CH1
  #define TIM1_PIN_nCH      _pinTim1_nCH1
  #define TIM1_PIN_ETR      _pinTim1_ETR
  #define TIM1_PIN_BRK      _pinTim1_BRK

  #define LCD_CONFLICT
  #define USE_SINGLE_CHANNEL

#elif defined (USE_MDR1986VK234)
  #define TIM1_CH_SEL       MDR_TIMER1_CH3
  #define TIM1_PIN_CH       _pinTim1_CH3
  #define TIM1_PIN_nCH      _pinTim1_nCH3
  #define TIM1_PIN_ETR      _pinTim1_ETR
  #define TIM1_PIN_BRK      _pinTim1_BRK  
  
  #define USE_SINGLE_CHANNEL  
#endif


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

  //  To LCD
#ifndef LCD_IS_7SEG_DISPLAY
  MDRB_LCD_Print("Clear ETR & BRK", 3);
  
#elif defined (LCD_CONFLICT)
  //  LCD conflicts with Timers channel
  //  Show Test index and LCD Off
  MDRB_LCD_Print("7");  
  MDR_LCD_BlinkyStart(MDR_LCD_Blink_2Hz, MDR_Off);
  MDR_Delay_ms(LCD_HIDE_DELAY, MDR_CPU_GetFreqHz(false));
  
  MDR_LCD_DeInit();
#else
  MDRB_LCD_Print("7");
#endif  
  
  //  Options settings
  cfgOptions.cfgPin_CH  = NULL;
  cfgOptions.cfgPin_nCH = NULL;  
  cfgOptions.cfgDTG     = NULL;
  cfgOptions.ClearRef_ByBRK = MDR_On;
#ifdef USE_SINGLE_CHANNEL    
  cfgOptions.ClearRef_ByETR = MDR_On;
#else  
  cfgOptions.ClearRef_ByETR = MDR_Off;
#endif

  // PWM Settings
  cfgPWM.use_nCH = true;
  cfgPWM.CCRs_UpdImmediately = MDR_On;
  cfgPWM.cfgOptions = &cfgOptions;
  
  //  Timer1
  MDR_Timer_InitPeriodDir(MDR_TIMER1ex, TIM_BRG_PWM, TIM_PSG_PWM1, TIM_PERIOD_PWM, false, TIM_CountUpDown);
  //  Channel1 PWM clear by BRK
  MDR_TimerCh_InitPWM (TIM1_CH_SEL, &cfgPWM, MDR_TIM_PWM_RefTgl_eqCCR,  TIM_PERIOD_PWM / 3);

#ifndef USE_SINGLE_CHANNEL
  //  Channel2 PWM clear by ETR
  cfgOptions.ClearRef_ByBRK = MDR_Off;
  cfgOptions.ClearRef_ByETR = MDR_On;
  MDR_TimerCh_InitPWM1(MDR_TIMER1_CH2, &cfgPWM, MDR_TIM_PWM1_RefTgl_eqCCRx, TIM_PERIOD_PWM / 3, TIM_PERIOD_PWM * 2 / 3);
#endif

  //  ETR and BRK Init
  MDR_Timer_InitBRKETR(MDR_TIMER1ex, cfgBRKETR);
  
  //  PinsInit
  MDR_TimerCh_InitPinGPIO(&TIM1_PIN_CH,  MDR_PIN_FAST);
  MDR_TimerCh_InitPinGPIO(&TIM1_PIN_nCH, MDR_PIN_FAST);
#ifndef USE_SINGLE_CHANNEL  
  MDR_TimerCh_InitPinGPIO(&_pinTim1_CH2,  MDR_PIN_FAST);
  MDR_TimerCh_InitPinGPIO(&_pinTim1_nCH2, MDR_PIN_FAST);
#endif
  
  MDR_TimerCh_InitPinGPIO(&TIM1_PIN_ETR, MDR_PIN_FAST);
  MDR_TimerCh_InitPinGPIO(&TIM1_PIN_BRK, MDR_PIN_FAST);
    
  // Sync Start
  MDR_Timer_Start(MDR_TIMER1ex);
}  

static void Test_Finit(void)
{
  MDR_TimerCh_DeInitPinGPIO(&TIM1_PIN_CH);
  MDR_TimerCh_DeInitPinGPIO(&TIM1_PIN_nCH);
  MDR_TimerCh_DeInitPinGPIO(&TIM1_PIN_ETR);
  MDR_TimerCh_DeInitPinGPIO(&TIM1_PIN_BRK);  
  
#ifndef USE_SINGLE_CHANNEL   
  MDR_TimerCh_DeInitPinGPIO(&_pinTim1_CH2);
  MDR_TimerCh_DeInitPinGPIO(&_pinTim1_nCH2);
#endif
   
  MDR_Timer_Stop(MDR_TIMER1ex);
  MDR_Timer_DeInit(MDR_TIMER1ex);
  
#ifdef LCD_CONFLICT 
  // Restore LCD
  MDRB_LCD_Init(MDR_CPU_GetFreqHz(false));   
#endif
}

static void Test_Empty(void)
{

}



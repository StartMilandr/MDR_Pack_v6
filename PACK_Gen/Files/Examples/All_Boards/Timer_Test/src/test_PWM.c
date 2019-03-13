#include <MDR_Timer.h>
#include <MDRB_LEDs.h>
#include <MDRB_LCD.h>

#include <MDRB_Timer_PinSelect.h>
#include "test_Defs.h"

//  ОПИСАНИЕ:
//  Пример генерации ШИМ по умолчанию - без задания опциональных настроек, MDR_TimerCh_CfgPWM = NULL.

//  Test Interface functions
static void  Test_Init(void);
static void  Test_Finit(void);
static void  Test_Change(void);
static void  Test_Exec(void);
static void  Test_MainLoop(void);
static void  Test_HandleTim1IRQ(void);
static void  Test_HandleTim2IRQ(void);
static void  Test_HandleTim3IRQ(void);

TestInterface TI_PWM = {
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

static void Test_Init(void)
{
  MDRB_LCD_Print("Simplest PWM", 3);
  MDRB_LCD_Print("and Sync Run", 5);
  
  //  Timer1
  MDR_Timer_InitPeriodDir(MDR_TIMER1ex, BRG_VALUE, PSC_VALUE1, PERIOD_VALUE, false, TIM_CountUpDown);
  MDR_TimerCh_InitPWM (MDR_TIMER1_CH1, NULL, MDR_TIM_PWM_RefTgl_eqCCR,  PERIOD_VALUE / 3);
  MDR_TimerCh_InitPWM1(MDR_TIMER1_CH2, NULL, MDR_TIM_PWM1_RefTgl_eqCCRx, PERIOD_VALUE / 3, PERIOD_VALUE * 2 / 3);
  
  MDR_TimerCh_InitPinGPIO(&_pinTim1_CH1,  MDR_PIN_FAST);
  MDR_TimerCh_InitPinGPIO(&_pinTim1_nCH1, MDR_PIN_FAST);
  MDR_TimerCh_InitPinGPIO(&_pinTim1_CH2,  MDR_PIN_FAST);
  MDR_TimerCh_InitPinGPIO(&_pinTim1_nCH2, MDR_PIN_FAST);
  
  //  Timer2
  MDR_Timer_InitPeriodDir(MDR_TIMER2ex, BRG_VALUE, PSC_VALUE2, PERIOD_VALUE, false, TIM_CountUpDown);
  MDR_TimerCh_InitPWM (MDR_TIMER2_CH3, NULL, MDR_TIM_PWM_RefTgl_eqCCR,  PERIOD_VALUE / 3);
  MDR_TimerCh_InitPWM1(MDR_TIMER2_CH4, NULL, MDR_TIM_PWM1_RefTgl_eqCCRx, PERIOD_VALUE / 3, PERIOD_VALUE * 2 / 3);  

  MDR_TimerCh_InitPinGPIO(&_pinTim2_CH3,  MDR_PIN_FAST);
  MDR_TimerCh_InitPinGPIO(&_pinTim2_nCH3, MDR_PIN_FAST);
  MDR_TimerCh_InitPinGPIO(&_pinTim2_CH4,  MDR_PIN_FAST);
  MDR_TimerCh_InitPinGPIO(&_pinTim2_nCH4, MDR_PIN_FAST);

  // Sync Start
  MDR_Timer_StartSync(TIM1_StartMsk | TIM2_StartMsk);
}  

static void Test_Finit(void)
{
  MDR_TimerCh_DeInitPinGPIO(&_pinTim1_CH1);
  MDR_TimerCh_DeInitPinGPIO(&_pinTim1_nCH1);
  MDR_TimerCh_DeInitPinGPIO(&_pinTim1_CH2);
  MDR_TimerCh_DeInitPinGPIO(&_pinTim1_nCH2);
  
  MDR_TimerCh_DeInitPinGPIO(&_pinTim2_CH3);
  MDR_TimerCh_DeInitPinGPIO(&_pinTim2_nCH3);
  MDR_TimerCh_DeInitPinGPIO(&_pinTim2_CH4);
  MDR_TimerCh_DeInitPinGPIO(&_pinTim2_nCH4);  
  
  MDR_Timer_StopSync(TIM1_StartMsk | TIM2_StartMsk);
  MDR_Timer_DeInit(MDR_TIMER1ex);
  MDR_Timer_DeInit(MDR_TIMER2ex);
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

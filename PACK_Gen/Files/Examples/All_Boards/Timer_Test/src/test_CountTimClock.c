#include <MDR_Timer.h>
#include <MDRB_LEDs.h>
#include <MDRB_LCD.h>

#include "test_Defs.h"

//  ОПИСАНИЕ:
//    Пример настройки счета таймера с указанием всех настроек - MDR_Timer_CfgCountClock

//  Test Interface functions
static void  Test_Init(void);
static void  Test_Finit(void);
static void  Test_Change(void);
static void  Test_Exec(void);
static void  Test_MainLoop(void);
static void  Test_HandleTim1IRQ(void);
static void  Test_HandleTim2IRQ(void);
static void  Test_HandleTim3IRQ(void);

TestInterface TI_CountTimClock = {
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


static void Test_Init(void)
{
  MDR_Timer_CfgCountClock cfgCntClock;
  
  MDRB_LCD_Print("Count TimClock", 3);
  MDRB_LCD_Print("All Dirs", 5);
  
  MDRB_LED_Init(MDRB_LED_1 | MDRB_LED_2 | MDRB_LED_3);
  MDRB_LED_Set (MDRB_LED_1 | MDRB_LED_2 | MDRB_LED_3, 0);
  
  //  Timer1 - Count Down
  cfgCntClock.cfgPeriod.clockBRG = MDR_BRG_div16;
  cfgCntClock.cfgPeriod.period = 4000;
  cfgCntClock.cfgPeriod.startValue = 0;
  cfgCntClock.cfgPeriod.periodUpdateImmediately = MDR_Off;
  
  cfgCntClock.cfgIRQ.activateNVIC_IRQ = true;
  cfgCntClock.cfgIRQ.priorityIRQ = 0;
  cfgCntClock.cfgIRQ.SelectIRQ = TIM_FL_CNT_ZERO;
  
  cfgCntClock.timClockPSG = 1000;
  cfgCntClock.countDir = TIM_CountDown;
  
  MDR_Timer_InitCountTimClock(MDR_TIMER1ex, &cfgCntClock);
  
  //  Timer2 - Count UpDown
  cfgCntClock.cfgIRQ.SelectIRQ = TIM_FL_CNT_ZERO | TIM_FL_CNT_ARR;
  cfgCntClock.countDir = TIM_CountUpDown;
  MDR_Timer_InitCountTimClock(MDR_TIMER2ex, &cfgCntClock);
  
  //  Timer3 - Count Up
  cfgCntClock.cfgIRQ.SelectIRQ = TIM_FL_CNT_ARR;
  cfgCntClock.countDir = TIM_CountUp;
  MDR_Timer_InitCountTimClock(MDR_TIMER3ex, &cfgCntClock);  
  
  MDR_Timer_StartSync(TIM1_StartMsk | TIM2_StartMsk | TIM3_StartMsk);
}  

static void Test_Finit(void)
{
  MDR_Timer_StopSync(TIM1_StartMsk | TIM2_StartMsk);
  MDR_Timer_DeInit(MDR_TIMER1ex);
  MDR_Timer_DeInit(MDR_TIMER2ex);
  MDR_Timer_DeInit(MDR_TIMER3ex);
  
  LED_Uninitialize();
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
  MDR_Timer_ClearEvent(MDR_TIMER1, TIM_FL_CNT_ZERO);
  
  MDRB_LED_Switch(MDRB_LED_1);
}

static void Test_HandleTim2IRQ(void)
{
  MDR_Timer_ClearEvent(MDR_TIMER2, TIM_FL_CNT_ZERO | TIM_FL_CNT_ARR);
  
  MDRB_LED_Switch(MDRB_LED_2);
}

static void Test_HandleTim3IRQ(void)
{
  MDR_Timer_ClearEvent(MDR_TIMER3, TIM_FL_CNT_ARR);
  
  MDRB_LED_Switch(MDRB_LED_3);
}

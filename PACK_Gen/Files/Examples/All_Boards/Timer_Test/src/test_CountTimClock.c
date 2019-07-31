#include <MDR_Timer.h>
#include <MDRB_LEDs.h>
#include <MDRB_LCD.h>

#include "test_Defs.h"

//  ОПИСАНИЕ:
//    Пример настройки счета таймера с указанием всех настроек через структуру MDR_Timer_CfgCountClock.
//    Аналог test_SimplesFlash, но с разными направлениями счета.
//    Светодиоды мигают синхронно.

//  Test Interface functions
static void  Test_Init(void);
static void  Test_Finit(void);
static void  Test_Empty(void);
static void  Test_HandleTim1IRQ(void);
static void  Test_HandleTim2IRQ(void);
static void  Test_HandleTim3IRQ(void);

extern TestInterface TI_CountTimClock;

TestInterface TI_CountTimClock = {
  .funcInit       = Test_Init,
  .funcFinit      = Test_Finit,
  .funcChange     = Test_Empty,
  .funcExec       = Test_Empty,
  .funcMainLoop   = Test_Empty,
  .funcHandlerTim1 = Test_HandleTim1IRQ,
  .funcHandlerTim2 = Test_HandleTim2IRQ,
  .funcHandlerTim3 = Test_HandleTim3IRQ,
  .funcHandlerTim4 = Test_HandleTim3IRQ,
};

static void Test_Init(void)
{
  MDR_Timer_CfgCountClock cfgCntClock;
  
#ifndef LCD_IS_7SEG_DISPLAY
  MDRB_LCD_Print("Count TimClock", 3);
  MDRB_LCD_Print("All Dirs", 5);
#else
  MDRB_LCD_Print(TEST_ID__COUNT_TIM_CLOCK);
#endif  
    
  MDRB_LED_Init(LED_SEL_MAX);
  MDRB_LED_Set (LED_SEL_MAX, 0);
  
  //  Timer1 - Count Down
  cfgCntClock.cfgPeriod.clockBRG = TIM_BRG_LED;
  cfgCntClock.cfgPeriod.period = TIM_PERIOD_LED;
  cfgCntClock.cfgPeriod.startValue = 0;
  cfgCntClock.cfgPeriod.periodUpdateImmediately = MDR_Off;
  
  cfgCntClock.cfgIRQ.activateNVIC_IRQ = true;
  cfgCntClock.cfgIRQ.priorityIRQ = 0;
  cfgCntClock.cfgIRQ.SelectIRQ = TIM_FL_CNT_ZERO;
  
  cfgCntClock.timClockPSG = TIM_PSG_LED;
  cfgCntClock.countDir = TIM_CountDown;
  
  MDR_Timer_InitCountTimClock(MDR_TIMER1ex, &cfgCntClock);
  
  //  Timer2 - Count UpDown
  cfgCntClock.cfgIRQ.SelectIRQ = TIM_FL_CNT_ZERO | TIM_FL_CNT_ARR;
  cfgCntClock.countDir = TIM_CountUpDown;
  MDR_Timer_InitCountTimClock(MDR_TIMER2ex, &cfgCntClock);
  
#ifdef  USE_TIMER3  
  //  Timer3 - Count Up
  cfgCntClock.cfgIRQ.SelectIRQ = TIM_FL_CNT_ARR;
  cfgCntClock.countDir = TIM_CountUp;
  MDR_Timer_InitCountTimClock(MDR_TIMER3ex, &cfgCntClock);  
#endif
  
  MDR_Timer_StartSync(START_SYNC_SEL_MAX);
}  

static void Test_Finit(void)
{
  MDR_Timer_StopSync(START_SYNC_SEL_MAX);
  MDR_Timer_DeInit(MDR_TIMER1ex);
  MDR_Timer_DeInit(MDR_TIMER2ex);
#ifdef  USE_TIMER3  
  MDR_Timer_DeInit(MDR_TIMER3ex);
#endif
 
  LED_Uninitialize();
  
#ifdef LCD_CONFLICT_LED
  MDRB_LCD_CapturePins();
#endif  
  
#ifndef LCD_IS_7SEG_DISPLAY
  MDRB_LCD_ClearLine(5);
#endif  
}

static void Test_Empty(void)
{

}

static void Test_HandleTim1IRQ(void)
{
  MDR_Timer_ClearEvent(MDR_TIMER1, TIM_FL_CNT_ZERO);
  MDRB_LED_Toggle(MDRB_LED_1);
}

static void Test_HandleTim2IRQ(void)
{
  MDR_Timer_ClearEvent(MDR_TIMER2, TIM_FL_CNT_ZERO | TIM_FL_CNT_ARR);  
#ifdef MDRB_LED_2  
  MDRB_LED_Toggle(MDRB_LED_2);
#endif
}

static void Test_HandleTim3IRQ(void)
{
#ifdef  USE_TIMER3   
  MDR_Timer_ClearEvent(MDR_TIMER3, TIM_FL_CNT_ARR); 
  MDRB_LED_Toggle(MDRB_LED_3);
#endif
}

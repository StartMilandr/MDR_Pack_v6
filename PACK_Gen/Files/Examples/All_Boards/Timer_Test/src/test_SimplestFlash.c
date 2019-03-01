#include <MDR_Timer.h>
#include <MDRB_LEDs.h>
#include <MDRB_LCD.h>

#include "test_Defs.h"

//  ОПИСАНИЕ:
//  Пример простейшей инициализации таймера для получения прерываний с заданным периодом.
//  Одновременно мигают три светодиода от трех таймеров считающих синхронно.

//  Test Interface functions
static void  Test_Init(void);
static void  Test_Finit(void);
static void  Test_Change(void);
static void  Test_Exec(void);
static void  Test_MainLoop(void);
static void  Test_HandleTim1IRQ(void);
static void  Test_HandleTim2IRQ(void);
static void  Test_HandleTim3IRQ(void);

TestInterface TI_SimplestFlash = {
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

#define TIM_BRG       MDR_BRG_div16
#define TIM_PSC       1000
#define TIM_PERIOD    4000

static void Test_Init(void)
{
  MDRB_LCD_Print("Simplest Timer", 3);
  MDRB_LCD_Print("and Sync Run", 5);
  
  MDRB_LED_Init(MDRB_LED_1 | MDRB_LED_2 | MDRB_LED_3);
  MDRB_LED_Set (MDRB_LED_1 | MDRB_LED_2 | MDRB_LED_3, 0);
  
  MDR_Timer_InitPeriod(MDR_TIMER1ex, TIM_BRG, TIM_PSC, TIM_PERIOD, true);
  MDR_Timer_InitPeriod(MDR_TIMER2ex, TIM_BRG, TIM_PSC, TIM_PERIOD, true);
  MDR_Timer_InitPeriod(MDR_TIMER3ex, TIM_BRG, TIM_PSC, TIM_PERIOD, true);
  
  MDR_Timer_StartSync(TIM1_StartMsk | TIM2_StartMsk | TIM3_StartMsk);
}  

static void Test_Finit(void)
{
  MDR_Timer_StopSync(TIM1_StartMsk | TIM2_StartMsk | TIM3_StartMsk);
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
  MDR_Timer_ClearEvent(MDR_TIMER1, TIM_FL_CNT_ARR);
  
  MDRB_LED_Switch(MDRB_LED_1);
}

static void Test_HandleTim2IRQ(void)
{
  MDR_Timer_ClearEvent(MDR_TIMER2, TIM_FL_CNT_ARR);
  
  MDRB_LED_Switch(MDRB_LED_2);
}

static void Test_HandleTim3IRQ(void)
{
  MDR_Timer_ClearEvent(MDR_TIMER3, TIM_FL_CNT_ARR);
  
  MDRB_LED_Switch(MDRB_LED_3);
}

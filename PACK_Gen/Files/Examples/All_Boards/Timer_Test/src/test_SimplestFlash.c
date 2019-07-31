#include <MDR_Timer.h>
#include <MDRB_LEDs.h>
#include <MDRB_LCD.h>

#include "test_Defs.h"

//  ОПИСАНИЕ:
//  Пример простейшей инициализации таймера для получения прерываний с заданным периодом.
//  Одновременно мигают три светодиода от трех таймеров считающих синхронно.
//  Кнопка Right включает-выключает синхронное мигание.

//  Test Interface functions
static void  Test_Init(void);
static void  Test_Finit(void);
static void  Test_Empty(void);
static void  Test_Change(void);
static void  Test_HandleTim1IRQ(void);
static void  Test_HandleTim2IRQ(void);
static void  Test_HandleTim3IRQ(void);

extern TestInterface TI_SimplestFlash;

TestInterface TI_SimplestFlash = {
  .funcInit       = Test_Init,
  .funcFinit      = Test_Finit,
  .funcChange     = Test_Change,
  .funcExec       = Test_Empty,
  .funcMainLoop   = Test_Empty,
  .funcHandlerTim1 = Test_HandleTim1IRQ,
  .funcHandlerTim2 = Test_HandleTim2IRQ,
  .funcHandlerTim3 = Test_HandleTim3IRQ,
  .funcHandlerTim4 = Test_HandleTim3IRQ,
};

static bool started = false;

static void Test_Init(void)
{
#ifndef LCD_IS_7SEG_DISPLAY
  MDRB_LCD_Print("Simplest Timer", 3);
  MDRB_LCD_Print("and Sync Run", 5);
#else
  MDRB_LCD_Print(TEST_ID__SIMPLE_FLASH);
#endif
  
  MDRB_LED_Init(LED_SEL_MAX);
  MDRB_LED_Set (LED_SEL_MAX, 0);
  
  MDR_Timer_InitPeriod(MDR_TIMER1ex, TIM_BRG_LED, TIM_PSG_LED, TIM_PERIOD_LED, true);
  MDR_Timer_InitPeriod(MDR_TIMER2ex, TIM_BRG_LED, TIM_PSG_LED, TIM_PERIOD_LED, true);
#ifdef  USE_TIMER3  
  MDR_Timer_InitPeriod(MDR_TIMER3ex, TIM_BRG_LED, TIM_PSG_LED, TIM_PERIOD_LED, true);
#endif
  
  MDR_Timer_StartSync(START_SYNC_SEL_MAX);
  started = true;
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
}

static void Test_Empty(void)
{

}

static void Test_Change(void)
{
 if (started)
   MDR_Timer_StopSync(START_SYNC_SEL_MAX);
 else
   MDR_Timer_StartSync(START_SYNC_SEL_MAX);
 
 started = !started;
}

static void Test_HandleTim1IRQ(void)
{
  MDR_Timer_ClearEvent(MDR_TIMER1, TIM_FL_CNT_ARR);
  MDRB_LED_Toggle(MDRB_LED_1);
}

static void Test_HandleTim2IRQ(void)
{
  MDR_Timer_ClearEvent(MDR_TIMER2, TIM_FL_CNT_ARR);
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

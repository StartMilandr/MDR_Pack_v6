#include <MDR_Timer.h>
#include <MDRB_LEDs.h>

#include "test_Defs.h"
#include "MDRB_ShowMess.h"

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
static void TestStart(void);
static void TestStop(void);

static void Test_Init(void)
{
  //  LCD / UART_Dbg show TestName
  MDR_ShowMess(MESS__SIMPLE_FLASH);   
    
  MDRB_LED_Init(LED_SEL_MAX);
  MDRB_LED_Set (LED_SEL_MAX, 0);
  
  MDR_Timer_InitPeriod(MDR_TIMER1ex, TIM_BRG_LED, TIM_PSG_LED, TIM_PERIOD_LED, true);
  MDR_Timer_InitPeriod(MDR_TIMER2ex, TIM_BRG_LED, TIM_PSG_LED, TIM_PERIOD_LED, true);
#ifdef  USE_TIMER3  
  MDR_Timer_InitPeriod(MDR_TIMER3ex, TIM_BRG_LED, TIM_PSG_LED, TIM_PERIOD_LED, true);
#endif

  TestStart();
  
  started = true;
}  

static void TestStart(void)
{
#if defined(MDR_TIM_HAS_SYNC_START) && !defined(SYNC_START_UNAVALABLE)    
  MDR_Timer_StartSync(START_SYNC_SEL_MAX);
#else
  MDR_Timer_Start(MDR_TIMER1ex);
  MDR_Timer_Start(MDR_TIMER2ex);
  #ifdef  USE_TIMER3    
    MDR_Timer_Start(MDR_TIMER3ex);
  #endif  
#endif 
}

static void TestStop(void)
{
#if defined(MDR_TIM_HAS_SYNC_START) && !defined(SYNC_START_UNAVALABLE)    
  MDR_Timer_StopSync(START_SYNC_SEL_MAX);
#else
  MDR_Timer_Stop(MDR_TIMER1ex);
  MDR_Timer_Stop(MDR_TIMER2ex);
  #ifdef  USE_TIMER3    
    MDR_Timer_Stop(MDR_TIMER3ex);
  #endif    
#endif
}

static void Test_Finit(void)
{
  TestStop();
  
  MDR_Timer_DeInit(MDR_TIMER1ex);
  MDR_Timer_DeInit(MDR_TIMER2ex);
#ifdef  USE_TIMER3  
  MDR_Timer_DeInit(MDR_TIMER3ex);
#endif
  
  LED_Uninitialize();
  
  if (!MDR_ShowRestore_IfConflTim())
    MDR_ShowRestore_IfConflLED();
}

static void Test_Empty(void)
{

}

static void Test_Change(void)
{
 if (started)
   TestStop();
 else
   TestStart();
 
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

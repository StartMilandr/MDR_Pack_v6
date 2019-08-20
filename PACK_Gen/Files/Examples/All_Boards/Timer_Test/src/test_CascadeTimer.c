#include <MDR_Timer.h>
#include <MDRB_LEDs.h>

#include "test_Defs.h"
#include "MDRB_ShowMess.h"

//  ОПИСАНИЕ:
//  Пример каскадного включения таймеров.
//
//  ОСОБЕННОСТИ:
//  TIMER1 считает TIM_CLOCK обычным образом.
//  TIMER2 подключенный каскадно к TIMER1 отрабатывает правильно - период в TIMER2_ARR+1 раза длиннее, события CNT=ARR возникают синхронно и соответственной с разной частотой.
//  НО по неизвестной причине TIMER3 и TIMER4 подключенные каскадно переключаются не по CNT=ARR предыдущего таймера, а с задержкой на один период самого младшего таймера TIMER1.
//  Для TIMER4 задержка на два периода TIMER1.
//  Возможно проблема в ПО, например при выводе в порты GPIO - будет проверено через аппаратный вывод PWM.
//  
//  Периоды удобней смотреть на осциллографе. Для этого на отладочных платах, там где есть, лучше снять джампера со светодиодов и подключиться осцилографом.
//  Период TIMER1 для удобства наблюдения лучше сильно уменьшить, например значениями - TIM_BRG_LED, TIM_PSG_LED. 


//  Test Interface functions
static void  Test_Init(void);
static void  Test_Finit(void);
static void  Test_Empty(void);
static void  Test_HandleTim1IRQ(void);
static void  Test_HandleTim2IRQ(void);
static void  Test_HandleTim3IRQ(void);
static void  Test_HandleTim4IRQ(void);

extern TestInterface TI_CascadeTimer;

TestInterface TI_CascadeTimer = {
  .funcInit       = Test_Init,
  .funcFinit      = Test_Finit,
  .funcChange     = Test_Empty,
  .funcExec       = Test_Empty,
  .funcMainLoop   = Test_Empty,
  .funcHandlerTim1 = Test_HandleTim1IRQ,
  .funcHandlerTim2 = Test_HandleTim2IRQ,
  .funcHandlerTim3 = Test_HandleTim3IRQ,
  .funcHandlerTim4 = Test_HandleTim4IRQ,
};


#define TIM_CASCADE_PER   2

static void Test_Init(void)
{
  //  LCD / UART_Dbg show TestName
  MDR_ShowMess(MESS__COUNT_CASCADE);    
  
  MDRB_LED_Init(LED_SEL_MAX);
  MDRB_LED_Set(LED_SEL_MAX, 0);
  
  //  Fastest Counter
  MDR_Timer_InitPeriod(MDR_TIMER1ex, TIM_BRG_LED, TIM_PSG_LED, TIM_PERIOD_LED, true);
  //  Middle Counter
  MDR_Timer_AddCascadePeriod(MDR_TIMER2ex, TIM_BRG_LED, TIM_EventTIM1_CNT_ARR, TIM_CASCADE_PER, true);
#ifdef  USE_TIMER3  
  //  Slow Counter
  MDR_Timer_AddCascadePeriod(MDR_TIMER3ex, TIM_BRG_LED, TIM_EventTIM2_CNT_ARR, TIM_CASCADE_PER, true);
#endif  
#ifdef  TIMER4_EXIST
  //  Slowest Counter
  MDR_Timer_AddCascadePeriod(MDR_TIMER4ex, TIM_BRG_LED, TIM_EventTIM3_CNT_ARR, TIM_CASCADE_PER, true);    
#endif

#if defined(MDR_TIM_HAS_SYNC_START) && !defined(SYNC_START_UNAVALABLE)
  #ifdef  TIMER4_EXIST
    MDR_Timer_Start(MDR_TIMER4ex);
  #endif 
  
  MDR_Timer_StartSync(START_SYNC_SEL_MAX);
#else
  // VE8 - Если инициализировать начиная с TIM3 до TIM1, то начинают непрерывно генерится прерывания и до включения TIM1 код не доходит.
  MDR_Timer_Start(MDR_TIMER1ex);
  MDR_Timer_Start(MDR_TIMER2ex);  
  #ifdef  USE_TIMER3  
    MDR_Timer_Start(MDR_TIMER3ex);
  #endif
  #ifdef  TIMER4_EXIST
    MDR_Timer_Start(MDR_TIMER4ex);
  #endif
#endif
}  

static void Test_Finit(void)
{
#if defined(MDR_TIM_HAS_SYNC_START) && !defined(SYNC_START_UNAVALABLE)
  MDR_Timer_StopSync(START_SYNC_SEL_MAX);
  #ifdef  USE_TIMER4  
    MDR_Timer_Stop(MDR_TIMER4ex);
  #endif    
#else
  #ifdef  TIMER4_EXIST  
    MDR_Timer_Stop(MDR_TIMER4ex);
  #endif      
  #ifdef  USE_TIMER3  
    MDR_Timer_Stop(MDR_TIMER3ex);
  #endif  
  MDR_Timer_Stop(MDR_TIMER2ex);
  MDR_Timer_Stop(MDR_TIMER1ex);
#endif
  
  MDR_Timer_DeInit(MDR_TIMER1ex);
  MDR_Timer_DeInit(MDR_TIMER2ex);
#ifdef  USE_TIMER3   
  MDR_Timer_DeInit(MDR_TIMER3ex);
#endif    
#ifdef  TIMER4_EXIST  
  MDR_Timer_DeInit(MDR_TIMER4ex);
#endif  
  
  LED_Uninitialize();

  MDR_ShowRestore_IfConflLED();
}

static void Test_Empty(void)
{

}

static void Test_HandleTim1IRQ(void)
{
  if (MDR_TIMER1->STATUS & TIM_FL_CNT_ARR)
  {      
    MDR_Timer_ClearEvent(MDR_TIMER1, TIM_FL_CNT_ARR);  
    MDRB_LED_Toggle(MDRB_LED_1);
  }
}

static void Test_HandleTim2IRQ(void)
{
  if (MDR_TIMER2->STATUS & TIM_FL_CNT_ARR)
  {  
    MDR_Timer_ClearEvent(MDR_TIMER2, TIM_FL_CNT_ARR);    
    
#ifdef MDRB_LED_2
    MDRB_LED_Toggle(MDRB_LED_2);
#endif
  }
}

static void Test_HandleTim3IRQ(void)
{
#ifdef USE_TIMER3
  if (MDR_TIMER3->STATUS & TIM_FL_CNT_ARR)
  {    
    MDR_Timer_ClearEvent(MDR_TIMER3, TIM_FL_CNT_ARR);  
    MDRB_LED_Toggle(MDRB_LED_3);
  }
#endif
}

static void Test_HandleTim4IRQ(void)
{
#ifdef TIMER4_EXIST  
  if (MDR_TIMER4->STATUS & TIM_FL_CNT_ARR)
  {    
    MDR_Timer_ClearEvent(MDR_TIMER4, TIM_FL_CNT_ARR);  
    MDRB_LED_Toggle(MDRB_LED_4);
  }
#endif
}

#include <MDR_Timer.h>
#include <MDRB_LEDs.h>
#include <MDRB_LCD.h>

#include "test_Defs.h"

//  ОПИСАНИЕ:
//  Пример каскадного включения таймеров.
//
//  ОСОБЕННОСТИ:
//  TIMER1 считает TIM_CLOCK обычным образом.
//  TIMER2 подключенный каскадно к TIMER1 отрабатывает правильно - период в TIMER2_ARR+1 раза длиннее, события CNT=ARR возникают синхронно и соответственной с разной частотой.
//  НО по неизвестной причине TIMER3 и TIMER4 подключенные каскадно переключаются не по CNT=ARR предыдущего таймера, а с задержкой на один период самого младшего таймера TIMER1.
//  Для TIMER4 задержка на два периода TIMER1.
//  Возможно проблема в ПО, например при выводе в порты GPIO - будет проверено через аппаратный вывод PWM.


//  Test Interface functions
static void  Test_Init(void);
static void  Test_Finit(void);
static void  Test_Change(void);
static void  Test_Exec(void);
static void  Test_MainLoop(void);
static void  Test_HandleTim1IRQ(void);
static void  Test_HandleTim2IRQ(void);
static void  Test_HandleTim3IRQ(void);
static void  Test_HandleTim4IRQ(void);

TestInterface TI_CascadeTimer = {
  .funcInit       = Test_Init,
  .funcFinit      = Test_Finit,
  .funcChange     = Test_Change,
  .funcExec       = Test_Exec,
  .funcMainLoop   = Test_MainLoop,
  .funcHandlerTim1 = Test_HandleTim1IRQ,
  .funcHandlerTim2 = Test_HandleTim2IRQ,
  .funcHandlerTim3 = Test_HandleTim3IRQ,
  .funcHandlerTim4 = Test_HandleTim4IRQ,
};

#define SHOW_TO_OSCILL  0

#if SHOW_TO_OSCILL
  //  Show to oscilloscope
  #define TIM_CLOCK_PSC     100
  #define TIM_BRG_DIV       MDR_BRG_div1
  #define TIM_CASCADE_PER   3
  
#else
  //  Show to LED
  #define TIM_CLOCK_PSC     1000
  #define TIM_BRG_DIV       MDR_BRG_div16
  #define TIM_CASCADE_PER   2
#endif 

static void Test_Init(void)
{
  MDRB_LCD_Print("Double Timer", 3);
  MDRB_LCD_ClearLine(5);
  
  MDRB_LED_Init(MDRB_LED_1 | MDRB_LED_2 | MDRB_LED_3 | MDRB_LED_4);
  MDRB_LED_Set(MDRB_LED_1 | MDRB_LED_2 | MDRB_LED_3 | MDRB_LED_4, 0);
  
  //  Fastest Counter
  MDR_Timer_InitPeriod(MDR_TIMER1ex, TIM_BRG_DIV, TIM_CLOCK_PSC, 4000, true);
  //  Middle Counter
  MDR_Timer_AddCascadePeriod(MDR_TIMER2ex, TIM_BRG_DIV, TIM_EventTIM1_CNT_ARR, TIM_CASCADE_PER, true);
  //  Slow Counter
  MDR_Timer_AddCascadePeriod(MDR_TIMER3ex, TIM_BRG_DIV, TIM_EventTIM2_CNT_ARR, TIM_CASCADE_PER, true);
  //  Slowest Counter
#ifdef  TIMER4_EXIST
  MDR_Timer_AddCascadePeriod(MDR_TIMER4ex, TIM_BRG_DIV, TIM_EventTIM3_CNT_ARR, TIM_CASCADE_PER, true);  
  MDR_Timer_Start(MDR_TIMER4ex);
#endif
  
  MDR_Timer_StartSync(TIM1_StartMsk | TIM2_StartMsk | TIM3_StartMsk);
}  

static void Test_Finit(void)
{
  MDR_Timer_StopSync(TIM1_StartMsk | TIM2_StartMsk | TIM3_StartMsk);
  MDR_Timer_DeInit(MDR_TIMER1ex);
  MDR_Timer_DeInit(MDR_TIMER2ex);
  MDR_Timer_DeInit(MDR_TIMER3ex);
  
#ifdef  TIMER4_EXIST  
  MDR_Timer_DeInit(MDR_TIMER4ex);
#endif
  
  LED_Uninitialize();
}

static void Test_Change(void)
{

}

static void Test_Exec(void)
{

}

static bool doSwitch1, doSwitch2, doSwitch3 = false;

#ifdef TIMER4_EXIST  
  static bool doSwitch4 = false;
#endif

static void  Test_MainLoop(void)
{ 
  if (doSwitch1)
  {
    MDRB_LED_Switch(MDRB_LED_1);
    doSwitch1 = false;
  }
  if (doSwitch2)
  {
    MDRB_LED_Switch(MDRB_LED_2);
    doSwitch2 = false;
  }
  if (doSwitch3)
  {
    MDRB_LED_Switch(MDRB_LED_3);
    doSwitch3 = false;
  }  
#ifdef TIMER4_EXIST  
  if (doSwitch4)
  {
    MDRB_LED_Switch(MDRB_LED_4);
    doSwitch4 = false;
  }  
#endif
}

static void Test_HandleTim1IRQ(void)
{
  if (MDR_TIMER1->STATUS & TIM_FL_CNT_ARR)
  {      
    //while (MDR_TIMER1->STATUS & TIM_FL_CNT_ARR)
      MDR_Timer_ClearEvent(MDR_TIMER1, TIM_FL_CNT_ARR);
  
    //MDRB_LED_Switch(MDRB_LED_1);
    doSwitch1 = true;
  }
}

static void Test_HandleTim2IRQ(void)
{
  if (MDR_TIMER2->STATUS & TIM_FL_CNT_ARR)
  {  
    //while (MDR_TIMER2->STATUS & TIM_FL_CNT_ARR)
      MDR_Timer_ClearEvent(MDR_TIMER2, TIM_FL_CNT_ARR);
    
    //MDRB_LED_Switch(MDRB_LED_2);
    doSwitch2 = true;
  }
}

static void Test_HandleTim3IRQ(void)
{
  if (MDR_TIMER3->STATUS & TIM_FL_CNT_ARR)
  {    
    //while (MDR_TIMER3->STATUS & TIM_FL_CNT_ARR)  
      MDR_Timer_ClearEvent(MDR_TIMER3, TIM_FL_CNT_ARR);
  
    //MDRB_LED_Switch(MDRB_LED_3);
    doSwitch3 = true;
  }
}

static void Test_HandleTim4IRQ(void)
{
#ifdef TIMER4_EXIST  
  while (MDR_TIMER4->STATUS & TIM_FL_CNT_ARR)    
    MDR_Timer_ClearEvent(MDR_TIMER4, TIM_FL_CNT_ARR);
  
  doSwitch4 = true;
#endif
}

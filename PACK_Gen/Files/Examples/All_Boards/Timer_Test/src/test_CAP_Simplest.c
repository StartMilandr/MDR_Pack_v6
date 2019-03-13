#include <MDR_Timer.h>
#include <MDRB_LEDs.h>
#include <MDRB_LCD.h>

#include <MDRB_Timer_PinSelect.h>
#include "test_Defs.h"


//  ОПИСАНИЕ:
//    Timer1 генерирует импульсы на выходе CH1 и мигает светодиодом LED1 каждый период.
//    Timer2 захватывает события переднего и заднего фронтов сигнала от Timer1_CH1.
//      При каждом событии генерируется прерывание и переключается светодиод LED2.
//    Мигания светодиода LED2 должны получиться в 2 раза чаще чем LED1.


//  Test Interface functions
static void  Test_Init(void);
static void  Test_Finit(void);
static void  Test_Change(void);
static void  Test_Exec(void);
static void  Test_MainLoop(void);
static void  Test_HandleTim1IRQ(void);
static void  Test_HandleTim2IRQ(void);
static void  Test_HandleTim3IRQ(void);

TestInterface TI_CAP_Simplest = {
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
#define TIM_PERIOD    3000
#define LED2_PERIOD   4

static void Test_Init(void)
{  
  MDRB_LCD_Print("CAP Simplest", 3);
  MDRB_LCD_ClearLine(5);
    
  MDRB_LED_Init(MDRB_LED_1 | MDRB_LED_2);
  MDRB_LED_Set (MDRB_LED_1 | MDRB_LED_2, 0);  
  
  //  Timer1_CH1 - Pulse output for Capture
  MDR_Timer_InitPeriod(MDR_TIMER1ex, TIM_BRG, TIM_PSC, TIM_PERIOD, true);
  MDR_TimerPulse_InitPulse(MDR_TIMER1_CH1, TIM_PERIOD, 50);
  
  MDR_TimerCh_InitPinGPIO(&_pinTim1_CH1,  MDR_PIN_FAST);
     
  //  Timer2_CH1 - Capture Rise and Fall fronts from Timer1_CH1
  MDR_Timer_InitPeriodDirIRQ(MDR_TIMER2ex, TIM_BRG, TIM_PSC, TIM_PERIOD, TIM_FL_CCR_CAP_CH1 | TIM_FL_CCR1_CAP_CH1, TIM_CountUp);
  MDR_TimerCh_InitCAP(MDR_TIMER2_CH1, NULL);
  
  MDR_TimerCh_InitPinGPIO(&_pinTim2_CH1, MDR_PIN_FAST);
    
  // Sync Start
  MDR_Timer_StartSync(TIM1_StartMsk | TIM2_StartMsk);
}  

static void Test_Finit(void)
{
  MDR_TimerCh_DeInitPinGPIO(&_pinTim1_CH1);
  MDR_TimerCh_DeInitPinGPIO(&_pinTim2_BRK);

  MDR_Timer_StopSync(TIM1_StartMsk | TIM2_StartMsk);
  MDR_Timer_DeInit(MDR_TIMER1ex);
  MDR_Timer_DeInit(MDR_TIMER2ex);
  
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
  if (MDR_Timer_GetStatus(MDR_TIMER2) & TIM_FL_CCR_CAP_CH1)
  {  
    MDR_Timer_ClearEvent(MDR_TIMER2, TIM_FL_CCR_CAP_CH1);
  }  
  else if (MDR_Timer_GetStatus(MDR_TIMER2) & TIM_FL_CCR1_CAP_CH1)
  {
    MDR_Timer_ClearEvent(MDR_TIMER2, TIM_FL_CCR1_CAP_CH1);
  }
  
  MDRB_LED_Switch(MDRB_LED_2);
}

static void Test_HandleTim3IRQ(void)
{

}

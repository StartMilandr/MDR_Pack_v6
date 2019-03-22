#include <MDR_Timer.h>
#include <MDRB_LEDs.h>
#include <MDRB_LCD.h>

#include <MDRB_Timer_PinSelect.h>
#include "test_Defs.h"


//  ОПИСАНИЕ:
//    Timer1 генерирует импульсы на выходе CH1 и мигает светодиодом LED1 каждый период.
//    Timer2 захватывает события переднего и заднего фронтов сигнала от Timer1_CH1.
//      При каждом событии захвата, по переднему и заднему вронту, генерируется прерывание и переключается светодиод LED2.
//    Мигания светодиода LED2 должны получиться в 2 раза чаще чем LED1.

//  ERRATA
//    В некоторых МК под отладчиком можно заметить, что при инициализации канала в режим захвата, канал почему-то отображается как будто бы он в режиме ШИМ.
//    Т.е. бит 15 CAP_nPWN в регистре CHx_CNTRL равен 0, хотя в регистр реально была записана 1-ца в этот бит.
//    Это ошибка чтения регистра. Канал реально работает в захвате, но чтение регистра всегда возвращает CAP_nPWN == 0.
//    В серии 1986ВЕ9х это поведение исправлено, остальные надо проверять:
//    Не исправлено в ВК214, ВК234.


//  Test Interface functions
static void  Test_Init(void);
static void  Test_Finit(void);
static void  Test_Empty(void);
static void  Test_HandleIRQ_PWM(void);
static void  Test_HandleIRQ_CAP(void);

TestInterface TI_CAP_Simplest = {
  .funcInit       = Test_Init,
  .funcFinit      = Test_Finit,
  .funcChange     = Test_Empty,
  .funcExec       = Test_Empty,
  .funcMainLoop   = Test_Empty,
  
#ifdef PWM1_IS_TIM1 
  .funcHandlerTim1 = Test_HandleIRQ_PWM,
#else
  .funcHandlerTim1 = Test_HandleIRQ_CAP,
#endif

#ifdef PWM1_IS_TIM2 
  .funcHandlerTim2 = Test_HandleIRQ_PWM,
#else
  .funcHandlerTim2 = Test_HandleIRQ_CAP,
#endif
  
  #ifdef PWM1_IS_TIM3 
  .funcHandlerTim3 = Test_HandleIRQ_PWM,
#else
  .funcHandlerTim3 = Test_HandleIRQ_CAP,
#endif

#ifdef PWM1_IS_TIM4 
  .funcHandlerTim4 = Test_HandleIRQ_PWM,
#else
  .funcHandlerTim4 = Test_HandleIRQ_CAP,
#endif
};


static void Test_Init(void)
{  
  //  To LCD
#ifndef LCD_IS_7SEG_DISPLAY
  MDRB_LCD_Print("CAP Simplest", 3);
  
#elif defined (LCD_CONFLICT_TIM)
  //  LCD conflicts with Timers channel
  //  Show Test index and LCD Off
  MDRB_LCD_Print("8");  
  MDR_LCD_BlinkyStart(MDR_LCD_Blink_2Hz, MDR_Off);
  MDR_Delay_ms(LCD_HIDE_DELAY, MDR_CPU_GetFreqHz(false));
  
  MDR_LCD_DeInit();
#else
  MDRB_LCD_Print("8");
#endif 
  
  MDRB_LED_Init(MDRB_LED_1 | MDRB_LED_2);
  MDRB_LED_Set(MDRB_LED_1 | MDRB_LED_2, 0);
  
  //  PWM - Output pulses  for Capture 
  MDR_Timer_InitPeriod    (PWM1_TIMex, TIM_BRG_LED, TIM_PSG_LED, TIM_PERIOD_LED, true); 
  MDR_TimerPulse_InitPulse(PWM1_TIM_CH, TIM_PERIOD_LED, 50);  
  MDR_TimerCh_InitPinGPIO(&PWM1_PIN_CH,  MDR_PIN_FAST);
     
  //  CAP - Capture Rise and Fall fronts from Timer1_CH1
  MDR_Timer_InitPeriodDirIRQ(CAP_TIMex, TIM_BRG_LED, TIM_PSG_LED, TIM_PERIOD_LED, CAP_EVENT_RISE | CAP_EVENT_FALL, TIM_CountUp);
  MDR_TimerCh_InitCAP(CAP_TIM_CH, NULL);
  MDR_TimerCh_InitPinGPIO(&CAP_PIN_CH, MDR_PIN_FAST);
      
  // Start
#ifndef SYNC_START_UNAVALABLE  
  MDR_Timer_StartSync(PWM1_START_SEL_MSK | CAP_START_SEL_MSK);
#else
  MDR_Timer_Start(PWM1_TIMex);
  MDR_Timer_Start(CAP_TIMex);
#endif  
}  

static void Test_Finit(void)
{
  //  Stop
#ifndef SYNC_START_UNAVALABLE  
  MDR_Timer_StopSync(PWM1_START_SEL_MSK | CAP_START_SEL_MSK);
#else
  MDR_Timer_Stop(PWM1_TIMex);
  MDR_Timer_Stop(CAP_TIMex);
#endif   
  
  //  Pins to third state  
  MDR_TimerCh_DeInitPinGPIO(&PWM1_PIN_CH);
  MDR_TimerCh_DeInitPinGPIO(&CAP_PIN_CH);
  
  //  Finit Timers
  MDR_Timer_DeInit(PWM1_TIMex);
  MDR_Timer_DeInit(CAP_TIMex);
  
  LED_Uninitialize();  
  
#ifdef LCD_CONFLICT_LED
  MDRB_LCD_CapturePins();
#endif
#ifdef LCD_CONFLICT_TIM
  // Restore LCD
  MDRB_LCD_Init(MDR_CPU_GetFreqHz(false));   
#endif  
}

static void Test_HandleIRQ_PWM(void)
{
  MDR_Timer_ClearEvent(PWM1_TIM, TIM_FL_CNT_ARR);
  
  MDRB_LED_Switch(MDRB_LED_1);  
}

static void Test_HandleIRQ_CAP(void)
{
  if (MDR_Timer_GetStatus(CAP_TIM) & CAP_EVENT_RISE)
    MDR_Timer_ClearEvent(CAP_TIM, CAP_EVENT_RISE);
  else if (MDR_Timer_GetStatus(CAP_TIM) & CAP_EVENT_FALL)
    MDR_Timer_ClearEvent(CAP_TIM, CAP_EVENT_FALL);
  
  MDRB_LED_Switch(MDRB_LED_2);
}

static void  Test_Empty(void)
{
}


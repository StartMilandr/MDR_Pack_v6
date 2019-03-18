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
static void  Test_HandleTim1IRQ(void);
static void  Test_HandleTim2IRQ(void);

TestInterface TI_CAP_Simplest = {
  .funcInit       = Test_Init,
  .funcFinit      = Test_Finit,
  .funcChange     = Test_Empty,
  .funcExec       = Test_Empty,
  .funcMainLoop   = Test_Empty,
  .funcHandlerTim1 = Test_HandleTim1IRQ,
  .funcHandlerTim2 = Test_HandleTim2IRQ,
  .funcHandlerTim3 = Test_Empty,
  .funcHandlerTim4 = Test_Empty,
};

//  Channel Select
#ifdef USE_MDR1986VE91
  #define TIM_PWM             MDR_TIMER1ex
  #define TIM_PWM_CH          MDR_TIMER1_CH1
  #define TIM_PWM_PIN_CH      _pinTim1_CH1
  #define TIM_PWM_START_MSK   TIM1_StartMsk

  #define TIM_CAP             MDR_TIMER2ex
  #define TIM_CAP_CH          MDR_TIMER2_CH1
  #define TIM_CAP_PIN_CH      _pinTim2_CH1
  #define TIM_CAP_START_MSK   TIM2_StartMsk
  #define TIM_CAP_FL_RISE     TIM_FL_CCR_CAP_CH1
  #define TIM_CAP_FL_FALL     TIM_FL_CCR1_CAP_CH1

#elif defined (USE_MDR1986VK214)
  #define TIM_PWM             MDR_TIMER1ex
  #define TIM_PWM_CH          MDR_TIMER1_CH1
  #define TIM_PWM_PIN_CH      _pinTim1_CH1
  #define TIM_PWM_START_MSK   TIM1_StartMsk

  #define TIM_CAP             MDR_TIMER2ex
  #define TIM_CAP_CH          MDR_TIMER2_CH1
  #define TIM_CAP_PIN_CH      _pinTim2_CH1
  #define TIM_CAP_START_MSK   TIM2_StartMsk
  #define TIM_CAP_FL_RISE     TIM_FL_CCR_CAP_CH1
  #define TIM_CAP_FL_FALL     TIM_FL_CCR1_CAP_CH1


  #define LCD_CONFLICT
  
#elif defined (USE_MDR1986VK234)
  #define TIM_PWM             MDR_TIMER1ex
  #define TIM_PWM_CH          MDR_TIMER1_CH3
  #define TIM_PWM_PIN_CH      _pinTim1_CH3
  #define TIM_PWM_START_MSK   TIM1_StartMsk

  #define TIM_CAP             MDR_TIMER2ex
  #define TIM_CAP_CH          MDR_TIMER2_CH3
  #define TIM_CAP_PIN_CH      _pinTim2_CH3
  #define TIM_CAP_START_MSK   TIM2_StartMsk
  #define TIM_CAP_FL_RISE     TIM_FL_CCR_CAP_CH3
  #define TIM_CAP_FL_FALL     TIM_FL_CCR1_CAP_CH3

#endif


static void Test_Init(void)
{  
  //  To LCD
#ifndef LCD_IS_7SEG_DISPLAY
  MDRB_LCD_Print("CAP Simplest", 3);
  
#elif defined (LCD_CONFLICT)
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
  MDRB_LED_Set (MDRB_LED_1 | MDRB_LED_2, 0);  
  
  //  Timer1_CH1 - Pulse output for Capture 
  MDR_Timer_InitPeriod(TIM_PWM, TIM_BRG_LED, TIM_PSG_LED, TIM_PERIOD_LED, true); 
  MDR_TimerPulse_InitPulse(TIM_PWM_CH, TIM_PERIOD_LED, 50);
  
  MDR_TimerCh_InitPinGPIO(&TIM_PWM_PIN_CH,  MDR_PIN_FAST);
     
  //  Timer2_CH1 - Capture Rise and Fall fronts from Timer1_CH1
  MDR_Timer_InitPeriodDirIRQ(TIM_CAP, TIM_BRG_LED, TIM_PSG_LED, TIM_PERIOD_LED, TIM_CAP_FL_RISE | TIM_CAP_FL_FALL, TIM_CountUp);
  MDR_TimerCh_InitCAP(TIM_CAP_CH, NULL);
  
  MDR_TimerCh_InitPinGPIO(&TIM_CAP_PIN_CH, MDR_PIN_FAST);
    
  // Sync Start
  MDR_Timer_StartSync(TIM_PWM_START_MSK | TIM_CAP_START_MSK);
}  

static void Test_Finit(void)
{
  MDR_TimerCh_DeInitPinGPIO(&TIM_PWM_PIN_CH);
  MDR_TimerCh_DeInitPinGPIO(&TIM_CAP_PIN_CH);

  MDR_Timer_StopSync(TIM_PWM_START_MSK | TIM_CAP_START_MSK);
  MDR_Timer_DeInit(TIM_PWM);
  MDR_Timer_DeInit(TIM_CAP);
  
  LED_Uninitialize();  
  
#ifdef LCD_CONFLICT
  // Restore LCD
  MDRB_LCD_Init(MDR_CPU_GetFreqHz(false));   
#endif  
}

static void Test_HandleTim1IRQ(void)
{
  MDR_Timer_ClearEvent(MDR_TIMER1, TIM_FL_CNT_ARR);
  
  MDRB_LED_Switch(MDRB_LED_1);  
}

static void Test_HandleTim2IRQ(void)
{
  if (MDR_Timer_GetStatus(MDR_TIMER2) & TIM_CAP_FL_RISE)
  {  
    MDR_Timer_ClearEvent(MDR_TIMER2, TIM_CAP_FL_RISE);
  }  
  else if (MDR_Timer_GetStatus(MDR_TIMER2) & TIM_CAP_FL_FALL)
  {
    MDR_Timer_ClearEvent(MDR_TIMER2, TIM_CAP_FL_FALL);
  }
  
  MDRB_LED_Switch(MDRB_LED_2);
}

static void  Test_Empty(void)
{
}


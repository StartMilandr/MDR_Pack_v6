#include <MDR_Timer.h>
#include <MDRB_LEDs.h>
#include <MDRB_LCD.h>

#include <MDRB_Timer_PinSelect.h>
#include "test_Defs.h"

//  ОПИСАНИЕ:
//  Пример генерации ШИМ по умолчанию - без задания опциональных настроек, MDR_TimerCh_CfgPWM = NULL.
//  Импульсы смотреть осциллографом на пинах.
//  ПРОВЕРИТЬ, что выходы каналов таймеров не замкнуты друг на друга (после тестов с захватом)!

//  Test Interface functions
static void  Test_Init(void);
static void  Test_Finit(void);
static void  Test_Empty(void);

TestInterface TI_PWM = {
  .funcInit       = Test_Init,
  .funcFinit      = Test_Finit,
  .funcChange     = Test_Empty,
  .funcExec       = Test_Empty,
  .funcMainLoop   = Test_Empty,
  .funcHandlerTim1 = Test_Empty,
  .funcHandlerTim2 = Test_Empty,
  .funcHandlerTim3 = Test_Empty,
  .funcHandlerTim4 = Test_Empty,
};

#define BRG_VALUE      MDR_BRG_div4
#define PSC_VALUE1     100
#define PSC_VALUE2      50
#define PERIOD_VALUE   900


#ifdef USE_MDR1986VE91
  #define TIM2_CH_SEL       MDR_TIMER2_CH3
  #define TIM2_PIN_CH       _pinTim2_CH3
  #define TIM2_PIN_nCH      _pinTim2_nCH3

#elif defined (USE_MDR1986VK214)
  #define TIM2_CH_SEL       MDR_TIMER2_CH1
  #define TIM2_PIN_CH       _pinTim2_CH1
  #define TIM2_PIN_nCH      _pinTim2_nCH1

  #define LCD_CONFLICT
  #define TIM_SINGLE_CH
#endif

static void Test_Init(void)
{ 
#ifndef LCD_IS_7SEG_DISPLAY
  MDRB_LCD_Print("Simplest PWM", 3);
  MDRB_LCD_Print("and Sync Run", 5);
  
#elif defined (LCD_CONFLICT)
  //  LCD conflicts with Timers channel
  //  Show Test index and LCD Off
  MDRB_LCD_Print("5");  
  MDR_LCD_BlinkyStart(MDR_LCD_Blink_2Hz, MDR_Off);
  MDR_Delay_ms(LCD_HIDE_DELAY, MDR_CPU_GetFreqHz(false));
  
  MDR_LCD_DeInit();
#else
  MDRB_LCD_Print("5");
#endif    
  
  //  Timer1
  MDR_Timer_InitPeriodDir(MDR_TIMER1ex, BRG_VALUE, PSC_VALUE1, PERIOD_VALUE, false, TIM_CountUpDown);
  
  MDR_TimerCh_InitPWM (MDR_TIMER1_CH1, NULL, MDR_TIM_PWM_RefTgl_eqCCR,   PERIOD_VALUE / 3); 
  MDR_TimerCh_InitPinGPIO(&_pinTim1_CH1,  MDR_PIN_FAST);
  MDR_TimerCh_InitPinGPIO(&_pinTim1_nCH1, MDR_PIN_FAST);
  
#ifndef TIM_SINGLE_CH
  MDR_TimerCh_InitPWM1(MDR_TIMER1_CH2, NULL, MDR_TIM_PWM1_RefTgl_eqCCRx, PERIOD_VALUE / 3, PERIOD_VALUE * 2 / 3);  
  MDR_TimerCh_InitPinGPIO(&_pinTim1_CH2,  MDR_PIN_FAST);
  MDR_TimerCh_InitPinGPIO(&_pinTim1_nCH2, MDR_PIN_FAST);
#endif
  
  //  Timer2
  MDR_Timer_InitPeriodDir(MDR_TIMER2ex, BRG_VALUE, PSC_VALUE2, PERIOD_VALUE, false, TIM_CountUpDown);
  MDR_TimerCh_InitPWM1(TIM2_CH_SEL, NULL, MDR_TIM_PWM1_RefTgl_eqCCRx, PERIOD_VALUE / 3, PERIOD_VALUE * 2 / 3);  

  MDR_TimerCh_InitPinGPIO(&TIM2_PIN_CH,  MDR_PIN_FAST);
  MDR_TimerCh_InitPinGPIO(&TIM2_PIN_nCH, MDR_PIN_FAST);

#ifndef TIM_SINGLE_CH
  MDR_TimerCh_InitPWM (MDR_TIMER2_CH4, NULL, MDR_TIM_PWM_RefTgl_eqCCR,   PERIOD_VALUE / 3);  
  MDR_TimerCh_InitPinGPIO(&_pinTim2_CH4,  MDR_PIN_FAST);
  MDR_TimerCh_InitPinGPIO(&_pinTim2_nCH4, MDR_PIN_FAST);
#endif

  // Sync Start
  MDR_Timer_StartSync(TIM1_StartMsk | TIM2_StartMsk);
}  

static void Test_Finit(void)
{
  MDR_TimerCh_DeInitPinGPIO(&_pinTim1_CH1);
  MDR_TimerCh_DeInitPinGPIO(&_pinTim1_nCH1);
  MDR_TimerCh_DeInitPinGPIO(&TIM2_PIN_CH);
  MDR_TimerCh_DeInitPinGPIO(&TIM2_PIN_nCH);
  
#ifndef TIM_SINGLE_CH  
  MDR_TimerCh_DeInitPinGPIO(&_pinTim1_CH2);
  MDR_TimerCh_DeInitPinGPIO(&_pinTim1_nCH2);
  MDR_TimerCh_DeInitPinGPIO(&_pinTim2_CH4);
  MDR_TimerCh_DeInitPinGPIO(&_pinTim2_nCH4);
#endif
  
  MDR_Timer_StopSync(TIM1_StartMsk | TIM2_StartMsk);
  MDR_Timer_DeInit(MDR_TIMER1ex);
  MDR_Timer_DeInit(MDR_TIMER2ex);
  
#ifdef LCD_CONFLICT  
  // Restore LCD
  MDRB_LCD_Init(MDR_CPU_GetFreqHz(false));   
#else  
  MDRB_LCD_ClearLine(5);
#endif
}

static void Test_Empty(void)
{
}


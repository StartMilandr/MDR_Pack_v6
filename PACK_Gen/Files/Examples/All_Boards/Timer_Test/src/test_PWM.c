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

static void Test_Init(void)
{ 
#ifndef LCD_IS_7SEG_DISPLAY
  MDRB_LCD_Print("Simplest PWM", 3);
  MDRB_LCD_Print("and Sync Run", 5);
  
#elif defined (LCD_CONFLICT_TIM)
  //  LCD conflicts with Timers channel
  //  Show Test index and LCD Off
  MDRB_LCD_Print("5");  
  MDR_LCD_BlinkyStart(MDR_LCD_Blink_2Hz, MDR_Off);
  MDR_Delay_ms(LCD_HIDE_DELAY, MDR_CPU_GetFreqHz(false));
  
  MDR_LCD_DeInit();
#else
  MDRB_LCD_Print("5");
#endif    
  
  //  PWM1
  MDR_Timer_InitPeriodDir(PWM1_TIMex, TIM_BRG_PWM, TIM_PSG_PWM1, TIM_PERIOD_PWM, false, TIM_CountUpDown);  
  MDR_TimerCh_InitPWM    (PWM1_TIM_CH, NULL, MDR_TIM_PWM_RefTgl_eqCCR,   TIM_PERIOD_PWM / 3); 
  MDR_TimerCh_InitPinGPIO(&PWM1_PIN_CH,  MDR_PIN_FAST);
  MDR_TimerCh_InitPinGPIO(&PWM1_PIN_nCH, MDR_PIN_FAST);
   
  //  PWM2
  MDR_Timer_InitPeriodDir(PWM2_TIMex, TIM_BRG_PWM, TIM_PSG_PWM1, TIM_PERIOD_PWM, false, TIM_CountUpDown);
  MDR_TimerCh_InitPWM1   (PWM2_TIM_CH, NULL, MDR_TIM_PWM1_RefTgl_eqCCRx, TIM_PERIOD_PWM / 3, TIM_PERIOD_PWM * 2 / 3);  
  MDR_TimerCh_InitPinGPIO(&PWM2_PIN_CH,  MDR_PIN_FAST);
  MDR_TimerCh_InitPinGPIO(&PWM2_PIN_nCH, MDR_PIN_FAST);

  // Start
#ifndef SYNC_START_UNAVALABLE  
  MDR_Timer_StartSync(PWM1_START_SEL_MSK | PWM2_START_SEL_MSK);
#else
  MDR_Timer_Start(PWM1_TIMex);
  MDR_Timer_Start(PWM2_TIMex);
#endif
}  

static void Test_Finit(void)
{
  //  Stop
#ifndef SYNC_START_UNAVALABLE  
  MDR_Timer_StopSync(PWM1_START_SEL_MSK | PWM2_START_SEL_MSK);
#else
  MDR_Timer_Stop(PWM1_TIMex);
  MDR_Timer_Stop(PWM2_TIMex);
#endif 
  
  //  Pins to third state
  MDR_TimerCh_DeInitPinGPIO(&PWM1_PIN_CH);
  MDR_TimerCh_DeInitPinGPIO(&PWM1_PIN_nCH);
  MDR_TimerCh_DeInitPinGPIO(&PWM2_PIN_CH);
  MDR_TimerCh_DeInitPinGPIO(&PWM2_PIN_nCH);
  
  //  Finit Timers
  MDR_Timer_DeInit(PWM1_TIMex);
  MDR_Timer_DeInit(PWM2_TIMex);
  
#ifdef LCD_CONFLICT_TIM  
  // Restore LCD
  MDRB_LCD_Init(MDR_CPU_GetFreqHz(false));   
#elif !defined(LCD_IS_7SEG_DISPLAY)
  MDRB_LCD_ClearLine(5);
#endif
}

static void Test_Empty(void)
{
}


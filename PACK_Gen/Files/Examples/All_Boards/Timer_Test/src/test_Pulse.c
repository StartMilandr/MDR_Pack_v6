#include <MDR_Timer.h>
#include <MDRB_LEDs.h>
#include <MDRB_LCD.h>
#include <MDR_Funcs.h>

#include <MDRB_Timer_PinSelect.h>

#include "test_Defs.h"

//  ОПИСАНИЕ:
//    Пример простейшей генерации импульсов на выходах канала таймера.
//    Требуется минимальное количество параметров, остальные по умолчанию.
//    Импульсы смотреть осциллографом на пинах.
//    При нажатии на кнопку DOWN  скважность импульсов меняетс на 10%, для разных каналов в разные стороны.
//
//    ПРОВЕРИТЬ, что выходы каналов таймеров не замкнуты друг на друга (после тестов с захватом)!


//  Test Interface functions
static void  Test_Init(void);
static void  Test_Finit(void);
static void  Test_Empty(void);
static void  Test_Exec(void);

TestInterface TI_Pulse = {
  .funcInit       = Test_Init,
  .funcFinit      = Test_Finit,
  .funcChange     = Test_Exec,
  .funcExec       = Test_Exec,
  .funcMainLoop   = Test_Empty,
  .funcHandlerTim1 = Test_Empty,
  .funcHandlerTim2 = Test_Empty,
  .funcHandlerTim3 = Test_Empty,
  .funcHandlerTim4 = Test_Empty,
};


uint32_t pulseWidthPerc = 50;

static void Test_Init(void)
{  
#ifndef LCD_IS_7SEG_DISPLAY
  MDRB_LCD_Print("Pulse Width", 3);
  
#elif defined (LCD_CONFLICT_TIM)
  MDRB_LCD_Print(TEST_ID__PULSE);  
  
  #ifdef LCD_BLINKY_ENA
    MDR_LCD_BlinkyStart(MDR_LCD_Blink_2Hz, MDR_Off);
    MDR_Delay_ms(LCD_HIDE_DELAY, MDR_CPU_GetFreqHz(false));
    MDR_LCD_DeInit();
  #endif 
  
#else
  MDRB_LCD_Print(TEST_ID__PULSE);
#endif  
  
  //  PWM1
  MDR_TimerPulse_InitPeriod(PWM1_TIMex, TIM_BRG_PWM, TIM_PSG_PWM1, TIM_PERIOD_PWM);
  MDR_TimerPulse_InitPulse(PWM1_TIM_CH, TIM_PERIOD_PWM, pulseWidthPerc);   
  MDR_TimerCh_InitPinGPIO(&PWM1_PIN_CH,  MDR_PIN_FAST);
  MDR_TimerCh_InitPinGPIO(&PWM1_PIN_nCH, MDR_PIN_FAST);
  
  //  PWM2
  MDR_TimerPulse_InitPeriod(PWM2_TIMex, TIM_BRG_PWM, TIM_PSG_PWM1, TIM_PERIOD_PWM);
  MDR_TimerPulse_InitPulse(PWM2_TIM_CH, TIM_PERIOD_PWM, 100 - pulseWidthPerc);
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
#endif
}

static void Test_Exec(void)
{
  pulseWidthPerc += 10;
  if (pulseWidthPerc > 100)
    pulseWidthPerc = 0;
  
  MDR_TimerPulse_ChangeWidth(PWM1_TIM_CH, TIM_PERIOD_PWM, pulseWidthPerc);
  MDR_TimerPulse_ChangeWidth(PWM2_TIM_CH, TIM_PERIOD_PWM, 100 - pulseWidthPerc);
}

static void Test_Empty(void)
{
}


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

#define BRG_VALUE      MDR_BRG_div4
#define PSC_VALUE1     100
#define PSC_VALUE2      50
#define PERIOD_VALUE   800

uint32_t pulseWidthPerc = 50;

#ifdef USE_MDR1986VE91
  #define TIM2_CH_SEL       MDR_TIMER2_CH3
  #define TIM2_PIN_CH       _pinTim2_CH3
  #define TIM2_PIN_nCH      _pinTim2_nCH3

#elif defined (USE_MDR1986VK214)
  #define TIM2_CH_SEL       MDR_TIMER2_CH1
  #define TIM2_PIN_CH       _pinTim2_CH1
  #define TIM2_PIN_nCH      _pinTim2_nCH1

  #define LCD_CONFLICT
#endif

static void Test_Init(void)
{  
#ifndef LCD_IS_7SEG_DISPLAY
  MDRB_LCD_Print("Pulse Width", 3);
  
#elif defined (LCD_CONFLICT)
  //  LCD conflicts with Timers channel
  //  Show Test index and LCD Off
  MDRB_LCD_Print("4");  
  MDR_LCD_BlinkyStart(MDR_LCD_Blink_2Hz, MDR_Off);
  MDR_Delay_ms(LCD_HIDE_DELAY, MDR_CPU_GetFreqHz(false));
  
  MDR_LCD_DeInit();
#else
  MDRB_LCD_Print("4");
#endif  
  
  //  Timer1
  MDR_TimerPulse_InitPeriod(MDR_TIMER1ex, BRG_VALUE, PSC_VALUE1, PERIOD_VALUE);
  MDR_TimerPulse_InitPulse(MDR_TIMER1_CH1, PERIOD_VALUE, pulseWidthPerc);
   
  MDR_TimerCh_InitPinGPIO(&_pinTim1_CH1,  MDR_PIN_FAST);
  MDR_TimerCh_InitPinGPIO(&_pinTim1_nCH1, MDR_PIN_FAST);
  
  //  Timer2
  MDR_TimerPulse_InitPeriod(MDR_TIMER2ex, BRG_VALUE, PSC_VALUE1, PERIOD_VALUE);
  MDR_TimerPulse_InitPulse(TIM2_CH_SEL, PERIOD_VALUE, 100 - pulseWidthPerc);
   
  MDR_TimerCh_InitPinGPIO(&TIM2_PIN_CH,  MDR_PIN_FAST);
  MDR_TimerCh_InitPinGPIO(&TIM2_PIN_nCH, MDR_PIN_FAST);

  // Sync Start
  MDR_Timer_StartSync(TIM1_StartMsk | TIM2_StartMsk);
}  

static void Test_Finit(void)
{
  MDR_TimerCh_DeInitPinGPIO(&_pinTim1_CH1);
  MDR_TimerCh_DeInitPinGPIO(&_pinTim1_nCH1);

  MDR_TimerCh_DeInitPinGPIO(&TIM2_PIN_CH);
  MDR_TimerCh_DeInitPinGPIO(&TIM2_PIN_nCH);  
  
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

static void Test_Exec(void)
{
  pulseWidthPerc += 10;
  if (pulseWidthPerc > 100)
    pulseWidthPerc = 0;
  
  MDR_TimerPulse_ChangeWidth(MDR_TIMER1_CH1, PERIOD_VALUE, pulseWidthPerc);
  MDR_TimerPulse_ChangeWidth(TIM2_CH_SEL, PERIOD_VALUE, 100 - pulseWidthPerc);
}

static void Test_Empty(void)
{
}


#include <MDR_Timer.h>
#include <MDRB_LEDs.h>
#include <MDRB_LCD.h>

#include <MDRB_Timer_PinSelect.h>
#include "test_Defs.h"

//  ОПИСАНИЕ:
//  Пример генерации ШИМ c задержкой между фронтами прямого и инверсного каналов - Dead Time Generator (DTG).
//  Смотреть осциллографом на каналах Timer1:
//    Сигнал с DTG выводится на CH1 и nCH1
//    Сигнал без DTG выводится на CH2 и nCH2 (кроме 1986ВК214, там в таймере только один канал)
//  ПРОВЕРИТЬ, что выходы каналов таймеров не замкнуты друг на друга (после тестов с захватом)!
  

//  Test Interface functions
static void  Test_Init(void);
static void  Test_Finit(void);
static void  Test_Empty(void);


TestInterface TI_PWM_DTG = {
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


//  Channel Select
#ifdef USE_MDR1986VE91
  #define TIM1_CH_SEL       MDR_TIMER1_CH1
  #define TIM1_PIN_CH       _pinTim1_CH1
  #define TIM1_PIN_nCH      _pinTim1_nCH1

#elif defined (USE_MDR1986VK214)
  #define TIM1_CH_SEL       MDR_TIMER1_CH1
  #define TIM1_PIN_CH       _pinTim1_CH1
  #define TIM1_PIN_nCH      _pinTim1_nCH1

  #define LCD_CONFLICT
  #define USE_SINGLE_CHANNEL

#elif defined (USE_MDR1986VK234)
  #define TIM1_CH_SEL       MDR_TIMER1_CH3
  #define TIM1_PIN_CH       _pinTim1_CH3
  #define TIM1_PIN_nCH      _pinTim1_nCH3
  
  #define USE_SINGLE_CHANNEL  
#endif



static void Test_Init(void)
{
  MDR_TimerCh_CfgPWM        cfgPWM =     {.use_nCH             = true,
                                          .CCRs_UpdImmediately = MDR_On,
                                          .cfgOptions          = NULL
                                         };  
  MDR_TimerCh_CfgDTG        cfgDTG =     {.Presc    = MDR_TIM_DTG_x12,
                                          .ClockSel = TIM_DTG_CLK_TimClk,
                                          .Mul = 100 
                                         };
  MDR_TimerCh_CfgOptionsPWM cfgOptions = {.cfgPin_CH      = NULL,
                                          .cfgPin_nCH     = NULL,
                                          .cfgDTG         = NULL,
                                          .ClearRef_ByBRK = MDR_Off,
                                          .ClearRef_ByETR = MDR_Off,
                                         };
  
  //  To LCD
#ifndef LCD_IS_7SEG_DISPLAY
  MDRB_LCD_Print("PWM with DTG", 3);
  
#elif defined (LCD_CONFLICT)
  //  LCD conflicts with Timers channel
  //  Show Test index and LCD Off
  MDRB_LCD_Print("6");  
  MDR_LCD_BlinkyStart(MDR_LCD_Blink_2Hz, MDR_Off);
  MDR_Delay_ms(LCD_HIDE_DELAY, MDR_CPU_GetFreqHz(false));
  
  MDR_LCD_DeInit();
#else
  MDRB_LCD_Print("6");
#endif                                          

  // PWM Settings
  cfgOptions.cfgDTG = &cfgDTG;
  cfgPWM.cfgOptions = &cfgOptions;
                                         
  //  Timer1
  MDR_Timer_InitPeriod(MDR_TIMER1ex, TIM_BRG_PWM, TIM_PSG_PWM1, TIM_PERIOD_PWM, false);
  
  MDR_TimerCh_InitPWM(TIM1_CH_SEL, &cfgPWM,    MDR_TIM_PWM_Ref1_ltCCR, TIM_PERIOD_PWM / 2);
  MDR_TimerCh_InitPinGPIO(&TIM1_PIN_CH,  MDR_PIN_FAST);
  MDR_TimerCh_InitPinGPIO(&TIM1_PIN_nCH, MDR_PIN_FAST);  
  
#ifndef USE_SINGLE_CHANNEL
  MDR_TimerCh_InitPWM(MDR_TIMER1_CH2, NULL, MDR_TIM_PWM_Ref1_ltCCR, TIM_PERIOD_PWM / 2);
  MDR_TimerCh_InitPinGPIO(&_pinTim1_CH2,  MDR_PIN_FAST);
  MDR_TimerCh_InitPinGPIO(&_pinTim1_nCH2, MDR_PIN_FAST);  
#endif
  
  // Sync Start
  MDR_Timer_Start(MDR_TIMER1ex);
}  

static void Test_Finit(void)
{
  MDR_TimerCh_DeInitPinGPIO(&TIM1_PIN_CH);
  MDR_TimerCh_DeInitPinGPIO(&TIM1_PIN_nCH);
  
#ifndef USE_SINGLE_CHANNEL  
  MDR_TimerCh_DeInitPinGPIO(&_pinTim1_CH2);
  MDR_TimerCh_DeInitPinGPIO(&_pinTim1_nCH2); 
#endif
  
  MDR_Timer_Stop(MDR_TIMER1ex);
  MDR_Timer_DeInit(MDR_TIMER1ex);
  
#ifdef LCD_CONFLICT 
  // Restore LCD
  MDRB_LCD_Init(MDR_CPU_GetFreqHz(false));   
#endif
}

static void Test_Empty(void)
{

}


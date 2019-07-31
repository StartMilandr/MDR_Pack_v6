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

extern TestInterface TI_PWM_DTG;

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


static void Test_Init(void)
{
  MDR_TimerCh_CfgPWM        cfgPWM =     {.use_nCH             = true,
                                          .CCRs_UpdImmediately = MDR_On,
                                          .cfgOptions          = NULL
                                         };  
  MDR_TimerCh_CfgDTG        cfgDTG =     {.Presc    = MDR_TIM_DTG_x12,
                                          .ClockSel = TIM_DTG_CLK_TimClk,
                                          .Mul = 200 
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
  
#elif defined (LCD_CONFLICT_TIM)
  MDRB_LCD_Print(TEST_ID__PWM_DTG);  
                                         
  #ifdef LCD_BLINKY_ENA                                         
    MDR_LCD_BlinkyStart(MDR_LCD_Blink_2Hz, MDR_Off);
    MDR_Delay_ms(LCD_HIDE_DELAY, MDR_CPU_GetFreqHz(false));
    MDR_LCD_DeInit();                                         
  #endif  

#else
  MDRB_LCD_Print(TEST_ID__PWM_DTG);
#endif                                          

  // PWM Settings
  cfgOptions.cfgDTG = &cfgDTG;
  cfgPWM.cfgOptions = &cfgOptions;
                                         
  //  PWM1
  MDR_Timer_InitPeriod(PWM1_TIMex, TIM_BRG_PWM, TIM_PSG_PWM1, TIM_PERIOD_PWM, false);  
  MDR_TimerCh_InitPWM (PWM1_TIM_CH, &cfgPWM, MDR_TIM_PWM_Ref1_ltCCR, TIM_PERIOD_PWM / 2);
  MDR_TimerCh_InitPinGPIO(&PWM1_PIN_CH,  MDR_PIN_FAST);
  MDR_TimerCh_InitPinGPIO(&PWM1_PIN_nCH, MDR_PIN_FAST);  
  
#ifdef USE_SECOND_CHANNEL
  MDR_TimerCh_InitPWM(PWM1_TIM_CH_EX, NULL, MDR_TIM_PWM_Ref1_ltCCR, TIM_PERIOD_PWM / 2);
  MDR_TimerCh_InitPinGPIO(&PWM1_PIN_CH_EX,  MDR_PIN_FAST);
  MDR_TimerCh_InitPinGPIO(&PWM1_PIN_nCH_EX, MDR_PIN_FAST);  
#endif
  
  // Simple Start
  MDR_Timer_Start(PWM1_TIMex);
}  

static void Test_Finit(void)
{
  //  Stop
  MDR_Timer_Stop(PWM1_TIMex);
  
  //  Pins to third state
  MDR_TimerCh_DeInitPinGPIO(&PWM1_PIN_CH);
  MDR_TimerCh_DeInitPinGPIO(&PWM1_PIN_nCH);
  
#ifdef USE_SECOND_CHANNEL  
  MDR_TimerCh_DeInitPinGPIO(&PWM1_PIN_CH_EX);
  MDR_TimerCh_DeInitPinGPIO(&PWM1_PIN_nCH_EX); 
#endif
  
  //  Finit Timer
  MDR_Timer_DeInit(PWM1_TIMex);
  
#ifdef LCD_CONFLICT_TIM 
  // Restore LCD
  MDRB_LCD_Init(MDR_CPU_GetFreqHz(false));   
#endif
}

static void Test_Empty(void)
{

}


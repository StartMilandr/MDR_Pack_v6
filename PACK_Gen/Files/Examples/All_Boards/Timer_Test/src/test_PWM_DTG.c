#include <MDR_Timer.h>
#include <MDRB_LEDs.h>
#include <MDRB_LCD.h>

#include <MDRB_Timer_PinSelect.h>
#include "test_Defs.h"

//  ОПИСАНИЕ:
//  Пример генерации ШИМ c задержкой между фронтами прямого и инверсного каналов - Dead Time Generator (DTG).
//  Смотреть осциллографом:
//    Сигнал без DTG выводится на CH1 и nCH1
//    Сигнал с DTG выводится на CH2 и nCH2


//  Test Interface functions
static void  Test_Init(void);
static void  Test_Finit(void);
static void  Test_Change(void);
static void  Test_Exec(void);
static void  Test_MainLoop(void);
static void  Test_HandleTim1IRQ(void);
static void  Test_HandleTim2IRQ(void);
static void  Test_HandleTim3IRQ(void);

TestInterface TI_PWM_DTG = {
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

#define BRG_VALUE      MDR_BRG_div4
#define PSC_VALUE1     100
#define PERIOD_VALUE   90

static void Test_Init(void)
{
  MDR_TimerCh_CfgPWM        cfgPWM =     {.use_nCH             = true,
                                          .CCRs_UpdImmediately = MDR_On,
                                          .cfgOptions          = NULL
                                         };  
  MDR_TimerCh_CfgDTG        cfgDTG =     {.Presc    = MDR_TIM_DTG_x12,
                                          .ClockSel = TIM_DTG_CLK_TimClk,
                                          .Mul = 40 
                                         };
  MDR_TimerCh_CfgOptionsPWM cfgOptions = {.cfgPin_CH      = NULL,
                                          .cfgPin_nCH     = NULL,
                                          .cfgDTG         = NULL,
                                          .ClearRef_ByBRK = MDR_Off,
                                          .ClearRef_ByETR = MDR_Off,
                                         };
  
  //  To LCD
  MDRB_LCD_Print("PWM with DTG", 3);
  MDRB_LCD_ClearLine(5);

  // PWM Settings
  cfgOptions.cfgDTG = &cfgDTG;
  cfgPWM.cfgOptions = &cfgOptions;
                                         
  //  Timer1
  MDR_Timer_InitPeriod(MDR_TIMER1ex, BRG_VALUE, PSC_VALUE1, PERIOD_VALUE, false);
  MDR_TimerCh_InitPWM(MDR_TIMER1_CH1, NULL,    MDR_TIM_PWM_Ref1_ltCCR, PERIOD_VALUE / 2);
  MDR_TimerCh_InitPWM(MDR_TIMER1_CH2, &cfgPWM, MDR_TIM_PWM_Ref1_ltCCR, PERIOD_VALUE / 2);
  
  MDR_TimerCh_InitPinGPIO(&_pinTim1_CH1,  MDR_PIN_FAST);
  MDR_TimerCh_InitPinGPIO(&_pinTim1_nCH1, MDR_PIN_FAST);
  MDR_TimerCh_InitPinGPIO(&_pinTim1_CH2,  MDR_PIN_FAST);
  MDR_TimerCh_InitPinGPIO(&_pinTim1_nCH2, MDR_PIN_FAST);
  
  // Sync Start
  MDR_Timer_Start(MDR_TIMER1ex);
}  

static void Test_Finit(void)
{
  MDR_TimerCh_DeInitPinGPIO(&_pinTim1_CH1);
  MDR_TimerCh_DeInitPinGPIO(&_pinTim1_nCH1);
  MDR_TimerCh_DeInitPinGPIO(&_pinTim1_CH2);
  MDR_TimerCh_DeInitPinGPIO(&_pinTim1_nCH2); 
  
  MDR_Timer_Stop(MDR_TIMER1ex);
  MDR_Timer_DeInit(MDR_TIMER1ex);
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
}

static void Test_HandleTim2IRQ(void)
{

}

static void Test_HandleTim3IRQ(void)
{

}

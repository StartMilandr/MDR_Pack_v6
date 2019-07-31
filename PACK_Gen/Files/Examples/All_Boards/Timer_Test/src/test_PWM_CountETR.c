#include <MDR_Timer.h>
#include <MDRB_LEDs.h>
#include <MDRB_LCD.h>

#include <MDRB_Timer_PinSelect.h>
#include "test_Defs.h"


//  ОПИСАНИЕ:
//    Пример подсчета внешних импульсов на входе ETR.
//    Таймер1 генерирует импульсы, которые подаются на вход ETR Таймера2.
//    В прерываниях таймеров по периоду: 
//      - Таймер1 переключается светодиод1, 
//      - Таймер2 переключается светодиод2.
//  В коде можно поменять настройки фильтров, частоты сэмплирования и прочего 
//  для изучения их влияния на периоды мигания светодиодов.
//
//  В 1986ВК214 без подключения налюдается беспорядочное мигание светодиода (из-за наводок или утечек).
//  При подключении TIM1_CH1 к TIM2_ETR мигания ожидаемо упорядочиваются.
//  В 1986ВК234 вывод TIM2_ETR подключен в светодиоду LED3, поэтому на нем удобно наблюдать период сигнала ETR. LED2 мигает с периодом LED2_PERIOD.

//  Test Interface functions
static void  Test_Init(void);
static void  Test_Finit(void);
static void  Test_Empty(void);
static void  Test_HandleIRQ_PWM(void);
static void  Test_HandleIRQ_ETR(void);

extern TestInterface TI_PWM_CountETR;

TestInterface TI_PWM_CountETR = {
  .funcInit       = Test_Init,
  .funcFinit      = Test_Finit,
  .funcChange     = Test_Empty,
  .funcExec       = Test_Empty,
  .funcMainLoop   = Test_Empty,  
  
#ifdef PWM1_IS_TIM1 
  .funcHandlerTim1 = Test_HandleIRQ_PWM,
#else
  .funcHandlerTim1 = Test_HandleIRQ_ETR,
#endif

#ifdef PWM1_IS_TIM2 
  .funcHandlerTim2 = Test_HandleIRQ_PWM,
#else
  .funcHandlerTim2 = Test_HandleIRQ_ETR,
#endif
  
  #ifdef PWM1_IS_TIM3 
  .funcHandlerTim3 = Test_HandleIRQ_PWM,
#else
  .funcHandlerTim3 = Test_HandleIRQ_ETR,
#endif

#ifdef PWM1_IS_TIM4 
  .funcHandlerTim4 = Test_HandleIRQ_PWM,
#else
  .funcHandlerTim4 = Test_HandleIRQ_ETR,
#endif  
};
  
//  Для счета ETR выбран тот же таймер, который используется в тесте захвата. Чтобы не переподключать провода.
#define ETR_TIMex           CAP_TIMex
#define ETR_TIM             CAP_TIM
#define ETR_TIM_PIN         CAP_PIN_ETR
#define ETR_START_SEL_MSK   CAP_START_SEL_MSK

#define LED2_PERIOD   4

static const MDR_Timer_cfgBRKETR  cfgBRKETR = {
  .Bits.BRK_INV = MDR_Off, 
  .Bits.ETR_INV = MDR_Off, 
  .Bits.ETR_PSC = MDR_TIM_BRKETR_ETR_div1,
  .Bits.ETR_Filter = MDR_TIM_FLTR_TIM_CLK
};

static const MDR_Timer_CfgCountETR  cfgETR = {  
  .cfgPeriod.clockBRG   = TIM_BRG_LED,
  .cfgPeriod.period     = LED2_PERIOD,
  .cfgPeriod.startValue = 0,
  .cfgPeriod.periodUpdateImmediately = MDR_Off,
  
  .cfgIRQ.SelectIRQ   = TIM_FL_CNT_ARR,
  .cfgIRQ.priorityIRQ = 0,
  .cfgIRQ.activateNVIC_IRQ = true,
   
  .selFrontETR = TIM_FrontRise,  
  .countDir    = TIM_Event_CountUp,  
  .clockDTS    = TIM_FDTS_TimClk_div1
};

static void Test_Init(void)
{     
  //  To LCD
#ifndef LCD_IS_7SEG_DISPLAY
  MDRB_LCD_Print("Count ETR", 3);
  
#elif defined (LCD_CONFLICT_TIM)
  MDRB_LCD_Print(TEST_ID__COUNT_ETR);  
  
  #ifdef LCD_BLINKY_ENA  
    MDR_LCD_BlinkyStart(MDR_LCD_Blink_2Hz, MDR_Off);
    MDR_Delay_ms(LCD_HIDE_DELAY, MDR_CPU_GetFreqHz(false));
    MDR_LCD_DeInit();
  #endif  

#else
  MDRB_LCD_Print(TEST_ID__COUNT_ETR);
#endif
  
  MDRB_LED_Init(LED_SEL_CAP);
  MDRB_LED_Set (LED_SEL_CAP, 0);
  
  //  PWM1 - Outputs pulses for ETR, show period with LED1
  MDR_Timer_InitPeriod(PWM1_TIMex, TIM_BRG_LED, TIM_PSG_LED, TIM_PERIOD_LED, true);
  MDR_TimerPulse_InitPulse(PWM1_TIM_CH, TIM_PERIOD_LED, 50);
  MDR_TimerCh_InitPinGPIO(&PWM1_PIN_CH,  MDR_PIN_FAST);
     
  //  Capture timer - Count ETR and, show period with LED2
  MDR_Timer_InitCountETR(ETR_TIMex, &cfgETR);
  MDR_Timer_InitBRKETR(ETR_TIMex, cfgBRKETR);
  MDR_TimerCh_InitPinGPIO(&ETR_TIM_PIN, MDR_PIN_FAST);

  // Start
#ifndef SYNC_START_UNAVALABLE  
  MDR_Timer_StartSync(PWM1_START_SEL_MSK | ETR_START_SEL_MSK);
#else
  MDR_Timer_Start(ETR_TIMex);
  MDR_Timer_Start(PWM1_TIMex);
#endif
}  

static void Test_Finit(void)
{
  //  Stop
#ifndef SYNC_START_UNAVALABLE  
  MDR_Timer_StopSync(PWM1_START_SEL_MSK | ETR_START_SEL_MSK);
#else
  MDR_Timer_Stop(ETR_TIMex);
  MDR_Timer_Stop(PWM1_TIMex);
#endif   
  
  //  Pins to third state
  MDR_TimerCh_DeInitPinGPIO(&PWM1_PIN_CH);
  MDR_TimerCh_DeInitPinGPIO(&ETR_TIM_PIN);

  //  Finit Timers
  MDR_Timer_DeInit(PWM1_TIMex);
  MDR_Timer_DeInit(ETR_TIMex);
  
  LED_Uninitialize(); 

#ifdef LCD_CONFLICT_LED
  MDRB_LCD_CapturePins();
#endif  
}

static void Test_HandleIRQ_PWM(void)
{
  MDR_Timer_ClearEvent(PWM1_TIM, TIM_FL_CNT_ARR);
#ifdef MDRB_LED_2
  MDRB_LED_Toggle(MDRB_LED_2);
#endif
}

static void Test_HandleIRQ_ETR(void)
{
  MDR_Timer_ClearEvent(ETR_TIM, TIM_FL_CNT_ARR);
    
  MDRB_LED_Toggle(MDRB_LED_1);  
}

static void Test_Empty(void)
{
}

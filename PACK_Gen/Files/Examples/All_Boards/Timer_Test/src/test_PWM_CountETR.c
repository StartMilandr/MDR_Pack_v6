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


//  Test Interface functions
static void  Test_Init(void);
static void  Test_Finit(void);
static void  Test_Empty(void);
static void  Test_HandleTim1IRQ(void);
static void  Test_HandleTim2IRQ(void);


TestInterface TI_PWM_CountETR = {
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
  .countDir    = TIM_CountUp,
  .clockDTS    = TIM_FDTS_TimClk_div1
};

static void Test_Init(void)
{     
  //  To LCD
#ifndef LCD_IS_7SEG_DISPLAY
  MDRB_LCD_Print("Count ETR", 3);
  
#elif defined (LCD_CONFLICT)
  //  LCD conflicts with Timers channel
  //  Show Test index and LCD Off
  MDRB_LCD_Print("10");  
  MDR_LCD_BlinkyStart(MDR_LCD_Blink_2Hz, MDR_Off);
  MDR_Delay_ms(LCD_HIDE_DELAY, MDR_CPU_GetFreqHz(false));
  
  MDR_LCD_DeInit();
#else
  MDRB_LCD_Print("10");
#endif
  
  MDRB_LED_Init(MDRB_LED_1 | MDRB_LED_2);
  MDRB_LED_Set (MDRB_LED_1 | MDRB_LED_2, 0);
  
  //  Timer1_CH1 - Pulse output for ETR, show period with LED1
  MDR_Timer_InitPeriod(MDR_TIMER1ex, TIM_BRG_LED, TIM_PSG_LED, TIM_PERIOD_LED, true);
  MDR_TimerPulse_InitPulse(MDR_TIMER1_CH1, TIM_PERIOD_LED, 50);
  MDR_TimerCh_InitPinGPIO(&_pinTim1_CH1,  MDR_PIN_FAST);
     
  //  Timer2 Count ETR and, show period with LED2
  MDR_Timer_InitCountETR(MDR_TIMER2ex, &cfgETR);
  MDR_Timer_InitBRKETR(MDR_TIMER2ex, cfgBRKETR);
  MDR_TimerCh_InitPinGPIO(&_pinTim2_ETR, MDR_PIN_FAST);
    
  // Sync Start
  MDR_Timer_StartSync(TIM1_StartMsk | TIM2_StartMsk);
}  

static void Test_Finit(void)
{
  MDR_TimerCh_DeInitPinGPIO(&_pinTim1_CH1);
  MDR_TimerCh_DeInitPinGPIO(&_pinTim2_BRK);

  MDR_Timer_StopSync(TIM1_StartMsk | TIM2_StartMsk);
  MDR_Timer_DeInit(MDR_TIMER1ex);
  MDR_Timer_DeInit(MDR_TIMER2ex);
  
  LED_Uninitialize();  
}

static void Test_HandleTim1IRQ(void)
{
  MDR_Timer_ClearEvent(MDR_TIMER1, TIM_FL_CNT_ARR);
  
  MDRB_LED_Switch(MDRB_LED_1);  
}

static void Test_HandleTim2IRQ(void)
{
  MDR_Timer_ClearEvent(MDR_TIMER2, TIM_FL_CNT_ARR);
  
  MDRB_LED_Switch(MDRB_LED_2);
}

static void Test_Empty(void)
{
}

#include <MDR_Timer.h>
#include <MDRB_LEDs.h>

#include <MDRB_Timer_PinSelect.h>
#include "test_Defs.h"
#include "MDRB_ShowMess.h"


//  ОПИСАНИЕ:
//    Пример подсчета передних фронтов на входе канала таймера.
//    Таймер1 генерирует импульсы c выхода CH1, которые подаются на вход CH1 Таймера2.
//    В прерываниях таймеров по периоду: 
//      - Таймер1 переключается светодиод1, 
//      - Таймер2 переключается светодиод2.
//  В коде можно поменять настройки фильтров, частоты сэмплирования и прочего 
//  для изучения их влияния на периоды мигания светодиодов.
//
//  В 1986ВК214 без подключения налюдается беспорядочное мигание светодиода (из-за наводок или утечек).
//  При подключении TIM1_CH1 к TIM2_CH1 мигания ожидаемо упорядочиваются.


//  Test Interface functions
static void  Test_Init(void);
static void  Test_Finit(void);
static void  Test_Empty(void);
static void  Test_HandleIRQ_PWM(void);
static void  Test_HandleIRQ_CAP(void);

extern TestInterface TI_PWM_CountCAP;

TestInterface TI_PWM_CountCAP = {
  .funcInit       = Test_Init,
  .funcFinit      = Test_Finit,
  .funcChange     = Test_Empty,
  .funcExec       = Test_Empty,
  .funcMainLoop   = Test_Empty,
  
  
#ifdef PWM1_IS_TIM1 
  .funcHandlerTim1 = Test_HandleIRQ_PWM,
#else
  .funcHandlerTim1 = Test_HandleIRQ_CAP,
#endif

#ifdef PWM1_IS_TIM2 
  .funcHandlerTim2 = Test_HandleIRQ_PWM,
#else
  .funcHandlerTim2 = Test_HandleIRQ_CAP,
#endif
  
  #ifdef PWM1_IS_TIM3 
  .funcHandlerTim3 = Test_HandleIRQ_PWM,
#else
  .funcHandlerTim3 = Test_HandleIRQ_CAP,
#endif

#ifdef PWM1_IS_TIM4 
  .funcHandlerTim4 = Test_HandleIRQ_PWM,
#else
  .funcHandlerTim4 = Test_HandleIRQ_CAP,
#endif
};  
  
#define LED2_PERIOD   4

static const MDR_Timer_CfgCountCH cfgCntCH = {
  .cfgPeriod.clockBRG = TIM_BRG_LED,
  .cfgPeriod.period = LED2_PERIOD,
  .cfgPeriod.startValue = 0,
  .cfgPeriod.periodUpdateImmediately = MDR_Off,
  
  .cfgIRQ.SelectIRQ   = TIM_FL_CNT_ARR,
  .cfgIRQ.priorityIRQ = 0,
  .cfgIRQ.activateNVIC_IRQ = true,
   
  .selEventCH  = CAP_EVENT_CH,  
  .countDir    = TIM_Event_CountUp,  
  .clockDTS    = TIM_FDTS_TimClk_div1
};

static const MDR_TimerCh_CfgCAP cfgCAP = {
  .Filter   = MDR_TIM_FLTR_TIM_CLK, 
  .EventPSC = MDR_Div8P_div1,
  .EventCAP = MDR_TIM_CAP_RiseOnPin,
  .enableCAP1 = false,
  .EventCAP1  = MDR_TIM_CAP1_FallOnPin
};

static void Test_Init(void)
{  
  //  LCD / UART_Dbg show TestName
  MDR_ShowMess(MESS__COUNT_CAP);  
    
  MDRB_LED_Init(LED_SEL_CAP);
  MDRB_LED_Set (LED_SEL_CAP, 0);  
      
  //  PWM1 - Output pulses for ETR, show period with LED1
  MDR_Timer_InitPeriod(PWM1_TIMex, TIM_BRG_LED, TIM_PSG_LED, TIM_PERIOD_LED, true);
  MDR_TimerPulse_InitPulse(PWM1_TIM_CH, TIM_PERIOD_LED, 50);
  MDR_TimerCh_InitPinGPIO(&PWM1_PIN_CH,  MDR_PIN_FAST);
     
  //  CAP - Counts CAP Events and show period with LED2
  MDR_Timer_InitCountChannelEvent(CAP_TIMex, &cfgCntCH);
  MDR_TimerCh_InitCAP(CAP_TIM_CH, &cfgCAP);
  MDR_TimerCh_InitPinGPIO(&CAP_PIN_CH, MDR_PIN_FAST);
      
  // Start
#if defined(MDR_TIM_HAS_SYNC_START) && !defined(SYNC_START_UNAVALABLE)    
  MDR_Timer_StartSync(PWM1_START_SEL_MSK | CAP_START_SEL_MSK);
#else
  MDR_Timer_Start(CAP_TIMex);
  MDR_Timer_Start(PWM1_TIMex);
#endif  
}  

static void Test_Finit(void)
{
  //  Stop
#if defined(MDR_TIM_HAS_SYNC_START) && !defined(SYNC_START_UNAVALABLE)    
  MDR_Timer_StopSync(PWM1_START_SEL_MSK | CAP_START_SEL_MSK);
#else
  MDR_Timer_Stop(PWM1_TIMex);
  MDR_Timer_Stop(CAP_TIMex);  
#endif    
  
  //  Pins to third state
  MDR_TimerCh_DeInitPinGPIO(&PWM1_PIN_CH);
  MDR_TimerCh_DeInitPinGPIO(&CAP_PIN_CH);

  //  Finit Timers
  MDR_Timer_DeInit(PWM1_TIMex);
  MDR_Timer_DeInit(CAP_TIMex);

  LED_Uninitialize();  
  
  //  Переинициализация экрана после использования пинов LCD под выводы таймера / LEDs
  if (!MDR_ShowRestore_IfConflTim())
    MDR_ShowRestore_IfConflLED();
}


static void Test_HandleIRQ_PWM(void)
{
  MDR_Timer_ClearEvent(PWM1_TIM, TIM_FL_CNT_ARR);
  
#ifdef MDRB_LED_2
  MDRB_LED_Toggle(MDRB_LED_2);
#endif
}

static void Test_HandleIRQ_CAP(void)
{
  MDR_Timer_ClearEvent(CAP_TIM, TIM_FL_CNT_ARR);
  
  MDRB_LED_Toggle(MDRB_LED_1);  
}

static void  Test_Empty(void)
{
}


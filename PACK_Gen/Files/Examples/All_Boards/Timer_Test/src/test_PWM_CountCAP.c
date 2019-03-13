#include <MDR_Timer.h>
#include <MDRB_LEDs.h>
#include <MDRB_LCD.h>

#include <MDRB_Timer_PinSelect.h>
#include "test_Defs.h"


//  ОПИСАНИЕ:
//    Пример подсчета внешних импульсов на входе ETR.
//    Таймер1 генерирует импульсы, которые подаются на вход ETR Таймера2.
//    По прерываниям Таймера1 переключается светодиод1, По прерываниям Таймера2, переключается светодиод2.
//    Изменения настройки фильтров, частоты сэмплирования и прочего отображаются на периоде мигания светодиодов.


//  Test Interface functions
static void  Test_Init(void);
static void  Test_Finit(void);
static void  Test_Change(void);
static void  Test_Exec(void);
static void  Test_MainLoop(void);
static void  Test_HandleTim1IRQ(void);
static void  Test_HandleTimIRQ_CAP(void);


TestInterface TI_PWM_CountCAP = {
  .funcInit       = Test_Init,
  .funcFinit      = Test_Finit,
  .funcChange     = Test_Change,
  .funcExec       = Test_Exec,
  .funcMainLoop   = Test_MainLoop,
  .funcHandlerTim1 = Test_HandleTim1IRQ,
  .funcHandlerTim2 = Test_HandleTimIRQ_CAP,
  .funcHandlerTim3 = Test_HandleTimIRQ_CAP,
  .funcHandlerTim4 = Test_HandleTimIRQ_CAP,
};

#define TIM_BRG       MDR_BRG_div16
#define TIM_PSC       1000
#define TIM_PERIOD    3000
#define LED2_PERIOD   4

#define CAP_TIMERex       MDR_TIMER3ex
#define CAP_TIMER         MDR_TIMER3
#define CAP_TIMER_CH      MDR_TIMER3_CH2
#define CAP_PIN_CH        _pinTim3_CH2
#define CAP_TIMER_START   TIM3_StartMsk
#define CAP_EVENT_CH      TIM_Event_CH2


static const MDR_Timer_CfgCountCH cfgCntCH = {
  .cfgPeriod.clockBRG = TIM_BRG,
  .cfgPeriod.period = LED2_PERIOD,
  .cfgPeriod.startValue = 0,
  .cfgPeriod.periodUpdateImmediately = MDR_Off,
  
  .cfgIRQ.SelectIRQ   = TIM_FL_CNT_ARR,
  .cfgIRQ.priorityIRQ = 0,
  .cfgIRQ.activateNVIC_IRQ = true,
   
  .selEventCH  = CAP_EVENT_CH,  
  .countDir    = TIM_CountUp,
  .clockDTS    = TIM_FDTS_TimClk_div1
};

static const MDR_TimerCH_CfgCAP cfgCAP = {
  .Filter   = MDR_TIM_FLTR_TIM_CLK, 
  .EventPSC = MDR_PSC_div1,
  .EventCAP = MDR_TIM_CAP_RiseOnPin,
  .enableCAP1 = false,
  .EventCAP1  = MDR_TIM_CAP1_FallOnPin
};

static void Test_Init(void)
{  
  MDRB_LCD_Print("Count CAP", 3);
  MDRB_LCD_ClearLine(5);
    
  MDRB_LED_Init(MDRB_LED_1 | MDRB_LED_2);
  MDRB_LED_Set (MDRB_LED_1 | MDRB_LED_2, 0);  
  
  //  Timer1_CH1 - Pulse output for ETR, show period with LED1
  MDR_Timer_InitPeriod(MDR_TIMER1ex, TIM_BRG, TIM_PSC, TIM_PERIOD, true);
  MDR_TimerPulse_InitPulse(MDR_TIMER1_CH1, TIM_PERIOD, 50);
  MDR_TimerCh_InitPinGPIO(&_pinTim1_CH1,  MDR_PIN_FAST);
     
  //  Timer2 Count CAP Events and show period with LED2
  MDR_Timer_InitCountChannelEvent(CAP_TIMERex, &cfgCntCH);
  MDR_TimerCh_InitCAP(CAP_TIMER_CH, &cfgCAP);
  MDR_TimerCh_InitPinGPIO(&CAP_PIN_CH, MDR_PIN_FAST);
    
  // Sync Start
  MDR_Timer_StartSync(TIM1_StartMsk | CAP_TIMER_START);
}  

static void Test_Finit(void)
{
  MDR_TimerCh_DeInitPinGPIO(&_pinTim1_CH1);
  MDR_TimerCh_DeInitPinGPIO(&CAP_PIN_CH);

  MDR_Timer_StopSync(TIM1_StartMsk | CAP_TIMER_START);
  MDR_Timer_DeInit(MDR_TIMER1ex);
  MDR_Timer_DeInit(CAP_TIMERex);
  
  LED_Uninitialize();  
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
  MDR_Timer_ClearEvent(MDR_TIMER1, TIM_FL_CNT_ARR);
  
  MDRB_LED_Switch(MDRB_LED_1);  
}

static void Test_HandleTimIRQ_CAP(void)
{
  MDR_Timer_ClearEvent(CAP_TIMER, TIM_FL_CNT_ARR);
  
  MDRB_LED_Switch(MDRB_LED_2);
}


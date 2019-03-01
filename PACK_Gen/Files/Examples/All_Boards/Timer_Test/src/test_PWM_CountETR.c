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
static void  Test_HandleTim2IRQ(void);
static void  Test_HandleTim3IRQ(void);

TestInterface TI_PWM_CountETR = {
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

#define TIM_BRG       MDR_BRG_div16
#define TIM_PSC       1000
#define TIM_PERIOD    3000
#define LED2_PERIOD   4

static const MDR_Timer_cfgBRKETR  cfgBRKETR = {
  .Bits.BRK_INV = MDR_Off, 
  .Bits.ETR_INV = MDR_Off, 
  .Bits.ETR_PSC = MDR_TIM_BRKETR_ETR_div1,
  .Bits.ETR_Filter = MDR_TIM_FLTR_TIM_CLK
};

static const MDR_Timer_CfgCountETR  cfgETR = {  
  .cfgPeriod.clockBRG = TIM_BRG,
  .cfgPeriod.period = LED2_PERIOD,
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
  MDRB_LCD_Print("Count ETR", 3);
  MDRB_LCD_ClearLine(5);
    
  MDRB_LED_Init(MDRB_LED_1 | MDRB_LED_2);
  MDRB_LED_Set (MDRB_LED_1 | MDRB_LED_2, 0);  
  
  //  Timer1_CH1 - Pulse output for ETR, show period with LED1
  MDR_Timer_InitPeriod(MDR_TIMER1ex, TIM_BRG, TIM_PSC, TIM_PERIOD, true);
  MDR_TimerPulse_InitPulse(MDR_TIMER1_CH1, TIM_PERIOD, 50);
  MDR_TimerCH_InitPinGPIO(&_pinTim1_CH1,  MDR_PIN_FAST);
     
  //  Timer2 Count ETR and, show period with LED2
  MDR_Timer_InitCountETR(MDR_TIMER2ex, &cfgETR);
  MDR_Timer_InitBRKETR(MDR_TIMER2ex, cfgBRKETR);
  MDR_TimerCH_InitPinGPIO(&_pinTim2_ETR, MDR_PIN_FAST);
    
  // Sync Start
  MDR_Timer_StartSync(TIM1_StartMsk | TIM2_StartMsk);
}  

static void Test_Finit(void)
{
  MDR_TimerCH_DeInitPinGPIO(&_pinTim1_CH1);
  MDR_TimerCH_DeInitPinGPIO(&_pinTim2_BRK);

  MDR_Timer_StopSync(TIM1_StartMsk | TIM2_StartMsk);
  MDR_Timer_DeInit(MDR_TIMER1ex);
  MDR_Timer_DeInit(MDR_TIMER2ex);
  
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

static void Test_HandleTim2IRQ(void)
{
  MDR_Timer_ClearEvent(MDR_TIMER2, TIM_FL_CNT_ARR);
  
  MDRB_LED_Switch(MDRB_LED_2);
}

static void Test_HandleTim3IRQ(void)
{

}

#include <MDR_Timer.h>
#include <MDRB_LEDs.h>
#include <MDRB_LCD.h>

#include <MDRB_Timer_PinSelect.h>

#include "test_Defs.h"

//  ОПИСАНИЕ:
//    Пример простейшей генерации импульсов на выходах канала таймера.
//    Требуется минимальное количество параметров, остальные по умолчанию.

//  Test Interface functions
static void  Test_Init(void);
static void  Test_Finit(void);
static void  Test_Change(void);
static void  Test_Exec(void);
static void  Test_MainLoop(void);
static void  Test_HandleTim1IRQ(void);
static void  Test_HandleTim2IRQ(void);
static void  Test_HandleTim3IRQ(void);

TestInterface TI_Pulse = {
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
#define PSC_VALUE2      50
#define PERIOD_VALUE   800

uint32_t pulseWidthPerc = 50;

static void Test_Init(void)
{
  MDRB_LCD_Print("Pulse Width", 3);
  MDRB_LCD_ClearLine(5);
  
  //  Timer1
  MDR_TimerPulse_InitPeriod(MDR_TIMER1ex, BRG_VALUE, PSC_VALUE1, PERIOD_VALUE);
  MDR_TimerPulse_InitPulse(MDR_TIMER1_CH1, PERIOD_VALUE, pulseWidthPerc);
   
  MDR_TimerCH_InitPinGPIO(&_pinTim1_CH1,  MDR_PIN_FAST);
  MDR_TimerCH_InitPinGPIO(&_pinTim1_nCH1, MDR_PIN_FAST);
  
  //  Timer2
  MDR_TimerPulse_InitPeriod(MDR_TIMER2ex, BRG_VALUE, PSC_VALUE1, PERIOD_VALUE);
  MDR_TimerPulse_InitPulse(MDR_TIMER2_CH3, PERIOD_VALUE, 100 - pulseWidthPerc);
   
  MDR_TimerCH_InitPinGPIO(&_pinTim2_CH3,  MDR_PIN_FAST);
  MDR_TimerCH_InitPinGPIO(&_pinTim2_nCH3, MDR_PIN_FAST);

  // Sync Start
  MDR_Timer_StartSync(TIM1_StartMsk | TIM2_StartMsk);
}  

static void Test_Finit(void)
{
  MDR_TimerCH_DeInitPinGPIO(&_pinTim1_CH1);
  MDR_TimerCH_DeInitPinGPIO(&_pinTim1_nCH1);

  MDR_TimerCH_DeInitPinGPIO(&_pinTim2_CH3);
  MDR_TimerCH_DeInitPinGPIO(&_pinTim2_nCH3);  
  
  MDR_Timer_StopSync(TIM1_StartMsk | TIM2_StartMsk);
  MDR_Timer_DeInit(MDR_TIMER1ex);
  MDR_Timer_DeInit(MDR_TIMER2ex);
}

static void Test_Change(void)
{

}

static void Test_Exec(void)
{
  pulseWidthPerc += 10;
  if (pulseWidthPerc > 100)
    pulseWidthPerc = 0;
  
  MDR_TimerPulse_ChangeWidth(MDR_TIMER1_CH1, PERIOD_VALUE, pulseWidthPerc);
  MDR_TimerPulse_ChangeWidth(MDR_TIMER2_CH3, PERIOD_VALUE, 100 - pulseWidthPerc);
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

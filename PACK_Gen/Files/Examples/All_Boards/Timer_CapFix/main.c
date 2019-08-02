#include <MDR_RST_Clock.h>
#include <MDR_PER_Clock.h>
#include <MDRB_Buttons.h>
#include <MDRB_LEDs.h>
#include <MDR_Timer.h>
#include <MDRB_UART_Debug.h>
#include <MDRB_Timer_PinSelect.h>

#include <stdio.h>
#include <stdlib.h>

#include "SelectConfig.h"

#define BTN_DEBOUNCE_MS 10

#define PWM_BRG           MDR_Div128P_div4
#define PWM_PSG           10
#define PWM_PERIOD        900

#define CAP_BRG           MDR_Div128P_div1
#define CAP_PSG           0


void InitTest(void);
void ExecTest_CAP(void);
void ExecTest_BRG(bool useCapFix);

void Timer_Handler_IRQ(void);
void TIMER1_IRQHandler(void);
void TIMER2_IRQHandler(void);
void TIMER3_IRQHandler(void);

int main(void)
{
  uint32_t freqCPU_Hz;
 
  //  Максимальная скорость тактирования
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDRB_CLK_PLL_HSE_RES_MAX;
  MDR_CPU_SetClock_PLL_HSE(&cfgPLL_HSE, true);  
  
  //  Инициализация LCD дисплея и кнопок
  freqCPU_Hz = MDR_CPU_GetFreqHz(true);
  MDRB_Buttons_Init(BTN_DEBOUNCE_MS, freqCPU_Hz);
  MDR_UART_DBG_Init();
  
  //  Для 1986VE4,VE214,VE234 частота TIM_Clock формируется мультиплексорами
  //  В VE214 отдельный выбор частоты с делителем для каждого из блоков UART, SSP, Timer
  //  В остальных МК TIM_Clock формируется только из HCLK (равной CPU_Clock) - выбор источника не требуется
#ifdef MDR_PER_CLOCK_SELF_TIM_UART_SSP  
  MDR_SetClock_Timer1(MDR_PER_PLLCPUo);
  MDR_SetClock_Timer2(MDR_PER_PLLCPUo);
#elif defined (MDR_TIM_CLOCK_FROM_PER_CLOCK)
  MDR_SetClock_UartTimSSP(MDR_PER_PLLCPUo);
#endif  
  
  MDRB_LED_Init(MDRB_LED_1);
  MDRB_LED_Set (MDRB_LED_1, false);

  InitTest();

  while (1)
  {
    if (MDRB_BntClicked_Up(true))
    {
      MDRB_LED_Set (MDRB_LED_1, true);
      ExecTest_BRG(false);
      MDRB_LED_Set (MDRB_LED_1, false);
    }
    
    if (MDRB_BntClicked_Right(true))
    {
      MDRB_LED_Set (MDRB_LED_1, true);
      ExecTest_BRG(true);
      MDRB_LED_Set (MDRB_LED_1, false);
    }
    
  }
}

void InitTest(void)
{
  MDR_TimerCh_CfgCAP cfgCAP = {
    .Filter   = MDR_TIM_FLTR_TIM_CLK, 
    .EventPSC = MDR_Div8P_div1,
    .EventCAP = MDR_TIM_CAP_RiseOnPin,
    .enableCAP1 = false,
    .EventCAP1  = MDR_TIM_CAP1_FallOnPin
  };  
  
  
  //  PWM - Output pulses for Capture
  MDR_Timer_InitPeriod(PWM_TIMex, PWM_BRG, PWM_PSG, PWM_PERIOD, false);
  MDR_TimerPulse_InitPulse(PWM_TIM_CH, PWM_PERIOD, 50);  
  MDR_TimerCh_InitPinGPIO(&PWM_PIN_CH,  MDR_PIN_FAST);
     
  //  Capture PWM from PIN
  MDR_Timer_InitPeriodDirIRQ(CAP_TIMex, CAP_BRG, CAP_PSG, TIM_MAX_VALUE, CAP_EVENT_CH | CAP_EVENT_CH_NEXT, TIM_CountUp);
  MDR_TimerCh_InitCAP(CAP_TIM_CH, &cfgCAP);  
  MDR_TimerCh_InitPinGPIO(&CAP_PIN_CH, MDR_PIN_FAST); 
  
  //  Capture Rise event from CAP_TIM_CH
  cfgCAP.EventCAP = MDR_TIM_CAP_RiseOnNextCh;
  MDR_TimerCh_InitCAP(CAP_TIM_CH_NEXT, &cfgCAP);  
}

//  ==================    Test  ===================

#define CAP_VALUE_GAP   3

#define TEST_BUFF_MSK    0x3F
#define TEST_BUFF_LEN    64
#define TEST_DATA_COUNT  20
static uint32_t dataCAP1[TEST_BUFF_LEN];
static uint32_t dataCnt1 = 0;
static uint32_t dataCAP2[TEST_BUFF_LEN];
static uint32_t dataCnt2 = 0;

static const uint32_t _BRG_Div[] = {1, 2, 4, 8, 16, 32, 64, 128};

void ExecTest_BRG(bool useCapFix)
{
  MDR_Div128P valueBRG;
  
  printf("\n");
  printf("=====   CAP Fix Test =====\n");
  
  if (useCapFix)
  {
    printf("CAP_FIX Enabled\n");
    CAP_TIM_CH->CHx_CNTRL2 |= MDR_TIM_CHx_CNTRL2_CAP_Fix_Msk;
  }
  else
    CAP_TIM_CH->CHx_CNTRL2 &= ~MDR_TIM_CHx_CNTRL2_CAP_Fix_Msk;
  
  for (valueBRG = MDR_Div128P_div1; valueBRG <= MDR_Div128P_div128; ++valueBRG)
  {    
    MDR_PerClock_SetBRG(&CAP_TIMex->CfgClock, valueBRG);
    printf("\n");
    printf("BRG = div%d\n", _BRG_Div[valueBRG]);
    
    ExecTest_CAP();
  }
}

void ExecTest_CAP(void)
{
  uint32_t i, d;
  uint32_t errCount = 0;
  
  //  SyncStart
  MDR_Timer_StartSync(PWM_START_SEL_MSK | CAP_START_SEL_MSK);  
  //  Wait Data Gathering
  while ((dataCnt1 < TEST_DATA_COUNT) || ((dataCnt2 < TEST_DATA_COUNT)));
  //  Stop
  MDR_Timer_StopSync(PWM_START_SEL_MSK | CAP_START_SEL_MSK);
    
  //  Send Data to UART
  //printf("\n");
  printf("CAP1  CAP2\n");
  for (i = 0; i < TEST_DATA_COUNT; ++i)
  {
    if (dataCAP1[i] > dataCAP2[i])
      d = dataCAP1[i] - dataCAP2[i];
    else
      d = dataCAP2[i] - dataCAP1[i];
    if (d < CAP_VALUE_GAP)
      printf("%8x  %8x\n", dataCAP1[i], dataCAP2[i]);
    else
    {  
      ++errCount;
      printf("%8x  %8x  - ERROR\n", dataCAP1[i], dataCAP2[i]);
    }
  }
  printf("Erors: %d\n", errCount);
  
  //  Prepare for New Test
  dataCnt1 = dataCnt2 = 0;
  PWM_TIM->CNT = 0;
  CAP_TIM->CNT = 0;
  PWM_TIM->STATUS = 0;
  CAP_TIM->STATUS = 0;
}

void Timer_Handler_IRQ(void)
{
  uint32_t clrEvent1 = 0;
  uint32_t clrEvent2 = 0;
  uint32_t status = MDR_Timer_GetStatus(CAP_TIM);
  
  if ((status & CAP_EVENT_CH) != 0)
  {
    dataCAP1[dataCnt1] = MDR_TimerCh_GetCCR(CAP_TIM_CH);
    dataCnt1 = (dataCnt1 + 1) & TEST_BUFF_MSK;
    
    clrEvent1 = CAP_EVENT_CH;
  }
  if ((status & CAP_EVENT_CH_NEXT) != 0)
  {
    dataCAP2[dataCnt2] = MDR_TimerCh_GetCCR(CAP_TIM_CH_NEXT);
    dataCnt2 = (dataCnt2 + 1) & TEST_BUFF_MSK;
    
    clrEvent2 = CAP_EVENT_CH_NEXT;
  }
    
  CAP_TIM->STATUS = ~(uint32_t)(clrEvent1 | clrEvent2);
}

void TIMER1_IRQHandler(void)
{
  Timer_Handler_IRQ();
}

void TIMER2_IRQHandler(void)
{
  Timer_Handler_IRQ();
}

void TIMER3_IRQHandler(void)
{
  Timer_Handler_IRQ();
}



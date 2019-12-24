#include "MDR_LwIP_Timer.h"
#include "MDR_Timer.h"

#define LWIP_TIMER_FREQ_HZ      100
#define LWIP_TIMER_PERIOD_MS    10
#define LWIP_TIMER              MDR_TIMER4ex

uint32_t _localTime_ms = 0;

bool MDR_LwIP_TimerRun(uint32_t timClockHz)
{
  uint_tim period;
  uint16_t PSG;
  
  uint32_t resOk = MDR_Timer_CalcPeriodAndPSG(LWIP_TIMER_FREQ_HZ, timClockHz, &period, &PSG);
  
  MDR_Timer_InitPeriod(LWIP_TIMER, MDR_Div128P_div1, PSG, period, true);
  MDR_Timer_Start(LWIP_TIMER);
  
  return resOk;
}

void MDR_LwIP_TimerStop(void)
{
  MDR_Timer_Stop(LWIP_TIMER);
}

void TIMER4_IRQHandler(void)
{
  if (MDR_Timer_IsEventsSet(LWIP_TIMER->TIMERx, TIM_FL_CNT_ARR))
  {
    _localTime_ms += LWIP_TIMER_PERIOD_MS;
    
    MDR_Timer_ClearEvent(LWIP_TIMER->TIMERx, TIM_FL_CNT_ARR);
  }
}

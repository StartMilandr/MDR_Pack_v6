#include <MDR_SysTimer.h>

void MDR_SysTimerStart(uint32_t ticks)
{
  SysTick->LOAD = ticks-1;
  SysTick->VAL  = 0;
  SysTick->CTRL = SysTick_CTRL_ENABLE_Msk | SysTick_CTRL_TICKINT_Msk | SysTick_CTRL_CLKSOURCE_Msk;
}

void MDR_SysTimerStop(void)
{
  SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}

bool MDR_SysTimerStart_ms(uint32_t mSec, uint32_t CPU_FregHz)
{  
  uint32_t period = MS_TO_CLOCKS(mSec, CPU_FregHz);
  
  if (period < SYS_TIMER_VALUE_MAX)
  {  
    MDR_SysTimerStart(period);
    return true;
  }
  else
  {
    return false;
  }
  
  //#define MDR_SysTimerStart_ms(mSec, CPU_FregHz)  MDR_SysTimerStart(MS_TO_CLOCKS((mSec), (CPU_FregHz)))  
}


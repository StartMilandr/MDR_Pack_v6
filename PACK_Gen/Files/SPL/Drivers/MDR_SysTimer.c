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

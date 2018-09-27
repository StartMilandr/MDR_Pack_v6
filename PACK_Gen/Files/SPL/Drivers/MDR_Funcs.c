#include "MDR_Funcs.h"

bool WaitCondition(uint32_t timeoutCycles, pBoolFunc_void checkFunc)
{
  while (timeoutCycles != 0)
  {
    if (checkFunc())
      return true;
    timeoutCycles--;
  };
  return false;
}

void MDR_Delay(uint32_t Ticks)
{
  volatile uint32_t i = Ticks;
  while (--i);
  //for (; i > 0; i--);  // - Больше циклов, сильнее зависит от оптимизации
}


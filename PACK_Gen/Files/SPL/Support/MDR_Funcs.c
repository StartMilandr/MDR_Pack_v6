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

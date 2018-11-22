#ifndef _MDR_SYSTIMER_H
#define _MDR_SYSTIMER_H

#include <MDR_Config.h>
#include <MDR_Funcs.h>

void MDR_SysTimerStart(uint32_t ticks);
void MDR_SysTimerStop(void);
  
#define SYS_TIMER_VALUE_MAX 0xFFFFFF
bool MDR_SysTimerStart_ms(uint32_t mSec, uint32_t CPU_FregHz);


//#define MDR_SysTimerStart_ms(mSec, CPU_FregHz)  MDR_SysTimerStart(MS_TO_CLOCKS((mSec), (CPU_FregHz)))

#endif //  _MDR_SYSTIMER_H

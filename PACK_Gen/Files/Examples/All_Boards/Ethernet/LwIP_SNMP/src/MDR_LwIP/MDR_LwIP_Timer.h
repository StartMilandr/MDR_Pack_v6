#ifndef _MDR_LWIP_TIMER_H
#define _MDR_LWIP_TIMER_H

#include "MDR_Config.h"
#include <stdint.h>
#include <stdbool.h>

extern uint32_t _localTime_ms;

bool      MDR_LwIP_TimerRun(uint32_t timClockHz);
void      MDR_LwIP_TimerStop(void);

__STATIC_INLINE uint32_t  MDR_LwIP_TimerGetTime_ms(void) { return _localTime_ms; }

#endif //_MDR_LWIP_TIMER_H

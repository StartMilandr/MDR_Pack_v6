#ifndef _MDR_HSRPRP_TIME_H
#define _MDR_HSRPRP_TIME_H

#include "MDR_HSRPRP_Config.h"
#include "MDR_Timer.h"
#include <stdint.h>

// Текущее время на хосте, обновляется таймером.
//extern uint32_t hostTime;


void MDR_HSRPRP_TimeInit(void);
bool MDR_HSRPRP_TimeGetEvent2MS(void);


__STATIC_INLINE uint32_t MDR_HSRPRP_GetHostTime(void)
{
	return TIMER_HSRPRP->TIMERx->CNT;
}

// проверка что прошел период с прошлого события
//__STATIC_INLINE bool MDR_HSRPRP_CheckEventPeriod(uint32_t timPeriod, uint32_t *activeTime);


#endif  //  _MDR_HSRPRP_TIME_H

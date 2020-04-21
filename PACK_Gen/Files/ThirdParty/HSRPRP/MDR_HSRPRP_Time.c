#include "MDR_HSRPRP_Time.h"


void MDR_HSRPRP_TimeInit(void)
{	
  MDR_Timer_InitPeriod(TIMER_HSRPRP, TIM_BRG_TO_1MS, TIM_PSC_TO_1MS, TIM_MAX_VALUE, true);
	MDR_Timer_Start(TIMER_HSRPRP);
}


//bool MDR_HSRPRP_TimeCheckPeriodEvent(uint32_t timPeriod, uint32_t lastEventTime, uint32_t *activeTime)
//{
//	*activeTime = MDR_HSRPRP_GetHostTime();
//  if ((*activeTime - lastEventTime) >= timPeriod)
//	{
//	  _HSRPRP_LastEventTime = *activeTime;
//		return true;
//	}
//	else
//		return false;
//}



//static inline void TimerX_HandlerIRQ(void)
//{
//  _HSRPRP_TimerEvent = true;
//	MDR_Timer_ClearEvent(TIMER_HSRPRP->TIMERx, TIM_FL_CNT_ARR);
//}

//void TIMER1_IRQHandler(void)
//{	
//	TimerX_HandlerIRQ();
//}


//bool MDR_HSRPRP_TimeGetEvent2MS(void)
//{
//	if (_HSRPRP_TimerEvent)
//	{
//		_HSRPRP_TimerEvent = false;
//		return true;
//	}
//	else
//		return false;
//}

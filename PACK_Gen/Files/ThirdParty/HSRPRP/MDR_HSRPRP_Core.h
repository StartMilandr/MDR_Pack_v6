#ifndef _MDR_HSRPRP_CORE_H
#define _MDR_HSRPRP_CORE_H

#include <stdint.h>

#include "MDR_HSRPRP_Frames.h"
#include "MDR_HSR.h"
#include "MDR_HSRPRP_TX.h"

//---------------------		Core Init	-----------------------
typedef enum {
	MDR_HSRPRP_EVENT_RingBroken = 1,
} MDR_HSRPRP_Events;

typedef void(*MDR_HSRPRP_EventCallBack)(MDR_HSRPRP_Events event);

void MDR_HSR_CoreInit(MDR_HSRPRP_EventCallBack onEventProc);


//---------------------		Process DANH	-----------------------
void MDR_HSR_ProcessDANH_loc(MDR_HSR_NodeCfg *cfgNode, 
												pHostReceiveFrame_CallBack procHostReceiveFrame,
												pHostReceiveItem_CallBack procHostReceiveItem);


__STATIC_INLINE void MDR_HSR_ProcessDANH(MDR_HSR_NodeCfg *cfgNode, pHostReceiveFrame_CallBack procHostReceiveFrame)
{
  MDR_HSR_ProcessDANH_loc(cfgNode, procHostReceiveFrame, NULL);
}
__STATIC_INLINE void MDR_HSR_ProcessDANHex(MDR_HSR_NodeCfg *cfgNode, pHostReceiveItem_CallBack procHostReceiveItem)
{
  MDR_HSR_ProcessDANH_loc(cfgNode, NULL, procHostReceiveItem);
}



//---------------------		Time Tasks	-----------------------
typedef uint32_t(*GetHostTimeProc)(void);

void MDR_HSR_ProcessAllTimedTasks(MDR_HSR_NodeCfg *cfgNode, GetHostTimeProc getTime);
void MDR_HSR_ProcessNextTimedTask(MDR_HSR_NodeCfg *cfgNode, GetHostTimeProc getTime);
	

//---------------------		Process RedBox	-----------------------
void MDR_HSR_ProcessRedBox(MDR_HSR_RedBoxCfg *cfgRedBox);



#endif  //  _MDR_HSR_ERROR_H

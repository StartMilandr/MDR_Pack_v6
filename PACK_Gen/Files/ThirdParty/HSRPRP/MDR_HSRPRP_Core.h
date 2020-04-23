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



#if MDR_HSR_REDBOX_EN
//---------------------		Process RedBox	-----------------------
  void MDR_HSR_ProcessRedBox_loc(MDR_HSR_RedBoxCfg *cfgRedBox, 
                          pHostReceiveFrame_CallBack procHostReceiveFrame,
                          pHostReceiveItem_CallBack procHostReceiveItem);


  __STATIC_INLINE void MDR_HSR_ProcessRedBox(MDR_HSR_RedBoxCfg *cfgRedBox, pHostReceiveFrame_CallBack procHostReceiveFrame)
  {
    MDR_HSR_ProcessRedBox_loc(cfgRedBox, procHostReceiveFrame, NULL);
  }
  __STATIC_INLINE void MDR_HSR_ProcessRedBoxEx(MDR_HSR_RedBoxCfg *cfgRedBox, pHostReceiveItem_CallBack procHostReceiveItem)
  {
    MDR_HSR_ProcessRedBox_loc(cfgRedBox, NULL, procHostReceiveItem);
  }

#else
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
#endif 


//---------------------		Time Tasks	-----------------------
typedef uint32_t(*GetHostTimeProc)(void);

#if MDR_HSR_REDBOX_EN
  void MDR_HSR_ProcessAllTimedTasks(MDR_HSR_RedBoxCfg *cfgRedBox, GetHostTimeProc getTime);
  void MDR_HSR_ProcessNextTimedTask(MDR_HSR_RedBoxCfg *cfgRedBox, GetHostTimeProc getTime);  
#else
  void MDR_HSR_ProcessAllTimedTasks(MDR_HSR_NodeCfg *cfgNode, GetHostTimeProc getTime);
  void MDR_HSR_ProcessNextTimedTask(MDR_HSR_NodeCfg *cfgNode, GetHostTimeProc getTime);
#endif




#endif  //  _MDR_HSR_ERROR_H

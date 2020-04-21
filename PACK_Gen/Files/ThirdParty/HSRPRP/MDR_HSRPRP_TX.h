#ifndef _MDR_HSRPRP_TX_H
#define _MDR_HSRPRP_TX_H

////#include <MDR_Config.h>
//#include <MDR_Funcs.h>
//#include <MDR_Ethernet.h>

#include "MDR_HSR.h"
#include "MDR_HSR_defs.h"
#include "MDR_HSRPRP_Frames.h"



typedef void(*pHostReceiveItem_CallBack)(MDR_HSRPRP_FrameItem *frameItem);
typedef void(*pHostReceiveFrame_CallBack)(MDR_ETH_FrameRX *frameRX);

void MDR_HSRPRP_ProcessForwardingEx(MDR_HSR_NodeCfg *cfgNode, 
																		MDR_HSRPRP_FrameItem *frameItem, 
																		pHostReceiveFrame_CallBack procHostReceiveFrame,
																		pHostReceiveItem_CallBack procHostReceiveItem);

__STATIC_INLINE void MDR_HSRPRP_ProcessForwarding(MDR_HSR_NodeCfg *cfgNode, MDR_HSRPRP_FrameItem *frameItem, pHostReceiveFrame_CallBack procHostReceiveFrame)
{
  MDR_HSRPRP_ProcessForwardingEx(cfgNode, frameItem, procHostReceiveFrame, NULL);
}
__STATIC_INLINE void MDR_HSRPRP_ProcessForwardingRaw(MDR_HSR_NodeCfg *cfgNode, MDR_HSRPRP_FrameItem *frameItem, pHostReceiveItem_CallBack procHostReceiveItem)
{
  MDR_HSRPRP_ProcessForwardingEx(cfgNode, frameItem, NULL, procHostReceiveItem);
}

bool MDR_HSR_SendSuperFrame(MDR_HSR_NodeCfg *cfgNode);


#endif  // _MDR_HSRPRP_TX_H

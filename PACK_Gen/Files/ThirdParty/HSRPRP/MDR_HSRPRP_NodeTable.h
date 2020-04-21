#ifndef _MDR_HSRPRP_NODE_TABLE_H
#define _MDR_HSRPRP_NODE_TABLE_H

#include <stdint.h>
#include "MDR_HSRPRP_Config.h"
#include "MDR_HSRPRP_Frames.h"
//#include "MDR_HSRPRP_Error.h"
//#include "MDR_HSRPRP_RX.h"
//#include "MDR_HSRPRP_TX.h"
//#include "MDR_HSRPRP_Time.h"
//#include "MDR_HSRPRP_DuplicateTables.h"
#include "MDR_HSR.h"


typedef struct {
	uint8_t 							srcMAC[6];
	MDR_HSRPRP_FramePort  srcPort;
	MDR_HSRPRP_LAN_ID   	lanID;	
	uint32_t							timeRx;
	bool									isActive;
} MDR_HSRPRP_NodeItem;

typedef struct {
	MDR_HSRPRP_NodeItem  *nodeItems;	
	uint32_t						  itemsCount;	
	//	locals
	uint32_t						  _lastAddInd;	
	uint32_t						  _lastFreeInd;
} MDR_HSRPRP_NodeTable;


extern MDR_HSRPRP_NodeTable _NodeTable;

bool MDR_HSR_AddNodeEx(MDR_HSRPRP_NodeTable *nodeTable, MDR_HSRPRP_FrameItem *frameItem);
void MDR_HSR_ProcessNodeForgetEx(MDR_HSRPRP_NodeTable *nodeTable, uint32_t timeNow, uint32_t forgetTime);
int32_t MDR_HSR_HasNodeEx(MDR_HSRPRP_NodeTable *nodeTable, MDR_HSRPRP_FrameItem *frameItem);

// True - if new added
__STATIC_INLINE bool MDR_HSR_AddNodeOrUpdateEx(MDR_HSRPRP_NodeTable *nodeTable, MDR_HSRPRP_FrameItem *frameItem)
{
  int32_t nodeInd =  MDR_HSR_HasNodeEx(nodeTable, frameItem);
	if (nodeInd >= 0)
	{
		nodeTable->nodeItems[nodeInd].timeRx = frameItem->timeRx;
		return false;
	}
	else
		return MDR_HSR_AddNodeEx(nodeTable, frameItem);
}

//----------------		Node Table	--------

//__STATIC_INLINE bool MDR_HSR_AddNode(MDR_HSRPRP_FrameItem *frameItem)
//{
//  return MDR_HSR_AddNodeEx(&_NodeTable, frameItem);
//}

//__STATIC_INLINE bool MDR_HSR_HasNode(MDR_HSRPRP_FrameItem *frameItem)
//{
//  return MDR_HSR_HasNodeEx(&_NodeTable, frameItem) != -1;
//}

__STATIC_INLINE bool MDR_HSR_AddNodeOrUpdate(MDR_HSRPRP_FrameItem *frameItem)
{
  return MDR_HSR_AddNodeOrUpdateEx(&_NodeTable, frameItem);
}

__STATIC_INLINE void MDR_HSR_ProcessNodeForget(uint32_t timeNow, uint32_t forgetTime)
{
  MDR_HSR_ProcessNodeForgetEx(&_NodeTable, timeNow, forgetTime);
}



//__STATIC_INLINE bool MDR_HSR_HasNodeAndUpdateTimeRx(MDR_HSRPRP_FrameItem *frameItem)
//{
//  int32_t nodeInd =  MDR_HSR_HasNodeEx(&_NodeTable, frameItem);
//	if (nodeInd >= 0)
//	{
//		_NodeTable.nodeItems[nodeInd].timeRx = frameItem->timeRx;
//		return true;
//	}
//	else
//		return false;
//}


//---------------		RedBox	--------------

//#if MDR_HSR_REDBOX_EN
extern MDR_HSRPRP_NodeTable _ProxyNodeTable;

//__STATIC_INLINE bool MDR_HSR_AddProxyNode(MDR_HSRPRP_FrameItem *frameItem)
//{
//	return MDR_HSR_AddNodeEx(&_ProxyNodeTable, frameItem);
//}

__STATIC_INLINE bool MDR_HSR_HasProxyNode(MDR_HSRPRP_FrameItem *frameItem)
{
  return MDR_HSR_HasNodeEx(&_ProxyNodeTable, frameItem) != -1;
}
	

__STATIC_INLINE bool MDR_HSR_AddProxyNodeOrUpdate(MDR_HSRPRP_FrameItem *frameItem)
{
  return MDR_HSR_AddNodeOrUpdateEx(&_ProxyNodeTable, frameItem);
}

	
__STATIC_INLINE void MDR_HSR_ProcessProxyNodeForget(uint32_t timeNow, uint32_t forgetTime)
{
	MDR_HSR_ProcessNodeForgetEx(&_ProxyNodeTable, timeNow, forgetTime);
}

//#endif																									






#endif  //  _MDR_HSRPRP_NODE_TABLE_H

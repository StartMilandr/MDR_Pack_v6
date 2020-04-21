#include "MDR_HSRPRP_NodeTable.h"


MDR_HSRPRP_NodeItem  _NodeTablesItems[HSR_NodeTableMaxEntries];
MDR_HSRPRP_NodeTable _NodeTable = {.nodeItems = _NodeTablesItems,
																					.itemsCount = HSR_NodeTableMaxEntries,	
																					._lastAddInd = 0,
																					._lastFreeInd = 0
																					};

MDR_HSRPRP_NodeItem  _ProxyNodeTablesItems[HSR_ProxyNodeTableMaxEntries];
MDR_HSRPRP_NodeTable _ProxyNodeTable = {.nodeItems = _ProxyNodeTablesItems,
																								.itemsCount = HSR_ProxyNodeTableMaxEntries,	
																								._lastAddInd = 0,
																								._lastFreeInd = 0
																								};
	
bool MDR_HSR_AddNodeEx(MDR_HSRPRP_NodeTable *nodeTable, MDR_HSRPRP_FrameItem *frameItem)
{
	uint32_t ind = nodeTable->_lastAddInd;
	uint32_t indStart = ind;
	uint32_t cnt = nodeTable->itemsCount;
	MDR_HSRPRP_NodeItem *nodeItem;
	
	do {
		if (!nodeTable->nodeItems[ind].isActive)
		{
			// Fill NodeItem
			nodeTable->_lastAddInd = ind;						
			nodeItem = &nodeTable->nodeItems[ind];

			MDR_ETH_CopyMAC(nodeItem->srcMAC, frameItem->framePtrs.pHeader->srcMAC);
			nodeItem->srcPort = frameItem->frameSrc;
			nodeItem->lanID = frameItem->framePtrs.lanID; // !?  lanID из самого фрейма, может надо из lanID порта?
			nodeItem->timeRx = frameItem->timeRx;
			nodeItem->isActive = true;		

			return true;
		}
			
		ind++;
		if (ind >= cnt)
			ind = 0;
	} while (ind != indStart);
	
	return false;
}


static inline bool MDR_HSRPRP_IsNodesSame(MDR_HSRPRP_FrameItem *frameItem, MDR_HSRPRP_NodeItem *nodeItem)
{
//	if (nodeItem->srcPort == frameItem->frameSrc)
//		if (nodeItem->lanID == frameItem->framePtrs.lanID)	
			if (MDR_ETH_IsSameMACs(nodeItem->srcMAC, frameItem->framePtrs.pHeader->srcMAC))
				return true;
			
	return false;		
}

int32_t MDR_HSR_HasNodeEx(MDR_HSRPRP_NodeTable *nodeTable, MDR_HSRPRP_FrameItem *frameItem)
{
  uint32_t ind = nodeTable->_lastFreeInd;
	uint32_t indStart = ind;
	uint32_t cnt = nodeTable->itemsCount;
	
	do {
		if (MDR_HSRPRP_IsNodesSame(frameItem, &(nodeTable->nodeItems[ind])))
		{			
#if DUPLICATE_TABLE_FREE_ITEM_ON_DUPL_RX
			nodeTable->duplItems[ind].isActive = false;
#endif
			
MDR_LOG_Add_def(LOG_HAS_DUPL);
MDR_LOG_Add_def(frameItem->_frmIndex);
MDR_LOG_Add_def(ind);			
			
		  return ind;
		}
			
		ind++;
		if (ind >= cnt)
			ind = 0;
	} while (ind != indStart);
	
	return -1;
}


void MDR_HSR_ProcessNodeForgetEx(MDR_HSRPRP_NodeTable *nodeTable, uint32_t timeNow, uint32_t forgetTime)
{
	MDR_HSRPRP_NodeItem *duplItem;
  uint32_t ind = nodeTable->_lastFreeInd;
	uint32_t indStart = ind;
	uint32_t cnt = nodeTable->itemsCount;
	
	do {
		duplItem = &(nodeTable->nodeItems[ind]);
		if (duplItem->isActive)
			if ((timeNow - duplItem->timeRx) >= forgetTime)
			{				
				duplItem->isActive = false;
				nodeTable->_lastFreeInd = ind;

MDR_LOG_Add_def(LOG_DEL_NODE_AGE);
MDR_LOG_Add_def(ind);
			}
			
		ind++;
		if (ind >= cnt)
			ind = 0;
	} while (ind != indStart);
}



#include "MDR_HSRPRP_DuplicateTables.h"


static MDR_HSRPRP_DuplItem lreDuplItems_PortA[DUPLICATE_TABLE_LEN_PORT];
static MDR_HSRPRP_DuplItem lreDuplItems_PortB[DUPLICATE_TABLE_LEN_PORT];
static MDR_HSRPRP_DuplItem lreDuplItems_HOST[DUPLICATE_TABLE_LEN_HOST];

MDR_HSRPRP_DuplTable  lreDuplTable_PortA = {.itemsCount = DUPLICATE_TABLE_LEN_PORT, .duplItems =	lreDuplItems_PortA};
MDR_HSRPRP_DuplTable  lreDuplTable_PortB = {.itemsCount = DUPLICATE_TABLE_LEN_PORT, .duplItems =	lreDuplItems_PortB};
MDR_HSRPRP_DuplTable  lreDuplTable_HOST  = {.itemsCount = DUPLICATE_TABLE_LEN_HOST, .duplItems =	lreDuplItems_HOST};

#if MDR_HSR_REDBOX_EN
	static MDR_HSRPRP_DuplItem lreDuplItems_Interlink[DUPLICATE_TABLE_LEN_INTERLINK];
	MDR_HSRPRP_DuplTable  lreDuplTable_Interlink  = {.itemsCount = DUPLICATE_TABLE_LEN_INTERLINK, .duplItems =	lreDuplItems_Interlink};
#endif



static inline bool MDR_HSRPRP_Dupl_IsItemsSame(MDR_HSRPRP_FrameItem *frameItem, MDR_HSRPRP_DuplItem *duplItem)
{
	MDR_HSR_Tag_t *frameTag = (MDR_HSR_Tag_t *)frameItem->framePtrs.pTag;
	
	return (duplItem->tag.etherType == frameTag->etherType) &&
				 (duplItem->tag.lanID_LSDUSize == frameTag->lanID_LSDUSize) &&
				 (duplItem->tag.seqNum == frameTag->seqNum);
}

static inline void MDR_HSRPRP_Dupl_CaptureItems(MDR_HSRPRP_FrameItem *frameItem, MDR_HSRPRP_DuplItem *duplItem)
{
	MDR_HSR_Tag_t *frameTag = (MDR_HSR_Tag_t *)frameItem->framePtrs.pTag;
	
	duplItem->tag.etherType = frameTag->etherType;
	duplItem->tag.lanID_LSDUSize = frameTag->lanID_LSDUSize;
	duplItem->tag.seqNum = frameTag->seqNum;
	
  duplItem->isActive = true;
}


bool MDR_HSRPRP_Dupl_HasItem(MDR_HSRPRP_FrameItem *frameItem, MDR_HSRPRP_DuplTable *table)
{
  uint32_t ind = table->_lastFreeInd;
	uint32_t indStart = ind;
	uint32_t cnt = table->itemsCount;
	
	do {
		if (MDR_HSRPRP_Dupl_IsItemsSame(frameItem, &(table->duplItems[ind])))
		{			
#if DUPLICATE_TABLE_FREE_ITEM_ON_DUPL_RX
			table->duplItems[ind].isActive = false;
#endif
			
MDR_LOG_Add_def(LOG_HAS_DUPL);
MDR_LOG_Add_def(frameItem->_frmIndex);
MDR_LOG_Add_def(ind);			
			
		  return true;
		}
			
		ind++;
		if (ind >= cnt)
			ind = 0;
	} while (ind != indStart);
	
	return false;
}	


bool MDR_HSRPRP_Dupl_AddItem(MDR_HSRPRP_FrameItem *frameItem, MDR_HSRPRP_DuplTable *table)
{
	if (frameItem->framePtrs.lenTag > 0)
	{
		uint32_t ind = table->_lastAddInd;
		uint32_t indStart = ind;
		uint32_t cnt = table->itemsCount;
		
		do {
			if (!table->duplItems[ind].isActive)
			{
				MDR_HSRPRP_Dupl_CaptureItems(frameItem, &(table->duplItems[ind]));
				table->_lastAddInd = ind;
				return true;
			}
				
			ind++;
			if (ind >= cnt)
				ind = 0;
		} while (ind != indStart);
  }
	
	return false;
}


void MDR_HSRPRP_Dupl_DelAgedItems(MDR_HSRPRP_DuplTable *table, uint32_t newTime, uint32_t ageDelTime)
{
	MDR_HSRPRP_DuplItem *duplItem;
  uint32_t ind = table->_lastFreeInd;
	uint32_t indStart = ind;
	uint32_t cnt = table->itemsCount;
	
	do {
		duplItem = &(table->duplItems[ind]);
		if (duplItem->isActive)
			if ((newTime - duplItem->timeRx) >= ageDelTime)
			{				
				duplItem->isActive = false;
				table->_lastFreeInd = ind;
				
MDR_LOG_Add_def(LOG_DEL_AGE);
MDR_LOG_Add_def(ind);
			}
			
		ind++;
		if (ind >= cnt)
			ind = 0;
	} while (ind != indStart);
}

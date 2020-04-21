#ifndef _MDR_HSRPRP_DUPLICATE_TABLES_H
#define _MDR_HSRPRP_DUPLICATE_TABLES_H

#include "MDR_HSRPRP_Config.h"
#include "MDR_HSRPRP_Frames.h"

typedef struct {
	uint32_t      timeRx;
	MDR_HSR_Tag_t tag;
	bool					isActive;
} MDR_HSRPRP_DuplItem;

typedef struct {
	MDR_HSRPRP_DuplItem *duplItems;	
	uint32_t						itemsCount;	
	//	locals
	uint32_t						_lastAddInd;	
	uint32_t						_lastFreeInd;
} MDR_HSRPRP_DuplTable;


extern MDR_HSRPRP_DuplTable  lreDuplTable_PortA;
extern MDR_HSRPRP_DuplTable  lreDuplTable_PortB;
extern MDR_HSRPRP_DuplTable  lreDuplTable_HOST;

#if MDR_HSR_REDBOX_EN
	extern MDR_HSRPRP_DuplTable  hsrDuplTable_Interlink;
#endif


bool MDR_HSRPRP_Dupl_HasItem(MDR_HSRPRP_FrameItem *frameItem, MDR_HSRPRP_DuplTable *table);
bool MDR_HSRPRP_Dupl_AddItem(MDR_HSRPRP_FrameItem *frameItem, MDR_HSRPRP_DuplTable *table);
void MDR_HSRPRP_Dupl_DelAgedItems(MDR_HSRPRP_DuplTable *table, uint32_t newTime, uint32_t ageDelTime);


__STATIC_INLINE void MDR_HSRPRP_Dupl_ProcessAgeing(uint32_t newTime, uint32_t ageDelTime)
{
  MDR_HSRPRP_Dupl_DelAgedItems(&lreDuplTable_PortA, newTime, ageDelTime);
	MDR_HSRPRP_Dupl_DelAgedItems(&lreDuplTable_PortB, newTime, ageDelTime);
	MDR_HSRPRP_Dupl_DelAgedItems(&lreDuplTable_HOST, newTime, ageDelTime);
	
#if MDR_HSR_REDBOX_E	
	MDR_HSRPRP_Dupl_DelAgedItems(&lreDuplTable_Interlink, newTime, &ageDelTime);
#endif
}



#endif  //  _MDR_HSRPRP_DUPLICATE_TABLES_H


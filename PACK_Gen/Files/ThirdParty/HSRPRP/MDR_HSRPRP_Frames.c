#include "MDR_HSRPRP_Frames.h"
#include <stdlib.h>

static MDR_HSRPRP_FrameItem  _InpFrames[MDR_HSRPRP_FRAME_ITEM_COUNT];
uint32_t _lastFreeInd = 1;			//	Чтобы выборка _lastSelectedInd была с 0
uint32_t _lastSelectedInd = 0;


void MDR_HSRPRP_AllocateFrameItems(void)
{
  uint32_t i;
	for (i = 0; i < MDR_HSRPRP_FRAME_ITEM_COUNT; ++i )
	  _InpFrames[i].frameBuff = malloc(MDR_HSRPRP_FRAME_MAX_LEN);
}

void MDR_HSRPRP_FreeFrameItems(void)
{
  uint32_t i;
	for (i = 0; i < MDR_HSRPRP_FRAME_ITEM_COUNT; ++i )
	  free(_InpFrames[i].frameBuff);
}

//  Получить свободный FrameItem чтобы записать туда фрейм
MDR_HSRPRP_FrameItem * MDR_HSRPRP_CaptureFrameItem(void)
{
  uint32_t startIndex = _lastFreeInd;
	uint32_t ind = startIndex;
	MDR_HSRPRP_FrameItem * resItem = NULL;
	
	do {
    if (_InpFrames[ind].status == MDR_HSRPRP_Free)
		{
			resItem = &_InpFrames[ind];
			resItem->_frmIndex = ind;
			resItem->status = MDR_HSRPRP_WaitInputProcess;
			resItem->forwTasks.selForwPort = 0;
			return resItem;
		}
		
		//	IncIndex
    ++ind;
    if (ind >= MDR_HSRPRP_FRAME_ITEM_COUNT)
      ind = 0;				
	} while (ind != startIndex);
	
	return resItem;
}

//  Освободить захваченый ранее FrameItem
void MDR_HSRPRP_FreeFrameItem(MDR_HSRPRP_FrameItem *frameItem)
{
  _InpFrames->status = MDR_HSRPRP_Free;
  _lastFreeInd = _InpFrames->_frmIndex;
}

bool MDR_HSRPRP_IsFramePRP(const MDR_HSRPRP_Payload *payload, uint32_t len, MDR_HSRPRP_LAN_ID *lanID)
{
  MDR_PRP_Tag_t *pTag = (MDR_PRP_Tag_t *)((uint32_t)payload + len - MDR_HSR_TAG_LEN);
  *lanID = MDR_HSRPRP_LanUndef;
  
  if (pTag->suffPRP != ETH_SUFF_PRP)
    return false;
  else
  {
    uint32_t lenRef = LSDUSize_ToSize(pTag->lanID_LSDUSize);
    if (lenRef != (len - MDR_ETH_TYPE_FLD_LEN))
      return false;
    
    uint32_t lanRef = LSDUSize_ToLanID(pTag->lanID_LSDUSize);
    if ((lanRef != MDR_HSRPRP_LanA ) && (lanRef == MDR_HSRPRP_LanB))
      return false;
    
    *lanID = (MDR_HSRPRP_LAN_ID)lanRef;
  }
  
  return true;
}


//  Распарсить автоматически указатели на структуры фрейма по его типу (маска frameTypes)
//  Вызывать после записи фрейма в frameItem->frameBuff
//  В frameSrc указать с какого порта считаны данные
static void MDR_HSRPRP_FillPTRs(MDR_HSRPRP_FrameItem *frameItem)
{
  uint8_t *pFrame = FrameItemGetFrameTX(frameItem)->frame;
  uint32_t frameLen = frameItem->frameLen;
  
  //  Проверка VLAN  
  frameItem->framePtrs.pHeader = (MDR_HSRPRP_HeaderMax *)pFrame;  
  frameItem->framePtrs.isVLAN = ((MDR_HSRPRP_HeaderVLAN *)pFrame)->tagVLAN == ETH_TYPE_VLAN;
  if (!frameItem->framePtrs.isVLAN)
    frameItem->framePtrs.lenHeader  = MDR_HSRPRP_HEADER_LEN;        
  else
    frameItem->framePtrs.lenHeader  = MDR_HSRPRP_HEADER_VLAN_LEN;    

  
  //  Проверка ethType и инициализация указателей Tag и Payload
  void *pEtherType = &pFrame[frameItem->framePtrs.lenHeader];  
  uint16_t ethType = *(uint16_t *)pEtherType;  
  bool setEmptyTag = false;  
  
  if (ethType == ETH_TYPE_PRP_SUP)
  {
    frameItem->framePtrs.frameType = MDR_HSRPRP_FrameSupPRP;
    setEmptyTag = true;
  }
  else if (ethType == ETH_TYPE_HSR)
  {
    MDR_HSR_SuperFrameTag* pSupHSR = (MDR_HSR_SuperFrameTag*)pEtherType;
    if (pSupHSR->supEtherType == ETH_HSR_SUP_ETHER_TYPE)
    {
      frameItem->framePtrs.frameType = MDR_HSRPRP_FrameSupHSR;
      setEmptyTag = true;      
    }
    else
    {
      frameItem->framePtrs.frameType = MDR_HSRPRP_FrameHSR;
      
      frameItem->framePtrs.pTag   = (uint8_t *)pEtherType;
      frameItem->framePtrs.lenTag = MDR_HSR_TAG_LEN;    
      frameItem->framePtrs.pPayload   = (MDR_HSRPRP_Payload *)((uint32_t)(pEtherType) + MDR_HSR_TAG_LEN);
      frameItem->framePtrs.lenPayload = frameLen - frameItem->framePtrs.lenHeader - MDR_HSR_TAG_LEN;
    }
  }
  else if (MDR_HSRPRP_IsFramePRP(pEtherType, frameLen - frameItem->framePtrs.lenHeader, &frameItem->framePtrs.lanID))
  {
    frameItem->framePtrs.frameType = MDR_HSRPRP_FramePRP;
    
    frameItem->framePtrs.pPayload   = (MDR_HSRPRP_Payload *)pEtherType;
    frameItem->framePtrs.lenPayload = frameLen - frameItem->framePtrs.lenHeader - MDR_PRP_TAG_LEN;    
    frameItem->framePtrs.pTag   = (uint8_t *)((uint32_t)(pEtherType) + frameItem->framePtrs.lenPayload);
    frameItem->framePtrs.lenTag = MDR_PRP_TAG_LEN;    
  }
  else
  {
    frameItem->framePtrs.frameType = MDR_HSRPRP_FrameEth;
    setEmptyTag = true;
  }
  
  //  Для суперфреймов Tag входит в pPayload (потому что вставлять при трансляции ничего не надо)
  if (setEmptyTag)
  {
    frameItem->framePtrs.pTag   = NULL;
    frameItem->framePtrs.lenTag = 0;
    frameItem->framePtrs.pPayload   = (MDR_HSRPRP_Payload *)pEtherType;
    frameItem->framePtrs.lenPayload = frameLen - frameItem->framePtrs.lenHeader;      
  }
}

//  Назначение приоритета на отправку в зависимости от содержимого фрейма
static void MDR_HSRPRP_FillPriority(MDR_HSRPRP_FrameItem *frameItem)
{
  // Пока по умолчанию
  frameItem->forwPriority = MDR_HSRPRP_PROIRITY_DEF;
}

//  Заполнение  FrameItem по содержимому фрейма
void MDR_HSRPRP_ProcessInputFrame(MDR_HSRPRP_FrameItem *frameItem)
{
  MDR_HSRPRP_FillPTRs(frameItem);
  MDR_HSRPRP_FillPriority(frameItem);
	frameItem->status = MDR_HSRPRP_WaitTackAssign;
}

//  Выборка следующего фрейма для обработки (выборка по статусу и приоритету)
MDR_HSRPRP_FrameItem*  MDR_HSRPRP_GetNextFrameByStatusAndPriority(MDR_HSRPRP_FrameItemStatus status)
{
	uint32_t maxPriority = MDR_HSRPRP_PROIRITY_MIN;
	uint32_t startInd = _lastSelectedInd;	
  uint32_t i = startInd;
	MDR_HSRPRP_FrameItem* resItem = NULL;
	MDR_HSRPRP_FrameItem* frameItem;
	
  do
  {
    ++i;
    if (i >= MDR_HSRPRP_FRAME_ITEM_COUNT)
      i = 0;
		
		frameItem = &(_InpFrames[i]);		
		if (frameItem->status == status)
		{
			if ((resItem == NULL)	|| (frameItem->forwPriority > maxPriority))
			{
				_lastSelectedInd = i;
				maxPriority = frameItem->forwPriority;
				resItem = frameItem;
			}
	  }
		
  } while (i != startInd);
  
	return resItem;
}

//  Выборка следующего фрейма для обработки (выборка по статусу и БЕЗ приоритета)
MDR_HSRPRP_FrameItem*  MDR_HSRPRP_GetNextFrameByStatus(MDR_HSRPRP_FrameItemStatus status)
{
	uint32_t startInd = _lastSelectedInd;	
  uint32_t i = startInd;	
	
  do
  {
    ++i;
    if (i >= MDR_HSRPRP_FRAME_ITEM_COUNT)
      i = 0;
		
		if (_InpFrames[i].status == status)
		{
			_lastSelectedInd = i;
			return &_InpFrames[i];
		}		
  } while (i != startInd);
  
	return NULL;
}

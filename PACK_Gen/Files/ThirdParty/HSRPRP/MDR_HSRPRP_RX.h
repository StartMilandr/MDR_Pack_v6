#ifndef _MDR_HSRPRP_RX_H
#define _MDR_HSRPRP_RX_H

#include <MDR_Config.h>
#include "MDR_HSRPRP_Frames.h"
#include "MDR_HSRPRP_Time.h"

//	Чтение пришедшего фрейма в FrameItem,  FrameItem.Status = MDR_HSRPRP_WaitInputProcess 
//  Далее ожидается вызов MDR_HSRPRP_ProcessInputFrame() для инициалиазции остальных полей FrameItem
//	(разбора что это за фрейм и инициализации указателей на header, tag, payload)
MDR_HSRPRP_FrameItem * ETH_HSRPRP_ReceiveFrame(MDR_ETH_Type *MDR_Eth, MDR_HSRPRP_FramePort portSrc);

//	Посылка фрейма от Host (содержит лишнее данных копирование из frameTX в FrameItem).
MDR_HSRPRP_FrameItem * ETH_HSRPRP_HostSendFrame(MDR_ETH_FrameTX *frameTX);

//	Лучше использовать сразу FrameItem.
__STATIC_INLINE MDR_HSRPRP_FrameItem * ETH_HSRPRP_HostGetFrameItem(void) { return MDR_HSRPRP_CaptureFrameItem(); }

//	Послать фрейм (доинициализация Item после записи пользователем данных в frameTX)
__STATIC_INLINE void ETH_HSRPRP_HostSendFrameItem(MDR_HSRPRP_FrameItem *frameItem)
{
	frameItem->frameLen = FrameItemGetFrameTX(frameItem)->frameLen;
	frameItem->frameSrc = MDR_HSRPRP_Host;
	frameItem->timeRx = MDR_HSRPRP_GetHostTime();
}



#endif	//_MDR_HSRPRP_RX_H

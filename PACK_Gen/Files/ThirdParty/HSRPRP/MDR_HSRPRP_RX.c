#include "MDR_HSRPRP_RX.h"

//#include <MDR_Config.h>
//#include <MDR_RST_Clock.h>
#include <MDR_Ethernet.h>
#include <MDR_Ethernet_FrameDefs.h>

//#include <MDR_Funcs.h>
//#include <MDRB_Buttons.h>
//#include <MDRB_LEDs.h>
#include <string.h>

//#include "MDR_Ethernet_Cfg1.h"
//#include "MDRB_ETH_ExtPHY_MII.h"

//#include "MDR_HSRPRP_Config.h"
//#include "MDR_HSRPRP_Frames.h"
#include "MDR_HSRPRP_Error.h"


MDR_HSRPRP_FrameItem * ETH_HSRPRP_ReceiveFrame(MDR_ETH_Type *MDR_Eth, MDR_HSRPRP_FramePort portSrc)
{
  //  Получаем свободный FrameItem
  MDR_HSRPRP_FrameItem *frameItem = MDR_HSRPRP_CaptureFrameItem();
  if (frameItem == NULL)
  {
    MDR_HSR_LogError(MDR_HSR_Err_RxNoFreeFrameItem, (uint32_t)portSrc);
    MDR_ETH_ClearBuffRX(MDR_Eth);
    return NULL;
  }    
  
  //MDR_ETH_FrameStatusRX statusRX;
  //  Первое 32-х битное слово - статус принятого фрейма (для передаваемого Фрейма это будет длина)
	MDR_ETH_FrameRX * frameRX = (MDR_ETH_FrameRX *)(frameItem->frameBuff);
	if (MDR_ETH_TryReadFrameF(MDR_Eth, frameRX))
  {
    frameItem->frameLen = frameRX->statusRX.Fields.Length;
		frameItem->frameSrc = portSrc;
		frameItem->timeRx = MDR_HSRPRP_GetHostTime();

    //  Перенести в основной цикл, чтобы прерывание было короче?
    //  Вместе с назначением задач на Forwarding
//    MDR_HSRPRP_ProcessInputFrame(frameItem);
		return frameItem;
  }
  else
	{
    MDR_HSRPRP_FreeFrameItem(frameItem);
		return NULL;
	}
}

MDR_HSRPRP_FrameItem * ETH_HSRPRP_HostSendFrame(MDR_ETH_FrameTX *frameTX)
{
  //  Получаем свободный FrameItem
  MDR_HSRPRP_FrameItem *frameItem = MDR_HSRPRP_CaptureFrameItem();
  if (frameItem == NULL)
  {
    MDR_HSR_LogError(MDR_HSR_Err_TxNoFreeFrameItem, (uint32_t)MDR_HSRPRP_Host);
    return NULL;
  }

	frameItem->frameLen = frameTX->frameLen;
	frameItem->frameSrc = MDR_HSRPRP_Host;
	memcpy(frameItem->frameBuff, (uint8_t *)frameTX, frameTX->frameLen); 
	return frameItem;
}



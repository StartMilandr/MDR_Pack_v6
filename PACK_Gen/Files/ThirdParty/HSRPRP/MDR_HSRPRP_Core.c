#include "MDR_HSRPRP_Core.h"

//#include "MDR_HSRPRP_Config.h"

#include "MDR_HSRPRP_Error.h"
#include "MDR_HSRPRP_RX.h"
#include "MDR_HSRPRP_Time.h"
#include "MDR_HSRPRP_DuplicateTables.h"
#include "MDR_HSRPRP_NodeTable.h"

MDR_HSRPRP_EventCallBack _onEventProc;

void MDR_HSR_CoreInit(MDR_HSRPRP_EventCallBack onEventProc)
{
	_onEventProc = onEventProc;
  MDR_HSRPRP_AllocateFrameItems();
}



//---------------------		Process DANH	-----------------------

void MDR_HSR_ProcessDANH_loc(MDR_HSR_NodeCfg *cfgNode, 
												pHostReceiveFrame_CallBack procHostReceiveFrame,
												pHostReceiveItem_CallBack procHostReceiveItem)
{
	MDR_HSRPRP_FrameItem* frameItem;
	
	//	Select frameItem for processing
	frameItem = MDR_HSRPRP_GetNextFrameByStatusAndPriority(MDR_HSRPRP_WaitInputProcess);
	//frameItem = MDR_HSRPRP_GetNextFrameByStatus(MDR_HSRPRP_WaitInputProcess);
	if (frameItem != NULL)
	{
		//	Define frame type and fill frameItem fields
		MDR_HSRPRP_ProcessInputFrame(frameItem);
		
		//	Assign ForwardTasks
		MDR_HSR_DANH_AssignForwardTasks(cfgNode, frameItem);
		
		//	Transmit Frame by ForwardTasks
		if (frameItem->status == MDR_HSRPRP_WaitForward)
		{
MDR_LOG_Add_def(LOG_PROC_FORW);
MDR_LOG_Add_def(frameItem->_frmIndex);
			
			MDR_HSRPRP_ProcessForwardingEx(cfgNode, frameItem, procHostReceiveFrame, procHostReceiveItem);			
		}
	}

}

//---------------------		Time Tasks	-----------------------

static bool MDR_HSR_ForgetDuplicateItems(MDR_HSR_NodeCfg *cfgNode, uint32_t timeNow)
{
	if ((timeNow - cfgNode->lastTimeForgetDuplicate) > HSR_EntryForgetTime)
	{
		MDR_HSRPRP_Dupl_ProcessAgeing(timeNow, HSR_EntryForgetTime);
		cfgNode->lastTimeForgetDuplicate = timeNow;
		return true;
	}
	else
		return false;
}		

static bool MDR_HSR_CheckAndSendSuperFrame(MDR_HSR_NodeCfg *cfgNode, uint32_t timeNow)
{
	if ((timeNow - cfgNode->lastTimeSuperSend) > HSR_LifeCheckInterval)
		if (MDR_HSR_SendSuperFrame(cfgNode))
		{
			cfgNode->lastTimeSuperSend = timeNow;
		  return true;
		}
  return false;
}		

static bool MDR_HSR_ForgetNode(MDR_HSR_NodeCfg *cfgNode, uint32_t timeNow)
{
	if ((timeNow - cfgNode->lastTimeForgetNode) > HSR_NodeForgetTime)
	{
		MDR_HSR_ProcessNodeForget(timeNow, HSR_NodeForgetTime);
		cfgNode->lastTimeForgetNode = timeNow;
		return true;
	}
	else
		return false;
}

static bool MDR_HSR_CheckSuperLostEx(MDR_HSR_NodeCfg *cfgNode, uint32_t timeNow)
{
	if ((timeNow - cfgNode->lastTimeSelfSuperRx) > HSR_WaitSuperFrameReturn)
	{
		cfgNode->isRingClosed = cfgNode->seqNumSup == cfgNode->seqNumSupRx;
	  if (!cfgNode->isRingClosed)
		{
			cfgNode->superLostCnt++;
			if (_onEventProc != NULL)
			  _onEventProc(MDR_HSRPRP_EVENT_RingBroken);
		}
	
		cfgNode->doCheckSupRx = false;
	}
	
	return cfgNode->isRingClosed;
}

static bool MDR_HSR_CheckSuperLost(MDR_HSR_NodeCfg *cfgNode, uint32_t timeNow)
{
	if (cfgNode->doCheckSupRx)
		return MDR_HSR_CheckSuperLostEx(cfgNode, timeNow);
	else
		return cfgNode->isRingClosed;
}

#if MDR_HSR_REDBOX_EN
static bool MDR_HSR_ForgetProxyNode(MDR_HSR_NodeCfg *cfgNode, uint32_t timeNow)
{
	if ((timeNow - cfgNode->lastTimeForgetNode) > HSR_ProxyNodeTableForgetTime)
	{
		MDR_HSR_ProcessProxyNodeForget(timeNow, HSR_ProxyNodeTableForgetTime);
		cfgNode->lastTimeForgetNode = timeNow;
		return true;
	}
	else
		return false;
}
#endif


typedef bool(*pTimeTaskProc)(MDR_HSR_NodeCfg *cfgNode, uint32_t timeNow);


pTimeTaskProc _timeHandlers[] = { MDR_HSR_ForgetDuplicateItems, 
																	//MDR_HSR_CheckAndSendSuperFrame, 
																	MDR_HSR_ForgetNode,
																	MDR_HSR_CheckSuperLost,
#if MDR_HSR_REDBOX_EN	
																	MDR_HSR_ForgetProxyNode
#endif
																};

#define TIME_HANDLER_COUNT		sizeof(_timeHandlers)/sizeof(_timeHandlers[0])	



void MDR_HSR_ProcessAllTimedTasks(MDR_HSR_NodeCfg *cfgNode, GetHostTimeProc getTime)
{
	MDR_HSR_ForgetDuplicateItems(cfgNode, getTime());
	MDR_HSR_CheckAndSendSuperFrame(cfgNode, getTime());
	MDR_HSR_ForgetNode(cfgNode, getTime());
	
	if (cfgNode->doCheckSupRx)
		MDR_HSR_CheckSuperLostEx(cfgNode, getTime());
	
#if MDR_HSR_REDBOX_EN	
	MDR_HSR_ForgetProxyNode(cfgNode, getTime());
#endif	
}

void MDR_HSR_ProcessNextTimedTask(MDR_HSR_NodeCfg *cfgNode, GetHostTimeProc getTime)
{
  uint32_t taskInd = cfgNode->lastTimeTaskInd;
	if (taskInd >= TIME_HANDLER_COUNT)
		taskInd = 0;
	
	_timeHandlers[taskInd](cfgNode, getTime());
	cfgNode->lastTimeTaskInd = taskInd + 1;	
}


//---------------------		Process RedBox	-----------------------
void MDR_HSR_ProcessRedBox(MDR_HSR_RedBoxCfg *cfgRedBox)
{

}

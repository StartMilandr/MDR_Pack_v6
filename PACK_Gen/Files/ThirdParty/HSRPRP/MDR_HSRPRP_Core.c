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

#if MDR_HSR_REDBOX_EN
  //---------------------		Process RedBox	-----------------------
  static bool MDR_HSR_ForgetProxyNode(void *cfg, uint32_t timeNow)
  {
    MDR_HSR_NodeCfg *cfgNode = (MDR_HSR_NodeCfg *)cfg;
    if ((timeNow - cfgNode->lastTimeForgetNode) > HSR_ProxyNodeTableForgetTime)
    {
      MDR_HSR_ProcessProxyNodeForget(timeNow, HSR_ProxyNodeTableForgetTime);
      cfgNode->lastTimeForgetNode = timeNow;
      return true;
    }
    else
      return false;
  }

  void MDR_HSR_ProcessRedBox_loc(MDR_HSR_RedBoxCfg *cfgRedBox, 
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
      MDR_HSR_Redbox_AssignForwardTasks(cfgRedBox, frameItem);
      
      //	Transmit Frame by ForwardTasks
      if (frameItem->status == MDR_HSRPRP_WaitForward)
      {
  MDR_LOG_Add_def(LOG_PROC_FORW);
  MDR_LOG_Add_def(frameItem->_frmIndex);
        
        MDR_HSRPRP_ProcessForwardingEx(&cfgRedBox->nodeCfg, frameItem, procHostReceiveFrame, procHostReceiveItem);			
      }
    }  
  
  }
  
  
#else
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

  
#endif


//---------------------		Timed Tasks	-----------------------
  
#if MDR_HSR_REDBOX_EN	  
  #define TO_NODE_CFG(cfg)     &((MDR_HSR_RedBoxCfg *)(cfg))->nodeCfg
#else  
  #define TO_NODE_CFG(cfg)     (MDR_HSR_NodeCfg *)(cfg)
#endif  

static bool MDR_HSR_ForgetDuplicateItems(void *cfg, uint32_t timeNow)
{
  MDR_HSR_NodeCfg *cfgNode = TO_NODE_CFG(cfg);
  
  if ((timeNow - cfgNode->lastTimeForgetDuplicate) > HSR_EntryForgetTime)
  {
    MDR_HSRPRP_Dupl_ProcessAgeing(timeNow, HSR_EntryForgetTime);
    cfgNode->lastTimeForgetDuplicate = timeNow;
    return true;
  }
  else
    return false;
}		

static bool MDR_HSR_TimedSendSuperFrame(void *cfg, uint32_t timeNow)
{
  MDR_HSR_NodeCfg *cfgNode = TO_NODE_CFG(cfg);
  
  if ((timeNow - cfgNode->lastTimeSuperSend) > HSR_LifeCheckInterval)
    if (MDR_HSR_SendSuperFrame(cfg))
    {
      cfgNode->lastTimeSuperSend = timeNow;
      return true;
    }
  return false;
}		

static bool MDR_HSR_ForgetNode(void *cfg, uint32_t timeNow)
{
  MDR_HSR_NodeCfg *cfgNode = TO_NODE_CFG(cfg);
  if ((timeNow - cfgNode->lastTimeForgetNode) > HSR_NodeForgetTime)
  {
    MDR_HSR_ProcessNodeForget(timeNow, HSR_NodeForgetTime);
    cfgNode->lastTimeForgetNode = timeNow;
    return true;
  }
  else
    return false;
}

static bool MDR_HSR_CheckSuperLostEx(void *cfg, uint32_t timeNow)
{
  MDR_HSR_NodeCfg *cfgNode = TO_NODE_CFG(cfg);
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

static bool MDR_HSR_CheckSuperLost(void *cfg, uint32_t timeNow)
{
  MDR_HSR_NodeCfg *cfgNode = TO_NODE_CFG(cfg);
  if (cfgNode->doCheckSupRx)
    return MDR_HSR_CheckSuperLostEx(cfgNode, timeNow);
  else
    return cfgNode->isRingClosed;
}

typedef bool(*pTimeTaskProc)(void *cfg, uint32_t timeNow);


#if MDR_HSR_REDBOX_EN	
  pTimeTaskProc _timeHandlers[] = { MDR_HSR_ForgetDuplicateItems, 
                                    MDR_HSR_TimedSendSuperFrame, 
                                    MDR_HSR_ForgetNode,
                                    MDR_HSR_CheckSuperLost,
                                    MDR_HSR_ForgetProxyNode
                                  };
  #define TIME_HANDLER_COUNT		sizeof(_timeHandlers)/sizeof(_timeHandlers[0])	  

  void MDR_HSR_ProcessNextTimedTask(MDR_HSR_RedBoxCfg *cfgRedBox, GetHostTimeProc getTime)
  {
    uint32_t taskInd = cfgRedBox->nodeCfg.lastTimeTaskInd;
    if (taskInd >= TIME_HANDLER_COUNT)
      taskInd = 0;
    
    _timeHandlers[taskInd](cfgRedBox, getTime());
    cfgRedBox->nodeCfg.lastTimeTaskInd = taskInd + 1;	
  }
  
  void MDR_HSR_ProcessAllTimedTasks(MDR_HSR_RedBoxCfg *cfgRedBox, GetHostTimeProc getTime)
  {
    MDR_HSR_ForgetDuplicateItems(cfgRedBox, getTime());
    MDR_HSR_TimedSendSuperFrame(cfgRedBox, getTime());
    MDR_HSR_ForgetNode(cfgRedBox, getTime());
    
    if (cfgRedBox->nodeCfg.doCheckSupRx)
      MDR_HSR_CheckSuperLostEx(cfgRedBox, getTime());
    

    MDR_HSR_ForgetProxyNode(cfgRedBox, getTime());
  }

#else
  pTimeTaskProc _timeHandlers[] = { MDR_HSR_ForgetDuplicateItems, 
                                      MDR_HSR_TimedSendSuperFrame, 
                                      MDR_HSR_ForgetNode,
                                      MDR_HSR_CheckSuperLost
                                    };
    #define TIME_HANDLER_COUNT		sizeof(_timeHandlers)/sizeof(_timeHandlers[0])	    
  
  void MDR_HSR_ProcessNextTimedTask(MDR_HSR_NodeCfg *cfgNode, GetHostTimeProc getTime)
  {
    uint32_t taskInd = cfgNode->lastTimeTaskInd;
    if (taskInd >= TIME_HANDLER_COUNT)
      taskInd = 0;
    
    _timeHandlers[taskInd](cfgNode, getTime());
    cfgNode->lastTimeTaskInd = taskInd + 1;	
  }
  
  void MDR_HSR_ProcessAllTimedTasks(MDR_HSR_NodeCfg *cfgNode, GetHostTimeProc getTime)
  {
    MDR_HSR_ForgetDuplicateItems(cfgNode, getTime());
    MDR_HSR_TimedSendSuperFrame(cfgNode, getTime());
    MDR_HSR_ForgetNode(cfgNode, getTime());
    
    if (cfgNode->doCheckSupRx)
      MDR_HSR_CheckSuperLostEx(cfgNode, getTime());
  }  
  
#endif	



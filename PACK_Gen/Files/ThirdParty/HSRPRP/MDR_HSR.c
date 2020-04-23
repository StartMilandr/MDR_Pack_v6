#include "MDR_HSR.h"
#include "MDR_HSRPRP_NodeTable.h"


//  ---------------  DANH forwarding from Interlink -----------------

void MDR_HSR_ForwBy802_1D(MDR_HSRPRP_FrameItem *frameItem)
{
//  TODO: bridge functionality (IEEE 802.1D) ???
  
//  The nodes support the IEEE 802.1D bridge functionality and forward frames from one port to
//  the other, according to four rules:
//  1) a node will not forward a frame that it injected into the ring or mesh;
//  2) a node will not forward a frame for which it is the unique destination (except for special
//     applications such as redundancy supervision);
//  3) a port will not send a frame that is a duplicate of a frame that it already sent into that
//     same direction;
//  4) a port will (optionally) refrain from sending a frame that is a duplicate of a frame that it
//     already received from the opposite direction (except for supervision and timing frames).  
  
//  frameItem->forwTasks.tagModifPortAB = MDR_HSRPRP_Tag_NoModif;
//  frameItem->forwTasks.selForwPort = MDR_HSRPRP_ForwPortA | MDR_HSRPRP_ForwPortB;
}

void MDR_HSR_DANH_ForwardFromHost(MDR_HSR_NodeCfg *cfgNode, MDR_HSRPRP_FrameItem *frameItem)
{   
  switch (cfgNode->forwMode) {
    // If the node is in Mode T
    case MDR_HSR_TranspForw: {
      //  do not modify the frame;
      //  duplicate the frame, enqueue it for sending into both HSR ports
      frameItem->forwTasks.tagModifPortAB = MDR_HSRPRP_Tag_NoModif;
      frameItem->forwTasks.selForwPort = MDR_HSRPRP_ForwPortA | MDR_HSRPRP_ForwPortB;
      break;
    }
    //  Else if the node is in Mode M
    case MDR_HSR_MixedForw: {
      //  If the local criteria is not met
      if (!cfgNode->hasLocalCriteria)
      {
        // insert the HSR tag and increment the sequence number depending on local criteria;
        // duplicate the frame, enqueue it for sending into both HSR ports
        frameItem->forwTasks.tagModifPortAB = MDR_HSRPRP_Tag_AddLocalHSR;
        frameItem->forwTasks.selForwPort = MDR_HSRPRP_ForwPortA | MDR_HSRPRP_ForwPortB;
      }  
      else
      {
        // do not insert the HSR tag;
        // process the frame according to IEEE 802.1D rules
        MDR_HSR_ForwBy802_1D(frameItem);
      }
      break;
    }
    //  Else
    default: {
      //  insert the HSR tag with the sequence number of the host;
      //  increment the sequence number, wrapping through 0;
      //  duplicate the frame, enqueue it for sending into both HSR ports
      frameItem->forwTasks.tagModifPortAB = MDR_HSRPRP_Tag_AddHSR;
      frameItem->forwTasks.selForwPort = MDR_HSRPRP_ForwPortA | MDR_HSRPRP_ForwPortB;
    }
  }
  
  if (frameItem->forwTasks.selForwPort == 0)
    MDR_HSRPRP_FreeFrameItem(frameItem);      //  Drop Frame
  else
    frameItem->status = MDR_HSRPRP_WaitForward;
}


//  ---------------  DANH forwarding from PORT A/B -----------------

bool MDR_HSR_IsFrame802_1D(MDR_HSRPRP_FrameItem *frameItem)
{

}

bool MDR_HSR_ProcessFrame802_1D(MDR_HSRPRP_FrameItem *frameItem)
{
  
}


bool MDR_HSR_IsMultyDestination(MDR_HSR_NodeCfg *cfgNode, MDR_HSRPRP_FrameItem *frameItem)
{
  // Unicast and Multicast traffic to host  
	  //Host is not only destination, Multicast/VLAN is ok
	//	todo
	
	//return false;
}


static bool MDR_HSR_SuperFrame_ProcessAndNeedForw(MDR_HSR_NodeCfg *cfgNode, MDR_HSRPRP_FrameItem *frameItem)
{	
  bool selfFrame = MDR_ETH_IsSameMACs(cfgNode->hostMAC, frameItem->framePtrs.pHeader->srcMAC);
	
	if (selfFrame)
	{
		// Это происходит дважды, два фрейма приходят с разных сторон кольца
		// - Нужен ли подсчет что оба фрейма вернулись?
		cfgNode->lastTimeSelfSuperRx = frameItem->timeRx;
		cfgNode->seqNumSupRx = ((MDR_HSR_SupHeader_DANH_t *)&frameItem->frameBuff[4])->supSeqNum;
	}
  else		
		MDR_HSR_AddNodeOrUpdate(frameItem);
		
	return !selfFrame;
}


static inline bool MDR_HSR_IsHostDestination(const MDR_HSR_NodeCfg *cfgNode, MDR_HSRPRP_FrameItem *frameItem)
{
  return MDR_ETH_IsSameMACs(cfgNode->hostMAC, frameItem->framePtrs.pHeader->destMAC);
}

static inline bool MDR_HSR_Host_HasNoDuplicate(MDR_HSRPRP_FrameItem *frameItem)
{
  return !MDR_HSRPRP_Dupl_HasItem(frameItem, &lreDuplTable_HOST);
}

static inline bool MDR_HSR_PortA_NoDuplicateSent(MDR_HSRPRP_FrameItem *frameItem)
{
  return !MDR_HSRPRP_Dupl_HasItem(frameItem, &lreDuplTable_PortA);
}

static inline bool MDR_HSR_PortB_NoDuplicateSent(MDR_HSRPRP_FrameItem *frameItem)
{
  return !MDR_HSRPRP_Dupl_HasItem(frameItem, &lreDuplTable_PortB);
}

static inline bool MDR_HSR_Interlink_NoDuplicateSent(MDR_HSRPRP_FrameItem *frameItem)
{
#if MDR_HSR_REDBOX_EN  
  return !MDR_HSRPRP_Dupl_HasItem(frameItem, &lreDuplTable_Interlink);
#else
  return false;
#endif
}



static inline bool MDR_HSR_PortsAB_HasNoDuplicate(MDR_HSRPRP_FrameItem *frameItem)
{
  return MDR_HSR_PortA_NoDuplicateSent(frameItem) && MDR_HSR_PortB_NoDuplicateSent(frameItem);
}

static void MDR_HSR_CheckAndForwToOtherPort(MDR_HSRPRP_FrameItem *frameItem, MDR_HSRPRP_TagModif tagModif)
{  
  frameItem->forwTasks.tagModifPortAB = tagModif;
  if (frameItem->frameSrc == MDR_HSRPRP_PortA)
  {
    if (MDR_HSR_PortA_NoDuplicateSent(frameItem))
      frameItem->forwTasks.selForwPort = MDR_HSRPRP_ForwPortB;
  }
  else if (frameItem->frameSrc == MDR_HSRPRP_PortB)
  {
    if (MDR_HSR_PortB_NoDuplicateSent(frameItem))
      frameItem->forwTasks.selForwPort = MDR_HSRPRP_ForwPortA;
  }
}



void MDR_HSR_DANH_ForwardFromPortAB(MDR_HSR_NodeCfg *cfgNode, MDR_HSRPRP_FrameItem *frameItem)
{ 
  uint32_t clrFrameSrc = ~(1 << frameItem->frameSrc);
  
//If this frame is not HSR-tagged:
  if (frameItem->framePtrs.frameType == MDR_HSRPRP_FrameEth)
  {
//  If the frame is a link local traffic (IEEE 802.1D Table 7-10) 
//    consume the frame and do not forward it.
    if (MDR_HSR_IsFrame802_1D(frameItem))
      MDR_HSR_ProcessFrame802_1D(frameItem);      
    
//  Else if the node is in Mode M    
//    forward according to 802.1D forwarding rules      
    else if (cfgNode->forwMode == MDR_HSR_MixedForw)
      MDR_HSR_ForwBy802_1D(frameItem);
    
//  Else if the node is in Mode T    
//    enqueue the unchanged frame for passing to its link layer interface.
//    enqueue the unmodified frame for sending over the second port.    
    else if (cfgNode->forwMode == MDR_HSR_TranspForw)
    {
      frameItem->forwTasks.tagModifPortAB = MDR_HSRPRP_Tag_NoModif;
      frameItem->forwTasks.tagModifHost   = MDR_HSRPRP_Tag_NoModif;
      frameItem->forwTasks.selForwPort = (MDR_HSRPRP_ForwPortA | MDR_HSRPRP_ForwPortB | MDR_HSRPRP_ForwHost) & clrFrameSrc;
    }
    else
//    enqueue the unchanged frame for passing to its link layer interface.
//    do not forward this frame
      frameItem->forwTasks.tagModifHost = MDR_HSRPRP_Tag_NoModif;
      frameItem->forwTasks.selForwPort = (MDR_HSRPRP_ForwHost);
  }
//Else (HSR-tagged frame):  
  else if (frameItem->framePtrs.frameType == MDR_HSRPRP_FrameHSR)
  {
//  If the node is in Mode T    
    if (cfgNode->forwMode == MDR_HSR_TranspForw)
    {
      // remove the HSR tag
      // send the modified frame over the second port
      // send the modified frame to its link layer interface
      frameItem->forwTasks.tagModifPortAB = MDR_HSRPRP_Tag_DelHSR;
      frameItem->forwTasks.tagModifHost   = MDR_HSRPRP_Tag_DelHSR;
      frameItem->forwTasks.selForwPort = (MDR_HSRPRP_ForwPortA | MDR_HSRPRP_ForwPortB | MDR_HSRPRP_ForwHost) & clrFrameSrc;
    }
//  Else (node is not in Mode T)    
    else
    {
//    If this node is a destination:
      bool isHostDestination  = MDR_HSR_IsHostDestination(cfgNode, frameItem);
      bool isMultyDestination = MDR_HSR_IsMultyDestination(cfgNode, frameItem);
      if (isHostDestination || isMultyDestination)
      {
//      If this is the first occurrence of the frame over the link layer interface:        
        if (MDR_HSR_Host_HasNoDuplicate(frameItem))
        {                                                 
//        remove the HSR tag and pass the modified frame to its link layer interface.
          frameItem->forwTasks.tagModifHost = MDR_HSRPRP_Tag_DelHSR;
          frameItem->forwTasks.selForwPort  = MDR_HSRPRP_ForwHost;
        }
//      Else (this is not the first occurrence of the frame over the link layer interface):        
//        do not pass the frame to the link layer interface.
      }
//    Else (if this node is not a destination): 
//      do not pass the frame to the link layer interface.
      
//    If this node is not the only destination or the node is in Mode U:
      if ((!isHostDestination) || (cfgNode->forwMode == MDR_HSR_UnicastForw))        
      {
//      If this is the first occurrence of the frame and the node is not in Mode N:
//        enqueue the unmodified frame for sending over the other port(s)        
//      Else (this is not the first occurrence of the frame):        
//        discard the frame.          
        
        if (cfgNode->forwMode != MDR_HSR_NoForw)
          MDR_HSR_CheckAndForwToOtherPort(frameItem, MDR_HSRPRP_Tag_NoModif);
      }
//    Else (If this node is not in Mode U and it is the unique destination):      
//      discard the frame.
    }  
  }
  else if  (frameItem->framePtrs.frameType == MDR_HSRPRP_FrameSupHSR)
  {
    if (MDR_HSR_SuperFrame_ProcessAndNeedForw(cfgNode, frameItem))
			MDR_HSR_CheckAndForwToOtherPort(frameItem, MDR_HSRPRP_Tag_NoModif);
  }
  
  //  Drop Frame if no task assigned
  if (frameItem->forwTasks.selForwPort == 0)
	{	
MDR_LOG_Add_def(LOG_DROP_RX);
MDR_LOG_Add_def(frameItem->_frmIndex);		
		
    MDR_HSRPRP_FreeFrameItem(frameItem);      
	}
  else
    frameItem->status = MDR_HSRPRP_WaitForward;
}


//==================================================================
//=========================   RedBox   =============================
//==================================================================

//  ---------------  RedBox forwarding from Interlink -----------------

static bool MDR_HSRPRP_ProxyHasMAC(MDR_HSRPRP_FrameItem *frameItem)
{
  return MDR_HSR_HasProxyNode(frameItem);
}

//static void MDR_HSRPRP_ProxyMacAdd(MDR_HSRPRP_FrameItem *frameItem)
//{
//  MDR_HSR_AddProxyNode(frameItem);
//}

bool MDR_HSR_RedBox_IsDestination(MDR_HSR_RedBoxCfg *cfgRedBox, MDR_HSRPRP_FrameItem *frameItem)
{
	return MDR_ETH_IsSameMACs(cfgRedBox->nodeCfg.hostMAC, frameItem->framePtrs.pHeader->destMAC);
}

bool MDR_HSR_RedBox_IsMultyDestination(MDR_HSR_RedBoxCfg *cfgRedBox, MDR_HSRPRP_FrameItem *frameItem)
{
  return MDR_HSR_IsMultyDestination(&cfgRedBox->nodeCfg, frameItem);
}



void MDR_HSR_RedBox_ForwardFromInterlink(MDR_HSR_RedBoxCfg *cfgRedBox, MDR_HSRPRP_FrameItem *frameItem)
{    
  //  MY: Superframe from external HSR Ring
  if ((frameItem->framePtrs.frameType == MDR_HSRPRP_FrameSupHSR) && (cfgRedBox->forwMode == MDR_HSR_RedBox_HSR_HSR))
  {
    MDR_HSR_AddProxyNodeOrUpdate(frameItem);
		
    frameItem->forwTasks.selForwPort = MDR_HSRPRP_Tag_NoModif;
    frameItem->forwTasks.selForwPort = MDR_HSRPRP_ForwPortA | MDR_HSRPRP_ForwPortB;
    return;
  }
  
//If the frame carries a HSR tag:  
  if (frameItem->framePtrs.frameType == MDR_HSRPRP_FrameHSR)
  {
//  If the node is in Mode T
    if (cfgRedBox->nodeCfg.forwMode == MDR_HSR_TranspForw)
    {
//    remove the HSR tag
//    enqueue the modified frame to the link layer interface of the RedBox
//    enqueue the modified frame into each HSR port
      frameItem->forwTasks.tagModifPortAB = MDR_HSRPRP_Tag_DelHSR;
      frameItem->forwTasks.tagModifHost   = MDR_HSRPRP_Tag_DelHSR;
      frameItem->forwTasks.selForwPort = MDR_HSRPRP_ForwPortA | MDR_HSRPRP_ForwPortB | MDR_HSRPRP_ForwHost;
    }
//  Else if the RedBox operates in HSR-HSR mode
    else if (cfgRedBox->forwMode == MDR_HSR_RedBox_HSR_HSR)
    {
//    If the RedBox is a destination of the frame
      bool isHostDestination = MDR_HSR_RedBox_IsDestination(cfgRedBox, frameItem);
      bool isMultyDestination = MDR_HSR_RedBox_IsMultyDestination(cfgRedBox, frameItem);
      if (isHostDestination || isMultyDestination)
      {  
//      If this is not the first occurrence of the frame at the link layer interface
//        discard the frame
//      Else (If this is the first occurrence of the frame at the link layer interface)
//        remove the HSR tag
//        enqueue to the link layer interface of the RedBox
        if (MDR_HSR_Host_HasNoDuplicate(frameItem))
        {
          frameItem->forwTasks.tagModifHost = MDR_HSRPRP_Tag_DelHSR;
          frameItem->forwTasks.selForwPort  = MDR_HSRPRP_ForwHost;
        }
      }
      
//    If the frame is to be injected into the ring (RedBox is not only destination, Multicast/VLAN is ok)
      if (!isHostDestination || isMultyDestination)
      {  
//      If this is not the first occurrence of the frame
//        discard the frame (already sent over that port)
//      Else (If this is the first occurrence of the frame)
//        enqueue the unmodified frame into each HSR port
        if (MDR_HSR_PortsAB_HasNoDuplicate(frameItem))
        {
          frameItem->forwTasks.tagModifPortAB = MDR_HSRPRP_Tag_DelHSR;
          frameItem->forwTasks.selForwPort = MDR_HSRPRP_ForwPortA | MDR_HSRPRP_ForwPortB;
        }
      }
    }
//  Else (If the RedBox does not operate in HSR-HSR mode)
//   discard the frame
  }
//Else if the frame carries a PRP RCT and the RedBox is in HSR-PRP mode  
  else if ((cfgRedBox->forwMode == MDR_HSR_RedBox_HSR_PRP) && ((frameItem->framePtrs.frameType == MDR_HSRPRP_FramePRP) || (frameItem->framePtrs.frameType == MDR_HSRPRP_FrameSupPRP)))
  {
//  If the node is in Mode T
    if (cfgRedBox->nodeCfg.forwMode == MDR_HSR_TranspForw)
    {
//    remove the PRP RCT
//    enqueue the modified frame to the link layer interface of the RedBox
//    enqueue the modified frame into each HSR port       
      frameItem->forwTasks.tagModifPortAB = MDR_HSRPRP_Tag_DelPRP;
      frameItem->forwTasks.tagModifHost   = MDR_HSRPRP_Tag_DelPRP;
      frameItem->forwTasks.selForwPort = MDR_HSRPRP_ForwPortA | MDR_HSRPRP_ForwPortB | MDR_HSRPRP_ForwHost;
    }
//  Else (No HSR tag)
    else
    {
//    If the source MAC address is not already registered:      
//      create an entry in the ProxyNodeTable;
			MDR_HSR_AddProxyNodeOrUpdate(frameItem);
//      if (!MDR_HSRPRP_ProxyHasMAC(frameItem))
//        MDR_HSRPRP_ProxyMacAdd(frameItem);
      
//    If the PRP tag does not correspond to the LanId of the RedBox “A” or “B”
//      increment the error counter lreCntWrongLanIdC;
      if (cfgRedBox->lanID != frameItem->framePtrs.lanID)
        MDR_HSR_LogError(MDR_HSR_Err_WrongLanID, frameItem->frameSrc);
      
//    If the RedBox is a destination of the frame
      bool isHostDestination = MDR_HSR_RedBox_IsDestination(cfgRedBox, frameItem);
      bool isMultyDestination = MDR_HSR_RedBox_IsMultyDestination(cfgRedBox, frameItem);
      if (isHostDestination || isMultyDestination)
      {
//      If this is not the first occurrence of the frame at the link layer interface
//        discard the frame
//      Else
//        enqueue to the link layer interface of the RedBox (with the PRP RCT)                
        if (MDR_HSR_Host_HasNoDuplicate(frameItem))
        {
          frameItem->forwTasks.tagModifHost   = MDR_HSRPRP_Tag_NoModif;
          frameItem->forwTasks.selForwPort = MDR_HSRPRP_ForwHost;
        }
      }
      
//    If the frame is to be injected into the ring (RedBox is not sole destination and multicast/VLAN is ok)
      if (!isHostDestination && isMultyDestination)
      {
//      If this is not the first occurrence of the frame at each HSR port
//        discard the frame (already sent over that port)
//      Else (If this is the first occurrence of the frame at each HSR port)
//        reuse the PRP sequence number and the RedBox’s path identifier to build the HSR tag
//        enqueue the frame into each HSR port
        
        if (MDR_HSR_PortsAB_HasNoDuplicate(frameItem))
        {
          frameItem->forwTasks.tagModifPortAB   = MDR_HSRPRP_Tag_PRPtoHSR;
          frameItem->forwTasks.selForwPort = MDR_HSRPRP_ForwPortA | MDR_HSRPRP_ForwPortB;
        }
      }
    }
  }
//Else (if the frame carries neither a HSR tag nor a PRP RCT)
  else
  {
//  If the node is in Mode T
    if (cfgRedBox->nodeCfg.forwMode == MDR_HSR_TranspForw)
    {
//    enqueue the unmodified frame to the link layer interface of the RedBox
//    enqueue the unmodified frame into each HSR port     
      frameItem->forwTasks.tagModifPortAB = MDR_HSRPRP_Tag_NoModif;
      frameItem->forwTasks.tagModifHost   = MDR_HSRPRP_Tag_NoModif;
      frameItem->forwTasks.selForwPort = MDR_HSRPRP_ForwPortA | MDR_HSRPRP_ForwPortB | MDR_HSRPRP_ForwHost;
    }
//  Else if the node is in Mode M
    else if (cfgRedBox->nodeCfg.forwMode == MDR_HSR_MixedForw)
    {
//    forward according to 802.1D forwarding rules
      MDR_HSR_ForwBy802_1D(frameItem);
    }
//  Else
    else
    {
//    If the source MAC address is not already registered in the ProxyNodeTable:
//      create an entry in the ProxyNodeTable;
//    Else (If the source is already registered)
//      (void)
			MDR_HSR_AddProxyNodeOrUpdate(frameItem);

//    If the RedBox is a destination of the frame:
//      enqueue to the link layer interface of the RedBox
      bool isHostDestination = MDR_HSR_RedBox_IsDestination(cfgRedBox, frameItem);
      bool isMultyDestination = MDR_HSR_RedBox_IsMultyDestination(cfgRedBox, frameItem);
      if (isHostDestination || isMultyDestination)
      {
        frameItem->forwTasks.tagModifHost = MDR_HSRPRP_Tag_NoModif;
        frameItem->forwTasks.selForwPort  = MDR_HSRPRP_ForwHost;
      }
      
//    If the frame is to be injected into the ring (RedBox is not sole destination and multicast/VLAN is ok))
//      append the HSR tag using the sequence number of that node
//      increment the sequence number of that source;
//      enqueue the tagged frame into each HSR port      
      if (!isHostDestination && isMultyDestination)
      {
        frameItem->forwTasks.tagModifHost = MDR_HSRPRP_Tag_AddHSR;
        frameItem->forwTasks.selForwPort  = MDR_HSRPRP_ForwPortA | MDR_HSRPRP_ForwPortB;
      }
    }
  }

  if (frameItem->forwTasks.selForwPort == 0)
    MDR_HSRPRP_FreeFrameItem(frameItem);      //  Drop Frame
  else
    frameItem->status = MDR_HSRPRP_WaitForward;
}



//  ---------------  RedBox forwarding from PortA or B -----------------

void MDR_HSR_RedBox_ForwardFromPortAB(MDR_HSR_RedBoxCfg *cfgRedBox, MDR_HSRPRP_FrameItem *frameItem)
{ 
  uint32_t clrFrameSrc = ~(1 << frameItem->frameSrc);
  
//Else (frame is HSR-tagged):
  if (frameItem->framePtrs.frameType == MDR_HSRPRP_FrameHSR)
  {
//  If the node is in Mode T
    if (cfgRedBox->nodeCfg.forwMode == MDR_HSR_TranspForw)
    {
//    remove the HSR tag
//    send the modified frame over the second port
//    send the modified frame to its link layer interface
      frameItem->forwTasks.tagModifPortAB = MDR_HSRPRP_Tag_DelHSR;
      frameItem->forwTasks.tagModifHost   = MDR_HSRPRP_Tag_DelHSR;
      frameItem->forwTasks.selForwPort = (MDR_HSRPRP_ForwPortA | MDR_HSRPRP_ForwPortB | MDR_HSRPRP_ForwHost) & clrFrameSrc;      
    }
//  Else
    else
    {
//    If this node is a destination:
      bool isHostDestination = MDR_HSR_RedBox_IsDestination(cfgRedBox, frameItem);
      bool isMultyDestination = MDR_HSR_RedBox_IsMultyDestination(cfgRedBox, frameItem);
      if (isHostDestination || isMultyDestination)
      {
//      If this is the first occurrence of the frame over the link layer interface:
//        remove the HSR tag and pass the modified frame to its link layer interface.
//      Else (this is not the first occurrence of the frame over the link layer interface):
//        do not pass the frame to the link layer interface.
        if (MDR_HSR_Host_HasNoDuplicate(frameItem))
        {
          frameItem->forwTasks.tagModifHost = MDR_HSRPRP_Tag_DelHSR;
          frameItem->forwTasks.selForwPort  = MDR_HSRPRP_ForwHost;
        }
      }
//    Else (if this node is not a destination):
//      do not pass the frame to the link layer interface.
      
//    If this node is not the unique destination or the node is in Mode U:
      if (!isHostDestination || (cfgRedBox->nodeCfg.forwMode == MDR_HSR_UnicastForw))
      {
//      If this is the first occurrence of the frame and the node is not in Mode N:
//        enqueue the unmodified frame for sending over the other port(s).
        if (MDR_HSR_PortsAB_HasNoDuplicate(frameItem) && (cfgRedBox->nodeCfg.forwMode != MDR_HSR_NoForw) )
        {
          frameItem->forwTasks.tagModifPortAB = MDR_HSRPRP_Tag_DelHSR;
          frameItem->forwTasks.selForwPort = (MDR_HSRPRP_ForwPortA | MDR_HSRPRP_ForwPortB) & clrFrameSrc;
        }
//      Else (this is not the first occurrence of the frame or the node is in Mode N):
//        do not enqueue the unchanged frame to the second HSR port.
                
//      If this is the first occurrence of the frame in direction of the interlink:
        if (MDR_HSR_Interlink_NoDuplicateSent(frameItem))
        {
//        If the RedBox is in SAN mode:        
          if (cfgRedBox->forwMode == MDR_HSR_RedBox_HSR_SAN)
          {
//          remove the HSR tag;
//          If Source in the ProxyNodeTable
//            discard the frame
//          Else
//            enqueue frame for passing to the interlink.
            if (MDR_HSRPRP_ProxyHasMAC(frameItem))
            {
              frameItem->forwTasks.tagModifInterlink = MDR_HSRPRP_Tag_DelHSR;
              frameItem->forwTasks.selForwPort = MDR_HSRPRP_ForwInterlink;
            }
          }          
//        Else if the RedBox is in PRP mode:
          else if (cfgRedBox->forwMode == MDR_HSR_RedBox_HSR_PRP)
          {
//          If the netId matches that of the RedBox
//            discard the frame
//          Else
//            remove the HSR tag and append the PRP RCT with LanId (“A” or “B”) of the RedBox and reusing the HSR sequence number.
//            enqueue frame for passing to the interlink.
            if (cfgRedBox->lanID != frameItem->framePtrs.lanID)
            {
              frameItem->forwTasks.tagModifInterlink = MDR_HSRPRP_Tag_HSRtoPRP;
              frameItem->forwTasks.selForwPort = MDR_HSRPRP_ForwInterlink;
            }
          }
//        Else (if the RedBox is in HSR mode)
          else
          {
//          do not modify the frame.
//          enqueue frame for passing to the interlink.
            frameItem->forwTasks.tagModifInterlink = MDR_HSRPRP_Tag_NoModif;
            frameItem->forwTasks.selForwPort = MDR_HSRPRP_ForwInterlink;
          }
        }
//      Else (If this is not the first occurrence of the frame in direction of the interlink):
//        discard the frame
      }
//    Else (If this node is the only (unicast) destination) and the node is not in Mode U:
//      discard the frame.
   }
 }
 else if (frameItem->framePtrs.frameType == MDR_HSRPRP_FrameSupHSR) 
 {
	  if (MDR_HSR_SuperFrame_ProcessAndNeedForw(&cfgRedBox->nodeCfg, frameItem))
      MDR_HSR_CheckAndForwToOtherPort(frameItem, MDR_HSRPRP_Tag_NoModif);   
 }
 //If this frame is not HSR-tagged:
 else  
  //if (frameItem->framePtrs.frameType != MDR_HSRPRP_FrameHSR)
  {
//  If the frame is a link local traffic (IEEE 802.1D Table 7-10)
    if (MDR_HSR_IsFrame802_1D(frameItem))
//    consume the frame and do not forward it.
      MDR_HSR_ProcessFrame802_1D(frameItem);        
//  Else if the node is in Mode M
    else if (cfgRedBox->nodeCfg.forwMode == MDR_HSR_MixedForw)
    {
//    enqueue the unchanged frame for passing to the interlink.      
      frameItem->forwTasks.tagModifInterlink = MDR_HSRPRP_Tag_NoModif;
      frameItem->forwTasks.selForwPort  = MDR_HSRPRP_ForwInterlink;
//    forward according to 802.1D forwarding rules
      MDR_HSR_ForwBy802_1D(frameItem);
    }
//  Else if the node is in Mode T
    else if (cfgRedBox->nodeCfg.forwMode == MDR_HSR_TranspForw)
    {
//    enqueue the unchanged frame for passing to its link layer interface.
//    enqueue the unmodified frame for sending over the second port.      
      frameItem->forwTasks.tagModifPortAB = MDR_HSRPRP_Tag_NoModif;
      frameItem->forwTasks.tagModifHost   = MDR_HSRPRP_Tag_NoModif;
      frameItem->forwTasks.selForwPort = (MDR_HSRPRP_ForwPortA | MDR_HSRPRP_ForwPortB | MDR_HSRPRP_ForwHost) & clrFrameSrc;
    }
//  Else
    else
    {
//    enqueue the unchanged frame for passing to its link layer interface.
//    do not forward this frame
      frameItem->forwTasks.tagModifHost = MDR_HSRPRP_Tag_NoModif;
      frameItem->forwTasks.selForwPort  = MDR_HSRPRP_ForwHost;
    }
  }
  
  if (frameItem->forwTasks.selForwPort == 0)
    MDR_HSRPRP_FreeFrameItem(frameItem);      //  Drop Frame
  else
    frameItem->status = MDR_HSRPRP_WaitForward;  
}


//  ---------------  RedBox forwarding from Host (Link Interface) -----------------

void MDR_HSR_RedBox_ForwardFromHost(MDR_HSR_RedBoxCfg *cfgRedBox, MDR_HSRPRP_FrameItem *frameItem)
{
//If the node is in Mode T
  if (cfgRedBox->nodeCfg.forwMode == MDR_HSR_TranspForw)
  {
//  do not modify the frame;
//  duplicate the frame, enqueue it for sending into both HSR ports
    frameItem->forwTasks.tagModifPortAB = MDR_HSRPRP_Tag_NoModif;
    frameItem->forwTasks.selForwPort = MDR_HSRPRP_ForwPortA | MDR_HSRPRP_ForwPortB;
  }
//Else If the node is in Mode M
  else if (cfgRedBox->nodeCfg.forwMode == MDR_HSR_MixedForw)
  {    
//  insert the HSR tag and increment the sequence number depending on local criteria
//  forward depending on local criteria
    frameItem->forwTasks.tagModifPortAB = MDR_HSRPRP_Tag_AddLocalHSR;
    frameItem->forwTasks.selForwPort = MDR_HSRPRP_ForwPortA | MDR_HSRPRP_ForwPortB;
  }
//Else
  else
  {
//  If the RedBox is in SAN mode:
    if (cfgRedBox->nodeCfg.forwMode == MDR_HSR_RedBox_HSR_SAN)
    {
//    enqueue frame for passing to the interlink.
      frameItem->forwTasks.tagModifInterlink = MDR_HSRPRP_Tag_NoModif;
      frameItem->forwTasks.selForwPort = MDR_HSRPRP_ForwInterlink;
    }
//  Else If the RedBox is in PRP mode:
    else if (cfgRedBox->nodeCfg.forwMode == MDR_HSR_RedBox_HSR_PRP)
    {
//    insert the PRP RCT with the sequence number of the host;
//    enqueue frame for passing to the interlink.
      frameItem->forwTasks.tagModifInterlink = MDR_HSRPRP_Tag_AddPRP;
      frameItem->forwTasks.selForwPort = MDR_HSRPRP_ForwInterlink;
    }
//  Else (if the RedBox is in HSR mode)
    else
    {
//    insert the HSR tag with the sequence number of the host;
//    enqueue frame for passing to the interlink.
      frameItem->forwTasks.tagModifInterlink = MDR_HSRPRP_Tag_AddHSR;
      frameItem->forwTasks.selForwPort = MDR_HSRPRP_ForwInterlink;
    }
    
    //duplicate the frame, enqueue it for sending into both HSR ports
    frameItem->forwTasks.tagModifPortAB = MDR_HSRPRP_Tag_AddHSR;
    frameItem->forwTasks.selForwPort = MDR_HSRPRP_ForwPortA | MDR_HSRPRP_ForwPortB;
  }
  
  if (frameItem->forwTasks.selForwPort == 0)
    MDR_HSRPRP_FreeFrameItem(frameItem);      //  Drop Frame
  else
    frameItem->status = MDR_HSRPRP_WaitForward;   
}



//=====================			Assign ForwardingTasks	=============
void MDR_HSR_DANH_AssignForwardTasks(MDR_HSR_NodeCfg *cfgNode, MDR_HSRPRP_FrameItem *frameItem)
{
	if (frameItem->frameSrc  == MDR_HSRPRP_Host)
		MDR_HSR_DANH_ForwardFromHost(cfgNode, frameItem);
	else if (frameItem->frameSrc  < MDR_HSRPRP_Host)
		MDR_HSR_DANH_ForwardFromPortAB(cfgNode, frameItem);
	else
	{
		MDR_HSR_LogError(MDR_HSR_Err_UnkFrameSrc_DANH, frameItem->frameSrc);
		MDR_HSRPRP_FreeFrameItem(frameItem);
	}
}

void MDR_HSR_Redbox_AssignForwardTasks(MDR_HSR_RedBoxCfg *cfgRedBox, MDR_HSRPRP_FrameItem *frameItem)
{
	switch (frameItem->frameSrc) 	{
		case MDR_HSRPRP_Host: 
			MDR_HSR_RedBox_ForwardFromHost(cfgRedBox, frameItem); 
			break;
		case MDR_HSRPRP_PortA:
		case MDR_HSRPRP_PortB:
			MDR_HSR_RedBox_ForwardFromPortAB(cfgRedBox, frameItem); 
			break;			
		case MDR_HSRPRP_Interlink:
			MDR_HSR_RedBox_ForwardFromInterlink(cfgRedBox, frameItem); 
		default:
			{
				MDR_HSR_LogError(MDR_HSR_Err_UnkFrameSrc_RedBox, frameItem->frameSrc);
				MDR_HSRPRP_FreeFrameItem(frameItem);
			}	
	}	
}



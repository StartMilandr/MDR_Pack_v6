#include "MDR_HSRPRP_TX.h"
#include "MDR_HSRPRP_Config.h"
#include "MDR_HSRPRP_DuplicateTables.h"
#include <MDR_Ethernet_FrameDefs.h>
#include "MDR_HSR_defs.h"
#include <string.h>

//  FrameBuff for transfer
static MDR_ETH_FrameTX _frameTX    __attribute__((section("EXECUTABLE_MEMORY_SECTION"))) __attribute__ ((aligned (4)));


//  Frame Modify handlers
static void Modif_No(MDR_HSR_NodeCfg *cfgNode, MDR_HSRPRP_FrameItem *frameItem, MDR_ETH_FrameTX *pFrameTX);
static void Modif_AddTagHSR(MDR_HSR_NodeCfg *cfgNode, MDR_HSRPRP_FrameItem *frameItem, MDR_ETH_FrameTX *pFrameTX);
static void Modif_DelTagHSR(MDR_HSR_NodeCfg *cfgNode, MDR_HSRPRP_FrameItem *frameItem, MDR_ETH_FrameTX *pFrameTX);
static void Modif_AddTagPRP(MDR_HSR_NodeCfg *cfgNode, MDR_HSRPRP_FrameItem *frameItem, MDR_ETH_FrameTX *pFrameTX);
static void Modif_DelTagPRP(MDR_HSR_NodeCfg *cfgNode, MDR_HSRPRP_FrameItem *frameItem, MDR_ETH_FrameTX *pFrameTX);
static void Modif_HSRtoPRP(MDR_HSR_NodeCfg *cfgNode, MDR_HSRPRP_FrameItem *frameItem, MDR_ETH_FrameTX *pFrameTX);
static void Modif_PRPtoHSR(MDR_HSR_NodeCfg *cfgNode, MDR_HSRPRP_FrameItem *frameItem, MDR_ETH_FrameTX *pFrameTX);
static void Modif_AddLocalHSR(MDR_HSR_NodeCfg *cfgNode, MDR_HSRPRP_FrameItem *frameItem, MDR_ETH_FrameTX *pFrameTX);

typedef void(*pModifyHandler)(MDR_HSR_NodeCfg *cfgNode, MDR_HSRPRP_FrameItem *frameItem, MDR_ETH_FrameTX *pFrameTX);
static pModifyHandler _ModifyHandlers[_MDR_HSRPRP_TagModifLen] = 
  { Modif_No, Modif_AddTagHSR, Modif_DelTagHSR, Modif_AddTagPRP, Modif_DelTagPRP, Modif_HSRtoPRP, Modif_PRPtoHSR, Modif_AddLocalHSR};


//	funcs
//static bool MDR_HSRPRP_CheckAlreadySend(MDR_HSRPRP_FrameItem *frameItem, MDR_HSRPRP_FramePort portForw);	
	
	
//====================	Forwarding (Посылка фреймов по назначению) =============

static bool   _canSingleIncSeqNum = false;
static inline void IncSeqNum(MDR_HSR_NodeCfg *cfgNode)
{
  if (_canSingleIncSeqNum)
	{
	  cfgNode->seqNum += 1;
		_canSingleIncSeqNum = false;
	}
}

void MDR_HSRPRP_ProcessForwardingEx(MDR_HSR_NodeCfg *cfgNode, MDR_HSRPRP_FrameItem *frameItem, 
	pHostReceiveFrame_CallBack procHostReceiveFrame,
  pHostReceiveItem_CallBack procHostReceiveItem)
{
  MDR_ETH_FrameTX *pFrameTX = &_frameTX;
  MDR_HSRPRP_TagModif activeTagModif = _MDR_HSRPRP_TagModifLen; //  Not Valid value
  
	//	Разрешение на единственный инкремент cfgNode->seqNum, если потребуется вставка HSR tag
	_canSingleIncSeqNum = true;
	
  //  Forward to Host
  if ((frameItem->forwTasks.selForwPort & MDR_HSRPRP_ForwHost) != 0)
  {
    if (procHostReceiveItem != NULL)
		{
MDR_LOG_Add_def(LOG_ADD_DUPL_H);
MDR_LOG_Add_def(frameItem->_frmIndex);					
			
      procHostReceiveItem(frameItem);
			MDR_HSRPRP_Dupl_AddItem(frameItem, &lreDuplTable_HOST);
		}
    else if (procHostReceiveFrame != NULL)
    {
      if (activeTagModif != frameItem->forwTasks.tagModifHost)
      {
        activeTagModif = frameItem->forwTasks.tagModifHost;
        _ModifyHandlers[activeTagModif](cfgNode, frameItem, pFrameTX);    
      }
MDR_LOG_Add_def(LOG_ADD_DUPL_H);
MDR_LOG_Add_def(frameItem->_frmIndex);					      
			
      procHostReceiveFrame((MDR_ETH_FrameRX *)(pFrameTX));
			MDR_HSRPRP_Dupl_AddItem(frameItem, &lreDuplTable_HOST);
    }    
  }
  
  //  Forward to Ports
  bool forwToA = (frameItem->forwTasks.selForwPort & MDR_HSRPRP_ForwPortA) != 0;
//  if (forwToA)
//    forwToA = !MDR_HSRPRP_CheckAlreadySend(frameItem, MDR_HSRPRP_PortA);
  bool forwToB = (frameItem->forwTasks.selForwPort & MDR_HSRPRP_ForwPortB) != 0;
//  if (forwToB)
//    forwToB = !MDR_HSRPRP_CheckAlreadySend(frameItem, MDR_HSRPRP_PortB);      
  
  if (forwToA || forwToB)
  {
    if (activeTagModif != frameItem->forwTasks.tagModifPortAB)
    {
      activeTagModif = frameItem->forwTasks.tagModifPortAB;
      _ModifyHandlers[activeTagModif](cfgNode, frameItem, pFrameTX);    
    }
    if (forwToA)
		{
MDR_LOG_Add_def(LOG_ADD_DUPL_A);
MDR_LOG_Add_def(frameItem->_frmIndex);					
			
      MDR_ETH_TrySendFrame(ETH_PortA, pFrameTX);
			MDR_HSRPRP_Dupl_AddItem(frameItem, &lreDuplTable_PortA);
		}
    if (forwToB)
		{
MDR_LOG_Add_def(LOG_ADD_DUPL_B);
MDR_LOG_Add_def(frameItem->_frmIndex);					
			
      MDR_ETH_TrySendFrame(ETH_PortB, pFrameTX);
			MDR_HSRPRP_Dupl_AddItem(frameItem, &lreDuplTable_PortB);			
		}
  }

#if MDR_HSR_REDBOX_EN
  //  Forward to Interlink
  bool forwToInterlink = (frameItem->forwTasks.selForwPort & MDR_HSRPRP_ForwInterlink) != 0;
  if (forwToInterlink)
  {
    forwToInterlink = !MDR_HSRPRP_CheckAlreadySend(frameItem, MDR_HSRPRP_Interlink);
    if (forwToInterlink)
    {
      if (activeTagModif != frameItem->forwTasks.tagModifInterlink)
      {
        activeTagModif = frameItem->forwTasks.tagModifInterlink;
        _ModifyHandlers[activeTagModif](cfgNode, frameItem, pFrameTX);    
      }      
      MDR_ETH_TrySendFrame(ETH_PortInterlink, pFrameTX);  
    }
  }
#endif
  
  MDR_HSRPRP_FreeFrameItem(frameItem);
}




// =======================		 Frame Modify handlers	============================
static void Modif_No(MDR_HSR_NodeCfg *cfgNode, MDR_HSRPRP_FrameItem *frameItem, MDR_ETH_FrameTX *pFrameTX)
{
	MDR_HSRPRP_FramePtrs *frmPtrs = &frameItem->framePtrs;
	
	pFrameTX->frameLen = frmPtrs->lenHeader + frmPtrs->lenTag + frmPtrs->lenPayload;
	//	Header
	memcpy(pFrameTX->frame, frmPtrs->pHeader->destMAC, frmPtrs->lenHeader);
	uint32_t indWR = frmPtrs->lenHeader;
	//	Tag
	if (frmPtrs->lenTag > 0) {
		memcpy(&pFrameTX->frame[indWR], frmPtrs->pTag, frmPtrs->lenTag);
		indWR += frmPtrs->lenTag;
	}
	//	Payload
	memcpy(&pFrameTX->frame[indWR], frmPtrs->pPayload, frmPtrs->lenPayload);
}

static void Modif_AddTagHSR(MDR_HSR_NodeCfg *cfgNode, MDR_HSRPRP_FrameItem *frameItem, MDR_ETH_FrameTX *pFrameTX)
{
	MDR_HSRPRP_FramePtrs *frmPtrs = &frameItem->framePtrs;
	
	pFrameTX->frameLen = frmPtrs->lenHeader + MDR_HSR_TAG_LEN + frmPtrs->lenPayload;
	//	Copy Only MACs
	memcpy(pFrameTX->frame, frmPtrs->pHeader->destMAC, frmPtrs->lenHeader);
	uint32_t indWR = frmPtrs->lenHeader;
	
	//	Add Tag	HSR
	MDR_HSR_Tag_t *tagHSR = (MDR_HSR_Tag_t *)&pFrameTX->frame[indWR];
	
	tagHSR->etherType = ETH_TYPE_HSR;
	tagHSR->lanID_LSDUSize = htons(FILL_LanID_LSDUSize(cfgNode->lanID, MDR_HSR_TAG_LSDU_LEN + frmPtrs->lenPayload));
	IncSeqNum(cfgNode);
	tagHSR->seqNum = htons(cfgNode->seqNum);	
	
	indWR += MDR_HSR_TAG_LEN;
	
	//	Payload
	memcpy(&pFrameTX->frame[indWR], frmPtrs->pPayload, frmPtrs->lenPayload);  
}

static void Modif_DelTagHSR(MDR_HSR_NodeCfg *cfgNode, MDR_HSRPRP_FrameItem *frameItem, MDR_ETH_FrameTX *pFrameTX)
{
	MDR_HSRPRP_FramePtrs *frmPtrs = &frameItem->framePtrs;

//  if (frmPtrs->frameType != MDR_HSRPRP_FrameSupHSR)
	{	
		pFrameTX->frameLen = frmPtrs->lenHeader + frmPtrs->lenPayload;
		//	Header
		memcpy(pFrameTX->frame, frmPtrs->pHeader->destMAC, frmPtrs->lenHeader);
		//	Payload
		memcpy(&pFrameTX->frame[frmPtrs->lenHeader], frmPtrs->pPayload, frmPtrs->lenPayload);	
	}
}

static void Modif_AddTagPRP(MDR_HSR_NodeCfg *cfgNode, MDR_HSRPRP_FrameItem *frameItem, MDR_ETH_FrameTX *pFrameTX)
{
  
}

static void Modif_DelTagPRP(MDR_HSR_NodeCfg *cfgNode, MDR_HSRPRP_FrameItem *frameItem, MDR_ETH_FrameTX *pFrameTX)
{
  
}

static void Modif_HSRtoPRP(MDR_HSR_NodeCfg *cfgNode, MDR_HSRPRP_FrameItem *frameItem, MDR_ETH_FrameTX *pFrameTX)
{
  
}

static void Modif_PRPtoHSR(MDR_HSR_NodeCfg *cfgNode, MDR_HSRPRP_FrameItem *frameItem, MDR_ETH_FrameTX *pFrameTX)
{
  
}

static void Modif_AddLocalHSR(MDR_HSR_NodeCfg *cfgNode, MDR_HSRPRP_FrameItem *frameItem, MDR_ETH_FrameTX *pFrameTX)
{
	// НЕ понятно что такое "локальные условия", поэтому посылаем пока как обычно
  Modif_AddTagHSR(cfgNode, frameItem, pFrameTX);
}


//static bool MDR_HSRPRP_CheckAlreadySend(MDR_HSRPRP_FrameItem *frameItem, MDR_HSRPRP_FramePort portForw)
//{
//  //  ToDO
//}


//=================		SuperFrame Send	================
static MDR_HSR_SupHeader_RedBox_t  _suHeader __attribute__ ((aligned (4))) = {
  .multyMAC 		= ETH_HSR_SUP_DEST_MAC_INIT,
  .nodeMAC 			= {0, 0, 0, 0, 0, 0},
  .tagHSR 			= {},
  .supEtherType = ETH_HSR_SUP_ETHER_TYPE,
  .supPath_Vers = htons(ETH_PRP_SUP_PATH_VERSION),
  .supSeqNum 		= 0,
  .TLV1 				= htons(MDR_HSR_SupHdr_TLV1),             // const 0x2300: type = 23, len = 6
  .DANP_MAC 		= {0, 0, 0, 0, 0, 0, },
  .TLV2 				= htons(MDR_HSR_SupHdr_TLV2_Empty),       // for RedBox const 0x3000: type = 30, len = 6
  .RedBoxMAC 		= {0, 0, 0, 0, 0, 0, },
  .TLV3 				= htons(MDR_HSR_SupHdr_TLV3),             // const 0x0000: type = 0,  len = 0
//  .pad_to74[] = NULL,                      			 // fill to 74 bytes frameLen
};

MDR_HSR_NodeCfg * _suHeaderOwner = NULL;


#if MDR_HSR_REDBOX_EN

#else
	bool MDR_HSR_SendSuperFrame(MDR_HSR_NodeCfg *cfgNode)
	{	
		//	Capture global _suHeader by cfgNode as MDR_HSR_SupHeader_DANH_t	
		if (_suHeaderOwner != cfgNode)
		{
			_suHeaderOwner = cfgNode;
			
			MDR_ETH_CopyMAC((uint8_t *)&_suHeader.nodeMAC,  (uint8_t *)cfgNode->hostMAC);
			MDR_ETH_CopyMAC((uint8_t *)&_suHeader.DANP_MAC, (uint8_t *)cfgNode->hostMAC);
			((MDR_HSR_SupHeader_DANH_t *)&_suHeader)->TLV3 = MDR_HSR_SupHdr_TLV3;
			
			_suHeader.tagHSR.etherType = ETH_TYPE_HSR;
			_suHeader.tagHSR.lanID_LSDUSize = htons(FILL_LanID_LSDUSize(cfgNode->lanID, MDR_HSR_SUPER_DANH_LSDU_LEN));
		}
		
		//	Update HSR tags
		cfgNode->seqNum++;
		cfgNode->seqNumSup++;		
		_suHeader.tagHSR.seqNum = htons(cfgNode->seqNum);
		_suHeader.supSeqNum = htons(cfgNode->seqNumSup);		
		cfgNode->doCheckSupRx = true;
		
		//	Copy to FrameTx
		memcpy(_frameTX.frame, &_suHeader, MDR_HSR_SUPER_DANH_FRAME_LEN);  
		_frameTX.frameLen = MDR_HSR_SUPER_DANH_FRAME_LEN;
		
		bool okTx = MDR_ETH_TrySendFrame(ETH_PortA, &_frameTX);
		if (okTx)
			okTx = MDR_ETH_TrySendFrame(ETH_PortB, &_frameTX);
		return okTx;
	}
#endif

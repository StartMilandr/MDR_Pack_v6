#ifndef _MDR_HSR_H
#define _MDR_HSR_H

#include "MDR_HSRPRP_Error.h"
#include "MDR_HSRPRP_Frames.h"
#include "MDR_HSR_defs.h"
//#include "MDR_ETH_ProxyTable.h"
#include "MDR_HSRPRP_DuplicateTables.h"

typedef struct {
  //uint8_t             multicast_addr[6];
	uint8_t							hostMAC[MDR_ETH_MAC_LEN];
  MDT_HSR_ForwMode_t  forwMode;
  bool                hasLocalCriteria;
  MDR_HSRPRP_LAN_ID   lanID;
	uint16_t        		seqNum;
	uint16_t        		seqNumSup;	
	//	Time events
	uint32_t						lastTimeTaskInd;
	uint32_t						lastTimeForgetDuplicate;
	uint32_t						lastTimeForgetNode;
	uint32_t						lastTimeForgetProxy;
	uint32_t						lastTimeSuperSend;	
	uint32_t						lastTimeSelfSuperRx;
	//	received
	uint16_t        		seqNumSupRx;
	uint16_t        		superLostCnt;
	bool        		    doCheckSupRx;
	bool        		    isRingClosed;		//	false - если потеряется суперфрейм, обновляется при каждой посылке суперфрейма
} MDR_HSR_NodeCfg;


//
void MDR_HSR_DANH_ForwardFromHost  (MDR_HSR_NodeCfg *cfgNode, MDR_HSRPRP_FrameItem *frameItem);
void MDR_HSR_DANH_ForwardFromPortAB(MDR_HSR_NodeCfg *cfgNode, MDR_HSRPRP_FrameItem *frameItem);

void MDR_HSR_DANH_AssignForwardTasks(MDR_HSR_NodeCfg *cfgNode, MDR_HSRPRP_FrameItem *frameItem);

//typedef enum {
//  MDR_HSR_LanA = 0,
//  MDR_HSR_LanB,
//} MDR_HSR_LanID;

typedef struct {
  MDR_HSR_NodeCfg            nodeCfg;
  MDT_HSR_RedBox_ForwMode_t  forwMode;
  //MDR_HSR_LanID              lanID;
	MDR_HSRPRP_LAN_ID					 lanID;
} MDR_HSR_RedBoxCfg;

void MDR_HSR_RedBox_ForwardFromHost			(MDR_HSR_RedBoxCfg *cfgRedBox, MDR_HSRPRP_FrameItem *frameItem);
void MDR_HSR_RedBox_ForwardFromPortAB   (MDR_HSR_RedBoxCfg *cfgRedBox, MDR_HSRPRP_FrameItem *frameItem);
void MDR_HSR_RedBox_ForwardFromInterlink(MDR_HSR_RedBoxCfg *cfgRedBox, MDR_HSRPRP_FrameItem *frameItem);

void MDR_HSR_Redbox_AssignForwardTasks(MDR_HSR_RedBoxCfg *cfgRedBox, MDR_HSRPRP_FrameItem *frameItem);

#endif  //  _MDR_HSR_H

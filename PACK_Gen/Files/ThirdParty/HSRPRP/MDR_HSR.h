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


//  Назначает пересылку от Host в PortA и PortB
void MDR_HSR_DANH_ForwardFromHost  (MDR_HSR_NodeCfg *cfgNode, MDR_HSRPRP_FrameItem *frameItem);

//  Назначает пересылку полученного фрейма в PortA, в PortB или в Host если для него нет дубликата
//    в таблицах дубликатов для данных портов.
//  Запись в таблицу дубликатов происходит при отправке - MDR_HSRPRP_ProcessForwardingEx(), после модификации фрейма
//  В Host передаются фреймы с МАС адресом Хоста или прошедшие фильтр на мультикастинг
//  Запись в таблице дубликатов удаляется при устаревании, 
//    либо по факту приходу дубликата - при опции DUPLICATE_TABLE_FREE_ITEM_ON_DUPL_RX
void MDR_HSR_DANH_ForwardFromPortAB(MDR_HSR_NodeCfg *cfgNode, MDR_HSRPRP_FrameItem *frameItem);

//  Функция проверяет откуда пришел фрейм и вызывает MDR_HSR_DANH_ForwardFromHost() или MDR_HSR_DANH_ForwardFromPortAB()
void MDR_HSR_DANH_AssignForwardTasks(MDR_HSR_NodeCfg *cfgNode, MDR_HSRPRP_FrameItem *frameItem);


typedef struct {
  MDR_HSR_NodeCfg            nodeCfg;
  MDT_HSR_RedBox_ForwMode_t  forwMode;
  //MDR_HSR_LanID              lanID;
	MDR_HSRPRP_LAN_ID					 lanID;
} MDR_HSR_RedBoxCfg;

//  Пересылает фреймы от Хоста в PortA и PortB, в определенных режимах в Interlink
//  ProxyTable не используется.
void MDR_HSR_RedBox_ForwardFromHost			(MDR_HSR_RedBoxCfg *cfgRedBox, MDR_HSRPRP_FrameItem *frameItem);

//  Пересылает фреймы полученные из PortA и PortB.
//  В сеть Interlink фрейм передается если есть адрес назначения в ProxyTable
//  Дубликаты отбрасываются
void MDR_HSR_RedBox_ForwardFromPortAB   (MDR_HSR_RedBoxCfg *cfgRedBox, MDR_HSRPRP_FrameItem *frameItem);

//  Пересылает фреймы из сети Interlink в PortA, PortB, Host.
//  Обновляет ProxyTable адресами устройств в сети Interlink, записи стареют по времени.
void MDR_HSR_RedBox_ForwardFromInterlink(MDR_HSR_RedBoxCfg *cfgRedBox, MDR_HSRPRP_FrameItem *frameItem);

//  Вызывает функции MDR_HSR_RedBox_ForwardFromHost() / MDR_HSR_RedBox_ForwardFromPortAB() / MDR_HSR_RedBox_ForwardFromInterlink()
//  В зависимостри от того, откуда пришел фрейм.
void MDR_HSR_Redbox_AssignForwardTasks(MDR_HSR_RedBoxCfg *cfgRedBox, MDR_HSRPRP_FrameItem *frameItem);


#endif  //  _MDR_HSR_H

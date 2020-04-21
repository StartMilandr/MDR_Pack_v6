#ifndef _MDR_HSRPRP_FRAMES
#define _MDR_HSRPRP_FRAMES

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <MDR_Ethernet_FrameDefs.h>
#include <MDR_HSRPRP_Config.h>
#include <MDR_HSR_defs.h>
#include <MDR_PRP_defs.h>


#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
	#include <cmsis_armclang.h>
#elif defined (__CC_ARM)
	#include <cmsis_armcc.h>  
#endif	

//	Все Фреймы на передачу / прием через HSR/PRP сохраняются в структуре MDR_HSRPRP_FrameItem
//  MDR_HSRPRP_FrameItem - это сам фрейм и дополнительные поля, определяющие что это за фрейм и что с ним делать.

//	Стандартный Фрейм делится на три части:
//    1 - Header, состоит из МАС адресов и VLAN таг если есть
//    2 - Payload, состоит из EthType и Payload.
//    3 - TAG, (HSR - между Header и Payload / PRP - после Payload)
//  Каждая часть имеет свой указатель и длину в структуре MDR_HSRPRP_FramePtrs

//	--------------		Headers	--------------
//	Заголовок без VLAN
typedef __PACKED_STRUCT {
  uint8_t  destMAC[MDR_ETH_MAC_LEN];
  uint8_t  srcMAC[MDR_ETH_MAC_LEN];
} MDR_HSRPRP_Header;

//	Заголовок с VLAN
typedef __PACKED_STRUCT {
  uint8_t  destMAC[MDR_ETH_MAC_LEN];
  uint8_t  srcMAC[MDR_ETH_MAC_LEN];
  uint32_t tagVLAN;
} MDR_HSRPRP_HeaderVLAN;


#define MDR_HSRPRP_HEADER_LEN        	sizeof(MDR_HSRPRP_Header)
#define MDR_HSRPRP_HEADER_VLAN_LEN    sizeof(MDR_HSRPRP_HeaderVLAN)

//	указатель на самую длинную из структур
#define MDR_HSRPRP_HeaderMax					MDR_HSRPRP_HeaderVLAN
#define MDR_HSRPRP_HEADER_LEN_MAX     MDR_HSRPRP_HEADER_VLAN_LEN


//	--------------		Payload 	--------------
typedef __PACKED_STRUCT {
  uint16_t ethType;
  uint8_t  payload[];
} MDR_HSRPRP_Payload;


//	--------------		TAG 	--------------
// определено в MDR_HSR_Defs.h и MDR_PRP_Defs.h

//typedef __PACKED_STRUCT { 
//  uint16_t        etherType;               //  ETH_TYPE_HSR      0x892F
//  uint16_t        lanID_LSDUSize;
//  uint16_t        seqNum; 
//} MDR_HSR_Tag_t;

//#define MDR_HSR_TAG_LEN           sizeof(MDR_HSR_Tag_t)
//#define MDR_HSR_TAG_LSDU_LEN		 (sizeof(MDR_HSR_Tag_t) - MDR_ETH_TYPE_LEN)

//typedef __PACKED_STRUCT { 
//  uint16_t        seqNum; 
//  uint16_t        lanID_LSDUSize;
//	uint16_t        suffPRP;
//} MDR_PRP_Tag_t;



#define LSDUSize_ToSize(val)         			((val) & 0xFFF)
#define LSDUSize_ToLanID(val)       			(((val) >> 12) & 0xF)
#define FILL_LanID_LSDUSize(lanID, size) 	((((lanID) & 0xF) << 12) | ((size) & 0xFFF))	


//	--------------	Структура идентификации фрейма	MDR_HSRPRP_FramePtrs 	--------------
//	Типы фреймов
typedef enum {
  MDR_HSRPRP_FrameEth,
  MDR_HSRPRP_FrameHSR,
  MDR_HSRPRP_FramePRP,
  MDR_HSRPRP_FrameSupHSR,
  MDR_HSRPRP_FrameSupPRP,
} MDR_HSRPRP_FrameType;

//	Из какой сети А или Б
typedef enum {
  MDR_HSRPRP_LanUndef = 0x0,
  MDR_HSRPRP_LanA = 0xA,
  MDR_HSRPRP_LanB = 0xB
} MDR_HSRPRP_LAN_ID;


//	Структура указателей на составные части фрейма
typedef struct {
  MDR_HSRPRP_HeaderMax  *pHeader;						//	MDR_HSRPRP_Header* или MDR_HSRPRP_HeaderVLAN*
  MDR_HSRPRP_Payload    *pPayload;					//  MDR_HSRPRP_Payload*
  uint8_t               *pTag;              //  &[TagHSR or pTagPRP]
  uint16_t              lenHeader;					//  MDR_HSRPRP_HEADER_LEN или MDR_HSRPRP_HEADER_VLAN_LEN
  uint16_t              lenPayload;         //  len(payload) + MDR_ETH_TYPE_LEN
  uint16_t              lenTag;             //  Length of pTagHSR or pTagPRP
  MDR_HSRPRP_FrameType  frameType;          //  BitMask of MDR_HSRPRP_FrameTypes
  MDR_HSRPRP_LAN_ID     lanID;
  bool                  isVLAN;
} MDR_HSRPRP_FramePtrs;



//	--------------	Основная структура  MDR_HSRPRP_FrameItem 	--------------
//	Перечисление возможных портов (откуда/куда пересылаются фреймы)
typedef enum {
  MDR_HSRPRP_PortA,
  MDR_HSRPRP_PortB,
  MDR_HSRPRP_Host,      //  свои фреймы
  MDR_HSRPRP_Interlink, //  фреймы в RedBox
} MDR_HSRPRP_FramePort;


//  Задачи для пересылки FrameItem в MDR_HSRPRP_FramePort задаются масками в MDR_HSRPRP_FrameForwTask.selForwPort  (Forwarding)
#define MDR_HSRPRP_ForwPortA      (1UL << MDR_HSRPRP_PortA)
#define MDR_HSRPRP_ForwPortB      (1UL << MDR_HSRPRP_PortB)
#define MDR_HSRPRP_ForwHost       (1UL << MDR_HSRPRP_Host)
#define MDR_HSRPRP_ForwInterlink  (1UL << MDR_HSRPRP_Interlink)

#define MDR_HSRPRP_ForwPortAB     (MDR_HSRPRP_ForwPortA | MDR_HSRPRP_ForwPortA)


//	Доступные операции по модификации фреймов, задаются в полях MDR_HSRPRP_FrameForwTask.tagModif...
typedef enum {
  MDR_HSRPRP_Tag_NoModif,
  MDR_HSRPRP_Tag_AddHSR,
  MDR_HSRPRP_Tag_DelHSR,
  MDR_HSRPRP_Tag_AddPRP,
  MDR_HSRPRP_Tag_DelPRP,
  MDR_HSRPRP_Tag_PRPtoHSR,
  MDR_HSRPRP_Tag_HSRtoPRP,
  //  Specific
  MDR_HSRPRP_Tag_AddLocalHSR,
  //  not for use
  _MDR_HSRPRP_TagModifLen
} MDR_HSRPRP_TagModif;

//	Структура в которой задаются задачи на пересылку и то как модифицировать фрейм для каждого порта
typedef struct {
  uint32_t              selForwPort;
  MDR_HSRPRP_TagModif   tagModifPortAB;
  MDR_HSRPRP_TagModif   tagModifHost;
  MDR_HSRPRP_TagModif   tagModifInterlink;
} MDR_HSRPRP_FrameForwTask;


//  Статусы (такты) обработки FrameItem
typedef enum {
  MDR_HSRPRP_Free,									//	FrameItem свободен
	MDR_HSRPRP_WaitInputProcess,			//  FrameItem получил данные, ждет обработки - заполнение MDR_HSRPRP_FramePtrs и т.д.
  MDR_HSRPRP_WaitTackAssign,			  //  FrameItem ждет назначения задач на Forwarding
  MDR_HSRPRP_WaitForward,						//	FrameItem	ждет очереди на отправку в порты
} MDR_HSRPRP_FrameItemStatus;

//	Приоритет выбора фрейма для обработки задается на этапе MDR_HSRPRP_WaitInputProcess
#define MDR_HSRPRP_PROIRITY_MIN   0
#define MDR_HSRPRP_PROIRITY_DEF   MDR_HSRPRP_PROIRITY_MIN
#define MDR_HSRPRP_PROIRITY_MAX   0x7FFFUL

//	Сама структура FrameItem
typedef struct {
	uint8_t                    *frameBuff;  													//  указатель на массив для фрейма в куче, размер = MDR_HSRPRP_FRAME_MAX_LEN

  //	Fields	
  MDR_HSRPRP_FramePtrs        framePtrs;                            //  Указатели на структуры фрейма - Header/Tag/Payload
  uint32_t                    frameLen;                             //  Длина фрейма
	uint32_t										timeRx;																//	Время, когда фрейм был принят (значение таймера)
  //  Task for forwarding frame
  MDR_HSRPRP_FrameItemStatus  status;                               //  Статус обработки фрейма
  MDR_HSRPRP_FrameForwTask    forwTasks;														//  Назначенные задачи на обработку
	MDR_HSRPRP_FramePort        frameSrc;                             //  Источник фрейма

  uint32_t                    forwPriority;                         //  0 - lowest (default)  
  //  private (not for user)
  uint32_t                    _frmIndex;                            //  Индекс в массиве фреймов
} MDR_HSRPRP_FrameItem;


//	Типизированный доступ к MDR_HSRPRP_FrameItem.frameBuff
#define FrameItemGetFrameTX(frmItm)		((MDR_ETH_FrameTX *)(frmItm->frameBuff))
#define FrameItemGetFrameRX(frmItm)		((MDR_ETH_FrameRX *)(frmItm->frameBuff))

//	Количество байт для буфера под фрейм MDR_HSRPRP_FrameItem.frameBuff
#define MDR_HSRPRP_FRAME_MAX_LEN    (MDR_ETH_FRAME_VLAN_LEN_MAX + MDR_HSR_TAG_LEN)


//============================		Функции работы с FrameItem	=============================

// Выделение памяти под FrameItems
void MDR_HSRPRP_AllocateFrameItems(void);
void MDR_HSRPRP_FreeFrameItems(void);

//  Получить свободный FrameItem чтобы записать туда фрейм
MDR_HSRPRP_FrameItem*  MDR_HSRPRP_CaptureFrameItem(void);
//  Освободить захваченый ранее FrameItem
void MDR_HSRPRP_FreeFrameItem(MDR_HSRPRP_FrameItem *frameItem);


//  Выборка следующего фрейма для обработки (выборка по статусу и приоритету)
MDR_HSRPRP_FrameItem*  MDR_HSRPRP_GetNextFrameByStatusAndPriority(MDR_HSRPRP_FrameItemStatus status);
//  Выборка следующего фрейма для обработки (выборка по статусу и БЕЗ приоритета)
MDR_HSRPRP_FrameItem*  MDR_HSRPRP_GetNextFrameByStatus(MDR_HSRPRP_FrameItemStatus status);

//  Распарсить автоматически указатели на структуры фрейма по его типу (маска frameTypes)
//  Вызывать после записи фрейма в frameItem->frameBuff
//  В frameSrc указать с какого порта считаны данные
void MDR_HSRPRP_ProcessInputFrame(MDR_HSRPRP_FrameItem *frameItem);





#endif  //  _MDR_HSRPRP_FRAMES

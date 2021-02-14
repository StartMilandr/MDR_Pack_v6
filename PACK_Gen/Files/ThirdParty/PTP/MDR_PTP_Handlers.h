#ifndef _MDR_PTP_HANDLERS_H
#define _MDR_PTP_HANDLERS_H

#include <stdint.h>
#include <stdbool.h>
#include <MDR_PTP_defs.h>
#include <MDR_PTP_Frames.h>


//=================   MASTER CLOCK  (TX: Sync, DelayResp, RX: DelayReq) ==============
// Структура для упрощения работы со временем, старшие секунды игнорируются.
typedef __PACKED_STRUCT {
	int16_t            _unused;
	int32_t            seconds_lsb;
	int32_t            nanoseconds;
} ptp_time_t;

typedef struct {
  ptp_timestamp_t  timeTX;
  ptp_timestamp_t  timeRX;
} MDR_PTP_TimeTxRx;


typedef void (*FuncGetNowTimestamp)(ptp_timestamp_t *timeStamp);
typedef void (*FuncSetTimeOffset)(ptp_time_t *timeOffset);
typedef void (*FuncSendFrame)(uint32_t ptpDataLen, ptp_MSG_message_e mess_id);
typedef void (*FuncGetTimestampLastTX)(ptp_timestamp_t *timeStamp);

typedef struct {
  FuncGetNowTimestamp     fnGetTimeStampNow;
  FuncGetTimestampLastTX  fnGetTimeStampLastTX; // Optionally if possible, otherwise nop function
  FuncSetTimeOffset       fnSetTimeOffset;
} MDR_PTP_TimeSrc_t;

typedef struct {
  uint8_t              *framePTP;        //  Указатель в Payload (L2/UDP), куда записать PTP Frame. 
  FuncSendFrame         fnSendFrame;     //  Функция отправки фрейма. Вызывается после заполнения framePTP.
} MDR_PTP_CtrlTx_t;

typedef struct {  
  //  UserDefined
  MDR_PTP_TimeSrc_t     timeSrc;
  MDR_PTP_CtrlTx_t      ctrlTx;   
  MDR_PTP_Port_t        port;
  bool                  syncTwoStep;  
  //  Locals
  ptp_timestamp_t       stampSyncSend;
} MDR_PTP_Master_t;

// Сброс полей структуры MDR_PTP_Master_t в начальное состояние. Кроме: timeSrc, ctrlTx, port.portIdent, port.numDomain;
void MDR_PTP_MasterClearObj(MDR_PTP_Master_t *obj);
// Запуск цикла синхронизации Sync, если текущий цикл закончился.
void MDR_PTP_MasterStartSync(MDR_PTP_Master_t *obj);
// Обработка пришедшего фрейма. Дропается все, что не DelayResponce с правильным sequenceID. 
//  TRUE - пакет верный (был обработан), FALSE - неправильный пакет.
bool MDR_PTP_E2E_MasterProcessFrameRx(MDR_PTP_Master_t *obj, void *rxFramePTP, ptp_timestamp_t *stampReceived);


//=================   SLAVE CLOCK  (RX: Sync, DelayResp  TX: DelayReq)  ==============
typedef struct {  
  //  UserDefined
  MDR_PTP_TimeSrc_t     timeSrc;
  MDR_PTP_CtrlTx_t      ctrlTx;
  MDR_PTP_Port_t        port;
  bool                  syncTwoStep;  
  //  Locals
  MDR_PTP_TimeTxRx      stampsSync;
  MDR_PTP_TimeTxRx      stampsDelayReq;
  uint64_t              correctionSync;
  uint64_t              correctionDelayReq;
} MDR_PTP_Slave_t;

// Сброс полей структуры MDR_PTP_Master_t в начальное состояние. Кроме: timeSrc, ctrlTx, port.portIdent, port.numDomain;
void MDR_PTP_SlaveClearObj(MDR_PTP_Slave_t *obj);
// Обработка пришедшего фрейма. Дропается все, что не Sync/DelayResponce с правильным sequenceID.
// TRUE - пакет верный (был обработан), FALSE - неправильный пакет.
bool MDR_PTP_E2E_SlaveProcessFrameRx(MDR_PTP_Slave_t *obj, void *rxFramePTP, ptp_timestamp_t *stampReceived);


//=================   P2P Sync (RX: Sync, DelayResp  TX: DelayReq)  ==============

typedef struct {  
  //  UserDefined
  MDR_PTP_TimeSrc_t     timeSrc;
  MDR_PTP_CtrlTx_t      ctrlTx;
  MDR_PTP_Port_t        port;
  bool                  syncTwoStep;  
  //  Locals
  MDR_PTP_TimeTxRx      stampsSync;
  uint64_t              correctionSync;  
  //  Peer Sync
  MDR_PTP_TimeTxRx      stampsPDelayReq;
  MDR_PTP_TimeTxRx      stampsPDelayResp;
  uint64_t              correctionReq;
  uint64_t              correctionResp;  
  ptp_timestamp_t       linkDelay;
  bool                  linkDelayReady;
  bool                  syncReceived;
} MDR_PTP_SlaveP2P_t;

void MDR_PTP_P2P_SlaveClearObj(MDR_PTP_SlaveP2P_t *obj);
void MDR_PTP_P2P_SlaveStart(MDR_PTP_SlaveP2P_t *obj);
// PDelay_Resp_FollowUp Used!
bool MDR_PTP_P2P_SlaveProcessFrameRx(MDR_PTP_SlaveP2P_t *obj, void *rxFramePTP, ptp_timestamp_t *stampReceived);

bool MDR_PTP_P2P_MasterProcessFrameRx(MDR_PTP_Master_t *obj, void *rxFramePTP, ptp_timestamp_t *stampReceived);

//=================   TimeCalculation  ==============
void subTime(ptp_time_t *r, const ptp_time_t *x, const ptp_time_t *y);
void addTime(ptp_time_t *r, const ptp_time_t *x, const ptp_time_t *y);


#endif  //_MDR_PTP_HANDLERS_H

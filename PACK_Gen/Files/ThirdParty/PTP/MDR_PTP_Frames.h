#ifndef _MDR_PRP_FRAMES_H
#define _MDR_PRP_FRAMES_H

#include <MDR_PTP_defs.h>
#include "MDR_PTP_Config.h"

typedef struct {  
  //  UserDefined
  ptp_port_ident_t      portIdent;
  uint8_t               numDomain;
  // Locals
  uint8_t               logInterv_Sync;         // передача ведомому периода синхронизации
  uint8_t               logInterv_MinDelayReq;  // рекомендация мастеру не опрашивать чаще
  uint8_t               logInterv_Announce;
  uint16_t              seqId_Sync;
  uint16_t              seqId_DelayReq;
  uint16_t              seqId_PeerDelayReq;
  uint16_t              seqId_Announce;
  uint16_t              seqId_Signaling;
  uint16_t              seqId_Managment;
} MDR_PTP_Port_t;

uint16_t MDR_PTP_FillMessSync    (void *ptr, const MDR_PTP_Port_t *port,  const ptp_timestamp_t *originTimestamp);
uint16_t MDR_PTP_FillMessFollowUp(void *ptr, const MDR_PTP_Port_t *port,  const ptp_timestamp_t *preciseOriginTimestamp);
uint16_t MDR_PTP_FillMessDelayReq(void *ptr, const MDR_PTP_Port_t *port,  const ptp_timestamp_t *originTimestamp);
uint16_t MDR_PTP_FillMessDelayResp(ptp_msg_delay_req_t *reqFrame, void *ptr, 
  const MDR_PTP_Port_t *port, const ptp_timestamp_t *receiveTimestamp);

uint16_t MDR_PTP_FillMessPDelayReq(void *ptr, const MDR_PTP_Port_t *port, const ptp_timestamp_t *originTimestamp);
uint16_t MDR_PTP_FillMessPDelayResp(ptp_msg_pdelay_req_t *reqFrame, void *ptr, 
  const MDR_PTP_Port_t *port, const ptp_timestamp_t *receiveTimestamp);
uint16_t MDR_PTP_FillMessPDelayRespFollowUp(ptp_msg_pdelay_req_t *reqFrame, void *ptr, 
  const MDR_PTP_Port_t *port, const ptp_timestamp_t *responseOriginTimestamp);

uint16_t MDR_PTP_UpdateTime_MessPDelayRespFollowUp(void *ptr, const ptp_timestamp_t *responseOriginTimestamp);

typedef struct {
  int16_t currentUtcOffset;
  int16_t stepsRemoved;
} ptp_self_time_t;

uint16_t MDR_PTP_FillMessAnnounce (void *ptr, const MDR_PTP_Port_t *port, ptp_self_time_t *selfTime);
uint16_t MDR_PTP_FillMessSignaling(void *ptr, const MDR_PTP_Port_t *port, uint16_t tlvType, uint16_t dataLen, 
  void *data, ptp_port_ident_t *targetPortIdentity);
uint16_t MDR_PTP_FillMessManagement(void *ptr, const MDR_PTP_Port_t *port, uint8_t action, uint16_t command,
  ptp_port_ident_t *targetPortIdentity, uint8_t startingBoundaryHops);

#endif // _MDR_PRP_FRAMES_H

#include "MDR_PTP_Frames.h"
#include <MDR_Funcs.h>
#include "string.h"

static const ptp_clock_ident_t _ptp_clock_indent = CFG_PTP_CLOCK_IDENTITY;

static void MDR_PTP_FillHeaderDef(ptp_header_t *hdr, uint8_t numDomain, const ptp_port_ident_t *portIdent)
{
  hdr->version = CFG_PTP_VERSION;                           // uint8_t
  hdr->domainNum = numDomain;                               // uint8_t
	hdr->_reserved1 = PTP_SDOID_MINOR_802_1_AS;               // uint8_t             
  hdr->_reserved2 = 0;                                      // uint32_t
  hdr->flags[0] = CFG_PTP_FLAG0;                            // uint8_t
  hdr->flags[1] = CFG_PTP_FLAG1;                            // uint8_t  
  memcpy(&hdr->srcPortId, portIdent, PTP_LEN_CLOCK_IDENTITY); // ptp_port_ident_t
  
  //hdr->mess_transp = CFG_PTP_TRANSP_SPECIFIC | mess;      // uint8_t
  //hdr->messLen                                            // uint16_t
  //dr->flags[0] = 0;                                       // uint8_t
  //hdr->flags[1] = 1;                                      // uint8_t
  //hdr->correction = 0;                                    // uint64_t
  //hdr->seqId = 0;                                         // uint16_t
  //hdr->control;                                           // uint8_t
}

//---------------   Sync, FollowUp -----------------
#define _ETH_HEADER_LEN   6*2 + 2

uint16_t MDR_PTP_FillMessSync(void *ptr, const MDR_PTP_Port_t *port, const ptp_timestamp_t *originTimestamp)
{
  ptp_header_t *hdr = ptr;
  
  MDR_PTP_FillHeaderDef(hdr, port->numDomain, &port->portIdent);
  hdr->mess_transp = CFG_PTP_TRANSP_SPECIFIC | PTP_MSG_SYNC; // uint8_t
  hdr->messLen = REV_BYTES16(PTP_LEN_SYNC);                  // uint16_t
  hdr->correction = 0;                                       // uint64_t  
  hdr->seqId = REV_BYTES16(port->seqId_Sync);                // uint16_t
  hdr->control = PTP_CTRL_SYNC;                              // uint8_t
  hdr->logMessInterval = port->logInterv_Sync;              // uint8_t    
  
	// Sync body
  ptp_msg_sync_t *mess = ptr;
  mess->originTimestamp.seconds_msb = REV_BYTES16(originTimestamp->seconds_msb);
  mess->originTimestamp.seconds_lsb = REV_BYTES32(originTimestamp->seconds_lsb);
  mess->originTimestamp.nanoseconds = REV_BYTES32(originTimestamp->nanoseconds);
  
  return _ETH_HEADER_LEN + PTP_LEN_SYNC;
}

uint16_t MDR_PTP_FillMessFollowUp(void *ptr, const MDR_PTP_Port_t *port, const ptp_timestamp_t *preciseOriginTimestamp)
{
  ptp_header_t *hdr = ptr;
  
  MDR_PTP_FillHeaderDef(hdr, port->numDomain, &port->portIdent);
  hdr->mess_transp = CFG_PTP_TRANSP_SPECIFIC | PTP_MSG_FOLLOW_UP; // uint8_t
  hdr->messLen = REV_BYTES16(PTP_LEN_FOLLOW_UP);                  // uint16_t
  hdr->correction = 0;                                            // uint64_t  
  hdr->seqId = REV_BYTES16(port->seqId_Sync);                     // uint16_t - Same as in SyncMess
  hdr->control = PTP_CTRL_FOLLOW_UP;                              // uint8_t
  hdr->logMessInterval = PTP_LOG_MESSAGE_INTERVAL_DEF;            // uint8_t    
  
	// Body
  ptp_msg_follow_up_t *mess = ptr;
  mess->preciseOriginTimestamp.seconds_msb = REV_BYTES16(preciseOriginTimestamp->seconds_msb);
  mess->preciseOriginTimestamp.seconds_lsb = REV_BYTES32(preciseOriginTimestamp->seconds_lsb);
  mess->preciseOriginTimestamp.nanoseconds = REV_BYTES32(preciseOriginTimestamp->nanoseconds);
  
  return _ETH_HEADER_LEN + PTP_LEN_FOLLOW_UP;
}


//---------------   DelayReq, DelayResp -----------------
uint16_t MDR_PTP_FillMessDelayReq(void *ptr, const MDR_PTP_Port_t *port, const ptp_timestamp_t *originTimestamp)
{
  ptp_header_t *hdr = ptr;
  
  MDR_PTP_FillHeaderDef(hdr, port->numDomain, &port->portIdent);
  hdr->mess_transp = CFG_PTP_TRANSP_SPECIFIC | PTP_MSG_DELAY_REQ; // uint8_t
  hdr->messLen = REV_BYTES16(PTP_LEN_DELAY_REQ);                  // uint16_t
  hdr->correction = 0;                                            // uint64_t  
  hdr->seqId = REV_BYTES16(port->seqId_DelayReq);                 // uint16_t
  hdr->control = PTP_CTRL_DELAY_REQ;                              // uint8_t
  hdr->logMessInterval = PTP_LOG_MESSAGE_INTERVAL_DEF;            // uint8_t    
  
	// Body
  ptp_msg_delay_req_t *mess = ptr;
  mess->originTimestamp.seconds_msb = REV_BYTES16(originTimestamp->seconds_msb);
  mess->originTimestamp.seconds_lsb = REV_BYTES32(originTimestamp->seconds_lsb);
  mess->originTimestamp.nanoseconds = REV_BYTES32(originTimestamp->nanoseconds);
  
  return _ETH_HEADER_LEN + PTP_LEN_DELAY_REQ;
}

// 11.3.2 Delay request-response mechanism operational specifications
// c) Upon receipt of the Delay_Req message, the master node shall :
uint16_t MDR_PTP_FillMessDelayResp(ptp_msg_delay_req_t *reqFrame, void *ptr,
  const MDR_PTP_Port_t *port, const ptp_timestamp_t *receiveTimestamp)
{
  ptp_header_t *hdr = ptr;
  
  MDR_PTP_FillHeaderDef(hdr, reqFrame->hdr.domainNum, &port->portIdent);
  hdr->mess_transp = CFG_PTP_TRANSP_SPECIFIC | PTP_MSG_DELAY_RESP; // uint8_t
  hdr->messLen = REV_BYTES16(PTP_LEN_DELAY_RESP);                  // uint16_t
  hdr->correction = reqFrame->hdr.correction;                      // uint64_t  
  hdr->seqId = reqFrame->hdr.seqId;                                // uint16_t
  hdr->control = PTP_CTRL_DELAY_RESP;                              // uint8_t
  hdr->logMessInterval = port->logInterv_MinDelayReq;              // uint8_t  

	// Body
  ptp_msg_delay_resp_t *mess = ptr;
  mess->receiveTimestamp.seconds_msb = REV_BYTES16(receiveTimestamp->seconds_msb);
  mess->receiveTimestamp.seconds_lsb = REV_BYTES32(receiveTimestamp->seconds_lsb);
  mess->receiveTimestamp.nanoseconds = REV_BYTES32(receiveTimestamp->nanoseconds);
	memcpy(&mess->requestingPortIdentity, &reqFrame->hdr.srcPortId, PTP_LEN_PORT_IDENT);
  
  return _ETH_HEADER_LEN + PTP_LEN_DELAY_RESP;
}


//---------------   PDelayReq, PDelayResp,PDelayRespFollowUp  (Peer) -----------------
uint16_t MDR_PTP_FillMessPDelayReq(void *ptr, const MDR_PTP_Port_t *port, const ptp_timestamp_t *originTimestamp)
{
  ptp_header_t *hdr = ptr;
  
  MDR_PTP_FillHeaderDef(hdr, port->numDomain, &port->portIdent);
  hdr->mess_transp = CFG_PTP_TRANSP_SPECIFIC | PTP_MSG_PDELAY_REQ;  // uint8_t
  hdr->messLen = REV_BYTES16(PTP_LEN_PDELAY_REQ);                   // uint16_t
  hdr->correction = 0;                                              // uint64_t  
  hdr->seqId = REV_BYTES16(port->seqId_PeerDelayReq);               // uint16_t
  hdr->control = PTP_CTRL_OTHER;                                    // uint8_t
  hdr->logMessInterval = PTP_LOG_MESSAGE_INTERVAL_DEF;              // uint8_t    
  
	// Body
  ptp_msg_pdelay_req_t *mess = ptr;
  mess->originTimestamp.seconds_msb = REV_BYTES16(originTimestamp->seconds_msb);
  mess->originTimestamp.seconds_lsb = REV_BYTES32(originTimestamp->seconds_lsb);
  mess->originTimestamp.nanoseconds = REV_BYTES32(originTimestamp->nanoseconds);  
  memset(&mess->reserved, 0, PTP_LEN_PORT_IDENT);
  
  return _ETH_HEADER_LEN + PTP_LEN_PDELAY_REQ;
}

uint16_t MDR_PTP_FillMessPDelayResp(ptp_msg_pdelay_req_t *reqFrame, void *ptr, 
  const MDR_PTP_Port_t *port, const ptp_timestamp_t *receiveTimestamp)
{
  ptp_header_t *hdr = ptr;
  
  MDR_PTP_FillHeaderDef(hdr, reqFrame->hdr.domainNum, &port->portIdent);
  hdr->mess_transp = CFG_PTP_TRANSP_SPECIFIC | PTP_MSG_PDELAY_RESP;   // uint8_t
  hdr->messLen = REV_BYTES16(PTP_LEN_PDELAY_RESP);                    // uint16_t
  hdr->correction = 0;                                                // uint64_t  
  hdr->seqId = reqFrame->hdr.seqId;                                   // uint16_t
  hdr->control = PTP_CTRL_OTHER;                                      // uint8_t
  hdr->logMessInterval = port->logInterv_MinDelayReq;                 // uint8_t  

	// Body
  ptp_msg_pdelay_resp_t *mess = ptr;
  mess->requestReceiptTimestamp.seconds_msb = REV_BYTES16(receiveTimestamp->seconds_msb);
  mess->requestReceiptTimestamp.seconds_lsb = REV_BYTES32(receiveTimestamp->seconds_lsb);
  mess->requestReceiptTimestamp.nanoseconds = REV_BYTES32(receiveTimestamp->nanoseconds);
	memcpy(&mess->requestingPortIdentity, &reqFrame->hdr.srcPortId, PTP_LEN_PORT_IDENT);
  
  return _ETH_HEADER_LEN + PTP_LEN_PDELAY_RESP;
}

uint16_t MDR_PTP_FillMessPDelayRespFollowUp(ptp_msg_pdelay_req_t *reqFrame, void *ptr, 
  const MDR_PTP_Port_t *port, const ptp_timestamp_t *responseOriginTimestamp)
{
  ptp_header_t *hdr = ptr;
  
  MDR_PTP_FillHeaderDef(hdr, reqFrame->hdr.domainNum, &port->portIdent);
  hdr->mess_transp = CFG_PTP_TRANSP_SPECIFIC | PTP_MSG_PDELAY_RESP_FOLLOW_UP;   // uint8_t
  hdr->messLen = REV_BYTES16(PTP_LEN_PDELAY_RESP_FOLLOW_UP);                    // uint16_t
  hdr->correction = reqFrame->hdr.correction;                                   // uint64_t  
  hdr->seqId = reqFrame->hdr.seqId;                                             // uint16_t
  hdr->control = PTP_CTRL_OTHER;                                                // uint8_t
  hdr->logMessInterval = PTP_LOG_MESSAGE_INTERVAL_DEF;                          // uint8_t   
  
  // Body
  ptp_msg_pdelay_resp_fup_t *mess = ptr;
  mess->responseOriginTimestamp.seconds_msb = REV_BYTES16(responseOriginTimestamp->seconds_msb);
  mess->responseOriginTimestamp.seconds_lsb = REV_BYTES32(responseOriginTimestamp->seconds_lsb);
  mess->responseOriginTimestamp.nanoseconds = REV_BYTES32(responseOriginTimestamp->nanoseconds);
	memcpy(&mess->requestingPortIdentity, &reqFrame->hdr.srcPortId, PTP_LEN_PORT_IDENT);  
  
  return _ETH_HEADER_LEN + PTP_LEN_PDELAY_RESP_FOLLOW_UP;
}

uint16_t MDR_PTP_UpdateTime_MessPDelayRespFollowUp(void *ptr, const ptp_timestamp_t *responseOriginTimestamp)
{
  // Body
  ptp_msg_pdelay_resp_fup_t *mess = ptr;
  mess->responseOriginTimestamp.seconds_msb = REV_BYTES16(responseOriginTimestamp->seconds_msb);
  mess->responseOriginTimestamp.seconds_lsb = REV_BYTES32(responseOriginTimestamp->seconds_lsb);
  mess->responseOriginTimestamp.nanoseconds = REV_BYTES32(responseOriginTimestamp->nanoseconds);
}


//---------------   Announce -----------------
uint16_t MDR_PTP_FillMessAnnounce(void *ptr, const MDR_PTP_Port_t *port, ptp_self_time_t *selfTime)
{
  ptp_header_t *hdr = ptr;
  
  MDR_PTP_FillHeaderDef(hdr, port->numDomain, &port->portIdent);
  hdr->mess_transp = CFG_PTP_TRANSP_SPECIFIC | PTP_MSG_ANNOUNCE;  // uint8_t
  hdr->messLen = REV_BYTES16(PTP_LEN_ANNOUNCE);                   // uint16_t
  hdr->correction = 0;                                            // uint64_t  
  hdr->seqId = REV_BYTES16(port->seqId_Announce);                 // uint16_t
  hdr->control = PTP_CTRL_OTHER;                                  // uint8_t  
  hdr->logMessInterval = port->logInterv_Announce;                // uint8_t  
  
	// Announce body
  ptp_msg_announce_t *mess = ptr;
  memset(&mess->originTimestamp, 0, PTP_LEN_TIMESTAMP);
	mess->currentUtcOffset = REV_BYTES16(selfTime->currentUtcOffset);
	mess->reserved = 0;
	mess->grandmasterPriority1 = CFG_PTP_CLOCK_PRIORITY1;
	mess->grandmasterClockQuality.clockAccuracy = CFG_PTP_CLOCK_QUALITY_CLASS;
  mess->grandmasterClockQuality.clockClass = CFG_PTP_CLOCK_ACCURACY;
  mess->grandmasterClockQuality.offsetScaledLogVariance = REV_BYTES16(CFG_PTP_CLOCK_VARIANCE);
	mess->grandmasterPriority2 = CFG_PTP_CLOCK_PRIORITY2;
  memcpy(&mess->grandmasterIdentity, &_ptp_clock_indent, PTP_LEN_CLOCK_IDENTITY);
	mess->stepsRemoved = REV_BYTES16(selfTime->stepsRemoved);
	mess->timeSource = CFG_PTP_CLOCK_TIME_SOURCE;
  
  return _ETH_HEADER_LEN + PTP_LEN_ANNOUNCE;
}


//---------------   PDelayReq, PDelayResp,PDelayRespFollowUp  (Peer) -----------------
uint16_t MDR_PTP_FillMessSignaling(void *ptr, const MDR_PTP_Port_t *port, uint16_t tlvType, uint16_t dataLen, void *data, 
  ptp_port_ident_t *targetPortIdentity)
{
  ptp_header_t *hdr = ptr;
  uint16_t ptp_len = PTP_LEN_SIGNALING + PTP_TLV_LEN_nVALUE + dataLen;
  
  MDR_PTP_FillHeaderDef(hdr, port->numDomain, &port->portIdent);
  hdr->mess_transp = CFG_PTP_TRANSP_SPECIFIC | PTP_MSG_SIGNALING;   // uint8_t
  hdr->messLen = REV_BYTES16(ptp_len);                              // uint16_t
  hdr->correction = 0;                                              // uint64_t  
  hdr->seqId = REV_BYTES16(port->seqId_Signaling);                  // uint16_t
  hdr->control = PTP_CTRL_OTHER;                                    // uint8_t
  hdr->logMessInterval = CFG_PTP_LOG_INTERVAL_SIGNALING;            // uint8_t    
  
	// Body
  ptp_msg_signaling_t *mess = ptr;
	memcpy(&mess->targetPortIdentity, targetPortIdentity, PTP_LEN_PORT_IDENT);
  
  ptp_tlv_t *tlv = (ptp_tlv_t *)mess->suffix;
  tlv->tlvType = REV_BYTES16(tlvType);
  tlv->lengthField = REV_BYTES16(dataLen); 
  memcpy(&tlv->valueField, data, dataLen);
  
  return _ETH_HEADER_LEN + ptp_len;
}

uint16_t MDR_PTP_FillMessManagement(void *ptr, const MDR_PTP_Port_t *port, uint8_t action, uint16_t command,
  ptp_port_ident_t *targetPortIdentity, uint8_t startingBoundaryHops)
{
  ptp_header_t *hdr = ptr;
  
  MDR_PTP_FillHeaderDef(hdr, port->numDomain, &port->portIdent);
  hdr->mess_transp = CFG_PTP_TRANSP_SPECIFIC | PTP_MSG_MANAGEMENT;          // uint8_t
  hdr->messLen = REV_BYTES16(PTP_LEN_MANAGEMENT + PTP_TLV_MNG_LEN_nVALUE);  // uint16_t
  hdr->correction = 0;                                                      // uint64_t  
  hdr->seqId = REV_BYTES16(port->seqId_Managment);                          // uint16_t
  hdr->control = PTP_CTRL_OTHER;                                            // uint8_t
  hdr->logMessInterval = CFG_PTP_LOG_INTERVAL_MANAGEMENT;                   // uint8_t    
  
	// Body
  ptp_msg_management_t *mess = ptr;
	memcpy(&mess->targetPortIdentity, targetPortIdentity, PTP_LEN_PORT_IDENT);
	mess->startingBoundaryHops = startingBoundaryHops;
	mess->boundaryHops = startingBoundaryHops;
	mess->actionField = action;
	mess->reserved = 0;
   
  ptp_tlv_manage_t *tlv = (ptp_tlv_manage_t *)mess->suffix;
  tlv->tlvType = REV_BYTES16(PTP_TLV_TYPE_MANAGEMENT);
  tlv->lengthField = REV_BYTES16(2); 
  tlv->managmentID = REV_BYTES16(command);
//  tlv->valueField[0] = REV_BYTES16(value);
  
  return _ETH_HEADER_LEN + PTP_LEN_MANAGEMENT + PTP_TLV_MNG_LEN_nVALUE;
}

#include <MDR_PTP_Handlers.h>
#include <MDR_Funcs.h>

static inline void clear_timestamp(ptp_timestamp_t *stamp)
{
  stamp->nanoseconds = 0;
  stamp->seconds_lsb = 0;
  stamp->seconds_msb = 0;
}

static inline void clear_port(MDR_PTP_Port_t *port)
{
  port->logInterv_Sync = CFG_PTP_LOG_INTERVAL_SYNC;
  port->logInterv_MinDelayReq = CFG_PTP_LOG_INTERVAL_MIN_DELAY_REQ;
  port->logInterv_Announce = CFG_PTP_LOG_INTERVAL_ANNOUNCE;
  port->seqId_Sync = 0;
  port->seqId_DelayReq = 0;
  port->seqId_PDelayReq = 0;
  port->seqId_Announce = 0;
  port->seqId_Signaling = 0;
  port->seqId_Managment = 0;
}

static void PTP_E2E_UpdateTime(MDR_PTP_Slave_t *obj);
static void PTP_P2P_UpdateTime(MDR_PTP_SlaveP2P_t *obj);
static void PTP_P2P_UpdateLinkDelay(MDR_PTP_SlaveP2P_t *obj);



//=================   MASTER CLOCK (Send Sync, DelayResp) ==============
// Сброс полей структуры MDR_PTP_Master_t в начальное состояние.
void MDR_PTP_MasterClearObj(MDR_PTP_Master_t *obj)
{
  clear_port(&obj->port);
  clear_timestamp(&obj->stampSyncSend);
}

// Запуск цикла синхронизации Sync, если текущий цикл закончился.
void MDR_PTP_MasterStartSync(MDR_PTP_Master_t *obj)
{
  obj->port.seqId_Sync++;
  obj->timeSrc.fnGetTimeStampNow(&obj->stampSyncSend);  
  uint32_t len = MDR_PTP_FillMessSync(obj->ctrlTx.framePTP, &obj->port, &obj->stampSyncSend);  
  obj->ctrlTx.fnSendFrame(len, PTP_MSG_SYNC);
  
  if (!obj->syncTwoStep)  
  {
    //  Update to more accuracy timestamp
    obj->timeSrc.fnGetTimeStampLastTX(&obj->stampSyncSend);
    
    len = MDR_PTP_FillMessFollowUp(obj->ctrlTx.framePTP, &obj->port, &obj->stampSyncSend);  
    obj->ctrlTx.fnSendFrame(len, PTP_MSG_FOLLOW_UP);  
  }
}

// Обработка пришедшего фрейма. Дропается все, что не DelayResponce с правильным sequenceID. TRUE - пакет верный, FALSE - неправильный пакет.
bool MDR_PTP_E2E_MasterProcessFrameRx(MDR_PTP_Master_t *obj, void *rxFramePTP, ptp_timestamp_t *stampReceived)
{
  ptp_header_t *ptp = rxFramePTP;
  
  bool processed = ((ptp->mess_transp & PTP_MESS_Msk) == PTP_MSG_DELAY_REQ); // && (REV_BYTES16(ptp->seqId) == obj->port.seqId_Sync);
  if (processed)
  {
    uint32_t len = MDR_PTP_FillMessDelayResp((ptp_msg_delay_req_t *)rxFramePTP, obj->ctrlTx.framePTP, &obj->port, stampReceived);
    obj->ctrlTx.fnSendFrame(len, PTP_MSG_DELAY_RESP);  
  }
  
  return processed;
}

//=================   SLAVE CLOCK  (RX: Sync, DelayResp  TX: DelayReq)  ==============
#define COPY_REV_TIMESTAMP(targ, pSrc)  (targ).seconds_msb  = REV_BYTES16((pSrc).seconds_msb); \
                                    (targ).seconds_lsb = REV_BYTES32((pSrc).seconds_lsb); \
                                    (targ).nanoseconds = REV_BYTES32((pSrc).nanoseconds);


// Сброс полей структуры MDR_PTP_Master_t в начальное состояние. Кроме: timeSrc, ctrlTx, port.portIdent, port.numDomain;
void MDR_PTP_SlaveClearObj(MDR_PTP_Slave_t *obj)
{
  clear_port(&obj->port);
  clear_timestamp(&obj->stampsSync.timeTX); 
  clear_timestamp(&obj->stampsSync.timeRX); 
  clear_timestamp(&obj->stampsDelayReq.timeTX); 
  clear_timestamp(&obj->stampsDelayReq.timeRX); 
}

// Обработка пришедшего фрейма. Дропается все, что не Sync/DelayResponce с правильным sequenceID.
// TRUE - пакет верный (был обработан), FALSE - неправильный пакет.
bool MDR_PTP_E2E_SlaveProcessFrameRx(MDR_PTP_Slave_t *obj, void *rxFramePTP, ptp_timestamp_t *stampReceived)
{
  bool processed = false;
  ptp_header_t *ptp = rxFramePTP;
  
  switch (ptp->mess_transp & PTP_MESS_Msk) {
    case PTP_MSG_SYNC: {      
      ptp_msg_sync_t *ptp = rxFramePTP;
      COPY_REV_TIMESTAMP(obj->stampsSync.timeTX, ptp->originTimestamp);
      obj->stampsSync.timeRX = *stampReceived;
      obj->port.seqId_Sync = REV_BYTES16(ptp->hdr.seqId);
      obj->correctionSync = ptp->hdr.correction;
      //  send DelayReq
      obj->port.seqId_DelayReq++;
      obj->timeSrc.fnGetTimeStampNow(&obj->stampsDelayReq.timeTX);
      uint32_t len = MDR_PTP_FillMessDelayReq(obj->ctrlTx.framePTP, &obj->port, stampReceived);
      obj->ctrlTx.fnSendFrame(len, PTP_MSG_DELAY_REQ);  
      //  Update to more accuracy timestamp
      obj->timeSrc.fnGetTimeStampLastTX(&obj->stampsDelayReq.timeTX);
      
      processed = true;
      break; }
    case PTP_MSG_FOLLOW_UP: {
      ptp_msg_follow_up_t *ptp = rxFramePTP;
      if (ptp->hdr.seqId == REV_BYTES16(obj->port.seqId_Sync))
      {
        COPY_REV_TIMESTAMP(obj->stampsSync.timeTX, ptp->preciseOriginTimestamp);
        processed = true;
      }
      break; }
    case PTP_MSG_DELAY_RESP: {
      ptp_msg_delay_resp_t *ptp = rxFramePTP;
      if (ptp->hdr.seqId == REV_BYTES16(obj->port.seqId_DelayReq))
      {
        COPY_REV_TIMESTAMP(obj->stampsDelayReq.timeRX, ptp->receiveTimestamp);
        obj->correctionDelayReq = REV_BYTES32(ptp->hdr.correction);
        PTP_E2E_UpdateTime(obj);
        processed = true;
      }
      break; }
  }
  
  return processed;
}



//=================   P2P Sync (RX: Sync, DelayResp  TX: DelayReq)  ==============
void MDR_PTP_P2P_SlaveClearObj(MDR_PTP_SlaveP2P_t *obj)
{
  clear_port(&obj->port);
  clear_timestamp(&obj->stampsSync.timeTX); 
  clear_timestamp(&obj->stampsSync.timeRX); 
  clear_timestamp(&obj->stampsPDelayReq.timeTX); 
  clear_timestamp(&obj->stampsPDelayReq.timeRX);
  clear_timestamp(&obj->stampsPDelayResp.timeTX); 
  clear_timestamp(&obj->stampsPDelayResp.timeRX);  
}

void MDR_PTP_P2P_SlaveStart(MDR_PTP_SlaveP2P_t *obj)
{
  obj->port.seqId_PDelayReq++;
  obj->timeSrc.fnGetTimeStampNow(&obj->stampsPDelayReq.timeTX);  
  uint32_t len = MDR_PTP_FillMessPDelayReq(obj->ctrlTx.framePTP, &obj->port, &obj->stampsPDelayReq.timeTX);  
  obj->ctrlTx.fnSendFrame(len, PTP_MSG_PDELAY_REQ);
  //  Update to more accuracy timestamp
  obj->timeSrc.fnGetTimeStampLastTX(&obj->stampsPDelayReq.timeTX);
}

bool MDR_PTP_P2P_SlaveProcessFrameRx(MDR_PTP_SlaveP2P_t *obj, void *rxFramePTP, ptp_timestamp_t *stampReceived)
{
  bool processed = false;
  ptp_header_t *ptp = rxFramePTP;
  
  switch (ptp->mess_transp & PTP_MESS_Msk) {
    case PTP_MSG_SYNC: {
      ptp_msg_sync_t *ptp = rxFramePTP;       
      COPY_REV_TIMESTAMP(obj->stampsSync.timeTX, ptp->originTimestamp);
      obj->stampsSync.timeRX = *stampReceived;
      obj->port.seqId_Sync = REV_BYTES16(ptp->hdr.seqId);
      obj->correctionSync = ptp->hdr.correction;
          
      if (obj->linkDelayReady)
      {        
        if (!obj->syncTwoStep)
          PTP_P2P_UpdateTime(obj);
      }
      else
      {
        MDR_PTP_P2P_SlaveStart(obj);
        obj->syncReceived = true;
      }
      processed = true;
      break; }
    case PTP_MSG_FOLLOW_UP: {
      ptp_msg_follow_up_t *ptp = rxFramePTP;
      if ((obj->linkDelayReady) && (obj->port.seqId_Sync == REV_BYTES16(ptp->hdr.seqId)))
      {        
        COPY_REV_TIMESTAMP(obj->stampsSync.timeTX, ptp->preciseOriginTimestamp);
        PTP_P2P_UpdateTime(obj);
      }
      processed = true;
      break; }    
    case PTP_MSG_PDELAY_RESP: {
      ptp_msg_pdelay_resp_t *ptp = rxFramePTP;
      if (REV_BYTES16(ptp->hdr.seqId) == obj->port.seqId_PDelayReq)
      {
        COPY_REV_TIMESTAMP(obj->stampsPDelayReq.timeRX, ptp->requestReceiptTimestamp);
        obj->stampsPDelayResp.timeRX = *stampReceived;
        obj->correctionResp = ptp->hdr.correction;
        processed = true;
      }
      break; }
    case PTP_MSG_PDELAY_RESP_FOLLOW_UP: {
      ptp_msg_pdelay_resp_fup_t *ptp = rxFramePTP;
      if (REV_BYTES16(ptp->hdr.seqId) == obj->port.seqId_PDelayReq)
      {
        COPY_REV_TIMESTAMP(obj->stampsPDelayResp.timeTX, ptp->responseOriginTimestamp);
        obj->correctionReq = ptp->hdr.correction;
        PTP_P2P_UpdateLinkDelay(obj);
        if (obj->syncReceived)
        {
          PTP_P2P_UpdateTime(obj);
          obj->syncReceived = false;
          obj->linkDelayReady = false;
        }
        processed = true;
      }
      break; }    
    case PTP_MSG_PDELAY_REQ: {
      ptp_msg_pdelay_req_t *ptp = rxFramePTP;      
      obj->timeSrc.fnGetTimeStampNow(&obj->stampsPDelayResp.timeTX);
      uint32_t len = MDR_PTP_FillMessPDelayResp(ptp, obj->ctrlTx.framePTP, &obj->port, stampReceived);
      obj->ctrlTx.fnSendFrame(len, PTP_MSG_PDELAY_RESP);
      //  Update to more accuracy timestamp
      obj->timeSrc.fnGetTimeStampLastTX(&obj->stampsPDelayResp.timeTX);
            
      len = MDR_PTP_FillMessPDelayRespFollowUp(ptp, obj->ctrlTx.framePTP, &obj->port, &obj->stampsPDelayResp.timeTX);
      obj->ctrlTx.fnSendFrame(len, PTP_MSG_PDELAY_RESP_FOLLOW_UP);           
      
      break;
    }
  }
  
  return processed;
}

bool MDR_PTP_P2P_MasterProcessFrameRx(MDR_PTP_Master_t *obj, void *rxFramePTP, ptp_timestamp_t *stampReceived)
{
  ptp_header_t *ptp = rxFramePTP;
  
  bool processed = ((ptp->mess_transp & PTP_MESS_Msk) == PTP_MSG_PDELAY_REQ);
  if (processed)
  {
    ptp_timestamp_t timeResponceTX;
    ptp_msg_pdelay_req_t *ptp = rxFramePTP;      
    obj->timeSrc.fnGetTimeStampNow(&timeResponceTX);
    uint32_t len = MDR_PTP_FillMessPDelayResp(ptp, obj->ctrlTx.framePTP, &obj->port, stampReceived);
    obj->ctrlTx.fnSendFrame(len, PTP_MSG_PDELAY_RESP);
    //  Update to more accuracy timestamp
    obj->timeSrc.fnGetTimeStampLastTX(&timeResponceTX);
            
    len = MDR_PTP_FillMessPDelayRespFollowUp(ptp, obj->ctrlTx.framePTP, &obj->port, &timeResponceTX);
    obj->ctrlTx.fnSendFrame(len, PTP_MSG_PDELAY_RESP_FOLLOW_UP);    
  }
  return processed;
}


//=================   UPDATE TIME  ==============
void normalizeTime(ptp_time_t *r)
{
  uint32_t sec = r->nanoseconds / 1000000000;
	r->seconds_lsb += sec;
	r->nanoseconds -= sec * 1000000000;
}

void subTime(ptp_time_t *r, const ptp_time_t *x, const ptp_time_t *y)
{
  r->seconds_lsb = x->seconds_lsb - y->seconds_lsb;
	r->nanoseconds = x->nanoseconds - y->nanoseconds;
	normalizeTime(r);
}

void addTime(ptp_time_t *r, const ptp_time_t *x, const ptp_time_t *y)
{
  r->seconds_lsb = x->seconds_lsb + y->seconds_lsb;
	r->nanoseconds = x->nanoseconds + y->nanoseconds;
	normalizeTime(r);
}

void divTime_by2(ptp_time_t *r)
{
	r->nanoseconds += r->seconds_lsb % 2 * 1000000000;
	r->seconds_lsb /= 2;
	r->nanoseconds /= 2;
	normalizeTime(r);
}

void correctionToTimestamp(int64_t nanosec, ptp_time_t *stamp)
{
	int sign;
	/* Determine sign of result big integer number */
	if (nanosec < 0)
	{
		nanosec = -nanosec;
		sign = -1;
	}
	else
	{
		sign = 1;
	}

	// fractional nanoseconds are excluded (see 5.3.2)
	nanosec >>= 16;
  if (nanosec == 0) {
    stamp->seconds_lsb = 0;
    stamp->nanoseconds = 0;
  } else {
    stamp->seconds_lsb = sign * (nanosec / 1000000000);
    stamp->nanoseconds = sign * (nanosec % 1000000000);
  }
}


// 11.3.2 Delay request-response mechanism operational specifications
// d) Upon receipt of the Delay_Resp message by the slave:
//  meanPathDelay = [(t2 - t3) + (Delay_Resp.receiveTimestamp – Sync.originTimestamp) 
//    – Sync.correctionField – Delay_Resp.correctionField] / 2.
//  meanPathDelay = [(t2 - t3) + (Delay_Resp.receiveTimestamp – Follow_Up.preciseOriginTimestamp) 
//    - Sync.correctionField - Delay_Resp.correctionField]/2.
//
//  TimeOffset = t2 - t1 - linkDelay = t2 - t1 - ([ (t2-t1) + (t4 - t3)] / 2) = (t2-t1) - (t4 - t3) / 2
static void PTP_E2E_UpdateTime(MDR_PTP_Slave_t *obj)
{
  ptp_time_t dSync, corrSync; 
  correctionToTimestamp(obj->correctionSync, &corrSync);
  subTime(&dSync, (ptp_time_t *)&obj->stampsSync.timeRX , (ptp_time_t *)&obj->stampsSync.timeTX);
  subTime(&dSync, &dSync, &corrSync);
  
  ptp_time_t dDelayReq, corrDelayReq;
  correctionToTimestamp(obj->correctionDelayReq, &corrDelayReq);   
  subTime(&dDelayReq, (ptp_time_t *)&obj->stampsDelayReq.timeRX, (ptp_time_t *)&obj->stampsDelayReq.timeTX);
  subTime(&dDelayReq, &dDelayReq, &corrDelayReq);
  
  ptp_time_t offset;
  subTime(&offset, &dSync, &dDelayReq);
	divTime_by2(&offset);
  obj->timeSrc.fnSetTimeOffset(&offset);
}

// TimeOffset = t2-t1 - linkDelay - correction
static void PTP_P2P_UpdateTime(MDR_PTP_SlaveP2P_t *obj)
{
  ptp_time_t offset, corr;
  correctionToTimestamp(obj->correctionSync, &corr);  
  
  subTime(&offset,  (ptp_time_t *)&obj->stampsSync.timeRX ,  (ptp_time_t *)&obj->stampsSync.timeTX);
  subTime(&offset,  &offset,  (ptp_time_t *)&obj->linkDelay);
  subTime(&offset,  &offset,  &corr);
  
  obj->timeSrc.fnSetTimeOffset(&offset);  
}


//  11.4.3 Peer delay mechanism operational specifications
//  meanPathDelay = [(t4 − t1) − Pdelay_Resp.correctionField]/2
//  meanPathDelay = [(t4 − t1) − (responseOriginTimestamp − requestReceiptTimestamp) −
//  Pdelay_Resp.correctionField − Pdelay_Resp_Follow_Up.correctionField]/2
static void PTP_P2P_UpdateLinkDelay(MDR_PTP_SlaveP2P_t *obj)
{
  ptp_time_t dReq, dResp;
  ptp_time_t *dMean = (ptp_time_t *)&obj->linkDelay;
  subTime(&dReq,  (ptp_time_t *)&obj->stampsPDelayReq.timeRX ,  (ptp_time_t *)&obj->stampsPDelayReq.timeTX);
  subTime(&dResp, (ptp_time_t *)&obj->stampsPDelayResp.timeRX , (ptp_time_t *)&obj->stampsPDelayResp.timeTX);
  addTime(dMean, &dReq, &dResp);
  
  correctionToTimestamp(obj->correctionReq,  &dReq);
  correctionToTimestamp(obj->correctionResp, &dResp);
  subTime(dMean, dMean, &dReq);
  subTime(dMean, dMean, &dResp);  
	divTime_by2(dMean);  

  obj->linkDelayReady = true;  
}

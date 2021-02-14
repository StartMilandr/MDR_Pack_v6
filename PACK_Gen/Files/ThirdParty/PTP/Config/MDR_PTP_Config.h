#ifndef _MDR_PTP_CONFIG_H
#define _MDR_PTP_CONFIG_H

#include <MDR_PTP_defs.h>

// specification annex D
#define CFG_PTP_TRANSP_SPECIFIC       PTP_SDOID_MAJOR_802_1_AS  

#define CFG_PTP_VERSION               2
#define CFG_PTP_PORT_NUMBER           0x0100    // PortNum = 1, ntohs(1)

//  0 Default domain
//  1 Alternate domain 1
//  2 Alternate domain 2
//  3 Alternate domain 3
//  4-127 User-defined domains
//  128-255 Reserved
#define CFG_PTP_DOMAIN_NUMBER         4
#define CFG_PTP_CLOCK_IDENTITY        PTP_CLOCK_IDENTITY_DEF

#define CFG_PTP_BOUNDARY_HOPS         10


#define USE_PTP_TWO_STEP              1
#if USE_PTP_TWO_STEP
  #define CFG_PTP_FLAG0               PTP_FLAG0_TWO_STEP
#else
  #define CFG_PTP_FLAG0               0
#endif

#define CFG_PTP_FLAG1                 0

//  7.7.2.1 General interval specification:
//  Для каждого из типов сообщений Announce, Sync, Delay_Req и Pdelay_Req средний временной интервал
//  между последовательными сообщениями должны быть представлены как логарифм с основанием 2 этого временного интервала
//  измеряется в секундах на локальных часах устройства, отправляющего сообщение.
//  J.3.2 PTP attribute values
#define CFG_PTP_LOG_INTERVAL_ANNOUNCE               1
#define CFG_PTP_LOG_INTERVAL_SYNC                   0
//  Это значение определяется и объявляется главными часами в зависимости от их способности
//  обрабатывать трафик сообщения Delay_Req. Значение должно быть целым числом с минимальным значением
//  portDS.logSyncInterval, то есть с той же скоростью, что и сообщения синхронизации, и максимальное значение
//  logSyncInterval + 5, т.е. 1 сообщение Delay_Req каждые 32 сообщения Sync
#define CFG_PTP_LOG_INTERVAL_MIN_DELAY_REQ          0

#define CFG_PTP_LOG_INTERVAL_MIN_PDELAY_REQ         0
#define CFG_PTP_LOG_INTERVAL_SIGNALING              PTP_LOG_MESSAGE_INTERVAL_DEF
#define CFG_PTP_LOG_INTERVAL_MANAGEMENT             PTP_LOG_MESSAGE_INTERVAL_DEF


#define CFG_PTP_CLOCK_PRIORITY1       PTP_CLOCK_PRIORITY1_DEF
#define CFG_PTP_CLOCK_PRIORITY2       PTP_CLOCK_PRIORITY2_DEF
#define CFG_PTP_CLOCK_QUALITY_CLASS   PTP_CLOCK_QUALITY_CLASS_DEF
#define CFG_PTP_CLOCK_ACCURACY        PTP_CLOCK_ACCURACY_DEF
#define CFG_PTP_CLOCK_VARIANCE        PTP_CLOCK_VARIANCE_DEF
#define CFG_PTP_CLOCK_TIME_SOURCE     PTP_TIME_SRC_INT_OSC






#endif  //_MDR_PTP_CONFIG_H

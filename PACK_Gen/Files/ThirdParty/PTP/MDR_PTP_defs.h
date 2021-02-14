#ifndef _MDR_PTPDEFS_H
#define _MDR_PTPDEFS_H

#include <cmsis_compiler.h>
#include <stdint.h>

//  Examples:
//  https://github.com/richardcochran/linuxptp/blob/master/msg.h   pdt.h   ddt.h
//  https://github.com/mpthompson/stm32_f4_ptpd
//  
//  https://www.youtube.com/watch?v=ovzt3IUFbyo
//  https://www.youtube.com/watch?v=rbb9DcIGLKY

#define PTP_IP_ADDRESS        "224.0.1.129"
#define PTP_PEER_IP_ADDRESS   "224.0.0.107"

#define PTP_MAC_FORWARDED   {0x01, 0x1B, 0x19, 0x00, 0x00, 0x00}
#define PTP_MAC_PEER        {0x01, 0x80, 0xC2, 0x00, 0x00, 0x0E}

// Message types
typedef enum {
  PTP_MSG_SYNC                  = 0x0,
  PTP_MSG_DELAY_REQ             = 0x1,
  PTP_MSG_PDELAY_REQ            = 0x2,
  PTP_MSG_PDELAY_RESP           = 0x3,
  PTP_MSG_FOLLOW_UP             = 0x8,
  PTP_MSG_DELAY_RESP            = 0x9,
  PTP_MSG_PDELAY_RESP_FOLLOW_UP = 0xA,
  PTP_MSG_ANNOUNCE              = 0xB,
  PTP_MSG_SIGNALING             = 0xC,
  PTP_MSG_MANAGEMENT            = 0xD,
  //  for realizaion
  PTP_MSG_NONE                  = 0xF,
} ptp_MSG_message_e;

// Masks for ptp_header_t.flags[0]
typedef enum
{
	PTP_FLAG0_ALTERNATE_MASTER    = 0x01,
	PTP_FLAG0_TWO_STEP            = 0x02,
	PTP_FLAG0_UNICAST             = 0x04,
	PTP_FLAG0_PROFILE_SPECIFIC_1  = 0x20,
	PTP_FLAG0_PROFILE_SPECIFIC_2  = 0x40,
	PTP_FLAG0_SECURITY            = 0x80,
} ptp_hdr_flag0_e;

// Masks for ptp_header_t.flags[1]
typedef enum
{
	PTP_FLAG1_LEAP61              = 0x01,
	PTP_FLAG1_LEAP59              = 0x02,
	PTP_FLAG1_UTC_OFFSET_VALID    = 0x04,
	PTP_FLAG1_PTP_TIMESCALE       = 0x08,
	PTP_FLAG1_TIME_TRACEABLE      = 0x10,
	PTP_FLAG1_FREQUENCY_TRACEABLE = 0x20,
} ptp_hdr_flag1_e;


//  Type defs
typedef __PACKED_STRUCT {
	uint16_t            seconds_msb;
	uint32_t            seconds_lsb; // 48 bits
	uint32_t            nanoseconds;
} ptp_timestamp_t;

#define PTP_LEN_TIMESTAMP        10
#define PTP_LEN_CLOCK_IDENTITY   8

typedef __PACKED_STRUCT {
	uint8_t             id[PTP_LEN_CLOCK_IDENTITY];
} ptp_clock_ident_t;

#define PTP_CLOCK_IDENTITY_DEF  {0x18, 0x8B, 0x9D, 0xFF, 0xFE, 0x75, 0xEC, 0x00}
#define PTP_CLOCK_IDENTITY_GPS  {0x08, 0x96, 0xAD, 0xFF, 0xFE, 0xA8, 0x01, 0x00}

typedef __PACKED_STRUCT {
	uint8_t             clockClass;
	uint8_t             clockAccuracy;
	uint16_t            offsetScaledLogVariance;
} ptp_clock_quality_t;

#define PTP_CLOCK_QUALITY_CLASS_DEF   248
#define PTP_CLOCK_QUALITY_CLASS_GPS     6
#define PTP_CLOCK_ACCURACY_DEF        0xFE
#define PTP_CLOCK_VARIANCE_DEF        5000 // 802.1AS


typedef __PACKED_STRUCT  {
	ptp_clock_ident_t   clockIdent;
	uint16_t            portNum;  // number of ptp ports
} ptp_port_ident_t;

#define PTP_LEN_PORT_IDENT   10

typedef enum
{
	PTP_CTRL_SYNC      = 0x00,
	PTP_CTRL_DELAY_REQ,
	PTP_CTRL_FOLLOW_UP,
	PTP_CTRL_DELAY_RESP,
	PTP_CTRL_MANAGEMENT,
	PTP_CTRL_OTHER,
} ptp_hdr_ctrl_e;

// CORRECTION:
// The correction field is measured in nanoseconds and is multiplied by 2^16. 
// For example 2.5ns is represented by the 64 bit value 0x0000000000028000 and is transmitted most significant byte first.
//
//Message type | correctionField description
//Sync:         Corrections for fractional nanoseconds, residence time in transparent clocks (see 11.5.2),
//              path delay in peer-to-peer clocks (see 11.4.5.1), and asymmetry corrections (see 11.6.2)
//Delay_Req:    Corrections for fractional nanoseconds, residence time in transparent clocks (see 11.5.3),
//              and asymmetry corrections (see 11.6.3)
//Pdelay_Req:   Corrections for fractional nanoseconds, residence time in transparent clocks (see 11.5.4),
//              and asymmetry corrections (see 11.6.4)
//Pdelay_Resp:  Corrections for fractional nanoseconds, residence time in transparent clocks (see 11.5.4),
//              and asymmetry corrections (see 11.6.5)
//Follow_Up:    Corrections for fractional nanoseconds, residence time in transparent clocks (see 11.5.2),
//              path delay in peer-to-peer clocks (see 11.4.5.1), and asymmetry corrections (see 11.6.2)
//Delay_Resp:   Corrections for fractional nanoseconds, residence time in transparent clocks (see 11.5.3),
//              and asymmetry corrections (see 11.6.3)
//Pdelay_Resp_Follow_Up: Corrections for fractional nanoseconds, residence time in transparent clocks (see 11.5.4),
//              and asymmetry corrections (see 11.6.4 and 11.6.5)
//Announce:     Zero
//Signaling:    Zero
//Management:   Zero


typedef __PACKED_STRUCT {
	uint8_t             mess_transp;
	uint8_t             version;    
	uint16_t            messLen;    
	uint8_t             domainNum;
	uint8_t             _reserved1;
	uint8_t             flags[2];
	uint64_t            correction;
	uint32_t            _reserved2;
	ptp_port_ident_t    srcPortId;
	uint16_t            seqId;
	uint8_t             control;
	int8_t              logMessInterval;
} ptp_header_t;

#define PTP_MESS_Msk   0x0F

#define PTP_SDOID_MAJOR_802_1_AS      0x80
#define PTP_SDOID_MINOR_802_1_AS      0
// Table 24 Values of logMessageInterval field
#define PTP_LOG_MESSAGE_INTERVAL_DEF  0x7F

#define PTP_PORTID_SOURCE_LINK_MASTER   0
#define PTP_PORTID_RESERVED             0xFFFF

//  ----------    PTP messages  -------------

#define PTP_LEN_HEADER                 34
#define PTP_LEN_ANNOUNCE               64
#define PTP_LEN_SYNC                   44
#define PTP_LEN_FOLLOW_UP              44
#define PTP_LEN_PDELAY_REQ             54
#define PTP_LEN_DELAY_REQ              44
#define PTP_LEN_DELAY_RESP             54
#define PTP_LEN_PDELAY_RESP            54
#define PTP_LEN_PDELAY_RESP_FOLLOW_UP  54
#define PTP_LEN_MANAGEMENT             48
#define PTP_LEN_SIGNALING              44

#define PTP_MSG_LEN_MAX                PTP_LEN_ANNOUNCE



typedef enum
{
	PTP_TIME_SRC_ATOMIC_CLOCK        = 0x10,
	PTP_TIME_SRC_GPS                 = 0x20,
	PTP_TIME_SRC_TERRESTRIAL_RADIO   = 0x30,
	PTP_TIME_SRC_PTP                 = 0x40,
	PTP_TIME_SRC_NTP                 = 0x50,
	PTP_TIME_SRC_HAND_SET            = 0x60,
	PTP_TIME_SRC_OTHER               = 0x90,
	PTP_TIME_SRC_INT_OSC             = 0xA0
} ptp_clock_time_source_e;

typedef __PACKED_STRUCT {
	ptp_header_t        hdr;
	ptp_timestamp_t     originTimestamp;
	uint16_t            currentUtcOffset;         // 0
	uint8_t             reserved;
	uint8_t             grandmasterPriority1;
	ptp_clock_quality_t grandmasterClockQuality;
	uint8_t             grandmasterPriority2;
	ptp_clock_ident_t   grandmasterIdentity;
	uint16_t            stepsRemoved;             // 0
	uint8_t             timeSource;
	uint8_t             suffix[0];
} ptp_msg_announce_t;

#define PTP_CLOCK_PRIORITY1_DEF   128
#define PTP_CLOCK_PRIORITY2_DEF   128

typedef __PACKED_STRUCT  {
	ptp_header_t      hdr;
	ptp_timestamp_t   originTimestamp;
} ptp_msg_sync_t;

typedef __PACKED_STRUCT  {
	ptp_header_t      hdr;
	ptp_timestamp_t   preciseOriginTimestamp;
//	uint8_t           suffix[0];
} ptp_msg_follow_up_t;

typedef __PACKED_STRUCT  {
	ptp_header_t      hdr;
	ptp_timestamp_t   originTimestamp;
//	uint8_t           suffix[0];
} ptp_msg_delay_req_t;

typedef __PACKED_STRUCT  {
	ptp_header_t      hdr;
	ptp_timestamp_t   receiveTimestamp;
	ptp_port_ident_t  requestingPortIdentity;
	uint8_t           suffix[0];
} ptp_msg_delay_resp_t;

typedef __PACKED_STRUCT  {
	ptp_header_t      hdr;
	ptp_timestamp_t   originTimestamp;
	ptp_port_ident_t  reserved;
} ptp_msg_pdelay_req_t;


//  6.6.4 Measuring link propagation delay in clocks supporting peer-to-peer path correction:
//  1. returns the difference between the timestamps t2 and t3 in the Pdelay_Resp message
//  2. returns the difference between the timestamps t2 and t3 in a Pdelay_Resp_Follow_Up message
//  3. returns the timestamps t2 and t3 in the Pdelay_Resp and Pdelay_Resp_Follow_Up messages respectively (gPTP - 802.1AS)
typedef __PACKED_STRUCT  {
	ptp_header_t      hdr;
	ptp_timestamp_t   requestReceiptTimestamp;
	ptp_port_ident_t  requestingPortIdentity;
} ptp_msg_pdelay_resp_t;

typedef __PACKED_STRUCT  {
	ptp_header_t      hdr;
	ptp_timestamp_t   responseOriginTimestamp;
	ptp_port_ident_t  requestingPortIdentity;
	uint8_t           suffix[0];
} ptp_msg_pdelay_resp_fup_t;

typedef __PACKED_STRUCT  {
	ptp_header_t      hdr;
	ptp_timestamp_t   targetPortIdentity;
	uint8_t           suffix[0];
} ptp_msg_signaling_t;

typedef __PACKED_STRUCT  {
	ptp_header_t      hdr;
	ptp_port_ident_t  targetPortIdentity;
	uint8_t           startingBoundaryHops;
	uint8_t           boundaryHops;
	uint8_t           actionField;
	uint8_t           reserved;
	uint8_t           suffix[0];
} ptp_msg_management_t;

typedef enum {
  PTP_MNG_GET = 0,
  PTP_MNG_SET,
  PTP_MNG_RESPONCE,
  PTP_MNG_COMMAND,
  PTP_MNG_ACK
} ptp_msg_manage_actions_e;
  


//  ----------    TLV ---------
#define PTP_TLV_TYPE_MANAGEMENT           1
#define PTP_TLV_TYPE_MANAGEMENT_ERR       2
#define PTP_TLV_TYPE_ORGANIZATION_EXT     3
#define PTP_TLV_TYPE_REQUEST_UNICAST      4
#define PTP_TLV_TYPE_GRANT_UNICAST        5
#define PTP_TLV_TYPE_CANCEL_UNICAST       6
#define PTP_TLV_TYPE_CANCEL_UC_ACK        7
#define PTP_TLV_TYPE_PATH_TRACE           8
#define PTP_TLV_TYPE_ALT_TIME_OFFS        9
#define PTP_TLV_TYPE_AUTHENTICATION       0x2000
#define PTP_TLV_TYPE_AUTH_CHALLENGE       0x2001
#define PTP_TLV_TYPE_SECURITY_UPD         0x2002
#define PTP_TLV_TYPE_FREQ_FACTOR_OFFS     2003

typedef __PACKED_STRUCT  {
  uint16_t tlvType;
  uint16_t lengthField;   // Length of valueField[lengthField]
  uint8_t  valueField[0];
} ptp_tlv_t;

#define PTP_TLV_LEN_nVALUE  4

typedef __PACKED_STRUCT  {
  uint16_t tlvType;       // always PTP_TLV_TYPE_MANAGEMENT
  uint16_t lengthField;   // Length of valueField[lengthField] + managmentID
  uint16_t managmentID;
  uint16_t valueField[0];
} ptp_tlv_manage_t;

#define PTP_TLV_MNG_LEN_nVALUE  6

//  Some of Management TLV values
#define PTP_MNG_VAL_NULL_MANAGEMENT          0    // Set/Get/Command
#define PTP_MNG_VAL_ENABLE_PORT         0x200D    // Command
#define PTP_MNG_VAL_DISABLE_PORT        0x200E    // Command
#define PTP_MNG_VAL_PATH_TRACE_ENABLE   0x2016    // Set/Get


typedef __PACKED_STRUCT {
	int16_t            _unused;
	int32_t            seconds_lsb;
	int32_t            nanoseconds;
} ptp_time_t;

typedef struct {
  ptp_timestamp_t  timeTX;
  ptp_timestamp_t  timeRX;
  uint64_t         correction;
} MDR_PTP_TimeTxRx;


#endif //_MDR_PTPDEFS_H

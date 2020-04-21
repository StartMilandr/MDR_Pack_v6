#ifndef _MDR_PRP_DEFS_H
#define _MDR_PRP_DEFS_H

//#include <MDR_Config.h>
#include <MDR_Funcs.h>
#include <MDR_Ethernet.h>
#include <MDR_Ethernet_FrameDefs.h>

#define ETH_SUFF_PRP      ETH_TYPE_PRP_SUP

//#define ETH_PRP_LAN_ID_A      0xA
//#define ETH_PRP_LAN_ID_B      0xB


typedef __PACKED_STRUCT { 
  uint16_t        seqNum; 
  uint16_t        lanID_LSDUSize;
  uint16_t        suffPRP;  
} MDR_PRP_Tag_t;

#define MDR_PRP_TAG_LEN       sizeof(MDR_PRP_Tag_t)

//typedef __PACKED_STRUCT { 
//	uint8_t         multyMAC[6];
//	uint8_t         nodeMAC[6];
//  MDR_HSR_Tag_t   tagHSR;  
//	uint16_t        supEtherType;     // ETH_TYPE_PRP = 0x88FB  
//  uint16_t        supPath_Vers;     // ETH_PRP_SUP_PATH_VERSION
//  uint16_t        supSeqNum;        
//  uint16_t        TLV1;             // const 0x2300: type = 23, len = 6
//  uint8_t         DANP_MAC[6];
//  uint16_t        TLV2;             // const 0x2300: type = 23, len = 6
//  uint8_t         RedBoxMAC[6];
//  uint16_t        TLV3;             // const 0x0000: type = 0,  len = 0
//  uint8_t         pad_to70[];         //  fill to 70 bytes frameLen
//} MDR_HSR_SupHeader_t;

//typedef __PACKED_STRUCT { 
//	uint8_t         multyMAC[6];
//	uint8_t         nodeMAC[6];
//  eth_VLAN_tag_t  tagVLAN;          // - VLAN TAG  
//  MDR_HSR_Tag_t   tagHSR;  
//	uint16_t        supEtherType;     // ETH_TYPE_PRP = 0x88FB  
//  uint16_t        supPath_Vers;     // ETH_PRP_SUP_PATH_VERSION
//  uint16_t        supSeqNum;
//  uint16_t        TLV1;             // const 0x2300: type = 23, len = 6
//  uint8_t         DANP_MAC[6];
//  uint16_t        TLV2;             // const 0x2300: type = 23, len = 6
//  uint8_t         RedBoxMAC[6];
//  uint16_t        TLV3;             // const 0x0000: type = 0,  len = 0
//  uint8_t         pad_to74[];         // fill to 74 bytes frameLen
//} MDR_HSR_SupHeader_VLAN_t;




//typedef enum {
//  MDR_HSR_HsrForw = 0,      //  H (default): shall insert the HSR tag on behalf of its host and shall forward the ring traffic, except for
//                        //     frames sent by the node itself, duplicate frames and frames for which the node is the unique destination.
//  MDR_HSR_NoForw,       //  N: like mode H with the exception that it shall not forward ring traffic from port to port.
//  MDR_HSR_TranspForw,   //  T: shall remove the HSR tag before forwarding the frame to the other port and shall send a frame from the host to
//                        //     both ports, untagged and without discarding duplicates.
//  MDR_HSR_MixedForw,    //  M: shall insert the HSR tag depending on local criteria when injecting frames into the
//                        //     ring. HSR tagged frames from ring ports are handled according to Mode H. Non-HSR
//                        //     tagged frames from ring ports are handled according to IEEE 802.1D forwarding rules.
//  MDR_HSR_UnicastForw,  //  U: shall behave as in Mode H, except that it shall also forward traffic for which it is the unique destination.
//  MDR_HSR_XForw,        //  X: No sending on counter-duplicate – in this mode, the node shall behave
//                        //     as in Mode H, except that a port shall not send a frame that is a duplicate of a frame that it
//                        //     received completely and correctly from the opposite direction.
//} MDT_HSR_ForwMode_t;


//typedef enum {
//  MDR_HSR_RedBox_HSR_SAN = 0,
//  MDR_HSR_RedBox_HSR_PRP = 0,
//  MDR_HSR_RedBox_HSR_HSR = 0,
//} MDT_HSR_RedBox_ForwMode_t;


//#define MDR_HSR_TAG_LEN       sizeof(MDR_HSR_Tag_t)
//#define MDR_ETH_TYPE_FLD_LEN  sizeof(uint16_t)

//typedef __PACKED_STRUCT {
//  uint8_t          spaceForTag[MDR_HSR_TAG_LEN + MDR_ETH_TYPE_FLD_LEN];
//  MDR_ETH_FrameTX  frameTX;
//} MDR_HSR_FrameContainer;


//typedef __PACKED_STRUCT {
//	uint8_t       to_addr[6];
//	uint8_t       from_addr[6];
//	uint16_t      type_HSR;
//  MDR_HSR_Tag_t tag_HSR;
//  uint16_t      type;
//	uint8_t       payload[];
//} MDR_HSR_TaggedFrame;

//typedef __PACKED_STRUCT {
//  uint32_t              frameLen;
//	MDR_HSR_TaggedFrame   tagFrame;
//} MDR_HSR_TaggedFrameTX;




#endif  // _MDR_PRP_DEFS_H

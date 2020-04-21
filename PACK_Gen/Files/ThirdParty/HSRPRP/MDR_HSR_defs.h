#ifndef _MDR_HSR_DEFS_H
#define _MDR_HSR_DEFS_H

//#include <MDR_Config.h>
#include <MDR_Funcs.h>
#include <MDR_Ethernet.h>
#include <MDR_Ethernet_FrameDefs.h>

//	---------------		HSR tag	-----------------------
typedef __PACKED_STRUCT { 
  uint16_t        etherType;               //  ETH_TYPE_HSR      0x892F
  uint16_t        lanID_LSDUSize;
  uint16_t        seqNum; 
} MDR_HSR_Tag_t;

#define MDR_HSR_TAG_LEN           sizeof(MDR_HSR_Tag_t)
#define MDR_HSR_TAG_LSDU_LEN		 (sizeof(MDR_HSR_Tag_t) - MDR_ETH_TYPE_LEN)
	



#define  ETH_HSR_SUP_ETHER_TYPE    ETH_TYPE_PRP_SUP

#define  HSR_SUP_DEST_MAC_b0 0x01
#define  HSR_SUP_DEST_MAC_b1 0x15
#define  HSR_SUP_DEST_MAC_b2 0x4E
#define  HSR_SUP_DEST_MAC_b3 0x00
#define  HSR_SUP_DEST_MAC_b4 0x01
#define  HSR_SUP_DEST_MAC_b5 0x00 		// XX - Can be any

#define ETH_HSR_SUP_DEST_MAC_INIT		{HSR_SUP_DEST_MAC_b0, HSR_SUP_DEST_MAC_b1, HSR_SUP_DEST_MAC_b2, HSR_SUP_DEST_MAC_b3, HSR_SUP_DEST_MAC_b4, HSR_SUP_DEST_MAC_b5}

#define ETH_PRP_SUP_PATH_VERSION		1

//typedef union { 
//  uint16_t                  lanID_LSDUSize;
//  Eth_PRP_LanID_LSDUSize_t  lanID_LSDUSize_b;
//} ;   

//typedef __PACKED_STRUCT { 
//  uint16_t        etherType;               //  ETH_TYPE_HSR      0x892F
//  uint16_t        lanID_LSDUSize;
//  uint16_t        seqNum; 
//} MDR_HSR_Tag_t;

//#define MDR_HSR_TAG_LEN        		sizeof(MDR_HSR_Tag_t)
//#define MDR_HSR_TAG_ETH_TYPE_LEN	sizeof(uint16_t)
////  Часть MDR_HSR_Tag_t входящая в LSDU_Size (+= sizeof(Payload))
//#define MDR_HSR_TAG_LSDU_LEN		 (sizeof(MDR_HSR_Tag_t) - MDR_HSR_TAG_ETH_TYPE_LEN)


typedef __PACKED_STRUCT { 
	uint8_t         multyMAC[6];
	uint8_t         nodeMAC[6];
  MDR_HSR_Tag_t   tagHSR;  
	uint16_t        supEtherType;       // ETH_TYPE_PRP = 0x88FB  
  uint16_t        supPath_Vers;       // ETH_PRP_SUP_PATH_VERSION
  uint16_t        supSeqNum;        
  uint16_t        TLV1;               // const 0x2300: type = 23, len = 6
  uint8_t         DANP_MAC[6];
  uint16_t        TLV2;               // const 0x0000: type = 0,  len = 0
  uint16_t        TLV3;               // const 0x0000: type = 0,  len = 0
  uint8_t         pad_to70[];         //  fill to 70 bytes frameLen
} MDR_HSR_SupHeader_DANH_t;

#define MDR_HSR_SUPER_DANH_HEADER_LEN		36
#define MDR_HSR_SUPER_DANH_FRAME_LEN 		66
#define MDR_HSR_SUPER_DANH_LSDU_LEN  		52


typedef __PACKED_STRUCT { 
	uint8_t         multyMAC[6];
	uint8_t         nodeMAC[6];
  MDR_HSR_Tag_t   tagHSR;  
	uint16_t        supEtherType;     // ETH_TYPE_PRP = 0x88FB  
  uint16_t        supPath_Vers;     // ETH_PRP_SUP_PATH_VERSION
  uint16_t        supSeqNum;        
  uint16_t        TLV1;             // const 0x2300: type = 23, len = 6
  uint8_t         DANP_MAC[6];
  uint16_t        TLV2;             // const 0x2300: type = 23, len = 6
  uint8_t         RedBoxMAC[6];
  uint16_t        TLV3;             // const 0x0000: type = 0,  len = 0
  uint8_t         pad_to70[];         //  fill to 70 bytes frameLen
} MDR_HSR_SupHeader_RedBox_t;

#define MDR_HSR_SupHdr_TLV1					0x1706
#define MDR_HSR_SupHdr_TLV2_Empty		0x0000
#define MDR_HSR_SupHdr_TLV2_RedBox  0x1E06
#define MDR_HSR_SupHdr_TLV3					0x0000

#define MDR_HSR_SuperFrameTag			MDR_HSR_SupHeader_RedBox_t


typedef __PACKED_STRUCT { 
	uint8_t         multyMAC[6];
	uint8_t         nodeMAC[6];
  eth_VLAN_tag_t  tagVLAN;          // - VLAN TAG  
  MDR_HSR_Tag_t   tagHSR;  
	uint16_t        supEtherType;     // ETH_TYPE_PRP = 0x88FB  
  uint16_t        supPath_Vers;     // ETH_PRP_SUP_PATH_VERSION
  uint16_t        supSeqNum;
  uint16_t        TLV1;             // const 0x2300: type = 23, len = 6
  uint8_t         DANP_MAC[6];
  uint16_t        TLV2;             // const 0x2300: type = 23, len = 6
  uint8_t         RedBoxMAC[6];
  uint16_t        TLV3;             // const 0x0000: type = 0,  len = 0
  uint8_t         pad_to74[];         // fill to 74 bytes frameLen
} MDR_HSR_SupHeader_VLAN_t;




typedef enum {
  MDR_HSR_HsrForw = 0,      //  H (default): shall insert the HSR tag on behalf of its host and shall forward the ring traffic, except for
                        //     frames sent by the node itself, duplicate frames and frames for which the node is the unique destination.
  MDR_HSR_NoForw,       //  N: like mode H with the exception that it shall not forward ring traffic from port to port.
  MDR_HSR_TranspForw,   //  T: shall remove the HSR tag before forwarding the frame to the other port and shall send a frame from the host to
                        //     both ports, untagged and without discarding duplicates.
  MDR_HSR_MixedForw,    //  M: shall insert the HSR tag depending on local criteria when injecting frames into the
                        //     ring. HSR tagged frames from ring ports are handled according to Mode H. Non-HSR
                        //     tagged frames from ring ports are handled according to IEEE 802.1D forwarding rules.
  MDR_HSR_UnicastForw,  //  U: shall behave as in Mode H, except that it shall also forward traffic for which it is the unique destination.
  MDR_HSR_XForw,        //  X: No sending on counter-duplicate – in this mode, the node shall behave
                        //     as in Mode H, except that a port shall not send a frame that is a duplicate of a frame that it
                        //     received completely and correctly from the opposite direction.
} MDT_HSR_ForwMode_t;


typedef enum {
  MDR_HSR_RedBox_HSR_SAN,
  MDR_HSR_RedBox_HSR_PRP,
  MDR_HSR_RedBox_HSR_HSR,
} MDT_HSR_RedBox_ForwMode_t;


#define MDR_ETH_TYPE_FLD_LEN  sizeof(uint16_t)

typedef __PACKED_STRUCT {
  uint8_t          spaceForTag[MDR_HSR_TAG_LEN + MDR_ETH_TYPE_FLD_LEN];
  MDR_ETH_FrameTX  frameTX;
} MDR_HSR_FrameContainer;


typedef __PACKED_STRUCT {
	uint8_t       to_addr[6];
	uint8_t       from_addr[6];
	uint16_t      type_HSR;
  MDR_HSR_Tag_t tag_HSR;
  uint16_t      type;
	uint8_t       payload[];
} MDR_HSR_TaggedFrame;

typedef __PACKED_STRUCT {
  uint32_t              frameLen;
	MDR_HSR_TaggedFrame   tagFrame;
} MDR_HSR_TaggedFrameTX;






#endif  // _MDR_HSR_DEFS_H

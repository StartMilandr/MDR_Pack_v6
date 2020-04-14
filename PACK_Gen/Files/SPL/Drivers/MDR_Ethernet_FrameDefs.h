#ifndef MDR_ETHERNET_FRAME_DEFS_H
#define MDR_ETHERNET_FRAME_DEFS_H

#include <stdint.h>
#include <stdbool.h>

/* ========================================  Start of section using anonymous unions  ======================================== */
#if defined (__CC_ARM)
  #pragma push
  #pragma anon_unions
	
	#include <cmsis_armcc.h>	
	
#elif defined (__ICCARM__)
  #pragma language=extended
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wc11-extensions"
  #pragma clang diagnostic ignored "-Wreserved-id-macro"
  #pragma clang diagnostic ignored "-Wgnu-anonymous-struct"
  #pragma clang diagnostic ignored "-Wnested-anon-types"
	
	#include <cmsis_armclang.h>	
	
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning 586
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif
/* ========================================  Start of section using anonymous unions  ======================================== */

#define MDR_ETH_FRAME_LEN_MAX         1518
#define MDR_ETH_VLAN_TAG_LEN_MAX      4
#define MDR_ETH_FRAME_VLAN_LEN_MAX    (MDR_ETH_FRAME_LEN_MAX + MDR_ETH_VLAN_TAG_LEN_MAX)


//  From here, thanks a lot!!!
//  http://we.easyelectronics.ru/electro-and-pc/podklyuchenie-mikrokontrollera-k-lokalnoy-seti-tcp-klient.html



/*
 * BE conversion, HostToNex, NetToHost
 */

#define htons(a)			((((a)>>8)&0xff)|(((a)<<8)&0xff00))
#define ntohs(a)			htons(a)

#define htonl(a)			( (((a)>>24)&0xff) | (((a)>>8)&0xff00) |\
                      (((a)<<8)&0xff0000) | (((a)<<24)&0xff000000) )
#define ntohl(a)			htonl(a)

#define ETH_CRC_SIZE      4

/*
 * Ethernet
 */
 
#define ETH_TYPE_ARP		  htons(0x0806)
#define ETH_TYPE_IP			  htons(0x0800)
#define ETH_TYPE_VLAN     htons(0x8100)
#define ETH_TYPE_VLAND    htons(0x9100)
#define ETH_TYPE_ETHERCAT htons(0x88A4)
#define ETH_TYPE_HSR      htons(0x892F)
#define ETH_TYPE_PRP_SUP  htons(0x88FB)

typedef __PACKED_STRUCT eth_frame {
	uint8_t  to_addr[6];
	uint8_t  from_addr[6];
	uint16_t type;
	uint8_t  payload[];
} eth_frame_t;


#define MDR_ETH_MAC_LEN               6
#define MDR_ETH_HEADER_LEN						(MDR_ETH_MAC_LEN * 2 + sizeof(uint16_t))
#define MDR_ETH_CRC_LEN               4
#define MDR_ETH_TYPE_LEN              2

__STATIC_INLINE bool IsFrameTypeEQ(const eth_frame_t *frame, uint16_t etherType)
{
  return frame->type == etherType;
}

#define IsFrameARP(frm)       IsFrameTypeEQ(frm, ETH_TYPE_ARP)
#define IsFrameIP(frm)        IsFrameTypeEQ(frm, ETH_TYPE_IP)
#define IsFrameVLAN(frm)      IsFrameTypeEQ(frm, ETH_TYPE_VLAN)
#define IsFrameVLAND(frm)     IsFrameTypeEQ(frm, ETH_TYPE_VLAND)
#define IsFrameEtherCAT(frm)  IsFrameTypeEQ(frm, ETH_TYPE_ETHERCAT)
#define IsFrameHSR(frm)       IsFrameTypeEQ(frm, ETH_TYPE_HSR)
#define IsFrameSuperPRP(frm)  IsFrameTypeEQ(frm, ETH_TYPE_PRP_SUP)

/*
 * Ethernet TAG
 */

typedef __PACKED_STRUCT eth_frame_tag {
	uint8_t  to_addr[6];
	uint8_t  from_addr[6];
	uint16_t TPID;    //  Tag protocol ID
  uint16_t TCID;    //  Tag control ID
  uint16_t type;
	uint8_t  payload[];
} eth_frame_tag_t;

__STATIC_INLINE bool IsTagFrameTypeEQ(const eth_frame_tag_t *frame, uint16_t etherType)
{
  return frame->type == etherType;
}

#define IsTagFrameARP(frm)       IsTagFrameTypeEQ(frm, ETH_TYPE_ARP)
#define IsTagFrameIP(frm)        IsTagFrameTypeEQ(frm, ETH_TYPE_IP)
#define IsTagFrameVLAN(frm)      IsTagFrameTypeEQ(frm, ETH_TYPE_VLAN)
#define IsTagFrameVLAND(frm)     IsTagFrameTypeEQ(frm, ETH_TYPE_VLAND)
#define IsTagFrameEtherCAT(frm)  IsTagFrameTypeEQ(frm, ETH_TYPE_ETHERCAT)
#define IsTagFrameHSR(frm)       IsTagFrameTypeEQ(frm, ETH_TYPE_HSR)
#define IsTagFrameSuperPRP(frm)  IsTagFrameTypeEQ(frm, ETH_TYPE_PRP_SUP)


/*
 * Ethernet TAG - VLAN
 */

typedef __PACKED_STRUCT eth_VLAN_tag {
  uint16_t            TPID;
  uint16_t            TCID;
} eth_VLAN_tag_t;  

typedef __PACKED_STRUCT eth_frame_VLAN_tag {
	uint8_t         to_addr[6];
	uint8_t         from_addr[6];
  eth_VLAN_tag_t  tagVLAN;
  uint16_t        type;
	uint8_t         payload[];
} eth_frame_LVAN_t;


__STATIC_INLINE bool IsFrameTypeEQ_VLAN(const eth_frame_LVAN_t *frame, uint16_t etherType)
{
  return frame->type == etherType;
}

#define IsFrameARP_VLAN(frm)       IsFrameTypeEQ_VLAN(frm, ETH_TYPE_ARP)
#define IsFrameIP_VLAN(frm)        IsFrameTypeEQ_VLAN(frm, ETH_TYPE_IP)
#define IsFrameVLAN_VLAN(frm)      IsFrameTypeEQ_VLAN(frm, ETH_TYPE_VLAN)
#define IsFrameVLAND_VLAN(frm)     IsFrameTypeEQ_VLAN(frm, ETH_TYPE_VLAND)
#define IsFrameEtherCAT_VLAN(frm)  IsFrameTypeEQ_VLAN(frm, ETH_TYPE_ETHERCAT)
#define IsFrameHSR_VLAN(frm)       IsFrameTypeEQ_VLAN(frm, ETH_TYPE_HSR)
#define IsFrameSuperPRP_VLAN(frm)  IsFrameTypeEQ_VLAN(frm, ETH_TYPE_PRP_SUP)



/*
 * ARP
 */

#define ARP_HW_TYPE_ETH		  htons(0x0001)
#define ARP_PROTO_TYPE_IP	  htons(0x0800)

#define ARP_TYPE_REQUEST	  htons(1)
#define ARP_TYPE_RESPONSE	  htons(2)

typedef struct arp_message {
	uint16_t  hw_type;
	uint16_t  proto_type;
	uint8_t   hw_addr_len;
	uint8_t   proto_addr_len;
	uint16_t  type;
	uint8_t   mac_addr_from[6];
	uint32_t  ip_addr_from;
	uint8_t   mac_addr_to[6];
	uint32_t  ip_addr_to;
} arp_message_t;

typedef struct arp_cache_entry {
	uint32_t  ip_addr;
	uint8_t   mac_addr[6];
} arp_cache_entry_t;

/*
 * IP
 */

#define IP_PROTOCOL_ICMP	  1
#define IP_PROTOCOL_TCP		  6
#define IP_PROTOCOL_UDP		  17

typedef struct ip_packet {
	uint8_t   ver_head_len;
	uint8_t   tos;
	uint16_t  total_len;
	uint16_t  fragment_id;
	uint16_t  flags_framgent_offset;
	uint8_t   ttl;
	uint8_t   protocol;
	uint16_t  cksum;
	uint32_t  from_addr;
	uint32_t  to_addr;
	uint8_t   data[];
} ip_packet_t;


/*
 * ICMP
 */

#define ICMP_TYPE_ECHO_RQ	    8
#define ICMP_TYPE_ECHO_RPLY	  0

typedef struct icmp_echo_packet {
	uint8_t   type;
	uint8_t   code;
	uint16_t  cksum;
	uint16_t  id;
	uint16_t  seq;
	uint8_t   data[];
} icmp_echo_packet_t;


/*
 * UDP
 */

typedef struct udp_packet {
	uint16_t  from_port;
	uint16_t  to_port;
	uint16_t  len;
	uint16_t  cksum;
	uint8_t   data[];
} udp_packet_t;


/*
 * DHCP
 */

#define DHCP_SERVER_PORT		htons(67)
#define DHCP_CLIENT_PORT		htons(68)

#define DHCP_OP_REQUEST			1
#define DHCP_OP_REPLY			  2

#define DHCP_HW_ADDR_TYPE_ETH	1

#define DHCP_FLAG_BROADCAST		htons(0x8000)

#define DHCP_MAGIC_COOKIE		  htonl(0x63825363)

typedef struct dhcp_message {
	uint8_t   operation;
	uint8_t   hw_addr_type;
	uint8_t   hw_addr_len;
	uint8_t   unused1;
	uint32_t  transaction_id;
	uint16_t  second_count;
	uint16_t  flags;
	uint32_t  client_addr;
	uint32_t  offered_addr;
	uint32_t  server_addr;
	uint32_t  unused2;
	uint8_t   hw_addr[16];
	uint8_t   unused3[192];
	uint32_t  magic_cookie;
	uint8_t   options[];
} dhcp_message_t;

#define DHCP_CODE_PAD			      0
#define DHCP_CODE_END			      255
#define DHCP_CODE_SUBNETMASK	  1
#define DHCP_CODE_GATEWAY		    3
#define DHCP_CODE_REQUESTEDADDR	50
#define DHCP_CODE_LEASETIME		  51
#define DHCP_CODE_MESSAGETYPE	  53
#define DHCP_CODE_DHCPSERVER	  54
#define DHCP_CODE_RENEWTIME		  58
#define DHCP_CODE_REBINDTIME	  59

typedef struct dhcp_option {
	uint8_t code;
	uint8_t len;
	uint8_t data[];
} dhcp_option_t;

#define DHCP_MESSAGE_DISCOVER	  1
#define DHCP_MESSAGE_OFFER		  2
#define DHCP_MESSAGE_REQUEST	  3
#define DHCP_MESSAGE_DECLINE	  4
#define DHCP_MESSAGE_ACK		    5
#define DHCP_MESSAGE_NAK		    6
#define DHCP_MESSAGE_RELEASE	  7
#define DHCP_MESSAGE_INFORM		  8

typedef enum dhcp_status_code {
	DHCP_INIT,
	DHCP_ASSIGNED,
	DHCP_WAITING_OFFER,
	DHCP_WAITING_ACK
} dhcp_status_code_t;


/* =========================================  End of section using anonymous unions  ========================================= */
#if defined (__CC_ARM)
  #pragma pop
#elif defined (__ICCARM__)
  /* leave anonymous unions enabled */
#elif (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic pop
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning restore
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#endif
/* =========================================  End of section using anonymous unions  ========================================= */



#endif // MDR_ETHERNET_FRAME_DEFS_H


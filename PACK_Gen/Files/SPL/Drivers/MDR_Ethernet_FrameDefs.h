#ifndef MDR_ETHERNET_FRAME_DEFS_H
#define MDR_ETHERNET_FRAME_DEFS_H

#include <stdint.h>

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

typedef struct eth_frame {
	uint8_t  to_addr[6];
	uint8_t  from_addr[6];
	uint16_t type;
	uint8_t  payload[];
} eth_frame_t;

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

#endif // MDR_ETHERNET_FRAME_DEFS_H


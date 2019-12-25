/**
 * @file
 * Ethernet Interface Skeleton
 *
 */

/*
 * Copyright (c) 2001-2004 Swedish Institute of Computer Science.
 * All rights reserved. 
 * 
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission. 
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR IMPLIED 
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF 
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT 
 * SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT 
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING 
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY 
 * OF SUCH DAMAGE.
 *
 * This file is part of the lwIP TCP/IP stack.
 * 
 * Author: Adam Dunkels <adam@sics.se>
 *
 */

/*
 * This file is a skeleton for developing Ethernet network interface
 * drivers for lwIP. Add code to the low_level functions and do a
 * search-and-replace for the word "ethernetif" to replace it with
 * something that better describes your network interface.
 */

#include <MDR_Config.h>

#include "lwip/pbuf.h"
#include "lwip/stats.h"
#include "netif/ethernet.h"

//#include "lwip/etharp.h"
//#include "lwip/netif.h"
//#include "lwip/snmp.h"
//#include "lwip/opt.h"
//#include "def.h"
//#include "mem.h"
//#include "pbuf.h"
//#include <stats.h>
//#include <snmp.h>
//#include "etharp.h"
//#include "ppp_oe.h"

#include "MDR_ethernetif.h"

#include "MDR_Ethernet_Cfg1.h"
#include "MDR_Ethernet.h"

uint8_t         inpFrame[MDR_ETH_BUFF_LEN_TX] __attribute__((section("EXECUTABLE_MEMORY_SECTION"))) __attribute__ ((aligned (4)));
MDR_ETH_FrameTX outFrame                      __attribute__((section("EXECUTABLE_MEMORY_SECTION"))) __attribute__ ((aligned (4)));

const uint16_t mac_ethernet_address[] = { ETHCFG1_MAC_L, ETHCFG1_MAC_M, ETHCFG1_MAC_H};

/**
 * In this function, the hardware should be initialized.
 * Called from ethernetif_init().
 *
 * @param netif the already initialized lwip network interface structure
 *        for this ethernetif
 */
void low_level_init(struct netif *netif)
{
  MDR_ETH_LwIP_State *state = netif->state;
  MDR_ETH_Type       *MDR_Eth = state->mdrEth;
  
  //	Init
  MDR_ETH_MAC_CfgRegs cfgMAC = MDR_ETH_MAC_INIT_DEF(state->ethClock_MHz, state->clockDivToMDIO);
  MDR_ETH_InitCfg     initCfg = {.cfgRegsMAC = &cfgMAC, .phyCfgReg = MDR_REG_PHY_CTRL };
  
  MDR_Eth_SetClockHSE2();
  MDR_Eth_Init(MDR_Eth, &initCfg);  
  
  state->isLinkUp = false;
	
  /* set MAC hardware address */
  netif->hwaddr[0] =   cfgMAC.MAC_L & 0xFF;
  netif->hwaddr[1] =  (cfgMAC.MAC_L >> 8) & 0xFF;
  netif->hwaddr[2] =   cfgMAC.MAC_M & 0xFF;
  netif->hwaddr[3] =  (cfgMAC.MAC_M >> 8) & 0xFF;
  netif->hwaddr[4] =   cfgMAC.MAC_H & 0xFF;
  netif->hwaddr[5] =  (cfgMAC.MAC_H >> 8) & 0xFF;
	
  MDR_Eth_Start(MDR_Eth);  
}

/**
 * This function should do the actual transmission of the packet. The packet is
 * contained in the pbuf that is passed to the function. This pbuf
 * might be chained.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @param p the MAC packet to send (e.g. IP packet including MAC addresses and type)
 * @return ERR_OK if the packet could be sent
 *         an err_t value if the packet couldn't be sent
 *
 * @note Returning ERR_MEM here if a DMA queue of your MAC is full can lead to
 *       strange results. You might consider waiting for space in the DMA queue
 *       to become availale since the stack doesn't retry to send a packet
 *       dropped because of memory failure (except for the TCP timers).
 */

err_t low_level_output(struct netif *netif, struct pbuf *p)
{
  MDR_ETH_LwIP_State *state = netif->state;
  MDR_ETH_Type       *MDR_Eth = state->mdrEth;  
	err_t Err;
  
#if ETH_PAD_SIZE
  pbuf_header(p, -ETH_PAD_SIZE); /* drop the padding word */
#endif

  pbuf_copy_partial(p, outFrame.frame, p->tot_len, 0);
  
	/* The above memcpy() reduces the system performance, but 
     it has to be done, as the RTE ethernet driver expects only
     one and continuous packet data buffer. */
  if (MDR_ETH_GetBuffFreeSizeTX(MDR_Eth) < p->tot_len)
    Err = ERR_MEM;
  else
  {
    outFrame.frameLen = p->tot_len;
    MDR_ETH_SendFrame(MDR_Eth, &outFrame);
    Err = ERR_OK;    
  }

#if ETH_PAD_SIZE
  pbuf_header(p, ETH_PAD_SIZE); /* reclaim the padding word */
#endif
  
  LINK_STATS_INC(link.xmit);

  return Err;
}


/**
 * Should allocate a pbuf and transfer the bytes of the incoming
 * packet from the interface into the pbuf.
 *
 * @param netif the lwip network interface structure for this ethernetif
 * @return a pbuf filled with the received packet (including MAC header)
 *         NULL on memory error
 */
struct pbuf * low_level_input(struct netif *netif)
{
  MDR_ETH_LwIP_State *state = netif->state;
  MDR_ETH_Type       *MDR_Eth = state->mdrEth;  
  struct pbuf *p, *q;
  int len, framelen;
	
	/* Obtain the size of the packet and put it into the "len"
     variable. */
  MDR_ETH_FrameStatusRX statusRX = MDR_ETH_ReadFrame(MDR_Eth, inpFrame);
  len = statusRX.Fields.Length;
  
#if ETH_PAD_SIZE
  len += ETH_PAD_SIZE; /* allow room for Ethernet padding */
#endif

  /* We allocate a pbuf chain of pbufs from the pool. */
  p = pbuf_alloc(PBUF_RAW, len, PBUF_POOL);
  
  if (p != NULL)
	{

#if ETH_PAD_SIZE
    pbuf_header(p, -ETH_PAD_SIZE); /* drop the padding word */
#endif

		/* Copy the data to intermediate buffer. This is required because
       the RTE ethernet driver copies all the data to one
       continuous packet data buffer. */
    framelen = 0;
    /* We iterate over the pbuf chain until we have read the entire
     * packet into the pbuf. */
    for(q = p; q != NULL; q = q->next) {
      /* Read enough bytes to fill this pbuf in the chain. The
       * available data in the pbuf is given by the q->len
       * variable.
       * This does not necessarily have to be a memcpy, you can also preallocate
       * pbufs for a DMA-enabled MAC and after receiving truncate it to the
       * actually received size. In this case, ensure the tot_len member of the
       * pbuf is the sum of the chained pbuf len members.
       */
       memcpy (q->payload, &inpFrame[framelen], q->len);
       framelen += q->len;
    }

#if ETH_PAD_SIZE
    pbuf_header(p, ETH_PAD_SIZE); /* reclaim the padding word */
#endif

    LINK_STATS_INC(link.recv);
  } else {
    //drop packet();
    LINK_STATS_INC(link.memerr);
    LINK_STATS_INC(link.drop);
  }

  return p;  
}

/**
 * This function should be called when a packet is ready to be read
 * from the interface. It uses the function low_level_input() that
 * should handle the actual reception of bytes from the network
 * interface. Then the type of the received packet is determined and
 * the appropriate input function is called.
 *
 * @param netif the lwip network interface structure for this ethernetif
 */
void ethernetif_input(struct netif *netif)
{
  struct eth_hdr *ethhdr;
  struct pbuf *p;

  /* move received packet into a new pbuf */
  p = low_level_input(netif);
  /* no packet could be read, silently ignore this */
  if (p == NULL) return;
  /* points to packet payload, which starts with an Ethernet header */
  ethhdr = p->payload;

  switch (htons(ethhdr->type)) {
  /* IP or ARP packet? */
  case ETHTYPE_IP:
  case ETHTYPE_ARP:
#if PPPOE_SUPPORT
  /* PPPoE packet? */
  case ETHTYPE_PPPOEDISC:
  case ETHTYPE_PPPOE:
#endif /* PPPOE_SUPPORT */
    /* full packet send to tcpip_thread to process */
    if (netif->input(p, netif)!=ERR_OK)
     { LWIP_DEBUGF(NETIF_DEBUG, ("ethernetif_input: IP input error\n"));
       pbuf_free(p);
       p = NULL;
     }
    break;

  default:
    pbuf_free(p);
    p = NULL;
    break;
  }
}

bool link_state_changed(struct netif *netif, bool *isLinkUp)
{
  MDR_ETH_LwIP_State *state = netif->state;
  MDR_ETH_Type       *MDR_Eth = state->mdrEth;  
  
  *isLinkUp = MDR_ETH_GetLinkUp(MDR_Eth, ETHCFG1_PHY_ADDR);
  
  bool result = state->isLinkUp != *isLinkUp;
  state->isLinkUp = *isLinkUp;
  return result;
}

void ethernetif_poll(struct netif *netif)
{
  MDR_ETH_LwIP_State *state = netif->state;
  if (!state->isLinkUp)
    return;
  
  if (MDR_ETH_HasFrameToRead(state->mdrEth))
    ethernetif_input(netif);
}



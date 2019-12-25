#include "MDR_Config.h"
#include "MDR_LwIP.h"
#include "MDR_LwIP_Timer.h"

#include "lwip/pbuf.h"
#include "lwip/stats.h"
#include "lwip/netif.h"
#include "lwip/snmp.h"
#include "netif/ethernet.h"
#include "lwip/etharp.h"
#include "lwip/init.h"
#include "lwip/dhcp.h"
#include "lwip/priv/tcp_priv.h"
#include "lwip/ip4_addr.h"

#include "lwip/apps/snmp_opts.h"
#include "lwip/snmp.h"
#include "lwip/apps/snmp.h"
#include "lwip/apps/snmp_core.h"
#include "lwip/apps/snmp_mib2.h"
#include "lwip/apps/snmp_scalar.h"

#include "MDR_ethernetif.h"
#include "MDR_Ethernet.h"

//#include "lwip/apps/snmp_mib2.h"
//#include "lwip/apps/snmp_traps.h"
//#include "UserMIB.h"
//#include "UserMIB.h"

//  Define this function in main.c for example!
void netif_status_callback(struct netif *netif);
void netif_link_callback(struct netif *netif);

//  Global vars for Ethernet Interface
static struct netif        _netifEth1;
static MDR_ETH_LwIP_State  _stateEth1;

#ifdef MDR_ETH2
  static struct netif        _netifEth2; 
  static MDR_ETH_LwIP_State  _stateEth2;  
  
  static bool _assignedEth2 = false;
#endif

static err_t  netif_init_loc(struct netif *netif);
static err_t  netif_output  (struct netif *netif, struct pbuf *p);

static void MDR_LwIP_UpdateTime(uint32_t localtime);
static void MDR_LwIP_Check_Link(struct netif *netif);

uint32_t sys_now (void);
__STATIC_INLINE void  lock_interrupts(void)   { __disable_irq(); }  
__STATIC_INLINE void  unlock_interrupts(void) { __enable_irq(); }  

 
//  Initialization of LwIP stack
struct netif* MDR_LwIP_Init(uint32_t ethClock_MHz, uint32_t clockDivToMDIO, MDR_ETH_Type *mdrEth)
{
  ip4_addr_t ipaddr;
  ip4_addr_t netmask;
  ip4_addr_t gw;

  lwip_init ();

  #if LWIP_DHCP
    ipaddr.addr = 0;
    netmask.addr = 0;
    gw.addr = 0;
  #else
    IP4_ADDR(&ipaddr, IP_ADDR0, IP_ADDR1, IP_ADDR2, IP_ADDR3);
    IP4_ADDR(&netmask, NETMASK_ADDR0, NETMASK_ADDR1 , NETMASK_ADDR2, NETMASK_ADDR3);
    IP4_ADDR(&gw, GW_ADDR0, GW_ADDR1, GW_ADDR2, GW_ADDR3);
  #endif  

  _stateEth1.ethClock_MHz = ethClock_MHz;
  _stateEth1.clockDivToMDIO = clockDivToMDIO;
  _stateEth1.mdrEth = mdrEth;
  _stateEth1.isLinkUp = false;
  
  netif_add(&_netifEth1, &ipaddr, &netmask, &gw, (void *)&_stateEth1, netif_init_loc, netif_input);
  _netifEth1.name[0] = IFNAME0;
  _netifEth1.name[1] = IFNAME1;
   
  #if LWIP_NETIF_STATUS_CALLBACK
    netif_set_status_callback(&_netifEth1, netif_status_callback);
  #endif
  #if LWIP_NETIF_LINK_CALLBACK
    netif_set_link_callback(&_netifEth1, netif_link_callback);
  #endif
  
  netif_set_default(&_netifEth1);
  netif_set_up(&_netifEth1);

  #if LWIP_DHCP
    /* Start DHCP and HTTPD */
    dhcp_start(&_netifEth1 );
    //httpd_init(); //- HTTP Daemon
  #endif
  
  MDR_LwIP_TimerRun(ethClock_MHz * 10E+6);
  
  return &_netifEth1;
}

#ifdef MDR_ETH2
  void MDR_LwIP_InitSecondary(uint32_t ethClock_MHz, uint32_t clockDivToMDIO, MDR_ETH_Type *mdrEth)
  {
    ip4_addr_t ipaddr;
    ip4_addr_t netmask;
    ip4_addr_t gw;  
    
    #if LWIP_DHCP
      ipaddr.addr = 0;
      netmask.addr = 0;
      gw.addr = 0;
    #else
      IP4_ADDR(&ipaddr, IP_ADDR0_EX1, IP_ADDR1_EX1, IP_ADDR2_EX1, IP_ADDR3_EX1);
      IP4_ADDR(&netmask, NETMASK_ADDR0_EX1, NETMASK_ADDR1_EX1, NETMASK_ADDR2_EX1, NETMASK_ADDR3_EX1);
      IP4_ADDR(&gw, GW_ADDR0_EX1, GW_ADDR1_EX1, GW_ADDR2_EX1, GW_ADDR3_EX1);
    #endif  

      _stateEth2.ethClock_MHz = ethClock_MHz;
      _stateEth2.clockDivToMDIO = clockDivToMDIO;
      _stateEth2.mdrEth = mdrEth;
      _stateEth2.isLinkUp = false;
      
      netif_add(&_netifEth2, &ipaddr, &netmask, &gw, (void *)&_stateEth2, netif_init_loc, netif_input);
      _netifEth2.name[0] = IFNAME0_EX1;
      _netifEth2.name[1] = IFNAME1_EX1;

    #if LWIP_NETIF_STATUS_CALLBACK
      netif_set_status_callback(&_netifEth2, netif_status_callback);
    #endif
    #if LWIP_NETIF_LINK_CALLBACK
      netif_set_link_callback(&_netifEth2, netif_link_callback);
    #endif    
    
      netif_set_up(&_netifEth2);
      
    #if LWIP_DHCP
      /* Start DHCP and HTTPD */
      dhcp_start(&_netifEth2 );
      //httpd_init(); //- HTTP Daemon
    #endif
    
    _assignedEth2 = true;
  }
#endif

//  Callback function for MDR_ETHx block initialization
static err_t netif_init_loc(struct netif *netif)
{
  //  Init MDR Ethernet Init
  low_level_init(netif);
  
  //  LWIP Staff
  netif->linkoutput = netif_output;
  netif->output     = etharp_output;
#if LWIP_IPV6  
  netif->output_ip6 = ethip6_output;
#endif
  netif->mtu        = ETHERNET_MTU;
  netif->flags      = NETIF_FLAG_BROADCAST | NETIF_FLAG_ETHARP | NETIF_FLAG_ETHERNET | NETIF_FLAG_IGMP | NETIF_FLAG_MLD6;
  MIB2_INIT_NETIF(netif, snmp_ifType_ethernet_csmacd, 100000000);

  SMEMCPY(netif->hwaddr, mac_ethernet_address, ETH_HWADDR_LEN);
  netif->hwaddr_len = ETH_HWADDR_LEN;
  
  return ERR_OK;
}

//  Callback function to send frame
static err_t  netif_output(struct netif *netif, struct pbuf *p)
{
  LINK_STATS_INC(link.xmit);

  /* Update SNMP stats (only if you use SNMP) */
  MIB2_STATS_NETIF_ADD(netif, ifoutoctets, p->tot_len);
  int unicast = ((((uint8_t *)(p->payload))[0] & 0x01) == 0);      
  if (unicast) {
    MIB2_STATS_NETIF_INC(netif, ifoutucastpkts);
  } else {
    MIB2_STATS_NETIF_INC(netif, ifoutnucastpkts);
  }

  lock_interrupts();  
  err_t Err = low_level_output(netif, p);
  unlock_interrupts();

  return Err;
}


uint32_t sys_now (void)
{
  return MDR_LwIP_TimerGetTime_ms();
}



//void MDR_LwIP_HandlerIRQ(void)
//{
//  /* Service MAC IRQ here */

//  /* Allocate pbuf from pool (avoid using heap in interrupts) */
//  struct pbuf* p = pbuf_alloc(PBUF_RAW, eth_data_count, PBUF_POOL);

//  if(p != NULL) {
//    /* Copy ethernet frame into pbuf */
//    int32_t freeInd = EthFrames_CaptureNextIndWR();
//    if (freeInd >= 0)
//      pbuf_take(&frameBuffs[freeInd], eth_data, eth_data_count);
//    else {
//      // Frame loss
//      //    /* Put in a queue which is processed in main loop */
//      //    if(!queue_try_put(&queue, p)) {
//      //      /* queue is full -> packet loss */
//      //      pbuf_free(p);
//      //    }      
//    }
//  }
//}



void MDR_LwIP_LoopHook(void)
{
    MDR_LwIP_UpdateTime(MDR_LwIP_TimerGetTime_ms());

    ethernetif_poll(&_netifEth1);
    #ifdef MDR_ETH2
      if (_assignedEth2)
        ethernetif_poll(&_netifEth2);
    #endif  
    
//    /* Check for received frames, feed them to lwIP */
//    lock_interrupts();    
//    struct pbuf* p = EthFrames_GetActiveRD();          
//    unlock_interrupts();

//    if(p != NULL) {
//      LINK_STATS_INC(link.recv);
// 
//      /* Update SNMP stats (only if you use SNMP) */
//      MIB2_STATS_NETIF_ADD(&_netif, ifinoctets, p->tot_len);
////      int unicast = ((p->payload[0] & 0x01) == 0);
//      int unicast = ((((uint8_t *)(p->payload))[0] & 0x01) == 0);      
//      if (unicast) {
//        MIB2_STATS_NETIF_INC(&_netif, ifinucastpkts);
//      } else {
//        MIB2_STATS_NETIF_INC(&_netif, ifinnucastpkts);
//      }

//      if(_netif.input(p, &_netif) != ERR_OK) {
//        pbuf_free(p);
//      }
//      
//      EthFrames_FreeActiveRD();
//    }
//     
//    /* Cyclic lwIP timers check */
//    sys_check_timeouts();
//     
//    /* your application goes here */
}

static void MDR_LwIP_Check_Link(struct netif *netif)
{
  bool isLinkUp;
  if (link_state_changed(netif, &isLinkUp)) 
  {
    if(isLinkUp) {
      netif_set_link_up(netif);
    } else {
      netif_set_link_down(netif);
    }
  } 
}

static void MDR_LwIP_UpdateTime(uint32_t localtime)
{
  static uint32_t lastLocalTime = 0;
  static uint32_t TCPTimer = 0;
  static uint32_t ARPTimer = 0;
  static uint32_t LINK_Time = 0;
#if LWIP_DHCP
  static uint32_t DHCPfineTimer   = 0;
  static uint32_t DHCPcoarseTimer = 0;
#endif

  //  Check time changed
  if (lastLocalTime == localtime)
    return;
  lastLocalTime = localtime;  
  
#if LWIP_TCP
  /* TCP periodic process every 250 ms */
  if (localtime - TCPTimer >= TCP_TMR_INTERVAL)
	{
    TCPTimer = localtime;
    tcp_tmr();
  }
#endif
  
  /* ARP periodic process every 5s */
  if ((localtime - ARPTimer) >= ARP_TMR_INTERVAL)
	{
    ARPTimer = localtime;
    etharp_tmr();
  }

#if LWIP_DHCP
  /* Fine DHCP periodic process every 500ms */
  if (localtime - DHCPfineTimer >= DHCP_FINE_TIMER_MSECS)
	{
    DHCPfineTimer = localtime;
    dhcp_fine_tmr();
  }

  /* DHCP Coarse periodic process every 60s */
  if (localtime - DHCPcoarseTimer >= DHCP_COARSE_TIMER_MSECS)
	{
    DHCPcoarseTimer = localtime;
    dhcp_coarse_tmr();
  }
#endif

  /* Link check every 500ms */
  if ((localtime - LINK_Time) >= LINK_TMR_INTERVAL_MSEC)
  {
    LINK_Time = localtime;

    MDR_LwIP_Check_Link(&_netifEth1);
    
#ifdef MDR_ETH2
    if (_assignedEth2)
      MDR_LwIP_Check_Link(&_netifEth2);    
#endif
  } 
}


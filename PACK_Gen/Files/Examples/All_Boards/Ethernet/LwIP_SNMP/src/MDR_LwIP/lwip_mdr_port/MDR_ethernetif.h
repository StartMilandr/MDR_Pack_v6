#ifndef __MDR_ETHERNETIF_H__
#define __MDR_ETHERNETIF_H__

#include "lwip/err.h"
#include "lwip/netif.h"
#include <stdint.h>


#include "MDR_Config.h"
#include <stdbool.h>
#include <string.h>


extern const uint16_t mac_ethernet_address[];

typedef struct {
  MDR_ETH_Type     *mdrEth;
  uint32_t          ethClock_MHz;
  uint32_t          clockDivToMDIO;
  bool              isLinkUp;
} MDR_ETH_LwIP_State;


void          low_level_init  (struct netif *netif);
struct pbuf * low_level_input (struct netif *netif);
        err_t low_level_output(struct netif *netif, struct pbuf *p);

void ethernetif_poll   (struct netif *netif);
bool link_state_changed(struct netif *netif, bool *isLinkUp);

#endif // __MDR_ETHERNETIF_H__

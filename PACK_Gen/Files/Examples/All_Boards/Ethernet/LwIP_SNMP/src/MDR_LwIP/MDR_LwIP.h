#ifndef _MDR_LWIP_H
#define _MDR_LWIP_H

#include "MDR_Config.h"

#define LINK_TMR_INTERVAL_MSEC    500


struct netif* MDR_LwIP_Init(uint32_t ethClock_MHz, uint32_t clockDivToMDIO, MDR_ETH_Type *mdrEth);
void MDR_LwIP_LoopHook(void);
void MDR_LwIP_HandlerIRQ(void);

#ifdef MDR_ETH2
  void MDR_LwIP_InitSecondary(uint32_t ethClock_MHz, uint32_t clockDivToMDIO, MDR_ETH_Type *mdrEth);
#endif
//void MDR_LwIP_LoopHookSecondary(void);

#endif //_MDR_LWIP_H

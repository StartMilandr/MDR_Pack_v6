#include "MDR_Config.h"
#include <MDR_RST_Clock.h>
#include <MDRB_LEDs.h>
#include <MDRB_BoardSelect.h>
#include <string.h>

#include "MDR_LwIP.h"
#include "udp_echoserver.h"
#include "MDR_ethernetif.h"

#define LED_LINK_UP          MDRB_LED_ETH1_GREEN

int main(void)
{ 
  //  Максимальная скорость тактирования
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDRB_CLK_PLL_HSE_RES_MAX;
  MDR_CPU_SetClock_PLL_HSE(&cfgPLL_HSE, true);
  
  //  Инициализация кнопок
  MDRB_LED_ETH1_Init(LED_LINK_UP);
  
  //  LwIP with UDP EchoServer
  MDR_LwIP_Init(144, 1, MDR_ETH1);  
  udp_echoserver_init();
  
  while (1)
  {
    MDR_LwIP_LoopHook();
  }  
}


#if LWIP_NETIF_LINK_CALLBACK
void netif_link_callback(struct netif *netif)
{
  MDR_ETH_LwIP_State *state = netif->state;

  if (state->isLinkUp)
    MDRB_LED_ETH1_Set(LED_LINK_UP, 1);
  else
    MDRB_LED_ETH1_Set(LED_LINK_UP, 0);
}
#endif

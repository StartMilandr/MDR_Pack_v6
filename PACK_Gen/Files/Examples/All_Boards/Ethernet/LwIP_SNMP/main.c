#include "MDR_Config.h"
#include <MDR_RST_Clock.h>
#include <MDRB_LEDs.h>
#include <string.h>

#include "MDR_LwIP.h"
#include "MDR_ethernetif.h"
#include "UserMIB.h"

#define LED_LINK_UP          MDRB_LED_ETH1_GREEN

struct netif* p_netif;

void SNMP_Init(void);

int main(void)
{ 
  //  Максимальная скорость тактирования
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDRB_CLK_PLL_HSE_RES_MAX;
  MDR_CPU_SetClock_PLL_HSE(&cfgPLL_HSE, true);
  
  //  Инициализация светодиодов
  MDRB_LED_ETH1_Init(LED_LINK_UP);
  
  //  LwIP with SNMP
  p_netif = MDR_LwIP_Init(144, 1, MDR_ETH1);  
  MIB_HandlersInit();
  SNMP_Init();
  
  while (1)
  {
    MDR_LwIP_LoopHook();
  }  
}

static const struct snmp_mib *my_snmp_mibs[] = { &mib2, &user_MIB };
u8_t * syscontact_str = (u8_t*) "root";
u16_t  syscontact_len = sizeof("root");
u8_t * syslocation_str = (u8_t*) "Milandr LWIP SNMP";
u16_t  syslocation_len = sizeof("Milandr LWIP SNMP");
u8_t * sysname_str = (u8_t*) "Milandr";
u16_t  sysname_len = sizeof("Milandr");
u16_t  bufsize = 64;
const u8_t * sysdescr = (u8_t*) "minimal_example";
const u16_t  sysdescr_len = sizeof("minimal_example");
#define TRAP_DESTINATION_0_INDEX    0

void SNMP_Init(void)
{
  snmp_mib2_set_syscontact(syscontact_str, &syscontact_len, bufsize);
  snmp_mib2_set_syslocation(syslocation_str, &syslocation_len, bufsize);
  snmp_set_auth_traps_enabled(true);
  snmp_mib2_set_sysdescr(sysdescr, &sysdescr_len);
  snmp_mib2_set_sysname(sysname_str, &sysname_len, bufsize);
  snmp_trap_dst_ip_set(TRAP_DESTINATION_0_INDEX, &(p_netif->gw));
  snmp_trap_dst_enable(TRAP_DESTINATION_0_INDEX, true);
  snmp_set_mibs(my_snmp_mibs, LWIP_ARRAYSIZE(my_snmp_mibs));
  snmp_init(); //Just after udp_init
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

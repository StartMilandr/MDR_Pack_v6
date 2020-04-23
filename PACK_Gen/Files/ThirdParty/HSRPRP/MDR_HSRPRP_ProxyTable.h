#ifndef _MDR_HSRPRP_PROXY_TABLE_H
#define _MDR_HSRPRP_PROXY_TABLE_H

#include "stdint.h"
#include "stdbool.h"

bool MDR_ProxyTable_HasMAC(uint8_t *MAC, uint32_t timeRX);
bool MDR_ProxyTable_AddMac(uint8_t *MAC, uint32_t timeRX);
void MDR_ProxyTable_ProcessForget(uint32_t timeNow, uint32_t forgetTime);

#endif  //  _MDR_HSRPRP_PROXY_TABLE_H

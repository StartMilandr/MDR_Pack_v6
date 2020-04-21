#ifndef _MDR_HSRPRP_PROXY_TABLE_H
#define _MDR_HSRPRP_PROXY_TABLE_H

#include "stdint.h"
#include "stdbool.h"

bool MDR_ProxyTable_HasMAC(uint8_t *MAC);
void MDR_ProxyTable_AddMac(uint8_t *MAC);

#endif  //  _MDR_HSRPRP_PROXY_TABLE_H

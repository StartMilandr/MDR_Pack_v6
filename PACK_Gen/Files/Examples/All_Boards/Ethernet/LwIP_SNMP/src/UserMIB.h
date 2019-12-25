#ifndef _USER_MIB_H
#define _USER_MIB_H

#include "lwip/apps/snmp_opts.h"
#include "lwip/snmp.h"
#include "lwip/apps/snmp.h"
#include "lwip/apps/snmp_core.h"
#include "lwip/apps/snmp_mib2.h"
#include "lwip/apps/snmp_scalar.h"

extern const struct snmp_mib user_MIB;

void MIB_HandlersInit(void);

#endif //_USER_MIB_H

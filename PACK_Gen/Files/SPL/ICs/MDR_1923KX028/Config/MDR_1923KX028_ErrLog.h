#ifndef MDR_1923KX029_ERRLOGH_H
#define MDR_1923KX029_ERRLOGH_H

#include <stdint.h>

typedef enum {
  MDR_KX028_Log_MAC_Table_InitFault,
  MDR_KX028_Log_MAC_Table_SpaceFault,
  MDR_KX028_Log_VLAN_Table_AddFault,
  MDR_KX028_Log_VLAN_Table_DelFault,
  MDR_KX028_Log_VLAN_Table_InitFault,
  MDR_KX028_Log_VLAN_Table_SpaceFault,
  MDR_KX028_Log_Learn_WrongStructInd,
  MDR_KX028_Log_Learn_UnusedPort,
} MDR_KX028_LogID;


void MDR_KX028_Log(MDR_KX028_LogID logID, uint32_t value);

#endif  //MDR_1923KX029_ERRLOGH_H

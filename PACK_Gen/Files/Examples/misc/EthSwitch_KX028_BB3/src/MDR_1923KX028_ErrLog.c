#include <MDR_1923KX028_ErrLog.h>

void MDR_KX028_Log(MDR_KX028_LogID logID, uint32_t value)
{
  switch (logID) {  
    case MDR_KX028_Log_MAC_Table_InitFault:
      //printf( "MAC HASH TABLE INIT FAILED! HW CLASS%d\n", value );  // "value" is classNum
      break;
    case MDR_KX028_Log_MAC_Table_SpaceFault:
      //printf( "MAC HASH TABLE INIT COLLISION SPACE FAILED!! HW CLASS%d\n", value ); // "value" is classNum
      break;
    case MDR_KX028_Log_VLAN_Table_AddFault:
      //printf("VLAN ADD CMD TO TABLE FAILED. HW CLASS%d\n", classNum);
      break;
    case MDR_KX028_Log_VLAN_Table_DelFault:
      //printf("VLAN DEL CMD FROM TABLE FAILED. HW CLASS%d\n", classNum);
      break;
    case MDR_KX028_Log_VLAN_Table_InitFault:  
      //printf("VLAN HASH TABLE INIT FAILED! HW CLASS%d\n", classNum);
      break;
    case MDR_KX028_Log_VLAN_Table_SpaceFault:
      //printf( "VLAN HASH TABLE COLLISION SPACE INIT FAILED! HW CLASS%d\n", classNum);
      break;
    case MDR_KX028_Log_Learn_WrongStructInd:
      //
      break;
      
  }
}


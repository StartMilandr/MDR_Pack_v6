#include "MDR_HSRPRP_ProxyTable.h"
#include <MDR_Ethernet_FrameDefs.h>
#include "MDR_HSRPRP_Config.h"

typedef union {
  uint32_t  loMAC32;
  uint16_t  hiMAC16;
  uint16_t  busy;
  uint32_t  timeRX;
} MDR_ProxyItemMAC;

MDR_ProxyItemMAC  _TableMAC[HSR_ProxyNodeTableMaxEntries];


bool MDR_ProxyTable_HasMAC(uint8_t *MAC, uint32_t timeRX)
{
  uint32_t i;
  uint32_t loMAC32 = *(uint32_t *)MAC;
  uint16_t hiMAC16 = *(uint16_t *)&MAC[4];
  
  for (i = 0; i < HSR_ProxyNodeTableMaxEntries; ++i)
    if (_TableMAC[i].busy)
      if ((loMAC32 == _TableMAC[i].loMAC32) && (hiMAC16 == _TableMAC[i].hiMAC16))
      {
        _TableMAC[i].timeRX = timeRX;
        return true;
      }
      
  return false;    
}

bool MDR_ProxyTable_AddMac(uint8_t *MAC, uint32_t timeRX)
{
  uint32_t i;
  for (i = 0; i < HSR_ProxyNodeTableMaxEntries; ++i)
    if (!_TableMAC[i].busy)
    {
      _TableMAC[i].loMAC32 = *(uint32_t *)MAC;
      _TableMAC[i].hiMAC16 = *(uint16_t *)&MAC[4];
      _TableMAC[i].timeRX = timeRX;
      _TableMAC[i].busy = true;
      return true;
    }
  
  return false;
}

void MDR_ProxyTable_ProcessForget(uint32_t timeNow, uint32_t forgetTime)
{
  uint32_t i;
  for (i = 0; i < HSR_ProxyNodeTableMaxEntries; ++i)
    if (_TableMAC[i].busy && (timeNow - _TableMAC[i].timeRX) > forgetTime)
      _TableMAC[i].busy = false;
}


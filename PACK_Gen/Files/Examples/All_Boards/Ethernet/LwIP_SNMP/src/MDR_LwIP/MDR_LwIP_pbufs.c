#include "MDR_LwIP_pbufs.h"
#include "lwip/pbuf.h"

static struct pbuf frameBuffs[LWIP_PBUFS_COUNT];
static uint32_t    frameBuffIndWR;
static uint32_t    frameBuffIndRD;

struct pbuf*    LwIP_pbuf_CaptureNextForWrite(void)
{   
  uint32_t nextIndWr = frameBuffIndWR + 1;
  if (nextIndWr == LWIP_PBUFS_COUNT)
    nextIndWr = 0;
  
  if (nextIndWr != frameBuffIndRD)
  {
    struct pbuf* result = &(frameBuffs[frameBuffIndWR]);
    
    frameBuffIndWR = nextIndWr;
    return result;
  }
  else
    return NULL;
}

struct pbuf* LwIP_pbuf_GetNextForRead(void)
{
  if (frameBuffIndRD == frameBuffIndWR)
    return NULL;
  else
  {
    struct pbuf* result = &(frameBuffs[frameBuffIndRD]);
    
    ++frameBuffIndRD;  
    if (frameBuffIndRD == LWIP_PBUFS_COUNT)
      frameBuffIndRD = 0;
    return result;
  }    
}

void LwIP_pbuf_Clear(void)
{
  frameBuffIndWR = frameBuffIndRD;
}

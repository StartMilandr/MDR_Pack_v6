#ifndef _MDR_LWIP_PBUFS_H
#define _MDR_LWIP_PBUFS_H

#define       LWIP_PBUFS_COUNT      5

struct pbuf*  LwIP_pbuf_CaptureNextForWrite(void);
struct pbuf*  LwIP_pbuf_GetNextForRead(void);
void          LwIP_pbuf_Clear(void);

#endif //_MDR_LWIP_PBUFS_H

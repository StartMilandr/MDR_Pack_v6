#ifndef _MDR_DMA_VEX_DEFS_H
#define _MDR_DMA_VEX_DEFS_H

// Определения блока BKP, общие для всех МК

#ifdef __cplusplus
extern "C" {
#endif

#include <MDR_Types.h>
#include <MDR_DMA_defs.h>

/* ========================================  Start of section using anonymous unions  ======================================== */
#if defined (__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined (__ICCARM__)
  #pragma language=extended
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wc11-extensions"
  #pragma clang diagnostic ignored "-Wreserved-id-macro"
  #pragma clang diagnostic ignored "-Wgnu-anonymous-struct"
  #pragma clang diagnostic ignored "-Wnested-anon-types"
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning 586
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif
/* ========================================  Start of section using anonymous unions  ======================================== */


typedef struct {                                      /*!< (@ 0x40028000) MDR_DMA Structure                                          */  
  union {
    __IM  uint32_t              STATUS;               /*!< (@ 0x00000000) Status register                                            */
    MDR_DMA_STATUS_Bits         STATUS_b; 
  } ;  
  union {
    __OM  uint32_t              CFG;                  /*!< (@ 0x00000004) Config register                                            */
    MDR_DMA_CFG_Bits            CFG_b;
  } ;  
  union {
    __IOM uint32_t              CTRL_BASE_PTR;        /*!< (@ 0x00000008) Channel control data base pointer                          */
    MDR_DMA_CTRL_BASE_PTR_Bits  CTRL_BASE_PTR_b;
  } ; 
  
  __IM  uint32_t ALT_CTRL_BASE_PTR;                   /*!< (@ 0x0000000C) Channel alternate control data base pointer                */  
  
  union {
    __IM  uint32_t              WAITONREQ_STATUS;     /*!< (@ 0x00000010) Channel wait on request status                             */
    MDR_DMA_CHNL_RO_Bits        WAITONREQ_STATUS_b;
  } ;  
  union {
    __OM  uint32_t              CHNL_SW_REQUEST;      /*!< (@ 0x00000014) Channel Software Request                                   */
    MDR_DMA_CHNL_WO_Bits        CHNL_SW_REQUEST_b;
  } ;  
  union {
    __IOM uint32_t              CHNL_USEBURST_SET;    /*!< (@ 0x00000018) Disable SREQ requests                                      */
    MDR_DMA_CHNL_RW_Bits        CHNL_USEBURST_SET_b;
  } ;
  union {
    __OM  uint32_t              CHNL_USEBURST_CLR;           /*!< (@ 0x0000001C) Enable SREQ requests                                       */
    MDR_DMA_CHNL_WO_Bits        CHNL_USEBURST_CLR_b;
  } ; 
  union {
    __IOM uint32_t              CHNL_REQ_MASK_SET;           /*!< (@ 0x00000020) Disable channel processing                                 */
    MDR_DMA_CHNL_RW_Bits        CHNL_REQ_MASK_SET_b;
  } ;
  union {
    __OM  uint32_t              CHNL_REQ_MASK_CLR;           /*!< (@ 0x00000024) Enable channel processing                                  */
    MDR_DMA_CHNL_WO_Bits        CHNL_REQ_MASK_CLR_b;
  } ;  
  union {
    __IOM uint32_t              CHNL_ENABLE_SET;             /*!< (@ 0x00000028) Start Channel                                              */
    MDR_DMA_CHNL_RW_Bits        CHNL_ENABLE_SET_b;
  } ;  
  union {
    __OM  uint32_t              CHNL_ENABLE_CLR;             /*!< (@ 0x0000002C) Stop Channel                                               */
    MDR_DMA_CHNL_WO_Bits        CHNL_ENABLE_CLR_b;
  } ;
  union {
    __IOM uint32_t              CHNL_PRI_ALT_SET;            /*!< (@ 0x00000030) Select Alter Structure                                     */
    MDR_DMA_CHNL_RW_Bits        CHNL_PRI_ALT_SET_b;
  } ;
  union {
    __OM  uint32_t              CHNL_PRI_ALT_CLR;            /*!< (@ 0x00000034) Select Primary Structure                                   */
    MDR_DMA_CHNL_WO_Bits        CHNL_PRI_ALT_CLR_b;
  } ;
  union {
    __IOM uint32_t              CHNL_PRIORITY_SET;            /*!< (@ 0x00000030) Select Alter Structure                                     */
    MDR_DMA_CHNL_RW_Bits        CHNL_PRIORITY_SET_b;
  } ;
  union {
    __OM  uint32_t              CHNL_PRIORITY_CLR;            /*!< (@ 0x00000034) Select Primary Structure                                   */
    MDR_DMA_CHNL_WO_Bits        CHNL_PRIORITY_CLR_b;
  } ;    
  __IM  uint32_t  RESERVED[3];  
  union {
    __IOM uint32_t              ERR_CLR;                     /*!< (@ 0x0000004C) AHB-Lite bus error clear                                   */
    MDR_DMA_CHNL_RW_Bits        ERR_CLR_b;
  } ;
} MDR_DMA_Type;                                 /*!< Size = 120 (0x70)                                                          */




/* =========================================  End of section using anonymous unions  ========================================= */
#if defined (__CC_ARM)
  #pragma pop
#elif defined (__ICCARM__)
  /* leave anonymous unions enabled */
#elif (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic pop
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning restore
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#endif
/* =========================================  End of section using anonymous unions  ========================================= */

#ifdef __cplusplus
}
#endif

#endif  //_MDR_DMA_VEX_DEFS_H

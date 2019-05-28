#ifndef _MDR_DMA_DEFS_H
#define _MDR_DMA_DEFS_H

// Определения блока BKP, общие для всех МК

#ifdef __cplusplus
extern "C" {
#endif

#include "MDR_Types.h"

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

typedef struct {
  __IM  uint32_t Enable     : 1;            /*!< [0..0] Enable block                                                       */
  __IM  uint32_t            : 3;
  __IM  uint32_t State      : 4;            /*!< [7..4] Active Operation                                                   */
  __IM  uint32_t            : 8;
  __IM  uint32_t Chnls_minus1 : 5;          /*!< [20..16] Channels count                                                   */
  __IM  uint32_t            : 7;
  __IM  uint32_t test_status : 1;           /*!< [28..28] Test logic availability                                          */
  __IM  uint32_t            : 3;
} MDR_DMA_STATUS_Bits;

#define MDR_DMA_STATUS_Enable_Pos         (0UL)                     /*!< MDR_DMA STATUS: Enable (Bit 0)                        */
#define MDR_DMA_STATUS_Enable_Msk         (0x1UL)                   /*!< MDR_DMA STATUS: Enable (Bitfield-Mask: 0x01)          */
#define MDR_DMA_STATUS_State_Pos          (4UL)                     /*!< MDR_DMA STATUS: State (Bit 4)                         */
#define MDR_DMA_STATUS_State_Msk          (0xf0UL)                  /*!< MDR_DMA STATUS: State (Bitfield-Mask: 0x0f)           */
#define MDR_DMA_STATUS_Chnls_minus1_Pos   (16UL)                    /*!< MDR_DMA STATUS: Chnls_minus1 (Bit 16)                 */
#define MDR_DMA_STATUS_Chnls_minus1_Msk   (0x1f0000UL)              /*!< MDR_DMA STATUS: Chnls_minus1 (Bitfield-Mask: 0x1f)    */
#define MDR_DMA_STATUS_test_status_Pos    (28UL)                    /*!< MDR_DMA STATUS: test_status (Bit 28)                  */
#define MDR_DMA_STATUS_test_status_Msk    (0x10000000UL)            /*!< MDR_DMA STATUS: test_status (Bitfield-Mask: 0x01)     */


typedef struct {
  __OM  uint32_t Enable     : 1;            /*!< [0..0] Enable block                                                       */
  __IM  uint32_t            : 4;
  __OM  uint32_t Privileged : 1;            /*!< [5..5] Privileged AHB bus priority                                        */
  __OM  uint32_t Bufferable : 1;            /*!< [6..6] Bufferable AHB bus priority                                        */
  __OM  uint32_t Cachable   : 1;            /*!< [7..7] Cachable AHB bus priority                                          */
  __IM  uint32_t            : 24;
} MDR_DMA_CFG_Bits;

#define MDR_DMA_CFG_Enable_Pos            (0UL)                     /*!< MDR_DMA CFG: Enable (Bit 0)                           */
#define MDR_DMA_CFG_Enable_Msk            (0x1UL)                   /*!< MDR_DMA CFG: Enable (Bitfield-Mask: 0x01)             */
#define MDR_DMA_CFG_Privileged_Pos        (5UL)                     /*!< MDR_DMA CFG: Privileged (Bit 5)                       */
#define MDR_DMA_CFG_Privileged_Msk        (0x20UL)                  /*!< MDR_DMA CFG: Privileged (Bitfield-Mask: 0x01)         */
#define MDR_DMA_CFG_Bufferable_Pos        (6UL)                     /*!< MDR_DMA CFG: Bufferable (Bit 6)                       */
#define MDR_DMA_CFG_Bufferable_Msk        (0x40UL)                  /*!< MDR_DMA CFG: Bufferable (Bitfield-Mask: 0x01)         */
#define MDR_DMA_CFG_Cachable_Pos          (7UL)                     /*!< MDR_DMA CFG: Cachable (Bit 7)                         */
#define MDR_DMA_CFG_Cachable_Msk          (0x80UL)                  /*!< MDR_DMA CFG: Cachable (Bitfield-Mask: 0x01)           */


typedef struct {
  __IM  uint32_t            : 10;
  __IOM uint32_t Addr_Hi    : 22;           /*!< [31..10] Pointer                                                          */
} MDR_DMA_CTRL_BASE_PTR_Bits;

#define MDR_DMA_CTRL_BASE_PTR_Addr_Hi_Pos (10UL)                    /*!< MDR_DMA CTRL_BASE_PTR: Addr_Hi (Bit 10)               */
#define MDR_DMA_CTRL_BASE_PTR_Addr_Hi_Msk (0xfffffc00UL)            /*!< MDR_DMA CTRL_BASE_PTR: Addr_Hi (Bitfield-Mask: 0x3fffff) */

#define MDR_DMA_ALT_CTRL_BASE_PTR_Addr_Pos (0UL)                    /*!< MDR_DMA ALT_CTRL_BASE_PTR: Addr (Bit 0)               */
#define MDR_DMA_ALT_CTRL_BASE_PTR_Addr_Msk (0xffffffffUL)           /*!< MDR_DMA ALT_CTRL_BASE_PTR: Addr (Bitfield-Mask: 0xffffffff) */


typedef struct {
  __IM  uint32_t Ch_0       : 1;            /*!< [0..0] Channel Select                                                     */
  __IM  uint32_t Ch_1       : 1;            /*!< [1..1] Channel Select                                                     */
  __IM  uint32_t Ch_2       : 1;            /*!< [2..2] Channel Select                                                     */
  __IM  uint32_t Ch_3       : 1;            /*!< [3..3] Channel Select                                                     */
  __IM  uint32_t Ch_4       : 1;            /*!< [4..4] Channel Select                                                     */
  __IM  uint32_t Ch_5       : 1;            /*!< [5..5] Channel Select                                                     */
  __IM  uint32_t Ch_6       : 1;            /*!< [6..6] Channel Select                                                     */
  __IM  uint32_t Ch_7       : 1;            /*!< [7..7] Channel Select                                                     */
  __IM  uint32_t Ch_8       : 1;            /*!< [8..8] Channel Select                                                     */
  __IM  uint32_t Ch_9       : 1;            /*!< [9..9] Channel Select                                                     */
  __IM  uint32_t Ch_10      : 1;            /*!< [10..10] Channel Select                                                   */
  __IM  uint32_t Ch_11      : 1;            /*!< [11..11] Channel Select                                                   */
  __IM  uint32_t Ch_12      : 1;            /*!< [12..12] Channel Select                                                   */
  __IM  uint32_t Ch_13      : 1;            /*!< [13..13] Channel Select                                                   */
  __IM  uint32_t Ch_14      : 1;            /*!< [14..14] Channel Select                                                   */
  __IM  uint32_t Ch_15      : 1;            /*!< [15..15] Channel Select                                                   */
  __IM  uint32_t Ch_16      : 1;            /*!< [16..16] Channel Select                                                   */
  __IM  uint32_t Ch_17      : 1;            /*!< [17..17] Channel Select                                                   */
  __IM  uint32_t Ch_18      : 1;            /*!< [18..18] Channel Select                                                   */
  __IM  uint32_t Ch_19      : 1;            /*!< [19..19] Channel Select                                                   */
  __IM  uint32_t Ch_20      : 1;            /*!< [20..20] Channel Select                                                   */
  __IM  uint32_t Ch_21      : 1;            /*!< [21..21] Channel Select                                                   */
  __IM  uint32_t Ch_22      : 1;            /*!< [22..22] Channel Select                                                   */
  __IM  uint32_t Ch_23      : 1;            /*!< [23..23] Channel Select                                                   */
  __IM  uint32_t Ch_24      : 1;            /*!< [24..24] Channel Select                                                   */
  __IM  uint32_t Ch_25      : 1;            /*!< [25..25] Channel Select                                                   */
  __IM  uint32_t Ch_26      : 1;            /*!< [26..26] Channel Select                                                   */
  __IM  uint32_t Ch_27      : 1;            /*!< [27..27] Channel Select                                                   */
  __IM  uint32_t Ch_28      : 1;            /*!< [28..28] Channel Select                                                   */
  __IM  uint32_t Ch_29      : 1;            /*!< [29..29] Channel Select                                                   */
  __IM  uint32_t Ch_30      : 1;            /*!< [30..30] Channel Select                                                   */
  __IM  uint32_t Ch_31      : 1;            /*!< [31..31] Channel Select                                                   */
} MDR_DMA_CHNL_RO_Bits;

typedef struct {
  __OM  uint32_t Ch_0       : 1;            /*!< [0..0] Channel Select                                                     */
  __OM  uint32_t Ch_1       : 1;            /*!< [1..1] Channel Select                                                     */
  __OM  uint32_t Ch_2       : 1;            /*!< [2..2] Channel Select                                                     */
  __OM  uint32_t Ch_3       : 1;            /*!< [3..3] Channel Select                                                     */
  __OM  uint32_t Ch_4       : 1;            /*!< [4..4] Channel Select                                                     */
  __OM  uint32_t Ch_5       : 1;            /*!< [5..5] Channel Select                                                     */
  __OM  uint32_t Ch_6       : 1;            /*!< [6..6] Channel Select                                                     */
  __OM  uint32_t Ch_7       : 1;            /*!< [7..7] Channel Select                                                     */
  __OM  uint32_t Ch_8       : 1;            /*!< [8..8] Channel Select                                                     */
  __OM  uint32_t Ch_9       : 1;            /*!< [9..9] Channel Select                                                     */
  __OM  uint32_t Ch_10      : 1;            /*!< [10..10] Channel Select                                                   */
  __OM  uint32_t Ch_11      : 1;            /*!< [11..11] Channel Select                                                   */
  __OM  uint32_t Ch_12      : 1;            /*!< [12..12] Channel Select                                                   */
  __OM  uint32_t Ch_13      : 1;            /*!< [13..13] Channel Select                                                   */
  __OM  uint32_t Ch_14      : 1;            /*!< [14..14] Channel Select                                                   */
  __OM  uint32_t Ch_15      : 1;            /*!< [15..15] Channel Select                                                   */
  __OM  uint32_t Ch_16      : 1;            /*!< [16..16] Channel Select                                                   */
  __OM  uint32_t Ch_17      : 1;            /*!< [17..17] Channel Select                                                   */
  __OM  uint32_t Ch_18      : 1;            /*!< [18..18] Channel Select                                                   */
  __OM  uint32_t Ch_19      : 1;            /*!< [19..19] Channel Select                                                   */
  __OM  uint32_t Ch_20      : 1;            /*!< [20..20] Channel Select                                                   */
  __OM  uint32_t Ch_21      : 1;            /*!< [21..21] Channel Select                                                   */
  __OM  uint32_t Ch_22      : 1;            /*!< [22..22] Channel Select                                                   */
  __OM  uint32_t Ch_23      : 1;            /*!< [23..23] Channel Select                                                   */
  __OM  uint32_t Ch_24      : 1;            /*!< [24..24] Channel Select                                                   */
  __OM  uint32_t Ch_25      : 1;            /*!< [25..25] Channel Select                                                   */
  __OM  uint32_t Ch_26      : 1;            /*!< [26..26] Channel Select                                                   */
  __OM  uint32_t Ch_27      : 1;            /*!< [27..27] Channel Select                                                   */
  __OM  uint32_t Ch_28      : 1;            /*!< [28..28] Channel Select                                                   */
  __OM  uint32_t Ch_29      : 1;            /*!< [29..29] Channel Select                                                   */
  __OM  uint32_t Ch_30      : 1;            /*!< [30..30] Channel Select                                                   */
  __OM  uint32_t Ch_31      : 1;            /*!< [31..31] Channel Select                                                   */
} MDR_DMA_CHNL_WO_Bits;

typedef struct {
  __IOM uint32_t Ch_0       : 1;            /*!< [0..0] Channel Select                                                     */
  __IOM uint32_t Ch_1       : 1;            /*!< [1..1] Channel Select                                                     */
  __IOM uint32_t Ch_2       : 1;            /*!< [2..2] Channel Select                                                     */
  __IOM uint32_t Ch_3       : 1;            /*!< [3..3] Channel Select                                                     */
  __IOM uint32_t Ch_4       : 1;            /*!< [4..4] Channel Select                                                     */
  __IOM uint32_t Ch_5       : 1;            /*!< [5..5] Channel Select                                                     */
  __IOM uint32_t Ch_6       : 1;            /*!< [6..6] Channel Select                                                     */
  __IOM uint32_t Ch_7       : 1;            /*!< [7..7] Channel Select                                                     */
  __IOM uint32_t Ch_8       : 1;            /*!< [8..8] Channel Select                                                     */
  __IOM uint32_t Ch_9       : 1;            /*!< [9..9] Channel Select                                                     */
  __IOM uint32_t Ch_10      : 1;            /*!< [10..10] Channel Select                                                   */
  __IOM uint32_t Ch_11      : 1;            /*!< [11..11] Channel Select                                                   */
  __IOM uint32_t Ch_12      : 1;            /*!< [12..12] Channel Select                                                   */
  __IOM uint32_t Ch_13      : 1;            /*!< [13..13] Channel Select                                                   */
  __IOM uint32_t Ch_14      : 1;            /*!< [14..14] Channel Select                                                   */
  __IOM uint32_t Ch_15      : 1;            /*!< [15..15] Channel Select                                                   */
  __IOM uint32_t Ch_16      : 1;            /*!< [16..16] Channel Select                                                   */
  __IOM uint32_t Ch_17      : 1;            /*!< [17..17] Channel Select                                                   */
  __IOM uint32_t Ch_18      : 1;            /*!< [18..18] Channel Select                                                   */
  __IOM uint32_t Ch_19      : 1;            /*!< [19..19] Channel Select                                                   */
  __IOM uint32_t Ch_20      : 1;            /*!< [20..20] Channel Select                                                   */
  __IOM uint32_t Ch_21      : 1;            /*!< [21..21] Channel Select                                                   */
  __IOM uint32_t Ch_22      : 1;            /*!< [22..22] Channel Select                                                   */
  __IOM uint32_t Ch_23      : 1;            /*!< [23..23] Channel Select                                                   */
  __IOM uint32_t Ch_24      : 1;            /*!< [24..24] Channel Select                                                   */
  __IOM uint32_t Ch_25      : 1;            /*!< [25..25] Channel Select                                                   */
  __IOM uint32_t Ch_26      : 1;            /*!< [26..26] Channel Select                                                   */
  __IOM uint32_t Ch_27      : 1;            /*!< [27..27] Channel Select                                                   */
  __IOM uint32_t Ch_28      : 1;            /*!< [28..28] Channel Select                                                   */
  __IOM uint32_t Ch_29      : 1;            /*!< [29..29] Channel Select                                                   */
  __IOM uint32_t Ch_30      : 1;            /*!< [30..30] Channel Select                                                   */
  __IOM uint32_t Ch_31      : 1;            /*!< [31..31] Channel Select                                                   */
} MDR_DMA_CHNL_RW_Bits;


#define MDR_DMA_MSK_CH_0    (0x1UL)
#define MDR_DMA_MSK_CH_1    (0x2UL)
#define MDR_DMA_MSK_CH_2    (0x4UL)
#define MDR_DMA_MSK_CH_3    (0x8UL)
#define MDR_DMA_MSK_CH_4    (0x10UL)
#define MDR_DMA_MSK_CH_5    (0x20UL)
#define MDR_DMA_MSK_CH_6    (0x40UL)
#define MDR_DMA_MSK_CH_7    (0x80UL)
#define MDR_DMA_MSK_CH_8    (0x100UL)
#define MDR_DMA_MSK_CH_9    (0x200UL)
#define MDR_DMA_MSK_CH_10   (0x400UL)
#define MDR_DMA_MSK_CH_11   (0x800UL)
#define MDR_DMA_MSK_CH_12   (0x1000UL)
#define MDR_DMA_MSK_CH_13   (0x2000UL)
#define MDR_DMA_MSK_CH_14   (0x4000UL)
#define MDR_DMA_MSK_CH_15   (0x8000UL)
#define MDR_DMA_MSK_CH_16   (0x10000UL)
#define MDR_DMA_MSK_CH_17   (0x20000UL)
#define MDR_DMA_MSK_CH_18   (0x40000UL)
#define MDR_DMA_MSK_CH_19   (0x80000UL)
#define MDR_DMA_MSK_CH_20   (0x100000UL)
#define MDR_DMA_MSK_CH_21   (0x200000UL)
#define MDR_DMA_MSK_CH_22   (0x400000UL)
#define MDR_DMA_MSK_CH_23   (0x800000UL)
#define MDR_DMA_MSK_CH_24   (0x1000000UL)
#define MDR_DMA_MSK_CH_25   (0x2000000UL)
#define MDR_DMA_MSK_CH_26   (0x4000000UL)
#define MDR_DMA_MSK_CH_27   (0x8000000UL)
#define MDR_DMA_MSK_CH_28   (0x10000000UL)
#define MDR_DMA_MSK_CH_29   (0x20000000UL)
#define MDR_DMA_MSK_CH_30   (0x40000000UL)
#define MDR_DMA_MSK_CH_31   (0x80000000UL)

#define MDR_DMA_CHANNELS_COUNT  32

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
} MDR_DMA_Type;                                 /*!< Size = 80 (0x50)                                                          */


// ==========  Управляющая структура канала DMA ==========
typedef enum {
  DMA_MODE_Stop           = 0,
  DMA_MODE_Base           = 1,
  DMA_MODE_AutoRequest    = 2,
  DMA_MODE_PingPong       = 3,
  DMA_MODE_MemScatterPri  = 4,
  DMA_MODE_MemScatterAlt  = 5,
  DMA_MODE_PerScatterPri  = 6,
  DMA_MODE_PerScatterAlt  = 7,
} MDR_DMA_Mode;

typedef enum {
  DMA_Arbitr_1    = 0,
  DMA_Arbitr_2    = 1,
  DMA_Arbitr_4    = 2,
  DMA_Arbitr_8    = 3,
  DMA_Arbitr_16   = 4,
  DMA_Arbitr_32   = 5,
  DMA_Arbitr_64   = 6,
  DMA_Arbitr_128  = 7,
  DMA_Arbitr_256  = 8,
  DMA_Arbitr_512  = 9,
  DMA_Arbitr_1024 = 10,
} MDR_DMA_Arbitr;

typedef enum {
  MDR_DMA_Data8  = 0,
  MDR_DMA_Data16 = 1,
  MDR_DMA_Data32 = 2,
} MDR_DMA_DataSize;

typedef enum {
  MDR_DMA_AddrInc8    = 0,
  MDR_DMA_AddrInc16   = 1,
  MDR_DMA_AddrInc32   = 2,
  MDR_DMA_AddrIncOff  = 3,
} MDR_DMA_AddrInc;

typedef struct {
  MDR_DMA_Mode      Mode               : 3;
  MDR_OnOff         UseBurst           : 1;
  uint32_t          N_minus1           : 10;
  MDR_DMA_Arbitr    ArbitrCount        : 4;
  MDR_OnOff         SrcAHB_Privileged  : 1;
  MDR_OnOff         SrcAHB_Bufferable  : 1;
  MDR_OnOff         SrcAHB_Cachable    : 1;
  MDR_OnOff         DestAHB_Privileged : 1;
  MDR_OnOff         DestAHB_Bufferable : 1;
  MDR_OnOff         DestAHB_Cachable   : 1; 
  MDR_DMA_DataSize  Src_DataSize       : 2;
  MDR_DMA_AddrInc   Src_AddrInc        : 2;
  MDR_DMA_DataSize  Dest_DataSize      : 2;
  MDR_DMA_AddrInc   Dest_AddrInc       : 2;
} MDR_DMA_ChCtrlBits;

#define MDR_DMA_ChCtrl_Mode_Pos             (0UL)
#define MDR_DMA_ChCtrl_Mode_Msk             (0x7UL)
#define MDR_DMA_ChCtrl_UseBurst_Pos         (1UL)
#define MDR_DMA_ChCtrl_UseBurste_Msk        (0x8UL)
#define MDR_DMA_ChCtrl_N_minus1_Pos         (4UL)
#define MDR_DMA_ChCtrl_N_minus1_Msk         (0x3FF0UL)
#define MDR_DMA_ChCtrl_ArbitrCount_Pos      (14UL)
#define MDR_DMA_ChCtrl_ArbitrCount_Msk      (0x3C000UL)
#define MDR_DMA_ChCtrl_SrcPrivileged_Pos    (18UL)
#define MDR_DMA_ChCtrl_SrcPrivileged_Msk    (0x40000UL)
#define MDR_DMA_ChCtrl_SrcBufferable_Pos    (19UL)
#define MDR_DMA_ChCtrl_SrcBufferable_Msk    (0x80000UL)
#define MDR_DMA_ChCtrl_SrcCachable_Pos      (20UL)
#define MDR_DMA_ChCtrl_SrcCachable_Msk      (0x100000UL)
#define MDR_DMA_ChCtrl_DestPrivileged_Pos   (21UL)
#define MDR_DMA_ChCtrl_DestPrivileged_Msk   (0x200000UL)
#define MDR_DMA_ChCtrl_DestBufferable_Pos   (22UL)
#define MDR_DMA_ChCtrl_DestBufferable_Msk   (0x400000UL)
#define MDR_DMA_ChCtrl_DestCachable_Pos     (23UL)
#define MDR_DMA_ChCtrl_DestCachable_Msk     (0x800000UL)
#define MDR_DMA_ChCtrl_SrcDataSize_Pos      (24UL)
#define MDR_DMA_ChCtrl_SrcDataSize_Msk      (0x3000000UL)
#define MDR_DMA_ChCtrl_SrcAddrInc_Pos       (26UL)
#define MDR_DMA_ChCtrl_SrcAddrInc_Msk       (0xC000000UL)
#define MDR_DMA_ChCtrl_DestDataSize_Pos     (28UL)
#define MDR_DMA_ChCtrl_DestDataSize_Msk     (0x30000000UL)
#define MDR_DMA_ChCtrl_DestAddrInc_Pos      (30UL)
#define MDR_DMA_ChCtrl_DestAddrInc_Msk      (0xC0000000UL)

typedef union {
  uint32_t           Value;
  MDR_DMA_ChCtrlBits Fields;
} MDR_DMA_ChCtrl;

typedef struct {
  uint32_t        Src_EndAddr;                /*!< Specifies the DMA channel source end address */
  uint32_t        Dest_EndAddr;               /*!< Specifies the DMA channel destination end address. */
  MDR_DMA_ChCtrl  Control;                    /*!< Specifies the DMA channel control data configuration. */
  uint32_t        _Unused;                    /*!< Specifies the DMA channel unused memory. */
} MDR_DMA_ChCfg;


//  Структура задания привилегий доступа по шине AHB
typedef struct {
  MDR_OnOff   Privileged: 1;
  MDR_OnOff   Bufferable: 1;
  MDR_OnOff   Cachable  : 1 ; 
  uint32_t              : 29;
} MDR_DMA_ProtAHB_Bits;

typedef union {
  uint32_t             Value;
  MDR_DMA_ProtAHB_Bits Fields;
} MDR_DMA_ProtAHB;


typedef __PACKED_STRUCT {
  MDR_DMA_Mode      Mode               : 3;
  MDR_OnOff         UseBurst           : 1;
  uint32_t                             : 10;
  MDR_DMA_Arbitr    ArbitrCount        : 4;
  uint32_t                             : 6;
  MDR_DMA_DataSize  DataSize           : 2;
  MDR_DMA_AddrInc   Src_AddrInc        : 2;
  uint32_t                             : 2;
  MDR_DMA_AddrInc   Dest_AddrInc       : 2;
} MDR_DMA_CfgTransfBase;


typedef struct {
  union {
  uint32_t              CfgValue;
  MDR_DMA_CfgTransfBase CfgFileds;
  } ;  
  
  //  NULL for default
  MDR_DMA_ProtAHB       *Src_ProtAHB;
  MDR_DMA_ProtAHB       *Dest_ProtAHB;  
} MDR_DMA_CfgTransf;




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

#endif  //_MDR_DMA_DEFS_H

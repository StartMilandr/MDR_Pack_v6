#ifndef _MDR_DMA_VE8X_DEFS_H
#define _MDR_DMA_VE8X_DEFS_H

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

#define MDR_DMA_LIKE_VE8


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
    __IOM uint32_t              CHNL_PRIORITY_SET;           /*!< (@ 0x00000030) Select Alter Structure                                     */
    MDR_DMA_CHNL_RW_Bits        CHNL_PRIORITY_SET_b;
  } ;
  union {
    __OM  uint32_t              CHNL_PRIORITY_CLR;           /*!< (@ 0x00000034) Select Primary Structure                                   */
    MDR_DMA_CHNL_WO_Bits        CHNL_PRIORITY_CLR_b;
  } ;    
  __IM  uint32_t  RESERVED[3];  
  union {
    __IOM uint32_t              ERR_CLR;                     /*!< (@ 0x0000004C) AHB-Lite bus error clear                                   */
    MDR_DMA_CHNL_RW_Bits        ERR_CLR_b;
  } ;  
  // ---- New for VE8 ----
  union {
    __IOM uint32_t CHMUX0;                      /*!< (@ 0x00000050) Periph select for DMA channels 0..3                        */
    struct {
      __IOM uint32_t CH0_Sel    : 8;            /*!< [7..0] Periph Event for DMA_Channel                                       */
      __IOM uint32_t CH1_Sel    : 8;            /*!< [15..8] Periph Event for DMA_Channel                                      */
      __IOM uint32_t CH2_Sel    : 8;            /*!< [23..16] Periph Event for DMA_Channel                                     */
      __IOM uint32_t CH3_Sel    : 8;            /*!< [31..24] Periph Event for DMA_Channel                                     */
    } CHMUX0_b;
  } ;
  union {
    __IOM uint32_t CHMUX1;                      /*!< (@ 0x00000054) Periph select for DMA channels 4..7                        */    
    struct {
      __IOM uint32_t CH4_Sel    : 8;            /*!< [7..0] Periph Event for DMA_Channel                                       */
      __IOM uint32_t CH5_Sel    : 8;            /*!< [15..8] Periph Event for DMA_Channel                                      */
      __IOM uint32_t CH6_Sel    : 8;            /*!< [23..16] Periph Event for DMA_Channel                                     */
      __IOM uint32_t CH7_Sel    : 8;            /*!< [31..24] Periph Event for DMA_Channel                                     */
    } CHMUX1_b;
  } ;
  union {
    __IOM uint32_t CHMUX2;                      /*!< (@ 0x00000058) Periph select for DMA channels 8..11                       */    
    struct {
      __IOM uint32_t CH8_Sel    : 8;            /*!< [7..0] Periph Event for DMA_Channel                                       */
      __IOM uint32_t CH9_Sel    : 8;            /*!< [15..8] Periph Event for DMA_Channel                                      */
      __IOM uint32_t CH10_Sel   : 8;            /*!< [23..16] Periph Event for DMA_Channel                                     */
      __IOM uint32_t CH11_Sel   : 8;            /*!< [31..24] Periph Event for DMA_Channel                                     */
    } CHMUX2_b;
  } ;
  union {
    __IOM uint32_t CHMUX3;                      /*!< (@ 0x0000005C) Periph select for DMA channels 12..15                      */
    struct {
      __IOM uint32_t CH12_Sel   : 8;            /*!< [7..0] Periph Event for DMA_Channel                                       */
      __IOM uint32_t CH13_Sel   : 8;            /*!< [15..8] Periph Event for DMA_Channel                                      */
      __IOM uint32_t CH14_Sel   : 8;            /*!< [23..16] Periph Event for DMA_Channel                                     */
      __IOM uint32_t CH15_Sel   : 8;            /*!< [31..24] Periph Event for DMA_Channel                                     */
    } CHMUX3_b;
  } ;
  union {
    __IOM uint32_t CHMUX4;                      /*!< (@ 0x00000060) Periph select for DMA channels 16..19                      */
    struct {
      __IOM uint32_t CH16_Sel   : 8;            /*!< [7..0] Periph Event for DMA_Channel                                       */
      __IOM uint32_t CH17_Sel   : 8;            /*!< [15..8] Periph Event for DMA_Channel                                      */
      __IOM uint32_t CH18_Sel   : 8;            /*!< [23..16] Periph Event for DMA_Channel                                     */
      __IOM uint32_t CH19_Sel   : 8;            /*!< [31..24] Periph Event for DMA_Channel                                     */
    } CHMUX4_b;
  } ;
  union {
    __IOM uint32_t CHMUX5;                      /*!< (@ 0x00000064) Periph select for DMA channels 20..23                      */
    struct {
      __IOM uint32_t CH20_Sel   : 8;            /*!< [7..0] Periph Event for DMA_Channel                                       */
      __IOM uint32_t CH21_Sel   : 8;            /*!< [15..8] Periph Event for DMA_Channel                                      */
      __IOM uint32_t CH22_Sel   : 8;            /*!< [23..16] Periph Event for DMA_Channel                                     */
      __IOM uint32_t CH23_Sel   : 8;            /*!< [31..24] Periph Event for DMA_Channel                                     */
    } CHMUX5_b;
  } ;
  union {
    __IOM uint32_t CHMUX6;                      /*!< (@ 0x00000068) Periph select for DMA channels 24..27                      */
    struct {
      __IOM uint32_t CH24_Sel   : 8;            /*!< [7..0] Periph Event for DMA_Channel                                       */
      __IOM uint32_t CH25_Sel   : 8;            /*!< [15..8] Periph Event for DMA_Channel                                      */
      __IOM uint32_t CH26_Sel   : 8;            /*!< [23..16] Periph Event for DMA_Channel                                     */
      __IOM uint32_t CH27_Sel   : 8;            /*!< [31..24] Periph Event for DMA_Channel                                     */
    } CHMUX6_b;
  } ;
  union {
    __IOM uint32_t CHMUX7;                      /*!< (@ 0x0000006C) Periph select for DMA channels 28..31                      */
    struct {
      __IOM uint32_t CH28_Sel   : 8;            /*!< [7..0] Periph Event for DMA_Channel                                       */
      __IOM uint32_t CH29_Sel   : 8;            /*!< [15..8] Periph Event for DMA_Channel                                      */
      __IOM uint32_t CH30_Sel   : 8;            /*!< [23..16] Periph Event for DMA_Channel                                     */
      __IOM uint32_t CH31_Sel   : 8;            /*!< [31..24] Periph Event for DMA_Channel                                     */
    } CHMUX7_b;
  } ; 
  
} MDR_DMA_Type;                                 /*!< Size = 80 (0x50)                                                          */



/* ========================================================  CHMUX0  ========================================================= */
#define MDR_DMA_CHMUX0_CH0_Sel_Pos        (0UL)                     /*!< MDR_DMA CHMUX0: CH0_Sel (Bit 0)                       */
#define MDR_DMA_CHMUX0_CH0_Sel_Msk        (0xffUL)                  /*!< MDR_DMA CHMUX0: CH0_Sel (Bitfield-Mask: 0xff)         */
#define MDR_DMA_CHMUX0_CH1_Sel_Pos        (8UL)                     /*!< MDR_DMA CHMUX0: CH1_Sel (Bit 8)                       */
#define MDR_DMA_CHMUX0_CH1_Sel_Msk        (0xff00UL)                /*!< MDR_DMA CHMUX0: CH1_Sel (Bitfield-Mask: 0xff)         */
#define MDR_DMA_CHMUX0_CH2_Sel_Pos        (16UL)                    /*!< MDR_DMA CHMUX0: CH2_Sel (Bit 16)                      */
#define MDR_DMA_CHMUX0_CH2_Sel_Msk        (0xff0000UL)              /*!< MDR_DMA CHMUX0: CH2_Sel (Bitfield-Mask: 0xff)         */
#define MDR_DMA_CHMUX0_CH3_Sel_Pos        (24UL)                    /*!< MDR_DMA CHMUX0: CH3_Sel (Bit 24)                      */
#define MDR_DMA_CHMUX0_CH3_Sel_Msk        (0xff000000UL)            /*!< MDR_DMA CHMUX0: CH3_Sel (Bitfield-Mask: 0xff)         */
/* ========================================================  CHMUX1  ========================================================= */
#define MDR_DMA_CHMUX1_CH4_Sel_Pos        (0UL)                     /*!< MDR_DMA CHMUX1: CH4_Sel (Bit 0)                       */
#define MDR_DMA_CHMUX1_CH4_Sel_Msk        (0xffUL)                  /*!< MDR_DMA CHMUX1: CH4_Sel (Bitfield-Mask: 0xff)         */
#define MDR_DMA_CHMUX1_CH5_Sel_Pos        (8UL)                     /*!< MDR_DMA CHMUX1: CH5_Sel (Bit 8)                       */
#define MDR_DMA_CHMUX1_CH5_Sel_Msk        (0xff00UL)                /*!< MDR_DMA CHMUX1: CH5_Sel (Bitfield-Mask: 0xff)         */
#define MDR_DMA_CHMUX1_CH6_Sel_Pos        (16UL)                    /*!< MDR_DMA CHMUX1: CH6_Sel (Bit 16)                      */
#define MDR_DMA_CHMUX1_CH6_Sel_Msk        (0xff0000UL)              /*!< MDR_DMA CHMUX1: CH6_Sel (Bitfield-Mask: 0xff)         */
#define MDR_DMA_CHMUX1_CH7_Sel_Pos        (24UL)                    /*!< MDR_DMA CHMUX1: CH7_Sel (Bit 24)                      */
#define MDR_DMA_CHMUX1_CH7_Sel_Msk        (0xff000000UL)            /*!< MDR_DMA CHMUX1: CH7_Sel (Bitfield-Mask: 0xff)         */
/* ========================================================  CHMUX2  ========================================================= */
#define MDR_DMA_CHMUX2_CH8_Sel_Pos        (0UL)                     /*!< MDR_DMA CHMUX2: CH8_Sel (Bit 0)                       */
#define MDR_DMA_CHMUX2_CH8_Sel_Msk        (0xffUL)                  /*!< MDR_DMA CHMUX2: CH8_Sel (Bitfield-Mask: 0xff)         */
#define MDR_DMA_CHMUX2_CH9_Sel_Pos        (8UL)                     /*!< MDR_DMA CHMUX2: CH9_Sel (Bit 8)                       */
#define MDR_DMA_CHMUX2_CH9_Sel_Msk        (0xff00UL)                /*!< MDR_DMA CHMUX2: CH9_Sel (Bitfield-Mask: 0xff)         */
#define MDR_DMA_CHMUX2_CH10_Sel_Pos       (16UL)                    /*!< MDR_DMA CHMUX2: CH10_Sel (Bit 16)                     */
#define MDR_DMA_CHMUX2_CH10_Sel_Msk       (0xff0000UL)              /*!< MDR_DMA CHMUX2: CH10_Sel (Bitfield-Mask: 0xff)        */
#define MDR_DMA_CHMUX2_CH11_Sel_Pos       (24UL)                    /*!< MDR_DMA CHMUX2: CH11_Sel (Bit 24)                     */
#define MDR_DMA_CHMUX2_CH11_Sel_Msk       (0xff000000UL)            /*!< MDR_DMA CHMUX2: CH11_Sel (Bitfield-Mask: 0xff)        */
/* ========================================================  CHMUX3  ========================================================= */
#define MDR_DMA_CHMUX3_CH12_Sel_Pos       (0UL)                     /*!< MDR_DMA CHMUX3: CH12_Sel (Bit 0)                      */
#define MDR_DMA_CHMUX3_CH12_Sel_Msk       (0xffUL)                  /*!< MDR_DMA CHMUX3: CH12_Sel (Bitfield-Mask: 0xff)        */
#define MDR_DMA_CHMUX3_CH13_Sel_Pos       (8UL)                     /*!< MDR_DMA CHMUX3: CH13_Sel (Bit 8)                      */
#define MDR_DMA_CHMUX3_CH13_Sel_Msk       (0xff00UL)                /*!< MDR_DMA CHMUX3: CH13_Sel (Bitfield-Mask: 0xff)        */
#define MDR_DMA_CHMUX3_CH14_Sel_Pos       (16UL)                    /*!< MDR_DMA CHMUX3: CH14_Sel (Bit 16)                     */
#define MDR_DMA_CHMUX3_CH14_Sel_Msk       (0xff0000UL)              /*!< MDR_DMA CHMUX3: CH14_Sel (Bitfield-Mask: 0xff)        */
#define MDR_DMA_CHMUX3_CH15_Sel_Pos       (24UL)                    /*!< MDR_DMA CHMUX3: CH15_Sel (Bit 24)                     */
#define MDR_DMA_CHMUX3_CH15_Sel_Msk       (0xff000000UL)            /*!< MDR_DMA CHMUX3: CH15_Sel (Bitfield-Mask: 0xff)        */
/* ========================================================  CHMUX4  ========================================================= */
#define MDR_DMA_CHMUX4_CH16_Sel_Pos       (0UL)                     /*!< MDR_DMA CHMUX4: CH16_Sel (Bit 0)                      */
#define MDR_DMA_CHMUX4_CH16_Sel_Msk       (0xffUL)                  /*!< MDR_DMA CHMUX4: CH16_Sel (Bitfield-Mask: 0xff)        */
#define MDR_DMA_CHMUX4_CH17_Sel_Pos       (8UL)                     /*!< MDR_DMA CHMUX4: CH17_Sel (Bit 8)                      */
#define MDR_DMA_CHMUX4_CH17_Sel_Msk       (0xff00UL)                /*!< MDR_DMA CHMUX4: CH17_Sel (Bitfield-Mask: 0xff)        */
#define MDR_DMA_CHMUX4_CH18_Sel_Pos       (16UL)                    /*!< MDR_DMA CHMUX4: CH18_Sel (Bit 16)                     */
#define MDR_DMA_CHMUX4_CH18_Sel_Msk       (0xff0000UL)              /*!< MDR_DMA CHMUX4: CH18_Sel (Bitfield-Mask: 0xff)        */
#define MDR_DMA_CHMUX4_CH19_Sel_Pos       (24UL)                    /*!< MDR_DMA CHMUX4: CH19_Sel (Bit 24)                     */
#define MDR_DMA_CHMUX4_CH19_Sel_Msk       (0xff000000UL)            /*!< MDR_DMA CHMUX4: CH19_Sel (Bitfield-Mask: 0xff)        */
/* ========================================================  CHMUX5  ========================================================= */
#define MDR_DMA_CHMUX5_CH20_Sel_Pos       (0UL)                     /*!< MDR_DMA CHMUX5: CH20_Sel (Bit 0)                      */
#define MDR_DMA_CHMUX5_CH20_Sel_Msk       (0xffUL)                  /*!< MDR_DMA CHMUX5: CH20_Sel (Bitfield-Mask: 0xff)        */
#define MDR_DMA_CHMUX5_CH21_Sel_Pos       (8UL)                     /*!< MDR_DMA CHMUX5: CH21_Sel (Bit 8)                      */
#define MDR_DMA_CHMUX5_CH21_Sel_Msk       (0xff00UL)                /*!< MDR_DMA CHMUX5: CH21_Sel (Bitfield-Mask: 0xff)        */
#define MDR_DMA_CHMUX5_CH22_Sel_Pos       (16UL)                    /*!< MDR_DMA CHMUX5: CH22_Sel (Bit 16)                     */
#define MDR_DMA_CHMUX5_CH22_Sel_Msk       (0xff0000UL)              /*!< MDR_DMA CHMUX5: CH22_Sel (Bitfield-Mask: 0xff)        */
#define MDR_DMA_CHMUX5_CH23_Sel_Pos       (24UL)                    /*!< MDR_DMA CHMUX5: CH23_Sel (Bit 24)                     */
#define MDR_DMA_CHMUX5_CH23_Sel_Msk       (0xff000000UL)            /*!< MDR_DMA CHMUX5: CH23_Sel (Bitfield-Mask: 0xff)        */
/* ========================================================  CHMUX6  ========================================================= */
#define MDR_DMA_CHMUX6_CH24_Sel_Pos       (0UL)                     /*!< MDR_DMA CHMUX6: CH24_Sel (Bit 0)                      */
#define MDR_DMA_CHMUX6_CH24_Sel_Msk       (0xffUL)                  /*!< MDR_DMA CHMUX6: CH24_Sel (Bitfield-Mask: 0xff)        */
#define MDR_DMA_CHMUX6_CH25_Sel_Pos       (8UL)                     /*!< MDR_DMA CHMUX6: CH25_Sel (Bit 8)                      */
#define MDR_DMA_CHMUX6_CH25_Sel_Msk       (0xff00UL)                /*!< MDR_DMA CHMUX6: CH25_Sel (Bitfield-Mask: 0xff)        */
#define MDR_DMA_CHMUX6_CH26_Sel_Pos       (16UL)                    /*!< MDR_DMA CHMUX6: CH26_Sel (Bit 16)                     */
#define MDR_DMA_CHMUX6_CH26_Sel_Msk       (0xff0000UL)              /*!< MDR_DMA CHMUX6: CH26_Sel (Bitfield-Mask: 0xff)        */
#define MDR_DMA_CHMUX6_CH27_Sel_Pos       (24UL)                    /*!< MDR_DMA CHMUX6: CH27_Sel (Bit 24)                     */
#define MDR_DMA_CHMUX6_CH27_Sel_Msk       (0xff000000UL)            /*!< MDR_DMA CHMUX6: CH27_Sel (Bitfield-Mask: 0xff)        */
/* ========================================================  CHMUX7  ========================================================= */
#define MDR_DMA_CHMUX7_CH28_Sel_Pos       (0UL)                     /*!< MDR_DMA CHMUX7: CH28_Sel (Bit 0)                      */
#define MDR_DMA_CHMUX7_CH28_Sel_Msk       (0xffUL)                  /*!< MDR_DMA CHMUX7: CH28_Sel (Bitfield-Mask: 0xff)        */
#define MDR_DMA_CHMUX7_CH29_Sel_Pos       (8UL)                     /*!< MDR_DMA CHMUX7: CH29_Sel (Bit 8)                      */
#define MDR_DMA_CHMUX7_CH29_Sel_Msk       (0xff00UL)                /*!< MDR_DMA CHMUX7: CH29_Sel (Bitfield-Mask: 0xff)        */
#define MDR_DMA_CHMUX7_CH30_Sel_Pos       (16UL)                    /*!< MDR_DMA CHMUX7: CH30_Sel (Bit 16)                     */
#define MDR_DMA_CHMUX7_CH30_Sel_Msk       (0xff0000UL)              /*!< MDR_DMA CHMUX7: CH30_Sel (Bitfield-Mask: 0xff)        */
#define MDR_DMA_CHMUX7_CH31_Sel_Pos       (24UL)                    /*!< MDR_DMA CHMUX7: CH31_Sel (Bit 24)                     */
#define MDR_DMA_CHMUX7_CH31_Sel_Msk       (0xff000000UL)            /*!< MDR_DMA CHMUX7: CH31_Sel (Bitfield-Mask: 0xff)        */



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

#endif  //_MDR_DMA_VE8X_DEFS_H

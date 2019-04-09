#ifndef _MDR_CRC_VK234_DEF_H
#define _MDR_CRC_VK234_DEF_H

#ifdef __cplusplus
extern "C" {
#endif

#include <MDR_Types.h>

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
typedef enum {
  CRC_FIRST_LSB = 0,
  CRC_FIRST_MSB = 1,  
} MDT_CRC_FirstBit;

//typedef enum {
//  CRC_FIRST_MSB = 0,
//  CRC_FIRST_LSB = 1,  
//} MDT_CRC_FirstBit;

typedef enum {
  CRC_FIFO_8Bit  = 0,
  CRC_FIFO_16Bit = 1,  
  CRC_FIFO_32Bit = 2,
} MDT_CRC_FIFO_WordSize;

typedef enum {
  CRC_Word_8Bit  = 0,
  CRC_Word_16Bit = 1,  
  CRC_Word_32Bit = 2,
} MDT_CRC_WordSize;

typedef struct {
  __IOM MDR_OnOff             CRCEn      : 1;            /*!< [0..0] Enable block                                                       */
  __IOM MDT_CRC_FirstBit      DataInv    : 1;            /*!< [1..1] Bit first selection                                                */
  __IOM MDR_OnOff             DMA_En     : 1;            /*!< [2..2] DMA Enable                                                         */
  __IOM MDT_CRC_FIFO_WordSize DL_Size    : 2;            /*!< [4..3] Loading data size                                                  */
  __IOM MDT_CRC_WordSize      DC_Size    : 2;            /*!< [6..5] Calculating data size                                              */
  __IM  uint32_t                         : 25;
} MDR_CRC_CTRL_Bits;

#define MDR_CRC_CTRL_CRCEn_Pos      (0UL)                     /*!< MDR_CRC_VK234 CTRL: CRCEn (Bit 0)                     */
#define MDR_CRC_CTRL_CRCEn_Msk      (0x1UL)                   /*!< MDR_CRC_VK234 CTRL: CRCEn (Bitfield-Mask: 0x01)       */
#define MDR_CRC_CTRL_DataInv_Pos    (1UL)                     /*!< MDR_CRC_VK234 CTRL: DataInv (Bit 1)                   */
#define MDR_CRC_CTRL_DataInv_Msk    (0x2UL)                   /*!< MDR_CRC_VK234 CTRL: DataInv (Bitfield-Mask: 0x01)     */
#define MDR_CRC_CTRL_DMA_En_Pos     (2UL)                     /*!< MDR_CRC_VK234 CTRL: DMA_En (Bit 2)                    */
#define MDR_CRC_CTRL_DMA_En_Msk     (0x4UL)                   /*!< MDR_CRC_VK234 CTRL: DMA_En (Bitfield-Mask: 0x01)      */
#define MDR_CRC_CTRL_DL_Size_Pos    (3UL)                     /*!< MDR_CRC_VK234 CTRL: DL_Size (Bit 3)                   */
#define MDR_CRC_CTRL_DL_Size_Msk    (0x18UL)                  /*!< MDR_CRC_VK234 CTRL: DL_Size (Bitfield-Mask: 0x03)     */
#define MDR_CRC_CTRL_DC_Size_Pos    (5UL)                     /*!< MDR_CRC_VK234 CTRL: DC_Size (Bit 5)                   */
#define MDR_CRC_CTRL_DC_Size_Msk    (0x60UL)                  /*!< MDR_CRC_VK234 CTRL: DC_Size (Bitfield-Mask: 0x03)     */

#define MDR_CRC_CNTRL_CLR_SIZES      (MDR_CRC_CTRL_DL_Size_Msk | MDR_CRC_CTRL_DC_Size_Msk)
#define MDR_CRC_CNTRL_SIZE_8BIT      (VAL2FLD_Pos(CRC_Word_8Bit,  MDR_CRC_CTRL_DL_Size_Pos) | VAL2FLD_Pos(CRC_Word_8Bit,  MDR_CRC_CTRL_DC_Size_Pos))
#define MDR_CRC_CNTRL_SIZE_16BIT     (VAL2FLD_Pos(CRC_Word_16Bit, MDR_CRC_CTRL_DL_Size_Pos) | VAL2FLD_Pos(CRC_Word_16Bit, MDR_CRC_CTRL_DC_Size_Pos))
#define MDR_CRC_CNTRL_SIZE_32BIT     (VAL2FLD_Pos(CRC_Word_32Bit, MDR_CRC_CTRL_DL_Size_Pos) | VAL2FLD_Pos(CRC_Word_32Bit, MDR_CRC_CTRL_DC_Size_Pos))

typedef struct {
  __IOM MDR_OnOff   ConvComp   : 1;            /*!< [0..0] Convertion Completed                                               */
  __IM  MDR_OnOff   FIFO_Full  : 1;            /*!< [1..1] FIFO Full                                                          */
  __IM  MDR_OnOff   FIFO_Empty : 1;            /*!< [2..2] FIFO Empty                                                         */
  __IM  MDR_OnOff   FIFO_Over  : 1;            /*!< [3..3] FIFO Over                                                          */
  __IM  uint32_t               : 28;
} MDR_CRC_STAT_Bits;

#define MDR_CRC_STAT_ConvComp_Pos   (0UL)                     /*!< MDR_CRC_VK234 STAT: ConvComp (Bit 0)                  */
#define MDR_CRC_STAT_ConvComp_Msk   (0x1UL)                   /*!< MDR_CRC_VK234 STAT: ConvComp (Bitfield-Mask: 0x01)    */
#define MDR_CRC_STAT_FIFO_Full_Pos  (1UL)                     /*!< MDR_CRC_VK234 STAT: FIFO_Full (Bit 1)                 */
#define MDR_CRC_STAT_FIFO_Full_Msk  (0x2UL)                   /*!< MDR_CRC_VK234 STAT: FIFO_Full (Bitfield-Mask: 0x01)   */
#define MDR_CRC_STAT_FIFO_Empty_Pos (2UL)                     /*!< MDR_CRC_VK234 STAT: FIFO_Empty (Bit 2)                */
#define MDR_CRC_STAT_FIFO_Empty_Msk (0x4UL)                   /*!< MDR_CRC_VK234 STAT: FIFO_Empty (Bitfield-Mask: 0x01)  */
#define MDR_CRC_STAT_FIFO_Over_Pos  (3UL)                     /*!< MDR_CRC_VK234 STAT: FIFO_Over (Bit 3)                 */
#define MDR_CRC_STAT_FIFO_Over_Msk  (0x8UL)                   /*!< MDR_CRC_VK234 STAT: FIFO_Over (Bitfield-Mask: 0x01)   */


typedef struct {
  __IM  uint32_t Value      : 32;           /*!< [31..0] Data Value                                                        */
} MDR_CRC_DATAIN_Bits;

#define MDR_CRC_DATAI_Value_Pos     (0UL)                     /*!< MDR_CRC_VK234 DATAI: Value (Bit 0)                    */
#define MDR_CRC_DATAI_Value_Msk     (0xffffffffUL)            /*!< MDR_CRC_VK234 DATAI: Value (Bitfield-Mask: 0xffffffff) */


typedef struct {
  __IOM uint16_t    CRC_Out    : 16;           /*!< [15..0] Result and Start Value                                            */
  __IM  uint32_t               : 16;
} MDR_CRC_OUT_Bits;

#define MDR_CRC_CRC_VAL_CRC_Out_Pos (0UL)                     /*!< MDR_CRC_VK234 CRC_VAL: CRC_Out (Bit 0)                */
#define MDR_CRC_CRC_VAL_CRC_Out_Msk (0xffffUL)                /*!< MDR_CRC_VK234 CRC_VAL: CRC_Out (Bitfield-Mask: 0xffff) */


typedef struct {
  __IOM uint32_t     CRC_POL    : 17;           /*!< [16..0] Select polinom bits                                               */
  __IM  uint32_t                : 15;
} MDR_CRC_POL_Bits;

#define MDR_CRC_CRC_POL_CRC_POL_Pos (0UL)                     /*!< MDR_CRC_VK234 CRC_POL: CRC_POL (Bit 0)                */
#define MDR_CRC_CRC_POL_CRC_POL_Msk (0x1ffffUL)               /*!< MDR_CRC_VK234 CRC_POL: CRC_POL (Bitfield-Mask: 0x1ffff) */


typedef struct {                                /*!< (@ 0x40038000) MDR_CRC_VK234 Structure                                    */  
  union {
    __IOM uint32_t        CTRL;                 /*!< (@ 0x00000000) Control register                                           */
    MDR_CRC_CTRL_Bits     CTRL_b;
  } ;  
  union {
    __IOM uint32_t        STAT;                 /*!< (@ 0x00000004) Status register                                            */
    MDR_CRC_STAT_Bits     STAT_b;
  } ;
  
  union {
    __OM  uint32_t        DATAI;                /*!< (@ 0x00000008) FIFO Input                                                 */
    MDR_CRC_DATAIN_Bits   DATAI_b; 
  } ;
  
  union {
    __IOM uint32_t        CRC_OUT;              /*!< (@ 0x0000000C) CRC result                                                 */
    MDR_CRC_OUT_Bits      CRC_OUT_b;
  } ;
  
  union {
    __IOM uint32_t        CRC_POL;              /*!< (@ 0x00000010) CRC Polinom select                                         */
    MDR_CRC_POL_Bits      CRC_POL_b;
  } ;
} MDR_CRC_Type;                                 /*!< Size = 20 (0x14)                                                          */


typedef struct {
  __IOM MDR_OnOff             Enable      : 1;            /*!< [0..0] Enable block                                                       */
  __IOM MDT_CRC_FirstBit      FirstBit    : 1;            /*!< [1..1] Bit first selection                                                */
  __IOM MDR_OnOff             DMA_En      : 1;            /*!< [2..2] DMA Enable                                                         */
  __IOM MDT_CRC_FIFO_WordSize WordSizeFIFO: 2;            /*!< [4..3] Loading data size                                                  */
  __IOM MDT_CRC_WordSize      WordSize    : 2;            /*!< [6..5] Calculating data size                                              */
  __IM  uint32_t                          : 25;
} MDR_CRC_CfgBits;

typedef union {
  __IOM uint32_t      Cfg;
  MDR_CRC_CfgBits     Cfg_b;
} MDR_CRC_CfgReg;

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

#endif  //  _MDR_CRC_VK234_DEF_H

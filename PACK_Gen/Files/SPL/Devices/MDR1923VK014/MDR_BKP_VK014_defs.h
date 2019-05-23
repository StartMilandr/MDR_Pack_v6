#ifndef _MDR_BKP_VK014_DEFS_H
#define _MDR_BKP_VK014_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif


#include <MDR_BKP_VE8VK14_defs.h>
#include <MDR_RTC_VE8x_defs.h>
  
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

//-------   Reg_61  ----------
typedef enum {                     /*!< MDR_BKP_REG_61_TMR0_LDO1_SRILow                                           */ 
  MDR_BKP_LDO_SRILow_ge10MHz = 0,  /*!< ge10MHz : Extra_I about ~300uA                                            */
  MDR_BKP_LDO_SRILow_ge200KHz = 1, /*!< ge200KHz : Extra_I about ~7uA                                             */
  MDR_BKP_LDO_SRILow_ge500KHz = 2, /*!< ge500KHz : Extra_I about ~20uA                                            */
  MDR_BKP_LDO_SRILow_ge1MHz = 3,   /*!< ge1MHz : Extra_I about ~80uA                                              */
  MDR_BKP_LDO_SRILow_GensOff = 4,  /*!< GensOff : Extra_I about ~2uA                                              */
  MDR_BKP_LDO_SRILow_ge40MHz = 5,  /*!< ge40MHz : Extra_I about ~900uA                                            */
  MDR_BKP_LDO_SRILow_ge80MHz = 6,  /*!< ge80MHz : Extra_I about ~5mA                                              */
  MDR_BKP_LDO_SRILow_gt80MHz = 7,  /*!< gt80MHz : Extra_I about ~20mA                                             */
  
} MDR_BKP_LDO_SRILow;

typedef enum {                     /*!< MDR_BKP_REG_61_TMR0_LDO1_Trim                                             */ 
  MDR_BKP_LDO_Trim_add_0v1  = 0,   /*!< add_0v1 : LD0 extra voltage +0.1V                                         */
  MDR_BKP_LDO_Trim_add_0v06 = 1,   /*!< add_0v06 : LD0 extra voltage +0.06V                                       */
  MDR_BKP_LDO_Trim_add_0v04 = 2,   /*!< add_0v04 : LD0 extra voltage +0.04V                                       */
  MDR_BKP_LDO_Trim_add_0v01 = 3,   /*!< add_0v01 : LD0 extra voltage +0.01V                                       */
  MDR_BKP_LDO_Trim_sub_0v01 = 4,   /*!< sub_0v01 : LD0 extra voltage -0.01V                                       */
  MDR_BKP_LDO_Trim_sub_0v04 = 5,   /*!< sub_0v04 : LD0 extra voltage -0.04V                                       */
  MDR_BKP_LDO_Trim_sub_0v06 = 6,   /*!< sub_0v06 : LD0 extra voltage -0.06V                                       */
  MDR_BKP_LDO_Trim_sub_0v1  = 7,   /*!< sub_0v1 : LD0 extra voltage -0.1V                                         */ 
} MDR_BKP_LDO_Trim;

typedef struct {
      __IOM MDR_BKP_LDO_SRILow    LDO0_SRILow : 3;           /*!< [2..0] LDO Power adjustment                      */
      __IOM MDR_BKP_LDO_Trim      LDO0_Trim   : 3;           /*!< [5..3] LDO voltage tuning                        */
      __IOM MDR_OnOff             LDO0_En     : 1;           /*!< [6..6] LDO Enable                                */
      __IOM MDR_OnOff             LDO0_RDY    : 1;           /*!< [7..7] LDO Ready                                 */
      __IOM MDR_BKP_LDO_SRILow    LDO1_SRILow : 3;           /*!< [10..8] LDO Power adjustment                     */
      __IOM MDR_BKP_LDO_Trim      LDO1_Trim   : 3;           /*!< [13..11] LDO voltage tuning                      */
      __IOM MDR_OnOff             LDO1_En     : 1;           /*!< [14..14] LDO Enable                              */
      __IOM MDR_OnOff             LDO1_RDY    : 1;           /*!< [15..15] LDO Ready                               */
      __IOM MDR_BKP_LDO_SRILow    LDO2_SRILow : 3;           /*!< [18..16] LDO Power adjustment                    */
      __IOM MDR_BKP_LDO_Trim      LDO2_Trim   : 3;           /*!< [21..19] LDO voltage tuning                      */
      __IOM MDR_OnOff             LDO2_En     : 1;           /*!< [22..22] LDO Enable                              */
      __IOM MDR_OnOff             LDO2_RDY    : 1;           /*!< [23..23] LDO Ready                               */
      __IOM MDR_BKP_LDO_SRILow    LDO3_SRILow : 3;           /*!< [26..24] LDO Power adjustment                    */
      __IOM MDR_BKP_LDO_Trim      LDO3_Trim   : 3;           /*!< [29..27] LDO voltage tuning                      */
      __IOM MDR_OnOff             LDO3_En     : 1;           /*!< [30..30] LDO Enable                              */
      __IOM MDR_OnOff             LDO3_RDY    : 1;           /*!< [31..31] LDO Ready                               */
} MDR_BKP_REG61_Bits;


#define MDR_BKP_REG61_LDO0_SRILow_Pos (0UL)                   /*!< MDR_BKP REG_61_TMR0: LDO0_SRILow (Bit 0)              */
#define MDR_BKP_REG61_LDO0_SRILow_Msk (0x7UL)                 /*!< MDR_BKP REG_61_TMR0: LDO0_SRILow (Bitfield-Mask: 0x07) */
#define MDR_BKP_REG61_LDO0_Trim_Pos (3UL)                     /*!< MDR_BKP REG_61_TMR0: LDO0_Trim (Bit 3)                */
#define MDR_BKP_REG61_LDO0_Trim_Msk (0x38UL)                  /*!< MDR_BKP REG_61_TMR0: LDO0_Trim (Bitfield-Mask: 0x07)  */
#define MDR_BKP_REG61_LDO0_En_Pos   (6UL)                     /*!< MDR_BKP REG_61_TMR0: LDO0_En (Bit 6)                  */
#define MDR_BKP_REG61_LDO0_En_Msk   (0x40UL)                  /*!< MDR_BKP REG_61_TMR0: LDO0_En (Bitfield-Mask: 0x01)    */
#define MDR_BKP_REG61_LDO0_RDY_Pos  (7UL)                     /*!< MDR_BKP REG_61_TMR0: LDO0_RDY (Bit 7)                 */
#define MDR_BKP_REG61_LDO0_RDY_Msk  (0x80UL)                  /*!< MDR_BKP REG_61_TMR0: LDO0_RDY (Bitfield-Mask: 0x01)   */
#define MDR_BKP_REG61_LDO1_SRILow_Pos (8UL)                   /*!< MDR_BKP REG_61_TMR0: LDO1_SRILow (Bit 8)              */
#define MDR_BKP_REG61_LDO1_SRILow_Msk (0x700UL)               /*!< MDR_BKP REG_61_TMR0: LDO1_SRILow (Bitfield-Mask: 0x07) */
#define MDR_BKP_REG61_LDO1_Trim_Pos (11UL)                    /*!< MDR_BKP REG_61_TMR0: LDO1_Trim (Bit 11)               */
#define MDR_BKP_REG61_LDO1_Trim_Msk (0x3800UL)                /*!< MDR_BKP REG_61_TMR0: LDO1_Trim (Bitfield-Mask: 0x07)  */
#define MDR_BKP_REG61_LDO1_En_Pos   (14UL)                    /*!< MDR_BKP REG_61_TMR0: LDO1_En (Bit 14)                 */
#define MDR_BKP_REG61_LDO1_En_Msk   (0x4000UL)                /*!< MDR_BKP REG_61_TMR0: LDO1_En (Bitfield-Mask: 0x01)    */
#define MDR_BKP_REG61_LDO1_RDY_Pos  (15UL)                    /*!< MDR_BKP REG_61_TMR0: LDO1_RDY (Bit 15)                */
#define MDR_BKP_REG61_LDO1_RDY_Msk  (0x8000UL)                /*!< MDR_BKP REG_61_TMR0: LDO1_RDY (Bitfield-Mask: 0x01)   */
#define MDR_BKP_REG61_LDO2_SRILow_Pos (16UL)                  /*!< MDR_BKP REG_61_TMR0: LDO2_SRILow (Bit 16)             */
#define MDR_BKP_REG61_LDO2_SRILow_Msk (0x70000UL)             /*!< MDR_BKP REG_61_TMR0: LDO2_SRILow (Bitfield-Mask: 0x07) */
#define MDR_BKP_REG61_LDO2_Trim_Pos (19UL)                    /*!< MDR_BKP REG_61_TMR0: LDO2_Trim (Bit 19)               */
#define MDR_BKP_REG61_LDO2_Trim_Msk (0x380000UL)              /*!< MDR_BKP REG_61_TMR0: LDO2_Trim (Bitfield-Mask: 0x07)  */
#define MDR_BKP_REG61_LDO2_En_Pos   (22UL)                    /*!< MDR_BKP REG_61_TMR0: LDO2_En (Bit 22)                 */
#define MDR_BKP_REG61_LDO2_En_Msk   (0x400000UL)              /*!< MDR_BKP REG_61_TMR0: LDO2_En (Bitfield-Mask: 0x01)    */
#define MDR_BKP_REG61_LDO2_RDY_Pos  (23UL)                    /*!< MDR_BKP REG_61_TMR0: LDO2_RDY (Bit 23)                */
#define MDR_BKP_REG61_LDO2_RDY_Msk  (0x800000UL)              /*!< MDR_BKP REG_61_TMR0: LDO2_RDY (Bitfield-Mask: 0x01)   */
#define MDR_BKP_REG61_LDO3_SRILow_Pos (24UL)                  /*!< MDR_BKP REG_61_TMR0: LDO3_SRILow (Bit 24)             */
#define MDR_BKP_REG61_LDO3_SRILow_Msk (0x7000000UL)           /*!< MDR_BKP REG_61_TMR0: LDO3_SRILow (Bitfield-Mask: 0x07) */
#define MDR_BKP_REG61_LDO3_Trim_Pos (27UL)                    /*!< MDR_BKP REG_61_TMR0: LDO3_Trim (Bit 27)               */
#define MDR_BKP_REG61_LDO3_Trim_Msk (0x38000000UL)            /*!< MDR_BKP REG_61_TMR0: LDO3_Trim (Bitfield-Mask: 0x07)  */
#define MDR_BKP_REG61_LDO3_En_Pos   (30UL)                    /*!< MDR_BKP REG_61_TMR0: LDO3_En (Bit 30)                 */
#define MDR_BKP_REG61_LDO3_En_Msk   (0x40000000UL)            /*!< MDR_BKP REG_61_TMR0: LDO3_En (Bitfield-Mask: 0x01)    */
#define MDR_BKP_REG61_LDO3_RDY_Pos  (31UL)                    /*!< MDR_BKP REG_61_TMR0: LDO3_RDY (Bit 31)                */
#define MDR_BKP_REG61_LDO3_RDY_Msk  (0x80000000UL)            /*!< MDR_BKP REG_61_TMR0: LDO3_RDY (Bitfield-Mask: 0x01)   */


//-------   Reg_61  ----------
typedef struct {
      __IOM MDR_BKP_LDO_SRILow    LDO_BUcc_SRILow : 3;       /*!< [2..0] LDO Power adjustment                      */
      __IOM MDR_BKP_LDO_Trim      LDO_BUcc_Trim   : 3;       /*!< [5..3] LDO voltage tuning                        */
      __IOM MDR_OnOff             LDO_BUcc_En     : 1;       /*!< [6..6] LDO Enable                                */
      __IOM MDR_OnOff             LDO_BUcc_RDY    : 1;       /*!< [7..7] LDO Ready                                 */
      __IOM MDR_BKP_LDO_SRILow    LDO_PLL_SRILow  : 3;       /*!< [10..8] LDO Power adjustment                     */
      __IOM MDR_BKP_LDO_Trim      LDO_PLL_Trim    : 3;       /*!< [13..11] LDO voltage tuning                      */
      __IOM MDR_OnOff             LDO_PLL_En      : 1;       /*!< [14..14] LDO Enable                              */
      __IOM MDR_OnOff             LDO_PLL_RDY     : 1;       /*!< [15..15] LDO Ready                               */
      __IM  uint32_t              TrimR           : 9;       /*!< [24..16] Do not change                           */
      __IM  uint32_t                              : 3;
      __IM  uint32_t              Trim_Ref        : 3;       /*!< [30..28] Do not change                           */
      __IM  uint32_t                              : 1;
} MDR_BKP_REG62_Bits;

#define MDR_BKP_REG62_LDO_BUcc_SRILow_Pos (0UL)               /*!< MDR_BKP REG_62_TMR0: LDO_BUcc_SRILow (Bit 0)          */
#define MDR_BKP_REG62_LDO_BUcc_SRILow_Msk (0x7UL)             /*!< MDR_BKP REG_62_TMR0: LDO_BUcc_SRILow (Bitfield-Mask: 0x07) */
#define MDR_BKP_REG62_LDO_BUcc_Trim_Pos   (3UL)               /*!< MDR_BKP REG_62_TMR0: LDO_BUcc_Trim (Bit 3)            */
#define MDR_BKP_REG62_LDO_BUcc_Trim_Msk   (0x38UL)            /*!< MDR_BKP REG_62_TMR0: LDO_BUcc_Trim (Bitfield-Mask: 0x07) */
#define MDR_BKP_REG62_LDO_BUcc_En_Pos     (6UL)               /*!< MDR_BKP REG_62_TMR0: LDO_BUcc_En (Bit 6)              */
#define MDR_BKP_REG62_LDO_BUcc_En_Msk     (0x40UL)            /*!< MDR_BKP REG_62_TMR0: LDO_BUcc_En (Bitfield-Mask: 0x01) */
#define MDR_BKP_REG62_LDO_BUcc_RDY_Pos    (7UL)               /*!< MDR_BKP REG_62_TMR0: LDO_BUcc_RDY (Bit 7)             */
#define MDR_BKP_REG62_LDO_BUcc_RDY_Msk    (0x80UL)            /*!< MDR_BKP REG_62_TMR0: LDO_BUcc_RDY (Bitfield-Mask: 0x01) */
#define MDR_BKP_REG62_LDO_PLL_SRILow_Pos  (8UL)               /*!< MDR_BKP REG_62_TMR0: LDO_PLL_SRILow (Bit 8)           */
#define MDR_BKP_REG62_LDO_PLL_SRILow_Msk  (0x700UL)           /*!< MDR_BKP REG_62_TMR0: LDO_PLL_SRILow (Bitfield-Mask: 0x07) */
#define MDR_BKP_REG62_LDO_PLL_Trim_Pos    (11UL)              /*!< MDR_BKP REG_62_TMR0: LDO_PLL_Trim (Bit 11)            */
#define MDR_BKP_REG62_LDO_PLL_Trim_Msk    (0x3800UL)          /*!< MDR_BKP REG_62_TMR0: LDO_PLL_Trim (Bitfield-Mask: 0x07) */
#define MDR_BKP_REG62_LDO_PLL_En_Pos      (14UL)              /*!< MDR_BKP REG_62_TMR0: LDO_PLL_En (Bit 14)              */
#define MDR_BKP_REG62_LDO_PLL_En_Msk      (0x4000UL)          /*!< MDR_BKP REG_62_TMR0: LDO_PLL_En (Bitfield-Mask: 0x01) */
#define MDR_BKP_REG62_LDO_PLL_RDY_Pos     (15UL)              /*!< MDR_BKP REG_62_TMR0: LDO_PLL_RDY (Bit 15)             */
#define MDR_BKP_REG62_LDO_PLL_RDY_Msk     (0x8000UL)          /*!< MDR_BKP REG_62_TMR0: LDO_PLL_RDY (Bitfield-Mask: 0x01) */
#define MDR_BKP_REG62_TrimR_Pos           (16UL)              /*!< MDR_BKP REG_62_TMR0: TrimR (Bit 16)                   */
#define MDR_BKP_REG62_TrimR_Msk           (0x1ff0000UL)       /*!< MDR_BKP REG_62_TMR0: TrimR (Bitfield-Mask: 0x1ff)     */
#define MDR_BKP_REG62_Trim_Ref_Pos        (28UL)              /*!< MDR_BKP REG_62_TMR0: Trim_Ref (Bit 28)                */
#define MDR_BKP_REG62_Trim_Ref_Msk        (0x70000000UL)      /*!< MDR_BKP REG_62_TMR0: Trim_Ref (Bitfield-Mask: 0x07)   */


//-------   BKP_Lock Instance  ----------
typedef struct {                                /*!< (@ 0x40001000) MDR_BKP Structure                                          */
  union {
    __IOM uint32_t      REG_60;                 /*!< (@ 0x00000100) REG60 Control register                                     */
    MDR_BKP_REG60_Bits  REG_60_b;
  } ;  
  union {
    __IOM uint32_t      REG_61;                 /*!< (@ 0x00000104) REG61 Control register                                     */
    MDR_BKP_REG61_Bits  REG_61_b;
  } ;  
  union {
    __IOM uint32_t      REG_62;                 /*!< (@ 0x00000108) REG62 Control register                                     */
    MDR_BKP_REG62_Bits  REG_62_b;
  } ;  
  union {
    __IOM uint32_t      REG_63;                 /*!< (@ 0x0000010C) REG63 Control register                                     */
    MDR_BKP_REG63_Bits  REG_63_b;
  } ;
}  MDR_BKP_REG6X;


/* =========================================================================================================================== */
/* ================                                          MDR_BKP                                          ================ */
/* =========================================================================================================================== */
typedef struct {                                /*!< (@ 0x40001000) MDR_BKP Structure                                          */
  __IOM uint32_t  REG[MDR_BKP_REG_XX_COUNT];    /*!< (@ 0x00000000) User backup registers                                      */
  __IOM uint32_t  KEY;                          /*!< (@ 0x000000F0) Unlock BKP and RTC Registers                               */
  __IM  uint32_t  RESERVED[3];
  
  MDR_BKP_REG6X   TMR0;
  MDR_BKP_REG6X   TMR1;
  MDR_BKP_REG6X   TMR2;
  
  MDR_RTC_Type    RTC0;
  __IM  uint32_t  RESERVED1[3];
  MDR_RTC_Type    RTC1;
  __IM  uint32_t  RESERVED2[3];  
  MDR_RTC_Type    RTC2;
} MDR_BKP_Type;                                 /*!< Size = 388 (0x184)                                                        */


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

#endif  //_MDR_BKP_VK014_DEFS_H

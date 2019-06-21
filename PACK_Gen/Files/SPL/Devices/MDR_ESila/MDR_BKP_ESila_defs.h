#ifndef _MDR_BKP_ESila_DEFS_H
#define _MDR_BKP_ESila_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif


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

#define MDR_BKP_REG_XX_COUNT  60

//-------   Reg_60  ----------
typedef struct {
      __IOM uint32_t    MODE            : 7;        /*!< [6..0] Boot Mode                                                          */
      __IOM MDR_OnOff   FPOR            : 1;        /*!< [7..7] Bootloader completed                                               */
      __IOM MDR_OnOff   JTAG_Enable     : 1;        /*!< [8..8] Disable JTAG                                                       */
      __IOM MDR_OnOff   LockStep_On     : 1;        /*!< [9..9] Enable LockStep CPUs Mode                                          */
      __IOM MDR_OnOff   S_SYSRSTn       : 1;        /*!< [10..10] Reset by software                                                */
      __IOM MDR_OnOff   S_RSTn1         : 1;        /*!< [11..11] Reset by RSTn1 signal                                            */
      __IOM MDR_OnOff   S_RSTn0         : 1;        /*!< [12..12] Reset by RSTn0 signal                                            */
      __IOM MDR_OnOff   S_FT_Reset      : 1;        /*!< [13..13] Reset from FT_CNTR                                               */
      __IOM MDR_OnOff   S_WDT_Reset     : 1;        /*!< [14..14] Reset from WDT                                                   */
      __IM  uint32_t                    : 10;
      __IOM MDR_OnOff   ERR_REG60x      : 1;        /*!< [25..25] Fault in REG_60x                                                 */
      __IOM MDR_OnOff   ERR_REG61x_62x  : 1;        /*!< [26..26] Fault in REG_61x or REG_62x                                      */
      __IOM MDR_OnOff   ERR_REG63x      : 1;        /*!< [27..27] Fault in REG_63x                                                 */
      __IM  uint32_t                    : 2;
      __IOM MDR_OnOff   CLR_ERR         : 1;        /*!< [30..30] Clear Errors of REG_60x - 63x                                    */
      __IOM MDR_OnOff   ERR_IRQ_EN      : 1;        /*!< [31..31] Enable BKP_IRQn on Errors                                        */
} MDR_BKP_REG60_Bits;

#define MDR_BKP_REG60_MODE_Pos        (0UL)                   /*!< MDR_BKP REG_60_TMR0: MODE (Bit 0)                     */
#define MDR_BKP_REG60_MODE_Msk        (0x7fUL)                /*!< MDR_BKP REG_60_TMR0: MODE (Bitfield-Mask: 0x7f)       */
#define MDR_BKP_REG60_FPOR_Pos        (7UL)                   /*!< MDR_BKP REG_60_TMR0: FPOR (Bit 7)                     */
#define MDR_BKP_REG60_FPOR_Msk        (0x80UL)                /*!< MDR_BKP REG_60_TMR0: FPOR (Bitfield-Mask: 0x01)       */
#define MDR_BKP_REG60_JTAG_Enable_Pos (8UL)                   /*!< MDR_BKP REG_60_TMR0: JTAG_Enable (Bit 8)              */
#define MDR_BKP_REG60_JTAG_Enable_Msk (0x100UL)               /*!< MDR_BKP REG_60_TMR0: JTAG_Enable (Bitfield-Mask: 0x01) */
#define MDR_BKP_REG60_LockStep_On_Pos (9UL)                   /*!< MDR_BKP REG_60_TMR0: LockStep_On (Bit 9)              */
#define MDR_BKP_REG60_LockStep_On_Msk (0x200UL)               /*!< MDR_BKP REG_60_TMR0: LockStep_On (Bitfield-Mask: 0x01) */
#define MDR_BKP_REG60_S_SYSRSTn_Pos   (10UL)                  /*!< MDR_BKP REG_60_TMR0: S_SYSRSTn (Bit 10)               */
#define MDR_BKP_REG60_S_SYSRSTn_Msk   (0x400UL)               /*!< MDR_BKP REG_60_TMR0: S_SYSRSTn (Bitfield-Mask: 0x01)  */
#define MDR_BKP_REG60_S_RSTn1_Pos     (11UL)                  /*!< MDR_BKP REG_60_TMR0: S_RSTn1 (Bit 11)                 */
#define MDR_BKP_REG60_S_RSTn1_Msk     (0x800UL)               /*!< MDR_BKP REG_60_TMR0: S_RSTn1 (Bitfield-Mask: 0x01)    */
#define MDR_BKP_REG60_S_RSTn0_Pos     (12UL)                  /*!< MDR_BKP REG_60_TMR0: S_RSTn0 (Bit 12)                 */
#define MDR_BKP_REG60_S_RSTn0_Msk     (0x1000UL)              /*!< MDR_BKP REG_60_TMR0: S_RSTn0 (Bitfield-Mask: 0x01)    */
#define MDR_BKP_REG60_S_FT_Reset_Pos  (13UL)                  /*!< MDR_BKP REG_60_TMR0: S_FT_Reset (Bit 13)              */
#define MDR_BKP_REG60_S_FT_Reset_Msk  (0x2000UL)              /*!< MDR_BKP REG_60_TMR0: S_FT_Reset (Bitfield-Mask: 0x01) */
#define MDR_BKP_REG60_S_WDT_Reset_Pos (14UL)                  /*!< MDR_BKP REG_60_TMR0: S_WDT_Reset (Bit 14)             */
#define MDR_BKP_REG60_S_WDT_Reset_Msk (0x4000UL)              /*!< MDR_BKP REG_60_TMR0: S_WDT_Reset (Bitfield-Mask: 0x01) */
#define MDR_BKP_REG60_ERR_REG60x_Pos  (25UL)                  /*!< MDR_BKP REG_60_TMR0: ERR_REG60x (Bit 25)              */
#define MDR_BKP_REG60_ERR_REG60x_Msk  (0x2000000UL)           /*!< MDR_BKP REG_60_TMR0: ERR_REG60x (Bitfield-Mask: 0x01) */
#define MDR_BKP_REG60_ERR_REG61x_62x_Pos (26UL)               /*!< MDR_BKP REG_60_TMR0: ERR_REG61x_62x (Bit 26)          */
#define MDR_BKP_REG60_ERR_REG61x_62x_Msk (0x4000000UL)        /*!< MDR_BKP REG_60_TMR0: ERR_REG61x_62x (Bitfield-Mask: 0x01) */
#define MDR_BKP_REG60_ERR_REG63x_Pos  (27UL)                  /*!< MDR_BKP REG_60_TMR0: ERR_REG63x (Bit 27)              */
#define MDR_BKP_REG60_ERR_REG63x_Msk  (0x8000000UL)           /*!< MDR_BKP REG_60_TMR0: ERR_REG63x (Bitfield-Mask: 0x01) */
#define MDR_BKP_REG60_CLR_ERR_Pos     (30UL)                  /*!< MDR_BKP REG_60_TMR0: CLR_ERR (Bit 30)                 */
#define MDR_BKP_REG60_CLR_ERR_Msk     (0x40000000UL)          /*!< MDR_BKP REG_60_TMR0: CLR_ERR (Bitfield-Mask: 0x01)    */
#define MDR_BKP_REG60_ERR_IRQ_EN_Pos  (31UL)                  /*!< MDR_BKP REG_60_TMR0: ERR_IRQ_EN (Bit 31)              */
#define MDR_BKP_REG60_ERR_IRQ_EN_Msk  (0x80000000UL)          /*!< MDR_BKP REG_60_TMR0: ERR_IRQ_EN (Bitfield-Mask: 0x01) */


//-------   Reg_61  ----------

//  Поля будут уточняться!
typedef enum {                     /*!< MDR_BKP_REG_61_TMR0_bg_trimVdd1p6                                         */
  MDR_BKP_LDO_Trim_add_0v1  = 0,   /*!< add_0v1 : LD0 extra voltage +0.1V                                         */
  MDR_BKP_LDO_Trim_add_0v06 = 1,   /*!< add_0v06 : LD0 extra voltage +0.06V                                      */
  MDR_BKP_LDO_Trim_add_0v04 = 2,   /*!< add_0v04 : LD0 extra voltage +0.04V                                      */
  MDR_BKP_LDO_Trim_add_0v01 = 3,   /*!< add_0v01 : LD0 extra voltage +0.01V                                      */
  MDR_BKP_LDO_Trim_sub_0v01 = 4,   /*!< sub_0v01 : LD0 extra voltage -0.01V                                      */
  MDR_BKP_LDO_Trim_sub_0v04 = 5,   /*!< sub_0v04 : LD0 extra voltage -0.04V                                      */
  MDR_BKP_LDO_Trim_sub_0v06 = 6,   /*!< sub_0v06 : LD0 extra voltage -0.06V                                      */
  MDR_BKP_LDO_Trim_sub_0v1  = 7,   /*!< sub_0v1 : LD0 extra voltage -0.1V                                         */
} MDR_BKP_LDO_Trim;

//  Поля будут уточняться!
typedef enum {                     /*!< MDR_BKP_REG_61_TMR0_bg_trimVdd1p6                                         */
  MDR_BKP_DCDC_Trim_unk0  = 0,
  MDR_BKP_DCDC_Trim_unk1  = 1,
  MDR_BKP_DCDC_Trim_unk2  = 2,
  MDR_BKP_DCDC_Trim_unk3  = 3,
  MDR_BKP_DCDC_Trim_unk4  = 4,
  MDR_BKP_DCDC_Trim_unk5  = 5,
  MDR_BKP_DCDC_Trim_unk6  = 6,
  MDR_BKP_DCDC_Trim_unk7  = 7,
  MDR_BKP_DCDC_Trim_unk8  = 8,
  MDR_BKP_DCDC_Trim_unk9  = 9,
  MDR_BKP_DCDC_Trim_unk10  = 10,
  MDR_BKP_DCDC_Trim_unk11  = 11,
  MDR_BKP_DCDC_Trim_unk12  = 12,
  MDR_BKP_DCDC_Trim_unk13  = 13,
  MDR_BKP_DCDC_Trim_unk14  = 14,  
  MDR_BKP_DCDC_Trim_unk15  = 15,
} MDR_BKP_DCDC_Trim;

//  Поля будут уточняться!
typedef enum {                     /*!< MDR_BKP_REG_61_TMR0_HLDO_SRILow                                           */
  MDR_BKP_LDO_SRILow_lt30MHz  = 0,  /*!< ge10MHz : Extra_I about ~400uA                                            */
  MDR_BKP_LDO_SRILow_lt50MHz  = 1,  /*!< ge30MHz : Extra_I about ~450uA                                            */
  MDR_BKP_LDO_SRILow_lt100MHz = 2,  /*!< ge50MHz : Extra_I about ~550uA                                            */
  MDR_BKP_LDO_SRILow_ge100MHz = 3,  /*!< ge100MHz : Extra_I about ~650uA                                           */
  MDR_BKP_LDO_SRILow_lt10MHz  = 4,  /*!< ge1MHz : Extra_I about ~300uA                                             */
  MDR_BKP_LDO_SRILow_lt1MHz   = 5,  /*!< ge500KHz : Extra_I about ~200uA                                           */
  MDR_BKP_LDO_SRILow_lt500KHz = 6,  /*!< ge100KHz : Extra_I about ~100uA                                           */
  MDR_BKP_LDO_SRILow_lt100KHz = 7,  /*!< ge10KHz : Extra_I about ~50uA                                             */
} MDR_BKP_LDO_SRILow;

typedef struct {
      __IOM MDR_OnOff           POR3p3_Dis    : 1;          /*!< [0..0] Reset by Ucc > Upor                        */
      __IOM MDR_OnOff           ORV3p3_Dis    : 1;          /*!< [1..1] Reset by Ucc > Uover                       */
      __IOM MDR_BKP_LDO_Trim    BG_TrimVdd1p6 : 3;          /*!< [4..2] DUcc 1.6V trim                             */
      __IOM MDR_BKP_LDO_Trim    BG_TrimVdd1p2 : 3;          /*!< [7..5] DUcc 1.6V trim                             */
      __IOM MDR_OnOff           DCDC_En       : 1;          /*!< [8..8] Enable DCDC 1.6V                           */
      __IOM MDR_BKP_DCDC_Trim   DCDC_Trim     : 4;          /*!< [12..9] DCDC 1.6V trim                            */
      __IOM MDR_BKP_LDO_SRILow  HLDO_SRILow   : 3;          /*!< [15..13] HLDO Power adjustment                    */
      __IOM MDR_OnOff           HLDO_Dis      : 1;          /*!< [16..16] HLDO Disable                             */
      __IOM MDR_OnOff           LLDO_Dis      : 1;          /*!< [17..17] LLDO Disable                             */
      __IOM MDR_OnOff           Temp_En       : 1;          /*!< [18..18] Thermo protection EN                     */
      __IOM MDR_OnOff           CProt_En      : 1;          /*!< [19..19] Current protection EN                    */
      __IM  uint32_t                          : 1;
      __IOM MDR_OnOff           P3p3_RDY      : 1;          /*!< [21..21] DUcc 3.3V ready                          */
      __IOM MDR_OnOff           S_nPOR3p3     : 1;          /*!< [22..22] Reset by DUcc_3.3V                       */
      __IOM MDR_OnOff           S_nPOR1p6     : 1;          /*!< [23..23] Reset by DUcc_1.6V                       */
      __IOM MDR_OnOff           S_nPOR1p2     : 1;          /*!< [24..24] Reset by DUcc_1.2V                       */
      __IOM MDR_OnOff           S_nOVRST3p3   : 1;          /*!< [25..25] Reset by Ucc > Uover                     */
      __IOM MDR_OnOff           LLDO_RDY      : 1;          /*!< [26..26] DUcc 1.2V ready                          */
      __IOM MDR_OnOff           DCDC_RDY      : 1;          /*!< [27..27] DCDC 1.6V ready                          */
      __IOM MDR_OnOff           HLDO_RDY      : 1;          /*!< [28..28] DUcc 1.6V ready                          */
      __IOM MDR_OnOff           CProt_Event   : 1;          /*!< [29..29] CProt_cnt > CProt_lim                    */
      __IOM MDR_OnOff           TProt_Event   : 1;          /*!< [30..30] Thermo is over                           */
      __IOM MDR_OnOff           STANDBY       : 1;          /*!< [31..31] Go Standby mode                          */
} MDR_BKP_REG61_Bits;

#define MDR_BKP_REG61_POR3p3_Dis_Pos    (0UL)               /*!< MDR_BKP REG_61_TMR0: POR3p3_Dis (Bit 0)               */
#define MDR_BKP_REG61_POR3p3_Dis_Msk    (0x1UL)             /*!< MDR_BKP REG_61_TMR0: POR3p3_Dis (Bitfield-Mask: 0x01) */
#define MDR_BKP_REG61_ORV3p3_Dis_Pos    (1UL)               /*!< MDR_BKP REG_61_TMR0: ORV3p3_Dis (Bit 1)               */
#define MDR_BKP_REG61_ORV3p3_Dis_Msk    (0x2UL)             /*!< MDR_BKP REG_61_TMR0: ORV3p3_Dis (Bitfield-Mask: 0x01) */
#define MDR_BKP_REG61_BG_TrimVdd1p6_Pos (2UL)               /*!< MDR_BKP REG_61_TMR0: bg_trimVdd1p6 (Bit 2)            */
#define MDR_BKP_REG61_BG_TrimVdd1p6_Msk (0x1cUL)            /*!< MDR_BKP REG_61_TMR0: bg_trimVdd1p6 (Bitfield-Mask: 0x07) */
#define MDR_BKP_REG61_BG_TrimVdd1p2_Pos (5UL)               /*!< MDR_BKP REG_61_TMR0: bg_trimVdd1p2 (Bit 5)            */
#define MDR_BKP_REG61_BG_TrimVdd1p2_Msk (0xe0UL)            /*!< MDR_BKP REG_61_TMR0: bg_trimVdd1p2 (Bitfield-Mask: 0x07) */
#define MDR_BKP_REG61_DCDC_En_Pos       (8UL)               /*!< MDR_BKP REG_61_TMR0: DCDC_En (Bit 8)                  */
#define MDR_BKP_REG61_DCDC_En_Msk       (0x100UL)           /*!< MDR_BKP REG_61_TMR0: DCDC_En (Bitfield-Mask: 0x01)    */
#define MDR_BKP_REG61_DCDC_Trim_Pos     (9UL)               /*!< MDR_BKP REG_61_TMR0: DCDC_Trim (Bit 9)                */
#define MDR_BKP_REG61_DCDC_Trim_Msk     (0x1e00UL)          /*!< MDR_BKP REG_61_TMR0: DCDC_Trim (Bitfield-Mask: 0x0f)  */
#define MDR_BKP_REG61_HLDO_SRILow_Pos   (13UL)              /*!< MDR_BKP REG_61_TMR0: HLDO_SRILow (Bit 13)             */
#define MDR_BKP_REG61_HLDO_SRILow_Msk   (0xe000UL)          /*!< MDR_BKP REG_61_TMR0: HLDO_SRILow (Bitfield-Mask: 0x07) */
#define MDR_BKP_REG61_HLDO_Dis_Pos      (16UL)              /*!< MDR_BKP REG_61_TMR0: HLDO_Dis (Bit 16)                */
#define MDR_BKP_REG61_HLDO_Dis_Msk      (0x10000UL)         /*!< MDR_BKP REG_61_TMR0: HLDO_Dis (Bitfield-Mask: 0x01)   */
#define MDR_BKP_REG61_LLDO_Dis_Pos      (17UL)              /*!< MDR_BKP REG_61_TMR0: LLDO_Dis (Bit 17)                */
#define MDR_BKP_REG61_LLDO_Dis_Msk      (0x20000UL)         /*!< MDR_BKP REG_61_TMR0: LLDO_Dis (Bitfield-Mask: 0x01)   */
#define MDR_BKP_REG61_Temp_En_Pos       (18UL)              /*!< MDR_BKP REG_61_TMR0: Temp_En (Bit 18)                 */
#define MDR_BKP_REG61_Temp_En_Msk       (0x40000UL)         /*!< MDR_BKP REG_61_TMR0: Temp_En (Bitfield-Mask: 0x01)    */
#define MDR_BKP_REG61_CProt_En_Pos      (19UL)              /*!< MDR_BKP REG_61_TMR0: CProt_En (Bit 19)                */
#define MDR_BKP_REG61_CProt_En_Msk      (0x80000UL)         /*!< MDR_BKP REG_61_TMR0: CProt_En (Bitfield-Mask: 0x01)   */
#define MDR_BKP_REG61_P3p3_RDY_Pos      (21UL)              /*!< MDR_BKP REG_61_TMR0: P3p3_RDY (Bit 21)                */
#define MDR_BKP_REG61_P3p3_RDY_Msk      (0x200000UL)        /*!< MDR_BKP REG_61_TMR0: P3p3_RDY (Bitfield-Mask: 0x01)   */
#define MDR_BKP_REG61_S_nPOR3p3_Pos     (22UL)              /*!< MDR_BKP REG_61_TMR0: S_nPOR3p3 (Bit 22)               */
#define MDR_BKP_REG61_S_nPOR3p3_Msk     (0x400000UL)        /*!< MDR_BKP REG_61_TMR0: S_nPOR3p3 (Bitfield-Mask: 0x01)  */
#define MDR_BKP_REG61_S_nPOR1p6_Pos     (23UL)              /*!< MDR_BKP REG_61_TMR0: S_nPOR1p6 (Bit 23)               */
#define MDR_BKP_REG61_S_nPOR1p6_Msk     (0x800000UL)        /*!< MDR_BKP REG_61_TMR0: S_nPOR1p6 (Bitfield-Mask: 0x01)  */
#define MDR_BKP_REG61_S_nPOR1p2_Pos     (24UL)              /*!< MDR_BKP REG_61_TMR0: S_nPOR1p2 (Bit 24)               */
#define MDR_BKP_REG61_S_nPOR1p2_Msk     (0x1000000UL)       /*!< MDR_BKP REG_61_TMR0: S_nPOR1p2 (Bitfield-Mask: 0x01)  */
#define MDR_BKP_REG61_S_nOVRST3p3_Pos   (25UL)              /*!< MDR_BKP REG_61_TMR0: S_nOVRST3p3 (Bit 25)             */
#define MDR_BKP_REG61_S_nOVRST3p3_Msk   (0x2000000UL)       /*!< MDR_BKP REG_61_TMR0: S_nOVRST3p3 (Bitfield-Mask: 0x01) */
#define MDR_BKP_REG61_LLDO_RDY_Pos      (26UL)              /*!< MDR_BKP REG_61_TMR0: LLDO_RDY (Bit 26)                */
#define MDR_BKP_REG61_LLDO_RDY_Msk      (0x4000000UL)       /*!< MDR_BKP REG_61_TMR0: LLDO_RDY (Bitfield-Mask: 0x01)   */
#define MDR_BKP_REG61_DCDC_RDY_Pos      (27UL)              /*!< MDR_BKP REG_61_TMR0: DCDC_RDY (Bit 27)                */
#define MDR_BKP_REG61_DCDC_RDY_Msk      (0x8000000UL)       /*!< MDR_BKP REG_61_TMR0: DCDC_RDY (Bitfield-Mask: 0x01)   */
#define MDR_BKP_REG61_HLDO_RDY_Pos      (28UL)              /*!< MDR_BKP REG_61_TMR0: HLDO_RDY (Bit 28)                */
#define MDR_BKP_REG61_HLDO_RDY_Msk      (0x10000000UL)      /*!< MDR_BKP REG_61_TMR0: HLDO_RDY (Bitfield-Mask: 0x01)   */
#define MDR_BKP_REG61_CProt_Event_Pos   (29UL)              /*!< MDR_BKP REG_61_TMR0: CProt_Event (Bit 29)             */
#define MDR_BKP_REG61_CProt_Event_Msk   (0x20000000UL)      /*!< MDR_BKP REG_61_TMR0: CProt_Event (Bitfield-Mask: 0x01) */
#define MDR_BKP_REG61_TProt_Event_Pos   (30UL)              /*!< MDR_BKP REG_61_TMR0: TProt_Event (Bit 30)             */
#define MDR_BKP_REG61_TProt_Event_Msk   (0x40000000UL)      /*!< MDR_BKP REG_61_TMR0: TProt_Event (Bitfield-Mask: 0x01) */
#define MDR_BKP_REG61_STANDBY_Pos       (31UL)              /*!< MDR_BKP REG_61_TMR0: STANDBY (Bit 31)                 */
#define MDR_BKP_REG61_STANDBY_Msk       (0x80000000UL)      /*!< MDR_BKP REG_61_TMR0: STANDBY (Bitfield-Mask: 0x01)    */


//-------   Reg_62  ----------    
typedef enum {                        /*!< MDR_BKP_REG_62_TMR0_PWRM_Vdd_lvl                                          */
  MDR_BKP_REG62_PWRM_lvl_lvl0 = 0,    /*!< lvl0 : unknown level yet                                                  */
  MDR_BKP_REG62_PWRM_lvl_lvl1 = 1,    /*!< lvl1 : unknown level yet                                                  */
  MDR_BKP_REG62_PWRM_lvl_lvl2 = 2,    /*!< lvl2 : unknown level yet                                                  */
  MDR_BKP_REG62_PWRM_lvl_lvl3 = 3,    /*!< lvl3 : unknown level yet                                                  */
  MDR_BKP_REG62_PWRM_lvl_lvl4 = 4,    /*!< lvl4 : unknown level yet                                                  */
  MDR_BKP_REG62_PWRM_lvl_lvl5 = 5,    /*!< lvl5 : unknown level yet                                                  */
  MDR_BKP_REG62_PWRM_lvl_lvl6 = 6,    /*!< lvl6 : unknown level yet                                                  */
  MDR_BKP_REG62_PWRM_lvl_lvl7 = 7,    /*!< lvl7 : unknown level yet                                                  */
  MDR_BKP_REG62_PWRM_lvl_lvl8 = 8,    /*!< lvl8 : unknown level yet                                                  */
  MDR_BKP_REG62_PWRM_lvl_lvl9 = 9,    /*!< lvl9 : unknown level yet                                                  */
  MDR_BKP_REG62_PWRM_lvl_lvl10 = 10,  /*!< lvl10 : unknown level yet                                                 */
  MDR_BKP_REG62_PWRM_lvl_lvl11 = 11,  /*!< lvl11 : unknown level yet                                                 */
  MDR_BKP_REG62_PWRM_lvl_lvl12 = 12,  /*!< lvl12 : unknown level yet                                                 */
  MDR_BKP_REG62_PWRM_lvl_lvl13 = 13,  /*!< lvl13 : unknown level yet                                                 */
  MDR_BKP_REG62_PWRM_lvl_lvl14 = 14,  /*!< lvl14 : unknown level yet                                                 */
  MDR_BKP_REG62_PWRM_lvl_lvl15 = 15,  /*!< lvl15 : unknown level yet                                                 */
  MDR_BKP_REG62_PWRM_lvl_lvl16 = 16,  /*!< lvl16 : unknown level yet                                                 */
  MDR_BKP_REG62_PWRM_lvl_lvl17 = 17,  /*!< lvl17 : unknown level yet                                                 */
  MDR_BKP_REG62_PWRM_lvl_lvl18 = 18,  /*!< lvl18 : unknown level yet                                                 */
  MDR_BKP_REG62_PWRM_lvl_lvl19 = 19,  /*!< lvl19 : unknown level yet                                                 */
  MDR_BKP_REG62_PWRM_lvl_lvl20 = 20,  /*!< lvl20 : unknown level yet                                                 */
  MDR_BKP_REG62_PWRM_lvl_lvl21 = 21,  /*!< lvl21 : unknown level yet                                                 */
  MDR_BKP_REG62_PWRM_lvl_lvl22 = 22,  /*!< lvl22 : unknown level yet                                                 */
  MDR_BKP_REG62_PWRM_lvl_lvl23 = 23,  /*!< lvl23 : unknown level yet                                                 */
  MDR_BKP_REG62_PWRM_lvl_lvl24 = 24,  /*!< lvl24 : unknown level yet                                                 */
  MDR_BKP_REG62_PWRM_lvl_lvl25 = 25,  /*!< lvl25 : unknown level yet                                                 */
  MDR_BKP_REG62_PWRM_lvl_lvl26 = 26,  /*!< lvl26 : unknown level yet                                                 */
  MDR_BKP_REG62_PWRM_lvl_lvl27 = 27,  /*!< lvl27 : unknown level yet                                                 */
  MDR_BKP_REG62_PWRM_lvl_lvl28 = 28,  /*!< lvl28 : unknown level yet                                                 */
  MDR_BKP_REG62_PWRM_lvl_lvl29 = 29,  /*!< lvl29 : unknown level yet                                                 */
  MDR_BKP_REG62_PWRM_lvl_lvl30 = 30,  /*!< lvl30 : unknown level yet                                                 */
  MDR_BKP_REG62_PWRM_lvl_lvl31 = 31  /*!< lvl31 : unknown level yet                                                 */
} MDR_BKP_REG62_PWRM_Level;


//  ToDo: С MDR_BKP_REG62_PWRM_Level адрес регистра смещается!?

typedef __PACKED_STRUCT {
      __IOM MDR_OnOff                 BLDO_Dis        : 1;      /*!< [0..0] Disable LDO_Bat                         */
      __IOM MDR_BKP_LDO_Trim          BLDO_Trim       : 3;      /*!< [3..1] LDO_Bat Trim                            */
      __IOM MDR_BKP_LDO_SRILow        BLDO_SRILow     : 3;      /*!< [6..4] LDO_Bat Power adjustment                */
      __IOM MDR_OnOff                 BLDO_RDY        : 1;      /*!< [7..7] BLDO Ready                              */
  
      //__IOM MDR_BKP_REG62_PWRM_Level  PWRM_Vdd_lvl    : 5;      /*!< [12..8] DCDC_3.3V level                        */
      __IOM uint32_t                  PWRM_Vdd_lvl    : 5;      /*!< [12..8] DCDC_3.3V level                        */  
  
      __IOM MDR_OnOff                 PWRM_Vdd_En     : 1;      /*!< [13..13] DCDC_3.3V monitor enable              */
  
      //__IOM MDR_BKP_REG62_PWRM_Level  PWRM_VddB_lvl   : 5;      /*!< [18..14] Vdd_BKP 3.3V level                    */
      //__IOM MDR_BKP_REG62_PWRM_Level  PWRM_VddIO_lvl  : 5;      /*!< [23..19] Vdd_BKP 3.3V level                    */
      __IOM uint32_t                  PWRM_VddB_lvl   : 5;      /*!< [18..14] Vdd_BKP 3.3V level                    */
      __IOM uint32_t                  PWRM_VddIO_lvl  : 5;      /*!< [23..19] Vdd_BKP 3.3V level                    */
  
      __IOM MDR_OnOff                 PWRM_VddB_En    : 1;      /*!< [24..24] Vdd_BKP monitor enable                */
      __IOM MDR_OnOff                 PWRM_VddIO_En   : 1;      /*!< [25..25] Vdd_IO monitor enable                 */
      __IOM MDR_OnOff                 PWRM_Vdd_Event  : 1;      /*!< [26..26] Vdd Event                             */
      __IOM MDR_OnOff                 PWRM_VddB_Event : 1;      /*!< [27..27] Vdd BKP Event                         */
      __IOM MDR_OnOff                 PWRM_VddIO_Event: 1;      /*!< [28..28] Vdd IO Event                          */
      __IOM MDR_OnOff                 SEL_NSW    : 1;           /*!< [29..29] Select NSW                            */
      __IOM MDR_OnOff                 SEL_SW     : 1;           /*!< [30..30] Select SW                             */
      __IOM MDR_OnOff                 PMU_BG_Dis : 1;           /*!< [31..31] Disable PMU                           */
} MDR_BKP_REG62_Bits;

#define MDR_BKP_REG62_BLDO_Dis_Pos          (0UL)              /*!< MDR_BKP REG_62_TMR0: BLDO_Dis (Bit 0)                 */
#define MDR_BKP_REG62_BLDO_Dis_Msk          (0x1UL)            /*!< MDR_BKP REG_62_TMR0: BLDO_Dis (Bitfield-Mask: 0x01)   */
#define MDR_BKP_REG62_BLDO_Trim_Pos         (1UL)              /*!< MDR_BKP REG_62_TMR0: BLDO_Trim (Bit 1)                */
#define MDR_BKP_REG62_BLDO_Trim_Msk         (0xeUL)            /*!< MDR_BKP REG_62_TMR0: BLDO_Trim (Bitfield-Mask: 0x07)  */
#define MDR_BKP_REG62_BLDO_SRILow_Pos       (4UL)              /*!< MDR_BKP REG_62_TMR0: BLDO_SRILow (Bit 4)              */
#define MDR_BKP_REG62_BLDO_SRILow_Msk       (0x70UL)           /*!< MDR_BKP REG_62_TMR0: BLDO_SRILow (Bitfield-Mask: 0x07) */
#define MDR_BKP_REG62_BLDO_RDY_Pos          (7UL)              /*!< MDR_BKP REG_62_TMR0: BLDO_RDY (Bit 7)                 */
#define MDR_BKP_REG62_BLDO_RDY_Msk          (0x80UL)           /*!< MDR_BKP REG_62_TMR0: BLDO_RDY (Bitfield-Mask: 0x01)   */
#define MDR_BKP_REG62_PWRM_Vdd_lvl_Pos      (8UL)              /*!< MDR_BKP REG_62_TMR0: PWRM_Vdd_lvl (Bit 8)             */
#define MDR_BKP_REG62_PWRM_Vdd_lvl_Msk      (0x1f00UL)         /*!< MDR_BKP REG_62_TMR0: PWRM_Vdd_lvl (Bitfield-Mask: 0x1f) */
#define MDR_BKP_REG62_PWRM_Vdd_En_Pos       (13UL)             /*!< MDR_BKP REG_62_TMR0: PWRM_Vdd_En (Bit 13)             */
#define MDR_BKP_REG62_PWRM_Vdd_En_Msk       (0x2000UL)         /*!< MDR_BKP REG_62_TMR0: PWRM_Vdd_En (Bitfield-Mask: 0x01) */
#define MDR_BKP_REG62_PWRM_VddB_lvl_Pos     (14UL)             /*!< MDR_BKP REG_62_TMR0: PWRM_VddB_lvl (Bit 14)           */
#define MDR_BKP_REG62_PWRM_VddB_lvl_Msk     (0x7c000UL)        /*!< MDR_BKP REG_62_TMR0: PWRM_VddB_lvl (Bitfield-Mask: 0x1f) */
#define MDR_BKP_REG62_PWRM_VddIO_lvl_Pos    (19UL)             /*!< MDR_BKP REG_62_TMR0: PWRM_VddIO_lvl (Bit 19)          */
#define MDR_BKP_REG62_PWRM_VddIO_lvl_Msk    (0xf80000UL)       /*!< MDR_BKP REG_62_TMR0: PWRM_VddIO_lvl (Bitfield-Mask: 0x1f) */
#define MDR_BKP_REG62_PWRM_VddB_Enl_Pos     (24UL)             /*!< MDR_BKP REG_62_TMR0: PWRM_VddB_Enl (Bit 24)           */
#define MDR_BKP_REG62_PWRM_VddB_Enl_Msk     (0x1000000UL)      /*!< MDR_BKP REG_62_TMR0: PWRM_VddB_Enl (Bitfield-Mask: 0x01) */
#define MDR_BKP_REG62_PWRM_VddIO_Enl_Pos    (25UL)             /*!< MDR_BKP REG_62_TMR0: PWRM_VddIO_Enl (Bit 25)          */
#define MDR_BKP_REG62_PWRM_VddIO_Enl_Msk    (0x2000000UL)      /*!< MDR_BKP REG_62_TMR0: PWRM_VddIO_Enl (Bitfield-Mask: 0x01) */
#define MDR_BKP_REG62_PWRM_Vdd_Event_Pos    (26UL)             /*!< MDR_BKP REG_62_TMR0: PWRM_Vdd_Event (Bit 26)          */
#define MDR_BKP_REG62_PWRM_Vdd_Event_Msk    (0x4000000UL)      /*!< MDR_BKP REG_62_TMR0: PWRM_Vdd_Event (Bitfield-Mask: 0x01) */
#define MDR_BKP_REG62_PWRM_VddB_Event_Pos   (27UL)             /*!< MDR_BKP REG_62_TMR0: PWRM_VddB_Event (Bit 27)         */
#define MDR_BKP_REG62_PWRM_VddB_Event_Msk   (0x8000000UL)      /*!< MDR_BKP REG_62_TMR0: PWRM_VddB_Event (Bitfield-Mask: 0x01) */
#define MDR_BKP_REG62_PWRM_VddIO_Event_Pos  (28UL)             /*!< MDR_BKP REG_62_TMR0: PWRM_VddIO_Event (Bit 28)        */
#define MDR_BKP_REG62_PWRM_VddIO_Event_Msk  (0x10000000UL)     /*!< MDR_BKP REG_62_TMR0: PWRM_VddIO_Event (Bitfield-Mask: 0x01) */
#define MDR_BKP_REG62_SEL_NSW_Pos           (29UL)             /*!< MDR_BKP REG_62_TMR0: Sel_NSW (Bit 29)                 */
#define MDR_BKP_REG62_SEL_NSW_Msk           (0x20000000UL)     /*!< MDR_BKP REG_62_TMR0: Sel_NSW (Bitfield-Mask: 0x01)    */
#define MDR_BKP_REG62_SEL_SW_Pos            (30UL)             /*!< MDR_BKP REG_62_TMR0: Sel_SW (Bit 30)                  */
#define MDR_BKP_REG62_SEL_SW_Msk            (0x40000000UL)     /*!< MDR_BKP REG_62_TMR0: Sel_SW (Bitfield-Mask: 0x01)     */
#define MDR_BKP_REG62_PMU_BG_Dis_Pos        (31UL)             /*!< MDR_BKP REG_62_TMR0: PMU_BG_Dis (Bit 31)              */
#define MDR_BKP_REG62_PMU_BG_Dis_Msk        (0x80000000UL)     /*!< MDR_BKP REG_62_TMR0: PMU_BG_Dis (Bitfield-Mask: 0x01) */


//-------   Reg_63  ----------
typedef __PACKED_STRUCT {
      __IOM MDR_OnOff   LSE_RDY       : 1;            /*!< [0..0] LSE REady                            */
      __IOM MDR_OnOff   LSE_FilterO   : 1;            /*!< [1..1] LSE Input filter                     */
      __IOM MDR_OnOff   LSE_BYP       : 1;            /*!< [2..2] LSE Bypass                           */
      __IOM MDR_OnOff   LSE_On        : 1;            /*!< [3..3] LSE Enable                           */
      __IOM MDR_OnOff   HSE0_RDY      : 1;            /*!< [4..4] HSE0 Ready                           */
      __IOM MDR_OnOff   HSE0_FilterEn : 1;            /*!< [5..5] HSE0 Filter enable                   */
      __IOM MDR_OnOff   HSE0_BYP      : 1;            /*!< [6..6] HSE0 Bypass                          */
      __IOM MDR_OnOff   HSE0_On       : 1;            /*!< [7..7] HSE0 Enable                          */
      __IOM MDR_OnOff   HSE1_RDY      : 1;            /*!< [8..8] HSE1 Ready                           */
      __IOM MDR_OnOff   HSE1_FilterEn : 1;            /*!< [9..9] HSE1 Filter enable                   */
      __IOM MDR_OnOff   HSE1_BYP      : 1;            /*!< [10..10] HSE1 Bypass                        */
      __IOM MDR_OnOff   HSE1_On       : 1;            /*!< [11..11] HSE1 Enable                        */
      __IOM MDR_OnOff   LSI_Ready     : 1;            /*!< [12..12] LSI ready                          */
      __IOM MDR_OnOff   LSI_Dis       : 1;            /*!< [13..13] LSI Disable                        */
      __IOM uint32_t    LSI_Trim      : 7;            /*!< [20..14] LSI freq trim                      */
      __IOM MDR_OnOff   HSI_Ready     : 1;            /*!< [21..21] HSI ready                          */
      __IOM uint32_t    HSI_Trim      : 7;            /*!< [28..22] HSI freq trim                      */
      __IOM MDR_OnOff   HSI_Dis       : 1;            /*!< [29..29] HSI Disable                        */
      __IM  uint32_t                  : 1;
      __IOM MDR_OnOff   LSI_POR_Ready : 1;            /*!< [31..31] LSI POR ready                      */
} MDR_BKP_REG63_Bits;

#define MDR_BKP_REG63_LSI_Trim  uint8_t
#define MDR_BKP_REG63_HSI_Trim  uint8_t

#define MDR_BKP_REG63_LSI_Trim_Def      0x2F
#define MDR_BKP_REG63_HSI_Trim_Def      0x2F

#define MDR_BKP_REG63_LSE_FilterEn_Msk  0

#define MDR_BKP_REG63_LSE_RDY_Pos       (0UL)                 /*!< MDR_BKP REG_63_TMR0: LSE_RDY (Bit 0)                  */
#define MDR_BKP_REG63_LSE_RDY_Msk       (0x1UL)               /*!< MDR_BKP REG_63_TMR0: LSE_RDY (Bitfield-Mask: 0x01)    */
#define MDR_BKP_REG63_LSE_FilterOm_Pos  (1UL)                 /*!< MDR_BKP REG_63_TMR0: LSE_FilterOm (Bit 1)             */
#define MDR_BKP_REG63_LSE_FilterOm_Msk  (0x2UL)               /*!< MDR_BKP REG_63_TMR0: LSE_FilterOm (Bitfield-Mask: 0x01) */
#define MDR_BKP_REG63_LSE_BYP_Pos       (2UL)                 /*!< MDR_BKP REG_63_TMR0: LSE_BYP (Bit 2)                  */
#define MDR_BKP_REG63_LSE_BYP_Msk       (0x4UL)               /*!< MDR_BKP REG_63_TMR0: LSE_BYP (Bitfield-Mask: 0x01)    */
#define MDR_BKP_REG63_LSE_On_Pos        (3UL)                 /*!< MDR_BKP REG_63_TMR0: LSE_On (Bit 3)                   */
#define MDR_BKP_REG63_LSE_On_Msk        (0x8UL)               /*!< MDR_BKP REG_63_TMR0: LSE_On (Bitfield-Mask: 0x01)     */
#define MDR_BKP_REG63_HSE0_RDY_Pos      (4UL)                 /*!< MDR_BKP REG_63_TMR0: HSE0_RDY (Bit 4)                 */
#define MDR_BKP_REG63_HSE0_RDY_Msk      (0x10UL)              /*!< MDR_BKP REG_63_TMR0: HSE0_RDY (Bitfield-Mask: 0x01)   */
#define MDR_BKP_REG63_HSE0_FilterEn_Pos (5UL)                 /*!< MDR_BKP REG_63_TMR0: HSE0_FilterEn (Bit 5)            */
#define MDR_BKP_REG63_HSE0_FilterEn_Msk (0x20UL)              /*!< MDR_BKP REG_63_TMR0: HSE0_FilterEn (Bitfield-Mask: 0x01) */
#define MDR_BKP_REG63_HSE0_BYP_Pos      (6UL)                 /*!< MDR_BKP REG_63_TMR0: HSE0_BYP (Bit 6)                 */
#define MDR_BKP_REG63_HSE0_BYP_Msk      (0x40UL)              /*!< MDR_BKP REG_63_TMR0: HSE0_BYP (Bitfield-Mask: 0x01)   */
#define MDR_BKP_REG63_HSE0_On_Pos       (7UL)                 /*!< MDR_BKP REG_63_TMR0: HSE0_On (Bit 7)                  */
#define MDR_BKP_REG63_HSE0_On_Msk       (0x80UL)              /*!< MDR_BKP REG_63_TMR0: HSE0_On (Bitfield-Mask: 0x01)    */
#define MDR_BKP_REG63_HSE1_RDY_Pos      (8UL)                 /*!< MDR_BKP REG_63_TMR0: HSE1_RDY (Bit 8)                 */
#define MDR_BKP_REG63_HSE1_RDY_Msk      (0x100UL)             /*!< MDR_BKP REG_63_TMR0: HSE1_RDY (Bitfield-Mask: 0x01)   */
#define MDR_BKP_REG63_HSE1_FilterEn_Pos (9UL)                 /*!< MDR_BKP REG_63_TMR0: HSE1_FilterEn (Bit 9)            */
#define MDR_BKP_REG63_HSE1_FilterEn_Msk (0x200UL)             /*!< MDR_BKP REG_63_TMR0: HSE1_FilterEn (Bitfield-Mask: 0x01) */
#define MDR_BKP_REG63_HSE1_BYP_Pos      (10UL)                /*!< MDR_BKP REG_63_TMR0: HSE1_BYP (Bit 10)                */
#define MDR_BKP_REG63_HSE1_BYP_Msk      (0x400UL)             /*!< MDR_BKP REG_63_TMR0: HSE1_BYP (Bitfield-Mask: 0x01)   */
#define MDR_BKP_REG63_HSE1_On_Pos       (11UL)                /*!< MDR_BKP REG_63_TMR0: HSE1_On (Bit 11)                 */
#define MDR_BKP_REG63_HSE1_On_Msk       (0x800UL)             /*!< MDR_BKP REG_63_TMR0: HSE1_On (Bitfield-Mask: 0x01)    */
#define MDR_BKP_REG63_LSI_RDY_Pos       (12UL)                /*!< MDR_BKP REG_63_TMR0: LSI_Ready (Bit 12)               */
#define MDR_BKP_REG63_LSI_RDY_Msk       (0x1000UL)            /*!< MDR_BKP REG_63_TMR0: LSI_Ready (Bitfield-Mask: 0x01)  */
#define MDR_BKP_REG63_LSI_Dis_Pos       (13UL)                /*!< MDR_BKP REG_63_TMR0: LSI_Dis (Bit 13)                 */
#define MDR_BKP_REG63_LSI_Dis_Msk       (0x2000UL)            /*!< MDR_BKP REG_63_TMR0: LSI_Dis (Bitfield-Mask: 0x01)    */
#define MDR_BKP_REG63_LSI_Trim_Pos      (14UL)                /*!< MDR_BKP REG_63_TMR0: LSI_Trim (Bit 14)                */
#define MDR_BKP_REG63_LSI_Trim_Msk      (0x1fc000UL)          /*!< MDR_BKP REG_63_TMR0: LSI_Trim (Bitfield-Mask: 0x7f)   */
#define MDR_BKP_REG63_HSI_RDY_Pos       (21UL)                /*!< MDR_BKP REG_63_TMR0: HSI_Ready (Bit 21)               */
#define MDR_BKP_REG63_HSI_RDY_Msk       (0x200000UL)          /*!< MDR_BKP REG_63_TMR0: HSI_Ready (Bitfield-Mask: 0x01)  */
#define MDR_BKP_REG63_HSI_Trim_Pos      (22UL)                /*!< MDR_BKP REG_63_TMR0: HSI_Trim (Bit 22)                */
#define MDR_BKP_REG63_HSI_Trim_Msk      (0x1fc00000UL)        /*!< MDR_BKP REG_63_TMR0: HSI_Trim (Bitfield-Mask: 0x7f)   */
#define MDR_BKP_REG63_HSI_Dis_Pos       (29UL)                /*!< MDR_BKP REG_63_TMR0: HSI_Dis (Bit 29)                 */
#define MDR_BKP_REG63_HSI_Dis_Msk       (0x20000000UL)        /*!< MDR_BKP REG_63_TMR0: HSI_Dis (Bitfield-Mask: 0x01)    */
#define MDR_BKP_REG63_LSI_POR_Ready_Pos (31UL)                /*!< MDR_BKP REG_63_TMR0: LSI_POR_Ready (Bit 31)           */
#define MDR_BKP_REG63_LSI_POR_Ready_Msk (0x80000000UL)        /*!< MDR_BKP REG_63_TMR0: LSI_POR_Ready (Bitfield-Mask: 0x01) */


//-------   Reg_64  ----------
typedef enum {                  /*!< MDR_BKP_REG_64_TMR0_RTC_Sel                                               */
  MDR_BKP_RTC_LSI      = 0,     /*!< LSI : LSI Clock                                                           */
  MDR_BKP_RTC_LSE      = 1,     /*!< LSE : LSE Clock                                                           */
  MDR_BKP_RTC_RTCCLK   = 2,     /*!< RTCCLK : RTCCLK Clock                                                     */
} MDR_BKP_RTC_Sel;

typedef struct {
      __IOM MDR_BKP_RTC_Sel RTC_Sel     : 2;           /*!< [1..0]   Select Clock for RTC                                               */
      __IOM uint32_t        RTC_Cal     : 8;           /*!< [9..2]   RTC pass counts                                                    */
      __IOM MDR_OnOff       RTC_RST     : 1;           /*!< [10..10] RTC Reset                                                        */
      __IOM MDR_OnOff       RTC_En      : 1;           /*!< [11..11] RTC Enable                                                       */
      __IOM uint32_t        CProt_Lim   : 10;          /*!< [21..12] Current protection limit                                         */
      __IOM uint32_t        CProt_Count : 10;          /*!< [31..22] Counter of I_Lim events                                          */
} MDR_BKP_REG64_Bits;

#define MDR_BKP_REG64_RTC_Sel_Pos     (0UL)                     /*!< MDR_BKP REG_64_TMR0: RTC_Sel (Bit 0)                  */
#define MDR_BKP_REG64_RTC_Sel_Msk     (0x3UL)                   /*!< MDR_BKP REG_64_TMR0: RTC_Sel (Bitfield-Mask: 0x03)    */
#define MDR_BKP_REG64_RTC_Cal_Pos     (2UL)                     /*!< MDR_BKP REG_64_TMR0: RTC_Cal (Bit 2)                  */
#define MDR_BKP_REG64_RTC_Cal_Msk     (0x3fcUL)                 /*!< MDR_BKP REG_64_TMR0: RTC_Cal (Bitfield-Mask: 0xff)    */
#define MDR_BKP_REG64_RTC_RST_Pos     (10UL)                    /*!< MDR_BKP REG_64_TMR0: RTC_RST (Bit 10)                 */
#define MDR_BKP_REG64_RTC_RST_Msk     (0x400UL)                 /*!< MDR_BKP REG_64_TMR0: RTC_RST (Bitfield-Mask: 0x01)    */
#define MDR_BKP_REG64_RTC_En_Pos      (11UL)                    /*!< MDR_BKP REG_64_TMR0: RTC_En (Bit 11)                  */
#define MDR_BKP_REG64_RTC_En_Msk      (0x800UL)                 /*!< MDR_BKP REG_64_TMR0: RTC_En (Bitfield-Mask: 0x01)     */
#define MDR_BKP_REG64_CProt_Lim_Pos   (12UL)                    /*!< MDR_BKP REG_64_TMR0: CProt_Lim (Bit 12)               */
#define MDR_BKP_REG64_CProt_Lim_Msk   (0x3ff000UL)              /*!< MDR_BKP REG_64_TMR0: CProt_Lim (Bitfield-Mask: 0x3ff) */
#define MDR_BKP_REG64_CProt_Count_Pos (22UL)                  /*!< MDR_BKP REG_64_TMR0: CProt_Count (Bit 22)             */
#define MDR_BKP_REG64_CProt_Count_Msk (0xffc00000UL)          /*!< MDR_BKP REG_64_TMR0: CProt_Count (Bitfield-Mask: 0x3ff) */


//-------   BLDO  ----------
typedef   struct {
      __IOM MDR_OnOff           BLDO_Dis    : 1;           /*!< [0..0] Disable Battery LDO                               */
      __IOM MDR_BKP_LDO_Trim    BLDO_Trim   : 3;           /*!< [3..1] LDO_Bat Trim                                      */
      __IOM MDR_BKP_LDO_SRILow  BLDO_SRILow : 3;           /*!< [6..4] LDO_Bat Power adjustment                          */
      __IOM MDR_OnOff           BLDO_RDY    : 1;           /*!< [7..7] BLDO Ready                                        */
      __IOM MDR_OnOff           ECC_Dis     : 1;           /*!< [8..8] Disable ECC                                       */
      __IM  uint32_t                        : 22;
      __IOM MDR_OnOff           PMU_BG_Dis  : 1;           /*!< [31..31] Disable PMU                                     */
} MDR_BKP_BLDO_Bits;

#define MDR_BKP_BLDO_BLDO_Dis_Pos    (0UL)                     /*!< MDR_BKP BLDO_CTRL0: BLDO_Dis (Bit 0)                  */
#define MDR_BKP_BLDO_BLDO_Dis_Msk    (0x1UL)                   /*!< MDR_BKP BLDO_CTRL0: BLDO_Dis (Bitfield-Mask: 0x01)    */
#define MDR_BKP_BLDO_BLDO_Trim_Pos   (1UL)                     /*!< MDR_BKP BLDO_CTRL0: BLDO_Trim (Bit 1)                 */
#define MDR_BKP_BLDO_BLDO_Trim_Msk   (0xeUL)                   /*!< MDR_BKP BLDO_CTRL0: BLDO_Trim (Bitfield-Mask: 0x07)   */
#define MDR_BKP_BLDO_BLDO_SRILow_Pos (4UL)                    /*!< MDR_BKP BLDO_CTRL0: BLDO_SRILow (Bit 4)               */
#define MDR_BKP_BLDO_BLDO_SRILow_Msk (0x70UL)                 /*!< MDR_BKP BLDO_CTRL0: BLDO_SRILow (Bitfield-Mask: 0x07) */
#define MDR_BKP_BLDO_BLDO_RDY_Pos    (7UL)                     /*!< MDR_BKP BLDO_CTRL0: BLDO_RDY (Bit 7)                  */
#define MDR_BKP_BLDO_BLDO_RDY_Msk    (0x80UL)                  /*!< MDR_BKP BLDO_CTRL0: BLDO_RDY (Bitfield-Mask: 0x01)    */
#define MDR_BKP_BLDO_ECC_Dis_Pos     (8UL)                     /*!< MDR_BKP BLDO_CTRL0: ECC_Dis (Bit 8)                   */
#define MDR_BKP_BLDO_ECC_Dis_Msk     (0x100UL)                 /*!< MDR_BKP BLDO_CTRL0: ECC_Dis (Bitfield-Mask: 0x01)     */
#define MDR_BKP_BLDO_PMU_BG_Dis_Pos  (31UL)                    /*!< MDR_BKP BLDO_CTRL0: PMU_BG_Dis (Bit 31)               */
#define MDR_BKP_BLDO_PMU_BG_Dis_Msk  (0x80000000UL)            /*!< MDR_BKP BLDO_CTRL0: PMU_BG_Dis (Bitfield-Mask: 0x01)  */


//-------   BKP_LockStep Instance  ----------
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
} MDR_BKP_Typeex;


typedef struct {                                /*!< (@ 0x40001000) MDR_BKP Structure                                          */
  __IOM uint32_t        REG[MDR_BKP_REG_XX_COUNT];                /*!< (@ 0x00000000) User backup registers                                      */
  __IOM uint32_t        KEY;                    /*!< (@ 0x000000F0) Unlock BKP and RTC Registers                               */  
  
  union {
    __IOM uint32_t      REG_64_TMR0;            /*!< (@ 0x000000F4) REG64 Control register                                     */
    MDR_BKP_REG64_Bits  REG_64_TMR0_b;
  } ;  
  union {
    __IOM uint32_t      REG_64_TMR1;            /*!< (@ 0x000000F8) REG64 Control register                                     */
    MDR_BKP_REG64_Bits  REG_64_TMR1_b;
  } ;  
  union {
    __IOM uint32_t      REG_64_TMR2;            /*!< (@ 0x000000FC) REG64 Control register                                     */
    MDR_BKP_REG64_Bits  REG_64_TMR2_b;
  } ;  
  
  MDR_BKP_REG6X         TMR0;
  MDR_BKP_REG6X         TMR1;
  MDR_BKP_REG6X         TMR2;  
  
  MDR_RTC_Type          RTC0;  
  __IM  uint32_t        _RESERVED[3];
  MDR_RTC_Type          RTC1;
  __IM  uint32_t        _RESERVED1[3];
  MDR_RTC_Type          RTC2;  
  __IM  uint32_t        _RESERVED2[3];
  
  union {
    __IOM uint32_t      BLDO_CTRL0;             /*!< (@ 0x00000190) Battery LDO Control                                        */
    MDR_BKP_BLDO_Bits   BLDO_CTRL0_b;
  } ;
  union {
    __IOM uint32_t      BLDO_CTRL1;             /*!< (@ 0x00000194) Battery LDO Control                                        */
    MDR_BKP_BLDO_Bits   BLDO_CTRL1_b;
  } ;  
  union {
    __IOM uint32_t      BLDO_CTRL2;             /*!< (@ 0x00000198) Battery LDO Control                                        */
    MDR_BKP_BLDO_Bits   BLDO_CTRL2_b;    
  } ;
} MDR_BKP_Type;                                 /*!< Size = 412 (0x19c)                                                        */


/*!< Size = 388 (0x184)                                                        */


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

#endif  //_MDR_BKP_ESila_DEFS_H

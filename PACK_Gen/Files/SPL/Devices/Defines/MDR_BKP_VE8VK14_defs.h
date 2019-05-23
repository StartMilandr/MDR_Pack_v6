#ifndef _MDR_BKP_VE8VK14_DEFS_H
#define _MDR_BKP_VE8VK14_DEFS_H

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

#define MDR_BKP_REG_XX_COUNT  14

//-------   Reg_60  ----------
typedef struct {
      __IOM uint32_t  MODE            : 7;       /*!< [6..0] Boot Mode                                                          */
      __IOM MDR_OnOff FPOR            : 1;       /*!< [7..7] Bootloader completed                                               */
      __IOM MDR_OnOff S_UccReset      : 1;       /*!< [8..8] Reset by Ucc                                                       */
      __IOM MDR_OnOff S_RSTn0         : 1;       /*!< [9..9] Reset by RSTn0 signal                                              */
      __IOM MDR_OnOff S_FT_Reset      : 1;       /*!< [10..10] Reset from FT_CNTR                                               */
      __IOM MDR_OnOff S_WDT_Reset     : 1;       /*!< [11..11] Reset from WDT                                                   */
      __IOM MDR_OnOff S_RSTn1         : 1;       /*!< [12..12] Reset by RSTn1 signal                                            */
      __IOM MDR_OnOff S_OVRSTn        : 1;       /*!< [13..13] Reset by Ucc > U_over (5.75V)                                    */
      __IOM MDR_OnOff S_SYSRSTn       : 1;       /*!< [14..14] Reset by software                                                */
      __IOM MDR_OnOff JTAG_Dis        : 1;       /*!< [15..15] Disable JTAG                                                     */
      __IOM MDR_OnOff LimEn_LDO_DUcc0 : 1;       /*!< [16..16] Enable limit for DUcc0 (~300mA)                                  */
      __IOM MDR_OnOff LimEn_LDO_DUcc1 : 1;       /*!< [17..17] Enable limit for DUcc1 (~300mA)                                  */
      __IOM MDR_OnOff LimEn_LDO_DUcc2 : 1;       /*!< [18..18] Enable limit for DUcc2 (~300mA)                                  */
      __IOM MDR_OnOff LimEn_LDO_DUcc3 : 1;       /*!< [19..19] Enable limit for DUcc3 (~300mA)                                  */
      __IOM MDR_OnOff LimEn_LDO_BUcc  : 1;       /*!< [20..20] Enable limit for DUcc_Bat (~50mA)                                */
      __IOM MDR_OnOff LimEn_LDO_PLL   : 1;       /*!< [21..21] Enable limit for DUcc_PLL (~50mA)                                */
      __IM  uint32_t                  : 3;
      __IOM MDR_OnOff ERR_REG60x      : 1;       /*!< [25..25] Fault in REG_60x                                                 */
      __IOM MDR_OnOff ERR_REG61x_62x  : 1;       /*!< [26..26] Fault in REG_61x or REG_62x                                      */
      __IOM MDR_OnOff ERR_REG63x      : 1;       /*!< [27..27] Fault in REG_63x                                                 */
      __IOM MDR_OnOff PORSTn_Dis      : 1;       /*!< [28..28] Disable reset by Ucc > U_POR (2.5V)                               */
      __IOM MDR_OnOff OVRSTn_Dis      : 1;       /*!< [29..29] Disable reset by Ucc > U_over (5.75V)                             */
      __IOM MDR_OnOff CLR_ERR         : 1;       /*!< [30..30] Clear Errors of REG_60x - 63x                                    */
      __IOM MDR_OnOff ERR_IRQ_EN      : 1;       /*!< [31..31] Enable BKP_IRQn on Errors                                        */
} MDR_BKP_REG60_Bits;

#define MDR_BKP_REG60_MODE_Pos            (0UL)                /*!< MDR_BKP REG_60_TMR0: MODE (Bit 0)                     */
#define MDR_BKP_REG60_MODE_Msk            (0x7fUL)             /*!< MDR_BKP REG_60_TMR0: MODE (Bitfield-Mask: 0x7f)       */
#define MDR_BKP_REG60_FPOR_Pos            (7UL)                /*!< MDR_BKP REG_60_TMR0: FPOR (Bit 7)                     */
#define MDR_BKP_REG60_FPOR_Msk            (0x80UL)             /*!< MDR_BKP REG_60_TMR0: FPOR (Bitfield-Mask: 0x01)       */
#define MDR_BKP_REG60_S_UccReset_Pos      (8UL)                /*!< MDR_BKP REG_60_TMR0: S_UccReset (Bit 8)               */
#define MDR_BKP_REG60_S_UccReset_Msk      (0x100UL)            /*!< MDR_BKP REG_60_TMR0: S_UccReset (Bitfield-Mask: 0x01) */
#define MDR_BKP_REG60_S_RSTn0_Pos         (9UL)                /*!< MDR_BKP REG_60_TMR0: S_RSTn0 (Bit 9)                  */
#define MDR_BKP_REG60_S_RSTn0_Msk         (0x200UL)            /*!< MDR_BKP REG_60_TMR0: S_RSTn0 (Bitfield-Mask: 0x01)    */
#define MDR_BKP_REG60_S_FT_Reset_Pos      (10UL)               /*!< MDR_BKP REG_60_TMR0: S_FT_Reset (Bit 10)              */
#define MDR_BKP_REG60_S_FT_Reset_Msk      (0x400UL)            /*!< MDR_BKP REG_60_TMR0: S_FT_Reset (Bitfield-Mask: 0x01) */
#define MDR_BKP_REG60_S_WDT_Reset_Pos     (11UL)               /*!< MDR_BKP REG_60_TMR0: S_WDT_Reset (Bit 11)             */
#define MDR_BKP_REG60_S_WDT_Reset_Msk     (0x800UL)            /*!< MDR_BKP REG_60_TMR0: S_WDT_Reset (Bitfield-Mask: 0x01) */
#define MDR_BKP_REG60_S_RSTn1_Pos         (12UL)               /*!< MDR_BKP REG_60_TMR0: S_RSTn1 (Bit 12)                 */
#define MDR_BKP_REG60_S_RSTn1_Msk         (0x1000UL)           /*!< MDR_BKP REG_60_TMR0: S_RSTn1 (Bitfield-Mask: 0x01)    */
#define MDR_BKP_REG60_S_OVRSTn_Pos        (13UL)               /*!< MDR_BKP REG_60_TMR0: S_OVRSTn (Bit 13)                */
#define MDR_BKP_REG60_S_OVRSTn_Msk        (0x2000UL)           /*!< MDR_BKP REG_60_TMR0: S_OVRSTn (Bitfield-Mask: 0x01)   */
#define MDR_BKP_REG60_S_SYSRSTn_Pos       (14UL)               /*!< MDR_BKP REG_60_TMR0: S_SYSRSTn (Bit 14)               */
#define MDR_BKP_REG60_S_SYSRSTn_Msk       (0x4000UL)           /*!< MDR_BKP REG_60_TMR0: S_SYSRSTn (Bitfield-Mask: 0x01)  */
#define MDR_BKP_REG60_JTAG_Dis_Pos        (15UL)               /*!< MDR_BKP REG_60_TMR0: JTAG_Enable (Bit 15)             */
#define MDR_BKP_REG60_JTAG_Dis_Msk        (0x8000UL)           /*!< MDR_BKP REG_60_TMR0: JTAG_Enable (Bitfield-Mask: 0x01) */
#define MDR_BKP_REG60_LimEn_LDO_DUcc0_Pos (16UL)               /*!< MDR_BKP REG_60_TMR0: LimEn_LDO_DUcc0 (Bit 16)         */
#define MDR_BKP_REG60_LimEn_LDO_DUcc0_Msk (0x10000UL)          /*!< MDR_BKP REG_60_TMR0: LimEn_LDO_DUcc0 (Bitfield-Mask: 0x01) */
#define MDR_BKP_REG60_LimEn_LDO_DUcc1_Pos (17UL)               /*!< MDR_BKP REG_60_TMR0: LimEn_LDO_DUcc1 (Bit 17)         */
#define MDR_BKP_REG60_LimEn_LDO_DUcc1_Msk (0x20000UL)          /*!< MDR_BKP REG_60_TMR0: LimEn_LDO_DUcc1 (Bitfield-Mask: 0x01) */
#define MDR_BKP_REG60_LimEn_LDO_DUcc2_Pos (18UL)               /*!< MDR_BKP REG_60_TMR0: LimEn_LDO_DUcc2 (Bit 18)         */
#define MDR_BKP_REG60_LimEn_LDO_DUcc2_Msk (0x40000UL)          /*!< MDR_BKP REG_60_TMR0: LimEn_LDO_DUcc2 (Bitfield-Mask: 0x01) */
#define MDR_BKP_REG60_LimEn_LDO_DUcc3_Pos (19UL)               /*!< MDR_BKP REG_60_TMR0: LimEn_LDO_DUcc3 (Bit 19)         */
#define MDR_BKP_REG60_LimEn_LDO_DUcc3_Msk (0x80000UL)          /*!< MDR_BKP REG_60_TMR0: LimEn_LDO_DUcc3 (Bitfield-Mask: 0x01) */
#define MDR_BKP_REG60_LimEn_LDO_BUcc_Pos  (20UL)               /*!< MDR_BKP REG_60_TMR0: LimEn_LDO_BUcc (Bit 20)          */
#define MDR_BKP_REG60_LimEn_LDO_BUcc_Msk  (0x100000UL)         /*!< MDR_BKP REG_60_TMR0: LimEn_LDO_BUcc (Bitfield-Mask: 0x01) */
#define MDR_BKP_REG60_LimEn_LDO_PLL_Pos   (21UL)               /*!< MDR_BKP REG_60_TMR0: LimEn_LDO_PLL (Bit 21)           */
#define MDR_BKP_REG60_LimEn_LDO_PLL_Msk   (0x200000UL)         /*!< MDR_BKP REG_60_TMR0: LimEn_LDO_PLL (Bitfield-Mask: 0x01) */
#define MDR_BKP_REG60_ERR_REG60x_Pos      (25UL)               /*!< MDR_BKP REG_60_TMR0: ERR_REG60x (Bit 25)              */
#define MDR_BKP_REG60_ERR_REG60x_Msk      (0x2000000UL)        /*!< MDR_BKP REG_60_TMR0: ERR_REG60x (Bitfield-Mask: 0x01) */
#define MDR_BKP_REG60_ERR_REG61x_62x_Pos  (26UL)               /*!< MDR_BKP REG_60_TMR0: ERR_REG61x_62x (Bit 26)          */
#define MDR_BKP_REG60_ERR_REG61x_62x_Msk  (0x4000000UL)        /*!< MDR_BKP REG_60_TMR0: ERR_REG61x_62x (Bitfield-Mask: 0x01) */
#define MDR_BKP_REG60_ERR_REG63x_Pos      (27UL)               /*!< MDR_BKP REG_60_TMR0: ERR_REG63x (Bit 27)              */
#define MDR_BKP_REG60_ERR_REG63x_Msk      (0x8000000UL)        /*!< MDR_BKP REG_60_TMR0: ERR_REG63x (Bitfield-Mask: 0x01) */
#define MDR_BKP_REG60_PORSTn_Dis_Pos      (28UL)               /*!< MDR_BKP REG_60_TMR0: PORSTn_Dis (Bit 28)               */
#define MDR_BKP_REG60_PORSTn_Dis_Msk      (0x10000000UL)       /*!< MDR_BKP REG_60_TMR0: PORSTn_Dis (Bitfield-Mask: 0x01)  */
#define MDR_BKP_REG60_OVRSTn_Dis_Pos      (29UL)               /*!< MDR_BKP REG_60_TMR0: OVRSTn_Dis (Bit 29)               */
#define MDR_BKP_REG60_OVRSTn_Dis_Msk      (0x20000000UL)       /*!< MDR_BKP REG_60_TMR0: OVRSTn_Dis (Bitfield-Mask: 0x01)  */
#define MDR_BKP_REG60_CLR_ERR_Pos         (30UL)               /*!< MDR_BKP REG_60_TMR0: CLR_ERR (Bit 30)                 */
#define MDR_BKP_REG60_CLR_ERR_Msk         (0x40000000UL)       /*!< MDR_BKP REG_60_TMR0: CLR_ERR (Bitfield-Mask: 0x01)    */
#define MDR_BKP_REG60_ERR_IRQ_EN_Pos      (31UL)               /*!< MDR_BKP REG_60_TMR0: ERR_IRQ_EN (Bit 31)              */
#define MDR_BKP_REG60_ERR_IRQ_EN_Msk      (0x80000000UL)       /*!< MDR_BKP REG_60_TMR0: ERR_IRQ_EN (Bitfield-Mask: 0x01) */

//-------   Reg_63  ----------
typedef enum {                                  /*!< MDR_BKP_REG_63_TMR1_LSI_Trim                                              */
  MDR_BKP_REG63_LSI_Trim_Max8    = 0,     /*!< Max8 : LSI Trim                                                           */
  MDR_BKP_REG63_LSI_Trim_Max7    = 1,     /*!< Max7 : LSI Trim                                                           */
  MDR_BKP_REG63_LSI_Trim_Max6    = 2,     /*!< Max6 : LSI Trim                                                           */
  MDR_BKP_REG63_LSI_Trim_Max5    = 3,     /*!< Max5 : LSI Trim                                                           */
  MDR_BKP_REG63_LSI_Trim_Max4    = 4,     /*!< Max4 : LSI Trim                                                           */
  MDR_BKP_REG63_LSI_Trim_Max3    = 5,     /*!< Max3 : LSI Trim                                                           */
  MDR_BKP_REG63_LSI_Trim_Max2    = 6,     /*!< Max2 : LSI Trim                                                           */
  MDR_BKP_REG63_LSI_Trim_Max1    = 7,     /*!< Max1 : LSI Trim                                                           */
  MDR_BKP_REG63_LSI_Trim_Typical = 8,     /*!< Typical : LSI Default                                                     */
  MDR_BKP_REG63_LSI_Trim_Min1    = 9,     /*!< Min1 : LSI Trim                                                           */
  MDR_BKP_REG63_LSI_Trim_Min2    = 10,    /*!< Min2 : LSI Trim                                                           */
  MDR_BKP_REG63_LSI_Trim_Min3    = 11,    /*!< Min3 : LSI Trim                                                           */
  MDR_BKP_REG63_LSI_Trim_Min4    = 12,    /*!< Min4 : LSI Trim                                                           */
  MDR_BKP_REG63_LSI_Trim_Min5    = 13,    /*!< Min5 : LSI Trim                                                           */
  MDR_BKP_REG63_LSI_Trim_Min6    = 14,    /*!< Min6 : LSI Trim                                                           */
  MDR_BKP_REG63_LSI_Trim_Min7    = 15,    /*!< Min7 : LSI Trim                                                           */
} MDR_BKP_REG63_LSI_Trim;

typedef enum {                  /*!< MDR_BKP_REG_64_TMR0_RTC_Sel                                               */
  MDR_BKP_RTC_LSI      = 0,     /*!< LSI : LSI Clock                                                           */
  MDR_BKP_RTC_LSE      = 1,     /*!< LSE : LSE Clock                                                           */
  MDR_BKP_RTC_RTCCLK   = 2,     /*!< RTCCLK : RTCCLK Clock                                                     */
} MDR_BKP_RTC_Sel;

typedef struct {
      __IOM MDR_OnOff               LSE_On     : 1;            /*!< [0..0] LSE Enable                                    */
      __IOM MDR_OnOff               LSE_BYP    : 1;            /*!< [1..1] LSE Bypass                                    */
      __IOM MDR_BKP_RTC_Sel         RTC_Sel    : 2;            /*!< [3..2] Select Clock for RTC                          */
      __IOM MDR_OnOff               RTC_En     : 1;            /*!< [4..4] RTC Enable                                    */
      __IOM uint32_t                RTC_Cal    : 8;            /*!< [12..5] RTC pass counts                              */
      __IOM MDR_OnOff               LSE_RDY    : 1;            /*!< [13..13] LSE Ready                                   */
      __IOM MDR_OnOff               LSE_FilterEn : 1;          /*!< [14..14] LSE Filter Enable                           */
      __IOM MDR_OnOff               LSI_On     : 1;            /*!< [15..15] LSI Enable                                  */
      __IOM MDR_BKP_REG63_LSI_Trim  LSI_Trim   : 5;            /*!< [20..16] LSI Trim freq                               */
      __IOM MDR_OnOff               LSI_RDY    : 1;            /*!< [21..21] LSI Ready                                   */
      __IOM MDR_OnOff               HSI_On     : 1;            /*!< [22..22] HSI Enable                                  */
      __IOM MDR_OnOff               HSI_RDY    : 1;            /*!< [23..23] HSI Ready                                   */
      __IOM uint32_t                HSI_Trim   : 6;            /*!< [29..24] HSI trim freq                               */
      __IOM MDR_OnOff               STANDBY    : 1;            /*!< [30..30] Go Standby mode                             */
      __IOM MDR_OnOff               RTC_RST    : 1;            /*!< [31..31] RTC Reset                                   */
} MDR_BKP_REG63_Bits;

#define MDR_BKP_REG63_LSE_On_Pos    (0UL)                     /*!< MDR_BKP REG_63_TMR0: LSE_On (Bit 0)                   */
#define MDR_BKP_REG63_LSE_On_Msk    (0x1UL)                   /*!< MDR_BKP REG_63_TMR0: LSE_On (Bitfield-Mask: 0x01)     */
#define MDR_BKP_REG63_LSE_BYP_Pos   (1UL)                     /*!< MDR_BKP REG_63_TMR0: LSE_BYP (Bit 1)                  */
#define MDR_BKP_REG63_LSE_BYP_Msk   (0x2UL)                   /*!< MDR_BKP REG_63_TMR0: LSE_BYP (Bitfield-Mask: 0x01)    */
#define MDR_BKP_REG63_RTC_Sel_Pos   (2UL)                     /*!< MDR_BKP REG_63_TMR0: RTC_Sel (Bit 2)                  */
#define MDR_BKP_REG63_RTC_Sel_Msk   (0xcUL)                   /*!< MDR_BKP REG_63_TMR0: RTC_Sel (Bitfield-Mask: 0x03)    */
#define MDR_BKP_REG63_RTC_En_Pos    (4UL)                     /*!< MDR_BKP REG_63_TMR0: RTC_En (Bit 4)                   */
#define MDR_BKP_REG63_RTC_En_Msk    (0x10UL)                  /*!< MDR_BKP REG_63_TMR0: RTC_En (Bitfield-Mask: 0x01)     */
#define MDR_BKP_REG63_RTC_Cal_Pos   (5UL)                     /*!< MDR_BKP REG_63_TMR0: RTC_Cal (Bit 5)                  */
#define MDR_BKP_REG63_RTC_Cal_Msk   (0x1fe0UL)                /*!< MDR_BKP REG_63_TMR0: RTC_Cal (Bitfield-Mask: 0xff)    */
#define MDR_BKP_REG63_LSE_RDY_Pos   (13UL)                    /*!< MDR_BKP REG_63_TMR0: LSE_RDY (Bit 13)                 */
#define MDR_BKP_REG63_LSE_RDY_Msk   (0x2000UL)                /*!< MDR_BKP REG_63_TMR0: LSE_RDY (Bitfield-Mask: 0x01)    */
#define MDR_BKP_REG63_LSE_FilterEn_Pos (14UL)                 /*!< MDR_BKP REG_63_TMR0: LSE_FilterEn (Bit 14)            */
#define MDR_BKP_REG63_LSE_FilterEn_Msk (0x4000UL)             /*!< MDR_BKP REG_63_TMR0: LSE_FilterEn (Bitfield-Mask: 0x01) */
#define MDR_BKP_REG63_LSI_On_Pos    (15UL)                    /*!< MDR_BKP REG_63_TMR0: LSI_On (Bit 15)                  */
#define MDR_BKP_REG63_LSI_On_Msk    (0x8000UL)                /*!< MDR_BKP REG_63_TMR0: LSI_On (Bitfield-Mask: 0x01)     */
#define MDR_BKP_REG63_LSI_Trim_Pos  (16UL)                    /*!< MDR_BKP REG_63_TMR0: LSI_Trim (Bit 16)                */
#define MDR_BKP_REG63_LSI_Trim_Msk  (0x1f0000UL)              /*!< MDR_BKP REG_63_TMR0: LSI_Trim (Bitfield-Mask: 0x1f)   */
#define MDR_BKP_REG63_LSI_RDY_Pos   (21UL)                    /*!< MDR_BKP REG_63_TMR0: LSI_RDY (Bit 21)                 */
#define MDR_BKP_REG63_LSI_RDY_Msk   (0x200000UL)              /*!< MDR_BKP REG_63_TMR0: LSI_RDY (Bitfield-Mask: 0x01)    */
#define MDR_BKP_REG63_HSI_On_Pos    (22UL)                    /*!< MDR_BKP REG_63_TMR0: HSI_On (Bit 22)                  */
#define MDR_BKP_REG63_HSI_On_Msk    (0x400000UL)              /*!< MDR_BKP REG_63_TMR0: HSI_On (Bitfield-Mask: 0x01)     */
#define MDR_BKP_REG63_HSI_RDY_Pos   (23UL)                    /*!< MDR_BKP REG_63_TMR0: HSI_RDY (Bit 23)                 */
#define MDR_BKP_REG63_HSI_RDY_Msk   (0x800000UL)              /*!< MDR_BKP REG_63_TMR0: HSI_RDY (Bitfield-Mask: 0x01)    */
#define MDR_BKP_REG63_HSI_Trim_Pos  (24UL)                    /*!< MDR_BKP REG_63_TMR0: HSI_Trim (Bit 24)                */
#define MDR_BKP_REG63_HSI_Trim_Msk  (0x3f000000UL)            /*!< MDR_BKP REG_63_TMR0: HSI_Trim (Bitfield-Mask: 0x3f)   */
#define MDR_BKP_REG63_STANDBY_Pos   (30UL)                    /*!< MDR_BKP REG_63_TMR0: STANDBY (Bit 30)                 */
#define MDR_BKP_REG63_STANDBY_Msk   (0x40000000UL)            /*!< MDR_BKP REG_63_TMR0: STANDBY (Bitfield-Mask: 0x01)    */
#define MDR_BKP_REG63_RTC_RST_Pos   (31UL)                    /*!< MDR_BKP REG_63_TMR0: RTC_RST (Bit 31)                 */
#define MDR_BKP_REG63_RTC_RST_Msk   (0x80000000UL)            /*!< MDR_BKP REG_63_TMR0: RTC_RST (Bitfield-Mask: 0x01)    */



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

#endif  //_MDR_BKP_VE8VK14_DEFS_H

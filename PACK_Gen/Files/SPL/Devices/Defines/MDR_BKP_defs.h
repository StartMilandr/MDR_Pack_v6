#ifndef _MDR_BKP_DEFS_H
#define _MDR_BKP_DEFS_H

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

/* =========================================================  REG_XX  ======================================================== */
#define MDR_BKP_REG_XX_COUNT  14

/* ========================================================  REG_0E  ========================================================= */

typedef enum {
  MDR_LOWRI_le10MHz   = 0,                  /*!< 10MHz   : CPU Clock less then 10MHz  : +I ~ 300uA                             */
  MDR_LOWRI_le100KHz  = 1,                  /*!< 200KHz  : CPU Clock less then 200KHz : +I ~ 6.6uA                             */
  MDR_LOWRI_le500KMHz = 2,                  /*!< 500KHz  : CPU Clock less then 500KHz : +I ~ 20A                               */
  MDR_LOWRI_le1MHz    = 3,                  /*!< 1MHz    : CPU Clock less then 1MHz   : +I ~ 80uA                              */
  MDR_LOWRI_GensOff   = 4,                  /*!< GensOffz: Generators Off             : +I ~ 2uA                               */
  MDR_LOWRI_le40MHz   = 5,                  /*!< 40MHz   : CPU Clock less then 40MHz  : +I ~ 900uA                             */
  MDR_LOWRI_le80MHz   = 6,                  /*!< 80MHz   : CPU Clock less then 80MHz  : +I ~ 4.4mA                             */
  MDR_LOWRI_gt80MHz   = 7,                  /*!< above_80MHz : CPU Clock above 10MHz  : +I ~ 19mA                              */
} MDR_BKP_LOW_RI;

typedef enum {
  MDR_dDUcc_p0v1      = 0,                  /*!< +0.1  : DUcc += 0.1 V                                                      */
  MDR_dDUcc_p0v06     = 1,                  /*!< +0.06 : DUcc += 0.06 V                                                     */
  MDR_dDUcc_p0v04     = 2,                  /*!< +0.04 : DUcc += 0.04 V                                                     */
  MDR_dDUcc_p0v01     = 3,                  /*!< +0.01 : DUcc += 0.01 V                                                     */
  MDR_dDUcc_m0v01     = 4,                  /*!< -0.01 : DUcc -= 0.01 V                                                     */
  MDR_dDUcc_m0v04     = 5,                  /*!< -0.04 : DUcc -= 0.04 V                                                     */
  MDR_dDUcc_m0v06     = 6,                  /*!< -0.6  : DUcc -= 0.06 V                                                     */
  MDR_dDUcc_m0v1      = 7                   /*!< -0.1  : DUcc -= 0.1 V                                                      */
} MDR_BKP_dDUcc;


/* ========================================================  REG_0F  ========================================================= */
typedef enum {
    MDR_RTC_LSI      = 0,                   /*!< LSI : RTC use LSI clock                                                       */
    MDR_RTC_LSE      = 0,                   /*!< LSE : RTC use LSE clock                                                       */
    MDR_RTC_HSIRTC   = 0,                   /*!< HSIRTC : RTC use HSIRTC clock                                                 */
    MDR_RTC_HSERTC   = 0                    /*!< HSERTC : RTC use HSERTC clock                                                 */
} MDR_BKP_RTC_SEL;

// MDR_BKP_LSI_TRIM can be used for LSI_TRIM, rest items (of 32) has value about 32KHz
typedef enum {                           /*!< MDR_BKP_REG_0F_LSI_TRIM                                                   */
  MDR_BKP_LSI_TRIM_69KHz        = 0,     /*!< 69KHz : LSI frequency tuner                                               */
  MDR_BKP_LSI_TRIM_65KHz        = 1,     /*!< 65KHz : LSI frequency tuner                                               */
  MDR_BKP_LSI_TRIM_60KHz        = 2,     /*!< 60KHz : LSI frequency tuner                                               */
  MDR_BKP_LSI_TRIM_58KHz        = 3,     /*!< 58KHz : LSI frequency tuner                                               */
  MDR_BKP_LSI_TRIM_52KHz        = 4,     /*!< 52KHz : LSI frequency tuner                                               */
  MDR_BKP_LSI_TRIM_50KHz        = 5,     /*!< 50KHz : LSI frequency tuner                                               */
  MDR_BKP_LSI_TRIM_49KHz        = 6,     /*!< 49KHz : LSI frequency tuner                                               */
  MDR_BKP_LSI_TRIM_45KHz        = 7,     /*!< 45KHz : LSI frequency tuner                                               */
  MDR_BKP_LSI_TRIM_44KHz        = 8,     /*!< 44KHz : LSI frequency tuner                                               */
  MDR_BKP_LSI_TRIM_42KHz        = 9,     /*!< 42KHz : LSI frequency tuner                                               */
  MDR_BKP_LSI_TRIM_40KHz        = 10,    /*!< 40KHz : LSI frequency tuner                                               */
  MDR_BKP_LSI_TRIM_39KHz        = 11,    /*!< 39KHz : LSI frequency tuner                                               */
  MDR_BKP_LSI_TRIM_37KHz        = 12,    /*!< 37KHz : LSI frequency tuner                                               */
  MDR_BKP_LSI_TRIM_36KHz        = 13,    /*!< 36KHz : LSI frequency tuner                                               */
  MDR_BKP_LSI_TRIM_35KHz        = 14,    /*!< 35KHz : LSI frequency tuner                                               */
  MDR_BKP_LSI_TRIM_33KHz        = 15,    /*!< 33KHz : LSI frequency tuner                                               */
  MDR_BKP_LSI_TRIM_32KHz        = 16,    /*!< 32KHz : LSI frequency tuner                                               */
} MDR_BKP_LSI_TRIM;

typedef enum {                           /*!< MDR_BKP_REG_0F_LSI_TRIM                                                   */
  MDR_BKP_HSI_TRIM_6M7Hz        = 0,     /*!< 69KHz : LSI frequency tuner                                               */
  MDR_BKP_HSI_TRIM_7M0Hz        = 5,     /*!< 65KHz : LSI frequency tuner                                               */
  MDR_BKP_HSI_TRIM_7M5Hz        = 10,    /*!< 60KHz : LSI frequency tuner                                               */
  MDR_BKP_HSI_TRIM_8M0Hz        = 23,    /*!< 58KHz : LSI frequency tuner                                               */
  MDR_BKP_HSI_TRIM_8M5Hz        = 32,    /*!< 52KHz : LSI frequency tuner                                               */
  MDR_BKP_HSI_TRIM_9M0Hz        = 38,    /*!< 50KHz : LSI frequency tuner                                               */
  MDR_BKP_HSI_TRIM_9M5Hz        = 44,    /*!< 49KHz : LSI frequency tuner                                               */
  MDR_BKP_HSI_TRIM_10M0KHz      = 49,    /*!< 45KHz : LSI frequency tuner                                               */
  MDR_BKP_HSI_TRIM_10M5Hz       = 53,     /*!< 44KHz : LSI frequency tuner                                               */
  MDR_BKP_HSI_TRIM_11M0Hz       = 57,     /*!< 42KHz : LSI frequency tuner                                               */
  MDR_BKP_HSI_TRIM_11M5Hz       = 60,    /*!< 40KHz : LSI frequency tuner                                               */
  MDR_BKP_HSI_TRIM_12M0Hz       = 63,    /*!< 39KHz : LSI frequency tuner                                               */
} MDR_BKP_HSI_TRIM;


typedef struct {
      __IOM MDR_OnOff         LSE_ON     : 1;          /*!< [0..0] LSE generator enable                                         */
      __IOM MDR_OnOff         LSE_BYP    : 1;          /*!< [1..1] LSE generator                                                */
      __IOM MDR_BKP_RTC_SEL   RTC_SEL    : 2;          /*!< [3..2] Select Clock for RTC                                         */
      __IOM MDR_OnOff         RTC_EN     : 1;          /*!< [4..4] RTC enable                                                   */
      __IOM uint32_t          RTC_CAL    : 8;          /*!< [12..5] RTC calibration                                             */
      __IM  MDR_OnOff         LSE_RDY    : 1;          /*!< [13..13] LSE frequency ready                                        */
      __IM  uint32_t                     : 1;
      __IOM MDR_OnOff         LSI_ON     : 1;          /*!< [15..15] LSI generator enable                                       */
      __IOM MDR_BKP_LSI_TRIM  LSI_TRIM   : 5;          /*!< [20..16] LSI frequency adjust                                       */
      __IM  MDR_OnOff         LSI_RDY    : 1;          /*!< [21..21] LSI frequency ready                                        */
      __IOM MDR_OnOff         HSI_ON     : 1;          /*!< [22..22] HSI generator enable                                       */
      __IOM MDR_OnOff         HSI_RDY    : 1;          /*!< [23..23] HSI frequency ready                                        */
      __IOM MDR_BKP_HSI_TRIM  HSI_TRIM   : 6;          /*!< [29..24] HSI frequency adjust                                       */
      __IOM MDR_OnOff         Standby    : 1;          /*!< [30..30] Standby sleep mode                                         */
      __IOM MDR_OnOff         RTC_RESET  : 1;          /*!< [31..31] Reset RTC bit                                              */
} MDR_BKP_REG_0F_Bits;

#define MDR_BKP_REG_0F_LSE_ON_Pos         (0UL)                     /*!< MDR_BKP REG_0F: LSE_ON (Bit 0)                        */
#define MDR_BKP_REG_0F_LSE_ON_Msk         (0x1UL)                   /*!< MDR_BKP REG_0F: LSE_ON (Bitfield-Mask: 0x01)          */
#define MDR_BKP_REG_0F_LSE_BYP_Pos        (1UL)                     /*!< MDR_BKP REG_0F: LSE_BYP (Bit 1)                       */
#define MDR_BKP_REG_0F_LSE_BYP_Msk        (0x2UL)                   /*!< MDR_BKP REG_0F: LSE_BYP (Bitfield-Mask: 0x01)         */
#define MDR_BKP_REG_0F_RTC_SEL_Pos        (2UL)                     /*!< MDR_BKP REG_0F: RTC_SEL (Bit 2)                       */
#define MDR_BKP_REG_0F_RTC_SEL_Msk        (0xcUL)                   /*!< MDR_BKP REG_0F: RTC_SEL (Bitfield-Mask: 0x03)         */
#define MDR_BKP_REG_0F_RTC_EN_Pos         (4UL)                     /*!< MDR_BKP REG_0F: RTC_EN (Bit 4)                        */
#define MDR_BKP_REG_0F_RTC_EN_Msk         (0x10UL)                  /*!< MDR_BKP REG_0F: RTC_EN (Bitfield-Mask: 0x01)          */
#define MDR_BKP_REG_0F_RTC_CAL_Pos        (5UL)                     /*!< MDR_BKP REG_0F: RTC_CAL (Bit 5)                       */
#define MDR_BKP_REG_0F_RTC_CAL_Msk        (0x1fe0UL)                /*!< MDR_BKP REG_0F: RTC_CAL (Bitfield-Mask: 0xff)         */
#define MDR_BKP_REG_0F_LSE_RDY_Pos        (13UL)                    /*!< MDR_BKP REG_0F: LSE_RDY (Bit 13)                      */
#define MDR_BKP_REG_0F_LSE_RDY_Msk        (0x2000UL)                /*!< MDR_BKP REG_0F: LSE_RDY (Bitfield-Mask: 0x01)         */
#define MDR_BKP_REG_0F_LSI_ON_Pos         (15UL)                    /*!< MDR_BKP REG_0F: LSI_ON (Bit 15)                       */
#define MDR_BKP_REG_0F_LSI_ON_Msk         (0x8000UL)                /*!< MDR_BKP REG_0F: LSI_ON (Bitfield-Mask: 0x01)          */
#define MDR_BKP_REG_0F_LSI_TRIM_Pos       (16UL)                    /*!< MDR_BKP REG_0F: LSI_TRIM (Bit 16)                     */
#define MDR_BKP_REG_0F_LSI_TRIM_Msk       (0x1f0000UL)              /*!< MDR_BKP REG_0F: LSI_TRIM (Bitfield-Mask: 0x1f)        */
#define MDR_BKP_REG_0F_LSI_RDY_Pos        (21UL)                    /*!< MDR_BKP REG_0F: LSI_RDY (Bit 21)                      */
#define MDR_BKP_REG_0F_LSI_RDY_Msk        (0x200000UL)              /*!< MDR_BKP REG_0F: LSI_RDY (Bitfield-Mask: 0x01)         */
#define MDR_BKP_REG_0F_HSI_ON_Pos         (22UL)                    /*!< MDR_BKP REG_0F: HSI_ON (Bit 22)                       */
#define MDR_BKP_REG_0F_HSI_ON_Msk         (0x400000UL)              /*!< MDR_BKP REG_0F: HSI_ON (Bitfield-Mask: 0x01)          */
#define MDR_BKP_REG_0F_HSI_RDY_Pos        (23UL)                    /*!< MDR_BKP REG_0F: HSI_RDY (Bit 23)                      */
#define MDR_BKP_REG_0F_HSI_RDY_Msk        (0x800000UL)              /*!< MDR_BKP REG_0F: HSI_RDY (Bitfield-Mask: 0x01)         */
#define MDR_BKP_REG_0F_HSI_TRIM_Pos       (24UL)                    /*!< MDR_BKP REG_0F: HSI_TRIM (Bit 24)                     */
#define MDR_BKP_REG_0F_HSI_TRIM_Msk       (0x3f000000UL)            /*!< MDR_BKP REG_0F: HSI_TRIM (Bitfield-Mask: 0x3f)        */
#define MDR_BKP_REG_0F_Standby_Pos        (30UL)                    /*!< MDR_BKP REG_0F: Standby (Bit 30)                      */
#define MDR_BKP_REG_0F_Standby_Msk        (0x40000000UL)            /*!< MDR_BKP REG_0F: Standby (Bitfield-Mask: 0x01)         */
#define MDR_BKP_REG_0F_RTC_RESET_Pos      (31UL)                    /*!< MDR_BKP REG_0F: RTC_RESET (Bit 31)                    */
#define MDR_BKP_REG_0F_RTC_RESET_Msk      (0x80000000UL)            /*!< MDR_BKP REG_0F: RTC_RESET (Bitfield-Mask: 0x01)       */

/* ========================================================  RTC_CS  ========================================================= */  
typedef struct {
      __IOM MDR_OnOff         OWF        : 1;          /*!< [0..0] CNT Overflow flag, clear by set 1                            */
      __IOM MDR_OnOff         SECF       : 1;          /*!< [1..1] DIV == PRL Event, clear by set 1                             */
      __IOM MDR_OnOff         ALRF       : 1;          /*!< [2..2] CNT == ALRM Event, clear by set 1                            */
      __IOM MDR_OnOff         OWF_IE     : 1;          /*!< [3..3] Enable IRQ by OWF                                            */
      __IOM MDR_OnOff         SECF_IE    : 1;          /*!< [4..4] Enable IRQ by SECF                                           */
      __IOM MDR_OnOff         ALRF_IE    : 1;          /*!< [5..5] Enable IRQ by ALRF                                           */
      __IOM MDR_OnOff         WEC_Busy   : 1;          /*!< [6..6] RTC Busy flag                                                */
      __I   uint32_t                     : 25;
} MDR_BKP_RTC_CS_Bits;

#define MDR_BKP_RTC_CS_OWF_Pos            (0UL)                     /*!< MDR_BKP RTC_CS: OWF (Bit 0)                           */
#define MDR_BKP_RTC_CS_OWF_Msk            (0x1UL)                   /*!< MDR_BKP RTC_CS: OWF (Bitfield-Mask: 0x01)             */
#define MDR_BKP_RTC_CS_SECF_Pos           (1UL)                     /*!< MDR_BKP RTC_CS: SECF (Bit 1)                          */
#define MDR_BKP_RTC_CS_SECF_Msk           (0x2UL)                   /*!< MDR_BKP RTC_CS: SECF (Bitfield-Mask: 0x01)            */
#define MDR_BKP_RTC_CS_ALRF_Pos           (2UL)                     /*!< MDR_BKP RTC_CS: ALRF (Bit 2)                          */
#define MDR_BKP_RTC_CS_ALRF_Msk           (0x4UL)                   /*!< MDR_BKP RTC_CS: ALRF (Bitfield-Mask: 0x01)            */
#define MDR_BKP_RTC_CS_OWF_IE_Pos         (3UL)                     /*!< MDR_BKP RTC_CS: OWF_IE (Bit 3)                        */
#define MDR_BKP_RTC_CS_OWF_IE_Msk         (0x8UL)                   /*!< MDR_BKP RTC_CS: OWF_IE (Bitfield-Mask: 0x01)          */
#define MDR_BKP_RTC_CS_SECF_IE_Pos        (4UL)                     /*!< MDR_BKP RTC_CS: SECF_IE (Bit 4)                       */
#define MDR_BKP_RTC_CS_SECF_IE_Msk        (0x10UL)                  /*!< MDR_BKP RTC_CS: SECF_IE (Bitfield-Mask: 0x01)         */
#define MDR_BKP_RTC_CS_ALRF_IE_Pos        (5UL)                     /*!< MDR_BKP RTC_CS: ALRF_IE (Bit 5)                       */
#define MDR_BKP_RTC_CS_ALRF_IE_Msk        (0x20UL)                  /*!< MDR_BKP RTC_CS: ALRF_IE (Bitfield-Mask: 0x01)         */
#define MDR_BKP_RTC_CS_WEC_Pos            (6UL)                     /*!< MDR_BKP RTC_CS: WEC (Bit 6)                           */
#define MDR_BKP_RTC_CS_WEC_Msk            (0x40UL)                  /*!< MDR_BKP RTC_CS: WEC (Bitfield-Mask: 0x01)             */

/* ========================================================  RTC_DIV  ======================================================== */
#define MDR_BKP_RTC_DIV_Value_Pos         (0UL)                     /*!< MDR_BKP RTC_DIV: Value (Bit 0)                        */
#define MDR_BKP_RTC_DIV_Value_Msk         (0xfffffUL)               /*!< MDR_BKP RTC_DIV: Value (Bitfield-Mask: 0xfffff)       */
/* ========================================================  RTC_PRL  ======================================================== */
#define MDR_BKP_RTC_PRL_Value_Pos         (0UL)                     /*!< MDR_BKP RTC_PRL: Value (Bit 0)                        */
#define MDR_BKP_RTC_PRL_Value_Msk         (0xfffffUL)               /*!< MDR_BKP RTC_PRL: Value (Bitfield-Mask: 0xfffff)       */
/* =======================================================  RTC_ALRM  ======================================================== */
#define MDR_BKP_RTC_ALRM_Value_Pos        (0UL)                     /*!< MDR_BKP RTC_ALRM: Value (Bit 0)                       */
#define MDR_BKP_RTC_ALRM_Value_Msk        (0xffffffffUL)            /*!< MDR_BKP RTC_ALRM: Value (Bitfield-Mask: 0xffffffff)   */



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

#endif  //_MDR_BKP_DEFS_H

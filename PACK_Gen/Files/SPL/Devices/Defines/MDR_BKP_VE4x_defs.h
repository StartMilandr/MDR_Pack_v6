#ifndef _MDR_BKP_VE4X_DEFS_H
#define _MDR_BKP_VE4X_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif


#include "MDR_BKP_defs.h"


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


/* ========================================================  REG_0E  ========================================================= */

//typedef enum {
//  MDR_LOWRI_le10MHz   = 0,                  /*!< 10MHz   : CPU Clock less then 10MHz  : +I ~ 300uA                             */
//  MDR_LOWRI_le100KHz  = 1,                  /*!< 200KHz  : CPU Clock less then 200KHz : +I ~ 6.6uA                             */
//  MDR_LOWRI_le500KMHz = 2,                  /*!< 500KHz  : CPU Clock less then 500KHz : +I ~ 20A                               */
//  MDR_LOWRI_le1MHz    = 3,                  /*!< 1MHz    : CPU Clock less then 1MHz   : +I ~ 80uA                              */
//  MDR_LOWRI_GensOff   = 4,                  /*!< GensOffz: Generators Off             : +I ~ 2uA                               */
//  MDR_LOWRI_le40MHz   = 5,                  /*!< 40MHz   : CPU Clock less then 40MHz  : +I ~ 900uA                             */
//  MDR_LOWRI_le80MHz   = 6,                  /*!< 80MHz   : CPU Clock less then 80MHz  : +I ~ 4.4mA                             */
//  MDR_LOWRI_gt80MHz   = 7,                  /*!< above_80MHz : CPU Clock above 10MHz  : +I ~ 19mA                              */
//} MDR_BKP_LOW_RI;

//typedef enum {
//  MDR_dDUcc_p0v1      = 0,                  /*!< +0.1  : DUcc += 0.1 V                                                      */
//  MDR_dDUcc_p0v06     = 1,                  /*!< +0.06 : DUcc += 0.06 V                                                     */
//  MDR_dDUcc_p0v04     = 2,                  /*!< +0.04 : DUcc += 0.04 V                                                     */
//  MDR_dDUcc_p0v01     = 3,                  /*!< +0.01 : DUcc += 0.01 V                                                     */
//  MDR_dDUcc_m0v01     = 4,                  /*!< -0.01 : DUcc -= 0.01 V                                                     */
//  MDR_dDUcc_m0v04     = 5,                  /*!< -0.04 : DUcc -= 0.04 V                                                     */
//  MDR_dDUcc_m0v06     = 6,                  /*!< -0.6  : DUcc -= 0.06 V                                                     */
//  MDR_dDUcc_m0v1      = 7                   /*!< -0.1  : DUcc -= 0.1 V                                                      */
//} MDR_BKP_dDUcc;

typedef enum {
  MDR_DUcc_1v8        = 0,                  /*!< 1.8 : DUcc = 1.8 V                                                         */
  MDR_DUcc_1v6        = 1,                  /*!< 1.6 : DUcc = 1.6 V                                                         */
  MDR_DUcc_1v4        = 2,                  /*!< 1.4 : DUcc = 1.4 V                                                         */
  MDR_DUcc_1v2        = 3                   /*!< 1.2 : DUcc = 1.2 V                                                         */
} MDR_BKP_DUcc;

typedef struct {
      __IOM MDR_BKP_LOW_RI    LOW        : 3;          /*!< [2..0] DUcc Freq control                                            */
      __IOM MDR_BKP_LOW_RI    SelectRI   : 3;          /*!< [5..3] DUcc extra I, should be equals to LOW field!                 */
      __IOM MDR_OnOff         Jtag_A     : 1;          /*!< [6..6] Enable Jtag_A interface                                      */
      __IOM MDR_OnOff         Jtag_B     : 1;          /*!< [7..7] Enable Jtag_B interface                                      */
      __IOM MDR_BKP_dDUcc     Trim_dDUcc : 3;          /*!< [10..8] Ducc adjust voltages                                        */
      __IOM uint32_t          FPOR       : 1;          /*!< [11..11] Power Reset Flag                                           */
      __IOM MDR_BKP_DUcc      Trim_DUcc  : 2;          /*!< [13..12] Select DUcc voltage                                        */
      __IOM MDR_OnOff         COVDET     : 1;          /*!< [14..14] Breaking access flag                                       */
      __IOM MDR_OnOff         I_LimEn    : 1;          /*!< [15..15] Enable I 150mA protection                                  */
      __IM  uint32_t                     : 16;
} MDR_BKP_REG_0E_Bits;


#define MDR_BKP_REG_0E_LOW_Pos            (0UL)                     /*!< MDR_BKP REG_0E: LOW (Bit 0)                           */
#define MDR_BKP_REG_0E_LOW_Msk            (0x7UL)                   /*!< MDR_BKP REG_0E: LOW (Bitfield-Mask: 0x07)             */
#define MDR_BKP_REG_0E_SelectRI_Pos       (3UL)                     /*!< MDR_BKP REG_0E: SelectRI (Bit 3)                      */
#define MDR_BKP_REG_0E_SelectRI_Msk       (0x38UL)                  /*!< MDR_BKP REG_0E: SelectRI (Bitfield-Mask: 0x07)        */
#define MDR_BKP_REG_0E_Jtag_A_Pos         (6UL)                     /*!< MDR_BKP REG_0E: Jtag_A (Bit 6)                        */
#define MDR_BKP_REG_0E_Jtag_A_Msk         (0x40UL)                  /*!< MDR_BKP REG_0E: Jtag_A (Bitfield-Mask: 0x01)          */
#define MDR_BKP_REG_0E_Jtag_B_Pos         (7UL)                     /*!< MDR_BKP REG_0E: Jtag_B (Bit 7)                        */
#define MDR_BKP_REG_0E_Jtag_B_Msk         (0x80UL)                  /*!< MDR_BKP REG_0E: Jtag_B (Bitfield-Mask: 0x01)          */
#define MDR_BKP_REG_0E_Trim_dDUcc_Pos     (8UL)                     /*!< MDR_BKP REG_0E: Trim_dDUcc (Bit 8)                    */
#define MDR_BKP_REG_0E_Trim_dDUcc_Msk     (0x700UL)                 /*!< MDR_BKP REG_0E: Trim_dDUcc (Bitfield-Mask: 0x07)      */
#define MDR_BKP_REG_0E_FPOR_Pos           (11UL)                    /*!< MDR_BKP REG_0E: FPOR (Bit 11)                         */
#define MDR_BKP_REG_0E_FPOR_Msk           (0x800UL)                 /*!< MDR_BKP REG_0E: FPOR (Bitfield-Mask: 0x01)            */
#define MDR_BKP_REG_0E_Trim_DUcc_Pos      (12UL)                    /*!< MDR_BKP REG_0E: Trim_DUcc (Bit 12)                    */
#define MDR_BKP_REG_0E_Trim_DUcc_Msk      (0x3000UL)                /*!< MDR_BKP REG_0E: Trim_DUcc (Bitfield-Mask: 0x03)       */
#define MDR_BKP_REG_0E_COVDET_Pos         (14UL)                    /*!< MDR_BKP REG_0E: COVDET (Bit 14)                       */
#define MDR_BKP_REG_0E_COVDET_Msk         (0x4000UL)                /*!< MDR_BKP REG_0E: COVDET (Bitfield-Mask: 0x01)          */
#define MDR_BKP_REG_0E_I_LimEn_Pos        (15UL)                    /*!< MDR_BKP REG_0E: I_LimEn (Bit 15)                      */
#define MDR_BKP_REG_0E_I_LimEn_Msk        (0x8000UL)                /*!< MDR_BKP REG_0E: I_LimEn (Bitfield-Mask: 0x01)         */


/* =============================================  BRK and RTC Block  ========================================================= */
typedef struct {                                /*!< (@ 0x400D8000) MDR_BKP Structure                                          */
  __IOM uint32_t  REG_xx[MDR_BKP_REG_XX_COUNT]; /*!< (@ 0x00000000) User backup registers                                      */

  union {
    __IOM uint32_t            REG_0E;           /*!< (@ 0x00000038) REG_OE Control register                                    */
    MDR_BKP_REG_0E_Bits       REG_0E_b;
  } ;
  union {
    __IOM uint32_t            REG_0F;           /*!< (@ 0x0000003C) REG_OF Control register                                    */
    MDR_BKP_REG_0F_Bits       REG_0F_b;
  } ;
  
  __IOM uint32_t  RTC_CNT;                      /*!< (@ 0x00000040) Count periods of PRL                                       */
  __IOM uint32_t  RTC_DIV;                      /*!< (@ 0x00000044) Counts RTC Clock to get PRL value                          */
  __IOM uint32_t  RTC_PRL;                      /*!< (@ 0x00000048) Period value for DIV counter                               */
  __IOM uint32_t  RTC_ALRM;                     /*!< (@ 0x0000004C) Event value for CNT counter                                */
  
  union {
    __IOM uint32_t            RTC_CS;           /*!< (@ 0x00000050) RTC Control and Status                                     */
    MDR_BKP_RTC_CS_Bits       RTC_CS_b;
  } ;
} MDR_BKP_Type;

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

#endif  //_MDR_BKP_VE4X_DEFS_H

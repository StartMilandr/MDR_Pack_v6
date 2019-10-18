#ifndef _MDR_OTP_DEFS_H
#define _MDR_OTP_DEFS_H

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

/* =========================================================================================================================== */
/* ================                          MDR_OTP common defs for VE8 and VE81                             ================ */
/* =========================================================================================================================== */

typedef enum {
  MDR_OTP_Delay_Forbiden    = 0,
  MDR_OTP_Delay_le_20MHz84  = 1,
  MDR_OTP_Delay_le_41MHz66  = 2,
  MDR_OTP_Delay_le_62MHz5   = 3,
  MDR_OTP_Delay_le_83MHz33  = 4,
  MDR_OTP_Delay_le_100MHz   = 5,
} MDR_OTP_Delay;

#define MDR_OTP_Delay_Min  MDR_OTP_Delay_le_20MHz84

typedef struct {
  __IOM MDR_OnOff SECC       : 1;            /*!< [0..0] SingleError flag                                                   */
  __IOM MDR_OnOff DECC       : 1;            /*!< [1..1] DoubleError flag                                                   */
  __IOM MDR_OnOff SECC_IE    : 1;            /*!< [2..2] SingleError IRQ Enable                                             */
  __IOM MDR_OnOff DECC_IE    : 1;            /*!< [3..3] DoubleError IRQ Enable                                             */
  __IOM MDR_OnOff FIX_SECC   : 1;            /*!< [4..4] Log SE to ECCADR, ECCDATA, ECCECC                                  */
  __IOM MDR_OnOff FIX_DECC   : 1;            /*!< [5..5] Log DE to ECCADR, ECCDATA, ECCECC                                  */
  __IOM MDR_OnOff CLR_SECNT  : 1;            /*!< [6..6] Clear SE counter                                                   */
  __IOM MDR_OnOff CLR_DECNT  : 1;            /*!< [7..7] Clear DE counter                                                   */
  __IOM uint32_t  ECC_DECNT  : 8;            /*!< [15..8] DE Events Counter                                                 */
  __IOM uint32_t  ECC_SECNT  : 16;           /*!< [31..16] SE Events Counter                                                */
} MDR_OTP_ECCCS_Bits;

#define MDR_OTP_ECCCS_SECC_Pos           (0UL)                     /*!< MDR_SRAM ECCCS: SECC (Bit 0)                          */
#define MDR_OTP_ECCCS_SECC_Msk           (0x1UL)                   /*!< MDR_SRAM ECCCS: SECC (Bitfield-Mask: 0x01)            */
#define MDR_OTP_ECCCS_DECC_Pos           (1UL)                     /*!< MDR_SRAM ECCCS: DECC (Bit 1)                          */
#define MDR_OTP_ECCCS_DECC_Msk           (0x2UL)                   /*!< MDR_SRAM ECCCS: DECC (Bitfield-Mask: 0x01)            */
#define MDR_OTP_ECCCS_SECC_IE_Pos        (2UL)                     /*!< MDR_SRAM ECCCS: SECC_IE (Bit 2)                       */
#define MDR_OTP_ECCCS_SECC_IE_Msk        (0x4UL)                   /*!< MDR_SRAM ECCCS: SECC_IE (Bitfield-Mask: 0x01)         */
#define MDR_OTP_ECCCS_DECC_IE_Pos        (3UL)                     /*!< MDR_SRAM ECCCS: DECC_IE (Bit 3)                       */
#define MDR_OTP_ECCCS_DECC_IE_Msk        (0x8UL)                   /*!< MDR_SRAM ECCCS: DECC_IE (Bitfield-Mask: 0x01)         */
#define MDR_OTP_ECCCS_FIX_SECC_Pos       (4UL)                     /*!< MDR_SRAM ECCCS: FIX_SECC (Bit 4)                      */
#define MDR_OTP_ECCCS_FIX_SECC_Msk       (0x10UL)                  /*!< MDR_SRAM ECCCS: FIX_SECC (Bitfield-Mask: 0x01)        */
#define MDR_OTP_ECCCS_FIX_DECC_Pos       (5UL)                     /*!< MDR_SRAM ECCCS: FIX_DECC (Bit 5)                      */
#define MDR_OTP_ECCCS_FIX_DECC_Msk       (0x20UL)                  /*!< MDR_SRAM ECCCS: FIX_DECC (Bitfield-Mask: 0x01)        */
#define MDR_OTP_ECCCS_CLR_SECNT_Pos      (6UL)                     /*!< MDR_SRAM ECCCS: CLR_SECNT (Bit 6)                     */
#define MDR_OTP_ECCCS_CLR_SECNT_Msk      (0x40UL)                  /*!< MDR_SRAM ECCCS: CLR_SECNT (Bitfield-Mask: 0x01)       */
#define MDR_OTP_ECCCS_CLR_DECNT_Pos      (7UL)                     /*!< MDR_SRAM ECCCS: CLR_DECNT (Bit 7)                     */
#define MDR_OTP_ECCCS_CLR_DECNT_Msk      (0x80UL)                  /*!< MDR_SRAM ECCCS: CLR_DECNT (Bitfield-Mask: 0x01)       */
#define MDR_OTP_ECCCS_ECC_DECNT_Pos      (8UL)                     /*!< MDR_SRAM ECCCS: ECC_DECNT (Bit 8)                     */
#define MDR_OTP_ECCCS_ECC_DECNT_Msk      (0xff00UL)                /*!< MDR_SRAM ECCCS: ECC_DECNT (Bitfield-Mask: 0xff)       */
#define MDR_OTP_ECCCS_ECC_SECNT_Pos      (16UL)                    /*!< MDR_SRAM ECCCS: ECC_SECNT (Bit 16)                    */
#define MDR_OTP_ECCCS_ECC_SECNT_Msk      (0xffff0000UL)            /*!< MDR_SRAM ECCCS: ECC_SECNT (Bitfield-Mask: 0xffff)     */


typedef enum {                             /*!< MDR_OTP_TEST_TUNING_TE                                                    */
  MDR_OTP_TUNING_TE_Off           = 0,     /*!< Off : Normal Operation                                                    */
  MDR_OTP_TUNING_TE_Test_1        = 1,     /*!< Test_1 : Test Mode 1                                                      */
  MDR_OTP_TUNING_TE_Test_2        = 2,     /*!< Test_2 : Test Mode 2                                                      */
  MDR_OTP_TUNING_TE_Test_3        = 3,     /*!< Test_3 : Test Mode 3                                                      */
} MDR_OTP_TUNING_TE;


typedef enum {                          /*!< MDR_OTP_TEST_TUNING_TIME_TUNING                                           */
  MDR_OTP_TUNING_OTP_Time_HardMax = 0,  /*!< Time_HardMax : Read Timeout                                            */
  MDR_OTP_TUNING_OTP_Time_Hard2   = 1,  /*!< Time_Hard2 : Read Timeout                                                */
  MDR_OTP_TUNING_OTP_Time_Hard1   = 2,  /*!< Time_Hard1 : Read Timeout                                                */
  MDR_OTP_TUNING_OTP_Time_Norm    = 3,  /*!< Time_Norm : Read Timeout                                                  */
  MDR_OTP_TUNING_OTP_Time_Easy1   = 4,  /*!< Time_Easy1 : Read Timeout                                                */
  MDR_OTP_TUNING_OTP_Time_Easy2   = 5,  /*!< Time_Easy2 : Read Timeout                                                */
  MDR_OTP_TUNING_OTP_Time_Easy3   = 6,  /*!< Time_Easy3 : Read Timeout                                                */
  MDR_OTP_TUNING_OTP_Time_EasyMax = 7,  /*!< Time_EasyMax : Read Timeout                                            */
} MDR_OTP_TUNING_OTP_Time;

typedef enum {                          /*!< MDR_OTP_TEST_TUNING_REPL_TUNING                                           */
  MDR_OTP_TUNING_OTP_Repl_EasyMax = 0,  /*!< Repl_EasyMax : Read Resistance                                         */
  MDR_OTP_TUNING_OTP_Repl_Easy1   = 1,  /*!< Repl_Easy1 : Read Resistance                                             */
  MDR_OTP_TUNING_OTP_Repl_Norm    = 2,  /*!< Repl_Norm : Read Resistance                                               */
  MDR_OTP_TUNING_OTP_Repl_Hard1   = 3,  /*!< Repl_Hard1 : Read Resistance                                             */
  MDR_OTP_TUNING_OTP_Repl_Hard2   = 4,  /*!< Repl_Hard2 : Read Resistance                                             */
  MDR_OTP_TUNING_OTP_Repl_Hard3   = 5,  /*!< Repl_Hard3 : Read Resistance                                             */
  MDR_OTP_TUNING_OTP_Repl_Hard4   = 6,  /*!< Repl_Hard4 : Read Resistance                                             */
  MDR_OTP_TUNING_OTP_Repl_Hard5   = 7,  /*!< Repl_Hard5 : Read Resistance                                             */
  MDR_OTP_TUNING_OTP_Repl_Hard6   = 8,  /*!< Repl_Hard6 : Read Resistance                                             */
  MDR_OTP_TUNING_OTP_Repl_Hard7   = 9,  /*!< Repl_Hard7 : Read Resistance                                             */
  MDR_OTP_TUNING_OTP_Repl_Hard8   = 10, /*!< Repl_Hard8 : Read Resistance                                            */
  MDR_OTP_TUNING_OTP_Repl_Hard9   = 11, /*!< Repl_Hard9 : Read Resistance                                            */
  MDR_OTP_TUNING_OTP_Repl_Hard10  = 12, /*!< Repl_Hard10 : Read Resistance                                          */
  MDR_OTP_TUNING_OTP_Repl_Hard11  = 13, /*!< Repl_Hard11 : Read Resistance                                          */
  MDR_OTP_TUNING_OTP_Repl_Hard12  = 14, /*!< Repl_Hard12 : Read Resistance                                          */
  MDR_OTP_TUNING_OTP_Repl_HardMax = 15, /*!< Repl_HardMax : Read Resistance                                        */
} MDR_OTP_TUNING_OTP_Repl;



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

#endif  //_MDR_OTP_DEFS_H

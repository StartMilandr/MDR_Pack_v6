#ifndef _MDR_OTP_VE81_DEFS_H
#define _MDR_OTP_VE81_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif


#include <MDR_OTP_defs.h>
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
/* ================                          MDR_OTPSRAM for VE81                                             ================ */
/* =========================================================================================================================== */

//-----------------------------  CNTR   ---------------------------------
typedef struct {
  __IOM MDR_OTP_Delay   WAITCYCL   : 4;            /*!< [3..0] OTP Access Delay                                                   */
  __IOM MDR_OnOff       REG_ACCESS : 1;            /*!< [4..4] OTP Access Delay                                                   */
  __IOM uint32_t        CLK        : 1;            /*!< [5..5] Rise front to write or read                                        */
  __IM  uint32_t                   : 1;
  __IOM MDR_OnOff       OE         : 1;            /*!< [7..7] OE for SRAM                                                        */
  __IM  uint32_t                   : 1;
  __IOM MDR_OnOff       WE_x00     : 1;            /*!< [9..9] WE for SRAM addr section 0x00                                      */
  __IOM MDR_OnOff       WE_x04     : 1;            /*!< [10..10] WE for SRAM addr section 0x04                                    */
  __IOM MDR_OnOff       WE_x08     : 1;            /*!< [11..11] WE for SRAM addr section 0x08                                    */
  __IOM MDR_OnOff       WE_x0C     : 1;            /*!< [12..12] WE for SRAM addr section 0x0C                                    */
  __IOM MDR_OnOff       WE_ECC     : 1;            /*!< [13..13] WE for SRAM addr ECC                                             */
  __IOM MDR_OnOff       CEN        : 1;            /*!< [14..14] CE for SRAM                                                      */
  __IM  uint32_t                   : 1;
  __IOM uint32_t        WECC       : 8;            /*!< [23..16] ECC for write with WDATA                                         */
  __IOM uint32_t        RECC       : 8;            /*!< [31..24] ECC after read with RDATA                                        */  
} MDR_OTP_CNTR_Bits;

//#define MDR_OTP_CNTR_WAITCYCL_Pos        (0UL)                     /*!< MDR_SRAM CNTR: WAITCYCL (Bit 0)                       */
//#define MDR_OTP_CNTR_WAITCYCL_Msk        (0xfUL)                   /*!< MDR_SRAM CNTR: WAITCYCL (Bitfield-Mask: 0x0f)         */
//#define MDR_OTP_CNTR_REG_ACCESS_Pos      (4UL)                     /*!< MDR_SRAM CNTR: REG_ACCESS (Bit 4)                     */
//#define MDR_OTP_CNTR_REG_ACCESS_Msk      (0x10UL)                  /*!< MDR_SRAM CNTR: REG_ACCESS (Bitfield-Mask: 0x01)       */
//#define MDR_OTP_CNTR_CLK_Pos             (5UL)                     /*!< MDR_SRAM CNTR: CLK (Bit 5)                            */
//#define MDR_OTP_CNTR_CLK_Msk             (0x20UL)                  /*!< MDR_SRAM CNTR: CLK (Bitfield-Mask: 0x01)              */
//#define MDR_OTP_CNTR_OE_Pos              (7UL)                     /*!< MDR_SRAM CNTR: OE (Bit 7)                             */
//#define MDR_OTP_CNTR_OE_Msk              (0x80UL)                  /*!< MDR_SRAM CNTR: OE (Bitfield-Mask: 0x01)               */
//#define MDR_OTP_CNTR_WE_x00_Pos          (8UL)                     /*!< MDR_SRAM CNTR: WE_x00 (Bit 8)                         */
//#define MDR_OTP_CNTR_WE_x00_Msk          (0x100UL)                 /*!< MDR_SRAM CNTR: WE_x00 (Bitfield-Mask: 0x01)           */
//#define MDR_OTP_CNTR_WE_x04_Pos          (9UL)                     /*!< MDR_SRAM CNTR: WE_x04 (Bit 9)                         */
//#define MDR_OTP_CNTR_WE_x04_Msk          (0x200UL)                 /*!< MDR_SRAM CNTR: WE_x04 (Bitfield-Mask: 0x01)           */
//#define MDR_OTP_CNTR_WE_x08_Pos          (10UL)                    /*!< MDR_SRAM CNTR: WE_x08 (Bit 10)                        */
//#define MDR_OTP_CNTR_WE_x08_Msk          (0x400UL)                 /*!< MDR_SRAM CNTR: WE_x08 (Bitfield-Mask: 0x01)           */
//#define MDR_OTP_CNTR_WE_x0C_Pos          (11UL)                    /*!< MDR_SRAM CNTR: WE_x0C (Bit 11)                        */
//#define MDR_OTP_CNTR_WE_x0C_Msk          (0x800UL)                 /*!< MDR_SRAM CNTR: WE_x0C (Bitfield-Mask: 0x01)           */
//#define MDR_OTP_CNTR_WE_ECC_Pos          (12UL)                    /*!< MDR_SRAM CNTR: WE_ECC (Bit 12)                        */
//#define MDR_OTP_CNTR_WE_ECC_Msk          (0x1000UL)                /*!< MDR_SRAM CNTR: WE_ECC (Bitfield-Mask: 0x01)           */
//#define MDR_OTP_CNTR_WECC_Pos            (16UL)                    /*!< MDR_SRAM CNTR: WECC (Bit 16)                          */
//#define MDR_OTP_CNTR_WECC_Msk            (0xff0000UL)              /*!< MDR_SRAM CNTR: WECC (Bitfield-Mask: 0xff)             */
//#define MDR_OTP_CNTR_RECC_Pos            (24UL)                    /*!< MDR_SRAM CNTR: RECC (Bit 24)                          */
//#define MDR_OTP_CNTR_RECC_Msk            (0xff000000UL)            /*!< MDR_SRAM CNTR: RECC (Bitfield-Mask: 0xff)             */


#define MDR_OTP_CNTR_WAITCYCL_Pos        (0UL)                     /*!< MDR_SRAM CNTR: WAITCYCL (Bit 0)                       */
#define MDR_OTP_CNTR_WAITCYCL_Msk        (0xfUL)                   /*!< MDR_SRAM CNTR: WAITCYCL (Bitfield-Mask: 0x0f)         */
#define MDR_OTP_CNTR_REG_ACCESS_Pos      (4UL)                     /*!< MDR_SRAM CNTR: REG_ACCESS (Bit 4)                     */
#define MDR_OTP_CNTR_REG_ACCESS_Msk      (0x10UL)                  /*!< MDR_SRAM CNTR: REG_ACCESS (Bitfield-Mask: 0x01)       */
#define MDR_OTP_CNTR_CLK_Pos             (5UL)                     /*!< MDR_SRAM CNTR: CLK (Bit 5)                            */
#define MDR_OTP_CNTR_CLK_Msk             (0x20UL)                  /*!< MDR_SRAM CNTR: CLK (Bitfield-Mask: 0x01)              */
#define MDR_OTP_CNTR_OE_Pos              (7UL)                     /*!< MDR_SRAM CNTR: OE (Bit 7)                             */
#define MDR_OTP_CNTR_OE_Msk              (0x80UL)                  /*!< MDR_SRAM CNTR: OE (Bitfield-Mask: 0x01)               */
#define MDR_OTP_CNTR_WE_x00_Pos          (9UL)                     /*!< MDR_SRAM CNTR: WE_x00 (Bit 9)                         */
#define MDR_OTP_CNTR_WE_x00_Msk          (0x200UL)                 /*!< MDR_SRAM CNTR: WE_x00 (Bitfield-Mask: 0x01)           */
#define MDR_OTP_CNTR_WE_x04_Pos          (10UL)                    /*!< MDR_SRAM CNTR: WE_x04 (Bit 10)                        */
#define MDR_OTP_CNTR_WE_x04_Msk          (0x400UL)                 /*!< MDR_SRAM CNTR: WE_x04 (Bitfield-Mask: 0x01)           */
#define MDR_OTP_CNTR_WE_x08_Pos          (11UL)                    /*!< MDR_SRAM CNTR: WE_x08 (Bit 11)                        */
#define MDR_OTP_CNTR_WE_x08_Msk          (0x800UL)                 /*!< MDR_SRAM CNTR: WE_x08 (Bitfield-Mask: 0x01)           */
#define MDR_OTP_CNTR_WE_x0C_Pos          (12UL)                    /*!< MDR_SRAM CNTR: WE_x0C (Bit 12)                        */
#define MDR_OTP_CNTR_WE_x0C_Msk          (0x1000UL)                /*!< MDR_SRAM CNTR: WE_x0C (Bitfield-Mask: 0x01)           */
#define MDR_OTP_CNTR_WE_ECC_Pos          (13UL)                    /*!< MDR_SRAM CNTR: WE_ECC (Bit 13)                        */
#define MDR_OTP_CNTR_WE_ECC_Msk          (0x2000UL)                /*!< MDR_SRAM CNTR: WE_ECC (Bitfield-Mask: 0x01)           */
#define MDR_OTP_CNTR_CEN_Pos             (14UL)                    /*!< MDR_SRAM CNTR: CEN (Bit 14)                           */
#define MDR_OTP_CNTR_CEN_Msk             (0x4000UL)                /*!< MDR_SRAM CNTR: CEN (Bitfield-Mask: 0x01)              */
#define MDR_OTP_CNTR_WECC_Pos            (16UL)                    /*!< MDR_SRAM CNTR: WECC (Bit 16)                          */
#define MDR_OTP_CNTR_WECC_Msk            (0xff0000UL)              /*!< MDR_SRAM CNTR: WECC (Bitfield-Mask: 0xff)             */
#define MDR_OTP_CNTR_RECC_Pos            (24UL)                    /*!< MDR_SRAM CNTR: RECC (Bit 24)                          */
#define MDR_OTP_CNTR_RECC_Msk            (0xff000000UL)            /*!< MDR_SRAM CNTR: RECC (Bitfield-Mask: 0xff)             */


#define MDR_OTP_CNTR_WAITCYCL_SRAM_Min  1
#define MDR_OTP_CNTR_WE_ALL_Pos         MDR_OTP_CNTR_WE_x00_Pos
#define MDR_OTP_CNTR_WE_ALL_Msk        (MDR_OTP_CNTR_WE_x00_Msk | MDR_OTP_CNTR_WE_x04_Msk | MDR_OTP_CNTR_WE_x08_Msk | MDR_OTP_CNTR_WE_x0C_Msk | MDR_OTP_CNTR_WE_ECC_Msk)


//-----------------------------  TEST_TUNING   ---------------------------------
typedef enum {                            /*!< MDR_SRAM_TEST_TUNING_SRAM_TIMEOUT                                    */
  MDR_OTP_TUNING_SRAM_Time_HardMax  = 0,  /*!< Time_HardMax : SRAM Read Timeout                                     */
  MDR_OTP_TUNING_SRAM_Time_Hard2    = 1,  /*!< Time_Hard2 : SRAM Read Timeout                                       */
  MDR_OTP_TUNING_SRAM_Time_Norm     = 2,  /*!< Time_Norm : SRAM Read Timeout                                        */
  MDR_OTP_TUNING_SRAM_Time_Easy1    = 3,  /*!< Time_Easy1 : SRAM Read Timeout                                       */
  MDR_OTP_TUNING_SRAM_Time_Easy2    = 4,  /*!< Time_Easy2 : SRAM Read Timeout                                       */
  MDR_OTP_TUNING_SRAM_Time_Easy3    = 5,  /*!< Time_Easy3 : SRAM Read Timeout                                       */
  MDR_OTP_TUNING_SRAM_Time_Easy4    = 6,  /*!< Time_Easy4 : SRAM Read Timeout                                       */
  MDR_OTP_TUNING_SRAM_Time_EasyMax  = 7,  /*!< Time_EasyMax : SRAM Read Timeout                                     */
} MDR_OTP_TUNING_SRAM_Time;

typedef __PACKED_STRUCT {
  __IOM MDR_OTP_TUNING_SRAM_Time  SRAM_TIME : 3;           /*!< [2..0] Timeouts to read SRAM                        */
  __IM  uint32_t                            : 1;
  __IOM MDR_OTP_TUNING_TE         TEST_SEL  : 2;           /*!< [5..4] Select Test Mode                             */
  __IM  uint32_t                            : 2;
  __IOM MDR_OTP_TUNING_OTP_Time   OTP_TIME  : 3;           /*!< [10..8] Timeouts to read bit                        */
  __IM  uint32_t                            : 5;
  __IOM MDR_OTP_TUNING_OTP_Repl   OTP_REPL  : 4;           /*!< [19..16] Bit Hi_Level Read Resistance               */
  __IM  uint32_t                            : 12;  
} MDR_OTP_TUNING_Bits;

#define MDR_OTP_TUNING_SRAM_TIME_Pos    (0UL)                  /*!< MDR_SRAM TEST_TUNING: SRAM_TIMEOUT (Bit 0)            */
#define MDR_OTP_TUNING_SRAM_TIME_Msk    (0x7UL)                /*!< MDR_SRAM TEST_TUNING: SRAM_TIMEOUT (Bitfield-Mask: 0x07) */
#define MDR_OTP_TUNING_TE_Pos           (4UL)                  /*!< MDR_SRAM TEST_TUNING: TE (Bit 4)                      */
#define MDR_OTP_TUNING_TE_Msk           (0x30UL)               /*!< MDR_SRAM TEST_TUNING: TE (Bitfield-Mask: 0x03)        */
#define MDR_OTP_TUNING_OTP_TIME_Pos     (8UL)                  /*!< MDR_SRAM TEST_TUNING: TIME_TUNING (Bit 8)             */
#define MDR_OTP_TUNING_OTP_TIME_Msk     (0x700UL)              /*!< MDR_SRAM TEST_TUNING: TIME_TUNING (Bitfield-Mask: 0x07) */
#define MDR_OTP_TUNING_OTP_REPL_Pos     (16UL)                 /*!< MDR_SRAM TEST_TUNING: REPL_TUNING (Bit 16)            */
#define MDR_OTP_TUNING_OTP_REPL_Msk     (0xf0000UL)            /*!< MDR_SRAM TEST_TUNING: REPL_TUNING (Bitfield-Mask: 0x0f) */

//  SRAM_TIME values
#define MDR_OTP_TUNING_SRAM_Time_HardMax_Msk  ((uint32_t)MDR_OTP_TUNING_SRAM_Time_HardMax << MDR_OTP_TUNING_SRAM_TIME_Pos)
#define MDR_OTP_TUNING_SRAM_Time_Hard2_Msk    ((uint32_t)MDR_OTP_TUNING_SRAM_Time_Hard2   << MDR_OTP_TUNING_SRAM_TIME_Pos)
#define MDR_OTP_TUNING_SRAM_Time_Norm_Msk     ((uint32_t)MDR_OTP_TUNING_SRAM_Time_Norm    << MDR_OTP_TUNING_SRAM_TIME_Pos)
#define MDR_OTP_TUNING_SRAM_Time_Easy1_Msk    ((uint32_t)MDR_OTP_TUNING_SRAM_Time_Easy1   << MDR_OTP_TUNING_SRAM_TIME_Pos)
#define MDR_OTP_TUNING_SRAM_Time_Easy2_Msk    ((uint32_t)MDR_OTP_TUNING_SRAM_Time_Easy2   << MDR_OTP_TUNING_SRAM_TIME_Pos)
#define MDR_OTP_TUNING_SRAM_Time_Easy3_Msk    ((uint32_t)MDR_OTP_TUNING_SRAM_Time_Easy3   << MDR_OTP_TUNING_SRAM_TIME_Pos)
#define MDR_OTP_TUNING_SRAM_Time_Easy4_Msk    ((uint32_t)MDR_OTP_TUNING_SRAM_Time_Easy4   << MDR_OTP_TUNING_SRAM_TIME_Pos)
#define MDR_OTP_TUNING_SRAM_Time_EasyMax_Msk  ((uint32_t)MDR_OTP_TUNING_SRAM_Time_EasyMax << MDR_OTP_TUNING_SRAM_TIME_Pos)

//  OTP_TIME values
#define MDR_OTP_TUNING_OTP_Time_HardMax_Msk   ((uint32_t)MDR_OTP_TUNING_OTP_Time_HardMax  << MDR_OTP_TUNING_SRAM_TIME_Pos)
#define MDR_OTP_TUNING_OTP_Time_Hard2_Msk     ((uint32_t)MDR_OTP_TUNING_OTP_Time_Hard2    << MDR_OTP_TUNING_SRAM_TIME_Pos)
#define MDR_OTP_TUNING_OTP_Time_Hard1_Msk     ((uint32_t)MDR_OTP_TUNING_OTP_Time_Hard1    << MDR_OTP_TUNING_SRAM_TIME_Pos)
#define MDR_OTP_TUNING_OTP_Time_Norm_Msk      ((uint32_t)MDR_OTP_TUNING_OTP_Time_Norm     << MDR_OTP_TUNING_SRAM_TIME_Pos)
#define MDR_OTP_TUNING_OTP_Time_Easy1_Msk     ((uint32_t)MDR_OTP_TUNING_OTP_Time_Easy1    << MDR_OTP_TUNING_SRAM_TIME_Pos)
#define MDR_OTP_TUNING_OTP_Time_Easy2_Msk     ((uint32_t)MDR_OTP_TUNING_OTP_Time_Easy2    << MDR_OTP_TUNING_SRAM_TIME_Pos)
#define MDR_OTP_TUNING_OTP_Time_Easy3_Msk     ((uint32_t)MDR_OTP_TUNING_OTP_Time_Easy3    << MDR_OTP_TUNING_SRAM_TIME_Pos)
#define MDR_OTP_TUNING_OTP_Time_EasyMax_Msk   ((uint32_t)MDR_OTP_TUNING_OTP_Time_EasyMax  << MDR_OTP_TUNING_SRAM_TIME_Pos)

//  OTP_REPL values
#define MDR_OTP_TUNING_OTP_Repl_EasyMax_Msk   ((uint32_t)MDR_OTP_TUNING_OTP_Repl_EasyMax  << MDR_OTP_TUNING_OTP_REPL_Pos)
#define MDR_OTP_TUNING_OTP_Repl_Easy1_Msk     ((uint32_t)MDR_OTP_TUNING_OTP_Repl_Easy1    << MDR_OTP_TUNING_OTP_REPL_Pos)
#define MDR_OTP_TUNING_OTP_Repl_Norm_Msk      ((uint32_t)MDR_OTP_TUNING_OTP_Repl_Norm     << MDR_OTP_TUNING_OTP_REPL_Pos)
#define MDR_OTP_TUNING_OTP_Repl_Hard1_Msk     ((uint32_t)MDR_OTP_TUNING_OTP_Repl_Hard1    << MDR_OTP_TUNING_OTP_REPL_Pos)
#define MDR_OTP_TUNING_OTP_Repl_Hard2_Msk     ((uint32_t)MDR_OTP_TUNING_OTP_Repl_Hard2    << MDR_OTP_TUNING_OTP_REPL_Pos)
#define MDR_OTP_TUNING_OTP_Repl_Hard3_Msk     ((uint32_t)MDR_OTP_TUNING_OTP_Repl_Hard3    << MDR_OTP_TUNING_OTP_REPL_Pos)
#define MDR_OTP_TUNING_OTP_Repl_Hard4_Msk     ((uint32_t)MDR_OTP_TUNING_OTP_Repl_Hard4    << MDR_OTP_TUNING_OTP_REPL_Pos)
#define MDR_OTP_TUNING_OTP_Repl_Hard5_Msk     ((uint32_t)MDR_OTP_TUNING_OTP_Repl_Hard5    << MDR_OTP_TUNING_OTP_REPL_Pos)
#define MDR_OTP_TUNING_OTP_Repl_Hard6_Msk     ((uint32_t)MDR_OTP_TUNING_OTP_Repl_Hard6    << MDR_OTP_TUNING_OTP_REPL_Pos)
#define MDR_OTP_TUNING_OTP_Repl_Hard7_Msk     ((uint32_t)MDR_OTP_TUNING_OTP_Repl_Hard7    << MDR_OTP_TUNING_OTP_REPL_Pos)
#define MDR_OTP_TUNING_OTP_Repl_Hard8_Msk     ((uint32_t)MDR_OTP_TUNING_OTP_Repl_Hard8    << MDR_OTP_TUNING_OTP_REPL_Pos)
#define MDR_OTP_TUNING_OTP_Repl_Hard9_Msk     ((uint32_t)MDR_OTP_TUNING_OTP_Repl_Hard9    << MDR_OTP_TUNING_OTP_REPL_Pos)
#define MDR_OTP_TUNING_OTP_Repl_Hard10_Msk    ((uint32_t)MDR_OTP_TUNING_OTP_Repl_Hard10   << MDR_OTP_TUNING_OTP_REPL_Pos)
#define MDR_OTP_TUNING_OTP_Repl_Hard11_Msk    ((uint32_t)MDR_OTP_TUNING_OTP_Repl_Hard11   << MDR_OTP_TUNING_OTP_REPL_Pos)
#define MDR_OTP_TUNING_OTP_Repl_Hard12_Msk    ((uint32_t)MDR_OTP_TUNING_OTP_Repl_Hard12   << MDR_OTP_TUNING_OTP_REPL_Pos)
#define MDR_OTP_TUNING_OTP_Repl_HardMax_Msk   ((uint32_t)MDR_OTP_TUNING_OTP_Repl_HardMax  << MDR_OTP_TUNING_OTP_REPL_Pos)


/* ====================================== OTP Struct  =================================================== */

typedef struct {                                /*!< (@ 0x40060000) MDR_SRAM Structure                                         */
  __IOM uint32_t                KEY;            /*!< (@ 0x00000000) Unlock block register                                      */  
  union {
    __IOM uint32_t              CNTR;           /*!< (@ 0x00000004) Control register                                           */
    __IOM MDR_OTP_CNTR_Bits     CNTR_b;
  } ;
  __IOM uint32_t                ADR;            /*!< (@ 0x00000008) Access address                                             */
  __IOM uint32_t                WDATA;          /*!< (@ 0x0000000C) Data to write                                              */
  __IOM uint32_t                RDATA;          /*!< (@ 0x00000010) Read out data                                              */  
  union {
    __IOM uint32_t              ECCCS;          /*!< (@ 0x00000014) Control-Status Register                                    */
    __IOM MDR_OTP_ECCCS_Bits    ECCCS_b;
  } ;
  __IOM uint32_t                ECCADR;         /*!< (@ 0x00000018) Last error address without correction                      */
  __IOM uint32_t                ECCDATA;        /*!< (@ 0x0000001C) Last error data without correction                         */
  __IOM uint32_t                ECCECC;         /*!< (@ 0x00000020) Last error ECC without correction                          */
  union {
    __IOM uint32_t              TUNING;         /*!< (@ 0x00000024) Access Memory Tuning register                              */
    __IOM MDR_OTP_TUNING_Bits   TUNING_b;

  } ;
} MDR_OTP_Type;                                /*!< Size = 40 (0x28)                                                          */


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

#endif  //_MDR_OTP_VE81_DEFS_H

#ifndef _MDR_OTP_VE8_DEFS_H
#define _MDR_OTP_VE8_DEFS_H


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
  __IOM MDR_OnOff       SE         : 1;            /*!< [5..5] OTP Read enable                                                    */
  __IOM MDR_OnOff       PE         : 1;            /*!< [6..6] OTP Programming enable                                             */
  __IM  uint32_t                   : 9;
  __IOM uint32_t        WECC       : 8;            /*!< [23..16] ECC for write with WDATA                                         */
  __IOM uint32_t        RECC       : 8;            /*!< [31..24] ECC after read with RDATA                                        */    
} MDR_OTP_CNTR_Bits;

#define MDR_OTP_CNTR_WAITCYCL_Pos         (0UL)                     /*!< MDR_OTP CNTR: WAITCYCL (Bit 0)                        */
#define MDR_OTP_CNTR_WAITCYCL_Msk         (0xfUL)                   /*!< MDR_OTP CNTR: WAITCYCL (Bitfield-Mask: 0x0f)          */
#define MDR_OTP_CNTR_REG_ACCESS_Pos       (4UL)                     /*!< MDR_OTP CNTR: REG_ACCESS (Bit 4)                      */
#define MDR_OTP_CNTR_REG_ACCESS_Msk       (0x10UL)                  /*!< MDR_OTP CNTR: REG_ACCESS (Bitfield-Mask: 0x01)        */
#define MDR_OTP_CNTR_SE_Pos               (5UL)                     /*!< MDR_OTP CNTR: SE (Bit 5)                              */
#define MDR_OTP_CNTR_SE_Msk               (0x20UL)                  /*!< MDR_OTP CNTR: SE (Bitfield-Mask: 0x01)                */
#define MDR_OTP_CNTR_PE_Pos               (6UL)                     /*!< MDR_OTP CNTR: PE (Bit 6)                              */
#define MDR_OTP_CNTR_PE_Msk               (0x40UL)                  /*!< MDR_OTP CNTR: PE (Bitfield-Mask: 0x01)                */
#define MDR_OTP_CNTR_WECC_Pos             (16UL)                    /*!< MDR_OTP CNTR: WECC (Bit 16)                           */
#define MDR_OTP_CNTR_WECC_Msk             (0xff0000UL)              /*!< MDR_OTP CNTR: WECC (Bitfield-Mask: 0xff)              */
#define MDR_OTP_CNTR_RECC_Pos             (24UL)                    /*!< MDR_OTP CNTR: RECC (Bit 24)                           */
#define MDR_OTP_CNTR_RECC_Msk             (0xff000000UL)            /*!< MDR_OTP CNTR: RECC (Bitfield-Mask: 0xff)              */


//-----------------------------  TEST_TUNING   ---------------------------------
typedef struct {
  __IM  uint32_t                            : 3;
  __IOM MDR_OTP_TUNING_TE         TEST_SEL  : 2;            /*!< [4..3] Select Test Mode                                  */
  __IM  uint32_t                            : 3;
  __IOM MDR_OTP_TUNING_OTP_Time   OTP_TIME  : 3;           /*!< [10..8] Timeouts to read bit                              */
  __IM  uint32_t                            : 5;
  __IOM MDR_OTP_TUNING_OTP_Repl   OTP_REPL  : 4;           /*!< [19..16] Bit Hi_Level Read Resistance                     */
} MDR_OTP_TUNING_Bits;

#define MDR_OTP_TUNING_TE_Pos           (3UL)                   /*!< MDR_OTP TEST_TUNING: TE (Bit 3)                       */
#define MDR_OTP_TUNING_TE_Msk           (0x18UL)                /*!< MDR_OTP TEST_TUNING: TE (Bitfield-Mask: 0x03)         */
#define MDR_OTP_TUNING_OTP_TIME_Pos     (8UL)                   /*!< MDR_OTP TEST_TUNING: TIME_TUNING (Bit 8)              */
#define MDR_OTP_TUNING_OTP_TIME_Msk     (0x700UL)               /*!< MDR_OTP TEST_TUNING: TIME_TUNING (Bitfield-Mask: 0x07) */
#define MDR_OTP_TUNING_OTP_REPL_Pos     (16UL)                  /*!< MDR_OTP TEST_TUNING: REPL_TUNING (Bit 16)             */
#define MDR_OTP_TUNING_OTP_REPL_Msk     (0xf0000UL)             /*!< MDR_OTP TEST_TUNING: REPL_TUNING (Bitfield-Mask: 0x0f) */


//  OTP_TIME values
#define MDR_OTP_TUNING_OTP_Time_HardMax_Msk   ((uint32_t)MDR_OTP_TUNING_OTP_Time_HardMax  << MDR_OTP_TUNING_OTP_TIME_Pos)
#define MDR_OTP_TUNING_OTP_Time_Hard2_Msk     ((uint32_t)MDR_OTP_TUNING_OTP_Time_Hard2    << MDR_OTP_TUNING_OTP_TIME_Pos)
#define MDR_OTP_TUNING_OTP_Time_Hard1_Msk     ((uint32_t)MDR_OTP_TUNING_OTP_Time_Hard1    << MDR_OTP_TUNING_OTP_TIME_Pos)
#define MDR_OTP_TUNING_OTP_Time_Norm_Msk      ((uint32_t)MDR_OTP_TUNING_OTP_Time_Norm     << MDR_OTP_TUNING_OTP_TIME_Pos)
#define MDR_OTP_TUNING_OTP_Time_Easy1_Msk     ((uint32_t)MDR_OTP_TUNING_OTP_Time_Easy1    << MDR_OTP_TUNING_OTP_TIME_Pos)
#define MDR_OTP_TUNING_OTP_Time_Easy2_Msk     ((uint32_t)MDR_OTP_TUNING_OTP_Time_Easy2    << MDR_OTP_TUNING_OTP_TIME_Pos)
#define MDR_OTP_TUNING_OTP_Time_Easy3_Msk     ((uint32_t)MDR_OTP_TUNING_OTP_Time_Easy3    << MDR_OTP_TUNING_OTP_TIME_Pos)
#define MDR_OTP_TUNING_OTP_Time_EasyMax_Msk   ((uint32_t)MDR_OTP_TUNING_OTP_Time_EasyMax  << MDR_OTP_TUNING_OTP_TIME_Pos)

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

#endif  //_MDR_OTP_VE8_DEFS_H

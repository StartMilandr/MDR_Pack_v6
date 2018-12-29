#ifndef _MDR_IWDT_DEFS_H
#define _MDR_IWDT_DEFS_H

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

/* ====================================== KR - Key Register  =================================================== */
typedef   struct {
  __OM  uint32_t KEY        : 16;           /*!< [15..0] Enable, start and reload control                                  */
  __IM  uint32_t            : 16;
} MDR_IWDT_KR_Bits;

#define IWDT_KEY_ACCESS_ENA   0x5555UL
#define IWDT_KEY_START        0xCCCCUL
#define IWDT_KEY_RELOAD       0xAAAAUL

#define MDR_IWDT_KR_KEY_Pos               (0UL)                     /*!< MDR_IWDT KR: KEY (Bit 0)                              */
#define MDR_IWDT_KR_KEY_Msk               (0xffffUL)                /*!< MDR_IWDT KR: KEY (Bitfield-Mask: 0xffff)              */


/* ====================================== PR - Prescaler Register  =================================================== */
typedef enum {                            /*!< MDR_IWDT_PR_PR                                                            */
  IWDT_PR_div4                   = 0,     /*!< div4 : LSI div 4                                                          */
  IWDT_PR_div8                   = 1,     /*!< div8 : LSI div 8                                                          */
  IWDT_PR_div16                  = 2,     /*!< div16 : LSI div 16                                                        */
  IWDT_PR_div32                  = 3,     /*!< div32 : LSI div 32                                                        */
  IWDT_PR_div64                  = 4,     /*!< div64 : LSI div 64                                                        */
  IWDT_PR_div128                 = 5,     /*!< div128 : LSI div 128                                                      */
  IWDT_PR_div256                 = 6,     /*!< div256 : LSI div 256                                                      */
  IWDT_PR_div256_1               = 7,     /*!< div256_1 : LSI div 256                                                    */
} MDR_IWDT_PR;

typedef struct {
  __IOM MDR_IWDT_PR PR         : 3;            /*!< [2..0] LSI Clock DIV                                                      */
  __IM  uint32_t               : 29;
} MDR_IWDT_PR_Bits;

#define MDR_IWDT_PR_PR_Pos                (0UL)                     /*!< MDR_IWDT PR: PR (Bit 0)                               */
#define MDR_IWDT_PR_PR_Msk                (0x7UL)                   /*!< MDR_IWDT PR: PR (Bitfield-Mask: 0x07)                 */


/* ====================================== Reload Register (Period)  =================================================== */
typedef struct {
  __IOM uint32_t PRL          : 12;           /*!< [11..0] Timer Period Value                                                */
  __IM  uint32_t              : 20;
} MDR_IWDT_RLR_Bits;
  
#define MDR_IWDT_PRL_PRL_Pos              (0UL)                     /*!< MDR_IWDT PRL: PRL (Bit 0)                             */
#define MDR_IWDT_PRL_PRL_Msk              (0xfffUL)                 /*!< MDR_IWDT PRL: PRL (Bitfield-Mask: 0xfff)              */


/* ====================================== Status Register  =================================================== */
typedef struct {
  __IM  MDR_OnOff PVU          : 1;            /*!< [0..0] PR busy                                                            */
  __IM  MDR_OnOff RVU          : 1;            /*!< [1..1] PRL busy                                                           */
  __IM  uint32_t               : 30;
} MDR_IWDT_SR_Bits;

#define MDR_IWDT_SR_PVU_Pos               (0UL)                     /*!< MDR_IWDT SR: PVU (Bit 0)                              */
#define MDR_IWDT_SR_PVU_Msk               (0x1UL)                   /*!< MDR_IWDT SR: PVU (Bitfield-Mask: 0x01)                */
#define MDR_IWDT_SR_RVU_Pos               (1UL)                     /*!< MDR_IWDT SR: RVU (Bit 1)                              */
#define MDR_IWDT_SR_RVU_Msk               (0x2UL)                   /*!< MDR_IWDT SR: RVU (Bitfield-Mask: 0x01)                */


/* ====================================== IWDT Struct  =================================================== */
typedef struct {                                /*!< (@ 0x40068000) MDR_IWDT Structure                                         */
  union {
    __OM  uint32_t    KR;                          /*!< (@ 0x00000000) Key register                                               */
    MDR_IWDT_KR_Bits  KR_b;
  } ;
  union {
    __IOM uint32_t    PR;                       /*!< (@ 0x00000004) Clock Prescaler register                                   */
    MDR_IWDT_PR_Bits  PR_b;
  } ;
  union {
    __IOM uint32_t    RLR;                         /*!< (@ 0x00000008) Reload Period Register                                     */
    MDR_IWDT_RLR_Bits RLR_b;
  } ;
  union {
    __IM  uint32_t    SR;                          /*!< (@ 0x0000000C) Status Regster                                             */
    MDR_IWDT_SR_Bits  SR_b;
  } ;
} MDR_IWDT_Type;                                /*!< Size = 16 (0x10)                                                          */


/* ==========================================================  PRL  ========================================================== */
/* ==========================================================  SR  =========================================================== */
/* ================================================  MDR_IWDT SR PVU [0..0]  ================================================= */
typedef enum {                                  /*!< MDR_IWDT_SR_PVU                                                           */
  MDR_IWDT_PVU___Ready                 = 0,     /*!< Ready : PR ready for write                                                */
  MDR_IWDT_PVU___Busy                  = 1,     /*!< Busy : PR busy                                                            */
} MDR_IWDT_PVU___Enum;

/* ================================================  MDR_IWDT SR RVU [1..1]  ================================================= */
typedef enum {                                  /*!< MDR_IWDT_SR_RVU                                                           */
  MDR_IWDT_RVU___Ready                 = 0,     /*!< Ready : PRL ready for write                                               */
  MDR_IWDT_RVU___Busy                  = 1,     /*!< Busy : PRL busy                                                           */
} MDR_IWDT_RVU___Enum;






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

#endif  //_MDR_IWDT_DEFS_H

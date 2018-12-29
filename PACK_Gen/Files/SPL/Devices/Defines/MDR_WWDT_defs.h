#ifndef _MDR_WWDT_DEFS_H
#define _MDR_WWDT_DEFS_H

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

/* ====================================== CR - Control Register  =================================================== */
typedef struct {
      __IOM uint32_t  T          : 7;            /*!< [6..0] Counter                                                            */
      __IOM MDR_OnOff WDGA       : 1;            /*!< [7..7] Enable                                                             */
      __IM  uint32_t             : 24;
} MDR_WWDT_CR_Bits;

#define MDR_WWDT_CR_T_Pos                 (0UL)                     /*!< MDR_WWDT CR: T (Bit 0)                                */
#define MDR_WWDT_CR_T_Msk                 (0x7fUL)                  /*!< MDR_WWDT CR: T (Bitfield-Mask: 0x7f)                  */
#define MDR_WWDT_CR_WDGA_Pos              (7UL)                     /*!< MDR_WWDT CR: WDGA (Bit 7)                             */
#define MDR_WWDT_CR_WDGA_Msk              (0x80UL)                  /*!< MDR_WWDT CR: WDGA (Bitfield-Mask: 0x01)               */


/* ====================================== CFR - Config Register  =================================================== */
typedef enum {                                  /*!< MDR_WWDT_CFR_WGTB                                                         */
  WWDT_CFR_WGTB_div1                  = 0,     /*!< div1 : CLK = LSI/4096/1                                                   */
  WWDT_CFR_WGTB_div2                  = 1,     /*!< div2 : CLK = LSI/4096/2                                                   */
  WWDT_CFR_WGTB_div4                  = 2,     /*!< div4 : CLK = LSI/4096/4                                                   */
  WWDT_CFR_WGTB_div8                  = 3,     /*!< div8 : CLK = LSI/4096/8                                                   */
} MDR_WWDT_CFR_WGTB;

typedef struct {
  __IOM uint32_t           W    : 7;            /*!< [6..0] Window value                                                       */
  __IOM MDR_WWDT_CFR_WGTB  WGTB : 2;            /*!< [8..7] Clock Divider                                                      */
  __IOM MDR_OnOff          EWI  : 1;            /*!< [9..9] Early Window Interrupt                                             */
  __IM  uint32_t                : 22;
} MDR_WWDT_CFR_Bits;

#define MDR_WWDT_CFR_W_Pos                (0UL)                     /*!< MDR_WWDT CFR: W (Bit 0)                               */
#define MDR_WWDT_CFR_W_Msk                (0x7fUL)                  /*!< MDR_WWDT CFR: W (Bitfield-Mask: 0x7f)                 */
#define MDR_WWDT_CFR_WGTB_Pos             (7UL)                     /*!< MDR_WWDT CFR: WGTB (Bit 7)                            */
#define MDR_WWDT_CFR_WGTB_Msk             (0x180UL)                 /*!< MDR_WWDT CFR: WGTB (Bitfield-Mask: 0x03)              */
#define MDR_WWDT_CFR_EWI_Pos              (9UL)                     /*!< MDR_WWDT CFR: EWI (Bit 9)                             */
#define MDR_WWDT_CFR_EWI_Msk              (0x200UL)                 /*!< MDR_WWDT CFR: EWI (Bitfield-Mask: 0x01)               */


/* ====================================== SR - Status Register  =================================================== */
typedef struct {
  __IOM uint32_t EWIF         : 1;            /*!< [0..0] Early Window Flag                                                  */
  __IM  uint32_t              : 31;
} MDR_WWDT_SR_Bits;

#define MDR_WWDT_SR_EWIF_Pos              (0UL)                     /*!< MDR_WWDT SR: EWIF (Bit 0)                             */
#define MDR_WWDT_SR_EWIF_Msk              (0x1UL)                   /*!< MDR_WWDT SR: EWIF (Bitfield-Mask: 0x01)               */


/* ====================================== WWDT Struct  =================================================== */

typedef struct {  
  union {
    __IOM   uint32_t    CR;                          /*!< (@ 0x00000000) WWDT Control register                                      */    
    MDR_WWDT_CR_Bits    CR_b;
  } ;  
  union {
    __IOM uint32_t      CFR;                         /*!< (@ 0x00000004) WWDT Config register                                       */
    MDR_WWDT_CFR_Bits   CFR_b;
  } ;  
  union {
    __IOM uint32_t      SR;                          /*!< (@ 0x00000008) WWDT Status register                                       */
    MDR_WWDT_SR_Bits    SR_b;
  } ;
} MDR_WWDT_Type;                                    /*!< Size = 12 (0xc)                                                           */


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

#endif  //_MDR_WWDT_DEFS_H

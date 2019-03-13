#ifndef _MDR_TIMER_CFGREGS_H
#define _MDR_TIMER_CFGREGS_H


#ifdef __cplusplus
extern "C" {
#endif

#include <MDR_Timer_Defs.h>


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


//==================    CfgRegs - выборка только конфигурационных регистров ===============

typedef struct {
  MDR_TIM_FLTR      CHFLTR      : 4;            /*!< [3..0] Front hold to set Event                                            */
  MDR_TIM_EventCAP  CHSEL       : 2;            /*!< [5..4] Event to capture in CCR                                            */
  MDR_TIM_CapPSC    CHPSC       : 2;            /*!< [7..6] Capture event decimation                                           */
  MDR_OnOff         OCCE        : 1;            /*!< [8..8] ETR pin Enable                                                     */
  MDR_TIM_PWM_Ref   OCCM        : 3;            /*!< [11..9] PWM Generate modes                                                */
  MDR_OnOff         BRK_En      : 1;            /*!< [12..12] Clear Ref by BRK                                                 */
  MDR_OnOff         ETR_En      : 1;            /*!< [13..13] Clear Ref by BRK                                                 */
  MDR_OnOff         WR_CCR_Busy : 1;            /*!< [14..14] Can write to CCRx                                                */
  MDR_TIM_CH_MODE   CAP_nPWM    : 1;            /*!< [15..15] CAP or PWM Mode                                                  */
} MDR_Timer_CHx_CNTRL_Bits;

typedef struct {
  MDR_TIM_SelOutEn  SelOE      : 2;       /*!< [1..0] Select Pin Output Enable                                           */
  MDR_TIM_SelOut    SelO       : 2;       /*!< [3..2] Select Output Signal                                               */
  MDR_OnOff         Inv        : 1;       /*!< [4..4] Invert Output Signal                                               */
  uint32_t                     : 3;
  MDR_TIM_SelOutEn  NSelOE     : 2;       /*!< [9..8] Select Pin Output Enable                                           */
  MDR_TIM_SelOut    NSelO      : 2;       /*!< [11..10] Select Output Signal                                             */
  MDR_OnOff         NInv       : 1;       /*!< [12..12] Invert Output Signal                                             */
} MDR_Timer_CHx_CNTRL1_Bits;

typedef struct {
  MDR_TIM_DTG_Presc DTG   : 4;            /*!< [3..0] DTG Prescaller                                                     */
  MDR_TIM_DTG_CLK   EDTS  : 1;            /*!< [4..4] DTG Clock Select                                                   */
  uint32_t                : 3;
  uint32_t          DTGx  : 8;            /*!< [15..8] DTGx scale, Delay = DTGx*(DTG + 1)                                */
} MDR_Timer_CHx_DTG_Bits;

typedef struct {
  MDR_TIM_EventCAP1   CHSel1 : 2;            /*!< [1..0] Event to capture in CCR1                                     */
  MDR_OnOff           CCR1_En: 1;            /*!< [2..2] Enable CCR1                                                  */
  MDR_TIM_CCR_Update  CCRRLD : 1;            /*!< [3..3] CCR Reload Mode                                              */
} MDR_Timer_CHx_CNTRL2_Bits;

typedef struct {
  union {
    uint32_t                    CH_CNTRL;
    MDR_Timer_CHx_CNTRL_Bits    CH_CNTRL_b;
  } ;
  union {
    uint32_t                    CH_CNTRL1;
    MDR_Timer_CHx_CNTRL1_Bits   CH_CNTRL1_b;
  } ;
  union {
    uint32_t                    CH_DTG;
    MDR_Timer_CHx_DTG_Bits      CH_DTG_b;
  } ;
  union {
    uint32_t                    CH_CNTRL2;
    MDR_Timer_CHx_CNTRL2_Bits   CH_CNTRL2_b;
  } ;
} MDR_TIMER_CH_CfgRegs;



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


#endif  // _MDR_TIMER_CFGREGS_H


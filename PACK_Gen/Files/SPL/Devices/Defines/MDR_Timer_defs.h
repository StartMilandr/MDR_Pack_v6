#ifndef _MDR_TIMER_DEFS_H
#define _MDR_TIMER_DEFS_H

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

typedef enum {
  TIM_Channel1 = 0,
  TIM_Channel2 = 1,
  TIM_Channel3 = 2,
  TIM_Channel4 = 3,
} MDR_Timer_Channel;


/* ========================================  PSG ======================================================= */
typedef struct {
  __IOM uint32_t Value      : 16;       /*!< [15..0] Counter Value                                                     */
  __IM  uint32_t            : 16;
} MDR_TIM_PSG_Bits;


/* ========================================  CNTRL ======================================================= */
typedef enum {
  TIM_DIR_UP    = 0,
  TIM_DIR_DOWM  = 1
} MDR_TIM_Dir;

typedef enum {                    /*!< MDR_TIMER1_CNTRL_FDTS                                       */
  TIM_FDTS_TimClk_div1   = 0,     /*!< TIM_CLK_div1 : TIM_Clock to FDTS scale                                    */
  TIM_FDTS_TimClk_div2   = 1,     /*!< TIM_CLK_div2 : TIM_Clock to FDTS scale                                    */
  TIM_FDTS_TimClk_div4   = 2,     /*!< TIM_CLK_div4 : TIM_Clock to FDTS scale                                    */
  TIM_FDTS_TimClk_div8   = 3,     /*!< TIM_CLK_div8 : TIM_Clock to FDTS scale                                    */
} MDR_TIM_FDTS;


/* ========================================  CHx_CNTRL - CAP and PWM Settings ==================================== */

typedef enum {                      /*!< MDR_TIMER1_CH1_CNTRL_CHFLTR                                               */
  MDR_TIM_FLTR_TIM_CLK  = 0,        /*!< TIM_CLK : Filter Value                                                    */
  MDR_TIM_FLTR_2_TIM_CLK = 1,       /*!< 2_TIM_CLK : Filter Value                                                  */
  MDR_TIM_FLTR_4_TIM_CLK = 2,       /*!< 4_TIM_CLK : Filter Value                                                  */
  MDR_TIM_FLTR_8_TIM_CLK = 3,       /*!< 8_TIM_CLK : Filter Value                                                  */
  MDR_TIM_FLTR_6_FDTS_div2 = 4,     /*!< 6_FDTS_div2 : Filter Value                                                */
  MDR_TIM_FLTR_8_FDTS_div2 = 5,     /*!< 8_FDTS_div2 : Filter Value                                                */
  MDR_TIM_FLTR_6_FDTS_div4 = 6,     /*!< 6_FDTS_div4 : Filter Value                                                */
  MDR_TIM_FLTR_8_FDTS_div4 = 7,     /*!< 8_FDTS_div4 : Filter Value                                                */
  MDR_TIM_FLTR_6_FDTS_div8 = 8,     /*!< 6_FDTS_div8 : Filter Value                                                */
  MDR_TIM_FLTR_8_FDTS_div8 = 9,     /*!< 8_FDTS_div8 : Filter Value                                                */
  MDR_TIM_FLTR_5_FDTS_div16 = 10,   /*!< 5_FDTS_div16 : Filter Value                                               */
  MDR_TIM_FLTR_6_FDTS_div16 = 11,   /*!< 6_FDTS_div16 : Filter Value                                               */
  MDR_TIM_FLTR_8_FDTS_div16 = 12,   /*!< 8_FDTS_div16 : Filter Value                                               */
  MDR_TIM_FLTR_5_FDTS_div32 = 13,   /*!< 5_FDTS_div32 : Filter Value                                               */
  MDR_TIM_FLTR_6_FDTS_div32 = 14,   /*!< 6_FDTS_div32 : Filter Value                                               */
  MDR_TIM_FLTR_8_FDTS_div32 = 15,   /*!< 8_FDTS_div32 : Filter Value                                               */
} MDR_TIM_FLTR;

typedef enum {                        /*!< MDR_TIMER1_CH1_CNTRL_CHSEL                                              */
  MDR_TIM_CAP_RiseOnPin  = 0,         /*!< Rise_Pin : Capture Event Select                                         */
  MDR_TIM_CAP_FallOnPin  = 1,         /*!< Fall_Pin : Capture Event Select                                         */
  MDR_TIM_CAP_RiseOnNextCh     = 2,   /*!< Rise_NextCH : Capture Event Select                                      */
  MDR_TIM_CAP_RiseOnNextNextCh = 3,   /*!< Fall_NextCH : Capture Event Select                                      */
} MDR_TIM_EventCAP;

typedef enum {                        /*!< MDR_TIMER1_CH1_CNTRL_CHSEL                                              */
  MDR_TIM_CAP1_RiseOnPin  = 0,        /*!< Rise_Pin : Capture Event Select                                         */
  MDR_TIM_CAP1_FallOnPin  = 1,        /*!< Fall_Pin : Capture Event Select                                         */
  MDR_TIM_CAP1_FallOnNextCh     = 2,  /*!< Fall_NextCH : Capture Event Select                                      */
  MDR_TIM_CAP1_FallOnNextNextCh = 3,  /*!< Fall_NextNextCH : Capture Event Select                                      */
} MDR_TIM_EventCAP1;

typedef enum {                  /*!< MDR_TIMER1_CH1_CNTRL_CHPSC                                                */
  MDR_TIM_CapPSC_div1 = 0,      /*!< EveryEvent  : Pass event for capture                                      */
  MDR_TIM_CapPSC_div2 = 1,      /*!< Events_div2 : Pass event for capture                                      */
  MDR_TIM_CapPSC_div4 = 2,      /*!< Events_div4 : Pass event for capture                                      */
  MDR_TIM_CapPSC_div8 = 3,      /*!< Events_div8 : Pass event for capture                                      */
} MDR_TIM_CapPSC;

typedef enum {                      /*!< MDR_TIMER1_CH1_CNTRL_OCCM                    */
  MDR_TIM_PWM_Ref0          = 0,    /*!< Ref=0                                        */
  MDR_TIM_PWM_Ref1_eqCCR   = 1,     /*!< if (CNT == [CCR, CCR1]) Ref=1, else Ref=1    */
  MDR_TIM_PWM_Ref0_eqCCR   = 2,     /*!< if (CNT == [CCR, CCR1]) Ref=0, else Ref=0    */
  MDR_TIM_PWM_RefTgl_eqCCR = 3,     /*!< if (CNT == [CCR, CCR1]) Ref=!Ref, start Ref = 1  */
  MDR_TIM_PWM_Ref_0         = 4,    /*!< Ref=0                                        */
  MDR_TIM_PWM_Ref1          = 5,    /*!< Ref=1                                        */
                                    //  for CHxCONTROL2.CCR1_EN = false
  MDR_TIM_PWM_Ref1_ltCCR    = 6,    /*!< if (CNT < CCR) Ref=1, else Ref=0             */
  MDR_TIM_PWM_Ref0_ltCCR    = 7,    /*!< if (CNT < CCR) Ref=0, else Ref=0             */
} MDR_TIM_PWM_Ref;

//  for CHxCONTROL2.CCR1_EN = true
//  if (CNT in [CCR..CCR1]) Ref=!Dir, else Ref=Dir
#define  MDR_TIM_PWM_RefNDir_inCCRs   MDR_TIM_PWM_Ref1_ltCCR
//  if (CNT in [CCR..CCR1]) Ref=Dir, else Ref=!Dir
#define  MDR_TIM_PWM_RefDIR_inCCRs    MDR_TIM_PWM_Ref0_ltCCR

typedef enum {
  TIM_CH_PWM = 0,
  TIM_CH_CAR = 1
} MDR_TIM_CH_MODE;

typedef struct {
  __IOM MDR_TIM_FLTR      CHFLTR      : 4;            /*!< [3..0] Front hold to set Event                                            */
  __IOM MDR_TIM_EventCAP  CHSEL       : 2;            /*!< [5..4] Event to capture in CCR                                            */
  __IOM MDR_TIM_CapPSC    CHPSC       : 2;            /*!< [7..6] Capture event decimation                                           */
  __IOM MDR_OnOff         OCCE        : 1;            /*!< [8..8] ETR pin Enable                                                     */
  __IOM MDR_TIM_PWM_Ref   OCCM        : 3;            /*!< [11..9] PWM Generate modes                                                */
  __IOM MDR_OnOff         BRK_En      : 1;            /*!< [12..12] Clear Ref by BRK                                                 */
  __IOM MDR_OnOff         ETR_En      : 1;            /*!< [13..13] Clear Ref by BRK                                                 */
  __IOM MDR_OnOff         WR_CCR_Busy : 1;            /*!< [14..14] Can write to CCRx                                                */
  __IOM MDR_TIM_CH_MODE   CAP_nPWM    : 1;            /*!< [15..15] CAP or PWM Mode                                                  */
} MDR_TIM_CHx_CNTRL_Bits;

#define MDR_TIM_CHx_CNTRL_CHFLTR_Pos   (0UL)                     /*!< MDR_TIMER1 CH4_CNTRL: CHFLTR (Bit 0)                  */
#define MDR_TIM_CHx_CNTRL_CHFLTR_Msk   (0xfUL)                   /*!< MDR_TIMER1 CH4_CNTRL: CHFLTR (Bitfield-Mask: 0x0f)    */
#define MDR_TIM_CHx_CNTRL_CHSEL_Pos    (4UL)                     /*!< MDR_TIMER1 CH4_CNTRL: CHSEL (Bit 4)                   */
#define MDR_TIM_CHx_CNTRL_CHSEL_Msk    (0x30UL)                  /*!< MDR_TIMER1 CH4_CNTRL: CHSEL (Bitfield-Mask: 0x03)     */
#define MDR_TIM_CHx_CNTRL_CHPSC_Pos    (6UL)                     /*!< MDR_TIMER1 CH4_CNTRL: CHPSC (Bit 6)                   */
#define MDR_TIM_CHx_CNTRL_CHPSC_Msk    (0xc0UL)                  /*!< MDR_TIMER1 CH4_CNTRL: CHPSC (Bitfield-Mask: 0x03)     */
#define MDR_TIM_CHx_CNTRL_OCCE_Pos     (8UL)                     /*!< MDR_TIMER1 CH4_CNTRL: OCCE (Bit 8)                    */
#define MDR_TIM_CHx_CNTRL_OCCE_Msk     (0x100UL)                 /*!< MDR_TIMER1 CH4_CNTRL: OCCE (Bitfield-Mask: 0x01)      */
#define MDR_TIM_CHx_CNTRL_OCCM_Pos     (9UL)                     /*!< MDR_TIMER1 CH4_CNTRL: OCCM (Bit 9)                    */
#define MDR_TIM_CHx_CNTRL_OCCM_Msk     (0xe00UL)                 /*!< MDR_TIMER1 CH4_CNTRL: OCCM (Bitfield-Mask: 0x07)      */
#define MDR_TIM_CHx_CNTRL_BRKEN_Pos    (12UL)                    /*!< MDR_TIMER1 CH4_CNTRL: BRKEN (Bit 12)                  */
#define MDR_TIM_CHx_CNTRL_BRKEN_Msk    (0x1000UL)                /*!< MDR_TIMER1 CH4_CNTRL: BRKEN (Bitfield-Mask: 0x01)     */
#define MDR_TIM_CHx_CNTRL_ETREN_Pos    (13UL)                    /*!< MDR_TIMER1 CH4_CNTRL: ETREN (Bit 13)                  */
#define MDR_TIM_CHx_CNTRL_ETREN_Msk    (0x2000UL)                /*!< MDR_TIMER1 CH4_CNTRL: ETREN (Bitfield-Mask: 0x01)     */
#define MDR_TIM_CHx_CNTRL_WR_CMPL_Pos  (14UL)                    /*!< MDR_TIMER1 CH4_CNTRL: WR_CMPL (Bit 14)                */
#define MDR_TIM_CHx_CNTRL_WR_CMPL_Msk  (0x4000UL)                /*!< MDR_TIMER1 CH4_CNTRL: WR_CMPL (Bitfield-Mask: 0x01)   */
#define MDR_TIM_CHx_CNTRL_CAP_nPWM_Pos (15UL)                    /*!< MDR_TIMER1 CH4_CNTRL: CAP_nPWM (Bit 15)               */
#define MDR_TIM_CHx_CNTRL_CAP_nPWM_Msk (0x8000UL)                /*!< MDR_TIMER1 CH4_CNTRL: CAP_nPWM (Bitfield-Mask: 0x01)  */

#define MDR_TIM_CHx_CNTRL_CAP_Mode      MDR_TIM_CHx_CNTRL_CAP_nPWM_Msk
#define MDR_TIM_CHx_CNTRL_PWM_Mode      0x0UL


/* ========================================  CHx_CNTRL1 - GPIO PIN Driver  =================================================== */
typedef enum {                                  /*!< MDR_TIMER1_CH1_CNTRL1_SelOE                                               */
  MDR_TIM_SelOE_PinIN       = 0,                /*!< IN : Pin IN                                                               */
  MDR_TIM_SelOE_PinOUT      = 1,                /*!< OUT : Pin OUT                                                             */
  MDR_TIM_SelOE_PinIO_byRef = 2,                /*!< IO_byRef : Pin IN or OUT by Ref signal                                    */
  MDR_TIM_SelOE_PinIO_byDTG = 3,                /*!< IO_byDTG : Pin IN or OUT by DTG signal                                    */
} MDR_TIM_SelOutEn;

typedef enum {                                  /*!< MDR_TIMER1_CH1_CNTRL1_SelO                                                */
  MDR_TIM_SelO_Low       = 0,                   /*!< Low : Outputs const GND                                                   */
  MDR_TIM_SelO_High      = 1,                   /*!< High : Outputs const Ucc                                                  */
  MDR_TIM_SelO_Ref       = 2,                   /*!< Ref : Ref PWM signal                                                      */
  MDR_TIM_SelO_DTG       = 3,                   /*!< DTG : DTG PWM signal                                                      */
} MDR_TIM_SelOut;

typedef struct {
  __IOM MDR_TIM_SelOutEn  SelOE      : 2;       /*!< [1..0] Select Pin Output Enable                                           */
  __IOM MDR_TIM_SelOut    SelO       : 2;       /*!< [3..2] Select Output Signal                                               */
  __IOM MDR_OnOff         Inv        : 1;       /*!< [4..4] Invert Output Signal                                               */
  __IM  uint32_t                     : 3;
  __IOM MDR_TIM_SelOutEn  NSelOE     : 2;       /*!< [9..8] Select Pin Output Enable                                           */
  __IOM MDR_TIM_SelOut    NSelO      : 2;       /*!< [11..10] Select Output Signal                                             */
  __IOM MDR_OnOff         NInv       : 1;       /*!< [12..12] Invert Output Signal                                             */
  __IM  uint32_t                     : 19;
} MDR_TIM_CHx_CNTRL1_Bits;

#define MDR_TIM_CHx_CNTRL1_SelOE_Pos   (0UL)                     /*!< MDR_TIMER1 CH1_CNTRL1: SelOE (Bit 0)                  */
#define MDR_TIM_CHx_CNTRL1_SelOE_Msk   (0x3UL)                   /*!< MDR_TIMER1 CH1_CNTRL1: SelOE (Bitfield-Mask: 0x03)    */
#define MDR_TIM_CHx_CNTRL1_SelO_Pos    (2UL)                     /*!< MDR_TIMER1 CH1_CNTRL1: SelO (Bit 2)                   */
#define MDR_TIM_CHx_CNTRL1_SelO_Msk    (0xcUL)                   /*!< MDR_TIMER1 CH1_CNTRL1: SelO (Bitfield-Mask: 0x03)     */
#define MDR_TIM_CHx_CNTRL1_Inv_Pos     (4UL)                     /*!< MDR_TIMER1 CH1_CNTRL1: Inv (Bit 4)                    */
#define MDR_TIM_CHx_CNTRL1_Inv_Msk     (0x10UL)                  /*!< MDR_TIMER1 CH1_CNTRL1: Inv (Bitfield-Mask: 0x01)      */
#define MDR_TIM_CHx_CNTRL1_NSelOE_Pos  (8UL)                     /*!< MDR_TIMER1 CH1_CNTRL1: NSelOE (Bit 8)                 */
#define MDR_TIM_CHx_CNTRL1_NSelOE_Msk  (0x300UL)                 /*!< MDR_TIMER1 CH1_CNTRL1: NSelOE (Bitfield-Mask: 0x03)   */
#define MDR_TIM_CHx_CNTRL1_NSelO_Pos   (10UL)                    /*!< MDR_TIMER1 CH1_CNTRL1: NSelO (Bit 10)                 */
#define MDR_TIM_CHx_CNTRL1_NSelO_Msk   (0xc00UL)                 /*!< MDR_TIMER1 CH1_CNTRL1: NSelO (Bitfield-Mask: 0x03)    */
#define MDR_TIM_CHx_CNTRL1_NInv_Pos    (12UL)                    /*!< MDR_TIMER1 CH1_CNTRL1: NInv (Bit 12)                  */
#define MDR_TIM_CHx_CNTRL1_NInv_Msk    (0x1000UL)                /*!< MDR_TIMER1 CH1_CNTRL1: NInv (Bitfield-Mask: 0x01)     */


/* ========================================  DTG  =================================================== */
typedef enum {                       /*!< MDR_TIMER1_CH4_DTG_DTG                                                    */
  MDR_TIM_DTG_x1            = 0,     /*!< x0 : Prescaler DTG                                                        */
  MDR_TIM_DTG_x2            = 1,     /*!< x1 : Prescaler DTG                                                        */
  MDR_TIM_DTG_x3            = 2,     /*!< x2 : Prescaler DTG                                                        */
  MDR_TIM_DTG_x4            = 3,     /*!< x3 : Prescaler DTG                                                        */
  MDR_TIM_DTG_x5            = 4,     /*!< x4 : Prescaler DTG                                                        */
  MDR_TIM_DTG_x6            = 5,     /*!< x5 : Prescaler DTG                                                        */
  MDR_TIM_DTG_x7            = 6,     /*!< x6 : Prescaler DTG                                                        */
  MDR_TIM_DTG_x8            = 7,     /*!< x7 : Prescaler DTG                                                        */
  MDR_TIM_DTG_x9            = 8,     /*!< x8 : Prescaler DTG                                                        */
  MDR_TIM_DTG_x10           = 9,    /*!< x9 : Prescaler DTG                                                        */
  MDR_TIM_DTG_x11           = 10,    /*!< x10 : Prescaler DTG                                                       */
  MDR_TIM_DTG_x12           = 11,    /*!< x11 : Prescaler DTG                                                       */
  MDR_TIM_DTG_x13           = 12,    /*!< x12 : Prescaler DTG                                                       */
  MDR_TIM_DTG_x14           = 13,    /*!< x13 : Prescaler DTG                                                       */
  MDR_TIM_DTG_x15           = 14,    /*!< x14 : Prescaler DTG                                                       */
  MDR_TIM_DTG_x16           = 15,    /*!< x15 : Prescaler DTG                                                       */
} MDR_TIM_DTG_Presc;


typedef enum {
  TIM_DTG_CLK_TimClk = 0,
  TIM_DTG_CLK_FDTS   = 1
} MDR_TIM_DTG_CLK;

typedef struct {
  __IOM MDR_TIM_DTG_Presc DTG   : 4;            /*!< [3..0] DTG Prescaller                                                     */
  __IOM MDR_TIM_DTG_CLK   EDTS  : 1;            /*!< [4..4] DTG Clock Select                                                   */
  __IM  uint32_t                : 3;
  __IOM uint32_t          DTGx  : 8;            /*!< [15..8] DTGx scale, Delay = DTGx*(DTG + 1)                                */
  __IM  uint32_t                : 16;
} MDR_TIM_CHx_DTG_Bits;

#define MDR_TIM_CHx_DTG_DTG_Pos        (0UL)                     /*!< MDR_TIMER1 CH3_DTG: DTG (Bit 0)                       */
#define MDR_TIM_CHx_DTG_DTG_Msk        (0xfUL)                   /*!< MDR_TIMER1 CH3_DTG: DTG (Bitfield-Mask: 0x0f)         */
#define MDR_TIM_CHx_DTG_EDTS_Pos       (4UL)                     /*!< MDR_TIMER1 CH3_DTG: EDTS (Bit 4)                      */
#define MDR_TIM_CHx_DTG_EDTS_Msk       (0x10UL)                  /*!< MDR_TIMER1 CH3_DTG: EDTS (Bitfield-Mask: 0x01)        */
#define MDR_TIM_CHx_DTG_DTGx_Pos       (8UL)                     /*!< MDR_TIMER1 CH3_DTG: DTGx (Bit 8)                      */
#define MDR_TIM_CHx_DTG_DTGx_Msk       (0xff00UL)                /*!< MDR_TIMER1 CH3_DTG: DTGx (Bitfield-Mask: 0xff)        */


/* ========================================  BRKETR_CNTRL  =================================================== */
typedef enum {                                  /*!< MDR_TIMER1_BRKETR_CNTRL_ETR_PSC                                           */
  MDR_TIM_BRKETR_ETR_div1 = 0,     /*!< div1 : No prescaler                                                       */
  MDR_TIM_BRKETR_ETR_div2 = 1,     /*!< div2 : Reduce freq by 2                                                   */
  MDR_TIM_BRKETR_ETR_div4 = 2,     /*!< div4 : Reduce freq by 4                                                   */
  MDR_TIM_BRKETR_ETR_div8 = 3,     /*!< div8 : Reduce freq by 8                                                   */
} MDR_TIM_BRKETR_ETR_PSC;

typedef struct {
  __IOM MDR_OnOff               BRK_INV    : 1;         /*!< [0..0] Invert Break Signal                                                */
  __IOM MDR_OnOff               ETR_INV    : 1;         /*!< [1..1] Invert External Count Signal                                       */
  __IOM MDR_TIM_BRKETR_ETR_PSC  ETR_PSC    : 2;         /*!< [3..2] External Count Div                                                 */
  __IOM MDR_TIM_FLTR            ETR_Filter : 4;         /*!< [7..4] External Count Signal Filter                                       */
} MDR_TIM_BRKETR_CNTRL_Bits;

#define MDR_TIM_BRKETR_BRK_INV_Pos (0UL)                   /*!< MDR_TIMER1 BRKETR_CNTRL: BRK_INV (Bit 0)              */
#define MDR_TIM_BRKETR_BRK_INV_Msk (0x1UL)                 /*!< MDR_TIMER1 BRKETR_CNTRL: BRK_INV (Bitfield-Mask: 0x01) */
#define MDR_TIM_BRKETR_ETR_INV_Pos (1UL)                   /*!< MDR_TIMER1 BRKETR_CNTRL: ETR_INV (Bit 1)              */
#define MDR_TIM_BRKETR_ETR_INV_Msk (0x2UL)                 /*!< MDR_TIMER1 BRKETR_CNTRL: ETR_INV (Bitfield-Mask: 0x01) */
#define MDR_TIM_BRKETR_ETR_PSC_Pos (2UL)                   /*!< MDR_TIMER1 BRKETR_CNTRL: ETR_PSC (Bit 2)              */
#define MDR_TIM_BRKETR_ETR_PSC_Msk (0xcUL)                 /*!< MDR_TIMER1 BRKETR_CNTRL: ETR_PSC (Bitfield-Mask: 0x03) */
#define MDR_TIM_BRKETR_ETR_Filter_Pos (4UL)                /*!< MDR_TIMER1 BRKETR_CNTRL: ETR_Filter (Bit 4)           */
#define MDR_TIM_BRKETR_ETR_Filter_Msk (0xf0UL)             /*!< MDR_TIMER1 BRKETR_CNTRL: ETR_Filter (Bitfield-Mask: 0x0f) */


/* ========================================  STATUS           =================================================== */
/* ========================================  IE               =================================================== */
/* ========================================  DMA_RE, DMA_REx  =================================================== */
typedef struct {
  __IOM MDR_OnOff  CNT_ZERO     : 1;          /*!< [0..0] CNT Zero                                                           */
  __IOM MDR_OnOff  CNT_ARR      : 1;          /*!< [1..1] CNT eq ARR                                                         */
  __IOM MDR_OnOff  ETR_RE       : 1;          /*!< [2..2] ETR Rise Front                                                     */
  __IOM MDR_OnOff  ETR_FE       : 1;          /*!< [3..3] ETR Fall Front                                                     */
  __IOM MDR_OnOff  BRK          : 1;          /*!< [4..4] BRK High Level                                                     */
  __IOM MDR_OnOff  CCR_CAP_CH1  : 1;          /*!< [5..5] Captured to CCR                                                    */
  __IOM MDR_OnOff  CCR_CAP_CH2  : 1;          /*!< [6..6] Captured to CCR                                                    */
  __IOM MDR_OnOff  CCR_CAP_CH3  : 1;          /*!< [7..7] Captured to CCR                                                    */
  __IOM MDR_OnOff  CCR_CAP_CH4  : 1;          /*!< [8..8] Captured to CCR                                                    */
  __IOM MDR_OnOff  CCR_REF_CH1  : 1;          /*!< [9..9] PWM Rise Front                                                     */
  __IOM MDR_OnOff  CCR_REF_CH2  : 1;          /*!< [10..10] PWM Rise Front                                                   */
  __IOM MDR_OnOff  CCR_REF_CH3  : 1;          /*!< [11..11] PWM Rise Front                                                   */
  __IOM MDR_OnOff  CCR_REF_CH4  : 1;          /*!< [12..12] PWM Rise Front                                                   */
  __IOM MDR_OnOff  CCR1_CAP_CH1 : 1;          /*!< [13..13] Captured to CCR1                                                 */
  __IOM MDR_OnOff  CCR1_CAP_CH2 : 1;          /*!< [14..14] Captured to CCR1                                                 */
  __IOM MDR_OnOff  CCR1_CAP_CH3 : 1;          /*!< [15..15] Captured to CCR1                                                 */
  __IOM MDR_OnOff  CCR1_CAP_CH4 : 1;          /*!< [16..16] Captured to CCR1                                                 */
  __IM  uint32_t                : 15;
} MDR_TIM_EVENT_Bits;

#define MDR_TIM_EVENT_CNT_ZERO_Pos    (0UL)                     /*!< MDR_TIMER1 STATUS: CNT_ZERO (Bit 0)                   */
#define MDR_TIM_EVENT_CNT_ZERO_Msk    (0x1UL)                   /*!< MDR_TIMER1 STATUS: CNT_ZERO (Bitfield-Mask: 0x01)     */
#define MDR_TIM_EVENT_CNT_ARR_Pos     (1UL)                     /*!< MDR_TIMER1 STATUS: CNT_ARR (Bit 1)                    */
#define MDR_TIM_EVENT_CNT_ARR_Msk     (0x2UL)                   /*!< MDR_TIMER1 STATUS: CNT_ARR (Bitfield-Mask: 0x01)      */
#define MDR_TIM_EVENT_ETR_RE_Pos      (2UL)                     /*!< MDR_TIMER1 STATUS: ETR_RE (Bit 2)                     */
#define MDR_TIM_EVENT_ETR_RE_Msk      (0x4UL)                   /*!< MDR_TIMER1 STATUS: ETR_RE (Bitfield-Mask: 0x01)       */
#define MDR_TIM_EVENT_ETR_FE_Pos      (3UL)                     /*!< MDR_TIMER1 STATUS: ETR_FE (Bit 3)                     */
#define MDR_TIM_EVENT_ETR_FE_Msk      (0x8UL)                   /*!< MDR_TIMER1 STATUS: ETR_FE (Bitfield-Mask: 0x01)       */
#define MDR_TIM_EVENT_BRK_Pos         (4UL)                     /*!< MDR_TIMER1 STATUS: BRK (Bit 4)                        */
#define MDR_TIM_EVENT_BRK_Msk         (0x10UL)                  /*!< MDR_TIMER1 STATUS: BRK (Bitfield-Mask: 0x01)          */
#define MDR_TIM_EVENT_CCR_CAP_CH1_Pos (5UL)                     /*!< MDR_TIMER1 STATUS: CCR_CAP_CH1 (Bit 5)                */
#define MDR_TIM_EVENT_CCR_CAP_CH1_Msk (0x20UL)                  /*!< MDR_TIMER1 STATUS: CCR_CAP_CH1 (Bitfield-Mask: 0x01)  */
#define MDR_TIM_EVENT_CCR_CAP_CH2_Pos (6UL)                     /*!< MDR_TIMER1 STATUS: CCR_CAP_CH2 (Bit 6)                */
#define MDR_TIM_EVENT_CCR_CAP_CH2_Msk (0x40UL)                  /*!< MDR_TIMER1 STATUS: CCR_CAP_CH2 (Bitfield-Mask: 0x01)  */
#define MDR_TIM_EVENT_CCR_CAP_CH3_Pos (7UL)                     /*!< MDR_TIMER1 STATUS: CCR_CAP_CH3 (Bit 7)                */
#define MDR_TIM_EVENT_CCR_CAP_CH3_Msk (0x80UL)                  /*!< MDR_TIMER1 STATUS: CCR_CAP_CH3 (Bitfield-Mask: 0x01)  */
#define MDR_TIM_EVENT_CCR_CAP_CH4_Pos (8UL)                     /*!< MDR_TIMER1 STATUS: CCR_CAP_CH4 (Bit 8)                */
#define MDR_TIM_EVENT_CCR_CAP_CH4_Msk (0x100UL)                 /*!< MDR_TIMER1 STATUS: CCR_CAP_CH4 (Bitfield-Mask: 0x01)  */
#define MDR_TIM_EVENT_CCR_REF_CH1_Pos (9UL)                     /*!< MDR_TIMER1 STATUS: CCR_REF_CH1 (Bit 9)                */
#define MDR_TIM_EVENT_CCR_REF_CH1_Msk (0x200UL)                 /*!< MDR_TIMER1 STATUS: CCR_REF_CH1 (Bitfield-Mask: 0x01)  */
#define MDR_TIM_EVENT_CCR_REF_CH2_Pos (10UL)                    /*!< MDR_TIMER1 STATUS: CCR_REF_CH2 (Bit 10)               */
#define MDR_TIM_EVENT_CCR_REF_CH2_Msk (0x400UL)                 /*!< MDR_TIMER1 STATUS: CCR_REF_CH2 (Bitfield-Mask: 0x01)  */
#define MDR_TIM_EVENT_CCR_REF_CH3_Pos (11UL)                    /*!< MDR_TIMER1 STATUS: CCR_REF_CH3 (Bit 11)               */
#define MDR_TIM_EVENT_CCR_REF_CH3_Msk (0x800UL)                 /*!< MDR_TIMER1 STATUS: CCR_REF_CH3 (Bitfield-Mask: 0x01)  */
#define MDR_TIM_EVENT_CCR_REF_CH4_Pos (12UL)                    /*!< MDR_TIMER1 STATUS: CCR_REF_CH4 (Bit 12)               */
#define MDR_TIM_EVENT_CCR_REF_CH4_Msk (0x1000UL)                /*!< MDR_TIMER1 STATUS: CCR_REF_CH4 (Bitfield-Mask: 0x01)  */
#define MDR_TIM_EVENT_CCR1_CAP_CH1_Pos (13UL)                   /*!< MDR_TIMER1 STATUS: CCR1_CAP_CH1 (Bit 13)              */
#define MDR_TIM_EVENT_CCR1_CAP_CH1_Msk (0x2000UL)               /*!< MDR_TIMER1 STATUS: CCR1_CAP_CH1 (Bitfield-Mask: 0x01) */
#define MDR_TIM_EVENT_CCR1_CAP_CH2_Pos (14UL)                   /*!< MDR_TIMER1 STATUS: CCR1_CAP_CH2 (Bit 14)              */
#define MDR_TIM_EVENT_CCR1_CAP_CH2_Msk (0x4000UL)               /*!< MDR_TIMER1 STATUS: CCR1_CAP_CH2 (Bitfield-Mask: 0x01) */
#define MDR_TIM_EVENT_CCR1_CAP_CH3_Pos (15UL)                   /*!< MDR_TIMER1 STATUS: CCR1_CAP_CH3 (Bit 15)              */
#define MDR_TIM_EVENT_CCR1_CAP_CH3_Msk (0x8000UL)               /*!< MDR_TIMER1 STATUS: CCR1_CAP_CH3 (Bitfield-Mask: 0x01) */
#define MDR_TIM_EVENT_CCR1_CAP_CH4_Pos (16UL)                   /*!< MDR_TIMER1 STATUS: CCR1_CAP_CH4 (Bit 16)              */
#define MDR_TIM_EVENT_CCR1_CAP_CH4_Msk (0x10000UL)              /*!< MDR_TIMER1 STATUS: CCR1_CAP_CH4 (Bitfield-Mask: 0x01) */

#define MDR_TIM_EVENT_ALL_Msk (0x1FFFFUL)

/* ========================================  CHx_CNTRL2           =================================================== */
typedef enum {
  TIM_CCR_Upd_Immediately,
  TIM_CCR_Upd_ZeroCNT
} MDR_TIM_CCR_Update;


typedef struct {
  __IOM MDR_TIM_EventCAP1   CHSel1 : 2;            /*!< [1..0] Event to capture in CCR1                                     */
  __IOM MDR_OnOff           CCR1_En: 1;            /*!< [2..2] Enable CCR1                                                  */
  __IOM MDR_TIM_CCR_Update  CCRRLD : 1;            /*!< [3..3] CCR Reload Mode                                              */
  __IOM MDR_OnOff           CAP_Fix: 1;            /*!< [4..4] Fix capture - IQR waits CCR regs update                      */
  __IM  uint32_t                   : 27;
} MDR_TIM_CHx_CNTRL2_Bits;

#define MDR_TIM_CHx_CNTRL2_CHSel1_Pos  (0UL)                     /*!< MDR_TIMER1 CH1_CNTRL2: CHSel1 (Bit 0)                 */
#define MDR_TIM_CHx_CNTRL2_CHSel1_Msk  (0x3UL)                   /*!< MDR_TIMER1 CH1_CNTRL2: CHSel1 (Bitfield-Mask: 0x03)   */
#define MDR_TIM_CHx_CNTRL2_CCR1_En_Pos (2UL)                     /*!< MDR_TIMER1 CH1_CNTRL2: CCR1_En (Bit 2)                */
#define MDR_TIM_CHx_CNTRL2_CCR1_En_Msk (0x4UL)                   /*!< MDR_TIMER1 CH1_CNTRL2: CCR1_En (Bitfield-Mask: 0x01)  */
#define MDR_TIM_CHx_CNTRL2_CCRRLD_Pos  (3UL)                     /*!< MDR_TIMER1 CH1_CNTRL2: CCRRLD (Bit 3)                 */
#define MDR_TIM_CHx_CNTRL2_CCRRLD_Msk  (0x8UL)                   /*!< MDR_TIMER1 CH1_CNTRL2: CCRRLD (Bitfield-Mask: 0x01)   */
#define MDR_TIM_CHx_CNTRL2_CAP_Fix_Pos (4UL)
#define MDR_TIM_CHx_CNTRL2_CAP_Fix_Msk (0x10UL)


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

#endif  //  _MDR_TIMER_DEFS_H

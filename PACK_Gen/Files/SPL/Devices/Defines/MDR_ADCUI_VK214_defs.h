#ifndef _MDR_ADCUI_VK214_DEFS_H
#define _MDR_ADCUI_VK214_DEFS_H

#include "MDR_ADCUI_VK2x4_defs.h"

#ifdef __cplusplus
extern "C" {
#endif
 
/* =========================================================  CTRL1  ======================================================== */  
typedef struct {
  __IOM MDR_OnOff                I0En : 1;            /*!< [0..0] Channel enable                                                     */
  __IOM MDR_OnOff                V0En : 1;            /*!< [1..1] Channel enable                                                     */
  __IM  uint32_t                      : 4;
  __IOM MDR_OnOff                I3En : 1;            /*!< [6..6] Channel enable                                                     */
  __IOM MDR_ADCUI_Resol         Resol : 1;            /*!< [7..7] Data resolution                                                    */
  __IOM MDR_OnOff               ZXLPF : 1;            /*!< [8..8] V0 cross zero LPF enable                                           */
  __IOM MDR_ADCUI_Period   Per_Length : 3;            /*!< [11..9] Period to calc aver period and dPhase                             */
  __IOM MDR_ADCUI_NoLoad     AP_NoLoad: 2;            /*!< [13..12] Active Energy min level to accumulate                            */
  __IM  uint32_t                      : 1;
  __IOM MDR_ADCUI_NoLoad    VAR_NoLoad: 2;            /*!< [16..15] Reactive Energy min level to accumulate                          */
  __IOM MDR_ADCUI_NoLoad    VA_NoLoad : 2;            /*!< [18..17] Full Energy min level to accumulate                              */
  __IOM MDR_OnOff             FreqSel : 1;            /*!< [19..19] Enable V0 period detection to FxMD0.PER_FREQ                     */
  __IOM MDR_ADCUI_Vref        VrefSel : 1;            /*!< [20..20] ADC Vref select                                                  */
  __IOM MDR_OnOff             Buf_Byp : 1;            /*!< [21..21] Bypass Vref buffer                                               */
  __IM  uint32_t                      : 5;
  __IOM MDR_ADCUI_RMS_Update    ZXRMS : 1;            /*!< [27..27] RMS Update mode                                                  */
  __IOM MDR_OnOff           Reset_Dig : 1;            /*!< [28..28] Digital Logic Reset                                              */
  __IOM MDR_OnOff              IBoost : 1;            /*!< [29..29] Boost I mode                                                     */
  __IOM MDR_ADCUI_SampleRate OSR_Conf : 2;            /*!< [31..30] ADC Output Sampling Rate                                         */
} MDR_ADCUI_CTRL1_Bits;  
  
#define MDR_ADCUI_CTRL1_I0EN_Pos          (0UL)                     /*!< MDR_ADCUI CTRL1: I0EN (Bit 0)                         */
#define MDR_ADCUI_CTRL1_I0EN_Msk          (0x1UL)                   /*!< MDR_ADCUI CTRL1: I0EN (Bitfield-Mask: 0x01)           */
#define MDR_ADCUI_CTRL1_V0EN_Pos          (1UL)                     /*!< MDR_ADCUI CTRL1: V0EN (Bit 1)                         */
#define MDR_ADCUI_CTRL1_V0EN_Msk          (0x2UL)                   /*!< MDR_ADCUI CTRL1: V0EN (Bitfield-Mask: 0x01)           */

#define MDR_ADCUI_CTRL1_I3EN_Pos          (6UL)                     /*!< MDR_ADCUI CTRL1: I3EN (Bit 6)                         */
#define MDR_ADCUI_CTRL1_I3EN_Msk          (0x40UL)                  /*!< MDR_ADCUI CTRL1: I3EN (Bitfield-Mask: 0x01)           */
#define MDR_ADCUI_CTRL1_RESOL_Pos         (7UL)                     /*!< MDR_ADCUI CTRL1: RESOL (Bit 7)                        */
#define MDR_ADCUI_CTRL1_RESOL_Msk         (0x80UL)                  /*!< MDR_ADCUI CTRL1: RESOL (Bitfield-Mask: 0x01)          */
#define MDR_ADCUI_CTRL1_ZXLPF_Pos         (8UL)                     /*!< MDR_ADCUI CTRL1: ZXLPF (Bit 8)                        */
#define MDR_ADCUI_CTRL1_ZXLPF_Msk         (0x100UL)                 /*!< MDR_ADCUI CTRL1: ZXLPF (Bitfield-Mask: 0x01)          */
#define MDR_ADCUI_CTRL1_PER_Length_Pos    (9UL)                     /*!< MDR_ADCUI CTRL1: PER_Length (Bit 9)                   */
#define MDR_ADCUI_CTRL1_PER_Length_Msk    (0xe00UL)                 /*!< MDR_ADCUI CTRL1: PER_Length (Bitfield-Mask: 0x07)     */
#define MDR_ADCUI_CTRL1_APNOLOAD_Pos      (12UL)                    /*!< MDR_ADCUI CTRL1: APNOLOAD (Bit 12)                    */
#define MDR_ADCUI_CTRL1_APNOLOAD_Msk      (0x3000UL)                /*!< MDR_ADCUI CTRL1: APNOLOAD (Bitfield-Mask: 0x03)       */
#define MDR_ADCUI_CTRL1_VARNOLOAD_Pos     (15UL)                    /*!< MDR_ADCUI CTRL1: VARNOLOAD (Bit 15)                   */
#define MDR_ADCUI_CTRL1_VARNOLOAD_Msk     (0x18000UL)               /*!< MDR_ADCUI CTRL1: VARNOLOAD (Bitfield-Mask: 0x03)      */
#define MDR_ADCUI_CTRL1_VANOLOAD_Pos      (17UL)                    /*!< MDR_ADCUI CTRL1: VANOLOAD (Bit 17)                    */
#define MDR_ADCUI_CTRL1_VANOLOAD_Msk      (0x60000UL)               /*!< MDR_ADCUI CTRL1: VANOLOAD (Bitfield-Mask: 0x03)       */
#define MDR_ADCUI_CTRL1_FREQSEL_Pos       (19UL)                    /*!< MDR_ADCUI CTRL1: FREQSEL (Bit 19)                     */
#define MDR_ADCUI_CTRL1_FREQSEL_Msk       (0x80000UL)               /*!< MDR_ADCUI CTRL1: FREQSEL (Bitfield-Mask: 0x01)        */
#define MDR_ADCUI_CTRL1_VREF_SEL_Pos      (20UL)                    /*!< MDR_ADCUI CTRL1: VREF_SEL (Bit 20)                    */
#define MDR_ADCUI_CTRL1_VREF_SEL_Msk      (0x100000UL)              /*!< MDR_ADCUI CTRL1: VREF_SEL (Bitfield-Mask: 0x01)       */
#define MDR_ADCUI_CTRL1_BUF_BYP_Pos       (21UL)                    /*!< MDR_ADCUI CTRL1: BUF_BYP (Bit 21)                     */
#define MDR_ADCUI_CTRL1_BUF_BYP_Msk       (0x200000UL)              /*!< MDR_ADCUI CTRL1: BUF_BYP (Bitfield-Mask: 0x01)        */

#define MDR_ADCUI_CTRL1_ZXRMS_Pos         (27UL)                    /*!< MDR_ADCUI CTRL1: ZXRMS (Bit 27)                       */
#define MDR_ADCUI_CTRL1_ZXRMS_Msk         (0x8000000UL)             /*!< MDR_ADCUI CTRL1: ZXRMS (Bitfield-Mask: 0x01)          */
#define MDR_ADCUI_CTRL1_RESET_DIG_Pos     (28UL)                    /*!< MDR_ADCUI CTRL1: RESET_DIG (Bit 28)                   */
#define MDR_ADCUI_CTRL1_RESET_DIG_Msk     (0x10000000UL)            /*!< MDR_ADCUI CTRL1: RESET_DIG (Bitfield-Mask: 0x01)      */
#define MDR_ADCUI_CTRL1_IBOOST_Pos        (29UL)                    /*!< MDR_ADCUI CTRL1: IBOOST (Bit 29)                      */
#define MDR_ADCUI_CTRL1_IBOOST_Msk        (0x20000000UL)            /*!< MDR_ADCUI CTRL1: IBOOST (Bitfield-Mask: 0x01)         */
#define MDR_ADCUI_CTRL1_OSR_CONF_Pos      (30UL)                    /*!< MDR_ADCUI CTRL1: OSR_CONF (Bit 30)                    */
#define MDR_ADCUI_CTRL1_OSR_CONF_Msk      (0xc0000000UL)            /*!< MDR_ADCUI CTRL1: OSR_CONF (Bitfield-Mask: 0x03)       */

/* =========================================================================================================================== */
/* ================                                         MDR_ADCUI                                         ================ */
/* =========================================================================================================================== */

typedef struct {                                /*!< (@ 0x40068000) MDR_ADCUI Structure                                        */  
  union {
    __IOM uint32_t          CTRL1;               /*!< (@ 0x00000000) ADCUI Control1 Register                                    */
    MDR_ADCUI_CTRL1_Bits    CTRL1_b;
  };  
  union {
    __IOM uint32_t          CTRL2;               /*!< (@ 0x00000004) ADCUI Control2 Register                                    */
    MDR_ADCUI_CTRL2_Bits    CTRL2_b;
  } ;  
  union {
    __IOM uint32_t          CTRL3;               /*!< (@ 0x00000008) ADCUI Control3 Register                                    */
    MDR_ADCUI_CTRL2_Bits    CTRL3_b;
  } ;  
  union {
    __IOM uint32_t          F0CTR;               /*!< (@ 0x0000000C) FxCTR register                                             */
    MDR_ADCUI_F0CTR_Bits    F0CTR_b;
  } ;  
  union {
    __IOM uint32_t          F0WC;                /*!< (@ 0x00000010) Active energy calibration                                  */
    MDR_ADCUI_FxWC_Bits     F0WC_b;
  } ;  
  union {
    __IM  uint32_t          F0WATTP;             /*!< (@ 0x00000014) Positive Active Energy accumulator                         */
    MDR_ADCUI_FxWattP_Bits  F0WATTP_b;
  } ;  
  union {
    __IM  uint32_t          F0WATTN;             /*!< (@ 0x00000018) Negative Active Energy accumulator                         */
    MDR_ADCUI_FxWattN_Bits  F0WATTN_b;
  } ;  
  union {
    __IOM uint32_t          F0VC;                /*!< (@ 0x0000001C) Reactive energy calibration                                */
    MDR_ADCUI_FxVC_Bits     F0VC_b;
  } ;
  union {
    __IM  uint32_t          F0VARP;              /*!< (@ 0x00000020) Positive Reactive Energy accumulator                       */
    MDR_ADCUI_FxVarP_Bits   F0VARP_b;
  } ;  
  union {
    __IM  uint32_t          F0VARN;              /*!< (@ 0x00000024) Negative Reactive Energy accumulator                       */
    MDR_ADCUI_FxVarN_Bits   F0VARN_b;
  } ;
  union {
    __IOM uint32_t          F0AC;                /*!< (@ 0x00000028) V0 RMS calibration                                         */
    MDR_ADCUI_FxAC_Bits     F0AC_b;
  } ;
  union {
    __IM  uint32_t          F0VR;                /*!< (@ 0x0000002C) Full Energy accumulator                                    */
    MDR_ADCUI_FxVR_Bits     F0VR_b;
  } ;  
  union {
    __IOM uint32_t          F0MD0;               /*!< (@ 0x00000030) FxMD0 register                                             */
    MDR_ADCUI_F0MD0_Bits    F0MD0_b;
  } ;
  union {
    __IOM uint32_t          F0MD1;               /*!< (@ 0x00000034) FxMD1 register                                             */
    MDR_ADCUI_FxMD1_Bits    F0MD1_b;
  } ;
  union {
    __IOM uint32_t          F0VPEAK;             /*!< (@ 0x00000038) VPEAK Result register                                      */
    MDR_ADCUI_Result24_Bits F0VPEAK_b;
  } ;
  union {
    __IOM uint32_t          F0IPEAK;             /*!< (@ 0x0000003C) IPEAK Result register                                      */
    MDR_ADCUI_Result24_Bits F0IPEAK_b;
  } ;
  union {
    __IM  uint32_t          F0VDAT;              /*!< (@ 0x00000040) VDAT Result register                                       */
    MDR_ADCUI_Result24_Bits F0VDAT_b;
  } ;
  union {
    __IM  uint32_t          F0I0DAT;             /*!< (@ 0x00000044) I0DAT Result register                                      */
    MDR_ADCUI_Result24_Bits F0I0DAT_b;
  } ;  
  union {
    __IM  uint32_t          F0I3DAT;             /*!< (@ 0x00000048) I3DAT Result register                                      */
    MDR_ADCUI_Result24_Bits F0I3DAT_b;
  } ;  
  union {
    __IM  uint32_t          F0VRMS;              /*!< (@ 0x0000004C) VRMS Result register                                       */
    MDR_ADCUI_Result24_Bits F0VRMS_b;
  } ;
  union {
    __IM  uint32_t          F0VRMS2;             /*!< (@ 0x00000050) VRMS^2 Result register                                     */
    MDR_ADCUI_Result24_Bits F0VRMS2_b;
  } ;
  union {
    __IM  uint32_t          F0IRMS;              /*!< (@ 0x00000054) IRMS Result register                                       */
    MDR_ADCUI_Result24_Bits F0IRMS_b;
  } ;
  union {
    __IM  uint32_t          F0IRMS2;             /*!< (@ 0x00000058) IRMS^2 Result register                                     */
    MDR_ADCUI_Result24_Bits F0IRMS2_b;
  } ; 
  union {
    __IOM uint32_t          F0STAT;              /*!< (@ 0x0000005C) Status Register                                            */
    MDR_ADCUI_F0Stat_Bits   F0STAT_b;
  } ;
  union {
    __IOM uint32_t          F0MASK;              /*!< (@ 0x00000060) IRQ Mask Register                                          */
    MDR_ADCUI_F0Mask_Bits   F0MASK_b;
  } ;
  __IM  uint32_t  RESERVED[44];  
  union {
    __IOM uint32_t          CCAL1;               /*!< (@ 0x00000114) Calibration Register 1                                     */
    MDR_ADCUI_CCAL1_Bits    CCAL1_b;
  } ;
  __IM  uint32_t  RESERVED1[2];  
  union {
    __IOM uint32_t          CCAL4;               /*!< (@ 0x00000120) Calibration Register 4                                     */
    MDR_ADCUI_CCAL4_Bits    CCAL4_b;
  } ;
} MDR_ADCUI_TypeDef;                             /*!< Size = 292 (0x124)                                                        */



#ifdef __cplusplus
}
#endif

#endif  //  _MDR_ADCUI_VK214_DEFS_H

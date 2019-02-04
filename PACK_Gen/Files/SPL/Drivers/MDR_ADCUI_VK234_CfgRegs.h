#ifndef _MDR_ADCUI_VK234_CFG_H
#define _MDR_ADCUI_VK234_CFG_H

#include <MDR_ADCUI_VK234_defs.h>

#ifdef __cplusplus
extern "C" {
#endif

#include "MDR_Types.h"
  
  
//  В типах _CfgBits биты переназваны более информативным образом, это легче для восприятия, но сложнее сравнивать со спецификацией.
  //  Для использования битов с именами по спецификации выставить USE_NATIVE_BITS = 1. Но будут warnings при сборке
#define USE_NATIVE_BITS   0

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


typedef struct {
  MDR_OnOff                    I0En : 1;       /*!< [0..0] Channel enable                                                     */
  MDR_OnOff                    V0En : 1;       /*!< [1..1] Channel enable                                                     */
  MDR_OnOff                    I1En : 1;       /*!< [0..0] Channel enable                                                     */
  MDR_OnOff                    V1En : 1;       /*!< [1..1] Channel enable                                                     */
  MDR_OnOff                    I2En : 1;       /*!< [0..0] Channel enable                                                     */
  MDR_OnOff                    V2En : 1;       /*!< [1..1] Channel enable                                                     */
  MDR_OnOff                    I3En : 1;       /*!< [6..6] Channel enable                                                     */
  MDR_OnOff               DataBit24 : 1;       /*!< Resol       [7..7] Data resolution                                        */
  MDR_OnOff             Vcrs0_LPFEn : 1;       /*!< ZXLPF       [8..8] V0 cross zero LPF enable                               */
  MDR_ADCUI_Period  VPer_DetectAver : 3;       /*!< Per_Length [11..9] Period to calc aver period and dPhase                  */
  MDR_ADCUI_NoLoad        Pa_NoLoad : 2;       /*!< AP_NoLoad [13..12] Active Energy min level to accumulate                  */
  uint32_t                          : 1;
  MDR_ADCUI_NoLoad        Pr_NoLoad : 2;       /*!< VAR_NoLoad [16..15] Reactive Energy min level to accumulate               */
  MDR_ADCUI_NoLoad        Pf_NoLoad : 2;       /*!< VA_NoLoad  [18..17] Full Energy min level to accumulate                   */
  MDR_OnOff           VPer_DetectOn : 1;       /*!< FreqSel    [19..19] Enable V0 period detection to FxMD0.PER_FREQ          */
  MDR_ADCUI_Vref            VrefSel : 1;       /*!< [20..20] ADC Vref select                                                  */
  MDR_OnOff            VrefPassBuff : 1;       /*!< Buf_Byp    [21..21] Bypass Vref buffer                                    */
  MDR_OnOff                 Chop_En : 1;       /*!< [22..22] Chopper Mode Select                                              */
  MDR_ADCUI_ChopDiv       Chop_Freq : 2;       /*!< [24..23] Chopper Frequency                                                */  
  uint32_t                          : 2;
  MDR_ADCUI_RMS_Update   RMS_Update : 1;       /*!< ZXRMS    [27..27] RMS Update mode                                         */
  MDR_OnOff               Reset_Dig : 1;       /*!< [28..28] Digital Logic Reset                                              */
  MDR_OnOff                  IBoost : 1;       /*!< [29..29] Boost I mode                                                     */
  MDR_ADCUI_SampleRate    SampleRate: 2;       /*!< OSR_Conf  [31..30] ADC Output Sampling Rate                               */
} MDR_ADCUI_CTRL1_CfgBits; 

typedef struct {
  uint32_t  Vmin_Level        : 16;              /*!< SAGLVL [15..0] V0 min OK level                                                   */
  uint32_t  Vmin_HalfPeriods  : 8;               /*!< SAGCYC [23..16] Count of V0 half periods to calc V0 level                        */
  uint32_t                    : 8;
} MDR_ADCUI_CTRL2_CfgBits;

typedef struct {
  uint32_t  Vcrs0_Timeout     : 12;              /*!< ZTXOUT [11..0] V0 cross zero timeout                                             */
  uint32_t                    : 20;
} MDR_ADCUI_CTRL3_CfgBits;



#if USE_NATIVE_BITS
  #define MDR_ADCUI_CTRL1_b MDR_ADCUI_CTRL1_Bits
  #define MDR_ADCUI_CTRL2_b MDR_ADCUI_CTRL2_Bits
  #define MDR_ADCUI_CTRL3_b MDR_ADCUI_CTRL3_Bits

#else
  #define MDR_ADCUI_CTRL1_b MDR_ADCUI_CTRL1_CfgBits
  #define MDR_ADCUI_CTRL2_b MDR_ADCUI_CTRL2_CfgBits
  #define MDR_ADCUI_CTRL3_b MDR_ADCUI_CTRL3_CfgBits
#endif

typedef struct {
  union { 
    uint32_t                CTRL1;
    MDR_ADCUI_CTRL1_b       CTRL1_b;
  };  
  union {
    uint32_t                CTRL2;
    MDR_ADCUI_CTRL2_b       CTRL2_b;
  } ;  
  union {
    uint32_t                CTRL3;
    MDR_ADCUI_CTRL3_b       CTRL3_b;
  } ;
}  MDR_ADCUI_CFG_CTRL;


typedef struct {
  MDR_OnOff         I0_SumOff : 1;            /*!< I0NTEn [0..0] Integrator enable                              */
  MDR_OnOff         I3_SumOff : 1;            /*!< I3NTEn [1..1] Integrator enable                              */
  MDR_ADCUI_VASel     RMStoEf : 1;            /*!< VASEL  [2..2] Select source for FullEnergy                   */
  MDR_OnOff          Ea_Clear : 1;            /*!< RARS   [3..3] Active Energy Accumulator Reset                */
  MDR_OnOff          Er_Clear : 1;            /*!< RRRS   [4..4] Reactive Energy Accumulator Reset              */
  MDR_OnOff          Ef_Clear : 1;            /*!< RVRS   [5..5] Full Energy Accumulator Reset                  */
  MDR_ADCUI_PGA        I0_PGA : 2;            /*!< I0GAIN [7..6] PGA value                                      */
  MDR_ADCUI_PGA        V0_PGA : 2;            /*!< V0GAIN [9..8] PGA value                                      */
  uint32_t             VPhase : 8;            /*!<        [17..10] Phase V0 adjustment by step of +-124us       */
  MDR_ADCUI_PGA        I3_PGA : 2;            /*!< I3GAIN [19..18] PGA value                                    */
  uint32_t           RMS_Bias : 12;           /*!< IRMSOS [31..20] RMS calibration of channel I                 */
} MDR_ADCUI_F0CTR_CfgBits;

typedef struct {
  MDR_OnOff         I0_SumOff : 1;            /*!< INTEn [0..0] Integrator enable                                                  */
  uint32_t                    : 1;            /*!< [1..1] Integrator enable                                                  */
  MDR_ADCUI_VASel     RMStoEf : 1;            /*! VASel< [2..2] Select source for FullEnergy                                       */
  MDR_OnOff          Ea_Clear : 1;            /*!< RARS [3..3] Active Energy Accumulator Reset                                    */
  MDR_OnOff          Er_Clear : 1;            /*!< RRRS [4..4] Reactive Energy Accumulator Reset                                  */
  MDR_OnOff          Ef_Clear : 1;            /*!< RVRS [5..5] Full Energy Accumulator Reset                                      */
  MDR_ADCUI_PGA         I_PGA : 2;            /*!< IGain [7..6] PGA value                                                          */
  MDR_ADCUI_PGA         V_PGA : 2;            /*!< VGain [9..8] PGA value                                                          */
  uint32_t             VPhase : 8;            /*!< [17..10] Phase V0 adjustment by step of +-124us                           */
  uint32_t                    : 2;            /*!< [19..18] PGA value                                                        */
  uint32_t           RMS_Bias : 12;           /*!< IRMSOS [31..20] RMS calibration of channel I                                     */
} MDR_ADCUI_FxCTR_CfgBits;

typedef struct {
  uint32_t Ea_Bias     : 16;           /*!< WattOS   [15..0] Calibr bias of active energy                                      */
  uint32_t Ea_Gain     : 12;           /*!< WattGain [27..16] Calibr gain of active energy                                     */
  uint32_t             : 4;
} MDR_ADCUI_FxWC_CfgBits;

typedef struct {
  uint32_t Er_Bias    : 16;           /*!< VarOS    [15..0] Calibr bias of active energy                                      */
  uint32_t Er_Gain    : 12;           /*!< VarGain  [27..16] Calibr gain of active energy                                     */
  uint32_t            : 4;
} MDR_ADCUI_FxVC_CfgBits;

typedef struct {
  uint32_t VRMS_Bias  : 12;           /*!< VRMSOS [11..0] Calibr bias of V0 RMS                                             */
  uint32_t            : 4;
  uint32_t Ef_Gain    : 12;           /*!< VAGain [27..16] Calibr gain of Full energy                                       */
  uint32_t            : 4;
} MDR_ADCUI_FxAC_CfgBits;

typedef struct {
  MDR_ADCUI_VDAT_Sel        VSel : 2;            /*!< [1..0] Select source for FxVDAT                                           */
  MDR_ADCUI_IDAT_Sel        ISel : 2;            /*!< [3..2] Select source for FxI0DAT                                          */
  MDR_ADCUI_Sign         Ea_Sign : 1;            /*!< ACTS   [4..4] Active Energy sign in last period                                  */
  MDR_ADCUI_Sign         Er_Sign : 1;            /*!< ReactS [5..5] Reactive Energy sign in last period                                */
  MDR_ADCUI_DecimGain   I0_ADCx2 : 1;            /*!< I0GAIN [6..6] ADC Decimation gain                                                */
  MDR_ADCUI_DecimGain   V0_ADCx2 : 1;            /*!< V0Gain [7..7] ADC Decimation gain                                                */
  MDR_ADCUI_DecimGain   I3_ADCx2 : 1;            /*!< I3Gain [8..8] ADC Decimation gain                                                */
  uint32_t                       : 3;
  uint32_t            Vper_Result: 17;           /*!< Per_Freq [28..12] Measured period of V                                             */
  MDR_ADCUI_I3DAT_Sel    I3Sel   : 1;            /*!< [29..29] Select source for FxI3DAT                                        */
  MDR_ADCUI_SelI      Sel_I_Ch   : 2;            /*!< [31..30] Select I for calc power                                          */
} MDR_ADCUI_F0MD0_CfgBits;

typedef struct {
  MDR_ADCUI_VDAT_Sel        VSel : 2;            /*!< [1..0] Select source for FxVDAT                                           */
  MDR_ADCUI_IDAT_Sel        ISel : 2;            /*!< [3..2] Select source for FxIDAT                                          */
  MDR_ADCUI_Sign         Ea_Sign : 1;            /*!< ActS   [4..4] Active Energy sign in last period                                  */
  MDR_ADCUI_Sign         Er_Sign : 1;            /*!< ReactS [5..5] Reactive Energy sign in last period                                */
  MDR_ADCUI_DecimGain    I_ADCx2 : 1;            /*!< IGain  [6..6] ADC Decimation gain                                                */
  MDR_ADCUI_DecimGain    V_ADCx2 : 1;            /*!< VGain  [7..7] ADC Decimation gain                                                */
  uint32_t                       : 4;
  uint32_t           Vper_Result : 17;           /*!< Per_Freq [28..12] Measured period of V                                             */
  uint32_t                       : 3;
} MDR_ADCUI_FxMD0_CfgBits;

typedef struct {
  uint32_t Imax_Level     : 16;           /*!< IPKLvl [15..0] Imax level                                                        */
  uint32_t Vmax_Level     : 16;           /*!< VPKLvl [31..16] Vmax level                                                       */
} MDR_ADCUI_FxMD1_CfgBits;

typedef struct {
  uint32_t VxPhaseToV0 : 16;           /*!< Phase [15..0] Vx phase to V0                                                        */
  uint32_t             : 16;
} MDR_ADCUI_FxMD2_CfgBits;

typedef struct {
  MDR_OnOff VF_EMP     : 1;            /*!< [0..0] FIFO_VDAT is Empty                                */
  MDR_OnOff VF_FLL     : 1;            /*!< [1..1] FIFO_VDAT is Full                                 */
  MDR_OnOff VF_OVER    : 1;            /*!< [2..2] FIFO_VDAT is Overflow                             */
  MDR_OnOff IF_EMP     : 1;            /*!< [3..3] FIFO_IDAT is Empty                                */
  MDR_OnOff IF_FLL     : 1;            /*!< [4..4] FIFO_IDAT is Full                                 */
  MDR_OnOff IF_OVER    : 1;            /*!< [5..5] FIFO_IDAT is Overflow                             */
  MDR_OnOff VMinOV     : 1;            /*!< SAGF   [6..6] V is less than CTRL2.SAGLVL                       */
  MDR_OnOff VMaxOV     : 1;            /*!< PEAKVF [7..7] V exceeds F0MD1.VPKLVL                            */
  MDR_OnOff IMaxOV     : 1;            /*!< PEAKIF [8..8] I exceeds F0MD1.VPKLVL                            */
  MDR_OnOff EaP_OV     : 1;            /*!< WATTOVP[9..9] FxWATTP value overflow                            */
  MDR_OnOff ErP_OV     : 1;            /*!< VAROVP [10..10] FxVARP value overflow                           */
  MDR_OnOff Ef_OV      : 1;            /*!< VAOV   [11..11] FxVR value overflow                             */
  MDR_OnOff Vcrs0_Timeout: 1;          /*!< ZTXVF  [12..12] Timeout of V cross zero                         */
  MDR_OnOff Iscr_Active  : 1;          /*!< ICHANNEL [13..13] Timeout of V cross zero                         */
  MDR_OnOff Isrc_Changed : 1;          /*!< FAULTCON [14..14] Active I switched                               */
  MDR_OnOff Pa_ReSign  : 1;            /*!< APSIGN   [15..15] ActivePower sign changed                        */
  MDR_OnOff Pa_NoLoad  : 1;            /*!< APNLDFL  [16..16] ActivePower less CNTL1.APNOLOAD                 */
  MDR_OnOff Pr_ReSign  : 1;            /*!< VARSIGN  [17..17] ReactivePower sign changed                      */
  MDR_OnOff Pr_NoLoad  : 1;            /*!< VARNLDFL [18..18] ReactivePower less CNTL1.VARNOLOAD              */
  uint32_t             : 1;
  MDR_OnOff Pf_NoLoad  : 1;            /*!< VANLDFL [20..20] FullPower less CNTL1.VANOLOAD                   */
  MDR_OnOff Vcrs0      : 1;            /*!< ZEROCRS [21..21] V crossed zero                                  */
  MDR_OnOff I3F_EMP    : 1;            /*!< [22..22] FIFO_I3DAT is Empty                             */
  MDR_OnOff I3F_FLL    : 1;            /*!< [23..23] FIFO_I3DAT is Full                              */
  MDR_OnOff I3F_OVER   : 1;            /*!< [24..24] FIFO_I3DAT is Overflow                          */
  MDR_OnOff EaN_OV     : 1;            /*!< WATTOVN [25..25] FxWATTN value overflow                          */
  MDR_OnOff ErN_OV     : 1;            /*!< VAROVN  [26..26] FxVARN value overflow                           */
  uint32_t             : 5;
} MDR_ADCUI_F0Stat_CfgBits;

typedef struct {
  MDR_OnOff VF_EMP     : 1;            /*!< [0..0] FIFO_VDAT is Empty                                */
  MDR_OnOff VF_FLL     : 1;            /*!< [1..1] FIFO_VDAT is Full                                 */
  MDR_OnOff VF_OVER    : 1;            /*!< [2..2] FIFO_VDAT is Overflow                             */
  MDR_OnOff IF_EMP     : 1;            /*!< [3..3] FIFO_IDAT is Empty                                */
  MDR_OnOff IF_FLL     : 1;            /*!< [4..4] FIFO_IDAT is Full                                 */
  MDR_OnOff IF_OVER    : 1;            /*!< [5..5] FIFO_IDAT is Overflow                             */
  MDR_OnOff VMinOV     : 1;            /*!< SAGF   [6..6] V is less than CTRL2.SAGLVL                */
  MDR_OnOff VMaxOV     : 1;            /*!< PEAKVF [7..7] V exceeds F0MD1.VPKLVL                     */
  MDR_OnOff IMaxOV     : 1;            /*!< PEAKIF [8..8] I exceeds F0MD1.VPKLVL                     */
  MDR_OnOff EaP_OV     : 1;            /*!< WATTOVP[9..9] FxWATTP value overflow                     */
  MDR_OnOff ErP_OV     : 1;            /*!< VAROVP [10..10] FxVARP value overflow                    */
  MDR_OnOff Ef_OV      : 1;            /*!< VAOV   [11..11] FxVR value overflow                      */
  MDR_OnOff Vcrs0_Timeout: 1;          /*!< ZTXVF  [12..12] Timeout of V cross zero                  */
  uint32_t             : 2;
  MDR_OnOff Pa_ReSign  : 1;            /*!< APSIGN   [15..15] ActivePower sign changed               */
  MDR_OnOff Pa_NoLoad  : 1;            /*!< APNLDFL  [16..16] ActivePower less CNTL1.APNOLOAD        */
  MDR_OnOff Pr_ReSign  : 1;            /*!< VARSIGN  [17..17] ReactivePower sign changed             */
  MDR_OnOff Pr_NoLoad  : 1;            /*!< VARNLDFL [18..18] ReactivePower less CNTL1.VARNOLOAD     */
  uint32_t             : 1;
  MDR_OnOff Pf_NoLoad  : 1;            /*!< VANLDFL [20..20] FullPower less CNTL1.VANOLOAD           */
  MDR_OnOff Vcrs0      : 1;            /*!< ZEROCRS [21..21] V crossed zero                          */
  uint32_t             : 3;
  MDR_OnOff EaN_OV     : 1;            /*!< WATTOVN [25..25] FxWATTN value overflow                  */
  MDR_OnOff ErN_OV     : 1;            /*!< VAROVN  [26..26] FxVARN value overflow                   */
  uint32_t             : 5;  
} MDR_ADCUI_FxStat_CfgBits;


typedef struct {
  MDR_OnOff VF_EMP     : 1;            /*!< [0..0] FIFO_VDAT is Empty                                                 */
  MDR_OnOff VF_FLL     : 1;            /*!< [1..1] FIFO_VDAT is Full                                                  */
  MDR_OnOff VF_OVER    : 1;            /*!< [2..2] FIFO_VDAT is Overflow                                              */
  MDR_OnOff IF_EMP     : 1;            /*!< [3..3] FIFO_IDAT is Empty                                                 */
  MDR_OnOff IF_FLL     : 1;            /*!< [4..4] FIFO_IDAT is Full                                                  */
  MDR_OnOff IF_OVER    : 1;            /*!< [5..5] FIFO_IDAT is Overflow                                              */
  MDR_OnOff VMinOV     : 1;            /*!< SAGF   [6..6] V is less than CTRL2.SAGLVL                                        */
  MDR_OnOff VMaxOV     : 1;            /*!< PEAKVF [7..7] V exceeds F0MD1.VPKLVL                                             */
  MDR_OnOff IMaxOV     : 1;            /*!< PEAKIF [8..8] I exceeds F0MD1.VPKLVL                                             */
  MDR_OnOff EaP_OV     : 1;            /*!< WATTOVP[9..9] FxWATTP value overflow                                             */
  MDR_OnOff ErP_OV     : 1;            /*!< VAROVP [10..10] FxVARP value overflow                                            */
  MDR_OnOff Ef_OV      : 1;            /*!< VAOV   [11..11] FxVR value overflow                                              */
  MDR_OnOff Vcrs0_Timeout: 1;          /*!< ZTXVF  [12..12] Timeout of V cross zero                                          */
  uint32_t             : 1;
  MDR_OnOff Isrc_Changed : 1;          /*!< FAULTCON [14..14] Active I switched                                                */
  MDR_OnOff Pa_ReSign  : 1;            /*!< APSIGN   [15..15] ActivePower sign changed                                         */
  MDR_OnOff Pa_NoLoad  : 1;            /*!< APNLDFL  [16..16] ActivePower less CNTL1.APNOLOAD                                  */
  MDR_OnOff Pr_ReSign  : 1;            /*!< VARSIGN  [17..17] ReactivePower sign changed                                       */
  MDR_OnOff Pr_NoLoad  : 1;            /*!< VARNLDFL [18..18] ReactivePower less CNTL1.VARNOLOAD                               */
  uint32_t             : 1;
  MDR_OnOff Pf_NoLoad  : 1;            /*!< VANLDFL [20..20] FullPower less CNTL1.VANOLOAD                                    */
  MDR_OnOff Vcrs0      : 1;            /*!< ZEROCRS [21..21] V crossed zero                                                   */
  MDR_OnOff I3F_EMP    : 1;            /*!< [22..22] FIFO_I3DAT is Empty                                              */
  MDR_OnOff I3F_FLL    : 1;            /*!< [23..23] FIFO_I3DAT is Full                                               */
  MDR_OnOff I3F_OVER   : 1;            /*!< [24..24] FIFO_I3DAT is Overflow                                           */
  MDR_OnOff EaN_OV     : 1;            /*!< WATTOVN [25..25] FxWATTN value overflow                                           */
  MDR_OnOff ErN_OV     : 1;            /*!< VAROVN  [26..26] FxVARN value overflow                                            */
  uint32_t             : 5;
} MDR_ADCUI_F0Mask_CfgBits;


typedef struct {
  MDR_OnOff VF_EMP     : 1;            /*!< [0..0] FIFO_VDAT is Empty                                */
  MDR_OnOff VF_FLL     : 1;            /*!< [1..1] FIFO_VDAT is Full                                 */
  MDR_OnOff VF_OVER    : 1;            /*!< [2..2] FIFO_VDAT is Overflow                             */
  MDR_OnOff IF_EMP     : 1;            /*!< [3..3] FIFO_IDAT is Empty                                */
  MDR_OnOff IF_FLL     : 1;            /*!< [4..4] FIFO_IDAT is Full                                 */
  MDR_OnOff IF_OVER    : 1;            /*!< [5..5] FIFO_IDAT is Overflow                             */
  MDR_OnOff VMinOV     : 1;            /*!< SAGF   [6..6] V is less than CTRL2.SAGLVL                */
  MDR_OnOff VMaxOV     : 1;            /*!< PEAKVF [7..7] V exceeds F0MD1.VPKLVL                     */
  MDR_OnOff IMaxOV     : 1;            /*!< PEAKIF [8..8] I exceeds F0MD1.VPKLVL                     */
  MDR_OnOff EaP_OV     : 1;            /*!< WATTOVP[9..9] FxWATTP value overflow                     */
  MDR_OnOff ErP_OV     : 1;            /*!< VAROVP [10..10] FxVARP value overflow                    */
  MDR_OnOff Ef_OV      : 1;            /*!< VAOV   [11..11] FxVR value overflow                      */
  MDR_OnOff Vcrs0_Timeout: 1;          /*!< ZTXVF  [12..12] Timeout of V cross zero                  */
  uint32_t             : 2;
  MDR_OnOff Pa_ReSign  : 1;            /*!< APSIGN   [15..15] ActivePower sign changed               */
  MDR_OnOff Pa_NoLoad  : 1;            /*!< APNLDFL  [16..16] ActivePower less CNTL1.APNOLOAD        */
  MDR_OnOff Pr_ReSign  : 1;            /*!< VARSIGN  [17..17] ReactivePower sign changed             */
  MDR_OnOff Pr_NoLoad  : 1;            /*!< VARNLDFL [18..18] ReactivePower less CNTL1.VARNOLOAD     */
  uint32_t             : 1;
  MDR_OnOff Pf_NoLoad  : 1;            /*!< VANLDFL [20..20] FullPower less CNTL1.VANOLOAD           */
  MDR_OnOff Vcrs0      : 1;            /*!< ZEROCRS [21..21] V crossed zero                          */
  uint32_t             : 3;
  MDR_OnOff EaN_OV     : 1;            /*!< WATTOVN [25..25] FxWATTN value overflow                  */
  MDR_OnOff ErN_OV     : 1;            /*!< VAROVN  [26..26] FxVARN value overflow                   */
  uint32_t             : 5;    
} MDR_ADCUI_FxMask_CfgBits;


#if USE_NATIVE_BITS
  #define MDR_ADCUI_F0CTR_b   MDR_ADCUI_F0CTR_Bits
  #define MDR_ADCUI_F0MD0_b   MDR_ADCUI_F0MD0_Bits
  #define MDR_ADCUI_F0Stat_b  MDR_ADCUI_F0Stat_Bits
  #define MDR_ADCUI_F0Mask_b  MDR_ADCUI_F0Mask_Bits

  #define MDR_ADCUI_FxCTR_b   MDR_ADCUI_FxCTR_Bits
  #define MDR_ADCUI_FxWC_b    MDR_ADCUI_FxWC_Bits
  #define MDR_ADCUI_FxVC_b    MDR_ADCUI_FxVC_Bits
  #define MDR_ADCUI_FxAC_b    MDR_ADCUI_FxAC_Bits
  #define MDR_ADCUI_FxMD0_b   MDR_ADCUI_FxMD0_Bits
  #define MDR_ADCUI_FxMD1_b   MDR_ADCUI_FxMD1_Bits
  #define MDR_ADCUI_FxMD2_b   MDR_ADCUI_FxMD2_Bits
  #define MDR_ADCUI_FxStat_b  MDR_ADCUI_FxStat_Bits
  #define MDR_ADCUI_FxMask_b  MDR_ADCUI_FxMask_Bits
#else
  #define MDR_ADCUI_F0CTR_b   MDR_ADCUI_F0CTR_CfgBits
  #define MDR_ADCUI_F0MD0_b   MDR_ADCUI_F0MD0_CfgBits
  #define MDR_ADCUI_F0Stat_b  MDR_ADCUI_F0Stat_CfgBits
  #define MDR_ADCUI_F0Mask_b  MDR_ADCUI_F0Mask_CfgBits

  #define MDR_ADCUI_FxCTR_b   MDR_ADCUI_FxCTR_CfgBits
  #define MDR_ADCUI_FxWC_b    MDR_ADCUI_FxWC_CfgBits
  #define MDR_ADCUI_FxVC_b    MDR_ADCUI_FxVC_CfgBits
  #define MDR_ADCUI_FxAC_b    MDR_ADCUI_FxAC_CfgBits
  #define MDR_ADCUI_FxMD0_b   MDR_ADCUI_FxMD0_CfgBits 
  #define MDR_ADCUI_FxMD1_b   MDR_ADCUI_FxMD1_CfgBits
  #define MDR_ADCUI_FxMD2_b   MDR_ADCUI_FxMD2_CfgBits
  #define MDR_ADCUI_FxStat_b  MDR_ADCUI_FxStat_CfgBits
  #define MDR_ADCUI_FxMask_b  MDR_ADCUI_FxMask_CfgBits
#endif


typedef struct {
  union {
    uint32_t                CTR;
    MDR_ADCUI_F0CTR_b       CTR_b;
  } ;  
  union {
    uint32_t                WC;
    MDR_ADCUI_FxWC_b        WC_b;
  } ;
  union {
    uint32_t                VC;
    MDR_ADCUI_FxVC_b        VC_b;
  } ;
  union {
    uint32_t                AC;
    MDR_ADCUI_FxAC_b        AC_b;
  } ;
  union {
    uint32_t                MD0;
    MDR_ADCUI_F0MD0_b       MD0_b;
  } ;
  union {
    uint32_t                MD1;
    MDR_ADCUI_FxMD1_b       MD1_b;
  } ;    
  union {
    uint32_t                STAT;
    MDR_ADCUI_F0Stat_b      STAT_b;
  } ;   
  union {
    uint32_t                MASK;
    MDR_ADCUI_F0Mask_b      MASK_b;
  } ;    
}  MDR_ADCUI_CFG_F0;

typedef struct {
  union {
    uint32_t                CTR;
    MDR_ADCUI_FxCTR_b       CTR_b;
  } ;  
  union {
    uint32_t                WC;
    MDR_ADCUI_FxWC_b        WC_b;
  } ;
  union {
    uint32_t                VC;
    MDR_ADCUI_FxVC_b        VC_b;
  } ;
  union {
    uint32_t                AC;
    MDR_ADCUI_FxAC_b        AC_b;
  } ;
  union {
    uint32_t                MD0;
    MDR_ADCUI_FxMD0_b       MD0_b;
  } ;
  union {
    uint32_t                MD1;
    MDR_ADCUI_FxMD1_b       MD1_b;
  } ;  
  union {
    uint32_t                MD2;
    MDR_ADCUI_FxMD2_b       MD2_b;
  } ;   
  union {
    uint32_t                STAT;
    MDR_ADCUI_FxStat_b      STAT_b;
  } ;     
  union {
    uint32_t                MASK;
    MDR_ADCUI_FxMask_b      MASK_b;
  } ;    
}  MDR_ADCUI_CFG_Fx;
  
typedef struct {
  uint32_t VBGAIN     : 12;           /*!< [11..0] V0 calibration gain                                               */
  uint32_t IBGAIN     : 12;           /*!< [23..12] I0 calibration gain                                              */
  uint32_t            : 8;
} MDR_ADCUI_CCALx_CfgBits;

typedef struct {
  uint32_t I3BGAIN    : 12;           /*!< [11..0] I3 calibration gain                                               */
  uint32_t            : 20;
} MDR_ADCUI_CCAL4_CfgBits;

#if USE_NATIVE_BITS
  #define MDR_ADCUI_CCALx_b   MDR_ADCUI_CCALx_Bits
  #define MDR_ADCUI_CCAL4_b   MDR_ADCUI_CCAL4_Bits
#else
  #define MDR_ADCUI_CCALx_b   MDR_ADCUI_CCALx_CfgBits
  #define MDR_ADCUI_CCAL4_b   MDR_ADCUI_CCAL4_CfgBits
#endif


typedef struct {
  union {
    uint32_t                CCAL1;
    MDR_ADCUI_CCALx_b       CCAL1_b;
  } ;
  union {
    uint32_t                CCAL2;
    MDR_ADCUI_CCALx_b       CCAL2_b;
  } ;
  union {
    uint32_t                CCAL3;
    MDR_ADCUI_CCALx_b       CCAL3_b;
  } ;  
  union {
    uint32_t                CCAL4;
    MDR_ADCUI_CCAL4_b       CCAL4_b;
  } ;
}  MDR_ADCUI_CFG_CAL;


typedef struct {
  MDR_ADCUI_CFG_CTRL Ctrl;
  
  MDR_ADCUI_CFG_F0   F0;
  MDR_ADCUI_CFG_Fx   F1;
  MDR_ADCUI_CFG_Fx   F2;
 
  MDR_ADCUI_CFG_CAL  Cal;
} MDR_ADCUI_CfgRegs;



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


#endif  // _MDR_ADCUI_VK234_CFG_H


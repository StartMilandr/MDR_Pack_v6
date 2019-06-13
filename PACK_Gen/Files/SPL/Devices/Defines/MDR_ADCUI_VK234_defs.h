#ifndef _MDR_ADCUI_VK234_DEFS_H
#define _MDR_ADCUI_VK234_DEFS_H

#include <MDR_ADCUI_VK2x4_defs.h>

#ifdef __cplusplus
extern "C" {
#endif
  
/* =========================================================  CTRL1  ======================================================== */    
typedef enum {
  ADCUI_ChopF_div2,
  ADCUI_ChopF_div4,
  ADCUI_ChopF_div8,
  ADCUI_ChopF_div16
} MDR_ADCUI_ChopDiv;
  
typedef __PACKED_STRUCT {
  __IOM MDR_OnOff                I0En : 1;            /*!< [0..0] Channel enable                                                     */
  __IOM MDR_OnOff                V0En : 1;            /*!< [1..1] Channel enable                                                     */
  __IOM MDR_OnOff                I1En : 1;            /*!< [0..0] Channel enable                                                     */
  __IOM MDR_OnOff                V1En : 1;            /*!< [1..1] Channel enable                                                     */
  __IOM MDR_OnOff                I2En : 1;            /*!< [0..0] Channel enable                                                     */
  __IOM MDR_OnOff                V2En : 1;            /*!< [1..1] Channel enable                                                     */
  __IOM MDR_OnOff                I3En : 1;            /*!< [6..6] Channel enable                                                     */
  __IOM MDR_ADCUI_Resol         Resol : 1;            /*!< [7..7] Data resolution                                                    */
  __IOM MDR_OnOff               ZXLPF : 1;            /*!< [8..8] V0 cross zero LPF enable                                           */
  __IOM MDR_ADCUI_Period   Per_Length : 3;            /*!< [11..9] Period to calc aver period and dPhase                             */
  __IOM MDR_ADCUI_NoLoad    AP_NoLoad : 2;            /*!< [13..12] Active Energy min level to accumulate                            */
  __IM  uint32_t                      : 1;
  __IOM MDR_ADCUI_NoLoad   VAR_NoLoad : 2;            /*!< [16..15] Reactive Energy min level to accumulate                          */
  __IOM MDR_ADCUI_NoLoad    VA_NoLoad : 2;            /*!< [18..17] Full Energy min level to accumulate                              */
  __IOM MDR_OnOff             FreqSel : 1;            /*!< [19..19] Enable V0 period detection to FxMD0.PER_FREQ                     */
  __IOM MDR_ADCUI_Vref        VrefSel : 1;            /*!< [20..20] ADC Vref select                                                  */
  __IOM MDR_OnOff             Buf_Byp : 1;            /*!< [21..21] Bypass Vref buffer                                               */
  __IOM MDR_OnOff             Chop_En : 1;            /*!< [22..22] Chopper Mode Select                                              */
  __IOM MDR_ADCUI_ChopDiv   Chop_Freq : 2;            /*!< [24..23] Chopper Frequency                                                */  
  __IM  uint32_t                      : 2;
  __IOM MDR_ADCUI_RMS_Update    ZXRMS : 1;            /*!< [27..27] RMS Update mode                                                  */
  __IOM MDR_OnOff           Reset_Dig : 1;            /*!< [28..28] Digital Logic Reset                                              */
  __IOM MDR_OnOff              IBoost : 1;            /*!< [29..29] Boost I mode                                                     */
  __IOM MDR_ADCUI_SampleRate OSR_Conf : 2;            /*!< [31..30] ADC Output Sampling Rate                                         */
} MDR_ADCUI_CTRL1_Bits;  

#define MDR_ADCUI_CTRL1_I0EN_Pos          (0UL)                     /*!< MDR_ADCUI CTRL1: I0EN (Bit 0)                         */
#define MDR_ADCUI_CTRL1_I0EN_Msk          (0x1UL)                   /*!< MDR_ADCUI CTRL1: I0EN (Bitfield-Mask: 0x01)           */
#define MDR_ADCUI_CTRL1_V0EN_Pos          (1UL)                     /*!< MDR_ADCUI CTRL1: V0EN (Bit 1)                         */
#define MDR_ADCUI_CTRL1_V0EN_Msk          (0x2UL)                   /*!< MDR_ADCUI CTRL1: V0EN (Bitfield-Mask: 0x01)           */
#define MDR_ADCUI_CTRL1_I1EN_Pos          (2UL)                     /*!< MDR_ADCUI CTRL1: I1EN (Bit 2)                         */
#define MDR_ADCUI_CTRL1_I1EN_Msk          (0x4UL)                   /*!< MDR_ADCUI CTRL1: I1EN (Bitfield-Mask: 0x01)           */
#define MDR_ADCUI_CTRL1_V1EN_Pos          (3UL)                     /*!< MDR_ADCUI CTRL1: V1EN (Bit 3)                         */
#define MDR_ADCUI_CTRL1_V1EN_Msk          (0x8UL)                   /*!< MDR_ADCUI CTRL1: V1EN (Bitfield-Mask: 0x01)           */
#define MDR_ADCUI_CTRL1_I2EN_Pos          (4UL)                     /*!< MDR_ADCUI CTRL1: I2EN (Bit 4)                         */
#define MDR_ADCUI_CTRL1_I2EN_Msk          (0x10UL)                  /*!< MDR_ADCUI CTRL1: I2EN (Bitfield-Mask: 0x01)           */
#define MDR_ADCUI_CTRL1_V2EN_Pos          (5UL)                     /*!< MDR_ADCUI CTRL1: V2EN (Bit 5)                         */
#define MDR_ADCUI_CTRL1_V2EN_Msk          (0x20UL)                  /*!< MDR_ADCUI CTRL1: V2EN (Bitfield-Mask: 0x01)           */
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
#define MDR_ADCUI_CTRL1_CHOP_EN_Pos       (22UL)                    /*!< MDR_ADCUI CTRL1: CHOP_EN (Bit 22)                     */
#define MDR_ADCUI_CTRL1_CHOP_EN_Msk       (0x400000UL)              /*!< MDR_ADCUI CTRL1: CHOP_EN (Bitfield-Mask: 0x01)        */
#define MDR_ADCUI_CTRL1_CHOP_FREQ_Pos     (23UL)                    /*!< MDR_ADCUI CTRL1: CHOP_FREQ (Bit 23)                   */
#define MDR_ADCUI_CTRL1_CHOP_FREQ_Msk     (0x1800000UL)             /*!< MDR_ADCUI CTRL1: CHOP_FREQ (Bitfield-Mask: 0x03)      */
#define MDR_ADCUI_CTRL1_ZXRMS_Pos         (27UL)                    /*!< MDR_ADCUI CTRL1: ZXRMS (Bit 27)                       */
#define MDR_ADCUI_CTRL1_ZXRMS_Msk         (0x8000000UL)             /*!< MDR_ADCUI CTRL1: ZXRMS (Bitfield-Mask: 0x01)          */
#define MDR_ADCUI_CTRL1_RESET_DIG_Pos     (28UL)                    /*!< MDR_ADCUI CTRL1: RESET_DIG (Bit 28)                   */
#define MDR_ADCUI_CTRL1_RESET_DIG_Msk     (0x10000000UL)            /*!< MDR_ADCUI CTRL1: RESET_DIG (Bitfield-Mask: 0x01)      */
#define MDR_ADCUI_CTRL1_IBOOST_Pos        (29UL)                    /*!< MDR_ADCUI CTRL1: IBOOST (Bit 29)                      */
#define MDR_ADCUI_CTRL1_IBOOST_Msk        (0x20000000UL)            /*!< MDR_ADCUI CTRL1: IBOOST (Bitfield-Mask: 0x01)         */
#define MDR_ADCUI_CTRL1_OSR_CONF_Pos      (30UL)                    /*!< MDR_ADCUI CTRL1: OSR_CONF (Bit 30)                    */
#define MDR_ADCUI_CTRL1_OSR_CONF_Msk      (0xc0000000UL)            /*!< MDR_ADCUI CTRL1: OSR_CONF (Bitfield-Mask: 0x03)       */

/* =========================================================  FxCTR  ======================================================== */    
typedef struct {
    __IOM MDR_OnOff          INTEn : 1;            /*!< [0..0] Integrator enable                                                  */
    __IM  uint32_t                 : 1;            /*!< [1..1] Integrator enable                                                  */
    __IOM MDR_ADCUI_VASel    VASel : 1;            /*!< [2..2] Select source for FullEnergy                                       */
    __OM  MDR_OnOff           RARS : 1;            /*!< [3..3] Active Energy Accumulator Reset                                    */
    __OM  MDR_OnOff           RRRS : 1;            /*!< [4..4] Reactive Energy Accumulator Reset                                  */
    __OM  MDR_OnOff           RVRS : 1;            /*!< [5..5] Full Energy Accumulator Reset                                      */
    __IOM MDR_ADCUI_PGA      IGain : 2;            /*!< [7..6] PGA value                                                          */
    __IOM MDR_ADCUI_PGA      VGain : 2;            /*!< [9..8] PGA value                                                          */
    __IOM uint32_t          VPhase : 8;            /*!< [17..10] Phase V0 adjustment by step of +-124us                           */
    __IM  uint32_t                 : 2;            /*!< [19..18] PGA value                                                        */
    __IOM uint32_t          IRMSOS : 12;           /*!< [31..20] RMS calibration of channel I                                     */
} MDR_ADCUI_FxCTR_Bits;

#define MDR_ADCUI_FxCTR_INTEN_Pos         (0UL)                     /*!< MDR_ADCUI F1CTR: INTEN (Bit 0)                        */
#define MDR_ADCUI_FxCTR_INTEN_Msk         (0x1UL)                   /*!< MDR_ADCUI F1CTR: INTEN (Bitfield-Mask: 0x01)          */
#define MDR_ADCUI_FxCTR_VASEL_Pos         (2UL)                     /*!< MDR_ADCUI F1CTR: VASEL (Bit 2)                        */
#define MDR_ADCUI_FxCTR_VASEL_Msk         (0x4UL)                   /*!< MDR_ADCUI F1CTR: VASEL (Bitfield-Mask: 0x01)          */
#define MDR_ADCUI_FxCTR_RARS_Pos          (3UL)                     /*!< MDR_ADCUI F1CTR: RARS (Bit 3)                         */
#define MDR_ADCUI_FxCTR_RARS_Msk          (0x8UL)                   /*!< MDR_ADCUI F1CTR: RARS (Bitfield-Mask: 0x01)           */
#define MDR_ADCUI_FxCTR_RRRS_Pos          (4UL)                     /*!< MDR_ADCUI F1CTR: RRRS (Bit 4)                         */
#define MDR_ADCUI_FxCTR_RRRS_Msk          (0x10UL)                  /*!< MDR_ADCUI F1CTR: RRRS (Bitfield-Mask: 0x01)           */
#define MDR_ADCUI_FxCTR_RVRS_Pos          (5UL)                     /*!< MDR_ADCUI F1CTR: RVRS (Bit 5)                         */
#define MDR_ADCUI_FxCTR_RVRS_Msk          (0x20UL)                  /*!< MDR_ADCUI F1CTR: RVRS (Bitfield-Mask: 0x01)           */
#define MDR_ADCUI_FxCTR_IGAIN_Pos         (6UL)                     /*!< MDR_ADCUI F1CTR: IGAIN (Bit 6)                        */
#define MDR_ADCUI_FxCTR_IGAIN_Msk         (0xc0UL)                  /*!< MDR_ADCUI F1CTR: IGAIN (Bitfield-Mask: 0x03)          */
#define MDR_ADCUI_FxCTR_VGAIN_Pos         (8UL)                     /*!< MDR_ADCUI F1CTR: VGAIN (Bit 8)                        */
#define MDR_ADCUI_FxCTR_VGAIN_Msk         (0x300UL)                 /*!< MDR_ADCUI F1CTR: VGAIN (Bitfield-Mask: 0x03)          */
#define MDR_ADCUI_FxCTR_VPHASE_Pos        (10UL)                    /*!< MDR_ADCUI F1CTR: VPHASE (Bit 10)                      */
#define MDR_ADCUI_FxCTR_VPHASE_Msk        (0x3fc00UL)               /*!< MDR_ADCUI F1CTR: VPHASE (Bitfield-Mask: 0xff)         */
#define MDR_ADCUI_FxCTR_IRMSOS_Pos        (20UL)                    /*!< MDR_ADCUI F1CTR: IRMSOS (Bit 20)                      */
#define MDR_ADCUI_FxCTR_IRMSOS_Msk        (0xfff00000UL)            /*!< MDR_ADCUI F1CTR: IRMSOS (Bitfield-Mask: 0xfff)        */

/* =========================================================  FxMD0  ======================================================== */    
typedef struct {
  __IOM MDR_ADCUI_VDAT_Sel      VSel : 2;            /*!< [1..0] Select source for FxVDAT                                           */
  __IOM MDR_ADCUI_IDAT_Sel      ISel : 2;            /*!< [3..2] Select source for FxIDAT                                          */
  __IM  MDR_ADCUI_Sign          ActS : 1;            /*!< [4..4] Active Energy sign in last period                                  */
  __IM  MDR_ADCUI_Sign        ReactS : 1;            /*!< [5..5] Reactive Energy sign in last period                                */
  __IOM MDR_ADCUI_DecimGain    IGain : 1;            /*!< [6..6] ADC Decimation gain                                                */
  __IOM MDR_ADCUI_DecimGain    VGain : 1;            /*!< [7..7] ADC Decimation gain                                                */
  __IM  uint32_t                     : 4;
  __IM  uint32_t            Per_Freq : 17;           /*!< [28..12] Measured period of V                                             */
  __IM  uint32_t                     : 3;
} MDR_ADCUI_FxMD0_Bits;

#define MDR_ADCUI_FxMD0_VSEL_Pos          (0UL)                     /*!< MDR_ADCUI F1MD0: VSEL (Bit 0)                         */
#define MDR_ADCUI_FxMD0_VSEL_Msk          (0x3UL)                   /*!< MDR_ADCUI F1MD0: VSEL (Bitfield-Mask: 0x03)           */
#define MDR_ADCUI_FxMD0_ISEL_Pos          (2UL)                     /*!< MDR_ADCUI F1MD0: ISEL (Bit 2)                         */
#define MDR_ADCUI_FxMD0_ISEL_Msk          (0xcUL)                   /*!< MDR_ADCUI F1MD0: ISEL (Bitfield-Mask: 0x03)           */
#define MDR_ADCUI_FxMD0_ACTS_Pos          (4UL)                     /*!< MDR_ADCUI F1MD0: ACTS (Bit 4)                         */
#define MDR_ADCUI_FxMD0_ACTS_Msk          (0x10UL)                  /*!< MDR_ADCUI F1MD0: ACTS (Bitfield-Mask: 0x01)           */
#define MDR_ADCUI_FxMD0_REACTS_Pos        (5UL)                     /*!< MDR_ADCUI F1MD0: REACTS (Bit 5)                       */
#define MDR_ADCUI_FxMD0_REACTS_Msk        (0x20UL)                  /*!< MDR_ADCUI F1MD0: REACTS (Bitfield-Mask: 0x01)         */
#define MDR_ADCUI_FxMD0_IGAIN_Pos         (6UL)                     /*!< MDR_ADCUI F1MD0: IGAIN (Bit 6)                        */
#define MDR_ADCUI_FxMD0_IGAIN_Msk         (0x40UL)                  /*!< MDR_ADCUI F1MD0: IGAIN (Bitfield-Mask: 0x01)          */
#define MDR_ADCUI_FxMD0_VGAIN_Pos         (7UL)                     /*!< MDR_ADCUI F1MD0: VGAIN (Bit 7)                        */
#define MDR_ADCUI_FxMD0_VGAIN_Msk         (0x80UL)                  /*!< MDR_ADCUI F1MD0: VGAIN (Bitfield-Mask: 0x01)          */
#define MDR_ADCUI_FxMD0_PER_FREQ_Pos      (12UL)                    /*!< MDR_ADCUI F1MD0: PER_FREQ (Bit 12)                    */
#define MDR_ADCUI_FxMD0_PER_FREQ_Msk      (0x1ffff000UL)            /*!< MDR_ADCUI F1MD0: PER_FREQ (Bitfield-Mask: 0x1ffff)    */

/* =========================================================  FxMD2  ======================================================== */
typedef struct {
  __IOM uint32_t Phase      : 16;           /*!< [15..0] Vx phase to V0                                                        */
  __IM uint32_t             : 16;
} MDR_ADCUI_FxMD2_Bits;

#define MDR_ADCUI_FxMD2_PhaseV_toV0_Pos   (0UL)                     /*!< MDR_ADCUI F1MD2: PhaseV_toV0 (Bit 0)                  */
#define MDR_ADCUI_FxMD2_PhaseV_toV0_Msk   (0x1ffffUL)               /*!< MDR_ADCUI F1MD2: PhaseV_toV0 (Bitfield-Mask: 0x1ffff) */

/* ======================================================  FxStat  ==================================================== */
typedef struct {
  __IM  MDR_OnOff VF_EMP     : 1;            /*!< [0..0] FIFO_VDAT is Empty                                                 */
  __IM  MDR_OnOff VF_FLL     : 1;            /*!< [1..1] FIFO_VDAT is Full                                                  */
  __IOM MDR_OnOff VF_OVER    : 1;            /*!< [2..2] FIFO_VDAT is Overflow                                              */
  __IM  MDR_OnOff IF_EMP     : 1;            /*!< [3..3] FIFO_IDAT is Empty                                                 */
  __IM  MDR_OnOff IF_FLL     : 1;            /*!< [4..4] FIFO_IDAT is Full                                                  */
  __IOM MDR_OnOff IF_OVER    : 1;            /*!< [5..5] FIFO_IDAT is Overflow                                              */
  __IOM MDR_OnOff SAGF       : 1;            /*!< [6..6] V is less than CTRL2.SAGLVL                                        */
  __IOM MDR_OnOff PEAKVF     : 1;            /*!< [7..7] V exceeds F0MD1.VPKLVL                                             */
  __IOM MDR_OnOff PEAKIF     : 1;            /*!< [8..8] I exceeds F0MD1.VPKLVL                                             */
  __IOM MDR_OnOff WATTOVP    : 1;            /*!< [9..9] FxWATTP value overflow                                             */
  __IOM MDR_OnOff VAROVP     : 1;            /*!< [10..10] FxVARP value overflow                                            */
  __IOM MDR_OnOff VAOV       : 1;            /*!< [11..11] FxVR value overflow                                              */
  __IOM MDR_OnOff ZTXVF      : 1;            /*!< [12..12] Timeout of V cross zero                                          */
  __IM  uint32_t             : 2;
  __IOM MDR_OnOff APSIGN     : 1;            /*!< [15..15] ActivePower sign changed                                         */
  __IM  MDR_OnOff APNLDFL    : 1;            /*!< [16..16] ActivePower less CNTL1.APNOLOAD                                  */
  __IOM MDR_OnOff VARSIGN    : 1;            /*!< [17..17] ReactivePower sign changed                                       */
  __IM  MDR_OnOff VARNLDFL   : 1;            /*!< [18..18] ReactivePower less CNTL1.VARNOLOAD                               */
  __IM  uint32_t             : 1;
  __IM  MDR_OnOff VANLDFL    : 1;            /*!< [20..20] FullPower less CNTL1.VANOLOAD                                    */
  __IOM MDR_OnOff ZEROCRS    : 1;            /*!< [21..21] V crossed zero                                                   */
  __IM  uint32_t             : 3;
  __IOM MDR_OnOff WATTOVN    : 1;            /*!< [25..25] FxWATTN value overflow                                           */
  __IOM MDR_OnOff VAROVN     : 1;            /*!< [26..26] FxVARN value overflow                                            */
  __IM  uint32_t             : 5;
} MDR_ADCUI_FxStat_Bits;

//  Use all Fx masks from MDR_ADCUI_F0Stat_Bits description in MDR_ADCUI_VK2x4_defs.h

/* ======================================================  FxMask  ==================================================== */
typedef struct {
  __IOM MDR_OnOff VF_EMPM    : 1;            /*!< [0..0] FIFO_VDAT is Empty                                                 */
  __IOM MDR_OnOff VF_FLLM    : 1;            /*!< [1..1] FIFO_VDAT is Full                                                  */
  __IOM MDR_OnOff VF_OVERM   : 1;            /*!< [2..2] FIFO_VDAT is Overflow                                              */
  __IOM MDR_OnOff IF_EMPM    : 1;            /*!< [3..3] FIFO_IDAT is Empty                                                 */
  __IOM MDR_OnOff IF_FLLM    : 1;            /*!< [4..4] FIFO_IDAT is Full                                                  */
  __IOM MDR_OnOff IF_OVERM   : 1;            /*!< [5..5] FIFO_IDAT is Overflow                                              */
  __IOM MDR_OnOff SAGFM      : 1;            /*!< [6..6] V is less than CTRL2.SAGLVL                                        */
  __IOM MDR_OnOff PEAKVFM    : 1;            /*!< [7..7] V exceeds F0MD1.VPKLVL                                             */
  __IOM MDR_OnOff PEAKIFM    : 1;            /*!< [8..8] I exceeds F0MD1.VPKLVL                                             */
  __IOM MDR_OnOff WATTOVPM   : 1;            /*!< [9..9] FxWATTP value overflow                                             */
  __IOM MDR_OnOff VAROVPM    : 1;            /*!< [10..10] FxVARP value overflow                                            */
  __IOM MDR_OnOff VAOVM      : 1;            /*!< [11..11] FxVR value overflow                                              */
  __IOM MDR_OnOff ZTXVFM     : 1;            /*!< [12..12] Timeout of V cross zero                                          */
  __IM  uint32_t             : 2;
  __IOM MDR_OnOff APSIGNM    : 1;            /*!< [15..15] ActivePower sign changed                                         */
  __IOM MDR_OnOff APNLDFLM   : 1;            /*!< [16..16] ActivePower less CNTL1.APNOLOAD                                  */
  __IOM MDR_OnOff VARSIGNM   : 1;            /*!< [17..17] ReactivePower sign changed                                       */
  __IOM MDR_OnOff VARNLDFLM  : 1;            /*!< [18..18] ReactivePower less CNTL1.VARNOLOAD                               */
  __IM  uint32_t             : 1;
  __IOM MDR_OnOff VANLDFLM   : 1;            /*!< [20..20] FullPower less CNTL1.VANOLOAD                                    */
  __IOM MDR_OnOff ZEROCRSM   : 1;            /*!< [21..21] V crossed zero                                                   */
  __IM  uint32_t             : 3;
  __IOM MDR_OnOff WATTOVNM   : 1;            /*!< [25..25] FxWATTN value overflow                                           */
  __IOM MDR_OnOff VAROVNM    : 1;            /*!< [26..26] FxVARN value overflow                                            */
  __IM  uint32_t             : 5;
} MDR_ADCUI_FxMask_Bits;

//  Use all Fx masks from MDR_ADCUI_F0Mask_Bits description in MDR_ADCUI_VK2x4_defs.h

/* ======================================================  CCALC2  ==================================================== */
typedef struct {
  __IOM uint32_t V1BGAIN    : 12;           /*!< [11..0] V1 calibration gain                                               */
  __IOM uint32_t I1BGAIN    : 12;           /*!< [23..12] I1 calibration gain                                              */
  __IM  uint32_t            : 8;
} MDR_ADCUI_CCAL2_Bits;

#define MDR_ADCUI_CCAL2_V1BGAIN_Pos       (0UL)                     /*!< MDR_ADCUI CCAL2: V1BGAIN (Bit 0)                      */
#define MDR_ADCUI_CCAL2_V1BGAIN_Msk       (0xfffUL)                 /*!< MDR_ADCUI CCAL2: V1BGAIN (Bitfield-Mask: 0xfff)       */
#define MDR_ADCUI_CCAL2_I1BGAIN_Pos       (12UL)                    /*!< MDR_ADCUI CCAL2: I1BGAIN (Bit 12)                     */
#define MDR_ADCUI_CCAL2_I1BGAIN_Msk       (0xfff000UL)              /*!< MDR_ADCUI CCAL2: I1BGAIN (Bitfield-Mask: 0xfff)       */


/* ======================================================  CCALC3  ==================================================== */
typedef struct {
  __IOM uint32_t V2BGAIN    : 12;           /*!< [11..0] V2 calibration gain                                               */
  __IOM uint32_t I2BGAIN    : 12;           /*!< [23..12] I2 calibration gain                                              */
  __IM  uint32_t            : 8;
} MDR_ADCUI_CCAL3_Bits;

#define MDR_ADCUI_CCAL3_V2BGAIN_Pos       (0UL)                     /*!< MDR_ADCUI CCAL3: V2BGAIN (Bit 0)                      */
#define MDR_ADCUI_CCAL3_V2BGAIN_Msk       (0xfffUL)                 /*!< MDR_ADCUI CCAL3: V2BGAIN (Bitfield-Mask: 0xfff)       */
#define MDR_ADCUI_CCAL3_I2BGAIN_Pos       (12UL)                    /*!< MDR_ADCUI CCAL3: I2BGAIN (Bit 12)                     */
#define MDR_ADCUI_CCAL3_I2BGAIN_Msk       (0xfff000UL)              /*!< MDR_ADCUI CCAL3: I2BGAIN (Bitfield-Mask: 0xfff)       */


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
  
  //  ============  Channel F1  ==================
  union {
    __IOM uint32_t          F1CTR;               /*!< (@ 0x0000000C) FxCTR register                                             */
    MDR_ADCUI_FxCTR_Bits    F1CTR_b;
  } ;  
  union {
    __IOM uint32_t          F1WC;                /*!< (@ 0x00000010) Active energy calibration                                  */
    MDR_ADCUI_FxWC_Bits     F1WC_b;
  } ;  
  union {
    __IM  uint32_t          F1WATTP;             /*!< (@ 0x00000014) Positive Active Energy accumulator                         */
    MDR_ADCUI_FxWattP_Bits  F1WATTP_b;
  } ;  
  union {
    __IM  uint32_t          F1WATTN;             /*!< (@ 0x00000018) Negative Active Energy accumulator                         */
    MDR_ADCUI_FxWattN_Bits  F1WATTN_b;
  } ;  
  union {
    __IOM uint32_t          F1VC;                /*!< (@ 0x0000001C) Reactive energy calibration                                */
    MDR_ADCUI_FxVC_Bits     F1VC_b;
  } ;
  union {
    __IM  uint32_t          F1VARP;              /*!< (@ 0x00000020) Positive Reactive Energy accumulator                       */
    MDR_ADCUI_FxVarP_Bits   F1VARP_b;
  } ;  
  union {
    __IM  uint32_t          F1VARN;              /*!< (@ 0x00000024) Negative Reactive Energy accumulator                       */
    MDR_ADCUI_FxVarN_Bits   F1VARN_b;
  } ;
  union {
    __IOM uint32_t          F1AC;                /*!< (@ 0x00000028) V0 RMS calibration                                         */
    MDR_ADCUI_FxAC_Bits     F1AC_b;
  } ;
  union {
    __IM  uint32_t          F1VR;                /*!< (@ 0x0000002C) Full Energy accumulator                                    */
    MDR_ADCUI_FxVR_Bits     F1VR_b;
  } ;  
  union {
    __IOM uint32_t          F1MD0;               /*!< (@ 0x00000030) FxMD0 register                                             */
    MDR_ADCUI_FxMD0_Bits    F1MD0_b;
  } ;
  union {
    __IOM uint32_t          F1MD1;               /*!< (@ 0x00000034) FxMD1 register                                             */
    MDR_ADCUI_FxMD1_Bits    F1MD1_b;
  } ;
  union {
    __IOM uint32_t          F1MD2;               /*!< (@ 0x00000034) FxMD1 register                                             */
    MDR_ADCUI_FxMD2_Bits    F1MD2_b;
  } ;    
  union {
    __IOM uint32_t          F1VPEAK;             /*!< (@ 0x00000038) VPEAK Result register                                      */
    MDR_ADCUI_Result24_Bits F1VPEAK_b;
  } ;
  union {
    __IOM uint32_t          F1IPEAK;             /*!< (@ 0x0000003C) IPEAK Result register                                      */
    MDR_ADCUI_Result24_Bits F1IPEAK_b;
  } ;
  union {
    __IM  uint32_t          F1VDAT;              /*!< (@ 0x00000040) VDAT Result register                                       */
    MDR_ADCUI_Result24_Bits F1VDAT_b;
  } ;
  union {
    __IM  uint32_t          F1IDAT;             /*!< (@ 0x00000044) I0DAT Result register                                      */
    MDR_ADCUI_Result24_Bits F1IDAT_b;
  } ;  
  union {
    __IM  uint32_t          F1VRMS;              /*!< (@ 0x0000004C) VRMS Result register                                       */
    MDR_ADCUI_Result24_Bits F1VRMS_b;
  } ;
  union {
    __IM  uint32_t          F1VRMS2;             /*!< (@ 0x00000050) VRMS^2 Result register                                     */
    MDR_ADCUI_Result24_Bits F1VRMS2_b;
  } ;
  union {
    __IM  uint32_t          F1IRMS;              /*!< (@ 0x00000054) IRMS Result register                                       */
    MDR_ADCUI_Result24_Bits F1IRMS_b;
  } ;
  union {
    __IM  uint32_t          F1IRMS2;             /*!< (@ 0x00000058) IRMS^2 Result register                                     */
    MDR_ADCUI_Result24_Bits F1IRMS2_b;
  } ; 
  union {
    __IOM uint32_t          F1STAT;              /*!< (@ 0x0000005C) Status Register                                            */
    MDR_ADCUI_FxStat_Bits   F1STAT_b;
  } ;
  union {
    __IOM uint32_t          F1MASK;              /*!< (@ 0x00000060) IRQ Mask Register                                          */
    MDR_ADCUI_FxMask_Bits   F1MASK_b;
  } ;  
  //  ============  Channel F2  ==================  
  union {
    __IOM uint32_t          F2CTR;               /*!< (@ 0x0000000C) FxCTR register                                             */
    MDR_ADCUI_FxCTR_Bits    F2CTR_b;
  } ;  
  union {
    __IOM uint32_t          F2WC;                /*!< (@ 0x00000010) Active energy calibration                                  */
    MDR_ADCUI_FxWC_Bits     F2WC_b;
  } ;  
  union {
    __IM  uint32_t          F2WATTP;             /*!< (@ 0x00000014) Positive Active Energy accumulator                         */
    MDR_ADCUI_FxWattP_Bits  F2WATTP_b;
  } ;  
  union {
    __IM  uint32_t          F2WATTN;             /*!< (@ 0x00000018) Negative Active Energy accumulator                         */
    MDR_ADCUI_FxWattN_Bits  F2WATTN_b;
  } ;  
  union {
    __IOM uint32_t          F2VC;                /*!< (@ 0x0000001C) Reactive energy calibration                                */
    MDR_ADCUI_FxVC_Bits     F2VC_b;
  } ;
  union {
    __IM  uint32_t          F2VARP;              /*!< (@ 0x00000020) Positive Reactive Energy accumulator                       */
    MDR_ADCUI_FxVarP_Bits   F2VARP_b;
  } ;  
  union {
    __IM  uint32_t          F2VARN;              /*!< (@ 0x00000024) Negative Reactive Energy accumulator                       */
    MDR_ADCUI_FxVarN_Bits   F2VARN_b;
  } ;
  union {
    __IOM uint32_t          F2AC;                /*!< (@ 0x00000028) V0 RMS calibration                                         */
    MDR_ADCUI_FxAC_Bits     F2AC_b;
  } ;
  union {
    __IM  uint32_t          F2VR;                /*!< (@ 0x0000002C) Full Energy accumulator                                    */
    MDR_ADCUI_FxVR_Bits     F2VR_b;
  } ;  
  union {
    __IOM uint32_t          F2MD0;               /*!< (@ 0x00000030) FxMD0 register                                             */
    MDR_ADCUI_FxMD0_Bits    F2MD0_b;
  } ;
  union {
    __IOM uint32_t          F2MD1;               /*!< (@ 0x00000034) FxMD1 register                                             */
    MDR_ADCUI_FxMD1_Bits    F2MD1_b;
  } ;
  union {
    __IOM uint32_t          F2MD2;               /*!< (@ 0x00000034) FxMD1 register                                             */
    MDR_ADCUI_FxMD2_Bits    F2MD2_b;
  } ;    
  union {
    __IOM uint32_t          F2VPEAK;             /*!< (@ 0x00000038) VPEAK Result register                                      */
    MDR_ADCUI_Result24_Bits F2VPEAK_b;
  } ;
  union {
    __IOM uint32_t          F2IPEAK;             /*!< (@ 0x0000003C) IPEAK Result register                                      */
    MDR_ADCUI_Result24_Bits F2IPEAK_b;
  } ;
  union {
    __IM  uint32_t          F2VDAT;              /*!< (@ 0x00000040) VDAT Result register                                       */
    MDR_ADCUI_Result24_Bits F2VDAT_b;
  } ;
  union {
    __IM  uint32_t          F2IDAT;             /*!< (@ 0x00000044) I0DAT Result register                                      */
    MDR_ADCUI_Result24_Bits F2IDAT_b;
  } ;  
  union {
    __IM  uint32_t          F2VRMS;              /*!< (@ 0x0000004C) VRMS Result register                                       */
    MDR_ADCUI_Result24_Bits F2VRMS_b;
  } ;
  union {
    __IM  uint32_t          F2VRMS2;             /*!< (@ 0x00000050) VRMS^2 Result register                                     */
    MDR_ADCUI_Result24_Bits F2VRMS2_b;
  } ;
  union {
    __IM  uint32_t          F2IRMS;              /*!< (@ 0x00000054) IRMS Result register                                       */
    MDR_ADCUI_Result24_Bits F2IRMS_b;
  } ;
  union {
    __IM  uint32_t          F2IRMS2;             /*!< (@ 0x00000058) IRMS^2 Result register                                     */
    MDR_ADCUI_Result24_Bits F2IRMS2_b;
  } ; 
  union {
    __IOM uint32_t          F2STAT;              /*!< (@ 0x0000005C) Status Register                                            */
    MDR_ADCUI_FxStat_Bits   F2STAT_b;
  } ;
  union {
    __IOM uint32_t          F2MASK;              /*!< (@ 0x00000060) IRQ Mask Register                                          */
    MDR_ADCUI_FxMask_Bits   F2MASK_b;
  } ;
  //  ============  Calibration  ==================  
  union {
    __IOM uint32_t          CCAL1;               /*!< (@ 0x00000114) Calibration Register 1                                     */
    MDR_ADCUI_CCAL1_Bits    CCAL1_b;
  } ;
  union {
    __IOM uint32_t          CCAL2;               /*!< (@ 0x00000118) Calibration Register 2                                     */
    MDR_ADCUI_CCAL2_Bits    CCAL2_b;
  } ;
  union {
    __IOM uint32_t          CCAL3;               /*!< (@ 0x0000011C) Calibration Register 3                                     */
    MDR_ADCUI_CCAL3_Bits    CCAL3_b;
  } ;  
  union {
    __IOM uint32_t          CCAL4;               /*!< (@ 0x00000120) Calibration Register 4                                     */
    MDR_ADCUI_CCAL4_Bits    CCAL4_b;
  } ;
} MDR_ADCUI_TypeDef;



#ifdef __cplusplus
}
#endif

#endif  //  _MDR_ADCUI_VK234_DEFS_H

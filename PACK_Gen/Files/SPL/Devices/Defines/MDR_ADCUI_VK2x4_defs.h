#ifndef _MDR_ADCIU_VK2X4_DEFS_H
#define _MDR_ADCIU_VK2X4_DEFS_H

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

/* =========================================================  CTRL1  ======================================================== */

typedef enum {
  ADCUI_out16,
  ADCUI_out24,
} MDR_ADCUI_Resol;

typedef enum {
  ADCUI_Per1,
  ADCUI_Per2,
  ADCUI_Per4,
  ADCUI_Per8,
  ADCUI_Per16,
  ADCUI_Per32,
  ADCUI_Per64,
  ADCUI_Per128
} MDR_ADCUI_Period;

typedef enum {
  ADCUI_NoLoad_0,
  ADCUI_NoLoad_0p012,
  ADCUI_NoLoad_0p0061,
  ADCUI_NoLoad_0p00305
} MDR_ADCUI_NoLoad;

typedef enum {
  ADCUI_VrefInt,
  ADCUI_VrefExt
} MDR_ADCUI_Vref;

typedef enum {
  ADCUI_RMS_Continuous,
  ADCUI_RMS_VcrsZero
} MDR_ADCUI_RMS_Update;

typedef enum {
  ADCUI_SRate_4KHz,
  ADCUI_SRate_8KHz,
  ADCUI_SRate_16KHz,
  ADCUI_SRate_reserved
} MDR_ADCUI_SampleRate;

/* =========================================================  CTRL2  ======================================================== */
typedef struct {
  __IOM uint32_t  SAGLVL     : 16;                    /*!< [15..0] V0 min OK level                                                   */
  __IOM uint32_t  SAGCYC     : 8;                     /*!< [23..16] Count of V0 half periods to calc V0 level                        */
  __IM  uint32_t             : 8;
} MDR_ADCUI_CTRL2_Bits;

#define MDR_ADCUI_CTRL2_SAGLVL_Pos        (0UL)                     /*!< MDR_ADCUI CTRL2: SAGLVL (Bit 0)                       */
#define MDR_ADCUI_CTRL2_SAGLVL_Msk        (0xffffUL)                /*!< MDR_ADCUI CTRL2: SAGLVL (Bitfield-Mask: 0xffff)       */
#define MDR_ADCUI_CTRL2_SAGCYC_Pos        (16UL)                    /*!< MDR_ADCUI CTRL2: SAGCYC (Bit 16)                      */
#define MDR_ADCUI_CTRL2_SAGCYC_Msk        (0xff0000UL)              /*!< MDR_ADCUI CTRL2: SAGCYC (Bitfield-Mask: 0xff)         */

/* =========================================================  CTRL3  ======================================================== */
typedef struct {
  __IOM uint32_t  ZTXOUT     : 12;                    /*!< [11..0] V0 cross zero timeout                                             */
  __IM  uint32_t             : 10;
} MDR_ADCUI_CTRL3_Bits;

#define MDR_ADCUI_CTRL3_ZTXOUT_Pos        (0UL)                     /*!< MDR_ADCUI CTRL3: ZTXOUT (Bit 0)                       */
#define MDR_ADCUI_CTRL3_ZTXOUT_Msk        (0xfffUL)                 /*!< MDR_ADCUI CTRL3: ZTXOUT (Bitfield-Mask: 0xfff)        */

/* =========================================================  F0CTR  ======================================================== */

typedef enum {
  ADCUI_VASEL_VA,
  ADCUI_VASEL_IRMS
} MDR_ADCUI_VASel;

typedef enum {
  ADCUI_PGA_x1,
  ADCUI_PGA_x2,
  ADCUI_PGA_x4,
  ADCUI_PGA_x8,
} MDR_ADCUI_PGA;

typedef struct {
    __IOM MDR_OnOff       I0NT_Dis : 1;            /*!< [0..0] Integrator disable                                                  */
    __IOM MDR_OnOff       I3NT_Dis : 1;            /*!< [1..1] Integrator disable                                                  */
    __IOM MDR_ADCUI_VASel    VASel : 1;            /*!< [2..2] Select source for FullEnergy                                       */
    __OM  MDR_OnOff           RARS : 1;            /*!< [3..3] Active Energy Accumulator Reset                                    */
    __OM  MDR_OnOff           RRRS : 1;            /*!< [4..4] Reactive Energy Accumulator Reset                                  */
    __OM  MDR_OnOff           RVRS : 1;            /*!< [5..5] Full Energy Accumulator Reset                                      */
    __IOM MDR_ADCUI_PGA     V0Gain : 2;            /*!< [7..6] PGA value                                                          */
    __IOM MDR_ADCUI_PGA     I0Gain : 2;            /*!< [9..8] PGA value                                                          */
    __IOM uint32_t          VPhase : 8;            /*!< [17..10] Phase V0 adjustment by step of +-124us                           */
    __IOM MDR_ADCUI_PGA     I3Gain : 2;            /*!< [19..18] PGA value                                                        */
    __IOM uint32_t          IRMSOS : 12;           /*!< [31..20] RMS calibration of channel I                                     */
} MDR_ADCUI_F0CTR_Bits;

#define MDR_ADCUI_F0CTR_I0NTEN_Pos        (0UL)                     /*!< MDR_ADCUI F0CTR: I0NTEN (Bit 0)                       */
#define MDR_ADCUI_F0CTR_I0NTEN_Msk        (0x1UL)                   /*!< MDR_ADCUI F0CTR: I0NTEN (Bitfield-Mask: 0x01)         */
#define MDR_ADCUI_F0CTR_I3NTEN_Pos        (1UL)                     /*!< MDR_ADCUI F0CTR: I3NTEN (Bit 1)                       */
#define MDR_ADCUI_F0CTR_I3NTEN_Msk        (0x2UL)                   /*!< MDR_ADCUI F0CTR: I3NTEN (Bitfield-Mask: 0x01)         */
#define MDR_ADCUI_F0CTR_VASEL_Pos         (2UL)                     /*!< MDR_ADCUI F0CTR: VASEL (Bit 2)                        */
#define MDR_ADCUI_F0CTR_VASEL_Msk         (0x4UL)                   /*!< MDR_ADCUI F0CTR: VASEL (Bitfield-Mask: 0x01)          */
#define MDR_ADCUI_F0CTR_RARS_Pos          (3UL)                     /*!< MDR_ADCUI F0CTR: RARS (Bit 3)                         */
#define MDR_ADCUI_F0CTR_RARS_Msk          (0x8UL)                   /*!< MDR_ADCUI F0CTR: RARS (Bitfield-Mask: 0x01)           */
#define MDR_ADCUI_F0CTR_RRRS_Pos          (4UL)                     /*!< MDR_ADCUI F0CTR: RRRS (Bit 4)                         */
#define MDR_ADCUI_F0CTR_RRRS_Msk          (0x10UL)                  /*!< MDR_ADCUI F0CTR: RRRS (Bitfield-Mask: 0x01)           */
#define MDR_ADCUI_F0CTR_RVRS_Pos          (5UL)                     /*!< MDR_ADCUI F0CTR: RVRS (Bit 5)                         */
#define MDR_ADCUI_F0CTR_RVRS_Msk          (0x20UL)                  /*!< MDR_ADCUI F0CTR: RVRS (Bitfield-Mask: 0x01)           */
#define MDR_ADCUI_F0CTR_V0GAIN_Pos        (6UL)                     /*!< MDR_ADCUI F0CTR: I0GAIN (Bit 6)                       */
#define MDR_ADCUI_F0CTR_V0GAIN_Msk        (0xc0UL)                  /*!< MDR_ADCUI F0CTR: I0GAIN (Bitfield-Mask: 0x03)         */
#define MDR_ADCUI_F0CTR_I0GAIN_Pos        (8UL)                     /*!< MDR_ADCUI F0CTR: VGAIN (Bit 8)                        */
#define MDR_ADCUI_F0CTR_I0GAIN_Msk        (0x300UL)                 /*!< MDR_ADCUI F0CTR: VGAIN (Bitfield-Mask: 0x03)          */
#define MDR_ADCUI_F0CTR_VPHASE_Pos        (10UL)                    /*!< MDR_ADCUI F0CTR: VPHASE (Bit 10)                      */
#define MDR_ADCUI_F0CTR_VPHASE_Msk        (0x3fc00UL)               /*!< MDR_ADCUI F0CTR: VPHASE (Bitfield-Mask: 0xff)         */
#define MDR_ADCUI_F0CTR_I3GAIN_Pos        (18UL)                    /*!< MDR_ADCUI F0CTR: I3GAIN (Bit 18)                      */
#define MDR_ADCUI_F0CTR_I3GAIN_Msk        (0xc0000UL)               /*!< MDR_ADCUI F0CTR: I3GAIN (Bitfield-Mask: 0x03)         */
#define MDR_ADCUI_F0CTR_IRMSOS_Pos        (20UL)                    /*!< MDR_ADCUI F0CTR: IRMSOS (Bit 20)                      */
#define MDR_ADCUI_F0CTR_IRMSOS_Msk        (0xfff00000UL)            /*!< MDR_ADCUI F0CTR: IRMSOS (Bitfield-Mask: 0xfff)        */

#define MDR_ADCUI_F0CTR_SUM_OFF_I0      MDR_ADCUI_F0CTR_I0NTEN_Msk
#define MDR_ADCUI_F0CTR_SUM_OFF_I3      MDR_ADCUI_F0CTR_I3NTEN_Msk


/* =========================================================  FxWC  ======================================================== */
typedef struct {
  __IOM uint32_t WattOS     : 16;           /*!< [15..0] Calibr bias of active energy                                      */
  __IOM uint32_t WattGain   : 12;           /*!< [27..16] Calibr gain of active energy                                     */
  __IM  uint32_t            : 4;
} MDR_ADCUI_FxWC_Bits;

#define MDR_ADCUI_FxWC_WATTOS_Pos         (0UL)                     /*!< MDR_ADCUI F0WC: WATTOS (Bit 0)                        */
#define MDR_ADCUI_FxWC_WATTOS_Msk         (0xffffUL)                /*!< MDR_ADCUI F0WC: WATTOS (Bitfield-Mask: 0xffff)        */
#define MDR_ADCUI_FxWC_WGAIN_Pos          (16UL)                    /*!< MDR_ADCUI F0WC: WGAIN (Bit 16)                        */
#define MDR_ADCUI_FxWC_WGAIN_Msk          (0xfff0000UL)             /*!< MDR_ADCUI F0WC: WGAIN (Bitfield-Mask: 0xfff)          */

/* =========================================================  FxWATTP, FxWATTN  ============================================= */
typedef struct {
  __IM  uint32_t WattHRP    : 32;           /*!< [31..0] High 32 bits of Accumulator                                       */
} MDR_ADCUI_FxWattP_Bits;

typedef struct {
  __IM  uint32_t WattHRN    : 32;           /*!< [31..0] High 32 bits of Accumulator                                       */
} MDR_ADCUI_FxWattN_Bits;

/* =========================================================  FxVC  ======================================================== */
typedef struct {
  __IOM uint32_t VarOS      : 16;           /*!< [15..0] Calibr bias of active energy                                      */
  __IOM uint32_t VarGain    : 12;           /*!< [27..16] Calibr gain of active energy                                     */
  __IM  uint32_t            : 4;
} MDR_ADCUI_FxVC_Bits;

#define MDR_ADCUI_FxVC_VAROS_Pos          (0UL)                     /*!< MDR_ADCUI F0VC: VAROS (Bit 0)                         */
#define MDR_ADCUI_FxVC_VAROS_Msk          (0xffffUL)                /*!< MDR_ADCUI F0VC: VAROS (Bitfield-Mask: 0xffff)         */
#define MDR_ADCUI_FxVC_VARGAIN_Pos        (16UL)                    /*!< MDR_ADCUI F0VC: VARGAIN (Bit 16)                      */
#define MDR_ADCUI_FxVC_VARGAIN_Msk        (0xfff0000UL)             /*!< MDR_ADCUI F0VC: VARGAIN (Bitfield-Mask: 0xfff)        */

/* =========================================================  FxVARP, FxVARN  ============================================= */
typedef struct {
  __IM  uint32_t VarHRP    : 32;           /*!< [31..0] High 32 bits of Accumulator                                       */
} MDR_ADCUI_FxVarP_Bits;

typedef struct {
  __IM  uint32_t VarHRN    : 32;           /*!< [31..0] High 32 bits of Accumulator                                       */
} MDR_ADCUI_FxVarN_Bits;

/* =========================================================  FxAC  ======================================================== */
typedef struct {
  __IOM uint32_t VRMSOS     : 12;           /*!< [11..0] Calibr bias of V0 RMS                                             */
  __IM  uint32_t            : 4;
  __IOM uint32_t VAGain     : 12;           /*!< [27..16] Calibr gain of Full energy                                       */
  __IM  uint32_t            : 4;
} MDR_ADCUI_FxAC_Bits;

#define MDR_ADCUI_FxAC_VRMSOS_Pos         (0UL)                     /*!< MDR_ADCUI F0AC: VRMSOS (Bit 0)                        */
#define MDR_ADCUI_FxAC_VRMSOS_Msk         (0xfffUL)                 /*!< MDR_ADCUI F0AC: VRMSOS (Bitfield-Mask: 0xfff)         */
#define MDR_ADCUI_FxAC_VAGAIN_Pos         (16UL)                    /*!< MDR_ADCUI F0AC: VAGAIN (Bit 16)                       */
#define MDR_ADCUI_FxAC_VAGAIN_Msk         (0xfff0000UL)             /*!< MDR_ADCUI F0AC: VAGAIN (Bitfield-Mask: 0xfff)         */

/* =========================================================  FxVR  ======================================================== */
typedef struct {
  __IM  uint32_t VAHR       : 32;           /*!< [31..0] High 32 bits of of 57bits Accumulator                             */
} MDR_ADCUI_FxVR_Bits;

/* =========================================================  F0MD0  ======================================================== */
typedef enum {
  ADCUI_VDAT_V,
  ADCUI_VDAT_Pact,
  ADCUI_VDAT_Prea,
  ADCUI_VDAT_Pfull
} MDR_ADCUI_VDAT_Sel;

typedef enum {
  ADCUI_IDAT_I,
  ADCUI_IDAT_Pact,
  ADCUI_IDAT_Prea,
  ADCUI_IDAT_Pfull
} MDR_ADCUI_IDAT_Sel;

typedef enum {
  ADCUI_I3DAT_ADC,
  ADCUI_I3DAT_HPF
} MDR_ADCUI_I3DAT_Sel;

typedef enum {
  ADCUI_Sign_Pos,
  ADCUI_Sign_New
} MDR_ADCUI_Sign;

typedef enum {
  ADCUI_DecimGain_x1,
  ADCUI_DecimGain_x2
} MDR_ADCUI_DecimGain;

typedef enum {
  ADCUI_UsedI_Auto,
  ADCUI_UsedI_I0,
  ADCUI_UsedI_I3,
  ADCUI_UsedI_res
} MDR_ADCUI_SelI;

typedef struct {
  __IOM MDR_ADCUI_VDAT_Sel      VSel : 2;            /*!< [1..0] Select source for FxVDAT                                           */
  __IOM MDR_ADCUI_IDAT_Sel      ISel : 2;            /*!< [3..2] Select source for FxI0DAT                                          */
  __IM  MDR_ADCUI_Sign          ActS : 1;            /*!< [4..4] Active Energy sign in last period                                  */
  __IM  MDR_ADCUI_Sign        ReactS : 1;            /*!< [5..5] Reactive Energy sign in last period                                */
  __IOM MDR_ADCUI_DecimGain   I0Gain : 1;            /*!< [6..6] ADC Decimation gain                                                */
  __IOM MDR_ADCUI_DecimGain   V0Gain : 1;            /*!< [7..7] ADC Decimation gain                                                */
  __IOM MDR_ADCUI_DecimGain   I3Gain : 1;            /*!< [8..8] ADC Decimation gain                                                */
  __IM  uint32_t                     : 3;
  __IM  uint32_t            Per_Freq : 17;           /*!< [28..12] Measured period of V                                             */
  __IOM MDR_ADCUI_I3DAT_Sel    I3Sel : 1;            /*!< [29..29] Select source for FxI3DAT                                        */
  __IOM MDR_ADCUI_SelI      Sel_I_Ch : 2;            /*!< [31..30] Select I for calc power                                          */
} MDR_ADCUI_F0MD0_Bits;

#define MDR_ADCUI_F0MD0_V0SEL_Pos          (0UL)                     /*!< MDR_ADCUI F0MD0: VSEL (Bit 0)                         */
#define MDR_ADCUI_F0MD0_V0SEL_Msk          (0x3UL)                   /*!< MDR_ADCUI F0MD0: VSEL (Bitfield-Mask: 0x03)           */
#define MDR_ADCUI_F0MD0_I0SEL_Pos          (2UL)                     /*!< MDR_ADCUI F0MD0: ISEL (Bit 2)                         */
#define MDR_ADCUI_F0MD0_I0SEL_Msk          (0xcUL)                   /*!< MDR_ADCUI F0MD0: ISEL (Bitfield-Mask: 0x03)           */
#define MDR_ADCUI_F0MD0_ACTS_Pos          (4UL)                     /*!< MDR_ADCUI F0MD0: ACTS (Bit 4)                         */
#define MDR_ADCUI_F0MD0_ACTS_Msk          (0x10UL)                  /*!< MDR_ADCUI F0MD0: ACTS (Bitfield-Mask: 0x01)           */
#define MDR_ADCUI_F0MD0_REACTS_Pos        (5UL)                     /*!< MDR_ADCUI F0MD0: REACTS (Bit 5)                       */
#define MDR_ADCUI_F0MD0_REACTS_Msk        (0x20UL)                  /*!< MDR_ADCUI F0MD0: REACTS (Bitfield-Mask: 0x01)         */
#define MDR_ADCUI_F0MD0_I0GAIN_Pos        (6UL)                     /*!< MDR_ADCUI F0MD0: IOGAIN (Bit 6)                       */
#define MDR_ADCUI_F0MD0_I0GAIN_Msk        (0x40UL)                  /*!< MDR_ADCUI F0MD0: IOGAIN (Bitfield-Mask: 0x01)         */
#define MDR_ADCUI_F0MD0_V0GAIN_Pos        (7UL)                     /*!< MDR_ADCUI F0MD0: V0GAIN (Bit 7)                       */
#define MDR_ADCUI_F0MD0_V0GAIN_Msk        (0x80UL)                  /*!< MDR_ADCUI F0MD0: V0GAIN (Bitfield-Mask: 0x01)         */
#define MDR_ADCUI_F0MD0_I3GAIN_Pos        (8UL)                     /*!< MDR_ADCUI F0MD0: I3GAIN (Bit 8)                       */
#define MDR_ADCUI_F0MD0_I3GAIN_Msk        (0x100UL)                 /*!< MDR_ADCUI F0MD0: I3GAIN (Bitfield-Mask: 0x01)         */
#define MDR_ADCUI_F0MD0_PER_FREQ_Pos      (12UL)                    /*!< MDR_ADCUI F0MD0: PER_FREQ (Bit 12)                    */
#define MDR_ADCUI_F0MD0_PER_FREQ_Msk      (0x1ffff000UL)            /*!< MDR_ADCUI F0MD0: PER_FREQ (Bitfield-Mask: 0x1ffff)    */
#define MDR_ADCUI_F0MD0_I3SEL_Pos         (29UL)                    /*!< MDR_ADCUI F0MD0: I3SEL (Bit 29)                       */
#define MDR_ADCUI_F0MD0_I3SEL_Msk         (0x20000000UL)            /*!< MDR_ADCUI F0MD0: I3SEL (Bitfield-Mask: 0x01)          */
#define MDR_ADCUI_F0MD0_SEL_I_CH_Pos      (30UL)                    /*!< MDR_ADCUI F0MD0: SEL_I_CH (Bit 30)                    */
#define MDR_ADCUI_F0MD0_SEL_I_CH_Msk      (0xc0000000UL)            /*!< MDR_ADCUI F0MD0: SEL_I_CH (Bitfield-Mask: 0x03)       */

/* =========================================================  FxMD1  ======================================================== */
typedef struct {
  __IOM uint32_t IPKLvl     : 16;           /*!< [15..0] Imax level                                                        */
  __IOM uint32_t VPKLvl     : 16;           /*!< [31..16] Vmax level                                                       */
} MDR_ADCUI_FxMD1_Bits;

#define MDR_ADCUI_FxMD1_IPKLVL_Pos        (0UL)                     /*!< MDR_ADCUI F0MD1: IPKLVL (Bit 0)                       */
#define MDR_ADCUI_FxMD1_IPKLVL_Msk        (0xffffUL)                /*!< MDR_ADCUI F0MD1: IPKLVL (Bitfield-Mask: 0xffff)       */
#define MDR_ADCUI_FxMD1_VPKLVL_Pos        (16UL)                    /*!< MDR_ADCUI F0MD1: VPKLVL (Bit 16)                      */
#define MDR_ADCUI_FxMD1_VPKLVL_Msk        (0xffff0000UL)            /*!< MDR_ADCUI F0MD1: VPKLVL (Bitfield-Mask: 0xffff)       */

/* =====================FxVPeak, FxIPeak, FxVDAT, FxIDAT, FxI3DAT, FxVRMS, FxVRMS2, FxIRMS, FxIRMS2 ====================== */
typedef struct {
  __IOM uint32_t value     : 24;           /*!< [15..0] Result value                                                      */
  __IM  uint32_t           : 8;
} MDR_ADCUI_Result24_Bits;

#define MDR_ADCUI_Result24_Pos       (0UL)                     /*!< MDR_ADCUI F0VPEAK: IPEAK (Bit 0)                      */
#define MDR_ADCUI_Result24_Msk       (0xffffffUL)              /*!< MDR_ADCUI F0VPEAK: IPEAK (Bitfield-Mask: 0xffffff)    */

/* ======================================================  F0Stat  ==================================================== */
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
  __IM  MDR_OnOff ICHANNEL   : 1;            /*!< [13..13] Timeout of V cross zero                                          */
  __IOM MDR_OnOff FAULTCON   : 1;            /*!< [14..14] Active I switched                                                */
  __IOM MDR_OnOff APSIGN     : 1;            /*!< [15..15] ActivePower sign changed                                         */
  __IM  MDR_OnOff APNLDFL    : 1;            /*!< [16..16] ActivePower less CNTL1.APNOLOAD                                  */
  __IOM MDR_OnOff VARSIGN    : 1;            /*!< [17..17] ReactivePower sign changed                                       */
  __IM  MDR_OnOff VARNLDFL   : 1;            /*!< [18..18] ReactivePower less CNTL1.VARNOLOAD                               */
  __IM  uint32_t             : 1;
  __IM  MDR_OnOff VANLDFL    : 1;            /*!< [20..20] FullPower less CNTL1.VANOLOAD                                    */
  __IOM MDR_OnOff ZEROCRS    : 1;            /*!< [21..21] V crossed zero                                                   */
  __IM  MDR_OnOff I3F_EMP    : 1;            /*!< [22..22] FIFO_I3DAT is Empty                                              */
  __IM  MDR_OnOff I3F_FLL    : 1;            /*!< [23..23] FIFO_I3DAT is Full                                               */
  __IOM MDR_OnOff I3F_OVER   : 1;            /*!< [24..24] FIFO_I3DAT is Overflow                                           */
  __IOM MDR_OnOff WATTOVN    : 1;            /*!< [25..25] FxWATTN value overflow                                           */
  __IOM MDR_OnOff VAROVN     : 1;            /*!< [26..26] FxVARN value overflow                                            */
  __IM  uint32_t             : 5;
} MDR_ADCUI_F0Stat_Bits;

#define MDR_ADCUI_FxSTAT_VF_EMP_Pos       (0UL)                     /*!< MDR_ADCUI F1STAT: VF_EMP (Bit 0)                      */
#define MDR_ADCUI_FxSTAT_VF_EMP_Msk       (0x1UL)                   /*!< MDR_ADCUI F1STAT: VF_EMP (Bitfield-Mask: 0x01)        */
#define MDR_ADCUI_FxSTAT_VF_FLL_Pos       (1UL)                     /*!< MDR_ADCUI F1STAT: VF_FLL (Bit 1)                      */
#define MDR_ADCUI_FxSTAT_VF_FLL_Msk       (0x2UL)                   /*!< MDR_ADCUI F1STAT: VF_FLL (Bitfield-Mask: 0x01)        */
#define MDR_ADCUI_FxSTAT_VF_OVER_Pos      (2UL)                     /*!< MDR_ADCUI F1STAT: VF_OVER (Bit 2)                     */
#define MDR_ADCUI_FxSTAT_VF_OVER_Msk      (0x4UL)                   /*!< MDR_ADCUI F1STAT: VF_OVER (Bitfield-Mask: 0x01)       */
#define MDR_ADCUI_FxSTAT_IF_EMP_Pos       (3UL)                     /*!< MDR_ADCUI F1STAT: IF_EMP (Bit 3)                      */
#define MDR_ADCUI_FxSTAT_IF_EMP_Msk       (0x8UL)                   /*!< MDR_ADCUI F1STAT: IF_EMP (Bitfield-Mask: 0x01)        */
#define MDR_ADCUI_FxSTAT_IF_FLL_Pos       (4UL)                     /*!< MDR_ADCUI F1STAT: IF_FLL (Bit 4)                      */
#define MDR_ADCUI_FxSTAT_IF_FLL_Msk       (0x10UL)                  /*!< MDR_ADCUI F1STAT: IF_FLL (Bitfield-Mask: 0x01)        */
#define MDR_ADCUI_FxSTAT_IF_OVER_Pos      (5UL)                     /*!< MDR_ADCUI F1STAT: IF_OVER (Bit 5)                     */
#define MDR_ADCUI_FxSTAT_IF_OVER_Msk      (0x20UL)                  /*!< MDR_ADCUI F1STAT: IF_OVER (Bitfield-Mask: 0x01)       */
#define MDR_ADCUI_FxSTAT_SAGF_Pos         (6UL)                     /*!< MDR_ADCUI F1STAT: SAGF (Bit 6)                        */
#define MDR_ADCUI_FxSTAT_SAGF_Msk         (0x40UL)                  /*!< MDR_ADCUI F1STAT: SAGF (Bitfield-Mask: 0x01)          */
#define MDR_ADCUI_FxSTAT_PEAKVF_Pos       (7UL)                     /*!< MDR_ADCUI F1STAT: PEAKVF (Bit 7)                      */
#define MDR_ADCUI_FxSTAT_PEAKVF_Msk       (0x80UL)                  /*!< MDR_ADCUI F1STAT: PEAKVF (Bitfield-Mask: 0x01)        */
#define MDR_ADCUI_FxSTAT_PEAKIF_Pos       (8UL)                     /*!< MDR_ADCUI F1STAT: PEAKIF (Bit 8)                      */
#define MDR_ADCUI_FxSTAT_PEAKIF_Msk       (0x100UL)                 /*!< MDR_ADCUI F1STAT: PEAKIF (Bitfield-Mask: 0x01)        */
#define MDR_ADCUI_FxSTAT_WATTOVP_Pos      (9UL)                     /*!< MDR_ADCUI F1STAT: WATTOVP (Bit 9)                     */
#define MDR_ADCUI_FxSTAT_WATTOVP_Msk      (0x200UL)                 /*!< MDR_ADCUI F1STAT: WATTOVP (Bitfield-Mask: 0x01)       */
#define MDR_ADCUI_FxSTAT_VAROVP_Pos       (10UL)                    /*!< MDR_ADCUI F1STAT: VAROVP (Bit 10)                     */
#define MDR_ADCUI_FxSTAT_VAROVP_Msk       (0x400UL)                 /*!< MDR_ADCUI F1STAT: VAROVP (Bitfield-Mask: 0x01)        */
#define MDR_ADCUI_FxSTAT_VAOV_Pos         (11UL)                    /*!< MDR_ADCUI F1STAT: VAOV (Bit 11)                       */
#define MDR_ADCUI_FxSTAT_VAOV_Msk         (0x800UL)                 /*!< MDR_ADCUI F1STAT: VAOV (Bitfield-Mask: 0x01)          */
#define MDR_ADCUI_FxSTAT_ZTXVF_Pos        (12UL)                    /*!< MDR_ADCUI F1STAT: ZTXVF (Bit 12)                      */
#define MDR_ADCUI_FxSTAT_ZTXVF_Msk        (0x1000UL)                /*!< MDR_ADCUI F1STAT: ZTXVF (Bitfield-Mask: 0x01)         */

#define MDR_ADCUI_F0STAT_ICHANNEL_Pos     (13UL)                    /*!< MDR_ADCUI F0STAT: ICHANNEL (Bit 13)                   */
#define MDR_ADCUI_F0STAT_ICHANNEL_Msk     (0x2000UL)                /*!< MDR_ADCUI F0STAT: ICHANNEL (Bitfield-Mask: 0x01)      */
#define MDR_ADCUI_F0STAT_FAULTCON_Pos     (14UL)                    /*!< MDR_ADCUI F0STAT: FAULTCON (Bit 14)                   */
#define MDR_ADCUI_F0STAT_FAULTCON_Msk     (0x4000UL)                /*!< MDR_ADCUI F0STAT: FAULTCON (Bitfield-Mask: 0x01)      */

#define MDR_ADCUI_FxSTAT_APSIGN_Pos       (15UL)                    /*!< MDR_ADCUI F1STAT: APSIGN (Bit 15)                     */
#define MDR_ADCUI_FxSTAT_APSIGN_Msk       (0x8000UL)                /*!< MDR_ADCUI F1STAT: APSIGN (Bitfield-Mask: 0x01)        */
#define MDR_ADCUI_FxSTAT_APNLDFL_Pos      (16UL)                    /*!< MDR_ADCUI F1STAT: APNLDFL (Bit 16)                    */
#define MDR_ADCUI_FxSTAT_APNLDFL_Msk      (0x10000UL)               /*!< MDR_ADCUI F1STAT: APNLDFL (Bitfield-Mask: 0x01)       */
#define MDR_ADCUI_FxSTAT_VARSIGN_Pos      (17UL)                    /*!< MDR_ADCUI F1STAT: VARSIGN (Bit 17)                    */
#define MDR_ADCUI_FxSTAT_VARSIGN_Msk      (0x20000UL)               /*!< MDR_ADCUI F1STAT: VARSIGN (Bitfield-Mask: 0x01)       */
#define MDR_ADCUI_FxSTAT_VARNLDFL_Pos     (18UL)                    /*!< MDR_ADCUI F1STAT: VARNLDFL (Bit 18)                   */
#define MDR_ADCUI_FxSTAT_VARNLDFL_Msk     (0x40000UL)               /*!< MDR_ADCUI F1STAT: VARNLDFL (Bitfield-Mask: 0x01)      */
#define MDR_ADCUI_FxSTAT_VANLDFL_Pos      (20UL)                    /*!< MDR_ADCUI F1STAT: VANLDFL (Bit 20)                    */
#define MDR_ADCUI_FxSTAT_VANLDFL_Msk      (0x100000UL)              /*!< MDR_ADCUI F1STAT: VANLDFL (Bitfield-Mask: 0x01)       */
#define MDR_ADCUI_FxSTAT_ZEROCRS_Pos      (21UL)                    /*!< MDR_ADCUI F1STAT: ZEROCRS (Bit 21)                    */
#define MDR_ADCUI_FxSTAT_ZEROCRS_Msk      (0x200000UL)              /*!< MDR_ADCUI F1STAT: ZEROCRS (Bitfield-Mask: 0x01)       */

#define MDR_ADCUI_F0STAT_I3F_EMP_Pos      (22UL)                    /*!< MDR_ADCUI F0STAT: I3F_EMP (Bit 22)                    */
#define MDR_ADCUI_F0STAT_I3F_EMP_Msk      (0x400000UL)              /*!< MDR_ADCUI F0STAT: I3F_EMP (Bitfield-Mask: 0x01)       */
#define MDR_ADCUI_F0STAT_I3F_FLL_Pos      (23UL)                    /*!< MDR_ADCUI F0STAT: I3F_FLL (Bit 23)                    */
#define MDR_ADCUI_F0STAT_I3F_FLL_Msk      (0x800000UL)              /*!< MDR_ADCUI F0STAT: I3F_FLL (Bitfield-Mask: 0x01)       */
#define MDR_ADCUI_F0STAT_I3F_OVER_Pos     (24UL)                    /*!< MDR_ADCUI F0STAT: I3F_OVER (Bit 24)                   */
#define MDR_ADCUI_F0STAT_I3F_OVER_Msk     (0x1000000UL)             /*!< MDR_ADCUI F0STAT: I3F_OVER (Bitfield-Mask: 0x01)      */

#define MDR_ADCUI_FxSTAT_WATTOVN_Pos      (25UL)                    /*!< MDR_ADCUI F1STAT: WATTOVN (Bit 25)                    */
#define MDR_ADCUI_FxSTAT_WATTOVN_Msk      (0x2000000UL)             /*!< MDR_ADCUI F1STAT: WATTOVN (Bitfield-Mask: 0x01)       */
#define MDR_ADCUI_FxSTAT_VAROVN_Pos       (26UL)                    /*!< MDR_ADCUI F1STAT: VAROVN (Bit 26)                     */
#define MDR_ADCUI_FxSTAT_VAROVN_Msk       (0x4000000UL)             /*!< MDR_ADCUI F1STAT: VAROVN (Bitfield-Mask: 0x01)        */

#define MDR_ADCUI_STATUS_CLEAR     0x00722DFE4UL

/* ======================================================  F0Mask  ==================================================== */
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
  __IM  uint32_t             : 1;
  __IOM MDR_OnOff FAULTCONM  : 1;            /*!< [14..14] Active I switched                                                */
  __IOM MDR_OnOff APSIGNM    : 1;            /*!< [15..15] ActivePower sign changed                                         */
  __IOM MDR_OnOff APNLDFLM   : 1;            /*!< [16..16] ActivePower less CNTL1.APNOLOAD                                  */
  __IOM MDR_OnOff VARSIGNM   : 1;            /*!< [17..17] ReactivePower sign changed                                       */
  __IOM MDR_OnOff VARNLDFLM  : 1;            /*!< [18..18] ReactivePower less CNTL1.VARNOLOAD                               */
  __IM  uint32_t             : 1;
  __IOM MDR_OnOff VANLDFLM   : 1;            /*!< [20..20] FullPower less CNTL1.VANOLOAD                                    */
  __IOM MDR_OnOff ZEROCRSM   : 1;            /*!< [21..21] V crossed zero                                                   */
  __IOM MDR_OnOff I3F_EMPM   : 1;            /*!< [22..22] FIFO_I3DAT is Empty                                              */
  __IOM MDR_OnOff I3F_FLLM   : 1;            /*!< [23..23] FIFO_I3DAT is Full                                               */
  __IOM MDR_OnOff I3F_OVERM  : 1;            /*!< [24..24] FIFO_I3DAT is Overflow                                           */
  __IOM MDR_OnOff WATTOVNM   : 1;            /*!< [25..25] FxWATTN value overflow                                           */
  __IOM MDR_OnOff VAROVNM    : 1;            /*!< [26..26] FxVARN value overflow                                            */
  __IM  uint32_t             : 5;
} MDR_ADCUI_F0Mask_Bits;

//  Fx Masks for All channels F0, F1, F2
//  F0 Masks for F0 channel only
#define MDR_ADCUI_FxMASK_VF_EMPM_Pos      (0UL)                     /*!< MDR_ADCUI F0MASK: VF_EMPM (Bit 0)                     */
#define MDR_ADCUI_FxMASK_VF_EMPM_Msk      (0x1UL)                   /*!< MDR_ADCUI F0MASK: VF_EMPM (Bitfield-Mask: 0x01)       */
#define MDR_ADCUI_FxMASK_VF_FLLM_Pos      (1UL)                     /*!< MDR_ADCUI F0MASK: VF_FLLM (Bit 1)                     */
#define MDR_ADCUI_FxMASK_VF_FLLM_Msk      (0x2UL)                   /*!< MDR_ADCUI F0MASK: VF_FLLM (Bitfield-Mask: 0x01)       */
#define MDR_ADCUI_FxMASK_VF_OVERM_Pos     (2UL)                     /*!< MDR_ADCUI F0MASK: VF_OVERM (Bit 2)                    */
#define MDR_ADCUI_FxMASK_VF_OVERM_Msk     (0x4UL)                   /*!< MDR_ADCUI F0MASK: VF_OVERM (Bitfield-Mask: 0x01)      */
#define MDR_ADCUI_FxMASK_IF_EMPM_Pos      (3UL)                     /*!< MDR_ADCUI F0MASK: IF_EMPM (Bit 3)                     */
#define MDR_ADCUI_FxMASK_IF_EMPM_Msk      (0x8UL)                   /*!< MDR_ADCUI F0MASK: IF_EMPM (Bitfield-Mask: 0x01)       */
#define MDR_ADCUI_FxMASK_IF_FLLM_Pos      (4UL)                     /*!< MDR_ADCUI F0MASK: IF_FLLM (Bit 4)                     */
#define MDR_ADCUI_FxMASK_IF_FLLM_Msk      (0x10UL)                  /*!< MDR_ADCUI F0MASK: IF_FLLM (Bitfield-Mask: 0x01)       */
#define MDR_ADCUI_FxMASK_IF_OVERM_Pos     (5UL)                     /*!< MDR_ADCUI F0MASK: IF_OVERM (Bit 5)                    */
#define MDR_ADCUI_FxMASK_IF_OVERM_Msk     (0x20UL)                  /*!< MDR_ADCUI F0MASK: IF_OVERM (Bitfield-Mask: 0x01)      */
#define MDR_ADCUI_FxMASK_SAGFM_Pos        (6UL)                     /*!< MDR_ADCUI F0MASK: SAGFM (Bit 6)                       */
#define MDR_ADCUI_FxMASK_SAGFM_Msk        (0x40UL)                  /*!< MDR_ADCUI F0MASK: SAGFM (Bitfield-Mask: 0x01)         */
#define MDR_ADCUI_FxMASK_PEAKVFM_Pos      (7UL)                     /*!< MDR_ADCUI F0MASK: PEAKVFM (Bit 7)                     */
#define MDR_ADCUI_FxMASK_PEAKVFM_Msk      (0x80UL)                  /*!< MDR_ADCUI F0MASK: PEAKVFM (Bitfield-Mask: 0x01)       */
#define MDR_ADCUI_FxMASK_PEAKIFM_Pos      (8UL)                     /*!< MDR_ADCUI F0MASK: PEAKIFM (Bit 8)                     */
#define MDR_ADCUI_FxMASK_PEAKIFM_Msk      (0x100UL)                 /*!< MDR_ADCUI F0MASK: PEAKIFM (Bitfield-Mask: 0x01)       */
#define MDR_ADCUI_FxMASK_WATTOVPM_Pos     (9UL)                     /*!< MDR_ADCUI F0MASK: WATTOVPM (Bit 9)                    */
#define MDR_ADCUI_FxMASK_WATTOVPM_Msk     (0x200UL)                 /*!< MDR_ADCUI F0MASK: WATTOVPM (Bitfield-Mask: 0x01)      */
#define MDR_ADCUI_FxMASK_VAROVPM_Pos      (10UL)                    /*!< MDR_ADCUI F0MASK: VAROVPM (Bit 10)                    */
#define MDR_ADCUI_FxMASK_VAROVPM_Msk      (0x400UL)                 /*!< MDR_ADCUI F0MASK: VAROVPM (Bitfield-Mask: 0x01)       */
#define MDR_ADCUI_FxMASK_VAOVM_Pos        (11UL)                    /*!< MDR_ADCUI F0MASK: VAOVM (Bit 11)                      */
#define MDR_ADCUI_FxMASK_VAOVM_Msk        (0x800UL)                 /*!< MDR_ADCUI F0MASK: VAOVM (Bitfield-Mask: 0x01)         */
#define MDR_ADCUI_FxMASK_ZTXVFM_Pos       (12UL)                    /*!< MDR_ADCUI F0MASK: ZTXVFM (Bit 12)                     */
#define MDR_ADCUI_FxMASK_ZTXVFM_Msk       (0x1000UL)                /*!< MDR_ADCUI F0MASK: ZTXVFM (Bitfield-Mask: 0x01)        */

#define MDR_ADCUI_F0MASK_FAULTCONM_Pos    (14UL)                    /*!< MDR_ADCUI F0MASK: FAULTCONM (Bit 14)                  */
#define MDR_ADCUI_F0MASK_FAULTCONM_Msk    (0x4000UL)                /*!< MDR_ADCUI F0MASK: FAULTCONM (Bitfield-Mask: 0x01)     */

#define MDR_ADCUI_FxMASK_APSIGNM_Pos      (15UL)                    /*!< MDR_ADCUI F0MASK: APSIGNM (Bit 15)                    */
#define MDR_ADCUI_FxMASK_APSIGNM_Msk      (0x8000UL)                /*!< MDR_ADCUI F0MASK: APSIGNM (Bitfield-Mask: 0x01)       */
#define MDR_ADCUI_FxMASK_APNLDFLM_Pos     (16UL)                    /*!< MDR_ADCUI F0MASK: APNLDFLM (Bit 16)                   */
#define MDR_ADCUI_FxMASK_APNLDFLM_Msk     (0x10000UL)               /*!< MDR_ADCUI F0MASK: APNLDFLM (Bitfield-Mask: 0x01)      */
#define MDR_ADCUI_FxMASK_VARSIGNM_Pos     (17UL)                    /*!< MDR_ADCUI F0MASK: VARSIGNM (Bit 17)                   */
#define MDR_ADCUI_FxMASK_VARSIGNM_Msk     (0x20000UL)               /*!< MDR_ADCUI F0MASK: VARSIGNM (Bitfield-Mask: 0x01)      */
#define MDR_ADCUI_FxMASK_VARNLDFLM_Pos    (18UL)                    /*!< MDR_ADCUI F0MASK: VARNLDFLM (Bit 18)                  */
#define MDR_ADCUI_FxMASK_VARNLDFLM_Msk    (0x40000UL)               /*!< MDR_ADCUI F0MASK: VARNLDFLM (Bitfield-Mask: 0x01)     */
#define MDR_ADCUI_FxMASK_VANLDFLM_Pos     (20UL)                    /*!< MDR_ADCUI F0MASK: VANLDFLM (Bit 20)                   */
#define MDR_ADCUI_FxMASK_VANLDFLM_Msk     (0x100000UL)              /*!< MDR_ADCUI F0MASK: VANLDFLM (Bitfield-Mask: 0x01)      */
#define MDR_ADCUI_FxMASK_ZEROCRSM_Pos     (21UL)                    /*!< MDR_ADCUI F0MASK: ZEROCRSM (Bit 21)                   */
#define MDR_ADCUI_FxMASK_ZEROCRSM_Msk     (0x200000UL)              /*!< MDR_ADCUI F0MASK: ZEROCRSM (Bitfield-Mask: 0x01)      */

#define MDR_ADCUI_F0MASK_I3F_EMPM_Pos     (22UL)                    /*!< MDR_ADCUI F0MASK: I3F_EMPM (Bit 22)                   */
#define MDR_ADCUI_F0MASK_I3F_EMPM_Msk     (0x400000UL)              /*!< MDR_ADCUI F0MASK: I3F_EMPM (Bitfield-Mask: 0x01)      */
#define MDR_ADCUI_F0MASK_I3F_FLLM_Pos     (23UL)                    /*!< MDR_ADCUI F0MASK: I3F_FLLM (Bit 23)                   */
#define MDR_ADCUI_F0MASK_I3F_FLLM_Msk     (0x800000UL)              /*!< MDR_ADCUI F0MASK: I3F_FLLM (Bitfield-Mask: 0x01)      */
#define MDR_ADCUI_F0MASK_I3F_OVERM_Pos    (24UL)                    /*!< MDR_ADCUI F0MASK: I3F_OVERM (Bit 24)                  */
#define MDR_ADCUI_F0MASK_I3F_OVERM_Msk    (0x1000000UL)             /*!< MDR_ADCUI F0MASK: I3F_OVERM (Bitfield-Mask: 0x01)     */

#define MDR_ADCUI_FxMASK_WATTOVNM_Pos     (25UL)                    /*!< MDR_ADCUI F0MASK: WATTOVNM (Bit 25)                   */
#define MDR_ADCUI_FxMASK_WATTOVNM_Msk     (0x2000000UL)             /*!< MDR_ADCUI F0MASK: WATTOVNM (Bitfield-Mask: 0x01)      */
#define MDR_ADCUI_FxMASK_VAROVNM_Pos      (26UL)                    /*!< MDR_ADCUI F0MASK: VAROVNM (Bit 26)                    */
#define MDR_ADCUI_FxMASK_VAROVNM_Msk      (0x4000000UL)             /*!< MDR_ADCUI F0MASK: VAROVNM (Bitfield-Mask: 0x01)       */


/* ======================================================  CCALC1  ==================================================== */
typedef struct {
  __IOM uint32_t V0BGAIN    : 12;           /*!< [11..0] V0 calibration gain                                               */
  __IOM uint32_t I0BGAIN    : 12;           /*!< [23..12] I0 calibration gain                                              */
  __IM  uint32_t            : 8;
} MDR_ADCUI_CCAL1_Bits;

#define MDR_ADCUI_CCAL1_V0BGAIN_Pos       (0UL)                     /*!< MDR_ADCUI CCAL1: V0BGAIN (Bit 0)                      */
#define MDR_ADCUI_CCAL1_V0BGAIN_Msk       (0xfffUL)                 /*!< MDR_ADCUI CCAL1: V0BGAIN (Bitfield-Mask: 0xfff)       */
#define MDR_ADCUI_CCAL1_I0BGAIN_Pos       (12UL)                    /*!< MDR_ADCUI CCAL1: I0BGAIN (Bit 12)                     */
#define MDR_ADCUI_CCAL1_I0BGAIN_Msk       (0xfff000UL)              /*!< MDR_ADCUI CCAL1: I0BGAIN (Bitfield-Mask: 0xfff)       */

/* ======================================================  CCALC2  ==================================================== */
typedef struct {
  __IOM uint32_t I3BGAIN    : 12;           /*!< [11..0] I3 calibration gain                                               */
  __IM  uint32_t            : 20;
} MDR_ADCUI_CCAL4_Bits;

#define MDR_ADCUI_CCAL4_I3BGAIN_Pos       (0UL)                     /*!< MDR_ADCUI CCAL4: I3BGAIN (Bit 0)                      */
#define MDR_ADCUI_CCAL4_I3BGAIN_Msk       (0xfffUL)                 /*!< MDR_ADCUI CCAL4: I3BGAIN (Bitfield-Mask: 0xfff)       */

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

#endif  //  _MDR_ADCIU_VK2X4_DEFS_H

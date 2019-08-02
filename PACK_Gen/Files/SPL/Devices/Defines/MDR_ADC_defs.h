#ifndef _MDR_ADC_DEF_H
#define _MDR_ADC_DEF_H

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

#define ADC_MIN_VALUE   0x0000UL
#define ADC_MAX_VALUE   0x0FFFUL

/* =========================================================  ADC1_Cfg  ====================================================== */
typedef enum {
  MDR_ADC_CLK_CPU = 0,                         /*!< CPU_Clock : CLK = CPU_Clock / MDR_ADC_CPU_DIV                             */
  MDR_ADC_CLK_ADC = 1                          /*!< ADC_Clock : CLK = ADC_Clock used                                          */
} MDR_ADC_CLK_SEL;

typedef enum {                                 /*!< div_1    : CLK = CPU_CLK                                                  */
  MDR_ADC_CPU_div1    = 0,                     /*!< div_2    : CLK = CPU_CLK/2                                                */
  MDR_ADC_CPU_div2    = 1,                     /*!< div_4    : CLK = CPU_CLK/4                                                */
  MDR_ADC_CPU_div4    = 2,                     /*!< div_8    : CLK = CPU_CLK/8                                                */
  MDR_ADC_CPU_div8    = 3,                     /*!< div_16   : CLK = CPU_CLK/16                                               */
  MDR_ADC_CPU_div16   = 4,                     /*!< div_32   : CLK = CPU_CLK/32                                               */
  MDR_ADC_CPU_div32   = 5,                     /*!< div_64   : CLK = CPU_CLK/64                                               */
  MDR_ADC_CPU_div64   = 6,                     /*!< div_128  : CLK = CPU_CLK/128                                              */
  MDR_ADC_CPU_div128  = 7,                     /*!< div_256  : CLK = CPU_CLK/256                                              */
  MDR_ADC_CPU_div256  = 8,                     /*!< div_512  : CLK = CPU_CLK/512                                              */
  MDR_ADC_CPU_div512  = 9,                     /*!< div_1024 : CLK = CPU_CLK/1024                                             */
  MDR_ADC_CPU_div1024 = 10,                    /*!< div_2048 : CLK = CPU_CLK/2048                                             */
  MDR_ADC_CPU_div2048 = 11
} MDR_ADC_CPU_DIV;

typedef enum {
  MDR_ADC_SAMPLE_SINGLE     = 0,               /*!< Single : Single measurement by GO                                         */
  MDR_ADC_SAMPLE_CONTINUOUS = 1                /*!< Continuouse : Continuous measurement, until stop by ADON                  */
} MDR_ADC_SAMPLE;

typedef enum {
  MDR_ADC_MAGREF_Internal = 0,                     /*!< Internal : Signal in [GND..AUcc]                                         */
  MDR_ADC_MAGREF_External = 1                      /*!< External : Signal in [ADC_Ref-..ADC_Ref+]                                */
} MDR_ADC_MAGREF_SRC;

typedef enum {                           /*!< MDR_ADC_ADC1_TRIM_TS_Trim                                              */
  MDR_ADC_TRIM_TS_Vref_1v23  = 0,     /*!< Vref_1v23 : 1.23V typically                                               */
  MDR_ADC_TRIM_TS_Vref_1v213 = 1,     /*!< Vref_1v213 : 1.213V typically                                             */
  MDR_ADC_TRIM_TS_Vref_1v211 = 2,     /*!< Vref_1v211 : 1.211V typically                                             */
  MDR_ADC_TRIM_TS_Vref_1v208 = 3,     /*!< Vref_1v208 : 1.208V typically                                             */
  MDR_ADC_TRIM_TS_Vref_1v206 = 4,     /*!< Vref_1v206 : 1.206V typically                                             */
  MDR_ADC_TRIM_TS_Vref_1v203 = 5,     /*!< Vref_1v203 : 1.203V typically                                             */
  MDR_ADC_TRIM_TS_Vref_1v200 = 6,     /*!< Vref_1v200 : 1.200V typically                                             */
  MDR_ADC_TRIM_TS_Vref_1v197 = 7,     /*!< Vref_1v197 : 1.197V typically                                             */
  MDR_ADC_TRIM_TS_Vref_1v193 = 8,     /*!< Vref_1v193 : 1.193V typically                                             */
} MDR_ADC_TRIM_TS_Vref;

#define MDR_ADC_TRIM_def   MDR_ADC_TRIM_TS_Vref_1v23

typedef enum {                                  /*!< MDR_ADC_ADC1_Cfg_Delay_GO                                           */
  MDR_ADC_DelayGO_0          = 0,               /*!< 1 : 1 period of CPU_CLK                                             */
  MDR_ADC_DelayGO_1          = 1,               /*!< 2 : 2 periods of CPU_CLK                                            */
  MDR_ADC_DelayGO_2          = 2,               /*!< 3 : 3 periods of CPU_CLK                                            */
  MDR_ADC_DelayGO_3          = 3,               /*!< 4 : 4 periods of CPU_CLK                                            */
  MDR_ADC_DelayGO_4          = 4,               /*!< 5 : 5 periods of CPU_CLK                                            */
  MDR_ADC_DelayGO_5          = 5,               /*!< 6 : 6 periods of CPU_CLK                                            */
  MDR_ADC_DelayGO_6          = 6,               /*!< 7 : 7 periods of CPU_CLK                                            */
  MDR_ADC_DelayGO_7          = 7,               /*!< 8 : 8 periods of CPU_CLK                                            */
} MDR_ADC_DelayGO;


/* ====================================================  ADC2_Cfg  ======================================================= */
typedef enum {
  MDR_ADC_OP_Own = 0,                              /*!< Own : Own setpoint Vref                                            */
  MDR_ADC_OP_TS = 1,                               /*!< Thermosensor : Setpoint Vref from Thermosensor                     */
} MDR_ADC_OP;

/* ========================================  ADCx_H_Level, ADCx_L_Level  ================================================= */
typedef struct {
  __IOM uint32_t Level      : 12;           /*!< [11..0] Signal limit level                                                */
  __IM  uint32_t            : 20;
} MDR_ADC_Level_Bits;

#define MDR_ADC_Level_Pos    (0UL)                     /*!< ADC_Level: Level (Bit 0)                   */
#define MDR_ADC_Level_Msk    (0xfffUL)                 /*!< ADC_Level: Level (Bitfield-Mask: 0xfff)    */

/* =========================================================  ADC_Result  ================================================ */
typedef struct {
  __IM  uint32_t Value      : 12;           /*!< [11..0] Channel signal value                                              */
  __IM  uint32_t            : 4;
  __IM  uint32_t Channel    : 5;            /*!< [20..16] Channel index                                                    */
  __IM  uint32_t            : 11;
} MDR_ADC_Result_Bits;

#define MDR_ADC_RESULT_Value_Pos     (0UL)                     /*!< MDR_ADC ADC1_RESULT: Value (Bit 0)                    */
#define MDR_ADC_RESULT_Value_Msk     (0xfffUL)                 /*!< MDR_ADC ADC1_RESULT: Value (Bitfield-Mask: 0xfff)     */
#define MDR_ADC_RESULT_Channel_Pos   (16UL)                    /*!< MDR_ADC ADC1_RESULT: Channel (Bit 16)                 */
#define MDR_ADC_RESULT_Channel_Msk   (0x1f0000UL)              /*!< MDR_ADC ADC1_RESULT: Channel (Bitfield-Mask: 0x1f)    */

/* =========================================================  ADC_Status  ================================================= */
typedef struct {
  __IOM MDR_OnOff Overwrite  : 1;            /*!< [0..0] Result overwritten flag                                            */
  __IOM MDR_OnOff AWOIFEN    : 1;            /*!< [1..1] Signal is out of limiters range                                    */
  __IOM MDR_OnOff EOCIF      : 1;            /*!< [2..2] Result ready to read                                               */
  __IOM MDR_OnOff AWOIF_IE   : 1;            /*!< [3..3] Enable IRQ by AWOIFEN flag                                         */
  __IOM MDR_OnOff EOCIF_IE   : 1;            /*!< [4..4] Enable IRQ by EOCIF flag                                           */
  __IM  uint32_t             : 27;
} MDR_ADC_STATUS_Bits;

#define MDR_ADC_STATUS_Overwrite_Pos (0UL)                     /*!< MDR_ADC ADC1_STATUS: Overwrite (Bit 0)                */
#define MDR_ADC_STATUS_Overwrite_Msk (0x1UL)                   /*!< MDR_ADC ADC1_STATUS: Overwrite (Bitfield-Mask: 0x01)  */
#define MDR_ADC_STATUS_AWOIFEN_Pos   (1UL)                     /*!< MDR_ADC ADC1_STATUS: AWOIFEN (Bit 1)                  */
#define MDR_ADC_STATUS_AWOIFEN_Msk   (0x2UL)                   /*!< MDR_ADC ADC1_STATUS: AWOIFEN (Bitfield-Mask: 0x01)    */
#define MDR_ADC_STATUS_EOCIF_Pos     (2UL)                     /*!< MDR_ADC ADC1_STATUS: EOCIF (Bit 2)                    */
#define MDR_ADC_STATUS_EOCIF_Msk     (0x4UL)                   /*!< MDR_ADC ADC1_STATUS: EOCIF (Bitfield-Mask: 0x01)      */
#define MDR_ADC_STATUS_AWOIF_IE_Pos  (3UL)                     /*!< MDR_ADC ADC1_STATUS: AWOIF_IE (Bit 3)                 */
#define MDR_ADC_STATUS_AWOIF_IE_Msk  (0x8UL)                   /*!< MDR_ADC ADC1_STATUS: AWOIF_IE (Bitfield-Mask: 0x01)   */
#define MDR_ADC_STATUS_EOCIF_EN_Pos  (4UL)                     /*!< MDR_ADC ADC1_STATUS: EOCIF_EN (Bit 4)                 */
#define MDR_ADC_STATUS_EOCIF_EN_Msk  (0x10UL)                  /*!< MDR_ADC ADC1_STATUS: EOCIF_EN (Bitfield-Mask: 0x01)   */

//  Rename Bits
typedef struct {
  MDR_OnOff Overwrite   : 1;
  MDR_OnOff Limit       : 1;
  MDR_OnOff Ready       : 1;
  MDR_OnOff LimitIRQ_EN : 1;
  MDR_OnOff ReadyIRQ_EN : 1;
  uint32_t              : 27;
} MDR_ADC_Status_Flags;

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

#endif  //  _MDR_ADC_DEF_H

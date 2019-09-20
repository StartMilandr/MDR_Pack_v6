#ifndef MDR_ADCUI_VE4_CFG_REGS_H
#define MDR_ADCUI_VE4_CFG_REGS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <MDR_Types.h>
#include <MDR_ADCUI_VE4_defs.h>

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
  //  Запуск канала на измерение
  MDR_OnOff CH1_Run    : 1;
  MDR_OnOff CH2_Run    : 1;
  MDR_OnOff CH3_Run    : 1;
  MDR_OnOff CH4_Run    : 1;
  MDR_OnOff CH5_Run    : 1;
  MDR_OnOff CH6_Run    : 1;
  MDR_OnOff CH7_Run    : 1;
  MDR_OnOff CH8_Run    : 1;
  //  Использование внешней опоры
  MDR_OnOff UseExtRef  : 1;
  //  Удаление постоянной составляющей сигнала
  MDR_OnOff CH1_DelDC  : 1;
  MDR_OnOff CH2_DelDC  : 1;
  MDR_OnOff CH3_DelDC  : 1;
  MDR_OnOff CH4_DelDC  : 1;
  MDR_OnOff CH5_DelDC  : 1;
  MDR_OnOff CH6_DelDC  : 1;
  MDR_OnOff CH7_DelDC  : 1;
  MDR_OnOff CH8_DelDC  : 1;
  uint32_t             : 15;
} MDR_ADCUI_regCTRL1_Flags;

typedef struct {
  MDR_ADCUI_PGA   CH1_GAIN   : 2;            /*!< [1..0] Gain Select                                                        */
  MDR_ADCUI_PGA   CH2_GAIN   : 2;            /*!< [3..2] Gain Select                                                        */
  MDR_ADCUI_PGA   CH3_GAIN   : 2;            /*!< [5..4] Gain Select                                                        */
  MDR_ADCUI_PGA   CH4_GAIN   : 2;            /*!< [7..6] Gain Select                                                        */
  MDR_ADCUI_PGA   CH5_GAIN   : 2;            /*!< [9..8] Gain Select                                                        */
  MDR_ADCUI_PGA   CH6_GAIN   : 2;            /*!< [11..10] Gain Select                                                      */
  MDR_ADCUI_PGA   CH7_GAIN   : 2;            /*!< [13..12] Gain Select                                                      */
  MDR_ADCUI_PGA   CH8_GAIN   : 2;            /*!< [16..14] Gain Select                                                      */
  uint32_t                   : 16;
} MDR_ADCUI_regGAIN_Flags;

typedef struct {
  MDR_OnOff DMA1_EN    : 1;            /*!< [0..0] DMA Request Enable                                                 */
  MDR_OnOff DMA2_EN    : 1;            /*!< [1..1] DMA Request Enable                                                 */
  MDR_OnOff DMA3_EN    : 1;            /*!< [2..2] DMA Request Enable                                                 */
  MDR_OnOff DMA4_EN    : 1;            /*!< [3..3] DMA Request Enable                                                 */
  MDR_OnOff DMA5_EN    : 1;            /*!< [4..4] DMA Request Enable                                                 */
  MDR_OnOff DMA6_EN    : 1;            /*!< [5..5] DMA Request Enable                                                 */
  MDR_OnOff DMA7_EN    : 1;            /*!< [6..6] DMA Request Enable                                                 */
  MDR_OnOff DMA8_EN    : 1;            /*!< [7..7] DMA Request Enable                                                 */
  uint32_t             : 24;
} MDR_ADCUI_regDMA_Flags;

typedef struct {
  MDR_OnOff   CH1_OnReady : 1;            /*!< [0..0] IRQ by ADC ready                                                   */
  MDR_OnOff   CH2_OnReady : 1;            /*!< [1..1] IRQ by ADC ready                                                   */
  MDR_OnOff   CH3_OnReady : 1;            /*!< [2..2] IRQ by ADC ready                                                   */
  MDR_OnOff   CH4_OnReady : 1;            /*!< [3..3] IRQ by ADC ready                                                   */
  MDR_OnOff   CH5_OnReady : 1;            /*!< [4..4] IRQ by ADC ready                                                   */
  MDR_OnOff   CH6_OnReady : 1;            /*!< [5..5] IRQ by ADC ready                                                   */
  MDR_OnOff   CH7_OnReady : 1;            /*!< [6..6] IRQ by ADC ready                                                   */
  MDR_OnOff   CH8_OnReady : 1;            /*!< [7..7] IRQ by ADC ready                                                   */
  MDR_OnOff   CH1_OnOver  : 1;            /*!< [8..8] IRQ by Override ready                                              */
  MDR_OnOff   CH2_OnOver  : 1;            /*!< [9..9] IRQ by Override ready                                              */
  MDR_OnOff   CH3_OnOver  : 1;            /*!< [10..10] IRQ by Override ready                                            */
  MDR_OnOff   CH4_OnOver  : 1;            /*!< [11..11] IRQ by Override ready                                            */
  MDR_OnOff   CH5_OnOver  : 1;            /*!< [12..12] IRQ by Override ready                                            */
  MDR_OnOff   CH6_OnOver  : 1;            /*!< [13..13] IRQ by Override ready                                            */
  MDR_OnOff   CH7_OnOver  : 1;            /*!< [14..14] IRQ by Override ready                                            */
  MDR_OnOff   CH8_OnOver  : 1;            /*!< [15..15] IRQ by Override ready                                            */
  uint32_t            : 16;
} MDR_ADCUI_RegIRQ_Flags;


typedef struct {
  uint32_t   SFF        : 7;            /*!< [6..0] Sinc Filter Fine correction                                        */
  uint32_t   SFC        : 3;            /*!< [9..7] Sinc Filter Rough correction                                       */
//  MDR_OnOff  Reset      : 1;            /*!< [10..10] Digital part reset                                               */
  uint32_t              : 1;
  MDR_OnOff  ByPassBuff : 1;            /*!< [11..11] Avoid Vref buffer                                                */
//  uint32_t   CHOP_Freq  : 2;            /*!< [13..12] Chopper frequency                                                */
  uint32_t              : 2;
  uint32_t              : 18;
} MDR_ADCUI_refCTRL2_Flags;

typedef struct {
  union {
    uint32_t                  regCTRL1;
    MDR_ADCUI_regCTRL1_Flags  regCTRL1_f;
  } ;
  union {
    uint32_t                  regGAIN;
    MDR_ADCUI_regGAIN_Flags   regGAIN_f;
  } ;
  union {
    uint32_t                  regDMA;
    MDR_ADCUI_regDMA_Flags    regDMA_f;
  } ; 
  union {
    uint32_t                  regCTRL2;
    MDR_ADCUI_refCTRL2_Flags  regCTRL2_f;
  } ;
  union {
    uint32_t                  regIRQ;
    MDR_ADCUI_RegIRQ_Flags    regIRQ_f;
  } ;
} MDR_ADCUI_CfgRegs;                               /*!< Size = 64 (0x40)                                                          */

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


#endif // MDR_ADCUI_VE4_CFG_REGS_H


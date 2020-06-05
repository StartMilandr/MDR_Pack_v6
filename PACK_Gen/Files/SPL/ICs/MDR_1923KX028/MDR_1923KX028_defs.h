#ifndef MDR_1923KX028_DEFS_H
#define MDR_1923KX028_DEFS_H

#include <stdint.h>
//#include <MDR_Types.h>

typedef enum {
  MDR_1923KX028_Mode0_PCIe,
  MDR_1923KX028_Mode1_ExtFlash,
  MDR_1923KX028_Mode2_SlaveSPI,
  MDR_1923KX028_Mode3_Uncontrolled,
} MDR_1923KX028_Mode;


// Адреса регистров
typedef enum {
  MDR_1923KX028_Control_1 = 0,
  MDR_1923KX028_Control_2,
  MDR_1923KX028_Control_3,
  MDR_1923KX028_Control_4,
  MDR_1923KX028_Control_5,
  MDR_1923KX028_Control_6,
  MDR_1923KX028_Control_7,
  MDR_1923KX028_Control_8,
  MDR_1923KX028_Control_9,
  MDR_1923KX028_Control_10,
  MDR_1923KX028_Control_11,
  MDR_1923KX028_Control_12,
  MDR_1923KX028_Control_13,
  MDR_1923KX028_Control_14,
  MDR_1923KX028_Control_15,
  MDR_1923KX028_Control_16,
  MDR_1923KX028_Control_17,
  MDR_1923KX028_Control_18,
  MDR_1923KX028_Control_19,
  MDR_1923KX028_Control_20,
  MDR_1923KX028_Control_21,
  MDR_1923KX028_Control_22,
  MDR_1923KX028_Control_23 = 0x16,
  //  Status
  MDR_1923KX028_Status_1 = 0x40,
  MDR_1923KX028_Status_2,
  MDR_1923KX028_Status_3,
  MDR_1923KX028_Status_4,
  MDR_1923KX028_Status_5,
  MDR_1923KX028_Status_6,
  MDR_1923KX028_Status_7,
  MDR_1923KX028_Status_8,
  MDR_1923KX028_Status_9,
  MDR_1923KX028_Status_10,
  MDR_1923KX028_Status_11,
  MDR_1923KX028_Status_12,
  MDR_1923KX028_Status_13,
  MDR_1923KX028_Status_14,
  MDR_1923KX028_Status_15,
  MDR_1923KX028_Status_16,
  MDR_1923KX028_Status_17,
  MDR_1923KX028_Status_18,
  MDR_1923KX028_Status_19,
  MDR_1923KX028_Status_20,
  MDR_1923KX028_Status_21,
  MDR_1923KX028_Status_22,
  MDR_1923KX028_Status_23,
  MDR_1923KX028_Status_24,
  MDR_1923KX028_Status_25,
  MDR_1923KX028_Status_26,
  MDR_1923KX028_Status_27,
  MDR_1923KX028_Status_28,
  MDR_1923KX028_Status_29,
  MDR_1923KX028_Status_30,
  MDR_1923KX028_Status_31,
  MDR_1923KX028_Status_32,
  MDR_1923KX028_Status_33 = 0x60,  
} MDR_1923KX028_Reg;


/*  Основные параметры настройки блоков PHY:

__кол.бит:_____ влияет на:___________Регистры:_______Описание: 
AcjtLvl[5]     - Value per PHY[4]   - Control 6      - Выбирает уровень чувствительности 1149.6 приемника для AC JTAG.
LosBias[3]     - Value per PHY[4]   - Control 6      - Управление уровнем порога детекции потери сигнала.
LosLvl[5]      - Value per PHY[4]   - Control 7      - Управление уровнем чувствительности детекции потери сигнала Ethernet PHY
RxEq[3]        - Value for each PHY - Control 8..9   - Выбиратеся величина коррекции в приемнике
RxTermEn[1]    - Value for each PHY - Control 9      - Наличие терминирования в приемнике
TxAmp[7]       - Value for each PHY - Control 10..13 - Амплитуда Tx (Режим полного размаха).
UseRefPad[1]   - Value per PHY[4]   - Control 11     - Разрешение источника опорной частоты на внешних выводах.
SoftRstXaui[1] - Value per PHY[4]   - Control 12     - Программный сброс
TxCommEn[1]    - Value for each PHY - Control 13..14 - Разрешение схемы фиксации common mode передатчика
TxDetectReq[1] - Value for each PHY - Control 14     - Разрешается запрос на детектирование нового соединения с приемником.
TxPreEmph[7]   - Value for each PHY - Control 15..18 - Устанавливается для компенсации значения предискажений Tx драйвера
TxTermOffs[5]  - Value for each PHY - Control 19..21 - Смещение терминирования передатчика.

Аналогичные параметры для PCEe PHY находятся в регистрах Control 22..23.
*/

// Значения AcjtLvl[5]
typedef enum {
  MDR_1923KX028_Lvl_mV_235_375 = 1,
  MDR_1923KX028_Lvl_mV_288_463 = 2,
  MDR_1923KX028_Lvl_mV_344_554 = 3,
  MDR_1923KX028_Lvl_mV_401_649 = 4,
  MDR_1923KX028_Lvl_mV_460_747 = 5,
  MDR_1923KX028_Lvl_mV_521_849 = 6,
  MDR_1923KX028_Lvl_mV_432_740 = 0x11,
  MDR_1923KX028_Lvl_mV_525_967 = 0x12,
} MDR_1923KX028_AcjtLvl;


// Значения LosBias[3]
typedef enum {
  MDR_1923KX028_Bias_mV_Reserved = 0,
  MDR_1923KX028_Bias_mV_120,
  MDR_1923KX028_Bias_mV_135,
  MDR_1923KX028_Bias_mV_150,
  MDR_1923KX028_Bias_mV_45,
  MDR_1923KX028_Bias_mV_60,
  MDR_1923KX028_Bias_mV_75,
  MDR_1923KX028_Bias_mV_90,
} MDR_1923KX028_LosBias;



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


/* ============================================================================================================================= */
/* ====================================================  CONTROL registers ===================================================== */
/* ============================================================================================================================= */


/* =========================================================  Control 1  ====================================================== */
typedef struct {
  __IOM uint32_t  VenMsiReq    : 1;
  __IOM uint32_t  VenMsiFunc   : 3;
  __IOM uint32_t  VenMsiTc     : 3;
  __IOM uint32_t  VenMsiVector : 5;
  __IOM uint32_t  VenMsgFmt    : 2;
  __IOM uint32_t  VenMsgType   : 5;
  __IOM uint32_t  VenMsgTc     : 4;
  __IOM uint32_t  VenMsgTd     : 1;
  __IOM uint32_t  VenMsgEp     : 1;
  __IOM uint32_t  VenMsgAttr   : 2;
  __IOM uint32_t  VenMsgFunc   : 3;
  __IOM uint32_t  VenMsgReq    : 1;
  __IOM uint32_t  AppLtssmEn   : 1;
  __IOM uint32_t  AppReqRetryEn: 1;
} MDR_1923KX028_Ctrl1_Bits;

#define MDR_1923KX028_Ctrl1_MsiReq_Pos      0
#define MDR_1923KX028_Ctrl1_MsiReq_Msk      1
#define MDR_1923KX028_Ctrl1_MsiFunc_Pos     1
#define MDR_1923KX028_Ctrl1_MsiFunc_Msk     0x000FUL
#define MDR_1923KX028_Ctrl1_MsiTc_Pos       4
#define MDR_1923KX028_Ctrl1_MsiTc_Msk       0x0070UL
#define MDR_1923KX028_Ctrl1_MsiVect_Pos     7
#define MDR_1923KX028_Ctrl1_MsiVect_Msk     0x0F80UL
#define MDR_1923KX028_Ctrl1_MsgFmt_Pos      12
#define MDR_1923KX028_Ctrl1_MsgFmt_Msk      0x3000UL
#define MDR_1923KX028_Ctrl1_MsgType_Pos     14
#define MDR_1923KX028_Ctrl1_MsgType_Msk     0x0007C000UL
#define MDR_1923KX028_Ctrl1_MsgTc_Pos       19
#define MDR_1923KX028_Ctrl1_MsgTc_Msk       0x00300000UL
#define MDR_1923KX028_Ctrl1_MsgTd_Pos       22
#define MDR_1923KX028_Ctrl1_MsgTd_Msk       0x00400000UL
#define MDR_1923KX028_Ctrl1_MsgEp_Pos       23
#define MDR_1923KX028_Ctrl1_MsgEp_Msk       0x00800000UL
#define MDR_1923KX028_Ctrl1_MsgAttr_Pos     24
#define MDR_1923KX028_Ctrl1_MsgAttr_Msk     0x03000000UL
#define MDR_1923KX028_Ctrl1_MsgFunc_Pos     26
#define MDR_1923KX028_Ctrl1_MsgFunc_Msk     0x1C000000UL
#define MDR_1923KX028_Ctrl1_MsgReq_Pos      29
#define MDR_1923KX028_Ctrl1_MsgReq_Msk      0x20000000UL
#define MDR_1923KX028_Ctrl1_LtssmEn_Pos     30
#define MDR_1923KX028_Ctrl1_AppLtssmEn_Msk  0x40000000UL
#define MDR_1923KX028_Ctrl1_ReqRetryEn_Pos  31
#define MDR_1923KX028_Ctrl1_ReqRetryEn_Msk  0x80000000UL

typedef union {
  __IOM uint32_t             value;
  MDR_1923KX028_Ctrl1_Bits  bits;
} MDR_1923KX028_Ctrl1_t;


/* =========================================================  Control 2  ====================================================== */
typedef struct {
  __IOM uint32_t  VenMsgLen    : 10;
  __IOM uint32_t  VenMsgTag    : 8;
  __IOM uint32_t  VenMsiCode   : 8;
  __IM uint32_t                : 6;
} MDR_1923KX028_Ctrl2_Bits;

#define MDR_1923KX028_Ctrl2_MsiReq_Pos      0
#define MDR_1923KX028_Ctrl2_MsiReq_Msk      0x000003FFUL
#define MDR_1923KX028_Ctrl2_MsiFunc_Pos     10
#define MDR_1923KX028_Ctrl2_MsiFunc_Msk     0x0003FC00UL
#define MDR_1923KX028_Ctrl2_MsiTc_Pos       18
#define MDR_1923KX028_Ctrl2_MsiTc_Msk       0x03FC0000UL

typedef union {
  __IOM uint32_t            value;
  MDR_1923KX028_Ctrl2_Bits  bits;
} MDR_1923KX028_Ctrl2_t;


/* =========================================================  Control 3 / 4  ====================================================== */
//  ven_msg_data[31:0]
#define MDR_1923KX028_Ctrl3_t   uint32_t
//  ven_msg_data[63:32]
#define MDR_1923KX028_Ctrl4_t   uint32_t


/* =========================================================  Control 5  ====================================================== */
typedef struct {
  __IOM uint32_t  OutbandPwrupCmd : 1;
  __IOM uint32_t  AppsPmXmtPme    : 1;
  __IOM uint32_t  SysAuxPwrDet    : 1;
  __IOM uint32_t  AppReqEntrL1    : 1;
  __IOM uint32_t  AppRdyEntrL23   : 1;
  __IOM uint32_t  AppReqExitL1    : 1;
  __IOM uint32_t  AppXferPending  : 1;
  __IOM uint32_t  SlvAWInfoAtuByp : 1;
  __IOM uint32_t  SlvARInfoAtuByp : 1;
  __IOM uint32_t  SlvCSysReq      : 1;
  __IOM uint32_t  MstrCSysReq     : 1;
  __IM  uint32_t                  : 21;
} MDR_1923KX028_Ctrl5_Bits;

#define MDR_1923KX028_Ctrl5_OutbandPwrupCmd_Pos  0
#define MDR_1923KX028_Ctrl5_OutbandPwrupCmd_Msk  0x0001UL
#define MDR_1923KX028_Ctrl5_AppsPmXmtPme_Pos     1
#define MDR_1923KX028_Ctrl5_AppsPmXmtPme_Msk     0x0002UL
#define MDR_1923KX028_Ctrl5_SysAuxPwrDet_Pos     2
#define MDR_1923KX028_Ctrl5_SysAuxPwrDet_Msk     0x0004UL
#define MDR_1923KX028_Ctrl5_AppReqEntrL1_Pos     3
#define MDR_1923KX028_Ctrl5_AppReqEntrL1_Msk     0x0008UL
#define MDR_1923KX028_Ctrl5_AppRdyEntrL23_Pos    4
#define MDR_1923KX028_Ctrl5_AppRdyEntrL23_Msk    0x0010UL
#define MDR_1923KX028_Ctrl5_AppReqExitL1_Pos     5
#define MDR_1923KX028_Ctrl5_AppReqExitL1_Msk     0x0020UL
#define MDR_1923KX028_Ctrl5_AppXferPending_Pos   6
#define MDR_1923KX028_Ctrl5_AppXferPending_Msk   0x0040UL
#define MDR_1923KX028_Ctrl5_SlvAWInfoAtuByp_Pos  7
#define MDR_1923KX028_Ctrl5_SlvAWInfoAtuByp_Msk  0x0080UL
#define MDR_1923KX028_Ctrl5_SlvARInfoAtuByp_Pos  8
#define MDR_1923KX028_Ctrl5_SlvARInfoAtuByp_Msk  0x0100UL
#define MDR_1923KX028_Ctrl5_SlvCSysReq_Pos       9
#define MDR_1923KX028_Ctrl5_SlvCSysReq_Msk       0x0200UL
#define MDR_1923KX028_Ctrl5_MstrCSysReq_Pos      10
#define MDR_1923KX028_Ctrl5_MstrCSysReq_Msk      0x0400UL

typedef union {
  __IOM uint32_t            value;
  MDR_1923KX028_Ctrl5_Bits  bits;
} MDR_1923KX028_Ctrl5_t;


/* =========================================================  Control 6  ====================================================== */
#define MDR_1923KX028_Ctrl6_AcjtLvl   MDR_1923KX028_AcjtLvl
#define MDR_1923KX028_Ctrl6_LosBias   MDR_1923KX028_LosBias

typedef struct {
  __IOM uint32_t  AcjtLvlPhy1_4   : 5;
  __IOM uint32_t  AcjtLvlPhy5_8   : 5;
  __IOM uint32_t  AcjtLvlPhy9_12  : 5;
  __IOM uint32_t  AcjtLvlPhy13_16 : 5;
  __IOM uint32_t  LosBiasPhy1_4   : 3;
  __IOM uint32_t  LosBiasPhy5_8   : 3;
  __IOM uint32_t  LosBiasPhy9_12  : 3;
  __IOM uint32_t  LosBiasPhy13_16 : 3;
} MDR_1923KX028_Ctrl6_Bits;

#define MDR_1923KX028_Ctrl6_AcjtLvlPhy1_4_Pos    0
#define MDR_1923KX028_Ctrl6_AcjtLvlPhy1_4_Msk    0x0000001FUL
#define MDR_1923KX028_Ctrl6_AcjtLvlPhy5_8_Pos    5
#define MDR_1923KX028_Ctrl6_AcjtLvlPhy5_8_Msk    0x000003E0UL
#define MDR_1923KX028_Ctrl6_AcjtLvlPhy9_12_Pos   10
#define MDR_1923KX028_Ctrl6_AcjtLvlPhy9_12_Msk   0x00007C00UL
#define MDR_1923KX028_Ctrl6_AcjtLvlPhy13_16_Pos  15
#define MDR_1923KX028_Ctrl6_AcjtLvlPhy13_16_Msk  0x000F8000UL
#define MDR_1923KX028_Ctrl6_LosBiasPhy1_4_Pos    20
#define MDR_1923KX028_Ctrl6_LosBiasPhy1_4_Msk    0x00700000UL
#define MDR_1923KX028_Ctrl6_LosBiasPhy5_8_Pos    23
#define MDR_1923KX028_Ctrl6_LosBiasPhy5_8_Msk    0x03800000UL
#define MDR_1923KX028_Ctrl6_LosBiasPhy9_12_Pos   26
#define MDR_1923KX028_Ctrl6_LosBiasPhy9_12_Msk   0x1C000000UL
#define MDR_1923KX028_Ctrl6_LosBiasPhy13_16_Pos  29
#define MDR_1923KX028_Ctrl6_LosBiasPhy13_16_Msk  0xE0000000UL

typedef union {
  __IOM uint32_t            value;
  MDR_1923KX028_Ctrl6_Bits  bits;
} MDR_1923KX028_Ctrl6_t;


/* =========================================================  Control 7 ====================================================== */
typedef enum {
  MDR_1923KX028_RxTxRate_div1 = 0,
  MDR_1923KX028_RxTxRate_div2,
  MDR_1923KX028_RxTxRate_div4,
  MDR_1923KX028_RxTxRate_reserved,
} MDR_1923KX028_Ctrl7_RxTxRate;

typedef struct {
  __IOM uint32_t  LosLvlPhy1_4   : 5;
  __IOM uint32_t  LosLvlPhy5_8   : 5;
  __IOM uint32_t  LosLvlPhy9_12  : 5;
  __IOM uint32_t  LosLvlPhy13_16 : 5;
  __IOM uint32_t  PhyMPLL_Mul    : 7;
  __IOM uint32_t  PhyMPLL_En     : 1;
  __IOM uint32_t  SoftResetPhy   : 1;
  __IOM uint32_t  RefClkDiv2     : 1;
  __IOM uint32_t  RxTxRate       : 2;
} MDR_1923KX028_Ctrl7_Bits;

#define MDR_1923KX028_Ctrl7_LosLvlPhy1_4_Pos    0
#define MDR_1923KX028_Ctrl7_LosLvlPhy1_4_Msk    0x0000001FUL
#define MDR_1923KX028_Ctrl7_LosLvlPhy5_8_Pos    5
#define MDR_1923KX028_Ctrl7_LosLvlPhy5_8_Msk    0x000003E0UL
#define MDR_1923KX028_Ctrl7_LosLvlPhy9_12_Pos   10
#define MDR_1923KX028_Ctrl7_LosLvlPhy9_12_Msk   0x00007C00UL
#define MDR_1923KX028_Ctrl7_LosLvlPhy13_16_Pos  15
#define MDR_1923KX028_Ctrl7_LosLvlPhy13_16_Msk  0x000F8000UL
#define MDR_1923KX028_Ctrl7_PhyMPLL_Mul_Pos     20
#define MDR_1923KX028_Ctrl7_PhyMPLL_Mul_Msk     0x07F00000UL
#define MDR_1923KX028_Ctrl7_PhyMPLL_En_Pos          27
#define MDR_1923KX028_Ctrl7_PhyMPLL_En_Msk          0x08000000UL
#define MDR_1923KX028_Ctrl7_SoftResetPhy_Pos     28
#define MDR_1923KX028_Ctrl7_SoftResetPhy_Msk     0x10000000UL
#define MDR_1923KX028_Ctrl7_RefClkDiv2_Pos       29
#define MDR_1923KX028_Ctrl7_RefClkDiv2_Msk       0x40000000UL
#define MDR_1923KX028_Ctrl7_RxTxRate_Pos         30
#define MDR_1923KX028_Ctrl7_RxTxRate_Msk         0xC0000000UL

typedef union {
  __IOM uint32_t            value;
  MDR_1923KX028_Ctrl7_Bits  bits;
} MDR_1923KX028_Ctrl7_t;


/* =========================================================  Control 8 ====================================================== */
typedef struct {
  __IOM uint32_t  RxEqPhy1   : 3;
  __IOM uint32_t  RxEqPhy2   : 3;
  __IOM uint32_t  RxEqPhy3   : 3;
  __IOM uint32_t  RxEqPhy4   : 3;
  __IOM uint32_t  RxEqPhy5   : 3;
  __IOM uint32_t  RxEqPhy6   : 3;
  __IOM uint32_t  RxEqPhy7   : 3;
  __IOM uint32_t  RxEqPhy8   : 3;
  __IOM uint32_t  RxEqPhy9   : 3;
  __IOM uint32_t  RxEqPhy10  : 3;
  __IM uint32_t              : 2;
} MDR_1923KX028_Ctrl8_Bits;

#define MDR_1923KX028_Ctrl8_RxEqPhy1_Pos    0
#define MDR_1923KX028_Ctrl8_RxEqPhy1_Msk    0x00000007UL
#define MDR_1923KX028_Ctrl8_RxEqPhy2_Pos    3
#define MDR_1923KX028_Ctrl8_RxEqPhy2_Msk    0x00000038UL
#define MDR_1923KX028_Ctrl8_RxEqPhy3_Pos    6
#define MDR_1923KX028_Ctrl8_RxEqPhy3_Msk    0x000001C0UL
#define MDR_1923KX028_Ctrl8_RxEqPhy4_Pos    9
#define MDR_1923KX028_Ctrl8_RxEqPhy4_Msk    0x00000E00UL
#define MDR_1923KX028_Ctrl8_RxEqPhy5_Pos    12
#define MDR_1923KX028_Ctrl8_RxEqPhy5_Msk    0x00007000UL
#define MDR_1923KX028_Ctrl8_RxEqPhy6_Pos    15
#define MDR_1923KX028_Ctrl8_RxEqPhy6_Msk    0x00038000UL
#define MDR_1923KX028_Ctrl8_RxEqPhy7_Pos    18
#define MDR_1923KX028_Ctrl8_RxEqPhy7_Msk    0x001C0000UL
#define MDR_1923KX028_Ctrl8_RxEqPhy8_Pos    21
#define MDR_1923KX028_Ctrl8_RxEqPhy8_Msk    0x00E00000UL
#define MDR_1923KX028_Ctrl8_RxEqPhy9_Pos    24
#define MDR_1923KX028_Ctrl8_RxEqPhy9_Msk    0x07000000UL
#define MDR_1923KX028_Ctrl8_RxEqPhy10_Pos   27
#define MDR_1923KX028_Ctrl8_RxEqPhy10_Msk   0x38000000UL

typedef union {
  __IOM uint32_t            value;
  MDR_1923KX028_Ctrl8_Bits  bits;
} MDR_1923KX028_Ctrl8_t;


/* =========================================================  Control 9 ====================================================== */
typedef struct {
  __IOM uint32_t  RxEqPhy11     : 3;
  __IOM uint32_t  RxEqPhy12     : 3;
  __IOM uint32_t  RxEqPhy13     : 3;
  __IOM uint32_t  RxEqPhy14     : 3;
  __IOM uint32_t  RxEqPhy15     : 3;
  __IOM uint32_t  RxEqPhy16     : 3;
  __IOM uint32_t  RxTermEnPhy1  : 1;
  __IOM uint32_t  RxTermEnPhy2  : 1;
  __IOM uint32_t  RxTermEnPhy3  : 1;
  __IOM uint32_t  RxTermEnPhy4  : 1;
  __IOM uint32_t  RxTermEnPhy5  : 1;
  __IOM uint32_t  RxTermEnPhy6  : 1;
  __IOM uint32_t  RxTermEnPhy7  : 1;
  __IOM uint32_t  RxTermEnPhy8  : 1;
  __IOM uint32_t  RxTermEnPhy9  : 1;
  __IOM uint32_t  RxTermEnPhy10 : 1;
  __IOM uint32_t  RxTermEnPhy11 : 1;
  __IOM uint32_t  RxTermEnPhy12 : 1;
  __IM uint32_t                 : 2;
} MDR_1923KX028_Ctrl9_Bits;

#define MDR_1923KX028_Ctrl9_RxEqPhy11_Pos      0
#define MDR_1923KX028_Ctrl9_RxEqPhy11_Msk      0x00000007UL
#define MDR_1923KX028_Ctrl9_RxEqPhy12_Pos      3
#define MDR_1923KX028_Ctrl9_RxEqPhy12_Msk      0x00000038UL
#define MDR_1923KX028_Ctrl9_RxEqPhy13_Pos      6
#define MDR_1923KX028_Ctrl9_RxEqPhy13_Msk      0x000001C0UL
#define MDR_1923KX028_Ctrl9_RxEqPhy14_Pos      9
#define MDR_1923KX028_Ctrl9_RxEqPhy14_Msk      0x00000E00UL
#define MDR_1923KX028_Ctrl9_RxEqPhy15_Pos      12
#define MDR_1923KX028_Ctrl9_RxEqPhy15_Msk      0x00007000UL
#define MDR_1923KX028_Ctrl9_RxEqPhy16_Pos      15
#define MDR_1923KX028_Ctrl9_RxEqPhy16_Msk      0x00038000UL
#define MDR_1923KX028_Ctrl9_RxTermEnPhy1_Pos   18
#define MDR_1923KX028_Ctrl9_RxTermEnPhy1_Msk   0x00040000UL
#define MDR_1923KX028_Ctrl9_RxTermEnPhy2_Pos   19
#define MDR_1923KX028_Ctrl9_RxTermEnPhy2_Msk   0x00080000UL
#define MDR_1923KX028_Ctrl9_RxTermEnPhy3_Pos   20
#define MDR_1923KX028_Ctrl9_RxTermEnPhy3_Msk   0x00100000UL
#define MDR_1923KX028_Ctrl9_RxTermEnPhy4_Pos   21
#define MDR_1923KX028_Ctrl9_RxTermEnPhy4_Msk   0x00200000UL
#define MDR_1923KX028_Ctrl9_RxTermEnPhy5_Pos   22
#define MDR_1923KX028_Ctrl9_RxTermEnPhy5_Msk   0x00400000UL
#define MDR_1923KX028_Ctrl9_RxTermEnPhy6_Pos   23
#define MDR_1923KX028_Ctrl9_RxTermEnPhy6_Msk   0x00800000UL
#define MDR_1923KX028_Ctrl9_RxTermEnPhy7_Pos   24
#define MDR_1923KX028_Ctrl9_RxTermEnPhy7_Msk   0x01000000UL
#define MDR_1923KX028_Ctrl9_RxTermEnPhy8_Pos   25
#define MDR_1923KX028_Ctrl9_RxTermEnPhy8_Msk   0x02000000UL
#define MDR_1923KX028_Ctrl9_RxTermEnPhy9_Pos   26
#define MDR_1923KX028_Ctrl9_RxTermEnPhy9_Msk   0x04000000UL
#define MDR_1923KX028_Ctrl9_RxTermEnPhy10_Pos  27
#define MDR_1923KX028_Ctrl9_RxTermEnPhy10_Msk  0x08000000UL
#define MDR_1923KX028_Ctrl9_RxTermEnPhy11_Pos  28
#define MDR_1923KX028_Ctrl9_RxTermEnPhy11_Msk  0x10000000UL
#define MDR_1923KX028_Ctrl9_RxTermEnPhy12_Pos  29
#define MDR_1923KX028_Ctrl9_RxTermEnPhy12_Msk  0x20000000UL

typedef union {
  __IOM uint32_t            value;
  MDR_1923KX028_Ctrl9_Bits  bits;
} MDR_1923KX028_Ctrl9_t;


/* =========================================================  Control 10  ====================================================== */
typedef struct {
  __IOM uint32_t  RxTermEnPhy13   : 1;
  __IOM uint32_t  RxTermEnPhy14   : 1;
  __IOM uint32_t  RxTermEnPhy15   : 1;
  __IOM uint32_t  RxTermEnPhy16   : 1;
  __IOM uint32_t  TxAmpPhy1       : 7;
  __IOM uint32_t  TxAmpPhy2       : 7;
  __IOM uint32_t  TxAmpPhy3       : 7;
  __IOM uint32_t  TxAmpPhy4       : 7;
} MDR_1923KX028_Ctrl10_Bits;

#define MDR_1923KX028_Ctrl10_RxTermEnPhy13_Pos    0
#define MDR_1923KX028_Ctrl10_RxTermEnPhy13_Msk    0x00000001UL
#define MDR_1923KX028_Ctrl10_RxTermEnPhy14_Pos    1
#define MDR_1923KX028_Ctrl10_RxTermEnPhy14_Msk    0x00000002UL
#define MDR_1923KX028_Ctrl10_RxTermEnPhy15_Pos    2
#define MDR_1923KX028_Ctrl10_RxTermEnPhy15_Msk    0x00000004UL
#define MDR_1923KX028_Ctrl10_RxTermEnPhy16_Pos    3
#define MDR_1923KX028_Ctrl10_RxTermEnPhy16_Msk    0x00000008UL
#define MDR_1923KX028_Ctrl10_TxAmpPhy1_Pos        4
#define MDR_1923KX028_Ctrl10_TxAmpPhy1_Msk        0x000007F0UL
#define MDR_1923KX028_Ctrl10_TxAmpPhy2_Pos        11
#define MDR_1923KX028_Ctrl10_TxAmpPhy2_Msk        0x0003F800UL
#define MDR_1923KX028_Ctrl10_TxAmpPhy3_Pos        18
#define MDR_1923KX028_Ctrl10_TxAmpPhy3_Msk        0x01FC0000UL
#define MDR_1923KX028_Ctrl10_TxAmpPhy4_Pos        25
#define MDR_1923KX028_Ctrl10_TxAmpPhy4_Msk        0xFE000000UL

typedef union {
  __IOM uint32_t             value;
  MDR_1923KX028_Ctrl10_Bits  bits;
} MDR_1923KX028_Ctrl10_t;


/* =========================================================  Control 11  ====================================================== */
typedef struct {
  __IOM uint32_t  TxAmpPhy5         : 7;
  __IOM uint32_t  TxAmpPhy6         : 7;
  __IOM uint32_t  TxAmpPhy7         : 7;
  __IOM uint32_t  TxAmpPhy8         : 7;
  __IOM uint32_t  UseRefPadPhy1_4   : 1;
  __IOM uint32_t  UseRefPadPhy5_8   : 1;
  __IOM uint32_t  UseRefPadPhy8_12  : 1;
  __IOM uint32_t  UseRefPadPhy13_16 : 1;  
} MDR_1923KX028_Ctrl11_Bits;

#define MDR_1923KX028_Ctrl11_TxAmpPhy5_Pos          0
#define MDR_1923KX028_Ctrl11_TxAmpPhy5_Msk          0x0000007FUL
#define MDR_1923KX028_Ctrl11_TxAmpPhy6_Pos          7
#define MDR_1923KX028_Ctrl11_TxAmpPhy6_Msk          0x00003F80UL
#define MDR_1923KX028_Ctrl11_TxAmpPhy7_Pos          14
#define MDR_1923KX028_Ctrl11_TxAmpPhy7_Msk          0x001FC000UL
#define MDR_1923KX028_Ctrl11_TxAmpPhy8_Pos          21
#define MDR_1923KX028_Ctrl11_TxAmpPhy8_Msk          0x0FE00000UL
#define MDR_1923KX028_Ctrl11_UseRefPadPhy1_4_Pos    28
#define MDR_1923KX028_Ctrl11_UseRefPadPhy1_4_Msk    0x10000000UL
#define MDR_1923KX028_Ctrl11_UseRefPadPhy5_8_Pos    29
#define MDR_1923KX028_Ctrl11_UseRefPadPhy5_8_Msk    0x20000000UL
#define MDR_1923KX028_Ctrl11_UseRefPadPhy8_12_Pos   30
#define MDR_1923KX028_Ctrl11_UseRefPadPhy8_12_Msk   0x40000000UL
#define MDR_1923KX028_Ctrl11_UseRefPadPhy13_16_Pos  31
#define MDR_1923KX028_Ctrl11_UseRefPadPhy13_16_Msk  0x80000000UL

typedef union {
  __IOM uint32_t             value;
  MDR_1923KX028_Ctrl11_Bits  bits;
} MDR_1923KX028_Ctrl11_t;


/* =========================================================  Control 12  ====================================================== */
typedef struct {
  __IOM uint32_t  TxAmpPhy9           : 7;
  __IOM uint32_t  TxAmpPhy10          : 7;
  __IOM uint32_t  TxAmpPhy11          : 7;
  __IOM uint32_t  TxAmpPhy12          : 7;
  __IOM uint32_t  SoftRstXauiPhy1_4   : 1;
  __IOM uint32_t  SoftRstXauiPhy5_8   : 1;
  __IOM uint32_t  SoftRstXauiPhy8_12  : 1;
  __IOM uint32_t  SoftRstXauiPhy13_16 : 1;  
} MDR_1923KX028_Ctrl12_Bits;

#define MDR_1923KX028_Ctrl12_TxAmpPhy9_Pos            0
#define MDR_1923KX028_Ctrl12_TxAmpPhy9_Msk            0x0000007FUL
#define MDR_1923KX028_Ctrl12_TxAmpPhy10_Pos           7
#define MDR_1923KX028_Ctrl12_TxAmpPhy10_Msk           0x00003F80UL
#define MDR_1923KX028_Ctrl12_TxAmpPhy11_Pos           14
#define MDR_1923KX028_Ctrl12_TxAmpPhy11_Msk           0x001FC000UL
#define MDR_1923KX028_Ctrl12_TxAmpPhy12_Pos           21
#define MDR_1923KX028_Ctrl12_TxAmpPhy12_Msk           0x0FE00000UL
#define MDR_1923KX028_Ctrl12_SoftRstXauiPhy1_4_Pos    28
#define MDR_1923KX028_Ctrl12_SoftRstXauiPhy1_4_Msk    0x10000000UL
#define MDR_1923KX028_Ctrl12_SoftRstXauiPhy5_8_Pos    29
#define MDR_1923KX028_Ctrl12_SoftRstXauiPhy5_8_Msk    0x20000000UL
#define MDR_1923KX028_Ctrl12_SoftRstXauiPhy8_12_Pos   30
#define MDR_1923KX028_Ctrl12_SoftRstXauiPhy8_12_Msk   0x40000000UL
#define MDR_1923KX028_Ctrl12_SoftRstXauiPhy13_16_Pos  31
#define MDR_1923KX028_Ctrl12_SoftRstXauiPhy13_16_Msk  0x80000000UL

typedef union {
  __IOM uint32_t             value;
  MDR_1923KX028_Ctrl12_Bits  bits;
} MDR_1923KX028_Ctrl12_t;


/* =========================================================  Control 13  ====================================================== */
typedef struct {
  __IOM uint32_t  TxAmpPhy13     : 7;
  __IOM uint32_t  TxAmpPhy14     : 7;
  __IOM uint32_t  TxAmpPhy15     : 7;
  __IOM uint32_t  TxAmpPhy16     : 7;
  __IOM uint32_t  TxCommEnPhy1   : 1;
  __IOM uint32_t  TxCommEnPhy2   : 1;
  __IOM uint32_t  TxCommEnPhy3   : 1;
  __IOM uint32_t  TxCommEnPhy4   : 1;  
} MDR_1923KX028_Ctrl13_Bits;

#define MDR_1923KX028_Ctrl13_TxAmpPhy13_Pos     0
#define MDR_1923KX028_Ctrl13_TxAmpPhy13_Msk     0x0000007FUL
#define MDR_1923KX028_Ctrl13_TxAmpPhy14_Pos     7
#define MDR_1923KX028_Ctrl13_TxAmpPhy14_Msk     0x00003F80UL
#define MDR_1923KX028_Ctrl13_TxAmpPhy15_Pos     14
#define MDR_1923KX028_Ctrl13_TxAmpPhy15_Msk     0x001FC000UL
#define MDR_1923KX028_Ctrl13_TxAmpPhy16_Pos     21
#define MDR_1923KX028_Ctrl13_TxAmpPhy16_Msk     0x0FE00000UL
#define MDR_1923KX028_Ctrl13_TxCommEnPhy1_Pos   28
#define MDR_1923KX028_Ctrl13_TxCommEnPhy1_Msk   0x10000000UL
#define MDR_1923KX028_Ctrl13_TxCommEnPhy2_Pos   29
#define MDR_1923KX028_Ctrl13_TxCommEnPhy2_Msk   0x20000000UL
#define MDR_1923KX028_Ctrl13_TxCommEnPhy3_Pos   30
#define MDR_1923KX028_Ctrl13_TxCommEnPhy3_Msk   0x40000000UL
#define MDR_1923KX028_Ctrl13_TxCommEnPhy4_Pos   31
#define MDR_1923KX028_Ctrl13_TxCommEnPhy4_Msk   0x80000000UL

typedef union {
  __IOM uint32_t             value;
  MDR_1923KX028_Ctrl13_Bits  bits;
} MDR_1923KX028_Ctrl13_t;


/* =========================================================  Control 14  ====================================================== */
typedef struct {
  __IOM uint32_t  TxCommEnPhy5     : 1;
  __IOM uint32_t  TxCommEnPhy6     : 1;
  __IOM uint32_t  TxCommEnPhy7     : 1;
  __IOM uint32_t  TxCommEnPhy8     : 1;
  __IOM uint32_t  TxCommEnPhy9     : 1;
  __IOM uint32_t  TxCommEnPhy10    : 1;
  __IOM uint32_t  TxCommEnPhy11    : 1;
  __IOM uint32_t  TxCommEnPhy12    : 1;
  __IOM uint32_t  TxCommEnPhy13    : 1;
  __IOM uint32_t  TxCommEnPhy14    : 1;
  __IOM uint32_t  TxCommEnPhy15    : 1;
  __IOM uint32_t  TxCommEnPhy16    : 1;  
  __IOM uint32_t  TxDetectReqPhy1  : 1;
  __IOM uint32_t  TxDetectReqPhy2  : 1;
  __IOM uint32_t  TxDetectReqPhy3  : 1;
  __IOM uint32_t  TxDetectReqPhy4  : 1;
  __IOM uint32_t  TxDetectReqPhy5  : 1;
  __IOM uint32_t  TxDetectReqPhy6  : 1;
  __IOM uint32_t  TxDetectReqPhy7  : 1;
  __IOM uint32_t  TxDetectReqPhy8  : 1;
  __IOM uint32_t  TxDetectReqPhy9  : 1;
  __IOM uint32_t  TxDetectReqPhy10 : 1;
  __IOM uint32_t  TxDetectReqPhy11 : 1;
  __IOM uint32_t  TxDetectReqPhy12 : 1;
  __IOM uint32_t  TxDetectReqPhy13 : 1;
  __IOM uint32_t  TxDetectReqPhy14 : 1;
  __IOM uint32_t  TxDetectReqPhy15 : 1;
  __IOM uint32_t  TxDetectReqPhy16 : 1;
  __IM  uint32_t                   : 4;
} MDR_1923KX028_Ctrl14_Bits;

#define MDR_1923KX028_Ctrl14_TxCommEnPhy5_Pos       0
#define MDR_1923KX028_Ctrl14_TxCommEnPhy5_Msk       0x00000001UL
#define MDR_1923KX028_Ctrl14_TxCommEnPhy6_Pos       1
#define MDR_1923KX028_Ctrl14_TxCommEnPhy6_Msk       0x00000002UL
#define MDR_1923KX028_Ctrl14_TxCommEnPhy7_Pos       2
#define MDR_1923KX028_Ctrl14_TxCommEnPhy7_Msk       0x00000004UL
#define MDR_1923KX028_Ctrl14_TxCommEnPhy8_Pos       3
#define MDR_1923KX028_Ctrl14_TxCommEnPhy8_Msk       0x00000008UL
#define MDR_1923KX028_Ctrl14_TxCommEnPhy9_Pos       4
#define MDR_1923KX028_Ctrl14_TxCommEnPhy9_Msk       0x00000010UL
#define MDR_1923KX028_Ctrl14_TxCommEnPhy10_Pos      5
#define MDR_1923KX028_Ctrl14_TxCommEnPhy10_Msk      0x00000020UL
#define MDR_1923KX028_Ctrl14_TxCommEnPhy11_Pos      6
#define MDR_1923KX028_Ctrl14_TxCommEnPhy11_Msk      0x00000040UL
#define MDR_1923KX028_Ctrl14_TxCommEnPhy12_Pos      7
#define MDR_1923KX028_Ctrl14_TxCommEnPhy12_Msk      0x00000080UL
#define MDR_1923KX028_Ctrl14_TxCommEnPhy13_Pos      8
#define MDR_1923KX028_Ctrl14_TxCommEnPhy13_Msk      0x0000010UL
#define MDR_1923KX028_Ctrl14_TxCommEnPhy14_Pos      9
#define MDR_1923KX028_Ctrl14_TxCommEnPhy14_Msk      0x00000200UL
#define MDR_1923KX028_Ctrl14_TxCommEnPhy15_Pos      10
#define MDR_1923KX028_Ctrl14_TxCommEnPhy15_Msk      0x00000400UL
#define MDR_1923KX028_Ctrl14_TxCommEnPhy16_Pos      11
#define MDR_1923KX028_Ctrl14_TxCommEnPhy16_Msk      0x00000800UL
#define MDR_1923KX028_Ctrl14_TxDetectReqPhy1_Pos    12
#define MDR_1923KX028_Ctrl14_TxDetectReqPhy1_Msk    0x00001000UL
#define MDR_1923KX028_Ctrl14_TxDetectReqPhy2_Pos    13
#define MDR_1923KX028_Ctrl14_TxDetectReqPhy2_Msk    0x00002000UL
#define MDR_1923KX028_Ctrl14_TxDetectReqPhy3_Pos    14
#define MDR_1923KX028_Ctrl14_TxDetectReqPhy3_Msk    0x00004000UL
#define MDR_1923KX028_Ctrl14_TxDetectReqPhy4_Pos    15
#define MDR_1923KX028_Ctrl14_TxDetectReqPhy4_Msk    0x00008000UL
#define MDR_1923KX028_Ctrl14_TxDetectReqPhy5_Pos    16
#define MDR_1923KX028_Ctrl14_TxDetectReqPhy5_Msk    0x00010000UL
#define MDR_1923KX028_Ctrl14_TxDetectReqPhy6_Pos    17
#define MDR_1923KX028_Ctrl14_TxDetectReqPhy6_Msk    0x00020000UL
#define MDR_1923KX028_Ctrl14_TxDetectReqPhy7_Pos    18
#define MDR_1923KX028_Ctrl14_TxDetectReqPhy7_Msk    0x00040000UL
#define MDR_1923KX028_Ctrl14_TxDetectReqPhy8_Pos    19
#define MDR_1923KX028_Ctrl14_TxDetectReqPhy8_Msk    0x00080000UL
#define MDR_1923KX028_Ctrl14_TxDetectReqPhy9_Pos    20
#define MDR_1923KX028_Ctrl14_TxDetectReqPhy9_Msk    0x00100000UL
#define MDR_1923KX028_Ctrl14_TxDetectReqPhy10_Pos   21
#define MDR_1923KX028_Ctrl14_TxDetectReqPhy10_Msk   0x00200000UL
#define MDR_1923KX028_Ctrl14_TxDetectReqPhy11_Pos   22
#define MDR_1923KX028_Ctrl14_TxDetectReqPhy11_Msk   0x00400000UL
#define MDR_1923KX028_Ctrl14_TxDetectReqPhy12_Pos   23
#define MDR_1923KX028_Ctrl14_TxDetectReqPhy12_Msk   0x00800000UL
#define MDR_1923KX028_Ctrl14_TxDetectReqPhy13_Pos   24
#define MDR_1923KX028_Ctrl14_TxDetectReqPhy13_Msk   0x01000000UL
#define MDR_1923KX028_Ctrl14_TxDetectReqPhy14_Pos   25
#define MDR_1923KX028_Ctrl14_TxDetectReqPhy14_Msk   0x02000000UL
#define MDR_1923KX028_Ctrl14_TxDetectReqPhy15_Pos   26
#define MDR_1923KX028_Ctrl14_TxDetectReqPhy15_Msk   0x04000000UL
#define MDR_1923KX028_Ctrl14_TxDetectReqPhy16_Pos   27
#define MDR_1923KX028_Ctrl14_TxDetectReqPhy16_Msk   0x08000000UL

typedef union {
  __IOM uint32_t             value;
  MDR_1923KX028_Ctrl14_Bits  bits;
} MDR_1923KX028_Ctrl14_t;


/* =========================================================  Control 15  ====================================================== */
typedef struct {
  __IOM uint32_t  TxPreEmphPhy1     : 7;
  __IOM uint32_t  TxPreEmphPhy2     : 7;
  __IOM uint32_t  TxPreEmphPhy3     : 7;
  __IOM uint32_t  TxPreEmphPhy4     : 7;
  __IM  uint32_t                    : 4;  
} MDR_1923KX028_Ctrl15_Bits;

#define MDR_1923KX028_Ctrl15_TxPreEmphPhy1_Pos     0
#define MDR_1923KX028_Ctrl15_TxPreEmphPhy1_Msk     0x0000007FUL
#define MDR_1923KX028_Ctrl15_TxPreEmphPhy2_Pos     7
#define MDR_1923KX028_Ctrl15_TxPreEmphPhy2_Msk     0x00003F80UL
#define MDR_1923KX028_Ctrl15_TxPreEmphPhy3_Pos     14
#define MDR_1923KX028_Ctrl15_TxPreEmphPhy3_Msk     0x001FC000UL
#define MDR_1923KX028_Ctrl15_TxPreEmphPhy4_Pos     21
#define MDR_1923KX028_Ctrl15_TxPreEmphPhy4_Msk     0x0FE00000UL

typedef union {
  __IOM uint32_t             value;
  MDR_1923KX028_Ctrl15_Bits  bits;
} MDR_1923KX028_Ctrl15_t;


/* =========================================================  Control 16  ====================================================== */
typedef struct {
  __IOM uint32_t  TxPreEmphPhy5     : 7;
  __IOM uint32_t  TxPreEmphPhy6     : 7;
  __IOM uint32_t  TxPreEmphPhy7     : 7;
  __IOM uint32_t  TxPreEmphPhy8     : 7;
  __IM  uint32_t                    : 4;  
} MDR_1923KX028_Ctrl16_Bits;

#define MDR_1923KX028_Ctrl16_TxPreEmphPhy5_Pos     0
#define MDR_1923KX028_Ctrl16_TxPreEmphPhy5_Msk     0x0000007FUL
#define MDR_1923KX028_Ctrl16_TxPreEmphPhy6_Pos     7
#define MDR_1923KX028_Ctrl16_TxPreEmphPhy6_Msk     0x00003F80UL
#define MDR_1923KX028_Ctrl16_TxPreEmphPhy7_Pos     14
#define MDR_1923KX028_Ctrl16_TxPreEmphPhy7_Msk     0x001FC000UL
#define MDR_1923KX028_Ctrl16_TxPreEmphPhy8_Pos     21
#define MDR_1923KX028_Ctrl16_TxPreEmphPhy8_Msk     0x0FE00000UL

typedef union {
  __IOM uint32_t             value;
  MDR_1923KX028_Ctrl16_Bits  bits;
} MDR_1923KX028_Ctrl16_t;


/* =========================================================  Control 17  ====================================================== */
typedef struct {
  __IOM uint32_t  TxPreEmphPhy9     : 7;
  __IOM uint32_t  TxPreEmphPhy10    : 7;
  __IOM uint32_t  TxPreEmphPhy11    : 7;
  __IOM uint32_t  TxPreEmphPhy12    : 7;
  __IM  uint32_t                    : 4;  
} MDR_1923KX028_Ctrl17_Bits;

#define MDR_1923KX028_Ctrl17_TxPreEmphPhy9_Pos     0
#define MDR_1923KX028_Ctrl17_TxPreEmphPhy9_Msk     0x0000007FUL
#define MDR_1923KX028_Ctrl17_TxPreEmphPhy10_Pos    7
#define MDR_1923KX028_Ctrl17_TxPreEmphPhy10_Msk    0x00003F80UL
#define MDR_1923KX028_Ctrl17_TxPreEmphPhy11_Pos    14
#define MDR_1923KX028_Ctrl17_TxPreEmphPhy11_Msk    0x001FC000UL
#define MDR_1923KX028_Ctrl17_TxPreEmphPhy12_Pos    21
#define MDR_1923KX028_Ctrl17_TxPreEmphPhy12_Msk    0x0FE00000UL

typedef union {
  __IOM uint32_t             value;
  MDR_1923KX028_Ctrl17_Bits  bits;
} MDR_1923KX028_Ctrl17_t;


/* =========================================================  Control 18  ====================================================== */
typedef struct {
  __IOM uint32_t  TxPreEmphPhy13    : 7;
  __IOM uint32_t  TxPreEmphPhy14    : 7;
  __IOM uint32_t  TxPreEmphPhy15    : 7;
  __IOM uint32_t  TxPreEmphPhy16    : 7;
  __IOM uint32_t  SelPhyToShowSpeed : 4;  
} MDR_1923KX028_Ctrl18_Bits;

#define MDR_1923KX028_Ctrl18_TxPreEmphPhy13_Pos     0
#define MDR_1923KX028_Ctrl18_TxPreEmphPhy13_Msk     0x0000007FUL
#define MDR_1923KX028_Ctrl18_TxPreEmphPhy14_Pos     7
#define MDR_1923KX028_Ctrl18_TxPreEmphPhy14_Msk     0x00003F80UL
#define MDR_1923KX028_Ctrl18_TxPreEmphPhy15_Pos     14
#define MDR_1923KX028_Ctrl18_TxPreEmphPhy15_Msk     0x001FC000UL
#define MDR_1923KX028_Ctrl18_TxPreEmphPhy16_Pos     21
#define MDR_1923KX028_Ctrl18_TxPreEmphPhy16_Msk     0x0FE00000UL
#define MDR_1923KX028_Ctrl18_SelPhyToShowSpeed_Pos  28
#define MDR_1923KX028_Ctrl18_SelPhyToShowSpeed_Msk  0xF0000000UL

typedef union {
  __IOM uint32_t             value;
  MDR_1923KX028_Ctrl18_Bits  bits;
} MDR_1923KX028_Ctrl18_t;


/* =========================================================  Control 19  ====================================================== */
#define MDR_1923KX028_TxTermOffsPhy_Def   0xF

typedef struct {
  __IOM uint32_t  TxTermOffsPhy1    : 5;
  __IOM uint32_t  TxTermOffsPhy2    : 5;
  __IOM uint32_t  TxTermOffsPhy3    : 5;
  __IOM uint32_t  TxTermOffsPhy4    : 5;
  __IOM uint32_t  TxTermOffsPhy5    : 5;
  __IOM uint32_t  TxTermOffsPhy6    : 5;
  __IM  uint32_t                    : 2;  
} MDR_1923KX028_Ctrl19_Bits;

#define MDR_1923KX028_Ctrl19_TxTermOffsPhy1_Pos     0
#define MDR_1923KX028_Ctrl19_TxTermOffsPhy1_Msk     0x0000001FUL
#define MDR_1923KX028_Ctrl19_TxTermOffsPhy2_Pos     5
#define MDR_1923KX028_Ctrl19_TxTermOffsPhy2_Msk     0x000003E0UL
#define MDR_1923KX028_Ctrl19_TxTermOffsPhy3_Pos     10
#define MDR_1923KX028_Ctrl19_TxTermOffsPhy3_Msk     0x00007C00UL
#define MDR_1923KX028_Ctrl19_TxTermOffsPhy4_Pos     15
#define MDR_1923KX028_Ctrl19_TxTermOffsPhy4_Msk     0x000F9000UL
#define MDR_1923KX028_Ctrl19_TxTermOffsPhy5_Pos     20
#define MDR_1923KX028_Ctrl19_TxTermOffsPhy5_Msk     0x01F00000UL
#define MDR_1923KX028_Ctrl19_TxTermOffsPhy6_Pos     25
#define MDR_1923KX028_Ctrl19_TxTermOffsPhy6_Msk     0x3E000000UL

#define MDR_1923KX028_Ctrl19_TxTermOffsPhy1_6_Msk   ( MDR_1923KX028_Ctrl19_TxTermOffsPhy1_Msk \
                                                    | MDR_1923KX028_Ctrl19_TxTermOffsPhy2_Msk \
                                                    | MDR_1923KX028_Ctrl19_TxTermOffsPhy3_Msk \
                                                    | MDR_1923KX028_Ctrl19_TxTermOffsPhy4_Msk \
                                                    | MDR_1923KX028_Ctrl19_TxTermOffsPhy5_Msk \
                                                    | MDR_1923KX028_Ctrl19_TxTermOffsPhy6_Msk )

typedef union {
  __IOM uint32_t             value;
  MDR_1923KX028_Ctrl19_Bits  bits;
} MDR_1923KX028_Ctrl19_t;


/* =========================================================  Control 20  ====================================================== */
typedef struct {
  __IOM uint32_t  TxTermOffsPhy7    : 5;
  __IOM uint32_t  TxTermOffsPhy8    : 5;
  __IOM uint32_t  TxTermOffsPhy9    : 5;
  __IOM uint32_t  TxTermOffsPhy10   : 5;
  __IOM uint32_t  TxTermOffsPhy11   : 5;
  __IOM uint32_t  TxTermOffsPhy12   : 5;
  __IOM uint32_t  PorUccEn          : 1;  
  __IOM uint32_t  PorUccIOEn        : 1;  
} MDR_1923KX028_Ctrl20_Bits;

#define MDR_1923KX028_Ctrl20_TxTermOffsPhy7_Pos     0
#define MDR_1923KX028_Ctrl20_TxTermOffsPhy7_Msk     0x0000001FUL
#define MDR_1923KX028_Ctrl20_TxTermOffsPhy8_Pos     5
#define MDR_1923KX028_Ctrl20_TxTermOffsPhy8_Msk     0x000003E0UL
#define MDR_1923KX028_Ctrl20_TxTermOffsPhy9_Pos     10
#define MDR_1923KX028_Ctrl20_TxTermOffsPhy9_Msk     0x00007C00UL
#define MDR_1923KX028_Ctrl20_TxTermOffsPhy10_Pos    15
#define MDR_1923KX028_Ctrl20_TxTermOffsPhy10_Msk    0x000F9000UL
#define MDR_1923KX028_Ctrl20_TxTermOffsPhy11_Pos    20
#define MDR_1923KX028_Ctrl20_TxTermOffsPhy11_Msk    0x01F00000UL
#define MDR_1923KX028_Ctrl20_TxTermOffsPhy12_Pos    25
#define MDR_1923KX028_Ctrl20_TxTermOffsPhy12_Msk    0x3E000000UL
#define MDR_1923KX028_Ctrl20_PorUccEn_Pos           30
#define MDR_1923KX028_Ctrl20_PorUccEn_Msk           0x40000000UL
#define MDR_1923KX028_Ctrl20_PorUccIOEn_Pos         31
#define MDR_1923KX028_Ctrl20_PorUccIOEn_Msk         0x80000000UL

#define MDR_1923KX028_Ctrl20_TxTermOffsPhy7_12_Msk   (MDR_1923KX028_Ctrl20_TxTermOffsPhy7_Msk \
                                                    | MDR_1923KX028_Ctrl20_TxTermOffsPhy8_Msk \
                                                    | MDR_1923KX028_Ctrl20_TxTermOffsPhy9_Msk \
                                                    | MDR_1923KX028_Ctrl20_TxTermOffsPhy10_Msk \
                                                    | MDR_1923KX028_Ctrl20_TxTermOffsPhy11_Msk \
                                                    | MDR_1923KX028_Ctrl20_TxTermOffsPhy12_Msk )

typedef union {
  __IOM uint32_t             value;
  MDR_1923KX028_Ctrl20_Bits  bits;
} MDR_1923KX028_Ctrl20_t;


/* =========================================================  Control 21  ====================================================== */
typedef struct {
  __IOM uint32_t  TxTermOffsPhy13   : 5;
  __IOM uint32_t  TxTermOffsPhy14   : 5;
  __IOM uint32_t  TxTermOffsPhy15   : 5;
  __IOM uint32_t  TxTermOffsPhy16   : 5;
  __IOM uint32_t  TxDataPhyAllEn    : 1;
  __IOM uint32_t  TxPhyAllEn        : 1;
  __IOM uint32_t  SscRefClkSel      : 9;  
  __IOM uint32_t  Lane10BitSel      : 1;  
} MDR_1923KX028_Ctrl21_Bits;

#define MDR_1923KX028_Ctrl21_TxTermOffsPhy13_Pos   0
#define MDR_1923KX028_Ctrl21_TxTermOffsPhy13_Msk   0x0000001FUL
#define MDR_1923KX028_Ctrl21_TxTermOffsPhy14_Pos   5
#define MDR_1923KX028_Ctrl21_TxTermOffsPhy14_Msk   0x000003E0UL
#define MDR_1923KX028_Ctrl21_TxTermOffsPhy15_Pos   10
#define MDR_1923KX028_Ctrl21_TxTermOffsPhy15_Msk   0x00007C00UL
#define MDR_1923KX028_Ctrl21_TxTermOffsPhy16_Pos   15
#define MDR_1923KX028_Ctrl21_TxTermOffsPhy16_Msk   0x000F9000UL
#define MDR_1923KX028_Ctrl21_TxDataPhyAllEn_Pos    20
#define MDR_1923KX028_Ctrl21_TxDataPhyAllEn_Msk    0x00100000UL
#define MDR_1923KX028_Ctrl21_TxPhyAllEn_Pos        21
#define MDR_1923KX028_Ctrl21_TxPhyAllEn_Msk        0x00200000UL
#define MDR_1923KX028_Ctrl21_SscRefClkSel_Pos      22
#define MDR_1923KX028_Ctrl21_SscRefClkSel_Msk      0x7FC00000UL
#define MDR_1923KX028_Ctrl21_Lane10BitSel_Pos      31
#define MDR_1923KX028_Ctrl21_Lane10BitSel_Msk      0x80000000UL

#define MDR_1923KX028_Ctrl21_TxTermOffsPhy13_16_Msk  (MDR_1923KX028_Ctrl21_TxTermOffsPhy13_Msk \
                                                    | MDR_1923KX028_Ctrl21_TxTermOffsPhy14_Msk \
                                                    | MDR_1923KX028_Ctrl21_TxTermOffsPhy15_Msk \
                                                    | MDR_1923KX028_Ctrl21_TxTermOffsPhy16_Msk)

typedef union {
  __IOM uint32_t             value;
  MDR_1923KX028_Ctrl21_Bits  bits;
} MDR_1923KX028_Ctrl21_t;


/* =========================================================  Control 22  ====================================================== */
#define MDR_1923KX028_Ctrl22_PCIeLosBias    MDR_1923KX028_LosBias
#define MDR_1923KX028_Ctrl22_PCIeAcjtLvl    MDR_1923KX028_AcjtLvl

typedef struct {
  __IOM uint32_t  PCIePLL_Mul       : 7;
  __IOM uint32_t  PCIeLosLvl        : 5;
  __IOM uint32_t  PCIeTxBoost       : 3;
  __IOM uint32_t  PCIeLosBias       : 3;    //  MDR_1923KX028_Ctrl22_PCIeLosBias
  __IOM uint32_t  PCIeAcjtLvl       : 5;    //  MDR_1923KX028_Ctrl22_PCIeAcjtLvl
  __IOM uint32_t  PCIeRxEq          : 3;
  __IOM uint32_t  PCIeTxTermOffs    : 5;  
  __IM  uint32_t                    : 1;
} MDR_1923KX028_Ctrl22_Bits;

#define MDR_1923KX028_Ctrl22_PCIePLL_Mul_Pos      0
#define MDR_1923KX028_Ctrl22_PCIePLL_Mul_Msk      0x0000007FUL
#define MDR_1923KX028_Ctrl22_PCIeLosLvl_Pos       7
#define MDR_1923KX028_Ctrl22_PCIeLosLvl_Msk       0x00000F80UL
#define MDR_1923KX028_Ctrl22_PCIeTxBoost_Pos      12
#define MDR_1923KX028_Ctrl22_PCIeTxBoost_Msk      0x00007000UL
#define MDR_1923KX028_Ctrl22_PCIeLosBias_Pos      15
#define MDR_1923KX028_Ctrl22_PCIeLosBias_Msk      0x00038000UL
#define MDR_1923KX028_Ctrl22_PCIeAcjtLvl_Pos      18
#define MDR_1923KX028_Ctrl22_PCIeAcjtLvl_Msk      0x007C0000UL
#define MDR_1923KX028_Ctrl22_PCIeRxEqn_Pos        23
#define MDR_1923KX028_Ctrl22_PCIeRxEq_Msk         0x03800000UL
#define MDR_1923KX028_Ctrl22_PCIeTxTermOffs_Pos   26
#define MDR_1923KX028_Ctrl22_PCIeTxTermOffs_Msk   0x7C000000UL

typedef union {
  __IOM uint32_t             value;
  MDR_1923KX028_Ctrl22_Bits  bits;
} MDR_1923KX028_Ctrl22_t;


/* =========================================================  Control 23  ====================================================== */
typedef struct {
  __IOM uint32_t  PCIeTxPreEmphGen2_3db5  : 6;
  __IOM uint32_t  PCIeTxPreEmphGen1_3db5  : 6;
  __IOM uint32_t  PCIeTxSwingFull        : 7;
  __IOM uint32_t  PCIeTxSwingLow         : 7;
  __IOM uint32_t  PCIeTxPreEmphGen2_6db   : 6;
} MDR_1923KX028_Ctrl23_Bits;

#define MDR_1923KX028_Ctrl23_PCIeTxPreEmphGen2_3db5_Pos   0
#define MDR_1923KX028_Ctrl23_PCIeTxPreEmphGen2_3db5_Msk   0x0000003FUL
#define MDR_1923KX028_Ctrl23_PCIeTxPreEmphGen1_3db5_Pos   6
#define MDR_1923KX028_Ctrl23_PCIeTxPreEmphGen1_3db5l_Msk  0x00000FC0UL
#define MDR_1923KX028_Ctrl23_PCIeTxSwingFull_Pos          12
#define MDR_1923KX028_Ctrl23_PCIeTxSwingFull_Msk          0x0007F000UL
#define MDR_1923KX028_Ctrl23_PCIeTxSwingLow_Pos           19
#define MDR_1923KX028_Ctrl23_PCIeTxSwingLow_Msk           0x03F80000UL
#define MDR_1923KX028_Ctrl23_PCIeTxPreEmphGen2_6db_Pos    26
#define MDR_1923KX028_Ctrl23_PCIeTxPreEmphGen2_6db_Msk    0xFC000000UL

typedef union {
  __IOM uint32_t             value;
  MDR_1923KX028_Ctrl23_Bits  bits;
} MDR_1923KX028_Ctrl23_t;


/* ============================================================================================================================= */
/* =========================================================  STATUS_MODE0  ==================================================== */
/* ============================================================================================================================= */

/* =========================================================  M0_Status 1  ====================================================== */
typedef struct {
  __IOM uint32_t  CfgMsiEn              : 1;
  __IOM uint32_t  VenMsiGrant           : 1;
  __IOM uint32_t  VenMsgGrant           : 1;
  __IOM uint32_t  RdlhLinkUp            : 1;
  __IOM uint32_t  BrdgSlvXferPending    : 1;
  __IOM uint32_t  BrdgDbiXferPending    : 1;
  __IOM uint32_t  RadmXferPending       : 1;
  __IOM uint32_t  RadmQNotEmpty         : 1;
  __IOM uint32_t  RadmQOverflow         : 1;
  __IOM uint32_t  EIOS_Detected         : 1;
  __IOM uint32_t  g2LTSSM_L1            : 1;
  __IOM uint32_t  g2LTSSM_L2            : 1;
  __IOM uint32_t  g2LTSSM_RxL0          : 1;
  __IOM uint32_t  g2LTSSM_Disabled      : 1;
  __IOM uint32_t  g2LTSSM_DetectQuiet   : 1;
  __IOM uint32_t  g2LTSSM_PollActive    : 1;
  __IOM uint32_t  g2LTSSM_PollCompat    : 1;
  __IOM uint32_t  g3LTSSM_BeforeL1L2    : 1;
  __IOM uint32_t  g3LTSSM_BeforeDis     : 1;
  __IOM uint32_t  g3LTSSM_LB_SlaveGen1  : 1;
  __IOM uint32_t  g3LTSSM_PollActive    : 1;
  __IOM uint32_t  g4LTSSM_ToRecovery    : 1;
  __IOM uint32_t  g4LTSSM_ToSpeed       : 1;
  __IOM uint32_t  g4LTSSM_EI_Speed      : 1;
  __IOM uint32_t  g4LTSSM_EI_LB         : 1;
  __IM  uint32_t                        : 7;
} MDR_1923KX028_M0_Status1_Bits;

#define MDR_1923KX028_M0_Status1_CfgMsiEn_Pos             0
#define MDR_1923KX028_M0_Status1_CfgMsiEn_Msk             0x00000001UL
#define MDR_1923KX028_M0_Status1_VenMsiGrant_Pos          1
#define MDR_1923KX028_M0_Status1_VenMsiGrant_Msk          0x00000002UL
#define MDR_1923KX028_M0_Status1_VenMsgGrant_Pos          2
#define MDR_1923KX028_M0_Status1_VenMsgGrant_Msk          0x00000004UL
#define MDR_1923KX028_M0_Status1_RdlhLinkUp_Pos           3
#define MDR_1923KX028_M0_Status1_RdlhLinkUp_Msk           0x00000008UL
#define MDR_1923KX028_M0_Status1_BrdgSlvXferPend_Pos      4
#define MDR_1923KX028_M0_Status1_BrdgSlvXferPend_Msk      0x00000010UL
#define MDR_1923KX028_M0_Status1_BrdgDbiXferPend_Pos      5
#define MDR_1923KX028_M0_Status1_BrdgDbiXferPend_Msk      0x00000020UL
#define MDR_1923KX028_M0_Status1_RadmXferPend_Pos         6
#define MDR_1923KX028_M0_Status1_RadmXferPend_Msk         0x00000040UL
#define MDR_1923KX028_M0_Status1_RadmQNotEmpty_Pos        7
#define MDR_1923KX028_M0_Status1_RadmQNotEmpty_Msk        0x00000080UL
#define MDR_1923KX028_M0_Status1_RadmQOverflow_Pos        8
#define MDR_1923KX028_M0_Status1_RadmQOverflow_Msk        0x00000100UL
#define MDR_1923KX028_M0_Status1_EIOS_Detected_Pos        9
#define MDR_1923KX028_M0_Status1_EIOS_Detected_Msk        0x00000200UL
#define MDR_1923KX028_M0_Status1_g2LTSSM_L1_Pos           10
#define MDR_1923KX028_M0_Status1_g2LTSSM_L1_Msk           0x00000400UL
#define MDR_1923KX028_M0_Status1_g2LTSSM_L2_Pos           11
#define MDR_1923KX028_M0_Status1_g2LTSSM_L2_Msk           0x00000800UL
#define MDR_1923KX028_M0_Status1_g2LTSSM_RxL0_Pos         12
#define MDR_1923KX028_M0_Status1_g2LTSSM_RxL0_Msk         0x00001000UL
#define MDR_1923KX028_M0_Status1_g2LTSSM_Dis_Pos          13
#define MDR_1923KX028_M0_Status1_g2LTSSM_Dis_Msk          0x00002000UL
#define MDR_1923KX028_M0_Status1_g2LTSSM_DetQuiet_Pos     14
#define MDR_1923KX028_M0_Status1_g2LTSSM_DetQuiet_Msk     0x00004000UL
#define MDR_1923KX028_M0_Status1_g2LTSSM_PollActive_Pos   15
#define MDR_1923KX028_M0_Status1_g2LTSSM_PollActive_Msk   0x00008000UL
#define MDR_1923KX028_M0_Status1_g2LTSSM_PollCompat_Pos   16
#define MDR_1923KX028_M0_Status1_g2LTSSM_PollCompat_Msk   0x00010000UL
#define MDR_1923KX028_M0_Status1_g3LTSSM_BeforeL1L2_Pos   17
#define MDR_1923KX028_M0_Status1_g3LTSSM_BeforeL1L2_Msk   0x00020000UL
#define MDR_1923KX028_M0_Status1_g3LTSSM_BeforeDis_Pos    18
#define MDR_1923KX028_M0_Status1_g3LTSSM_BeforeDis_Msk    0x00040000UL
#define MDR_1923KX028_M0_Status1_g3LTSSM_LB_SlaveGen1_Pos 19
#define MDR_1923KX028_M0_Status1_g3LTSSM_LB_SlaveGen1_Msk 0x00080000UL
#define MDR_1923KX028_M0_Status1_g3LTSSM_PollActive_Pos   20
#define MDR_1923KX028_M0_Status1_g3LTSSM_PollActive_Msk   0x00100000UL
#define MDR_1923KX028_M0_Status1_g4LTSSM_ToRecovery_Pos   21
#define MDR_1923KX028_M0_Status1_g4LTSSM_ToRecovery_Msk   0x00200000UL
#define MDR_1923KX028_M0_Status1_g4LTSSM_ToSpeed_Pos      22
#define MDR_1923KX028_M0_Status1_g4LTSSM_ToSpeed_Msk      0x00400000UL
#define MDR_1923KX028_M0_Status1_g4LTSSM_EI_Speed_Pos     23
#define MDR_1923KX028_M0_Status1_g4LTSSM_EI_Speed_Msk     0x00800000UL
#define MDR_1923KX028_M0_Status1_g4LTSSM_EI_LB_Pos        24
#define MDR_1923KX028_M0_Status1_g4LTSSM_EI_LB_Msk        0x01000000UL

typedef union {
  __IOM uint32_t                 value;
  MDR_1923KX028_M0_Status1_Bits  bits;
} MDR_1923KX028_M0_Status1_t;


/* =========================================================  M0_Status 2  ====================================================== */
typedef struct {
  __IOM uint32_t  LTSSM_State      : 6;
  __IOM uint32_t  MacPhyTxDataK    : 2;
  __IOM uint32_t  MacPhyTxData     : 16;
  __IOM uint32_t  RmlhRcvdIdle     : 1;
  __IOM uint32_t  RmlhTsLinkK237  : 1;
  __IOM uint32_t  RmlhTsLaneK237  : 1;
  __IOM uint32_t  RmlhTsLinkCtrl   : 1;
  __IM  uint32_t                   : 4;
} MDR_1923KX028_M0_Status2_Bits;

#define MDR_1923KX028_M0_Status2_LTSSM_State_Pos       0
#define MDR_1923KX028_M0_Status2_LTSSM_State_Msk       0x0000003FUL
#define MDR_1923KX028_M0_Status2_MacPhyTxDataK_Pos     6
#define MDR_1923KX028_M0_Status2_MacPhyTxDataK_Msk     0x000000C0UL
#define MDR_1923KX028_M0_Status2_MacPhyTxData_Pos      8
#define MDR_1923KX028_M0_Status2_MacPhyTxData_Msk      0x00FFFF00UL
#define MDR_1923KX028_M0_Status2_RmlhRcvdIdle_Pos      24
#define MDR_1923KX028_M0_Status2_RmlhRcvdIdle_Msk      0x01000000UL
#define MDR_1923KX028_M0_Status2_RmlhTsLinkK237_Pos    25
#define MDR_1923KX028_M0_Status2_RmlhTsLinkK237_Msk    0x02000000UL
#define MDR_1923KX028_M0_Status2_RmlhTsLaneK237_Pos    26
#define MDR_1923KX028_M0_Status2_RmlhTsLaneK237_Msk    0x04000000UL
#define MDR_1923KX028_M0_Status2_RmlhTsLinkCtrl_Pos    27
#define MDR_1923KX028_M0_Status2_RmlhTsLinkCtrl_Msk    0x08000000UL

typedef union {
  __IOM uint32_t                 value;
  MDR_1923KX028_M0_Status2_Bits  bits;
} MDR_1923KX028_M0_Status2_t;


/* =========================================================  M0_Status 3  ====================================================== */
typedef struct {
  __IOM uint32_t  RmlhRcvdLaneRev     : 1;
  __IOM uint32_t  RmlhTs2Rcvd         : 1;
  __IOM uint32_t  RmlhTs1Rcvd         : 1;
  __IOM uint32_t  RmlhInSkipRcv       : 1;
  __IOM uint32_t  RmlhLinkUp          : 1;
  __IOM uint32_t  XmtByteSkipSend     : 1;
  __IM  uint32_t                      : 2;  
  __IOM uint32_t  RmlhTsLinkNum       : 8;
  __IM  uint32_t                      : 3;
  __IOM uint32_t  ReqAppInitRst       : 1;
  __IOM uint32_t  ReqTxCompat         : 1;
  __IOM uint32_t  ReqTxElectIdle      : 1;
  __IOM uint32_t  ReqDetectLB         : 1;
  __IM  uint32_t                      : 4;
  __IOM uint32_t  SmlhTrain_nRst      : 1;
  __IOM uint32_t  SmlhLTSSM_PollCfg   : 1;
  __IOM uint32_t  SmlhLinkInTrain     : 1;
  __IOM uint32_t  SmlhLinkDis         : 1;
  __IOM uint32_t  SmlhScrambDis       : 1;
} MDR_1923KX028_M0_Status3_Bits;

#define MDR_1923KX028_M0_Status3_RmlhRcvdLaneRev_Pos    0
#define MDR_1923KX028_M0_Status3_RmlhRcvdLaneRev_Msk    0x00000001UL
#define MDR_1923KX028_M0_Status3_RmlhTs2Rcvd_Pos        1
#define MDR_1923KX028_M0_Status3_RmlhTs2Rcvd_Msk        0x00000002UL
#define MDR_1923KX028_M0_Status3_RmlhTs1Rcvd_Pos        2
#define MDR_1923KX028_M0_Status3_RmlhTs1Rcvd_Msk        0x00000004UL
#define MDR_1923KX028_M0_Status3_RmlhInSkipRcv_Pos      3
#define MDR_1923KX028_M0_Status3_RmlhInSkipRcv_Msk      0x00000008UL
#define MDR_1923KX028_M0_Status3_RmlhLinkUp_Pos         4
#define MDR_1923KX028_M0_Status3_RmlhLinkUp_Msk         0x00000010UL
#define MDR_1923KX028_M0_Status3_XmtByteSkipSend_Pos    5
#define MDR_1923KX028_M0_Status3_XmtByteSkipSend_Msk    0x00000020UL
#define MDR_1923KX028_M0_Status3_RmlhTsLinkNum_Pos      8
#define MDR_1923KX028_M0_Status3_RmlhTsLinkNum_Msk      0x0000FF00UL
#define MDR_1923KX028_M0_Status3_ReqAppInitRst_Pos      19
#define MDR_1923KX028_M0_Status3_ReqAppInitRst_Msk      0x00080000UL
#define MDR_1923KX028_M0_Status3_ReqTxCompat_Pos        20
#define MDR_1923KX028_M0_Status3_ReqTxCompat_Msk        0x00100000UL
#define MDR_1923KX028_M0_Status3_ReqTxElectIdle_Pos     21
#define MDR_1923KX028_M0_Status3_ReqTxElectIdle_Msk     0x00200000UL
#define MDR_1923KX028_M0_Status3_ReqDetectLB_Pos        22
#define MDR_1923KX028_M0_Status3_ReqDetectLB_Msk        0x00400000UL
#define MDR_1923KX028_M0_Status3_SmlhTrain_nRst_Pos     27
#define MDR_1923KX028_M0_Status3_SmlhTrain_nRst_Msk     0x08000000UL
#define MDR_1923KX028_M0_Status3_SmlhLTSSM_PollCfg_Pos  28
#define MDR_1923KX028_M0_Status3_SmlhLTSSM_PollCfg_Msk  0x10000000UL
#define MDR_1923KX028_M0_Status3_SmlhLinkInTrain_Pos    29
#define MDR_1923KX028_M0_Status3_SmlhLinkInTrain_Msk    0x20000000UL
#define MDR_1923KX028_M0_Status3_SmlhLinkDis_Pos        30
#define MDR_1923KX028_M0_Status3_SmlhLinkDis_Msk        0x40000000UL
#define MDR_1923KX028_M0_Status3_SmlhScrambDis_Pos       31
#define MDR_1923KX028_M0_Status3_SmlhScrambDis_Msk       0x80000000UL

typedef union {
  __IOM uint32_t                 value;
  MDR_1923KX028_M0_Status3_Bits  bits;
} MDR_1923KX028_M0_Status3_t;


/* =========================================================  M0_Status 4/5  ====================================================== */
#define MDR_1923KX028_M0_Status4_t  uint32_t
#define MDR_1923KX028_M0_Status5_t  uint32_t


/* =========================================================  M0_Status 6  ====================================================== */
typedef struct {
  uint16_t numFunc  : 3;
  uint16_t numDevice: 5;
  uint16_t numBus   : 8;
} MDR_1923KX028_MsgReqID_Bits;

#define MDR_1923KX028_MsgReqID_numFunc_Pos    0
#define MDR_1923KX028_MsgReqID_numFunc_Msk    0x0007
#define MDR_1923KX028_MsgReqID_numDevice_Pos  3
#define MDR_1923KX028_MsgReqID_numDevice_Msk  0x00F8
#define MDR_1923KX028_MsgReqID_numBus_Pos     8
#define MDR_1923KX028_MsgReqID_numBus_Msk     0xFF00UL

typedef union {
  uint16_t                     value;
  MDR_1923KX028_MsgReqID_Bits  bits;
} MDR_1923KX028_MsgReqID_t;


typedef struct {
  __IOM uint32_t  RadmVendMsg         : 1;
  __IOM uint32_t  RadmMsgReqId        : 16; // MDR_1923KX028_MsgReqID_t
  __IOM uint32_t  CfgSendCorrErr      : 1;
  __IOM uint32_t  CfgSendNoFatErr     : 1;
  __IOM uint32_t  CfgSendFatErr       : 1;
  __IOM uint32_t  SmlhLinkUp          : 1;
  __IOM uint32_t  SmlhReqRSTn         : 1;  
  __IOM uint32_t  LinkReqRSTn         : 1;
  __IOM uint32_t  TrgtLookupId        : 8;  
  __IM  uint32_t                      : 1;
} MDR_1923KX028_M0_Status6_Bits;

#define MDR_1923KX028_M0_Status6_RadmVendMsg_Pos      0
#define MDR_1923KX028_M0_Status6_RadmVendMsg_Msk      0x00000001UL
#define MDR_1923KX028_M0_Status6_RadmMsgReqId_Pos     1
#define MDR_1923KX028_M0_Status6_RadmMsgReqId_Msk     0x0001FFFEUL
#define MDR_1923KX028_M0_Status6_CfgSendCorrErr_Pos   17
#define MDR_1923KX028_M0_Status6_CfgSendCorrErr_Msk   0x00020000UL
#define MDR_1923KX028_M0_Status6_CfgSendNoFatErr_Pos  18
#define MDR_1923KX028_M0_Status6_CfgSendNoFatErr_Msk  0x00040000UL
#define MDR_1923KX028_M0_Status6_CfgSendFatErr_Pos    19
#define MDR_1923KX028_M0_Status6_CfgSendFatErr_Msk    0x00080000UL
#define MDR_1923KX028_M0_Status6_SmlhLinkUp_Pos       20
#define MDR_1923KX028_M0_Status6_SmlhLinkUp_Msk       0x00100000UL
#define MDR_1923KX028_M0_Status6_SmlhReqRSTn_Pos      21
#define MDR_1923KX028_M0_Status6_SmlhReqRSTn_Msk      0x00200000UL
#define MDR_1923KX028_M0_Status6_LinkReqRSTn_Pos      22
#define MDR_1923KX028_M0_Status6_LinkReqRSTn_Msk      0x00400000UL
#define MDR_1923KX028_M0_Status6_TrgtLookupId_Pos     23
#define MDR_1923KX028_M0_Status6_TrgtLookupId_Msk     0x7F800000UL

typedef union {
  __IOM uint32_t                 value;
  MDR_1923KX028_M0_Status6_Bits  bits;
} MDR_1923KX028_M0_Status6_t;


/* =========================================================  M0_Status 7  ====================================================== */
typedef struct {
  __IOM uint32_t  TrgtTimeoutCmpl     : 1;
  __IOM uint32_t  TrgtTimeoutCmplFunc : 3;
  __IOM uint32_t  TrgtTimeoutCmplTc   : 3;
  __IOM uint32_t  TrgtTimeoutCmplAttr : 2;
  __IOM uint32_t  TrgtTimeoutCmplLen  : 12;
  __IOM uint32_t  TrgtTimeoutLookupID : 8;
  __IOM uint32_t  TrgtLookupEmpty     : 1;  
  __IM  uint32_t                      : 2;
} MDR_1923KX028_M0_Status7_Bits;

#define MDR_1923KX028_M0_Status7_TrgtTimeoutCmpl_Pos      0
#define MDR_1923KX028_M0_Status7_TrgtTimeoutCmpl_Msk      0x00000001UL
#define MDR_1923KX028_M0_Status7_TrgtTimeoutCmplFunc_Pos  1
#define MDR_1923KX028_M0_Status7_TrgtTimeoutCmplFunc_Msk  0x0000000EUL
#define MDR_1923KX028_M0_Status7_TrgtTimeoutCmplTc_Pos    4
#define MDR_1923KX028_M0_Status7_TrgtTimeoutCmplTc_Msk    0x00000070UL
#define MDR_1923KX028_M0_Status7_TrgtTimeoutCmplAttr_Pos  7
#define MDR_1923KX028_M0_Status7_TrgtTimeoutCmplAttr_Msk  0x00000180UL
#define MDR_1923KX028_M0_Status7_TrgtTimeoutCmplLen_Pos   9
#define MDR_1923KX028_M0_Status7_TrgtTimeoutCmplLen_Msk   0x001FFE00UL
#define MDR_1923KX028_M0_Status7_TrgtTimeoutLookupID_Pos  21
#define MDR_1923KX028_M0_Status7_TrgtTimeoutLookupID_Msk  0x1FE00000UL
#define MDR_1923KX028_M0_Status7_TrgtLookupEmpty_Pos      29
#define MDR_1923KX028_M0_Status7_TrgtLookupEmpty_Msk      0x20000000UL

typedef union {
  __IOM uint32_t                 value;
  MDR_1923KX028_M0_Status7_Bits  bits;
} MDR_1923KX028_M0_Status7_t;


/* =========================================================  M0_Status 8  ====================================================== */
typedef struct {
  __IOM uint32_t  RadmTimeoutCmpl     : 1;
  __IOM uint32_t  RadmTimeoutCmplFunc : 3;
  __IOM uint32_t  RadmTimeoutCmplTc   : 3;
  __IOM uint32_t  RadmTimeoutCmplAttr : 2;
  __IOM uint32_t  RadmTimeoutCmplLen  : 12;
  __IOM uint32_t  RamdTimeoutLookupTag: 8;
  __IM  uint32_t                      : 3;
} MDR_1923KX028_M0_Status8_Bits;

#define MDR_1923KX028_M0_Status7_RadmTimeoutCmpl_Pos      0
#define MDR_1923KX028_M0_Status7_RadmTimeoutCmpl_Msk      0x00000001UL
#define MDR_1923KX028_M0_Status7_RadmTimeoutCmplFunc_Pos  1
#define MDR_1923KX028_M0_Status7_RadmTimeoutCmplFunc_Msk  0x0000000EUL
#define MDR_1923KX028_M0_Status7_RadmTimeoutCmplTc_Pos    4
#define MDR_1923KX028_M0_Status7_RadmTimeoutCmplTc_Msk    0x00000030UL
#define MDR_1923KX028_M0_Status7_RadmTimeoutCmplAttr_Pos  7
#define MDR_1923KX028_M0_Status7_RadmTimeoutCmplAttr_Msk  0x00000000UL
#define MDR_1923KX028_M0_Status7_RadmTimeoutCmplLen_Pos   9
#define MDR_1923KX028_M0_Status7_RadmTimeoutCmplLen_Msk   0x00000000UL
#define MDR_1923KX028_M0_Status7_RadmTimeoutLookupID_Pos  21
#define MDR_1923KX028_M0_Status7_RadmTimeoutLookupID_Msk  0x00000000UL

typedef union {
  __IOM uint32_t                 value;
  MDR_1923KX028_M0_Status8_Bits  bits;
} MDR_1923KX028_M0_Status8_t;


/* =========================================================  M0_Status 9..28  ====================================================== */
#define MDR_1923KX028_M0_Status9_28_t uint32_t


/* =========================================================  M0_Status 29  ====================================================== */
typedef struct {
  __IOM uint32_t  CfgBusMasterEn    : 1;
  __IOM uint32_t  CfgMemSpaceEn     : 1;
  __IOM uint32_t  CfgMaxRdReqSize   : 3;
  __IOM uint32_t  CfgMaxPayloadSize : 3;
  __IOM uint32_t  CfgRCB            : 1;
  __IOM uint32_t  CfgPBusNum        : 8;
  __IOM uint32_t  CfgPBusDevNum     : 5;
  __IOM uint32_t  CfgNoSnoopEn      : 1;
  __IOM uint32_t  CfgRelaxOrderEn   : 1;  
  __IM  uint32_t                    : 8;
} MDR_1923KX028_M0_Status29_Bits;

#define MDR_1923KX028_M0_Status29_CfgBusMasterEn_Pos    0
#define MDR_1923KX028_M0_Status29_CfgBusMasterEn_Msk    0x00000001UL
#define MDR_1923KX028_M0_Status29_CfgMemSpaceEn_Pos     1
#define MDR_1923KX028_M0_Status29_CfgMemSpaceEn_Msk     0x00000002UL
#define MDR_1923KX028_M0_Status29_CfgMaxRdReqSize_Pos   2
#define MDR_1923KX028_M0_Status29_CfgMaxRdReqSize_Msk   0x0000001CUL
#define MDR_1923KX028_M0_Status29_CfgMaxPayloadSize_Pos 5
#define MDR_1923KX028_M0_Status29_CfgMaxPayloadSize_Msk 0x000000E0UL
#define MDR_1923KX028_M0_Status29_CfgRCB_Pos            8
#define MDR_1923KX028_M0_Status29_CfgRCB_Msk            0x00000100UL
#define MDR_1923KX028_M0_Status29_CfgPBusNum_Pos        9
#define MDR_1923KX028_M0_Status29_CfgPBusNum_Msk        0x0001FE00UL
#define MDR_1923KX028_M0_Status29_CfgPBusDevNum_Pos     17
#define MDR_1923KX028_M0_Status29_CfgPBusDevNum_Msk     0x003E0000UL
#define MDR_1923KX028_M0_Status29_CfgNoSnoopEn_Pos      22
#define MDR_1923KX028_M0_Status29_CfgNoSnoopEn_Msk      0x00400000UL
#define MDR_1923KX028_M0_Status29_CfgRelaxOrderEn_Pos   23
#define MDR_1923KX028_M0_Status29_CfgRelaxOrderEn_Msk   0x00800000UL

typedef union {
  __IOM uint32_t                 value;
  MDR_1923KX028_M0_Status29_Bits  bits;
} MDR_1923KX028_M0_Status29_t;


/* =========================================================  M0_Status 30  ====================================================== */
typedef enum {
  MDR_1923KX028_LTSSM_DETECT_QUIET,
  MDR_1923KX028_LTSSM_DETECT_ACT,
  MDR_1923KX028_LTSSM_POLL_ACTIVE,
  MDR_1923KX028_LTSSM_POLL_COMPLIANCE,
  MDR_1923KX028_LTSSM_POLL_CONFIG,
  MDR_1923KX028_LTSSM_PRE_DETECT_QUIET,
  MDR_1923KX028_LTSSM_DETECT_WAIT,
  MDR_1923KX028_LTSSM_CFG_LINKWD_START,
  MDR_1923KX028_LTSSM_CFG_LINKWD_ACEPT,
  MDR_1923KX028_LTSSM_CFG_LANENUM_WAI,
  MDR_1923KX028_LTSSM_CFG_LANENUM_ACEPT,
  MDR_1923KX028_LTSSM_CFG_COMPLETE,
  MDR_1923KX028_LTSSM_CFG_IDLE,
  MDR_1923KX028_LTSSM_RCVRY_LOCK,
  MDR_1923KX028_LTSSM_RCVRY_SPEED,
  MDR_1923KX028_LTSSM_RCVRY_RCVRCFG,
  MDR_1923KX028_LTSSM_RCVRY_IDLE,
  MDR_1923KX028_LTSSM_L0,
  MDR_1923KX028_LTSSM_L0S,
  MDR_1923KX028_LTSSM_L123_SEND_EIDLE,
  MDR_1923KX028_LTSSM_L1_IDLE,
  MDR_1923KX028_LTSSM_L2_IDLE,
  MDR_1923KX028_LTSSM_L2_WAKE,
  MDR_1923KX028_LTSSM_DISABLED_ENTRY,
  MDR_1923KX028_LTSSM_DISABLED_IDLE,
  MDR_1923KX028_LTSSM_DISABLED,
  MDR_1923KX028_LTSSM_LPBK_ENTRY,
  MDR_1923KX028_LTSSM_LPBK_ACTIVE,
  MDR_1923KX028_LTSSM_LPBK_EXIT,
  MDR_1923KX028_LTSSM_LPBK_EXIT_TIMEOUT,
  MDR_1923KX028_LTSSM_HOT_RESET_ENTRY,
  MDR_1923KX028_LTSSM_HOT_RESET,
  MDR_1923KX028_LTSSM_RCVRY_EQ0,
  MDR_1923KX028_LTSSM_RCVRY_EQ1,
  MDR_1923KX028_LTSSM_RCVRY_EQ2,
  MDR_1923KX028_LTSSM_RCVRY_EQ3,
} MDR_1923KX028_LTSSM_State;

typedef struct {
  __IOM uint32_t  PwrCurntState     : 3;
  __IOM uint32_t  SmlhLTSSM_State   : 6;    //  MDR_1923KX028_LTSSM_State
  __IOM uint32_t  Wake              : 1;
  __IOM uint32_t  ClkReqN           : 1;  
  __IOM uint32_t  PwrState          : 3;
  __IOM uint32_t  PwrPmeEn          : 1;
  __IOM uint32_t  PwrStateL0s       : 1;
  __IOM uint32_t  PwrStateL1        : 1;
  __IOM uint32_t  PwrStateL2        : 1;
  __IOM uint32_t  PwrExitL2         : 1;
  __IOM uint32_t  PwrStatusPME      : 1;
  __IOM uint32_t  PwrAuxEn          : 1;
  __IOM uint32_t  CfgHwAutoSpDis    : 1;
  __IOM uint32_t  CfgINT_Dis        : 1;
  __IOM uint32_t  RadmPwrOff        : 1;
  __IOM uint32_t  RadmMsgUnlock     : 1;
  __IOM uint32_t  PwrXtlhBlockTpl   : 1;
  __IM  uint32_t                    : 6;
} MDR_1923KX028_M0_Status30_Bits;

#define MDR_1923KX028_M0_Status30_PwrCurntState_Pos     0
#define MDR_1923KX028_M0_Status30_PwrCurntState_Msk     0x00000007UL
#define MDR_1923KX028_M0_Status30_SmlhLTSSM_State_Pos   3
#define MDR_1923KX028_M0_Status30_SmlhLTSSM_State_Msk   0x000001F8UL
#define MDR_1923KX028_M0_Status30_Wake_Pos              9
#define MDR_1923KX028_M0_Status30_Wake_Msk              0x00000200UL
#define MDR_1923KX028_M0_Status30_ClkReqN_Pos           10
#define MDR_1923KX028_M0_Status30_ClkReqN_Msk           0x00000400UL
#define MDR_1923KX028_M0_Status30_PwrState_Pos          11
#define MDR_1923KX028_M0_Status30_PwrState_Msk          0x00003800UL
#define MDR_1923KX028_M0_Status30_PwrPmeEn_Pos          14
#define MDR_1923KX028_M0_Status30_PwrPmeEn_Msk          0x00004000UL
#define MDR_1923KX028_M0_Status30_PwrStateL0s_Pos       15
#define MDR_1923KX028_M0_Status30_PwrStateL0s_Msk       0x00008000UL
#define MDR_1923KX028_M0_Status30_PwrStateL1_Pos        16
#define MDR_1923KX028_M0_Status30_PwrStateL1_Msk        0x00010000UL
#define MDR_1923KX028_M0_Status30_PwrStateL2_Pos        17
#define MDR_1923KX028_M0_Status30_PwrStateL2_Msk        0x00020000UL
#define MDR_1923KX028_M0_Status30_PwrExitL2_Pos         18
#define MDR_1923KX028_M0_Status30_PwrExitL2_Msk         0x00040000UL
#define MDR_1923KX028_M0_Status30_PwrStatusPME_Pos      19
#define MDR_1923KX028_M0_Status30_PwrStatusPME_Msk      0x00080000UL
#define MDR_1923KX028_M0_Status30_PwrAuxEn_Pos          20
#define MDR_1923KX028_M0_Status30_PwrAuxEn_Msk          0x00100000UL
#define MDR_1923KX028_M0_Status30_CfgHwAutoSpDis_Pos    21
#define MDR_1923KX028_M0_Status30_CfgHwAutoSpDis_Msk    0x00200000UL
#define MDR_1923KX028_M0_Status30_CfgINT_Dis_Pos        22
#define MDR_1923KX028_M0_Status30_CfgINT_Dis_Msk        0x00400000UL
#define MDR_1923KX028_M0_Status30_RadmPwrOff_Pos        23
#define MDR_1923KX028_M0_Status30_RadmPwrOff_Msk        0x00800000UL
#define MDR_1923KX028_M0_Status30_RadmMsgUnlock_Pos     24
#define MDR_1923KX028_M0_Status30_RadmMsgUnlock_Msk     0x01000000UL
#define MDR_1923KX028_M0_Status30_PwrXtlhBlockTpl_Pos   25
#define MDR_1923KX028_M0_Status30_PwrXtlhBlockTpl_Msk   0x02000000UL

typedef union {
  __IOM uint32_t                  value;
  MDR_1923KX028_M0_Status30_Bits  bits;
} MDR_1923KX028_M0_Status30_t;


/* ============================================================================================================================= */
/* =========================================================  STATUS_MODE0 / MODE2  ==================================================== */
/* ============================================================================================================================= */


/* =========================================================  M0M2_Status 31 ====================================================== */
typedef struct {
  __IOM uint32_t  RxDPllReadyPhy1     : 1;
  __IOM uint32_t  RxDPllReadyPhy5     : 1;
  __IOM uint32_t  RxDPllReadyPhy9     : 1;
  __IOM uint32_t  RxDPllReadyPhy13    : 1;
  __IOM uint32_t  RxDPllReadyPhy2     : 1;
  __IOM uint32_t  RxDPllReadyPhy6     : 1;
  __IOM uint32_t  RxDPllReadyPhy10    : 1;
  __IOM uint32_t  RxDPllReadyPhy14    : 1;
  __IOM uint32_t  RxDPllReadyPhy3     : 1;
  __IOM uint32_t  RxDPllReadyPhy7     : 1;
  __IOM uint32_t  RxDPllReadyPhy11    : 1;
  __IOM uint32_t  RxDPllReadyPhy15    : 1;  
  __IOM uint32_t  RxDPllReadyPhy4     : 1;
  __IOM uint32_t  RxDPllReadyPhy8     : 1;
  __IOM uint32_t  RxDPllReadyPhy12    : 1;
  __IOM uint32_t  RxDPllReadyPhy16    : 1;  
  __IOM uint32_t  TxCommModePhy1     : 1;
  __IOM uint32_t  TxCommModePhy5     : 1;
  __IOM uint32_t  TxCommModePhy9     : 1;
  __IOM uint32_t  TxCommModePhy13    : 1;
  __IOM uint32_t  TxCommModePhy2     : 1;
  __IOM uint32_t  TxCommModePhy6     : 1;
  __IOM uint32_t  TxCommModePhy10    : 1;
  __IOM uint32_t  TxCommModePhy14    : 1;
  __IOM uint32_t  TxCommModePhy3     : 1;
  __IOM uint32_t  TxCommModePhy7     : 1;
  __IOM uint32_t  TxCommModePhy11    : 1;
  __IOM uint32_t  TxCommModePhy15    : 1;  
  __IOM uint32_t  TxCommModePhy4     : 1;
  __IOM uint32_t  TxCommModePhy8     : 1;
  __IOM uint32_t  TxCommModePhy12    : 1;
  __IOM uint32_t  TxCommModePhy16    : 1;
} MDR_1923KX028_M0M2_Status31_Bits;

#define MDR_1923KX028_M0M2_Status31_RxDPllReadyPhy1_Msk    0x00000001UL
#define MDR_1923KX028_M0M2_Status31_RxDPllReadyPhy5_Msk    0x00000002UL
#define MDR_1923KX028_M0M2_Status31_RxDPllReadyPhy9_Msk    0x00000004UL
#define MDR_1923KX028_M0M2_Status31_RxDPllReadyPhy13_Msk   0x00000008UL
#define MDR_1923KX028_M0M2_Status31_RxDPllReadyPhy2_Msk    0x00000010UL
#define MDR_1923KX028_M0M2_Status31_RxDPllReadyPhy6_Msk    0x00000020UL
#define MDR_1923KX028_M0M2_Status31_RxDPllReadyPhy10_Msk   0x00000040UL
#define MDR_1923KX028_M0M2_Status31_RxDPllReadyPhy14_Msk   0x00000080UL
#define MDR_1923KX028_M0M2_Status31_RxDPllReadyPhy3_Msk    0x00000100UL
#define MDR_1923KX028_M0M2_Status31_RxDPllReadyPhy7_Msk    0x00000200UL
#define MDR_1923KX028_M0M2_Status31_RxDPllReadyPhy11_Msk   0x00000400UL
#define MDR_1923KX028_M0M2_Status31_RxDPllReadyPhy15_Msk   0x00000800UL
#define MDR_1923KX028_M0M2_Status31_RxDPllReadyPhy4_Msk    0x00001000UL
#define MDR_1923KX028_M0M2_Status31_RxDPllReadyPhy8_Msk    0x00002000UL
#define MDR_1923KX028_M0M2_Status31_RxDPllReadyPhy12_Msk   0x00004000UL
#define MDR_1923KX028_M0M2_Status31_RxDPllReadyPhy16_Msk   0x00008000UL
#define MDR_1923KX028_M0M2_Status31_TxCommModePhy1_Msk     0x00010000UL
#define MDR_1923KX028_M0M2_Status31_TxCommModePhy5_Msk     0x00020000UL
#define MDR_1923KX028_M0M2_Status31_TxCommModePhy9_Msk     0x00040000UL
#define MDR_1923KX028_M0M2_Status31_TxCommModePhy13_Msk    0x00080000UL
#define MDR_1923KX028_M0M2_Status31_TxCommModePhy2_Msk     0x00100000UL
#define MDR_1923KX028_M0M2_Status31_TxCommModePhy6_Msk     0x00200000UL
#define MDR_1923KX028_M0M2_Status31_TxCommModePhy10_Msk    0x00400000UL
#define MDR_1923KX028_M0M2_Status31_TxCommModePhy14_Msk    0x00800000UL
#define MDR_1923KX028_M0M2_Status31_TxCommModePhy3_Msk     0x01000000UL
#define MDR_1923KX028_M0M2_Status31_TxCommModePhy7_Msk     0x02000000UL
#define MDR_1923KX028_M0M2_Status31_TxCommModePhy11_Msk    0x04000000UL
#define MDR_1923KX028_M0M2_Status31_TxCommModePhy15_Msk    0x08000000UL
#define MDR_1923KX028_M0M2_Status31_TxCommModePhy4_Msk     0x10000000UL
#define MDR_1923KX028_M0M2_Status31_TxCommModePhy8_Msk     0x20000000UL
#define MDR_1923KX028_M0M2_Status31_TxCommModePhy12_Msk    0x40000000UL
#define MDR_1923KX028_M0M2_Status31_TxCommModePhy16_Msk    0x80000000UL

typedef union {
  __IOM uint32_t                    value;
  MDR_1923KX028_M0M2_Status31_Bits  bits;
} MDR_1923KX028_M0M2_Status31_t;


/* =========================================================  M0M2_Status 32 ====================================================== */
typedef struct {
  __IOM uint32_t  TxReadyPhy1       : 1;
  __IOM uint32_t  TxReadyPhy5       : 1;
  __IOM uint32_t  TxReadyPhy9       : 1;
  __IOM uint32_t  TxReadyPhy13      : 1;
  __IOM uint32_t  TxReadyPhy2       : 1;
  __IOM uint32_t  TxReadyPhy6       : 1;
  __IOM uint32_t  TxReadyPhy10      : 1;
  __IOM uint32_t  TxReadyPhy14      : 1;
  __IOM uint32_t  TxReadyPhy3       : 1;
  __IOM uint32_t  TxReadyPhy7       : 1;
  __IOM uint32_t  TxReadyPhy11      : 1;
  __IOM uint32_t  TxReadyPhy15      : 1;  
  __IOM uint32_t  TxReadyPhy4       : 1;
  __IOM uint32_t  TxReadyPhy8       : 1;
  __IOM uint32_t  TxReadyPhy12      : 1;
  __IOM uint32_t  TxReadyPhy16      : 1;    
  __IOM uint32_t  MPllReadyPhy1_4   : 1;
  __IOM uint32_t  MPllReadyPhy5_8   : 1;
  __IOM uint32_t  MPllReadyPhy9_12  : 1;
  __IOM uint32_t  MPllReadyPhy13_16 : 1;
  __IM  uint32_t                    : 12;
} MDR_1923KX028_M0M2_Status32_Bits;

#define MDR_1923KX028_M0M2_Status32_TxReadyPhy1_Pos         0
#define MDR_1923KX028_M0M2_Status32_TxReadyPhy1_Msk         0x00000001UL
#define MDR_1923KX028_M0M2_Status32_TxReadyPhy5_Pos         1
#define MDR_1923KX028_M0M2_Status32_TxReadyPhy5_Msk         0x00000002UL
#define MDR_1923KX028_M0M2_Status32_TxReadyPhy9_Pos         2
#define MDR_1923KX028_M0M2_Status32_TxReadyPhy9_Msk         0x00000004UL
#define MDR_1923KX028_M0M2_Status32_TxReadyPhy13_Pos        3
#define MDR_1923KX028_M0M2_Status32_TxReadyPhy13_Msk        0x00000008UL
#define MDR_1923KX028_M0M2_Status32_TxReadyPhy2_Pos         4
#define MDR_1923KX028_M0M2_Status32_TxReadyPhy2_Msk         0x00000010UL
#define MDR_1923KX028_M0M2_Status32_TxReadyPhy6_Pos         5
#define MDR_1923KX028_M0M2_Status32_TxReadyPhy6_Msk         0x00000020UL
#define MDR_1923KX028_M0M2_Status32_TxReadyPhy10_Pos        6
#define MDR_1923KX028_M0M2_Status32_TxReadyPhy10_Msk        0x00000040UL
#define MDR_1923KX028_M0M2_Status32_TxReadyPhy14_Pos        7
#define MDR_1923KX028_M0M2_Status32_TxReadyPhy14_Msk        0x00000080UL
#define MDR_1923KX028_M0M2_Status32_TxReadyPhy3_Pos         8
#define MDR_1923KX028_M0M2_Status32_TxReadyPhy3_Msk         0x00000100UL
#define MDR_1923KX028_M0M2_Status32_TxReadyPhy7_Pos         9
#define MDR_1923KX028_M0M2_Status32_TxReadyPhy7_Msk         0x00000200UL
#define MDR_1923KX028_M0M2_Status32_TxReadyPhy11_Pos        10
#define MDR_1923KX028_M0M2_Status32_TxReadyPhy11_Msk        0x00000400UL
#define MDR_1923KX028_M0M2_Status32_TxReadyPhy15_Pos        11
#define MDR_1923KX028_M0M2_Status32_TxReadyPhy15_Msk        0x00000800UL
#define MDR_1923KX028_M0M2_Status32_TxReadyPhy4_Pos         12
#define MDR_1923KX028_M0M2_Status32_TxReadyPhy4_Msk         0x00001000UL
#define MDR_1923KX028_M0M2_Status32_TxReadyPhy8_Pos         13
#define MDR_1923KX028_M0M2_Status32_TxReadyPhy8_Msk         0x00002000UL
#define MDR_1923KX028_M0M2_Status32_TxReadyPhy12_Pos        14
#define MDR_1923KX028_M0M2_Status32_TxReadyPhy12_Msk        0x00004000UL
#define MDR_1923KX028_M0M2_Status32_TxReadyPhy16_Pos        15
#define MDR_1923KX028_M0M2_Status32_TxReadyPhy16_Msk        0x00008000UL
#define MDR_1923KX028_M0M2_Status32_MPllReadyPhy1_4_Pos     16
#define MDR_1923KX028_M0M2_Status32_MPllReadyPhy1_4_Msk     0x00010000UL
#define MDR_1923KX028_M0M2_Status32_MPllReadyPhy5_8_Pos     17
#define MDR_1923KX028_M0M2_Status32_MPllReadyPhy5_8_Msk     0x00020000UL
#define MDR_1923KX028_M0M2_Status32_MPllReadyPhy9_12_Pos    18
#define MDR_1923KX028_M0M2_Status32_MPllReadyPhy9_12_Msk    0x00040000UL
#define MDR_1923KX028_M0M2_Status32_MPllReadyPhy13_16_Pos   19
#define MDR_1923KX028_M0M2_Status32_MPllReadyPhy13_16_Msk   0x00080000UL

typedef union {
  __IOM uint32_t                    value;
  MDR_1923KX028_M0M2_Status32_Bits  bits;
} MDR_1923KX028_M0M2_Status32_t;


/* =========================================================  M0M2_Status 33 ====================================================== */
typedef struct {
  __IOM uint32_t  TxDetectRxAckPhy1       : 1;
  __IOM uint32_t  TxDetectRxAckPhy5       : 1;
  __IOM uint32_t  TxDetectRxAckPhy9       : 1;
  __IOM uint32_t  TxDetectRxAckPhy13      : 1;
  __IOM uint32_t  TxDetectRxResPhy1       : 1;
  __IOM uint32_t  TxDetectRxResPhy5       : 1;
  __IOM uint32_t  TxDetectRxResPhy9       : 1;
  __IOM uint32_t  TxDetectRxResPhy13      : 1;  
  __IOM uint32_t  TxDetectRxAckPhy2       : 1;
  __IOM uint32_t  TxDetectRxAckPhy6       : 1;
  __IOM uint32_t  TxDetectRxAckPhy10      : 1;
  __IOM uint32_t  TxDetectRxAckPhy14      : 1;  
  __IOM uint32_t  TxDetectRxResPhy2       : 1;
  __IOM uint32_t  TxDetectRxResPhy6       : 1;
  __IOM uint32_t  TxDetectRxResPhy10      : 1;
  __IOM uint32_t  TxDetectRxResPhy14      : 1;   
  __IOM uint32_t  TxDetectRxAckPhy3       : 1;
  __IOM uint32_t  TxDetectRxAckPhy7       : 1;
  __IOM uint32_t  TxDetectRxAckPhy11      : 1;
  __IOM uint32_t  TxDetectRxAckPhy15      : 1;
  __IOM uint32_t  TxDetectRxResPhy3       : 1;
  __IOM uint32_t  TxDetectRxResPhy7       : 1;
  __IOM uint32_t  TxDetectRxResPhy11      : 1;
  __IOM uint32_t  TxDetectRxResPhy15      : 1;
  __IOM uint32_t  TxDetectRxAckPhy4       : 1;
  __IOM uint32_t  TxDetectRxAckPhy8       : 1;
  __IOM uint32_t  TxDetectRxAckPhy12      : 1;
  __IOM uint32_t  TxDetectRxAckPhy16      : 1;
  __IOM uint32_t  TxDetectRxResPhy4       : 1;
  __IOM uint32_t  TxDetectRxResPhy8       : 1;
  __IOM uint32_t  TxDetectRxResPhy12      : 1;
  __IOM uint32_t  TxDetectRxResPhy16      : 1;      
} MDR_1923KX028_M0M2_Status33_Bits;

#define MDR_1923KX028_M0M2_Status33_TxDetectRxAckPhy1_Msk    0x00000001UL
#define MDR_1923KX028_M0M2_Status33_TxDetectRxAckPhy5_Msk    0x00000002UL
#define MDR_1923KX028_M0M2_Status33_TxDetectRxAckPhy9_Msk    0x00000004UL
#define MDR_1923KX028_M0M2_Status33_TxDetectRxAckPhy13_Msk   0x00000008UL
#define MDR_1923KX028_M0M2_Status33_TxDetectRxResPhy1_Msk    0x00000010UL
#define MDR_1923KX028_M0M2_Status33_TxDetectRxResPhy5_Msk    0x00000020UL
#define MDR_1923KX028_M0M2_Status33_TxDetectRxResPhy9_Msk    0x00000040UL
#define MDR_1923KX028_M0M2_Status33_TxDetectRxResPhy13_Msk   0x00000080UL
#define MDR_1923KX028_M0M2_Status33_TxDetectRxAckPhy2_Msk    0x00000100UL
#define MDR_1923KX028_M0M2_Status33_TxDetectRxAckPhy6_Msk    0x00000200UL
#define MDR_1923KX028_M0M2_Status33_TxDetectRxAckPhy10_Msk   0x00000400UL
#define MDR_1923KX028_M0M2_Status33_TxDetectRxAckPhy14_Msk   0x00000800UL
#define MDR_1923KX028_M0M2_Status33_TxDetectRxResPhy2_Msk    0x00001000UL
#define MDR_1923KX028_M0M2_Status33_TxDetectRxResPhy6_Msk    0x00002000UL
#define MDR_1923KX028_M0M2_Status33_TxDetectRxResPhy10_Msk   0x00004000UL
#define MDR_1923KX028_M0M2_Status33_TxDetectRxResPhy14_Msk   0x00008000UL
#define MDR_1923KX028_M0M2_Status33_TxDetectRxAckPhy3_Msk    0x00010000UL
#define MDR_1923KX028_M0M2_Status33_TxDetectRxAckPhy7_Msk    0x00020000UL
#define MDR_1923KX028_M0M2_Status33_TxDetectRxAckPhy11Msk    0x00040000UL
#define MDR_1923KX028_M0M2_Status33_TxDetectRxAckPhy15_Msk   0x00080000UL
#define MDR_1923KX028_M0M2_Status33_TxDetectRxResPhy3_Msk    0x00100000UL
#define MDR_1923KX028_M0M2_Status33_TxDetectRxResPhy7_Msk    0x00200000UL
#define MDR_1923KX028_M0M2_Status33_TxDetectRxResPhy11_Msk   0x00400000UL
#define MDR_1923KX028_M0M2_Status33_TxDetectRxResPhy15_Msk   0x00800000UL
#define MDR_1923KX028_M0M2_Status33_TxDetectRxAckPhy4_Msk    0x01000000UL
#define MDR_1923KX028_M0M2_Status33_TxDetectRxAckPhy8_Msk    0x02000000UL
#define MDR_1923KX028_M0M2_Status33_TxDetectRxAckPhy12_Msk   0x04000000UL
#define MDR_1923KX028_M0M2_Status33_TxDetectRxAckPhy16_Msk   0x08000000UL
#define MDR_1923KX028_M0M2_Status33_TxDetectRxResPhy4_Msk    0x10000000UL
#define MDR_1923KX028_M0M2_Status33_TxDetectRxResPhy8_Msk    0x20000000UL
#define MDR_1923KX028_M0M2_Status33_TxDetectRxResPhy12_Msk   0x40000000UL
#define MDR_1923KX028_M0M2_Status33_TxDetectRxResPhy16_Msk   0x80000000UL

typedef union {
  __IOM uint32_t                    value;
  MDR_1923KX028_M0M2_Status33_Bits  bits;
} MDR_1923KX028_M0M2_Status33_t;




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


#endif  //MDR_1923KX028_DEFS_H


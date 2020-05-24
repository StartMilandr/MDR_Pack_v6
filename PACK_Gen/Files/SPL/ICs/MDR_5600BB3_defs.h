#ifndef MDR_5600BB3_DEFS_H
#define MDR_5600BB3_DEFS_H

#include <stdint.h>
#include <MDR_Types.h>

//  Маски полей в 16-ти битной приемопередаче по SPI
#define MDR_5600BB3_ADDR_POS        10
#define MDR_5600BB3_ADDR_MSK        0x3F
#define MDR_5600BB3_DATA_MSK        0xFF
#define MDR_5600BB3_WR_MSK          0x200

#define MDR_5600BB3_MAC_ADDR_HASH_Pos    3
#define MDR_5600BB3_MAC_ADDR_USER_Msk    0x7

//  Адреса регистров
typedef enum {
  MDR_5600BB3_regControl      = 0,
  MDR_5600BB3_regStatus       = 1,
  MDR_5600BB3_regFD_Mode5     = 3,
  MDR_5600BB3_regPhyModes12   = 4,
  MDR_5600BB3_regPhyModes34   = 0xB,
  
  MDR_5600BB3_regRamData1     = 0x13,
  MDR_5600BB3_regRamData2     = 0x14,
  MDR_5600BB3_regRamData3     = 0x15,
  MDR_5600BB3_regRamData4     = 0x16,
  MDR_5600BB3_regRamData5     = 0x17,
  MDR_5600BB3_regRamData6     = 0x18,
  MDR_5600BB3_regRamData7     = 0x19,
  MDR_5600BB3_regRamData8     = 0x1A,
  
  MDR_5600BB3_regRamCtrl0     = 0x1B,
  MDR_5600BB3_regRamCtrl1     = 0x1C,
  
  MDR_5600BB3_regAgeCtrl0     = 0x1D,
  MDR_5600BB3_regAgeCtrl1     = 0x1E,
  MDR_5600BB3_regAgeCtrl2     = 0x1F,
  
  MDR_5600BB3_regMacRamWrEn   = 0x20,
  
  MDR_5600BB3_regPN1_MskAnd   = 0x21,
  MDR_5600BB3_regPN2_MskAnd   = 0x22,
  MDR_5600BB3_regPN3_MskAnd   = 0x23,
  MDR_5600BB3_regPN4_MskAnd   = 0x24,
  MDR_5600BB3_regPN5_MskAnd   = 0x25,
  
  MDR_5600BB3_regPN1_MskOr    = 0x26,
  MDR_5600BB3_regPN2_MskOr    = 0x27,
  MDR_5600BB3_regPN3_MskOr    = 0x28,
  MDR_5600BB3_regPN4_MskOr    = 0x29,
  MDR_5600BB3_regPN5_MskOr    = 0x2A,  
  
  MDR_5600BB3_regIPGh         = 0x2B,
  MDR_5600BB3_regIPGl         = 0x2C,
  
  MDR_5600BB3_regMAC_CtrlTx   = 0x2D,
  MDR_5600BB3_regCollWindow   = 0x2E,
  MDR_5600BB3_regMAC_CtrlRx   = 0x2F,
  
  MDR_5600BB3_regMinFrameH    = 0x30,
  MDR_5600BB3_regMinFrameL    = 0x31,
  MDR_5600BB3_regMaxFrameH    = 0x32,
  MDR_5600BB3_regMaxFrameL    = 0x33,
} MDR_5600BB3_Reg;


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

/* =========================================================  Control  ====================================================== */
typedef struct {
  __IOM uint8_t  SW_RST      : 1;
  __IM  uint8_t              : 3;
  __IOM uint8_t  CLR_CALC_EN : 1;
  __IM  uint8_t              : 1;
  __IOM uint8_t  PORT5_DIS   : 1;
  __IOM uint8_t  HSE_BYP     : 1;
} MDR_5600BB3_Control_Bits;

#define MDR_5600BB3_Control_SW_RST_Pos       0
#define MDR_5600BB3_Control_SW_RST_Msk       1
#define MDR_5600BB3_Control_ClrCalcEn_Pos    4
#define MDR_5600BB3_Control_ClrCalcEn_Msk    0x10
#define MDR_5600BB3_Control_Port5Dis_Pos     6
#define MDR_5600BB3_Control_Port5Dis_Msk     0x40
#define MDR_5600BB3_Control_HSE_BYP_Pos      7
#define MDR_5600BB3_Control_HSE_BYP_Msk      0x80

typedef union {
  __IOM uint8_t             value;
  MDR_5600BB3_Control_Bits  bits;
} MDR_5600BB3_Control_t;


/* =========================================================  Status  ====================================================== */
typedef struct {
  __IM uint8_t               : 7;
  __IM uint8_t  HSE_RDY      : 1;
} MDR_5600BB3_Status_Bits;

#define MDR_5600BB3_Control_HSE_RDY_Pos      7
#define MDR_5600BB3_Control_HSE_RDY_Msk      0x80

typedef union {
  __IM  uint8_t            value;
  MDR_5600BB3_Status_Bits  bits;
} MDR_5600BB3_Status_t;


/* =========================================================  FD_MODE5  ====================================================== */
typedef struct {
  __IM  uint8_t               : 4;
  __IOM uint8_t  FD_Ena       : 1;
  __IM  uint8_t               : 3;
} MDR_5600BB3_FDMode5_Bits;

#define MDR_5600BB3_FDMode5_DFEna_Pos      4
#define MDR_5600BB3_FDMode5_FDEna_RDY_Msk  0x10

typedef union {
  __IOM uint8_t             value;
  MDR_5600BB3_FDMode5_Bits  bits;
} MDR_5600BB3_FDMode5_t;


/* =========================================================  PHY_MODE12  ====================================================== */
typedef struct {
  __IOM uint8_t  MODE_PHY1    : 3;
  __IOM uint8_t  RST_PHY1     : 1;
  __IOM uint8_t  MODE_PHY2    : 3;
  __IOM uint8_t  RST_PHY2     : 1;
} MDR_5600BB3_PhyMode12_Bits;

#define MDR_5600BB3_PhyMode12_Mode1_Pos   0
#define MDR_5600BB3_PhyMode12_Mode1_Msk   0x07
#define MDR_5600BB3_PhyMode12_RST1_Pos    3
#define MDR_5600BB3_PhyMode12_RST1_Msk    0x08

#define MDR_5600BB3_PhyMode12_Mode2_Pos   4
#define MDR_5600BB3_PhyMode12_Mode2_Msk   0x70
#define MDR_5600BB3_PhyMode12_RST2_Pos    8
#define MDR_5600BB3_PhyMode12_RST2_Msk    0x80

typedef union {
  __IOM uint8_t               value;
  MDR_5600BB3_PhyMode12_Bits  bits;
} MDR_5600BB3_PhyMode12_t;


/* =========================================================  PHY_MODE34  ====================================================== */
typedef struct {
  __IOM uint8_t  MODE_PHY3    : 3;
  __IOM uint8_t  RST_PHY3     : 1;
  __IOM uint8_t  MODE_PHY4    : 3;
  __IOM uint8_t  RST_PHY4     : 1;
} MDR_5600BB3_PhyMode34_Bits;

#define MDR_5600BB3_PhyMode34_Mode3_Pos   0
#define MDR_5600BB3_PhyMode34_Mode3_Msk   0x07
#define MDR_5600BB3_PhyMode34_RST3_Pos    3
#define MDR_5600BB3_PhyMode34_RST3_Msk    0x08

#define MDR_5600BB3_PhyMode34_Mode4_Pos   4
#define MDR_5600BB3_PhyMode34_Mode4_Msk   0x70
#define MDR_5600BB3_PhyMode34_RST4_Pos    8
#define MDR_5600BB3_PhyMode34_RST4_Msk    0x80

typedef union {
  __IOM uint8_t               value;
  MDR_5600BB3_PhyMode34_Bits  bits;
} MDR_5600BB3_PhyMode34_t;


/* =========================================================  RAM_DATA[8]  ====================================================== */
#define MDR_5600BB3_RamData_t  uint8_t

/* =========================================================  RAM_CONTROL_0 ====================================================== */
typedef struct {
  __IOM uint8_t  RAM_AddrHi   : 4;
  __IM  uint8_t               : 1;
  __IOM uint8_t  DATA_nMAC    : 1;
  __IOM uint8_t  SPI_WE_nRD   : 1;
  __IOM uint8_t  SPI_EN       : 1;
} MDR_5600BB3_RamCtrl0_Bits;

#define MDR_5600BB3_RamCtrl0_RAM_AddrHi_Pos   0
#define MDR_5600BB3_RamCtrl0_RAM_AddrHi_Msk   0x0F
#define MDR_5600BB3_RamCtrl0_DATA_nMAC_Pos    5
#define MDR_5600BB3_RamCtrl0_DATA_nMAC_Msk    0x20
#define MDR_5600BB3_RamCtrl0_SPI_WE_nRD_Pos   6
#define MDR_5600BB3_RamCtrl0_SPI_WE_nRD_Msk   0x40
#define MDR_5600BB3_RamCtrl0_SPI_EN_Pos       7
#define MDR_5600BB3_RamCtrl0_SPI_EN_Msk       0x80

typedef union {
  __IOM uint8_t              value;
  MDR_5600BB3_RamCtrl0_Bits  bits;
} MDR_5600BB3_RamCtrl0_t;


/* =========================================================  RAM_CONTROL_1 ====================================================== */
//  AddrLo 8-bit
#define MDR_5600BB3_RamCtrl1_t  uint8_t


/* =========================================================  Age_CONTROL_0 ====================================================== */
typedef struct {
  __IOM uint8_t  MAC_AgeLimHi : 4;
  __IM  uint8_t               : 1;
  __IOM uint8_t  MAC_ClrEn    : 1;
  __IOM uint8_t  MAC_AgeIncEn : 1;
  __IOM uint8_t  MAC_AgeDelEn : 1;
} MDR_5600BB3_AgeCtrl0_Bits;

#define MDR_5600BB3_AgeCtrl0_MAC_AgeLimHi_Pos   0
#define MDR_5600BB3_AgeCtrl0_MAC_AgeLimHi_Msk   0x0F
#define MDR_5600BB3_AgeCtrl0_MAC_ClrEn_Pos      5
#define MDR_5600BB3_AgeCtrl0_MAC_ClrEn_Msk      0x20
#define MDR_5600BB3_AgeCtrl0_MAC_AgeIncEn_Pos   6
#define MDR_5600BB3_AgeCtrl0_MAC_AgeIncEn_Msk   0x40
#define MDR_5600BB3_AgeCtrl0_MAC_AgeDelEn_Pos   7
#define MDR_5600BB3_AgeCtrl0_MAC_AgeDelEn_Msk   0x80

typedef union {
  __IOM uint8_t              value;
  MDR_5600BB3_AgeCtrl0_Bits  bits;
} MDR_5600BB3_AgeCtrl0_t;


/* =========================================================  Age_CONTROL_1 ====================================================== */
//  MAC_AgeLimLo
#define MDR_5600BB3_AgeCtrl1_t  uint8_t

/* =========================================================  Age_CONTROL_2 ====================================================== */
//  Delay_Lim
#define MDR_5600BB3_AgeCtrl2_t  uint8_t


/* =========================================================  MAC_RAM_WE ====================================================== */
typedef struct {
  __IOM uint8_t  MAC1_RAM_WE  : 1;
  __IOM uint8_t  MAC2_RAM_WE  : 1;
  __IOM uint8_t  MAC3_RAM_WE  : 1;
  __IOM uint8_t  MAC4_RAM_WE  : 1;
  __IOM uint8_t  MAC5_RAM_WE  : 1;
  __IM  uint8_t               : 3;
} MDR_5600BB3_MAC_RamWE_Bits;

#define MDR_5600BB3_RamCtrl0_MAC1_RamWE_Pos   0
#define MDR_5600BB3_RamCtrl0_MAC1_RamWE_Msk   0x01
#define MDR_5600BB3_RamCtrl0_MAC2_RamWE_Pos   1
#define MDR_5600BB3_RamCtrl0_MAC2_RamWE_Msk   0x02
#define MDR_5600BB3_RamCtrl0_MAC3_RamWE_Pos   2
#define MDR_5600BB3_RamCtrl0_MAC3_RamWE_Msk   0x04
#define MDR_5600BB3_RamCtrl0_MAC4_RamWE_Pos   3
#define MDR_5600BB3_RamCtrl0_MAC4_RamWE_Msk   0x08
#define MDR_5600BB3_RamCtrl0_MAC5_RamWE_Pos   4
#define MDR_5600BB3_RamCtrl0_MAC5_RamWE_Msk   0x01

typedef union {
  __IOM uint8_t               value;
  MDR_5600BB3_MAC_RamWE_Bits  bits;
} MDR_5600BB3_MAC_RamWE_t;


/* =========================================================  PNx_Mask_AND / OR  ====================================================== */
typedef struct {
  __IOM uint8_t  maskAND  : 5;
  __IM  uint8_t           : 3;
} MDR_5600BB3_PNx_MaskAndOr_Bits;

#define MDR_5600BB3_RamCtrl0_PNx_MaskAndOr_Pos   0
#define MDR_5600BB3_RamCtrl0_PNx_MaskAndOr_Msk   0x1F

typedef union {
  __IOM uint8_t                 value;
  MDR_5600BB3_PNx_MaskAndOr_Bits  bits;
} MDR_5600BB3_PNx_MaskAndOr_t;


/* =========================================================  IPG_h/IPG_l ====================================================== */
#define MDR_5600BB3_IPG_t         uint8_t

/* =========================================================  CollWindow ====================================================== */
#define MDR_5600BB3_CollWindow_t  uint8_t

/* =========================================================  Min/Max Frame hi/lo ====================================================== */
#define MDR_5600BB3_MinFrame_t  uint8_t
#define MDR_5600BB3_MaxFrame_t  uint8_t


/* =========================================================  MAC_TX_CTRL ====================================================== */
typedef struct {
  __IOM uint8_t  PAD_EN       : 1;
  __IM  uint8_t               : 3;
  __IOM uint8_t  TRY_lim      : 4;  
} MDR_5600BB3_CtrlTX_Bits;

#define MDR_5600BB3_CtrlTX_PAD_EN_Pos       0
#define MDR_5600BB3_CtrlTX_PAD_EN_Msk       0x01
#define MDR_5600BB3_CtrlTX_TryLim_Pos       4
#define MDR_5600BB3_CtrlTX_TryLim_Msk       0xF0
typedef union {
  __IOM uint8_t               value;
  MDR_5600BB3_CtrlTX_Bits  bits;
} MDR_5600BB3_CtrlTX_t;



/* =========================================================  MAC_RX_CTRL ====================================================== */
typedef struct {
  __IOM uint8_t  ERR_EN       : 1;
  __IM  uint8_t               : 7;
} MDR_5600BB3_CtrlRX_Bits;

#define MDR_5600BB3_CtrlRX_ErrEn_Pos      0
#define MDR_5600BB3_CtrlRX_ErrEn_Msk      0x01

typedef union {
  __IOM uint8_t            value;
  MDR_5600BB3_CtrlRX_Bits  bits;
} MDR_5600BB3_CtrlRX_t;



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



#endif  //MDR_5600BB3_DEFS_H


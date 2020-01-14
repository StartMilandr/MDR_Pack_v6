#ifndef _MDR_ETH_VE8_DEFS_H
#define _MDR_ETH_VE8_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif


#include <MDR_Types.h>
#include <MDR_ETH_defs.h>


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

/* ========================================================  G_CFGH  ========================================================= */
typedef enum {                                  /*!< MDR_ETH1_G_CFGH_RUN_Mode                                                  */
  MDR_ETH_GCFGH_RunMode_FreeRun     = 0,     /*!< FreeRun : Work mode                                                       */
  MDR_ETH_GCFGH_RunMode_Halt        = 1,     /*!< Halt : Debug Halt mode                                                    */
  MDR_ETH_GCFGH_RunMode_Stop        = 2,     /*!< Stop : Debug Stop mode                                                    */
} MDR_ETH_GCFGH_RunMode;

typedef struct {
  __IOM MDR_OnOff             XRST       : 1;            /*!< [0..0] Reset Transmitter                                                  */
  __IOM MDR_OnOff             RRST       : 1;            /*!< [1..1] Reset Receiver                                                     */
  __IOM MDR_OnOff             DLB        : 1;            /*!< [2..2] Dig Loopback                                                       */
  __IM  uint16_t                         : 9;
  __IOM MDR_OnOff             DBG_RF_EN  : 1;            /*!< [12..12] Enable Auto PTR_RX                                               */
  __IOM MDR_OnOff             DBG_TF_EN  : 1;            /*!< [13..13] Enable Auto PTR_TX                                               */
  __IOM MDR_ETH_GCFGH_RunMode RUN_Mode   : 2;            /*!< [15..14] Work mode                                                        */
} MDR_ETH_GCfgH_Bits;

#define MDR_ETH_GCFGH_XRST_Pos          (0UL)                     /*!< MDR_ETH1 G_CFGH: XRST (Bit 0)                         */
#define MDR_ETH_GCFGH_XRST_Msk          (0x1UL)                   /*!< MDR_ETH1 G_CFGH: XRST (Bitfield-Mask: 0x01)           */
#define MDR_ETH_GCFGH_RRST_Pos          (1UL)                     /*!< MDR_ETH1 G_CFGH: RRST (Bit 1)                         */
#define MDR_ETH_GCFGH_RRST_Msk          (0x2UL)                   /*!< MDR_ETH1 G_CFGH: RRST (Bitfield-Mask: 0x01)           */
#define MDR_ETH_GCFGH_DLB_Pos           (2UL)                     /*!< MDR_ETH1 G_CFGH: DLB (Bit 2)                          */
#define MDR_ETH_GCFGH_DLB_Msk           (0x4UL)                   /*!< MDR_ETH1 G_CFGH: DLB (Bitfield-Mask: 0x01)            */
#define MDR_ETH_GCFGH_DBG_RF_EN_Pos     (12UL)                    /*!< MDR_ETH1 G_CFGH: DBG_RF_EN (Bit 12)                   */
#define MDR_ETH_GCFGH_DBG_RF_EN_Msk     (0x1000UL)                /*!< MDR_ETH1 G_CFGH: DBG_RF_EN (Bitfield-Mask: 0x01)      */
#define MDR_ETH_GCFGH_DBG_TF_EN_Pos     (13UL)                    /*!< MDR_ETH1 G_CFGH: DBG_TF_EN (Bit 13)                   */
#define MDR_ETH_GCFGH_DBG_TF_EN_Msk     (0x2000UL)                /*!< MDR_ETH1 G_CFGH: DBG_TF_EN (Bitfield-Mask: 0x01)      */
#define MDR_ETH_GCFGH_RUN_Mode_Pos      (14UL)                    /*!< MDR_ETH1 G_CFGH: RUN_Mode (Bit 14)                    */
#define MDR_ETH_GCFGH_RUN_Mode_Msk      (0xc000UL)                /*!< MDR_ETH1 G_CFGH: RUN_Mode (Bitfield-Mask: 0x03)       */


/* ======================================================  PHY_CONTROL  ====================================================== */
typedef enum {                              /*!< MDR_ETH1_PHY_CONTROL_Duplex                                               */
  MDR_ETH_PHY_CTRL_Duplex_Full     = 0,     /*!< Full : Full Duplex                                                        */
  MDR_ETH_PHY_CTRL_Duplex_Half     = 1,     /*!< Half : Half Duplex                                                        */
} MDR_ETH_PHY_CTRL_Duplex;

typedef enum {                              /*!< MDR_ETH1_PHY_CONTROL_DIR                                                  */
  MDR_ETH_PHY_CTRL_DIR_Standard    = 0,     /*!< Standard : Standard bits direction                                        */
  MDR_ETH_PHY_CTRL_DIR_Inverted    = 1,     /*!< Inverted : Inverted bits direction                                        */
} MDR_ETH_PHY_CTRL_DIR;

typedef enum {                              /*!< MDR_ETH1_PHY_CONTROL_BASE_2                                               */
  MDR_ETH_PHY_CTRL_TwinPair        = 0,     /*!< TwinPair : Twin Pair cable                                                */
  MDR_ETH_PHY_CTRL_Coaxial         = 1,     /*!< Coaxial : Coaxial cable                                                   */
} MDR_ETH_PHY_CTRL_Cable;

typedef enum {                                                /*!< MDR_ETH1_PHY_CONTROL_nRST                               */
  MDR_ETH_PHY_CTRL_nRST_Reset      = 0,                       /*!< Reset : Reset State                                     */
  MDR_ETH_PHY_CTRL_nRST_Work       = 1,                       /*!< Work : Work State                                       */
} MDR_ETH_PHY_CTRL_nRST;

typedef struct {
  __IOM MDR_OnOff                 LB          : 1;            /*!< [0..0] Analog LoopBack                                   */
  __IOM MDR_OnOff                 DLB         : 1;            /*!< [1..1] Digital LoopBack                                  */
  __IOM MDR_ETH_PHY_CTRL_Duplex   Duplex      : 1;            /*!< [2..2] Digital LoopBack                                  */
  __IM  uint16_t                              : 1;
  __IOM MDR_ETH_PHY_CTRL_DIR      DIR         : 1;            /*!< [4..4] Bit Order                                         */
  __IOM MDR_ETH_PHY_CTRL_Cable    Cable       : 1;            /*!< [5..5] Cable select                                      */
  __IOM uint16_t                  LINK_Period : 6;            /*!< [11..6] Link period                                      */
  __IM  uint16_t                              : 2;
  __IOM MDR_OnOff                 ExtPHY_En   : 1;            /*!< [14..14] External PHY enable                             */
  __IOM MDR_ETH_PHY_CTRL_nRST     nRST        : 1;            /*!< [15..15] PHY Reset                                       */
} MDR_ETH_PHY_CTRL_Bits;

#define MDR_ETH_PHY_CTRL_LB_Pos          (0UL)                     /*!< MDR_ETH1 PHY_CONTROL: LB (Bit 0)                      */
#define MDR_ETH_PHY_CTRL_LB_Msk          (0x1UL)                   /*!< MDR_ETH1 PHY_CONTROL: LB (Bitfield-Mask: 0x01)        */
#define MDR_ETH_PHY_CTRL_DLB_Pos         (1UL)                     /*!< MDR_ETH1 PHY_CONTROL: DLB (Bit 1)                     */
#define MDR_ETH_PHY_CTRL_DLB_Msk         (0x2UL)                   /*!< MDR_ETH1 PHY_CONTROL: DLB (Bitfield-Mask: 0x01)       */
#define MDR_ETH_PHY_CTRL_Duplex_Pos      (2UL)                     /*!< MDR_ETH1 PHY_CONTROL: Duplex (Bit 2)                  */
#define MDR_ETH_PHY_CTRL_Duplex_Msk      (0x4UL)                   /*!< MDR_ETH1 PHY_CONTROL: Duplex (Bitfield-Mask: 0x01)    */
#define MDR_ETH_PHY_CTRL_DIR_Pos         (4UL)                     /*!< MDR_ETH1 PHY_CONTROL: DIR (Bit 4)                     */
#define MDR_ETH_PHY_CTRL_DIR_Msk         (0x10UL)                  /*!< MDR_ETH1 PHY_CONTROL: DIR (Bitfield-Mask: 0x01)       */
#define MDR_ETH_PHY_CTRL_BASE_2_Pos      (5UL)                     /*!< MDR_ETH1 PHY_CONTROL: BASE_2 (Bit 5)                  */
#define MDR_ETH_PHY_CTRL_BASE_2_Msk      (0x20UL)                  /*!< MDR_ETH1 PHY_CONTROL: BASE_2 (Bitfield-Mask: 0x01)    */
#define MDR_ETH_PHY_CTRL_LINK_Period_Pos (6UL)                     /*!< MDR_ETH1 PHY_CONTROL: LINK_Period (Bit 6)             */
#define MDR_ETH_PHY_CTRL_LINK_Period_Msk (0xfc0UL)                 /*!< MDR_ETH1 PHY_CONTROL: LINK_Period (Bitfield-Mask: 0x3f) */
#define MDR_ETH_PHY_CTRL_EXT_En_Pos      (14UL)                    /*!< MDR_ETH1 PHY_CONTROL: EXT_En (Bit 14)                 */
#define MDR_ETH_PHY_CTRL_EXT_En_Msk      (0x4000UL)                /*!< MDR_ETH1 PHY_CONTROL: EXT_En (Bitfield-Mask: 0x01)    */
#define MDR_ETH_PHY_CTRL_RST_Pos         (15UL)                    /*!< MDR_ETH1 PHY_CONTROL: RST (Bit 15)                    */
#define MDR_ETH_PHY_CTRL_RST_Msk         (0x8000UL)                /*!< MDR_ETH1 PHY_CONTROL: RST (Bitfield-Mask: 0x01)       */


/* =====================================================  PHY_STATUS  ======================================================= */
typedef struct {
  __IM  uint16_t                 : 8;
  __IOM MDR_OnOff     LED_LINK   : 1;            /*!< [8..8] Link Indicator                                                     */
  __IOM MDR_OnOff     LED_COL    : 1;            /*!< [9..9] Collision Indicator                                                */
  __IOM MDR_OnOff     INT_LOSS   : 1;            /*!< [10..10] Link Lost                                                        */
  __IOM MDR_OnOff     INT_POL    : 1;            /*!< [11..11] Link Pulse inverted                                              */
  __IOM MDR_OnOff     INT_JAB    : 1;            /*!< [12..12] Long frame received                                              */
  __IOM MDR_OnOff     INT_JAM    : 1;            /*!< [13..13] JAM signal received                                              */
} MDR_ETH_PHY_STATUS_Bits;

#define MDR_ETH_PHY_STATUS_LED_LINK_Pos  (8UL)                     /*!< MDR_ETH1 PHY_STATUS: LED_LINK (Bit 8)                 */
#define MDR_ETH_PHY_STATUS_LED_LINK_Msk  (0x100UL)                 /*!< MDR_ETH1 PHY_STATUS: LED_LINK (Bitfield-Mask: 0x01)   */
#define MDR_ETH_PHY_STATUS_LED_COL_Pos   (9UL)                     /*!< MDR_ETH1 PHY_STATUS: LED_COL (Bit 9)                  */
#define MDR_ETH_PHY_STATUS_LED_COL_Msk   (0x200UL)                 /*!< MDR_ETH1 PHY_STATUS: LED_COL (Bitfield-Mask: 0x01)    */
#define MDR_ETH_PHY_STATUS_INT_LOSS_Pos  (10UL)                    /*!< MDR_ETH1 PHY_STATUS: INT_LOSS (Bit 10)                */
#define MDR_ETH_PHY_STATUS_INT_LOSS_Msk  (0x400UL)                 /*!< MDR_ETH1 PHY_STATUS: INT_LOSS (Bitfield-Mask: 0x01)   */
#define MDR_ETH_PHY_STATUS_INT_POL_Pos   (11UL)                    /*!< MDR_ETH1 PHY_STATUS: INT_POL (Bit 11)                 */
#define MDR_ETH_PHY_STATUS_INT_POL_Msk   (0x800UL)                 /*!< MDR_ETH1 PHY_STATUS: INT_POL (Bitfield-Mask: 0x01)    */
#define MDR_ETH_PHY_STATUS_INT_JAB_Pos   (12UL)                    /*!< MDR_ETH1 PHY_STATUS: INT_JAB (Bit 12)                 */
#define MDR_ETH_PHY_STATUS_INT_JAB_Msk   (0x1000UL)                /*!< MDR_ETH1 PHY_STATUS: INT_JAB (Bitfield-Mask: 0x01)    */
#define MDR_ETH_PHY_STATUS_INT_JAM_Pos   (13UL)                    /*!< MDR_ETH1 PHY_STATUS: INT_JAM (Bit 13)                 */
#define MDR_ETH_PHY_STATUS_INT_JAM_Msk   (0x2000UL)                /*!< MDR_ETH1 PHY_STATUS: INT_JAM (Bitfield-Mask: 0x01)    */


/* ====================================================  PHY_CONTROL_A  ===================================================== */
typedef enum {                                  /*!< MDR_ETH1_PHY_CONTORL_A_SELR                                               */
  MDR_ETH_PHY_CTRLA_SELR_Internal = 0,          /*!< Internal : EXTR pin in Z-state                                            */
  MDR_ETH_PHY_CTRLA_SELR_External = 1,          /*!< External : Use external R on EXTR pin                                     */
} MDR_ETH_PHY_CTRLA_SELR;

typedef enum {                                  /*!< MDR_ETH1_PHY_CONTORL_A_TRIM                                               */
  MDR_ETH_PHY_CTRLA_TRIM_1v25 = 0,              /*!< Uref_1v25 : Internal Uref Trim                                            */
  MDR_ETH_PHY_CTRLA_TRIM_1v23 = 1,              /*!< Uref_1v23 : Internal Uref Trim                                            */
  MDR_ETH_PHY_CTRLA_TRIM_1v22 = 2,              /*!< Uref_1v22 : Internal Uref Trim                                            */
  MDR_ETH_PHY_CTRLA_TRIM_1v20 = 3,              /*!< Uref_1v20 : Internal Uref Trim                                            */
  MDR_ETH_PHY_CTRLA_TRIM_1v19 = 4,              /*!< Uref_1v19 : Internal Uref Trim                                            */
  MDR_ETH_PHY_CTRLA_TRIM_1v17 = 5,              /*!< Uref_1v17 : Internal Uref Trim                                            */
  MDR_ETH_PHY_CTRLA_TRIM_1v16 = 6,              /*!< Uref_1v16 : Internal Uref Trim                                            */
  MDR_ETH_PHY_CTRLA_TRIM_1v15 = 7,              /*!< Uref_1v15 : Internal Uref Trim                                            */
} MDR_ETH_PHY_CTRLA_TRIM;

typedef enum {                                  /*!< MDR_ETH1_PHY_CONTORL_A_ISRC                                               */
  MDR_ETH_PHY_CTRLA_ISRC_le4V   = 0,            /*!< U_le4V : for Ucc less than 4V                                             */
  MDR_ETH_PHY_CTRLA_ISRC_gt4V   = 1,            /*!< U_gt4V : for Ucc greater than 4V                                          */
} MDR_ETH_PHY_CTRLA_ISRC;


typedef struct {
  __IOM MDR_ETH_PHY_CTRLA_SELR  SELR       : 1;            /*!< [0..0] Select U_Ref source                                    */
  __IOM MDR_ETH_PHY_CTRLA_TRIM  TRIM       : 3;            /*!< [3..1] Trin internal U_Ref                                    */
  __IOM uint8_t                 TRIMR      : 8;            /*!< [11..4] Select I_Ref                                          */
  __IM  uint16_t                           : 2;
  __IOM MDR_ETH_PHY_CTRLA_ISRC  ISRC       : 1;            /*!< [14..14] I source select                                      */
  __IOM MDR_OnOff               PHY_En     : 1;            /*!< [15..15] PHY Enable                                           */
} MDR_ETH_PHY_CTRLA_Bits;

#define MDR_ETH_PHY_CTRLA_SELR_Pos       (0UL)                     /*!< MDR_ETH1 PHY_CONTORL_A: SELR (Bit 0)                  */
#define MDR_ETH_PHY_CTRLA_SELR_Msk       (0x1UL)                   /*!< MDR_ETH1 PHY_CONTORL_A: SELR (Bitfield-Mask: 0x01)    */
#define MDR_ETH_PHY_CTRLA_TRIM_Pos       (1UL)                     /*!< MDR_ETH1 PHY_CONTORL_A: TRIM (Bit 1)                  */
#define MDR_ETH_PHY_CTRLA_TRIM_Msk       (0xeUL)                   /*!< MDR_ETH1 PHY_CONTORL_A: TRIM (Bitfield-Mask: 0x07)    */
#define MDR_ETH_PHY_CTRLA_TRIMR_Pos      (4UL)                     /*!< MDR_ETH1 PHY_CONTORL_A: TRIMR (Bit 4)                 */
#define MDR_ETH_PHY_CTRLA_TRIMR_Msk      (0xff0UL)                 /*!< MDR_ETH1 PHY_CONTORL_A: TRIMR (Bitfield-Mask: 0xff)   */
#define MDR_ETH_PHY_CTRLA_ISRC_Pos       (14UL)                    /*!< MDR_ETH1 PHY_CONTORL_A: ISRC (Bit 14)                 */
#define MDR_ETH_PHY_CTRLA_ISRC_Msk       (0x4000UL)                /*!< MDR_ETH1 PHY_CONTORL_A: ISRC (Bitfield-Mask: 0x01)    */
#define MDR_ETH_PHY_CTRLA_PHY_En_Pos     (15UL)                    /*!< MDR_ETH1 PHY_CONTORL_A: PHY_En (Bit 15)               */
#define MDR_ETH_PHY_CTRLA_PHY_En_Msk     (0x8000UL)                /*!< MDR_ETH1 PHY_CONTORL_A: PHY_En (Bitfield-Mask: 0x01)  */


/**
  * @brief Ethernet Control (MDR_ETH1)
  */

typedef struct {                                          /*!< (@ 0x30000000) MDR_ETH1 Structure                                         */
  __IOM uint16_t            DELIMETER;                    /*!< (@ 0x00000000) Slit EthMem to FIFO_Rx and FIFO_Tx                         */
  __IOM uint16_t            MAC_L;                        /*!< (@ 0x00000002) MAC low bits                                               */
  __IOM uint16_t            MAC_M;                        /*!< (@ 0x00000004) MAC middle bits                                            */
  __IOM uint16_t            MAC_H;                        /*!< (@ 0x00000006) MAC high bits                                              */
  __IOM uint16_t            HASH0;                        /*!< (@ 0x00000008) HASH of MAC to filter multycast                            */
  __IOM uint16_t            HASH1;                        /*!< (@ 0x0000000A) HASH of MAC to filter multycast                            */
  __IOM uint16_t            HASH2;                        /*!< (@ 0x0000000C) HASH of MAC to filter multycast                            */
  __IOM uint16_t            HASH3;                        /*!< (@ 0x0000000E) HASH of MAC to filter multycast                            */
  __IOM uint16_t            IPG;                          /*!< (@ 0x00000010) Inter Packet Gap                                           */
  __IOM uint16_t            PSC;                          /*!< (@ 0x00000012) Prescaller of ETH_Clock to get TimeStep                    */
  __IOM uint16_t            BAG;                          /*!< (@ 0x00000014) Frame Send Period in DetermMode                            */
  __IOM uint16_t            JitterWnd;                    /*!< (@ 0x00000016) BAG's Jitter to start transfer                             */
  union { 
    __IOM uint16_t          R_CFG;                        /*!< (@ 0x00000018) RX Config Register                                         */
    MDR_ETH_RCfg_Bits       R_CFG_b;                      
  } ;                                                     
  union {                                                 
    __IOM uint16_t          X_CFG;                        /*!< (@ 0x0000001A) TX Config Register                                         */
    MDR_ETH_XCfg_Bits       X_CFG_b;                      
  } ;                                                     
  union {                                                 
    __IOM uint16_t          G_CFGL;                       /*!< (@ 0x0000001C) Global Config Register1                                    */
    MDR_ETH_GCfgL_Bits      G_CFGL_b;                     
  } ;                                                     
  union {                                                 
    __IOM uint16_t          G_CFGH;                       /*!< (@ 0x0000001E) Global Config Register2                                    */
    MDR_ETH_GCfgH_Bits      G_CFGH_b;                     
  } ;                                                     
  union {                                                 
    __IOM uint16_t          IMR;                          /*!< (@ 0x00000020) IRQ Mask Register                                          */
    MDR_ETH_EVENT_Bits      IMR_b;                        
  } ;                                                     
  union {                                                 
    __IOM uint16_t          IFR;                          /*!< (@ 0x00000022) IRQ flag register                                          */
    MDR_ETH_EVENT_Bits      IFR_b;                        
  } ;                                                     
  union {                                                 
    __IOM uint16_t          MDIO_CTRL;                    /*!< (@ 0x00000024) MDIO Control Register                                      */
    MDR_ETH_MDIO_CTRL_Bits  MDIO_CTRL_b;
  } ;
  __IOM uint16_t            MDIO_DATA;                    /*!< (@ 0x00000026) MDIO Data                                                  */
  __IOM uint16_t            R_HEAD;                       /*!< (@ 0x00000028) PTR to start of received data                              */
  __IOM uint16_t            X_TAIL;                       /*!< (@ 0x0000002A) PTR to write data                                          */
  __IM  uint16_t            R_TAIL;                       /*!< (@ 0x0000002C) PTR to end of received data                                */
  __IM  uint16_t            X_HEAD;                       /*!< (@ 0x0000002E) PTR to start of data to send                               */
  union {
    __IOM uint16_t          STAT;                         /*!< (@ 0x00000030) Status Register                                            */
    MDR_ETH_STAT_Bits       STAT_b;
  } ;
  __IM  uint16_t            RCOUNTER;                     /*!< (@ 0x00000032) Frame Received in Total                                    */  
  union {
    __IOM uint16_t          PHY_CTRL;                     /*!< (@ 0x00000034) PHY Control Register                                       */
    MDR_ETH_PHY_CTRL_Bits   PHY_CTRL_b;
  } ;
  union {
    __IOM uint16_t          PHY_STATUS;                   /*!< (@ 0x00000036) PHY Status Register                                        */
    MDR_ETH_PHY_STATUS_Bits PHY_STATUS_b;
  } ;  
  union {
    __IOM uint16_t          PHY_CTRLA;                    /*!< (@ 0x00000038) PHY Control Extra Register                                 */
    MDR_ETH_PHY_CTRLA_Bits  PHY_CTRLA_b;
  } ;
} MDR_ETH_Type;                                /*!< Size = 58 (0x3a)                                                          */

//  BuffAddr = addrOf(MDR_ETH_Type) + MDR_ETH_BUFF_OFFSET
#define MDR_ETH_TO_BUFF_OFFSET   0x00008000UL
//  BuffLen = 8KB
#define MDR_ETH_BUF_LEN          0x2000
#define MDR_ETH_BUF_DELIM_DEF    0x1000

//#define MDR_HAS_ETH_PHY          1


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


#endif  //_MDR_ETH_VE8_DEFS_H

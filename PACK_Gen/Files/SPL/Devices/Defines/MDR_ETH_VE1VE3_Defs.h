#ifndef _MDR_ETH_VE1VE3_DEFS_H
#define _MDR_ETH_VE1VE3_DEFS_H

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
typedef enum {                                                /*!< MDR_ETH1_PHY_CONTROL_nRST                               */
  MDR_ETH_PHY_CTRL_nRST_Reset      = 0,                       /*!< Reset : Reset State                                     */
  MDR_ETH_PHY_CTRL_nRST_Work       = 1,                       /*!< Work : Work State                                       */
} MDR_ETH_PHY_CTRL_nRST;                  
                  
typedef enum {                                                /*!< MDR_ETH1_PHY_CONTROL_MODE                               */
  MDR_ETH_PHY_CTRL_MODE_10BaseT_HD = 0,                       /*!< 10BaseT_HD : 10BaseT Half Duplex                        */
  MDR_ETH_PHY_CTRL_MODE_10BaseT_FD = 1,                       /*!< 10BaseT_FD : 10BaseT Full Duplex                        */
  MDR_ETH_PHY_CTRL_MODE_100BaseT_HD = 2,                      /*!< 100BaseT_HD : 100BaseT Half Duplex                      */
  MDR_ETH_PHY_CTRL_MODE_100BaseT_FD = 3,                      /*!< 100BaseT_FD : 100BaseT Full Duplex                      */
  MDR_ETH_PHY_CTRL_MODE_100BaseT_HDA = 4,                     /*!< 100BaseT_HDA : 10BaseT HD with Autonegotiation          */
  MDR_ETH_PHY_CTRL_MODE_Repeater   = 5,                       /*!< Repeater : Repeater mode                                */
  MDR_ETH_PHY_CTRL_MODE_LowPower   = 6,                       /*!< LowPower : Low Power mode                               */
  MDR_ETH_PHY_CTRL_MODE_Auto       = 7,                       /*!< Auto : 10BaseT Half Duplex                              */
} MDR_ETH_PHY_CTRL_MODE;                  
                  
typedef enum {                                                /*!< MDR_ETH1_PHY_CONTROL_MDIO_SEL                           */
  MDR_ETH_PHY_CTRL_MDIO_SEL_byMAC  = 0,                       /*!< byMAC : Controlled by MAC                               */
  MDR_ETH_PHY_CTRL_MDIO_SEL_Manual = 1,                       /*!< Manual : Manual Control                                 */
} MDR_ETH_PHY_CTRL_MDIO_SEL;


typedef struct {
  __IOM MDR_ETH_PHY_CTRL_nRST     nRST       : 1;             /*!< [0..0] PHY Reset                                         */
  __IOM MDR_ETH_PHY_CTRL_MODE     MODE       : 3;             /*!< [3..1] Config mode                                       */
  __IM  uint16_t                             : 3;
  __IOM MDR_OnOff                 FX_En      : 1;             /*!< [7..7] 100BaseFx enable                                  */
  __IOM uint16_t                  MDI        : 1;             /*!< [8..8] MII Line MDI                                      */
  __IOM MDR_ETH_PHY_CTRL_MDIO_SEL MDIO_SEL   : 1;             /*!< [9..9] MDIO select control                               */
  __IOM uint16_t MDC                         : 1;             /*!< [10..10] MII Line MDC                                    */
  __IOM uint16_t                  PHY_ADDR   : 5;             /*!< [15..11] Phy Address                                     */
} MDR_ETH_PHY_CTRL_Bits;

#define MDR_ETH_PHY_CTRL_nRST_Pos     (0UL)                     /*!< MDR_ETH1 PHY_CONTROL: nRST (Bit 0)                    */
#define MDR_ETH_PHY_CTRL_nRST_Msk     (0x1UL)                   /*!< MDR_ETH1 PHY_CONTROL: nRST (Bitfield-Mask: 0x01)      */
#define MDR_ETH_PHY_CTRL_MODE_Pos     (1UL)                     /*!< MDR_ETH1 PHY_CONTROL: MODE (Bit 1)                    */
#define MDR_ETH_PHY_CTRL_MODE_Msk     (0xeUL)                   /*!< MDR_ETH1 PHY_CONTROL: MODE (Bitfield-Mask: 0x07)      */
#define MDR_ETH_PHY_CTRL_FX_En_Pos    (7UL)                     /*!< MDR_ETH1 PHY_CONTROL: FX_En (Bit 7)                   */
#define MDR_ETH_PHY_CTRL_FX_En_Msk    (0x80UL)                  /*!< MDR_ETH1 PHY_CONTROL: FX_En (Bitfield-Mask: 0x01)     */
#define MDR_ETH_PHY_CTRL_MDI_Pos      (8UL)                     /*!< MDR_ETH1 PHY_CONTROL: MDI (Bit 8)                     */
#define MDR_ETH_PHY_CTRL_MDI_Msk      (0x100UL)                 /*!< MDR_ETH1 PHY_CONTROL: MDI (Bitfield-Mask: 0x01)       */
#define MDR_ETH_PHY_CTRL_MDIO_SEL_Pos (9UL)                     /*!< MDR_ETH1 PHY_CONTROL: MDIO_SEL (Bit 9)                */
#define MDR_ETH_PHY_CTRL_MDIO_SEL_Msk (0x200UL)                 /*!< MDR_ETH1 PHY_CONTROL: MDIO_SEL (Bitfield-Mask: 0x01)  */
#define MDR_ETH_PHY_CTRL_MDC_Pos      (10UL)                    /*!< MDR_ETH1 PHY_CONTROL: MDC (Bit 10)                    */
#define MDR_ETH_PHY_CTRL_MDC_Msk      (0x400UL)                 /*!< MDR_ETH1 PHY_CONTROL: MDC (Bitfield-Mask: 0x01)       */
#define MDR_ETH_PHY_CTRL_PHY_ADDR_Pos (11UL)                    /*!< MDR_ETH1 PHY_CONTROL: PHY_ADDR (Bit 11)               */
#define MDR_ETH_PHY_CTRL_PHY_ADDR_Msk (0xf800UL)                /*!< MDR_ETH1 PHY_CONTROL: PHY_ADDR (Bitfield-Mask: 0x1f)  */


/* ======================================================  PHY_STATUS  ======================================================= */
typedef enum {                               /*!< MDR_ETH1_PHY_STATYS_LED0                                                  */
  MDR_ETH_PHY_STAT_LED0_100MBit     = 0,     /*!< 100MBit : 100MBit Indicator                                               */
  MDR_ETH_PHY_STAT_LED0_10MBit      = 1,     /*!< 10MBit : 10MBit Indicator                                                 */
} MDR_ETH_PHY_STAT_LED0;

typedef enum {                               /*!< MDR_ETH1_PHY_STATYS_LED1                                                  */
  MDR_ETH_PHY_STAT_LED1_NoLink      = 0,     /*!< NoLink : No Link Indicator                                                */
  MDR_ETH_PHY_STAT_LED1_Link        = 1,     /*!< Link : Link Indicator                                                     */
} MDR_ETH_PHY_STAT_LED1;

typedef enum {                               /*!< MDR_ETH1_PHY_STATYS_LED2                                                  */
  MDR_ETH_PHY_STAT_LED2_NoSRC       = 0,     /*!< NoSRC : No CRS Indicator                                                  */
  MDR_ETH_PHY_STAT_LED2_CRS         = 1,     /*!< CRS : CRS Indicator                                                       */
} MDR_ETH_PHY_STAT_LED2;

typedef enum {                               /*!< MDR_ETH1_PHY_STATYS_LED3                                                  */
  MDR_ETH_PHY_STAT_LED3_FullDuplex  = 0,     /*!< FullDuplex : Full Duplex Indicator                                        */
  MDR_ETH_PHY_STAT_LED3_HalfDuplex  = 1,     /*!< HalfDuplex : Half Duplex Indicator                                        */
} MDR_ETH_PHY_STAT_LED3;


typedef struct {
  __IOM MDR_ETH_PHY_STAT_LED0   LED0      : 1;            /*!< [0..0] Bitrate Indicator                                         */
  __IOM MDR_ETH_PHY_STAT_LED1   LED1      : 1;            /*!< [1..1] Link Indicator                                            */
  __IOM MDR_ETH_PHY_STAT_LED2   LED2      : 1;            /*!< [2..2] CRS Indicator                                             */
  __IOM MDR_ETH_PHY_STAT_LED3   LED3      : 1;            /*!< [3..3] Duplex Indicator                                          */
  __IOM MDR_OnOff               READY     : 1;            /*!< [4..4] PHY Ready                                                 */
  __IOM MDR_OnOff               CRS       : 1;            /*!< [5..5] Transferring flag                                         */
  __IOM MDR_OnOff               COL1      : 1;            /*!< [6..6] Collision flag                                            */
  __IOM MDR_OnOff               COL2      : 1;            /*!< [7..7] Collision flag                                            */
  __IOM MDR_OnOff               FX_VALUE  : 1;            /*!< [8..8] Optic transferring                                        */
  __IOM uint16_t                MDO       : 1;            /*!< [9..9] MII Line MDO                                              */
  __IOM MDR_OnOff               MDINT     : 1;            /*!< [10..10] IRQ req from PHY                                        */
} MDR_ETH_PHY_STATUS_Bits;

#define MDR_ETH_PHY_STATUS_LED0_Pos      (0UL)                     /*!< MDR_ETH1 PHY_STATYS: LED0 (Bit 0)                     */
#define MDR_ETH_PHY_STATUS_LED0_Msk      (0x1UL)                   /*!< MDR_ETH1 PHY_STATYS: LED0 (Bitfield-Mask: 0x01)       */
#define MDR_ETH_PHY_STATUS_LED1_Pos      (1UL)                     /*!< MDR_ETH1 PHY_STATYS: LED1 (Bit 1)                     */
#define MDR_ETH_PHY_STATUS_LED1_Msk      (0x2UL)                   /*!< MDR_ETH1 PHY_STATYS: LED1 (Bitfield-Mask: 0x01)       */
#define MDR_ETH_PHY_STATUS_LED2_Pos      (2UL)                     /*!< MDR_ETH1 PHY_STATYS: LED2 (Bit 2)                     */
#define MDR_ETH_PHY_STATUS_LED2_Msk      (0x4UL)                   /*!< MDR_ETH1 PHY_STATYS: LED2 (Bitfield-Mask: 0x01)       */
#define MDR_ETH_PHY_STATUS_LED3_Pos      (3UL)                     /*!< MDR_ETH1 PHY_STATYS: LED3 (Bit 3)                     */
#define MDR_ETH_PHY_STATUS_LED3_Msk      (0x8UL)                   /*!< MDR_ETH1 PHY_STATYS: LED3 (Bitfield-Mask: 0x01)       */
#define MDR_ETH_PHY_STATUS_READY_Pos     (4UL)                     /*!< MDR_ETH1 PHY_STATYS: READY (Bit 4)                    */
#define MDR_ETH_PHY_STATUS_READY_Msk     (0x10UL)                  /*!< MDR_ETH1 PHY_STATYS: READY (Bitfield-Mask: 0x01)      */
#define MDR_ETH_PHY_STATUS_CRS_Pos       (5UL)                     /*!< MDR_ETH1 PHY_STATYS: CRS (Bit 5)                      */
#define MDR_ETH_PHY_STATUS_CRS_Msk       (0x20UL)                  /*!< MDR_ETH1 PHY_STATYS: CRS (Bitfield-Mask: 0x01)        */
#define MDR_ETH_PHY_STATUS_COL1_Pos      (6UL)                     /*!< MDR_ETH1 PHY_STATYS: COL1 (Bit 6)                     */
#define MDR_ETH_PHY_STATUS_COL1_Msk      (0x40UL)                  /*!< MDR_ETH1 PHY_STATYS: COL1 (Bitfield-Mask: 0x01)       */
#define MDR_ETH_PHY_STATUS_COL2_Pos      (7UL)                     /*!< MDR_ETH1 PHY_STATYS: COL2 (Bit 7)                     */
#define MDR_ETH_PHY_STATUS_COL2_Msk      (0x80UL)                  /*!< MDR_ETH1 PHY_STATYS: COL2 (Bitfield-Mask: 0x01)       */
#define MDR_ETH_PHY_STATUS_FX_VALUE_Pos  (8UL)                     /*!< MDR_ETH1 PHY_STATYS: FX_VALUE (Bit 8)                 */
#define MDR_ETH_PHY_STATUS_FX_VALUE_Msk  (0x100UL)                 /*!< MDR_ETH1 PHY_STATYS: FX_VALUE (Bitfield-Mask: 0x01)   */
#define MDR_ETH_PHY_STATUS_MDO_Pos       (9UL)                     /*!< MDR_ETH1 PHY_STATYS: MDO (Bit 9)                      */
#define MDR_ETH_PHY_STATUS_MDO_Msk       (0x200UL)                 /*!< MDR_ETH1 PHY_STATYS: MDO (Bitfield-Mask: 0x01)        */
#define MDR_ETH_PHY_STATUS_MDINT_Pos     (10UL)                    /*!< MDR_ETH1 PHY_STATYS: MDINT (Bit 10)                   */
#define MDR_ETH_PHY_STATUS_MDINT_Msk     (0x400UL)                 /*!< MDR_ETH1 PHY_STATYS: MDINT (Bitfield-Mask: 0x01)      */


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
    __IOM uint16_t          R_CFG;                       /*!< (@ 0x00000018) RX Config Register                                         */
    MDR_ETH_RCfg_Bits       R_CFG_b;
  } ; 
  union { 
    __IOM uint16_t          X_CFG;                       /*!< (@ 0x0000001A) TX Config Register                                         */
    MDR_ETH_XCfg_Bits       X_CFG_b;
  } ; 
  union { 
    __IOM uint16_t          G_CFGL;                      /*!< (@ 0x0000001C) Global Config Register1                                    */
    MDR_ETH_GCfgL_Bits      G_CFGL_b;
  } ; 
  union { 
    __IOM uint16_t          G_CFGH;                      /*!< (@ 0x0000001E) Global Config Register2                                    */
    MDR_ETH_GCfgH_Bits      G_CFGH_b;
  } ; 
  union { 
    __IOM uint16_t          IMR;                         /*!< (@ 0x00000020) IRQ Mask Register                                          */
    MDR_ETH_EVENT_Bits      IMR_b;
  } ; 
  union { 
    __IOM uint16_t          IFR;                         /*!< (@ 0x00000022) IRQ flag register                                          */
    MDR_ETH_EVENT_Bits      IFR_b;
  } ;  
  union {
    __IOM uint16_t          MDIO_CTRL;                   /*!< (@ 0x00000024) MDIO Control Register                                      */
    MDR_ETH_MDIO_CTRL_Bits  MDIO_CTRL_b;
  } ;
  __IOM uint16_t            MDIO_DATA;                    /*!< (@ 0x00000026) MDIO Data                                                  */
  __IOM uint16_t            R_HEAD;                       /*!< (@ 0x00000028) PTR to start of received data                              */
  __IOM uint16_t            X_TAIL;                       /*!< (@ 0x0000002A) PTR to write data                                          */
  __IM  uint16_t            R_TAIL;                       /*!< (@ 0x0000002C) PTR to end of received data                                */
  __IM  uint16_t            X_HEAD;                       /*!< (@ 0x0000002E) PTR to start of data to send                               */
  union {
    __IOM uint16_t          STAT;                        /*!< (@ 0x00000030) Status Register                                            */
    MDR_ETH_STAT_Bits       STAT_b;
  } ;
  __IM  uint16_t            RESERVED;  
  union {
    __IOM uint16_t          PHY_CTRL;                 /*!< (@ 0x00000034) PHY Control Register                                       */
    MDR_ETH_PHY_CTRL_Bits   PHY_CTRL_b;
  } ;
  union {
    __IOM uint16_t          PHY_STATUS;                  /*!< (@ 0x00000036) PHY Status Register                                        */
    MDR_ETH_PHY_STATUS_Bits PHY_STATUS_b;
  } ;
} MDR_ETH_Type;                                /*!< Size = 56 (0x38)                                                          */

//  BuffAddr = addrOf(MDR_ETH_Type) + MDR_ETH_BUFF_OFFSET
#define MDR_ETH_TO_BUFF_OFFSET   0x08000000UL
//  BuffLen = 8KB
#define MDR_ETH_BUF_LEN          0x2000
#define MDR_ETH_BUF_DELIM_DEF    0x1000

#define MDR_HAS_ETH_PHY          1


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


#endif  //_MDR_ETH_VE1VE3_DEFS_H

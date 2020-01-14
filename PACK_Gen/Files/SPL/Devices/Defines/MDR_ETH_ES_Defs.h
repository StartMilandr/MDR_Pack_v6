#ifndef _MDR_ETH_ES_DEFS_H
#define _MDR_ETH_ES_DEFS_H

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

typedef enum {                                  /*!< MDR_ETH1_G_CFGH_RUN_Mode                                                  */
  MDR_ETH_GCFGH_MII     = 0,     /*!< FreeRun : Work mode                                                       */
  MDR_ETH_GCFGH_RMII    = 1,     /*!< Halt : Debug Halt mode                                                    */
} MDR_ETH_GCFGH_RMII_Sel;

typedef enum {                                  /*!< MDR_ETH1_G_CFGH_RUN_Mode                                                  */
  MDR_ETH_RMII_10Mbps    = 0,     /*!< FreeRun : Work mode                                                       */
  MDR_ETH_RMII_100Mbps   = 1,     /*!< Halt : Debug Halt mode                                                    */
} MDR_ETH_RMII_Rate;

typedef struct {
  __IOM MDR_OnOff                 XRST       : 1;            /*!< [0..0] Reset Transmitter                                                  */
  __IOM MDR_OnOff                 RRST       : 1;            /*!< [1..1] Reset Receiver                                                     */
  __IOM MDR_OnOff                 DLB        : 1;            /*!< [2..2] Dig Loopback                                                       */
  __IOM MDR_ETH_GCFGH_RMII_Sel    RMII_Sel   : 1;            /*!< [3..3] */
  __IOM MDR_ETH_RMII_Rate         RMII_Rate  : 1;            /*!< [4..4] */
  __IM  uint16_t                             : 7;
  __IOM MDR_OnOff                 DBG_RF_EN  : 1;            /*!< [12..12] Enable Auto PTR_RX                                               */
  __IOM MDR_OnOff                 DBG_TF_EN  : 1;            /*!< [13..13] Enable Auto PTR_TX                                               */
  __IOM MDR_ETH_GCFGH_RunMode     RUN_Mode   : 2;            /*!< [15..14] Work mode                                                        */
} MDR_ETH_GCfgH_Bits;

#define MDR_ETH_GCFGH_XRST_Pos          (0UL)                     /*!< MDR_ETH1 G_CFGH: XRST (Bit 0)                         */
#define MDR_ETH_GCFGH_XRST_Msk          (0x1UL)                   /*!< MDR_ETH1 G_CFGH: XRST (Bitfield-Mask: 0x01)           */
#define MDR_ETH_GCFGH_RRST_Pos          (1UL)                     /*!< MDR_ETH1 G_CFGH: RRST (Bit 1)                         */
#define MDR_ETH_GCFGH_RRST_Msk          (0x2UL)                   /*!< MDR_ETH1 G_CFGH: RRST (Bitfield-Mask: 0x01)           */
#define MDR_ETH_GCFGH_DLB_Pos           (2UL)                     /*!< MDR_ETH1 G_CFGH: DLB (Bit 2)                          */
#define MDR_ETH_GCFGH_DLB_Msk           (0x4UL)                   /*!< MDR_ETH1 G_CFGH: DLB (Bitfield-Mask: 0x01)            */
#define MDR_ETH_GCFGH_RMII_Pos          (3UL)                     /*!< MDR_ETH1 G_CFGH: DLB (Bit 2)                          */
#define MDR_ETH_GCFGH_RMII_Msk          (0x8UL)                   /*!< MDR_ETH1 G_CFGH: DLB (Bitfield-Mask: 0x01)            */
#define MDR_ETH_GCFGH_RMII100_Pos       (4UL)                     /*!< MDR_ETH1 G_CFGH: DLB (Bit 2)                          */
#define MDR_ETH_GCFGH_RMII100_Msk       (0x10UL)                  /*!< MDR_ETH1 G_CFGH: DLB (Bitfield-Mask: 0x01)            */
#define MDR_ETH_GCFGH_DBG_RF_EN_Pos     (12UL)                    /*!< MDR_ETH1 G_CFGH: DBG_RF_EN (Bit 12)                   */
#define MDR_ETH_GCFGH_DBG_RF_EN_Msk     (0x1000UL)                /*!< MDR_ETH1 G_CFGH: DBG_RF_EN (Bitfield-Mask: 0x01)      */
#define MDR_ETH_GCFGH_DBG_TF_EN_Pos     (13UL)                    /*!< MDR_ETH1 G_CFGH: DBG_TF_EN (Bit 13)                   */
#define MDR_ETH_GCFGH_DBG_TF_EN_Msk     (0x2000UL)                /*!< MDR_ETH1 G_CFGH: DBG_TF_EN (Bitfield-Mask: 0x01)      */
#define MDR_ETH_GCFGH_RUN_Mode_Pos      (14UL)                    /*!< MDR_ETH1 G_CFGH: RUN_Mode (Bit 14)                    */
#define MDR_ETH_GCFGH_RUN_Mode_Msk      (0xc000UL)                /*!< MDR_ETH1 G_CFGH: RUN_Mode (Bitfield-Mask: 0x03)       */


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
  __IM  uint16_t            RCOUNTER;                     /*!< (@ 0x00000032) Frame Received in Total                                    */
} MDR_ETH_Type;                                /*!< Size = 52 (0x34)                                                          */


//  BuffAddr = addrOf(MDR_ETH_Type) + MDR_ETH_BUFF_OFFSET
#define MDR_ETH_TO_BUFF_OFFSET   0x00008000UL
//  BuffLen = 8KB
#define MDR_ETH_BUF_LEN          0x8000
#define MDR_ETH_BUF_DELIM_DEF    0x4000


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


#endif  //_MDR_ETH_ES_DEFS_H

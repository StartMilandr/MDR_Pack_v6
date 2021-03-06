#ifndef _MDR_ETH_PHY_DEFS_H
#define _MDR_ETH_PHY_DEFS_H

#ifdef __cplusplus
extern "C" {
#endif


#include <stdint.h>


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


/* ================================================  Standard Internal PHY Registers  ============================================== */
//  Register R0 - RW Base Control
#define MDR_ETH_PHY_R0                        0

#define MDR_ETH_PHY_R0_FULL_DUPLEX_Pos        8
#define MDR_ETH_PHY_R0_FULL_DUPLEX_Msk        0x0100
#define MDR_ETH_PHY_R0_RESTART_AUTONEG_Pos    9
#define MDR_ETH_PHY_R0_RESTART_AUTONEG_Msk    0x0200
#define MDR_ETH_PHY_R0_ISOL_Pos               10
#define MDR_ETH_PHY_R0_ISOL_Msk               0x0400
#define MDR_ETH_PHY_R0_PWR_DOWN_Pos           11
#define MDR_ETH_PHY_R0_PWR_DOWN_Msk           0x0800
#define MDR_ETH_PHY_R0_AUTONEG_ENA_Pos        12
#define MDR_ETH_PHY_R0_AUTONEG_ENA_Msk        0x1000
#define MDR_ETH_PHY_R0_100Mbps_Pos            13
#define MDR_ETH_PHY_R0_100Mbps_Msk            0x2000
#define MDR_ETH_PHY_R0_Loopback_Pos           14
#define MDR_ETH_PHY_R0_Loopback_Msk           0x4000
#define MDR_ETH_PHY_R0_RESET_Pos              15
#define MDR_ETH_PHY_R0_RESET_Msk              0x8000

#define MDR_ETH_PHY_R0_Reserved_Msk           0x00FF

#define MDR_ETH_PHY_R0_100FD_AUTO     (MDR_ETH_PHY_R0_FULL_DUPLEX_Msk | MDR_ETH_PHY_R0_AUTONEG_ENA_Msk | MDR_ETH_PHY_R0_100Mbps_Msk)

//  Register R1 - RO Base Status
#define MDR_ETH_PHY_R1                        1

#define MDR_ETH_PHY_R1_ExtEna_Pos             0
#define MDR_ETH_PHY_R1_ExtEna_Msk            (1 << MDR_ETH_PHY_R1_ExtEna_Pos)
#define MDR_ETH_PHY_R1_Jabber_Pos             1
#define MDR_ETH_PHY_R1_Jabber_Msk            (1 << MDR_ETH_PHY_R1_Jabber_Pos)
#define MDR_ETH_PHY_R1_Link_Pos               2
#define MDR_ETH_PHY_R1_Link_Msk              (1 << MDR_ETH_PHY_R1_Link_Pos)
#define MDR_ETH_PHY_R1_OptAutoneg_Pos         3
#define MDR_ETH_PHY_R1_OptAutoneg_Msk        (1 << MDR_ETH_PHY_R1_OptAutoneg_Pos)
#define MDR_ETH_PHY_R1_RemoteFault_Pos        4
#define MDR_ETH_PHY_R1_RemoteFault_Msk       (1 << MDR_ETH_PHY_R1_RemoteFault_Pos)
#define MDR_ETH_PHY_R1_AutonegReady_Pos       5
#define MDR_ETH_PHY_R1_AutonegReady_Msk      (1 << MDR_ETH_PHY_R1_AutonegReady_Pos)
#define MDR_ETH_PHY_R1_Opt10BaseHD_Pos        11
#define MDR_ETH_PHY_R1_Opt10BaseHD_Msk       ( 1 << MDR_ETH_PHY_R1_Opt10BaseHD_Pos)
#define MDR_ETH_PHY_R1_Opt10BaseFD_Pos        12
#define MDR_ETH_PHY_R1_Opt10BaseFD_Msk       ( 1 << MDR_ETH_PHY_R1_Opt10BaseFD_Pos)
#define MDR_ETH_PHY_R1_Opt100BaseHD_Pos       13
#define MDR_ETH_PHY_R1_Opt100BaseHD_Msk      ( 1 << MDR_ETH_PHY_R1_Opt100BaseHD_Pos)
#define MDR_ETH_PHY_R1_Opt100BaseFD_Pos       14
#define MDR_ETH_PHY_R1_Opt100BaseFD_Msk      ( 1 << MDR_ETH_PHY_R1_Opt100BaseFD_Pos)
#define MDR_ETH_PHY_R1_Opt100BaseT4_Pos       16
#define MDR_ETH_PHY_R1_Opt100BaseT4_Msk      ( 1 << MDR_ETH_PHY_R1_Opt100BaseT4_Pos)

//  Register R2,R3 - Identificator
#define MDR_ETH_PHY_R2                        2
#define MDR_ETH_PHY_R3                        3

#define MDR_ETH_PHY_R2_VALUE                  0x0FDF
#define MDR_ETH_PHY_R3_VALUE                  0x0DC0

//  Register R4 - Autonegotiation 
#define MDR_ETH_PHY_R4                        4

#define MDR_ETH_PHY_R4_10BaseHD_Ena_Pos        5
#define MDR_ETH_PHY_R4_10BaseHD_Ena_Msk        0x0020
#define MDR_ETH_PHY_R4_10BaseFD_Ena_Pos        6
#define MDR_ETH_PHY_R4_10BaseFD_Ena_Msk        0x0040
#define MDR_ETH_PHY_R4_100BaseHD_Ena_Pos       7
#define MDR_ETH_PHY_R4_100BaseHD_Ena_Msk       0x0080
#define MDR_ETH_PHY_R4_100BaseFD_Ena_Pos       8
#define MDR_ETH_PHY_R4_100BaseFD_Ena_Msk       0x0100
#define MDR_ETH_PHY_R4_100BaseT4_Ena_Pos       9
#define MDR_ETH_PHY_R4_100BaseT4_Ena_Msk       0x0200

#define MDR_ETH_PHY_R4_SEL_100Mbps      (MDR_ETH_PHY_R4_100BaseHD_Ena_Msk | MDR_ETH_PHY_R4_100BaseFD_Ena_Msk | MDR_ETH_PHY_R4_100BaseT4_Ena_Msk)


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


#endif  //_MDR_ETH_PHY_DEFS_H

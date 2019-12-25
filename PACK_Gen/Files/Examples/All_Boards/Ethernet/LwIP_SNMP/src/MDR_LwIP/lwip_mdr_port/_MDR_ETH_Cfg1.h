#ifndef __MDR_ETH_CFG1_H__
#define __MDR_ETH_CFG1_H__

#include "MDR_ETH_Defs.h"
#include "MDR_Config.h"
#include <stdint.h>


//  Settings
#define  ETHCFG1_DELIMETER                     0x1000

#define  ETHCFG1_MAC_L                         0x0012
#define  ETHCFG1_MAC_M                         0x2345
#define  ETHCFG1_MAC_H                         0x678A

#define  ETHCFG1_MAC_FLT_HASH0                 0x0000
#define  ETHCFG1_MAC_FLT_HASH1                 0x0000
#define  ETHCFG1_MAC_FLT_HASH2                 0x0000
#define  ETHCFG1_MAC_FLT_HASH3                 0x0000

//  Receiver Options
#define  ETHCFG1_RX_ACCEPT_MULTYCAST           1
#define  ETHCFG1_RX_ACCEPT_BROADCAST           1
#define  ETHCFG1_RX_ACCEPT_UNICAST             1
#define  ETHCFG1_RX_ACCEPT_WITH_ANY_MAC        1
#define  ETHCFG1_RX_ACCEPT_WITH_ERRORS         1
#define  ETHCFG1_RX_ACCEPT_CONTROL_FRAMES      1
#define  ETHCFG1_RX_ACCEPT_LONG_FRAMES         1
#define  ETHCFG1_RX_ACCEPT_SHORT_FRAMES        1
#define  ETHCFG1_RX_EVENT_MODE                 MDR_ETH_RCFG_EVENT_Saved

//  Transmitter Options
#define  ETHCFG1_TX_ADD_PAD_FOR_SHORT          1
#define  ETHCFG1_TX_TRY_SEND_COUNT             MDR_ETH_XCFG_Rtry_Off
#define  ETHCFG1_TX_EVENT_MODE                 MDR_ETH_XCFG_EVENT_FIFO_Half

//  IRQ Select
#define  ETHCFG1_IRQ_ON_RECEIVE_OK             0
#define  ETHCFG1_IRQ_ON_LOST_RX_OVER           0
#define  ETHCFG1_IRQ_ON_FIFO_RX_OVER           0
#define  ETHCFG1_IRQ_ON_RX_SOME_ERR            0
#define  ETHCFG1_IRQ_ON_RX_CRC_ERR             0
#define  ETHCFG1_IRQ_ON_RX_CONTROL             0
#define  ETHCFG1_IRQ_ON_RX_LONG                0
#define  ETHCFG1_IRQ_ON_RX_SHORT               0
#define  ETHCFG1_IRQ_ON_TX_OK                  0
#define  ETHCFG1_IRQ_ON_TX_ERR                 0
#define  ETHCFG1_IRQ_ON_TX_FIFO_EMPTY          0
#define  ETHCFG1_IRQ_ON_LATE_COLLISION         0
#define  ETHCFG1_IRQ_ON_CRC_LOST               0
#define  ETHCFG1_IRQ_ON_MDIO_REQ               0
#define  ETHCFG1_IRQ_ON_MDIO_RDY               0

//  Global Options
#define  ETHCFG1_ACCEPT_PAUSE_FRAME            0
#define  ETHCFG1_DETERM_MODE_ON                0
#define  ETHCFG1_HALF_DUPLEX_ON                0
#define  ETHCFG1_FILL_SLOTTIME_ON              0
#define  ETHCFG1_EVENT_CLR_ON_READ             0
#define  ETHCFG1_COLLISION_BIT_WIDTH           0x80


//  Debug - receive self frames
#define  ETHCFG1_LOOPBACK_ON                   0

//  Some Debug Tunes
#define  ETHCFG1_TX_IPG_ENABLE                 1
#define  ETHCFG1_TX_ADD_FRAME_CRC              1
#define  ETHCFG1_TX_PREAMBLE_ENABLE            1
#define  ETHCFG1_MDIO_PREAMBLE_ON              0
#define  ETHCFG1_IPG                           96

//  Determ mode 
#define  ETHCFG1_PSC_TO_US(clk_MHz)            (clk_MHz - 1)
#define  ETHCFG1_BAG_US                        0x63
#define  ETHCFG1_JitterWnd_US                  0x04


//  Not recomended to change (Default Values):
#define  ETHCFG1_RX_BIG_ENDIAN                 0
#define  ETHCFG1_RX_MSB_FIRST                  0

#define  ETHCFG1_TX_RESET_ON                   0
#define  ETHCFG1_RX_RESET_ON                   0
#define  ETHCFG1_RX_PTR_EN                     1
#define  ETHCFG1_TX_PTR_EN                     1
#define  ETHCFG1_RUN_MODE                      MDR_ETH_GCFGH_RunMode_FreeRun

//  PHY Settings
#define ETHCFG1_PHY_ADDR                       0x1C
#define ETHCFG1_PHY_EXTERNAL                   0
#define ETHCFG1_PHY_OPTIC_MODE                 0
#define ETHCFG1_PHY_MODE                       MDR_ETH_PHY_CTRL_MODE_Auto



//====================    Private (Options to Registers' Values)  ============
//  ----------  R_CFG Register Masks by Options  ------------
#if ETHCFG1_RX_ACCEPT_MULTYCAST
  #define  ETHCFG1_RX_MSK_MULTYCAST          MDR_ETH_RCFG_MCA_En_Msk
#else  
  #define  ETHCFG1_RX_MSK_MULTYCAST          0
#endif

#if ETHCFG1_RX_ACCEPT_BROADCAST
  #define  ETHCFG1_RX_MSK_BROADCAST          MDR_ETH_RCFG_BCA_En_Msk
#else  
  #define  ETHCFG1_RX_MSK_BROADCAST          0
#endif

#if ETHCFG1_RX_ACCEPT_UNICAST
  #define  ETHCFG1_RX_MSK_UNICAST            MDR_ETH_RCFG_UCA_En_Msk
#else  
  #define  ETHCFG1_RX_MSK_UNICAST            0
#endif

#if ETHCFG1_RX_ACCEPT_WITH_ANY_MAC
  #define  ETHCFG1_RX_MSK_WITH_ANY_MAC       MDR_ETH_RCFG_AC_En_Msk
#else  
  #define  ETHCFG1_RX_MSK_WITH_ANY_MAC       0
#endif

#if ETHCFG1_RX_ACCEPT_WITH_ERRORS
  #define  ETHCFG1_RX_MSK_WITH_ERRORS        MDR_ETH_RCFG_EF_En_Msk
#else  
  #define  ETHCFG1_RX_MSK_WITH_ERRORS        0
#endif

#if ETHCFG1_RX_ACCEPT_CONTROL_FRAMES
  #define  ETHCFG1_RX_MSK_CONTROL_FRAMES     MDR_ETH_RCFG_CF_En_Msk
#else  
  #define  ETHCFG1_RX_MSK_CONTROL_FRAMES     0
#endif

#if ETHCFG1_RX_ACCEPT_LONG_FRAMES
  #define  ETHCFG1_RX_MSK_LONG_FRAMES        MDR_ETH_RCFG_LF_En_Msk
#else  
  #define  ETHCFG1_RX_MSK_LONG_FRAMES        0
#endif

#if ETHCFG1_RX_ACCEPT_SHORT_FRAMES
  #define  ETHCFG1_RX_MSK_SHORT_FRAMES       MDR_ETH_RCFG_SF_En_Msk
#else  
  #define  ETHCFG1_RX_MSK_SHORT_FRAMES       0
#endif

#if ETHCFG1_RX1_BIG_ENDIAN
  #define  ETHCFG1_RX_MSK_ENDIAN             MDR_ETH_RCFG_MSB_1st_Msk
#else  
  #define  ETHCFG1_RX_MSK_ENDIAN             0
#endif

#if ETHCFG1_RX1_MSB_FIRST
  #define  ETHCFG1_RX_MSK_MSB                MDR_ETH_RCFG_BE_Msk
#else  
  #define  ETHCFG1_RX_MSK_MSB                0
#endif

#define ETHCFG1_REG_RCFG     ETHCFG1_RX_MSK_MULTYCAST       \
                          |  ETHCFG1_RX_MSK_BROADCAST       \
                          |  ETHCFG1_RX_MSK_UNICAST         \
                          |  ETHCFG1_RX_MSK_WITH_ANY_MAC    \
                          |  ETHCFG1_RX_MSK_WITH_ERRORS     \
                          |  ETHCFG1_RX_MSK_CONTROL_FRAMES  \
                          |  ETHCFG1_RX_MSK_LONG_FRAMES     \
                          |  ETHCFG1_RX_MSK_SHORT_FRAMES    \
                          |  ETHCFG1_RX_MSK_ENDIAN          \
                          |  ETHCFG1_RX_MSB_FIRST           \
                          |((ETHCFG1_RX_EVENT_MODE << MDR_ETH_RCFG_EVNT_MODE_Pos) & MDR_ETH_RCFG_EVNT_MODE_Msk)


//  ----------  X_CFG Register Masks by Options  ------------
#if ETHCFG1_TX_ADD_PAD_FOR_SHORT
  #define ETHCFG1_TX_MSK_PAD                 MDR_ETH_XCFG_PAD_En_Msk
#else
  #define ETHCFG1_TX_MSK_PAD                 0
#endif

#if ETHCFG1_TX_IPG_ENABLE
  #define ETHCFG1_TX_MSK_IPG                 MDR_ETH_XCFG_IPG_En_Msk
#else
  #define ETHCFG1_TX_MSK_IPG                 0
#endif

#if ETHCFG1_TX_ADD_FRAME_CRC
  #define ETHCFG1_TX_MSK_CRC                 MDR_ETH_XCFG_CRC_En_Msk
#else
  #define ETHCFG1_TX_MSK_CRC                 0
#endif

#if ETHCFG1_TX_PREAMBLE_ENABLE
  #define ETHCFG1_TX_MSK_PREAMBLE            MDR_ETH_XCFG_PRE_En_Msk
#else
  #define ETHCFG1_TX_MSK_PREAMBLE            0
#endif

#if ETHCFG1_TX_BIG_ENDIAN
  #define  ETHCFG1_TX_MSK_ENDIAN             MDR_ETH_X_CFG_MSB_1st_Msk
#else  
  #define  ETHCFG1_TX_MSK_ENDIAN             0
#endif

#if ETHCFG1_TX_MSB_FIRST
  #define  ETHCFG1_TX_MSK_MSB                MDR_ETH_X_CFG_BE_Msk
#else  
  #define  ETHCFG1_TX_MSK_MSB                0
#endif


#define ETHCFG1_REG_XCFG        ETHCFG1_TX_MSK_PAD         \
                            |   ETHCFG1_TX_MSK_IPG         \
                            |   ETHCFG1_TX_MSK_CRC         \
                            |   ETHCFG1_TX_MSK_PREAMBLE    \
                            |   ETHCFG1_TX_MSK_ENDIAN      \
                            |   ETHCFG1_TX_MSK_MSB         \
                            | ((ETHCFG1_TX_EVENT_MODE << MDR_ETH_XCFG_EVNT_MODE_Pos) & MDR_ETH_XCFG_EVNT_MODE_Msk)
                          

//  ----------  G_CFGL Register Masks by Options  ------------
#if ETHCFG1_ACCEPT_PAUSE_FRAME
  #define  ETHCFG1_GCFGL_PAUSE        MDR_ETH_GCFGL_Pause_En_Msk
#else  
  #define  ETHCFG1_GCFGL_PAUSE        0
#endif

#if ETHCFG1_DETERM_MODE_ON
  #define  ETHCFG1_GCFGL_DETERM       MDR_ETH_GCFGL_DTRM_En_Msk
#else  
  #define  ETHCFG1_GCFGL_DETERM       0
#endif

#if ETHCFG1_HALF_DUPLEX_ON
  #define  ETHCFG1_GCFGL_HALFDUP      MDR_ETH_GCFGL_HD_En_Msk
#else  
  #define  ETHCFG1_GCFGL_HALFDUP      0
#endif

#if ETHCFG1_FILL_SLOTTIME_ON
  #define  ETHCFG1_GCFGL_SLOTTIME     MDR_ETH_GCFGL_EXT_En_Msk
#else  
  #define  ETHCFG1_GCFGL_SLOTTIME     0
#endif

#if ETHCFG1_EVENT_CLR_ON_READ
  #define  ETHCFG1_GCFGL_IFR_CLR      MDR_ETH_GCFGL_IFR_CLR_En_Msk
#else  
  #define  ETHCFG1_GCFGL_IFR_CLR      0
#endif

#define ETHCFG1_REG_GCFGL(bufMode)      ETHCFG1_GCFGL_PAUSE     \
                                     |  ETHCFG1_GCFGL_DETERM    \
                                     |  ETHCFG1_GCFGL_HALFDUP   \
                                     |  ETHCFG1_GCFGL_SLOTTIME  \
                                     |  ETHCFG1_GCFGL_IFR_CLR   \
                                     | (ETHCFG1_COLLISION_BIT_WIDTH & MDR_ETH_GCFGL_ColWnd_Msk) \
                                     | ((bufMode << MDR_ETH_GCFGL_BUFF_Mode_Pos) & MDR_ETH_GCFGL_BUFF_Mode_Msk)


//  ----------  G_CFGH Register Masks by Options  ------------
#if ETHCFG1_TX_RESET_ON
  #define  ETHCFG1_GCFGH_XRST         MDR_ETH_GCFGH_XRST_Msk
#else  
  #define  ETHCFG1_GCFGH_XRST         0
#endif

#if ETHCFG1_RX_RESET_ON
  #define  ETHCFG1_GCFGH_RRST         MDR_ETH_GCFGH_RRST_Msk
#else  
  #define  ETHCFG1_GCFGH_RRST         0
#endif

#if ETHCFG1_LOOPBACK_ON
  #define  ETHCFG1_GCFGH_LB           MDR_ETH_GCFGH_DLB_Msk
#else  
  #define  ETHCFG1_GCFGH_LB           0
#endif

#if ETHCFG1_RX_PTR_EN
  #define  ETHCFG1_GCFGH_PTR_R_EN     MDR_ETH_GCFGH_DBG_RF_EN_Msk
#else  
  #define  ETHCFG1_GCFGH_PTR_R_EN     0
#endif

#if ETHCFG1_TX_PTR_EN
  #define  ETHCFG1_GCFGH_PTR_X_EN     MDR_ETH_GCFGH_DBG_TF_EN_Msk
#else  
  #define  ETHCFG1_GCFGH_PTR_X_EN     0
#endif

#define ETHCFG1_REG_GCFGH     ETHCFG1_GCFGH_XRST      \
                           |  ETHCFG1_GCFGH_RRST      \
                           |  ETHCFG1_GCFGH_LB        \
                           |  ETHCFG1_GCFGH_PTR_R_EN  \
                           |  ETHCFG1_GCFGH_PTR_X_EN  \
                           |((ETHCFG1_RUN_MODE << MDR_ETH_GCFGH_RUN_Mode_Pos) & MDR_ETH_GCFGH_RUN_Mode_Msk)


//  ----------  MDIO_CTRL Register Masks by Options  ------------
#if ETHCFG1_MDIO_PREAMBLE_ON
  #define  ETHCFG1_MDIO_PREAMBLE     MDR_ETH_MDIO_CTRL_PRE_En_Msk
#else  
  #define  ETHCFG1_MDIO_PREAMBLE     0
#endif

#define ETHCFG1_REG_MDIO_CTRL(clkDiv)    ETHCFG1_MDIO_PREAMBLE                                                                  \
                                     | ((ETHCFG1_PHY_ADDR) << MDR_ETH_MDIO_CTRL_PHY_Addr_Pos) & MDR_ETH_MDIO_CTRL_PHY_Addr_Msk  \
                                     | ((clkDiv)  << MDR_ETH_MDIO_CTRL_DIV_Pos)               & MDR_ETH_MDIO_CTRL_DIV_Msk       \


//  ----------  IRQ (IMR) Register Masks by Options  ------------
#if ETHCFG1_IRQ_ON_RECEIVE_OK
  #define  ETHCFG1_IQR_RXOK       MDR_ETH_EVENT_RF_OK_Msk
#else  
  #define  ETHCFG1_IQR_RXOK       0
#endif

#if ETHCFG1_IRQ_ON_LOST_RX_OVER
  #define  ETHCFG1_IQR_MISS       MDR_ETH_EVENT_MISSED_F_Msk
#else  
  #define  ETHCFG1_IQR_MISS       0
#endif

#if ETHCFG1_IRQ_ON_FIFO_RX_OVER
  #define  ETHCFG1_IRQ_RX_OVF     MDR_ETH_EVENT_OVF_Msk
#else  
  #define  ETHCFG1_IRQ_RX_OVF     0
#endif

#if ETHCFG1_IRQ_ON_RX_SOME_ERR
  #define  ETHCFG1_IRQ_RX_SMBERR  MDR_ETH_EVENT_SMB_Err_Msk
#else  
  #define  ETHCFG1_IRQ_RX_SMBERR  0
#endif

#if ETHCFG1_IRQ_ON_RX_CRC_ERR
  #define  ETHCFG1_IRQ_CRCERR     MDR_ETH_EVENT_CRC_Err_Msk
#else  
  #define  ETHCFG1_IRQ_CRCERR     0
#endif
#if ETHCFG1_IRQ_ON_RX_CONTROL
  #define  ETHCFG1_IRQ_CONTROL    MDR_ETH_EVENT_CF_Msk
#else  
  #define  ETHCFG1_IRQ_CONTROL    0
#endif
#if ETHCFG1_IRQ_ON_RX_LONG
  #define  ETHCFG1_IRQ_RXLONG     MDR_ETH_EVENT_LF_Msk
#else  
  #define  ETHCFG1_IRQ_RXLONG     0
#endif
#if ETHCFG1_IRQ_ON_RX_SHORT
  #define  ETHCFG1_IRQ_RXSHORT    MDR_ETH_EVENT_SF_Msk
#else  
  #define  ETHCFG1_IRQ_RXSHORT    0
#endif
#if ETHCFG1_IRQ_ON_TX_OK
  #define  ETHCFG1_IRQ_TXOK       MDR_ETH_EVENT_XF_Ok_Msk
#else  
  #define  ETHCFG1_IRQ_TXOK       0
#endif
#if ETHCFG1_IRQ_ON_TX_ERR
  #define  ETHCFG1_IRQ_TXERR      MDR_ETH_EVENT_XF_Err_Msk
#else  
  #define  ETHCFG1_IRQ_TXERR      0
#endif
#if ETHCFG1_IRQ_ON_TX_FIFO_EMPTY
  #define  ETHCFG1_IRQ_TXEMPTY    MDR_ETH_EVENT_UNDEF_Msk
#else  
  #define  ETHCFG1_IRQ_TXEMPTY    0
#endif
#if ETHCFG1_IRQ_ON_LATE_COLLISION
  #define  ETHCFG1_IRQ_LATECOL    MDR_ETH_EVENT_LC_Msk
#else  
  #define  ETHCFG1_IRQ_LATECOL    0
#endif
#if ETHCFG1_IRQ_ON_CRS_LOST
  #define  ETHCFG1_IRQ_CRSLOST    MDR_ETH_EVENT_CRS_Lost_Msk
#else  
  #define  ETHCFG1_IRQ_CRSLOST     0
#endif
#if ETHCFG1_IRQ_ON_MDIO_REQ
  #define  ETHCFG1_IRQ_MDIOREQ     MDR_ETH_EVENT_MDIO_INT_Msk
#else  
  #define  ETHCFG1_IRQ_MDIOREQ     0
#endif
#if ETHCFG1_IRQ_ON_MDIO_RDY
  #define  ETHCFG1_IRQ_MDIORDY     MDR_ETH_EVENT_MDIO_RDY_Msk
#else  
  #define  ETHCFG1_IRQ_MDIORDY     0
#endif


#define ETHCFG1_REG_IMR    ETHCFG1_IQR_RXOK      \
                         | ETHCFG1_IQR_MISS      \
                         | ETHCFG1_IRQ_RX_OVF    \
                         | ETHCFG1_IRQ_RX_SMBERR \
                         | ETHCFG1_IRQ_CRCERR    \
                         | ETHCFG1_IRQ_CONTROL   \
                         | ETHCFG1_IRQ_RXLONG    \
                         | ETHCFG1_IRQ_RXSHORT   \
                         | ETHCFG1_IRQ_TXOK      \
                         | ETHCFG1_IRQ_TXERR     \
                         | ETHCFG1_IRQ_TXEMPTY   \
                         | ETHCFG1_IRQ_LATECOL   \
                         | ETHCFG1_IRQ_CRSLOST   \
                         | ETHCFG1_IRQ_MDIOREQ   \
                         | ETHCFG1_IRQ_MDIORDY
                          

//  ----------  PHY Settings  ------------
#if ETHCFG1_PHY_OPTIC_MODE
  #define  ETHCFG1_PHY_MSK_OPTIC            MDR_ETH_PHY_CTRL_FX_En_Msk
#else  
  #define  ETHCFG1_PHY_MSK_OPTIC            0
#endif

#define MDR_REG_PHY_CTRL            ((ETHCFG1_PHY_ADDR << MDR_ETH_PHY_CTRL_PHY_ADDR_Pos) & MDR_ETH_PHY_CTRL_PHY_ADDR_Msk)  \
                                  | ((ETHCFG1_PHY_MODE << MDR_ETH_PHY_CTRL_MODE_Pos)     & MDR_ETH_PHY_CTRL_MODE_Msk)  \
                                  |  ETHCFG1_PHY_MSK_OPTIC                


//==========================    Init Macros =======================
#define MDR_ETH_MAC_INIT(freqMHz, mdioClkDiv, buffMode)  {            \
                        .DELIMETER = ETHCFG1_DELIMETER,               \
                        .MAC_L  = ETHCFG1_MAC_L,                      \
                        .MAC_M  = ETHCFG1_MAC_M,                      \
                        .MAC_H  = ETHCFG1_MAC_H,                      \
                        .HASH0  = ETHCFG1_MAC_FLT_HASH0,              \
                        .HASH1  = ETHCFG1_MAC_FLT_HASH1,              \
                        .HASH2  = ETHCFG1_MAC_FLT_HASH2,              \
                        .HASH3  = ETHCFG1_MAC_FLT_HASH3,              \
                        .IPG    = ETHCFG1_IPG,                        \
                        .PSC    = ETHCFG1_PSC_TO_US(freqMHz),         \
                        .BAG    = ETHCFG1_BAG_US,                     \
                        .JitterWnd = ETHCFG1_JitterWnd_US,            \
                        .R_CFG  = ETHCFG1_REG_RCFG,                   \
                        .X_CFG  = ETHCFG1_REG_XCFG,                   \
                        .G_CFGL = ETHCFG1_REG_GCFGL(buffMode),        \
                        .G_CFGH = ETHCFG1_REG_GCFGH,                  \
                        .IMR    = ETHCFG1_REG_IMR,                    \
                        .MDIO_CTRL = ETHCFG1_REG_MDIO_CTRL(mdioClkDiv)  \
                      }

#if MDR_ETH_BUFF_LIN
  #define MDR_ETH_MAC_INIT_DEF(freqMHz, mdioClkDiv)    MDR_ETH_MAC_INIT(freqMHz, mdioClkDiv, MDR_ETH_BuffMode_Linear)
#elif MDR_ETH_BUFF_AUTO_PTR
  #define MDR_ETH_MAC_INIT_DEF(freqMHz, mdioClkDiv)    MDR_ETH_MAC_INIT(freqMHz, mdioClkDiv, MDR_ETH_BuffMode_AutoPTR)
#elif MDR_ETH_BUFF_FIFO
  #define MDR_ETH_MAC_INIT_DEF(freqMHz, mdioClkDiv)    MDR_ETH_MAC_INIT(freqMHz, mdioClkDiv, MDR_ETH_BuffMode_FIFO)
#else  
  Select Ethernet Buffer mode in MDR_Config.h!
#endif
                      


#endif // __MDR_ETH_CFG1_H__

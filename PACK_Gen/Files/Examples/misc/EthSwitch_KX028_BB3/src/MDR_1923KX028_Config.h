#ifndef  MDR_1923KX028_CONFIG_H_
#define  MDR_1923KX028_CONFIG_H_

#include <stdint.h>

//  Прототип функция задержки, (передается в функции работы с базисом, для реализации задержки).
//  В случае RTOS можно использовать Sleep
typedef void (*MDR_KX028_DelayMs)(uint32_t);

//  Задержки, используемые внутри функций базиса, подставляются в функцию типа MDR_KX028_DelayMs
#define MDR_KX028_RESET_DLEAY_MS    100

//  Redefine Functions
//#define MDR_KX028_DelayMs(x)
#define MDR_KX028_CRITSECT_ENTER
#define MDR_KX028_CRITSECT_LEAVE


//  Port Init Settings
#define KX028_PORTS_FALLBACK_ID   AXI_CLASS_STRUC1_PORT_FALLBACK_BDID_DEF
#define KX028_PORTS_TAG_ID        0x8100

#define KX028_PORTS_SHUTDOWN           0                              //     0x00000001
#define KX028_PORTS_AFT                KX028_PortAcc_AnyTagging       //     0x000000F0
#define KX028_PORTS_BLOCKSTATE         KX028_PortBlkState_Forwarding  //     0x00000F00
#define KX028_PORTS_DEF_CFI            0                         //     0x00001000
#define KX028_PORTS_DEF_PRI            0                         //     0x0000E000
#define KX028_PORTS_DEF_TC             0                         //     0x00070000
#define KX028_PORTS_TRUSTED            0                         //     0x00080000
#define KX028_PORTS_VID_PREFIX         0                         //     0x00100000
#define KX028_PORTS_UNTAG_FROM_BTABLE  0                         //     0x00200000


#define MDR_KX028_DEBUG     1

#define KX028_SOFT_RESET_DELAY_MS     1000


// =================  BMU Configs  ===============
// Program for Maximum buffer count as 2048 (i.e. 256K memory accommodating, 2048 buffers of size 128 bytes) - 0x800
#define CFG_BMU_UCAST_BUF_CNT           AXI_BMU_UCAST_BUF_CNT_MAX
// Buffers count for slave SPI
#define CFG_BMU1_SPI_READ_BUFF_COUNT    1
// Buffer size bits or number of bit representing the LMEM buffer size (7 = 128bytes).
#define CFG_BMU_BUF_SIZE_128            AXI_BMU_BUF_SIZE_128
//  Threshold number of LMEM buffers occupied to generate interrupt - 0x800
#define CFG_BMU_THRES_UCAST             CFG_BMU_UCAST_BUF_CNT


// =================  EMAC Configs  ===============
//  --------    Full Duplex   ---------
//  GMII Full Duplex 1Gbps - 0x0123040A
#define CFG_EMAC_NETCFG_GMII_FD_1G        AXI_EMAC_NETCFG_FD_Msk \
                                        | AXI_EMAC_NETCFG_JFRAME_Msk \
                                        | AXI_EMAC_NETCFG_CLK_1GBps_Msk \
                                        | AXI_EMAC_NETCFG_RLCE_Msk \
                                        | AXI_EMAC_NETCFG_DRFCS_Msk \
                                        | AXI_EMAC_NETCFG_FIFO_W64_Mks \
                                        | AXI_EMAC_NETCFG_RX_FCS_Mks
                                            
//  MII Full Duplex 100M - 0x01230003
#define CFG_EMAC_NETCFG_MII_FD_100M       AXI_EMAC_NETCFG_SPD_Msk \
                                        | AXI_EMAC_NETCFG_FD_Msk \
                                        | AXI_EMAC_NETCFG_RLCE_Msk \
                                        | AXI_EMAC_NETCFG_DRFCS_Msk \
                                        | AXI_EMAC_NETCFG_FIFO_W64_Mks \
                                        | AXI_EMAC_NETCFG_RX_FCS_Mks

//  MII Full Duplex 10M - 0x01230002
#define CFG_EMAC_NETCFG_MII_FD_10M        AXI_EMAC_NETCFG_FD_Msk \
                                        | AXI_EMAC_NETCFG_RLCE_Msk \
                                        | AXI_EMAC_NETCFG_DRFCS_Msk \
                                        | AXI_EMAC_NETCFG_FIFO_W64_Mks \
                                        | AXI_EMAC_NETCFG_RX_FCS_Mks

//  --------    Half Duplex   ---------
//  MII Half Duplex 100M - 0x01231009
#define CFG_EMAC_NETCFG_MII_HD_100M       AXI_EMAC_NETCFG_SPD_Msk \
                                        | AXI_EMAC_NETCFG_JFRAME_Msk \
                                        | AXI_EMAC_NETCFG_RTY_Pos  \
                                        | AXI_EMAC_NETCFG_RLCE_Msk \
                                        | AXI_EMAC_NETCFG_DRFCS_Msk \
                                        | AXI_EMAC_NETCFG_FIFO_W64_Mks \
                                        | AXI_EMAC_NETCFG_RX_FCS_Mks

//  MII Half Duplex 10M - 0x01231008
#define CFG_EMAC_NETCFG_MII_HD_10M        AXI_EMAC_NETCFG_JFRAME_Msk \
                                        | AXI_EMAC_NETCFG_RTY_Pos  \
                                        | AXI_EMAC_NETCFG_RLCE_Msk \
                                        | AXI_EMAC_NETCFG_DRFCS_Msk \
                                        | AXI_EMAC_NETCFG_FIFO_W64_Mks \
                                        | AXI_EMAC_NETCFG_RX_FCS_Mks

//  --------    SGMII MODE (Serial GMII)   ---------
//  SGMII Full Duplex 1Gbps - 0x09230C0A
#define CFG_EMAC_NETCFG_SGMII_FD_1G       AXI_EMAC_NETCFG_FD_Msk \
                                        | AXI_EMAC_NETCFG_JFRAME_Msk \
                                        | AXI_EMAC_NETCFG_CLK_1GBps_Msk \
                                        | AXI_EMAC_NETCFG_CLK_SGMII_Msk \
                                        | AXI_EMAC_NETCFG_RLCE_Msk \
                                        | AXI_EMAC_NETCFG_DRFCS_Msk \
                                        | AXI_EMAC_NETCFG_FIFO_W64_Mks \
                                        | AXI_EMAC_NETCFG_RX_FCS_Mks  \
                                        | AXI_EMAC_NETCFG_SGMII_Mks
                                            
//  SGMII Full Duplex 100M - 0x0923080B
#define CFG_EMAC_NETCFG_SGMII_FD_100M     AXI_EMAC_NETCFG_SPD_Msk \
                                        | AXI_EMAC_NETCFG_FD_Msk \
                                        | AXI_EMAC_NETCFG_JFRAME_Msk \
                                        | AXI_EMAC_NETCFG_CLK_SGMII_Msk \
                                        | AXI_EMAC_NETCFG_RLCE_Msk \
                                        | AXI_EMAC_NETCFG_DRFCS_Msk \
                                        | AXI_EMAC_NETCFG_FIFO_W64_Mks \
                                        | AXI_EMAC_NETCFG_RX_FCS_Mks \
                                        | AXI_EMAC_NETCFG_SGMII_Mks

//  SGMII Full Duplex 10M - 0x0923080A
#define CFG_EMAC_NETCFG_SGMII_FD_10M      AXI_EMAC_NETCFG_FD_Msk \
                                        | AXI_EMAC_NETCFG_JFRAME_Msk \
                                        | AXI_EMAC_NETCFG_CLK_SGMII_Msk \
                                        | AXI_EMAC_NETCFG_RLCE_Msk \
                                        | AXI_EMAC_NETCFG_DRFCS_Msk \
                                        | AXI_EMAC_NETCFG_FIFO_W64_Mks \
                                        | AXI_EMAC_NETCFG_RX_FCS_Mks \
                                        | AXI_EMAC_NETCFG_SGMII_Mks


//  Enable Stacked VLAN Processing mode. Otherwise write 0
#define CFG_EMAC_GEM_VLAN_EN            AXI_EMAC_GEM_VLAN_EN_Msk

// =================  TSU Configs  ===============
#define CFG_TSU_INC_PER_1NS     0x14


// =================  HGPI Configs  ===============
#define CFG_HGPI_LMEM_BUF_EN                1
//  Number of system clock cycles, the state machine has to wait before retrying incase the buffers are full at the buffer manager.
#define CFG_HGPI_RX_LMEM_BUF_RETR_WAIT_CLK  0x200
//  LMEM first buffer header size value
#define CFG_HGPI_LMEM_BUF1_HRD_SIZE         0x30
//  DDR first buffer header size value
#define CFG_HGPI_DDR_BUF1_HRD_SIZE          0
//  LMEM buffer size value as 128 bytes
#define CFG_HGPI_LMEM_BUF_SIZE              0x80
//  DDR buffer size value as 128 bytes
#define CFG_HGPI_DDR_BUF_SIZE               0
//  LMEM header size from second buffer onwards for each buffer in chain.
#define CFG_HGPI_LMEM_BUF_HDR_CHAIN_SIZE    0x10
//  Threshold number of TMLF words - 64bit size, to be in the TMLF FIFO before transmission starts.
#define CFG_HGPI_TX_FIFO_START_THRES        0x178
//  Initial number of bytes read from received pointer in LMEM, to check for action fields.
#define CFG_GPI_DTX_ASEQ_CNT                0x40

// =================  EGPI/ETGPI Configs  ===============
#define CFG_EGPI_LMEM_BUF_EN                1
#define CFG_EGPI_RX_LMEM_BUF_RETR_WAIT_CLK  CFG_HGPI_RX_LMEM_BUF_RETR_WAIT_CLK
#define CFG_EGPI_LMEM_BUF1_HRD_SIZE         CFG_HGPI_LMEM_BUF1_HRD_SIZE
#define CFG_EGPI_DDR_BUF1_HRD_SIZE          CFG_HGPI_DDR_BUF1_HRD_SIZE
#define CFG_EGPI_LMEM_BUF_SIZE              CFG_HGPI_LMEM_BUF_SIZE
#define CFG_EGPI_DDR_BUF_SIZE               CFG_HGPI_DDR_BUF_SIZE
#define CFG_EGPI_LMEM_BUF_HDR_CHAIN_SIZE    CFG_HGPI_LMEM_BUF_HDR_CHAIN_SIZE
#define CFG_EGPI_TX_FIFO_START_THRES        CFG_HGPI_TX_FIFO_START_THRES
#define CFG_EGPI_DTX_ASEQ_LEN               0x0050UL

#define CFG_ETGPI_LMEM_BUF_EN               1
#define CFG_ETGPI_RX_LMEM_BUF_RETR_WAIT_CLK CFG_HGPI_RX_LMEM_BUF_RETR_WAIT_CLK
#define CFG_ETGPI_LMEM_BUF1_HRD_SIZE        CFG_EGPI_LMEM_BUF1_HRD_SIZE
#define CFG_ETGPI_DDR_BUF1_HRD_SIZE         0x0100UL
#define CFG_ETGPI_LMEM_BUF_SIZE             CFG_EGPI_LMEM_BUF_SIZE
#define CFG_ETGPI_DDR_BUF_SIZE              0x0800UL 
#define CFG_ETGPI_LMEM_BUF_HDR_CHAIN_SIZE   CFG_EGPI_LMEM_BUF_HDR_CHAIN_SIZE
#define CFG_ETGPI_TX_FIFO_START_THRES       0x00BCUL
#define CFG_ETGPI_DTX_ASEQ_LEN              0x0050UL

// =================  HIF Configs  ===============
//  TX/RX - BDP read poll counter / BDP write poll counter.
#define CFG_HIF_TX_POLL_RD_CNT    0x40
#define CFG_HIF_TX_POLL_WR_CNT    0x40
#define CFG_HIF_RX_POLL_RD_CNT    0x40
#define CFG_HIF_RX_POLL_WR_CNT    0x40

//  Sequence number check enable
#define CFG_HIF_SEQ_CHECK_EN        1

//  Initial sequence number to be programmed, default – 0
  //  #define CFG_HIF_SEQ_START_NUM    0          // specification VASSA   
#define CFG_HIF_SEQ_START_NUM       0x5CC5        // from driver

//  timeout enable for BDP fetch/update, Data write/read.
#define CFG_HIF_BDP_TIMEOUT_EN      0
#define CFG_HIF_BDP_TIMEOUT         0xC92C3BCD

//  Default reg values
#define CFG_HIF_MISK_BDPRD_WRDONE   0

// Based on the requirement need to map the TMU queue 0-7 to any of the HIF Channels
#define CFG_HIF_RX1_TO_TMU_QUE      0
#define CFG_HIF_RX2_TO_TMU_QUE      1
#define CFG_HIF_RX3_TO_TMU_QUE      2
#define CFG_HIF_RX4_TO_TMU_QUE      3
#define CFG_HIF_RX5_TO_TMU_QUE      4
#define CFG_HIF_RX6_TO_TMU_QUE      5
#define CFG_HIF_RX7_TO_TMU_QUE      6
#define CFG_HIF_RX8_TO_TMU_QUE      7

#define CFG_HIF_DMA_BURST_Bytes     AXI_HIF_DMA_BURST_128Bytes

// Maximum no of packets accpeted by HIF TX for this channel when LTC pkt flow bit is enabled.
#define CFG_HIF_CH_LTC_MAX_PKT      4


//==================    CLASS_HW  Configs  ======================
//----------- Class HW1 -------------
//  LMEM first buffer header size value. (Data in the LMEM is written from this offset. The first location of LMEM is however written with the subsequent buffer address if it exists.) - 48
#define CFG_CLASS1_LMEM_HDR_SIZE          0x0030

//  Snoop MCAST address mask (lower 32bit and upper 16bit)
#define CFG_CLASS1_SNOOP_MCAST_MASK_LO    0xFFFFFFFFUL
#define CFG_CLASS1_SNOOP_MCAST_MASK_HI    0x0000FFFFUL
//  SPL multicast address of PTP packets to punt to host control channel. (lower 32bit and upper 16bit)
#define CFG_CLASS1_SNOOP_MCAST_ADDR_LO    0xC200000EUL
#define CFG_CLASS1_SNOOP_MCAST_ADDR_HI    0x00000180UL

//  special punt enable for all ports
#define CFG_CLASS1_SPEC_PUNT_ALL_EN       1
// global fall back bd entry (31 bits in CFG and 24 bits in CFG1 registers)
#define CFG_CLASS1_GL_FALLBACK_ENTRY      0

//  Processor peripherals base address
#define CFG_CLASS1_PER_BASE_ADDR          0x00C2UL

// COS value for punt operation of Management packet
#define CFG_CLASS1_PUNT_COS_MGMT          KX028_ACT_FORWARD
// COS value for punt operation of L2 Special
#define CFG_CLASS1_PUNT_COS_L2            KX028_ACT_FORWARD
// COS value for punt operation of SA Miss
#define CFG_CLASS1_PUNT_COS_SA_MISS       KX028_ACT_FORWARD
// COS value for punt operation of SA Relearn
#define CFG_CLASS1_PUNT_COS_SA_RELEARN    KX028_ACT_FORWARD
// COS value for punt operation of SA is Active
#define CFG_CLASS1_PUNT_COS_SA_ACTIVE     KX028_ACT_FORWARD
// COS value for punt operation of SNOOP upper
#define CFG_CLASS1_PUNT_COS_SNOOP         KX028_ACT_FORWARD
// COS value for punt operation for PUNT requested
#define CFG_CLASS1_PUNT_COS_REQ           KX028_ACT_FORWARD

//----------- Class HW2 -------------
#define CFG_CLASS2_LMEM_HDR_SIZE          CFG_CLASS1_LMEM_HDR_SIZE

#define CFG_CLASS2_SNOOP_MCAST_MASK_LO    CFG_CLASS1_SNOOP_MCAST_MASK_LO
#define CFG_CLASS2_SNOOP_MCAST_MASK_HI    CFG_CLASS1_SNOOP_MCAST_MASK_HI
#define CFG_CLASS2_SNOOP_MCAST_ADDR_LO    CFG_CLASS1_SNOOP_MCAST_ADDR_LO
#define CFG_CLASS2_SNOOP_MCAST_ADDR_HI    CFG_CLASS1_SNOOP_MCAST_ADDR_HI


#define CFG_CLASS2_SPEC_PUNT_ALL_EN       1
#define CFG_CLASS2_GL_FALLBACK_ENTRY      0
#define CFG_CLASS2_PER_BASE_ADDR          CFG_CLASS1_PER_BASE_ADDR

#define CFG_CLASS2_PUNT_COS_MGMT          KX028_ACT_FORWARD
#define CFG_CLASS2_PUNT_COS_L2            KX028_ACT_FORWARD
#define CFG_CLASS2_PUNT_COS_SA_MISS       KX028_ACT_FORWARD
#define CFG_CLASS2_PUNT_COS_SA_RELEARN    KX028_ACT_FORWARD
#define CFG_CLASS2_PUNT_COS_SA_ACTIVE     KX028_ACT_FORWARD
#define CFG_CLASS2_PUNT_COS_SNOOP         KX028_ACT_FORWARD
#define CFG_CLASS2_PUNT_COS_REQ           KX028_ACT_FORWARD


// =================  Class HW Configs  ===============

#define CFG_BUF_WATERMARK_AFULL   40


// Punt port map. Only one bit should be set(hif1 = 4 or hif2 = 8) - TODO?
#define CFG_HW1_PUNT_PORT         16
// Q number from TC value or cos (1:  NPU, 0: not NPU)
#define CFG_HW1_Q_NUM_SEL         1
// Disables the punt
#define CFG_HW1_PUNT_DIS          1
// Q number for egress time-stamp report
#define CFG_HW1_Q_ETGS_COS        1
// flood supression.setting a bit would make the respective cos value to flood when the action==ACT_COS_DISCARD; 
// if the value is zero and action==ACT_COS_DISCARD then the packet will be discarded
#define CFG_HW1_DISCARD_COS       1
// setting 1 will use tmu inq full
#define CFG_HW1_USE_TMU_INQ       1

//  Class HW2
#define CFG_HW2_PUNT_PORT         CFG_HW1_PUNT_PORT
#define CFG_HW2_Q_NUM_SEL         CFG_HW1_Q_NUM_SEL
#define CFG_HW2_PUNT_DIS          CFG_HW1_PUNT_DIS
#define CFG_HW2_Q_ETGS_COS        CFG_HW1_Q_ETGS_COS
#define CFG_HW2_DISCARD_COS       CFG_HW1_DISCARD_COS
#define CFG_HW2_USE_TMU_INQ       CFG_HW1_USE_TMU_INQ

//  TMU
#define CFG_TMU_PHY_TDQ_CTRL      AXI_TMU_PHY_TDQ_EN_ALL
#define CFG_TMU_CNTX_ACCESS_MODE  AXI_TMU_CNTX_ACCESS_CTRL_INDIRECT


//  ====================  Slow SPI Access ===========
#define CFG_NEW_PACKET_IN_LMEM_REG_ADDR     AXI_NEW_PACKET_IN_LMEM_REG_ADDR_DEF

//  TX/RX path enable, Management port enable, External TSU timer enable - 0x0080001C
#define CFG_EMAC1_ENA_CTRL      AXI_EMAC_NETCTRL_RX_EN_Msk | AXI_EMAC_NETCTRL_TX_EN_Msk | AXI_EMAC_NETCTRL_MANAG_EN_Msk | AXI_EMAC_NETCTRL_TSU_EN_Msk
#define CFG_EMAC2_ENA_CTRL      CFG_EMAC1_ENA_CTRL
#define CFG_EMAC3_ENA_CTRL      CFG_EMAC1_ENA_CTRL
#define CFG_EMAC4_ENA_CTRL      CFG_EMAC1_ENA_CTRL
#define CFG_EMAC5_ENA_CTRL      CFG_EMAC1_ENA_CTRL
#define CFG_EMAC6_ENA_CTRL      CFG_EMAC1_ENA_CTRL
#define CFG_EMAC7_ENA_CTRL      CFG_EMAC1_ENA_CTRL
#define CFG_EMAC8_ENA_CTRL      CFG_EMAC1_ENA_CTRL
#define CFG_EMAC9_ENA_CTRL      CFG_EMAC1_ENA_CTRL
#define CFG_EMAC10_ENA_CTRL     CFG_EMAC1_ENA_CTRL
#define CFG_EMAC11_ENA_CTRL     CFG_EMAC1_ENA_CTRL
#define CFG_EMAC12_ENA_CTRL     CFG_EMAC1_ENA_CTRL
#define CFG_EMAC13_ENA_CTRL     CFG_EMAC1_ENA_CTRL
#define CFG_EMAC14_ENA_CTRL     CFG_EMAC1_ENA_CTRL
#define CFG_EMAC15_ENA_CTRL     CFG_EMAC1_ENA_CTRL
#define CFG_EMAC16_ENA_CTRL     CFG_EMAC1_ENA_CTRL



#endif  //MDR_1923KX028_CONFIG_H_

#ifndef  MDR_1923KX028_CONFIG_H_
#define  MDR_1923KX028_CONFIG_H_

#include <stdint.h>


#define CFG_LEANR_BY_EMAC           0
#define CFG_USE_CRIT_SECT           1
#define CFG_PTP_PUNT_FORW_MAC       1

//  The MAC can optionally replace the timestamp field in PTP 1588 transmit sync frames to support one step clock mode.
#define CFG_PTP_ONE_STEP_TIMESTAMP  0
//  The MAC can optionally do one step transparent clock residence time correction for PTP 1588 version 2 transmit sync frames
#define CFG_PTP_CORRECTION          0
//  FlowControl - Enable Pause Frames
#define CFG_EMAC_PAUSE_RX_ENABLE    0


#define KX028_SOFT_RESET_DELAY_MS   100

//#define MDR_KX028_DEBUG     1


//  Прототип функция задержки, (передается в функции работы с базисом, для реализации задержки).
//  В случае RTOS можно использовать Sleep
typedef void (*MDR_KX028_DelayMs)(uint32_t);

//  Задержки, используемые внутри функций базиса, подставляются в функцию типа MDR_KX028_DelayMs
#define MDR_KX028_RESET_DLEAY_MS    100

//  Redefine Functions
//#define MDR_KX028_DelayMs(x)

#if CFG_USE_CRIT_SECT
  #define MDR_KX028_CRITSECT_ENTER    __disable_irq()
  #define MDR_KX028_CRITSECT_EXIT     __enable_irq()
#else  
  #define MDR_KX028_CRITSECT_ENTER    (void)(0)
  #define MDR_KX028_CRITSECT_EXIT     (void)(0)
#endif

//  ===============================================================
//  ================  MODE1: PC Driver Acknowledge  ===============
//  ===============================================================
#define CFG_KX028_PC_ACK_ADDR                 0
#define CFG_KX028_PC_ACK_MSK                  0xFFFFUL
#define CFG_KX028_PC_ACK_READY                0x16C3UL

#define CFG_KX028_PC_MAJOR_FW_VERSION         1
#define CFG_KX028_PC_MINOR_FW_VERSION         2

#define CFG_KX028_PC_REG_CMD                  0x814
#define CFG_KX028_PC_REG_STATUS               0x5C
#define CFG_KX028_PC_REG_DATA1                0x58
#define CFG_KX028_PC_REG_DATA2                0x54

#define CFG_KX028_PC_TEST_DATA1               0x09080706
#define CFG_KX028_PC_TEST_DATA2               0x19181700


//  ===============================================================
//  ===============  MODE2: SELECT ENABLE PORTS ===================
//  ===============================================================

// =================  EMAC Configs  ===============
#if CFG_EMAC_PAUSE_RX_ENABLE
  #define CFG_AXI_EMAC_NETCFG_PAUSE   AXI_EMAC_NETCFG_PAE_Msk
#else
  #define CFG_AXI_EMAC_NETCFG_PAUSE   0
#endif


// 0x01230000
#define CFG_EMAC_NETCFG_COMMON            AXI_EMAC_NETCFG_RLCE_Msk \
                                        | AXI_EMAC_NETCFG_DRFCS_Msk \
                                        | AXI_EMAC_NETCFG_FIFO_W64_Msk \
                                        | AXI_EMAC_NETCFG_RX_FCS_Msk \
                                        | CFG_AXI_EMAC_NETCFG_PAUSE

//  --------    Full Duplex   ---------
//  GMII Full Duplex 1Gbps - 0x0123040A
#define CFG_EMAC_NETCFG_GMII_FD_1G        AXI_EMAC_NETCFG_1G_EN_Msk  \
                                        | AXI_EMAC_NETCFG_JFRAME_Msk \
                                        | AXI_EMAC_NETCFG_FD_Msk \
                                        | CFG_EMAC_NETCFG_COMMON
                                            
//  MII Full Duplex 100M - 0x01230003
#define CFG_EMAC_NETCFG_MII_FD_100M       AXI_EMAC_NETCFG_100M \
                                        | AXI_EMAC_NETCFG_FD_Msk \
                                        | CFG_EMAC_NETCFG_COMMON

//  MII Full Duplex 10M - 0x01230002
#define CFG_EMAC_NETCFG_MII_FD_10M        AXI_EMAC_NETCFG_FD_Msk \
                                        | CFG_EMAC_NETCFG_COMMON

//  --------    Half Duplex   ---------
//  MII Half Duplex 100M - 0x01231009 
#define CFG_EMAC_NETCFG_MII_HD_100M       AXI_EMAC_NETCFG_100M \
                                        | AXI_EMAC_NETCFG_JFRAME_Msk \
                                        | AXI_EMAC_NETCFG_RTY_Msk  \
                                        | CFG_EMAC_NETCFG_COMMON

//  MII Half Duplex 10M - 0x01231008
#define CFG_EMAC_NETCFG_MII_HD_10M        AXI_EMAC_NETCFG_JFRAME_Msk \
                                        | AXI_EMAC_NETCFG_RTY_Msk  \
                                        | CFG_EMAC_NETCFG_COMMON

//  --------    SGMII MODE (Serial GMII)   ---------
#define CFG_EMAC_NETCFG_SGMII_FD_SEL      AXI_EMAC_NETCFG_FD_Msk \
                                        | AXI_EMAC_NETCFG_JFRAME_Msk \
                                        | AXI_EMAC_NETCFG_PCS_SGMII_Msk \
                                        | AXI_EMAC_NETCFG_SGMII_Msk \
                                        | CFG_EMAC_NETCFG_COMMON
                                        
//  SGMII Full Duplex 1Gbps - 0x09230C0A
#define CFG_EMAC_NETCFG_SGMII_FD_1G     (CFG_EMAC_NETCFG_SGMII_FD_SEL | AXI_EMAC_NETCFG_1G_EN_Msk)
//  SGMII Full Duplex 100M - 0x0923080B
#define CFG_EMAC_NETCFG_SGMII_FD_100M   (CFG_EMAC_NETCFG_SGMII_FD_SEL | AXI_EMAC_NETCFG_100M)
//  SGMII Full Duplex 10M - 0x0923080A
#define CFG_EMAC_NETCFG_SGMII_FD_10M    (CFG_EMAC_NETCFG_SGMII_FD_SEL)

//  Enable Stacked VLAN Processing mode. Otherwise write 0
#define CFG_EMAC_GEM_VLAN_EN            AXI_EMAC_GEM_VLAN_EN_Msk
#define CFG_EMAC_JUMBO_MAX_LEN          9000


//  ===============  SELECT ENABLE PORTS ===================
#define EMAC_DISABLED           AXI_EMAC_CTRL_PORT_DIS_Msk

#define CFG_EMAC1_NETCFG        EMAC_DISABLED
#define CFG_EMAC2_NETCFG        CFG_EMAC_NETCFG_MII_FD_100M
#define CFG_EMAC3_NETCFG        CFG_EMAC_NETCFG_MII_FD_100M
#define CFG_EMAC4_NETCFG        EMAC_DISABLED //CFG_EMAC_NETCFG_MII_FD_100M
#define CFG_EMAC5_NETCFG        EMAC_DISABLED
#define CFG_EMAC6_NETCFG        EMAC_DISABLED
#define CFG_EMAC7_NETCFG        EMAC_DISABLED //CFG_EMAC_NETCFG_SGMII_FD_100M // CFG_EMAC_NETCFG_SGMII_FD_1G
#define CFG_EMAC8_NETCFG        EMAC_DISABLED
#define CFG_EMAC9_NETCFG        EMAC_DISABLED
#define CFG_EMAC10_NETCFG       EMAC_DISABLED
#define CFG_EMAC11_NETCFG       EMAC_DISABLED
#define CFG_EMAC12_NETCFG       EMAC_DISABLED
#define CFG_EMAC13_NETCFG       EMAC_DISABLED
#define CFG_EMAC14_NETCFG       EMAC_DISABLED
#define CFG_EMAC15_NETCFG       EMAC_DISABLED
#define CFG_EMAC16_NETCFG       EMAC_DISABLED

#define CFG_DEF_VLANID          1

#define CFG_EMAC1_VLANID        CFG_DEF_VLANID
#define CFG_EMAC2_VLANID        CFG_DEF_VLANID
#define CFG_EMAC3_VLANID        CFG_DEF_VLANID
#define CFG_EMAC4_VLANID        CFG_DEF_VLANID
#define CFG_EMAC5_VLANID        CFG_DEF_VLANID
#define CFG_EMAC6_VLANID        CFG_DEF_VLANID
#define CFG_EMAC7_VLANID        CFG_DEF_VLANID
#define CFG_EMAC8_VLANID        CFG_DEF_VLANID
#define CFG_EMAC9_VLANID        CFG_DEF_VLANID
#define CFG_EMAC10_VLANID       CFG_DEF_VLANID
#define CFG_EMAC11_VLANID       CFG_DEF_VLANID
#define CFG_EMAC12_VLANID       CFG_DEF_VLANID
#define CFG_EMAC13_VLANID       CFG_DEF_VLANID
#define CFG_EMAC14_VLANID       CFG_DEF_VLANID
#define CFG_EMAC15_VLANID       CFG_DEF_VLANID
#define CFG_EMAC16_VLANID       CFG_DEF_VLANID


#define CFG_GPI_EN              AXI_GPI_CTRL_EN_Msk
#define CFG_GPI_DIS             0

//  ===============  MAC ENABLE WITH ===================
//  TX/RX path enable, Management port enable, External TSU timer enable - 0x0080001C
#define CFG_EMAC_CTRL_OFF       0
#define CFG_EMAC1_CTRL_ON       (AXI_EMAC_NETCTRL_RX_EN_Msk | AXI_EMAC_NETCTRL_TX_EN_Msk | AXI_EMAC_NETCTRL_MANAG_EN_Msk | CFG_EMAC_PTP_ONE_STEP | CFG_EMAC_PTP_CORRECTION)
//  TSU external (CLK from EMAC1 to others)
#define CFG_EMAC2_16_CTRL_ON    (CFG_EMAC1_CTRL_ON | AXI_EMAC_NETCTRL_TSU_EN_Msk)

#define CFG_EMAC1_ENA_CTRL      CFG_EMAC1_NETCFG  != EMAC_DISABLED ? CFG_EMAC1_CTRL_ON    : CFG_EMAC_CTRL_OFF
#define CFG_EMAC2_ENA_CTRL      CFG_EMAC2_NETCFG  != EMAC_DISABLED ? CFG_EMAC2_16_CTRL_ON : CFG_EMAC_CTRL_OFF
#define CFG_EMAC3_ENA_CTRL      CFG_EMAC3_NETCFG  != EMAC_DISABLED ? CFG_EMAC2_16_CTRL_ON : CFG_EMAC_CTRL_OFF
#define CFG_EMAC4_ENA_CTRL      CFG_EMAC4_NETCFG  != EMAC_DISABLED ? CFG_EMAC2_16_CTRL_ON : CFG_EMAC_CTRL_OFF
#define CFG_EMAC5_ENA_CTRL      CFG_EMAC5_NETCFG  != EMAC_DISABLED ? CFG_EMAC2_16_CTRL_ON : CFG_EMAC_CTRL_OFF
#define CFG_EMAC6_ENA_CTRL      CFG_EMAC6_NETCFG  != EMAC_DISABLED ? CFG_EMAC2_16_CTRL_ON : CFG_EMAC_CTRL_OFF
#define CFG_EMAC7_ENA_CTRL      CFG_EMAC7_NETCFG  != EMAC_DISABLED ? CFG_EMAC2_16_CTRL_ON : CFG_EMAC_CTRL_OFF
#define CFG_EMAC8_ENA_CTRL      CFG_EMAC8_NETCFG  != EMAC_DISABLED ? CFG_EMAC2_16_CTRL_ON : CFG_EMAC_CTRL_OFF
#define CFG_EMAC9_ENA_CTRL      CFG_EMAC9_NETCFG  != EMAC_DISABLED ? CFG_EMAC2_16_CTRL_ON : CFG_EMAC_CTRL_OFF
#define CFG_EMAC10_ENA_CTRL     CFG_EMAC10_NETCFG != EMAC_DISABLED ? CFG_EMAC2_16_CTRL_ON : CFG_EMAC_CTRL_OFF
#define CFG_EMAC11_ENA_CTRL     CFG_EMAC11_NETCFG != EMAC_DISABLED ? CFG_EMAC2_16_CTRL_ON : CFG_EMAC_CTRL_OFF
#define CFG_EMAC12_ENA_CTRL     CFG_EMAC12_NETCFG != EMAC_DISABLED ? CFG_EMAC2_16_CTRL_ON : CFG_EMAC_CTRL_OFF
#define CFG_EMAC13_ENA_CTRL     CFG_EMAC13_NETCFG != EMAC_DISABLED ? CFG_EMAC2_16_CTRL_ON : CFG_EMAC_CTRL_OFF
#define CFG_EMAC14_ENA_CTRL     CFG_EMAC14_NETCFG != EMAC_DISABLED ? CFG_EMAC2_16_CTRL_ON : CFG_EMAC_CTRL_OFF
#define CFG_EMAC15_ENA_CTRL     CFG_EMAC15_NETCFG != EMAC_DISABLED ? CFG_EMAC2_16_CTRL_ON : CFG_EMAC_CTRL_OFF
#define CFG_EMAC16_ENA_CTRL     CFG_EMAC16_NETCFG != EMAC_DISABLED ? CFG_EMAC2_16_CTRL_ON : CFG_EMAC_CTRL_OFF


//  Port Init Settings
#define KX028_PORTS_VLAN_TAG            0x8100UL
#define KX028_PORTS_STRUC1_DEF(vlanFallback)       AXI_CLASS_STRUC1_FILL( vlanFallback, KX028_PORTS_VLAN_TAG )

#define KX028_PORTS_SHUTDOWN_ON         AXI_CLASS_STRUC2_PORT_SHUTDOWN_Msk  // 0x00000001
#define KX028_PORTS_SHUTDOWN_OFF        0
#define KX028_PORTS_AFT                 KX028_PortAcc_AnyTagging       // 0x000000F0
#define KX028_PORTS_BLOCKSTATE          KX028_PortBlkState_Forwarding  // 0x00000F00
#define KX028_PORTS_DEF_CFI             0                              // 0x00001000
#define KX028_PORTS_DEF_PRI             0                              // 0x0000E000
#define KX028_PORTS_DEF_TC              0                              // 0x00070000
#define KX028_PORTS_TRUSTED             0                              // 0x00080000
#define KX028_PORTS_VID_PREFIX          0                              // 0x00100000
#define KX028_PORTS_UNTAG_FROM_BTABLE   0                              // 0x00200000

#define KX028_PORTS_STRUC2_OFF_DEF     AXI_CLASS_STRUC2_FILL( KX028_PORTS_SHUTDOWN_ON, \
                                                   KX028_PORTS_AFT, \
                                                   KX028_PORTS_BLOCKSTATE, \
                                                   KX028_PORTS_DEF_CFI, \
                                                   KX028_PORTS_DEF_PRI, \
                                                   KX028_PORTS_DEF_TC,  \
                                                   KX028_PORTS_TRUSTED, \
                                                   KX028_PORTS_VID_PREFIX,  \
                                                   KX028_PORTS_UNTAG_FROM_BTABLE)
                                                   
#define KX028_PORTS_STRUC2_ON_DEF     AXI_CLASS_STRUC2_FILL( KX028_PORTS_SHUTDOWN_OFF,\
                                                   KX028_PORTS_AFT, \
                                                   KX028_PORTS_BLOCKSTATE, \
                                                   KX028_PORTS_DEF_CFI, \
                                                   KX028_PORTS_DEF_PRI, \
                                                   KX028_PORTS_DEF_TC,  \
                                                   KX028_PORTS_TRUSTED, \
                                                   KX028_PORTS_VID_PREFIX,  \
                                                   KX028_PORTS_UNTAG_FROM_BTABLE)                                                   


// =================  BMU Configs  ===============
// Program for Maximum buffer count as 2048 (i.e. 256K memory accommodating, 2048 buffers of size 128 bytes) - 0x800
#define CFG_BMU_UCAST_BUF_CNT           AXI_BMU_UCAST_BUF_CNT_MAX
// Buffers count for slave SPI
#define CFG_BMU1_SPI_READ_BUFF_COUNT    1
// Buffer size bits or number of bit representing the LMEM buffer size (7 = 128bytes).
#define CFG_BMU_BUF_SIZE_128            AXI_BMU_BUF_SIZE_128
// Defined for SPL, according to CFG_BMU_BUF_SIZE_128
#define CFG_BMU_BUF_LEN                 128
//  Threshold number of LMEM buffers occupied to generate interrupt - 0x800
#define CFG_BMU_THRES_UCAST             CFG_BMU_UCAST_BUF_CNT


#define CFG_BMU1_SEL_LMEM_ADDR    AXI_LMEM0_BASE_ADDR
#define CFG_BMU2_SEL_LMEM_ADDR    AXI_LMEM4_BASE_ADDR



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
#define CFG_HGPI_DTX_ASEQ_CNT               0x40

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
#define CFG_ETGPI_DDR_BUF1_HRD_SIZE         0 //0x0100UL
#define CFG_ETGPI_LMEM_BUF_SIZE             CFG_EGPI_LMEM_BUF_SIZE
#define CFG_ETGPI_DDR_BUF_SIZE              0 //0x0800UL 
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

#define CFG_CLASS1_INQ_ADDR     (CBUS_BASE_ADDR | AXI_CLASS_HW1_BASE_ADDR | AXI_CLASS_INQ_PKTPTR)
#define CFG_TMU_INQ_ADDR        (CBUS_BASE_ADDR | AXI_TMU_BASE_ADDR  | AXI_TMU_PHY_INQ_PKTPTR)


//==================    CLASS_HW  Configs  ======================
//----------- Class HW1 -------------
//  LMEM first buffer header size value. (Data in the LMEM is written from this offset. The first location of LMEM is however written with the subsequent buffer address if it exists.) - 48
#define CFG_CLASS1_LMEM_HDR_SIZE            0x0030

//  Snoop MCAST address mask (lower 32bit and upper 16bit)
#define CFG_CLASS1_SNOOP_MCAST_MASK_LO      0xFFFFFFFFUL
#define CFG_CLASS1_SNOOP_MCAST_MASK_HI      0x0000FFFFUL
//  SPL multicast address of PTP packets to punt to host control channel. (lower 32bit and upper 16bit)
//  No Forwarded PTP MAC
#if CFG_PTP_PUNT_FORW_MAC
  #define CFG_CLASS1_SNOOP_MCAST_ADDR_LO    0x19000000UL
  #define CFG_CLASS1_SNOOP_MCAST_ADDR_HI    0x0000011BUL
#else
  #define CFG_CLASS1_SNOOP_MCAST_ADDR_LO    0xC200000EUL
  #define CFG_CLASS1_SNOOP_MCAST_ADDR_HI    0x00000180UL  
#endif

//  special punt enable for all ports
#define CFG_CLASS1_SPEC_PUNT_ALL_EN       0
// global fall back bd entry (31 bits in CFG and 24 bits in CFG1 registers)
// Данные поля задают, что классификатору делать с пакетом по умолчанию.
// Т.е. когда для пакета нет соответствия в таблиах МАС и/или VLAN
#define CFG_CLASS1_DEF_FORW_LIST          0
#define CFG_CLASS1_DEF_UNTAG_LIST         0
#define CFG_CLASS1_DEF_HIT_ACTION_UC      KX028_ACT_FORWARD
#define CFG_CLASS1_DEF_HIT_ACTION_MC      KX028_ACT_FORWARD
#define CFG_CLASS1_DEF_MISS_ACTION_UC     KX028_ACT_FORWARD
#define CFG_CLASS1_DEF_MISS_ACTION_MC     KX028_ACT_FORWARD
#define CFG_CLASS1_DEF_MSTP_ACTION        KX028_ACT_FORWARD


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


#define CFG_CLASS2_SPEC_PUNT_ALL_EN       0
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
//#if CFG_LEANR_BY_EMAC
//  #define CFG_HW1_PUNT_PORT         CFG_LEARN_EMAC
//#else
  #define CFG_HW1_PUNT_PORT         16  
//#endif


// Q number from TC value or cos (1:  NPU, 0: not NPU)
#define CFG_HW1_Q_NUM_SEL         1
// Disables the punt
#define CFG_HW1_PUNT_DIS          0
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


//  ====================  Slow SPI Access ===========
#if CFG_LEANR_BY_EMAC
  //  Отправка пакетов на обучение через EMAC - выбрать необходимый
  #define CFG_LEARN_EMAC                            KX028_EMAC4
  #define CFG_LEARN_EGPI                            KX028_EGPI4
  #define CFG_LEARN_TMU_INQ_ADDR                    AXI_TMU_PHY3_INQ_ADDR
  
  #define CFG_TMU_PUNT_ADDR                        (AXI_EGPI4_BASE_ADDR  | AXI_GPI_INQ_PKTPTR)  
#else
  //  Адрес с которого читается указатель на входной фрейм по шине AXI (соответствует CFG_BMU2_SEL_LMEM_ADDR)
  #define CFG_NEW_PACKET_IN_LMEM_ADDR              (AXI_LMEM4_BASE_ADDR + 0x0003FFA0UL)     //0x0043FFA0UL
  #define CFG_TMU_PUNT_ADDR                         CFG_NEW_PACKET_IN_LMEM_ADDR  
#endif


//  Адрес с которого лежат данные принятого пакета в CFG_NEW_PACKET_IN_LMEM_REG_ADDR
//  Начинается с MAC_DEST, предыдущие данные - загловки
#define CFG_LMEM_NEW_PACKET_UNKNOWN_HEADER    32
#define CFG_LMEM_NEW_PACKET_OFFS      (CFG_LMEM_NEW_PACKET_UNKNOWN_HEADER + CFG_HGPI_LMEM_BUF_HDR_CHAIN_SIZE)

#if CFG_PTP_ONE_STEP_TIMESTAMP
  #define CFG_EMAC_PTP_ONE_STEP   AXI_EMAC_NETCTRL_OSSMODE_EN_Msk
#else
  #define CFG_EMAC_PTP_ONE_STEP   0
#endif

#if CFG_PTP_CORRECTION
  #define CFG_EMAC_PTP_CORRECTION AXI_EMAC_NETCTRL_OSS_CORRECTION_Msk
#else
  #define CFG_EMAC_PTP_CORRECTION 0
#endif


//======================= MAC Table  ==================
#define CFG_MAC_TABLE_START_ADDR               0x40000UL 

#define CFG_MAC_TABLE_HASH_ITEMS_COUNT         0x1000
#define CFG_MAC_TABLE_COLL_ITEMS_COUNT         0x1000
#define CFG_MAC_TABLE_ITEMS_COUNT              (CFG_MAC_TABLE_HASH_ITEMS_COUNT + CFG_MAC_TABLE_COLL_ITEMS_COUNT)
#define CFG_MAC_TABLE_COLL_HEAD_PTR            CFG_MAC_TABLE_HASH_ITEMS_COUNT
#define CFG_MAC_TABLE_COLL_TAIL_PTR            (CFG_MAC_TABLE_COLL_HEAD_PTR + CFG_MAC_TABLE_COLL_ITEMS_COUNT - 1)


//======================= VLAN Table  ==================
#define CFG_VLAN_TABLE_HASH_ENTRIES             0x40
#define CFG_VLAN_TABLE_COLL_ENTRIES             0x40    
#define CFG_VLAN_TABLE_ENTRIES                  (CFG_VLAN_TABLE_HASH_ENTRIES + CFG_VLAN_TABLE_COLL_ENTRIES)
#define CFG_VLAN_TABLE_INIT_HEAD_PTR            0x40
#define CFG_VLAN_TABLE_INIT_TAIL_PTR            (CFG_VLAN_TABLE_HASH_ENTRIES + CFG_VLAN_TABLE_COLL_ENTRIES - 1)


//======================= SFP modules on board  ==================
#define SFP_COUNT  1


//======================= PCI Config  ==================
#define CFG_PCIE_VENDOR_ID   0x16c3
#define CFG_PCIE_DEVICE_ID   0x0fac

#define CFG_PCIE_REVISION_ID            0
#define CFG_PCIE_PROGRAM_INTERFACE      0
#define CFG_PCIE_SUBCLASS_CODE          0
#define CFG_PCIE_BASE_CLASS_CODE        2


//======================= EMAC PHYs  ==================
// Must be set to 1 for a valid Clause 22 frame and to 0 for a valid Clause 45 frame
// (Clause45 - косвенная адресация, появилась когда не хватило 5 бит на адрес регистра)
#define CFG_EMAC_PHY_CLAUSE_22    1
#define CFG_EMAC_PHY_RESET_MS     50


//======================= FRAME INJECTION ================
#define CFG_INJECT_BMU_ADDR        AXI_BMU1_BASE_ADDR
#define CFG_INJECT_LMEM_ADDR      (CBUS_BASE_ADDR | AXI_LMEM0_BASE_ADDR)  // 0xC0200000
#define CFG_INJECT_LMEM_ADDR_Msk   0xFFF00000

// 128 buff len - 16 header len = 112 bytes in buff, starting from second
// 1518 max frame Len / 112 = 13
// +2 for first and second - for classifier operations
#define CFG_INJECT_BUFF_CHAIN_LEN_MAX    15


#endif  //MDR_1923KX028_CONFIG_H_

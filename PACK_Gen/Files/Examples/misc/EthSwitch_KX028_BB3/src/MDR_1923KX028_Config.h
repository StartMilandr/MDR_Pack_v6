#ifndef  MDR_1923KX028_CONFIG_H_
#define  MDR_1923KX028_CONFIG_H_

//  Таймаут ожидании окончания операции, в количествах чтения регистра статуса
#define KX028_TABLES_WAIT_CYCLES_MAX  100

//  Table Processing
#define KX028_AGING_HASH_CNT_PER_ITERATION    MDR_KX028_MAC_TABLE_LEN
#define KX028_DYN_MAC_PACKETS_PER_ITERATION   10

//  Redefine Functions
#define MDR_KX028_DelayMs(x)
#define MDR_KX028_CRITSECT_ENTER
#define MDR_KX028_CRITSECT_LEAVE


//  Port Init Settings
#define KX028_PORTS_FALLBACK_ID   AXI_CLASS_STRUC1_PORT_FALLBACK_BDID_DEF
#define KX028_PORTS_TAG_ID        0x8100

#define KX028_PORTS_SHUTDOWN           0                         //     0x00000001
#define KX028_PORTS_AFT                KX028_FRM_ACC_ANY_TAGGING //     0x000000F0
#define KX028_PORTS_BLOCKSTATE         KX028_STP_ACC_FORWARDING  //     0x00000F00
#define KX028_PORTS_DEF_CFI            0                         //     0x00001000
#define KX028_PORTS_DEF_PRI            0                         //     0x0000E000
#define KX028_PORTS_DEF_TC             0                         //     0x00070000
#define KX028_PORTS_TRUSTED            0                         //     0x00080000
#define KX028_PORTS_VID_PREFIX         0                         //     0x00100000
#define KX028_PORTS_UNTAG_FROM_BTABLE  0                         //     0x00200000


#define MDR_KX028_DEBUG     1


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


// =================  TSU Configs  ===============
#define CFG_TSU_INC_PER_1NS     0x14


#endif  //MDR_1923KX028_CONFIG_H_

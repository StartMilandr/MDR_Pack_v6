#include <MDR_1923KX028_M2_Init.h>

static void MDR_KX028_SetCtrlBMU_All(uint32_t regValue);
static void MDR_KX028_SetCtrlEGPI_All(uint32_t regValue);
static void MDR_KX028_SetCtrlHGPI(uint32_t regValue);
static void MDR_KX028_SetCtrlCLASS_All(uint32_t regValue);


// ---------  BMU Initialization  -----------

void MDR_KX028_InitBMU1(MDR_KX028_DelayMs DelayFunc)
{
  // 1 - Soft reset the BMU block. After soft reset, need to wait for 100us to perform another CSR write/read.
  MDR_KX028_WriteAXI(AXI_BMU1_BASE_ADDR + AXI_BMU_CTRL,           AXI_BMU_CTRL_RESET_Msk);
  DelayFunc(MDR_KX028_RESET_DLEAY_MS);  
  // 2 - Program for Maximum buffer count as 2048
  MDR_KX028_WriteAXI(AXI_BMU1_BASE_ADDR + AXI_BMU_UCAST_CONFIG,   CFG_BMU_UCAST_BUF_CNT);
  // 3 - Program LMEM block base address
  MDR_KX028_WriteAXI(AXI_BMU1_BASE_ADDR + AXI_BMU_UCAST_BASEADDR, CBUS_BASE_ADDR | CFG_BMU1_SEL_LMEM_ADDR);
  // 4 - Buffer size bits or number of bit representing the LMEM buffer size
  MDR_KX028_WriteAXI(AXI_BMU1_BASE_ADDR + AXI_BMU_BUF_SIZE,       CFG_BMU_BUF_SIZE_128);
  // 5 - Threshold number of LMEM buffers occupied to generate interrupt (all 2048)
  MDR_KX028_WriteAXI(AXI_BMU1_BASE_ADDR + AXI_BMU_THRES,          CFG_BMU_THRES_UCAST);
  // 6 - Clearing the interrupts.
  MDR_KX028_WriteAXI(AXI_BMU1_BASE_ADDR + AXI_BMU_INT_SRC,        AXI_BMU_INT_SRC_ALL);
  // 7 - Disabling the interrupts
  MDR_KX028_WriteAXI(AXI_BMU1_BASE_ADDR + AXI_BMU_INT_ENABLE,     AXI_BMU_INT_DisALL);
}  

void MDR_KX028_InitBMU2(MDR_KX028_DelayMs DelayFunc)
{
  MDR_KX028_WriteAXI(AXI_BMU2_BASE_ADDR + AXI_BMU_CTRL,           AXI_BMU_CTRL_RESET_Msk);
  DelayFunc(MDR_KX028_RESET_DLEAY_MS);
  MDR_KX028_WriteAXI(AXI_BMU2_BASE_ADDR + AXI_BMU_UCAST_CONFIG,   CFG_BMU_UCAST_BUF_CNT - CFG_BMU1_SPI_READ_BUFF_COUNT);
  MDR_KX028_WriteAXI(AXI_BMU2_BASE_ADDR + AXI_BMU_UCAST_BASEADDR, CBUS_BASE_ADDR | CFG_BMU2_SEL_LMEM_ADDR);
  MDR_KX028_WriteAXI(AXI_BMU2_BASE_ADDR + AXI_BMU_BUF_SIZE,       CFG_BMU_BUF_SIZE_128);
  MDR_KX028_WriteAXI(AXI_BMU2_BASE_ADDR + AXI_BMU_THRES,          CFG_BMU_THRES_UCAST);
  MDR_KX028_WriteAXI(AXI_BMU2_BASE_ADDR + AXI_BMU_INT_SRC,        AXI_BMU_INT_SRC_ALL);
  MDR_KX028_WriteAXI(AXI_BMU2_BASE_ADDR + AXI_BMU_INT_ENABLE,     AXI_BMU_INT_DisALL);
}

// ---------  EMAC Initialization  -----------
void MDR_KX028_InitEMAC(MDR_KX028_EMAC_e emac, uint32_t netCfgReg)
{
  // 1 - Disable EMAC ports
  MDR_KX028_WriteAXI(MDR_KX028_AxiAddrEMAC[emac] + AXI_EMAC_CTRL, AXI_EMAC_CTRL_PORT_DIS_Msk);
  // 2 - Apply Network configuration
  MDR_KX028_WriteAXI(MDR_KX028_AxiAddrEMAC[emac] + AXI_EMAC_NETCFG, netCfgReg);
}  

void MDR_KX028_InitEMAC_GEM(MDR_KX028_EMAC_e emac)
{
  // 1 - Programming the lower 32bit DA address register to accept all packets
  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrEMAC[emac] + AXI_EMAC_GEM_DA_ADDR_LO, 0x00000000 );
  // 2 - Programming the upper 32bit DA address register to accept all packets.
  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrEMAC[emac] + AXI_EMAC_GEM_DA_ADDR_HI, 0x00000000 );          
  // 3 - Programming the lower 32bit DA address mask register to accept all packets
  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrEMAC[emac] + AXI_EMAC_GEM_DA_MASK_L0, 0xFFFFFFFF );
  // 4 - Programming the upper 16bit DA address mask register to accept all packets.
  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrEMAC[emac] + AXI_EMAC_GEM_DA_MASK_Hi, 0x0000FFFF );
  // 5 - Enable Stacked VLAN Processing mode.
  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrEMAC[emac] + AXI_EMAC_GEM_VLAN, CFG_EMAC_GEM_VLAN_EN);
}

//  from Demo-Board MAC Init
void MDR_KX028_InitEMAC_ex(MDR_KX028_EMAC_e emac)
{
////  EMAC 
//  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrEMAC[emac] + AXI_EMAC_IER,  0x00010200 );       // enable interrupts at: pcs_autoneg_compete, pcs_link_change
//  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrEMAC[emac] + AXI_EMAC_CTRL, AXI_EMAC_CTRL_PORT_DIS_Msk );

////  next 2 string is new in 1.1 version of firmware
//  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrEMAC[emac] + AXI_EMAC_PCS_AN_ADV,   0x00008020 );       //EMAC support full duplex via SGMII, next page support
//  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrEMAC[emac] + AXI_EMAC_PCS_AN_NT_TX, 0x00002001 );       //EMAC has not next page
//         
//  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrEMAC[emac] + AXI_EMAC_NETCFG,      0x083F0C12 );       // 1G, SGMII mode, jumbo frames disable, 1536 bytes frame disable, reject error packets...      
//  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrEMAC[emac] + AXI_EMAC_TSU_TIM_INC, 0x00000014 );

  //  EMAC_GEM
  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrEMAC[emac] + AXI_EMAC_GEM_DA_ADDR_LO, 0x00000000 );
  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrEMAC[emac] + AXI_EMAC_GEM_DA_ADDR_HI, 0x00000000 );          
  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrEMAC[emac] + AXI_EMAC_GEM_DA_MASK_L0, 0xFFFFFFFF );
  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrEMAC[emac] + AXI_EMAC_GEM_DA_MASK_Hi, 0x0000FFFF );
  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrEMAC[emac] + AXI_EMAC_GEM_VLAN,       CFG_EMAC_GEM_VLAN_EN);

  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrEMAC[emac] + AXI_EMAC_MAN_JUMBO_MAX_LEN, CFG_EMAC_JUMBO_MAX_LEN ); // Jumbo
}  
  
void MDR_KX028_WritePortStruct(MDR_KX028_EMAC_e emac, uint32_t regClassStruct1, uint32_t regClassStruct2 )
{ 
  MDR_KX028_WriteAXI( AXI_CLASS_HW1_BASE_ADDR + KX028_PortOffsStruct1[emac], regClassStruct1);                
  MDR_KX028_WriteAXI( AXI_CLASS_HW1_BASE_ADDR + KX028_PortOffsStruct2[emac], regClassStruct2);  
  MDR_KX028_WriteAXI( AXI_CLASS_HW2_BASE_ADDR + KX028_PortOffsStruct1[emac], regClassStruct1);                
  MDR_KX028_WriteAXI( AXI_CLASS_HW2_BASE_ADDR + KX028_PortOffsStruct2[emac], regClassStruct2);    
}

// ---------  GPI Initialization (EGPI/ETGPI/HGPI) -----------

void MDR_KX028_InitHGPI(void)
{
  // 1 - LMEM buffer enable / Wait CLK count for retry allocate LMEM buffers
  MDR_KX028_WriteAXI(AXI_HGPI_BASE_ADDR + AXI_GPI_RX_CONFIG,         AXI_GPI_RX_CONFIG_FILL(CFG_HGPI_LMEM_BUF_EN, CFG_HGPI_RX_LMEM_BUF_RETR_WAIT_CLK));  //{ 0x00650008, 0x02000001 },
  // 2 - LMEM first buffer header size value
  MDR_KX028_WriteAXI(AXI_HGPI_BASE_ADDR + AXI_GPI_HDR_SIZE,          AXI_GPI_HDR_SIZE_FILL(CFG_HGPI_LMEM_BUF1_HRD_SIZE, CFG_HGPI_DDR_BUF1_HRD_SIZE)); //{ 0x0065000C, 0x00000030 },	
  // 3 - LMEM buffer size value as 128 bytes
  MDR_KX028_WriteAXI(AXI_HGPI_BASE_ADDR + AXI_GPI_BUF_SIZE,          AXI_GPI_BUF_SIZE_FILL(CFG_HGPI_LMEM_BUF_SIZE, CFG_HGPI_DDR_BUF_SIZE));  //{ 0x00650010, 0x00000080 },	
  // 4 - Address of BMU1 / BMU2, where buffer should be allocated
  MDR_KX028_WriteAXI(AXI_HGPI_BASE_ADDR + AXI_GPI_LMEM_ALLOC_ADDR,   CBUS_BASE_ADDR | AXI_BMU1_BASE_ADDR | AXI_BMU_ALLOC_CTRL);       //{ 0x00650014, 0xC0100030 },	//BMU_1
  // 5 - Address of BMU1 / BMU2, where buffer should be freed.
  MDR_KX028_WriteAXI(AXI_HGPI_BASE_ADDR + AXI_GPI_LMEM_FREE_ADDR,    CBUS_BASE_ADDR | AXI_BMU1_BASE_ADDR | AXI_BMU_FREE_CTRL);        //{ 0x00650018, 0xC0100034 },	//BMU_1
  // 6 - Address of Class HW1 / HW2 INQ register where packet from peripherals are sent to.
  MDR_KX028_WriteAXI(AXI_HGPI_BASE_ADDR + AXI_GPI_CLASS_ADDR,        CBUS_BASE_ADDR | AXI_CLASS_HW1_BASE_ADDR | AXI_CLASS_INQ_PKTPTR);  //{ 0x00650024, 0xC0620010 },	//CLASS_HW_1 CLASS_INQ_PKTPTR      
  // 7 - LMEM header size from second buffer onwards for each buffer in chain.
  MDR_KX028_WriteAXI(AXI_HGPI_BASE_ADDR + AXI_GPI_LMEM_SEC_BUF_DATA_OFFSET, CFG_HGPI_LMEM_BUF_HDR_CHAIN_SIZE);  //{ 0x00650060, 0x00000010 },  
  // 8 - Threshold number of TMLF words - 64bit size, to be in the TMLF FIFO before transmission starts.
  MDR_KX028_WriteAXI(AXI_HGPI_BASE_ADDR + AXI_GPI_TMLF_TX,  CFG_HGPI_TX_FIFO_START_THRES);                      //{ 0x0065004C, 0x00000178 },
  // 9 - Initial number of bytes read from received pointer in LMEM, to check for action fields.
  MDR_KX028_WriteAXI(AXI_HGPI_BASE_ADDR + AXI_GPI_DTX_ASEQ, CFG_HGPI_DTX_ASEQ_CNT);                              //{ 0x00650050, 0x00000040 },
}  
 
void MDR_KX028_InitHGPI_Ex(void)
{  
//  MDR_KX028_WriteAXI(AXI_HGPI_BASE_ADDR + AXI_GPI_DDR_DATA_OFFSET,   0x00000100);         //{ 0x00650034, 0x00000100 },	//___Q no in spec  
  // LMEM data offset. Not applicable for NPU
  MDR_KX028_WriteAXI(AXI_HGPI_BASE_ADDR + AXI_GPI_LMEM_DATA_OFFSET,  CFG_HGPI_LMEM_BUF_HDR_CHAIN_SIZE);         //{ 0x00650038, 0x00000010 },	//___Q no in spec  
}

void MDR_KX028_InitEGPI(MDR_KX028_EMAC_e emac)
{
  //  The same like in MDR_KX028_InitHGPI
  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrEGPI[emac] + AXI_GPI_RX_CONFIG,          AXI_GPI_RX_CONFIG_FILL(CFG_EGPI_LMEM_BUF_EN, CFG_EGPI_RX_LMEM_BUF_RETR_WAIT_CLK));  // 0x02000001 );
  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrEGPI[emac] + AXI_GPI_HDR_SIZE,           AXI_GPI_HDR_SIZE_FILL(CFG_EGPI_LMEM_BUF1_HRD_SIZE, CFG_EGPI_DDR_BUF1_HRD_SIZE)); //0x00000030 );       //___Q in spec value 0x30
  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrEGPI[emac] + AXI_GPI_BUF_SIZE,           AXI_GPI_BUF_SIZE_FILL(CFG_HGPI_LMEM_BUF_SIZE, CFG_EGPI_DDR_BUF_SIZE));  //0x00000080 );       //___Q in spec value 0x80
  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrEGPI[emac] + AXI_GPI_LMEM_ALLOC_ADDR,    CBUS_BASE_ADDR | AXI_BMU1_BASE_ADDR | AXI_BMU_ALLOC_CTRL);              //0xC0100030 );
  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrEGPI[emac] + AXI_GPI_LMEM_FREE_ADDR,     CBUS_BASE_ADDR | AXI_BMU1_BASE_ADDR | AXI_BMU_FREE_CTRL);               //0xC0100034 );
  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrEGPI[emac] + AXI_GPI_CLASS_ADDR,         CBUS_BASE_ADDR | AXI_CLASS_HW1_BASE_ADDR | AXI_CLASS_INQ_PKTPTR);       //0xC0620010 );    
  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrEGPI[emac] + AXI_GPI_LMEM_SEC_BUF_DATA_OFFSET,  CFG_EGPI_LMEM_BUF_HDR_CHAIN_SIZE);                               //{ 0x00650060, 0x00000010 },  
  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrEGPI[emac] + AXI_GPI_TMLF_TX,            CFG_EGPI_TX_FIFO_START_THRES );                                         //0x00000178
  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrEGPI[emac] + AXI_GPI_DTX_ASEQ,           CFG_EGPI_DTX_ASEQ_LEN);                                                 //0x00000050 );
}

void MDR_KX028_InitEGPI_Ex(MDR_KX028_EMAC_e emac)
{
  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrEGPI[emac] + AXI_GPI_LMEM2_FREE_ADDR,    CBUS_BASE_ADDR | AXI_BMU2_BASE_ADDR | AXI_BMU_FREE_CTRL);         //0xC0700034 );    
  //MDR_KX028_WriteAXI ( MDR_KX028_AxiAddrEGP[emac] + AXI_GPI_DDR_DATA_OFFSET, 0x00000100 );
  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrEGPI[emac] + AXI_GPI_LMEM_DATA_OFFSET,   0x00000010 );
//  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrEGPI[emac] + AXI_GPI_LMEM_SEC_BUF_DATA_OFFSET, CFG_EGPI_LMEM_BUF_HDR_CHAIN_SIZE );
}

void MDR_KX028_InitETGPI(MDR_KX028_EMAC_e emac)
{
  //  The same like in MDR_KX028_InitHGPI
  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrETGPI[emac] + AXI_GPI_RX_CONFIG,         AXI_GPI_RX_CONFIG_FILL(CFG_ETGPI_LMEM_BUF_EN, CFG_ETGPI_RX_LMEM_BUF_RETR_WAIT_CLK));  //0x02000001 );
  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrETGPI[emac] + AXI_GPI_HDR_SIZE,          AXI_GPI_HDR_SIZE_FILL(CFG_EGPI_LMEM_BUF1_HRD_SIZE, CFG_ETGPI_DDR_BUF1_HRD_SIZE)); //0x01000030 );       //___Q in spec value 0x30  -TODO ?
  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrETGPI[emac] + AXI_GPI_BUF_SIZE,          AXI_GPI_BUF_SIZE_FILL(CFG_HGPI_LMEM_BUF_SIZE, CFG_ETGPI_DDR_BUF_SIZE)); //0x08000080 );       //___Q in spec value 0x80  -TODO ?
  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrETGPI[emac] + AXI_GPI_LMEM_ALLOC_ADDR,   CBUS_BASE_ADDR | AXI_BMU1_BASE_ADDR | AXI_BMU_ALLOC_CTRL);              //0xC0100030 );
  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrETGPI[emac] + AXI_GPI_LMEM_FREE_ADDR,    CBUS_BASE_ADDR | AXI_BMU1_BASE_ADDR | AXI_BMU_FREE_CTRL);               //0xC0100034 );
  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrETGPI[emac] + AXI_GPI_CLASS_ADDR,        CBUS_BASE_ADDR | AXI_CLASS_HW1_BASE_ADDR | AXI_CLASS_INQ_PKTPTR);       //0xC0620010 );
  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrETGPI[emac] + AXI_GPI_LMEM_SEC_BUF_DATA_OFFSET, CFG_ETGPI_LMEM_BUF_HDR_CHAIN_SIZE );  
  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrETGPI[emac] + AXI_GPI_TMLF_TX,           CFG_ETGPI_TX_FIFO_START_THRES);     //0x000000BC
  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrETGPI[emac] + AXI_GPI_DTX_ASEQ,          CFG_ETGPI_DTX_ASEQ_LEN );           //0x00000050 ); 
}

void MDR_KX028_InitETGPI_Ex(MDR_KX028_EMAC_e emac)
{
  //MDR_KX028_WriteAXI( MDR_KX028_AxiAddrETGPI[emac] + AXI_GPI_DDR_DATA_OFFSET,   0x00000100 );
  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrETGPI[emac] + AXI_GPI_LMEM_DATA_OFFSET,  0x00000010 );
  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrETGPI[emac] + AXI_GPI_CTRL,              0x00000001 );  // -TODO - (different with EGPI)?  ENABLE-?
}


// ---------  HIF Initialization -----------

void MDR_KX028_InitHIF(void)
{
  // 1, 2 - TX/RX BDP read/write poll counter
  MDR_KX028_WriteAXI(AXI_HIF1_BASE_ADDR + AXI_HIF_TX_POLL_CTRL,  AXI_HIF_TXRX_POLL_CTRL_FILL(CFG_HIF_TX_POLL_RD_CNT, CFG_HIF_TX_POLL_WR_CNT)); //{ 0x00640004, 0x00400040 },
  MDR_KX028_WriteAXI(AXI_HIF1_BASE_ADDR + AXI_HIF_RX_POLL_CTRL,  AXI_HIF_TXRX_POLL_CTRL_FILL(CFG_HIF_RX_POLL_RD_CNT, CFG_HIF_RX_POLL_WR_CNT)); //{ 0x00640008, 0x00400040 },
  // 3 - Sequence number check enable / BDP Timeout / Initial sequence number to be programmed, default – 0
  MDR_KX028_WriteAXI(AXI_HIF1_BASE_ADDR + AXI_HIF_MISC,  AXI_HIF_MISC_FILL(CFG_HIF_SEQ_CHECK_EN, CFG_HIF_MISK_BDPRD_WRDONE, CFG_HIF_BDP_TIMEOUT_EN, CFG_HIF_SEQ_START_NUM));	//{ 0x0064000C, 0x5CC50001 },	//___Q in spec value 0x0000_0001
  // 4 - Based on the requirement need to map the TMU queue 0-7 to any of the HIF Channels
  MDR_KX028_WriteAXI(AXI_HIF1_BASE_ADDR + AXI_HIF_RX_QUEUE_MAP_CH_NO_ADDR,   AXI_HIF_RX_QUEUE_MAP_CH_FILL(	          //{ 0x006400CC, 0x32103210 },	//___Q in spec value 0x3210_3210    
      CFG_HIF_RX1_TO_TMU_QUE,
      CFG_HIF_RX2_TO_TMU_QUE,
      CFG_HIF_RX3_TO_TMU_QUE,
      CFG_HIF_RX4_TO_TMU_QUE,
      CFG_HIF_RX5_TO_TMU_QUE,
      CFG_HIF_RX6_TO_TMU_QUE,
      CFG_HIF_RX7_TO_TMU_QUE,
      CFG_HIF_RX8_TO_TMU_QUE
    ));
  // 5 - HIF programmable DMA busrt size. Default : 128byte
  MDR_KX028_WriteAXI(AXI_HIF1_BASE_ADDR + AXI_HIF_DMA_BURST_SIZE_ADDR, CFG_HIF_DMA_BURST_Bytes);                     //{ 0x006400C8, 0x00000000 },    
}

void MDR_KX028_InitHIF_Ex(void)
{  
  // Timeout for BDP fetch/update, Data write/read.
  MDR_KX028_WriteAXI(AXI_HIF1_BASE_ADDR + AXI_HIF_TIMEOUT_REG, CFG_HIF_BDP_TIMEOUT);	                                //{ 0x00640010, 0xC92C3BCD },	//___Q no in spec    
  // Maximum no of packets accpeted by HIF TX for this channel when LTC pkt flow bit is enabled.
  MDR_KX028_WriteAXI(AXI_HIF1_BASE_ADDR + AXI_HIF_CH0_BASE_ADDR + AXI_HIF_CH_LTC_MAX_PKT, CFG_HIF_CH_LTC_MAX_PKT);	  //{ 0x006401E4, 0x00000004 },	//___Q no in spec
}


// ---------  CLASS Initialization -----------

void MDR_KX028_InitClassHW1(void)
{
  //  1 - LMEM first buffer header size value
  MDR_KX028_WriteAXI(AXI_CLASS_HW1_BASE_ADDR + AXI_CLASS_HDR_SIZE,                  CFG_CLASS1_LMEM_HDR_SIZE);                                       //{ 0x00620014, 0x00000030 },
  //  2 - Address of the Traffic Manager's input Queue
  MDR_KX028_WriteAXI(AXI_CLASS_HW1_BASE_ADDR + AXI_CLASS_TM_INQ_ADDR,               CBUS_BASE_ADDR | AXI_TMU_BASE_ADDR  | AXI_TMU_PHY_INQ_PKTPTR);  //{ 0x00620114, 0xC0600008 },
  //  3 - Address of BMU1, where buffer should be freed
  MDR_KX028_WriteAXI(AXI_CLASS_HW1_BASE_ADDR + AXI_CLASS_BMU1_BUF_FREE,             CBUS_BASE_ADDR | AXI_BMU1_BASE_ADDR | AXI_BMU_FREE_CTRL);       //{ 0x0062024C, 0xC0100034 },    
  // ? - Processor peripherals base address - TODO -?
  MDR_KX028_WriteAXI(AXI_CLASS_HW1_BASE_ADDR + AXI_CLASS_BUS_ACCESS_BASE_ADDR,      CFG_CLASS1_PER_BASE_ADDR);                                      //{ 0x00620258, 0x000000C2 },    
  //  4- special punt enable for all ports / global fall back bd entry
  MDR_KX028_WriteAXI(AXI_CLASS_HW1_BASE_ADDR + AXI_CLASS_GLOBAL_CFG,                AXI_CLASS_GLOBAL_CFG_FILL(CFG_CLASS1_SPEC_PUNT_ALL_EN, CFG_CLASS1_GL_FALLBACK_ENTRY)); //{ 0x006204AC, 0x00000001 },		//CLASS_GLOBAL_CFG
  MDR_KX028_WriteAXI(AXI_CLASS_HW1_BASE_ADDR + AXI_CLASS_GLOBAL_CFG1,               AXI_CLASS_GLOBAL_CFG1_FILL(CFG_CLASS1_GL_FALLBACK_ENTRY));                             //{ 0x006207E8, 0x00000000 },		//CLASS_GLOBAL_CFG1
  //  5 - Snoop MCAST address lower 32bit mask programming
  MDR_KX028_WriteAXI(AXI_CLASS_HW1_BASE_ADDR + AXI_CLASS_SNOOP_SPL_MCAST_MASK1_LSB, CFG_CLASS1_SNOOP_MCAST_MASK_LO);                //{ 0x00620378, 0xFFFFFFFF },
  //  6 - Snoop MCAST address upper 16bit mask programming
  MDR_KX028_WriteAXI(AXI_CLASS_HW1_BASE_ADDR + AXI_CLASS_SNOOP_SPL_MCAST_MASK1_MSB, CFG_CLASS1_SNOOP_MCAST_MASK_HI);                //{ 0x0062037C, 0x0000FFFF },
  //  7 - SPL multicast address1 lsb 32 bits, program DA lower 32bit address of PTP packets to punt to host control channel.
  MDR_KX028_WriteAXI(AXI_CLASS_HW1_BASE_ADDR + AXI_CLASS_SNOOP_SPL_MCAST_ADDR1_LSB, CFG_CLASS1_SNOOP_MCAST_ADDR_LO);                //{ 0x00620368, 0xC200000E },
  //  8 - SPL multicast address1 msb remaining 16 bits, program DA upper 16bits address of PTP packets to punt to host control channel.
  MDR_KX028_WriteAXI(AXI_CLASS_HW1_BASE_ADDR + AXI_CLASS_SNOOP_SPL_MCAST_ADDR1_MSB, CFG_CLASS1_SNOOP_MCAST_ADDR_HI);                //{ 0x0062036C, 0x00000180 },    
}  
  
void MDR_KX028_InitClassHW1_Ex(void)  
{  
  MDR_KX028_WriteAXI(AXI_CLASS_HW1_BASE_ADDR + AXI_CLASS_PUNT_COS,  AXI_CLASS_PUNT_COS_FILL(
        CFG_CLASS1_PUNT_COS_MGMT,
        CFG_CLASS1_PUNT_COS_L2,
        CFG_CLASS1_PUNT_COS_SA_MISS,
        CFG_CLASS1_PUNT_COS_SA_RELEARN,
        CFG_CLASS1_PUNT_COS_SA_ACTIVE,
        CFG_CLASS1_PUNT_COS_SNOOP,
        CFG_CLASS1_PUNT_COS_REQ
        ));		     //{ 0x006204C0, 0x0 }

  MDR_KX028_WriteAXI(AXI_CLASS_HW1_BASE_ADDR + AXI_CLASS_NPU_CTRL, AXI_CLASS_NPU_CTRL_FILL(
          CFG_HW1_PUNT_PORT,   	  
          CFG_HW1_Q_NUM_SEL,
          CFG_HW1_PUNT_DIS,
          CFG_HW1_Q_ETGS_COS,
          CFG_HW1_DISCARD_COS
          ));     //{ 0x006204FC, 0x01011000 },	//CLASS_NPU_CTRL
  
  MDR_KX028_WriteAXI(AXI_CLASS_HW1_BASE_ADDR + AXI_CLASS_NPU_CTRL1, AXI_CLASS_NPU_CTRL1_FILL(CFG_HW1_PUNT_PORT));	  //{ 0x006207F0, 0x00000100 },	//CLASS_NPU_CTRL1	HIF - port 16 (count to 0)
  MDR_KX028_WriteAXI(AXI_CLASS_HW1_BASE_ADDR + AXI_CLASS_INQ_AFULL_THRES, CFG_BUF_WATERMARK_AFULL);                 //{ 0x00620290, BUFFERS_WATERMARK_AFULL },	//CLASS_ING_AFULL_THRES
  MDR_KX028_WriteAXI(AXI_CLASS_HW1_BASE_ADDR + AXI_CLASS_USE_TMU_INQ,     CFG_HW1_USE_TMU_INQ);	                    //{ 0x00620250, 0x00000001 },	              //CLASS_USE_TMU_INQ
}


void MDR_KX028_InitClassHW2(void)
{
  MDR_KX028_WriteAXI(AXI_CLASS_HW2_BASE_ADDR + AXI_CLASS_HDR_SIZE,                  CFG_CLASS2_LMEM_HDR_SIZE); //{ 0x00770014, 0x00000030 },
  MDR_KX028_WriteAXI(AXI_CLASS_HW2_BASE_ADDR + AXI_CLASS_TM_INQ_ADDR,               CBUS_BASE_ADDR | AXI_TMU_BASE_ADDR  | AXI_TMU_PHY_INQ_PKTPTR);  //{ 0x00770114, 0xC0600008 },
  MDR_KX028_WriteAXI(AXI_CLASS_HW2_BASE_ADDR + AXI_CLASS_BMU1_BUF_FREE,             CBUS_BASE_ADDR | AXI_BMU2_BASE_ADDR | AXI_BMU_FREE_CTRL);       //{ 0x0077024C, 0xC0700034 },		//___Q must be 0xC070_0034 (BMU2)    
  MDR_KX028_WriteAXI(AXI_CLASS_HW2_BASE_ADDR + AXI_CLASS_BUS_ACCESS_BASE_ADDR,      CFG_CLASS2_PER_BASE_ADDR);                                      //{ 0x00770258, 0x000000C2 },    
  MDR_KX028_WriteAXI(AXI_CLASS_HW2_BASE_ADDR + AXI_CLASS_GLOBAL_CFG,                AXI_CLASS_GLOBAL_CFG_FILL(CFG_CLASS2_SPEC_PUNT_ALL_EN, CFG_CLASS2_GL_FALLBACK_ENTRY));  //{ 0x007704AC, 0x00000001 },		//CLASS_GLOBAL_CFG
  MDR_KX028_WriteAXI(AXI_CLASS_HW2_BASE_ADDR + AXI_CLASS_GLOBAL_CFG1,               AXI_CLASS_GLOBAL_CFG1_FILL(CFG_CLASS2_GL_FALLBACK_ENTRY));                              //{ 0x007707E8, 0x00000000 },		//CLASS_GLOBAL_CFG1    
  MDR_KX028_WriteAXI(AXI_CLASS_HW2_BASE_ADDR + AXI_CLASS_SNOOP_SPL_MCAST_MASK1_LSB, CFG_CLASS2_SNOOP_MCAST_MASK_LO); //{ 0x00770378, 0xFFFFFFFF },
  MDR_KX028_WriteAXI(AXI_CLASS_HW2_BASE_ADDR + AXI_CLASS_SNOOP_SPL_MCAST_MASK1_MSB, CFG_CLASS2_SNOOP_MCAST_MASK_HI); //{ 0x0077037C, 0x0000FFFF },
  MDR_KX028_WriteAXI(AXI_CLASS_HW2_BASE_ADDR + AXI_CLASS_SNOOP_SPL_MCAST_ADDR1_LSB, CFG_CLASS2_SNOOP_MCAST_ADDR_LO); //{ 0x00770368, 0xC200000E },
  MDR_KX028_WriteAXI(AXI_CLASS_HW2_BASE_ADDR + AXI_CLASS_SNOOP_SPL_MCAST_ADDR1_MSB, CFG_CLASS2_SNOOP_MCAST_ADDR_HI); //{ 0x0077036C, 0x00000180 },      
}

void MDR_KX028_InitClassHW2_Ex(void)
{
  MDR_KX028_WriteAXI(AXI_CLASS_HW2_BASE_ADDR + AXI_CLASS_PUNT_COS, AXI_CLASS_PUNT_COS_FILL(
        CFG_CLASS2_PUNT_COS_MGMT,
        CFG_CLASS2_PUNT_COS_L2,
        CFG_CLASS2_PUNT_COS_SA_MISS,
        CFG_CLASS2_PUNT_COS_SA_RELEARN,
        CFG_CLASS2_PUNT_COS_SA_ACTIVE,
        CFG_CLASS2_PUNT_COS_SNOOP,
        CFG_CLASS2_PUNT_COS_REQ
        ));   //{ 0x007704C0, 0x00000000 },		//CLASS_PUNT_COS

  MDR_KX028_WriteAXI(AXI_CLASS_HW2_BASE_ADDR + AXI_CLASS_NPU_CTRL, AXI_CLASS_NPU_CTRL_FILL(CFG_HW2_PUNT_PORT,	    //{ 0x007704FC, 0x01011000 },	//CLASS_NPU_CTRL
          CFG_HW2_Q_NUM_SEL,
          CFG_HW2_PUNT_DIS,
          CFG_HW2_Q_ETGS_COS,
          CFG_HW2_DISCARD_COS
          ));  
  MDR_KX028_WriteAXI(AXI_CLASS_HW2_BASE_ADDR + AXI_CLASS_NPU_CTRL1, AXI_CLASS_NPU_CTRL1_FILL(CFG_HW2_PUNT_PORT));	//{ 0x007707F0, 0x00000100 },	//CLASS_NPU_CTRL1	HIF - port 16 (count to 0)
  MDR_KX028_WriteAXI(AXI_CLASS_HW2_BASE_ADDR + AXI_CLASS_INQ_AFULL_THRES,  CFG_BUF_WATERMARK_AFULL);              //{ 0x00770290, BUFFERS_WATERMARK_AFULL },	//CLASS_ING_AFULL_THRES
  MDR_KX028_WriteAXI(AXI_CLASS_HW2_BASE_ADDR + AXI_CLASS_USE_TMU_INQ,      CFG_HW2_USE_TMU_INQ);	                //{ 0x00770250, 0x00000001 },	//CLASS_USE_TMU_INQ  
}


// ---------  TMU Initialization (TLITE) -----------

void MDR_KX028_InitTMU(void)
{
  // 1..16 - INQ address of PORT0 is EGPI1, etc
  MDR_KX028_WriteAXI(AXI_TMU_BASE_ADDR + AXI_TMU_PHY0_INQ_ADDR,  CBUS_BASE_ADDR | AXI_EGPI1_BASE_ADDR  | AXI_GPI_INQ_PKTPTR);	//{ 0x00600200, 0xC0780030 },	//EGPI1
  MDR_KX028_WriteAXI(AXI_TMU_BASE_ADDR + AXI_TMU_PHY1_INQ_ADDR,  CBUS_BASE_ADDR | AXI_EGPI2_BASE_ADDR  | AXI_GPI_INQ_PKTPTR);	//{ 0x00600204, 0xC0790030 },	//EGPI2
  MDR_KX028_WriteAXI(AXI_TMU_BASE_ADDR + AXI_TMU_PHY2_INQ_ADDR,  CBUS_BASE_ADDR | AXI_EGPI3_BASE_ADDR  | AXI_GPI_INQ_PKTPTR);	//{ 0x00600208, 0xC07A0030 },	//EGPI3
  MDR_KX028_WriteAXI(AXI_TMU_BASE_ADDR + AXI_TMU_PHY3_INQ_ADDR,  CBUS_BASE_ADDR | AXI_EGPI4_BASE_ADDR  | AXI_GPI_INQ_PKTPTR);	//{ 0x0060020C, 0xC07B0030 },	//EGPI4  
  MDR_KX028_WriteAXI(AXI_TMU_BASE_ADDR + AXI_TMU_PHY4_INQ_ADDR,  CBUS_BASE_ADDR | AXI_EGPI5_BASE_ADDR  | AXI_GPI_INQ_PKTPTR);	//{ 0x00600210, 0xC07C0030 },	//EGPI5 
  MDR_KX028_WriteAXI(AXI_TMU_BASE_ADDR + AXI_TMU_PHY5_INQ_ADDR,  CBUS_BASE_ADDR | AXI_EGPI6_BASE_ADDR  | AXI_GPI_INQ_PKTPTR);	//{ 0x00600214, 0xC07D0030 },	//EGPI6
  MDR_KX028_WriteAXI(AXI_TMU_BASE_ADDR + AXI_TMU_PHY6_INQ_ADDR,  CBUS_BASE_ADDR | AXI_EGPI7_BASE_ADDR  | AXI_GPI_INQ_PKTPTR);	//{ 0x00600218, 0xC07E0030 },	//EGPI7
  MDR_KX028_WriteAXI(AXI_TMU_BASE_ADDR + AXI_TMU_PHY7_INQ_ADDR,  CBUS_BASE_ADDR | AXI_EGPI8_BASE_ADDR  | AXI_GPI_INQ_PKTPTR);	//{ 0x0060021C, 0xC07F0030 },	//EGPI8
  MDR_KX028_WriteAXI(AXI_TMU_BASE_ADDR + AXI_TMU_PHY8_INQ_ADDR,  CBUS_BASE_ADDR | AXI_EGPI9_BASE_ADDR  | AXI_GPI_INQ_PKTPTR);	//{ 0x00600220, 0xC0800030 },	//EGPI9
  MDR_KX028_WriteAXI(AXI_TMU_BASE_ADDR + AXI_TMU_PHY9_INQ_ADDR,  CBUS_BASE_ADDR | AXI_EGPI10_BASE_ADDR | AXI_GPI_INQ_PKTPTR);	//{ 0x00600224, 0xC0810030 },	//EGPI10
  MDR_KX028_WriteAXI(AXI_TMU_BASE_ADDR + AXI_TMU_PHY10_INQ_ADDR, CBUS_BASE_ADDR | AXI_EGPI11_BASE_ADDR | AXI_GPI_INQ_PKTPTR);	//{ 0x00600228, 0xC0820030 },	//EGPI11
  MDR_KX028_WriteAXI(AXI_TMU_BASE_ADDR + AXI_TMU_PHY11_INQ_ADDR, CBUS_BASE_ADDR | AXI_EGPI12_BASE_ADDR | AXI_GPI_INQ_PKTPTR);	//{ 0x0060022C, 0xC0830030 },	//EGPI12
  MDR_KX028_WriteAXI(AXI_TMU_BASE_ADDR + AXI_TMU_PHY12_INQ_ADDR, CBUS_BASE_ADDR | AXI_EGPI13_BASE_ADDR | AXI_GPI_INQ_PKTPTR);	//{ 0x00600230, 0xC0840030 },	//EGPI13
  MDR_KX028_WriteAXI(AXI_TMU_BASE_ADDR + AXI_TMU_PHY13_INQ_ADDR, CBUS_BASE_ADDR | AXI_EGPI14_BASE_ADDR | AXI_GPI_INQ_PKTPTR);	//{ 0x00600234, 0xC0850030 },	//EGPI14
  MDR_KX028_WriteAXI(AXI_TMU_BASE_ADDR + AXI_TMU_PHY14_INQ_ADDR, CBUS_BASE_ADDR | AXI_EGPI15_BASE_ADDR | AXI_GPI_INQ_PKTPTR);	//{ 0x00600238, 0xC0860030 },	//EGPI15
  MDR_KX028_WriteAXI(AXI_TMU_BASE_ADDR + AXI_TMU_PHY15_INQ_ADDR, CBUS_BASE_ADDR | AXI_EGPI16_BASE_ADDR | AXI_GPI_INQ_PKTPTR);	//{ 0x0060023C, 0xC0870030 },	//EGPI16
  // 17 (modified) - Addr to access unknown packets through SlaveSPI - for tables learning
  MDR_KX028_WriteAXI(AXI_TMU_BASE_ADDR + AXI_TMU_PHY16_INQ_ADDR, CBUS_BASE_ADDR | CFG_TMU_PUNT_ADDR); //{ 0x00600240, CBUS_BASE_ADDR | AXI_NEW_PACKET_IN_LMEM_REG_ADDR },        //HGPI ADDRESS IN LMEM
  
  // 18 - Controls the direct/indirect access to context memory. 0 - indirect, 1 - direct  
  MDR_KX028_WriteAXI(AXI_TMU_BASE_ADDR + AXI_TMU_CNTX_ACCESS_CTRL, AXI_TMU_CNTX_ACCESS_CTRL_DIRECT); //{ 0x006002F0, 0x00000000 }, //INDIRECT ACCESS
  
  //  CONTEXT MEMORY INITIALISATION
  uint32_t queInd;
  uint32_t port;
  for (port = 0; port < AXI_CLASS_PORT_COUNT; port++)
    for (queInd = 0; queInd < AXI_TMU_PHY_QUEUE_COUNT; queInd++ )
    {
      // 19 - Select Queue
      MDR_KX028_WriteAXI( ( AXI_TMU_BASE_ADDR + AXI_TMU_PHY_QUEUE_SEL ), AXI_PHY_QUEUE_SEL_FILL(port, queInd));
      
      // 20 - Resetting current queue pointer.
      MDR_KX028_WriteAXI( AXI_TMU_BASE_ADDR + AXI_TMU_CURQ_PTR,         0x00000000 );
      // 21 - used to configure queue for either tail drop or wred drop.
      MDR_KX028_WriteAXI( AXI_TMU_BASE_ADDR + AXI_TMU_CURQ_PKT_CNT,     0x00000000 );
      // 22 - Resetting current queue drop count value.
      MDR_KX028_WriteAXI( AXI_TMU_BASE_ADDR + AXI_TMU_CURQ_DROP_CNT,    0x00000000 );
      // 23 - Resetting current queue transmitted packet count value.
      MDR_KX028_WriteAXI( AXI_TMU_BASE_ADDR + AXI_TMU_CURQ_TRANS_CNT,   0x00000000 );
      // 24 - Resetting current queue status value (not selecting any drop algorithm).
      MDR_KX028_WriteAXI( AXI_TMU_BASE_ADDR + AXI_TMU_CURQ_QSTAT,       0x00000000 );
      // 25 - Resetting HW probability table0 values.
      MDR_KX028_WriteAXI( AXI_TMU_BASE_ADDR + AXI_TMU_HW_PROB_CFG_TBL0, 0x00000000 );
      // 26 - Resetting HW probability table1 values.
      MDR_KX028_WriteAXI( AXI_TMU_BASE_ADDR + AXI_TMU_HW_PROB_CFG_TBL1, 0x00000000 );
      // clr for debug
      MDR_KX028_WriteAXI( AXI_TMU_BASE_ADDR + AXI_TMU_CURQ_DEBUG,       0x00000000 );
    }  
    
  // 27..43
  MDR_KX028_WriteAXI(AXI_TMU_BASE_ADDR + AXI_TMU_PHY0_TDQ_CTRL,  CFG_TMU_PHY_TDQ_CTRL);	//{ 0x006002A0, 0x0000000F },	//TMU PHY0 TDQ
  MDR_KX028_WriteAXI(AXI_TMU_BASE_ADDR + AXI_TMU_PHY1_TDQ_CTRL,  CFG_TMU_PHY_TDQ_CTRL);	//{ 0x006002A4, 0x0000000F },	//TMU PHY1 TDQ
  MDR_KX028_WriteAXI(AXI_TMU_BASE_ADDR + AXI_TMU_PHY2_TDQ_CTRL,  CFG_TMU_PHY_TDQ_CTRL);	//{ 0x006002A8, 0x0000000F },	//TMU PHY2 TDQ
  MDR_KX028_WriteAXI(AXI_TMU_BASE_ADDR + AXI_TMU_PHY3_TDQ_CTRL,  CFG_TMU_PHY_TDQ_CTRL);	//{ 0x006002AC, 0x0000000F },	//TMU PHY3 TDQ
  MDR_KX028_WriteAXI(AXI_TMU_BASE_ADDR + AXI_TMU_PHY4_TDQ_CTRL,  CFG_TMU_PHY_TDQ_CTRL);	//{ 0x006002B0, 0x0000000F },	//TMU PHY4 TDQ
  MDR_KX028_WriteAXI(AXI_TMU_BASE_ADDR + AXI_TMU_PHY5_TDQ_CTRL,  CFG_TMU_PHY_TDQ_CTRL);	//{ 0x006002B4, 0x0000000F },	//TMU PHY5 TDQ
  MDR_KX028_WriteAXI(AXI_TMU_BASE_ADDR + AXI_TMU_PHY6_TDQ_CTRL,  CFG_TMU_PHY_TDQ_CTRL);	//{ 0x006002B8, 0x0000000F },	//TMU PHY6 TDQ
  MDR_KX028_WriteAXI(AXI_TMU_BASE_ADDR + AXI_TMU_PHY7_TDQ_CTRL,  CFG_TMU_PHY_TDQ_CTRL);	//{ 0x006002BC, 0x0000000F },	//TMU PHY7 TDQ
  MDR_KX028_WriteAXI(AXI_TMU_BASE_ADDR + AXI_TMU_PHY8_TDQ_CTRL,  CFG_TMU_PHY_TDQ_CTRL);	//{ 0x006002C0, 0x0000000F },	//TMU PHY8 TDQ
  MDR_KX028_WriteAXI(AXI_TMU_BASE_ADDR + AXI_TMU_PHY9_TDQ_CTRL,  CFG_TMU_PHY_TDQ_CTRL);	//{ 0x006002C4, 0x0000000F },	//TMU PHY9 TDQ
  MDR_KX028_WriteAXI(AXI_TMU_BASE_ADDR + AXI_TMU_PHY10_TDQ_CTRL, CFG_TMU_PHY_TDQ_CTRL);	//{ 0x006002C8, 0x0000000F },	//TMU PHY10 TDQ
  MDR_KX028_WriteAXI(AXI_TMU_BASE_ADDR + AXI_TMU_PHY11_TDQ_CTRL, CFG_TMU_PHY_TDQ_CTRL);	//{ 0x006002CC, 0x0000000F },	//TMU PHY11 TDQ
  MDR_KX028_WriteAXI(AXI_TMU_BASE_ADDR + AXI_TMU_PHY12_TDQ_CTRL, CFG_TMU_PHY_TDQ_CTRL);	//{ 0x006002D0, 0x0000000F },	//TMU PHY12 TDQ
  MDR_KX028_WriteAXI(AXI_TMU_BASE_ADDR + AXI_TMU_PHY13_TDQ_CTRL, CFG_TMU_PHY_TDQ_CTRL);	//{ 0x006002D4, 0x0000000F },	//TMU PHY13 TDQ
  MDR_KX028_WriteAXI(AXI_TMU_BASE_ADDR + AXI_TMU_PHY14_TDQ_CTRL, CFG_TMU_PHY_TDQ_CTRL);	//{ 0x006002D8, 0x0000000F },	//TMU PHY14 TDQ
  MDR_KX028_WriteAXI(AXI_TMU_BASE_ADDR + AXI_TMU_PHY15_TDQ_CTRL, CFG_TMU_PHY_TDQ_CTRL);	//{ 0x006002DC, 0x0000000F },	//TMU PHY15 TDQ
  MDR_KX028_WriteAXI(AXI_TMU_BASE_ADDR + AXI_TMU_PHY16_TDQ_CTRL, CFG_TMU_PHY_TDQ_CTRL);	//{ 0x006002E0, 0x0000000F },	//TMU PHY16 TDQ (host)    
  // 44 - Address of BMU, where buffer should be freed in case of drop.  
  MDR_KX028_WriteAXI(AXI_TMU_BASE_ADDR + AXI_TMU_BMU_INQ_ADDR, CBUS_BASE_ADDR | AXI_BMU1_BASE_ADDR | AXI_BMU_FREE_CTRL);  //{ 0x00600100, 0xC0100034 },    
}

void MDR_KX028_InitTMU_Ex(void)
{
  //  Threshold point above which, RTL shows INQ fifo is full
  MDR_KX028_WriteAXI(AXI_TMU_BASE_ADDR + AXI_TMU_INQ_WATERMARK, CFG_BUF_WATERMARK_AFULL);                                 //{ 0x00600004, BUFFERS_WATERMARK_AFULL },	//TMU_INQ_WATERMARK
}

//=======================   Enable Blocks ====================
static void MDR_KX028_SetCtrlBMU_All(uint32_t regValue)
{
  MDR_KX028_WriteAXI(AXI_BMU1_BASE_ADDR + AXI_BMU_CTRL, regValue);   //{ 0x00100004, 0x00000001 },         /* BMU1 enable */
  MDR_KX028_WriteAXI(AXI_BMU2_BASE_ADDR + AXI_BMU_CTRL, regValue);   //{ 0x00700004, 0x00000001 },         /* BMU2 enable */
}

static void MDR_KX028_SetCtrlEGPI_All(uint32_t regValue)
{
  MDR_KX028_WriteAXI(AXI_EGPI1_BASE_ADDR  + AXI_GPI_CTRL,  regValue); //{ 0x00780004, 0x00000001 },         /* EGPI1 enable */
  MDR_KX028_WriteAXI(AXI_EGPI2_BASE_ADDR  + AXI_GPI_CTRL,  regValue); //{ 0x00790004, 0x00000001 },         /* EGPI2 enable */
  MDR_KX028_WriteAXI(AXI_EGPI3_BASE_ADDR  + AXI_GPI_CTRL,  regValue); //{ 0x007A0004, 0x00000001 },         /* EGPI3 enable */
  MDR_KX028_WriteAXI(AXI_EGPI4_BASE_ADDR  + AXI_GPI_CTRL,  regValue); //{ 0x007B0004, 0x00000001 },         /* EGPI4 enable */
  MDR_KX028_WriteAXI(AXI_EGPI5_BASE_ADDR  + AXI_GPI_CTRL,  regValue); //{ 0x007C0004, 0x00000001 },         /* EGPI5 enable */
  MDR_KX028_WriteAXI(AXI_EGPI6_BASE_ADDR  + AXI_GPI_CTRL,  regValue); //{ 0x007D0004, 0x00000001 },         /* EGPI6 enable */
  MDR_KX028_WriteAXI(AXI_EGPI7_BASE_ADDR  + AXI_GPI_CTRL,  regValue); //{ 0x007E0004, 0x00000001 },         /* EGPI7 enable */
  MDR_KX028_WriteAXI(AXI_EGPI8_BASE_ADDR  + AXI_GPI_CTRL,  regValue); //{ 0x007F0004, 0x00000001 },         /* EGPI8 enable */
  MDR_KX028_WriteAXI(AXI_EGPI9_BASE_ADDR  + AXI_GPI_CTRL,  regValue); //{ 0x00800004, 0x00000001 },         /* EGPI9 enable */
  MDR_KX028_WriteAXI(AXI_EGPI10_BASE_ADDR + AXI_GPI_CTRL,  regValue); //{ 0x00810004, 0x00000001 },         /* EGPI10 enable */
  MDR_KX028_WriteAXI(AXI_EGPI11_BASE_ADDR + AXI_GPI_CTRL,  regValue); //{ 0x00820004, 0x00000001 },         /* EGPI11 enable */
  MDR_KX028_WriteAXI(AXI_EGPI12_BASE_ADDR + AXI_GPI_CTRL,  regValue); //{ 0x00830004, 0x00000001 },         /* EGPI12 enable */
  MDR_KX028_WriteAXI(AXI_EGPI13_BASE_ADDR + AXI_GPI_CTRL,  regValue); //{ 0x00840004, 0x00000001 },         /* EGPI13 enable */
  MDR_KX028_WriteAXI(AXI_EGPI14_BASE_ADDR + AXI_GPI_CTRL,  regValue); //{ 0x00850004, 0x00000001 },         /* EGPI14 enable */
  MDR_KX028_WriteAXI(AXI_EGPI15_BASE_ADDR + AXI_GPI_CTRL,  regValue); //{ 0x00860004, 0x00000001 },         /* EGPI15 enable */
  MDR_KX028_WriteAXI(AXI_EGPI16_BASE_ADDR + AXI_GPI_CTRL,  regValue); //{ 0x00870004, 0x00000001 },         /* EGPI16 enable */
}

static void MDR_KX028_SetCtrlETGPI_All(uint32_t regValue)
{
  MDR_KX028_WriteAXI(AXI_ETGPI1_BASE_ADDR  + AXI_GPI_CTRL,  regValue);
  MDR_KX028_WriteAXI(AXI_ETGPI2_BASE_ADDR  + AXI_GPI_CTRL,  regValue);
  MDR_KX028_WriteAXI(AXI_ETGPI3_BASE_ADDR  + AXI_GPI_CTRL,  regValue);
  MDR_KX028_WriteAXI(AXI_ETGPI4_BASE_ADDR  + AXI_GPI_CTRL,  regValue);
  MDR_KX028_WriteAXI(AXI_ETGPI5_BASE_ADDR  + AXI_GPI_CTRL,  regValue);
  MDR_KX028_WriteAXI(AXI_ETGPI6_BASE_ADDR  + AXI_GPI_CTRL,  regValue);
  MDR_KX028_WriteAXI(AXI_ETGPI7_BASE_ADDR  + AXI_GPI_CTRL,  regValue);
  MDR_KX028_WriteAXI(AXI_ETGPI8_BASE_ADDR  + AXI_GPI_CTRL,  regValue);
  MDR_KX028_WriteAXI(AXI_ETGPI9_BASE_ADDR  + AXI_GPI_CTRL,  regValue);
  MDR_KX028_WriteAXI(AXI_ETGPI10_BASE_ADDR + AXI_GPI_CTRL,  regValue);
  MDR_KX028_WriteAXI(AXI_ETGPI11_BASE_ADDR + AXI_GPI_CTRL,  regValue);
  MDR_KX028_WriteAXI(AXI_ETGPI12_BASE_ADDR + AXI_GPI_CTRL,  regValue);
  MDR_KX028_WriteAXI(AXI_ETGPI13_BASE_ADDR + AXI_GPI_CTRL,  regValue);
  MDR_KX028_WriteAXI(AXI_ETGPI14_BASE_ADDR + AXI_GPI_CTRL,  regValue);
  MDR_KX028_WriteAXI(AXI_ETGPI15_BASE_ADDR + AXI_GPI_CTRL,  regValue);
  MDR_KX028_WriteAXI(AXI_ETGPI16_BASE_ADDR + AXI_GPI_CTRL,  regValue);
}

static void MDR_KX028_SetCtrlHGPI(uint32_t regValue)
{
  MDR_KX028_WriteAXI(AXI_HGPI_BASE_ADDR + AXI_GPI_CTRL, regValue);   //{ 0x00650004, 0x00000001 },         /* HGPI enable */    
}

static void MDR_KX028_SetCtrlCLASS_All(uint32_t regValue)
{
  MDR_KX028_WriteAXI(AXI_CLASS_HW1_BASE_ADDR + AXI_CLASS_TX_CTRL, regValue); //{ 0x00620004, 0x00000001 },         /* CLASS_HW1 enable */
  MDR_KX028_WriteAXI(AXI_CLASS_HW2_BASE_ADDR + AXI_CLASS_TX_CTRL, regValue); //{ 0x00770004, 0x00000001 },         /* CLASS_HW2 enable */
}

static void MDR_KX028_EnableEMACs(void)
{   
  MDR_KX028_WriteAXI(AXI_EMAC1_BASE_ADDR,  CFG_EMAC1_ENA_CTRL);  //{ 0x00660000, 0x0080001C },         /* EMAC1 enable */
  MDR_KX028_WriteAXI(AXI_EMAC2_BASE_ADDR,  CFG_EMAC2_ENA_CTRL);  //{ 0x00670000, 0x0080001C },         /* EMAC2 enable */	//Ext TSU timer port enable, RX enable,TX enable
  MDR_KX028_WriteAXI(AXI_EMAC3_BASE_ADDR,  CFG_EMAC3_ENA_CTRL);  //{ 0x00680000, 0x0080001C },         /* EMAC3 enable */	//Ext TSU timer port enable, RX enable,TX enable
  MDR_KX028_WriteAXI(AXI_EMAC4_BASE_ADDR,  CFG_EMAC4_ENA_CTRL);  //{ 0x00690000, 0x0080001C },         /* EMAC4 enable */	//Ext TSU timer port enable, RX enable,TX enable
  MDR_KX028_WriteAXI(AXI_EMAC5_BASE_ADDR,  CFG_EMAC5_ENA_CTRL);  //{ 0x006A0000, 0x0080001C },	        /* EMAC5 enable */  //Ext TSU timer port enable, RX enable,TX enable
  MDR_KX028_WriteAXI(AXI_EMAC6_BASE_ADDR,  CFG_EMAC6_ENA_CTRL);  //{ 0x006B0000, 0x0080001C },         /* EMAC6 enable */	//Ext TSU timer port enable, RX enable,TX enable
  MDR_KX028_WriteAXI(AXI_EMAC7_BASE_ADDR,  CFG_EMAC7_ENA_CTRL);  //{ 0x006C0000, 0x0080001C },         /* EMAC7 enable */	//Ext TSU timer port enable, RX enable,TX enable
  MDR_KX028_WriteAXI(AXI_EMAC8_BASE_ADDR,  CFG_EMAC8_ENA_CTRL);  //{ 0x006D0000, 0x0080001C },         /* EMAC8 enable */	//Ext TSU timer port enable, RX enable,TX enable
  MDR_KX028_WriteAXI(AXI_EMAC9_BASE_ADDR,  CFG_EMAC9_ENA_CTRL);  //{ 0x006E0000, 0x0080001C },         /* EMAC9 enable */	//Ext TSU timer port enable, RX enable,TX enable
  MDR_KX028_WriteAXI(AXI_EMAC10_BASE_ADDR, CFG_EMAC10_ENA_CTRL); //{ 0x006F0000, 0x0080001C },         /* EMAC10 enable */	//Ext TSU timer port enable, RX enable,TX enable
  MDR_KX028_WriteAXI(AXI_EMAC11_BASE_ADDR, CFG_EMAC11_ENA_CTRL); //{ 0x00760000, 0x0080001C },         /* EMAC11 enable */	//Ext TSU timer port enable, RX enable,TX enable
  MDR_KX028_WriteAXI(AXI_EMAC12_BASE_ADDR, CFG_EMAC12_ENA_CTRL); //{ 0x00710000, 0x0080001C },         /* EMAC12 enable */	//Ext TSU timer port enable, RX enable,TX enable
  MDR_KX028_WriteAXI(AXI_EMAC13_BASE_ADDR, CFG_EMAC13_ENA_CTRL); //{ 0x00720000, 0x0080001C },         /* EMAC13 enable */	//Ext TSU timer port enable, RX enable,TX enable
  MDR_KX028_WriteAXI(AXI_EMAC14_BASE_ADDR, CFG_EMAC14_ENA_CTRL); //{ 0x00730000, 0x0080001C },         /* EMAC14 enable */	//Ext TSU timer port enable, RX enable,TX enable
  MDR_KX028_WriteAXI(AXI_EMAC15_BASE_ADDR, CFG_EMAC15_ENA_CTRL); //{ 0x00740000, 0x0080001C },         /* EMAC15 enable */	//Ext TSU timer port enable, RX enable,TX enable
  MDR_KX028_WriteAXI(AXI_EMAC16_BASE_ADDR, CFG_EMAC16_ENA_CTRL); //{ 0x00750000, 0x0080001C },         /* EMAC16 enable */	//Ext TSU timer port enable, RX enable,TX enable
};



__STATIC_INLINE void MDR_KX028_EnableBMU(void)   { MDR_KX028_SetCtrlBMU_All(AXI_BMU_CTRL_EN_Msk); }
__STATIC_INLINE void MDR_KX028_EnableEGPI(void)  { MDR_KX028_SetCtrlEGPI_All(AXI_GPI_CTRL_EN_Msk); }
__STATIC_INLINE void MDR_KX028_EnableHGPI(void)  { MDR_KX028_SetCtrlHGPI(AXI_GPI_CTRL_EN_Msk); }
__STATIC_INLINE void MDR_KX028_EnableETGPI(void) { MDR_KX028_SetCtrlETGPI_All(AXI_GPI_CTRL_EN_Msk); }
__STATIC_INLINE void MDR_KX028_EnableClass(void) { MDR_KX028_SetCtrlCLASS_All(AXI_CLASS_TX_CTRL_EN_Msk); }

void MDR_KX028_EnableBlocks(void)
{
  MDR_KX028_WriteAXI( CFG_NEW_PACKET_IN_LMEM_ADDR, 0);    
  
  MDR_KX028_EnableBMU();      // 1,2 - by specification
  MDR_KX028_EnableEGPI();     // 3..18
  MDR_KX028_EnableHGPI();     // 19
  MDR_KX028_EnableETGPI();    // 20..35
  MDR_KX028_EnableClass();    // 36, 37
  MDR_KX028_EnableEMACs();    // 38..53
}


static bool AXI_IndirWaitCompleted(uint32_t readyMask,  uint32_t *status, uint32_t waitCyclesMax)
{
  while (--waitCyclesMax)
  {
    *status = MDR_KX028_ReadAXI(AXI_TMU_INDIRECT_ACCESS_CMD_REG);
    if ((*status & readyMask) == readyMask)
      return true;
  }
  return false;
}

//void MDR_KX028_M2_HostPort_InitTailDrop(uint16_t maxFrameInHostQueue, uint32_t waitCyclesMax)
void MDR_KX028_M2_TMU_InitTailDropGPI(MDR_KX028_GPI_e gpi, uint16_t maxFrameInHostQueue, uint32_t waitCyclesMax)
{
  uint32_t que, reg;
  uint32_t status;
      
  MDR_KX028_WriteAXI(AXI_TMU_BASE_ADDR + AXI_TMU_CNTX_ACCESS_CTRL, AXI_TMU_CNTX_ACCESS_CTRL_INDIRECT);

  for(que = 0; que < AXI_TMU_PHY_QUEUE_COUNT; que++)
    for (reg = 0; reg < AXI_TMU_IND_REG_COUNT; reg++)
    {
      MDR_KX028_WriteAXI( AXI_TMU_INDIRECT_ACCESS_ADDR_REG, AXI_TMU_INDIRECT_ACCESS_ADDR_FILL((uint8_t)gpi, que, reg));
              
      if (reg == AXI_TMU_IND_REG_QSTAT)
        MDR_KX028_WriteAXI( AXI_TMU_INDIRECT_ACCESS_DATA_REG, AXI_TMU_IND_REG_QSTAT_TAILDROP_FILL(0, maxFrameInHostQueue));
      else
        MDR_KX028_WriteAXI( AXI_TMU_INDIRECT_ACCESS_DATA_REG, 0 );

      MDR_KX028_WriteAXI(AXI_TMU_INDIRECT_ACCESS_CMD_REG, AXI_TMU_INDIRECT_ACCESS_CMD_WRITE | AXI_TMU_INDIRECT_ACCESS_CMD_START);
      AXI_IndirWaitCompleted(AXI_TMU_INDIRECT_ACCESS_CMD_DONE, &status, waitCyclesMax);          
    }
}



//  From demoboard
void MDR_KX028_SysSoftReset(MDR_KX028_DelayMs DelayFunc)
{
  //  TODO
  //1 - Disable EMAC RX
  //#define CFG_EMAC1_ENA_CTRL      AXI_EMAC_NETCTRL_RX_EN_Msk | AXI_EMAC_NETCTRL_TX_EN_Msk | AXI_EMAC_NETCTRL_MANAG_EN_Msk | AXI_EMAC_NETCTRL_TSU_EN_Msk
  
  //2 - Disable HIF TX DMA Engine By doing these steps, we are stopping traffic from external to NPU
  //3 - Wait for remaining BMU Count as zero This makes sure that there is no packet inside NPU
  //4 - Disable HIF RX DMA Engine
  
  //5 - Wait for 100us ( Resonable time , so that packets are send out to host)
  DelayFunc(MDR_KX028_RESET_DLEAY_MS);  
  //6 - Write Soft Reset bit of wsp global register
  MDR_KX028_WriteAXI(AXI_WSP_GLOBAL_BASE_ADDR + AXI_WSP_SYS_GENERIC_CONTROL, AXI_WSP_SYS_GENERIC_CONTROL_SOFT_RESET_Msk);
  //7 - Wait for 100us
  DelayFunc(MDR_KX028_RESET_DLEAY_MS);
  //8 - Clear Soft Reset
  MDR_KX028_WriteAXI(AXI_WSP_GLOBAL_BASE_ADDR + AXI_WSP_SYS_GENERIC_CONTROL, 0);
}


//===================   EMACs MDIO Control  ==========================
void MDR_KX028_MDIO_Init(MDR_KX028_EMAC_e emac, MDR_KX028_MDC_DIV divMDC)
{
  //  Set Clock Divider
  MDR_KX028_MaskAXI_def(MDR_KX028_AxiAddrEMAC[emac] + AXI_EMAC_NETCFG, AXI_EMAC_NETCFG_MDC_DIV_Msk, _VAL2FLD(AXI_EMAC_NETCFG_MDC_DIV, divMDC));    
  //  Enable MDC Output
  MDR_KX028_MaskAXI_def(MDR_KX028_AxiAddrEMAC[emac] + AXI_EMAC_NETCTRL, AXI_EMAC_NETCTRL_MANAG_EN_Msk, AXI_EMAC_NETCTRL_MANAG_EN_Msk);
}

//It takes about 2000 pclk cycles to complete, when MDC is set for pclk divide by 32 in the network configuration register
bool MDR_KX028_MDIO_Write(MDR_KX028_EMAC_e emac, uint16_t addrPHY, uint16_t addrRegInPHY, uint16_t value, uint32_t delayTicks_10us)
{
  uint32_t regValue = AXI_EMAC_MDIO_FILL_WRITE(addrPHY, addrRegInPHY, value, CFG_EMAC_PHY_CLAUSE_22);
  
  MDR_KX028_WriteAXI(MDR_KX028_AxiAddrEMAC[emac] + AXI_EMAC_MAN, regValue);  
  if (delayTicks_10us > 0)
    MDR_Delay(delayTicks_10us);
  
  uint32_t ackRegValue = MDR_KX028_ReadAXI(MDR_KX028_AxiAddrEMAC[emac] + AXI_EMAC_MAN);
  return ((regValue ^ ackRegValue) & (~AXI_EMAC_MDIO_VERIF_MSK)) == 0;
}
  
bool MDR_KX028_MDIO_Read(MDR_KX028_EMAC_e emac, uint16_t addrPHY, uint16_t addrRegInPHY, uint16_t *value, uint32_t delayTicks_10us)
{
  uint32_t regValue = AXI_EMAC_MDIO_FILL_READ(addrPHY, addrRegInPHY, CFG_EMAC_PHY_CLAUSE_22);
  
  MDR_KX028_WriteAXI(MDR_KX028_AxiAddrEMAC[emac] + AXI_EMAC_MAN, regValue);
  if (delayTicks_10us > 0)
    MDR_Delay(delayTicks_10us);
  
  uint32_t ackRegValue = MDR_KX028_ReadAXI(MDR_KX028_AxiAddrEMAC[emac] + AXI_EMAC_MAN);  
  
  bool rdOk = ((regValue ^ ackRegValue) & (~AXI_EMAC_MDIO_VERIF_MSK)) == 0;
  if (rdOk)
    *value = (uint16_t)ackRegValue;    
  return rdOk;
}

bool MDR_KX028_MDIO_Mask(MDR_KX028_EMAC_e emac, uint16_t addrPHY, uint16_t addrRegInPHY, uint16_t clrMask, uint16_t setMask, uint32_t delayTicks_10us)
{
  uint16_t regValue;
  if (MDR_KX028_MDIO_Read(emac, addrPHY, addrRegInPHY, &regValue, delayTicks_10us))
  {
    regValue &= ~clrMask;
    regValue |= setMask;
    return MDR_KX028_MDIO_Write(emac, addrPHY, addrRegInPHY, regValue, delayTicks_10us);
  }
  else
    return false;    
}


void MDR_KX028_InitAll_AfterEMAC(MDR_KX028_DelayMs DelayFunc, bool doExtraInit)
{
  MDR_KX028_EMAC_e emac; 
  for (emac = KX028_EMAC1; emac < KX028_EMAC_NUMS; ++emac)
  {
    if (doExtraInit)
      MDR_KX028_InitEMAC_ex(emac);
    MDR_KX028_InitEMAC_TSU(emac); 
    MDR_KX028_InitEMAC_GEM(emac);
  }
  //  Classif 1-2
  MDR_KX028_InitClassHW1();
  MDR_KX028_InitClassHW2();
  if (doExtraInit)
  {
    MDR_KX028_InitClassHW1_Ex();  
    MDR_KX028_InitClassHW2_Ex();
  }
  //  EGPI
  for (emac = KX028_EMAC1; emac < KX028_EMAC_NUMS; ++emac)
  {
    MDR_KX028_InitEGPI(emac);
    if (doExtraInit)
      MDR_KX028_InitEGPI_Ex(emac);  
  }
#if CFG_LEANR_BY_EMAC
  MDR_KX028_WriteAXI(AXI_TMU_BASE_ADDR + CFG_LEARN_TMU_INQ_ADDR,  CBUS_BASE_ADDR | CFG_NEW_PACKET_IN_LMEM_ADDR);
  MDR_KX028_WriteAXI( MDR_KX028_AxiAddrEGPI[CFG_LEARN_EMAC] + AXI_GPI_DTX_ASEQ, CFG_HGPI_DTX_ASEQ_CNT);                              //{ 0x00650050, 0x00000040 },  
#endif
  
  //  HGPI
  MDR_KX028_InitHGPI();
  if (doExtraInit)
    MDR_KX028_InitHGPI_Ex();
  //  ETGPI  
  for (emac = KX028_EMAC1; emac < KX028_EMAC_NUMS; ++emac)
  {
    MDR_KX028_InitETGPI(emac);
    if (doExtraInit)
      MDR_KX028_InitETGPI_Ex(emac);
  }
  //  TMU
  MDR_KX028_InitTMU();
  if (doExtraInit)
    MDR_KX028_InitTMU_Ex();
  //  HIF
  MDR_KX028_InitHIF();  
  if (doExtraInit)
    MDR_KX028_InitHIF_Ex();
}

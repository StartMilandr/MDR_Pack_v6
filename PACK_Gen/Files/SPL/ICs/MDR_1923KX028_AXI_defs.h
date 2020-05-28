#ifndef MDR_1923KX028_AXI_DEFS_H
#define MDR_1923KX028_AXI_DEFS_H

#include <stdint.h>


typedef enum {
    KX028_EMAC1 = 0,
    KX028_EMAC2,
    KX028_EMAC3,
    KX028_EMAC4,
    KX028_EMAC5,
    KX028_EMAC6,
    KX028_EMAC7,
    KX028_EMAC8,
    KX028_EMAC9,
    KX028_EMAC10,
    KX028_EMAC11,
    KX028_EMAC12,
    KX028_EMAC13,
    KX028_EMAC14,
    KX028_EMAC15,
    KX028_EMAC16,
    //  Count
    KX028_EMAC_NUMS
} MDR_KX028_EMAC_e;

#define AXI_CLASS_HOST_COUNT        1
#define AXI_CLASS_PORT_COUNT        (KX028_EMAC_NUMS + AXI_CLASS_HOST_COUNT) 


//  Внутренний адрес на шине:  AXI SLAVE ADDRESS is CBUS_BASE_ADDR + SLAVE BASE ADDRESS
//  SLAVE BASE ADDRESS - AXI адреса в данном файле
//  CBUS_BASE_ADDR - расширитель адреса на шине, необходим при записи адресов в регистры.
#define CBUS_BASE_ADDR    0xC0000000UL


typedef enum {
    KX028_ACT_FORWARD = 0,      // Normal forward, use forward_list of MAC entry
    KX028_ACT_FLOOD,            // Flood to all ports in bridge domain, use forward list of BD entry
    KX028_ACT_PUNT,             // Punt packet to host
    KX028_ACT_DISCARD,          // Discard this frame
    KX028_ACT_OVERRIDE,         // The action field is taken from vlan entry in case of vlan search success, if vlan search fails, it is taken from fallback bd entry
    KX028_ACT_FWD_MASK,         // Forward list is ANDed with vlan table forward list
    KX028_ACT_COS_DISCARD       // Packets matching with configured  cos values will be forwarded, remaining will be discarded. Added for AVB support.
} MDR_KX028_ACTION_e;


// ======================== Адресное пространство ведомого AXI  ========================
//  CSR - ControlStatusRegister

// -----------    BMU - менеджер буферизации данных   ----------------
#define AXI_BMU1_BASE_ADDR                       0x100000
#define AXI_BMU2_BASE_ADDR                       0x700000

#define AXI_BMU1_END_OFFSET                      0x10FFFF
#define AXI_BMU2_END_OFFSET                      0x70FFFF

  #define AXI_BMU_VERSION             0x00
    //  Reset = 32'h0
    //- bmu_id 15:0 R Read only register that contains the ID of the block
    //- bmu_version 23:16 R Read Only register that indicates the Version of the Block
    //- bmu_revision 31:24 R Read Only register that indicates the Revision of the Block
  #define AXI_BMU_CTRL                0x04 
    #define AXI_BMU_CTRL_EN_Msk             0x0001UL
    #define AXI_BMU_CTRL_RESET_Msk          0x0002UL
    //  Reset = 2'b01
    //- csr_bmu_en 0 R/W BMU Enable. This signal needs to be set to enable the BMU module
    //- csr_bmu_sw_rst 1 R/W BMU Reset. This signal is used to initiate soft reset of the BMU. This is a self clear signal. Software should
    //  only set this regsiter and should not attempt to clear it. Soft reset is mandatory to have the internal bitmap memory cleared at reset
  #define AXI_BMU_UCAST_CONFIG        0x08 
    #define AXI_BMU_UCAST_BUF_CNT_MAX       0x0800UL
    //  Reset = 16'h800
    //- csr_bmu_max_buf_cnt 15:0 R/W Maximum number of buffers that can be used. This number must be smaller than the hardware can support.
  #define AXI_BMU_UCAST_BASEADDR      0x0c 
    //  Reset = 32'h0
    //- csr_bmu_base_addr 31:0 R/W Base address of the Memory buffer for addresses. The least significant bits till the buffer size are invalid. 
    //  The base address needs to be aligned to max_buf_cnt * buf_size
  #define AXI_BMU_BUF_SIZE            0x10 
    #define AXI_BMU_BUF_SIZE_128            7  // 2^7 = 128 bytes
    //  Reset = 16'h7)
    //- csr_bmu_buf_size 15:0 R/W This indicates the buffer size of each of the buffers allocated and freed  
  #define AXI_BMU_BUF_CNT             0x14 
    //  Reset = 32'h0
    //- bmu_active_buf_cnt 15:0 R Count of the number of buffers occupied
    //- bmu_active_mcast_cnt 31:16 R Bmu Free error count. This is a free running counter on every error'd free. 
    //  (Freeing a buffer that is not allocated)  
  #define AXI_BMU_THRES               0x18 
    #define AXI_BMU_THRES_UCAST_MAX         AXI_BMU_UCAST_BUF_CNT_MAX 
    //  Reset = 32'h0800_0800
    //- csr_bmu_ucast_thres 15:0 R/W Threshold of number of Uni-Cast buffers to generate an Interrupt   
    //- csr_bmu_mcast_thres 31:16 R/W Threshold of number of Multi-Cast buffers to generate an Interrupt. This is reserved and writing to this register has no effect
  #define AXI_BMU_LOW_WATERMARK       0x50 
    //Reset = 16'h0
    //- csr_bmu_low_watermark 15:0 R/W CSR BMU Low Watermark
  #define AXI_BMU_HIGH_WATERMARK      0x54 
    //Reset = 16'hFFFF
    //-csr_bmu_high_watermark 15:0 R/W CSR BMU High Watermark
  #define AXI_BMU_MCAST_CNT           0x40 
    //  Reset = 3'h0
    //- csr_mcast_cnt 2:0 R/W csr_mcast_cnt. Reserved - read / write has no impact on the design
  #define AXI_BMU_REM_BUF_CNT         0x48 
    //  Reset = 16'h800
    //- bmu_rem_buf_cnt 15:0 R The number of buffers remaining in the BMU to be allocated. 
  #define AXI_BMU_INT_SRC             0x20 
    #define AXI_BMU_INT_SRC_GLOB_Msk          0x0001UL
    #define AXI_BMU_INT_SRC_Empty_Msk         0x0002UL
    #define AXI_BMU_INT_SRC_Full_Msk          0x0004UL
    #define AXI_BMU_INT_SRC_Thres_Msk         0x0008UL
    #define AXI_BMU_INT_SRC_FreeErr_Msk       0x0010UL
    #define AXI_BMU_INT_SRC_MCastEmpty_Msk    0x0020UL
    #define AXI_BMU_INT_SRC_MCastFull_Msk     0x0040UL
    #define AXI_BMU_INT_SRC_MCastThres_Msk    0x0080UL
    #define AXI_BMU_INT_SRC_MCastFreeErr_Msk  0x0100UL
    #define AXI_BMU_INT_SRC_ALL               0x01FFUL
    //  Reset = 9'h0
    //- bmu_int 0 BMU Global Interrupt Status 
    //- bmu_empty_int 1 BMU Buffer Empty Interrupt. Initially BMU Empty Interrupt will be generated, 
    //  incase if interrupt enables are set, then this register will hold a value of 9'h1, after reset.
    //- bmu_full_int 2 BMU Buffer Full Interrupt
    //- bmu_thres_int 3 BMU Buffer Threshold Interrupt 
    //- bmu_free_err_int 4 INT This interrupt is generated when a free is generated for an already free buffer
    //- bmu_mcast_empty_int 5 BMU MCAST Buffer Empty Interrupt. Reserved - Always reads '0'
    //- bmu_mcast_full_int 6 BMU MCAST Buffer Full Interrupt. ReservedAlways reads '0' 
    //- bmu_mcast_thres_int 7 BMU MCAST Buffer Threshold Interrupt. Reserved - Always reads '0'
    //- bmu_mcast_free_err_int 8 BMU MCAST free error interrupt is generated when a free is generated for an already free buffer. Reserved - Always reads '0'
  #define AXI_BMU_INT_ENABLE          0x24 
    #define AXI_BMU_INT_Ena_GLOB_Msk          0x0001UL
    #define AXI_BMU_INT_Ena_Empty_Msk         0x0002UL
    #define AXI_BMU_INT_Ena_Full_Msk          0x0004UL
    #define AXI_BMU_INT_Ena_Thres_Msk         0x0008UL
    #define AXI_BMU_INT_Ena_FreeErr_Msk       0x0010UL
    #define AXI_BMU_INT_Ena_MCastEmpty_Msk    0x0020UL
    #define AXI_BMU_INT_Ena_MCastFull_Msk     0x0040UL
    #define AXI_BMU_INT_Ena_MCastThres_Msk    0x0080UL
    #define AXI_BMU_INT_Ena_MCastFreeErr_Msk  0x0100UL
    #define AXI_BMU_INT_EnaALL                0x01FFUL
    #define AXI_BMU_INT_DisALL                0x0000UL
    //  Reset = 9'h0
    //- bmu_int_en 0 Master Enable for BMU interrupt
    //- bmu_empty_int_en 1 Enable for the single cast buffer Empty Interrupt
    //- bmu_full_int_en 2 Enable for the single cast buffer full Interrupt
    //- bmu_thres_int_en 3 Enable for the single cast buffer Threshold Interrupt
    //- bmu_free_err_int_en 4 Enable for the when single cast Buffer is freed again
    //- bmu_mcast_empty_int_en 5 Enable for the Multi cast buffer Empty Interrupt. Reserved - Has no effect on Interrupts
    //- bmu_mcast_full_int_en 6 Enable for the Multi cast buffer full Interrupt. Reserved - Has no effect on Interrupts
    //- bmu_mcast_thres_int_en 7 Enable for the Multi cast buffer Threshold Interrupt. Reserved - Has no effect on Interrupts
    //- bmu_mcast_free_err_int_en 8 INT_EN Enable for the when Multi cast Buffer is freed again.
  #define AXI_BMU_ALLOC_CTRL          0x30 
    //  Reset = 32'h0000_0380
    //- ucast_alloc_addr 31:0 R This register is used to allocate a buffer. 
    //  A read of this address allocates a buffer. The read data is the buffer that is allocated. 
    //  A write to this register should be avoided. After system reset this register holds a value
    //  of 32'h0000_0380 and after bmu sw reset, this holds a value of 32'h0010_0380.
  #define AXI_BMU_FREE_CTRL           0x34 
    //  Reset = 32'h0
    //- ucast_free_addr 31:0 R/W This register is used to free a buffer. A write to this register frees the buffer. 
    //  The free location is indicated by the write data. A read to this location should be avoided
  #define AXI_BMU_MCAST_ALLOC_CTRL    0x44 
    //  Reset = 32'h0
    //- mcast_alloc_addr 31:0 R/W A write to this location will adjust the instance count of the buffer that is already allocated. 
    //  The write data to indicate the address to allocate and the reference count to increase. 
    //  The LSB bits of the value written indicates the reference count. 
    //  (For example - addr[4:0] for MCAST_LG2 = 5 option). The LSB bits are by default '0' as min buf size is 64 bytes (and aligned)
  #define AXI_BMU_FREE_ERROR_ADDR     0x38 
    //  Reset = 32'h0
    //- bmu_free_err_addr 31:0 R Address of the buffer that is freed more times than allocated 
    // (This is the same register across mcast and unicast)
  #define AXI_BMU_CURR_BUF_CNT        0x3c 
    //  Reset = 16'h0
    //- bmu_curr_buf_cnt 15:0 R Indicates number of buffers allocated currently
  #define AXI_BMU_MAS0_BUF_CNT        0x60
  #define AXI_BMU_MAS1_BUF_CNT        0x64
  #define AXI_BMU_MAS2_BUF_CNT        0x68
  #define AXI_BMU_MAS3_BUF_CNT        0x6C
  #define AXI_BMU_MAS4_BUF_CNT        0x70
  #define AXI_BMU_MAS5_BUF_CNT        0x74
  #define AXI_BMU_MAS6_BUF_CNT        0x78
  #define AXI_BMU_MAS7_BUF_CNT        0x7C
  #define AXI_BMU_MAS8_BUF_CNT        0x80
  #define AXI_BMU_MAS9_BUF_CNT        0x84
  #define AXI_BMU_MAS10_BUF_CNT       0x88
  #define AXI_BMU_MAS11_BUF_CNT       0x8C
  #define AXI_BMU_MAS12_BUF_CNT       0x90
  #define AXI_BMU_MAS13_BUF_CNT       0x94
  #define AXI_BMU_MAS14_BUF_CNT       0x98
  #define AXI_BMU_MAS15_BUF_CNT       0x9C
  #define AXI_BMU_MAS16_BUF_CNT       0xA0
  #define AXI_BMU_MAS17_BUF_CNT       0xA4
  #define AXI_BMU_MAS18_BUF_CNT       0xA8
  #define AXI_BMU_MAS19_BUF_CNT       0xAC
  #define AXI_BMU_MAS20_BUF_CNT       0xB0
  #define AXI_BMU_MAS21_BUF_CNT       0xB4
  #define AXI_BMU_MAS22_BUF_CNT       0xB8
  #define AXI_BMU_MAS23_BUF_CNT       0xBC
  #define AXI_BMU_MAS24_BUF_CNT       0xC0
  #define AXI_BMU_MAS25_BUF_CNT       0xC4
  #define AXI_BMU_MAS26_BUF_CNT       0xC8
  #define AXI_BMU_MAS27_BUF_CNT       0xCC
  #define AXI_BMU_MAS28_BUF_CNT       0xD0
  #define AXI_BMU_MAS29_BUF_CNT       0xD4
  #define AXI_BMU_MAS30_BUF_CNT       0xD8
  #define AXI_BMU_MAS31_BUF_CNT       0xDC
    //  Reset = 16'h0
    //- bmu_mas0_buf_cnt 15:0 R Indicates the buffers occupied by Master-0
    //  ...
    //- bmu_mas31_buf_cnt 15:0 R Indicates the buffers occupied by Master-17
  #define AXI_BMU_DEBUG_BUS           0xE0 
    //  Reset = 16'h0
    //- csr_bmu_db_g_bus 15:0 R BMU Debug Bus signals, bmu_buf_thres, bmu_buf_empty, bmu_buf_full, bcnt_cstate, 
    //  free_cstate, alloc_cstate, rst_cstate
  #define AXI_BMU_INT_MEM_ACCESS      0x100 
    //  Reset = 32'h0
    //- ucast_int_mem 31:0 R/W This provides access to the internal memory. It is used only for debug purpose. Memory data [31:0]
  #define AXI_BMU_INT_MEM_ACCESS2     0x104 
    //  Reset = 8'h0
    //- ucast_int_mem2 7:0 R/W This provides access to the internal memory. It is used only for debug purpose. Memory data [39:32]



// -------------- LMEM - локальная память ------------------------
#define AXI_LMEM0_BASE_ADDR                      0x200000
#define AXI_LMEM1_BASE_ADDR                      0x280000
#define AXI_LMEM2_BASE_ADDR                      0x300000
#define AXI_LMEM3_BASE_ADDR                      0x380000
#define AXI_LMEM4_BASE_ADDR                      0x400000
#define AXI_LMEM5_BASE_ADDR                      0x480000
#define AXI_LMEM6_BASE_ADDR                      0x500000
#define AXI_LMEM7_BASE_ADDR                      0x580000

#define AXI_LMEM0_END_OFFSET                     0x27FFFF
#define AXI_LMEM1_END_OFFSET                     0x2FFFFF
#define AXI_LMEM2_END_OFFSET                     0x37FFFF
#define AXI_LMEM3_END_OFFSET                     0x3FFFFF 
#define AXI_LMEM4_END_OFFSET                     0x47FFFF
#define AXI_LMEM5_END_OFFSET                     0x4FFFFF
#define AXI_LMEM6_END_OFFSET                     0x57FFFF
#define AXI_LMEM7_END_OFFSET                     0x5FFFFF

  //  Адрес с которого читается указатель на входной фрейм по шине AXI
  #define AXI_NEW_PACKET_IN_LMEM_REG_ADDR_DEF	   0x0043FFA0UL

  //  Маска адреса считанного из AXI_NEW_PACKET_IN_LMEM_REG_ADDR_DEF
  #define KX028_FRAME_PTR_ADDR_MSK               0xFFFFFF80
  //  Смещения относительно адреса считанного из AXI_NEW_PACKET_IN_LMEM_REG_ADDR_DEF
  #define KX028_FRAME_SIZE_ADDR_OFFS            0x10
    #define KX028_FRAME_SIZE_MSK                  0xFFFF

  #define KX028_FRAME_PR_ADDR_OFFS              0x20
    #define KX028_FRAME_PR_CTRL_OFFS              0
    #define KX028_FRAME_PR_CTRL_MSK               0xFF
    #define KX028_FRAME_PR_PORT_OFFS              8
    #define KX028_FRAME_PR_PORT_MSK               0x0F
    #define KX028_FRAME_PR_PUNT_OFFS              16
    #define KX028_FRAME_PR_PUNT_MSK               0xFFFF
    
    //  Bits of KX028_FRAME_PR_CTRL_MSK
    #define KX028_FRAME_CTRL_FP_RX_TS_REPORT_EN    ( 1 << 4 )
    #define KX028_FRAME_CTRL_FP_PUNT_VALID         ( 1 << 5 )
    
    // Punt reason codes of KX028_FRAME_PR_PORT_MSK
    #define KX028_FRAME_PUNT_L2_SPECIAL            ( 1 << 0 )   // L2 protocol frame (e.g. STP BPDU)
    #define KX028_FRAME_PUNT_SA_MISS               ( 1 << 1 )   // SA miss in the MAC table, need to learn MAC
    #define KX028_FRAME_PUNT_SA_RELEARN            ( 1 << 2 )   // SA found on different port, need to relearn MAC
    #define KX028_FRAME_PUNT_SA_IS_ACTIVE          ( 1 << 3 )   // SA is active, need to set Fresh bit to zero
    #define KX028_FRAME_PUNT_SNOOP_UPPER           ( 1 << 4 )   // Upper layer protocol snoop
    #define KX028_FRAME_PUNT_REQ                   ( 1 << 5 )
    #define KX028_FRAME_PUNT_MGMT                  ( 1 << 6 )
    #define KX028_FRAME_PUNT_IGMP                  ( 1 << 7 )
    #define KX028_FRAME_PUNT_FLOOD                 ( 1 << 8 )
    #define KX028_FRAME_PUNT_PARSE                 ( 1 << 9 )    
    

// ----------------------   TMU - Traffic Management Unit -----------------------
#define AXI_TMU_BASE_ADDR                        0x600000
#define AXI_TMU_END_OFFSET                       0x60FFFF


  #define AXI_TMU_VERSION             0x00
    //  Reset = 32'h10011
    //- tmu_id 15:0 R Read only register that contains the ID of the block
    //- tmu_version 23:16 R Read Only register that indicates the Version of the Block
    //- tmu_revision 31:24 R Read Only register that indicates the Revision of the Block
  #define AXI_TMU_INQ_WATERMARK       0x04 
    //  Reset = 10'h3ff
    //- csr_inq_watermark 9:0 R/W threshold point above which, RTL shows INQ fifo is full.
  #define AXI_TMU_PHY_INQ_PKTPTR      0x08 
    //  Reset = 32'h0
    //- csr_phy_inq_pktptr 31:0 R/W Classifier (or Host) writes packet pointer to this address. 
    //  This will be a blocking request, if the queue is full. However queuing discipline will clear the buffers and free them.
  #define AXI_TMU_PHY_INQ_PKTINFO     0x0c 
    //  Reset = 32'h0
    //- csr_phy_inq_pktinfo 31:0 R/W Classifier (or Host) writes packet length to this address. 
    //  This will be a blocking request, if the queue is full. 
    //  However queuing discipline will clear the buffers and free them. 
    //  It is essential that the master does an INCR (2) to write to this register and the previous one. 
    //  It needs to be a locked access write. All masters accessing these registers in WSP perform INCR (2) Accesses
  #define AXI_TMU_PHY_INQ_STAT        0x10 
    //  Reset = 32'h0
    //- tmu_phy_inq_stat 31:0 R shows INQ fifo count and wr/rd address;{tmu_inq_fifo_cnt, inq_rd_ptr(8), inq_wr_ptr(8)}

  #define AXI_PHY_QUEUE_SEL           0x34 
    //  Reset = 12'b0
    //- csr_queue_sel 2:0 R/W Direct Access; NA for NPU_AVB; 
    //- csr_phy_sel 12:8 R/W Direct Access; NA for NPU_AVB;   
    //  One has to write this register with PHY_NUM and QNUM to configure respective queue of that phy. 
    //  For example to configure hardware drop probablity table of a particular queue of a
    //  particular phy, first step should be to write phy_num and queue_num to this register and then whatever is written to
    //  CFG0-CFG3 will be written in probablity table of that queue for configured phy
  #define AXI_TMU_CURQ_PTR            0x38 
    //  Reset = 32'b0
    //- csr_curq_ptr 31:0 R/W Direct Access; NA for NPU_AVB; used to configure queue for either tail drop or wred drop. 
  #define AXI_MU_CURQ_PKT_CNT         0x3c 
    //  Reset = 32'b0
    //- csr_pkt_cnt 31:0 R/W Direct Access; NA for NPU_AVB; used to configure queue for either tail drop or wred drop.
  #define AXI_TMU_CURQ_DROP_CNT       0x40 
    //  Reset = 32'b0
    //- csr_drop_cnt 31:0 R/W Direct Access; NA for NPU_AVB; used to configure queue for either tail drop or wred drop.
  #define AXI_TMU_CURQ_TRANS_CNT      0x44 
    //  Reset = 32'b0
    //- csr_trans_cnt 31:0 R/W Direct Access; NA for NPU_AVB; used to configure queue for either tail drop or wred drop.
  #define AXI_TMU_CURQ_QSTAT          0x48 
    //  Reset = 32'b0
    //- csr_qstat 31:0 R/W Direct Access; NA for NPU_AVB; used to configure queue for either tail drop or wred drop.
  #define AXI_TMU_HW_PROB_CFG_TBL0    0x4c 
    //  Reset = 32'b0
    //- csr_prob_cfg_tbl0 31:0 R/W Direct Access; NA for NPU_AVB; used to configure queue for either tail drop or wred drop.
  #define AXI_TMU_HW_PROB_CFG_TBL1    0x50 
    //  Reset = 32'b0
    //- csr_prob_cfg_tbl1 31:0 R/W Direct Access;NA for NPU_AVB;used to configure queue for either tail drop or wred drop.
  #define AXI_TMU_CURQ_DEBUG          0x54 
    //  Reset = 32'b0
    //- csr_curq_debug 31:0 R/W Direct Access;NA for NPU_AVB;used to configure queue for either tail drop or wred drop.
  #define AXI_TMU_CTRL                0xe0 
    //  Reset = 32'b0
    //- csr_tmu_ctrl 31:0 R/W controlls the reset for multiple blocks; 0 --> S/W reset of tlite module
  #define AXI_TMU_BMU_INQ_ADDR        0x100 
    //  Reset = 32'b0
    //- csr_bmu_inq_addr 31:0 R/W Address of BMU, where buffer should be freed in case of drop.  
  #define AXI_TMU_AFULL_THRES         0x11c 
    //  Reset = 16'h640
    //- csr_afull_thres 15:0 R/W Controlls the LLM aful threshold. As of now not used
  #define AXI_TMU_BMU_BUF_SIZE        0x144 
    //  Reset = 16'h800
    //- csr_bmu_buf_size 15:0 R/W DDR BMU buffer size. Not applicable for NPU_AVB
  #define AXI_TMU_MAX_BUF_CNT         0x148 
    //  Reset = 32'h8
    //- csr_max_buf_cnt 31:0 R/W Not applicable for NPU_AVB
  #define AXI_TMU_TEQ_CTRL            0x14C 
    //  Reset = 2'b1
    //- csr_llm_en 0 R/W enables the llm in teq module 
    //- csr_drop_efifo_full 1 R/W setting this bit would result in dropping of packets in TEQ, if the llm becomes full
  #define AXI_TMU_DDR_DATA_OFFSET     0x16C 
    //  Reset = 9'h100
    //- csr_ddr_data_offset 8:0 R/W Not applicable for NPU_AVB
  #define AXI_TMU_LMEM_BUF_SIZE       0x170 
    //  Reset = 16'h80
    //- csr_lmem_buf_size 15:0 R/W LMEM buffer size
  #define AXI_TMU_LMEM_DATA_OFFSET    0x174 
    //  Reset = 9'h10
    //- csr_lmem_data_offset 8:0 R/W data offset of buffer structure
  #define AXI_TMU_LMEM_BASE_ADDR      0x178 
    //  Reset = 32'h0
    //- csr_lmem_base_addr 31:0 R/W not used
  #define AXI_TMU_PHY0_INQ_ADDR       0x200 
  #define AXI_TMU_PHY1_INQ_ADDR       0x204
  #define AXI_TMU_PHY2_INQ_ADDR       0x208
  #define AXI_TMU_PHY3_INQ_ADDR       0x20c
  #define AXI_TMU_PHY4_INQ_ADDR       0x210
  #define AXI_TMU_PHY5_INQ_ADDR       0x214
  #define AXI_TMU_PHY6_INQ_ADDR       0x218
  #define AXI_TMU_PHY7_INQ_ADDR       0x21c
  #define AXI_TMU_PHY8_INQ_ADDR       0x220
  #define AXI_TMU_PHY9_INQ_ADDR       0x224
  #define AXI_TMU_PHY10_INQ_ADDR      0x228
  #define AXI_TMU_PHY11_INQ_ADDR      0x22c
  #define AXI_TMU_PHY12_INQ_ADDR      0x230
  #define AXI_TMU_PHY13_INQ_ADDR      0x234
  #define AXI_TMU_PHY14_INQ_ADDR      0x238
  #define AXI_TMU_PHY15_INQ_ADDR      0x23c
  #define AXI_TMU_PHY16_INQ_ADDR      0x240
    //  Reset = 32'b0
    //- csr_phy0_inq_addr 31:0 R/W INQ address of Egress port0
    //  ...
    //- csr_phy16_inq_addr 31:0 R/W INQ address of Egress port0
  #define AXI_TMU_PHY0_TDQ_IIFG_CFG   0x250 
  #define AXI_TMU_PHY1_TDQ_IIFG_CFG   0x254
  #define AXI_TMU_PHY2_TDQ_IIFG_CFG   0x258
  #define AXI_TMU_PHY3_TDQ_IIFG_CFG   0x25c
  #define AXI_TMU_PHY4_TDQ_IIFG_CFG   0x260
  #define AXI_TMU_PHY5_TDQ_IIFG_CFG   0x264
  #define AXI_TMU_PHY6_TDQ_IIFG_CFG   0x268
  #define AXI_TMU_PHY7_TDQ_IIFG_CFG   0x26c
  #define AXI_TMU_PHY8_TDQ_IIFG_CFG   0x270
  #define AXI_TMU_PHY9_TDQ_IIFG_CFG   0x274
  #define AXI_TMU_PHY10_TDQ_IIFG_CFG  0x278
  #define AXI_TMU_PHY11_TDQ_IIFG_CFG  0x27c
  #define AXI_TMU_PHY12_TDQ_IIFG_CFG  0x280
  #define AXI_TMU_PHY13_TDQ_IIFG_CFG  0x284
  #define AXI_TMU_PHY14_TDQ_IIFG_CFG  0x288
  #define AXI_TMU_PHY15_TDQ_IIFG_CFG  0x28c
  #define AXI_TMU_PHY16_TDQ_IIFG_CFG  0x290
    //  Reset = 8'b0)
    //- csr_phy0_tdq_iifg_cfg 7:0 R/W IFG value of Egress port0
  #define AXI_TMU_PHY0_TDQ_CTRL       0x2A0 
  #define AXI_TMU_PHY1_TDQ_CTRL       0x2A4
  #define AXI_TMU_PHY2_TDQ_CTRL       0x2A8
  #define AXI_TMU_PHY3_TDQ_CTRL       0x2AC
  #define AXI_TMU_PHY4_TDQ_CTRL       0x2B0
  #define AXI_TMU_PHY5_TDQ_CTRL       0x2B4
  #define AXI_TMU_PHY6_TDQ_CTRL       0x2B8
  #define AXI_TMU_PHY7_TDQ_CTRL       0x2BC
  #define AXI_TMU_PHY8_TDQ_CTRL       0x2C0
  #define AXI_TMU_PHY9_TDQ_CTRL       0x2C4
  #define AXI_TMU_PHY10_TDQ_CTRL      0x2C8
  #define AXI_TMU_PHY11_TDQ_CTRL      0x2CC
  #define AXI_TMU_PHY12_TDQ_CTRL      0x2D0
  #define AXI_TMU_PHY13_TDQ_CTRL      0x2D4
  #define AXI_TMU_PHY14_TDQ_CTRL      0x2D8
  #define AXI_TMU_PHY15_TDQ_CTRL      0x2DC
  #define AXI_TMU_PHY16_TDQ_CTRL      0x2E0
    //  Reset = 32'hF
    //- csr_phy0_tdq_ctrl 31:0 R/W 
    //  0-->shp_clk_cntrl_en 
    //  1-->hw_en for tdq_sch_shaper,
    //  3:2:--> for enabling the schedulers;
    //  4-->allw_tdq_prog(Read only)
    #define AXI_TMU_PHY_TDQ_SHAPER_CLK_EN_Msk   0x0001UL
    #define AXI_TMU_PHY_TDQ_SHAPER_HW_EN_Msk    0x0002UL
    #define AXI_TMU_PHY_TDQ_SCHDLR_EN_Msk       0x000CUL
    
    #define AXI_TMU_PHY_TDQ_EN_ALL              0x000FUL

    
  #define AXI_TMU_CNTX_ACCESS_CTRL    0x2F0 
    //  Reset = 1'b0
    //- csr_cntx_access_ctrl 0 R/W controlls the direct/indirect access to context memory, 
    //  0 --> indirect,
    //  1 --> direct. SW should only use indirect access
    #define AXI_TMU_CNTX_ACCESS_CTRL_INDIRECT   0
    #define AXI_TMU_CNTX_ACCESS_CTRL_DIRECT     1
  #define AXI_TMU_CNTX_ADDR           0x2F4 
    //  Reset = 20'b0
    //- csr_cntx_ind_addr 15:0 R/W write the context memory address to this register.
    //  Per PHY context memory of 64 is devided to have 8 registers per Queue with Q0 registers occupying
    //  0-7 locations and Q7 occupying 56:63. 
    //  Each Queue has following registers 
    //  <0: {curQ_head_ptr, curQ_tail_ptr} 
    //  <1: curQ_pkt_cnt 
    //  <2: curQ_drop_cnt 
    //   3: curQ_trans_cnt
    //   4: {curQ_Qmax, curQ_Qmin, curQ_cfg}
    //   5: curQ_hw_prob_cfg_tbl0
    //   6: curQ_hw_prob_cfg_tbl1 
    //   7: curQ_dbg
    //- csr_cntx_ind_phy_no 20:16 R/W Phy no field
  #define AXI_TMU_CNTX_DATA           0x2F8 
    //  Reset = 32'b0
    //- csr_cntx_ind_data 31:0 R/W it will have the read/write data based on the command
  #define AXI_TMU_CNTX_CMD            0x2FC 
    //  Reset = 3'b0
    //- csr_cntx_ind_cmd   0 R/W 0--> for read, 1--> for write
    //- csr_cntx_ind_start 1 R/W write 1 to start the context access
    //- csr_cntx_ind_done  2 R context access operation done signal; poll for this bit for access complition
  #define AXI_TMU_DBG_BUS_TOP         0x300 
    //  Reset = NA
    //- csr_dbg_bus_top 31:0 R dbg_bus_mtr(6), winner_c_mtr(NUM_PHYS_LG2), dbg_bus_rclm(3), winner_c_rclm(NUM_PHYS_LG2)
  #define AXI_TMU_DBG_BUS_PP0         0x304 
    //  Reset = NA
    //- csr_dbg_bus_pp0 31:0 R debug bus;
    //  12:0-->{enQ_state(12:9),inq_lbuf_valid(8),phy_queue_hd_stat(7:0)};
    //  24:13-->{tdq_state(23:21),shp_status(20:17),winner_queue(16:14),phy_sch_result(13)};28:25{qos_cstate(28:26),gpi_qos_tinq_ready(25)};
    //  31:29 -->cntx_state
  #define AXI_TMU_DBG_BUS_PP1         0x308 
  #define AXI_TMU_DBG_BUS_PP2         0x30c 
  #define AXI_TMU_DBG_BUS_PP3         0x310
  #define AXI_TMU_DBG_BUS_PP4         0x314
  #define AXI_TMU_DBG_BUS_PP5         0x318
  #define AXI_TMU_DBG_BUS_PP6         0x31c
  #define AXI_TMU_DBG_BUS_PP7         0x320
  #define AXI_TMU_DBG_BUS_PP8         0x324
  #define AXI_TMU_DBG_BUS_PP9         0x328
  #define AXI_TMU_DBG_BUS_PP10        0x32c
  #define AXI_TMU_DBG_BUS_PP11        0x330
  #define AXI_TMU_DBG_BUS_PP12        0x334
  #define AXI_TMU_DBG_BUS_PP13        0x338
  #define AXI_TMU_DBG_BUS_PP15        0x340
  #define AXI_TMU_DBG_BUS_PP16        0x344
    //  Reset = NA
    //- csr_dbg_bus_pp131:0 Rdebug bus;
    //  12:0-->{enQ_state(12:9),inq_lbuf_valid(8),phy_queue_hd_stat(7:0)};
    //  24:13-->{tdq_state(23:21),shp_status(20:17),winner_queue(16:14),phy_sch_result(13)};
    //  28:25-->{qos_cstate(28:26),gpi_qos_tinq_ready(25)};
    //  31:29 -->cntx_state
  #define AXI_TMU_METER_ADDR          0x500 
    //  Reset = 10'h0
    //- csr_meter_addr 7:0 R/W NA for NPU_AVB; Program the meter no. to be accessed
    //- csr_global_mtr_en 8 R/W NA for NPU_AVB;Enables the meter logic
    //- csr_clr_mtr_wgts 9 R/W NA for NPU_AVB; setting this bit would clear the credit counter,
    //  frac counter values when configuring cfg0,cfg1
  #define AXI_TMU_METER_CFG0          0x504 
    //  Reset = 16'h0
    //- csr_mtr_cfg0 15:0 R/W NA for NPU_AVB; fractional wght. 
    //  Will be added to itself per divided clk, and when wraps at upper boundry, credit of 1 will be added
  #define AXI_TMU_METER_CFG1          0x508 
    //  Reset = 32'h0
    //- csr_mtr_cfg1 31:0 R/W NA for NPU_AVB;
    //  28:7 --> max credit and 
    //  6:0 --> integer wgt,
    //  29 -->meter_disable;
    //  30-->meter IFG no add;
    //  31-->pktrate
  #define AXI_TMU_METER_CMD           0x50c 
    //  Reset = 3'b0
    //- csr_mtr_cmd 0 R/W NA for NPU_AVB;0--> for read,1--> for write
    //- csr_mtr_start 1 R/W NA for NPU_AVB; write 1 to start the context access 
    //- csr_mtr_done 2 R NA for NPU_AVB; context access operation done signal;poll for this bit for access complition
  #define AXI_TMU_SCH_SHP_RANGE_START 0x1000
  #define AXI_TMU_SCH_SHP_RANGE_END   0x11fff
    //  Reset = NA
    //- csr_tmu_sch_shp_range_reg 31:0 R/W Range for the TDQ(scheduler/shaper) registers inside phy
    //  All the registers inside tlite_tdq_pp_csr gets repeated per PHY.
    //  Each phy will take x1000 registers w/
    //  PHY0 starting at x1000, For Milandr, it has
    //  only 17 PHYs, so valid range is x01000 to x11fff


#define AXI_TMU_INDIRECT_ACCESS_PAR1_REG	     AXI_TMU_BASE_ADDR + AXI_TMU_CNTX_ADDR
#define AXI_TMU_INDIRECT_ACCESS_PAR2_REG	     AXI_TMU_BASE_ADDR + AXI_TMU_CNTX_DATA
#define AXI_TMU_INDIRECT_ACCESS_CMD_REG	       AXI_TMU_BASE_ADDR + AXI_TMU_CNTX_CMD    
    #define AXI_TMU_INDIRECT_ACCESS_CMD_READ	     0x0
    #define AXI_TMU_INDIRECT_ACCESS_CMD_WRITE	     0x1
    #define AXI_TMU_INDIRECT_ACCESS_CMD_START	     0x2
    #define AXI_TMU_INDIRECT_ACCESS_CMD_DONE	     0x4


// ---------------------- CLASS_HW - аппаратный классификатор -------------------
#define AXI_CLASS_HW1_BASE_ADDR                  0x620000
#define AXI_CLASS_HW1_END_OFFSET                 0x62FFFF

#define AXI_CLASS_HW2_BASE_ADDR                  0x770000
#define AXI_CLASS_HW2_END_OFFSET                 0x77FFFF

  #define AXI_CLASS_VERSION           0x00 
    //  Reset = 32'h10031
    //- class_id 15:0 R Read only register that indicates the ID of the block
    //- class_version 23:16 R Read Only register that indicates the Version of the Block
    //- class_revision 31:24 R Read Only register that indicates the Revision of the Block
  #define AXI_CLASS_TX_CTRL           0x04 
    //  Reset = 2'b01
    //- csr_class_en 0 R/W Classifier Enable bit
    //- csr_class_hw_swrst 1 R/W Classifier Software reset
    #define AXI_CLASS_TX_CTRL_EN_Msk         0x0001UL
    #define AXI_CLASS_TX_CTRL_RESET_Msk      0x0002UL
    
  #define AXI_CLASS_INQ_PKTPTR        0x10 
    //  Reset = 32'h0
    //- csr_inq_pktptr 31:0 R/W PHY Ports (Etherent) writes packet pointer to this address. 
    //  This will be a blocking request, if the queue is full. 
    //  However queuing discipline will clear the buffers and free them
  #define AXI_CLASS_HDR_SIZE          0x14 
    //  Reset = 8'h30
    //- csr_lmem_hdr_size 7:0 R/W LMEM Header Size. Data in the LMEM is written from this offset. 
    //  The first location of LMEM is however written with the subsequent buffer address if it exists. 
    //  This location is a 32 bit aligned address. 
    //  If two byte offset is required, the register in the EMAC is programmed to add two bytes.
  #define AXI_CLASS_QOS_PORT01_TC_SEL     0x18
    //  Reset = 32'h0
    //- csr_qos_port0_tc_sel 15:0 R/W Port 0 TC SEL
    //- csr_qos_port1_tc_sel 31:16 R/W Port 1 TC SEL
  #define AXI_CLASS_QOS_PORT23_TC_SEL     0x1c 
    //- csr_qos_port2_tc_sel 15:0 R/W Port 2 TC SEL
    //- csr_qos_port3_tc_sel 31:16 R/W Port 3 TC SEL
  #define AXI_CLASS_QOS_PORT45_TC_SEL     0x20 
    //- csr_qos_port4_tc_sel 15:0 R/W Port 4 TC SEL
    //- csr_qos_port5_tc_sel 31:16 R/W Port 5 TC SEL
  #define AXI_CLASS_QOS_PORT67_TC_SEL     0x24 
    //- csr_qos_port6_tc_sel 15:0 R/W Port 6 TC SEL
    //- csr_qos_port7_tc_sel 31:16 R/W Port 7 TC SEL
  #define AXI_CLASS_QOS_PORT89_TC_SEL     0x5d8 
    //- csr_qos_port8_tc_sel 15:0 R/W Port 8 TC SEL
    //- csr_qos_port9_tc_sel 31:16 R/W Port 9 TC SEL
  #define AXI_CLASS_QOS_PORT1011_TC_SEL   0x5dc
    //- csr_qos_port10_tc_sel 15:0 R/W Port 10 TC SEL
    //- csr_qos_port11_tc_sel 31:16 R/W Port 11 TC SEL
  #define AXI_CLASS_QOS_PORT1213_TC_SEL   0x5e0
    //- csr_qos_port12_tc_sel 15:0 R/W Port 12 TC SEL
    //- csr_qos_port13_tc_sel 31:16 R/W Port 13 TC SEL
  #define AXI_CLASS_QOS_PORT1415_TC_SEL   0x5e4
    //- csr_qos_port14_tc_sel 15:0 R/W Port 14 TC SEL
    //- csr_qos_port15_tc_sel 31:16 R/W Port 15 TC SEL
  #define AXI_CLASS_QOS_PORT1617_TC_SEL   0x5e8
    //- csr_qos_port16_tc_sel 15:0 R/W Port 16 TC SEL
    //- csr_qos_port17_tc_sel 31:16 R/W NA  
  #define AXI_CLASS_QOS_GLOBAL_DSCP2TC_MAP0   0x28 
  #define AXI_CLASS_QOS_GLOBAL_DSCP2TC_MAP1   0x2c 
  #define AXI_CLASS_QOS_GLOBAL_DSCP2TC_MAP2   0x30
  #define AXI_CLASS_QOS_GLOBAL_DSCP2TC_MAP3   0x34
  #define AXI_CLASS_QOS_GLOBAL_DSCP2TC_MAP4   0x38
  #define AXI_CLASS_QOS_GLOBAL_DSCP2TC_MAP5   0x3c
  #define AXI_CLASS_QOS_GLOBAL_DSCP2TC_MAP6   0x40
    //  Reset = 30'h0
    //- csr_qos_global_dscp2tc_map0 29:0 R/W DSCP2TC MAP, For every 16 TOS value, 3 bit TC value.
  #define AXI_CLASS_QOS_PORT0_PCP2TC_MAP      0x44 
  #define AXI_CLASS_QOS_PORT1_PCP2TC_MAP      0x48 
  #define AXI_CLASS_QOS_PORT2_PCP2TC_MAP      0x4c
  #define AXI_CLASS_QOS_PORT3_PCP2TC_MAP      0x50
  #define AXI_CLASS_QOS_PORT4_PCP2TC_MAP      0x54
  #define AXI_CLASS_QOS_PORT5_PCP2TC_MAP      0x58
  #define AXI_CLASS_QOS_PORT6_PCP2TC_MAP      0x5c
  #define AXI_CLASS_QOS_PORT7_PCP2TC_MAP      0x60
  #define AXI_CLASS_QOS_PORT8_PCP2TC_MAP      0x5b4
  #define AXI_CLASS_QOS_PORT9_PCP2TC_MAP      0x5b8
  #define AXI_CLASS_QOS_PORT10_PCP2TC_MAP     0x5bc
  #define AXI_CLASS_QOS_PORT11_PCP2TC_MAP     0x5c0
  #define AXI_CLASS_QOS_PORT12_PCP2TC_MAP     0x5c4
  #define AXI_CLASS_QOS_PORT13_PCP2TC_MAP     0x5c8
  #define AXI_CLASS_QOS_PORT14_PCP2TC_MAP     0x5cc
  #define AXI_CLASS_QOS_PORT15_PCP2TC_MAP     0x5d0
  #define AXI_CLASS_QOS_PORT16_PCP2TC_MAP     0x5d4
    //  Reset = 24'h0
    //- csr_qos_port0_pcp2tc_map 23:0 R/W Port 0, PCP to TC Map. 
    //  TC at 2:0 for PCP0, 
    //  TC at 5:3 for PCP1, 
    //  8:6 for PCP2, 
    //  11:9 for PCP3,
    //  14:12 for PCP4, 
    //  17:15 for PCP5,
    //  20:18 for PCP6, 
    //  23:21 for PCP7
  #define AXI_CLASS_QOS_PORT_PID2TC_MAP       0x64 
    //  Reset = 30'h0
    //- csr_qos_port0_pid2tc_map 2:0 R/W Port 0 to tc map
    //- csr_qos_port1_pid2tc_map 5:3 R/W Port 1 to tc map
    //- csr_qos_port2_pid2tc_map 8:6 R/W Port 2 to tc map
    //- csr_qos_port3_pid2tc_map 11:9 R/W Port 3 to tc map
    //- csr_qos_port4_pid2tc_map 14:12 R/W Port 4 to tc map
    //- csr_qos_port5_pid2tc_map 17:15 R/W Port 5 to tc map
    //- csr_qos_port6_pid2tc_map 20:18 R/W Port 6 to tc map
    //- csr_qos_port7_pid2tc_map 23:21 R/W Port 7 to tc map
    //- csr_qos_port8_pid2tc_map 26:24 R/W Port 8 to tc map
    //- csr_qos_port9_pid2tc_map 29:27 R/W Port 9 to tc map
  #define AXI_CLASS_QOS_PORT1_PID2TC_MAP      0x5ec 
    //  Reset = 21'h0
    //- csr_qos_port10_pid2tc_map 2:0 R/W Port 10 to tc map
    //- csr_qos_port11_pid2tc_map 5:3 R/W Port 11 to tc map
    //- csr_qos_port12_pid2tc_map 8:6 R/W Port 12 to tc map
    //- csr_qos_port13_pid2tc_map 11:9 R/W Port 13 to tc map
    //- csr_qos_port14_pid2tc_map 14:12 R/W Port 14 to tc map
    //- csr_qos_port15_pid2tc_map 17:15 R/W Port 15 to tc map
    //- csr_qos_port16_pid2tc_map 20:18 R/W Port 16 to tc map  
  #define AXI_CLASS_QOS_PORT0_TC2COS_MAP      0x68
  #define AXI_CLASS_QOS_PORT1_TC2COS_MAP      0x6c
  #define AXI_CLASS_QOS_PORT2_TC2COS_MAP      0x70
  #define AXI_CLASS_QOS_PORT3_TC2COS_MAP      0x74
  #define AXI_CLASS_QOS_PORT4_TC2COS_MAP      0x78
  #define AXI_CLASS_QOS_PORT5_TC2COS_MAP      0x7c
  #define AXI_CLASS_QOS_PORT6_TC2COS_MAP      0x80
  #define AXI_CLASS_QOS_PORT7_TC2COS_MAP      0x84
  #define AXI_CLASS_QOS_PORT8_TC2COS_MAP      0x590
  #define AXI_CLASS_QOS_PORT9_TC2COS_MAP      0x594
  #define AXI_CLASS_QOS_PORT10_TC2COS_MAP     0x598
  #define AXI_CLASS_QOS_PORT11_TC2COS_MAP     0x59c
  #define AXI_CLASS_QOS_PORT12_TC2COS_MAP     0x5a0
  #define AXI_CLASS_QOS_PORT13_TC2COS_MAP     0x5a4
  #define AXI_CLASS_QOS_PORT14_TC2COS_MAP     0x5a8
  #define AXI_CLASS_QOS_PORT15_TC2COS_MAP     0x5ac
  #define AXI_CLASS_QOS_PORT16_TC2COS_MAP     0x5b0
    //  Reset = 24'hfac688
    //- class_qos_port0_tc2cos_map 
    //  23:0 R/W TC 2 COS map, cos value 
    //  2:0 for TC 0,
    //  5:3 for TC1,
    //  8:6 for TC2, 
    //  11:9 for TC3,
    //  14:12 for TC4,
    //  17:15 for TC5,
    //  20:18 for TC6,
    //  23:21 for TC7
  #define AXI_CLASS_SNOOP_SPL_ETYPE_REG01     0x88 
    //  Reset = 32'h0
    //- csr_snoop_spl_etype0 15:0 R/W snoop ether type 0, when programmed and enabled, snoops this ethertype
    //- csr_snoop_spl_etype1 31:16 R/W snoop ether type 1, when programmed and enabled, snoops this ethertype
  #define AXI_CLASS_SNOOP_SPL_ETYPE_REG23     0x8c
    //  Reset = 32'h0
    //- csr_snoop_spl_etype2 15:0 R/W snoop ether type 2, when programmed and enabled, snoops this ethertype
    //- csr_snoop_spl_etype3 31:16 R/W snoop ether type3, when programmed and enabled, snoops this ethertype
  #define AXI_CLASS_SNOOP_CONTROL             0x90
    //  Reset = 16'h0
    //- csr_snoop_cntrl 15:0 R/W snoop control register; 
    //  csr_snoop_igmp_en = csr_snoop_cntrl[4]; 
    //  csr_snoop_mldv2_en = csr_snoop_cntrl[5]; 
    //  csr_snoop_etype0_en = csr_snoop_cntrl[8]; 
    //  csr_snoop_etype1_en = csr_snoop_cntrl[9]; 
    //  csr_snoop_etype2_en = csr_snoop_cntrl[10]; 
    //  csr_snoop_etype3_en = csr_snoop_cntrl[11]; 
    //  csr_snoop_etype_arp = csr_snoop_cntrl[12]; 
    //  csr_snoop_etype_rarp = csr_snoop_cntrl[13]; 
    //  csr_snoop_hopopts = csr_snoop_cntrl[14];

  #define AXI_CLASS_MEM_ACCESS_ADDR           0x100 
    //  Reset = 32'h0
    //- csr_pe_mem_addr 23:0 R/W Internal memory address.Its an indirect R/W access from Host. 
    //  Bits[23:20] indicate the processor to write the data to 
    //- csr_pe_mem_wren 27:24 R/W Byte Enables of the Internal memory access 
    //- csr_pe_mem_cmd 31 R/W Mem Access Command. 
    //    0 = Internal Memory Read,
    //    1 = Internal memory Write. 
    //  16th bit must has to be set to 1, to perform the memory access.
  #define AXI_CLASS_MEM_ACCESS_WDATA          0x104 
    //  Reset = 32'h0
    //- csr_pe_mem_wdata 31:0 R/W Internal Memory Access Write Data
  #define AXI_CLASS_MEM_ACCESS_RDATA          0x108 
    //  Reset = NA
    //- csr_mem_access_rdata 31:0 R Internal Memory Access Read Data. The commands are blocked at the mem_access only
  #define AXI_CLASS_TM_INQ_ADDR               0x114 
    //  Reset = 32'hC0000000+24'h310008
    //- csr_tm_inq_addr 31:0 R/W Address of the Traffic Manager's input Queue.
  #define AXI_CLASS_PE_STATUS                 0x118 
    //  Reset = 18'h0
    //- pe_dbg_bus 15:0 R Used to debug Procsessor
    //- pe_csr_bus_wait_temp 16 R wait signal to perform R/W to PE peripherals through PIB master
    //- pe_csr_mem_wait_temp 17 R wait signal to perform R/W to PE peripherals
  #define AXI_CLASS_PHY1_RX_PKTS              0x11c 
  #define AXI_CLASS_PHY2_RX_PKTS              0x144
  #define AXI_CLASS_PHY3_RX_PKTS              0x16c
  #define AXI_CLASS_PHY4_RX_PKTS              0x1d4 
  #define AXI_CLASS_PHY5_RX_PKTS              0x298
  #define AXI_CLASS_PHY6_RX_PKTS              0x2d0
  #define AXI_CLASS_PHY7_RX_PKTS              0x308
  #define AXI_CLASS_PHY8_RX_PKTS              0x330
  #define AXI_CLASS_PHY9_RX_PKTS              0x5f0
  #define AXI_CLASS_PHY11_RX_PKTS             0x640
  #define AXI_CLASS_PHY12_RX_PKTS             0x668
  #define AXI_CLASS_PHY13_RX_PKTS             0x690
  #define AXI_CLASS_PHY14_RX_PKTS             0x6b8
  #define AXI_CLASS_PHY15_RX_PKTS             0x6e0
  #define AXI_CLASS_PHY16_RX_PKTS             0x708
  #define AXI_CLASS_PHY17_RX_PKTS             0x730
  #define AXI_CLASS_PHY10_RX_PKTS             0x618
    //  Reset = 32'h0
    //- class_phy1_rx_pkts 31:0 R count for number of packets received at phy0 port
  #define AXI_CLASS_PHY1_TX_PKTS              0x120 
  #define AXI_CLASS_PHY2_TX_PKTS              0x148
  #define AXI_CLASS_PHY3_TX_PKTS              0x170
  #define AXI_CLASS_PHY4_TX_PKTS              0x1d8
  #define AXI_CLASS_PHY5_TX_PKTS              0x29c
  #define AXI_CLASS_PHY6_TX_PKTS              0x2d4
  #define AXI_CLASS_PHY7_TX_PKTS              0x30c
  #define AXI_CLASS_PHY8_TX_PKTS              0x334
  #define AXI_CLASS_PHY9_TX_PKTS              0x5f4
  #define AXI_CLASS_PHY10_TX_PKTS             0x61c
  #define AXI_CLASS_PHY11_TX_PKTS             0x644
  #define AXI_CLASS_PHY12_TX_PKTS             0x66c
  #define AXI_CLASS_PHY13_TX_PKTS             0x694
  #define AXI_CLASS_PHY14_TX_PKTS             0x6bc
  #define AXI_CLASS_PHY15_TX_PKTS             0x6e4
  #define AXI_CLASS_PHY16_TX_PKTS             0x70c
  #define AXI_CLASS_PHY17_TX_PKTS             0x734
    //  Reset = 32'h0
    //- class_phy1_tx_pkts 31:0 R count for number of packets transmitted through phy0 port; for future use
  #define AXI_CLASS_PHY1_LP_FAIL_PKTS         0x124 
  #define AXI_CLASS_PHY2_LP_FAIL_PKTS         0x14c
  #define AXI_CLASS_PHY3_LP_FAIL_PKTS         0x174
  #define AXI_CLASS_PHY4_LP_FAIL_PKTS         0x1dc
  #define AXI_CLASS_PHY5_LP_FAIL_PKTS         0x2a0
  #define AXI_CLASS_PHY6_LP_FAIL_PKTS         0x2d8
  #define AXI_CLASS_PHY7_LP_FAIL_PKTS         0x310
  #define AXI_CLASS_PHY8_LP_FAIL_PKTS         0x338
  #define AXI_CLASS_PHY9_LP_FAIL_PKTS         0x5f8
  #define AXI_CLASS_PHY10_LP_FAIL_PKTS        0x620
  #define AXI_CLASS_PHY11_LP_FAIL_PKTS        0x648
  #define AXI_CLASS_PHY12_LP_FAIL_PKTS        0x670
  #define AXI_CLASS_PHY13_LP_FAIL_PKTS        0x698
  #define AXI_CLASS_PHY14_LP_FAIL_PKTS        0x6c0
  #define AXI_CLASS_PHY15_LP_FAIL_PKTS        0x6e8
  #define AXI_CLASS_PHY16_LP_FAIL_PKTS        0x710
  #define AXI_CLASS_PHY17_LP_FAIL_PKTS        0x738
    //  Reset = 32'h0
    //- class_phy1_lp_fail_pkts 31:0 R port0 lookup fail packets count. For future use
  #define AXI_CLASS_PHY1_INTF_FAIL_PKTS       0x128 
  #define AXI_CLASS_PHY2_INTF_FAIL_PKTS       0x150
  #define AXI_CLASS_PHY3_INTF_FAIL_PKTS       0x178
  #define AXI_CLASS_PHY4_INTF_FAIL_PKTS       0x1e0
  #define AXI_CLASS_PHY5_INTF_FAIL_PKTS       0x2a4
  #define AXI_CLASS_PHY6_INTF_FAIL_PKTS       0x2dc
  #define AXI_CLASS_PHY7_INTF_FAIL_PKTS       0x314
  #define AXI_CLASS_PHY8_INTF_FAIL_PKTS       0x33c
  #define AXI_CLASS_PHY9_INTF_FAIL_PKTS       0x5fc
  #define AXI_CLASS_PHY10_INTF_FAIL_PKTS      0x624
  #define AXI_CLASS_PHY11_INTF_FAIL_PKTS      0x64c
  #define AXI_CLASS_PHY12_INTF_FAIL_PKTS      0x674
  #define AXI_CLASS_PHY13_INTF_FAIL_PKTS      0x69c
  #define AXI_CLASS_PHY14_INTF_FAIL_PKTS      0x6c4
  #define AXI_CLASS_PHY15_INTF_FAIL_PKTS      0x6ec
  #define AXI_CLASS_PHY16_INTF_FAIL_PKTS      0x714
  #define AXI_CLASS_PHY17_INTF_FAIL_PKTS      0x73c
    //  Reset = 32'h0
    //- class_phy1_intf_fail_pkts 31:0 R port0 interface fail packets count. For future use
  #define AXI_CLASS_PHY1_INTF_MATCH_PKTS      0x12c 
  #define AXI_CLASS_PHY2_INTF_MATCH_PKTS      0x154
  #define AXI_CLASS_PHY3_INTF_MATCH_PKTS      0x17c
  #define AXI_CLASS_PHY4_INTF_MATCH_PKTS      0x1e4
  #define AXI_CLASS_PHY5_INTF_MATCH_PKTS      0x2a8
  #define AXI_CLASS_PHY6_INTF_MATCH_PKTS      0x2e0
  #define AXI_CLASS_PHY7_INTF_MATCH_PKTS      0x318
  #define AXI_CLASS_PHY8_INTF_MATCH_PKTS      0x340
  #define AXI_CLASS_PHY9_INTF_MATCH_PKTS      0x600
  #define AXI_CLASS_PHY10_INTF_MATCH_PKTS     0x628
  #define AXI_CLASS_PHY11_INTF_MATCH_PKTS     0x650
  #define AXI_CLASS_PHY12_INTF_MATCH_PKTS     0x678
  #define AXI_CLASS_PHY13_INTF_MATCH_PKTS     0x6a0
  #define AXI_CLASS_PHY14_INTF_MATCH_PKTS     0x6c8
  #define AXI_CLASS_PHY15_INTF_MATCH_PKTS     0x6f0
  #define AXI_CLASS_PHY16_INTF_MATCH_PKTS     0x718
  #define AXI_CLASS_PHY17_INTF_MATCH_PKTS     0x740
    //  Reset = 32'h0
    //- class_phy1_intf_match_pkts 31:0 R port0 interface match packets count. For future use
  #define AXI_CLASS_PHY1_L3_FAIL_PKTS         0x130 
  #define AXI_CLASS_PHY2_L3_FAIL_PKTS         0x158
  #define AXI_CLASS_PHY3_L3_FAIL_PKTS         0x180
  #define AXI_CLASS_PHY4_L3_FAIL_PKTS         0x1e8
  #define AXI_CLASS_PHY5_L3_FAIL_PKTS         0x2ac
  #define AXI_CLASS_PHY6_L3_FAIL_PKTS         0x2e4
  #define AXI_CLASS_PHY7_L3_FAIL_PKTS         0x31c
  #define AXI_CLASS_PHY8_L3_FAIL_PKTS         0x344
  #define AXI_CLASS_PHY9_L3_FAIL_PKTS         0x604
  #define AXI_CLASS_PHY10_L3_FAIL_PKTS        0x62c
  #define AXI_CLASS_PHY11_L3_FAIL_PKTS        0x654
  #define AXI_CLASS_PHY12_L3_FAIL_PKTS        0x67c
  #define AXI_CLASS_PHY13_L3_FAIL_PKTS        0x6a4
  #define AXI_CLASS_PHY14_L3_FAIL_PKTS        0x6cc
  #define AXI_CLASS_PHY15_L3_FAIL_PKTS        0x6f4
  #define AXI_CLASS_PHY16_L3_FAIL_PKTS        0x71c
  #define AXI_CLASS_PHY17_L3_FAIL_PKTS        0x744
    //  Reset = 32'h0
    //- class_phy1_l3_fail_pkts 31:0 R port0 layer3 fail packets count
  #define AXI_CLASS_PHY1_V4_PKTS              0x134 
  #define AXI_CLASS_PHY2_V4_PKTS              0x15c
  #define AXI_CLASS_PHY3_V4_PKTS              0x184
  #define AXI_CLASS_PHY4_V4_PKTS              0x1ec
  #define AXI_CLASS_PHY5_V4_PKTS              0x2b0
  #define AXI_CLASS_PHY6_V4_PKTS              0x2e8
  #define AXI_CLASS_PHY7_V4_PKTS              0x4e8
  #define AXI_CLASS_PHY8_V4_PKTS              0x348
  #define AXI_CLASS_PHY9_V4_PKTS              0x608
  #define AXI_CLASS_PHY10_V4_PKTS             0x630
  #define AXI_CLASS_PHY11_V4_PKTS             0x658
  #define AXI_CLASS_PHY12_V4_PKTS             0x680
  #define AXI_CLASS_PHY13_V4_PKTS             0x6a8
  #define AXI_CLASS_PHY14_V4_PKTS             0x6d0
  #define AXI_CLASS_PHY15_V4_PKTS             0x6f8
  #define AXI_CLASS_PHY16_V4_PKTS             0x720
  #define AXI_CLASS_PHY17_V4_PKTS             0x748
    //  Reset = 32'h0
    //- class_phy1_v4_pkts 31:0 R port0 - IPV4 packets count
  #define AXI_CLASS_PHY1_V6_PKTS              0x138 
  #define AXI_CLASS_PHY2_V6_PKTS              0x160
  #define AXI_CLASS_PHY3_V6_PKTS              0x188
  #define AXI_CLASS_PHY4_V6_PKTS              0x1f0
  #define AXI_CLASS_PHY5_V6_PKTS              0x2b4
  #define AXI_CLASS_PHY6_V6_PKTS              0x2ec
  #define AXI_CLASS_PHY7_V6_PKTS              0x4ec
  #define AXI_CLASS_PHY8_V6_PKTS              0x34c
  #define AXI_CLASS_PHY9_V6_PKTS              0x60c
  #define AXI_CLASS_PHY10_V6_PKTS             0x634
  #define AXI_CLASS_PHY11_V6_PKTS             0x65c
  #define AXI_CLASS_PHY12_V6_PKTS             0x684
  #define AXI_CLASS_PHY13_V6_PKTS             0x6ac
  #define AXI_CLASS_PHY14_V6_PKTS             0x6d4
  #define AXI_CLASS_PHY15_V6_PKTS             0x6fc
  #define AXI_CLASS_PHY16_V6_PKTS             0x724
  #define AXI_CLASS_PHY17_V6_PKTS             0x74c
    //  Reset = 32'h0
    //- class_phy1_v6_pkts 31:0 R port0 - IPV6 packets count
  #define AXI_CLASS_PHY1_CHKSUM_ERR_PKTS      0x13c 
  #define AXI_CLASS_PHY2_CHKSUM_ERR_PKTS      0x164
  #define AXI_CLASS_PHY3_CHKSUM_ERR_PKTS      0x18c
  #define AXI_CLASS_PHY4_CHKSUM_ERR_PKTS      0x1f4
  #define AXI_CLASS_PHY5_CHKSUM_ERR_PKTS      0x2b8
  #define AXI_CLASS_PHY6_CHKSUM_ERR_PKTS      0x2f0
  #define AXI_CLASS_PHY7_CHKSUM_ERR_PKTS      0x4f0
  #define AXI_CLASS_PHY8_CHKSUM_ERR_PKTS      0x350
  #define AXI_CLASS_PHY9_CHKSUM_ERR_PKTS      0x610
  #define AXI_CLASS_PHY10_CHKSUM_ERR_PKTS     0x638
  #define AXI_CLASS_PHY11_CHKSUM_ERR_PKTS     0x660
  #define AXI_CLASS_PHY12_CHKSUM_ERR_PKTS     0x688
  #define AXI_CLASS_PHY13_CHKSUM_ERR_PKTS     0x6b0
  #define AXI_CLASS_PHY14_CHKSUM_ERR_PKTS     0x6d8
  #define AXI_CLASS_PHY15_CHKSUM_ERR_PKTS     0x700
  #define AXI_CLASS_PHY16_CHKSUM_ERR_PKTS     0x728
  #define AXI_CLASS_PHY17_CHKSUM_ERR_PKTS     0x750
    //  Reset = 32'h0
    //- class_phy1_chksum_err_pkts 31:0 R port0 - Checksum error packets count
  #define AXI_CLASS_PHY1_TTL_ERR_PKTS         0x140 
  #define AXI_CLASS_PHY2_TTL_ERR_PKTS         0x168
  #define AXI_CLASS_PHY3_TTL_ERR_PKTS         0x190
  #define AXI_CLASS_PHY4_TTL_ERR_PKTS         0x1f8
  #define AXI_CLASS_PHY5_TTL_ERR_PKTS         0x2bc
  #define AXI_CLASS_PHY6_TTL_ERR_PKTS         0x2f4
  #define AXI_CLASS_PHY7_TTL_ERR_PKTS         0x4f4
  #define AXI_CLASS_PHY8_TTL_ERR_PKTS         0x354
  #define AXI_CLASS_PHY9_TTL_ERR_PKTS         0x614
  #define AXI_CLASS_PHY10_TTL_ERR_PKTS        0x63c
  #define AXI_CLASS_PHY11_TTL_ERR_PKTS        0x664
  #define AXI_CLASS_PHY12_TTL_ERR_PKTS        0x68c
  #define AXI_CLASS_PHY13_TTL_ERR_PKTS        0x6b4
  #define AXI_CLASS_PHY14_TTL_ERR_PKTS        0x6dc
  #define AXI_CLASS_PHY15_TTL_ERR_PKTS        0x704
  #define AXI_CLASS_PHY16_TTL_ERR_PKTS        0x72c
  #define AXI_CLASS_PHY17_TTL_ERR_PKTS        0x754
    //  Reset = 32'h0
    //- class_phy1_ttl_err_pkts 31:0 R port0 - TTL error packets count
  #define AXI_CLASS_PHY1_ICMP_PKTS            0x194 
  #define AXI_CLASS_PHY2_ICMP_PKTS            0x1a4 
  #define AXI_CLASS_PHY3_ICMP_PKTS            0x1b4
  #define AXI_CLASS_PHY4_ICMP_PKTS            0x1c4
  #define AXI_CLASS_PHY5_ICMP_PKTS            0x2c0
  #define AXI_CLASS_PHY6_ICMP_PKTS            0x2f8
  #define AXI_CLASS_PHY7_ICMP_PKTS            0x320
  #define AXI_CLASS_PHY8_ICMP_PKTS            0x358
  #define AXI_CLASS_PHY9_ICMP_PKTS            0x758
  #define AXI_CLASS_PHY10_ICMP_PKTS           0x768
  #define AXI_CLASS_PHY11_ICMP_PKTS           0x778
  #define AXI_CLASS_PHY12_ICMP_PKTS           0x788
  #define AXI_CLASS_PHY13_ICMP_PKTS           0x798
  #define AXI_CLASS_PHY14_ICMP_PKTS           0x7a8
  #define AXI_CLASS_PHY15_ICMP_PKTS           0x7b8
  #define AXI_CLASS_PHY16_ICMP_PKTS           0x7c8
  #define AXI_CLASS_PHY17_ICMP_PKTS           0x7d8
    //  Reset = 32'h0
    //- class_phy1_icmp_pkts 31:0 R count for number of ICMP packets received at phy0 port
  #define AXI_CLASS_PHY1_IGMP_PKTS            0x198 
  #define AXI_CLASS_PHY2_IGMP_PKTS            0x1a8 
  #define AXI_CLASS_PHY3_IGMP_PKTS            0x1b8
  #define AXI_CLASS_PHY4_IGMP_PKTS            0x1c8
  #define AXI_CLASS_PHY5_IGMP_PKTS            0x2c4
  #define AXI_CLASS_PHY6_IGMP_PKTS            0x2fc
  #define AXI_CLASS_PHY7_IGMP_PKTS            0x324
  #define AXI_CLASS_PHY8_IGMP_PKTS            0x35c
  #define AXI_CLASS_PHY9_IGMP_PKTS            0x75c
  #define AXI_CLASS_PHY10_IGMP_PKTS           0x76c
  #define AXI_CLASS_PHY11_IGMP_PKTS           0x77c
  #define AXI_CLASS_PHY12_IGMP_PKTS           0x78c
  #define AXI_CLASS_PHY13_IGMP_PKTS           0x79c
  #define AXI_CLASS_PHY14_IGMP_PKTS           0x7ac
  #define AXI_CLASS_PHY15_IGMP_PKTS           0x7bc
  #define AXI_CLASS_PHY16_IGMP_PKTS           0x7cc
  #define AXI_CLASS_PHY17_IGMP_PKTS           0x7dc
    //  Reset = 32'h0
    //- class_phy1_igmp_pkts 31:0 R count for number of IGMP packets Received at phy0 port
  #define AXI_CLASS_PHY1_TCP_PKTS             0x19c 
  #define AXI_CLASS_PHY2_TCP_PKTS             0x1ac
  #define AXI_CLASS_PHY3_TCP_PKTS             0x1bc
  #define AXI_CLASS_PHY4_TCP_PKTS             0x1cc
  #define AXI_CLASS_PHY5_TCP_PKTS             0x2c8
  #define AXI_CLASS_PHY6_TCP_PKTS             0x300
  #define AXI_CLASS_PHY7_TCP_PKTS             0x328
  #define AXI_CLASS_PHY8_TCP_PKTS             0x360
  #define AXI_CLASS_PHY9_TCP_PKTS             0x760
  #define AXI_CLASS_PHY10_TCP_PKTS            0x770
  #define AXI_CLASS_PHY11_TCP_PKTS            0x780
  #define AXI_CLASS_PHY12_TCP_PKTS            0x790
  #define AXI_CLASS_PHY13_TCP_PKTS            0x7a0
  #define AXI_CLASS_PHY14_TCP_PKTS            0x7b0
  #define AXI_CLASS_PHY15_TCP_PKTS            0x7c0
  #define AXI_CLASS_PHY16_TCP_PKTS            0x7d0
  #define AXI_CLASS_PHY17_TCP_PKTS            0x7e0
    //  Reset = 32'h0
    //- class_phy1_tcp_pkts 31:0 R count for number of TCP packets received at phy0 port
  #define AXI_CLASS_PHY1_UDP_PKTS             0x1a0 
  #define AXI_CLASS_PHY2_UDP_PKTS             0x1b0
  #define AXI_CLASS_PHY3_UDP_PKTS             0x1c0
  #define AXI_CLASS_PHY4_UDP_PKTS             0x1d0
  #define AXI_CLASS_PHY5_UDP_PKTS             0x2cc
  #define AXI_CLASS_PHY6_UDP_PKTS             0x304
  #define AXI_CLASS_PHY7_UDP_PKTS             0x32c
  #define AXI_CLASS_PHY8_UDP_PKTS             0x364
  #define AXI_CLASS_PHY9_UDP_PKTS             0x764
  #define AXI_CLASS_PHY10_UDP_PKTS            0x774
  #define AXI_CLASS_PHY11_UDP_PKTS            0x784
  #define AXI_CLASS_PHY12_UDP_PKTS            0x794
  #define AXI_CLASS_PHY13_UDP_PKTS            0x7a4
  #define AXI_CLASS_PHY14_UDP_PKTS            0x7b4
  #define AXI_CLASS_PHY15_UDP_PKTS            0x7c4
  #define AXI_CLASS_PHY16_UDP_PKTS            0x7d4
  #define AXI_CLASS_PHY17_UDP_PKTS            0x7e4
    //  Reset = 32'h0
    //- class_phy1_udp_pkts 31:0 R count for number of UDP packets Received at phy0 port
  #define AXI_CLASS_GLOBAL_MGMT_REG           0x200 
    //  Reset = 24'h0
    //- csr_glb_mgmt_etype 15:0 R/W global management ether type
    //- csr_glb_mgmt_port 23:16 R/W global management port
  #define AXI_CLASS_AFULL_THRES               0x204 
    //  Reset = 5'h14
    //- csr_afull_thres 4:0 R/W Threshold for llm fifo
  #define AXI_CLASS_BUS_ACCESS_ADDR           0x228 
    //  Reset = 32'h0
    //- csr_pe_bus_addr 23:0 R/W PE-AHB peripherals are accessed from Host through PIB master block. This is an indirect access register
    //- csr_pe_bus_wren 27:24 R/W Byte Enables
    //- csr_pe_bus_cmd 31 R/W Bus Access Command. 0 = Read, 1 = Write .
  #define AXI_CLASS_BUS_ACCESS_WDATA          0x22c 
    //  Reset = 32'h0
    //- csr_pe_bus_wdata 31:0 R/W Write Data
  #define AXI_CLASS_BUS_ACCESS_RDATA          0x230 
    //  Reset = 32'h0
    //- csr_bus_access_rdata 31:0 R Read Data.
  #define AXI_CLASS_ROUTE_HASH_ENTRY_SIZE     0x234 
    //  Reset = 24'h80
    //- csr_route_entry_size 9:0 R/W NA for NPU AVB.route entry size
    //- csr_route_hash_size 23:16 R/W NA for NPU AVB.route hash size
  #define AXI_CLASS_ROUTE_TABLE_BASE          0x238 
    //  Reset = 32'h0
    //- csr_route_table_base 31:0 R/W NA for NPU AVB.route table base addr
  #define AXI_CLASS_ROUTE_MULTI_REG           0x23c 
    //  Reset = 21'h8000
    //- csr_rt_two_level_ref 0 R/W CLASS_ROUTE_MULTI_REG not used for NPU AVB.1:Route two level reference, 0:single level reference
    //- csr_phyno_in_hash 1 R/W Phy no in hash calculation in route for asymmetric hash
    //- csr_parse_route_en 3 R/W H/W route fetch enable
    //- csr_vlan_aware_bridge 4 R/W vlan aware bridge
    //- csr_parse_bridge_en 5 R/W H/W bridge lookup enable
    //- csr_ipaligned_pkt 6 R/W Sets Ip aligned packet
    //- csr_arc_hit_check_en 7 R/W Sets Arc hit
    //- csr_vlan_aware_bridge_phy1 8 R/W Port1 is aware of Vlan pkt .For future use
    //- csr_vlan_aware_bridge_phy2 9 R/W Port2 is aware of Vlan pkt.For future use
    //- csr_vlan_aware_bridge_phy3 10 R/W Port3 is aware of Vlan pkt .For future use
    //- csr_class_toe 11 R/W Sets TCP offload process
    //- csr_asym_hash 13:12 R/W asymmetric hash calculation. 
    //    00 means normal hash, 
    //    01 means crc on srcport, 
    //    10 means crc on src_ip address, 
    //    11 means crc on exclusive or of srcip, srcport
    //- csr_sym_rtentry 14 R/W symmentric route entry
    //- csr_qb2bus_endianess 15 R/W specifies route entry endianess access from DDR for QFET.Default it is one.
    //- csr_len_check 16 R/W length check enable
    //- csr_config_gen1 17 R/W general config reg. For future use
    //- csr_config_gen2 18 R/W general config reg. For future use
    //- csr_config_gen3 19 R/W general config reg. For future use
    //- csr_config_gen4 20 R/W general config reg. For future use
  #define AXI_CLASS_SMEM_OFFSET               0x240 
    //  Reset = 27'h220080
    //- csr_smem_data_offset 8:0 R/W Intermediate memory smem data offset. To have flexibility with addresses. Default value is 0x80
    //- csr_smem_rte_offset 17:9 R/W Intermediate memory smem route offset. To have flexibility with addresses. Default value is 0x100
    //- csr_smem_hdr_offset 26:18 R/W Intermediate memory smem header offset. To have flexibility with addresses. Default value is 0x8
  #define AXI_CLASS_LMEM_BUF_SIZE             0x244 
    //  Reset = 16'h80
    //- csr_lmem_buf_size 15:0 R/W lmem buffer size
  #define AXI_CLASS_VLAN_ID                   0x248 
    //  Reset = 26'h0
    //- csr_use_default_vlanid 0 R/W use default vlan
    //- csr_def_vlanid 12:1 R/W default vlan id values
    //- csr_use_default_vlanid_phy1 13 R/W use default vlan for port1. For future use
    //- csr_def_vlanid_phy1 25:14 R/W default vlan id values for port1 .For future use
  #define AXI_CLASS_BMU1_BUF_FREE             0x24c 
    //  Reset = 32'h00000000+24'h240034
    //- csr_bmu1_buf_free 31:0 R/W lmem buffer free address
  #define AXI_CLASS_USE_TMU_INQ               0x250 
    //  Reset = 1'h0
    //- csr_use_tmu_inq_afull 0 R/W setting 1 will use tmu inq full
  #define AXI_CLASS_VLAN_ID1                  0x254 
    //  Reset = 26'h0
    //- csr_use_default_vlanid_phy2 0 R/W use default vlan for port2 .For future use
    //- csr_def_vlanid_phy2 12:1 R/W default vlan id values for port2 .For future use
    //- csr_use_default_vlanid_phy3 13 R/W use default vlan for port3 .For future use
    //- csr_def_vlanid_phy3 25:14 R/W default vlan id values for port3 .For future use
  #define AXI_CLASS_BUS_ACCESS_BASE_ADDR      0x258 
    //  Reset = 8'hC2
    //- csr_pe_bus_base 7:0 R/W Processor peripherals base address
  #define AXI_CLASS_HIF_PARSE                 0x25C 
    //  Reset = 5'h0
    //- csr_hif_pkt_class_en 0 R/W Enables Hardware parsing for HIF pkts
    //- csr_hif_pkt_offset 4:1 R/W Offset which says from which point pkt needs to parsed
  #define AXI_CLASS_PE_INT_SRC                0x260 
    //  Reset = 9'h0
    //- class_pe_int 0 INT NA for NPU AVB.Master interrupt for all PE's
    //- class_pe0_int 1 INT NA for NPU AVB.Interrupt register for PE0
    //- class_pe1_int 2 INT NA for NPU AVB.Interrupt register for PE1
    //- class_pe2_int 3 INT NA for NPU AVB.Interrupt register for PE2
    //- class_pe3_int 4 INT NA for NPU AVB.Interrupt register for PE3
    //- class_pe4_int 5 INT NA for NPU AVB.Interrupt register for PE4
    //- class_pe5_int 6 INT NA for NPU AVB.Interrupt register for PE5
    //- class_pe6_int 7 INT NA for NPU AVB.Interrupt register for PE6
    //- class_pe7_int 8 INT NA for NPU AVB.Interrupt register for PE7
  #define AXI_CLASS_PE_INT_ENABLE             0x264 
    //  Reset = 9'h0
    //- class_pe_int_en 0 INT_EN NA for NPU AVB.Interrupt enable register for PE
    //- class_pe0_int_en 1 INT_EN NA for NPU AVB.Interrupt enable register for PE0
    //- class_pe1_int_en 2 INT_EN NA for NPU AVB.Interrupt enable register for PE1
    //- class_pe2_int_en 3 INT_EN NA for NPU AVB.Interrupt enable register for PE2
    //- class_pe3_int_en 4 INT_EN NA for NPU AVB.Interrupt enable register for PE3
    //- class_pe4_int_en 5 INT_EN NA for NPU AVB.Interrupt enable register for PE4
    //- class_pe5_int_en 6 INT_EN NA for NPU AVB.Interrupt enable register for PE5
    //- class_pe6_int_en 7 INT_EN NA for NPU AVB.Interrupt enable register for PE6
    //- class_pe7_int_en 8 INT_EN NA for NPU AVB.Interrupt enable register for PE7
  #define AXI_CLASS_TPID0_TPID1               0x268 
    //  Reset = 32'h81008100
    //- csr_tpid0 15:0 R/W vlan protocol for port0  
    //- tpid1 31:16 R/W vlan protocol for port1
  #define AXI_CLASS_TPID2                     0x26C 
    //  Reset = 16'h8100
    //- csr_tpid2 15:0 R/W vlan protocol for port2
  #define AXI_CLASS_L4_CHKSUM                 0x270 
    //  Reset = 10'h250
    //- csr_tcp_chksum_drop 0 R/W tcp checksum drop
    //- csr_udp_chksum_drop 1 R/W udp checksum drop
    //- csr_short_pkt_thres 8:2 R/W threshold for short packets
    //- csr_ipv4_chksum_drop 9 R/W ipv4 checksum drop
  #define AXI_CLASS_STATE                     0x274 
    //  Reset = NA
    //- qinq_cstate 3:0 R qinq module states
    //- rtfet_cstate 6:4 R route fet states
    //- qfet_cstate 10:7 R qfet states
    //- dmi_cstate 14:11 R dmi states
    //- ro_cstate 19:15 R ro states
    //- pesm_cstate 23:20 R pesm states
    //- tsq_state 27:24 R tsq states
  #define AXI_CLASS_QB_BUF_AVAIL              0x278 
    //  Reset = 24'h0
    //- pe_qb_buf_avail 23:0 R qb buf avails
  #define AXI_CLASS_RO_BUF_AVAIL              0x27c 
    //  Reset = 24'h0
    //- pe_ro_buf_avail 23:0 R ro buf avails
  #define AXI_CLASS_DOS_CONTRL1               0x280 
    //  Reset = 32'h0
    //- csr_dos_cntrl1 31:0 R/W dos control register 
    //  bit 0 dos enable, 
    //  bits 3:1 dos action, 
    //  bits 7:4 tcp flag combination enable, other bits are reserved
  #define AXI_CLASS_DOS_CONTRL2               0x284 
    //  Reset = 32'h0
    //- csr_dos_cntrl2 31:0 R/W dos control register 2 
    //  bit0 ipv4_sip_eq_dip_en, 
    //  bit1 ipv4_icmp_frag_en, 
    //  bit2 ipv4_icmp_ping_too_big_en,
    //  bit3 ipv4_udp_sp_eq_dp_en, 
    //  bit4 ipv4 tcp_flag chk, 
    //  bit5 ipv4 tcp sp eq dp, 
    //  bit6 ipv4 tcp frag_off1, 
    //  bit7 ipv4 tcp_syn_err, 
    //  bit8 ipv4 tcp_xmas, 
    //  bit9 ipv4 tcp_null, 
    //  bits 15:10 reserved, 
    //  bit16 ipv6_sip_eq_dip_en, 
    //  bit17 ipv6_icmp_frag_en, 
    //  bit18 ipv6_icmp_ping_too_big_en, 
    //  bit19 ipv6_udp_sp_eq_dp_en, 
    //  bit20 ipv6 tcp_flag chk, 
    //  bit21 ipv6 tcp sp eq dp, 
    //  bit22 ipv6 tcp frag_off1, 
    //  bit23 ipv6 tcp_syn_err, 
    //  bit24 ipv6 tcp_xmas, 
    //  bit25 ipv6 tcp_null, 
    //  bits 31:26 reserved,
  #define AXI_CLASS_DOS_TCP_FLAGCHK_COMB_VALUE1 0x288 
    //  Reset = 32'h0
    //- csr_dos_tcp_flagchk_comb_value1 31:0 R/W For TCP flags combination values. 6 bits for each combinations. 
    //  This register hold for comb 6 to 8
  #define AXI_CLASS_DOS_ICMPV4_MAX_PKTLEN     0x28c 
    //  Reset = 32'h4000
    //- csr_dos_icmpv4_max_pktlen 31:0 R/W icmp packets max packet lenght, initialized to 16k. It can go upto 64k.
  #define AXI_CLASS_INQ_AFULL_THRES           0x290 
    //  Reset = 16'h3f6
    //- csr_inq_afull_thres 15:0 R/W Class inq fifo is almost full threshold
  #define AXI_CLASS_DMEM_BRS_OFFSET           0x294 
    //  Reset = 9'h028
    //- csr_dmem_brs_offset 8:0 R/W offset of bridge result, in the dmem structure. 
    //  for 20 bit results, it can be 'h28 
    //  for 32 bit results it can be 48
  #define AXI_CLASS_SNOOP_SPL_MCAST_ADDR1_LSB 0x368 
  //  Reset = 32'h0
  //- csr_snoop_spl_mcast_addr1_lsb 31:0 R/W SPL multicast address1 lsb 32 bits [31:0]
  #define AXI_CLASS_SNOOP_SPL_MCAST_ADDR1_MSB 0x36C 
    //  Reset = 16'h0
    //- csr_snoop_spl_mcast_addr1_msb 15:0 R/W SPL multicast address1 msb remaining 16 bits
  #define AXI_CLASS_SNOOP_SPL_MCAST_ADDR2_LSB 0x370 
    //  Reset = 32'h0
    //- csr_snoop_spl_mcast_addr2_lsb 31:0 R/W SPL multicast address2 lsb 32 bits [31:0]
  #define AXI_CLASS_SNOOP_SPL_MCAST_ADDR2_MSB 0x374 
    //  Reset = 16'h0
    //- csr_snoop_spl_mcast_addr2_msb 15:0 R/W SPL multicast address2 msb remaining 16 bits
  #define AXI_CLASS_SNOOP_SPL_MCAST_MASK1_LSB 0x378 
    //  Reset = 32'h0
    //- csr_snoop_spl_mcast_mask1_lsb 31:0 R/W SPL multicast mask1 lsb 32 bits [31:0]
  #define AXI_CLASS_SNOOP_SPL_MCAST_MASK1_MSB 0x37C 
    //  Reset = 16'h0
    //- csr_snoop_spl_mcast_mask1_msb 15:0 R/W SPL multicast mask1 msb remaining 16 bits
  #define AXI_CLASS_SNOOP_SPL_MCAST_MASK2_LSB 0x380 
    //  Reset = 32'h0
    //- csr_snoop_spl_mcast_mask2_lsb 31:0 R/W SPL multicast mask2 lsb 32 bits [31:0]
  #define AXI_CLASS_SNOOP_SPL_MCAST_MASK2_MSB 0x384 
    //  Reset = 16'h0
    //- csr_snoop_spl_mcast_mask2_msb 15:0 R/W SPL multicast mask2 msb remaining 16 bits
  #define AXI_CLASS_LMEM_DATA_OFFSET          0x388 
    //  Reset = 9'h10
    //- csr_lmem_data_offset 8:0 R/W LMEM data offset
  #define AXI_CLASS_BCAST_PORTMAP             0x38C 
    //  Reset = 8'h0F
    //- csr_bcast_portmap 7:0 R/W NA for NPU AVB.BCAST port map.
  #define AXI_CLASS_DAMACHASH_HOST_CMD_REG        0x390 
    //  Reset = 32'h0
    //- damachash_host_cmd_reg 31:0 R/W direct access, hash host command register
  #define AXI_CLASS_DAMACHASH_HOST_MAC_ADDR1_REG  0x394 
    //  Reset = 32'h0
    //- damachash_host_mac_addr1 31:0 R/W direct access, hash host address register
  #define AXI_CLASS_DAMACHASH_HOST_MAC_ADDR2_REG  0x398 
    //  Reset = 32'h0
    //- damachash_host_mac_addr2 31:0 R/W direct access, hash host address register
  #define AXI_CLASS_DAMACHASH_HOST_MAC_ADDR3_REG  0x39C 
    //  Reset = 32'h0
    //- damachash_host_mac_addr3 31:0 R/W direct access, hash host address register
  #define AXI_CLASS_DAMACHASH_HOST_MAC_ADDR4_REG  0x3a0 
    //  Reset = 32'h0
    //- damachash_host_mac_addr4 31:0 R/W direct access, hash host address register
  #define AXI_CLASS_DAMACHASH_HOST_MAC_ADDR5_REG  0x3a4 
    //  Reset = 32'h0
    //- damachash_host_mac_addr5 31:0 R/W direct access, hash host address register
  #define AXI_CLASS_DAMACHASH_HOST_ENTRY_REG      0x3a8 
    //  Reset = 32'h0
    //- damachash_host_entry_reg 31:0 R/W direct access, hash host command register
  #define AXI_CLASS_DAMACHASH_HOST_STATUS_REG     0x3aC 
    //  Reset = 32'h0 
    //- damachash_host_status_reg 31:0 R/W direct access, hash host status register
  #define AXI_CLASS_DAMACHASH_HOST_DIRECT         0x3b0 
    //  Reset = 32'h0
    //- damachash_host_direct 31:0 R/W direct access, hash host command register
  #define AXI_CLASS_DAMACHASH_PE_CMD_REG          0x3b4 
    //  Reset = 32'h0
    //- damachash_pe_cmd_reg 31:0 R/W direct access, hash host command register
  #define AXI_CLASS_DAMACHASH_PE_MAC_ADDR1_REG    0x3b8 
    //  Reset = 32'h0
    //- damachash_pe_mac_addr1 31:0 R/W direct access, hash host address register
  #define AXI_CLASS_DAMACHASH_PE_MAC_ADDR2_REG    0x3bc 
    //  Reset = 32'h0
    //- damachash_pe_mac_addr2 31:0 R/W direct access, hash host address register
  #define AXI_CLASS_DAMACHASH_PE_MAC_ADDR3_REG    0x3c0 
    //  Reset = 32'h0
    //- pe_mac_addr3 31:0 R/W direct access, hash host address register
  #define AXI_CLASS_DAMACHASH_PE_MAC_ADDR4_REG    0x3c4 
    //  Reset = 32'h0
    //- damachash_pe_mac_addr4 31:0 R/W direct access, hash host address register
  #define AXI_CLASS_DAMACHASH_PE_MAC_ADDR5_REG    0x3c8 
    //  Reset = 32'h0
    //- damachash_pe_mac_addr5 31:0 R/W direct access, hash host address register
  #define AXI_CLASS_DAMACHASH_PE_ENTRY_REG        0x3cc 
    //  Reset = 32'h0
    //- damachash_pe_entry_reg 31:0 R/W direct access, hash host command register
  #define AXI_CLASS_DAMACHASH_PE_STATUS_REG       0x3d0 
    //  Reset = 32'h0
    //- damachash_pe_status_reg 31:0 R/W direct access, hash host status register
  #define AXI_CLASS_DAMACHASH_PE_DIRECT           0x3d4 
    //  Reset = 32'h0
    //- damachash_pe_direct 31:0 R/W direct access, hash host command register
  #define AXI_CLASS_DAMACHASH_FREELIST_ENTRIES    0x3d8 
    //  Reset = 32'h0
    //- damachash_freelist_entries 31:0 R/W direct access, hash host command register
  #define AXI_CLASS_DAMACHASH_FREELIST_HEAD_PTR   0x3dc 
    //  Reset = 32'h0
    //- damachash_freelist_head_ptr 31:0 R/W direct access, hash host command register
  #define AXI_CLASS_DAMACHASH_FREELIST_TAIL_PTR   0x3e0 
    //  Reset = 32'h0
    //- damachash_freelist_tail_ptr 31:0 R/W direct access, hash host command register
  #define AXI_CLASS_DAVLANHASH_HOST_CMD_REG       0x3e4 
    //  Reset = 32'h0
    //- davlanhash_host_cmd_reg 31:0 R/W direct access, hash host command register
  #define AXI_CLASS_DAVLANHASH_HOST_MAC_ADDR1_REG 0x3e8 
    //  Reset = 32'h0
    //- davlanhash_host_mac_addr1 31:0 R/W direct access, hash host address register
  #define AXI_CLASS_DAVLANHASH_HOST_MAC_ADDR2_REG 0x3ec 
    //  Reset = 32'h0
    //- davlanhash_host_mac_addr2 31:0 R/W direct access, hash host address register
  #define AXI_CLASS_DAVLANHASH_HOST_MAC_ADDR3_REG 0x3f0 
    //  Reset = 32'h0
    //- davlanhash_host_mac_addr3 31:0 R/W direct access, hash host address register
  #define AXI_CLASS_DAVLANHASH_HOST_MAC_ADDR4_REG 0x3f4 
    //  Reset = 32'h0
    //- davlanhash_host_mac_addr4 31:0 R/W direct access, hash host address register
  #define AXI_CLASS_DAVLANHASH_HOST_MAC_ADDR5_REG 0x3f8 
    //  Reset = 32'h0
    //- davlanhash_host_mac_addr5 31:0 R/W direct access, hash host address
  #define AXI_CLASS_DAVLANHASH_HOST_ENTRY_REG     0x3fc 
    //  Reset = 32'h0
    //- davlanhash_host_entry_reg 31:0 R/W direct access, hash host command register
  #define AXI_CLASS_DAVLANHASH_HOST_STATUS_REG    0x400 
    //  Reset = 32'h0
    //- davlanhash_host_status_reg 31:0 R/W direct access, hash host status register
  #define AXI_CLASS_DAVLANHASH_HOST_DIRECT        0x404 
    //  Reset = 32'h0
    //- davlanhash_host_direct 31:0 R/W direct access, hash host command register
  #define AXI_CLASS_DAVLANHASH_PE_CMD_REG         0x408 
    //  Reset = 32  h0
    //- davlanhash_pe_cmd_reg 31:0 R/W direct access, hash host command register
  #define AXI_CLASS_DAVLANHASH_PE_MAC_ADDR1_REG   0x40c 
    //  Reset = 32'h0
    //- davlanhash_pe_mac_addr1 31:0 R/W direct access, hash host address register
  #define AXI_CLASS_DAVLANHASH_PE_MAC_ADDR2_REG   0x410 
    //  Reset = 32'h0
    //- davlanhash_pe_mac_addr2 31:0 R/W direct access, hash host address register
  #define AXI_CLASS_DAVLANHASH_PE_MAC_ADDR3_REG   0x414 
    //  Reset = 32'h0
    //- davlanhash_pe_mac_addr3 31:0 R/W direct access, hash host address register
  #define AXI_CLASS_DAVLANHASH_PE_MAC_ADDR4_REG   0x418 
    //  Reset = 32'h0
    //- davlanhash_pe_mac_addr4 31:0 R/W direct access, hash host address register
  #define AXI_CLASS_DAVLANHASH_PE_MAC_ADDR5_REG   0x41c 
    //  Reset = 32'h0
    //- davlanhash_pe_mac_addr5 31:0 R/W direct access, hash host address register
  #define AXI_CLASS_DAVLANHASH_PE_ENTRY_REG       0x420 
    //  Reset = 32'h0
    //- davlanhash_pe_entry_reg 31:0 R/W direct access, hash host command register
  #define AXI_CLASS_DAVLANHASH_PE_STATUS_REG      0x424 
    //  Reset = 32'h0
    //- davlanhash_pe_status_reg 31:0 R/W direct access, hash host status register
  #define AXI_CLASS_DAVLANHASH_PE_DIRECT          0x428 
    //  Reset = 32'h0
    //- davlanhash_pe_direct 31:0 R/W direct access, hash host command register
  #define AXI_CLASS_DAVLANHASH_FREELIST_ENTRIES   0x42c 
    //  Reset = 32'h0
    //- davlanhash_freelist_entries 31:0 R/W direct access, hash host command register
  #define AXI_CLASS_DAVLANHASH_FREELIST_HEAD_PTR  0x430 
    //  Reset = 32'h0
    //- davlanhash_freelist_head_ptr 31:0 R/W direct access, hash host command register
  #define AXI_CLASS_DAVLANHASH_FREELIST_TAIL_PTR  0x434 
    //  Reset = 32'h0
    //- davlanhash_freelist_tail_ptr 31:0 R/W  direct access, hash host command register
  #define AXI_CLASS_PKT_CHAIN_CNTRL               0x438 
    //  Reset = 16'h0
    //- csr_pkt_chain_enable 0 R/W NA for NPU AVB.
    //- csr_pkt_chain_transmit_port 7:4 R/W NA for NPU AVB.
    //- csr_pkt_chain_srcport_bitmap 15:8 R/W NA for NPU AVB.
  #define AXI_CLASS_CACHE_HOST_CMD_REG            0x43c 
    //  Reset = 32'h0
    //- csr_cache_host_cmd_reg 31:0 R/W NA for NPU AVB.pkt chaining cache cmd reg for host request. 
    //  Bit 3:0 cmd 
    //  Bit 7:4 cache 
    //  Bit 31:16 Addr
  #define AXI_CLASS_CACHE_HOST_REG1               0x440 
    //  Reset = 32'h0
    //- csr_cache_host_reg1 31:0 R/W NA for NPU AVB.pkt chaining cache reg1 for host reguest
  #define AXI_CLASS_CACHE_HOST_REG2               0x444 
    //  Reset = 32'h0
    //- csr_cache_host_reg2 31:0 R/W NA for NPU AVB.pkt chaining cache reg2 for host reguest
  #define AXI_CLASS_CACHE_HOST_REG3               0x448 
    //  Reset = 32'h0
    //- csr_cache_host_reg3 31:0 R/W NA for NPU AVB.pkt chaining cache reg3 for host reguest
  #define AXI_CLASS_CACHE_HOST_REG4               0x44c 
    //  Reset = 32'h0)
    //- csr_cache_host_reg4 31:0 R/W NA for NPU AVB.pkt chaining cache reg4 for host reguest
  #define AXI_CLASS_CACHE_HOST_STATUS_REG         0x450 
    //  Reset = 32'h0
    //- csr_cache_host_status_reg 31:0 R/W NA for NPU AVB.pkt chaining cache status for host reguest 
    //  Bit 0 cmd done, 
    //  Bit 1 entry found, 
    //  Bit 2 entry added
  #define AXI_CLASS_CACHE_FW_CMD_REG      0x454 
    //  Reset = 32'h0
    //- csr_cache_fw_cmd_reg 31:0 R/W NA for NPU AVB.pkt chaining cache cmd reg for host request. 
    //  Bit 3:0 cmd 
    //  Bit 7:4 cache Bit
    //  31:16 Addr
  #define AXI_CLASS_CACHE_FW_REG1         0x458 
    //  Reset = 32'h0
    //- csr_cache_fw_reg1 31:0 R/W NA for NPU AVB.pkt chaining cache reg1 for firmware reguest
  #define AXI_CLASS_CACHE_FW_REG2         0x45c 
    //  Reset = 32'h0
    //- csr_cache_fw_reg2 31:0 R/W NA for NPU AVB.pkt chaining cache reg2 for firmware reguest
  #define AXI_CLASS_CACHE_FW_REG3         0x460 
    //  Reset = 32'h0
    //- csr_cache_fw_reg3 31:0 R/W NA for NPU AVB.pkt chaining cache reg3 for firmware reguest
  #define AXI_CLASS_CACHE_FW_REG4         0x464 
    //  Reset = 32'h0
    //- csr_cache_fw_reg4 31:0 R/W NA for NPU AVB.pkt chaining cache reg4 for firware reguest
  #define AXI_CLASS_CACHE_FW_STATUS_REG   0x468 
    //  Reset = 32'h0
    //- csr_cache_fw_status_reg 31:0 R/W NA for NPU AVB.pkt chaining cache status for firware reguest 
    //  Bit 0 cmd done, 
    //  Bit 1 entry found, 
    //  Bit 2 entry added
  #define AXI_CLASS_PORT0_STRUC1          0x46c 
  #define AXI_CLASS_PORT1_STRUC1          0x474 
  #define AXI_CLASS_PORT2_STRUC1          0x47c
  #define AXI_CLASS_PORT3_STRUC1          0x484
  #define AXI_CLASS_PORT4_STRUC1          0x48c
  #define AXI_CLASS_PORT5_STRUC1          0x494
  #define AXI_CLASS_PORT6_STRUC1          0x49c
  #define AXI_CLASS_PORT7_STRUC1          0x4a4
  #define AXI_CLASS_PORT8_STRUC1          0x548
  #define AXI_CLASS_PORT9_STRUC1          0x550
  #define AXI_CLASS_PORT10_STRUC1         0x558
  #define AXI_CLASS_PORT11_STRUC1         0x560
  #define AXI_CLASS_PORT12_STRUC1         0x568
  #define AXI_CLASS_PORT13_STRUC1         0x570
  #define AXI_CLASS_PORT14_STRUC1         0x578
  #define AXI_CLASS_PORT15_STRUC1         0x580
  #define AXI_CLASS_PORT16_STRUC1         0x588
    //  Reset = 29'h0
    //- csr_port0_tpid 15:0 R/W Port 0 tpid
    //- csr_port0_fallback_bd_id 28:16 R/W Port 0 fallback bd id
    #define AXI_CLASS_STRUC1_PORT_TPID_Pos               0
    #define AXI_CLASS_STRUC1_PORT_TPID_Msk               0x0000FFFF
    #define AXI_CLASS_STRUC1_PORT_FALLBACK_BDID_Pos      16
    #define AXI_CLASS_STRUC1_PORT_FALLBACK_BDID_Msk      0x1FFF0000
       #define AXI_CLASS_STRUC1_PORT_FALLBACK_BDID_DEF        0x1 // iports fallback bd id
      
    #define AXI_CLASS_STRUC1_FILL(fallback, tag)   _VAL2FLD(AXI_CLASS_STRUC1_PORT_TPID, tag) \
                                                 | _VAL2FLD(AXI_CLASS_STRUC1_PORT_FALLBACK_BDID, fallback)
                                                 
        
  #define AXI_CLASS_PORT0_STRUC2          0x470 
  #define AXI_CLASS_PORT1_STRUC2          0x478
  #define AXI_CLASS_PORT2_STRUC2          0x480
  #define AXI_CLASS_PORT3_STRUC2          0x488
  #define AXI_CLASS_PORT4_STRUC2          0x490
  #define AXI_CLASS_PORT5_STRUC2          0x498
  #define AXI_CLASS_PORT6_STRUC2          0x4a0
  #define AXI_CLASS_PORT7_STRUC2          0x4a8
  #define AXI_CLASS_PORT8_STRUC2          0x54c
  #define AXI_CLASS_PORT9_STRUC2          0x554
  #define AXI_CLASS_PORT10_STRUC2         0x55c
  #define AXI_CLASS_PORT11_STRUC2         0x564
  #define AXI_CLASS_PORT12_STRUC2         0x56c
  #define AXI_CLASS_PORT13_STRUC2         0x574
  #define AXI_CLASS_PORT14_STRUC2         0x57c
  #define AXI_CLASS_PORT15_STRUC2         0x584
  #define AXI_CLASS_PORT16_STRUC2         0x58c
    //  Reset = 22'h0
    //- csr_port0_shutdown 0 R/W Value 1 implements shutdown
    //- csr_port0_aft 7:4 R/W
    //  0: any tagging 
    //  1: tagged only 
    //  2: untagged only
      typedef enum {
        KX028_PortAcc_AnyTagging = 0,
        KX028_PortAcc_TaggedOnly,
        KX028_PortAcc_UntaggedOnly,
      } MDR_KX028_PortAcceptTag_e;    
    //- csr_port0_blockstate 11:8 R/W 
    //  0: forward, 
    //  1: blocked 
    //  2: Learnonly
      typedef enum {
        KX028_PortBlkState_Forwarding = 0,    // ok to learn SA and forward traffic
        KX028_PortBlkState_Blocked,           // do not learn SA; do not forward frames
        KX028_PortBlkState_LearnOnly,         // ok to learn SA, but do not forward frames
      } MDR_KX028_PortAcceptSTP_t;
    //- csr_port0_def_cfi 12 R/W Def CFI value
    //- csr_port0_def_pri 15:13 R/W Def prio field.
    //- csr_port0_def_tc 18:16 R/W def tc field
    //- csr_port0_trusted 19 R/W indicates the port is trusted
    //- csr_port0_vid_prefix 20 R/W port0 vid prefix
    //- csr_port0_untag_from_btable 21 R/W Port 0 Enabling of Untag from Btable
      #define AXI_CLASS_STRUC2_PORT_SHUTDOWN_Pos                 0
      #define AXI_CLASS_STRUC2_PORT_AFT_Pos                      4
      #define AXI_CLASS_STRUC2_PORT_BLOCKSTATE_Pos               8
      #define AXI_CLASS_STRUC2_PORT_DEF_CFI_Pos                  12
      #define AXI_CLASS_STRUC2_PORT_DEF_PRI_Pos                  13
      #define AXI_CLASS_STRUC2_PORT_DEF_TC_Pos                   16
      #define AXI_CLASS_STRUC2_PORT_TRUSTED_Pos                  19
      #define AXI_CLASS_STRUC2_PORT_VID_PREFIX_Pos               20
      #define AXI_CLASS_STRUC2_PORT_UNTAG_FROM_BTABLE_Pos        21

      #define AXI_CLASS_STRUC2_PORT_SHUTDOWN_Msk                0x00000001
      #define AXI_CLASS_STRUC2_PORT_AFT_Msk                     0x000000F0
      #define AXI_CLASS_STRUC2_PORT_BLOCKSTATE_Msk              0x00000F00
      #define AXI_CLASS_STRUC2_PORT_DEF_CFI_Msk                 0x00001000
      #define AXI_CLASS_STRUC2_PORT_DEF_PRI_Msk                 0x0000E000
      #define AXI_CLASS_STRUC2_PORT_DEF_TC_Msk                  0x00070000
      #define AXI_CLASS_STRUC2_PORT_TRUSTED_Msk                 0x00080000
      #define AXI_CLASS_STRUC2_PORT_VID_PREFIX_Msk              0x00100000
      #define AXI_CLASS_STRUC2_PORT_UNTAG_FROM_BTABLE_Msk       0x00200000
      
      #define AXI_CLASS_STRUC2_FILL(shdwn, aft, blst, cfi, pri, tc, trst, vid, untg)  \
              _VAL2FLD(AXI_CLASS_STRUC2_PORT_SHUTDOWN,    shdwn) \
            | _VAL2FLD(AXI_CLASS_STRUC2_PORT_AFT,         aft) \
            | _VAL2FLD(AXI_CLASS_STRUC2_PORT_BLOCKSTATE,  blst) \
            | _VAL2FLD(AXI_CLASS_STRUC2_PORT_DEF_CFI,     cfi) \
            | _VAL2FLD(AXI_CLASS_STRUC2_PORT_DEF_PRI,     pri) \
            | _VAL2FLD(AXI_CLASS_STRUC2_PORT_DEF_TC,      tc) \
            | _VAL2FLD(AXI_CLASS_STRUC2_PORT_TRUSTED,     trst) \
            | _VAL2FLD(AXI_CLASS_STRUC2_PORT_VID_PREFIX,  vid) \
            | _VAL2FLD(AXI_CLASS_STRUC2_PORT_UNTAG_FROM_BTABLE, untg)  

    
  #define AXI_CLASS_GLOBAL_CFG              0x4ac 
    //  Reset = 32'h0
    //- csr_glb_l2_special_punt_enable 0 R/W l2 special punt enable for all ports
    //- csr_glb_fallback_bd_entry 31:1 R/W global fall back bd entry, 
    //  16 bit default forward list for bd entry(vlan table)
    #define AXI_CLASS_GLOBAL_CFG_SPEC_PUNT_EN_ALL_Pos   0
    #define AXI_CLASS_GLOBAL_CFG_SPEC_PUNT_EN_ALL_Msk   0x0001UL
    #define AXI_CLASS_GLOBAL_CFG_BALLBACK_BR_ENTR_Pos   1
    #define AXI_CLASS_GLOBAL_CFG_BALLBACK_BR_ENTR_Msk   0xFFFFFFFEUL
    
    #define AXI_CLASS_GLOBAL_CFG_FILL(en, flbackentr) _VAL2FLD(AXI_CLASS_GLOBAL_CFG_SPEC_PUNT_EN_ALL,    en) \
                                                    | _VAL2FLD(AXI_CLASS_GLOBAL_CFG_BALLBACK_BR_ENTR,    flbackentr)
    
  #define AXI_CLASS_GLOBAL_CFG1             0x7e8 
    //  Reset = 24'h0
    //- csr_glb_fallback_bd_entry1 23:0 R/W global fall back bd entry msb. 
    //  First 31 bits are stored in GLOBAL_CFG and remaning bits of vlan action entry need to be configured.    
    #define AXI_CLASS_GLOBAL_CFG1_BALLBACK_BR_ENTR_Pos   0
    #define AXI_CLASS_GLOBAL_CFG1_BALLBACK_BR_ENTR_Msk   0x00FFFFFFUL

    #define AXI_CLASS_GLOBAL_CFG1_FILL(flbackentr)  _VAL2FLD(AXI_CLASS_GLOBAL_CFG_SPEC_PUNT_EN_ALL, flbackentr >> 31)
    //  Field in entry - used for learning VLAN
    #define AXI_CLASS_CFG1_FRW_ACK_Pos  10
    #define AXI_CLASS_CFG1_FRW_ACK_Msk   7

  #define AXI_CLASS_GLOBAL_CUTTHRU_REG      0x4b0 
    //  Reset = 32'h0
    //- csr_glb_cutthru_list 15:0 R/W global cutthru list
    //- csr_glb_cutthru_etype 31:16 R/W global cutthru etype
  #define AXI_CLASS_LPHY_PPHY_BITMAP1       0x4b4 
    //  Reset = 32'hCC520C20
    //- csr_lphy2pphy_map1 31:0 R/W logical phy to physical phy map - port width is 5 bits
  #define AXI_CLASS_LPHY_PPHY_BITMAP2       0x7f4 
    //  Reset = 32'hCD62D494
    //- csr_lphy2pphy_map2 31:0 R/W logical phy to physical phy map - port width is 5 bits
  #define AXI_CLASS_LPHY_PPHY_BITMAP3       0x7f8 
    //  Reset = 32'h3D
    //- csr_lphy2pphy_map3 31:0 R/W logical phy to physical phy map - port width is 5 bits  
  #define AXI_CLASS_DEF_PTPID               0x4b8 
    //  Reset = 16'h8100
    //- csr_def_ptpid 15:0 R/W tpid value to be compared for decoding PTAGed frames
  #define AXI_CLASS_PARSE_INCOMPLETE_ACTION 0x4bc 
    //  Reset = 2'h0
    //- csr_parse_incomplete_action 1:0 R/W 00 discard, 01 punt, 10 forward
  #define AXI_CLASS_PUNT_COS                0x4c0 
    //  Reset = 28'h6543210
    //- csr_punt_mgmt_cos 3:0 R/W COS value for punt operation of Management packet.
    //- csr_punt_sa_l2_spl_cos 7:4 R/W COS value for punt operation of L2 Special
    //- csr_punt_sa_miss_cos 11:8 R/W COS value for punt operation of SA Miss
    //- csr_punt_sa_relearn_cos 15:12 R/W COS value for punt operation of SA Relearn
    //- csr_punt_sa_is_actv_cos 19:16 R/W COS value for punt operation of SA is Active
    //- csr_punt_snp_upr_cos 23:20 R/W COS value for punt operation of SNOOP upper
    //- csr_punt_req_cos 27:24 R/W COS value for punt operation for PUNT requested
    #define AXI_CLASS_PUNT_COS_MGMT_Pos         0
    #define AXI_CLASS_PUNT_COS_MGMT_Msk         0x0000000FUL
    #define AXI_CLASS_PUNT_COS_L2_Pos           4
    #define AXI_CLASS_PUNT_COS_L2_Msk           0x000000F0UL
    #define AXI_CLASS_PUNT_COS_SA_MISS_Pos      8
    #define AXI_CLASS_PUNT_COS_SA_MISS_Msk      0x00000F00UL
    #define AXI_CLASS_PUNT_COS_SA_RELEARN_Pos   12
    #define AXI_CLASS_PUNT_COS_SA_RELEARN_Msk   0x0000F000UL
    #define AXI_CLASS_PUNT_COS_SA_ACTIVE_Pos    16
    #define AXI_CLASS_PUNT_COS_SA_ACTIVE_Msk    0x000F0000UL
    #define AXI_CLASS_PUNT_COS_SNOOP_Pos        20
    #define AXI_CLASS_PUNT_COS_SNOOP_Msk        0x00F00000UL
    #define AXI_CLASS_PUNT_COS_REQ_Pos         24
    #define AXI_CLASS_PUNT_COS_REQ_Msk        0x0F000000UL
    
    #define AXI_CLASS_PUNT_COS_FILL(mgm, l2, mis, rel, act, snoop, req) \
                  _VAL2FLD(AXI_CLASS_PUNT_COS_MGMT,       mgm) \
                | _VAL2FLD(AXI_CLASS_PUNT_COS_L2,         l2) \
                | _VAL2FLD(AXI_CLASS_PUNT_COS_SA_MISS,    mis) \
                | _VAL2FLD(AXI_CLASS_PUNT_COS_SA_RELEARN, rel) \
                | _VAL2FLD(AXI_CLASS_PUNT_COS_SA_ACTIVE,  act) \
                | _VAL2FLD(AXI_CLASS_PUNT_COS_SNOOP,      snoop) \
                | _VAL2FLD(AXI_CLASS_PUNT_COS_REQ,        req)
    
    
  #define AXI_CLASS_PORT_TCP_CHKSUM_OFFLOAD 0x4c4 
    //  Reset = 20'h0
    //- csr_port_tcp_chksum_offload 19:0 R/W tcp checksum offload bit. Each bit corresponds to each port.
  #define AXI_CLASS_GLOBAL_REGISTER         0x4c8 
    //  Reset = 32'h0
    //- csr_class_hw_glb_reg 31:0 R/W added for future use
  #define AXI_CLASS_DOS_ICMPV6_MAX_PKTLEN   0x4cc 
    //  Reset = 32'h4000
    //- csr_dos_icmpv6_max_pktlen 31:0 R/W
    //- icmp v6 packets max packet lenght, initialized to 16k. It can go upto 64k.
  #define AXI_CLASS_DEBUG_BUS01             0x4d0 
    //  Reset = NA
    //- csr_class_hw_dbg_bus0 15:0 R cbus_cstate[1:0],dbus_cstate[1:0],bufm_state[2:0],bufm_req[2:0],pesm_cstate[3:0]
    //- csr_class_hw_dbg_bus1 31:16 R parse_cstate,brfet_cstate,inq_fifo_full,inq_fifo_cnt
  #define AXI_CLASS_DEBUG_BUS23             0x4d4 
    //  Reset = NA
    //- csr_class_hw_dbg_bus2 15:0 R hw_pe_state,pesm_nstate
    //- csr_class_hw_dbg_bus3 31:16 R vlan_hash_debug_control[15:0]
  #define AXI_CLASS_DEBUG_BUS45             0x4d8 
    //  Reset = NA
    //- csr_class_hw_dbg_bus4 15:0 R vlan_hash_debug_control[31:16]
    //- csr_class_hw_dbg_bus5 31:16 R vlan_hash_debug_state[15:0]
  #define AXI_CLASS_DEBUG_BUS67             0x4dc 
    //  Reset = NA
    //- csr_class_hw_dbg_bus6 15:0 R vlan_hash_debug_state[31:16]
    //- csr_class_hw_dbg_bus7 31:16 R mac_hash_debug_control[15:0]
  #define AXI_CLASS_DEBUG_BUS89             0x4e0 
    //  Reset = NA
    //- csr_class_hw_dbg_bus8 15:0 R mac_hash_debug_control[31:16]
    //- csr_class_hw_dbg_bus9 31:16 R mac_hash_debug_state[15:0]
  #define AXI_CLASS_DEBUG_BUS1011           0x4e4 
    //  Reset = NA
    //- csr_class_hw_dbg_bus10 15:0 R mac_hash_debug_state[31:16]
    //- csr_class_hw_dbg_bus11 31:16 R NA for NPU AVB.pkt_chain_dbug_bus
  #define AXI_CLASS_TCP_OFFLOAD_PKTLEN_THRESH   0x4f8 
    //  Reset = 16'h5dc
    //- csr_tcp_offload_pktlen_thresh 15:0 R/W if frame lenght is less than this threshold
    //  and tcp offload enable is set,then only tcp offloading will be done in gpi transmit
  #define AXI_CLASS_NPU_CTRL                0x4fc 
    //  Reset = 32'h11004
    //- csr_punt_port_map 7:0 R/W Punt port map;only one bit should be set(hif1 or hif2) value of 4 --> hif1, 8 --> HIF2
    //- csr_bcast_q_no 10:8 R/W not used 
    //- csr_qos_mode 12 R/W Q number from TC value or cos 1 --> NPU; 0 --> not NPU
    //- csr_glbl_punt_dis 13 R/W disables the punt
    //- csr_egts_cos 19:16 R/W Q number for egress time-stamp report
    //- csr_discard_cos_n 31:24 R/W flood supression.
    //  setting a bit would make the respective cos value to flood when the action==ACT_COS_DISCARD; 
    //  if the value is zero and action==ACT_COS_DISCARD then the packet will be discarded    
    #define AXI_CLASS_NPU_CTRL_PUNT_PORT_MAP_Pos  0
    #define AXI_CLASS_NPU_CTRL_PUNT_PORT_MAP_Msk  0x000FUL
        #define AXI_CLASS_NPU_CTRL_HIF1_Msk         0x0004UL
        #define AXI_CLASS_NPU_CTRL_HIF2_Msk         0x0008UL
    #define AXI_CLASS_NPU_CTRL_QOS_NPU_Pos        12
    #define AXI_CLASS_NPU_CTRL_QOS_NPU_Msk        0x1000UL
    #define AXI_CLASS_NPU_CTRL_PUNT_DIS_Pos       13
    #define AXI_CLASS_NPU_CTRL_PUNT_DIS_Msk       0x2000UL
    #define AXI_CLASS_NPU_CTRL_EGTS_COS_Pos       16
    #define AXI_CLASS_NPU_CTRL_EGTS_COS_Msk       0x000F0000UL
    #define AXI_CLASS_NPU_CTRL_DISC_COSN_Pos      24
    #define AXI_CLASS_NPU_CTRL_DISC_COSN_Msk      0x0100000UL

    #define AXI_CLASS_NPU_CTRL_FILL(puntPortInd, qos, puntdis, etgs, floodon)     \
                              ((1UL << puntPortInd) & AXI_CLASS_NPU_CTRL_PUNT_PORT_MAP_Msk) \
                              | _VAL2FLD(AXI_CLASS_NPU_CTRL_QOS_NPU, qos) \
                              | _VAL2FLD(AXI_CLASS_NPU_CTRL_PUNT_DIS, puntdis) \
                              | _VAL2FLD(AXI_CLASS_NPU_CTRL_EGTS_COS, etgs) \
                              | _VAL2FLD(AXI_CLASS_NPU_CTRL_DISC_COSN, floodon)

    
  #define AXI_CLASS_NPU_CTRL1               0x7f0 
    //  Reset = 12'h200
    //- csr_punt_port_map_msb 11:0 R/W Punt port map;only one bit should be set. This is upper 12 bits of port map      
    #define AXI_CLASS_NPU_CTRL1_PUNT_PORT_MAP_Pos  0
    #define AXI_CLASS_NPU_CTRL1_PUNT_PORT_MAP_Msk  0x0FFFUL
    
    #define AXI_CLASS_NPU_CTRL1_FILL(puntPortInd)   (((1UL << puntPortInd) >> 12) & AXI_CLASS_NPU_CTRL1_PUNT_PORT_MAP_Msk)
    
  #define AXI_CLASS_UNMANAGED_PORTMAP       0x500 
    //  Reset = 24'h03
    //- csr_unmanaged_portmap 19:0 R/W Unmanaged(no software) mode def. port map.
    //- csr_unmanaged_cos 23:20 R/W Q number for unmanaged mode
  #define AXI_CLASS_PORT0_STRUC3            0x504 
  #define AXI_CLASS_PORT1_STRUC3            0x508 
  #define AXI_CLASS_PORT2_STRUC3            0x50c
  #define AXI_CLASS_PORT3_STRUC3            0x510
  #define AXI_CLASS_PORT4_STRUC3            0x514
  #define AXI_CLASS_PORT5_STRUC3            0x518
  #define AXI_CLASS_PORT6_STRUC3            0x51c
  #define AXI_CLASS_PORT7_STRUC3            0x520
  #define AXI_CLASS_PORT8_STRUC3            0x524
  #define AXI_CLASS_PORT9_STRUC3            0x528
  #define AXI_CLASS_PORT10_STRUC3           0x52c
  #define AXI_CLASS_PORT11_STRUC3           0x530
  #define AXI_CLASS_PORT12_STRUC3           0x534
  #define AXI_CLASS_PORT13_STRUC3           0x538
  #define AXI_CLASS_PORT14_STRUC3           0x53c
  #define AXI_CLASS_PORT15_STRUC3           0x540
  #define AXI_CLASS_PORT16_STRUC3           0x544
    //  Reset = 24'hfac688
    //- csr_port0_pcp 23:0 R/W cos(pcp) regeneration table for port0.cos(pcp) regeneration table for port0. 
    //  First 3 bits corresponds to cos(pcp) value replacement for input packet cos value of 0; 
    //  if input (cos==0) output cos = [2:0];
    //  if input (cos==1) output cos = [5:3]; 
    //  if input (cos==2) output cos = [8:6]; 
    //  if input (cos==3) output cos = [11:9]; 
    //  if input (cos==4) output cos = [15:12]; 
    //  if input (cos==5) output cos = [17:15]; 
    //  if input (cos==6) output cos = [20:18]; 
    //  if input (cos==7) output cos = [23:21];
  #define AXI_CLASS_PORT_IP_CHKSUM_OFFLOAD  0x7ec 
    //  Reset = 20'h0
    //- csr_port_ip_chksum_offload 19:0 R/W ip checksum offload bit. Each bit corresponds to each port.

   
       
    // HASH Commands Defines
    typedef enum
    {
        AXI_HASH_CMD_ID_INIT = 1,
        AXI_HASH_CMD_ID_ADD,
        AXI_HASH_CMD_ID_DEL,
        AXI_HASH_CMD_ID_UPDATE,
        AXI_HASH_CMD_ID_SEARCH,
        AXI_HASH_CMD_ID_MEM_READ,
        AXI_HASH_CMD_ID_MEM_WRITE,
        AXI_HASH_CMD_ID_FLUSH
    } AXI_HASH_CMD_ID;
    
    typedef struct {
      uint32_t cmd        : 4;    // 3..0 - AXI_HASH_CMD
      uint32_t reserved1  : 4;    // 7..4
      uint32_t isValidMAC1: 1;    // 8  - value in MAC1 register is Valid
      uint32_t isValidMAC2: 1;    // 9  - value in MAC2 register is Valid
      uint32_t isValidMAC3: 1;    // 10 - value in MAC3 register is Valid
      uint32_t isValidMAC4: 1;    // 11 - value in MAC4 register is Valid
      uint32_t isValidMAC5: 1;    // 12 - value in MAC5 register is Valid
      uint32_t isPortValid: 1;    // 13 - Port value is Valid
      uint32_t reserved2  : 2;    // 15..14
      uint32_t port       : 4;    // 16..19
      uint32_t reserved3  : 12;   // 20..31
    } AXI_HASH_CMD_Bits;
    
    typedef union {
      uint32_t              value;
      AXI_HASH_CMD_Bits  bits;
    } AXI_HASH_CMD_t;
    
    #define AXI_HASH_CMD_CMD_Pos          0
    #define AXI_HASH_CMD_CMD_Msk          0x000FUL
    #define AXI_HASH_CMD_VALID_MAC1_Pos   8
    #define AXI_HASH_CMD_VALID_MAC1_Msk   0x0100UL
    #define AXI_HASH_CMD_VALID_MAC2_Pos   9
    #define AXI_HASH_CMD_VALID_MAC2_Msk   0x0200UL
    #define AXI_HASH_CMD_VALID_MAC3_Pos   10
    #define AXI_HASH_CMD_VALID_MAC3_Msk   0x0400UL
    #define AXI_HASH_CMD_VALID_MAC4_Pos   11
    #define AXI_HASH_CMD_VALID_MAC4_Msk   0x0800UL
    #define AXI_HASH_CMD_VALID_MAC5_Pos   12
    #define AXI_HASH_CMD_VALID_MAC5_Msk   0x1000UL
    #define AXI_HASH_CMD_VALID_Port_Pos   13
    #define AXI_HASH_CMD_VALID_Port_Msk   0x2000UL
    #define AXI_HASH_CMD_Port_Pos         16
    #define AXI_HASH_CMD_Port_Msk         0xF0000UL
    //  For AXI_HASH_CMD_ID_MEM_READ / AXI_HASH_CMD_ID_MEM_WRITE
    #define AXI_HASH_CMD_ADDR_Pos         16
    #define AXI_HASH_CMD_ADDR_Msk         0xF0000UL

    //    AXI_CLASS_DAMACHASH_HOST_STATUS_REG def - Command Status Bits
    //     Description of STAUTS CMD REG:
    #define AXI_HASH_STAT_CMD_DONE               0x00000001
    #define AXI_HASH_STAT_ENTR_NFOUND            0x00000002
    #define AXI_HASH_STAT_INIT_DONE              0x00000004
    #define AXI_HASH_STAT_ENTR_ADD               0x00000008
    #define AXI_HASH_STAT_ENTR_MATCH             0x00000010
    #define AXI_HASH_STAT_REG_CLR                0xFFFFFFFF       
        
    //   AXI_CLASS_DAMACHASH_HOST_MAC_ADDR3_REG def 
    #define AXI_HASH_REG3_ENTRY_FRESH_FLAG        0x04000000
    #define AXI_HASH_REG3_ENTRY_STATIC_FLAG       0x08000000    
    //   AXI_CLASS_DAMACHASH_HOST_MAC_ADDR4_REG def 
    #define AXI_HASH_REG4_ENTRY_VALID_FLAG        0x08000000
    #define AXI_HASH_REG4_ENTRY_COLL_FLAG         0x04000000    

    //    MAC_TABLE TWO_FIELD
    #define MAC_TABLE_HASH_ENTRIES             0x1000
    #define MAC_TABLE_COLL_ENTRIES             0x1000
    #define MAC_TABLE_INIT_HEAD_PTR            0x1000
    #define MAC_TABLE_INIT_TAIL_PTR            0x1FFF
    
    //    VLAN_TABLE
    //    AXI_CLASS_BUS_ACCESS_ADDR defs 
    #define AXI_BUS_ACCESS_RD_FLAG                0x80000000UL
    
    #define AXI_BUS_VLAN_CMD_REG        	        0x2050000
    #define AXI_BUS_VLAN_MAC1_REG   	            (AXI_BUS_VLAN_CMD_REG + 0x04)
    #define AXI_BUS_VLAN_MAC2_REG                 (AXI_BUS_VLAN_CMD_REG + 0x08)
    #define AXI_BUS_VLAN_MAC3_REG                 (AXI_BUS_VLAN_CMD_REG + 0x0c)
    #define AXI_BUS_VLAN_MAC4_REG                 (AXI_BUS_VLAN_CMD_REG + 0x10)
    #define AXI_BUS_VLAN_MAC5_REG                 (AXI_BUS_VLAN_CMD_REG + 0x14)
    #define AXI_BUS_VLAN_ENTRY_REG                (AXI_BUS_VLAN_CMD_REG + 0x18)
    #define AXI_BUS_VLAN_STATUS_REG               (AXI_BUS_VLAN_CMD_REG + 0x1c)
    #define AXI_BUS_VLAN_DIRECT_REG               (AXI_BUS_VLAN_CMD_REG + 0x20)    
    
    //  Common defs
    #define AXI_VLAN_VALID_ID_MSK                 0x1FFF
    
    #define VLAN_TABLE_HASH_ENTRIES               0x40
    #define VLAN_TABLE_COLL_ENTRIES               0x40    
    #define VLAN_TABLE_INIT_HEAD_PTR              0x40
    #define VLAN_TABLE_INIT_TAIL_PTR              0x7f
    

//  --------------------------    WSP_GLOBAL_CSR ----------------------------------------
#define AXI_WSP_GLOBAL_BASE_ADDR                 0x630000
#define AXI_WSP_GLOBAL_END_OFFSET                0x63FFFF

#define AXI_WSP_VERSION                 0x00 
  //  Reset = 24'h05_0300
  //- npu_maintenance_rev 7:0 R Read only register that indicates the ID of the blockRead only register that indicates the Maintenace rev of NPU IP. 
  //  This is incremented for every release.
  //- npu_minor_rev 15:8 R Read Only register that indicates the Minor Revision of NPU IP. 
  //  It is incremented, if any software impact related fixes are done in IP
  //- npu_major_rev 23:16 R Read Only register that indicates the Major rev. It is incremented for architectural changes
#define AXI_WSP_CLASS_PE_CNT            0x04 
  //  Reset = 32'h0
  //- class_pe_cnt 31:0 R Contains the Class Block PE count. Currently it is set to 0
#define AXI_WSP_PE_IMEM_DMEM_SIZE       0x08 
  //  Reset = 32'h0006_000C
  //- class_pe_imem_size 15:0 R Size of IMEM memory in KB. Not applicable for NPU.
  //- class_pe_dmem_size 31:16 R Size of DMEM memory in KB. Not applicable for NPU.
#define AXI_WSP_LMEM_SIZE               0x0c 
  //  Reset = 32'h200
  //- lmem_size 31:0 R Size of WSP Internal memory(i.e. LMEM) in KB.
#define AXI_WSP_TMU_EMAC_PORT_COUNT     0x10 
  //  Reset = 32'h0011_0010
  //- emac_port_count 15:0 R Number of EMAC ports in WSP. For NPU it is tied to 16.
  //- tmu_phy_count 31:16 R Number of PHYS available at TMU. For NPU it is tied to 17.
#define AXI_WSP_EGPIS_PHY_NO            0x14 
  //  Reset = 32'h7654_3210
  //- egpi1_phy_num_at_tmu 3:0 R EGPI 1 Phy number at TMU; Value 4'hF is decoded as not connected to TMU. It is tied to 0.
  //- egpi2_phy_num_at_tmu 7:4 R EGPI 2 Phy number at TMU; Value 4'hF is decoded as not connected to TMU. It is tied to 1
  //- egpi3_phy_num_at_tmu 11:8 R EGPI 3 Phy number at TMU; Value 4'hF is decoded as not connected to TMU
  //- egpi4_phy_num_at_tmu 15:12 R EGPI 4 Phy number at TMU; Value 4'hF is decoded as not connected to TMU
  //- egpi5_phy_num_at_tmu 19:16 R EGPI 5 Phy number at TMU; Value 4'hF is decoded as not connected to TMU
  //- egpi6_phy_num_at_tmu 23:20 R EGPI 6 Phy number at TMU; Value 4'hF is decoded as not connected to TMU
  //- egpi7_phy_num_at_tmu 27:24 R EGPI 7 Phy number at TMU; Value 4'hF is decoded as not connected to TMU
  //- egpi8_phy_num_at_tmu 31:28 R EGPI 8 Phy number at TMU; Value 4'hF is decoded as not connected to TMU
#define AXI_WSP_HIF_SUPPORT_PHY_NO      0x18 
  //  Reset = 12'h111
  //- hif_support 3:0 R HIF block support is present 
  //- hif_phy_num_at_tmu 11:4 R HIF Phy number at TMU; Value 4'h2 is tied to this field
#define AXI_WSP_CLASS_HW_SUPPORT        0x1c 
  //  Reset = 2'h1
  //- class_hw_support 1:0 R CLASS HW block support. It is set to 1. Class HW is present.
#define AXI_WSP_SYS_GENERIC_CONTROL     0x20 
  //  Reset = 32'h0
  //- sys_generic_control 31:0 R/W This programmable control register bits goes as output ports(sys_generic_control) to the WSP. 
  //  Bit 31 is used for software configuration done. 
  //  Bit 30 is used for system soft reset
  #define AXI_WSP_SYS_GENERIC_CONTROL_SOFT_RESET_Msk      0x40000000UL
  #define AXI_WSP_SYS_GENERIC_CONTROL_SORT_CFG_DONE_Msk   0x80000000UL
#define AXI_WSP_SYS_GENERIC_STATUS      0x24 
  //  Reset = 32'h0 
  //- sys_generic_status 31:0 R This register shows the 32bit ports(sys_generic_status) to the WSP
#define AXI_WSP_SYS_GEN_CON0            0x28 
  //  Reset = 32'h00104000
  //- sys_gen_con0 31:0 R/W 32bit control register which go as ports to WSP
#define AXI_WSP_SYS_GEN_CON1            0x2c 
  //  Reset = 32'H0017ffff
  //- sys_gen_con1 31:0 R/W 32bit control register which go as ports to WSP
#define AXI_WSP_SYS_GEN_CON2            0x30 
  //  Reset = 32'h0
  //- sys_gen_con2 31:0 R/W For NPU these are not relevent as there is no soft processor. 
  //  4:0 selects UART pins
  //  CLASS_PE0_UART_SEL = 5'b0000,
  //  CLASS_PE1_UART_SEL = 5'b0001,
  //  CLASS_PE2_UART_SEL = 5'b0010,
  //  CLASS_PE3_UART_SEL = 5'b0011,
  //  CLASS_PE4_UART_SEL = 5'b0100, 
  //  CLASS_PE5_UART_SEL = 5'b0101, 
  //  CLASS_PE6_UART_SEL = 5'b0110, 
  //  CLASS_PE7_UART_SEL = 5'b0111,
  //  TMU_PE0_UART_SEL = 5'b10000,
  //  TMU_PE1_UART_SEL = 5'b10001,
  //  TMU_PE2_UART_SEL = 5'b10010,
  //  TMU_PE3_UART_SEL = 5'b10011; 
  //  UTILPE_UART_SEL = 5'b11000, 
  //  DPIPE_ UART_SEL = 5'b11001, 
  //  IPSECPE_ UART_SEL = 5'b11010.
#define AXI_WSP_SYS_GEN_CON3            0x34 
  //  Reset = 32'h2
  //- sys_gen_con3 31:0 R/W
  //  1:0 selects Endian Config for HBUS data output (64 bit)
  //  Bit0: swaps all 8 bytes 
  //  Bit1: swaps lower and upper 32bit
  //  3:2 selects Endian Config for HBUS data output (32 bit)
  //  Bit2: swaps all 8 bytes 
  //  Bit3: swaps lower and upper 32bit
#define AXI_WSP_SYS_GEN_CON4            0x38 
  //  Reset = 32'h0
  //- sys_gen_con4 31:0 R/W 32bit control register for future use
#define AXI_WSP_DBUG_BUS                0x3c 
  //  Reset = 16'h0
  //- csr_mod_dbg_bus_sel 7:0 R/W Module debug bus select 7:0
  //- csr_top_dbg_bus_sel 15:8 R/W Top debug bus select 15:8
#define AXI_WSP_CLK_FRQ                 0x40 
  //  Reset = 32'h0190_00C8
  //- wsp_sys_clk_frequency 15:0 R System clock frequency configured in decimal. For NPU it is set to 267Mhz
  //- wsp_pe_clk_frequency 31:16 R Processor clock frequency configured in decimal. For NPU it is set to 534Mhz
#define AXI_WSP_EMAC_CLASS_CONFIG       0x44 
  //  Reset = 16'hFF00
  //- emac_class_config 15:0 R/W Each bit corresponds specifies, the connection of class HW1 or class HW to emac. 
  //  Bit value 1, corresponds to class HW2 and if bit value is zero, the emac is connected to class hw1.
#define AXI_WSP_EGPIS_PHY_NO1           0x48 
  //  Reset = 32'hfedc_ba98
  //- egpi9_phy_num_at_tmu 3:0 R EGPI 9 Phy number at TMU; Value 4'hF is decoded as not connected to TMU.
  //- egpi10_phy_num_at_tmu 7:4 R EGPI 10 Phy number at TMU; Value 4'hF is decoded as not connected to TMU.
  //- egpi11_phy_num_at_tmu 11:8 R EGPI 11 Phy number at TMU; Value 4'hF is decoded as not connected to TMU
  //- egpi12_phy_num_at_tmu 15:12 R EGPI 12 Phy number at TMU; Value 4'hF is decoded as not connected to TMU
  //- egpi13_phy_num_at_tmu 19:16 R EGPI 13 Phy number at TMU; Value 4'hF is decoded as not connected to TMU
  //- egpi14_phy_num_at_tmu 23:20 R EGPI 14 Phy number at TMU; Value 4'hF is decoded as not connected to TMU
  //- egpi15_phy_num_at_tmu 27:24 R EGPI 15 Phy number at TMU; Value 4'hF is decoded as not connected to TMU
  //- egpi16_phy_num_at_tmu 31:28 R EGPI 16 Phy number at TMU; Value 4'hF is decoded as not connected to TMU

  
// ---------------------------   HIF1 - хост-интерфейс  ---------------------------------
#define AXI_HIF1_BASE_ADDR                       0x640000
#define AXI_HIF1_END_OFFSET                      0x64FFFF


  #define AXI_HIF_VERSION                 0x00 
    //  Reset = 32'h00000010
    //- hif_id 15:0 R Read only register that contains the ID of the block 
    //- hif_version 23:16 R Read Only register that indicates the Version of the Block
    //- hif_revision 31:24 R Read Only register that indicates the Revision of the Block
  #define AXI_HIF_TX_POLL_CTRL            0x04 
    //  Reset = 32'h00ff00ff
    //- csr_tx_bdp_poll_cntr1 15:0 R/W Number of cycles that HIF TX BDP block would wait before re-fetchecing the Descritpor
    //  control word if the previous descriptor fetched was disabled
    //- csr_tx_bdp_poll_cntr2 31:16 R/W Number of cycles that HIF TX BDP block would wait before writing updated bd back to
    //  system memory when number of bd's are less than treshold value.
  #define AXI_HIF_RX_POLL_CTRL            0x08 
    //  Reset = 32'h00ff00ff
    //- csr_rx_bdp_poll_cntr1 15:0 R/W Number of cycles that HIF RX BDP block would wait before re-fetchecing the Descritpor
    //  control word if the previous descriptor fetched was disabled
    //- csr_rx_bdp_poll_cntr2 31:16 R/W Number of cycles that HIF RX BDP block would wait before writing updated bd back to
    //  system memory when number of bd's are less than treshold value.
    #define AXI_HIF_TXRX_POLL_CTRL_RD_Pos   0
    #define AXI_HIF_TXRX_POLL_CTRL_RD_Msk   0xFFFFUL
    #define AXI_HIF_TXRX_POLL_CTRL_WR_Pos   16
    #define AXI_HIF_TXRX_POLL_CTRL_WR_Msk   0xFFFF0000UL       

  #define AXI_HIF_TXRX_POLL_CTRL_FILL(cntRD, cnrWR)  _VAL2FLD(AXI_HIF_TXRX_POLL_CTRL_RD, cntRD) | _VAL2FLD(AXI_HIF_TXRX_POLL_CTRL_WR, cnrWR)

  #define AXI_HIF_MISC                    0x0c 
    //  Reset = 32'h1
    //- csr_seq_num_check_en 0 R/W Sequence number check enable/disable. 
    //  1 : Enable sequecnce number checking of Fetched BDs, 
    //  0 : Disable sequnec number checking of fetched BDs. 
    //- csr_bdprd_axi_write_done 1 R/W If write_done is set to 1,ack will not be sent to new request till old request is written out.
    //  If write done is set to 0, request will be accpeted once data is written to internal fifo without really going out for buffer descriptor read 
    //- csr_bdpwr_axi_write_done 2 R/W If write_done is set to 1,ack will not be sent to new request till old request is written out.
    //  If write done is set to 0, request will be accpeted once data is written to internal fifo without really going out for buffer descriptor write
    //- csr_rxdxr_axi_write_done 3 R/W If write_done is set to 1,ack will not be sent to new request till old request is written out.
    //  If write done is set to 0, request will be accpeted once data is written to internal fifo without really going out for data write
    //- csr_txdxr_axi_write_done 4 R/W If write_done is set to 1,ack will not be sent to new request till old request is written out.
    //  If write done is set to 0, request will be accpeted once data is written to internal fifo without really going out for data read
    //- csr_hif_timeout_en 5 R/W HIF timeout enable for BDP fetch/update, Data write/read. 
    //- csr_bd_start_seq_num 31:16 R/W this will be initial seq number for the BD.All the channels should get BD's starting from this sequence number.
    //  it is common across all channels.
    #define AXI_HIF_MISC_SEQ_CHK_EN_Pos       0
    #define AXI_HIF_MISC_SEQ_CHK_EN_Msk       0x0001UL    
    #define AXI_HIF_MISC_BDPRD_WRDONE1_Pos    1
    #define AXI_HIF_MISC_BDPRD_WRDONE1_Msk    0x0002UL
    #define AXI_HIF_MISC_BDPRD_WRDONE2_Pos    2
    #define AXI_HIF_MISC_BDPRD_WRDONE2_Msk    0x0004UL
    #define AXI_HIF_MISC_BDPRD_WRDONE3_Pos    3
    #define AXI_HIF_MISC_BDPRD_WRDONE3_Msk    0x0008UL
    #define AXI_HIF_MISC_BDPRD_WRDONE4_Pos    4
    #define AXI_HIF_MISC_BDPRD_WRDONE4_Msk    0x0010UL    
    #define AXI_HIF_MISC_TIMEOUT_EN_Pos       5
    #define AXI_HIF_MISC_TIMEOUT_EN_Msk       0x0020UL        
    #define AXI_HIF_MISC_SEQ_START_NUM_Pos    16
    #define AXI_HIF_MISC_SEQ_START_NUM_Msk    0xFFFF0000UL

    #define AXI_HIF_MISC_FILL_EX(en, dn1, dn2, dn3, dn4, time, st)   _VAL2FLD(AXI_HIF_MISC_SEQ_CHK_EN, en) \
                                                      | _VAL2FLD(AXI_HIF_MISC_BDPRD_WRDONE1, dn1) \
                                                      | _VAL2FLD(AXI_HIF_MISC_BDPRD_WRDONE2, dn2) \
                                                      | _VAL2FLD(AXI_HIF_MISC_BDPRD_WRDONE3, dn3) \
                                                      | _VAL2FLD(AXI_HIF_MISC_BDPRD_WRDONE4, dn4) \
                                                      | _VAL2FLD(AXI_HIF_MISC_TIMEOUT_EN, time) \
                                                      | _VAL2FLD(AXI_HIF_MISC_SEQ_START_NUM, st) \

    #define AXI_HIF_MISC_FILL(en, dn, time, st)     AXI_HIF_MISC_FILL_EX(en, dn, dn, dn, dn, time, st)
    
  #define AXI_HIF_TIMEOUT_REG             0x10 
    //  Reset = 32'hffffffff
    //- csr_hif_timeout_val 31:0 R/W Need to program Max value for hif to timeout,when timeout enable is set
  #define AXI_HIF_SOFT_RESET              0x14 
    //  Reset = 4'h0
    //- sys_sw_reset_rx_path 0 R/W soft reset for rx path.this is not applicable for BD_ONE_RD_ONE_WR mode.
    //- sys_sw_reset_tx_path 1 R/W soft reset for tx path.this is not applicable for BD_ONE_RD_ONE_WR mode
    //- sys_sw_reset_tx_rx_path 2 R/W soft reset csr_sw_reset 3 R/W soft reset for csr
  #define AXI_HIF_INT_SRC                 0x40 
    //  Reset = 19'h0
    //- hif_ch0_int 0 R Channel 0 interrupt signal status
    //- hif_ch1_int 1 R Channel 1 interrupt signal status
    //- hif_ch2_int 2 R Channel 2 interrupt signal status
    //- hif_ch3_int 3 R Channel 3 interrupt signal status
    //- hif_err_int 16 R Hif error interrupt signal status
    //- hif_tx_fifo_err_int 17 R Tx fifo error interrupt signal status
    //- hif_rx_fifo_err_int 18 R Rx fifo error interrupt signal status
  #define AXI_HIF_ERR_INT_SRC             0x68 
    //  Reset = 15'h0
    //- hif_err_int 0 INT A value of '1' would indicate that interrupt from HIF block is pending. This value is a OR of all error interrupts in HIF block.
    //- dxr_csr_tx_pkt_len_err_int 1 INT HIF DXR TX Packet length error. It happens when we get packet greater than packet length mentioned in BD. 
    //  This field is not applicable to NPU AVB
    //- dxr_csr_tx_sof_err_int 2 INT HIF DXR TX sof error .It happens when sof is followed by sof with no eof(app side).
    //  This field is not applicable to NPU AVB
    //- dxr_csr_tx_data_err_int 3 INT HIF DXR TX Data error .It happens When we eof is followed by data with no sof in between.(app side). 
    //  This field is not applicable to NPU AVB
    //- dxr_csr_tx_eof_err_int 4 INT HIF DXR TX eof error .It happens when eof is followed by eof with no sof(app side).
    //  This field is not applicable to NPU AVB
    //- dxr_csr_rx_pkt_len_err_int 5 INT HIF DXR RX Packet length error. It happens when we get packet greater than packet length mentioned in BD. 
    //  This field is not applicable to NPU AVB
    //- dxr_csr_rx_sof_err_int 6 INT HIF DXR RX sof error .It happens when sof is followed by sof with no eof(app side).
    //  This field is not applicable to NPU AVB
    //- dxr_csr_rx_data_err_int 7 INT HIF DXR RX Data error .It happens When we eof is followed by data with no sof in between.(app side). 
    //  This field is not applicable to NPU AVB
    //- dxr_csr_rx_eof_err_int 8 INT HIF DXR RX eof error .It happens when eof is followed by eof with no sof(app side).
    //  This field is not applicable to NPU AVB
    //- bdp_csr_tx_rd_axi_err_int 9 INT HIF BDP TX RD axi error .It happens when tx bdp read block send request to axi with zero as data count
    //- bdp_csr_tx_wr_axi_err_int 10 INT HIF BDP TX WR axi error .It happens when tx bdp wirte block send request to axi with zero as data count
    //- bdp_csr_rx_rd_axi_err_int 11 INT HIF BDP RX RD axi error .It happens when rx bdp read block send request to axi with zero as data count
    //- bdp_csr_rx_wr_axi_err_int 12 INT HIF BDP RX WR axi error .It happens when rx bdp wirte block send request to axi with zero as data count
    //- dxr_csr_tx_axi_err_int 13 INT HIF DXR TX axi error .It happens when tx dxr block send request to axi with zero as data count
    //- dxr_csr_rx_axi_err_int 14 INT HIF DXR RX axi error .It happens when rx dxr block send request to axi with zero as data count
  #define AXI_HIF_ERR_INT_EN              0x6c 
    //  Reset = 15'h0
    //- hif_err_int_en 0 INT_EN Master Enable bit for HIF ERR interrupt
    //- dxr_csr_tx_pkt_len_err_int_en 1 INT_EN Enable bit for DXR TX packet length error interrupt. This field is not applicable to NPU AVB
    //- dxr_csr_tx_sof_err_int_en 2 INT_EN Enable bit for DXR TX SOF error interrupt. This field is not applicable to NPU AVB
    //- dxr_csr_tx_data_err_int_en 3 INT_EN  Enable bit for DXR TX Data error interrupt. This field is not applicable to NPU AVB
    //- dxr_csr_tx_eof_err_int_en 4 INT_EN Enable bit for DXR TX EOF error interrupt. This field is not applicable to NPU AVB
    //- dxr_csr_rx_pkt_len_err_int_en 5 INT_EN Enable bit for DXR RX packet length error interrupt. This field is not applicable to NPU AVB
    //- dxr_csr_rx_sof_err_int_en 6 INT_EN Enable bit for DXR RX SOF error interrupt. This field is not applicable to NPU AVB
    //- dxr_csr_rx_data_err_int_en 7 INT_EN Enable bit for DXR RX Data error interrupt. This field is not applicable to NPU AVB
    //- dxr_csr_rx_eof_err_int_en 8 INT_EN Enable bit for DXR RX EOF error interrupt. This field is not applicable to NPU AVB
    //- bdp_csr_tx_rd_axi_err_int_en 9 INT_EN Enable bit for TX BDP read axi error interrupt
    //- bdp_csr_tx_wr_axi_err_int_en 10 INT_EN Enable bit for TX BDP write axi error interrupt
    //- bdp_csr_rx_rd_axi_err_int_en 11 INT_EN Enable bit for RX BDP read axi error interrupt
    //- bdp_csr_rx_wr_axi_err_int_en 12 INT_EN Enable bit for RX BDP write axi error interrupt
    //- dxr_csr_tx_axi_err_int_en 13 INT_EN Enable bit for TX DXR axi error interrupt
    //- dxr_csr_rx_axi_err_int_en 14 INT_EN Enable bit for RX DXR axi error interrupt
  #define AXI_HIF_TX_FIFO_ERR_INT_SRC     0x70 
    //  Reset = 19'h0
    //- hif_tx_fifo_err_int 0 INT A value of '1' would indicate that interrupt from HIF block is pending. This value is a OR of all fifo error interrupts in HIF block for tx.
    //- bdp_csr_tx_rd_fifo_overrun_int 1 INT tx bd read fifo overrun
    //- bdp_csr_tx_wr_fifo_overrun_int 2 INT tx bd write fifo overrun
    //- dxr_csr_tx_fifo_overrun_int 3 INT tx data fifo overrun
    //- dxr_csr_tx_lbuf_overrun_int 4 INT tx data lbuf fifo overrun
    //- dxr_csr_tx_sof_ctrl_word_fifo_overrun_int 5 INT tx sof control word fifo overrun
    //- bdp_dxr_csr_tx_bd_ctrl_fifo_overrun_int 6 INT tx bd control fifo overrun
    //- dxr_csr_tx_sad_fifo_overrun_int 7 INT tx sad fifo overrun. This field is not applicable to NPU AVB
    //- bdp_csr_tx_bvalid_fifo_overrun_int 8 INT tx bvalid fifo overrun
    //- hif_axi_bdp_csr_tx_bvalid_fifo_overrun_int 9 INT tx hif axi bvalid fifo overrun
    //- bdp_csr_tx_rd_fifo_underrun_int 10 INT tx bd read fifo underrun
    //- bdp_csr_tx_wr_fifo_underrun_int 11 INT tx bd write fifo underrun
    //- dxr_csr_tx_fifo_underrun_int 12 INT tx data fifo underrun
    //- dxr_csr_tx_lbuf_underrun_int 13 INT tx data lbuf fifo underrun
    //- dxr_csr_tx_sof_ctrl_word_fifo_underrun_int 14 INT tx sof control word fifo underrun
    //- bdp_dxr_csr_tx_bd_ctrl_fifo_underrun_int 15 INT tx bd control fifo underrun
    //- dxr_csr_tx_sad_fifo_underrun_int 16 INT tx sad fifo underrun. This field is not applicable to NPU AVB
    //- bdp_csr_tx_bvalid_fifo_underrun_int 17 INT tx bvalid fifo underrun 
    //- hif_axi_bdp_csr_tx_bvalid_fifo_underrun_int 18 INT tx hif axi bvalid fifo underrun
  #define AXI_HIF_TX_FIFO_ERR_INT_EN      0x74 
    //  Reset = 19'h0
    //- hif_tx_fifo_err_int_en 0 INT_EN Master Enable bit for HIF TX FIFO ERR interrupt
    //- bdp_csr_tx_rd_fifo_overrun_int_en 1 INT_EN Enable bit for tx bdp rd fifo overrun
    //- bdp_csr_tx_wr_fifo_overrun_int_en 2 INT_EN Enable bit for tx bdp wr fifo overrun
    //- dxr_csr_tx_fifo_overrun_int_en 3 INT_EN Enable bit for tx dxr fifo overrun
    //- dxr_csr_tx_lbuf_overrun_int_en 4 INT_EN Enable bit for tx dxr lbuf fifo overrun
    //- dxr_csr_tx_sof_ctrl_word_fifo_overrun_int_en 5 INT_EN Enable bit for tx sof control word fifo overrun
    //- bdp_dxr_csr_tx_bd_ctrl_fifo_overrun_int_en 6 INT_EN Enable bit for tx bd ctrl fifo overrun
    //- dxr_csr_tx_sad_fifo_overrun_int_en 7 INT_EN Enable bit for tx sad fifo overrun. This field is not applicable to NPU AVB
    //- bdp_csr_tx_bvalid_fifo_overrun_int_en 8 INT_EN Enable bit for tx bvalid fifo overrun
    //- hif_axi_bdp_csr_tx_bvalid_fifo_overrun_int_en 9 INT_EN Enable bit for tx hif axi bvalid fifo overrun 
    //- bdp_csr_tx_rd_fifo_underrun_int_en 10 INT_EN Enable bit for tx bdp rd fifo underrun
    //- bdp_csr_tx_wr_fifo_underrun_int_en 11 INT_EN Enable bit for tx bdp wr fifo underrun
    //- dxr_csr_tx_fifo_underrun_int_en 12 INT_EN Enable bit for tx dxr fifo underrun
    //- dxr_csr_tx_lbuf_underrun_int_en 13 INT_EN Enable bit for tx dxr lbuf fifo underrun
    //- dxr_csr_tx_sof_ctrl_word_fifo_underrun_int_en 14 INT_EN Enable bit for tx sof control word fifo underrun
    //- bdp_dxr_csr_tx_bd_ctrl_fifo_underrun_int_en 15 INT_EN Enable bit for tx bd ctrl fifo underrun
    //- dxr_csr_tx_sad_fifo_underrun_int_en 16 INT_EN Enable bit for tx sad fifo underrun. This field is not applicable to NPU AVB
    //- bdp_csr_tx_bvalid_fifo_underrun_int_en 17 INT_EN Enable bit for tx bvalid fifo underrun
    //- hif_axi_bdp_csr_tx_bvalid_fifo_underrun_int_en 18 INT_EN Enable bit for tx hif axi bvalid fifo underrun
  #define AXI_HIF_RX_FIFO_ERR_INT_SRC     0x78 
    //  Reset = 21'h0
    //- hif_rx_fifo_err_int 0 INT A value of '1' would indicate that interrupt from HIF block is pending. This value is a OR of all fifo error interrupts in HIF block for rx.
    //- bdp_csr_rx_rd_fifo_overrun_int 1 INT rx bd read fifo overrun
    //- bdp_csr_rx_wr_fifo_overrun_int 2 INT rx bd write fifo overrun
    //- dxr_csr_rx_fifo_overrun_int 3 INT rx data fifo overrun
    //- dxr_csr_rx_lbuf_overrun_int 4 INT rx data lbuf fifo overrun
    //- dxr_csr_rx_sof_ctrl_word_fifo_overrun_int 5 INT rx sof control word fifo overrun
    //- dxr_csr_rx_eof_ctrl_word_fifo_overrun_int 6 INT rx eof control word fifo overrun. This field is not applicable to NPU AVB
    //- bdp_csr_rx_bvalid_fifo_overrun_int 7 INT rx bd update bvalid fifo overrun 
    //- hif_axi_bdp_csr_rx_bvalid_fifo_overrun_int 8 INT rx bd update hif axi bvalid fifo overrun
    //- dxr_csr_rx_bvalid_fifo_overrun_int 9 INT rx data bvalid fifo overrun 
    //- hif_axi_dxr_csr_rx_bvalid_fifo_overrun_int 10 INT rx data hif axi bvalid fifo overrun
    //- bdp_csr_rx_rd_fifo_underrun_int 11 INT rx bd read fifo underrun
    //- bdp_csr_rx_wr_fifo_underrun_int 12 INT rx bd write fifo underrun
    //- dxr_csr_rx_fifo_underrun_int 13 INT rx data fifo underrun
    //- dxr_csr_rx_lbuf_underrun_int 14 INT rx data lbuf fifo underrun
    //- dxr_csr_rx_sof_ctrl_word_fifo_underrun_int 15 INT rx sof control word fifo underrun
    //- dxr_csr_rx_eof_ctrl_word_fifo_underrun_int 16 INT rx eof control word fifo underrun. This field is not applicable to NPU AVB
    //- bdp_csr_rx_bvalid_fifo_underrun_int 17 INT rx bdp update bvalid fifo underrun
    //- hif_axi_bdp_csr_rx_bvalid_fifo_underrun_int 18 INT rx bdp update hif axi bvalid fifo underrun
    //- dxr_csr_rx_bvalid_fifo_underrun_int 19 INT rx data bvalid fifo underrun
    //- hif_axi_dxr_csr_rx_bvalid_fifo_underrun_int 20 INT rx bd hif axi bvalid fifo underrun
  #define AXI_HIF_RX_FIFO_ERR_INT_EN      0x7c 
    //  Reset = 21'h0
    //- hif_rx_fifo_err_int_en 0 INT_EN Master Enable bit for HIF RX FIFO ERR interrupt
    //- bdp_csr_rx_rd_fifo_overrun_int_en 1 INT_EN Enable bit for rx bdp rd fifo overrun
    //- bdp_csr_rx_wr_fifo_overrun_int_en 2 INT_EN Enable bit for rx bdp wr fifo overrun
    //- dxr_csr_rx_fifo_overrun_int_en 3 INT_EN Enable bit for rx dxr fifo overrun
    //- dxr_csr_rx_lbuf_overrun_int_en 4 INT_EN Enable bit for rx dxr lbuf fifo overrun
    //- dxr_csr_rx_sof_ctrl_word_fifo_overrun_int_en 5 INT_EN Enable bit for rx sof control word fifo overrun
    //- dxr_csr_rx_eof_ctrl_word_fifo_overrun_int_en 6 INT_EN Enable bit for rx eof control word fifo overrun. This field is not applicable to NPU AVB
    //- bdp_csr_rx_bvalid_fifo_overrun_int_en 7 INT_EN Enable bit for rx bvalid fifo overrun
    //- hif_axi_bdp_csr_rx_bvalid_fifo_overrun_int_en 8 INT_EN Enable bit for rx hif axi bvalid fifo overrun
    //- dxr_csr_rx_bvalid_fifo_overrun_int_en 9 INT_EN Enable bit for rx dxr bvalid fifo overrun
    //- hif_axi_dxr_csr_rx_bvalid_fifo_overrun_int_en 10 INT_EN Enable bit for rx dxr hif axi bvalid fifo overrun
    //- bdp_csr_rx_rd_fifo_underrun_int_en 11 INT_EN Enable bit for rx bdp rd fifo underrun
    //- bdp_csr_rx_wr_fifo_underrun_int_en 12 INT_EN Enable bit for rx bdp wr fifo underrun
    //- dxr_csr_rx_fifo_underrun_int_en 13 INT_EN Enable bit for rx dxr fifo underrun 
    //- dxr_csr_rx_lbuf_underrun_int_en 14 INT_EN Enable bit for rx dxr lbuf fifo underrun
    //- dxr_csr_rx_sof_ctrl_word_fifo_underrun_int_en 15 INT_EN Enable bit for rx sof control word fifo underrun
    //- dxr_csr_rx_eof_ctrl_word_fifo_underrun_int_en 16 INT_EN Enable bit for rx eof control word fifo underrun. This field is not applicable to NPU AVB
    //- bdp_csr_rx_bvalid_fifo_underrun_int_en 17 INT_EN Enable bit for rx bdp bvalid fifo underrun 
    //- hif_axi_bdp_csr_rx_bvalid_fifo_underrun_int_en 18 INT_EN Enable bit for rx bdp hif axi bvalid fifo underrun
    //- dxr_csr_rx_bvalid_fifo_underrun_int_en 19 INT_EN Enable bit for rx dxr bvalid fifo underrun 
    //- hif_axi_dxr_csr_rx_bvalid_fifo_underrun_int_en 20 INT_EN Enable bit for rx dxr hif axi bvalid fifo underrun
  #define AXI_HIF_TX_STATE                0x80 
    //  Reset = 32'h0
    //- dxr_csr_tx_state 15:0 R data transfer tx states
    //- bdp_csr_tx_state 31:16 R bdp transfer tx states
  #define AXI_HIF_TX_ACTV                 0x84 
    //  Reset = 32'h0
    //- dxr_csr_tx_actv 15:0 R This field indicates if dxr is active or not for tx
    //- bdp_csr_tx_actv 31:16 R This field indicates which bdp is active or not for tx
  #define AXI_HIF_TX_CURR_CH_NO           0x88 
    //  Reset = 32'h0
    //- dxr_csr_tx_curr_ch_no 15:0 R This field corresponds to current dxr active channel number on tx side
    //- bdp_csr_tx_curr_ch_no 31:16 R This field corresponds to current bdp active channel number on tx side
  #define AXI_HIF_DXR_TX_FIFO_CNT         0x8c 
    //  Reset = 32'h0
    //- dxr_csr_tx_fifo_cnt 31:0 R This field corresponds to fifo count of data fifo on tx side
  #define AXI_HIF_TX_CTRL_WORD_FIFO_CNT1  0x90 
    //  Reset = 16'h0
    //- dxr_csr_tx_sof_ctrl_word_fifo_cnt 15:0 R this field corresponds to fifo count of tx sof control word
  #define AXI_HIF_TX_CTRL_WORD_FIFO_CNT2  0x94 
    //  Reset = 32'h0
    //- bdp_dxr_csr_tx_bd_ctrl_fifo_cnt 15:0 R This field corresponds to fifo count of tx bd ctrl fifo
    //- dxr_csr_tx_sad_fifo_cnt 31:16 R fifo count of sad fifo. This is not applicable for NPU AVB
  #define AXI_HIF_TX_BVALID_FIFO_CNT      0x98 
    //  Reset = 16'h0
    //- bdp_csr_tx_bvalid_fifo_cnt 7:0 R fifo count of bdp_wr bvalid fifo(this will be updated whenever a burst of data is wriiten to systme memory from hif).
    //  this is reserved for BD_ONE_RD_ONE_WR mode
    //- hif_axi_bdp_csr_tx_bvalid_fifo_cnt 15:8 R fifo count of bdp_wr bvalid fifo on axi side.(this fifo will be updated whenever hif recives bvalid 
    //  response from axi for bd written out).this is reserved for BD_ONE_RD_ONE_WR mode
  #define AXI_HIF_TX_PKT_CNT1             0x9c 
    //  Reset = 32'h0
    //- hif2app_csr_tx_pkt_cnt 31:0 R This field corresponds to packet count of packets going out of hif to application.
  #define AXI_HIF_TX_PKT_CNT2             0xa0 
    //  Reset = 32'h0
    //- axi2hif_csr_tx_pkt_cnt 31:0 R This field corresponds to packet count of packets coming to hif from system memory through axi bus.
  #define AXI_HIF_RX_STATE                0xa4 
    //  Reset = 32'h0
    //- dxr_csr_rx_state 15:0 R data transfer rx states
    //- bdp_csr_rx_state 31:16 R bdp transfer rx states
  #define AXI_HIF_RX_ACTV                 0xa8 
    //  Reset = 32'h0
    //- dxr_csr_rx_actv 15:0 R This field indicates if dxr is active or not for rx
    //- bdp_csr_rx_actv 31:16 R This field indicates which bdp is active or not for rx
  #define AXI_HIF_RX_CURR_CH_NO           0xac 
    //  Reset = 32'h0
    //- dxr_csr_rx_curr_ch_no 15:0 R This field corresponds to current dxr active channel number on rx side
    //- bdp_csr_rx_curr_ch_no 31:16 R This field corresponds to current bdp active channel number on rx side
  #define AXI_HIF_DXR_RX_FIFO_CNT         0xb0 
    //  Reset = 32'h0
    //- dxr_csr_rx_fifo_cnt 31:0 R This field corresponds to fifo count of data fifo on rx side
  #define AXI_HIF_RX_CTRL_WORD_FIFO_CNT   0xb4 
    //  Reset = 32'h0)
    //- dxr_csr_rx_sof_ctrl_word_fifo_cnt 15:0 R this field corresponds to fifo count of rx sof control word
    //- dxr_csr_rx_eof_ctrl_word_fifo_cnt 31:16 R this field corresponds to fifo count of rx eof control word. 
    //  This is not applicalble for NPU AVB
  #define AXI_HIF_RX_BVALID_FIFO_CNT      0xb8 
    //  Reset = 32'h0
    //- bdp_csr_rx_bvalid_fifo_cnt 7:0 R fifo count of bdp_wr bvalid fifo for rx
    //  (this will be updated whenever a burst of data is wriiten to systme memory from hif)
    //- hif_axi_bdp_csr_rx_bvalid_fifo_cnt 15:8 R fifo count of bdp_wr bvalid fifo on axi side for rx.
    //  (this fifo will be updated whenever hif recives bvalid response from axi for bd written out)
    //- dxr_csr_rx_bvalid_fifo_cnt 23:16 R fifo count of data_wr bvalid fifo 
    //  (this will be updated whenever burst of data is written to system meory from hif)
    //- hif_axi_dxr_csr_rx_bvalid_fifo_cnt 31:24 R fifo count of data_wr bvalid fifo on axi side.
    //  (this will be updated whenever hif recieves bvalud response from axi for data written out)
  #define AXI_HIF_RX_PKT_CNT1             0xbc 
    //  Reset = 32'h0
    //- app2hif_csr_rx_pkt_cnt 31:0 R This field corresponds to packet count of packets coming to hif from application.
  #define AXI_HIF_RX_PKT_CNT2             0xc0 
    //  Reset = 32'h0
    //- hif2axi_csr_rx_pkt_cnt 31:0 R This field corresponds to packet count of packets going out of hif to system memory through axi bus.
  #define AXI_HIF_DMA_BASE_ADDR           0xc4 
    //  Reset = 32'hFFFF_FFFF
    //- hif_dma_base_addr 31:0 R/W HIF DMA upper base address for [63:32] bits, 
    //  This address will be concatenated with BD address or Data buffer addres, SO that DMA address width will be 64-bit
  #define AXI_HIF_DMA_BURST_SIZE_ADDR     0xc8 
    //  Reset = 3'h1)
    //- hif_dma_burst_size 2:0 R/W HIF programmable DMA busrt size. Default : 128byte
    //  00- 128byte burst, 
    //  01- 256-byte, 
    //  10- 512byte, 
    //  11- 1024byte.
    #define AXI_HIF_DMA_BURST_128Bytes      0
    #define AXI_HIF_DMA_BURST_256Bytes      1
    #define AXI_HIF_DMA_BURST_512Bytes      2
    #define AXI_HIF_DMA_BURST_1024Bytes     3
    
  #define AXI_HIF_RX_QUEUE_MAP_CH_NO_ADDR   0xcc 
    //  Reset = 32'h76543210
    //- csr_hif_rx_queue_map_ch_no 31:0 R/W TMU queue mapping to HIF RX channels. 
    //  [3:0]- indicates RX ch number mapped to TMU queue0, 
    //  [7:4]-indicates RX ch number mapped to TMU Queue1,
    //  [11:8]-indicates RX ch mapped to TMU Queue2, 
    //  [15:12]-indicates RX ch number mapped to TMU Queue 3, 
    //  [19:16]- inidcates RX ch number mapped to TMU Queue 4, 
    //  [23:20]-indicates RX ch number mapped to TMU Queue5, 
    //  [27:24]- indicates RX ch number mapped to TMU Queue6, 
    //  [31:28]-indicates RX ch number mapped to TMU Queue 7
    #define AXI_HIF_RX_CH_TO_TMU_QUE1_Pos   0
    #define AXI_HIF_RX_CH_TO_TMU_QUE1_Msk   0x0000000FUL
    #define AXI_HIF_RX_CH_TO_TMU_QUE2_Pos   4
    #define AXI_HIF_RX_CH_TO_TMU_QUE2_Msk   0x000000F0UL
    #define AXI_HIF_RX_CH_TO_TMU_QUE3_Pos   8
    #define AXI_HIF_RX_CH_TO_TMU_QUE3_Msk   0x00000F00UL
    #define AXI_HIF_RX_CH_TO_TMU_QUE4_Pos   12
    #define AXI_HIF_RX_CH_TO_TMU_QUE4_Msk   0x0000F000UL
    #define AXI_HIF_RX_CH_TO_TMU_QUE5_Pos   16
    #define AXI_HIF_RX_CH_TO_TMU_QUE5_Msk   0x000F0000UL
    #define AXI_HIF_RX_CH_TO_TMU_QUE6_Pos   20
    #define AXI_HIF_RX_CH_TO_TMU_QUE6_Msk   0x00F00000UL
    #define AXI_HIF_RX_CH_TO_TMU_QUE7_Pos   24
    #define AXI_HIF_RX_CH_TO_TMU_QUE7_Msk   0x0F000000UL
    #define AXI_HIF_RX_CH_TO_TMU_QUE8_Pos   28
    #define AXI_HIF_RX_CH_TO_TMU_QUE8_Msk   0xF0000000UL
    
    #define AXI_HIF_RX_QUEUE_MAP_CH_FILL(q1, q2, q3, q4, q5, q6, q7, q8)  _VAL2FLD(AXI_HIF_RX_CH_TO_TMU_QUE1, q1) \
                                                                        | _VAL2FLD(AXI_HIF_RX_CH_TO_TMU_QUE2, q2) \
                                                                        | _VAL2FLD(AXI_HIF_RX_CH_TO_TMU_QUE3, q3) \
                                                                        | _VAL2FLD(AXI_HIF_RX_CH_TO_TMU_QUE4, q4) \
                                                                        | _VAL2FLD(AXI_HIF_RX_CH_TO_TMU_QUE5, q5) \
                                                                        | _VAL2FLD(AXI_HIF_RX_CH_TO_TMU_QUE6, q6) \
                                                                        | _VAL2FLD(AXI_HIF_RX_CH_TO_TMU_QUE7, q7) \
                                                                        | _VAL2FLD(AXI_HIF_RX_CH_TO_TMU_QUE8, q8)
   
  #define AXI_HIF_LTC_PKT_CTRL_ADDR         0xd0 
    //  Reset = 1'h0
    //- csr_hif_tx_ltc_pkt_flow_en 0 R/W HIF TX packet flow through Launch time control(LTC) module flow enable. 
    //  When this bit is enabled, HIF TX will accept maximum "csr_hif_tx_ltc_max_pkt_cnt_per_ch"
    //  packets after that wait fot LTC read enable signal to fetch next packet else packets will
    //  be accpted by HIF TX till it has space in internal memory
    
  //  CHANNELS baseAddr:
  #define AXI_HIF_CH0_BASE_ADDR                 0x0100
  #define AXI_HIF_CH1_BASE_ADDR                 0x0200
  #define AXI_HIF_CH2_BASE_ADDR                 0x0300
  #define AXI_HIF_CH3_BASE_ADDR                 0x0400
  #define AXI_HIF_CH4_BASE_ADDR                 0x0500
  #define AXI_HIF_CH5_BASE_ADDR                 0x0600
  #define AXI_HIF_CH6_BASE_ADDR                 0x0700
  #define AXI_HIF_CH7_BASE_ADDR                 0x0800
  #define AXI_HIF_CH8_BASE_ADDR                 0x0900
  #define AXI_HIF_CH9_BASE_ADDR                 0x0A00
  #define AXI_HIF_CH10_BASE_ADDR                0x0B00
  #define AXI_HIF_CH11_BASE_ADDR                0x0C00
  #define AXI_HIF_CH12_BASE_ADDR                0x0D00
  #define AXI_HIF_CH13_BASE_ADDR                0x0E00
  #define AXI_HIF_CH14_BASE_ADDR                0x0F00
  #define AXI_HIF_CH15_BASE_ADDR                0x1000  
  //  Registers:
    #define AXI_HIF_CH_CTRL                       0x000   
      //  Reset = 18'h0
      //- csr_tx_dma_en_ch0_out 0 R/W TX DMA enable bit 1- Enabled, 0 -Disabled
      //- csr_tx_bdp_poll_cntr_en_ch0_out 1 R/W Setting this bit would cause TX
      //  Buffer Descriptor processor(BDP) to poll for descriptor valid till descriptor valid bit is set
      //- csr_rx_dma_en_ch0_out 16 R/W RX DMA enable bit 1- Enabled, 0 - Disabled. This bit is reserved in BD_ONE_RD_ONE_WR mode
      //- csr_rx_bdp_poll_cntr_en_ch0_out 17 R/W Setting this bit would cause RX Buffer Descriptor processor(BDP) to
      //  poll for descriptor valid till descriptor valid bit is set. This bit is reserved in BD_ONE_RD_ONE_WR mode
    #define AXI_HIF_CH_RX_BDP_WR_LOW_ADDR         0x004
      //  Reset = 32'b0
      //- csr_rx_bdp_wr_bd_low_addr_ch0_out 31:0 R/W This register field contains the lower base address of the Receive Sections DMA. 
      //  This register must be updated only when the DMA is IDLE
    #define AXI_HIF_CH_RX_BDP_WR_HIGH_ADDR        0x008
      //  Reset = 32'b0
      //- csr_rx_bdp_wr_bd_high_addr_ch0_out 31:0 R/W This register field contains the upper base address of the Receive Sections DMA. 
      //  This sregister must be update only when the DMA is IDLE. This field is reserved for BD size 16Bytes and not appilcable for NPU AVB
    #define AXI_HIF_CH_RX_BDP_RD_LOW_ADDR         0x00c
      //  Reset = 32'b0
      //- csr_rx_bdp_rd_bd_low_addr_ch0_out 31:0 R/W This register field contains the lower base address of the Receive Sections DMA. 
      //  This sregister must be update only when the DMA is IDLE. This field is reserved in BD_ONE_RD_ONE_WR mode
    #define AXI_HIF_CH_RX_BDP_RD_HIGH_ADDR        0x010
      //  Reset = 32'b0
      //- csr_rx_bdp_rd_bd_high_addr_ch0_out 31:0 R/W This register field contains the upper base address of the Receive Sections DMA. 
      //  This sregister must be update only when the DMA is IDLE.
      //  This field is reserved in BD_ONE_RD_ONE_WR mode and for BD size is 16bytes and not applicable for NPU AVB
    #define AXI_HIF_CH_TX_BDP_WR_LOW_ADDR         0x014  
      //  Reset = 32'b0
      //- csr_tx_bdp_wr_bd_low_addr_ch0_out 31:0 R/W This register field contains the lower base address of the Receive Sections DMA. 
      //  This sregister must be update only when the DMA is IDLE. This field is reserved in BD_ONE_RD_ONE_WR mode
    #define AXI_HIF_CH_TX_BDP_WR_HIGH_ADDR        0x018
      //  Reset = 32'b0
      //- csr_tx_bdp_wr_bd_high_addr_ch0_out 31:0 R/W This register field contains the upper base address of the Receive Sections DMA. 
      //  This sregister must be update only when the DMA is IDLE.
      //  This field is reserved in BD_ONE_RD_ONE_WR mode and for BD size 16bytes mode and not appilcable for NPU AVB
    #define AXI_HIF_CH_TX_BDP_RD_LOW_ADDR         0x01c
      //  Reset = 32'b0
      //- csr_tx_bdp_rd_bd_low_addr_ch0_out 31:0 R/W This register field contains the lower base address of the Transmit Sections DMA. 
      //  This sregister must be update only when the DMA is IDLE
    #define AXI_HIF_CH_TX_BDP_RD_HIGH_ADDR        0x020
      //  Reset = 32'b0
      //- csr_tx_bdp_rd_bd_high_addr_ch0_out 31:0 R/W This register field contains the upper base address of the Transmit Sections DMA. 
      //  This sregister must be update only when the DMA is IDLE. This field is reserved for BD size 16bytes and not applicable for NPU AVB
    #define AXI_HIF_CH_RX_WRBK_BD_BUFFER_SIZE     0x024
      //  Reset = 16'h28
      //- csr_rx_wr_bck_bd_ch0_buffer_size 15:0 R/W RX WR Back Bd buffer size to wrap around .By default we keep space for 40 double words.
    #define AXI_HIF_CH_RX_START                   0x028
      //  Reset = 1'b0
      //- csr_rx_bdp_ch0_start_out 0 R/W Setting this bit to '1' would start Rx BDP (Buffer Descriptor Processor) to fetch a descriptor 
      //  and hence this bit should be enabled only when all the DMA descriptor programming is done.This bit is reserved in BD_ONE_RD_ONE_WR mode
    #define AXI_HIF_CH_TX_WRBK_BD_BUFFER_SIZE     0x02c
      //  Reset = 16'h28
      //- csr_tx_wr_bck_bd_ch0_buffer_size 15:0 R/W TX WR Back Bd buffer size to wrap around.
      //  By default we keep space for 40 double words. This field is reserved in BD_ONE_RD_ONE_WR mode
    #define AXI_HIF_CH_TX_START                   0x030
      //  Reset = 1'b0
      //- csr_tx_bdp_ch0_start_out 0 R/W Setting this bit to '1' would start Tx BDP (Buffer Descriptor Processor) to fetch a descriptor 
      //  and hence this bit should be enabled only when all the DMA descriptor programming is done.
    #define AXI_HIF_CH_INT_SRC                    0x060
      //  Reset = 11'b0
      //- hif_ch0_int 0 INT A value of '1' would indicate that interrupt from HIF block is pending. This value is a OR of all interrupts in HIF block 
      //- bdp_csr_rx_cbd_ch0_int 1 INT this bit is set if any of cbd_int_en in BD is set within burst of BD's written out.
      //- bdp_csr_rx_pkt_ch0_int 2 INT this bit is set if any of pkt_int_en in BD is set within burst of BD's written out.
      //- bdp_csr_tx_cbd_ch0_int 3 INT this bit is set if any of cbd_int_en in BD is set within burst of BD's written out. This is reserved for BD_ONE_RD_ONE_WR mode
      //- bdp_csr_tx_pkt_ch0_int 4 INT this bit is set if any of pkt_int_en in BD is set within burst of BD's written out.This is reserved for BD_ONE_RD_ONE_WR mode
      //- bdp_rd_csr_rx_timeout_ch0_int 5 INT HIF Rx BD Read Timeout
      //- bdp_wr_csr_rx_timeout_ch0_int 6 INT HIF Rx BD WriteTimeout
      //- bdp_rd_csr_tx_timeout_ch0_int 7 INT HIF Tx BD Read Timeout
      //- bdp_wr_csr_tx_timeout_ch0_int 8 INT HIF Tx BD WriteTimeout.this is reserved for BD_ONE_RD_ONE_WR mode
      //- dxr_csr_rx_timeout_ch0_int 9 INT HIF DXR RX timeout
      //- dxr_csr_tx_timeout_ch0_int 10 INT HIF DXR TX timeout(common for both data as well as sad)
    #define AXI_HIF_CH_INT_EN                     0x064
      //  Reset = 11'b0
      //- hif_ch0_int_en 0 INT_EN Master Enable bit for HIF interrupts
      //- bdp_csr_rx_cbd_ch0_int_en 1 INT_EN Enable bit for HIF RX BDP interrupt
      //- bdp_csr_rx_pkt_ch0_int_en 2 INT_EN Enable bit for HIF RX Packet completion Interrupt
      //- bdp_csr_tx_cbd_ch0_int_en 3 INT_EN Enable bit for HIF TX BDP interrupt
      //- bdp_csr_tx_pkt_ch0_int_en 4 INT_EN Enable bit for HIF TX Packet completion Interrupt
      //- bdp_rd_csr_rx_timeout_ch0_int_en 5 INT_EN Enable bit for HIF RX BDP Rd timeout interrupt
      //- bdp_wr_csr_rx_timeout_ch0_int_en 6 INT_EN Enable bit for HIF RX BDP WR timeout interrupt
      //- bdp_rd_csr_tx_timeout_ch0_int_en 7 INT_EN Enable bit for HIF RX BDP Rd timeout interrupt
      //- bdp_wr_csr_tx_timeout_ch0_int_en 8 INT_EN Enable bit for HIF RX BDP WR timeout interrupt
      //- dxr_csr_rx_timeout_ch0_int_en 9 INT_EN Enable bit for DXR RX timeout interrupt
      //- dxr_csr_tx_timeout_ch0_int_en 10 INT_EN Enable bit for DXR TX timeout interrupt
    #define AXI_HIF_CH_TX_RD_CURR_BD_LOW_ADDR     0x080
      //  Reset = 32'h0
      //- bdp_rd_curr_tx_bd_low_addr_ch0_in 31:0 R This register field contains the current descritptor lower address being processed by Buffer Descriptor Processor (BDP)
    #define AXI_HIF_CH_TX_RD_CURR_BD_HIGH_ADDR    0x084
      //  Reset = 32'h0
      //- bdp_rd_curr_tx_bd_high_addr_ch0_in 31:0 R This register field contains the current descritptor upper address being processed by Buffer Descriptor Processor (BDP). 
      //  This field is reverved for BD size 16bytes and not applicable for NPU AVB
    #define AXI_HIF_CH_TX_WR_CURR_BD_LOW_ADDR     0x088
      //  Reset = 32'h0
      //- bdp_wr_curr_tx_bd_low_addr_ch0_in 31:0 R This register field contains the current descritptor lower address being processed by Buffer Descriptor Processor (BDP).
      //  this is reserved for BD_ONE_RD_ONE_WR mode.
    #define AXI_HIF_CH_TX_WR_CURR_BD_HIGH_ADDR    0x08c
      //  Reset = 32'h0
      //- bdp_wr_curr_tx_bd_high_addr_ch0_in 31:0 R This register field contains the current descritptor upper address being processed by Buffer Descriptor Processor (BDP).
      //  This is reserved for BD_ONE_RD_ONE_WR mode and for BD size 16bytes and not applicable for NPU AVB
    #define AXI_HIF_CH_BDP_TX_FIFO_CNT            0x090
      //  Reset = 32'h0
      //- bdp_csr_tx_rd_ch0_fifo_cnt_in 15:0 R This field corresponds to fifo count of read fifo on tx side 
      //- bdp_csr_tx_wr_ch0_fifo_cnt_in 31:16 R This field corresponds to fifo count of write fifo on tx side
    #define AXI_HIF_CH_TX_DMA_STATUS_0            0x094
      //  Reset = 32'h0
      //- dxr_csr_tx_curr_buflen_ch0_in 15:0 R This register field gives the length of the current buffer.gives the transmittion length
      //- dxr_csr_tx_lbuf_bytecnt_ch0_in 31:16 R This register field gives the information about the internal FIFO space
    #define AXI_HIF_CH_TX_STATUS_0                0x098
      //  Reset = 32'h0 
      //- bdp_csr_tx_bd_word0_ch0_in 31:0 R This register field containts the current TX Descritpor control word
    #define AXI_HIF_CH_TX_STATUS_1                0x09c
      //  Reset = 32'h2000_0000
      //- dxr_csr_tx_bd_word0_ch0_in 31:0 R This register field containts the current TX Descritpor control word of the data that is being read
    #define AXI_HIF_CH_TX_PKT_CNT0                0x0a0
      //  Reset = 32'h0
      //- dxr_csr_tx_req_pkt_cnt_ch0 31:0 R This register field contains number of data packets requested from system memory
    #define AXI_HIF_CH_TX_PKT_CNT1                0x0a4
      //  Reset = 32'h0 
      //- dxr_csr_tx_bus_data_pkt_cnt_ch0 31:0 R This register field contains number of data packets received from system memory
    #define AXI_HIF_CH_TX_PKT_CNT2                0x0a8
      //  Reset = 32'h0
      //- dxr_csr_tx_app_data_pkt_cnt_ch0 31:0 R This register field contains number of data packets written to app
    #define AXI_HIF_CH_RX_RD_CURR_BD_LOW_ADDR     0x0c0
      //  Reset = 32'h0
      //- bdp_rd_curr_rx_bd_low_addr_ch0_in 31:0 R This register field contains the lower base address of the Receive Sections DMA.
      //  this is reserved for BD_ONE_RD_ONE_WR mode
    #define AXI_HIF_CH_RX_RD_CURR_BD_HIGH_ADDR    0x0c4
      //  Reset = 32'h0
      //- bdp_rd_curr_rx_bd_high_addr_ch0_in 31:0 R This register field contains the upper base address of the Receive Sections DMA. 
      //  This is reserved for BD_ONE_RD_ONE_WR mode and for BD size 16bytes and not applicable for NPU AVB
    #define AXI_HIF_CH_RX_WR_CURR_BD_LOW_ADDR     0x0c8
      //  Reset = 32'h0
      //- bdp_wr_curr_rx_bd_low_addr_ch0_in 31:0 R This register field contains the lower base address of the Receive Sections DMA
    #define AXI_HIF_CH_RX_WR_CURR_BD_HIGH_ADDR    0x0cc
      //  Reset = 32'h0
      //- bdp_wr_curr_rx_bd_high_addr_ch0_in 31:0 R This register field contains the upper base address of the Receive Sections DMA and not applicable for NPU AVB
    #define AXI_HIF_CH_BDP_RX_FIFO_CNT            0x0d0
      //  Reset = 32'h0
      //- bdp_csr_rx_rd_ch0_fifo_cnt_in 15:0 R This field corresponds to fifo count of read fifo on rx side
      //- bdp_csr_rx_wr_ch0_fifo_cnt_in 31:16 R This field corresponds to fifo count of write fifo on rx side
    #define AXI_HIF_CH_RX_DMA_STATUS_0            0x0d4
      //  Reset = 32'h0
      //- dxr_csr_rx_curr_buflen_ch0_in 15:0 R This field corresponds to fifo count of write fifo on rx side
      //- dxr_csr_rx_lbuf_bytecnt_ch0_in 31:16 R This register field gives the length of the current buffer.gives the transmittion length
    #define AXI_HIF_CH_RX_STATUS_0                0x0d8
      //  Reset = 32'h0
      //- bdp_csr_rx_bd_word0_ch0_in 31:0 R This register field containts the current RX Descritpor control word 
    #define AXI_HIF_CH_RX_PKT_CNT0                0x0dc
      //  Reset = 32'h0
      //- dxr_csr_rx_bus_data_pkt_cnt_ch0 31:0 R This register field contains number of data packets written to system memory for rx
    #define AXI_HIF_CH_RX_PKT_CNT1                0x0e0
      //  Reset = 32'h0
      //- dxr_csr_rx_app_data_pkt_cnt_ch0 31:0 R This register field contains number of data packets recievedfrom app for rx
    #define AXI_HIF_CH_LTC_MAX_PKT                0x0e4
      //  Reset = 8'h4
      //- csr_hif_tx_ltc_max_pkt_cnt_ch0 7:0 R/W Maximum no of packets accpeted by HIF TX for this channel when LTC pkt flow bit is enabled.


// ---------------------------- EMAC - периферийное Ethernet устройство ------------------
#define AXI_EMAC1_BASE_ADDR                      0x660000
#define AXI_EMAC2_BASE_ADDR                      0x670000
#define AXI_EMAC3_BASE_ADDR                      0x680000
#define AXI_EMAC4_BASE_ADDR                      0x690000
#define AXI_EMAC5_BASE_ADDR                      0x6A0000
#define AXI_EMAC6_BASE_ADDR                      0x6B0000
#define AXI_EMAC7_BASE_ADDR                      0x6C0000
#define AXI_EMAC8_BASE_ADDR                      0x6D0000
#define AXI_EMAC9_BASE_ADDR                      0x6E0000
#define AXI_EMAC10_BASE_ADDR                     0x6F0000
#define AXI_EMAC11_BASE_ADDR                     0x760000
#define AXI_EMAC12_BASE_ADDR                     0x710000
#define AXI_EMAC13_BASE_ADDR                     0x720000
#define AXI_EMAC14_BASE_ADDR                     0x730000
#define AXI_EMAC15_BASE_ADDR                     0x740000
#define AXI_EMAC16_BASE_ADDR                     0x750000

#define AXI_EMAC1_END_OFFSET                     0x66FFFF
#define AXI_EMAC2_END_OFFSET                     0x67FFFF
#define AXI_EMAC3_END_OFFSET                     0x68FFFF
#define AXI_EMAC4_END_OFFSET                     0x69FFFF
#define AXI_EMAC5_END_OFFSET                     0x6AFFFF
#define AXI_EMAC6_END_OFFSET                     0x6BFFFF
#define AXI_EMAC7_END_OFFSET                     0x6CFFFF
#define AXI_EMAC8_END_OFFSET                     0x6DFFFF
#define AXI_EMAC9_END_OFFSET                     0x6EFFFF
#define AXI_EMAC10_END_OFFSET                    0x6FFFFF
#define AXI_EMAC11_END_OFFSET                    0x76FFFF
#define AXI_EMAC12_END_OFFSET                    0x71FFFF
#define AXI_EMAC13_END_OFFSET                    0x72FFFF
#define AXI_EMAC14_END_OFFSET                    0x73FFFF
#define AXI_EMAC15_END_OFFSET                    0x74FFFF
#define AXI_EMAC16_END_OFFSET                    0x75FFFF


#define AXI_EMAC_CTRL          0x08A0 
  //  Reset = 8'hB0
  //- reserved [3:0] R Reserved.
  //- tsu_incr_ctrl [5:4] R/W Default value is 2’b11. Incase of PPS mode is set, and
  //  whenever input emac1_pps_in pulse is received, the GEM GXL tsu_incr_ctrl bits are driven as 2’b00.
  //- tsu_ms [6] R/W Default value is 1’b0. tsu_ms port of emac will be connected to tsu_ms bit of this register 
  //- pps_mode [7] R/W Default value is 1’b1. In case of PPS mode bit set,
  //  Whenever input emac1_pps_in pulse is received, the GEM GXL tsu_incr_ctrl bits are driven as 2’b00.
  //  Else they are driven by bits[5:4] of emac control register.
  //  Input emac1_pps_in is synchronized to tsu clock and pulse is generated from that. PPS_IN has to be asserted atleast for one clock duration of tsu_clk.
  //  In case of PPS mode bit not set, The tsu_incr_ctrl bit from the tsu_control_reg will be connected to emac1_tsu_incr_ctrl bits.
  #define AXI_EMAC_CTRL_PORT_DIS_Msk    0x00B0UL
  
  //  Register description from here:  https://github.com/torvalds/linux/blob/master/drivers/net/ethernet/cadence/macb.h
  #define AXI_EMAC_NETCTRL		      0x0000 
    // Network Control
    #define AXI_EMAC_NETCTRL_LB_Pos		        0         /* reserved */
    #define AXI_EMAC_NETCTRL_LB_Msk		        0x0001
    #define AXI_EMAC_NETCTRL_LLB_Pos		      1         /* Loop back local */
    #define AXI_EMAC_NETCTRL_LLB_Msk		      0x0002
    #define AXI_EMAC_NETCTRL_RX_EN_Pos		    2         /* Receive enable */
    #define AXI_EMAC_NETCTRL_RX_EN_Msk		    0x0004
    #define AXI_EMAC_NETCTRL_TX_EN_Pos		    3         /* Transmit enable */
    #define AXI_EMAC_NETCTRL_TX_EN_Msk		    0x0008
    #define AXI_EMAC_NETCTRL_MANAG_EN_Pos		  4         /* Management port enable */
    #define AXI_EMAC_NETCTRL_MANAG_EN_Msk		  0x0010
    #define AXI_EMAC_NETCTRL_CLRSTAT_Pos	    5         /* Clear stats regs */
    #define AXI_EMAC_NETCTRL_CLRSTAT_Msk	    0x0020
    #define AXI_EMAC_NETCTRL_INCSTAT_Pos	    6         /* Incremental stats regs */
    #define AXI_EMAC_NETCTRL_INCSTAT_Msk	    0x0040
    #define AXI_EMAC_NETCTRL_WR_STAT_EN_Pos	  7         /* Write enable stats regs */
    #define AXI_EMAC_NETCTRL_WR_STAT_EN_Msk	  0x0080
    #define AXI_EMAC_NETCTRL_BACKPRESS_Pos	  8         /* Back pressure */
    #define AXI_EMAC_NETCTRL_BACKPRESS_Msk	  0x0100
    #define AXI_EMAC_NETCTRL_TX_START_Pos	    9         /* Start transmission */
    #define AXI_EMAC_NETCTRL_TX_START_Msk	    0x0200
    #define AXI_EMAC_NETCTRL_TX_HALT_Pos	    10        /* Transmit halt */
    #define AXI_EMAC_NETCTRL_TX_HALT_Msk		  0x0400
    #define AXI_EMAC_NETCTRL_TX_PAUSE_Pos	    11        /* Transmit pause frame */
    #define AXI_EMAC_NETCTRL_TX_PAUSE_Msk	    0x0800
    #define AXI_EMAC_NETCTRL_TX_PAUSEZQ_Pos	  12        /* Transmit zero quantum pause frame */
    #define AXI_EMAC_NETCTRL_TX_PAUSEZQ_Msk	  0x1000
    //#define AXI_EMAC_NETCTRL_SRTSM_Pos	    15     // -???
    //#define AXI_EMAC_NETCTRL_SRTSM_Msk	    0x8000 // -???
    #define AXI_EMAC_NETCTRL_TSU_EN_Pos       23        // External TSU timer enable
    #define AXI_EMAC_NETCTRL_TSU_EN_Msk	      0x00800000UL
    #define AXI_EMAC_NETCTRL_OSSMODE_EN_Pos   24        /* Enable One Step Synchro Mode */
    #define AXI_EMAC_NETCTRL_OSSMODE_EN_Msk	  0x01000000UL


  #define AXI_EMAC_NETCFG		      0x0004 
    // Network Config
    #define AXI_EMAC_NETCFG_SPD_Pos		        0         /* Speed */
    #define AXI_EMAC_NETCFG_SPD_Msk		        0x0001
    #define AXI_EMAC_NETCFG_FD_Pos		        1         /* Full duplex */
    #define AXI_EMAC_NETCFG_FD_Msk		        0x0002
    #define AXI_EMAC_NETCFG_BIT_RATE_Pos	    2         /* Discard non-VLAN frames */
    #define AXI_EMAC_NETCFG_BIT_RATE_Msk  	  0x0004
    #define AXI_EMAC_NETCFG_JFRAME_Pos	      3         /* reserved */
    #define AXI_EMAC_NETCFG_JFRAME_Msk	      0x0008
    #define AXI_EMAC_NETCFG_CAF_Pos		        4         /* Copy all frames */
    #define AXI_EMAC_NETCFG_CAF_Msk		        0x0010
    #define AXI_EMAC_NETCFG_NBC_Pos		        5         /* No broadcast */
    #define AXI_EMAC_NETCFG_NBC_Msk		        0x0020
    #define AXI_EMAC_NETCFG_NCFGR_MTI_Pos	    6         /* Multicast hash enable */
    #define AXI_EMAC_NETCFG_NCFGR_MTI_Msk	    0x0040
    #define AXI_EMAC_NETCFG_UNI_Pos		        7         /* Unicast hash enable */
    #define AXI_EMAC_NETCFG_UNI_Msk		        0x0080
    #define AXI_EMAC_NETCFG_BIG_Pos		        8         /* Receive 1536 byte frames */
    #define AXI_EMAC_NETCFG_BIG_Msk		        0x0100
    #define AXI_EMAC_NETCFG_EAE_Pos		        9         /* External address match enable */
    #define AXI_EMAC_NETCFG_EAE_Msk		        0x0200
    #define AXI_EMAC_NETCFG_CLK_Pos		        10
    #define AXI_EMAC_NETCFG_CLK_Msk		        0x0C00
      #define AXI_EMAC_NETCFG_CLK_1GBps_Msk		  0x0400
      #define AXI_EMAC_NETCFG_CLK_SGMII_Msk		  0x0800
    #define AXI_EMAC_NETCFG_RTY_Pos		        12        /* Retry test */
    #define AXI_EMAC_NETCFG_RTY_Msk		        0x1000
    #define AXI_EMAC_NETCFG_PAE_Pos		        13        /* Pause enable */
    #define AXI_EMAC_NETCFG_PAE_Msk		        0x2000
  //  #define AXI_EMAC_NETCFG_RM9200_RMII_Pos	13      /* AT91RM9200 only */
  //  #define AXI_EMAC_NETCFG_RM9200_RMII_Msk	0x2000  /* AT91RM9200 only */
    #define AXI_EMAC_NETCFG_RBOF_Pos	        14        /* Receive buffer offset */
    #define AXI_EMAC_NETCFG_RBOF_Msk		      0xC000
    #define AXI_EMAC_NETCFG_RLCE_Pos	        16        /* Length field error frame discard */
    #define AXI_EMAC_NETCFG_RLCE_Msk		      0x10000
    #define AXI_EMAC_NETCFG_DRFCS_Pos	        17        /* FCS remove */
    #define AXI_EMAC_NETCFG_DRFCS_Msk		      0x20000
    #define AXI_EMAC_NETCFG_EFRHD_Pos	        18
    #define AXI_EMAC_NETCFG_EFRHD_Msk		      0x40000
    #define AXI_EMAC_NETCFG_IRXFCS_Pos	      19
    #define AXI_EMAC_NETCFG_IRXFCS_Mks	      0x80000
    
    #define AXI_EMAC_NETCFG_FIFO_W64_Mks	    0x00200000UL
    #define AXI_EMAC_NETCFG_RX_FCS_Mks	      0x01000000UL
    #define AXI_EMAC_NETCFG_SGMII_Mks	        0x08000000UL
                                                  
    
  #define AXI_EMAC_NETSTAT		    0x0008 
    // Network Status
    #define AXI_EMAC_NETSTAT_LINK_Pos	        0       /* pcs_link_state */
    #define AXI_EMAC_NETSTAT_LINK_Msk	        0x0001
    #define AXI_EMAC_NETSTAT_MDIO_Pos	        1       /* status of the mdio_in pin */
    #define AXI_EMAC_NETSTAT_MDIO_Msk		      0x0002
    #define AXI_EMAC_NETSTAT_IDLE_Pos	        2       /* The PHY management logic is idle */
    #define AXI_EMAC_NETSTAT_IDLE_Msk		      0x0004
   
  #define AXI_EMAC_TAR		        0x000c /* AT91RM9200 only */
  #define AXI_EMAC_TCR		        0x0010 /* AT91RM9200 only */
  #define AXI_EMAC_TXSTAT		      0x0014 
    // Transmit Status
    #define AXI_EMAC_TXSTAT_UBR_OFFSET		      0       /* Used bit read */
    #define AXI_EMAC_TXSTAT_UBR_SIZE		        0x0001
    #define AXI_EMAC_TXSTAT_COL_OFFSET		      1       /* Collision occurred */
    #define AXI_EMAC_TXSTAT_COL_SIZE		        0x0002
    #define AXI_EMAC_TXSTAT_RETR_OV_OFFSET	    2       /* Retry limit exceeded */
    #define AXI_EMAC_TXSTAT_RETR_OV_SIZE	      0x0004
    #define AXI_EMAC_TXSTAT_GO_OFFSET		        3       /* Transmit go */
    #define AXI_EMAC_TXSTAT_GO_SIZE		          0x0008
    #define AXI_EMAC_TXSTAT_BUS_ERR_OFFSET		  4       /* TX frame corruption due to AHB error */
    #define AXI_EMAC_TXSTAT_BUS_ERR_SIZE		    0x0010
    //#define AXI_EMAC_TXSTAT_RM9200_BNQ_OFFSET	4       /* AT91RM9200 only */
    //#define AXI_EMAC_TXSTAT_RM9200_BNQ_SIZE	  0x0010  /* AT91RM9200 only */
    #define AXI_EMAC_TXSTAT_COMPL_OFFSET	      5       /* Trnasmit complete */
    #define AXI_EMAC_TXSTAT_COMPL_SIZE		      0x0020
    #define AXI_EMAC_TXSTAT_UNDRUN_OFFSET		    6       /* Trnasmit under run */
    #define AXI_EMAC_TXSTAT_UNDRUN_SIZE		      0x0040

  #define AXI_EMAC_RBQP		        0x0018 /* RX Q Base Address */
  #define AXI_EMAC_TBQP		        0x001c /* TX Q Base Address */
  #define AXI_EMAC_RXSTAT		      0x0020 
    // Receive Status
    #define AXI_EMAC_RXSTAT_BNA_Pos		        0       /* Buffer not available */
    #define AXI_EMAC_RXSTAT_BNA_Msk		        0x0001
    #define AXI_EMAC_RXSTAT_REC_Pos		        1       /* Frame received */
    #define AXI_EMAC_RXSTAT_REC_Msk		        0x0002
    #define AXI_EMAC_RXSTAT_OVR_Pos		        2       /* Receive overrun */
    #define AXI_EMAC_RXSTAT_OVR_Msk		        0x0004

  #define AXI_EMAC_ISR		        0x0024 /* Interrupt Status */
  #define AXI_EMAC_IER		        0x0028 /* Interrupt Enable */
  #define AXI_EMAC_IDR		        0x002c /* Interrupt Disable */
  #define AXI_EMAC_IMR		        0x0030 /* Interrupt Mask */
  #define AXI_EMAC_MAN		        0x0034 /* PHY Maintenance */  
  // ... other regs from link
  
  //  MAC_GEM
  //  Programming the lower 32bit DA address register to accept all packets
  #define AXI_EMAC_GEM_DA_ADDR_LO  0x0088
  //  Programming the upper 32bit DA address register to accept all packets.
  #define AXI_EMAC_GEM_DA_ADDR_HI  0x008C
  //  Programming the lower 32bit DA address mask register to accept all packets.
  #define AXI_EMAC_GEM_DA_MASK_L0  0x00C8
  //  Programming the upper 16bit DA address mask register to accept all packets.
  #define AXI_EMAC_GEM_DA_MASK_Hi  0x00CC
  //  Enable Stacked VLAN Processing mode.
  #define AXI_EMAC_GEM_VLAN        0x00C0
    #define AXI_EMAC_GEM_VLAN_EN_Pos  31
    #define AXI_EMAC_GEM_VLAN_EN_Msk  0x80000000UL
  
  //  MAC_TSU
  #define AXI_EMAC_TSU_TIM_INC    0x01DC

//  ------------    HGPI1 - Host общий интерфейс пакетов Хоста (GigabitPacketInterface)-------
#define AXI_HGPI_BASE_ADDR                       0x650000
#define AXI_HGPI_END_OFFSET                      0x65FFFF

// ------------------ EGPI (Ethernet Generic Packet Interface) - общий интерфейс пакетов ----------------------------
#define AXI_EGPI1_BASE_ADDR                      0x780000
#define AXI_EGPI2_BASE_ADDR                      0x790000
#define AXI_EGPI3_BASE_ADDR                      0x7A0000
#define AXI_EGPI4_BASE_ADDR                      0x7B0000
#define AXI_EGPI5_BASE_ADDR                      0x7C0000
#define AXI_EGPI6_BASE_ADDR                      0x7D0000
#define AXI_EGPI7_BASE_ADDR                      0x7E0000
#define AXI_EGPI8_BASE_ADDR                      0x7F0000
#define AXI_EGPI9_BASE_ADDR                      0x800000
#define AXI_EGPI10_BASE_ADDR                     0x810000
#define AXI_EGPI11_BASE_ADDR                     0x820000
#define AXI_EGPI12_BASE_ADDR                     0x830000
#define AXI_EGPI13_BASE_ADDR                     0x840000
#define AXI_EGPI14_BASE_ADDR                     0x850000
#define AXI_EGPI15_BASE_ADDR                     0x860000
#define AXI_EGPI16_BASE_ADDR                     0x870000

#define AXI_EGPI1_END_OFFSET                     0x78FFFF
#define AXI_EGPI2_END_OFFSET                     0x79FFFF
#define AXI_EGPI3_END_OFFSET                     0x7AFFFF
#define AXI_EGPI4_END_OFFSET                     0x7BFFFF
#define AXI_EGPI5_END_OFFSET                     0x7CFFFF
#define AXI_EGPI6_END_OFFSET                     0x7DFFFF
#define AXI_EGPI7_END_OFFSET                     0x7EFFFF
#define AXI_EGPI8_END_OFFSET                     0x7FFFFF
#define AXI_EGPI9_END_OFFSET                     0x80FFFF
#define AXI_EGPI10_END_OFFSET                    0x81FFFF
#define AXI_EGPI11_END_OFFSET                    0x82FFFF
#define AXI_EGPI12_END_OFFSET                    0x83FFFF
#define AXI_EGPI13_END_OFFSET                    0x84FFFF
#define AXI_EGPI14_END_OFFSET                    0x85FFFF
#define AXI_EGPI15_END_OFFSET                    0x86FFFF
#define AXI_EGPI16_END_OFFSET                    0x87FFFF

#define AXI_GPI_VERSION           0x00 
  //  Reset = 32'h0
  //- gpi_id 15:0 R Read only register that contains the ID of the block 
  //- gpi_version 23:16 R Read Only register that indicates the Version of the Block
  //- gpi_revision 31:24 R Read Only register that indicates the Revision of the Block
#define AXI_GPI_CTRL              0x04 
  //  Reset = 2'b01
  //- csr_gpi_en 0 R/W GPI Enable. This signal needs to be set to enable the gpi module
  //- csr_gpi_swrst 1 R/W GPI Reset. This signal is used to initiate soft reset of the gpi. 
  //  This is a self clear signal. Software should only set this register and should not attempt to clear it.
  #define AXI_GPI_CTRL_EN_Mks       0x0001UL
  #define AXI_GPI_CTRL_RESET_Mks    0x0002UL
  
#define AXI_GPI_RX_CONFIG         0x08 
  //  Reset = 26'h200_0001
  //- csr_lmem_buf_en 0 R/W Enable for LMEM buffer. If this bit is set, the hardware fetches the LMEM for the first buffer.
  //  If the Enable for the DDR buffer is not set, the data will be fetched only from LMEM for first and subsequent buffers too. 
  //  For NPU all the buffers are LMEM enabled.
  //- csr_ddr_buf_en 1 R/W Enable for DDR Buffer. If the enable for LMEM is set, this will be the second buffer fetched.
  //  Otherwise, this will be the only buffer fetched. If the packet size is larger than the DDR BUF size, multiple buffers are fetched and chained together.
  //  For NPU DDR buffers are not enabled. 
  //- csr_alloc_retry_cycles 25:16 R/W This register has the number of system clock cycles, the state machine has to wait before
  //  retrying incase the buffers are full at the buffer manager.
  #define AXI_GPI_RX_CONFIG_LMEM_BUFF_EN_Pos    0x0
  #define AXI_GPI_RX_CONFIG_LMEM_BUFF_EN_Msk    0x0001UL  
  #define AXI_GPI_RX_CONFIG_LMEM_RETR_CNT_Pos   16UL
  #define AXI_GPI_RX_CONFIG_LMEM_RETR_CNT_Msk   0xFFFF0000UL
  
  #define AXI_GPI_RX_CONFIG_FILL(en, cnt)     _VAL2FLD(AXI_GPI_RX_CONFIG_LMEM_BUFF_EN, en) \
                                            | _VAL2FLD(AXI_GPI_RX_CONFIG_LMEM_RETR_CNT, cnt)
  
#define AXI_GPI_HDR_SIZE            0x0c 
  //  Reset = 26'h100_0030
  //- csr_lmem_hdr_size 7:0 R/W LMEM Header Size. Data in the LMEM is written from this offset. 
  //  The first location of LMEM is written with the subsequent buffer address if it exists. This location is a 32 bit aligned address.
  //- csr_ddr_hdr_size 25:16 R/W DDR Header Size. Data in the DDR is written from this offset. 
  //  The subsequent buffer address if it exists is written before the offset. Not applicable for NPU.
  #define AXI_GPI_HDR_SIZE_LMEM_HDR_SIZE_Pos     0
  #define AXI_GPI_HDR_SIZE_LMEM_HDR_SIZE_Msk     0x00FFUL
  #define AXI_GPI_HDR_SIZE_DDR_HDR_SIZE_Pos      16
  #define AXI_GPI_HDR_SIZE_DDR_HDR_SIZE_Msk      0x01FF0000UL
  
  #define AXI_GPI_HDR_SIZE_FILL(lmemHdrSize, ddrHdrSize)    _VAL2FLD(AXI_GPI_HDR_SIZE_LMEM_HDR_SIZE, lmemHdrSize) \
                                                          | _VAL2FLD(AXI_GPI_HDR_SIZE_DDR_HDR_SIZE, ddrHdrSize)
  
#define AXI_GPI_BUF_SIZE            0x10 
  //  Reset = 32'h800_0080
  //- csr_lmem_bufsize 15:0 R/W Buffer size of an LMEM buffer
  //- csr_ddr_bufsize 31:16 R/W Buffer size of an DDR buffer. Not applicable for NPU.
  #define AXI_GPI_BUF_SIZE_LMEM_BUFF_SIZE_Pos   0
  #define AXI_GPI_BUF_SIZE_LMEM_BUFF_SIZE_Msk   0xFFFFUL
  #define AXI_GPI_BUF_SIZE_DDR_BUFF_SIZE_Pos    16
  #define AXI_GPI_BUF_SIZE_DDR_BUFF_SIZE_Msk    0xFFFFUL
  
  #define AXI_GPI_BUF_SIZE_FILL(lmemBufSize, ddrBufSize)   _VAL2FLD(AXI_GPI_BUF_SIZE_LMEM_BUFF_SIZE, lmemBufSize) \
                                                         | _VAL2FLD(AXI_GPI_BUF_SIZE_DDR_BUFF_SIZE, ddrBufSize)

#define AXI_GPI_LMEM_ALLOC_ADDR     0x14 
  //  Reset = 32'h0
  //- csr_lmem_bm_alloc_addr 31:0 R/W Address Location within the BMU to fetch an LMEM buffer
#define AXI_GPI_LMEM_FREE_ADDR      0x18 
  //  Reset = 32'h0
  //- csr_lmem_bm_free_addr 31:0 R/W Address Location within the BMU to free an LMEM buffer
#define AXI_GPI_DDR_ALLOC_ADDR      0x1c 
  //  Reset = 32'h0
  //- csr_ddr_bm_alloc_addr 31:0 R/W Address Location within the BMU to fetch a DDR buffer. Not applicable for NPU.
#define AXI_GPI_DDR_FREE_ADDR       0x20 
  //  Reset = 32'h0
  //- csr_ddr_bm_free_addr 31:0 R/W Address Location within the BMU to free a DDR buffer. Not applicatble for NPU.
#define AXI_GPI_CLASS_ADDR          0x24 
  //  Reset = 32'h0
  //- csr_class_addr 31:0 R/W Address of the location in the Classifier where packet from peripherals are sent to.
#define AXI_GPI_DRX_FIFO            0x28 
  //  Reset = 16'd128
  //- csr_drx_fiford_thres 15:0 R/W Receive FIFO threshold. The receiver starts to send the packets from internal FIFO to the bus
  //  whenever it has a complete packet or threshold number of bytes are received in the FIFO
#define AXI_GPI_TRX_FIFO            0x2C 
  //  Reset = 16'd128
  //- csr_inq_pktfetch_thres 15:0 R/W Whenever threshold number of locations are free in the transmitter, the transmitter would start the
  //  handshake with the QoS/TM block to indicate its ability to take a new packet
#define AXI_GPI_INQ_PKTPTR          0x30 
  //  Reset = 32'h0
  //- csr_inq_pktptr 31:0 R/W Packet pointer of the next packet to send. Sent by the QoS/TM block  
#define AXI_GPI_DDR_DATA_OFFSET     0x34 
  //  Reset = 10'h100
  //- csr_ddr_data_offset 9:0 R/W CSR DDR data offset. Not applicable for NPU.
#define AXI_GPI_LMEM_DATA_OFFSET    0x38 
  //  Reset = 8'h10
  //- csr_lmem_data_offset 7:0 R/W CSR LMEM data offset. Not applicable for NPU
#define AXI_GPI_TMLF_TX             0x4C 
  //  Reset = 16'h178
  //- csr_gpi_tmlf_txthres 15:0 R/W Threshold number of TMLF words (64bit size) to be in the TMLF FIFO before transmission starts.  
#define AXI_GPI_DTX_ASEQ            0X50 
  //  Reset = 8'h50
  //- csr_gpi_dtx_aseq_len 7:0 R/W Length of action sequence.
#define AXI_GPI_FIFO_DEBUG          0x58 
  //  Reset = 28'h0
  //- txf_pkt_cnt 5:0 R Transmit fifo packet count.
  //- rxf_pkt_cnt 11:6 R Receive GPI fifo packet count
  //- txf_fifo_cnt 19:12 R Number of transmit fifo locations filled
  //- rxf_fifo_cnt 27:20 R Number of receive fifo locations filled
#define AXI_GPI_TX_PAUSE_TIME       0x5c 
  //  Reset = 16'hffff
  //- csr_gpi_tx_pause_time 15:0 R/W Transmit pause time, used in case of pause frame generation. 
  //  It has to be same as pause time register of EMAC.
#define AXI_GPI_LMEM_SEC_BUF_DATA_OFFSET    0x60 
  //  Reset = 16'h10
  //- csr_lmem_sec_buf_data_offset 15:0 R/W Buffer offset used for second and subsequent buffers of LMEM
  
#define AXI_GPI_DDR_SEC_BUF_DATA_OFFSET     0x64 
  //  Reset = 16'h0
  //- csr_ddr_sec_buf_data_offset 15:0 R/W Buffer offset used for second and subsequent buffers of DMEM. Not applicable for NPU.
#define AXI_GPI_FIFO_STATUS                 0x54 
  //  Reset = 1'b0
  //- tx_under_stick 0 R/W GPI Fifo Status (tx underrun condition)
#define AXI_GPI_CSR_TOE_CHKSUM_EN           0x68 
  //  Reset = 1'b0
  //- csr_gpi_toe_chksum_en 0 R/W csr_gpi_toe_chksum_en is enabled, the hardware module in gpi_dtx_aseq calcualtes ip/tcp/udp checks and updated the packet
#define AXI_GPI_CSR_OVERRUN_DROPCNT         0x6C 
  //  Reset = 32'h0
  //- csr_gpi_overrun_dropcnt 31:0 R Overrun drop counter. Clear on read counter.
#define AXI_GPI_TX_DBUG_REG1                0x70 
  //  Reset = NA
  //- gpi_tx_dbug_reg1 31:0 R Tx debug register 1 - inq_ptr 
#define AXI_GPI_TX_DBUG_REG2                0x74 
  //  Reset = NA
  //- gpi_tx_dbug_reg2 31:0 R Tx debug register 2 - previous inq pointer
#define AXI_GPI_TX_DBUG_REG3                0x78 
  //  Reset = NA
  //- gpi_tx_dbug_reg3 31:0 R Tx debug register 3 -
  // {action_debug[11:0],
  //  aseq_state_prev3[3:0],
  //  aseq_state_prev2[3:0], 
  //  aseq_state_prev1[3:0],
  //  aseq_state_curr[3:0], 
  //  1'b0, 
  //  gpi_qos_tinq_ready,
  //  dtxsm_inq_pktptr_ack, 
  //  inq_pktptr_valid}
#define AXI_GPI_TX_DBUG_REG4                0x7C 
  //  Reset = NA
  //- gpi_tx_dbug_reg4 31:0 R Tx debug register 4 - 
  //  {action_debug[_prev[19:0], 
  //   action_debug[23:12]}
#define AXI_GPI_TX_DBUG_REG5                0x80 
  //  Reset = NA
  //- gpi_tx_dbug_reg5 31:0 R Tx debug register 5 - 
  //  {dtx_dxfr_dbug_bus[3:0],
  //   dtx_sm_dbug_bus[11:0], 
  //   tmlf_dbug_bus[11:0],
  //   action_debug_prev[23:20]}
#define AXI_GPI_TX_DBUG_REG6                0x84 
  //  Reset = NA
  //- gpi_tx_dbug_reg6 31:0 R Tx debug register 6 - 
  //  {tbma_dbug_bus[7:0],   
  //   dtx_dxfr_dbug_bus[11 :4]}
#define AXI_GPI_RX_DBUG_REG1                0x90 
  //  Reset = NA
  //- gpi_rx_dbug_reg1 31:0 R Rx debug register 1 - 
  //  {rbma_dbug_bus,
  //   drx_dxfr_dbug_bus[3:0], 
  //   drx_sm_dbug_bus[15:0],
  //   rmlf_dbug_bus[11:0]}
#define AXI_GPI_RX_DBUG_REG2                0x94 
  //  Reset = NA
  //- gpi_rx_dbug_reg2 31:0 R Rx debug register 2 - 
  //  {rbma_dbug_bus[15:0],
  //   drx_dxfr_dbug_bus[15:4]}
#define AXI_GPI_PORT_SHP0_CTRL              0x98 
  //  Reset = 32'h0
  //- csr_port_shp0_ctrl 31:0 R/W Ingress qos, shaper0 control register. Not applicable for NPU.
#define AXI_GPI_PORT_SHP0_WGHT              0x9c 
  //  Reset = 32'h0
  //- csr_port_shp0_wght 31:0 R/W Ingress qos, shaper0 weight register. Not applicable for NPU.
#define AXI_GPI_PORT_SHP0_STATUS            0x100 
  //  Reset = 32'h1
  //- port_shp0_csr_status 31:0 R Ingress qos, shaper0 status. Not applicable for NPU.
#define AXI_GPI_BMU1_PHY_LOW_WATERMARK      0x104 
  //  Reset = 16'h0
  //- bmu1_phy_low_watermark 15:0 R/W BMU1 PHY counter, low watermark
#define AXI_GPI_BMU1_PHY_HIGH_WATERMARK     0x108 
  //  Reset = 16'h0
  //- bmu1_phy_high_watermark 15:0 R/W BMU1 PHY counter, high watermark
#define AXI_GPI_BMU2_PHY_LOW_WATERMARK      0x10c 
  //  Reset = 16'h0
  //- bmu2_phy_low_watermark 15:0 R/W BMU2 PHY counter, low watermark
#define AXI_GPI_BMU2_PHY_HIGH_WATERMARK     0x110 
  //  Reset = 16'h0
  //- bmu2_phy_high_watermark 15:0 R/W BMU2 PHY counter, high watermark
#define AXI_GPI_FW_CONTROL                  0x114 
  //  Reset = 32'h0
  //- csr_fw_control 31:0 R/W Flow control enable register
#define AXI_GPI_USE_CLASS_INQ_AFULL         0x118 
  //  Reset = 1'b1
  //- csr_use_class_inq_afull 0 R/W Enable to use, class alomost ful signal
#define AXI_GPI_PORT_SHP1_CTRL              0x11c 
  //  Reset = 32'h0
  //- csr_port_shp1_ctrl 31:0 R/W Ingress qos, shaper1 control register. Not applicable for NPU.
#define AXI_GPI_PORT_SHP1_WGHT              0x120 
  //  Reset = 32'h0
  //- csr_port_shp1_wght 31:0 R/W Ingress qos, shaper1 weight register. Not applicable for NPU.
#define AXI_GPI_PORT_SHP1_STATUS            0x124 
  //  Reset = 32'h1)
  //- port_shp1_csr_status 31:0 R Ingress qos, shaper1 status. Not applicable for NPU.
#define AXI_GPI_PORT_SHP_CONFIG             0x128 
  //  Reset = 16'h2000
  //- csr_port_shp_config 7:0 R/W Ingress qos, shape config register. Not applicable for NPU. 
  //  Bit 0 value of 0 shaper0 is - Shaper is bps, value of 1 Shaper0 is pps. 
  //  Bit 1 value of 0 Shaper1 is bps, value of 1 Shaper1 is pps, 
  //  Bits [3:2] 
  //    value 00 Shaper0 is for port level data rate, 
  //    value 01 Shaper0 is for BCAST Packets, 
  //    value 10 Shaper0 is for MCAST Packets. 
  //  Bits [6:4] 
  //    value 00 Shaper1 is for port level data rate 
  //    value 01 Shaper1 is for BCAST Packets 
  //    value 10 Shaper1 is for MCAST Packets
  //- csr_port_shp_ifg 15:8 R/W IFG between packets. Used In ingress shaper. Not applicable for NPU.
#define AXI_GPI_CSR_SHP_DROPCNT             0x12c 
  //  Reset = 32'h0
  //- csr_gpi_shp_dropcnt 31:0 R Shaper drop count. Clear on read counter. Not applicable for NPU.
#define AXI_GPI_FW_CONTROL1                 0x130 
  //  Reset = 8'h0
  //- csr_fw_control1 7:0 R/W Flow control enable register1. 
  //  Bit 0 for oob rxf fifo cnt xoff enable 
  //  Bit1 for oob rxf fifo cnt xon enable, 
  //  Bit2 foroob rxf fifo cnt xoff inv, 
  //  Bit 3 for oob rxf fifo cnt xon inv
#define AXI_GPI_RXF_FIFO_LOW_WATERMARK      0x134 
  //  Reset = 16'h0
  //- rxf_fifo_low_watermark 15:0 R/W Rxf fifo cnt low watermark for oob flow control xon
#define AXI_GPI_RXF_FIFO_HIGH_WATERMARK     0x138 
  //  Reset = 16'h0
  //- rxf_fifo_high_watermark 15:0 R/W RXF fifo high water mark, for oob flow control xoff
#define AXI_GPI_EMAC_1588_TIMESTAMP_EN      0x13C 
  //  Reset = 1'b0
  //- csr_emac_1588_timestamp_en 0 R/W If set, extra status quad is written into gpi fifo. This is for 1588 timestamp.
#define AXI_GPI_PORT_SHP0_MIN_CREDIT        0x140 
  //  Reset = 22'h0
  //- csr_port_shp0_min_credit 21:0 R/W shaper 0 min weight
#define AXI_GPI_PORT_SHP1_MIN_CREDIT        0x144 
  //  Reset = 22'h0
  //- csr_port_shp1_min_credit 21:0 R/W shaper 1 min weight
#define AXI_GPI_LMEM2_FREE_ADDR             0x148 
  //  Reset = 32'hC0700034
  //- csr_lmem2_bm_free_addr 31:0 R/W Address Location within the BMU to free an LMEM2 buffer


/* --------------------- ETGPI (Egress Timestamp Report) - отчет о выходных метках времени -------------- */
#define AXI_ETGPI1_BASE_ADDR                     0x880000
#define AXI_ETGPI2_BASE_ADDR                     0x890000
#define AXI_ETGPI3_BASE_ADDR                     0x8A0000
#define AXI_ETGPI4_BASE_ADDR                     0x8B0000
#define AXI_ETGPI5_BASE_ADDR                     0x8C0000
#define AXI_ETGPI6_BASE_ADDR                     0x8D0000
#define AXI_ETGPI7_BASE_ADDR                     0x8E0000
#define AXI_ETGPI8_BASE_ADDR                     0x8F0000
#define AXI_ETGPI9_BASE_ADDR                     0x900000
#define AXI_ETGPI10_BASE_ADDR                    0x910000
#define AXI_ETGPI11_BASE_ADDR                    0x920000
#define AXI_ETGPI12_BASE_ADDR                    0x930000
#define AXI_ETGPI13_BASE_ADDR                    0x940000
#define AXI_ETGPI14_BASE_ADDR                    0x950000
#define AXI_ETGPI15_BASE_ADDR                    0x960000
#define AXI_ETGPI16_BASE_ADDR                    0x970000
             
#define AXI_ETGPI1_END_OFFSET                    0x88FFFF
#define AXI_ETGPI2_END_OFFSET                    0x89FFFF
#define AXI_ETGPI3_END_OFFSET                    0x8AFFFF
#define AXI_ETGPI4_END_OFFSET                    0x8BFFFF
#define AXI_ETGPI5_END_OFFSET                    0x8CFFFF
#define AXI_ETGPI6_END_OFFSET                    0x8DFFFF
#define AXI_ETGPI7_END_OFFSET                    0x8EFFFF
#define AXI_ETGPI8_END_OFFSET                    0x8FFFFF
#define AXI_ETGPI9_END_OFFSET                    0x90FFFF
#define AXI_ETGPI10_END_OFFSET                   0x91FFFF
#define AXI_ETGPI11_END_OFFSET                   0x92FFFF
#define AXI_ETGPI12_END_OFFSET                   0x93FFFF
#define AXI_ETGPI13_END_OFFSET                   0x94FFFF
#define AXI_ETGPI14_END_OFFSET                   0x95FFFF
#define AXI_ETGPI15_END_OFFSET                   0x96FFFF
#define AXI_ETGPI16_END_OFFSET                   0x97FFFF



#endif	//MDR_1923KX028_AXI_DEFS_H

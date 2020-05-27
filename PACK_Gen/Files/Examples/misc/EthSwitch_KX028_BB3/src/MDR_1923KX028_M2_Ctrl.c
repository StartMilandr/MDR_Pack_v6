#include <MDR_1923KX028_M2_Ctrl.h>

#include <MDR_1923KX028_M2_Defs.h>
#include <MDR_1923KX028_Config.h>
#include <MDR_1923KX028_AXI_defs.h>
#include <MDR_1923KX028_TableMAC.h>
#include <MDR_1923KX028_TableVLAN.h>

#if MDR_KX028_DEBUG
  #include <stdio.h>
#endif

static void Write_InitHW_Table( MDR_KX028_AddrData_t *initItem )
{
	MDR_KX028_AddrData_t *hwdata;
	hwdata = initItem;

	while ( hwdata->addr != 0 ){
      MDR_KX028_WriteAXI( hwdata->addr, hwdata->data );
      hwdata++;
	}
}

#if MDR_KX028_DEBUG
  static void Printf_InitHW_Table( MDR_KX028_AddrData_t *initItem )
  {
    uint32_t dt;
    
    for(; initItem->addr != 0; initItem++ ){
      dt = MDR_KX028_ReadAXI(initItem->addr);
      printf("addr 0x%06X val 0x%08X\n", (uint32_t)( initItem->addr ) , dt );
    }
  }
#endif

static inline void MDR_KX028_InitEMAC(uint32_t i)
{
//  EMAC 
    MDR_KX028_WriteAXI(MDR_KX028_AxiAddrEMAC[i] + AXI_EMAC_IER , 0x00010200 );       // enable interrupts at: pcs_autoneg_compete, pcs_link_change
    MDR_KX028_WriteAXI(MDR_KX028_AxiAddrEMAC[i] + AXI_EMAC_CTRL, AXI_EMAC_CTRL_PORT_DIS_Msk );

//  next 2 string is new in 1.1 version of firmware
    MDR_KX028_WriteAXI( ( MDR_KX028_AxiAddrEMAC[i] + 0x210 ), 0x00008020 );       //EMAC support full duplex via SGMII, next page support
    MDR_KX028_WriteAXI( ( MDR_KX028_AxiAddrEMAC[i] + 0x21C ), 0x00002001 );       //EMAC has not next page
           
//  MDR_KX028_WriteAXI( ( emac[i] + 0x004 ), 0x09230C18 );                        // 1G, SGMII mode, rcv jumbo frames, reject error packets...
    MDR_KX028_WriteAXI( ( MDR_KX028_AxiAddrEMAC[i] + AXI_EMAC_NETCFG),      0x083F0C12 );       // 1G, SGMII mode, jumbo frames disable, 1536 bytes frame disable, reject error packets...      
    MDR_KX028_WriteAXI( ( MDR_KX028_AxiAddrEMAC[i] + AXI_EMAC_TSU_TIM_INC), 0x00000014 );
    MDR_KX028_WriteAXI( ( MDR_KX028_AxiAddrEMAC[i] + 0x0C8 ), 0xFFFFFFFF );
    MDR_KX028_WriteAXI( ( MDR_KX028_AxiAddrEMAC[i] + 0x0CC ), 0x0000FFFF );
    MDR_KX028_WriteAXI( ( MDR_KX028_AxiAddrEMAC[i] + 0x088 ), 0x00000000 );
    MDR_KX028_WriteAXI( ( MDR_KX028_AxiAddrEMAC[i] + 0x08C ), 0x00000000 );        
    MDR_KX028_WriteAXI( ( MDR_KX028_AxiAddrEMAC[i] + 0x0C0 ), 0x80000000 );       // enable VLAN processing
    MDR_KX028_WriteAXI( ( MDR_KX028_AxiAddrEMAC[i] + 0x048 ), 9000 );             // ������������ ������ jumbo ������
        
//  EGPI 
    MDR_KX028_WriteAXI( ( MDR_KX028_AxiAddrEGPI[i] + 0x008 ), 0x02000001 );
    MDR_KX028_WriteAXI( ( MDR_KX028_AxiAddrEGPI[i] + 0x00C ), 0x00000030 );       //___Q in spec value 0x30
    MDR_KX028_WriteAXI( ( MDR_KX028_AxiAddrEGPI[i] + 0x010 ), 0x00000080 );       //___Q in spec value 0x80
    MDR_KX028_WriteAXI( ( MDR_KX028_AxiAddrEGPI[i] + 0x014 ), 0xC0100030 );
    MDR_KX028_WriteAXI( ( MDR_KX028_AxiAddrEGPI[i] + 0x018 ), 0xC0100034 );
    MDR_KX028_WriteAXI( ( MDR_KX028_AxiAddrEGPI[i] + 0x024 ), 0xC0620010 );
    //MDR_KX028_WriteAXI( ( MDR_KX028_AxiAddrEGPI[i] + 0x034 ), 0x00000100 );
    MDR_KX028_WriteAXI( ( MDR_KX028_AxiAddrEGPI[i] + 0x038 ), 0x00000010 );
    MDR_KX028_WriteAXI( ( MDR_KX028_AxiAddrEGPI[i] + 0x060 ), 0x00000010 );
    MDR_KX028_WriteAXI( ( MDR_KX028_AxiAddrEGPI[i] + 0x04C ), 0x00000178 );
    MDR_KX028_WriteAXI( ( MDR_KX028_AxiAddrEGPI[i] + 0x050 ), 0x00000050 );
    MDR_KX028_WriteAXI( ( MDR_KX028_AxiAddrEGPI[i] + 0x148 ), 0xC0700034 );
    
    // ETGPI
    MDR_KX028_WriteAXI( ( MDR_KX028_AxiAddrEGPI[i] + 0x008 ), 0x02000001 );
    MDR_KX028_WriteAXI( ( MDR_KX028_AxiAddrEGPI[i] + 0x00C ), 0x01000030 );       //___Q in spec value 0x30
    MDR_KX028_WriteAXI( ( MDR_KX028_AxiAddrEGPI[i] + 0x010 ), 0x08000080 );       //___Q in spec value 0x80
    MDR_KX028_WriteAXI( ( MDR_KX028_AxiAddrEGPI[i] + 0x014 ), 0xC0100030 );
    MDR_KX028_WriteAXI( ( MDR_KX028_AxiAddrEGPI[i] + 0x018 ), 0xC0100034 );
    MDR_KX028_WriteAXI( ( MDR_KX028_AxiAddrEGPI[i] + 0x024 ), 0xC0620010 );
    MDR_KX028_WriteAXI( ( MDR_KX028_AxiAddrEGPI[i] + 0x034 ), 0x00000100 );
    MDR_KX028_WriteAXI( ( MDR_KX028_AxiAddrEGPI[i] + 0x038 ), 0x00000010 );
    MDR_KX028_WriteAXI( ( MDR_KX028_AxiAddrEGPI[i] + 0x060 ), 0x00000010 );
    MDR_KX028_WriteAXI( ( MDR_KX028_AxiAddrEGPI[i] + 0x04C ), 0x000000BC );
    MDR_KX028_WriteAXI( ( MDR_KX028_AxiAddrEGPI[i] + 0x050 ), 0x00000050 );  
    MDR_KX028_WriteAXI( ( MDR_KX028_AxiAddrEGPI[i] + 0x004 ), 0x00000001 );
}


static uint32_t addrClass[2] = {AXI_CLASS_HW1_BASE_ADDR, AXI_CLASS_HW2_BASE_ADDR};


//typedef enum {
//    KX028_FRM_ACC_ANY_TAGGING = 0,   // allow both tagged and untagged frames
//    KX028_FRM_ACC_TAGGED_ONLY,       // allow only tagged frames
//    KX028_FRM_ACC_UNTAGGED_ONLY,     // allow only untagged frames
//} MDR_KX028_PortAcceptFrm_t;


//// STP blocking state
//typedef enum {
//    KX028_STP_ACC_FORWARDING = 0,    // ok to learn SA and forward traffic
//    KX028_STP_ACC_BLOCKED,           // do not learn SA; do not forward frames
//    KX028_STP_ACC_LEARN_ONLY,        // ok to learn SA, but do not forward frames
//} MDR_KX028_PortAcceptSTP_t;

void MDR_KX028_PortsInit( void )
{
    uint8_t ucI, classNum;
    uint32_t addrReg1, addrReg2; 
    uint32_t portCfgStruct1 = AXI_CLASS_STRUC1_FILL(KX028_PORTS_FALLBACK_ID, KX028_PORTS_TAG_ID);
    uint32_t portCfgStruct2 = AXI_CLASS_STRUC2_FILL(  KX028_PORTS_SHUTDOWN, 
                                                      KX028_PORTS_AFT,
                                                      KX028_PORTS_BLOCKSTATE, 
                                                      KX028_PORTS_DEF_CFI, 
                                                      KX028_PORTS_DEF_PRI, 
                                                      KX028_PORTS_DEF_TC,
                                                      KX028_PORTS_TRUSTED, 
                                                      KX028_PORTS_VID_PREFIX, 
                                                      KX028_PORTS_UNTAG_FROM_BTABLE);
  
    //uint32_t classBase = AXI_CLASS_HW1_BASE_ADDR;
    for( classNum = 0; classNum < 2; classNum++ )
    {
      for( ucI = 0; ucI < KX028_EMAC_NUMS; ucI++ )
      {
          addrReg1 = addrClass[classNum] + KX028_PortOffsStruct1[ucI];
          addrReg2 = addrClass[classNum] + KX028_PortOffsStruct2[ucI];
        
          MDR_KX028_WriteAXI( addrReg1,  portCfgStruct1);                
          MDR_KX028_WriteAXI( addrReg2, portCfgStruct2);
      }     
        
        //????????????????????????????????????????????????????????????????
        //wr_axi( classBase + CLASS_HW_BCAST_PORTMAP, FWD_PORT_LIST_MASK );
        
        /* Configure STP MAC details */
        //MDR_KX028_WriteAXI( classBase + AXI_CLASS_SNOOP_CTRL, STP_CTRL_REG_VAL );
        //MDR_KX028_WriteAXI( classBase + AXI_CLASS_SNOOP_CTRL, 0 );
        //MDR_KX028_WriteAXI( classBase + AXI_CLASS_SNOOP_SPL_MCAST_ADDR1_LSB, STP_MAC_ADDR1_LSB );
        //MDR_KX028_WriteAXI( classBase + AXI_CLASS_SNOOP_SPL_MCAST_ADDR1_MSB, STP_MAC_ADDR1_MSB );
        //MDR_KX028_WriteAXI( classBase + AXI_CLASS_SNOOP_SPL_MCAST_ADDR2_LSB, STP_MAC_ADDR2_LSB );
        //MDR_KX028_WriteAXI( classBase + AXI_CLASS_SNOOP_SPL_MCAST_ADDR2_MSB, STP_MAC_ADDR2_MSB );
        //MDR_KX028_WriteAXI( classBase + AXI_CLASS_SNOOP_SPL_MCAST_MASK1_LSB, STP_MAC_MASK1_LSB );
        //MDR_KX028_WriteAXI( classBase + AXI_CLASS_SNOOP_SPL_MCAST_MASK1_MSB, STP_MAC_MASK1_MSB );
        //MDR_KX028_WriteAXI( classBase + AXI_CLASS_SNOOP_SPL_MCAST_MASK2_LSB, STP_MAC_MASK2_LSB );
        //MDR_KX028_WriteAXI( classBase + AXI_CLASS_SNOOP_SPL_MCAST_MASK2_MSB, STP_MAC_MASK2_MSB );
        
        //wr_axi( classBase + CLASS_HW_GLOBAL_CUTTHRU_REG, CUT_THRU_PORTLIST | ( STPID1 << STPID1_START_POS ) );
      
//      //  The same for CLASS2_HW2
//      classBase = AXI_CLASS_HW1_BASE_ADDR;
    }
}



static inline void AXI_IndirExecCommand(uint32_t command)
{
  MDR_KX028_WriteAXI(AXI_TMU_INDIRECT_ACCESS_CMD_REG, command);
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

void MDR_KX028_Mode2_Init( uint32_t waitCyclesMax )
{
    uint32_t i, j, reg;
    uint32_t status;
    MDR_KX028_VLAN_Entry_t action_entry;
        
    MDR_KX028_WriteAXI( AXI_BMU1_BASE_ADDR + 0x04, 0x3 );
    MDR_KX028_WriteAXI( AXI_BMU2_BASE_ADDR + 0x04, 0x3 );
    
    MDR_KX028_WriteAXI( ( AXI_WSP_GLOBAL_BASE_ADDR + 0x20 ), ( 1 << 30 ) );
    MDR_KX028_DelayMs(1000); //    vTaskDelay( 1000 );
    MDR_KX028_WriteAXI( ( AXI_WSP_GLOBAL_BASE_ADDR + 0x20 ), 0 );

    Write_InitHW_Table(&sw_hwreg_settings[0]);
    
    for( i = 0; i < KX028_EMAC_NUMS; i++ )
      MDR_KX028_InitEMAC(i);
    
    // Context memory init
    /*
    for( i = 0; i < 17; i++ )
    {
        for( j = 0; j < 8; j++ )
        {
            MDR_KX028_WriteAXI( ( AXI_TMU_BASE_ADDR + 0x034 ), ( i << 8 ) | j );                            // i - ����� PHY, j - ����� �������
            MDR_KX028_WriteAXI( ( AXI_TMU_BASE_ADDR + 0x038 ), 0x00000000 );
            MDR_KX028_WriteAXI( ( AXI_TMU_BASE_ADDR + 0x03C ), 0x00000000 );
            MDR_KX028_WriteAXI( ( AXI_TMU_BASE_ADDR + 0x040 ), 0x00000000 );
            MDR_KX028_WriteAXI( ( AXI_TMU_BASE_ADDR + 0x044 ), 0x00000000 );
            MDR_KX028_WriteAXI( ( AXI_TMU_BASE_ADDR + 0x048 ), 0x00000000 );
            MDR_KX028_WriteAXI( ( AXI_TMU_BASE_ADDR + 0x04C ), 0x00000000 );
            MDR_KX028_WriteAXI( ( AXI_TMU_BASE_ADDR + 0x050 ), 0x00000000 );
            MDR_KX028_WriteAXI( ( AXI_TMU_BASE_ADDR + 0x054 ), 0x00000000 );                                //___Q no in spec
        }
    }
    */
    
    /* Config Queues for Port 1 - 16*/
    for( i = 0; i < 16; i++ ){
      for( j = 0; j < 8; j++ ){
        for( reg = 0; reg < 8; reg++ )
        {
          MDR_KX028_WriteAXI( AXI_TMU_INDIRECT_ACCESS_PAR1_REG, (i << 16) + (j << 3) + reg );
          MDR_KX028_WriteAXI( AXI_TMU_INDIRECT_ACCESS_PAR2_REG, 0 );
          AXI_IndirExecCommand(AXI_TMU_INDIRECT_ACCESS_CMD_WRITE | AXI_TMU_INDIRECT_ACCESS_CMD_START);
          AXI_IndirWaitCompleted(AXI_TMU_INDIRECT_ACCESS_CMD_DONE, &status, waitCyclesMax);          
        }
      }
    }
    
    // Config Queues for Management Port (17)
    for( j = 0; j < 8; j++ ){   //for all queues
      for( reg = 0; reg < 8; reg++ )
      {   //for all regs
        MDR_KX028_WriteAXI( AXI_TMU_INDIRECT_ACCESS_PAR1_REG, (16 << 16) + (j << 3) + reg );
        
        if( reg == 4 )
          MDR_KX028_WriteAXI( AXI_TMU_INDIRECT_ACCESS_PAR2_REG, ( 3 << 11)|( 1 << 0 ) );       //max 3 packets in queue, tail drop
          //MDR_KX028_WriteAXI( AXI_TMU_INDIRECT_ACCESS_PAR2_REG, ( 1 << 11)|( 1 << 0 ) );       //max 1 packets in queue, tail drop
        else
          MDR_KX028_WriteAXI( AXI_TMU_INDIRECT_ACCESS_PAR2_REG, 0 );

        AXI_IndirExecCommand(AXI_TMU_INDIRECT_ACCESS_CMD_WRITE | AXI_TMU_INDIRECT_ACCESS_CMD_START);
        AXI_IndirWaitCompleted(AXI_TMU_INDIRECT_ACCESS_CMD_DONE, &status, waitCyclesMax);          
      }
    }
        
    /*---------------------------------------*/
    /* Config Shapers for Port (17) */
    /* Disable shaper, scheduler of HOST interface in TMU */
//    rd_axi( ( AXI_TMU_BASE_ADDR + TMU_PHY16_TDQ_CTRL ), i );
//    i &= ~(1 << 1);
//    MDR_KX028_WriteAXI( ( AXI_TMU_BASE_ADDR + TMU_PHY16_TDQ_CTRL ), i );
//    
//    param.tlsp_shpr_id = 1;
//    param.tlsp_dev_id = 17;
//    param.tlsp_clk_frequency = 200;
//    param.tlsp_rate = 10;
//    param.tlsp_rate_units = 2;
//    param.tlsp_max_credit = 1;
//    param.tlsp_position = 1;
//    param.tlsp_min_credit = 0;
//    param.tlsp_mode = 0;
//      
//    pcm_tlite_shaper_config( &param, 0 );
    MDR_KX028_WriteAXI( CFG_NEW_PACKET_IN_LMEM_REG_ADDR, 0 );
    MDR_KX028_WriteAXI( ( AXI_HGPI_BASE_ADDR + 4 ), 3 );
//    
//    /* Enable shaper, scheduler of HOST interface in TMU */
//    MDR_KX028_WriteAXI( ( AXI_TMU_BASE_ADDR + TMU_PHY16_TDQ_CTRL ), 0xF );
    /*---------------------------------------*/
    
    Write_InitHW_Table( &sw_hwreg_enable_bmu_1_2_egpi_1_to_16[0] );
    Write_InitHW_Table( &sw_hwreg_enable_class_1_2[0] );
          
    MDR_KX028_MAC_TableInit(waitCyclesMax);
    MDR_KX028_VLAN_TableInit(waitCyclesMax);
    
    action_entry.value = MDR_KX028_FILL_VLAN_ENTRY(MDR_KX028_FWD_PORT_LIST_MASK, 0, ACT_FORWARD, ACT_FORWARD, ACT_FORWARD, ACT_FORWARD, ACT_FORWARD);      
    MDR_KX028_VLAN_TableAdd( 1, action_entry, waitCyclesMax);
    
    Write_InitHW_Table( &sw_hwreg_enable_emac_1_to_16[0] );
    MDR_KX028_PortsInit();
    
#if MDR_KX028_DEBUG    
    Printf_InitHW_Table( &sw_hwreg_settings[0] );
    Printf_InitHW_Table( &sw_hwreg_enable_bmu_1_2_egpi_1_to_16[0] );
    Printf_InitHW_Table( &sw_hwreg_enable_class_1_2[0] );
    Printf_InitHW_Table( &sw_hwreg_enable_emac_1_to_16[0] );
#endif

//    xSemaphoreGive( xCfgSemaphore );    //release the semaphore, setup complete
}


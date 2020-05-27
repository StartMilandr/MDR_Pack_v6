#include <MDR_1923KX028_M2_TablesCtrl.h>
#include <MDR_1923KX028_ErrLog.h>
#include <MDR_1923KX028_M2_Defs.h>

/* 2-field Mac table format: Table Depth - 1024(hash 512 + collison 512)
*============================================================================*
* valid bits | col_ptr | portNO | field_valids | action entry | vlanid|  MAC *
*============================================================================*
* 4-bit      | 16-bit  | 4-bit  | 8-bit(mac4)  | 31-bit (mac3)| 13-bit|48-bit*
*============================================================================*/

/*=============================================================================*
* MAC1:MAC[31:0]                                                               *
*==============================================================================*
* MAC2:ACT_ENTRY[31:29] + VLANID[28:16] + MAC[15:0]                            *
*==============================================================================*
* MAC3:FIELD_VALIDS[31:28] + ACT_ENTRY[27:0]                                   *
*==============================================================================*
*MAC4:RSVD[31:28]+VALIDBITS[27:24]+COLPTR[23:8]+ PORTNO[7:4] + FIELDVALIDS[3:0]*
*=============================================================================*/

static void MDR_KX028_MAC_DeleteTableItem(MDR_KX028_MAC_TableItem_t *tableItem, uint32_t waitCyclesMax)
{
  uint8_t mac[6];
  uint16_t vlanid;
  
  mac[0] = ( tableItem->regMAC1 >> 24 ) & 0xFF;
  mac[1] = ( tableItem->regMAC1 >> 16 ) & 0xFF;
  mac[2] = ( tableItem->regMAC1 >> 8 )  & 0xFF;
  mac[3] =   tableItem->regMAC1 & 0xFF;
  mac[4] = ( tableItem->regMAC2 >> 8 )  & 0xFF;
  mac[5] =   tableItem->regMAC2 & 0xFF;
  vlanid = ( tableItem->regMAC2 >> 16 ) & 0xFFFF;

// taskENTER_CRITICAL();
  MDR_KX028_MAC_TableDel(mac, vlanid, waitCyclesMax);
// taskEXIT_CRITICAL();            
}

static inline void MDR_KX028_MAC_ReadTableItem( MDR_KX028_MAC_TableItem_t *tableItem, uint16_t entry, uint32_t waitCyclesMax)
{
// taskENTER_CRITICAL();
  MDR_KX028_MAC_TableRead(tableItem, entry, waitCyclesMax);
// taskEXIT_CRITICAL();  
}

static inline void MDR_KX028_MAC_WriteTableItem( MDR_KX028_MAC_TableItem_t *tableItem, uint16_t entry, uint32_t waitCyclesMax)
{
// taskENTER_CRITICAL();
  MDR_KX028_MAC_TableWrite(tableItem, entry, waitCyclesMax);
// taskEXIT_CRITICAL();  
}

#define IS_ITEM_VALID(item)          (item).regMAC4 & AXI_HASH_REG4_ENTRY_VALID_FLAG
#define IS_ITEM_HAS_COLLISION(item)  (item).regMAC4 & AXI_HASH_REG4_ENTRY_COLL_FLAG
#define IS_ITEM_FRESH(item)          (item).regMAC3 & AXI_HASH_REG3_ENTRY_FRESH_FLAG
#define IS_ITEM_NOT_STATIC(item)     !((item).regMAC3 & AXI_HASH_REG3_ENTRY_STATIC_FLAG)



void MDR_KX028_M2_ProcessTablesAgeing(uint32_t framesToProcessMax, uint32_t waitCyclesMax)
{
    uint32_t hashidx, coll_ptr;
    MDR_KX028_MAC_TableItem_t tableItem;
    uint16_t entry;

    static uint32_t hashBase = 0;

    for (hashidx = 0; hashidx <  framesToProcessMax; hashidx++)
    {
        coll_ptr = 0;
        entry = hashBase + hashidx;
        MDR_KX028_MAC_ReadTableItem(&tableItem, entry, waitCyclesMax);

        if (IS_ITEM_VALID(tableItem))
        {
          if (IS_ITEM_HAS_COLLISION(tableItem))
            coll_ptr = ( tableItem.regMAC4 >> 8 ) & 0xFFFF;

          if (IS_ITEM_FRESH(tableItem))
            MDR_KX028_MAC_DeleteTableItem(&tableItem, waitCyclesMax);              // FRESH bit set, so delete entry
          else if (IS_ITEM_NOT_STATIC(tableItem))
          {
            tableItem.regMAC3 |= AXI_HASH_REG3_ENTRY_FRESH_FLAG;    // Set FRESH bit, if entry isn't static
            MDR_KX028_MAC_WriteTableItem(&tableItem, entry, waitCyclesMax);
          }
        }

        // Process collision space entries
        while( coll_ptr )
        {
          MDR_KX028_MAC_ReadTableItem(&tableItem, coll_ptr, waitCyclesMax);

          if (IS_ITEM_VALID(tableItem))
          { 
            if (IS_ITEM_FRESH(tableItem))
              MDR_KX028_MAC_DeleteTableItem(&tableItem, waitCyclesMax);              // FRESH bit set, so delete entry
            else if (IS_ITEM_NOT_STATIC(tableItem))
            {
              tableItem.regMAC3 |= AXI_HASH_REG3_ENTRY_FRESH_FLAG;    // Set FRESH bit, if entry isn't static
              MDR_KX028_MAC_WriteTableItem(&tableItem, coll_ptr, waitCyclesMax);
            }
            
            if (IS_ITEM_HAS_COLLISION(tableItem))
              coll_ptr = ( tableItem.regMAC4 >> 8 ) & 0xFFFF;
            else
              coll_ptr = 0;
          }
          else
            coll_ptr = 0;
        }
    }

    // update hashBase
    hashBase += hashidx;

    // updating entries in blocks
    if (hashBase >= MDR_KX028_MAC_TABLE_LEN){
      hashBase = 0;
    }
}


//========================   Frame Learning ==========================
#define _ETH_TYPE_VLAN  0x8100

typedef struct {
  uint8_t  ctrl;
  uint8_t  portNum;
  uint8_t  puntReason;
  uint8_t  reserved;
} MDR_KX028_FrameCtrl_Fields;

typedef union {
} MDR_KX028_FrameCtrl;

typedef struct {
  uint32_t   size;
  union {
    uint32_t                    ctrl;
    MDR_KX028_FrameCtrl_Fields  ctrl_b;
  };
  uint32_t   destMAC;
  uint32_t   destMAC_srcMAC;
  uint32_t   srcMAC;
  uint32_t   vlanTag;
} MDR_KX028_FrameInfo;

static inline uint32_t PortGetAddrStruct1_HW1(uint32_t portInd)
{
  if (portInd < AXI_CLASS_PORT_COUNT)
  {
    MDR_KX028_Log(MDR_KX028_Log_Learn_WrongStructInd, portInd);
    portInd = 0;
  }    
  return AXI_CLASS_HW1_BASE_ADDR + KX028_PortOffsStruct1[portInd];
}
  

bool fp_switch_host_learn( MDR_KX028_FrameInfo *frmInfo, bool static_entry, uint32_t waitCyclesMax )
{  
  uint32_t vlan_id, fwd_action, action_port;
  MDR_KX028_MAC_Entry_t entryMAC;
  MDR_KX028_MAC_Entry_t actionEntry;
  MDR_KX028_VLAN_Entry_t entryVLAN;
  bool result;
  uint8_t *src_mac;
  
  if( ( ( frmInfo->vlanTag >> 16 ) & 0xFFFF ) == _ETH_TYPE_VLAN ) 
    vlan_id = frmInfo->vlanTag & 0x0FFF;                          //get vlan id from packet
  else 
  {                
    uint32_t addr = PortGetAddrStruct1_HW1(frmInfo->ctrl_b.portNum);
    vlan_id = MDR_KX028_ReadAXI(addr);                            //get vlan id from register
    vlan_id = ( ( vlan_id >> 16 ) & 0xFFF );
  }  
  //printf( "vlan id %d\n", vlan_id );
  
////src_mac = ( uint8_t* )( ( ( uint32_t )ptr ) + 22 );  
//  src_mac[0] = ( ( ptr[5] >> 8 ) & 0xFF );
//  src_mac[1] = (   ptr[5] & 0xFF );
//  src_mac[2] = ( ( ptr[6] >> 24 ) & 0xFF );
//  src_mac[3] = ( ( ptr[6] >> 16 ) & 0xFF );
//  src_mac[4] = ( ( ptr[6] >> 8 ) & 0xFF );
//  src_mac[5] = (   ptr[6] & 0xFF );
  src_mac = (uint8_t *)(&frmInfo->destMAC) + 2;
  
  //printf( "src mac %02X:%02X:%02X:%02X:%02X:%02X\n", src_mac[0], src_mac[1], src_mac[2], src_mac[3], src_mac[4], src_mac[5] );
  entryMAC = MDR_KX028_MAC_TableSearch( src_mac, vlan_id, waitCyclesMax);

  actionEntry.value = 0;    
  if( entryMAC.value == -1 )  // Search fail
  {     
    //printf( "Search in mac fail\n" );
    if (static_entry)
      actionEntry.value |= MDR_KX028_MAC_ENTRY_STATIC_MSK;  // Static entry     
    actionEntry.value |= ( 1 << frmInfo->ctrl_b.portNum ) & MDR_KX028_MAC_ENTRY_FWD_PORT_LIST_MSK;
    
    entryVLAN = MDR_KX028_VLAN_TableSearch(vlan_id, waitCyclesMax);
    if( entryVLAN.value == -1 ){
      //printf( "Search in vlan fail\n" );
      fwd_action = MDR_KX028_ReadAXI( AXI_CLASS_HW1_BASE_ADDR + AXI_CLASS_GLOBAL_CFG1 );
      fwd_action = ( fwd_action >> AXI_CLASS_CFG1_FRW_ACK_Pos ) & AXI_CLASS_CFG1_FRW_ACK_Msk;
    }else{
      fwd_action = (entryVLAN.value & MDR_KX028_VLAN_ENTRY_UCAST_HIT_ACT_MASK) >> MDR_KX028_VLAN_ENTRY_UCAST_HIT_ACT_POS;
    }
    
    actionEntry.value = (actionEntry.value & ~MDR_KX028_MAC_ENTRY_FWD_ACT_MSK) | (fwd_action << MDR_KX028_MAC_ENTRY_FWD_ACT_POS);
    
    result = MDR_KX028_MAC_TableAdd( src_mac, vlan_id, actionEntry, waitCyclesMax);
//    if (!result)
//      //printf( "Add to mac fail!\n" );    
  }
  else
  { // MAC hash entry found
    //printf( "Search in mac success\n" );
    actionEntry.value = entryMAC.value;
    switch (frmInfo->ctrl_b.puntReason)
    {
      case KX028_FRAME_PUNT_SA_IS_ACTIVE:
        //printf( "Punt is ACTIVE\n" );
        if (actionEntry.value & MDR_KX028_MAC_ENTRY_FRESH_MSK)
          actionEntry.value = ( actionEntry.value & ~MDR_KX028_MAC_ENTRY_FRESH_MSK );
        else
          return true;
        //  Unreachable
        break;
        
      case KX028_FRAME_PUNT_SA_RELEARN:
      {
        //printf( "Punt is RELEARN\n" );
        uint32_t rxPortSel = ( 1 << frmInfo->ctrl_b.portNum );
        action_port = ( result & MDR_KX028_MAC_ENTRY_FWD_PORT_LIST_MSK  &  rxPortSel);
            
        if ( !action_port ) 
        {
          actionEntry.value &= ~MDR_KX028_MAC_ENTRY_FWD_PORT_LIST_MSK;
          actionEntry.value |= ( rxPortSel & MDR_KX028_MAC_ENTRY_FWD_PORT_LIST_MSK );
        }
        break;
      }
       
      case KX028_FRAME_PUNT_SA_MISS:
        //printf( "Punt is MISS\n" );
        return 0;
       
      default:
        break;
    }
    result = MDR_KX028_MAC_TableUpdate( src_mac, vlan_id, actionEntry, waitCyclesMax);
//    if( result.value == -1 )
//      printf( "Add to mac fail!\n" );
    
  }
  return result;
}

static void free_buffers_of_packets( uint32_t start_packet_pointer, int32_t pck_size)
{
  uint32_t tmp, next_buffer, offset;
  
  tmp = start_packet_pointer;
  offset = 32;
  
  while(1)
  {
    next_buffer = MDR_KX028_ReadAXI(tmp);
    //printf("\n\r\tbuffer for free: 0x%X, next buffer: 0x%X", tmp, next_buffer );
    
    if( ( tmp & 0xFFE00000) == 0xC0200000 ){
      MDR_KX028_WriteAXI(AXI_BMU1_BASE_ADDR + AXI_BMU_FREE_CTRL, tmp);
    }else{
      MDR_KX028_WriteAXI(AXI_BMU1_BASE_ADDR + AXI_BMU_FREE_CTRL, tmp);
    }
    
    pck_size -= (128 - offset);
    offset = 16;
    tmp = next_buffer;
    if( ( ( tmp & 0xFFE00000) != 0xC0200000) && ( ( tmp & 0xFFE00000) != 0xC0400000) )
    {
      //printf("\n\r\tall buffers for this packet was free\n\r");
      break;
    }
    if( pck_size <= 0)
    {
      //printf("\n\r\tlen equal or below 0\n\r");
      break;
    }
  } ;
}

static void MDR_KX028_ProcessFrame(uint32_t frameAddr, uint32_t waitCyclesMax)
{   
    MDR_KX028_FrameInfo frmInfo;
      
  // taskENTER_CRITICAL();

    frameAddr &= KX028_FRAME_PTR_ADDR_MSK;
    frmInfo.size = MDR_KX028_ReadAXI(frameAddr + KX028_FRAME_SIZE_ADDR_OFFS) & KX028_FRAME_SIZE_MSK;
    frmInfo.ctrl = MDR_KX028_ReadAXI(frameAddr + KX028_FRAME_PR_ADDR_OFFS);
        
    if( frmInfo.ctrl_b.ctrl & KX028_FRAME_CTRL_FP_RX_TS_REPORT_EN)
    {    
      //timestamp report      
    }
    else
    {      
      //packet      
      if( !( frmInfo.ctrl_b.ctrl & KX028_FRAME_CTRL_FP_PUNT_VALID ) )
      { 
        //packet doesn't punt with reasone code (normal packet)
      }
      else
      {    
        frmInfo.destMAC = MDR_KX028_ReadAXI( frameAddr + 32 + 16);          //DST MAC
        frmInfo.destMAC_srcMAC = MDR_KX028_ReadAXI( frameAddr + 36 + 16);   //DST MAC, SRC MAC
        frmInfo.srcMAC  = MDR_KX028_ReadAXI( frameAddr + 40 + 16);          //SRC MAC
        frmInfo.vlanTag = MDR_KX028_ReadAXI( frameAddr + 44 + 16);          //VLAN TAG
        
        //printf( "Pck ptr: 0x%X port num %d punt res %d ctrl 0x%X size %d\n", pck_pointer, packet_buffer[1], packet_buffer[3], packet_buffer[2], packet_buffer[0] );
        //printf( "Pck: %08X %08X %08X %08X\n", packet_buffer[4], packet_buffer[5], packet_buffer[6], packet_buffer[7] );
        
        switch( frmInfo.ctrl_b.puntReason ){          
          case KX028_FRAME_PUNT_SA_MISS:
          case KX028_FRAME_PUNT_SA_RELEARN:
          case KX028_FRAME_PUNT_SA_IS_ACTIVE:
            fp_switch_host_learn( &frmInfo, 0, waitCyclesMax);
            break;
          
          default:
          break;
        }        
      }
    }
    
    // Free BMU buffers
    free_buffers_of_packets(frameAddr, frmInfo.size);
    // Free polling register
    MDR_KX028_WriteAXI(CFG_NEW_PACKET_IN_LMEM_REG_ADDR, 0 );
    // Reset HGPI
    MDR_KX028_WriteAXI(AXI_HGPI_BASE_ADDR + 4, 3 );
    
//    taskEXIT_CRITICAL();
}


//  Return processed frames count
uint32_t MDR_KX028_M2_ProcessTablesLearning(uint32_t framesToProcessMax, uint32_t waitCyclesMax)
{
  uint32_t i = 0;
  uint32_t pck_pointer = 0;
  
  for (i = 0; i < framesToProcessMax; i++)
  {
    pck_pointer = MDR_KX028_ReadAXI(CFG_NEW_PACKET_IN_LMEM_REG_ADDR);   
    if (pck_pointer)
      MDR_KX028_ProcessFrame(pck_pointer, waitCyclesMax);
    else
      break;  
  }
  
  return i;
}


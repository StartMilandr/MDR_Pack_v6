#include <MDR_1923KX028_M2_TableVLAN.h>
#include <MDR_1923KX028_ErrLog.h>
#include <stdio.h>


static uint32_t AXI_BUS_ReadIndirect(uint32_t offset)
{
    MDR_KX028_WriteAXI( AXI_CLASS_BUS_ACCESS_ADDR, offset );
    return MDR_KX028_ReadAXI( AXI_CLASS_BUS_ACCESS_RDATA);
}

static void AXI_BUS_WriteIndirect(uint32_t offset, uint32_t value)
{
    MDR_KX028_WriteAXI(AXI_CLASS_BUS_ACCESS_WDATA, value);
    MDR_KX028_WriteAXI(AXI_CLASS_BUS_ACCESS_ADDR, offset | AXI_BUS_ACCESS_RD_FLAG);
}


static bool AXI_BUS_WaitCommandCompleted(uint32_t readyMask,  uint32_t *status, uint32_t waitCyclesMax)
{
  while (--waitCyclesMax)
  {
    *status = AXI_BUS_ReadIndirect(AXI_BUS_VLAN_STATUS_REG);
    if ((*status & readyMask) == readyMask)
      return true;
  }
  return false; 
}

static inline void AXI_BUS_ClearStatus(void)
{
  AXI_BUS_WriteIndirect(AXI_BUS_VLAN_STATUS_REG, AXI_HASH_STAT_REG_CLR );
}

static inline void AXI_BUS_ExecCommand(uint32_t command)
{
  AXI_BUS_WriteIndirect(AXI_BUS_VLAN_CMD_REG, command);
}


static inline void AXI_WriteMAC_Regs(uint32_t classBaseAddr, uint16_t vlanId)
{
  // initialize MAC regs
  MDR_KX028_WriteAXI( classBaseAddr + AXI_CLASS_DAVLANHASH_HOST_MAC_ADDR1_REG, vlanId);
  MDR_KX028_WriteAXI( classBaseAddr + AXI_CLASS_DAVLANHASH_HOST_MAC_ADDR2_REG, 0x00);
  MDR_KX028_WriteAXI( classBaseAddr + AXI_CLASS_DAVLANHASH_HOST_MAC_ADDR3_REG, 0x00);
  MDR_KX028_WriteAXI( classBaseAddr + AXI_CLASS_DAVLANHASH_HOST_MAC_ADDR4_REG, 0x00);
  MDR_KX028_WriteAXI( classBaseAddr + AXI_CLASS_DAVLANHASH_HOST_MAC_ADDR5_REG, 0x00);
}

static inline void AXI_ExecCommand(uint32_t classBaseAddr, uint32_t command)
{
  MDR_KX028_WriteAXI( classBaseAddr + AXI_CLASS_DAVLANHASH_HOST_CMD_REG, command);
}

static inline void AXI_ClearStatus(uint32_t classBaseAddr)
{
  MDR_KX028_WriteAXI( classBaseAddr + AXI_CLASS_DAVLANHASH_HOST_STATUS_REG, AXI_HASH_STAT_REG_CLR);
}

static bool AXI_WaitCommandCompleted(uint32_t classBase, uint32_t readyMask,  uint32_t *status, uint32_t waitCyclesMax)
{
  classBase = classBase + AXI_CLASS_DAVLANHASH_HOST_STATUS_REG;
  while (--waitCyclesMax)
  {
    *status = MDR_KX028_ReadAXI(classBase);
    if ((*status & readyMask) == readyMask)
      return true;
  }
  return false;
}


//   Returns entry values if found, -1 - NotFound
MDR_KX028_VLAN_Entry_t MDR_KX028_VLAN_TableSearch(uint16_t vlanid, uint32_t waitCyclesMax)
{
    uint32_t status;
    MDR_KX028_VLAN_Entry_t result;

    // Write Params
    AXI_BUS_WriteIndirect( ( AXI_BUS_VLAN_MAC1_REG ), ( vlanid & AXI_VLAN_VALID_ID_MSK ) );
    AXI_BUS_WriteIndirect( ( AXI_BUS_VLAN_MAC2_REG ), 0 );
    AXI_BUS_WriteIndirect( ( AXI_BUS_VLAN_MAC3_REG ), 0 );
    AXI_BUS_WriteIndirect( ( AXI_BUS_VLAN_MAC4_REG ), 0 );
    AXI_BUS_WriteIndirect( ( AXI_BUS_VLAN_MAC5_REG ), 0 );
    // Exec CMD
    AXI_BUS_ExecCommand(AXI_HASH_CMD_ID_SEARCH | AXI_HASH_CMD_VALID_MAC1_Msk);    
    bool resOk = AXI_BUS_WaitCommandCompleted(AXI_HASH_STAT_CMD_DONE, &status, waitCyclesMax);    
    AXI_BUS_ClearStatus();
    
    // Bridge entry match done check
    if( resOk && (status & AXI_HASH_STAT_ENTR_MATCH) )
    { // SEARCH FOUND
      result.value64.lo32 = AXI_BUS_ReadIndirect( AXI_BUS_VLAN_ENTRY_REG );
      result.value64.hi32 = AXI_BUS_ReadIndirect( AXI_BUS_VLAN_DIRECT_REG );      

      // Clear req entry reg
      AXI_BUS_WriteIndirect( AXI_BUS_VLAN_ENTRY_REG, 0x0 );
      AXI_BUS_WriteIndirect( AXI_BUS_VLAN_DIRECT_REG, 0x0 );
    }
    else
    { // SEARCH NOT FOUND
      result.value = -1;
    } 
    
  return result;    
}

    /* vlan group table format *
    *======================================================================*
    * valid bits | col_ptr | portNo | field_valids | action entry | vlan   *
    *======================================================================*
    * 4-bit      | 16-bit  | 4-bit  | 8-bit        | 55-bit       | 12-bit *
    *=====================================================================*/

    /* VLAN (BD) Hash table action entry map:*
    *=======================================*
    * [19:0]        - forward port list
    * [39:20]       - untag list
    * [42:40]		    - ucast_hit_action
    * [45:43]       - mcast_hit_action
    * [48:46]       - ucast_miss_action
    * [51:49]       - mcast_miss_action
    * [54-52]       - Not used yet
    *=======================================*/


bool MDR_KX028_VLAN_TableAdd(uint16_t vlanid, MDR_KX028_VLAN_Entry_t brentry, uint32_t waitCyclesMax)
{
    uint32_t status, classNum, classBase;//, entry1, entry2;
    bool result = true;
    
    classBase = AXI_CLASS_HW1_BASE_ADDR;
    for( classNum = 1; classNum <= 2; classNum++ )
    {
        // Write entries corresponding MAC REGs
        AXI_WriteMAC_Regs(classBase, vlanid & AXI_VLAN_VALID_ID_MSK);
        MDR_KX028_WriteAXI( classBase + AXI_CLASS_DAVLANHASH_HOST_ENTRY_REG, brentry.value64.lo32);
        MDR_KX028_WriteAXI( classBase + AXI_CLASS_DAVLANHASH_HOST_DIRECT, brentry.value64.hi32);

        // Exec ADD
        AXI_ExecCommand(classBase, AXI_HASH_CMD_ID_ADD | AXI_HASH_CMD_VALID_MAC1_Msk);     
        bool resOK = AXI_WaitCommandCompleted(classBase, AXI_HASH_STAT_CMD_DONE, &status, waitCyclesMax);
        AXI_ClearStatus(classBase);

        if (!(resOK && (status | AXI_HASH_STAT_ENTR_ADD)))
        {
            MDR_KX028_Log(MDR_KX028_Log_VLAN_Table_AddFault, classNum);
            result = false;
        }
        
        //  Repeat the same for CLASS_HW2
        classBase = AXI_CLASS_HW2_BASE_ADDR;
    }

	return result;
}


bool MDR_KX028_VLAN_TableDel(uint16_t vlanid, uint32_t waitCyclesMax)
{
    uint32_t status, classNum, classBase;
	  bool result = true;

    classBase = AXI_CLASS_HW1_BASE_ADDR;
    for( classNum = 1; classNum <= 2; classNum++ )
    {
        // Write entries corresponding MAC REG
        AXI_WriteMAC_Regs(classBase, vlanid & AXI_VLAN_VALID_ID_MSK);
        AXI_ExecCommand(classBase, ( AXI_HASH_CMD_ID_DEL | AXI_HASH_CMD_VALID_MAC1_Msk ) );
        bool resOK = AXI_WaitCommandCompleted(classBase, AXI_HASH_STAT_CMD_DONE, &status, waitCyclesMax);
        AXI_ClearStatus(classBase);

        if (!resOK)
        {
            MDR_KX028_Log(MDR_KX028_Log_VLAN_Table_DelFault, classNum);
            result = false;
        }
        
        //  Repeat the same for CLASS_HW2
        classBase = AXI_CLASS_HW2_BASE_ADDR;
    }

	return result;
}


bool MDR_KX028_VLAN_TableUpdate(uint16_t vlanid, MDR_KX028_VLAN_Entry_t brentry, uint32_t waitCyclesMax)
{
    uint32_t status, classNum, classBase;
    bool result = true;
  
    classBase = AXI_CLASS_HW1_BASE_ADDR;
    for( classNum = 1; classNum <= 2; classNum++ )
    {
        AXI_WriteMAC_Regs(classBase, vlanid & AXI_VLAN_VALID_ID_MSK);
        MDR_KX028_WriteAXI(classBase + AXI_CLASS_DAVLANHASH_HOST_ENTRY_REG, brentry.value64.lo32);
        MDR_KX028_WriteAXI(classBase + AXI_CLASS_DAVLANHASH_HOST_DIRECT, brentry.value64.hi32);

        AXI_ExecCommand(classBase, AXI_HASH_CMD_ID_UPDATE | AXI_HASH_CMD_VALID_MAC1_Msk);
        bool resOK = AXI_WaitCommandCompleted(classBase, AXI_HASH_STAT_CMD_DONE, &status, waitCyclesMax);
        AXI_ClearStatus(classBase);

        if (!(resOK && (status & AXI_HASH_STAT_ENTR_ADD)))
          result = false;     // Entry Not Added
        
        //  Repeat the same for CLASS_HW2
        classBase = AXI_CLASS_HW2_BASE_ADDR;
    }
    
	  return result;
}


#define COLL_PTR_MSK          0x40000 
#define COLL_PTR_ADDR_START  (COLL_PTR_MSK | 0x00040)
#define COLL_PTR_ADDR_RETR    COLL_PTR_MSK 

void MDR_KX028_VLAN_TableInit(uint32_t waitCyclesMax)
{
    uint32_t status, i, classNum, collisionPtr, classBase;

    /* vlan group table format *
    *======================================================================*
    * valid bits | col_ptr | portNO  | field_valids | action entry | vlan  *
    *======================================================================*
    * 4-bit      | 16-bit  | 4-bit   | 8-bit        | 55-bit       | 13-bit*
    *   99 - 96  | 95 - 80 | 79 - 76 |	 75 - 68	|	67 - 13	   | 12 - 0*
    *======================================================================*/
    /*	CLASS_DAVLANHASH_HOST_MAC_ADDR1_REG	has VLAN entry bits:	31 - 0	*/
    /*	CLASS_DAVLANHASH_HOST_MAC_ADDR2_REG	has VLAN entry bits:	63 - 32	*/
    /*	CLASS_DAVLANHASH_HOST_MAC_ADDR3_REG	has VLAN entry bits:	95 - 64	*/
    /*	CLASS_DAVLANHASH_HOST_MAC_ADDR4_REG	has VLAN entry bits:	99 - 96	*/

    classBase = AXI_CLASS_HW1_BASE_ADDR;
    for( classNum = 1; classNum <= 2; classNum++ )
    {
        //  Init VLAN Table
        AXI_ClearStatus(classBase);
        AXI_ExecCommand(classBase, AXI_HASH_CMD_ID_INIT);
        bool resOK = AXI_WaitCommandCompleted(classBase, AXI_HASH_STAT_CMD_DONE, &status, waitCyclesMax);
        AXI_ClearStatus(classBase);

        if (!resOK)
            MDR_KX028_Log(MDR_KX028_Log_VLAN_Table_InitFault, classNum);

        AXI_WriteMAC_Regs(classBase, 0);
        MDR_KX028_WriteAXI( ( classBase + AXI_CLASS_DAVLANHASH_HOST_ENTRY_REG ), 0x0);
        MDR_KX028_WriteAXI( ( classBase + AXI_CLASS_DAVLANHASH_HOST_DIRECT ), 0x0);

        for( i = 0; i < VLAN_TABLE_HASH_ENTRIES; i++ )
        {
            if( i == (VLAN_TABLE_HASH_ENTRIES - 1) ){
                collisionPtr = COLL_PTR_ADDR_RETR;          // 0x40000
            }else{
                collisionPtr = COLL_PTR_ADDR_START + 1 + i; // 0x40041 + i
            }

            MDR_KX028_WriteAXI( classBase + AXI_CLASS_DAVLANHASH_HOST_MAC_ADDR3_REG, ( ( collisionPtr & 0xFFFF ) << 16 ) );
            MDR_KX028_WriteAXI( classBase + AXI_CLASS_DAVLANHASH_HOST_MAC_ADDR4_REG, ( ( collisionPtr >> 16 ) & 0xF ) );
            AXI_ExecCommand( classBase, AXI_HASH_CMD_ID_MEM_WRITE | ( ( VLAN_TABLE_HASH_ENTRIES + i ) << 16 ) );
            bool resOK = AXI_WaitCommandCompleted(classBase, AXI_HASH_STAT_CMD_DONE, &status, waitCyclesMax);
            AXI_ClearStatus(classBase);

            if( !resOK )
                MDR_KX028_Log(MDR_KX028_Log_VLAN_Table_SpaceFault, classNum);
        }

        MDR_KX028_WriteAXI( classBase + AXI_CLASS_DAVLANHASH_FREELIST_HEAD_PTR, VLAN_TABLE_INIT_HEAD_PTR );
        MDR_KX028_WriteAXI( classBase + AXI_CLASS_DAVLANHASH_FREELIST_TAIL_PTR, VLAN_TABLE_INIT_TAIL_PTR );
        MDR_KX028_WriteAXI( classBase + AXI_CLASS_DAVLANHASH_FREELIST_ENTRIES , VLAN_TABLE_HASH_ENTRIES );
        
        //  Repeat the same for CLASS_HW2
        classBase = AXI_CLASS_HW2_BASE_ADDR;
    }
}


// Read function for procFS 
static const uint8_t act[8][20] = {"ACT_FORWARD", "ACT_FLOOD", "ACT_PUNT", "ACT_DISCARD", "ACT_OVERRIDE", "ACT_FWD_MASK", "ACT_COS_DISCARD", "UNKNOWN"};

bool MDR_KX028_VLAN_TableRead( MDR_KX028_VLAN_TableItem *tableItem, uint16_t hashAddr, uint32_t waitCyclesMax )
{
    uint32_t status, classBase = AXI_CLASS_HW1_BASE_ADDR;
  
    AXI_ExecCommand( classBase, (hashAddr << AXI_HASH_CMD_ADDR_Pos) | AXI_HASH_CMD_ID_MEM_READ );
    bool resOK = AXI_WaitCommandCompleted(classBase, AXI_HASH_STAT_CMD_DONE, &status, waitCyclesMax);
    AXI_ClearStatus(classBase);

    if (resOK)
    {
      tableItem->regMAC1 = MDR_KX028_ReadAXI(classBase + AXI_CLASS_DAVLANHASH_HOST_MAC_ADDR1_REG);      
      if (tableItem->regMAC1)
      {
          tableItem->regMAC2 = MDR_KX028_ReadAXI(classBase + AXI_CLASS_DAVLANHASH_HOST_MAC_ADDR2_REG);
          tableItem->regMAC3 = MDR_KX028_ReadAXI(classBase + AXI_CLASS_DAVLANHASH_HOST_MAC_ADDR3_REG);
          tableItem->regMAC4 = MDR_KX028_ReadAXI(classBase + AXI_CLASS_DAVLANHASH_HOST_MAC_ADDR4_REG);
      }
      else
        resOK = false;
    }
    return resOK;
}

uint32_t MDR_KX028_VLAN_TableSprintf(char *buff, uint32_t waitCyclesMax)
{
    uint16_t pos;
    uint32_t tmp, dataLen;
    MDR_KX028_VLAN_TableItem tableItem;
    bool resOK;

    for (pos = 0; pos < 128; pos++)
    {
    //taskENTER_CRITICAL();
        resOK = MDR_KX028_VLAN_TableRead(&tableItem, pos, waitCyclesMax);
    //taskEXIT_CRITICAL();        

        if (resOK)
        {
            tmp = tableItem.regMAC1 & 0xFFF;
            dataLen = sprintf( buff, "VLAN ID:       %d\r\n", tmp );
            tmp = ((tableItem.regMAC1 >> 13)|((tableItem.regMAC2 & 1) << 20)) & 0xFFFFF;
            dataLen += sprintf( &buff[dataLen], "Forward list:  0x%05X\r\n", tmp );
            tmp = (tableItem.regMAC2 >> 1) & 0xFFFFF;
            dataLen += sprintf( &buff[dataLen], "Untag list:    0x%05X\r\n", tmp );
            tmp = (tableItem.regMAC2 >> 21) & 7;
            dataLen += sprintf( &buff[dataLen], "UnicastHit:    %s\r\n", act[tmp] );
            tmp = (tableItem.regMAC2 >> 27) & 7;
            dataLen += sprintf( &buff[dataLen], "UnicastMiss:   %s\r\n", act[tmp] );
            tmp = (tableItem.regMAC2 >> 24) & 7;
            dataLen += sprintf( &buff[dataLen], "MulticastHit:  %s\r\n", act[tmp] );
            tmp = ((tableItem.regMAC2 >> 30) & 7)|((tableItem.regMAC3 & 1) << 2);
            dataLen += sprintf( &buff[dataLen], "MulticastMiss: %s\r\n", act[tmp] );
            tmp = (tableItem.regMAC3 >> 1) & 7;
            dataLen += sprintf( &buff[dataLen], "Mstp:          %s\r\n", act[tmp] );
            tmp = (tableItem.regMAC3 >> 4) & 0xFF;
            dataLen += sprintf( &buff[dataLen], "True field:    0x%02X\r\n", tmp );
            tmp = (tableItem.regMAC3 >> 12) & 0xF;
            dataLen += sprintf( &buff[dataLen], "Port field:    0x%X\r\n", tmp );
            tmp = (tableItem.regMAC3 >> 16) & 0xFFFF;
            dataLen += sprintf( &buff[dataLen], "Collision ptr: 0x%04X\r\n", tmp );
            tmp = tableItem.regMAC4 & 0xF;
            dataLen += sprintf( &buff[dataLen], "Flags:         0x%X\r\n\r\n", tmp );

            return dataLen;
        }
    }

    return 0;
}

void MDR_KX028_VLAN_TableFlush(uint32_t optionMask, uint32_t waitCyclesMax)
{
  uint32_t status, classBase = AXI_CLASS_HW1_BASE_ADDR;

  AXI_ExecCommand(classBase, optionMask | AXI_HASH_CMD_ID_FLUSH );
  AXI_WaitCommandCompleted(classBase, AXI_HASH_STAT_CMD_DONE, &status, waitCyclesMax);
}


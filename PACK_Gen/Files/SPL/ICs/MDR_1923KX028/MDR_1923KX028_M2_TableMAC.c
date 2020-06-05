#include <MDR_Funcs.h>
#include <MDR_1923KX028_M2_TableMAC.h>
#include <MDR_1923KX028_ErrLog.h>
#include <stdio.h>

static bool AXI_WaitCommandCompleted(uint32_t classBase, uint32_t readyMask,  uint32_t *status, uint32_t waitCyclesMax)
{
  classBase = classBase + AXI_CLASS_DAMACHASH_HOST_STATUS_REG;
  while (--waitCyclesMax)
  {
    *status = MDR_KX028_ReadAXI(classBase);
    if ((*status & readyMask) == readyMask)
      return true;
  }
  return false;
}

static inline void AXI_WriteMAC_Regs(uint32_t classBaseAddr, uint8_t *mac, uint16_t vlanId)
{
  MDR_KX028_WriteAXI( classBaseAddr + AXI_CLASS_DAMACHASH_HOST_MAC_ADDR1_REG, ( mac[0] << 24 | mac[1] << 16 | mac[2] << 8 | mac[3] ) );
  MDR_KX028_WriteAXI( classBaseAddr + AXI_CLASS_DAMACHASH_HOST_MAC_ADDR2_REG, ( ((vlanId << 16) & 0xFFFF0000) | mac[4] << 8 | mac[5] ) );
  MDR_KX028_WriteAXI( classBaseAddr + AXI_CLASS_DAMACHASH_HOST_MAC_ADDR3_REG, 0x00 );
  MDR_KX028_WriteAXI( classBaseAddr + AXI_CLASS_DAMACHASH_HOST_MAC_ADDR4_REG, 0x00 );
}

static inline void AXI_ExecCommand(uint32_t classBaseAddr, uint32_t command)
{
  MDR_KX028_WriteAXI( classBaseAddr + AXI_CLASS_DAMACHASH_HOST_CMD_REG, command);
}

static inline void AXI_ClearStatus(uint32_t classBaseAddr)
{
  MDR_KX028_WriteAXI( classBaseAddr + AXI_CLASS_DAMACHASH_HOST_STATUS_REG, AXI_HASH_STAT_REG_CLR);
}

static inline void AXI_WriteEntry(uint32_t classBaseAddr, uint32_t entry)
{
  MDR_KX028_WriteAXI( classBaseAddr + AXI_CLASS_DAMACHASH_HOST_ENTRY_REG, entry);
}


MDR_KX028_MAC_Entry_t MDR_KX028_MAC_TableSearch(uint8_t *mac, uint16_t vlanId, uint32_t waitCyclesMax)
{
    uint32_t status, classBase = AXI_CLASS_HW1_BASE_ADDR;
    MDR_KX028_MAC_Entry_t result;

    // Run Command
    AXI_WriteMAC_Regs(classBase, mac, vlanId);
    AXI_ExecCommand(classBase, AXI_HASH_CMD_ID_SEARCH | AXI_HASH_CMD_VALID_MAC1_Msk | AXI_HASH_CMD_VALID_MAC2_Msk );
    bool cmdOk = AXI_WaitCommandCompleted(classBase, AXI_HASH_STAT_CMD_DONE, &status, waitCyclesMax);
  
    AXI_ClearStatus(classBase);

    // Bridge entry match done check
    if (cmdOk && ((status & AXI_HASH_STAT_ENTR_MATCH) != 0))
    { // FOUND
      result.value = MDR_KX028_ReadAXI(classBase + AXI_CLASS_DAMACHASH_HOST_ENTRY_REG);
//      result.value &= AXI_CLASS_MAC_2F_ENTRY_MASK;
      
      // Clear req entry reg
      AXI_WriteEntry(classBase, 0x0);
    }
    else { //  NOT FOUND
      result.value = -1;
    }
    return result;    
}


static int32_t MDR_KX028_MAC_TableAddHW(uint32_t classBaseAddr, uint8_t *mac, uint16_t vlanId, MDR_KX028_MAC_Entry_t entry, uint32_t waitCyclesMax)
{
    // Run Command
    AXI_WriteMAC_Regs(classBaseAddr, mac, vlanId);
    AXI_WriteEntry(classBaseAddr, entry.value);
    AXI_ExecCommand(classBaseAddr, AXI_HASH_CMD_ID_ADD | AXI_HASH_CMD_VALID_MAC1_Msk | AXI_HASH_CMD_VALID_MAC2_Msk);

    uint32_t  status;  
    bool cmdOk = AXI_WaitCommandCompleted(classBaseAddr, AXI_HASH_STAT_CMD_DONE, &status, waitCyclesMax);
    AXI_ClearStatus(classBaseAddr);

    if (cmdOk && ((status & AXI_HASH_STAT_ENTR_ADD) != 0))  
      return 0;
    else
      return -1;
}

bool MDR_KX028_MAC_TableAdd(uint8_t *mac, uint16_t vlaId, MDR_KX028_MAC_Entry_t entry, uint32_t waitCyclesMax)
{
  int32_t errCnt =  MDR_KX028_MAC_TableAddHW(AXI_CLASS_HW1_BASE_ADDR, mac, vlaId, entry, waitCyclesMax)
                  + MDR_KX028_MAC_TableAddHW(AXI_CLASS_HW2_BASE_ADDR, mac, vlaId, entry, waitCyclesMax);
  
  return errCnt == 0;
}


void MDR_KX028_MAC_TableDel(uint8_t *mac, uint16_t vlanId, uint32_t waitCyclesMax)
{
    uint32_t  status, i, classBase;

    classBase = AXI_CLASS_HW1_BASE_ADDR;
    for (i = 0; i < 2; i++)
    {
      // Exec Command
      AXI_WriteMAC_Regs(classBase, mac, vlanId);
      AXI_ExecCommand(classBase, AXI_HASH_CMD_ID_DEL | AXI_HASH_CMD_VALID_MAC1_Msk | AXI_HASH_CMD_VALID_MAC2_Msk);
      AXI_WaitCommandCompleted(classBase, AXI_HASH_STAT_CMD_DONE, &status, waitCyclesMax);
      AXI_ClearStatus(classBase);
            
      //  The same for CLASS_HW2
      classBase = AXI_CLASS_HW2_BASE_ADDR;
    }
}


bool MDR_KX028_MAC_TableUpdateHW(uint32_t classBaseAddr, uint8_t *mac, uint16_t vlanId, MDR_KX028_MAC_Entry_t entry, uint32_t waitCyclesMax)
{
    uint32_t  status;

    // Exec Command
    AXI_WriteMAC_Regs(classBaseAddr, mac, vlanId);
    AXI_WriteEntry(classBaseAddr, entry.value);
    AXI_ExecCommand(classBaseAddr, AXI_HASH_CMD_ID_UPDATE | AXI_HASH_CMD_VALID_MAC1_Msk | AXI_HASH_CMD_VALID_MAC2_Msk);
    bool cmdOk = AXI_WaitCommandCompleted(classBaseAddr, AXI_HASH_STAT_CMD_DONE, &status, waitCyclesMax);
    AXI_ClearStatus(classBaseAddr);

    return  cmdOk && ((status & AXI_HASH_STAT_ENTR_ADD) != 0);
}

bool MDR_KX028_MAC_TableUpdate(uint8_t *mac, uint16_t vlanId, MDR_KX028_MAC_Entry_t entry, uint32_t waitCyclesMax)
{
  uint32_t errCnt = MDR_KX028_MAC_TableUpdateHW(AXI_CLASS_HW1_BASE_ADDR, mac, vlanId, entry, waitCyclesMax)
                  + MDR_KX028_MAC_TableUpdateHW(AXI_CLASS_HW2_BASE_ADDR, mac, vlanId, entry, waitCyclesMax);
  return errCnt == 0;
}

#define REG4_COLL_PTR_ADDR_START   ((CFG_MAC_TABLE_START_ADDR + CFG_MAC_TABLE_COLL_HEAD_PTR) << KX028_ItemMAC_REG4_CollizPtr_Pos)
#define REG4_COLL_PTR_ADDR_INC     (0x1UL << KX028_ItemMAC_REG4_CollizPtr_Pos)

#define REG4_COLL_PTR_MAC_PTR       REG4_COLL_PTR_MSK 

void MDR_KX028_MAC_TableInit(uint32_t waitCyclesMax)
{
    uint32_t status, classNum, i, classBase, REG4_collisionPtr;

    /* 2-field Mac table format: Table Depth - 8192(hash 4096 + collison 4096)
    *=====================================================================================*
    * valid bits |  col_ptr  |   portNO  | field_valids | action entry |  vlanid |	MAC   *
    *=====================================================================================*
    *    4-bit   |  16-bit   |   4-bit   | 	  8-bit     |    31-bit    |  13-bit | 48-bit *
    *  123 - 120 | 119 - 104 | 103 - 100 | 	 99 - 92	  | 	91 - 61	   | 60 - 48 | 47 - 0 *
    *=====================================================================================*/
    /* CLASS_DACAMHASH_HOST_MAC_ADDR1_REG has MAC entry bits:	31 - 0	*/
    /* CLASS_DACAMHASH_HOST_MAC_ADDR2_REG has MAC entry bits:	63 - 32	*/
    /* CLASS_DACAMHASH_HOST_MAC_ADDR3_REG has MAC entry bits:	95 - 64	*/
    /* CLASS_DACAMHASH_HOST_MAC_ADDR4_REG has MAC entry bits:	127 - 96*/

    classBase = AXI_CLASS_HW1_BASE_ADDR;
    for( classNum = 1; classNum <= 2; classNum++ )
    {
        // Clear Status and Init
        AXI_ClearStatus(classBase);
        AXI_ExecCommand( classBase, AXI_HASH_CMD_ID_INIT);
        bool cmdOk = AXI_WaitCommandCompleted(classBase, AXI_HASH_STAT_INIT_DONE | AXI_HASH_STAT_CMD_DONE, &status, waitCyclesMax);
        AXI_ClearStatus(classBase);

        if (!cmdOk)
          MDR_KX028_Log(MDR_KX028_Log_MAC_Table_InitFault, classNum);

        // initialize mac addresses
        MDR_KX028_WriteAXI( ( classBase + AXI_CLASS_DAMACHASH_HOST_MAC_ADDR1_REG ), 0x0);
        MDR_KX028_WriteAXI( ( classBase + AXI_CLASS_DAMACHASH_HOST_MAC_ADDR2_REG ), 0x0);
        MDR_KX028_WriteAXI( ( classBase + AXI_CLASS_DAMACHASH_HOST_MAC_ADDR3_REG ), 0x0);
        MDR_KX028_WriteAXI( ( classBase + AXI_CLASS_DAMACHASH_HOST_MAC_ADDR4_REG ), 0x0);
        MDR_KX028_WriteAXI( ( classBase + AXI_CLASS_DAMACHASH_HOST_MAC_ADDR5_REG ), 0x0);
        MDR_KX028_WriteAXI( ( classBase + AXI_CLASS_DAMACHASH_HOST_ENTRY_REG ), 0x0);

        //  Update col_ptr in AXI_CLASS_DAMACHASH_HOST_MAC_ADDR4_REG and Write
        REG4_collisionPtr = REG4_COLL_PTR_ADDR_START;
        for (i = 0; i < CFG_MAC_TABLE_COLL_ITEMS_COUNT; i++)
        {
            if (i == (CFG_MAC_TABLE_COLL_ITEMS_COUNT - 1))
                REG4_collisionPtr = CFG_MAC_TABLE_START_ADDR << KX028_ItemMAC_REG4_CollizPtr_Pos;    //0x40000 << 8;
            else
                REG4_collisionPtr += REG4_COLL_PTR_ADDR_INC;                                         //( 0x41001 + i ) << 8;

            MDR_KX028_WriteAXI( classBase + AXI_CLASS_DAMACHASH_HOST_MAC_ADDR4_REG, REG4_collisionPtr);
            AXI_ExecCommand(classBase, ( ( CFG_MAC_TABLE_COLL_ITEMS_COUNT + i ) << AXI_HASH_CMD_ADDR_OFFS ) | AXI_HASH_CMD_ID_MEM_WRITE );
            cmdOk = AXI_WaitCommandCompleted(classBase, AXI_HASH_STAT_CMD_DONE, &status, waitCyclesMax);

            if (!cmdOk)
              MDR_KX028_Log(MDR_KX028_Log_MAC_Table_SpaceFault, classNum);
        }

        MDR_KX028_WriteAXI( ( classBase + AXI_CLASS_DAMACHASH_FREELIST_HEAD_PTR ), CFG_MAC_TABLE_COLL_HEAD_PTR );
        MDR_KX028_WriteAXI( ( classBase + AXI_CLASS_DAMACHASH_FREELIST_TAIL_PTR ), CFG_MAC_TABLE_COLL_TAIL_PTR );
        MDR_KX028_WriteAXI( ( classBase + AXI_CLASS_DAMACHASH_FREELIST_ENTRIES ),  CFG_MAC_TABLE_COLL_ITEMS_COUNT );

        MDR_KX028_WriteAXI( ( classBase + AXI_CLASS_DAMACHASH_HOST_STATUS_REG ), AXI_HASH_STAT_REG_CLR );
        MDR_KX028_WriteAXI( ( classBase + AXI_CLASS_DAMACHASH_HOST_MAC_ADDR4_REG ), 0x00 );
        
        //  Repeat the same for CLASS_HW2
        classBase = AXI_CLASS_HW2_BASE_ADDR;
    }
}

// Read one entry data 
bool MDR_KX028_MAC_TableRead( MDR_KX028_MAC_TableItem_t *tableItem, uint16_t hashAddr, uint32_t waitCyclesMax )
{
    uint32_t status, classBase = AXI_CLASS_HW1_BASE_ADDR;

    AXI_ExecCommand(classBase, ( (hashAddr << AXI_HASH_CMD_ADDR_Pos) | AXI_HASH_CMD_ID_MEM_READ ) );
    bool cmdOk = AXI_WaitCommandCompleted(classBase, AXI_HASH_STAT_CMD_DONE, &status, waitCyclesMax);

    if( cmdOk ){
        tableItem->regMAC1 = MDR_KX028_ReadAXI(classBase + AXI_CLASS_DAMACHASH_HOST_MAC_ADDR1_REG);
        tableItem->regMAC2 = MDR_KX028_ReadAXI(classBase + AXI_CLASS_DAMACHASH_HOST_MAC_ADDR2_REG);
        tableItem->regMAC3 = MDR_KX028_ReadAXI(classBase + AXI_CLASS_DAMACHASH_HOST_MAC_ADDR3_REG);
        tableItem->regMAC4 = MDR_KX028_ReadAXI(classBase + AXI_CLASS_DAMACHASH_HOST_MAC_ADDR4_REG);
    }
//    else{
//        tableItem->regMAC1 = 0;
//        tableItem->regMAC2 = 0;
//        tableItem->regMAC3 = 0;
//        tableItem->regMAC4 = 0;
//    }
    
    return cmdOk;
}

/* Write one entry data */
bool MDR_KX028_MAC_TableWrite( MDR_KX028_MAC_TableItem_t *tableItem, uint16_t hashAddr, uint32_t waitCyclesMax )
{
    uint32_t classNum, status, classBase;
    bool result = true;

    classBase = AXI_CLASS_HW1_BASE_ADDR;
    for( classNum = 1; classNum <= 2; classNum++ )
    {
        MDR_KX028_WriteAXI( ( classBase + AXI_CLASS_DAMACHASH_HOST_MAC_ADDR1_REG ), tableItem->regMAC1 );
        MDR_KX028_WriteAXI( ( classBase + AXI_CLASS_DAMACHASH_HOST_MAC_ADDR2_REG ), tableItem->regMAC2 );
        MDR_KX028_WriteAXI( ( classBase + AXI_CLASS_DAMACHASH_HOST_MAC_ADDR3_REG ), tableItem->regMAC3 );
        MDR_KX028_WriteAXI( ( classBase + AXI_CLASS_DAMACHASH_HOST_MAC_ADDR4_REG ), tableItem->regMAC4 );
        AXI_ExecCommand( classBase, ( (hashAddr << AXI_HASH_CMD_ADDR_Pos) | AXI_HASH_CMD_ID_MEM_WRITE ) );
        
        result &= AXI_WaitCommandCompleted(classBase, AXI_HASH_STAT_CMD_DONE, &status, waitCyclesMax);
        
        //  Repeat the same for CLASS_HW2
        classBase = AXI_CLASS_HW2_BASE_ADDR;
    }
    
    return result;
}

// Read function for procFS 
static const unsigned char act[8][20] = {"ACT_FORWARD", "ACT_FLOOD", "ACT_PUNT", "ACT_DISCARD", "ACT_OVERRIDE", "ACT_FWD_MASK", "ACT_COS_DISCARD", "UNKNOWN"};

int32_t MDR_KX028_MAC_TableSprintf(char *buff, uint32_t waitCyclesMax)
{
    uint16_t entry = 0, record = 0;
    uint32_t tmp, dataLen, counter;
    MDR_KX028_MAC_TableItem_t tableItem;
    bool resOK;

    for (entry = 0; entry < MDR_KX028_MAC_TABLE_LEN; entry++)  
    {
//        taskENTER_CRITICAL();
        resOK = MDR_KX028_MAC_TableRead(&tableItem, entry, waitCyclesMax);
//        taskEXIT_CRITICAL();
          
        if( resOK && (tableItem.regMAC4 & KX028_ItemMAC_REG4_IsActive_Msk) )
        {
            record++;
            dataLen = sprintf( buff, "Record %d:\r\n", record );

            dataLen += sprintf( &buff[dataLen], "VLAN ID:   %d\r\nMAC:       ", ( tableItem.regMAC2 >> 16 ) & 0xFFF );
            dataLen += sprintf( &buff[dataLen], "%02x:",  ( tableItem.regMAC1 >> 24 ) & 0xFF );
            dataLen += sprintf( &buff[dataLen], "%02x:",  ( tableItem.regMAC1 >> 16 ) & 0xFF );
            dataLen += sprintf( &buff[dataLen], "%02x:",  ( tableItem.regMAC1 >> 8 ) & 0xFF );
            dataLen += sprintf( &buff[dataLen], "%02x:",    tableItem.regMAC1 & 0xFF );
            dataLen += sprintf( &buff[dataLen], "%02x:",  ( tableItem.regMAC2 >> 8 ) & 0xFF );
            dataLen += sprintf( &buff[dataLen], "%02x\r\n", tableItem.regMAC2 & 0xFF );

            if( tableItem.regMAC3 & KX028_ItemMAC_REG3_IsFresh_Msk )
                dataLen += sprintf( &buff[dataLen], "Fresh bit: Set\r\n" );
            else
                dataLen += sprintf( &buff[dataLen], "Fresh bit: Reset\r\n" );

            if( tableItem.regMAC3 & KX028_ItemMAC_REG3_IsStatic_Msk )
                dataLen += sprintf( &buff[dataLen], "Type:      Static\r\n" );
            else
                dataLen += sprintf( &buff[dataLen], "Type:      Dynamic\r\n" );

            dataLen += sprintf( &buff[dataLen], "Action:    %s\r\n", act[(tableItem.regMAC3 >> 20) & 0x07] );

            tmp = ((tableItem.regMAC3 << 3 ) | (tableItem.regMAC2 >> 29)) & 0x1FFFF;

//            counter = 1;
//            while( tmp != 1 )
//            {
//                tmp = tmp >> 1;
//                counter++;
//            }
            //counter =__clz(__RBIT(tmp));
            counter = BIT_SEL_TO_IND(tmp);
            
            dataLen += sprintf( &buff[dataLen], "Port:      %d\r\n\r\n", counter );
            return dataLen;
        }
    }

    return 0;
}
/*********************** End of File **********************/

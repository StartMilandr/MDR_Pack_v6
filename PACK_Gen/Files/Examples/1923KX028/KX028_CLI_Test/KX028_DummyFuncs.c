#include "KX028_DummyFuncs.h"

#define TST_TBL_MAC_LEN   4
MDR_KX028_MAC_TableItem_t tstTblMac[TST_TBL_MAC_LEN];

#define TST_TBL_VLAN_LEN  2
MDR_KX028_VLAN_TableItem tstTblVLAN[TST_TBL_VLAN_LEN];

#define TST_REGS_LEN  10
uint32_t tstTblREGS[TST_REGS_LEN];


MDR_KX028_StatsClassHW_t statsClassHW[ KX028_EMAC_NUMS ];
MDR_KX028_StatsEMAC_t    statsEMAC[ KX028_EMAC_NUMS ];

static void IncStataEMACS(void);
static void IncStatClassEMACs(void);



//  ----------------    Handlers MAC  ----------------
//  Обновить значение "entry" для item c заданным [mac, vlanId]
static void KeyEntryToMacItem(MDR_KX028_MAC_TableItem_t *tblItem, MDR_KX028_KeyEntryMAC_t *keyEntry)
{
  tblItem->regMAC1 = keyEntry->key.regs.valReg1;
  tblItem->regMAC2_b.MAC_Hi16 = keyEntry->key.fields.MAC[4] | (keyEntry->key.fields.MAC[5] << 8);
  tblItem->regMAC2_b.VLANID = keyEntry->key.fields.VLAN_ID;
  tblItem->regMAC2_b.PortList_lo = keyEntry->entry.bits.forwPortList & 0x7;
  
  tblItem->regMAC3_b.PortList_hi = keyEntry->entry.bits.forwPortList >> 3;
  tblItem->regMAC3_b.IsFresh = keyEntry->entry.bits.isFresh;
  tblItem->regMAC3_b.IsStatic = keyEntry->entry.bits.isStatic;
  tblItem->regMAC3_b.Actions = keyEntry->entry.bits.forwActions;
  tblItem->regMAC3_b.TC = keyEntry->entry.bits.TC;
  
  tblItem->regMAC4_b.IsActive = 1;
  tblItem->regMAC4_b.IsValidCollizPtr = 1;
}

bool MDR_KX028_MAC_TableUpdateByKey(MDR_KX028_KeyEntryMAC_t *keyEntry, uint32_t waitCyclesMax)
{
  uint16_t i;
  for (i = 0; i < TST_TBL_MAC_LEN; i++)
    if (tstTblMac[i].regMAC1 == keyEntry->key.regs.valReg1)  // Упрощенное сравнение
      if (tstTblMac[i].regMAC4_b.IsActive)
      {
        KeyEntryToMacItem(&tstTblMac[i], keyEntry);
        return true;
      }
  
  return false;
}

//  Добавить item c заданным [mac, vlanId] и "entry"
bool MDR_KX028_MAC_TableAddByKey(MDR_KX028_KeyEntryMAC_t *keyEntry, uint32_t waitCyclesMax)
{
  uint16_t i;
  for (i = 0; i < TST_TBL_MAC_LEN; i++)
    if (tstTblMac[i].regMAC4_b.IsActive == 0)
    {
      KeyEntryToMacItem(&tstTblMac[i], keyEntry);
      return true;
    }
    
  return false;  
}

//  Удалить item c заданным [mac, vlanId]
void MDR_KX028_MAC_TableDelByKey(MDR_KX028_KeyMAC_t *key, uint32_t waitCyclesMax)
{
  uint16_t i;
  for (i = 0; i < TST_TBL_MAC_LEN; i++)
    if (tstTblMac[i].regMAC1 == key->regs.valReg1)  // Упрощенное сравнение
      if (tstTblMac[i].regMAC4_b.IsActive)
      {
        tstTblMac[i].regMAC4_b.IsActive = 0;
        break;
      }
}

bool MDR_KX028_MAC_TableRead ( MDR_KX028_MAC_TableItem_t *tableItem, uint16_t hashAddr, uint32_t waitCyclesMax )
{
  IncStataEMACS();  
  
  if (hashAddr < TST_TBL_MAC_LEN)
  {
    *tableItem = tstTblMac[hashAddr];
    return true;
  }
  else
    return false;
}

bool MDR_KX028_MAC_TableWrite( MDR_KX028_MAC_TableItem_t *tableItem, uint16_t hashAddr, uint32_t waitCyclesMax )
{
    if (hashAddr < TST_TBL_MAC_LEN)
  {
    tstTblMac[hashAddr] = *tableItem;
    return true;
  }
  else
    return false;
}

void MDR_KX028_MAC_TableFlush(uint32_t optionMask, uint32_t waitCyclesMax)
{
  uint16_t i;
  for (i = 0; i < TST_TBL_MAC_LEN; i++)
    tstTblMac[i].regMAC4_b.IsActive = 0;
}


//  ----------------    Handlers VLAN  ----------------
static void KeyEntryToVlanItem(MDR_KX028_VLAN_TableItem *tblItem, uint16_t vlanid, MDR_KX028_VLAN_Entry_t *keyEntry)
{
  tblItem->regMAC1_b.VLANID = vlanid;
  tblItem->regMAC1_b.forwPorts_lo = keyEntry->bits.forwPortList; 
  tblItem->regMAC2_b.untagPorts = keyEntry->bits.untagList;
  tblItem->regMAC2_b.MCastHit = keyEntry->bits.mcastHitActions;
  tblItem->regMAC2_b.MCastMiss_lo = keyEntry->bits.mcastMissActions;
  tblItem->regMAC2_b.UCastHit = keyEntry->bits.ucastHitActions;
  tblItem->regMAC2_b.UCastMiss = keyEntry->bits.ucastMisstActions;
  
  tblItem->regMAC3_b.MSTP = keyEntry->bits.mstp;
  tblItem->regMAC4_b.IsActive = 1;
}

bool MDR_KX028_VLAN_TableUpdate(uint16_t vlanid, MDR_KX028_VLAN_Entry_t brentry, uint32_t waitCyclesMax)
{
  uint16_t i;
  for (i = 0; i < TST_TBL_VLAN_LEN; i++)
    if (tstTblVLAN[i].regMAC1_b.VLANID == vlanid)
      if (tstTblVLAN[i].regMAC4_b.IsActive)
      {
        KeyEntryToVlanItem(&tstTblVLAN[i], vlanid, &brentry);
        return true;
      }
  
  return false;  
}

bool MDR_KX028_VLAN_TableAdd(uint16_t vlanid, MDR_KX028_VLAN_Entry_t brentry, uint32_t waitCyclesMax)
{
  uint16_t i;
  for (i = 0; i < TST_TBL_VLAN_LEN; i++)
    if (tstTblVLAN[i].regMAC4_b.IsActive == 0)
    {
      KeyEntryToVlanItem(&tstTblVLAN[i], vlanid, &brentry);
      return true;
    }
    
  return false; 
}

bool MDR_KX028_VLAN_TableDel(uint16_t vlanid, uint32_t waitCyclesMax)
{
  uint16_t i;
  for (i = 0; i < TST_TBL_VLAN_LEN; i++)
    if (tstTblVLAN[i].regMAC1_b.VLANID == vlanid)
      if (tstTblVLAN[i].regMAC4_b.IsActive == 0)
      {
        tstTblVLAN[i].regMAC4_b.IsActive = 0;
        return true;
      }
      
  return false;    
}



bool MDR_KX028_VLAN_TableRead( MDR_KX028_VLAN_TableItem *tableItem, uint16_t hashAddr, uint32_t waitCyclesMax )
{
  IncStatClassEMACs();
  
  if (hashAddr < TST_TBL_VLAN_LEN)
  {
    *tableItem = tstTblVLAN[hashAddr];
    return true;
  }
  else
    return false;
}

void MDR_KX028_VLAN_TableFlush(uint32_t optionMask, uint32_t waitCyclesMax)
{
  uint16_t i;
  for (i = 0; i < TST_TBL_VLAN_LEN; i++)
    tstTblVLAN[i].regMAC4_b.IsActive = 0;  
}



//  ----------------    Handlers AXI BUS  ----------------
uint32_t MDR_KX028_ReadAXI_def(uint32_t addr)
{
  if (addr <  TST_REGS_LEN)
    return tstTblREGS[addr];
  else
    return 0xBEADBEAF;
}

void     MDR_KX028_WriteAXI_def(uint32_t addr, uint32_t data)
{
  if (addr <  TST_REGS_LEN)
    tstTblREGS[addr] = data;
}


//  ----------------    Handlers Statistics  ----------------

static void IncStatEMAC(uint8_t emac, uint8_t step)
{ 
  statsEMAC[emac].tx_ok                += step;
  statsEMAC[emac].tx_broadcast         += step;
  statsEMAC[emac].tx_multicast         += step;
  statsEMAC[emac].tx_pause             += step;
  statsEMAC[emac].tx_64                += step;
  statsEMAC[emac].tx_65_127            += step;
  statsEMAC[emac].tx_128_255           += step;
  statsEMAC[emac].tx_256_511           += step;
  statsEMAC[emac].tx_512_1023          += step;
  statsEMAC[emac].tx_1024_1518         += step;
  statsEMAC[emac].tx_more_1518         += step;
  statsEMAC[emac].tx_underruns         += step;
  statsEMAC[emac].tx_single_collision  += step;
  statsEMAC[emac].tx_2_15_collision    += step;
  statsEMAC[emac].tx_more_15_collision += step;
  statsEMAC[emac].tx_late_collision    += step;
  statsEMAC[emac].tx_deferred      += step;
  statsEMAC[emac].rx_ok            += step;
  statsEMAC[emac].rx_broadcast     += step;
  statsEMAC[emac].rx_multicast     += step;
  statsEMAC[emac].rx_pause         += step;
  statsEMAC[emac].rx_64            += step;
  statsEMAC[emac].rx_65_127        += step;
  statsEMAC[emac].rx_128_255       += step;
  statsEMAC[emac].rx_256_511       += step;
  statsEMAC[emac].rx_512_1023      += step;
  statsEMAC[emac].rx_1024_1518     += step;
  statsEMAC[emac].rx_more_1518     += step;
  statsEMAC[emac].rx_less_64       += step;
  statsEMAC[emac].rx_excessive_len += step;
  statsEMAC[emac].rx_jabbers       += step;
  statsEMAC[emac].rx_fcs_err       += step;
  statsEMAC[emac].rx_len_err       += step;
  statsEMAC[emac].rx_symbol_err    += step;
  statsEMAC[emac].rx_aligment_err  += step;
  statsEMAC[emac].rx_recource_err  += step;
  statsEMAC[emac].rx_overruns      += step;
  statsEMAC[emac].rx_ip_crc_err    += step;
  statsEMAC[emac].rx_tcp_crc_err   += step;
  statsEMAC[emac].rx_udp_crc_err   += step;
  statsEMAC[emac].rx_dropped       += step;
  statsEMAC[emac].tx_bytes         += step;
  statsEMAC[emac].rx_bytes         += step;
}

static void IncStataEMACS(void)
{
  IncStatEMAC(0, 10);
  IncStatEMAC(1, 20);
  IncStatEMAC(2, 30);
  IncStatEMAC(3, 40);
}

static void IncStatClassEMAC(uint8_t emac, uint8_t step)
{
  statsClassHW[emac].class_rx += step;
  statsClassHW[emac].class_l3_fail += step;
  statsClassHW[emac].class_ipv4 += step;
  statsClassHW[emac].class_ipv6 += step;
  statsClassHW[emac].class_crc_err += step;
  statsClassHW[emac].class_ttl_err += step;
  statsClassHW[emac].class_icmp += step;
  statsClassHW[emac].class_igmp += step;
  statsClassHW[emac].class_tcp  += step;
  statsClassHW[emac].class_udp  += step;
}

static void IncStatClassEMACs(void)
{
  IncStatClassEMAC(0, 10);
  IncStatClassEMAC(1, 20);
  IncStatClassEMAC(2, 30);
  IncStatClassEMAC(3, 40);
}

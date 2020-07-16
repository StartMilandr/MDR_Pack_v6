#ifndef KX028_DummyFuncs_H
#define KX028_DummyFuncs_H

#include <MDR_1923KX028_M2_TableMAC.h>
#include <MDR_1923KX028_M2_TableVLAN.h>
#include <MDR_1923KX028_M2_Stats.h>
#include <MDR_1923KX028_Config.h>

////  Обновить значение "entry" для item c заданным [mac, vlanId]
//bool MDR_KX028_MAC_TableUpdateByKey(MDR_KX028_KeyEntryMAC_t *keyEntry, uint32_t waitCyclesMax);
////  Добавить item c заданным [mac, vlanId] и "entry"
//bool MDR_KX028_MAC_TableAddByKey(MDR_KX028_KeyEntryMAC_t *keyEntry, uint32_t waitCyclesMax);
////  Удалить item c заданным [mac, vlanId]
//void MDR_KX028_MAC_TableDelByKey(MDR_KX028_KeyMAC_t *key, uint32_t waitCyclesMax);

//bool MDR_KX028_MAC_TableRead ( MDR_KX028_MAC_TableItem_t *tableItem, uint16_t hashAddr, uint32_t waitCyclesMax );
//bool MDR_KX028_MAC_TableWrite( MDR_KX028_MAC_TableItem_t *tableItem, uint16_t hashAddr, uint32_t waitCyclesMax );
//void MDR_KX028_MAC_TableFlush(uint32_t optionMask, uint32_t waitCyclesMax);


//bool MDR_KX028_VLAN_TableAdd(uint16_t vlanid, MDR_KX028_VLAN_Entry_t brentry, uint32_t waitCyclesMax);
//bool MDR_KX028_VLAN_TableDel(uint16_t vlanid, uint32_t waitCyclesMax);
//bool MDR_KX028_VLAN_TableUpdate(uint16_t vlanid, MDR_KX028_VLAN_Entry_t brentry, uint32_t waitCyclesMax);

//bool MDR_KX028_VLAN_TableRead( MDR_KX028_VLAN_TableItem *tableItem, uint16_t hashAddr, uint32_t waitCyclesMax );
//void MDR_KX028_VLAN_TableFlush(uint32_t optionMask, uint32_t waitCyclesMax);

extern MDR_KX028_StatsClassHW_t statsClassHW[ KX028_EMAC_NUMS ];
//extern MDR_KX028_StatsEMAC_t    statsEMAC[ KX028_EMAC_NUMS ];


#endif  // KX028_DummyFuncs_H

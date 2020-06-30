#ifndef  MDR_1923KX028_M2_TABLE_VLAN_H
#define  MDR_1923KX028_M2_TABLE_VLAN_H

#include <MDR_1923KX028.h>
#include <MDR_1923KX028_AXI_defs.h>

// waitCyclesMax - таймаут ожидания исполнения команды, в количествах считывания регистра статуса.

// Инициализация таблицы
void MDR_KX028_VLAN_TableInit(uint32_t waitCyclesMax);

// VLAN (BD) Hash table action entry map:
typedef __PACKED_STRUCT {
  uint64_t forwPortList       : 20;    // [19:00]         - forward port list
  uint64_t untagList          : 20;    // [39:20]         - untag list
  uint64_t ucastHitActions    : 3;     // [42:40]         - ucast_hit_action
  uint64_t mcastHitActions    : 3;     // [45:43]         - mcast_hit_action
  uint64_t ucastMisstActions  : 3;     // [48:46]         - ucast_miss_action
  uint64_t mcastMissActions   : 3;     // [51:49]         - mcast_miss_action
  uint64_t mstp               : 3;     // [54:52]         - mstp  
  uint64_t reserved           : 9;
} MDR_KX028_VLAN_Entry_Bits;


#define MDR_KX028_VLAN_ENTRY_FWD_PORT_LIST_POS         0
#define MDR_KX028_VLAN_ENTRY_UNTAG_LIST_POS            20
#define MDR_KX028_VLAN_ENTRY_UCAST_HIT_ACT_POS         40
#define MDR_KX028_VLAN_ENTRY_MCAST_HIT_ACT_POS         43
#define MDR_KX028_VLAN_ENTRY_UCAST_MISS_ACT_POS        46
#define MDR_KX028_VLAN_ENTRY_MCAST_MISS_ACT_POS        49
#define MDR_KX028_VLAN_ENTRY_MSTP_ACT_POS              52

//#define MDR_KX028_FWD_PORT_LIST_MASK                   0x1FFFF
//#define MDR_KX028_FWD_PORT_LIST_MASK                   0x0FFFF

#define MDR_KX028_VLAN_ENTRY_FWD_PORT_LIST_MASK              0x000000000000FFFF       // 00 - 19
#define MDR_KX028_VLAN_ENTRY_UNTAG_LIST_MASK                 0x000000FFFFF00000       // 20 - 39
#define MDR_KX028_VLAN_ENTRY_UCAST_HIT_ACT_MASK              0x0000070000000000       // 40 - 42
#define MDR_KX028_VLAN_ENTRY_MCAST_HIT_ACT_MASK              0x0000380000000000       // 43 - 45
#define MDR_KX028_VLAN_ENTRY_UCAST_MISS_ACT_MASK             0x0001c00000000000       // 46 - 48
#define MDR_KX028_VLAN_ENTRY_MCAST_MISS_ACT_MASK             0x000E000000000000       // 49 - 51
#define MDR_KX028_VLAN_ENTRY_MSTP_ACT_MASK                   0x0070000000000000       // 52 - 54

#define MDR_KX028_VLAN_ENTRY_FILL(ports, utl, uha, mha, uma, mma, mstp)   \
      ((( uint64_t )(ports) & MDR_KX028_VLAN_ENTRY_FWD_PORT_LIST_MASK) \
    | ((( uint64_t )(utl) << MDR_KX028_VLAN_ENTRY_UNTAG_LIST_POS)     & MDR_KX028_VLAN_ENTRY_UNTAG_LIST_MASK)      \
    | ((( uint64_t )(uha) << MDR_KX028_VLAN_ENTRY_UCAST_HIT_ACT_POS)  & MDR_KX028_VLAN_ENTRY_UCAST_HIT_ACT_MASK)   \
    | ((( uint64_t )(mha) << MDR_KX028_VLAN_ENTRY_MCAST_HIT_ACT_POS)  & MDR_KX028_VLAN_ENTRY_MCAST_HIT_ACT_MASK)   \
    | ((( uint64_t )(uma) << MDR_KX028_VLAN_ENTRY_UCAST_MISS_ACT_POS) & MDR_KX028_VLAN_ENTRY_UCAST_MISS_ACT_MASK)  \
    | ((( uint64_t )(mma) << MDR_KX028_VLAN_ENTRY_MCAST_MISS_ACT_POS) & MDR_KX028_VLAN_ENTRY_MCAST_MISS_ACT_MASK)  \
    | ((( uint64_t )(mstp) << MDR_KX028_VLAN_ENTRY_MSTP_ACT_POS)  & MDR_KX028_VLAN_ENTRY_MSTP_ACT_MASK))   \

#define MDR_KX028_VLAN_ENTRY_FILL_FORW_ALL(ports, untPorts)   \
                         ((( uint64_t )(ports) & MDR_KX028_VLAN_ENTRY_FWD_PORT_LIST_MASK) \
                       | ((( uint64_t )(untPorts) << MDR_KX028_VLAN_ENTRY_UNTAG_LIST_POS) & MDR_KX028_VLAN_ENTRY_UNTAG_LIST_MASK))


typedef __PACKED_STRUCT {
  uint32_t lo32;
  uint32_t hi32;
} MDR_KX028_VLAN_Entry32;

typedef __packed union {
  int64_t                    value;
  MDR_KX028_VLAN_Entry32     value64;
  MDR_KX028_VLAN_Entry_Bits  bits;
} MDR_KX028_VLAN_Entry_t;

//   Returns entry values if found, -1 is NotFound
MDR_KX028_VLAN_Entry_t MDR_KX028_VLAN_TableSearch(uint16_t vlanid, uint32_t waitCyclesMax);

bool MDR_KX028_VLAN_TableAdd(uint16_t vlanid, MDR_KX028_VLAN_Entry_t brentry, uint32_t waitCyclesMax);
bool MDR_KX028_VLAN_TableDel(uint16_t vlanid, uint32_t waitCyclesMax);
bool MDR_KX028_VLAN_TableUpdate(uint16_t vlanid, MDR_KX028_VLAN_Entry_t brentry, uint32_t waitCyclesMax);


// Read function for procFS
typedef struct {
  uint32_t regMAC1;
  uint32_t regMAC2;
  uint32_t regMAC3;
  uint32_t regMAC4;
} MDR_KX028_VLAN_TableItem;

bool MDR_KX028_VLAN_TableRead( MDR_KX028_VLAN_TableItem *tableItem, uint16_t hashAddr, uint32_t waitCyclesMax );

uint32_t MDR_KX028_VLAN_TableSprintf(char *buff, uint32_t waitCyclesMax);

void MDR_KX028_VLAN_TableFlush(uint32_t optionMask, uint32_t waitCyclesMax);



#endif // MDR_1923KX028_M2_TABLE_VLAN_H

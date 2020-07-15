#ifndef  MDR_1923KX028_M2_TABLE_VLAN_H
#define  MDR_1923KX028_M2_TABLE_VLAN_H

#include <MDR_1923KX028.h>
#include <MDR_1923KX028_AXI_defs.h>
#include <MDR_1923KX028_Config.h>

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


// =============    VLAN TABLE ITEM =======================

typedef struct {
  uint32_t VLANID         : 13; //  0..12
  uint32_t forwPorts_lo   : 19; //  13..31
} MDR_KX028_ItemVLAN_REG1_Bits;  

#define KX028_ItemVLAN_REG1_VlanID_Pos        0
#define KX028_ItemVLAN_REG1_VlanID_Msk        0x00001FFFUL
#define KX028_ItemVLAN_REG1_ForwPortsLo_Pos   13
#define KX028_ItemVLAN_REG1_ForwPortsLo_Msk   0xFFFFE000UL

typedef struct {
  uint32_t untagPorts_hi  : 1;  //  0..0  
  uint32_t untagPorts     : 20; //  1..20
  uint32_t UCastHit       : 3;  //  21..23
  uint32_t MCastHit       : 3;  //  24..26
  uint32_t UCastMiss      : 3;  //  27..29
  uint32_t MCastMiss_lo   : 3;  //  30..31
} MDR_KX028_ItemVLAN_REG2_Bits;

#define KX028_ItemVLAN_REG2_ForwPortsHi_Pos   0
#define KX028_ItemVLAN_REG2_ForwPortsHi_Msk   0x00000001UL
#define KX028_ItemVLAN_REG2_UntagPorts_Pos    1
#define KX028_ItemVLAN_REG2_UntagPorts_Msk    0x001FFFFEUL
#define KX028_ItemVLAN_REG2_UCastHit_Pos      21
#define KX028_ItemVLAN_REG2_UCastHit_Msk      0x00E00000UL
#define KX028_ItemVLAN_REG2_MCastHit_Pos      24
#define KX028_ItemVLAN_REG2_MCastHit_Msk      0x0700000UL
#define KX028_ItemVLAN_REG2_UCastMiss_Pos     27
#define KX028_ItemVLAN_REG2_UCastMiss_Msk     0x38000000UL
#define KX028_ItemVLAN_REG2_MCastMissLo_Pos   30
#define KX028_ItemVLAN_REG2_MCastMissLo_Msk   0xC0000000UL


typedef struct {
  uint32_t MCastMiss_hi   : 1;  //  0..0
  uint32_t MSTP           : 3;  //  1..3
  uint32_t IsValidREG1    : 1;  //  4
  uint32_t IsValidREG2    : 1;  //  5
  uint32_t IsValidREG3    : 1;  //  6
  uint32_t IsValidREG4    : 1;  //  7
  uint32_t IsValidREG5    : 1;  //  8
  uint32_t _reserved      : 3;  //  9..11
  uint32_t PortNum        : 4;  //  12..15
  uint32_t CollizPtr      : 16; //  16..31
} MDR_KX028_ItemVLAN_REG3_Bits;

#define KX028_ItemVLAN_REG3_MCastMissHi_Pos   0
#define KX028_ItemVLAN_REG3_MCastMissHi_Msk   0x00000001UL
#define KX028_ItemVLAN_REG3_MSTP_Pos          1
#define KX028_ItemVLAN_REG3_MSTP_Msk          0x0000000EUL
#define KX028_ItemVLAN_REG3_IsValidREG1_Pos   4
#define KX028_ItemVLAN_REG3_IsValidREG1_Msk   0x00000010UL
#define KX028_ItemVLAN_REG3_IsValidREG2_Pos   5
#define KX028_ItemVLAN_REG3_IsValidREG2_Msk   0x00000020UL
#define KX028_ItemVLAN_REG3_IsValidREG3_Pos   6
#define KX028_ItemVLAN_REG3_IsValidREG3_Msk   0x00000040UL
#define KX028_ItemVLAN_REG3_IsValidREG4_Pos   7
#define KX028_ItemVLAN_REG3_IsValidREG4_Msk   0x00000080UL
#define KX028_ItemVLAN_REG3_IsValidREG5_Pos   8
#define KX028_ItemVLAN_REG3_IsValidREG5_Msk   0x00000100UL
#define KX028_ItemVLAN_REG3_PortNum_Pos       12
#define KX028_ItemVLAN_REG3_PortNum_Msk       0x0000F000UL
#define KX028_ItemVLAN_REG3_CollizPtr_Pos     16
#define KX028_ItemVLAN_REG3_CollizPtr_Msk     0xFFFF0000UL

typedef struct {
  uint32_t _reserved        : 2;  // 0..1
  uint32_t IsValidCollizPtr : 1;  // 2
  uint32_t IsActive         : 1;  // 3
} MDR_KX028_ItemVLAN_REG4_Bits;

#define KX028_ItemVLAN_REG4_IsValidCollPtr_Pos   2
#define KX028_ItemVLAN_REG4_IsValidCollPtr_Msk   0x00000004UL
#define KX028_ItemVLAN_REG4_IsActive_Pos         3
#define KX028_ItemVLAN_REG4_IsActive_Msk         0x00000008UL


/* ========================================  Start of section using anonymous unions  ======================================== */
#if defined (__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined (__ICCARM__)
  #pragma language=extended
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wc11-extensions"
  #pragma clang diagnostic ignored "-Wreserved-id-macro"
  #pragma clang diagnostic ignored "-Wgnu-anonymous-struct"
  #pragma clang diagnostic ignored "-Wnested-anon-types"
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning 586
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif
/* ========================================  Start of section using anonymous unions  ======================================== */


// Read function for procFS
typedef struct {
  union {
    uint32_t                      regMAC1;
    MDR_KX028_ItemVLAN_REG1_Bits  regMAC1_b;
  };  
  union {
    uint32_t                      regMAC2;
    MDR_KX028_ItemVLAN_REG2_Bits  regMAC2_b;
  };
  union {
    uint32_t                      regMAC3;
    MDR_KX028_ItemVLAN_REG3_Bits  regMAC3_b;
  };
  union {  
    uint32_t                      regMAC4;
    MDR_KX028_ItemVLAN_REG4_Bits  regMAC4_b;
  };  
  
//  uint32_t regMAC1;
//  uint32_t regMAC2;
//  uint32_t regMAC3;
//  uint32_t regMAC4;
} MDR_KX028_VLAN_TableItem;



/* =========================================  End of section using anonymous unions  ========================================= */
#if defined (__CC_ARM)
  #pragma pop
#elif defined (__ICCARM__)
  /* leave anonymous unions enabled */
#elif (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic pop
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning restore
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#endif
/* =========================================  End of section using anonymous unions  ========================================= */


bool MDR_KX028_VLAN_TableRead( MDR_KX028_VLAN_TableItem *tableItem, uint16_t hashAddr, uint32_t waitCyclesMax );

uint32_t MDR_KX028_VLAN_TableSprintf(char *buff, uint32_t waitCyclesMax);

void MDR_KX028_VLAN_TableFlush(uint32_t optionMask, uint32_t waitCyclesMax);



#endif // MDR_1923KX028_M2_TABLE_VLAN_H

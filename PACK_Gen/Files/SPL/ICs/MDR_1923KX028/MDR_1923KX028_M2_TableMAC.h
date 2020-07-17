#ifndef  _1923KX028_M2_MAC_TABLE_H_
#define  _1923KX028_M2_MAC_TABLE_H_

#include <MDR_1923KX028.h>
#include <MDR_1923KX028_AXI_defs.h>
#include <MDR_1923KX028_Config.h>


// ==========   Инициализация таблицы   =================
void MDR_KX028_MAC_TableInit(uint32_t waitCyclesMax);


//  =========   Функции работы с "entry" для пары [mac, vlanId]   ===========
typedef __PACKED_STRUCT {
  uint32_t forwPortList: 20;    // [19:0] – список коммутируемых портов
  uint32_t TC          : 3;     // [22:20] – TC для MACDA2TC
  uint32_t forwActions : 3;     // [25:23] – поле операции (ACTION FIELD)
  uint32_t cutThrough  : 1;     // [26] – cut through
  uint32_t reserved1   : 2;     // [28:27] – не используется
  uint32_t isFresh     : 1;     // [29] – fresh
  uint32_t isStatic    : 1;     // [30] – static
  uint32_t reserved2   : 1;     // [31]
} MDR_KX028_MAC_Entry_Bits;


#define MDR_KX028_MAC_ENTRY_FWD_PORT_LIST_Pos   0
#define MDR_KX028_MAC_ENTRY_FWD_PORT_LIST_Msk   0xFFFFUL
#define MDR_KX028_MAC_ENTRY_TC_Pos 		          20
#define MDR_KX028_MAC_ENTRY_TC_Msk 		          0x00700000UL
#define MDR_KX028_MAC_ENTRY_FWD_ACT_Pos         23
#define MDR_KX028_MAC_ENTRY_FWD_ACT_Msk         0x03800000UL
#define MDR_KX028_MAC_ENTRY_CUT_THROUGH_Pos     26
#define MDR_KX028_MAC_ENTRY_CUT_THROUGH_Msk     0x04000000UL
#define MDR_KX028_MAC_ENTRY_FRESH_Pos           29
#define MDR_KX028_MAC_ENTRY_FRESH_Msk           0x20000000UL
#define MDR_KX028_MAC_ENTRY_STATIC_Pos          30
#define MDR_KX028_MAC_ENTRY_STATIC_Msk          0x40000000UL

#define MDR_KX028_MAC_ENTRY_FILL(ports, TC, Action, CutThr, Fresh, Static) \
                  _VAL2FLD(MDR_KX028_MAC_ENTRY_FWD_PORT_LIST, ports) \
                | _VAL2FLD(MDR_KX028_MAC_ENTRY_TC,            TC) \
                | _VAL2FLD(MDR_KX028_MAC_ENTRY_FWD_ACT,       Action) \
                | _VAL2FLD(MDR_KX028_MAC_ENTRY_CUT_THROUGH,   CutThr) \
                | _VAL2FLD(MDR_KX028_MAC_ENTRY_FRESH,         Fresh) \
                | _VAL2FLD(MDR_KX028_MAC_ENTRY_STATIC,        Static)

#define MDR_KX028_MAC_ENTRY_FILL_DEF(ports, Action, Static) \
                  _VAL2FLD(MDR_KX028_MAC_ENTRY_FWD_PORT_LIST, ports) \
                | _VAL2FLD(MDR_KX028_MAC_ENTRY_FWD_ACT,       Action) \
                | _VAL2FLD(MDR_KX028_MAC_ENTRY_STATIC,        Static)


typedef __PACKED_UNION {
  int32_t                  value;
  MDR_KX028_MAC_Entry_Bits bits;
} MDR_KX028_MAC_Entry_t;

typedef __PACKED_STRUCT {  
  uint8_t   MAC[6];
  uint16_t  VLAN_ID;
} MDR_KX028_KeyMAC_Fields;

typedef __PACKED_STRUCT {  
  uint32_t  valReg1;
  uint32_t  valReg2;
} MDR_KX028_KeyMAC_Regs;

typedef __PACKED_UNION {
  MDR_KX028_KeyMAC_Regs     regs;
  MDR_KX028_KeyMAC_Fields   fields;
} MDR_KX028_KeyMAC_t;

typedef __PACKED_STRUCT {
  MDR_KX028_KeyMAC_t    key;
  MDR_KX028_MAC_Entry_t entry;
} MDR_KX028_KeyEntryMAC_t;

__STATIC_INLINE void MDR_KX028_MAC_FillKey(uint8_t *mac, uint16_t vlanId, MDR_KX028_KeyMAC_t *key)
{
  key->regs.valReg1 =   mac[0] << 24 | mac[1] << 16 | mac[2] << 8 | mac[3];
  key->regs.valReg2 = ((vlanId << 16) & 0xFFFF0000) | mac[4] << 8 | mac[5];
}

__STATIC_INLINE void MDR_KX028_MAC_FillKeyEntry(uint8_t *mac, uint16_t vlanId, MDR_KX028_MAC_Entry_t entry, MDR_KX028_KeyEntryMAC_t *keyEntry)
{
  MDR_KX028_MAC_FillKey(mac, vlanId, &keyEntry->key);
  keyEntry->entry = entry;
}

//  Считать "entry" для item c заданным [mac, vlanId]
//  if not found returns value = -1
MDR_KX028_MAC_Entry_t MDR_KX028_MAC_TableSearchByKey(MDR_KX028_KeyMAC_t *key, uint32_t waitCyclesMax);

__STATIC_INLINE MDR_KX028_MAC_Entry_t MDR_KX028_MAC_TableSearch(uint8_t *mac, uint16_t vlanId, uint32_t waitCyclesMax)
{
  MDR_KX028_KeyMAC_t key;
  MDR_KX028_MAC_FillKey(mac, vlanId, &key);
  return MDR_KX028_MAC_TableSearchByKey(&key, waitCyclesMax);
}


//  Добавить item c заданным [mac, vlanId] и "entry"
bool MDR_KX028_MAC_TableAddByKey(MDR_KX028_KeyEntryMAC_t *keyEntry, uint32_t waitCyclesMax);

__STATIC_INLINE bool MDR_KX028_MAC_TableAdd(uint8_t *mac, uint16_t vlanId, MDR_KX028_MAC_Entry_t entry, uint32_t waitCyclesMax)
{
  MDR_KX028_KeyEntryMAC_t keyEntry;
  MDR_KX028_MAC_FillKeyEntry(mac, vlanId, entry, &keyEntry);
  return MDR_KX028_MAC_TableAddByKey(&keyEntry, waitCyclesMax);
}

//  Обновить значение "entry" для item c заданным [mac, vlanId]
bool MDR_KX028_MAC_TableUpdateByKey(MDR_KX028_KeyEntryMAC_t *keyEntry, uint32_t waitCyclesMax);

__STATIC_INLINE bool MDR_KX028_MAC_TableUpdate(uint8_t *mac, uint16_t vlanId, MDR_KX028_MAC_Entry_t entry, uint32_t waitCyclesMax)
{
  MDR_KX028_KeyEntryMAC_t keyEntry;
  MDR_KX028_MAC_FillKeyEntry(mac, vlanId, entry, &keyEntry);
  return MDR_KX028_MAC_TableUpdateByKey(&keyEntry, waitCyclesMax);
}


//  Удалить item c заданным [mac, vlanId]
void MDR_KX028_MAC_TableDelByKey(MDR_KX028_KeyMAC_t *key, uint32_t waitCyclesMax);

__STATIC_INLINE void MDR_KX028_MAC_TableDel(uint8_t *mac, uint16_t vlanId, uint32_t waitCyclesMax)
{
  MDR_KX028_KeyMAC_t key;
  MDR_KX028_MAC_FillKey(mac, vlanId, &key);
  return MDR_KX028_MAC_TableDelByKey(&key, waitCyclesMax);
}

// ==========   Чтение запись таблицы МАС =================
typedef struct {
  uint32_t MAC_Lo32;
} MDR_KX028_ItemMAC_REG1_Bits;

typedef struct {
  uint32_t MAC_Hi16     : 16; //   0..15
  uint32_t VLANID       : 13; //  16..28
  uint32_t PortList_lo  :  3; //  29..31
} MDR_KX028_ItemMAC_REG2_Bits;

#define KX028_ItemMAC_REG2_MAC_Hi16_Pos     0
#define KX028_ItemMAC_REG2_MAC_Hi16_Msk     0x0000FFFFUL
#define KX028_ItemMAC_REG2_VlanID_Pos       16
#define KX028_ItemMAC_REG2_VlanID_Msk       0x1FFF0000UL
#define KX028_ItemMAC_REG2_PortListL_Pos    29
#define KX028_ItemMAC_REG2_PortListL_Msk    0xE0000000UL

#define KX028_ItemMAC_REG2_FILL(MACh16, VlanID, PortsLo3) \
                _VAL2FLD(KX028_ItemMAC_REG2_MAC_Hi16,  MACh16) \
              | _VAL2FLD(KX028_ItemMAC_REG2_VlanID,    VlanID) \
              | _VAL2FLD(KX028_ItemMAC_REG2_PortListL, PortsLo3)

typedef struct {
  uint32_t PortList_hi  : 13; //  0..12
  uint32_t _reserved1   : 4;  //  13..16
  uint32_t TC           : 3;  //  17..19
  uint32_t Actions      : 3;  //  20..22
  uint32_t CutThrough   : 1;  //  23
  uint32_t _reserved2   : 2;  //  24..25
  uint32_t IsFresh      : 1;  //  26
  uint32_t IsStatic     : 1;  //  27
  uint32_t IsValidREG1  : 1;  //  28
  uint32_t IsValidREG2  : 1;  //  29
  uint32_t IsValidREG3  : 1;  //  30
  uint32_t IsValidREG4  : 1;  //  31
} MDR_KX028_ItemMAC_REG3_Bits;

#define KX028_ItemMAC_REG3_PortListH_Pos    0
#define KX028_ItemMAC_REG3_PortListH_Msk    0x00001FFFUL
#define KX028_ItemMAC_REG3_TC_Pos           17
#define KX028_ItemMAC_REG3_TC_Msk           0x000E0000UL
#define KX028_ItemMAC_REG3_Actions_Pos      20
#define KX028_ItemMAC_REG3_Actions_Msk      0x00700000UL
#define KX028_ItemMAC_REG3_CutThrough_Pos   23
#define KX028_ItemMAC_REG3_CutThrough_Msk   0x00800000UL
#define KX028_ItemMAC_REG3_IsFresh_Pos      26
#define KX028_ItemMAC_REG3_IsFresh_Msk      0x04000000UL
#define KX028_ItemMAC_REG3_IsStatic_Pos     27
#define KX028_ItemMAC_REG3_IsStatic_Msk     0x08000000UL
#define KX028_ItemMAC_REG3_IsValidREG1_Pos  28
#define KX028_ItemMAC_REG3_IsValidREG1_Msk  0x10000000UL
#define KX028_ItemMAC_REG3_IsValidREG2_Pos  29
#define KX028_ItemMAC_REG3_IsValidREG2_Msk  0x20000000UL
#define KX028_ItemMAC_REG3_IsValidREG3_Pos  30
#define KX028_ItemMAC_REG3_IsValidREG3_Msk  0x40000000UL
#define KX028_ItemMAC_REG3_IsValidREG4_Pos  31
#define KX028_ItemMAC_REG3_IsValidREG4_Msk  0x80000000UL

#define KX028_ItemMAC_REG3_FILL(PortsHi13, TC, Action, CutThrough, IsFresh, IsStatic, IsValR1, IsValR2, IsValR3, IsValR4) \
                _VAL2FLD(KX028_ItemMAC_REG3_PortListH_Msk,    PortsHi13) \
              | _VAL2FLD(KX028_ItemMAC_REG3_TC_Pos,           TC) \
              | _VAL2FLD(KX028_ItemMAC_REG3_Actions_Pos,      Action) \
              | _VAL2FLD(KX028_ItemMAC_REG3_CutThrough_Pos,   CutThrough) \
              | _VAL2FLD(KX028_ItemMAC_REG3_IsFresh_Pos,      IsFresh) \
              | _VAL2FLD(KX028_ItemMAC_REG3_IsStatic_Pos,     IsStatic) \
              | _VAL2FLD(KX028_ItemMAC_REG3_IsValidREG1_Pos,  IsValR1) \
              | _VAL2FLD(KX028_ItemMAC_REG3_IsValidREG2_Pos,  IsValR2) \
              | _VAL2FLD(KX028_ItemMAC_REG3_IsValidREG3_Pos,  IsValR3) \
              | _VAL2FLD(KX028_ItemMAC_REG3_IsValidREG4_Pos,  IsValR4)

#define KX028_ItemMAC_REG3_FILL_DEF(PortsHi13, TC, Action, CutThrough, IsFresh, IsStatic) \
                _VAL2FLD(KX028_ItemMAC_REG3_PortListH_Msk,    PortsHi13) \
              | _VAL2FLD(KX028_ItemMAC_REG3_TC_Pos,           TC) \
              | _VAL2FLD(KX028_ItemMAC_REG3_Actions_Pos,      Action) \
              | _VAL2FLD(KX028_ItemMAC_REG3_CutThrough_Pos,   CutThrough) \
              | _VAL2FLD(KX028_ItemMAC_REG3_IsFresh_Pos,      IsFresh) \
              | _VAL2FLD(KX028_ItemMAC_REG3_IsStatic_Pos,     IsStatic) \
              | KX028_ItemMAC_REG3_IsValidREG1_Msk \
              | KX028_ItemMAC_REG3_IsValidREG2_Msk \
              | KX028_ItemMAC_REG3_IsValidREG3_Msk \
              | KX028_ItemMAC_REG3_IsValidREG4_Msk


typedef struct {
  uint32_t IsValidREG5      : 1;  //  0
  uint32_t _reserved1       : 3;  //  1..3
  uint32_t PortNum          : 4;  //  4..7
  uint32_t CollizPtr        : 16; //  8..23
  uint32_t _reserved2       : 2;  //  24..25
  uint32_t IsValidCollizPtr : 1;  // 26
  uint32_t IsActive         : 1;  // 27
} MDR_KX028_ItemMAC_REG4_Bits;

#define KX028_ItemMAC_REG4_IsValidREG5_Pos      0
#define KX028_ItemMAC_REG4_IsValidREG5_Msk      0x00000001UL
#define KX028_ItemMAC_REG4_PortNum_Pos          4
#define KX028_ItemMAC_REG4_PortNum_Msk          0x000000F0UL
#define KX028_ItemMAC_REG4_CollizPtr_Pos        8
#define KX028_ItemMAC_REG4_CollizPtr_Msk        0x00FFFF00UL
#define KX028_ItemMAC_REG4_IsValidCollPtr_Pos   26
#define KX028_ItemMAC_REG4_IsValidCollPtr_Msk   0x04000000UL
#define KX028_ItemMAC_REG4_IsActive_Pos         27
#define KX028_ItemMAC_REG4_IsActive_Msk         0x08000000UL

#define KX028_ItemMAC_REG4_FILL_DEF(IsValR5, PortNum, CollPtr, IsValCollPtr, IsActive) \
                _VAL2FLD(KX028_ItemMAC_REG4_IsValidREG5,    IsValR5) \
              | _VAL2FLD(KX028_ItemMAC_REG4_PortNum,        PortNum) \
              | _VAL2FLD(KX028_ItemMAC_REG4_CollizPtr,      CollPtr) \
              | _VAL2FLD(KX028_ItemMAC_REG4_IsValidCollPtr, IsValCollPtr) \
              | _VAL2FLD(KX028_ItemMAC_REG4_IsActive,       IsActive)


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


typedef struct {
  uint32_t regMAC1;
  union {
    uint32_t                      regMAC2;
    MDR_KX028_ItemMAC_REG2_Bits   regMAC2_b;
  };
  union {
    uint32_t regMAC3;
    MDR_KX028_ItemMAC_REG3_Bits   regMAC3_b;
  };
  union {  
    uint32_t regMAC4;
    MDR_KX028_ItemMAC_REG4_Bits   regMAC4_b;
  };
} MDR_KX028_MAC_TableItem_t;

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

#define KX028_MAC_ITEM_IS_ACTIVE(item)         (item).regMAC4 & KX028_ItemMAC_REG4_IsActive_Msk
#define KX028_MAC_ITEM_IS_HAS_COLLISION(item)  (item).regMAC4 & KX028_ItemMAC_REG4_IsValidCollPtr_Msk
#define KX028_MAC_ITEM_IS_FRESH(item)          (item).regMAC3 & KX028_ItemMAC_REG3_IsFresh_Msk
#define KX028_MAC_ITEM_IS_STATIC(item)         (item).regMAC3 & KX028_ItemMAC_REG3_IsStatic_Msk

#define KX028_MAC_ITEM_COLLIS_PTR(item)        _FLD2VAL(KX028_ItemMAC_REG4_IsValidCollPtr, (item).regMAC4)

#define KX028_MAC_ITEM_SET_FRESH(item)          (item).regMAC3 |= KX028_ItemMAC_REG3_IsFresh_Msk
#define KX028_MAC_ITEM_SET_STATIC(item)         (item).regMAC3 |= KX028_ItemMAC_REG3_IsStatic_Msk


#define MDR_KX028_MAC_TABLE_LEN     8192

bool MDR_KX028_MAC_TableRead ( MDR_KX028_MAC_TableItem_t *tableItem, uint16_t hashAddr, uint32_t waitCyclesMax );
bool MDR_KX028_MAC_TableWrite( MDR_KX028_MAC_TableItem_t *tableItem, uint16_t hashAddr, uint32_t waitCyclesMax );

int32_t MDR_KX028_MAC_TableSprintf(char *buff, uint32_t waitCyclesMax);

void MDR_KX028_MAC_TableFlush(uint32_t optionMask, uint32_t waitCyclesMax);


#endif // _1923KX028_M2_MAC_TABLE_H_

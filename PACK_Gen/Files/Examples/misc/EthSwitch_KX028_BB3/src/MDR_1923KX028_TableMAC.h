#ifndef  _1923KX028_MAC_TABLE_H_
#define  _1923KX028_MAC_TABLE_H_

#include <MDR_1923KX028.h>
#include <MDR_1923KX028_AXI_defs.h>


// ==========   Инициализация таблицы   =================
void MDR_KX028_MAC_TableInit(uint32_t waitCyclesMax);


//  =========   Функции работы с "entry" для пары [mac, vlanId]   ===========
typedef struct {
  uint32_t forwPortList: 20;    // [19:0] – список коммутируемых портов
  uint32_t TC          : 3;     // [22:20] – TC для MACDA2TC
  uint32_t forwActions : 3;     // [25:23] – поле операции (ACTION FIELD)
  uint32_t cutThrough  : 1;     // [26] – cut through
  uint32_t reserved1   : 2;     // [28:27] – не используется
  uint32_t isFresh     : 1;     // [29] – fresh
  uint32_t isStatic    : 1;     // [30] – static
  uint32_t reserved2   : 1;     // [31]
} MDR_KX028_MAC_Entry_Bits;


#define MDR_KX028_MAC_ENTRY_FWD_PORT_LIST_POS   0
#define MDR_KX028_MAC_ENTRY_FWD_PORT_LIST_MSK   0xFFFFUL
#define MDR_KX028_MAC_ENTRY_TC_POS 		          20
#define MDR_KX028_MAC_ENTRY_TC_MSK 		          0x00700000UL
#define MDR_KX028_MAC_ENTRY_FWD_ACT_POS         23
#define MDR_KX028_MAC_ENTRY_FWD_ACT_MSK         0x03800000UL
#define MDR_KX028_MAC_ENTRY_CUT_THROUGH_POS     26
#define MDR_KX028_MAC_ENTRY_CUT_THROUGH_MSK     0x04000000UL
#define MDR_KX028_MAC_ENTRY_FRESH_POS           29
#define MDR_KX028_MAC_ENTRY_FRESH_MSK           0x20000000UL
#define MDR_KX028_MAC_ENTRY_STATIC_POS          30
#define MDR_KX028_MAC_ENTRY_STATIC_MSK          0x40000000UL


typedef union {
  int32_t                value;
  MDR_KX028_MAC_Entry_Bits bits;
} MDR_KX028_MAC_Entry_t;

//  Считать "entry" для item c заданным [mac, vlanId]
//  if not found returns value = -1
MDR_KX028_MAC_Entry_t MDR_KX028_MAC_TableSearch(uint8_t *mac, uint16_t vlanId, uint32_t waitCyclesMax);

//  Добавить item c заданным [mac, vlanId] и "entry"
bool MDR_KX028_MAC_TableAdd   (uint8_t *mac, uint16_t vlanId, MDR_KX028_MAC_Entry_t entry, uint32_t waitCyclesMax);
//  Обновить значение "entry" для item c заданным [mac, vlanId]
bool MDR_KX028_MAC_TableUpdate(uint8_t *mac, uint16_t vlanId, MDR_KX028_MAC_Entry_t entry, uint32_t waitCyclesMax);
//  Удалить item c заданным [mac, vlanId]
void MDR_KX028_MAC_TableDel   (uint8_t *mac, uint16_t vlanId, uint32_t waitCyclesMax);


// ==========   Чтение запись таблицы МАС =================
#define MDR_KX028_MAC_TABLE_LEN     8192

typedef struct {
  uint32_t regMAC1;
  uint32_t regMAC2;
  uint32_t regMAC3;
  uint32_t regMAC4;
} MDR_KX028_MAC_TableItem_t;

bool MDR_KX028_MAC_TableRead ( MDR_KX028_MAC_TableItem_t *tableItem, uint16_t hashAddr, uint32_t waitCyclesMax );
bool MDR_KX028_MAC_TableWrite( MDR_KX028_MAC_TableItem_t *tableItem, uint16_t hashAddr, uint32_t waitCyclesMax );

int32_t MDR_KX028_MAC_TableSprintf(char *buff, uint32_t waitCyclesMax);

#endif /* _1923KX028_MAC_TABLE_H_ */

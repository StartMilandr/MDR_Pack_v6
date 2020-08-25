#ifndef MDR_1923KX029_M2_TABLES_CTRL_H
#define MDR_1923KX029_M2_TABLES_CTRL_H

#include <MDR_1923KX028_M2_TableMAC.h>
#include <MDR_1923KX028_M2_TableVLAN.h>
#include <MDR_1923KX028_Config.h>

//  Инициализация таблиц
__STATIC_INLINE void MDR_KX028_M2_InitTables(uint32_t waitCyclesMax)
{
  MDR_KX028_MAC_TableInit(waitCyclesMax);
  MDR_KX028_VLAN_TableInit(waitCyclesMax);
}

//  Обработка старения пакетов
//    framesToProcessMax - сколько фреймов обработать за вызов функции
//    fromHashAddr - начиная с этого адреса
//    return - следующий fromHashAddr (для следующего вызова)
//    waitCyclesMax - таймаут в количествах опроса регистра статуса об окончании операции
uint16_t MDR_KX028_M2_ProcessTablesAgeing(uint16_t framesToProcessMax, uint16_t fromHashAddr, uint32_t waitCyclesMax);  
//  Обработка единичного Item
void MDR_KX028_M2_ProcessTableItemAgeing(uint16_t hashAddr, uint32_t waitCyclesMax);

//  Обучение таблиц маршрутизации, 
//    framesToProcessMax - сколько фреймов обработать за вызов функции
//    возвращает количество обработанных фреймов
uint32_t MDR_KX028_M2_ProcessTablesLearning(uint32_t framesToProcessMax, uint32_t waitCyclesMax, uint16_t enabledPortList);



typedef __PACKED_STRUCT {
  uint8_t  ctrl;
  uint8_t  portNum;  
  uint8_t  reserved;
  uint8_t  puntReason;  // ntoh(hi16)
} MDR_KX028_FrameCtrl_Fields;

typedef __PACKED_STRUCT {
  uint32_t   size;
  __PACKED_UNION {
    uint32_t                    ctrl;
    MDR_KX028_FrameCtrl_Fields  ctrl_b;
  };
  uint32_t   destMAC;
  uint32_t   destMAC_srcMAC;
  uint32_t   srcMAC;
  uint32_t   vlanTag;
} MDR_KX028_FrameInfo;

void MDR_KX028_LearnFrame( MDR_KX028_FrameInfo *frmInfo, bool static_entry, uint32_t waitCyclesMax, uint16_t enabledPortList);
void MDR_KX028_FreeFrameBMU( uint32_t start_packet_pointer, int32_t pck_size);

#endif  //MDR_1923KX029_M2_TABLES_CTRL_H

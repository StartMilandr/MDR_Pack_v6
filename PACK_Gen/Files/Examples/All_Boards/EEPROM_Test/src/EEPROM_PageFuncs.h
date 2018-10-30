#ifndef _EEPROM_PAGEFUNCS_H
#define _EEPROM_PAGEFUNCS_H

#include <MDR_EEPROM.h>

void WriteAllPages(MDR_EEPROM_MEM bank);
bool ReadAllPagesAndCheckData(MDR_EEPROM_MEM bank);
bool WriteAllPagesAndCheck(MDR_EEPROM_MEM bank);
bool EraseAllPagesAndCheck(MDR_EEPROM_MEM bank);
bool CheckClearAllPages(MDR_EEPROM_MEM bank);

#ifndef MDR_EEPROM_18MHz
  void WritePage(MDR_EEPROM_PAGE page, MDR_EEPROM_MEM bank);
  bool ReadPageAndCheckData(MDR_EEPROM_PAGE page, MDR_EEPROM_MEM bank);
  bool ErasePageAndCheck(MDR_EEPROM_PAGE page, MDR_EEPROM_MEM bank);
  bool CheckClearPage(MDR_EEPROM_PAGE page, MDR_EEPROM_MEM bank);
#else
  void WritePage(MDR_EEPROM_BLOCK block, MDR_EEPROM_PAGE page, MDR_EEPROM_MEM bank);
  bool ReadPageAndCheckData(MDR_EEPROM_BLOCK block, MDR_EEPROM_PAGE page, MDR_EEPROM_MEM bank);
  bool ErasePageAndCheck(MDR_EEPROM_BLOCK block, MDR_EEPROM_PAGE page, MDR_EEPROM_MEM bank);
  bool CheckClearPage(MDR_EEPROM_BLOCK block, MDR_EEPROM_PAGE page, MDR_EEPROM_MEM bank);
#endif


#endif  //_EEPROM_PAGEFUNCS_H

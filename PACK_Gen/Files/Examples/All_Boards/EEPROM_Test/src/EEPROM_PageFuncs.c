#include "EEPROM_PageFuncs.h"

#ifdef MDR_EEPROM_18MHz
  Вместо этого необходимо подключить модуль EEPROM_PageFuncs_CM0.c !
#endif

//----------  Варианты записываемых данных  -------------
// На 8МГц много времени уходит на рассчет MDR_ToPseudoRand(),
// Запись просто индексов происходит значительно быстрее.
#define USE_PSEUDO_RAND_VALUES  1

#if USE_PSEUDO_RAND_VALUES
  #define GetTestValue  MDR_ToPseudoRand
#else
  uint32_t ReturnInput(uint32_t value) { return value; }

  #define GetTestValue  ReturnInput
#endif

  
//------------  Последняя страница в банках памяти и Main Info  -----------
#define EEPROM_BANK_COUNT 2
static  MDR_EEPROM_PAGE  endPage[EEPROM_BANK_COUNT] = {EEPROM_Page32, EEPROM_Page1};


//==========    Write Data ===============
void WritePage(MDR_EEPROM_PAGE page, MDR_EEPROM_MEM bank)
{
  uint32_t i = 0;
  uint32_t addr = MDR_EEPROM_PageToAddr(page, bank);
  
  //  bank - чтобы данные в Info и Main памяти не совпадали
  for (i = 0; i < MDR_EEPROM_PAGE_SIZE; i += 4)
    MDR_EEPROM_Write(addr + i, GetTestValue(addr + i + (uint32_t)bank), bank);    
}

void WriteAllPages(MDR_EEPROM_MEM bank)
{
  MDR_EEPROM_PAGE page; 
  
  for (page = EEPROM_Page1; page <= endPage[bank]; ++page)
    WritePage(page, bank);
}

//==========    Read and Check ===============
bool ReadPageAndCheckData(MDR_EEPROM_PAGE page, MDR_EEPROM_MEM bank)
{
  uint32_t i = 0;
  uint32_t addr = MDR_EEPROM_PageToAddr(page, bank);
  uint32_t data;
  
  for (i = 0; i < MDR_EEPROM_PAGE_SIZE; i += 4)
  {
    data = GetTestValue(addr + i + (uint32_t)bank);
    if (MDR_EEPROM_Read(addr + i, bank) != data)
      return false;
  }
  
  return true;
}

bool ReadAllPagesAndCheckData(MDR_EEPROM_MEM bank)
{
  MDR_EEPROM_PAGE page;  
   
  for (page = EEPROM_Page1; page <= endPage[bank]; ++page)
    if (!ReadPageAndCheckData(page, bank))
      return false;
  
  return true;
}

//==========    Write, Read and Check ===============
bool WriteAllPagesAndCheck(MDR_EEPROM_MEM bank)
{
  WriteAllPages(bank);
  return ReadAllPagesAndCheckData(bank);
}


//==========    Erase ===============
bool ErasePageAndCheck(MDR_EEPROM_PAGE page, MDR_EEPROM_MEM bank)
{
  MDR_EEPROM_ErasePage(MDR_EEPROM_PageToAddr(page, bank), bank);
  
  return CheckClearPage(page, bank);  
}

bool EraseAllPagesAndCheck(MDR_EEPROM_MEM bank)
{
  MDR_EEPROM_PAGE page;  
   
  for (page = EEPROM_Page1; page <= endPage[bank]; ++page)  
    MDR_EEPROM_ErasePage(MDR_EEPROM_PageToAddr(page, bank), bank);
  
  return CheckClearAllPages(bank);  
}

//==========    Check data clear ===============

bool CheckClearPage(MDR_EEPROM_PAGE page, MDR_EEPROM_MEM bank)
{
  uint32_t i = 0;
  uint32_t addr = MDR_EEPROM_PageToAddr(page, bank);
  
  for (i = 0; i < MDR_EEPROM_PAGE_SIZE; i += 4)
    if (MDR_EEPROM_Read(addr + i, bank) != MDR_EEPROM_CLEAR_VALUE)
      return false;
    
  return true;
}

bool CheckClearAllPages(MDR_EEPROM_MEM bank)
{
  MDR_EEPROM_PAGE page;  
   
  for (page = EEPROM_Page1; page <= endPage[bank]; ++page)
    if (!CheckClearPage(page, bank))
      return false;
  
  return true;  
}

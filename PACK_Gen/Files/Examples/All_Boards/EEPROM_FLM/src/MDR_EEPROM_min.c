#include "MDR_DeviceDefs.h"

static void RAM_Delay(uint32_t delayLoops)
{
  volatile uint32_t i = delayLoops;
  while (--i);
}


static void MDR_EEPROM_Erase(uint32_t address, uint32_t MAS1_Mask, uint32_t delayEraseExit)
{
  uint32_t sector;
 
  //  Разблокировка контроллера EEPROM
  regKEY = EEPROM_KEY_ACCESS_CODE;
  
  // Включение регистрового доступа к памяти
  regCMD = MDR_EEPROM_CMD_BIT_CON | MEM_BANK;

  // Стирание секторов по очереди
  // b00 - sector A, b01 - sector B,  b10 - sector C,  b11 - sector D
  for (sector = 0; sector < (4 << 2); sector += 4)
  {
    regADDR = address + sector;
    regDI = 0;
    
    // Вход в режим стирания, задержка 5мкс. MAS1 - стирание всех страниц в секторе.
    regCMD = MAS1_Mask | MDR_EEPROM_CMD_BIT_CON | MEM_BANK | MDR_EEPROM_CMD_BIT_XE | MDR_EEPROM_CMD_BIT_ERASE;
    RAM_Delay(delay_5us);
    
    // Запуск стирания, время стирания сектора 40 мс
    regCMD = MAS1_Mask | MDR_EEPROM_CMD_BIT_CON | MEM_BANK | MDR_EEPROM_CMD_BIT_XE | MDR_EEPROM_CMD_BIT_ERASE | MDR_EEPROM_CMD_BIT_NVSTR;
    RAM_Delay(delay_40ms);               
    
    // Выход из режима стирания, задержка для
    // страницы    5мкс
    // весь сектор 100мкс
    regCMD = MAS1_Mask | MDR_EEPROM_CMD_BIT_CON | MEM_BANK | MDR_EEPROM_CMD_BIT_XE | MDR_EEPROM_CMD_BIT_NVSTR;
    RAM_Delay(delayEraseExit);              
    
    // Сброс флагов перед следующим циклом стирания сектора, задержка 1мкс
    regCMD = MDR_EEPROM_CMD_BIT_CON | MEM_BANK;
    RAM_Delay(delay_1us);
  }
  
  // Выход из регистрового доступа к памяти в обычный режим
  regCMD = 0;
  regKEY = 0;
}

void MDR_EEPROM_ErasePage(uint32_t address)
{
  MDR_EEPROM_Erase(address, 0, delay_5us);
}

void MDR_EEPROM_EraseFull(void)
{
  MDR_EEPROM_Erase(0, MDR_EEPROM_CMD_BIT_MAS1, delay_100us);
}

void MDR_EEPROM_Write(uint32_t address, uint32_t data)
{ 
  //  Разблокировка контроллера EEPROM
  regKEY = EEPROM_KEY_ACCESS_CODE;
  
  // Включение регистрового доступа к памяти
  regCMD  = MDR_EEPROM_CMD_BIT_CON | MEM_BANK;
  regADDR = address;
  regDI   = data;
  
  // Вход в режим программирования, задержка 5мкс.
  regCMD = MDR_EEPROM_CMD_BIT_CON | MEM_BANK | MDR_EEPROM_CMD_BIT_XE | MDR_EEPROM_CMD_BIT_PROG;
  RAM_Delay(delay_5us);
  
  // Операция записи
  regCMD = MDR_EEPROM_CMD_BIT_CON | MEM_BANK | MDR_EEPROM_CMD_BIT_XE | MDR_EEPROM_CMD_BIT_PROG | MDR_EEPROM_CMD_BIT_NVSTR;
  RAM_Delay(delay_10us);
  
  // Время записи слова, задержка 40мкс
  regCMD = MDR_EEPROM_CMD_BIT_CON | MEM_BANK | MDR_EEPROM_CMD_BIT_XE | MDR_EEPROM_CMD_BIT_PROG | MDR_EEPROM_CMD_BIT_NVSTR | MDR_EEPROM_CMD_BIT_YE;
  RAM_Delay(delay_40us);
  
  // Выход из режима программирования, задержка 5мкс
  regCMD = MDR_EEPROM_CMD_BIT_CON | MEM_BANK | MDR_EEPROM_CMD_BIT_XE | MDR_EEPROM_CMD_BIT_PROG | MDR_EEPROM_CMD_BIT_NVSTR;  
  regCMD = MDR_EEPROM_CMD_BIT_CON | MEM_BANK | MDR_EEPROM_CMD_BIT_XE | MDR_EEPROM_CMD_BIT_NVSTR;
  RAM_Delay(delay_5us);
  
  //  Сброс остальных флагов, задержка 1мкс
  regCMD = MDR_EEPROM_CMD_BIT_CON | MEM_BANK;
  RAM_Delay(delay_1us);

  // Выход из регистрового доступа к памяти в обычный режим
  regCMD = 0;
  regKEY = 0;
}

uint32_t MDR_EEPROM_Read(uint32_t address)
{
  uint32_t Data;
 
  //  Разблокировка контроллера EEPROM
  regKEY = EEPROM_KEY_ACCESS_CODE;
  
  // Включение регистрового доступа к памяти
  regCMD = MDR_EEPROM_CMD_BIT_CON | MEM_BANK;
  //  Запрос слова
  regADDR = address;
  regCMD = MDR_EEPROM_CMD_BIT_CON | MEM_BANK | MDR_EEPROM_CMD_BIT_XE | MDR_EEPROM_CMD_BIT_YE | MDR_EEPROM_CMD_BIT_SE;
  //  Задержка 30нс (для 144МГц один такт ~7нс)
  regDO;
  regDO;
  regDO;
  //  Чтение слова
  Data = regDO;

  // Выход из регистрового доступа к памяти в обычный режим
  regCMD = 0;
  regKEY = 0;
   
  return Data;
}


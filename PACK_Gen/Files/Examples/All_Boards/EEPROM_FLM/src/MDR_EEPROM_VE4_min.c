#include "MDR_DeviceDefs.h"

#include "Bootloader_VE4.h"

static void RAM_Delay(uint32_t delayLoops)
{
  volatile uint32_t i = delayLoops;
  while (--i);
}

static void MDR_EEPROM_Erase(uint32_t address, uint32_t MAS1_Mask, uint32_t IFREN_Mask, uint32_t delayEraseExit)
{  
  //  Разблокировка контроллера EEPROM
  regKEY = EEPROM_KEY_ACCESS_CODE;
  
  // Включение регистрового доступа к памяти
  // IFREN: 0 - Main, 1 - Main и Info
  regCMD = IFREN_Mask | MDR_EEPROM_CMD_BIT_CON;

  regADDR = address;
  regDI = 0;
  
  // Вход в режим стирания, задержка 10мкс. MAS1 - стирание всех страниц в секторе.
  regCMD = MAS1_Mask | IFREN_Mask | MDR_EEPROM_CMD_BIT_CON | MDR_EEPROM_CMD_BIT_XE | MDR_EEPROM_CMD_BIT_ERASE;
  RAM_Delay(delay_10us);
  
  // Запуск стирания, время стирания сектора 40 мс
  regCMD = MAS1_Mask | IFREN_Mask | MDR_EEPROM_CMD_BIT_CON | MDR_EEPROM_CMD_BIT_XE | MDR_EEPROM_CMD_BIT_ERASE | MDR_EEPROM_CMD_BIT_NVSTR;
  RAM_Delay(delay_40ms);               
  
  // Выход из режима стирания, задержка для
  // страницы    5мкс
  // весь сектор 100мкс
  regCMD = MAS1_Mask | IFREN_Mask | MDR_EEPROM_CMD_BIT_CON | MDR_EEPROM_CMD_BIT_XE | MDR_EEPROM_CMD_BIT_NVSTR;
  RAM_Delay(delayEraseExit);              
  
  // Сброс флагов перед следующим циклом стирания сектора, задержка 1мкс
  regCMD = IFREN_Mask | MDR_EEPROM_CMD_BIT_CON;
  RAM_Delay(delay_1us);
  
  // Выход из регистрового доступа к памяти в обычный режим. Восстановление Delay.
  regCMD = 0;
  regKEY = 0;
}

void MDR_EEPROM_ErasePage(uint32_t address)
{
  MDR_EEPROM_Erase(address, 0, IFREN_ERASE_MAIN, delay_5us);
}

void MDR_EEPROM_EraseFull(void)
{
  uint32_t maskIFREN = IFREN_ERASE_MAIN;
  uint32_t isPowerUp = (regBKP_REG_0E & bFPOR) == 0;
  uint32_t i;
  
  if (isPowerUp)
    maskIFREN = IFREN_ERASE_MAIN_AND_INFO;
  else
    maskIFREN = IFREN_ERASE_MAIN;
   
  MDR_EEPROM_Erase(0x00000000, MDR_EEPROM_CMD_BIT_MAS1, maskIFREN, delay_100us);
  MDR_EEPROM_Erase(0x00008000, MDR_EEPROM_CMD_BIT_MAS1, maskIFREN, delay_100us);
  MDR_EEPROM_Erase(0x00010000, MDR_EEPROM_CMD_BIT_MAS1, maskIFREN, delay_100us);
  MDR_EEPROM_Erase(0x00018000, MDR_EEPROM_CMD_BIT_MAS1, maskIFREN, delay_100us);
  
  //  Write Bootloader to Info memory
  if (isPowerUp)
    for (i = 0; i < BOOTLOADER_WORD_COUNT; ++i)
    {
      MDR_EEPROM_Write(i << 2, BOOT_LOADER[i], MDR_EEPROM_CMD_BIT_IFREN);
    }
}

void MDR_EEPROM_Write(uint32_t address, uint32_t data, uint32_t maskIFREN)
{ 
  //  Разблокировка контроллера EEPROM
  regKEY = EEPROM_KEY_ACCESS_CODE;
  
  // Включение регистрового доступа к памяти
  regCMD  = maskIFREN | MDR_EEPROM_CMD_BIT_CON;
  regADDR = address;
  regDI   = data;
  
  // Вход в режим программирования, задержка 5мкс.
  regCMD = maskIFREN | MDR_EEPROM_CMD_BIT_CON | MDR_EEPROM_CMD_BIT_XE | MDR_EEPROM_CMD_BIT_PROG;
  RAM_Delay(delay_5us);
  
  // Операция записи
  regCMD = maskIFREN | MDR_EEPROM_CMD_BIT_CON | MDR_EEPROM_CMD_BIT_XE | MDR_EEPROM_CMD_BIT_PROG | MDR_EEPROM_CMD_BIT_NVSTR;
  RAM_Delay(delay_10us);
  
  // Время записи слова, задержка 40мкс
  regCMD = maskIFREN | MDR_EEPROM_CMD_BIT_CON | MDR_EEPROM_CMD_BIT_XE | MDR_EEPROM_CMD_BIT_PROG | MDR_EEPROM_CMD_BIT_NVSTR | MDR_EEPROM_CMD_BIT_YE;
  RAM_Delay(delay_40us);
  
  // Выход из режима программирования, задержка 5мкс
  regCMD = maskIFREN | MDR_EEPROM_CMD_BIT_CON | MDR_EEPROM_CMD_BIT_XE | MDR_EEPROM_CMD_BIT_PROG | MDR_EEPROM_CMD_BIT_NVSTR;  
  regCMD = maskIFREN | MDR_EEPROM_CMD_BIT_CON | MDR_EEPROM_CMD_BIT_XE | MDR_EEPROM_CMD_BIT_NVSTR;
  RAM_Delay(delay_5us);
  
  //  Сброс остальных флагов, задержка 1мкс
  regCMD = maskIFREN | MDR_EEPROM_CMD_BIT_CON;
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
  //  Задержка 55нс (для 36МГц один такт ~28нс)
  regDO;
  regDO;
  //  Чтение слова
  Data = regDO;

  // Выход из регистрового доступа к памяти в обычный режим
  regCMD = 0;
  regKEY = 0;
   
  return Data;
}


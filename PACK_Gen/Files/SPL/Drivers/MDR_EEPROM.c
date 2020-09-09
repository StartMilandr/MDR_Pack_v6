#include <MDR_EEPROM.h>


static void RAM_Delay(uint32_t delayLoops) __RAM_EXEC;
static void     MDR_EEPROM_Erase(uint32_t address, uint32_t IFREN_Mask, uint32_t MAS1_Mask, uint32_t delayEraseExit) __RAM_EXEC;
static uint32_t MDR_EEPROM_WriteBuff_PageSector(uint32_t dataInd, uint32_t address, uint32_t nextPageAddr, uint32_t count, uint32_t * data, MDR_EEPROM_MEM memBank) __RAM_EXEC;
static uint32_t MDR_EEPROM_ReadBuff_PageSector (uint32_t dataInd, uint32_t address, uint32_t nextPageAddr, uint32_t count, uint32_t * data, MDR_EEPROM_MEM memBank) __RAM_EXEC;

// ==================   Инициализация  =====================

static MDR_EEPROM_Delays _Delays __RAM_EXEC = {
  .loops_1us   = US_TO_DELAY_LOOPS_EX(1,   HSI_FREQ_HZ, DELAY_LOOP_CYCLES_C_RAM),
  .loops_5us   = US_TO_DELAY_LOOPS_EX(5,   HSI_FREQ_HZ, DELAY_LOOP_CYCLES_C_RAM),  
  .loops_40us  = US_TO_DELAY_LOOPS_EX(40,  HSI_FREQ_HZ, DELAY_LOOP_CYCLES_C_RAM),
  .loops_100us = US_TO_DELAY_LOOPS_EX(100, HSI_FREQ_HZ, DELAY_LOOP_CYCLES_C_RAM),
  .loops_40ms  = US_TO_DELAY_LOOPS_EX(40,  HSI_FREQ_HZ, DELAY_LOOP_CYCLES_C_RAM),  
} ;

void MDR_EEPROM_InitDelayStruct(uint32_t CPU_FreqHz, MDR_EEPROM_Delays * delays)
{  
  delays->loops_1us   = US_TO_DELAY_LOOPS_EX(1,   CPU_FreqHz, DELAY_LOOP_CYCLES_C_RAM);
  delays->loops_5us   = US_TO_DELAY_LOOPS_EX(5,   CPU_FreqHz, DELAY_LOOP_CYCLES_C_RAM);  
  delays->loops_40us  = US_TO_DELAY_LOOPS_EX(40,  CPU_FreqHz, DELAY_LOOP_CYCLES_C_RAM);
  delays->loops_100us = US_TO_DELAY_LOOPS_EX(100, CPU_FreqHz, DELAY_LOOP_CYCLES_C_RAM);
  delays->loops_40ms  = US_TO_DELAY_LOOPS_EX(40,  CPU_FreqHz, DELAY_LOOP_CYCLES_C_RAM);
}

void MDR_EEPROM_Init(uint32_t CPU_FreqHz)
{
  MDR_EEPROM_InitDelayStruct(CPU_FreqHz, &_Delays);
     
  MDR_CLOCK->MDR_CLK_EN_REG_EEPROM |= MDR_CLK_EN_BIT_EEPROM;
}

void MDR_EEPROM_InitEx(MDR_EEPROM_Delays * delays)
{
  _Delays = *delays;
  
  MDR_CLOCK->MDR_CLK_EN_REG_EEPROM |= MDR_CLK_EN_BIT_EEPROM;
}

static void RAM_Delay(uint32_t delayLoops)
{
  volatile uint32_t i = delayLoops;
  if (i)
    while (--i);
}

static uint32_t wasMaskedIRQ = 0;

void MDR_EEPROM_DisableIRQ(void)
{
  wasMaskedIRQ = __disable_irq();
}

void MDR_EEPROM_RestoreIRQ(void)
{
  if (!wasMaskedIRQ)
    __enable_irq();  
}


// ==================   Чтение  =====================
uint32_t MDR_EEPROM_Read(uint32_t address, MDR_EEPROM_MEM memBank)
{
  uint32_t tmpCMD;
  uint32_t bankMask = VAL2FLD(memBank, MDR_EEPROM_CMD_IFREN);
  uint32_t Data;
 
  //  Разблокировка контроллера EEPROM
  MDR_EEPROM->KEY = EEPROM_KEY_ACCESS_CODE;
  // Сохранение поля Delay для восстановления после исполнения функции
  tmpCMD = MDR_EEPROM->CMD; 
  
  // Включение регистрового доступа к памяти
  // IFREN: 0 - Main, 1 - Main и Info
  MDR_EEPROM->CMD = bankMask | MDR_EEPROM_CMD_BIT_CON;
  
  //  Запрос слова
  MDR_EEPROM->ADDR = address;
  MDR_EEPROM->CMD = bankMask | MDR_EEPROM_CMD_BIT_CON | MDR_EEPROM_CMD_BIT_XE | MDR_EEPROM_CMD_BIT_YE | MDR_EEPROM_CMD_BIT_SE;
  //  Задержка 30нс (для 144МГц один такт ~7нс)
  MDR_EEPROM->DO;   // Idle Reading for Delay
  MDR_EEPROM->DO;   // Idle Reading for Delay
  MDR_EEPROM->DO;   // Idle Reading for Delay
  MDR_EEPROM->DO;   // Idle Reading for Delay
  //  Чтение слова
  Data = MDR_EEPROM->DO;

  // Выход из регистрового доступа к памяти в обычный режим
  MDR_EEPROM->CMD = tmpCMD & MDR_EEPROM_CMD_DELAY_Msk;
  MDR_EEPROM->KEY = 0;
   
  return Data;
}

// ==================   Стирание  =====================
static void MDR_EEPROM_Erase(uint32_t address, uint32_t IFREN_Mask, uint32_t MAS1_Mask, uint32_t delayEraseExit)
{
  uint32_t tmpCMD;
  uint32_t sector;
 
  //  Разблокировка контроллера EEPROM
  MDR_EEPROM->KEY = EEPROM_KEY_ACCESS_CODE;
  // Сохранение поля Delay для восстановления после исполнения функции
  tmpCMD = MDR_EEPROM->CMD;    
  
  // Включение регистрового доступа к памяти
  // IFREN: 0 - Main, 1 - Main и Info
  MDR_EEPROM->CMD = IFREN_Mask | MDR_EEPROM_CMD_BIT_CON;

  // Стирание секторов по очереди
  // 0x_0 - sector A, 0x_4 - sector B,  0x_8 - sector C,  0x_C - sector D
  for (sector = 0; sector < (4 << 2); sector += 4)
  {
    MDR_EEPROM->ADDR = address + sector;
    MDR_EEPROM->DI = 0;
    
    // Вход в режим стирания, задержка 5мкс. MAS1 - стирание всех страниц в секторе.
    MDR_EEPROM->CMD = MAS1_Mask | IFREN_Mask  | MDR_EEPROM_CMD_BIT_CON | MDR_EEPROM_CMD_BIT_XE | MDR_EEPROM_CMD_BIT_ERASE;
    RAM_Delay(_Delays.loops_5us);
    
    // Запуск стирания, время стирания сектора 40 мс
    MDR_EEPROM->CMD = MAS1_Mask | IFREN_Mask  | MDR_EEPROM_CMD_BIT_CON | MDR_EEPROM_CMD_BIT_XE | MDR_EEPROM_CMD_BIT_ERASE | MDR_EEPROM_CMD_BIT_NVSTR;
    RAM_Delay(_Delays.loops_40ms);               
    
    // Выход из режима стирания, задержка для
    // страницы    5мкс
    // весь сектор 100мкс
    MDR_EEPROM->CMD = MAS1_Mask | IFREN_Mask | MDR_EEPROM_CMD_BIT_CON | MDR_EEPROM_CMD_BIT_XE | MDR_EEPROM_CMD_BIT_NVSTR;
    RAM_Delay(delayEraseExit);              
    
    // Сброс флагов перед следующим циклом стирания сектора, задержка 1мкс
    MDR_EEPROM->CMD = IFREN_Mask  | MDR_EEPROM_CMD_BIT_CON;
    RAM_Delay(_Delays.loops_1us);
  }

  // Выход из регистрового доступа к памяти в обычный режим. Восстановление Delay.
  MDR_EEPROM->CMD = tmpCMD & MDR_EEPROM_CMD_DELAY_Msk;
  MDR_EEPROM->KEY = 0;
}

void MDR_EEPROM_ErasePage(uint32_t pageStartAddr, MDR_EEPROM_MEM memBank)
{ 
  MDR_EEPROM_Erase(pageStartAddr, VAL2FLD(memBank, MDR_EEPROM_CMD_IFREN), 0, _Delays.loops_5us);
}

void MDR_EEPROM_EraseFull(MDR_EEPROM_ERASE_FULL_MEM eraseBank)
{
  MDR_EEPROM_Erase(0, VAL2FLD(eraseBank, MDR_EEPROM_CMD_IFREN), MDR_EEPROM_CMD_BIT_MAS1, _Delays.loops_100us);
}

// ==================   Запись  =====================
void MDR_EEPROM_Write(uint32_t address, uint32_t data, MDR_EEPROM_MEM memBank)
{
  uint32_t tmpCMD;
  uint32_t bankMask = VAL2FLD(memBank, MDR_EEPROM_CMD_IFREN);
  
  //  Разблокировка контроллера EEPROM
  MDR_EEPROM->KEY = EEPROM_KEY_ACCESS_CODE;
  // Сохранение поля Delay для восстановления после исполнения функции
  tmpCMD = MDR_EEPROM->CMD;
  
  // Включение регистрового доступа к памяти
  MDR_EEPROM->CMD = bankMask | MDR_EEPROM_CMD_BIT_CON;
  MDR_EEPROM->ADDR = address;
  MDR_EEPROM->DI  = data;
  
  // Вход в режим программирования, задержка 5мкс.
  MDR_EEPROM->CMD = bankMask | MDR_EEPROM_CMD_BIT_CON | MDR_EEPROM_CMD_BIT_XE | MDR_EEPROM_CMD_BIT_PROG;
  RAM_Delay(_Delays.loops_5us);
  
  // Операция записи
  MDR_EEPROM->CMD = bankMask | MDR_EEPROM_CMD_BIT_CON | MDR_EEPROM_CMD_BIT_XE | MDR_EEPROM_CMD_BIT_PROG | MDR_EEPROM_CMD_BIT_NVSTR;
  RAM_Delay(_Delays.loops_5us << 1);
  
  // Время записи слова, задержка 40мкс
  MDR_EEPROM->CMD = bankMask | MDR_EEPROM_CMD_BIT_CON | MDR_EEPROM_CMD_BIT_XE | MDR_EEPROM_CMD_BIT_PROG | MDR_EEPROM_CMD_BIT_NVSTR | MDR_EEPROM_CMD_BIT_YE;
  RAM_Delay(_Delays.loops_40us);
  
  // Выход из режима программирования, задержка 5мкс
  MDR_EEPROM->CMD = bankMask | MDR_EEPROM_CMD_BIT_CON | MDR_EEPROM_CMD_BIT_XE | MDR_EEPROM_CMD_BIT_PROG | MDR_EEPROM_CMD_BIT_NVSTR;
  MDR_EEPROM->CMD = bankMask | MDR_EEPROM_CMD_BIT_CON | MDR_EEPROM_CMD_BIT_XE | MDR_EEPROM_CMD_BIT_NVSTR;
  RAM_Delay(_Delays.loops_5us);
  
  //  Сброс остальных флагов, задержка 1мкс
  MDR_EEPROM->CMD = bankMask | MDR_EEPROM_CMD_BIT_CON;
  RAM_Delay(_Delays.loops_1us);

  // Выход из регистрового доступа к памяти в обычный режим. Восстановление Delay.
  MDR_EEPROM->CMD = tmpCMD & MDR_EEPROM_CMD_DELAY_Msk;
  MDR_EEPROM->KEY = 0;
}

// ==================   Стирание страниц под размер буфера  =====================
uint32_t MDR_EEPROM_EraseForBuff(uint32_t pageStartAddr, uint32_t count, MDR_EEPROM_MEM memBank)
{
  uint32_t buffEraseCount = 0;
  uint32_t sizeMem = MDR_EEPROM_GetSize(memBank);
  
  while (buffEraseCount < count)
  {
    if (pageStartAddr >= sizeMem)
      break;    
    
    MDR_EEPROM_ErasePage(pageStartAddr, memBank);
    buffEraseCount += MDR_EEPROM_PAGE_WORD_COUNT;

    pageStartAddr += MDR_EEPROM_PAGE_SIZE;
  }
  
  return buffEraseCount;
}

// ==================   Запись буфера в страницы =====================
static uint32_t MDR_EEPROM_WriteBuff_PageSector(uint32_t dataInd, uint32_t address, uint32_t nextPageAddr, uint32_t count, uint32_t * data, MDR_EEPROM_MEM memBank)
{
  uint32_t tmpCMD;
  uint32_t bankMask = VAL2FLD(memBank, MDR_EEPROM_CMD_IFREN);
  uint32_t writenCount = 0;
    
  // Сохранение поля Delay для восстановления после исполнения функции
  tmpCMD = MDR_EEPROM->CMD;
  
  // Включение регистрового доступа к памяти
  MDR_EEPROM->CMD = bankMask | MDR_EEPROM_CMD_BIT_CON;
  MDR_EEPROM->ADDR = address;
  MDR_EEPROM->DI = data[dataInd];
  
  // Вход в режим программирования, задержка 5мкс.
  MDR_EEPROM->CMD = bankMask | MDR_EEPROM_CMD_BIT_CON | MDR_EEPROM_CMD_BIT_XE | MDR_EEPROM_CMD_BIT_PROG;
  RAM_Delay(_Delays.loops_5us);
  
  // Операция записи
  MDR_EEPROM->CMD = bankMask | MDR_EEPROM_CMD_BIT_CON | MDR_EEPROM_CMD_BIT_XE | MDR_EEPROM_CMD_BIT_PROG | MDR_EEPROM_CMD_BIT_NVSTR;
  RAM_Delay(_Delays.loops_5us << 1);
  
  // Цикл записи данных в сектор страницы
  while (1)
  {
    // Время записи слова, задержка 40мкс
    MDR_EEPROM->CMD = bankMask | MDR_EEPROM_CMD_BIT_CON | MDR_EEPROM_CMD_BIT_XE | MDR_EEPROM_CMD_BIT_PROG | MDR_EEPROM_CMD_BIT_NVSTR | MDR_EEPROM_CMD_BIT_YE;
    RAM_Delay(_Delays.loops_40us);
  
    // Выход из режима программирования, задержка 5мкс
    MDR_EEPROM->CMD = bankMask | MDR_EEPROM_CMD_BIT_CON | MDR_EEPROM_CMD_BIT_XE | MDR_EEPROM_CMD_BIT_PROG | MDR_EEPROM_CMD_BIT_NVSTR;    
    //  Задержка 20нс
    RAM_Delay(_Delays.loops_5us << 2);
    
    ++writenCount;    
    //  Проверка окончания данных
    dataInd += 4;
    if (dataInd >= count)
      break;
    //  Проверка конца страницы
    address += 16;
    if (address >= nextPageAddr)
      break;
    
    //  Запись следующего слова
    //  Следующая ячейка в секторе страницы
    MDR_EEPROM->ADDR = address;
    MDR_EEPROM->DI = data[dataInd];
    //  Задержка 20нс
    RAM_Delay(_Delays.loops_5us << 2);      
  }  
  //  Выход из записи буфера
  MDR_EEPROM->CMD = bankMask | MDR_EEPROM_CMD_BIT_CON | MDR_EEPROM_CMD_BIT_XE | MDR_EEPROM_CMD_BIT_NVSTR;
  RAM_Delay(_Delays.loops_5us);
  
  //  Сброс остальных флагов, задержка 1мкс
  MDR_EEPROM->CMD = bankMask | MDR_EEPROM_CMD_BIT_CON;
  RAM_Delay(_Delays.loops_1us);

  // Выход из регистрового доступа к памяти в обычный режим. Восстановление Delay.
  MDR_EEPROM->CMD = tmpCMD & MDR_EEPROM_CMD_DELAY_Msk;
  
  return writenCount;
}

void MDR_EEPROM_WriteBuff(uint32_t addr, uint32_t count, uint32_t * data, MDR_EEPROM_MEM memBank)
{
  uint32_t i;
  uint32_t writenCount = 0;
  uint32_t wrCount = 0;
  uint32_t wrAddr;
  uint32_t nextAddr = addr;
  uint32_t * pData;
  uint32_t nextPageAddr = (addr & ~MDR_EEPROM_PAGE_ADDR_MASK) + MDR_EEPROM_PAGE_SIZE;
   
  //  Разблокировка контроллера EEPROM
  MDR_EEPROM->KEY = EEPROM_KEY_ACCESS_CODE;
  
  //  Запись страниц по секторам, пока не запишем count слов
  while (writenCount < count)
  {
    pData = &data[writenCount];
    wrCount = count - writenCount;
    
    // Запись секторов по очереди
    for (i = 0; i < 4; ++i)
    {   
      wrAddr = nextAddr + (i << 2);
      // Если адрес в странице
      if (wrAddr < nextPageAddr)
      {
        writenCount += MDR_EEPROM_WriteBuff_PageSector(i, wrAddr, nextPageAddr, wrCount, pData, memBank);
        if (writenCount >= count)
          break;
      }
    }
    
    nextAddr = addr + (writenCount << 2);
    nextPageAddr += MDR_EEPROM_PAGE_SIZE; 
  }
  MDR_EEPROM->KEY = 0;
}

// ==================   Чтение буфера из страниц =====================
static uint32_t MDR_EEPROM_ReadBuff_PageSector(uint32_t dataInd, uint32_t address, uint32_t nextPageAddr, uint32_t count, uint32_t * data, MDR_EEPROM_MEM memBank)
{
  uint32_t tmpCMD;
  uint32_t bankMask = VAL2FLD(memBank, MDR_EEPROM_CMD_IFREN);
  uint32_t readCount = 0;  
  
  // Сохранение поля Delay для восстановления после исполнения функции
  tmpCMD = MDR_EEPROM->CMD;
  
  // Включение регистрового доступа к памяти
  // IFREN: 0 - Main, 1 - Main и Info
  // Исполнение этого кода происходит не из EEPROM - поэтому Delay можно занулить
  MDR_EEPROM->CMD = bankMask | MDR_EEPROM_CMD_BIT_CON;
  //  Запрос слова
  MDR_EEPROM->ADDR = address;
  MDR_EEPROM->CMD = bankMask | MDR_EEPROM_CMD_BIT_CON | MDR_EEPROM_CMD_BIT_XE | MDR_EEPROM_CMD_BIT_YE | MDR_EEPROM_CMD_BIT_SE;
  
  while (1)
  {
    //  Задержка 30нс (для 144МГц один такт ~7нс)
    MDR_EEPROM->DO;   // Idle Reading for Delay
    MDR_EEPROM->DO;   // Idle Reading for Delay
    MDR_EEPROM->DO;   // Idle Reading for Delay
    MDR_EEPROM->DO;   // Idle Reading for Delay
    //  Чтение слова
    data[dataInd] = MDR_EEPROM->DO;
    ++readCount;
    
    //  Проверка окончания данных
    dataInd += 4;
    if (dataInd >= count)
      break;

    //  Проверка конца страницы
    address += 16;
    if (address >= nextPageAddr)
      break;

    //  Старт чтения следующего слова в секторе      
    MDR_EEPROM->ADDR = address;
  }

  // Выход из регистрового доступа к памяти в обычный режим. Восстановление Delay.
  MDR_EEPROM->CMD = tmpCMD & MDR_EEPROM_CMD_DELAY_Msk;
   
  return readCount;
}

void MDR_EEPROM_ReadBuff(uint32_t addr, uint32_t count, uint32_t * data, MDR_EEPROM_MEM memBank)
{
  uint32_t i;
  uint32_t writenCount = 0;
  uint32_t wrCount;
  uint32_t wrAddr;
  uint32_t * pData;
  uint32_t nextAddr = addr;  
  uint32_t nextPageAddr = (addr & ~MDR_EEPROM_PAGE_ADDR_MASK) + MDR_EEPROM_PAGE_SIZE;
   
  //  Разблокировка контроллера EEPROM
  MDR_EEPROM->KEY = EEPROM_KEY_ACCESS_CODE;
  
  //  Чтение страниц по секторам, пока не считаем count слов
  while (writenCount < count)
  {
    pData = &data[writenCount];
    wrCount = count - writenCount;
    
    // Чтение секторов по очереди
    for (i = 0; i < 4; ++i)
    {   
      wrAddr = nextAddr + (i << 2);
      // Если адрес в странице
      if (wrAddr < nextPageAddr)
      {
        writenCount += MDR_EEPROM_ReadBuff_PageSector(i, wrAddr, nextPageAddr, wrCount, pData, memBank);
        if (writenCount >= count)
          break;
      }
    }
    
    nextAddr = addr + (writenCount << 2);
    nextPageAddr += MDR_EEPROM_PAGE_SIZE; 
  }
  MDR_EEPROM->KEY = 0;
}

// ==================   Адресация страниц  =====================

uint32_t MDR_EEPROM_PageToAddr(MDR_EEPROM_PAGE page, MDR_EEPROM_MEM memBank)
{
  if (memBank == MDR_EEPROM_Main)
    return MDR_EEPROM_MAIN_PAGE_SIZE * (uint32_t) page;
  else
    return MDR_EEPROM_INFO_PAGE_SIZE * (uint32_t) page;
}

uint32_t MDR_EEPROM_GetPageSize(MDR_EEPROM_MEM memBank)
{
  if (memBank == MDR_EEPROM_Main)
    return MDR_EEPROM_MAIN_PAGE_SIZE;
  else
    return MDR_EEPROM_INFO_PAGE_SIZE;
}

uint32_t MDR_EEPROM_GetSize(MDR_EEPROM_MEM memBank)
{
  if (memBank == MDR_EEPROM_Main)
    return MDR_EEPROM_MAIN_PAGE_SIZE * MDR_EEPROM_MAIN_PAGE_COUNT;
  else
    return MDR_EEPROM_INFO_PAGE_SIZE * MDR_EEPROM_INFO_PAGE_COUNT;
}

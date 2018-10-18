#include "MDR_EEPROM.h"


static MDR_EEPROM_Delays _Delays __attribute__((section("EXECUTABLE_MEMORY_SECTION"))) = {
  .loops_1us   = US_TO_DELAY_LOOPS(1,   HSI_FREQ_HZ),
  .loops_5us   = US_TO_DELAY_LOOPS(5,   HSI_FREQ_HZ),  
  .loops_40us  = US_TO_DELAY_LOOPS(40,   HSI_FREQ_HZ),
  .loops_100us = US_TO_DELAY_LOOPS(100, HSI_FREQ_HZ),
  .loops_40ms  = MS_TO_DELAY_LOOPS(40,  HSI_FREQ_HZ),  
} ;

void MDR_EEPROM_InitDelayStruct(uint32_t CPU_FreqHz, MDR_EEPROM_Delays * delays)
{
  delays->loops_1us   = US_TO_DELAY_LOOPS(1,   CPU_FreqHz);
  delays->loops_5us   = US_TO_DELAY_LOOPS(5,   CPU_FreqHz);  
  delays->loops_40us  = US_TO_DELAY_LOOPS(40,  CPU_FreqHz);
  delays->loops_100us = US_TO_DELAY_LOOPS(100, CPU_FreqHz);
  delays->loops_40ms  = MS_TO_DELAY_LOOPS(40,  CPU_FreqHz);
}

void MDR_EEPROM_Init(uint32_t CPU_FreqHz)
{
  MDR_EEPROM_InitDelayStruct(CPU_FreqHz, &_Delays);
     
  MDR_CLOCK->MDR_CLK_EN_REG_EEPROM_b.EEPROM_CLK_EN = MDR_On;
}

void MDR_EEPROM_InitEx(MDR_EEPROM_Delays * delays)
{
  _Delays = *delays;
  
  MDR_CLOCK->MDR_CLK_EN_REG_EEPROM_b.EEPROM_CLK_EN = MDR_On;
}


static void RAM_Delay(uint32_t delayLoops) __attribute__((section("EXECUTABLE_MEMORY_SECTION")));

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


uint32_t MDR_EEPROM_Read(uint32_t address, MDR_EEPROM_MEM memBank)
{
  uint32_t Command;
  uint32_t Data;
 
  //  Разблокировка контроллера EEPROM
  MDR_EEPROM->KEY = EEPROM_KEY_ACCESS_CODE;
  // Включение регистрового доступа к памяти
  // IFREN: 0 - Main, 1 - Main и Info  
  Command = (MDR_EEPROM->CMD & MDR_EEPROM_CMD_DELAY_Msk) | MDR_EEPROM_CMD_BIT_CON | VAL2FLD(memBank, MDR_EEPROM_CMD_IFREN);
  MDR_EEPROM->CMD = Command;
  //  Запрос слова
  MDR_EEPROM->ADDR = address;
  MDR_EEPROM->CMD = Command | MDR_EEPROM_CMD_BIT_XE | MDR_EEPROM_CMD_BIT_YE | MDR_EEPROM_CMD_BIT_SE;
  //  Задержка 30нс (для 144МГц один такт ~7нс)
  MDR_EEPROM->DO;   // Idle Reading for Delay
  MDR_EEPROM->DO;   // Idle Reading for Delay
  MDR_EEPROM->DO;   // Idle Reading for Delay
  //MDR_EEPROM->DO;   // Idle Reading for Delay
  //  Чтение слова
  Data = MDR_EEPROM->DO;

  // Выход из регистрового доступа к памяти в обычный режим
  Command &= MDR_EEPROM_CMD_DELAY_Msk;
  MDR_EEPROM->CMD = Command;
  MDR_EEPROM->KEY = 0;
   
  return Data;
}

static void MDR_EEPROM_Erase(uint32_t address, uint32_t IFREN_Mask, uint32_t MAS1_Mask, uint32_t delayEraseExit) __attribute__((section("EXECUTABLE_MEMORY_SECTION")));

#ifndef MDR_EEPROM_36MHz
  static void MDR_EEPROM_Erase(uint32_t address, uint32_t IFREN_Mask, uint32_t MAS1_Mask, uint32_t delayEraseExit)
  {
    uint32_t Command;
    uint32_t sector;
   
    //  Разблокировка контроллера EEPROM
    MDR_EEPROM->KEY = EEPROM_KEY_ACCESS_CODE;
    
    // Включение регистрового доступа к памяти
    // IFREN: 0 - Main, 1 - Main и Info
    Command = (MDR_EEPROM->CMD & MDR_EEPROM_CMD_DELAY_Msk) | MDR_EEPROM_CMD_BIT_CON | IFREN_Mask;
    MDR_EEPROM->CMD = Command;

    // Стирание секторов по очереди
    // b00 - sector A, b01 - sector B,  b10 - sector C,  b11 - sector D
    for (sector = 0; sector < (4 << 2); sector += 4)
    {
      MDR_EEPROM->ADDR = address + sector;
      MDR_EEPROM->DI = 0;
      
      // Вход в режим стирания, задержка 5мкс. MAS1 - стирание всех страниц в секторе.
      Command |= MDR_EEPROM_CMD_BIT_XE | MDR_EEPROM_CMD_BIT_ERASE | MAS1_Mask;
      MDR_EEPROM->CMD = Command;
      RAM_Delay(_Delays.loops_5us);
      
      // Запуск стирания, время стирания сектора 40 мс
      Command |= MDR_EEPROM_CMD_BIT_NVSTR;
      MDR_EEPROM->CMD = Command;
      RAM_Delay(_Delays.loops_40ms);               
      
      // Выход из режима стирания, задержка для
      // страницы    5мкс
      // весь сектор 100мкс
      Command &= ~MDR_EEPROM_CMD_BIT_ERASE;
      MDR_EEPROM->CMD = Command;
      RAM_Delay(delayEraseExit);              
      
      // Сброс флагов перед следующим циклом стирания сектора, задержка 1мкс
      Command &= ~(MDR_EEPROM_CMD_BIT_XE | MDR_EEPROM_CMD_BIT_NVSTR | MAS1_Mask);
      MDR_EEPROM->CMD = Command;
      RAM_Delay(_Delays.loops_1us);
    }
    
    // Выход из регистрового доступа к памяти в обычный режим
    Command &= MDR_EEPROM_CMD_DELAY_Msk;
    MDR_EEPROM->CMD = Command;
    MDR_EEPROM->KEY = 0;
  }
#else
  static void MDR_EEPROM_Erase(uint32_t address, uint32_t IFREN_Mask, uint32_t MAS1_Mask, uint32_t delayEraseExit)
  {
    uint32_t Command;
    //uint32_t block = address / MDR_EEPROM_PAGE_SIZE;
        
    //  Разблокировка контроллера EEPROM
    MDR_EEPROM->KEY = EEPROM_KEY_ACCESS_CODE;
    
    // Включение регистрового доступа к памяти
    // IFREN: 0 - Main, 1 - Main и Info
    Command = (MDR_EEPROM->CMD & MDR_EEPROM_CMD_DELAY_Msk) | MDR_EEPROM_CMD_BIT_CON | IFREN_Mask;
    MDR_EEPROM->CMD = Command;

    MDR_EEPROM->ADDR = address;// + (block << 2);
    MDR_EEPROM->DI = 0;
    
    // Вход в режим стирания, задержка 10мкс. MAS1 - стирание всех страниц в секторе.
    Command |= MDR_EEPROM_CMD_BIT_XE | MDR_EEPROM_CMD_BIT_ERASE | MAS1_Mask;
    MDR_EEPROM->CMD = Command;
    RAM_Delay(_Delays.loops_5us << 1);
    
    // Запуск стирания, время стирания сектора 40 мс
    Command |= MDR_EEPROM_CMD_BIT_NVSTR;
    MDR_EEPROM->CMD = Command;
    RAM_Delay(_Delays.loops_40ms);               
    
    // Выход из режима стирания, задержка для
    // страницы    5мкс
    // весь сектор 100мкс
    Command &= ~MDR_EEPROM_CMD_BIT_ERASE;
    MDR_EEPROM->CMD = Command;
    RAM_Delay(delayEraseExit);              
    
    // Сброс флагов перед следующим циклом стирания сектора, задержка 1мкс
    Command &= ~(MDR_EEPROM_CMD_BIT_XE | MDR_EEPROM_CMD_BIT_NVSTR | MAS1_Mask);
    MDR_EEPROM->CMD = Command;
    RAM_Delay(_Delays.loops_1us);
    
    // Выход из регистрового доступа к памяти в обычный режим
    Command &= MDR_EEPROM_CMD_DELAY_Msk;
    MDR_EEPROM->CMD = Command;
    MDR_EEPROM->KEY = 0;
  }  
#endif

void MDR_EEPROM_ErasePage(MDR_EEPROM_PAGE page, MDR_EEPROM_MEM memBank)
{ 
  MDR_EEPROM_Erase(MDR_EEPROM_PageToAddr(page), VAL2FLD(memBank, MDR_EEPROM_CMD_IFREN), 0, _Delays.loops_5us);
}

void MDR_EEPROM_EraseFull(MDR_EEPROM_ERASE_MEM_BANK eraseBank)
{
  MDR_EEPROM_Erase(0, VAL2FLD(eraseBank, MDR_EEPROM_CMD_IFREN), MDR_EEPROM_CMD_BIT_MAS1, _Delays.loops_100us);
}

void MDR_EEPROM_Write(uint32_t address, uint32_t data, MDR_EEPROM_MEM memBank)
{
  uint32_t Command;
  
  //  Разблокировка контроллера EEPROM
  MDR_EEPROM->KEY = EEPROM_KEY_ACCESS_CODE;
  
  // Включение регистрового доступа к памяти
  Command = (MDR_EEPROM->CMD & MDR_EEPROM_CMD_DELAY_Msk) | MDR_EEPROM_CMD_BIT_CON | VAL2FLD(memBank, MDR_EEPROM_CMD_IFREN);
  MDR_EEPROM->CMD = Command;
  MDR_EEPROM->ADDR = address;
  MDR_EEPROM->DI  = data;
  
  // Вход в режим программирования, задержка 5мкс.
  Command |= MDR_EEPROM_CMD_BIT_XE | MDR_EEPROM_CMD_BIT_PROG;
  MDR_EEPROM->CMD = Command;
  RAM_Delay(_Delays.loops_5us);
  
  // Операция записи
  Command |= MDR_EEPROM_CMD_BIT_NVSTR;
  MDR_EEPROM->CMD = Command;
  RAM_Delay(_Delays.loops_5us << 1);
  
  // Время записи слова, задержка 40мкс
  Command |= MDR_EEPROM_CMD_BIT_YE;
  MDR_EEPROM->CMD = Command;
  RAM_Delay(_Delays.loops_40us);
  
  // Выход из режима программирования, задержка 5мкс
  Command &= ~MDR_EEPROM_CMD_BIT_YE;
  MDR_EEPROM->CMD = Command;
  Command &= ~MDR_EEPROM_CMD_BIT_PROG;
  MDR_EEPROM->CMD = Command;
  RAM_Delay(_Delays.loops_5us);
  
  //  Сброс остальных флагов, задержка 1мкс
  Command &= ~(MDR_EEPROM_CMD_BIT_XE | MDR_EEPROM_CMD_BIT_NVSTR);
  MDR_EEPROM->CMD = Command;
  RAM_Delay(_Delays.loops_1us);

  // Выход из регистрового доступа к памяти в обычный режим
  MDR_EEPROM->CMD = Command & MDR_EEPROM_CMD_DELAY_Msk;
  MDR_EEPROM->KEY = 0;
}

#ifndef _MDR_EEPROM_H
#define _MDR_EEPROM_H

#include <MDR_Config.h>
#include <MDR_Funcs.h>


#define MDR_EEPROM_Main      EEPROM_IFREN_Main
#define MDR_EEPROM_Info      EEPROM_IFREN_Info
#define MDR_EEPROM_MEM       MDR_EEPROM_IFREN

#define MDR_EEPROM_CLEAR_VALUE   0xFFFFFFFFUL

// moved to MDR_Config
//#define __RAM_EXEC    __attribute__((section("EXECUTABLE_MEMORY_SECTION")))

//====================  Инициализация блока ======================
//  Включение тактирования блока и задание задержек в зависимости от частоты CPU
typedef struct {
  uint32_t loops_1us;
  uint32_t loops_5us;  
  uint32_t loops_40us;
  uint32_t loops_100us;
  uint32_t loops_40ms;  
} MDR_EEPROM_Delays;

void MDR_EEPROM_Init(uint32_t CPU_FreqHz);
void MDR_EEPROM_InitEx(MDR_EEPROM_Delays * delays);
void MDR_EEPROM_InitDelayStruct(uint32_t CPU_FreqHz, MDR_EEPROM_Delays * delays);

//  Выключение тактирования блока
__STATIC_INLINE void MDR_EEPROM_Finit(void) {MDR_CLOCK->MDR_CLK_EN_REG_EEPROM &= ~MDR_CLK_EN_BIT_EEPROM;}


//====================  Отключение прерываний ======================
//  Перед операциями стирание, чтения, записи необходимо отключить прерывания!
//  Функция MDR_EEPROM_DisableIRQ запрещает все прерывания кроме NMI и HardFault.
//  После работы с EEPROM необходимо вернуть перерывания вызовом MDR_EEPROM_RestoreIRQ
void MDR_EEPROM_DisableIRQ(void);
void MDR_EEPROM_RestoreIRQ(void);


// ===============    Чтение и запись 32-битных слов  ====================
void     MDR_EEPROM_Write(uint32_t address, uint32_t data, MDR_EEPROM_MEM memBank) __RAM_EXEC;
uint32_t MDR_EEPROM_Read (uint32_t address, MDR_EEPROM_MEM memBank) __RAM_EXEC;


// ===============    Стирание страниц или всей памяти  ====================
//  Стирание страницы памяти. Основная и информационная стираются по отдельности!
void MDR_EEPROM_ErasePage(uint32_t pageStartAddr, MDR_EEPROM_MEM memBank) __RAM_EXEC;

// Стирание всей памяти. Информационная память не может быть стерта отдельно от основной!
typedef enum {
  EEPROM_EraseFull_Main,
  EEPROM_EraseFull_MainAndInfo
} MDR_EEPROM_ERASE_FULL_MEM;
  
void MDR_EEPROM_EraseFull(MDR_EEPROM_ERASE_FULL_MEM eraseBank) __RAM_EXEC;


// =====    Чтение и запись 32-битных массивов на несколько страниц  ======
//  Возвращает количество стертых слов начиная с addr. addr может быть не кратен страницы.
uint32_t MDR_EEPROM_EraseForBuff(uint32_t pageStartAddr, uint32_t count, MDR_EEPROM_MEM memBank);

void MDR_EEPROM_WriteBuff(uint32_t addr, uint32_t count, uint32_t * data, MDR_EEPROM_MEM memBank) __RAM_EXEC;
void MDR_EEPROM_ReadBuff (uint32_t addr, uint32_t count, uint32_t * data, MDR_EEPROM_MEM memBank) __RAM_EXEC;


//====================  Перечисление страниц памяти ======================
//  Получение размера страницы
uint32_t MDR_EEPROM_GetPageSize(MDR_EEPROM_MEM memBank);
uint32_t MDR_EEPROM_GetSize(MDR_EEPROM_MEM memBank);


#ifndef MDR_EEPROM_18MHz  
  typedef enum {
    EEPROM_Page1,    EEPROM_Page2,    EEPROM_Page3,  EEPROM_Page4,    EEPROM_Page5,
    EEPROM_Page6,    EEPROM_Page7,    EEPROM_Page8,  EEPROM_Page9,    EEPROM_Page10,
    EEPROM_Page11,   EEPROM_Page12,   EEPROM_Page13, EEPROM_Page14,   EEPROM_Page15,
    EEPROM_Page16,   EEPROM_Page17,   EEPROM_Page18, EEPROM_Page19,   EEPROM_Page20,
    EEPROM_Page21,   EEPROM_Page22,   EEPROM_Page23, EEPROM_Page24,   EEPROM_Page25,
    EEPROM_Page26,   EEPROM_Page27,   EEPROM_Page28, EEPROM_Page29,   EEPROM_Page30,
    EEPROM_Page31,   EEPROM_Page32
  } MDR_EEPROM_PAGE; 
  
  #define MDR_EEPROM_LastPage_Main      EEPROM_Page32
  #define MDR_EEPROM_LastPage_Info      EEPROM_Page1  

  #define MDR_EEPROM_MAIN_PAGE_SIZE     MDR_EEPROM_PAGE_SIZE
  #define MDR_EEPROM_INFO_PAGE_SIZE     MDR_EEPROM_PAGE_SIZE
   
  uint32_t MDR_EEPROM_PageToAddr(MDR_EEPROM_PAGE page, MDR_EEPROM_MEM memBank);  
  
#else

  #ifdef MDR_EEPROM_HAS_TWO_BLOCK_ONLY  
    // VK214 64KB
    typedef enum {
      EEPROM_Block1,    EEPROM_Block2
    } MDR_EEPROM_BLOCK;

    #define MDR_EEPROM_LastBlock_Main     EEPROM_Block2
    #define MDR_EEPROM_LastBlock_Info     EEPROM_Block2
  #else  
    // VK234 128KB
    typedef enum {
      EEPROM_Block1,    EEPROM_Block2,    EEPROM_Block3,  EEPROM_Block4
    } MDR_EEPROM_BLOCK;

    #define MDR_EEPROM_LastBlock_Main     EEPROM_Block4
    #define MDR_EEPROM_LastBlock_Info     EEPROM_Block4  
  #endif
  
  //  Страницы в блоке
  typedef enum {
    EEPROM_Page1,    EEPROM_Page2,    EEPROM_Page3,   EEPROM_Page4,    EEPROM_Page5,
    EEPROM_Page6,    EEPROM_Page7,    EEPROM_Page8,   EEPROM_Page9,    EEPROM_Page10,
    EEPROM_Page11,   EEPROM_Page12,   EEPROM_Page13,  EEPROM_Page14,   EEPROM_Page15,
    EEPROM_Page16,   EEPROM_Page17,   EEPROM_Page18,  EEPROM_Page19,   EEPROM_Page20,
    EEPROM_Page21,   EEPROM_Page22,   EEPROM_Page23,  EEPROM_Page24,   EEPROM_Page25,
    EEPROM_Page26,   EEPROM_Page27,   EEPROM_Page28,  EEPROM_Page29,   EEPROM_Page30,
    EEPROM_Page31,   EEPROM_Page32,   EEPROM_Page33,  EEPROM_Page34,   EEPROM_Page35,
    EEPROM_Page36,   EEPROM_Page37,   EEPROM_Page38,  EEPROM_Page39,   EEPROM_Page40,
    EEPROM_Page41,   EEPROM_Page42,   EEPROM_Page43,  EEPROM_Page44,   EEPROM_Page45,
    EEPROM_Page46,   EEPROM_Page47,   EEPROM_Page48,  EEPROM_Page49,   EEPROM_Page50,
    EEPROM_Page51,   EEPROM_Page52,   EEPROM_Page53,  EEPROM_Page54,   EEPROM_Page55,
    EEPROM_Page56,   EEPROM_Page57,   EEPROM_Page58,  EEPROM_Page59,   EEPROM_Page60,
    EEPROM_Page61,   EEPROM_Page62,   EEPROM_Page63,  EEPROM_Page64
  } MDR_EEPROM_PAGE;


  #define MDR_EEPROM_LastPage_Main      EEPROM_Page64
  #define MDR_EEPROM_LastPage_Info      EEPROM_Page4
  
  #define MDR_EEPROM_MAIN_PAGE_SIZE     MDR_EEPROM_PAGE_SIZE
  #define MDR_EEPROM_INFO_PAGE_SIZE     MDR_EEPROM_PAGE_SIZE

  uint32_t MDR_EEPROM_PageToAddr(MDR_EEPROM_BLOCK block, MDR_EEPROM_PAGE page, MDR_EEPROM_MEM memBank);  
  
  void MDR_EEPROM_EraseBlock(uint32_t blockStartAddr, MDR_EEPROM_MEM memBank);
  
#endif




#endif //_MDR_EEPROM_H


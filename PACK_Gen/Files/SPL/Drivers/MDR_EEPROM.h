#ifndef _MDR_EEPROM_H
#define _MDR_EEPROM_H

#include "MDR_Config.h"
#include "MDR_Funcs.h"


#define MDR_EEPROM_Main      EEPROM_IFREN_Main
#define MDR_EEPROM_Info      EEPROM_IFREN_Info
#define MDR_EEPROM_MEM       MDR_EEPROM_IFREN

//#define MDR_EEPROM_PAGE_WORD_COUNT        1024  //  32bits word
//#define MDR_EEPROM_PAGE_SIZE              (4 * MDR_EEPROM_PAGE_WORD_COUNT)
//#define MDR_EEPROM_PAGE_COUNT             32
#define MDR_EEPROM_CLEAR_VALUE            0xFFFFFFFFUL

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
__STATIC_INLINE void MDR_EEPROM_Finit(void) {MDR_CLOCK->MDR_CLK_EN_REG_EEPROM_b.EEPROM_CLK_EN = MDR_On;}

//  Перед операциями стирание, чтения, записи необходимо отключить прерывания!
//  Функция MDR_EEPROM_DisableIRQ запрещает все прерывания кроме NMI и HardFault.
//  После работы с EEPROM необходимо вернуть перерывания вызовом MDR_EEPROM_RestoreIRQ
void MDR_EEPROM_DisableIRQ(void);
void MDR_EEPROM_RestoreIRQ(void);

//  Чтение и запись 32-битных слов
void     MDR_EEPROM_Write(uint32_t address, uint32_t data, MDR_EEPROM_MEM memBank) __attribute__((section("EXECUTABLE_MEMORY_SECTION")));
uint32_t MDR_EEPROM_Read (uint32_t address, MDR_EEPROM_MEM memBank) __attribute__((section("EXECUTABLE_MEMORY_SECTION")));

//  Перечисление страниц памяти
typedef enum {
  EEPROM_Page1,    EEPROM_Page2,    EEPROM_Page3,  EEPROM_Page4,    EEPROM_Page5,
  EEPROM_Page6,    EEPROM_Page7,    EEPROM_Page8,  EEPROM_Page9,    EEPROM_Page10,
  EEPROM_Page11,   EEPROM_Page12,   EEPROM_Page13, EEPROM_Page14,   EEPROM_Page15,
  EEPROM_Page16,   EEPROM_Page17,   EEPROM_Page18, EEPROM_Page19,   EEPROM_Page20,
  EEPROM_Page21,   EEPROM_Page22,   EEPROM_Page23, EEPROM_Page24,   EEPROM_Page25,
  EEPROM_Page26,   EEPROM_Page27,   EEPROM_Page28, EEPROM_Page29,   EEPROM_Page30,
  EEPROM_Page31,   EEPROM_Page32
  
#ifdef MDR_EEPROM_36MHz  
                                ,   EEPROM_Page33,  EEPROM_Page34,  EEPROM_Page35,  EEPROM_Page36,   EEPROM_Page37,   EEPROM_Page38,  EEPROM_Page39,  EEPROM_Page40,
  EEPROM_Page41,   EEPROM_Page42,   EEPROM_Page43,  EEPROM_Page44,  EEPROM_Page45,  EEPROM_Page46,   EEPROM_Page47,   EEPROM_Page48,  EEPROM_Page49,  EEPROM_Page50,
  EEPROM_Page51,   EEPROM_Page52,   EEPROM_Page53,  EEPROM_Page54,  EEPROM_Page55,  EEPROM_Page56,   EEPROM_Page57,   EEPROM_Page58,  EEPROM_Page59,  EEPROM_Page60,
  EEPROM_Page61,   EEPROM_Page62,   EEPROM_Page63,  EEPROM_Page64,  EEPROM_Page65,  EEPROM_Page66,   EEPROM_Page67,   EEPROM_Page68,  EEPROM_Page69,  EEPROM_Page70,
  EEPROM_Page71,   EEPROM_Page72,   EEPROM_Page73,  EEPROM_Page74,  EEPROM_Page75,  EEPROM_Page76,   EEPROM_Page77,   EEPROM_Page78,  EEPROM_Page79,  EEPROM_Page80,
  EEPROM_Page81,   EEPROM_Page82,   EEPROM_Page83,  EEPROM_Page84,  EEPROM_Page85,  EEPROM_Page86,   EEPROM_Page87,   EEPROM_Page88,  EEPROM_Page89,  EEPROM_Page90,
  EEPROM_Page91,   EEPROM_Page92,   EEPROM_Page93,  EEPROM_Page94,  EEPROM_Page95,  EEPROM_Page96,   EEPROM_Page97,   EEPROM_Page98,  EEPROM_Page99,  EEPROM_Page100,
  EEPROM_Page101,  EEPROM_Page102,  EEPROM_Page03,  EEPROM_Page104, EEPROM_Page105, EEPROM_Page106,  EEPROM_Page107,  EEPROM_Page108, EEPROM_Page109, EEPROM_Page110,
  EEPROM_Page111,  EEPROM_Page112,  EEPROM_Page113, EEPROM_Page114, EEPROM_Page115, EEPROM_Page116,  EEPROM_Page117,  EEPROM_Page118, EEPROM_Page119, EEPROM_Page120,
  EEPROM_Page121,  EEPROM_Page122,  EEPROM_Page123, EEPROM_Page124, EEPROM_Page125, EEPROM_Page126,  EEPROM_Page127,  EEPROM_Page128, EEPROM_Page129, EEPROM_Page130,
  EEPROM_Page131,  EEPROM_Page132,  EEPROM_Page133, EEPROM_Page134, EEPROM_Page135, EEPROM_Page136,  EEPROM_Page137,  EEPROM_Page138, EEPROM_Page139, EEPROM_Page140,
  EEPROM_Page141,  EEPROM_Page142,  EEPROM_Page143, EEPROM_Page144, EEPROM_Page145, EEPROM_Page146,  EEPROM_Page147,  EEPROM_Page148, EEPROM_Page149, EEPROM_Page150,
  EEPROM_Page151,  EEPROM_Page152,  EEPROM_Page153, EEPROM_Page154, EEPROM_Page155, EEPROM_Page156,  EEPROM_Page157,  EEPROM_Page158, EEPROM_Page159, EEPROM_Page160,
  EEPROM_Page161,  EEPROM_Page162,  EEPROM_Page163, EEPROM_Page164, EEPROM_Page165, EEPROM_Page166,  EEPROM_Page167,  EEPROM_Page168, EEPROM_Page169, EEPROM_Page170,
  EEPROM_Page171,  EEPROM_Page172,  EEPROM_Page173, EEPROM_Page174, EEPROM_Page175, EEPROM_Page176,  EEPROM_Page177,  EEPROM_Page178, EEPROM_Page179, EEPROM_Page180,
  EEPROM_Page181,  EEPROM_Page182,  EEPROM_Page183, EEPROM_Page184, EEPROM_Page185, EEPROM_Page186,  EEPROM_Page187,  EEPROM_Page188, EEPROM_Page189, EEPROM_Page190,
  EEPROM_Page191,  EEPROM_Page192,  EEPROM_Page193, EEPROM_Page194, EEPROM_Page195, EEPROM_Page196,  EEPROM_Page197,  EEPROM_Page198, EEPROM_Page199, EEPROM_Page200,
  EEPROM_Page201,  EEPROM_Page202,  EEPROM_Page203, EEPROM_Page204, EEPROM_Page205, EEPROM_Page206,  EEPROM_Page207,  EEPROM_Page208, EEPROM_Page209, EEPROM_Page210,
  EEPROM_Page211,  EEPROM_Page212,  EEPROM_Page213, EEPROM_Page214, EEPROM_Page215, EEPROM_Page216,  EEPROM_Page217,  EEPROM_Page218, EEPROM_Page219, EEPROM_Page220,
  EEPROM_Page221,  EEPROM_Page222,  EEPROM_Page223, EEPROM_Page224, EEPROM_Page225, EEPROM_Page226,  EEPROM_Page227,  EEPROM_Page228, EEPROM_Page229, EEPROM_Page230,
  EEPROM_Page231,  EEPROM_Page232,  EEPROM_Page233, EEPROM_Page234, EEPROM_Page235, EEPROM_Page236,  EEPROM_Page237,  EEPROM_Page238, EEPROM_Page239, EEPROM_Page240,
  EEPROM_Page241,  EEPROM_Page242,  EEPROM_Page243, EEPROM_Page244, EEPROM_Page245, EEPROM_Page246,  EEPROM_Page247,  EEPROM_Page248, EEPROM_Page249, EEPROM_Page250,
  EEPROM_Page251,  EEPROM_Page252,  EEPROM_Page523, EEPROM_Page254, EEPROM_Page255, EEPROM_Page256
  
#endif
} MDR_EEPROM_PAGE;

#ifndef MDR_EEPROM_36MHz
  #define MDR_EEPROM_LastPage_Main  EEPROM_Page32
  #define MDR_EEPROM_LastPage_Info  EEPROM_Page1
#else
  #define MDR_EEPROM_LastPage_Main  EEPROM_Page256
  #define MDR_EEPROM_LastPage_Info  EEPROM_Page16
#endif


//  Получение начального адреса страницы
__STATIC_INLINE uint32_t MDR_EEPROM_PageToAddr(MDR_EEPROM_PAGE page)
{
  return MDR_EEPROM_PAGE_SIZE * (uint32_t) page;
}

//  Стирание страницы памяти. Основная и информационная стираются по отдельности!
void MDR_EEPROM_ErasePage (MDR_EEPROM_PAGE page, MDR_EEPROM_MEM memBank) __attribute__((section("EXECUTABLE_MEMORY_SECTION")));

// Стирание всей памяти. Информационная память не может быть стерта отдельно от основной!
typedef enum {
  EEPROM_Erase_Main,
  EEPROM_Erase_MainAndInfo
} MDR_EEPROM_ERASE_MEM_BANK;

void MDR_EEPROM_EraseFull(MDR_EEPROM_ERASE_MEM_BANK eraseBank);
  

#endif //_MDR_EEPROM_H


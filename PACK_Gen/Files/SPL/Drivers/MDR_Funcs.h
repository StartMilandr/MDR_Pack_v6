#ifndef MDR_FUNCS_H
#define MDR_FUNCS_H

#include <MDR_Types.h>

//===================    Функция ожидания с таймаутом  ===================
bool WaitCondition(uint32_t timeoutCycles, pBoolFunc_void checkFunc);


void MDR_WaitFlagSet  (uint32_t addr, uint32_t flag);
void MDR_WaitFlagClear(uint32_t addr, uint32_t flag);


//=========================    Задержки и времена =======================
//  Задержка в количестве пустых циклов
void MDR_Delay(uint32_t Ticks);

#define MDR_DebugerProtectDelay()     MDR_Delay(2000000)

//  Минимальное количество тактов на исполнение одного пустого цикла 
//  (Зависит от настроек компилятора и самого компилятора)

#if   defined (__CC_ARM)
  // Измерено практическим путем для компилятора ARM V5.06 update4 (build 422)
  #if (__OPTIMISE_LEVEL > 1 )
    #define DELAY_LOOP_CYCLES                 4UL    // O2 и выше
  #else
    #define DELAY_LOOP_CYCLES                 8UL
  #endif
#elif (__ARMCC_VERSION >= 6010050)
  // Измерено практическим путем для компилятора V6.6 (LVVM). Одинаково при любой оптимизации
  #define DELAY_LOOP_CYCLES                   8UL
#else
  // По умолчанию
  #define DELAY_LOOP_CYCLES                   8UL
#endif

//  Пересчет миллисекунд в такты CPU
#define MS_TO_CLOCKS(mSec, CPU_FregHz)            ((uint32_t)((double)(mSec) * (CPU_FregHz) / 1000))
#define US_TO_CLOCKS(uSec, CPU_FregHz)            ((uint32_t)((double)(uSec) * (CPU_FregHz) / 1000000))
#define NS_TO_CLOCKS(nSec, CPU_FregHz)            ((uint32_t)((double)(uSec) * (CPU_FregHz) / 1000000000))

//  Пересчет миллисекунд в количество тактов от частоты тактирования
#define  S_TO_DELAY_LOOPS(Sec, CPU_FregHz)      ((uint32_t)((double)(Sec)  * (CPU_FregHz) / DELAY_LOOP_CYCLES))
#define MS_TO_DELAY_LOOPS(mSec, CPU_FregHz)     ((uint32_t)((double)(mSec) * (CPU_FregHz) / DELAY_LOOP_CYCLES / 1000 ))
#define US_TO_DELAY_LOOPS(uSec, CPU_FregHz)     ((uint32_t)((double)(uSec) * (CPU_FregHz) / DELAY_LOOP_CYCLES / 1000000 ))
#define NS_TO_DELAY_LOOPS(nSec, CPU_FregHz)     ((uint32_t)((double)(nSec) * (CPU_FregHz) / DELAY_LOOP_CYCLES / 1000000000 ))
 
#define MDR_Delay_ms(mSec, CPU_FregHz)          MDR_Delay(MS_TO_DELAY_LOOPS((mSec), (CPU_FregHz)))
#define MDR_Delay_us(uSec, CPU_FregHz)          MDR_Delay(US_TO_DELAY_LOOPS((uSec), (CPU_FregHz)))

//=====================    Псевдо-случайное значение ===================
uint32_t MDR_ToPseudoRand(uint32_t value);


//===========================    Битовые поля ===========================
//  Доступ к регистрам по адресу
#define REG32(x)   (*((volatile uint32_t *)(x)))
#define REG32_C(x) (*((const volatile uint32_t *)(x)))

//  Доступ к полям в слове
#define VAL2FLD(value, field)      _VAL2FLD(field, value)
#define VAL2FLD_Pos(value, pos)     ((uint32_t)(value) << pos)

#define FLD_CLEAR(value, mask)     ((uint32_t)(value) & (~(mask)))

static __inline uint32_t MaskClrSet(uint32_t value, uint32_t maskClr, uint32_t maskSet)
{
  return (value & (~maskClr)) | maskSet;
}

static __inline uint32_t MaskClr(uint32_t value, uint32_t maskClr)
{
  return (value & (~maskClr));
}

static __inline uint32_t MaskSet(uint32_t value, uint32_t maskSet)
{
  return (value | maskSet);
}

//================    Макрос для подавления ворнингов от неиспользуемых параметров =======================
#define UNUSED(x) (void)(x)

//================    Макрос количества элементов в массиве =======================

#define ARR_LEN(arr)  sizeof(arr)/sizeof(arr[0])


//=========================    Log for debug ===========================
//#define DEBUG_LOG_ENA   // Для активации можно добавить в настройки проекта, закладка C/C++ поле define: DEBUG_LOG_ENA

#ifdef DEBUG_LOG_ENA
  typedef struct
  {
    uint32_t *pBuff;
    uint32_t BuffLen;
    uint32_t IndWR;
    uint32_t DataCnt;
    
  } MDR_LogRec;

  // Объект лога. Можно завести несколько, чтобы логгировать в разные массивы.
  extern MDR_LogRec MDR_LogRec1;

  void MDR_LOG_Clear(MDR_LogRec *pLogRec);
  void MDR_LOG_Add(MDR_LogRec *pLogRec, uint32_t value);
  
  #define MDR_LOG_Clear_def()       MDR_LOG_Clear(&MDR_LogRec1);
  #define MDR_LOG_Add_def(value)    MDR_LOG_Add(&MDR_LogRec1, (value));
  
#else
  #define MDR_LogRec MDR_LogRec1;

  #define MDR_LOG_Clear()
  #define MDR_LOG_Add()
#endif




#endif // MDR_FUNCS_H


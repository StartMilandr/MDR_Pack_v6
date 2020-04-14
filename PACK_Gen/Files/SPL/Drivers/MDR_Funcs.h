#ifndef MDR_FUNCS_H
#define MDR_FUNCS_H

#include <MDR_Config.h>
#include <MDR_Types.h>

//=========    BiteOrder and BitOrder ==========
#define REV_BYTES32(x)  __REV(x)
#define REV_BYTES16(x)  __REVSH(x)
#define REV_BITS32(x)   __RBIT(x)


//=========    Макрос для подавления ворнингов от неиспользуемых параметров ==========
#define UNUSED(x) (void)(x)

//===================    Функция ожидания с таймаутом  ===================
bool WaitCondition(uint32_t timeoutCycles, pBoolFunc_void checkFunc);


void MDR_WaitFlagSet  (uint32_t addr, uint32_t flag);
void MDR_WaitFlagClear(uint32_t addr, uint32_t flag);


//=========================    Преобразование времени в такты CPU и циклы MDR_Delay ====================
#define _SEC_TO_CLOCK(Sec, freqCPU_Hz, SecUnit)    ((uint32_t)((double)(Sec) * (freqCPU_Hz) / SecUnit))
  
#define  S_TO_CLOCKS(Sec, freqCPU_Hz)             _SEC_TO_CLOCK(Sec, freqCPU_Hz, 1)
#define MS_TO_CLOCKS(mSec, freqCPU_Hz)            _SEC_TO_CLOCK(mSec, freqCPU_Hz, 1000)
#define US_TO_CLOCKS(uSec, freqCPU_Hz)            _SEC_TO_CLOCK(uSec, freqCPU_Hz, 1000000)
#define NS_TO_CLOCKS(nSec, freqCPU_Hz)            _SEC_TO_CLOCK(nSec, freqCPU_Hz, 1000000000)

//=========================    Преобразование времени в циклы MDR_Delay =================================

//  Минимальное количество тактов на исполнение одного пустого цикла 
//  (Зависит от настроек компилятора и самого компилятора)
#ifndef DELAY_LOOP_CYCLES
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
#endif

//  CycPerLoop - количество тактов CPU на исполнение одного цикла
#define _SEC_TO_DELAY_LOOPS(Sec, freqCPU_Hz, CycPerLoop, SecUnit)   ((uint32_t)((double)(Sec) * (freqCPU_Hz) / SecUnit / CycPerLoop))

#define  S_TO_DELAY_LOOPS_EX(Sec,  freqCPU_Hz, CycPerLoop)    _SEC_TO_DELAY_LOOPS(Sec,  freqCPU_Hz, CycPerLoop, 1         )
#define MS_TO_DELAY_LOOPS_EX(mSec, freqCPU_Hz, CycPerLoop)    _SEC_TO_DELAY_LOOPS(mSec, freqCPU_Hz, CycPerLoop, 1000      )
#define US_TO_DELAY_LOOPS_EX(uSec, freqCPU_Hz, CycPerLoop)    _SEC_TO_DELAY_LOOPS(uSec, freqCPU_Hz, CycPerLoop, 1000000   )
#define NS_TO_DELAY_LOOPS_EX(nSec, freqCPU_Hz, CycPerLoop)    _SEC_TO_DELAY_LOOPS(nSec, freqCPU_Hz, CycPerLoop, 1000000000)

#define  S_TO_DELAY_LOOPS(Sec,  freqCPU_Hz)                    S_TO_DELAY_LOOPS_EX(Sec,  freqCPU_Hz, DELAY_LOOP_CYCLES)
#define MS_TO_DELAY_LOOPS(mSec, freqCPU_Hz)                   MS_TO_DELAY_LOOPS_EX(mSec, freqCPU_Hz, DELAY_LOOP_CYCLES)
#define US_TO_DELAY_LOOPS(uSec, freqCPU_Hz)                   US_TO_DELAY_LOOPS_EX(uSec, freqCPU_Hz, DELAY_LOOP_CYCLES)
#define NS_TO_DELAY_LOOPS(nSec, freqCPU_Hz)                   NS_TO_DELAY_LOOPS_EX(nSec, freqCPU_Hz, DELAY_LOOP_CYCLES)

#define CLOCKS_TO_DELAY_LOOPS(clock)                          ((uint32_t)((double)(clock) / DELAY_LOOP_CYCLES))

//=========================    Варианты задержки =======================
//  Тип функции для ссылки на реализацию
#define pWaitTicksFunc    pVoidFunc_U32

//  1: Задержка на СИ - Сильно зависит от опций компиляции
void MDR_DelayC(volatile uint32_t Ticks);

//  2: Задержка на ASM - Зависит от того из какой помяти выполняется - EEPROM или RAM
#if defined (__CC_ARM)
  __asm void MDR_DelayASM(uint32_t Ticks);
#elif (__ARMCC_VERSION >= 6010050)
  __attribute__((naked)) void MDR_DelayASM(uint32_t Ticks);
#endif

//  3: Задержка на DWT отладчика, есть только в Cortex-M3/M4. Самая точная!
void MDR_DelayDWT_Init(void);
void MDR_DelayDWT(uint32_t clockCountCPU);
void MDR_DelayDWT_DeInit(void);


//  MDR_ConfigVEx.h: Выбор текущего варианта MDR_Delay - задержка в DELAY_LOOPS
#if defined (USE_MDR_DELAY_C)
  #define MDR_Delay_Init()    UNUSED(0)
  #define MDR_Delay()         MDR_DelayС
#elif defined (USE_MDR_DELAY_DWT)
  #define MDR_Delay_Init      MDR_DelayDWT_Init
  #define MDR_Delay           MDR_DelayDWT
#else
  #define MDR_Delay_Init()    UNUSED(0)
  #define MDR_Delay           MDR_DelayASM
#endif

//  Функции задержки в единицах времени
#define MDR_Delay_ms(mSec, freqCPU_Hz)    MDR_Delay(MS_TO_DELAY_LOOPS((mSec), (freqCPU_Hz)))
#define MDR_Delay_us(uSec, freqCPU_Hz)    MDR_Delay(US_TO_DELAY_LOOPS((uSec), (freqCPU_Hz)))

//  Задержка для начала Main, чтобы отладчик успевал перехватить управление, 
//  пока не начал исполняться пользовательский код, который может поломать отладчик.
#define MDR_DebugerProtectDelay()         MDR_Delay(2000000)


//=====================    Псевдо-случайное значение ===================
uint32_t MDR_ToPseudoRand(uint32_t value);


//===========================    Битовые поля ===========================
//  Доступ к регистрам по адресу
#define REG32(x)   (*((volatile uint32_t *)(x)))
#define REG32_C(x) (*((const volatile uint32_t *)(x)))

#define MEM32    REG32

//  Доступ к полям в слове
#define FLD2VAL(value, field)      _FLD2VAL(field, value)
#define VAL2FLD(value, field)      _VAL2FLD(field, value)
#define VAL2FLD_Pos(value, pos)     ((uint32_t)(value) << (pos))

#define FLD_CLEAR(value, mask)     ((uint32_t)(value) & (~(mask)))

static __inline uint32_t MDR_MaskClrSet(uint32_t value, uint32_t maskClr, uint32_t maskSet)
{
  return (value & (~maskClr)) | maskSet;
}

static __inline uint32_t MDR_MaskClr(uint32_t value, uint32_t maskClr)
{
  return (value & (~maskClr));
}

static __inline uint32_t MDR_MaskSet(uint32_t value, uint32_t maskSet)
{
  return (value | maskSet);
}


//================    Макрос количества элементов в массиве =======================

#define ARR_LEN(arr)  sizeof(arr)/sizeof(arr[0])


//============    Переход на новое ПО (новую прошивку) (реализация от Professor Chaos)============
// https://forum.milandr.ru/viewtopic.php?p=25799#p25799
#if defined(__CORE_CM3_H_GENERIC) || defined(__CORE_CM4_H_GENERIC)
	// Переход в новый проект по его адресу в памяти
	void RunNewApp_CortexM3M4(uint32_t newAppAddr);
#endif


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
#ifndef LOG_BUFF_Len
  #define LOG_BUFF_Len  200
#endif

  extern MDR_LogRec MDR_LogRec1;
  extern uint32_t   MDR_LogData1[LOG_BUFF_Len];

  void MDR_LOG_Clear(MDR_LogRec *pLogRec);
  void MDR_LOG_Add(MDR_LogRec *pLogRec, uint32_t value);
  
  #define MDR_LOG_Clear_def()       MDR_LOG_Clear(&MDR_LogRec1);
  #define MDR_LOG_Add_def(value)    MDR_LOG_Add(&MDR_LogRec1, (value));
  
#else
  #define MDR_LogRec MDR_LogRec1;

  #define MDR_LOG_Clear()
  #define MDR_LOG_Add()
	#define MDR_LOG_Add_def(value)
#endif




#endif // MDR_FUNCS_H


#ifndef MDR_FUNCS_H
#define MDR_FUNCS_H

#include <MDR_Types.h>

typedef bool (*pBoolFunc_U32)(uint32_t);
typedef bool (*pBoolFunc_void)(void);

bool WaitCondition(uint32_t timeoutCycles, pBoolFunc_void checkFunc);


//  Задержка в количестве пустых циклов
void MDR_Delay(uint32_t Ticks);

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


//  Пересчет миллисекунд в количество тактов от частоты тактирования
#define MS_TO_DELAY_LOOPS(mSec, CPU_FregHz)     ((uint32_t)((double)(mSec) * (CPU_FregHz) / 1000 / DELAY_LOOP_CYCLES))
 
#define MDR_Delay_ms(mSec, CPU_FregHz)          MDR_Delay(MS_TO_DELAY_LOOPS((mSec), (CPU_FregHz)))
#define MDR_Delay_us(uSec, CPU_FregHz)          MDR_Delay(MS_TO_DELAY_LOOPS((uSec) / 1000, (CPU_FregHz)))

//  Пересчет миллисекунд в такты CPU
#define MS_TO_TIKS(mSec, CPU_FregHz)            ((uint32_t)((double)(mSec) * (CPU_FregHz) / 1000))


//  Доступ к регистрам по адресу
#define REG32(x) (*((volatile uint32_t *)(x)))


//  Доступ к полям в слове
#define VAL2FLD(value, field)      _VAL2FLD(field, value)
#define FLD_CLEAR(value, mask)     ((uint32_t)(value) & (~(mask)))



#endif // MDR_FUNCS_H


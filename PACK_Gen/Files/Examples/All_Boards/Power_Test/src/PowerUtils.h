#ifndef _POWERUTILS_H
#define _POWERUTILS_H

#include <MDR_Config.h>
#include "MDR_Power.h"
#include <MDR_Funcs.h>

//==================    Определение диапазона в котором находится Ucc ==================
typedef struct {
  MDR_PWR_LevelUcc levelAbove;
  MDR_PWR_LevelUcc levelBelow;
} PWR_Range_Ucc;

typedef struct {
  MDR_PWR_LevelBUcc levelAbove;
  MDR_PWR_LevelBUcc levelBelow;
} PWR_Range_BUcc;

bool FindRange_Ucc (uint32_t delay, PWR_Range_Ucc  *rangeUcc);
bool FindRange_BUcc(uint32_t delay, PWR_Range_BUcc *rangeUcc);

//==================    Определение времени выставления уровня eventLevel ==================
typedef struct {
  uint32_t cyclesRise;
  uint32_t cyclesFall;
} PWR_LevelWaitCycles;

void FindLevelSetCycles_Ucc (const PWR_Range_Ucc *rangeUcc,  uint32_t delay, PWR_LevelWaitCycles *levelWaitCycles);
void FindLevelSetCycles_BUcc(const PWR_Range_BUcc *rangeUcc, uint32_t delay, PWR_LevelWaitCycles *levelWaitCycles);

#endif  //_POWERUTILS_H


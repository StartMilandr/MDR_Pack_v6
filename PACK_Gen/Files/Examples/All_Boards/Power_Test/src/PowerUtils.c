#include "PowerUtils.h"

void POWER_IRQHandler(void);

static bool SearchForEventLevel_Ucc(MDR_PWR_LevelUcc level1, MDR_PWR_LevelUcc level2, uint32_t delay, MDR_PWR_LevelUcc *eventLevelUcc)
{
  MDR_PWR_LevelUcc i;
  
  if (level1 < level2)
    for (i = level1; i <= level2; ++i)
    {
      MDR_Power_ChangeLevelUcc(i);
      MDR_Delay(delay);
      
      if (MDR_Power_GetEventUcc())
      {
        *eventLevelUcc = i;
        return true;
      }
    }
  else
    for (i = level1; i <= level1; --i)
    {
      MDR_Power_ChangeLevelUcc(i);
      MDR_Delay(delay);
      
      if (MDR_Power_GetEventUcc())
      {
        *eventLevelUcc = i;
        return true;
      }
    }
  
  *eventLevelUcc = level2;
  return false;
}

static bool SearchForEventLevel_BUcc(MDR_PWR_LevelBUcc level1, MDR_PWR_LevelBUcc level2, uint32_t delay, MDR_PWR_LevelBUcc *eventLevelBUcc)
{
  MDR_PWR_LevelBUcc i;
  
  if (level1 < level2)
    for (i = level1; i <= level2; ++i)
    {
      MDR_Power_ChangeLevelBUcc(i);
      MDR_Delay(delay);

      if (MDR_Power_GetEventBUcc())
      {
        *eventLevelBUcc = i;
        return true;
      }
    }
  else  
    for (i = level1; i <= level1; --i)
    {
      MDR_Power_ChangeLevelBUcc(i);
      MDR_Delay(delay);

      if (MDR_Power_GetEventBUcc())
      {
        *eventLevelBUcc = i;
        return true;
      }
    }
  
  *eventLevelBUcc = level2;  
  return false;
}


//==================    Определение диапазона в котором находится Ucc ==================
bool FindRange_Ucc(uint32_t delay, PWR_Range_Ucc *rangeUcc)
{
  bool             okAbove;
  bool             okBelow;

  //  Выставляем максимальный eventLevel
  MDR_Power_ChangeLevelUcc(MDR_PWR_LevelUcc_Max);
  MDR_Delay(delay);    
  
  //  Ищем уровень ниже текущего Ucc, 
  //  т.е. ждем событие по eventLevel < Ucc , понижая eventLevel
  MDR_Power_ChangeEventCondUcc(PWR_xUcc_Higher);
  MDR_Power_ClearEvents();
  okBelow = SearchForEventLevel_Ucc(MDR_PWR_LevelUcc_Max, MDR_PWR_LevelUcc_Min, delay, &(rangeUcc->levelBelow));
  
  //  Ищем уровень превышающий текущий Ucc,
  //  т.е. ждем событие по Ucc < eventLevel, повышая eventLevel
  MDR_Power_ChangeEventCondUcc(PWR_xUcc_Lower);
  MDR_Power_ClearEvents();
  if (okBelow)
    okAbove = SearchForEventLevel_Ucc(rangeUcc->levelBelow, MDR_PWR_LevelUcc_Max, delay, &(rangeUcc->levelAbove));
  else
    okAbove = SearchForEventLevel_Ucc(MDR_PWR_LevelUcc_Min, MDR_PWR_LevelUcc_Max, delay, &(rangeUcc->levelAbove));

  return okAbove && okBelow;
}

bool FindRange_BUcc(uint32_t delay, PWR_Range_BUcc *rangeUcc)
{
  bool             okAbove;
  bool             okBelow;

  //  Выставляем максимальный eventLevel
  MDR_Power_ChangeLevelBUcc(MDR_PWR_LevelBUcc_Max);
  MDR_Delay(delay);    
  
  //  Ищем уровень ниже текущего Ucc, 
  //  т.е. ждем событие по eventLevel < Ucc , понижая eventLevel
  MDR_Power_ChangeEventCondBUcc(PWR_xUcc_Higher);
  MDR_Power_ClearEvents();
  okBelow = SearchForEventLevel_BUcc(MDR_PWR_LevelBUcc_Max, MDR_PWR_LevelBUcc_Min, delay, &(rangeUcc->levelBelow));
  
  //  Ищем уровень превышающий текущий Ucc,
  //  т.е. ждем событие по Ucc < eventLevel, повышая eventLevel
  MDR_Power_ChangeEventCondBUcc(PWR_xUcc_Lower);
  MDR_Power_ClearEvents();
  if (okBelow)
    okAbove = SearchForEventLevel_BUcc(rangeUcc->levelBelow, MDR_PWR_LevelBUcc_Max, delay, &(rangeUcc->levelAbove));
  else
    okAbove = SearchForEventLevel_BUcc(MDR_PWR_LevelBUcc_Min, MDR_PWR_LevelBUcc_Max, delay, &(rangeUcc->levelAbove));

  return okAbove && okBelow;
}


//==================    Определение времени выставления уровня eventLevel ==================
static uint32_t LoopCounter;
static uint32_t LoopCounterResult;
static bool     WaitForIRQ;


void FindLevelSetCycles_Ucc(const PWR_Range_Ucc *rangeUcc, uint32_t delay, PWR_LevelWaitCycles *levelWaitCycles)
{
  //  Выставляем максимальный eventLevel
  MDR_Power_ChangeLevelUcc(rangeUcc->levelAbove);
  MDR_Delay(delay);
  //  Настраиваемся на событие по eventLevel < Ucc
  MDR_Power_ChangeEventCondUcc(PWR_xUcc_Higher);
  MDR_Power_ClearEvents();
  //  Разрешаем прерывание по событию - выключается в прерывании
  MDR_Power_EnaIRQ_Ucc(); 
  
  //  Выставляем минимальное значение из диапазона, считаем циклы пока уровень установится и сработает прерывание.
  LoopCounter = 0;
  WaitForIRQ = true;
  MDR_Power_ChangeLevelUcc(rangeUcc->levelBelow);
  while (WaitForIRQ)
    ++LoopCounter;
  
  //  Сохраняем результат
  levelWaitCycles->cyclesFall = LoopCounterResult;
  
  //  Из прерывания, настраиваемся на событие по Ucc < eventLevel
  MDR_Power_ChangeEventCondUcc(PWR_xUcc_Lower);
  MDR_Power_ClearEvents();
  //  Разрешаем прерывание по событию - выключается в прерывании
  MDR_Power_EnaIRQ_Ucc();
  
  //  Выставляем максимальное значение из диапазона, считаем циклы пока уровень установится и сработает прерывание.
  LoopCounter = 0;
  WaitForIRQ = true;
  MDR_Power_ChangeLevelUcc(rangeUcc->levelAbove);
  while (WaitForIRQ)
    ++LoopCounter;
  
  //  Сохраняем результат
  levelWaitCycles->cyclesRise = LoopCounterResult;  
}

void POWER_IRQHandler(void)
{
  LoopCounterResult = LoopCounter;
  
  MDR_Power_DisIRQ();
  WaitForIRQ = false;
}

// Все аналогично Ucc но для BUcc
void FindLevelSetCycles_BUcc(const PWR_Range_BUcc *rangeUcc, uint32_t delay, PWR_LevelWaitCycles *levelWaitCycles)
{
  //  Выставляем максимальный eventLevel
  MDR_Power_ChangeLevelBUcc(rangeUcc->levelAbove);
  MDR_Delay(delay);
  //  Настраиваемся на событие по eventLevel < Ucc
  MDR_Power_ChangeEventCondBUcc(PWR_xUcc_Higher);
  MDR_Power_ClearEvents();
  //  Разрешаем прерывание по событию - выключается в прерывании
  MDR_Power_EnaIRQ_BUcc();  

  //  Выставляем минимальное значение из диапазона, считаем циклы пока уровень установится и сработает прерывание.
  LoopCounter = 0;
  WaitForIRQ = true;
  MDR_Power_ChangeLevelBUcc(rangeUcc->levelBelow);
  while (WaitForIRQ)
    ++LoopCounter;
  
  //  Сохраняем результат
  levelWaitCycles->cyclesFall = LoopCounterResult;
  
  //  Из прерывания, настраиваемся на событие по Ucc < eventLevel
  MDR_Power_ChangeEventCondBUcc(PWR_xUcc_Lower);
  MDR_Power_ClearEvents();
  //  Разрешаем прерывание по событию - выключается в прерывании
  MDR_Power_EnaIRQ_BUcc();
  
  //  Выставляем максимальное значение из диапазона, считаем циклы пока уровень установится и сработает прерывание.
  LoopCounter = 0;
  WaitForIRQ = true;
  MDR_Power_ChangeLevelBUcc(rangeUcc->levelAbove);
  while (WaitForIRQ)
    ++LoopCounter;
  
  //  Сохраняем результат
  levelWaitCycles->cyclesRise = LoopCounterResult;
}

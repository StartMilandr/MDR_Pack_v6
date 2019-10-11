#include <MDR_Funcs.h>

//===================    Функция ожидания с таймаутом  ===================
bool WaitCondition(uint32_t timeoutCycles, pBoolFunc_void checkFunc)
{
  while (timeoutCycles != 0)
  {
    if (checkFunc())
      return true;
    timeoutCycles--;
  }
  return checkFunc();
}

void MDR_WaitFlagSet(uint32_t addr, uint32_t flag)
{
  while ((REG32(addr) & flag) != flag);
}

void MDR_WaitFlagClear(uint32_t addr, uint32_t flag)
{
  while ((REG32(addr) & flag) == flag);
}


//=========================    Задержка =======================
//-----------------   Задержка на СИ-------------------
//  Сильно зависит от опций компиляции
void MDR_DelayC(volatile uint32_t Ticks)
{
  if (Ticks)
    while(--Ticks);  
}

//-----------------   Задержка на ASM-------------------
// Зависит от того из какой помяти выполняется - EEPROM или RAM
#if   defined (__CC_ARM)

__asm void MDR_DelayASM(uint32_t Ticks)
{
           CMP   r0,#0x00
           BEQ   __Exit
           NOP   
__NextLoop SUBS  r0,r0,#1
           BNE   __NextLoop
__Exit BX  lr
}

#elif (__ARMCC_VERSION >= 6010050)
__attribute__((naked)) void MDR_DelayASM(uint32_t Ticks)
{
  __asm(
  "  CMP   r0,#0x00     ;\n"
  "  BEQ   1f           ;\n"
  "  NOP                ;\n"
  "0:                   ;\n"
  "  SUBS  r0,r0,#1     ;\n"
  "  BNE   0b           ;\n"
  "1:                   ;\n"
  "  BX  lr             ;\n"
  );
}
#endif


//-----------------   Задержка на DWT отладчика  -------------------
#define    regDWT_CYCCNT    *(volatile unsigned long *)0xE0001004
#define    regDWT_CONTROL   *(volatile unsigned long *)0xE0001000
#define    regSCB_DEMCR     *(volatile unsigned long *)0xE000EDFC
  
#define    _CoreDebug_DEMCR_TRCENA_Msk   0x01000000UL
#define    _DWT_CTRL_CYCCNTENA_Msk       0x1UL

void MDR_DelayDWT_Init(void)
{
  //разрешаем использовать счётчик
  regSCB_DEMCR |= _CoreDebug_DEMCR_TRCENA_Msk;
  //обнуляем значение счётного регистра
	regDWT_CYCCNT  = 0;
  //запускаем счётчик
	regDWT_CONTROL |= _DWT_CTRL_CYCCNTENA_Msk; 
}

void MDR_DelayDWT(uint32_t clockCountCPU)
{    
  uint32_t t0 = regDWT_CYCCNT;
  while ((regDWT_CYCCNT - t0) < (clockCountCPU));
}

void MDR_DelayDWT_DeInit(void)
{
	regDWT_CONTROL &= ~_DWT_CTRL_CYCCNTENA_Msk; 
}

//=====================    Псевдо-случайное значение ===================
uint32_t MDR_ToPseudoRand(uint32_t value)
{ 
  uint32_t hash = 0;
  uint32_t i = 0;
  uint8_t* key = (uint8_t *)&value;

  for (i = 0; i < 4; i++)
  {
    hash += key[i];
    hash += (hash << 10);
    hash ^= (hash >> 6);
  }

  for (i = 0; i < 256; i++)
  {
    hash += (hash << 10);
    hash ^= (hash >> 6);
  }

  hash += (hash << 3);
  hash ^= (hash >> 11);
  hash += (hash << 15);
  return hash;
}

//============    Log for debug ============
#ifdef DEBUG_LOG_ENA
  // Объект лога. Можно завести несколько, чтобы логгировать в разные массивы.  
  uint32_t MDR_LogData1[LOG_BUFF_Len];

  MDR_LogRec MDR_LogRec1 =
  {
    .pBuff    = MDR_LogData1,
    .BuffLen  = LOG_BUFF_Len,
    .IndWR    = 0,
    .DataCnt  = 0  
  };

  void MDR_LOG_Clear(MDR_LogRec *pLogRec)
  {
    uint16_t i;
    
    for (i = 0; i < pLogRec->BuffLen; ++i)
      pLogRec->pBuff[i] = 0;
    pLogRec->IndWR = 0;
    pLogRec->DataCnt = 0;
  }

  void MDR_LOG_Add(MDR_LogRec *pLogRec, uint32_t value)
  {
    pLogRec->pBuff[pLogRec->IndWR++] = value;
    pLogRec->DataCnt++;
    if (pLogRec->IndWR >= pLogRec->BuffLen)
      pLogRec->IndWR = 0;
  }
#endif

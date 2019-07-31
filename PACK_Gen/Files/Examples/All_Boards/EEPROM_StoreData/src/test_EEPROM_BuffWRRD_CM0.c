#include "test_EEPROM_BuffWRRD.h"

#ifndef MDR_EEPROM_18MHz
  Вместо этого необходимо подключить модуль test_EEPROM_PageWRRD.c !
#endif

#define USE_PSEUDO_RAND_VALUES  0

#if USE_PSEUDO_RAND_VALUES
  #define GetTestValue  MDR_ToPseudoRand
#else
  static uint32_t ReturnInput(uint32_t value) { return value; }

  #define GetTestValue  ReturnInput
#endif
  
  
typedef enum {
  tst_OK,
  tst_WriteFinished,
  tst_Err_CheckData,  
  tst_Err_CheckBuff
} TestResult;  

#define STATUS_COUNT    4
static char* resultNames[STATUS_COUNT] = {"Success", "WriteCompleted", "E_WRRD", "DataFault"};


#define DATA_BLOCK_MAIN  MDR_EEPROM_LastBlock_Main
#define DATA_PAGE_MAIN   EEPROM_Page7

#define SHOW_ERROR_INFO_PAGE_BF   0

#if SHOW_ERROR_INFO_PAGE_BF
  #define DATA_BLOCK_INFO  MDR_EEPROM_LastBlock_Info
  #define DATA_PAGE_INFO   EEPROM_Page1
#else
  #define DATA_BLOCK_INFO  EEPROM_Block1
  #define DATA_PAGE_INFO   EEPROM_Page1
#endif


//  Тестирование записи буфера длиной 2 страницsы по 512 байт
#define BUFF_WORD_COUNT  (MDR_EEPROM_PAGE_WORD_COUNT * 2)

//  Сдвиг начала записи буферов чтобы пересечь границу страниц. Только для MAIN.
#define BUFF_DATA_OFFS_MAIN   (MDR_EEPROM_PAGE_WORD_COUNT - 16)
#define BUFF_DATA_OFFS_INFO   0  

static uint32_t pageAddrMain;
static uint32_t pageAddrInfo;

static uint32_t buffCountWR_Main;
static uint32_t buffCountWR_Info;

static void     PrepareBuffData(uint32_t runIndex);
static uint32_t WritePageBuffs(uint32_t addr, MDR_EEPROM_MEM bank, uint32_t runIndex);
static void     ReadPageBuffs(uint32_t addr, MDR_EEPROM_MEM bank);
static uint32_t CompareBuffWRRD(void);
static uint32_t ReadAndCheckWords(uint32_t addr, MDR_EEPROM_MEM bank, uint32_t count);

static uint32_t   ExecTest(uint32_t addr, MDR_EEPROM_MEM bank, uint32_t runIndex, uint32_t wrOffsetInd);
static TestResult CheckResult(uint32_t addr, MDR_EEPROM_MEM bank, uint32_t writtenCount, uint32_t wrOffsetInd);

//  ===========   Interface functions ==============
static void TestInit(void);

static char * TestGetName_Main(void);
static uint32_t TestExec_Main(uint32_t runIndex);
static uint32_t TestCheckResult_Main(uint32_t runIndex);

static char * TestGetName_Info(void);
static uint32_t TestExec_Info(uint32_t runIndex);
static uint32_t TestCheckResult_Info(uint32_t runIndex);

static char * TestResultToString(uint32_t result);


TestInterface TI_EEPROM_Buff_Main = {
  .funcInit             = &TestInit,
  .funcTestExec         = &TestExec_Main,
  .funcCheckResult      = &TestCheckResult_Main,
  .funcResultToString   = &TestResultToString,
  .funcTestName         = &TestGetName_Main
};

TestInterface TI_EEPROM_Buff_Info = {
  .funcInit             = &TestInit,
  .funcTestExec         = &TestExec_Info,
  .funcCheckResult      = &TestCheckResult_Info,
  .funcResultToString   = &TestResultToString,
  .funcTestName         = &TestGetName_Info
};

static void TestInit(void)
{
  pageAddrMain = MDR_EEPROM_PageToAddr(DATA_BLOCK_MAIN, DATA_PAGE_MAIN, MDR_EEPROM_Main);
  pageAddrInfo = MDR_EEPROM_PageToAddr(DATA_BLOCK_INFO, DATA_PAGE_INFO, MDR_EEPROM_Info);
}

static char * TestGetName_Main(void)
{
  return "MainBf";
}

static uint32_t TestExec_Main(uint32_t runIndex)
{ 
  buffCountWR_Main = ExecTest(pageAddrMain, MDR_EEPROM_Main, runIndex, BUFF_DATA_OFFS_MAIN);
  return (uint32_t)tst_WriteFinished;
}

static uint32_t TestCheckResult_Main(uint32_t runIndex)
{
  UNUSED(runIndex);
  return CheckResult(pageAddrMain, MDR_EEPROM_Main, buffCountWR_Main, BUFF_DATA_OFFS_MAIN);
}

static char * TestGetName_Info(void)
{
  return "InfoBf";
}

static uint32_t TestExec_Info(uint32_t runIndex)
{
  buffCountWR_Info = ExecTest(pageAddrInfo, MDR_EEPROM_Info, runIndex, BUFF_DATA_OFFS_INFO);
  return tst_WriteFinished;  
}

static uint32_t TestCheckResult_Info(uint32_t runIndex)
{
  UNUSED(runIndex);
  return CheckResult(pageAddrInfo, MDR_EEPROM_Info, buffCountWR_Info, BUFF_DATA_OFFS_INFO);
}

static char * TestResultToString(uint32_t result)
{
  if (result < STATUS_COUNT)
    return resultNames[result];
  else
    return "Unk Err";
}


//==========    Buffer Write, Read and Check ===============
static uint32_t pageDataWR[BUFF_WORD_COUNT];
static uint32_t pageDataRD[BUFF_WORD_COUNT];

static void PrepareBuffData(uint32_t runIndex)
{
  uint32_t lenWR  = 1; // in bytes
  uint32_t offsWR = 0;
  uint32_t i;
  
  while ((offsWR + lenWR) < BUFF_WORD_COUNT)
  {
    //  Запись данных увеличивающимися порциями
    for (i = 0; i < lenWR; ++i)
      pageDataWR[offsWR + i] = GetTestValue(offsWR + i + runIndex);
   
    offsWR += lenWR;
    ++lenWR;
  }
}

static uint32_t WritePageBuffs(uint32_t addr, MDR_EEPROM_MEM bank, uint32_t runIndex)
{
  uint32_t lenWR  = 1;
  uint32_t offsWR = 0;
    
  PrepareBuffData(runIndex);
  
  while ((offsWR + lenWR) < BUFF_WORD_COUNT)
  {
    //  Запись данных увеличивающимися порциями
    MDR_EEPROM_WriteBuff(addr + (offsWR << 2), lenWR, &pageDataWR[offsWR], bank);
       
    offsWR += lenWR;
    ++lenWR;
  }
  
  return offsWR;
}

static void ReadPageBuffs(uint32_t addr, MDR_EEPROM_MEM bank)
{
  uint32_t lenWR  = 1;
  uint32_t offsWR = 0;
  
  while ((offsWR + lenWR) < BUFF_WORD_COUNT)
  {
    //  Запись данных увеличивающимися порциями
    MDR_EEPROM_ReadBuff(addr + (offsWR << 2), lenWR, &pageDataRD[offsWR], bank);
       
    offsWR += lenWR;
    ++lenWR;
  }
}

static uint32_t CompareBuffWRRD(void)
{
  uint32_t i;
  uint32_t errCnt = 0;
  for (i = 0; i < BUFF_WORD_COUNT; ++i)
    if (pageDataWR[i] != pageDataRD[i])
      ++errCnt;
    
  return errCnt;  
}

static uint32_t ReadAndCheckWords(uint32_t addr, MDR_EEPROM_MEM bank, uint32_t count)
{
  uint32_t i;
  uint32_t errCnt = 0;
  uint32_t rdData;
  for (i = 0; i < count; ++i)
  {
    rdData = MDR_EEPROM_Read(addr + (i << 2), bank);
    if (pageDataWR[i] != rdData)
      ++errCnt;
  }  
    
  return errCnt;  
}

static uint32_t ExecTest(uint32_t addr, MDR_EEPROM_MEM bank, uint32_t runIndex, uint32_t wrOffsetInd)
{
  // Стирание памяти под буфер только с начала страницы!
  MDR_EEPROM_EraseForBuff(addr, BUFF_WORD_COUNT + wrOffsetInd, bank);
  
  // wrOffset - для возможности запись буфера не сначала страницы
  return WritePageBuffs(addr + (wrOffsetInd << 2), bank, runIndex);  
}

static TestResult CheckResult(uint32_t addr, MDR_EEPROM_MEM bank, uint32_t writtenCount, uint32_t wrOffsetInd)
{
  uint32_t errCount;
  
  addr += (wrOffsetInd << 2);
  
  ReadPageBuffs(addr, bank);
  errCount = CompareBuffWRRD();
  if (errCount != 0)
    return tst_Err_CheckBuff;
  else
  {
    errCount = ReadAndCheckWords(addr, bank, writtenCount);
    if (errCount != 0)
      return tst_Err_CheckData;
  }
  
  return tst_OK;
}

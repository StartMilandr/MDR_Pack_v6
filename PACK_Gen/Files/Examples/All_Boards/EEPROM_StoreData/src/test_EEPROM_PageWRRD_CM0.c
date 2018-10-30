#include "test_EEPROM_PageWRRD.h"

#ifndef MDR_EEPROM_18MHz
  Вместо этого необходимо подключить модуль test_EEPROM_PageWRRD.c !
#endif

#define DATA_BLOCK_MAIN  MDR_EEPROM_LastBlock_Main
#define DATA_BLOCK_INFO  MDR_EEPROM_LastBlock_Info

#define DATA_PAGE_MAIN   MDR_EEPROM_LastPage_Main
#define DATA_PAGE_INFO   EEPROM_Page1 //MDR_EEPROM_LastPage_Info

//  Сдвиг начала записи буферов чтобы пересечь границу страниц. Только для MAIN.
#define BUFF_DATA_OFFS_MAIN   (MDR_EEPROM_PAGE_WORD_COUNT - 16)
#define BUFF_DATA_OFFS_INFO   0  

static uint32_t pageAddrMain;
static uint32_t pageAddrInfo;

typedef enum 
{
  tst_OK,
  tst_Err_Erase,
  tst_Err_CheckData,
  tst_WriteFinished
} TestResult;

#define STATUS_COUNT    4
static char* resultNames[STATUS_COUNT] = {"Success", "EraseFault", "DataFault", "WriteCompleted"};

//----------  Варианты записываемых данных  -------------
// На 8МГц много времени уходит на рассчет MDR_ToPseudoRand(),
// Запись просто индексов происходит значительно быстрее.
#define USE_PSEUDO_RAND_VALUES  0

#if USE_PSEUDO_RAND_VALUES
  #define GetTestValue  MDR_ToPseudoRand
#else
  static uint32_t ReturnInput(uint32_t value) { return value; }

  #define GetTestValue  ReturnInput
#endif
  
static TestResult EEPROM_WritePage(uint32_t pageStartAddr, MDR_EEPROM_MEM bank, uint32_t runIndex);
static TestResult EEPROM_ClearAndWritePage(uint32_t pageStartAddr, MDR_EEPROM_MEM bank, uint32_t runIndex);  
static TestResult EEPROM_ReadAndCheck(uint32_t pageStartAddr, MDR_EEPROM_MEM bank, uint32_t runIndex);

//  Interface functions
static void TestInit(void);

static char * TestGetName_Main(void);
static uint32_t TestExec_Main(uint32_t runIndex);
static uint32_t TestCheckResult_Main(uint32_t runIndex);

static char * TestGetName_Info(void);
static uint32_t TestExec_Info(uint32_t runIndex);
static uint32_t TestCheckResult_Info(uint32_t runIndex);

static char * TestResultToString(uint32_t result);


TestInterface TI_EEPROM_PageWRRD_Main = {
  .funcInit             = &TestInit,
  .funcTestExec         = &TestExec_Main,
  .funcCheckResult      = &TestCheckResult_Main,
  .funcResultToString   = &TestResultToString,
  .funcTestName         = &TestGetName_Main
};

TestInterface TI_EEPROM_PageWRRD_Info = {
  .funcInit             = &TestInit,
  .funcTestExec         = &TestExec_Info,
  .funcCheckResult      = &TestCheckResult_Info,
  .funcResultToString   = &TestResultToString,
  .funcTestName         = &TestGetName_Info
};
 
  
//  Interface functions
static void TestInit(void)
{
  pageAddrMain = MDR_EEPROM_PageToAddr(DATA_BLOCK_MAIN, DATA_PAGE_MAIN, MDR_EEPROM_Main);
  pageAddrInfo = MDR_EEPROM_PageToAddr(DATA_BLOCK_INFO, DATA_PAGE_INFO, MDR_EEPROM_Info); 
}

static char * TestGetName_Main(void)
{
  return "Main";
}

static uint32_t TestExec_Main(uint32_t runIndex)
{
  return EEPROM_ClearAndWritePage(pageAddrMain, MDR_EEPROM_Main, runIndex);
}

static uint32_t TestCheckResult_Main(uint32_t runIndex)
{
  return EEPROM_ReadAndCheck(pageAddrMain, MDR_EEPROM_Main, runIndex);
}

static char * TestGetName_Info(void)
{
  return "Info";
}

static uint32_t TestExec_Info(uint32_t runIndex)
{
  return EEPROM_ClearAndWritePage(pageAddrInfo, MDR_EEPROM_Info, runIndex);
}

static uint32_t TestCheckResult_Info(uint32_t runIndex)
{
  return EEPROM_ReadAndCheck(pageAddrInfo, MDR_EEPROM_Info, runIndex);
}

static char * TestResultToString(uint32_t result)
{
  if (result < STATUS_COUNT)
    return resultNames[result];
  else
    return "Unk Err";
}


//  Work functions 
static TestResult EEPROM_WritePage(uint32_t pageStartAddr, MDR_EEPROM_MEM bank, uint32_t runIndex)
{
  uint32_t i = 0;
  uint32_t addr = pageStartAddr;
  uint32_t pageSize = MDR_EEPROM_GetPageSize(bank);
  uint32_t dataWR, dataRD;
  
  for (i = 0; i < pageSize; i += 4)
  {
    dataRD = MDR_EEPROM_Read(addr + i, bank);
    if (dataRD != MDR_EEPROM_CLEAR_VALUE)
      return tst_Err_Erase;
    
    dataWR = GetTestValue(addr + i + runIndex);
    MDR_EEPROM_Write(addr + i, dataWR, bank);
  }
  
  return tst_WriteFinished;
}

static TestResult EEPROM_ClearAndWritePage(uint32_t pageStartAddr, MDR_EEPROM_MEM bank, uint32_t runIndex)
{
  MDR_EEPROM_ErasePage(pageStartAddr, bank);
  return EEPROM_WritePage(pageStartAddr, bank, runIndex);
}

static TestResult EEPROM_ReadAndCheck(uint32_t pageStartAddr, MDR_EEPROM_MEM bank, uint32_t runIndex)
{
  uint32_t i = 0;
  uint32_t addr = pageStartAddr;
  uint32_t pageSize = MDR_EEPROM_GetPageSize(bank);
  uint32_t dataWR, dataRD;
  
  for (i = 0; i < pageSize; i += 4)
  {
    dataWR = GetTestValue(addr + i + runIndex);
    dataRD = MDR_EEPROM_Read(addr + i, bank);
    if (dataRD != dataWR)
      return tst_Err_CheckData;
  }
  
  return tst_OK;
}

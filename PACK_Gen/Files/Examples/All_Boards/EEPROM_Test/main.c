#include <MDR_GPIO.h>
#include <MDR_RST_Clock.h>
#include <MDR_Funcs.h>
#include <MDRB_Buttons.h>
#include <MDRB_LCD.h>

#include "MDR_EEPROM.h"

//----------  Варианты записываемых данных  -------------
// На 8МГц много времени уходит на рассчет MDR_ToPseudoRand(),
// Запись просто индексов происходит значительно быстрее.
#define USE_PSEUDO_RAND_VALUES  1

#if USE_PSEUDO_RAND_VALUES
  #define GetTestValue  MDR_ToPseudoRand
#else
  uint32_t ReturnInput(uint32_t value) { return value; }

  #define GetTestValue  ReturnInput
#endif
 
//--------------  Параметры тактирования  -----------------
// Тест запускается на двух частотах - от HSI и от HSE с максимальным умножением в PLL
#define PLL_MUL   HSE_PLL_MUL_MAX
static MDR_BKP_LOW_RI    BKP_LowRI;
static MDR_EEPROM_DELAY  EEPROM_Delay;

static bool       activeFreqIsHSI;  //  Текущее тактирование

//-------  Задержка от дребезга контактов в кнопках  ------
#define DEBOUNCE_MS         5

//------------  Последняя страница в банках памяти и Main Info  -----------
#define EEPROM_BANK_COUNT 2
static MDR_EEPROM_PAGE  endPage[EEPROM_BANK_COUNT] = {EEPROM_Page32, EEPROM_Page1};

//------------  Функции работы с памятью EEPROM  ---------
bool CheckClearAllPages(MDR_EEPROM_MEM bank);
bool ReadAllPagesAndCheckData(MDR_EEPROM_MEM bank);
bool EraseAllPagesAndCheck(MDR_EEPROM_MEM bank);
bool WriteAllPagesAndCheck(MDR_EEPROM_MEM bank);

//------------  Статус выполения теста  -----------
typedef enum {
  tst_OK,
  tst_Err_EraseFull_Info,
  tst_Err_EraseFull_Main,
  tst_Err_CheckData,
  tst_Err_HoldData,
  tst_Err_ErasePages,
  tst_Started,
} TestResult;

#define STATUS_COUNT    7
static char* resultNames[STATUS_COUNT] = {"Success", "E_EraseF_Info", "E_EraseF_Main", "E_CheckData", "E_HoldData", "E_ErasePages", "Started..."};

//------------- Варианты тестов и их параметры--------------
typedef enum {
  test_Main_HoldInfo,
  test_Info_HoldMain,
  test_EraseFull
} TestActive;

static TestActive activeTest;
static char* testNames[STATUS_COUNT] = {"MainWR", "InfoWR", "Erase"};

//  Функции самих тестов
TestResult Test_BankWriteErase(MDR_EEPROM_MEM testBank, MDR_EEPROM_MEM holdDataBank);
TestResult Test_EraseModes(void);

//--------------  Настройки LCD Экрана  -----------------
#ifdef LCD_PIN_CONFLICT  
  #define LCD_PIN_CAPTURE   MDRB_LCD_CapturePins()
  #define LCD_PIN_RELEASE   MDRB_LCD_ReleasePins()
  
#else
  #define LCD_PIN_CAPTURE
  #define LCD_PIN_RELEASE
#endif

#define LCD_LINE_INFO       3
#define LCD_LINE_RESULT     5

void LCD_ShowActiveTest(TestActive testItem);
void LCD_ShowTestResult(TestResult result);

//  ------------------- Программа -------------------
int main(void)
{
  TestResult result;
  uint32_t CPU_FreqHz;
  
 // MDR_DebugerProtectDelay();
   
  //  Сброс блока, тактирование от HSI
  MDR_RST_ResetBlock_def();

  // Инициализация экрана для вывода статуса
  MDRB_LCD_Init(HSI_FREQ_HZ);
  
  // Инициализация кнопок
  MDRB_Buttons_Init(DEBOUNCE_MS, HSI_FREQ_HZ);

  // Оторабжение текущего теста
  activeTest = test_Main_HoldInfo;  
  LCD_ShowActiveTest(activeTest);
  
  // Тактирование от HSI и выставление задержек
  activeFreqIsHSI = true;
  MDR_EEPROM_Init(HSI_FREQ_HZ);
  
  //  Параметры для тактирования на максимальной частоте
  BKP_LowRI = MDR_FreqCPU_ToLowRI(HSE_FREQ_HZ * (HSE_PLL_MUL_MAX) + 1);  
  EEPROM_Delay = MDR_FreqCPU_ToDelayEEPROM(HSE_FREQ_HZ * (HSE_PLL_MUL_MAX) + 1);
  
  while (1)
  {
    //  Смена частоты HSI или HSE_Max
    if (MDRB_BntClicked_Up(true))
    {
      if (!activeFreqIsHSI)
        MDR_CPU_SetClock_HSI_def();
      else
        MDR_CPU_SetClock_HSE_PLL_def(MDR_Off, PLL_MUL, BKP_LowRI, EEPROM_Delay);
      
      CPU_FreqHz = MDR_CPU_GetFreqHz(true);
      MDR_EEPROM_Init(CPU_FreqHz);
      MDRB_Buttons_ChangeFreqCPU(DEBOUNCE_MS, CPU_FreqHz);
      MDRB_LCD_ChangeFreqCPU(CPU_FreqHz);
      
      LCD_ShowActiveTest(activeTest);
      activeFreqIsHSI = !activeFreqIsHSI;
    }    
    //  Смена теста
    if (MDRB_BntClicked_Down(true))
    {
      if (activeTest != test_EraseFull)
        ++activeTest;
      else
        activeTest = test_Main_HoldInfo;
      
      LCD_ShowActiveTest(activeTest);
    }
    //  Запуск теста
    if (MDRB_BntClicked_Right(true))
    {
      LCD_ShowTestResult(tst_Started);
      switch (activeTest) 
      {
        case test_Main_HoldInfo:
          result = Test_BankWriteErase(MDR_EEPROM_Main, MDR_EEPROM_Info);
          break;
        case test_Info_HoldMain:
          result = Test_BankWriteErase(MDR_EEPROM_Info, MDR_EEPROM_Main);
          break;
        case test_EraseFull:
          result = Test_EraseModes();
      }
      LCD_ShowTestResult(result);
    }
  }
}

TestResult Test_BankWriteErase(MDR_EEPROM_MEM testBank, MDR_EEPROM_MEM holdDataBank)
{
  //  Стирание основной и информационной памяти
  MDR_EEPROM_EraseFull(EEPROM_Erase_MainAndInfo);
  //  Проверка Info стрелась
  if (!CheckClearAllPages(MDR_EEPROM_Info))
    return tst_Err_EraseFull_Info; 
  //  Проверка main стрелась
  if (!CheckClearAllPages(MDR_EEPROM_Main))
    return tst_Err_EraseFull_Main;   

  //  Запись данных для хранения 
  if (!WriteAllPagesAndCheck(holdDataBank))
    return tst_Err_CheckData;
  
  // Запись и стирание тестируемого банка памяти
  if (!WriteAllPagesAndCheck(testBank))
    return tst_Err_CheckData;  
  if (!EraseAllPagesAndCheck(testBank))
    return tst_Err_ErasePages;
  
  // Проверка сохранности данных
  if (!ReadAllPagesAndCheckData(holdDataBank))
    return tst_Err_HoldData;
  
  return tst_OK;
}

TestResult Test_EraseModes(void)
{
  // Запись данных в Main память
  if (!WriteAllPagesAndCheck(MDR_EEPROM_Main))
    return tst_Err_CheckData;
  // Запись данных в Info память
  if (!WriteAllPagesAndCheck(MDR_EEPROM_Info))
    return tst_Err_CheckData;

  // ==== 1 - Стирание только основной =======
  MDR_EEPROM_EraseFull(EEPROM_Erase_Main);
  if (!CheckClearAllPages(MDR_EEPROM_Main))
    return tst_Err_EraseFull_Main;   
  
  // Проверка сохранности данных в Info
  if (!ReadAllPagesAndCheckData(MDR_EEPROM_Info))
    return tst_Err_HoldData;  
  
  // ==== 2 - Стирание Main и Info =======
  // Запись данных в Main память
  if (!WriteAllPagesAndCheck(MDR_EEPROM_Main))
    return tst_Err_CheckData;  
  
  //  Стирание
  MDR_EEPROM_EraseFull(EEPROM_Erase_MainAndInfo);
  
  //  Проверка Info стрелась
  if (!CheckClearAllPages(MDR_EEPROM_Info))
    return tst_Err_EraseFull_Info; 
  //  Проверка main стрелась
  if (!CheckClearAllPages(MDR_EEPROM_Main))
    return tst_Err_EraseFull_Main;

  return tst_OK;  
}


//==========    Write, Read and Check ===============
static void WritePage(MDR_EEPROM_PAGE page, MDR_EEPROM_MEM bank)
{
  uint32_t i = 0;
  uint32_t addr = MDR_EEPROM_PageToAddr(page);
  
  //  bank - чтобы данные в Info и Main памяти не совпадали
  for (i = 0; i < MDR_EEPROM_PAGE_SIZE; i += 4)
    MDR_EEPROM_Write(addr + i, GetTestValue(addr + i + (uint32_t)bank), bank);    
}

static void WriteAllPages(MDR_EEPROM_MEM bank)
{
  MDR_EEPROM_PAGE page; 
  
  for (page = EEPROM_Page1; page <= endPage[bank]; ++page)
    WritePage(page, bank);
}

static bool ReadPageAndCheckData(MDR_EEPROM_PAGE page, MDR_EEPROM_MEM bank)
{
  uint32_t i = 0;
  uint32_t addr = MDR_EEPROM_PageToAddr(page);
  uint32_t data;
  
  for (i = 0; i < MDR_EEPROM_PAGE_SIZE; i += 4)
  {
    data = GetTestValue(addr + i + (uint32_t)bank);
    if (MDR_EEPROM_Read(addr + i, bank) != data)
      return false;
  }
  
  return true;
}

bool ReadAllPagesAndCheckData(MDR_EEPROM_MEM bank)
{
  MDR_EEPROM_PAGE page;  
   
  for (page = EEPROM_Page1; page <= endPage[bank]; ++page)
    if (!ReadPageAndCheckData(page, bank))
      return false;
  
  return true;
}

bool WriteAllPagesAndCheck(MDR_EEPROM_MEM bank)
{
  WriteAllPages(bank);
  return ReadAllPagesAndCheckData(bank);
}

//==========    Clear Pages and check ===============
static bool CheckClearPage(MDR_EEPROM_PAGE page, MDR_EEPROM_MEM bank)
{
  uint32_t i = 0;
  uint32_t addr = MDR_EEPROM_PageToAddr(page);
  
  for (i = 0; i < MDR_EEPROM_PAGE_SIZE; i += 4)
    if (MDR_EEPROM_Read(addr + i, bank) != MDR_EEPROM_CLEAR_VALUE)
      return false;
    
  return true;
}

bool CheckClearAllPages(MDR_EEPROM_MEM bank)
{
  MDR_EEPROM_PAGE page;  
   
  for (page = EEPROM_Page1; page <= endPage[bank]; ++page)
    if (!CheckClearPage(page, bank))
      return false;
  
  return true;  
}

bool EraseAllPagesAndCheck(MDR_EEPROM_MEM bank)
{
  MDR_EEPROM_PAGE page;  
   
  for (page = EEPROM_Page1; page <= endPage[bank]; ++page)  
    MDR_EEPROM_ErasePage(page, bank);
  
  return CheckClearAllPages(bank);  
}

void LCD_ShowActiveTest(TestActive testItem)
{
  static char mess[64];  
  uint32_t cpuFreqHz = (uint32_t)MDR_CPU_GetFreqHz(false) / 1000000;
  
  LCD_PIN_CAPTURE;
  
#ifndef LCD_IS_7SEG_DISPLAY   
  sprintf(mess, "%s, %dMHz", testNames[testItem], cpuFreqHz);
  MDRB_LCD_Print(mess, LCD_LINE_INFO);
#else
//  //  Вывод источника тактирования
//  sprintf(mess, "%d %d", (uint8_t)activeClockSrc, cpuFreqHz);
//  MDRB_LCD_Print(mess, 0);
#endif 
  
  LCD_PIN_RELEASE; 
}

void LCD_ShowTestResult(TestResult result)
{
  LCD_PIN_CAPTURE;
  
#ifndef LCD_IS_7SEG_DISPLAY   
  MDRB_LCD_Print(resultNames[result], LCD_LINE_RESULT);
#else
  MDRB_LCD_Print((uint32_t)result, 0);
#endif 
  
  LCD_PIN_RELEASE;
}




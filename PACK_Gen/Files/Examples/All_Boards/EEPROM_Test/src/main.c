#include <MDR_GPIO.h>
#include <MDR_RST_Clock.h>
#include <MDR_Funcs.h>
#include <MDRB_Buttons.h>
#include <MDRB_LCD.h>
#include <MDR_EEPROM.h>

#include <EEPROM_PageFuncs.h>

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

#ifndef LCD_IS_7SEG_DISPLAY 
  #define STATUS_COUNT    7
  static char* resultNames[STATUS_COUNT] = {"Success", "E_EraseF_Info", "E_EraseF_Main", "E_CheckData", "E_HoldData", "E_ErasePages", "Started..."};
#endif

//------------- Варианты тестов и их параметры--------------
typedef enum {
  test_Main_HoldInfo,
  test_Info_HoldMain,
  test_EraseFull
} TestActive;

static TestActive activeTest;
#ifndef LCD_IS_7SEG_DISPLAY 
  static char* testNames[] = {"MainWR", "InfoWR", "Erase"};
#endif

//  !!! ДЛЯ 1986ВЕ4У (вероятно и для 1986ВК214,1986ВК234)!!!
//  Работа со страницами информационной памяти работает только в первом блоке. 
//  Со страницами в остальных блоках добиться работоспособности пока не удалось!
  
//  Функции самих тестов
#ifdef MDR_EEPROM_18MHz
  TestResult Test_EraseCM0_T1(void);
  TestResult Test_EraseCM0_T2(void); 
#else  
  TestResult Test_BankWriteErase(MDR_EEPROM_MEM testBank, MDR_EEPROM_MEM holdDataBank);
  TestResult Test_EraseModes(void);
#endif

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
      
#ifndef MDR_EEPROM_18MHz      
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
      
#else
      result = Test_EraseCM0_T1();
      LCD_ShowTestResult(result);
      
      result = Test_EraseCM0_T2();
      LCD_ShowTestResult(result);
      
#endif
    }
  }
}

#ifdef MDR_EEPROM_18MHz
  TestResult Test_EraseCM0_T2(void)
  {
    uint32_t addr, valRD;
    MDR_EEPROM_PAGE page;
    MDR_EEPROM_BLOCK block;  
    MDR_EEPROM_MEM bank = MDR_EEPROM_Info;
    
    uint32_t errCnt, clrCnt;
    
    MDR_EEPROM_EraseFull(EEPROM_EraseFull_MainAndInfo);  
    
    
    errCnt = clrCnt = 0;
    for (block = EEPROM_Block1; block <= EEPROM_Block4; ++block)
      for (page = EEPROM_Page1; page <= EEPROM_Page4; ++page)
      {
        addr = MDR_EEPROM_PageToAddr(block, page, bank);
        MDR_EEPROM_Write(addr, addr, bank);
        valRD = MDR_EEPROM_Read(addr, bank);
        if (valRD != addr)
          ++errCnt;
        if (valRD == MDR_EEPROM_CLEAR_VALUE)
          ++clrCnt;
      }
      
    if ((clrCnt + errCnt) == 0)
      return tst_OK;
    else
      return tst_Err_HoldData;
  }


  TestResult Test_EraseCM0_T1(void)
  {
    //WriteAllPages(MDR_EEPROM_Main);
    //WriteAllPages(MDR_EEPROM_Info);
    //  Стирание основной и информационной памяти
    MDR_EEPROM_EraseFull(EEPROM_EraseFull_MainAndInfo);

    //  Проверка main стрелась
    if (!CheckClearAllPages(MDR_EEPROM_Main))
      return tst_Err_EraseFull_Main;   
    
    //  Проверка Info стрелась
    if (!CheckClearAllPages(MDR_EEPROM_Info))
      return tst_Err_EraseFull_Info;

    //=========== 
    //WriteAllPages(MDR_EEPROM_Main);
    WriteAllPages(MDR_EEPROM_Info);

  //  if (!ReadAllPagesAndCheckData(MDR_EEPROM_Main))
  //    return tst_Err_HoldData;
    
    ReadAllPagesAndCheckData(MDR_EEPROM_Info);
    
    //if (!ReadAllPagesAndCheckData(MDR_EEPROM_Info))
  //    return tst_Err_HoldData;
    
    MDR_EEPROM_EraseFull(EEPROM_EraseFull_Main);
     
    //  Проверка main стрелась
    if (!CheckClearAllPages(MDR_EEPROM_Main))
      return tst_Err_EraseFull_Main;   
    
    //  Проверка Info сохранилась
    if (!ReadAllPagesAndCheckData(MDR_EEPROM_Info))
      return tst_Err_HoldData;
    
    return tst_OK;
  }

#else


  TestResult Test_BankWriteErase(MDR_EEPROM_MEM testBank, MDR_EEPROM_MEM holdDataBank)
  {
    //  Стирание основной и информационной памяти
    MDR_EEPROM_EraseFull(EEPROM_EraseFull_MainAndInfo);
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
    MDR_EEPROM_EraseFull(EEPROM_EraseFull_Main);
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
    MDR_EEPROM_EraseFull(EEPROM_EraseFull_MainAndInfo);
    
    //  Проверка Info стрелась
    if (!CheckClearAllPages(MDR_EEPROM_Info))
      return tst_Err_EraseFull_Info; 
    //  Проверка main стрелась
    if (!CheckClearAllPages(MDR_EEPROM_Main))
      return tst_Err_EraseFull_Main;

    return tst_OK;  
  }
#endif

void LCD_ShowActiveTest(TestActive testItem)
{
  static char mess[64];
  uint32_t cpuFreqHz = (uint32_t)MDR_CPU_GetFreqHz(false) / 1000000;
  
  LCD_PIN_CAPTURE;
  
#ifndef LCD_IS_7SEG_DISPLAY
  sprintf(mess, "%s, %dMHz", testNames[testItem], cpuFreqHz);
  MDRB_LCD_Print(mess, LCD_LINE_INFO);
  
#else
  sprintf(mess, "%d %d", (uint8_t)testItem, cpuFreqHz);
  MDRB_LCD_Print(mess);
  
#endif 
  
  LCD_PIN_RELEASE; 
}

void LCD_ShowTestResult(TestResult result)
{
  LCD_PIN_CAPTURE;
  
#ifndef LCD_IS_7SEG_DISPLAY   
  MDRB_LCD_Print(resultNames[result], LCD_LINE_RESULT);
  
#else
  static char mess[10];
  sprintf(mess, "%d", (uint8_t)result);
  MDRB_LCD_Print(mess);
  
#endif 
  
  LCD_PIN_RELEASE;
}





#include <MDR_GPIO.h>
#include <MDR_RST_Clock.h>
#include <MDR_Funcs.h>
#include <MDRB_Buttons.h>
#include <MDRB_LCD.h>
#include <MDR_BKP_RTC.h>
#include <MDR_SysTimer.h>

#include <MDR_EEPROM.h>


//----------  Варианты записываемых данных  -------------
// На 8МГц много времени уходит на рассчет MDR_ToPseudoRand(),
// Запись просто индексов происходит значительно быстрее.
#define USE_PSEUDO_RAND_VALUES  0

#if USE_PSEUDO_RAND_VALUES
  #define GetTestValue  MDR_ToPseudoRand
#else
  uint32_t ReturnInput(uint32_t value) { return value; }

  #define GetTestValue  ReturnInput
#endif
 
//--------------  Параметры тактирования  -----------------
#define PLL_MUL   HSE_PLL_MUL_MAX

//-------  Задержка от дребезга контактов в кнопках  ------
#define DEBOUNCE_MS         5

//------------  Статус выполения теста  -----------
typedef enum {
  tst_OK,
  tst_Err_Erase,
  tst_Err_CheckData,
  tst_WriteStarted,
  tst_WriteFinished,
  tst_ReadStarted
} TestResult;

#ifndef LCD_IS_7SEG_DISPLAY
  #define STATUS_COUNT    6
  static char* resultNames[STATUS_COUNT] = {"Success", "EraseFault", "DataFault", "WriteStarted...", "WriteCompleted", "ReadStarted..."};
#endif

//------------- Варианты тестов и их параметры--------------
static MDR_EEPROM_MEM   activeBank = EEPROM_IFREN_Main;

#ifndef MDR_EEPROM_36MHz
  //  Страницы по 4КБ (Cortex M1, M3)
  #define DATA_PAGE_MAIN   EEPROM_Page7  // Любая из 32-х страниц, кроме 0-й страницы - там лежит сама эта программа
  #define DATA_PAGE_INFO   EEPROM_Page1  // Info памяти всего одна страница
#else
  //  Страницы по 512Б (Cortex M0)
  #define DATA_PAGE_MAIN   MDR_EEPROM_LastPage_Main  // Любая, например последняя страница.
  // Функция стирания работает только на первые 4-ре страницы информационной памяти - до адреса 0х800. (вероятно баг)
  // Но в Info памяти лежит начальный загрузчик на 341 32-битное слово, и данная программа его затрет.
  // Чтобы FLM заново перепрописывал загрузчик необходимо работать с 1-й страницей. 
  // (Необходимо затереть код выставления FPOR, тогда FLM перепрописывает bootloader)
  #define DATA_PAGE_INFO   EEPROM_Page1
#endif

#ifndef LCD_IS_7SEG_DISPLAY
  #define EEPROM_BANK_COUNT 2
  static char* bankNames[STATUS_COUNT] = {"Main", "Info"};
#endif
  
// Сам тест записи - чтения данных в страницу
TestResult WritePage(MDR_EEPROM_PAGE page, MDR_EEPROM_MEM bank, uint32_t runIndex);
TestResult ReadPageAndCheckData(MDR_EEPROM_PAGE page, MDR_EEPROM_MEM bank, uint32_t runIndex);

//--------------  BKP  -----------------
#define RUN_IND_Main  MDR_BKP_REG0
#define RUN_IND_Info  MDR_BKP_REG1
#define RUN_IND_SEL   MDR_BKP_REGs

#define RUN_IND_MAX   20

//  Регистры BKP используются для сохранения дополнительных инкрементов к данным.
//  Значение инкрементируется с каждой операцией записи и используется для того, чтобы данные отличались от записи к записи.
//  Энергонезависимость регистров позволяет верифицировать ранее записанную память после сброса по reset и при наличии батарейки после сброса по питанию.
void     IncRunIndex(RUN_IND_SEL selReg);
uint32_t GetRunIndex(RUN_IND_SEL selReg);
  
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

void LCD_ShowActiveBank(MDR_EEPROM_MEM memBank);
void LCD_ShowTestResult(TestResult result);

//  ------------------- Системный таймер -------------------
//  В функциях EEPROM стоит выключение обработки прерываний.
//  Включаем прерывания от системного таймера, чтобы убедиться что прерывания выключаются и не мешают работе с EEPROM.
//  Если прерывание сработает когда EEPROM находится в режиме регистрового доступа (доступ к памяти со стороны ядра не возможен), 
//  то будет попытка выборки адреса обработчика SysTick_Handler в таблице векторов, которая расположена в этом EEPROM. Это приведет к HardFault.
void SysTick_Handler(void);

//  ------------------- Программа -------------------
int main(void)
{
  TestResult result;
  uint32_t CPU_FreqHz;
  MDR_BKP_LOW_RI    BKP_LowRI;
  MDR_EEPROM_DELAY  EEPROM_Delay;
  
 // MDR_DebugerProtectDelay();

  //  Тактирование на максимальной частоте
  BKP_LowRI = MDR_FreqCPU_ToLowRI(HSE_FREQ_HZ * (HSE_PLL_MUL_MAX) + 1);  
  EEPROM_Delay = MDR_FreqCPU_ToDelayEEPROM(HSE_FREQ_HZ * (HSE_PLL_MUL_MAX) + 1);
  MDR_CPU_SetClock_HSE_PLL_def(MDR_Off, PLL_MUL, BKP_LowRI, EEPROM_Delay);
  //  Текущая частота
  CPU_FreqHz = MDR_CPU_GetFreqHz(true);
  
  // Инициализация экрана для вывода статуса
  MDRB_LCD_Init(CPU_FreqHz);
  // Инициализация кнопок
  MDRB_Buttons_Init(DEBOUNCE_MS, CPU_FreqHz);
  // Тактирование и выставление задержек
  MDR_EEPROM_Init(CPU_FreqHz);

  //  Включение BKP и валидация содержимого регистров, от первоначальных случайных значений.
  //  Значения регистров сохраняются при ресете. При наличии батарейки и при сбросе по питанию.
  MDR_BKP_ClockOn();

  // Отображение текущеего банка памяти
  LCD_ShowActiveBank(activeBank);
  
  //  Включаем прерывания от системного таймера.
  MDR_SysTimerStart_ms(1, CPU_FreqHz);
  
  while (1)
  {
    //  Смена банка памяти
    if (MDRB_BntClicked_Up(true))
    {
      if (activeBank != EEPROM_IFREN_Main)
        activeBank = EEPROM_IFREN_Main;
      else
        activeBank = EEPROM_IFREN_Info;
      
      LCD_ShowActiveBank(activeBank);
    }    
    
    //  Запись банка памяти
    if (MDRB_BntClicked_Right(true))    
    {
      LCD_ShowTestResult(tst_WriteStarted);
      
      MDR_EEPROM_DisableIRQ();
      if (activeBank == EEPROM_IFREN_Main) 
      {
        MDR_EEPROM_ErasePage(DATA_PAGE_MAIN, MDR_EEPROM_Main);      
        IncRunIndex(RUN_IND_Main);
        result = WritePage(DATA_PAGE_MAIN, MDR_EEPROM_Main, GetRunIndex(RUN_IND_Main));
      }
      else
      {
        MDR_EEPROM_ErasePage(DATA_PAGE_INFO, MDR_EEPROM_Info);      
        IncRunIndex(RUN_IND_Info);
        result = WritePage(DATA_PAGE_INFO, MDR_EEPROM_Info, GetRunIndex(RUN_IND_Info));
      }
      MDR_EEPROM_RestoreIRQ();
      
      if (result == tst_OK )
        LCD_ShowTestResult(tst_WriteFinished);
      else
        LCD_ShowTestResult(result);
    }
    
    //  Верификация банка памяти
    if (MDRB_BntClicked_Down(true))
    {
      LCD_ShowTestResult(tst_ReadStarted);
      
      MDR_EEPROM_DisableIRQ();
      if (activeBank == EEPROM_IFREN_Main) 
        result = ReadPageAndCheckData(DATA_PAGE_MAIN, MDR_EEPROM_Main, GetRunIndex(RUN_IND_Main));
      else
        result = ReadPageAndCheckData(DATA_PAGE_INFO, MDR_EEPROM_Info, GetRunIndex(RUN_IND_Info));
      MDR_EEPROM_RestoreIRQ();

      LCD_ShowTestResult(result);
    }
  }
}

void IncRunIndex(RUN_IND_SEL selReg)
{
  uint32_t value = MDR_BKP_GetReg(selReg);
  ++value;
  if (value > RUN_IND_MAX)
    value = 0;
  
  MDR_BKP_SetReg(selReg, value);
}

uint32_t GetRunIndex(RUN_IND_SEL selReg)
{
  return MDR_BKP_GetReg(selReg);
}

void SysTick_Handler(void)
{
  volatile static uint32_t count;
  ++count;
}


//==========    Write, Read and Check ===============
TestResult WritePage(MDR_EEPROM_PAGE page, MDR_EEPROM_MEM bank, uint32_t runIndex)
{
  uint32_t i = 0;
  uint32_t addr = MDR_EEPROM_PageToAddr(page);
  uint32_t dataWR, dataRD;
  
  for (i = 0; i < MDR_EEPROM_PAGE_SIZE; i += 4)
  {
    dataRD = MDR_EEPROM_Read(addr + i, bank);
    if (dataRD != MDR_EEPROM_CLEAR_VALUE)
      return tst_Err_Erase;
    
    dataWR = GetTestValue(addr + i + runIndex);
    MDR_EEPROM_Write(addr + i, dataWR, bank);
  }
  
  return tst_OK;
}

TestResult ReadPageAndCheckData(MDR_EEPROM_PAGE page, MDR_EEPROM_MEM bank, uint32_t runIndex)
{
  uint32_t i = 0;
  uint32_t addr = MDR_EEPROM_PageToAddr(page);
  uint32_t dataWR, dataRD;
  
  for (i = 0; i < MDR_EEPROM_PAGE_SIZE; i += 4)
  {
    dataWR = GetTestValue(addr + i + runIndex);
    dataRD = MDR_EEPROM_Read(addr + i, bank);
    if (dataRD != dataWR)
      return tst_Err_CheckData;
  }
  
  return tst_OK;
}

//==========    LCD Show ===============
void LCD_ShowActiveBank(MDR_EEPROM_MEM memBank)
{
  static char mess[64];  
  uint32_t cpuFreqHz = (uint32_t)MDR_CPU_GetFreqHz(false) / 1000000;
  
  LCD_PIN_CAPTURE;
  
#ifndef LCD_IS_7SEG_DISPLAY   
  sprintf(mess, "%s, %dMHz", bankNames[memBank], cpuFreqHz);
  MDRB_LCD_Print(mess, LCD_LINE_INFO);
  MDRB_LCD_ClearLine(LCD_LINE_RESULT);
#else
  //  Вывод источника тактирования
  sprintf(mess, "%d", (uint8_t)memBank);
  MDRB_LCD_Print(mess, 0);
#endif 
  
  LCD_PIN_RELEASE; 
}

void LCD_ShowTestResult(TestResult result)
{
  LCD_PIN_CAPTURE;
  
#ifndef LCD_IS_7SEG_DISPLAY   
  MDRB_LCD_Print(resultNames[result], LCD_LINE_RESULT);
#else
  static char mess[LCD_SCREEN_WIDTH];
  sprintf(mess, "%d  %d", (uint8_t)activeBank, (uint8_t)result);
  MDRB_LCD_Print(mess, 0);
#endif 
  
  LCD_PIN_RELEASE;
}




#include <MDR_GPIO.h>
#include <MDR_RST_Clock.h>
#include <MDR_Funcs.h>
#include <MDRB_Buttons.h>
#include <MDRB_LCD.h>
#include <MDR_BKP_RTC.h>
#include <MDR_SysTimer.h>

#include <MDR_EEPROM.h>

#include "test_EEPROM_Defs.h"
#include "test_EEPROM_PageWRRD.h"
#include "test_EEPROM_BuffWRRD.h"


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
#define DEBOUNCE_MS   5
  
//----------  TestInterfaces ------------
#define TEST_COUNT    4
TestInterface * pTI[] = {&TI_EEPROM_PageWRRD_Main, &TI_EEPROM_PageWRRD_Info, &TI_EEPROM_Buff_Main, &TI_EEPROM_Buff_Main};

uint32_t activeTest;


//--------------  BKP  -----------------
#define RUN_IND_Main  MDR_BKP_REG0
#define RUN_IND_Info  MDR_BKP_REG1
#define RUN_IND_SEL   MDR_BKP_REGs

MDR_BKP_REGs  BKP_RunIndReg[TEST_COUNT] = {MDR_BKP_REG0, MDR_BKP_REG1, MDR_BKP_REG0, MDR_BKP_REG1};

#define RUN_IND_MAX   20

//  Регистры BKP используются для сохранения дополнительных инкрементов к данным.
//  Значение инкрементируется с каждой операцией записи и используется для того, чтобы данные отличались от записи к записи.
//  Энергонезависимость регистров позволяет верифицировать ранее записанную память после сброса по reset и при наличии батарейки после сброса по питанию.
uint32_t IncRunIndex(uint32_t testInd);
uint32_t GetRunIndex(uint32_t testInd);
  
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

void LCD_ShowTestName(uint32_t testInd);
void LCD_ShowTestResult(uint32_t result);

#define LCD_SHOW_EXECUTING      100
#define LCD_SHOW_CHECKING       101

//  ------------------- Системный таймер -------------------
//  Используем прерывания от системного таймера, чтобы убедиться в работоспособности MDR_EEPROM_DisableIRQ().
//  Если прерывание сработает когда EEPROM находится в режиме регистрового доступа (доступ к памяти со стороны ядра не возможен), 
//  то будет попытка выборки адреса обработчика SysTick_Handler в таблице векторов, которая расположена в этом EEPROM. Это приведет к HardFault.
void SysTick_Handler(void);


//  ------------------- Программа -------------------
int main(void)
{
  uint32_t result;
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
  activeTest = 0;
  pTI[activeTest]->funcInit();
  LCD_ShowTestName(activeTest);
  
  //  Включаем прерывания от системного таймера.
  MDR_SysTimerStart_ms(1, CPU_FreqHz);
  
  while (1)
  {
    //  Смена теста
    if (MDRB_BntClicked_Up(true))
    {
      ++activeTest;
      if (activeTest >= TEST_COUNT)
        activeTest = 0;
            
      pTI[activeTest]->funcInit();
      
      LCD_ShowTestName(activeTest);
    }    
    
    //  Исполнение теста
    if (MDRB_BntClicked_Right(true))    
    {
      LCD_ShowTestResult(LCD_SHOW_EXECUTING);
      
      MDR_EEPROM_DisableIRQ();      
      //  Запуск теста
      result = pTI[activeTest]->funcTestExec(IncRunIndex(activeTest));
      MDR_EEPROM_RestoreIRQ();
      
      LCD_ShowTestResult(result);
    }
    
    //  Проверка результатов теста
    if (MDRB_BntClicked_Down(true))
    {
      LCD_ShowTestResult(LCD_SHOW_CHECKING);
      
      MDR_EEPROM_DisableIRQ();      
      //  Проверка
      result = pTI[activeTest]->funcCheckResult(GetRunIndex(activeTest));      
      MDR_EEPROM_RestoreIRQ();

      LCD_ShowTestResult(result);
    }
  }
}

uint32_t IncRunIndex(uint32_t testInd)
{
  uint32_t value = MDR_BKP_GetReg(BKP_RunIndReg[testInd]);
  ++value;
  if (value > RUN_IND_MAX)
    value = 0;
  
  MDR_BKP_SetReg(BKP_RunIndReg[testInd], value);
  return value;
}

uint32_t GetRunIndex(uint32_t testInd)
{
  return MDR_BKP_GetReg(BKP_RunIndReg[testInd]);
}

void SysTick_Handler(void)
{
  volatile static uint32_t count;
  ++count;
}

//==========    LCD Show ===============
void LCD_ShowTestName(uint32_t testInd)
{
  static char mess[64];  
  uint32_t cpuFreqHz = (uint32_t)MDR_CPU_GetFreqHz(false) / 1000000;
  
  LCD_PIN_CAPTURE;
  
#ifndef LCD_IS_7SEG_DISPLAY   
  
  sprintf(mess, "%s, %dMHz", pTI[testInd]->funcTestName(), cpuFreqHz);  
  MDRB_LCD_Print(mess, LCD_LINE_INFO);
  MDRB_LCD_ClearLine(LCD_LINE_RESULT);
#else
  //  Вывод источника тактирования
  sprintf(mess, "%d", (uint8_t)testInd);
  MDRB_LCD_Print(mess, 0);
#endif 
  
  LCD_PIN_RELEASE; 
}

void LCD_ShowTestResult(uint32_t result)
{
  LCD_PIN_CAPTURE;
  
#ifndef LCD_IS_7SEG_DISPLAY
  if (result == LCD_SHOW_EXECUTING)
    MDRB_LCD_Print("Executing...", LCD_LINE_RESULT);
  else if (result == LCD_SHOW_CHECKING)
    MDRB_LCD_Print("Checking...", LCD_LINE_RESULT);  
  else
    MDRB_LCD_Print(pTI[activeTest]->funcResultToString(result), LCD_LINE_RESULT);
#else
  static char mess[LCD_SCREEN_WIDTH];
    
  sprintf(mess, "%d  %d", (uint8_t)activeTest, (uint8_t)result);
  MDRB_LCD_Print(mess, 0);
#endif 
  
  LCD_PIN_RELEASE;
}




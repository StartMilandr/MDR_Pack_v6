#include <MDR_RST_Clock.h>
#include <MDR_ADC.h>
#include <MDRB_LCD.h>
#include <MDRB_Buttons.h>
#include <MDR_SysTimer.h>

#include "ADC_cfg.h"
#include "test_ADC_Interfs.h"
#include "MDR_PER_Clock.h"

//  ИСПРАВИТЬ запятые в testStack в соответствие с выбором тестов, доступных для переключения.
//  Удобней запускать по паре тестов за раз (чтобы сравнивать поведение).
#define USE_TEST_CYCLICK_ONE_CHANNEL      1
#define USE_TEST_CYCLICK_SEL_CHANNELS     1
#define USE_TEST_MANUAL_ONE_CHANNEL       1
#define USE_TEST_MANUAL_SEL_CHANNELS      1
#define USE_TEST_MANUAL_SYNC_ONE_CHANNEL  1
#define USE_TEST_MANUAL_SYNC_SEL_CHANNEL  1

#define BTN_DEBOUNCE_MS   20

void ADC_IRQHandler(void);

//  Список доступных тестов - вариантов использования АЦП
#ifdef MDR_HAS_ADC2
static  TestInterface *testStack[] = {
  
    #if USE_TEST_CYCLICK_ONE_CHANNEL
      //  Запуск непрерывных измерений для выбранного канала, считывание в IRQ. (доступны сигналы термосенсора)
      &TI_ADC1_CyclicOneChannel,  &TI_ADC2_CyclicOneChannel
    #endif
    #if USE_TEST_CYCLICK_SEL_CHANNELS
      //  Запуск непрерывных измерений для каналов заданных маской, считывание в IRQ.
      , &TI_ADC1_CyclicSelChannels, &TI_ADC2_CyclicSelChannels
    #endif
    #if USE_TEST_MANUAL_ONE_CHANNEL
      //  Запуск единичных измерений для выбранного канала. (доступны сигналы термосенсора)
      , &TI_ADC1_ManualOneChannel,  &TI_ADC2_ManualOneChannel
    #endif
    #if USE_TEST_MANUAL_SEL_CHANNELS
      //  Запуск единичных измерений для каналов заданных маской.
      , &TI_ADC1_ManualSelChannels,  &TI_ADC2_ManualSelChannels
    #endif
    #if USE_TEST_MANUAL_SYNC_ONE_CHANNEL
      , &TI_ADC12_SyncroOneChannel
    #endif
    #if USE_TEST_MANUAL_SYNC_SEL_CHANNEL
      , &TI_ADC12_SyncroSelChannel
    #endif
    };
#else
static  TestInterface *testStack[] = {
  
    #if USE_TEST_CYCLICK_ONE_CHANNEL
      &TI_ADC1_CyclicOneChannel
    #endif
    #if USE_TEST_CYCLICK_SEL_CHANNELS
      , &TI_ADC1_CyclicSelChannels
    #endif
    #if USE_TEST_MANUAL_ONE_CHANNEL
      , &TI_ADC1_ManualOneChannel
    #endif
    #if USE_TEST_MANUAL_SEL_CHANNELS
      , &TI_ADC1_ManualSelChannels
    #endif
    };  
#endif

static uint32_t activeTest = 0;

static bool  timerStarted = false;
static bool  startByTimer = false;
    
void SysTick_Handler(void);
    
int main(void)
{
  uint32_t freqCPU_Hz;
  uint32_t testCount = sizeof(testStack)/sizeof(testStack[0]);
   
  //  Максимальная скорость тактирования
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDRB_CLK_PLL_HSE_RES_MAX;
  MDR_CPU_SetClock_PLL_HSE(&cfgPLL_HSE, true);
  
  //  Инициализация LCD дисплея и кнопок
  freqCPU_Hz = MDR_CPU_GetFreqHz(true);
  MDRB_LCD_Init(freqCPU_Hz);
  MDRB_Buttons_Init(BTN_DEBOUNCE_MS, freqCPU_Hz);
    
  //  Инициализация конфигруации в глобальных переменных
  Cfg_InitSelectedConfigs();
  
  // Настройка частоты ADC_Clock=HSE=8MHz. Используется в некоторых тестах вместо CPU_Clk.
  MDR_ADC_SetClock_CPU_C1(MDR_Div256P_div1);
  
  //  Выводы GPIO в аналоговую функцию для выбраных сигналов в ADC_Cfg.с  
  if (Cfg_GPIO_PinSelected)
    MDR_ADC_PinsInitByMask(CFG_ADC_GPIO_Port, Cfg_GPIO_PinSelected);
#ifdef CFG_ADC_GPIO_PortEx  
  //  В ВЕ4,ВК214,ВК234 пины каналов АЦП находятся в двух портах
  if (Cfg_GPIO_PinSelectedEx)
    MDR_ADC_PinsInitByMask(CFG_ADC_GPIO_PortEx, Cfg_GPIO_PinSelectedEx);
#endif  
  // Базовая настройка ADC - опции меняются в тестах
  MDR_ADC_Init(&_cfgAdc); 
  
  //  Активный тест
  testStack[activeTest]->funcInit();
  
#ifdef USE_MDR1986VK214  
  MDR_SysTimerStart(SYS_TIMER_VALUE_MAX);
#endif
  
  while (1)
  {
    //  Смена теста
    if (MDRB_BntClicked_Up(true))
    {
      MDR_SysTimerStop();
      timerStarted = false;
      
      //  Возврат к базовой конфигурации АЦП
      testStack[activeTest]->funcFinit();
      
      //  Инициализация нового теста
      ++activeTest;
      if (activeTest >= testCount)
        activeTest = 0;
      
      testStack[activeTest]->funcInit();
    #ifdef USE_MDR1986VK214  
      MDR_SysTimerStart(SYS_TIMER_VALUE_MAX);
    #endif      
      
    }

    //  Изменение режима теста
    if (MDRB_BntClicked_Right(true))
    {
      testStack[activeTest]->funcChange();
    }    
    
    //  Запуск
    if ((startByTimer) || (MDRB_BntClicked_Down(true)))
    {
      testStack[activeTest]->funcExec();
      
      startByTimer = false;
    }
    
    //  Циклический запуск по таймеру - максимально не часто, чтобы успеть увидеть
    if (MDRB_BntClicked_Left(true))
    {
      if (timerStarted)
        MDR_SysTimerStop();
      else  
        MDR_SysTimerStart(SYS_TIMER_VALUE_MAX);
      timerStarted = !timerStarted;
    }
    
  }  
}

void SysTick_Handler(void)
{
  static uint32_t cnt = 0;
  ++cnt;
  if (cnt > 4)
  {
    cnt = 0;
    startByTimer = true;
  }
}

void ADC_IRQHandler(void)
{
  //  Обработчик прерывания если тесту необходим
  testStack[activeTest]->funcHandlerIrq();
}


#include <MDR_RST_Clock.h>
#include <MDR_PER_Clock.h>
#include <MDRB_Buttons.h>
#include <MDR_Timer.h>

#include "test_Defs.h"
#include "MDRB_ShowMess.h"

#ifdef MDRB_HAS_LCD
  #define USE_LCD   true
  #ifdef LCD_IS_7SEG_DISPLAY
    #define USE_UART_DBG    true
  #else
    #define USE_UART_DBG    false
  #endif
#else 
  #define USE_LCD         false
  #define USE_UART_DBG    true
#endif  


//  Некоторые тесты можно закомментировать для рассмотрения только интересующих
//  Счет импульсов TIM_CLOCK или внешних, каскадное включение таймеров
extern TestInterface TI_SimplestFlash;
extern TestInterface TI_CountTimClock;
extern TestInterface TI_CascadeTimer;
extern TestInterface TI_PWM_CountCAP;

//  Генерация ШИМ
extern TestInterface TI_Pulse;
extern TestInterface TI_PWM;
extern TestInterface TI_PWM_DTG;
//  Захват фронтов на прямом входе канала таймера
extern TestInterface TI_CAP_Simplest;
extern TestInterface TI_CAP_Period;


//  Тесты с ETR не доступны для 1986ВЕ93, на плате нет не конфликтующих выводов ETR
#ifndef NO_ETR_PIN 
extern TestInterface TI_PWM_ClearBRKETR;
extern TestInterface TI_PWM_CountETR;
#endif

static  TestInterface *testStack[] = {
  //  Режим внутреннего счета - Счет импульсов TIM_CLOCK
  &TI_SimplestFlash,
  &TI_CountTimClock,
  &TI_CascadeTimer, 
  //  Вывод ШИМ на пины каналов таймeров (PWM)
  //  ПРОВЕРИТЬ, что выходы каналов таймеров не замкнуты друг на друга, после тестов с захватом!
  &TI_Pulse,      // Simplest control to get pulses (PWM mode)
  &TI_PWM,
  &TI_PWM_DTG, 
#ifndef NO_PWM1_ETR_PIN  
  &TI_PWM_ClearBRKETR,   
#endif
  //  Режим захвата (CAP)
  //  НЕОБХОДИМО внешнее подключение пинов с ШИМ к пинам захвата!
  &TI_CAP_Simplest,
  &TI_CAP_Period,
  //  Режимы внешнего счета - импульсов на входе ETR и событий на каналах захвата
  &TI_PWM_CountCAP,
#ifndef NO_CAP_ETR_PIN    
  &TI_PWM_CountETR,
#endif
};

static uint32_t activeTest = 0;
static const uint32_t testCount = sizeof(testStack)/sizeof(testStack[0]);

#define BTN_DEBOUNCE_MS 10

void TIMER1_IRQHandler(void);
void TIMER2_IRQHandler(void);
void TIMER3_IRQHandler(void);
void TIMER4_IRQHandler(void);

int main(void)
{
  uint32_t freqCPU_Hz;

#ifdef USE_MDR1923VK014 
  //  Задержка для 1923ВК014 для переключения в PC с программы UART загрузчика на Terminal.
  MDR_Delay_ms(7000, HSI_FREQ_HZ);
#endif
  
  //  Максимальная скорость тактирования
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDRB_CLK_PLL_HSE_RES_MAX;
  MDR_CPU_SetClock_PLL_HSE(&cfgPLL_HSE, true);
  
  //  Инициализация кнопок и вывода SHOW(LCD и/или UART_DBG)
  freqCPU_Hz = MDR_CPU_GetFreqHz(true);
  MDRB_Buttons_Init(BTN_DEBOUNCE_MS, freqCPU_Hz);
  MDR_ShowInit(USE_LCD, USE_UART_DBG);
  
  //  Для 1986VE4,VE214,VE234 частота TIM_Clock формируется мультиплексорами
  //  В VE214 отдельный выбор частоты с делителем для каждого из блоков UART, SSP, Timer
  //  В остальных МК TIM_Clock формируется только из HCLK (равной CPU_Clock) - выбор источника не требуется
#ifdef MDR_PER_CLOCK_SELF_TIM_UART_SSP  
  MDR_SetClock_Timer1(MDR_PER_PLLCPUo);
  MDR_SetClock_Timer2(MDR_PER_PLLCPUo);
#elif defined (MDR_TIM_CLOCK_FROM_PER_CLOCK)
  MDR_SetClock_UartTimSSP(MDR_PER_PLLCPUo);  
#elif defined(MDR_CLK_LIKE_VE8)
  MDR_Timer_SetTimClockSrc(PWM1_TIMex, MDR_RST_ASYNC_IN_MAX_CLK);
  MDR_Timer_SetTimClockSrc(PWM2_TIMex, MDR_RST_ASYNC_IN_MAX_CLK);
  MDR_Timer_SetTimClockSrc(CAP_TIMex, MDR_RST_ASYNC_IN_MAX_CLK);  
#endif
   
  //  Активный тест
  activeTest = 0;  
  testStack[activeTest]->funcInit();
  
  while (1)
  {
    //  Смена теста
    if (MDRB_BntClicked_Up(true) || MDRB_NeedActon(MDRB_ACT_NEXT_TEST))
    {      
      //  Возврат к базовой кончигурации АЦП
      testStack[activeTest]->funcFinit();
      
      //  Инициализация нового теста
      ++activeTest;
      if (activeTest >= testCount)
        activeTest = 0;
      
      testStack[activeTest]->funcInit();
    }

    //  Изменение режима теста
    if (MDRB_BntClicked_Right(true) || MDRB_NeedActon(MDRB_ACT_CHANGE_MODE))
    {
      testStack[activeTest]->funcChange();
    }    
    
    //  Запуск
    if (MDRB_BntClicked_Down(true)  || MDRB_NeedActon(MDRB_ACT_EXEC))
    {
      testStack[activeTest]->funcExec();
    }   
    //  Main thread
    testStack[activeTest]->funcMainLoop();
  }  
}

void TIMER1_IRQHandler(void)
{
  testStack[activeTest]->funcHandlerTim1();
}

void TIMER2_IRQHandler(void)
{
  testStack[activeTest]->funcHandlerTim2();
}

void TIMER3_IRQHandler(void)
{
  testStack[activeTest]->funcHandlerTim3();
}

void TIMER4_IRQHandler(void)
{
  testStack[activeTest]->funcHandlerTim4();
}



#include <MDR_RST_Clock.h>
#include <MDR_PER_Clock.h>
#include <MDRB_Buttons.h>
#include <MDRB_LCD.h>

#include "test_Defs.h"

//  Некоторые тесты можно закомментировать для рассмотрения только интересующих
//  Счет импульсов TIM_CLOCK или внешних, каскадное включение таймеров
extern TestInterface TI_SimplestFlash;
extern TestInterface TI_CountTimClock;
extern TestInterface TI_CascadeTimer;
extern TestInterface TI_PWM_CountETR;
extern TestInterface TI_PWM_CountCAP;

//  Генерация ШИМ
extern TestInterface TI_Pulse;
extern TestInterface TI_PWM;
extern TestInterface TI_PWM_ClearBRKETR;
extern TestInterface TI_PWM_DTG;
//  Захват фронтов на прямом входе канала таймера
extern TestInterface TI_CAP_Simplest;
extern TestInterface TI_CAP_Period;


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
  &TI_PWM_ClearBRKETR,   
  //  Режим захвата (CAP)
  //  НЕОБХОДИМО внешнее подключение пинов с ШИМ к пинам захвата!
  &TI_CAP_Simplest,
  &TI_CAP_Period,
  //  Режимы внешнего счета - импульсов на входе ETR и событий на каналах захвата
  &TI_PWM_CountCAP,
  &TI_PWM_CountETR,
};

uint32_t activeTest = 0;
uint32_t testCount = sizeof(testStack)/sizeof(testStack[0]);

#define BTN_DEBOUNCE_MS 10

int main(void)
{
  uint32_t freqCPU_Hz;
 
  //  Максимальная скорость тактирования
  MDR_CPU_SetClock_HSE_Max(MDR_Off);
  
  //  Инициализация LCD дисплея и кнопок
  freqCPU_Hz = MDR_CPU_GetFreqHz(true);
  MDRB_LCD_Init(freqCPU_Hz);
  MDRB_Buttons_Init(BTN_DEBOUNCE_MS, freqCPU_Hz);
  
  //  Для 1986VE4,VE214,VE234 частота TIM_Clock формируется мультиплексорами
  //  В VE214 отдельный выбор частоты с делителем для каждого из блоков UART, SSP, Timer
  //  В остальных МК TIM_Clock формируется только из HCLK (равной CPU_Clock) - выбор источника не требуется
#ifdef MDR_PER_CLOCK_SELF_TIM_UART_SSP  
  MDR_SetClock_Timer1(MDR_PER_PLLCPUo);
  MDR_SetClock_Timer2(MDR_PER_PLLCPUo);
#elif defined (MDR_TIM_CLOCK_FROM_PER_CLOCK)
  MDR_SetClock_UartTimSSP(MDR_PER_PLLCPUo);
#endif
   
  //  Активный тест
  activeTest = 0;  
  testStack[activeTest]->funcInit();
  
  while (1)
  {
    //  Смена теста
    if (MDRB_BntClicked_Up(true))
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
    if (MDRB_BntClicked_Right(true))
    {
      testStack[activeTest]->funcChange();
    }    
    
    //  Запуск
    if (MDRB_BntClicked_Down(true))
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

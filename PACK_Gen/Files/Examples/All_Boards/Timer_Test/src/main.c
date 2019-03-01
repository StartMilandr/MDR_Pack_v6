#include <MDR_RST_Clock.h>
#include <MDR_PER_Clock.h>
#include <MDRB_Buttons.h>
#include <MDRB_LCD.h>

#include "test_Defs.h"

//  Некоторые тесты можно закомментировать для рассмотрения только интересующих
extern TestInterface TI_SimplestFlash;
extern TestInterface TI_CascadeTimer;
extern TestInterface TI_PWM;
extern TestInterface TI_CountTimClock;
extern TestInterface TI_Pulse;
extern TestInterface TI_PWM_ClearBRKETR;
extern TestInterface TI_PWM_CountETR;

static  TestInterface *testStack[] = {&TI_PWM_CountETR, &TI_PWM_ClearBRKETR, &TI_Pulse, &TI_PWM, &TI_CountTimClock, &TI_CascadeTimer, &TI_SimplestFlash};

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
  
  //  Для 1986VE4,VE214,VE234 частота UART_Clock формируется мультиплексорами
  //  В VE214 отдельный выбор частоты с делителем для каждого из блоков UART, SSP, Timer
  //  В остальных МК UART_Clock формируется только из HCLK (равной CPU_Clock) - выбор источника не требуется
//#ifdef MDR_PER_CLOCK_SELF_TIM_UART_SSP  
//  MDR_SetClock_Uart1(MDR_PER_PLLCPUo);
//  MDR_SetClock_Uart2(MDR_PER_PLLCPUo);
//#elif defined (MDR_PER_CLK_LIKE_VE4)
//  MDR_SetClock_UartTimSSP(MDR_PER_PLLCPUo);
//#endif
   
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

//    //  Изменение режима теста
//    if (MDRB_BntClicked_Right(true))
//    {
//      //testStack[activeTest]->funcChange();
//      testStack[activeTest]->funcExec();
//    }    
//    
    //  Запуск
    if (MDRB_BntClicked_Down(true))
    {
      testStack[activeTest]->funcExec();
    }
    
    //  ОБработчик цикла
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

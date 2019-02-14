#include <MDR_RST_Clock.h>
#include <MDR_UART.h>
#include <MDR_PER_Clock.h>
#include <MDRB_LCD.h>
#include <MDRB_Buttons.h>

//#include "UART_Cfg.h"
//#include "UART_Select.h"

#include "test_Defs.h"

//  Некоторые тесты можно закомментировать для рассмотрения только интересующих
extern TestInterface TI_Uart_Debug;
extern TestInterface TI_Uart_DebugRate;


#ifdef BDR_NO_SLAVE_UART
  static  TestInterface *testStack[] = {&TI_Uart_Debug, &TI_Uart_DebugRate};
#else
  static  TestInterface *testStack[] = {&TI_Uart_Debug, &TI_Uart_DebugRate};
#endif

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
  //MDRB_LCD_Init(freqCPU_Hz);
  MDRB_Buttons_Init(BTN_DEBOUNCE_MS, freqCPU_Hz);
  
  //  Для 1986VE4,VE214,VE234 частота UART_Clock формируется мультиплексорами
  //  В VE214 отдельный выбор частоты с делителем для каждого из блоков UART, SSP, Timer
  //  В остальных МК UART_Clock формируется только из HCLK (равной CPU_Clock) - выбор источника не требуется
#ifdef MDR_PER_CLOCK_SELF_TIM_UART_SSP  
  MDR_SetClock_Uart1(MDR_PER_PLLCPUo);
  MDR_SetClock_Uart2(MDR_PER_PLLCPUo);
#elif defined (MDR_UART_CLOCK_FROM_PER_CLOCK)
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
      //testStack[activeTest]->funcChange();
      testStack[activeTest]->funcExec();
    }    
    
    //  Запуск
    if (MDRB_BntClicked_Down(true))
    {
      testStack[activeTest]->funcExec();
    }   
  }  
}

void UART1_IRQHandler(void)
{
  testStack[activeTest]->funcHandlerIrqMaster();
}

void UART2_IRQHandler(void)
{
  testStack[activeTest]->funcHandlerIrqSlave();
}

#ifdef USE_MDR1901VC1
void UART3_IRQHandler(void)
{
  testStack[activeTest]->funcHandlerIrqSlave();
}
#endif

#include <MDR_RST_Clock.h>
#include <MDR_SSP.h>
#include <MDR_PER_Clock.h>
#include <MDRB_LCD.h>
#include <MDRB_Buttons.h>

#include "SSP_cfg.h"
#include "test_SSP_Interfs.h"
#include "SSP_CommonFuncs.h"

#define BTN_DEBOUNCE_MS   20

//  Тесты - это варианты использования, в каждом тесте меняется один параметр и проверяется работоспособность
//  Изменяемый параметр глобальный - т.е. при переключении в другой тест остается для нового теста.
//  КНОПКИ:
//    Up    - смена теста
//    Down  - передача данных и вывод результата.
//    Right - смена изменяемого параметра, в каждом тесте своего.
//  Тесты:
//---
//    LBM - Тестовый обмен TX->RX внутри одного блока, без использования выводов GPIO.
//          (Работает при максимальной скорости, PSR_2_254 = 2)
//      Right - Смена режима SPI - CPO и CPH.
//---
//    TXRT - Обмен данных в одном блоке SPI, необходимо подключить выводы GPIO TX->RX.
//          (Работает при максимальной скорости, PSR_2_254 = 2)
//      Right - Смена делителя PSR_2_254, по +2. Младший бит делителя не валиден.
//---
//    Master-Slave - Обмен между двумя блоками SPI на одной плате. Подключить все выводы GPIO.
//          (Работает при делителе, PSR_2_254 = 14)
//          Master_TX  -> Slave_RX
//          Master_RX  -> Slave_TX
//          Master_CLK -> Slave_CLK
//          Master_FSS -> Slave_FSS
//      Right - Смена делителя PSR_2_254, по +2. Младший бит делителя не валиден.
//---
//    DataBits - Вариант Master-Slave, меняется количество бит в слове.
//          (Работает при делителе, PSR_2_254 = 14)
//      Right - Смена количества бит в слове
//---
//    Frames - Вариант Master-Slave, меняется тип фрейма.
//          (Работает при делителе, PSR_2_254 = 14)
//      Right - Смена фрейма - SPI, SSI, Microwire
//      Работает только для SPI и SSI. При Microwire особый протокол, для которого тест не подходит.
//---
//    Microwire - Вариант Master-Slave, используется режим Microwire.
//      Right - Смена битов в ответном слове от ведомого. Команда от мастера всегда 8-ми битная.
//---
//    IRQ - Вариант Master-Slave, c использованием прерываний и заполнением FIFO.
//      Right - Смена количества бит в слове
//---
//    LBM_ALL - Перебор всех доступных SSP и проверка в режиме LBM (проверка, что функции работают со всеми SSP правильно)
//      Right - смена блока SSP для которого выполняется тест LBM.


//  Некоторые тесты можно закомментировать для рассмотрения только интересующих
#ifdef BDR_NO_SLAVE_SSP
  static  TestInterface *testStack[] = {&TI_SPI_LBM, &TI_SPI_TXRX, &TI_SPI_LBM_ALL};
#else
  static  TestInterface *testStack[] = {&TI_SPI_LBM, &TI_SPI_TXRX, &TI_SPI_MasterSlave, &TI_SSP_DataBits, &TI_SSP_Frames, &TI_SSP_Microwire, &TI_SSP_IRQ, &TI_SPI_LBM_ALL};
#endif


int main(void)
{
  uint32_t freqCPU_Hz;
  uint32_t testCount = sizeof(testStack)/sizeof(testStack[0]);
 
  //  Максимальная скорость тактирования
  MDR_CPU_SetClock_HSE_Max(MDR_Off);
  
  //  Инициализация LCD дисплея и кнопок
  freqCPU_Hz = MDR_CPU_GetFreqHz(true);
  MDRB_LCD_Init(freqCPU_Hz);
  MDRB_Buttons_Init(BTN_DEBOUNCE_MS, freqCPU_Hz);
  
  //  Инициализация масок для захвата пинов под SSP и освобождения
  //  Необходимы из-за конфликтов пинов SSP с LCD на некоторых отладочных платах.
  Cfg_SSP_CapturePinsInit(MDR_PIN_FAST);

  //  Для 1986VE4,VE214,VE234 частота SSP_Clock формируется мультиплексорами
  //  В остальных МК SSP_Clock формируется только из HCLK (равной CPU_Clock) - выбор источника не требуется
#ifdef MDR_SSP_CLOCK_FROM_PER_CLOCK  
  MDR_SelectSrcFor_UartTimSSP_Clock(MDR_PER_PLLCPUo);
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
  }  
}

void SSP1_IRQHandler(void)
{
  if (MDR_SSP1ex == SSP_MASTER)
    testStack[activeTest]->funcHandlerIrqMaster();
#ifndef BDR_NO_SLAVE_SSP
  else if (MDR_SSP1ex == SSP_SLAVE)
    testStack[activeTest]->funcHandlerIrqSlave();
#endif
}

#ifdef MDR_SSP2ex
void SSP2_IRQHandler(void)
{
  if (MDR_SSP2ex == SSP_MASTER)
    testStack[activeTest]->funcHandlerIrqMaster();
#ifndef BDR_NO_SLAVE_SSP  
  else if (MDR_SSP2ex == SSP_SLAVE)
    testStack[activeTest]->funcHandlerIrqSlave();
#endif
}
#endif


#ifdef MDR_SSP4ex
void SSP3_IRQHandler(void)
{
  if (MDR_SSP4ex == SSP_MASTER)
    testStack[activeTest]->funcHandlerIrqMaster();
  else if (MDR_SSP4ex == SSP_SLAVE)
    testStack[activeTest]->funcHandlerIrqSlave();
}
#endif


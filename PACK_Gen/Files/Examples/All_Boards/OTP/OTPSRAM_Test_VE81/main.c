#include <MDR_RST_Clock.h>
#include <MDR_OTP_VE8x.h>
#include <MDR_Funcs.h>

#include <MDRB_Buttons.h>
#include <MDRB_LEDs.h>

//  ОПИСАНИЕ:
//  По нажатию KEY1:
//    В память SRAM 1986ВЕ81Т, которая вместо ОТР, записывается массив значений.
//    Затем массив считывается и проверяется то, что данные совпали.
//    Этим проверяется что функция записи в память MDR_OTPSRAM_ProgWordWord() работает корректно.
//    Если функция некорректна и память находится в не согласованном с ЕСС состоянии после включения питания,
//    то при обращении к памяти происходит выход в HardFault.
//  Реализация функций для работы с памятью взята от Vasili с форума - http://forum.milandr.ru/viewtopic.php?p=20531#p20531
//  За что ему большое СПАСИБО!

//  По нажатию KEY2:
//    Производится считывание из области памяти ОРТ в которой значения не согласованы с  ЕСС - содержат хаотичные значения возникшие при включении питания.
//    При чтении возникает не одинарная ошибка ЕСС, шине запрещено возвращать ядру некорректные данные, поэтому шина не отвечает и ядро фиксирует ошибку BusFault.
//    Исключение BusFault не активировано, поэтому исключение падает в HardFault, в обработчике которого переключаются все три светодиода.
//    Мигание светодиодов происходит потому, что исполнение после обработчика возвращается на адрес который привел к ошике и исполняет ту-же самую инструкцию. 
//    Которая, в свою очередь, снова вызывает исключение HardFault. Обработчик HardFault оказвается зацикленным, исполняется снова и снова.
//    Поэтому в обработчике инкрементируется счетчик, чтобы мигание светодиодов происходило заметно для человека.

//  По нажатию KEY3:
//    Чтобы выйти из зацикленного обработчика HardFault необходимо парировать ошибку, т.е. проинициализировать ячейку памяти которая читается в тесте - OPT_TEST_FAULT_ADDR.
//    По нажатию на KEY3 в данную ячейку записывается любое значение, например 0. 
//    Для адреса и памяти функция MDR_OTPSRAM_ProgWordWord() значение ECC, которое записывается вместе с данными.
//    Теперь чтение данного адреса не вызывает ошибки ЕСС, поэтому при выходе из HardFault возврат в обработчик не происходит.
//    Зацикливание прервано и исполнение снова в главном цикле.
//    еперь по KEY2 выход в HardFault уже не происходит!
//    Чтобы в тесте снова срабатывало HardFault необходимо снять питание и подождать десяток секунд чтобы память сбросилась.
//    Пары секунд на это бывает недостаточно.

//  LED:
//    LED_CYCLE - мигает, показывая что основной цикл исполняется. 
//    LED_OK  - Загорается после нажатия на KEY1, если запись-чтение выполнились успешно.
//    LED_ERR - Загорается после нажатия на KEY1, если запись-чтение выполнились не успешно, данные не совпали.
//    Мигают все LED_CYCLE | LED_OK | LED_ERR - произошел выход в HardFault по кнопке KEY2.



//  Работает так-же на максимальной частоте
#define CHECK_AT_MAX_CLOCK    0

#define BTN_DEBOUNCE_MS  10

#define LED_CYCLE     MDRB_LED_1
#define LED_OK        MDRB_LED_2
#define LED_ERR       MDRB_LED_3

#define LED_CYCLICK_PERIOD  5000

#define OTP_TEST_WRITE_COUNT  100
#define OPT_TEST_FAULT_ADDR   0x01018000
#define OPT_TEST_START_ADDR   OPT_TEST_FAULT_ADDR + 4


void OPT_WriteTestData(void);
bool OPT_ReadAndCheck(void);
void LedCyclicToggle(void);

uint32_t RunIndex = 0;

int main(void)
{ 
#if CHECK_AT_MAX_CLOCK  
  //  Максимальная скорость тактирования
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDRB_CLK_PLL_HSE_RES_MAX;
  MDR_CLK_Enable_RST_BPK();
  MDR_CPU_SetClock_PLL_HSE(&cfgPLL_HSE, true);  
#endif
  
  uint32_t freqCPU_Hz = MDR_CPU_GetFreqHz(true); 
  MDRB_Buttons_Init(BTN_DEBOUNCE_MS, freqCPU_Hz);
  MDRB_LED_Init(LED_CYCLE | LED_OK | LED_ERR);
   
  while (1)
  {
    if (MDRB_BntClicked_Up(true))
    {
      MDRB_LED_Set(LED_CYCLE | LED_OK | LED_ERR, 0);
      
      OPT_WriteTestData();
      MDR_Delay_ms(200, freqCPU_Hz);
      
      if (OPT_ReadAndCheck())
        MDRB_LED_Set(LED_OK, 1);
      else
        MDRB_LED_Set(LED_ERR, 1);
      
      ++RunIndex;
    }
    
    if (MDRB_BntClicked_Right(true))
    {
      MDRB_LED_Set(LED_CYCLE | LED_OK | LED_ERR, 0);
      //  Go to HardFault
      REG32(OPT_TEST_FAULT_ADDR);
    }
    
    LedCyclicToggle();
  }
}

void OPT_WriteTestData(void)
{
  uint32_t i;
  
  MDR_OTP_Enable();
  for (i = 0; i < OTP_TEST_WRITE_COUNT; ++i)
    MDR_OTPSRAM_ProgWord(OPT_TEST_START_ADDR + (i << 2), i + RunIndex);  
  MDR_OTP_Disable();
}

bool OPT_ReadAndCheck(void)
{
  uint32_t i;
  uint32_t cntErr = 0;
  uint32_t rdValue;
  for (i = 0; i < OTP_TEST_WRITE_COUNT; ++i)
  {
    rdValue = REG32(OPT_TEST_START_ADDR + (i << 2));
    if (rdValue != (i + RunIndex))
      ++cntErr;   
  }
  
  return cntErr == 0;
}

void LedCyclicToggle(void)
{
  static uint32_t cnt = 0;
  
  ++cnt;
  if (cnt > LED_CYCLICK_PERIOD)
  {
    MDRB_LED_Toggle(LED_CYCLE);
    cnt = 0;
  }
}

void HardFault_Handler(void)
{
  static uint32_t cnt = 0;
  
  ++cnt;
  if (cnt > LED_CYCLICK_PERIOD * 5)
  {
    MDRB_LED_Toggle(LED_CYCLE | LED_OK | LED_ERR);
    cnt = 0;
  }
  
  if (MDRB_BntClicked_Down(true))
  {
    // Парируем ошибку для прерывания зацикливания вызова HardFault_Handler
    MDR_OTP_Enable();
    MDR_OTPSRAM_ProgWord(OPT_TEST_FAULT_ADDR, 0); 
    MDR_OTP_Disable();
    
    MDRB_LED_Set(LED_CYCLE | LED_OK | LED_ERR, 0);
  }
}


#include <MDR_Config.h>
#include <MDR_RST_Clock.h>
#include <MDR_PER_Clock.h>
#include <MDRB_Buttons.h>
#include <MDRB_LEDs.h>
#include <MDR_Funcs.h>
#include <MDR_DMA.h>

#ifdef USE_MDR1923VK014 
  #include <MDRB_UART_Debug.h>
  #include <stdio.h>
#endif

//  ОПИСАНИЕ:
//  По кнопкам UP и DOWN запускается копирование трех буферов с разной размерностью данных тремя разными каналами DMA по программному запросу.
//  По UP копирование данных идет по очереди друг за другом.
//  По DOWN копирование запускается не дожидаясь окончания предыдущего.
//  - Светодиод LED_CYCLE (LED1) показывает что тест исполняется.
//  - Если после запуска загорается LED_ERROR (LED2) - значит скопированные данные не совпадают - ошибка.
//  - При SHOW_DMA_IRQ_BEHAVIOUR = 1, в прерывании по окончанию DMA загорается LED_IRQ (LED3). При выходе в основной цикл, LED_IRQ выключается после задержки.
//    Мигание LED_IRQ показывает, что перывание сработало и не зациклилось.


#define SHOW_DMA_IRQ_BEHAVIOUR   1
#define BTN_DEBOUNCE_MS 10

#define DATA_LEN    1024
#ifdef DMA_NEED_EXECUTABLE_MEM_RANGE
  //  Для 1986ВЕ1 и 1986ВЕ3Т массивы должны лежать в области памяти доступной для DMA - с адресов 0x2010_0000
  //  Необходимо задать это в скаттер файле, или в настройках модуля *.с
  //  В закладке линкера подключен готовый скаттер файл MDR1986VE1T_sctr.txt.
  static uint32_t SrcData[DATA_LEN]    __RAM_EXEC;
  static uint32_t DestData32[DATA_LEN] __RAM_EXEC;
  static uint16_t DestData16[DATA_LEN] __RAM_EXEC;
  static uint8_t  DestData8[DATA_LEN]  __RAM_EXEC;
#else
  static uint32_t SrcData[DATA_LEN];
  static uint32_t DestData32[DATA_LEN];
  static uint16_t DestData16[DATA_LEN];
  static uint8_t  DestData8[DATA_LEN];
#endif

static uint32_t *pSrc32 = SrcData;
static uint16_t *pSrc16 = (uint16_t *)SrcData;
static uint8_t  *pSrc8  = (uint8_t  *)SrcData;

static uint32_t *pDest32 = DestData32;
static uint16_t *pDest16 = (uint16_t *)DestData16;
static uint8_t  *pDest8  = (uint8_t  *)DestData8;

void ClearData(void);
bool CompareData(void);

#define LED_FLASH_PERIOD  50000

#ifdef MDRB_LED_3
  #define LED_CYCLE         MDRB_LED_1
  #define LED_ERROR         MDRB_LED_2
  #define LED_IRQ           MDRB_LED_3

#elif defined(MDRB_LED_2)
  #define LED_CYCLE         MDRB_LED_1
  #define LED_ERROR         MDRB_LED_2
  #define LED_IRQ           MDRB_LED_2
#else
  #define LED_CYCLE         MDRB_LED_1
  #define LED_ERROR         MDRB_LED_1
  #define LED_IRQ           MDRB_LED_1
#endif

#ifndef MDR_DMA_IRQ_LIKE_VE8
  void DMA_IRQHandler(void);
#else
  static uint32_t IRQ_cnt = 0;
  void DMA_CountIRQ(void);
  
  void DMA_DONE0_IRQHandler(void);
  void DMA_DONE1_IRQHandler(void);
  void DMA_DONE2_IRQHandler(void);
#endif

static bool forcedKeyUp = false;
static bool forcedKeyDown = false;
void MDRB_UART_Dbg_Handler(void);
void UART1_IRQHandler(void);
void UART2_IRQHandler(void);

int main(void)
{
  uint32_t freqCPU_Hz;
  uint32_t cycleCnt = 0;
 
#ifdef USE_MDR1923VK014 
  //  Задержка для 1923ВК014 для переключения в PC с программы UART загрузчика на Terminal.
  MDR_Delay_ms(7000, HSI_FREQ_HZ);
#endif  
  
  //  Максимальная скорость тактирования
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDRB_CLK_PLL_HSE_RES_MAX;
  MDR_CPU_SetClock_PLL_HSE(&cfgPLL_HSE, true);
  
  //  Инициализация кнопок и светодиодов
  freqCPU_Hz = MDR_CPU_GetFreqHz(true);
  MDRB_Buttons_Init(BTN_DEBOUNCE_MS, freqCPU_Hz);
  MDRB_LED_Init(LED_CYCLE | LED_ERROR | LED_IRQ);

#ifdef USE_MDR1923VK014
  // команды от UART вместо кнопок
  MDR_UART_DBG_InitIrqRT(UART_DEBUG_BAUD_DEF, true);
#endif
  
  //  DMA
  MDR_DMA_Init();
  
#if SHOW_DMA_IRQ_BEHAVIOUR
  //  Включение прерываний для контроля, что исполнение не зависает в обработчике.
  //  Практической пользы в данном примере не несет, можно удалить
  //  Но показывает что прерывание возникает!
  #ifndef MDR_DMA_IRQ_LIKE_VE8
    NVIC_ClearPendingIRQ(DMA_IRQn);
    NVIC_EnableIRQ(DMA_IRQn);
  #else
    // VE8, VK014, ESila
    NVIC_ClearPendingIRQ(DMA_DONE0_IRQn);
    NVIC_EnableIRQ(DMA_DONE0_IRQn);  
    NVIC_ClearPendingIRQ(DMA_DONE1_IRQn);
    NVIC_EnableIRQ(DMA_DONE1_IRQn);  
    NVIC_ClearPendingIRQ(DMA_DONE2_IRQn);
    NVIC_EnableIRQ(DMA_DONE2_IRQn);  
  #endif
#endif
  
  while (1)
  {
    if (MDRB_BntClicked_Up(true) || forcedKeyUp)
    { 
      forcedKeyUp = false;
      ClearData();

      MDRB_LED_Set(LED_CYCLE | LED_ERROR, MDR_On);
     
      MDR_DMA_Copy8 (0, pSrc8,  pDest8,  DATA_LEN);
      MDR_DMA_Copy16(1, pSrc16, pDest16, DATA_LEN);
      MDR_DMA_Copy32(2, pSrc32, pDest32, DATA_LEN);      
    
      if (CompareData())
        MDRB_LED_Set(LED_CYCLE | LED_ERROR, MDR_Off);
      else
        MDR_Delay_ms(3000, freqCPU_Hz);
    }
    
    if (MDRB_BntClicked_Right(true) || forcedKeyDown)
    {
      forcedKeyDown = false;
      ClearData();

      MDRB_LED_Set(LED_CYCLE | LED_ERROR, MDR_On);
     
      //  Запуск нескольких каналов
      MDR_DMA_CopyStart8 (0, pSrc8,  pDest8,  DATA_LEN);
      MDR_DMA_CopyStart16(1, pSrc16, pDest16, DATA_LEN);
      MDR_DMA_CopyStart32(2, pSrc32, pDest32, DATA_LEN);
      
      //  Ожидание окончания
      while (!MDR_DMA_CopyGetCompletedSel(0x7UL));
    
      if (CompareData())
        MDRB_LED_Set(LED_CYCLE | LED_ERROR, MDR_Off);
      else
        MDR_Delay_ms(3000, freqCPU_Hz);
    }     
    
    //  Led flashing
    ++cycleCnt;
    if (cycleCnt > LED_FLASH_PERIOD)
    {
      cycleCnt = 0;
      MDRB_LED_Toggle(LED_CYCLE);
      
#ifdef MDRB_LED_2      
      MDRB_LED_Set(LED_IRQ, MDR_Off);      
   #ifdef MDR_DMA_IRQ_LIKE_VE8
      IRQ_cnt = 0;
   #endif
#endif
    }
  }   
 
}

static uint32_t  nextData = 0;

void ClearData(void)
{
  uint32_t i;
  
  for (i = 0; i < DATA_LEN; ++i)
  {
    SrcData[i]    = MDR_ToPseudoRand(nextData++);
    DestData32[i] = 0;
    if (SrcData[i] == DestData32[i])
      ++SrcData[i];
    
    DestData16[i] = 0;
    DestData8[i]  = 0;
  }
}

bool CompareData(void)
{
  uint32_t i;
  uint32_t cntErr = 0;
  
  for (i = 0; i < DATA_LEN; ++i)
  {
    if (pSrc32[i] != pDest32[i])
      ++cntErr;
    if (pSrc16[i] != pDest16[i])
      ++cntErr;
    if (pSrc8[i] != pDest8[i])
      ++cntErr;
  }
  return cntErr == 0;
}

#ifndef MDR_DMA_IRQ_LIKE_VE8
  void DMA_IRQHandler(void)
  {
    MDRB_LED_Set(LED_IRQ, MDR_On);
  }
#else
  void DMA_CountIRQ(void)
  {
    ++IRQ_cnt;
    if (IRQ_cnt == 3)
      MDRB_LED_Set(LED_IRQ, MDR_On);
  }

  void DMA_DONE0_IRQHandler(void)
  {
    DMA_CountIRQ();
  }

  void DMA_DONE1_IRQHandler(void)
  {
    DMA_CountIRQ();
  }

  void DMA_DONE2_IRQHandler(void)
  {
    DMA_CountIRQ();
  }
#endif

#ifdef USE_MDR1923VK014
  // команды от UART вместо кнопок
  void MDRB_UART_Dbg_Handler(void)
  {
    uint16_t command;
    while (MDR_UART_CanRead(UART_DBG->UARTx))
    {
      command = MDR_UART_ReadData(UART_DBG->UARTx);
      switch (command & 0x00FF) {
      case 'U': { forcedKeyUp = true; break; }
      case 'R': { forcedKeyDown = true; break; }
      }
      //  Ack
      printf("%c\n", (char)command);
    }
  }
  
  void UART1_IRQHandler(void)
  {
    MDRB_UART_Dbg_Handler();
  }

  void UART2_IRQHandler(void)
  {
    MDRB_UART_Dbg_Handler();
  }  
  
#endif

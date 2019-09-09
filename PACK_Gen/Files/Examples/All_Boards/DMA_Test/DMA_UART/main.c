#include <MDR_RST_Clock.h>
#include <MDR_PER_Clock.h>
#include <MDRB_Buttons.h>
#include <MDRB_LEDs.h>
#include <MDR_Funcs.h>
#include <MDR_DMA.h>
#include <MDR_UART.h>

//  ОПИСАНИЕ:
//    По нажатию на кнопку UP(KEY1) включается канал DMA_Chan_TX, который передает буфер DataTX в UART1.
//    На плате должны быть соединены UART1_TX -> UART2_RX, поэтому данные из UART1 приходят в UART2.
//    Канал DMA_Chan_RX забирает данные из UART2 и записывает в DataRX, после чего данные сравниваются.
//    Светодиод LED_CYCLE мигает чтобы показать исполнение программы.
//    На момент передачи данных загораются светодиоды LED_CYCLE и LED_ERR. 
//    Если данные в DataTX совпали с данными в  DataRX, то светодиод LED_ERR выключается, если есть ошибки - остается гореть.


#define BTN_DEBOUNCE_MS 10

#define LED_PERIOD      100000
#define LED_CYCLE       MDRB_LED_1
#define LED_ERR         MDRB_LED_2


//  ----------- Массивы для хранение данных от АЦП  ----------
#define DATA_LEN        1024
#define AVER_DIV_RSH    10

#ifdef DMA_NEED_EXECUTABLE_MEM_RANGE
  //  Для 1986ВЕ1 и 1986ВЕ3Т массивы должны лежать в области памяти доступной для DMA - с адресов 0x2010_0000
  //  Необходимо задать это в скаттер файле, или в настройках модуля *.с
  //  В закладке линкера подключен готовый скаттер файл MDR1986VE1T_sctr.txt.
  static uint8_t DataTX[DATA_LEN] __RAM_EXEC;
  static uint8_t DataRX[DATA_LEN] __RAM_EXEC;

#else
  // Для остальных МК этого не нужно
  static uint8_t DataTX[DATA_LEN];
  static uint8_t DataRX[DATA_LEN];
#endif

//  ----------- Настройка каналов DMA  ----------
#ifndef MDR_DMA_CHMUX_LIKE_VE8
  #define DMA_Chan_TX           MDR_DMA_CH_SREQ_UART1_TX
  #define DMA_Chan_RX           MDR_DMA_CH_SREQ_UART2_RX
#else
  // В ВЕ8, ВК014, ESila для каналов DMA 0..31
  #define DMA_Chan_TX            0
  #define DMA_Chan_RX            1
  // мультиплексором выбираются истоничники запросов 
  #define DMA_Chan_TX_Src           MDR_DMA_CH_SREQ_UART1_TX
  #define DMA_Chan_RX_Src           MDR_DMA_CH_SREQ_UART2_RX
  
  //  В 1986ВЕ8Т, 1923ВК014, ЕСиле обнаружено. что при пустом FIFO_RX UART к каналу DMA стоит активный запрос.
  //  Поэтому при включении канала DMA, этот канал сразу же копирует одно слово из UART->DR, хотя все флаги в UART показывают что данных для чтения нет.
  //  При MDR_LIKE_VE8_BUG_AVOID в функции CheckData() не проверяется первое слово от DMA чтобы сравнить остальные, правильно переданные данные.  
  #define MDR_LIKE_VE8_BUG_AVOID
  
#endif

//  ----------- Выбор пинов UART  ----------
#if defined (USE_MDR1986VK234)
  //  MDRB_1986VK234.h  
  static const MDR_UART_CfgPinGPIO _pinTX_UART1 = {MDRB_UART1_TX_PB0_Port, MDRB_UART1_TX_PB0_Ind, MDRB_UART1_TX_PB0_Func};                                                                        
  static const MDR_UART_CfgPinGPIO _pinRX_UART2 = {MDRB_UART2_RX_PC1_Port, MDRB_UART2_RX_PC1_Ind, MDRB_UART2_RX_PC1_Func};

#elif defined(USE_BOARD_VE8)
  //  см. MDRB_1986VE8.h  
  static const MDR_UART_CfgPinGPIO _pinTX_UART1 = {MDR_GPIO_A,  7, MDR_PIN_FUNC_5};
  static const MDR_UART_CfgPinGPIO _pinRX_UART2 = {MDR_GPIO_A, 10, MDR_PIN_FUNC_5};

 
#elif defined(USE_BOARD_VK014)
  //  см. MDRB_1923VK014.h
  static const MDR_UART_CfgPinGPIO _pinTX_UART1 = {MDR_GPIO_B, 15, MDR_PIN_FUNC_5};
  static const MDR_UART_CfgPinGPIO _pinRX_UART2 = {MDR_GPIO_B, 14, MDR_PIN_FUNC_5};  
  
#elif defined(USE_BOARD_ESila)
  //  см. MDRB_ESila.h
  static const MDR_UART_CfgPinGPIO _pinTX_UART1 = {MDRB_UART1_TX_PB1_Port, MDRB_UART1_TX_PB1_Ind, MDRB_UART1_TX_PB1_Func};
  static const MDR_UART_CfgPinGPIO _pinRX_UART2 = {MDR_GPIO_B, 2, MDR_PIN_FUNC_5}; 

#elif defined(USE_BOARD_VE1)
  //  см. MDRB_1986VE1.h
  static const MDR_UART_CfgPinGPIO _pinTX_UART1 = {MDRB_UART1_TX_PC3_Port,  MDRB_UART1_TX_PC3_Ind,  MDRB_UART1_TX_PC3_Func};
  static const MDR_UART_CfgPinGPIO _pinRX_UART2 = {MDRB_UART2_RX_PD14_Port, MDRB_UART2_RX_PD14_Ind, MDRB_UART2_RX_PD14_Func};  

#endif

//  Для 1923ВК014 старт теста происходит через период мигания светодиода LED_CYCLE,
  //  потому что кнопкок на плате нет.
#ifdef MDRB_HAS_NO_BUTTONS  
  #define NO_BTN_START_PERIOD   10  
  static uint32_t  NoBtn_LedCnt = 0;
  static bool doForcedStart = false;
#endif
static bool CheckStartByPeriod(void);  

#define UART_TX               MDR_UART1ex
#define UART_RX               MDR_UART2ex

static const MDR_UART_CfgPinsGPIO UART_TX_Pins = {
  .pPinTX = &_pinTX_UART1,
  .pPinRX = NULL,
};

static const MDR_UART_CfgPinsGPIO UART_RX_Pins = {
  .pPinTX = NULL,
  .pPinRX = &_pinRX_UART2,
};


#define DMA_IRQ_PRIORITY    0

static const MDR_DMA_CfgTransf  cfgDMA_TX = { 
  //  DMA
  .CfgFileds.Mode         = DMA_MODE_Base,
  .CfgFileds.UseBurst     = MDR_Off,
  .CfgFileds.ArbitrCount  = DMA_Arbitr_1,  
  .CfgFileds.DataSize     = MDR_DMA_Data8,
  .CfgFileds.Src_AddrInc  = MDR_DMA_AddrInc8,
  .CfgFileds.Dest_AddrInc = MDR_DMA_AddrIncOff,
  //  NULL for default init
  .Src_ProtAHB  = NULL,
  .Dest_ProtAHB = NULL,
};

static const MDR_DMA_CfgTransf  cfgDMA_RX = { 
  //  DMA
  .CfgFileds.Mode         = DMA_MODE_Base,
  .CfgFileds.UseBurst     = MDR_Off,
  .CfgFileds.ArbitrCount  = DMA_Arbitr_1,  
  .CfgFileds.DataSize     = MDR_DMA_Data8,
  .CfgFileds.Src_AddrInc  = MDR_DMA_AddrIncOff,
  .CfgFileds.Dest_AddrInc = MDR_DMA_AddrInc8,
  //  NULL for default init
  .Src_ProtAHB  = NULL,
  .Dest_ProtAHB = NULL,
};

//  ----------- Настройки UART  ----------
static MDR_UART_Cfg CfgUART = 
{
  .cfgBase.WordLength   = MDR_UART_WordLen8,
  .cfgBase.Parity  = UART_Parity_Off,
  .cfgBase.useFIFO = MDR_Off, //MDR_On,
  //  Some Options, инициализировать нулем если опции не нужны
  .cfgBase.Options.Value = 0,
  
  //  IRQ Enable
  .pCfgIRQ = NULL,
  //  DMA Enable
  .pCfgDMA = NULL, 
  //  IrDA
  .pCfgIrDA = NULL,
  //  Modem Options
  .pCfgModem = NULL,
};


//  ----------- Application  ----------
static MDR_DMA_ChCtrl RestartCtrl_TX;
static MDR_DMA_ChCtrl RestartCtrl_RX;

static bool DMA_CompletedTX;
static bool DMA_CompletedRX;
static bool DMA_DoCheckData = false;

void ClearData(void);
bool CheckData(void);
void CyclicLedFlash(void);

#ifndef MDR_DMA_IRQ_LIKE_VE8 
  void DMA_IRQHandler(void);
#else
  void DMA_DONE0_IRQHandler(void);
  void DMA_DONE1_IRQHandler(void);
#endif

int main(void)
{
  uint32_t freqCPU_Hz;
  bool     firstStart = true;

#ifdef USE_MDR1923VK014 
  MDR_Delay_ms(4000, HSI_FREQ_HZ);
#endif   
  
  //  Максимальная скорость тактирования
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDRB_CLK_PLL_HSE_RES_MAX;
  MDR_CPU_SetClock_PLL_HSE(&cfgPLL_HSE, true);
  
  //  Инициализация кнопок и LCD экрана
  freqCPU_Hz = MDR_CPU_GetFreqHz(true);
  MDRB_Buttons_Init(BTN_DEBOUNCE_MS, freqCPU_Hz);
  MDRB_LED_Init(LED_CYCLE | LED_ERR);

  //  Для 1986VE4,VE214,VE234 частота UART_Clock формируется мультиплексорами
  //  В VE214 отдельный выбор частоты с делителем для каждого из блоков UART, SSP, Timer
  //  В остальных МК UART_Clock формируется только из HCLK (равной CPU_Clock) - выбор источника не требуется
#ifdef MDR_PER_CLOCK_SELF_TIM_UART_SSP  
  MDR_SetClock_Uart1(MDR_PER_PLLCPUo);
  MDR_SetClock_Uart2(MDR_PER_PLLCPUo);
#elif defined (MDR_PER_CLK_LIKE_VE4)
  MDR_SetClock_UartTimSSP(MDR_PER_PLLCPUo);
#endif 

  //  Подача UART_Clock
  MDR_UARTex_SetUartClock_InpPLLCPU(UART_TX, MDR_Div128P_div1);
  MDR_UARTex_SetUartClock_InpPLLCPU(UART_RX, MDR_Div128P_div1);
  //  Инициализация блока с высчитыванием cfgBaud по входным параметрам.
  MDR_UARTex_Init(UART_TX, &CfgUART, UART_BAUD_921600, freqCPU_Hz);  
  MDR_UARTex_Init(UART_RX, &CfgUART, UART_BAUD_921600, freqCPU_Hz);
  //  Настройка выводов GPIO
  MDR_UART_InitPinsGPIO(&UART_TX_Pins, MDR_PIN_FAST);
  MDR_UART_InitPinsGPIO(&UART_RX_Pins, MDR_PIN_FAST);

  //  UART Enable DMA call
  MDR_UART_TX_DMA_Enable(UART_TX->UARTx);  
  MDR_UART_RX_DMA_Enable(UART_RX->UARTx);

  //  DMA
  MDR_DMA_Init();
  RestartCtrl_TX = MDR_DMA_InitTransfPri(DMA_Chan_TX, (uint32_t)DataTX, (uint32_t)&(UART_TX->UARTx)->DR, DATA_LEN, &cfgDMA_TX);
  RestartCtrl_RX = MDR_DMA_InitTransfPri(DMA_Chan_RX, (uint32_t)&(UART_RX->UARTx)->DR, (uint32_t)DataRX, DATA_LEN, &cfgDMA_RX);
  
  //  Select PeriphEvents to DMA_Channels
#ifdef MDR_DMA_CHMUX_LIKE_VE8  
  MDR_DMA_SetChannelSource(DMA_Chan_TX, DMA_Chan_TX_Src);
  MDR_DMA_SetChannelSource(DMA_Chan_RX, DMA_Chan_RX_Src);
#endif  
  
  //  Enable IRQ
#ifndef MDR_DMA_IRQ_LIKE_VE8  
  MDR_DMA_EnableIRQ(DMA_IRQ_PRIORITY);
#else  
  MDR_DMA_EnableIRQ(DMA_Chan_TX, DMA_IRQ_PRIORITY);
  MDR_DMA_EnableIRQ(DMA_Chan_RX, DMA_IRQ_PRIORITY);
#endif  
  
  //  Start DMA_RX channed
  MDR_DMA_StartChannel(DMA_Chan_RX, false, false, true);

  while (1)
  {
    if (MDRB_BntClicked_Up(true) || CheckStartByPeriod())
    {
      MDRB_LED_Set(LED_CYCLE | LED_ERR, 1);
      
      //  Restart new transfer
      ClearData();      
      DMA_CompletedTX = false;
      DMA_CompletedRX = false;
      
      //  Run DMA Transfer
      if (firstStart)
      {
        MDR_DMA_StartChannel(DMA_Chan_TX, false, false, true);  //  Start transfer
        firstStart = false;
      }
      else
      {
        MDR_UART_ClearRxFIFO(UART_RX->UARTx);
        
        MDR_DMA_InitNextCyclePri(DMA_Chan_RX, RestartCtrl_RX);
        MDR_DMA_InitNextCyclePri(DMA_Chan_TX, RestartCtrl_TX);
        MDR_DMA_ReStartChannel(DMA_Chan_RX);
        MDR_DMA_ReStartChannel(DMA_Chan_TX);                    //  Start transfer
      }
    }
    
    if (DMA_DoCheckData)
    {      
      if (CheckData())
        MDRB_LED_Set(LED_ERR, 0);
      DMA_DoCheckData = false;
    }
    
    CyclicLedFlash();
  }
}

#ifndef MDR_DMA_IRQ_LIKE_VE8 
  void DMA_IRQHandler(void)
  {
    if (!DMA_CompletedTX)
      if (MDR_DMA_GetChannelCompleted(DMA_Chan_TX))
      {
        MDR_DMA_StopChannel(DMA_Chan_TX);
        DMA_CompletedTX = true;
      }

    if (!DMA_CompletedRX)
      if (MDR_DMA_GetChannelCompleted(DMA_Chan_RX))
      {
        MDR_DMA_StopChannel(DMA_Chan_RX);
        DMA_CompletedRX = true;
      }
      
    DMA_DoCheckData = DMA_CompletedTX && DMA_CompletedRX;
  }
#else
  void DMA_DONE0_IRQHandler(void)
  {
    if (!DMA_CompletedTX)
      if (MDR_DMA_GetChannelCompleted(DMA_Chan_TX))
      {
        MDR_DMA_StopChannel(DMA_Chan_TX);
        DMA_CompletedTX = true;
      }
    DMA_DoCheckData = DMA_CompletedTX && DMA_CompletedRX;    
  }

  void DMA_DONE1_IRQHandler(void)
  {
    if (!DMA_CompletedRX)
      if (MDR_DMA_GetChannelCompleted(DMA_Chan_RX))
      {
        MDR_DMA_StopChannel(DMA_Chan_RX);
        DMA_CompletedRX = true;
      }
    
    DMA_DoCheckData = DMA_CompletedTX && DMA_CompletedRX;    
  }
#endif


void ClearData(void)
{
  static uint32_t nextData = 0;
  uint32_t i;
  
  for (i = 0; i < DATA_LEN; ++i)
  {
    DataTX[i] = (uint8_t)MDR_ToPseudoRand(nextData++);
    DataRX[i] = 0;
  }
}

bool CheckData(void)
{
  uint32_t i;
  uint32_t cntErr = 0;

#ifndef MDR_LIKE_VE8_BUG_AVOID
  for (i = 0; i < DATA_LEN; ++i)
    if (DataTX[i] != DataRX[i])
      ++cntErr;
#else
  for (i = 0; i < (DATA_LEN - 1); ++i)
    if (DataTX[i] != DataRX[i + 1])
      ++cntErr;    
#endif    
    
  return cntErr == 0;
}

void CyclicLedFlash(void)
{
  static uint32_t cnt = 0;
  
  ++cnt;
  if (cnt > LED_PERIOD)
  {
    cnt = 0;
    MDRB_LED_Toggle(LED_CYCLE);
    
#ifdef MDRB_HAS_NO_BUTTONS  
    ++NoBtn_LedCnt;
    if (NoBtn_LedCnt >= NO_BTN_START_PERIOD)
    {
      NoBtn_LedCnt = 0;
      doForcedStart = true;
    }
#endif
  }
}

bool CheckStartByPeriod(void)
{
#ifdef MDRB_HAS_NO_BUTTONS  
  if (doForcedStart)
  {
    doForcedStart = false;
    // Задержка чтобы увидеть что тест перезапускается
    MDR_Delay(1000000);
    return true;
  }
  else
    return false;
#else
  return false;    
#endif
}

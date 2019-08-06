#include <MDR_RST_Clock.h>
#include <MDR_PER_Clock.h>
#include <MDRB_Buttons.h>
#include <MDRB_LEDs.h>
#include <MDR_Funcs.h>
#include <MDR_DMA.h>
#include <MDR_UART.h>

#include <MDRB_UART_PinSelect.h>

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
  uint8_t DataTX[DATA_LEN] __RAM_EXEC;
  uint8_t DataRX[DATA_LEN] __RAM_EXEC;

#else
  // Для остальных МК этого не нужно
  uint8_t DataTX[DATA_LEN];
  uint8_t DataRX[DATA_LEN];
#endif

//  ----------- Настройка каналов DMA  ----------
#define DMA_Chan_TX           MDR_DMA_CH_SREQ_UART1_TX
#define DMA_Chan_RX           MDR_DMA_CH_SREQ_UART2_RX

#define UART_TX               MDR_UART1ex
#define UART_RX               MDR_UART2ex

MDR_UART_CfgPinsGPIO UART_TX_Pins = {
  .pPinTX = &_pinTX_UART1,
  .pPinRX = NULL,
};

MDR_UART_CfgPinsGPIO UART_RX_Pins = {
  .pPinTX = NULL,
  .pPinRX = &_pinRX_UART2,
};


#define DMA_IRQ_PRIORITY    0

const MDR_DMA_CfgTransf  cfgDMA_TX = { 
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

const MDR_DMA_CfgTransf  cfgDMA_RX = { 
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
MDR_UART_Cfg CfgUART = 
{
  .cfgBase.WordLength   = MDR_UART_WordLen8,
  .cfgBase.Parity  = UART_Parity_Off,
  .cfgBase.useFIFO = MDR_On,
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
MDR_DMA_ChCtrl RestartCtrl_TX;
MDR_DMA_ChCtrl RestartCtrl_RX;

bool DMA_CompletedTX;
bool DMA_CompletedRX;
bool DMA_DoCheckData = false;

void ClearData(void);
bool CheckData(void);
void CyclicLedFlash(void);


int main(void)
{
  uint32_t freqCPU_Hz;
  bool     firstStart = true;

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

  //  Инициализация блока с высчитыванием cfgBaud по входным параметрам.
  MDR_UARTex_Init(UART_TX, &CfgUART, UART_BAUD_921600, freqCPU_Hz);  
  MDR_UARTex_Init(UART_RX, &CfgUART, UART_BAUD_921600, freqCPU_Hz);

  MDR_UART_InitPinsGPIO(&UART_TX_Pins, MDR_PIN_FAST);
  MDR_UART_InitPinsGPIO(&UART_RX_Pins, MDR_PIN_FAST);

  //  UART Enable DMA call
  MDR_UART_TX_DMA_Enable(UART_TX->UARTx);  
  MDR_UART_RX_DMA_Enable(UART_RX->UARTx);

  //  DMA
  MDR_DMA_Init();
  RestartCtrl_TX = MDR_DMA_InitTransfPri(DMA_Chan_TX, (uint32_t)DataTX, (uint32_t)&(UART_TX->UARTx)->DR, DATA_LEN, &cfgDMA_TX);
  RestartCtrl_RX = MDR_DMA_InitTransfPri(DMA_Chan_RX, (uint32_t)&(UART_RX->UARTx)->DR, (uint32_t)DataRX, DATA_LEN, &cfgDMA_RX);
  //  Start IRQ and RX channed
  MDR_DMA_EnableIRQ(DMA_IRQ_PRIORITY);
  MDR_DMA_StartChannel(DMA_Chan_RX, false, false, true);

  while (1)
  {
    if (MDRB_BntClicked_Up(true))
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



void ClearData(void)
{
  static uint32_t nextData = 0;
  uint32_t i;
  
  for (i = 0; i < DATA_LEN; ++i)
  {
    DataTX[i] = MDR_ToPseudoRand(nextData++);
    DataRX[i] = 0;
  }
}

bool CheckData(void)
{
  uint32_t i;
  uint32_t cntErr = 0;
  
  for (i = 0; i < DATA_LEN; ++i)
    if (DataTX[i] != DataRX[i])
      ++cntErr;

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
  }
}

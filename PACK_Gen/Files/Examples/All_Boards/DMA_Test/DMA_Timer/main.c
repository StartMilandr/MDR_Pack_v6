#include <MDR_RST_Clock.h>
#include <MDR_PER_Clock.h>
#include <MDRB_LEDs.h>
#include <MDR_Funcs.h>
#include <MDR_DMA.h>
#include <MDR_UART.h>
#include <MDR_Timer.h>

#include <MDRB_UART_PinSelect.h>


#define LED_CYCLE       MDRB_LED_1

//  -----------  Данные передаваемые по UART  ----------
#define DATA_LEN        10

#ifdef DMA_NEED_EXECUTABLE_MEM_RANGE
  //  Для 1986ВЕ1 и 1986ВЕ3Т массивы должны лежать в области памяти доступной для DMA - с адресов 0x2010_0000
  //  Необходимо задать это в скаттер файле, или в настройках модуля *.с
  //  В закладке линкера подключен готовый скаттер файл MDR1986VE1T_sctr.txt.
  static uint8_t DataTX[DATA_LEN] __RAM_EXEC;
#else
  // Для остальных МК этого не нужно
  static uint8_t DataTX[DATA_LEN];
#endif

//  ----------- Настройка каналов DMA  ----------
#define DMA_Chan_TX           MDR_DMA_CH_SREQ_TIM1
#define UART_TX               MDR_UART1ex


static MDR_UART_CfgPinsGPIO UART_TX_Pins = {
  .pPinTX = &_pinTX_UART1,
  .pPinRX = NULL,
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

//  ----------- Настройки UART  ----------
static MDR_UART_Cfg CfgUART = 
{
  .cfgBase.WordLength   = MDR_UART_WordLen8,
  .cfgBase.Parity  = UART_Parity_Off,
  .cfgBase.useFIFO = MDR_Off,
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
  
void DMA_IRQHandler(void);


//  ----------- Application  ----------
static MDR_DMA_ChCtrl RestartCtrl_TX;


int main(void)
{
  uint32_t freqCPU_Hz;
  uint32_t i;
  uint_tim timPeriod;
  uint16_t timPSG;
  
  //  Максимальная скорость тактирования
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDRB_CLK_PLL_HSE_RES_MAX;
  MDR_CPU_SetClock_PLL_HSE(&cfgPLL_HSE, true);
  
  //  Инициализация светодиода
  freqCPU_Hz = MDR_CPU_GetFreqHz(true);
  MDRB_LED_Init(LED_CYCLE);

  //  Для 1986VE4,VE214,VE234 частоты UART_Clock и TIM_Clock формируется мультиплексорами
  //  В остальных МК UART_Clock формируется только из HCLK (равной CPU_Clock) - выбор источника не требуется
#ifdef MDR_PER_CLOCK_LIKE_VE4  
  MDR_SetClock_UartTimSSP(MDR_PER_PLLCPUo);
#endif 

  //  Инициализация блока с высчитыванием cfgBaud по входным параметрам.
  MDR_UARTex_Init(UART_TX, &CfgUART, UART_BAUD_9600, freqCPU_Hz);  
  MDR_UART_InitPinsGPIO(&UART_TX_Pins, MDR_PIN_FAST);

  //  Данные для посылки по UART
  for (i = 0; i < DATA_LEN; ++i)
    DataTX[i] = (uint8_t)('0' + i);

  //  DMA
  MDR_DMA_Init();
  RestartCtrl_TX = MDR_DMA_InitTransfPri(DMA_Chan_TX, (uint32_t)DataTX, (uint32_t)&(UART_TX->UARTx)->DR, DATA_LEN, &cfgDMA_TX);
  //  Start DMA_TX
  MDR_DMA_EnableIRQ(DMA_IRQ_PRIORITY);
  MDR_DMA_StartChannel(DMA_Chan_TX, false, false, true);

  //  Timer Period 1sec
  MDR_Timer_CalcPeriodAndPSG(1, freqCPU_Hz, &timPeriod, &timPSG);  
  MDR_Timer_InitPeriod(MDR_TIMER1ex, MDR_Div128P_div1, timPSG, timPeriod, false);
  MDR_Timer_DMA_Enable_CntArr(MDR_TIMER1ex->TIMERx);
  MDR_Timer_Start(MDR_TIMER1ex);

  while (1)
  {
  }
}

void DMA_IRQHandler(void)
{ 
  //  Перезапуск нового цикла DMA
  MDR_DMA_RunNextCyclePri(DMA_Chan_TX, RestartCtrl_TX);
  
  // Индикация на светодиод
  MDRB_LED_Toggle(LED_CYCLE);
}




#include <MDR_RST_Clock.h>
#include <MDR_PER_Clock.h>
#include <MDRB_Buttons.h>
#include <MDRB_LCD.h>
#include <MDR_Funcs.h>
#include <MDR_DMA.h>
#include <MDR_ADC.h>

#define BTN_DEBOUNCE_MS 10

//  ---- Настройка АЦП ----
static const MDR_ADCx_CfgBase _CfgADCx_clkCPU = {
  .ClockSource    = MDR_ADC_CLK_ADC,
  .CPU_ClockDiv   = MDR_ADC_CPU_div2048,
  .MagRefExternal = MDR_Off,             // GND..AUcc
  .SwitchDelay_GO = MDR_ADC_DelayGO_7    // Delay between continuous start
};

static const MDR_ADC_Config _cfgAdc = 
{
  .pCfgThermo = NULL,
  
  .pCfgADC1   = &_CfgADCx_clkCPU,
  .pCfgLim1   = NULL,
  .pCfgIRQ1   = NULL,

#ifdef MDR_HAS_ADC2
  .pCfgADC2   = NULL,
  .pCfgLim2   = NULL,
  .pCfgIRQ2   = NULL,  
  .pCfgSync   = NULL,
#endif 
  //  flags
  .ActivateNVIC_IRQ = MDR_Off,
  .Priority_IRQ = 0
};


//  ----------- Массивы для хранение данных от АЦП  ----------
#define DATA_LEN        1024
#define AVER_DIV_RSH    10

#ifdef DMA_NEED_EXECUTABLE_MEM_RANGE
  //  Для 1986ВЕ1 и 1986ВЕ3Т массивы должны лежать в области памяти доступной для DMA - с адресов 0x2010_0000
  //  Необходимо задать это в скаттер файле, или в настройках модуля *.с
  //  В закладке линкера подключен готовый скаттер файл MDR1986VE1T_sctr.txt.
  uint16_t DataPri[DATA_LEN] __RAM_EXEC;
  uint16_t DataAlt[DATA_LEN] __RAM_EXEC;

#else
  // Для остальных МК этого не нужно
  uint16_t DataPri[DATA_LEN] __RAM_EXEC;
  uint16_t DataAlt[DATA_LEN] __RAM_EXEC;
#endif

//  ----------- Настройка канала DMA  ----------
#ifdef MDR_DMA_CH_SREQ_ADC1
  #define DMA_Chan            MDR_DMA_CH_SREQ_ADC1
#else
  #define DMA_Chan            MDR_DMA_CH_REQ_ADC1
#endif

#define DMA_IRQ_PRIORITY    0

const MDR_DMA_CfgTransf  cfgDMA_ADC = { 
  //  DMA
  .CfgFileds.Mode         = DMA_MODE_PingPong,
  .CfgFileds.UseBurst     = MDR_Off,
  .CfgFileds.ArbitrCount  = DMA_Arbitr_1,  
  .CfgFileds.DataSize     = MDR_DMA_Data16,
  .CfgFileds.Src_AddrInc  = MDR_DMA_AddrIncOff,
  .CfgFileds.Dest_AddrInc = MDR_DMA_AddrInc16,
  //  NULL for default init
  .Src_ProtAHB  = NULL,
  .Dest_ProtAHB = NULL,
};

MDR_DMA_ChCtrl RestartCtrlPri;
MDR_DMA_ChCtrl RestartCtrlAlt;
bool DoProcessDataPri = false;
bool DoProcessDataAlt = false;
bool DoStop  = false;
bool Stopped = false;

uint32_t AverADC_Pri;
uint32_t AverADC_Alt;

uint32_t CalcAverData(uint16_t *data);
void LCD_PrintResult(uint32_t valuePri, uint32_t valueAlt, uint32_t ind);
void LCD_PrintStopped(void);
void DMA_IRQHandler(void);

void _checkDMA(void)
{
  volatile uint32_t ctrlDMA_Pri = MDR_DMA_CtrlTablePri(DMA_Chan).Control.Value;
  volatile uint32_t ctrlDMA_Alt = MDR_DMA_CtrlTableAlt(DMA_Chan).Control.Value;
}

int main(void)
{
  uint32_t freqCPU_Hz;

  //  Максимальная скорость тактирования
  MDR_CPU_SetClock_HSE_Max(MDR_Off);
  
  //  Инициализация кнопок и LCD экрана
  freqCPU_Hz = MDR_CPU_GetFreqHz(true);
  MDRB_Buttons_Init(BTN_DEBOUNCE_MS, freqCPU_Hz);
  MDRB_LCD_Init(freqCPU_Hz);

  //  DMA
  MDR_DMA_Init();
  RestartCtrlPri = MDR_DMA_InitTransfPri(DMA_Chan, (uint32_t)&MDR_ADC->ADC1_Result, (uint32_t)DataPri, DATA_LEN, &cfgDMA_ADC);
  RestartCtrlAlt = MDR_DMA_InitTransfAlt(DMA_Chan, (uint32_t)&MDR_ADC->ADC1_Result, (uint32_t)DataAlt, DATA_LEN, &cfgDMA_ADC);
  MDR_DMA_EnableIRQ(DMA_IRQ_PRIORITY);
  MDR_DMA_StartChannel(DMA_Chan, false, false, true);

  // ADC
  MDR_ADC_SetClock_CPU_C1(MDR_CLK_div256);
  MDR_ADC_PinsInitByMask(MDRB_ADC_TUNE_PORT, MDRB_ADC_TUNE_PIN);  
  MDR_ADC_Init(&_cfgAdc);
  MDR_ADC_StartSignal(MDR_ADC1, MDRB_ADC_CH_TUNE, true, NULL);
  
  while (1)
  {
    if (DoProcessDataPri)
    {
      AverADC_Pri = CalcAverData(DataPri);
      LCD_PrintResult(AverADC_Pri, AverADC_Alt, 1);
      
      DoProcessDataPri = false;
    }
      
    if (DoProcessDataAlt)
    {
      AverADC_Alt = CalcAverData(DataAlt);
      LCD_PrintResult(AverADC_Pri, AverADC_Alt, 2);
      
      DoProcessDataAlt = false;
    }
    
    //  Остановка работы при окончании цикла DMA
    //  АЦП остается работать
    if (MDRB_BntClicked_Up(true))
      DoStop = true;

    //  Возобновление работы
    if (MDRB_BntClicked_Right(true))
    {
      MDR_DMA_InitNextCyclePri(DMA_Chan, RestartCtrlPri);
      MDR_DMA_InitNextCycleAlt(DMA_Chan, RestartCtrlAlt);
      MDR_DMA_ReStartChannel(DMA_Chan);
      Stopped = false;
    }        
    
    //  Индикация остановки работы.
    if (Stopped)
    {
      LCD_PrintStopped(); 
      Stopped = false;
    }
    
    _checkDMA();
  }

}

void DMA_IRQHandler(void)
{
  if (MDR_DMA_GetCycleCompletedPri(DMA_Chan) && !DoStop)
  {
    MDR_DMA_InitNextCyclePri(DMA_Chan, RestartCtrlPri);
    DoProcessDataPri = true;
  }
  else if (MDR_DMA_GetCycleCompletedAlt(DMA_Chan) && !DoStop)
  {
    MDR_DMA_InitNextCycleAlt(DMA_Chan, RestartCtrlAlt);
    DoProcessDataAlt = true;
  }
  
  if (MDR_DMA_GetChannelCompleted(DMA_Chan))
  {
    MDR_DMA_StopChannel(DMA_Chan);
    DoStop  = false;
    Stopped = true;
  }
}

uint32_t CalcAverData(uint16_t *data)
{
  uint32_t i;
  uint32_t sum = 0;
  
  for (i = 0; i < DATA_LEN; ++i)
    sum += data[i] & 0xFFFUL;
  
  return (sum >> AVER_DIV_RSH);
}

void LCD_PrintResult(uint32_t valuePri, uint32_t valueAlt, uint32_t ind)
{
  static char message[20];  
  sprintf(message , "%x %x %d", valuePri, valueAlt, ind);  
  
#ifndef LCD_IS_7SEG_DISPLAY
  MDRB_LCD_Print (message, 3);
#else
  MDRB_LCD_Print (message);
#endif
}

void LCD_PrintStopped(void)
{
#ifndef LCD_IS_7SEG_DISPLAY
  MDRB_LCD_Print ("Stopped", 3);
#else
  MDRB_LCD_Print ("FFFF");
#endif
}

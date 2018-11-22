#include "test_ADC_Interfs.h"

//  =======================   ОПИСАНИЕ    ====================
//  Тест измеряет выбранные маской (Cfg_PinChannelsSelected в ADC_Cfg.h) каналы в непрерывном режиме.
//  Значения с АЦП считываются в прерывании по готовности данных в АЦП.
//  Количество измерений, равное количеству переключаемых каналов, сохраняется в массив ADC_Data[] вместе с текущим статусом ADC_Status[].
//  После этого, непрерывное измерение каналов выключается (прерывания перестают генерироваться).
//  Далее можно выбрать канал, сохраненные значение и статус которого, будут выведены на экран LCD.
//  Кнопки:
//    UP - поменять тест - исполнение ADC1 или ADC2
//    Down - запустить измерение выбраных каналов.
//    Right - Поменять канал и показать значение сигнала и статуса. НАЖИМАТЬ для отображения данных!
//
//  При переключении каналов измерять сигналы с термосенсора нельзя, поскольку требуется отдельная инициализация блока термосенсора и деинициализация.

//  Отдельный выбор частоты блока для теста, если не задан глобальный в ADC_Cfg.h
#ifndef USE_ADC_CLOCK
  #define USE_ADC_CLOCK   0
#endif

//  Текущий ADC
static MDR_ADCx_ItemType *activeADC = MDR_ADC1;
//static MDR_ADC_PinChannel activeChannel;
static uint32_t activeChannel;

//  Значения каналов
static uint32_t DataCount = MDR_ADC_PIN_CHANNEL_COUNT;
static uint32_t DataIndex;
static uint32_t ADC_Data[MDR_ADC_PIN_CHANNEL_COUNT];
static uint32_t ADC_Status[MDR_ADC_PIN_CHANNEL_COUNT];
static bool testStarted = false;
static uint32_t RunIndex;

static void ClearData(void);

//  LCD Show Result
static void LCD_ShowInit(void);
static void LCD_ShowResult(void);

//  Test Interface functions
static void TestCycleSel_ADC1_Init(void);
static void TestCycleSel_ADCx_Finit(void);

#ifdef MDR_HAS_ADC2
static void TestCycleSel_ADC2_Init(void);
#endif

static void TestCycleSel_Change(void);
static void TestCycleSel_Exec(void);
static void TestCycleSel_HandleIRQ(void);

TestInterface TI_ADC1_CyclicSelChannels = {
  .funcInit       = TestCycleSel_ADC1_Init,
  .funcFinit      = TestCycleSel_ADCx_Finit,
  .funcChange     = TestCycleSel_Change,
  .funcExec       = TestCycleSel_Exec,
  .funcHandlerIrq = TestCycleSel_HandleIRQ
};

#ifdef MDR_HAS_ADC2
TestInterface TI_ADC2_CyclicSelChannels = {
  .funcInit       = TestCycleSel_ADC2_Init,
  .funcFinit      = TestCycleSel_ADCx_Finit,
  .funcChange     = TestCycleSel_Change,
  .funcExec       = TestCycleSel_Exec,
  .funcHandlerIrq = TestCycleSel_HandleIRQ
};
#endif

static void Test_Init(MDR_ADCx_ItemType *selADC)
{
  RunIndex = 0;
  activeChannel = 0;
  DataCount = Cfg_PinSignalCount;
  activeADC = selADC;
  LCD_ShowInit();
  
#if USE_ADC_CLOCK
  MDR_ADC_Change_CfgBase(activeADC, &_CfgADCx_clkADC);
#endif  
  
  // Включение прерываний по завершению преобразования
  MDR_ADC_Change_CfgIRQ(activeADC, &_CfgIRQ_OnResult); 
}

static void TestCycleSel_ADC1_Init(void)
{
  Test_Init(MDR_ADC1);
}

#ifdef MDR_HAS_ADC2
static void TestCycleSel_ADC2_Init(void)
{
  Test_Init(MDR_ADC2);
}
#endif

static void TestCycleSel_ADCx_Finit(void)
{
  // Возвращение к базовой настройке
  MDR_ADC_Change_CfgIRQ(activeADC, &_CfgIRQ_Off);
  
#if USE_ADC_CLOCK
  MDR_ADC_Change_CfgBase(activeADC, &_CfgADCx_clkCPU);
#endif   
}


static void TestCycleSel_Change(void)
{
  ++activeChannel;
  if (activeChannel >= DataCount)
    activeChannel = 0;
  
  LCD_ShowResult();
}

static void TestCycleSel_Exec(void)
{ 
  ClearData();
  ++RunIndex;
  
  DataIndex = 0;
  testStarted = true;
  MDR_ADC_ClearStatus(activeADC);
  MDR_ADC_StartSelected(activeADC, Cfg_PinChannelsSelected, true, NULL);
}

static void TestCycleSel_HandleIRQ(void)
{
  if (!testStarted)
    return;
  
  ADC_Data[DataIndex] = MDR_ADC_GetResult(activeADC).Result;
  ADC_Status[DataIndex] = MDR_ADC_GetStatus(activeADC).Status;
  ++DataIndex;
  if (DataIndex >= DataCount)
  {  
    MDR_ADC_Stop(activeADC);
    testStarted = false;
    
    LCD_ShowResult();
  }
}

void ClearData(void)
{
  uint32_t i;
  for (i = 0; i < MDR_ADC_PIN_CHANNEL_COUNT; ++i)
    ADC_Data[i] = 0;
  
  DataIndex = 0;
}

static char message[64];

void LCD_ShowInit(void)
{
  uint32_t indADC;
  if (activeADC == MDR_ADC1)
    indADC = 1;
  else
    indADC = 2;
    
#ifndef LCD_IS_7SEG_DISPLAY  
  MDRB_LCD_Clear();
  sprintf(message , "C_ADC%d SelCh=x%x ", indADC, Cfg_PinChannelsSelected.Select);
  MDRB_LCD_Print (message, LED_LINE_INIT);
#else
  sprintf(message , "CF%d %x ", indADC, Cfg_PinChannelsSelected.Select);
  MDRB_LCD_Print (message);
#endif  
  
}

void LCD_ShowResult(void)
{  
  MDR_ADC_Result resADC;
  
  resADC.Result = ADC_Data[activeChannel];
  
#ifndef LCD_IS_7SEG_DISPLAY      
  sprintf(message , "Ch=%d  Val=%d ", resADC.Flags.Channel, resADC.Flags.Value);
  MDRB_LCD_Print (message, LED_LINE_RESULT);
  
  sprintf(message , "Run=%d  St=x%x", RunIndex, ADC_Status[activeChannel]);
  MDRB_LCD_Print (message, LED_LINE_INFO);
  
  sprintf(message , "Cfg1=%x", MDR_ADC->ADC1_Cfg);
  MDRB_LCD_Print (message, LED_LINE_CFG1);  
  sprintf(message , "Cfg2=%x", MDR_ADC->ADC2_Cfg);
  MDRB_LCD_Print (message, LED_LINE_CFG2);
#else
  #if LED7_SHOW_INFO
    sprintf(message , "%x  %x", ADC_Status[activeChannel], MDR_ADC->ADC1_Cfg);
    MDRB_LCD_Print (message);  
    MDR_Delay_ms(LED7_DELAY_MS, MDR_CPU_GetFreqHz(false));
  #endif
  
  sprintf(message , "%d %d ", resADC.Flags.Channel, resADC.Flags.Value);
  MDRB_LCD_Print (message);  
#endif  
}


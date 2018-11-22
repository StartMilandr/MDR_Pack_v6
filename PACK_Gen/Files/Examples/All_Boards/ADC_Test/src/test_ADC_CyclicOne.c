#include "test_ADC_Interfs.h"

//  =======================   ОПИСАНИЕ    ====================
//  Тест измеряет один и тот же сигнал (activeSignal) несколько раз (ONE_CHANNEL_AVER в ADC_Cfg.h). Для этого запускается непрерывное измерение этого канала.
//  Значения с АЦП считываются в прерывании по готовности данных в АЦП.
//  При накоплении ONE_CHANNEL_AVER измерений в массив ADC_Data[], цикличное измерение канала выключается (прерывания перестают генерироваться).
//  После этого усредненный результат выводится на экран LCD.
//  Кнопки:
//    UP - поменять тест - исполнение ADC1 или ADC2
//    Right - Поменять канал, который будет измеряться
//    Down - запустить описанный выше цикл измерения для выбранного канала. НАЖИМАТЬ для обновления данных!
//  Сигналы выбираются в ADC_Cfg.h, можно измерять сигналы от термосенсора.

//  Отдельный выбор частоты блока для теста, если не задан глобальный в ADC_Cfg.h
#ifndef USE_ADC_CLOCK
  #define USE_ADC_CLOCK   0
#endif


//  Текущий ADC
static MDR_ADCx_ItemType *activeADC = MDR_ADC1;

//  Значения каналов
static uint32_t DataCount;
static uint32_t DataIndex;
static uint32_t ADC_Data[ONE_CHANNEL_AVER];
static bool testStarted = false;

static MDR_ADC_Status ADC_LastSatus;

static void ClearData(void);

//  LCD Show Result
static void LCD_ShowInit(void);
static void LCD_ShowResult(void);

//  Test Interface functions
static void TestCycleOne_ADC1_Init(void);
static void TestCycleOne_ADCx_Finit(void);

#ifdef MDR_HAS_ADC2
  static void TestCycleOne_ADC2_Init(void); 
#endif

static void TestCycleOne_Change(void);
static void TestCycleOne_Exec(void);
static void TestCycleOne_HandleIRQ(void);

TestInterface TI_ADC1_CyclicOneChannel = {
  .funcInit       = TestCycleOne_ADC1_Init,
  .funcFinit      = TestCycleOne_ADCx_Finit,
  .funcChange     = TestCycleOne_Change,
  .funcExec       = TestCycleOne_Exec,
  .funcHandlerIrq = TestCycleOne_HandleIRQ
};

#ifdef MDR_HAS_ADC2
TestInterface TI_ADC2_CyclicOneChannel = {
  .funcInit       = TestCycleOne_ADC2_Init,
  .funcFinit      = TestCycleOne_ADCx_Finit,
  .funcChange     = TestCycleOne_Change,
  .funcExec       = TestCycleOne_Exec,
  .funcHandlerIrq = TestCycleOne_HandleIRQ
};
#endif

static void Test_Init(MDR_ADCx_ItemType *selADC)
{
  activeADC = selADC;
  DataCount = ONE_CHANNEL_AVER;
  
  LCD_ShowInit();

#if USE_ADC_CLOCK
  MDR_ADC_Change_CfgBase(activeADC, &_CfgADCx_clkADC);
#endif  
  
  // Включение прерываний по завершению преобразования
  MDR_ADC_Change_CfgIRQ(activeADC, &_CfgIRQ_OnResult);  
}

static void TestCycleOne_ADC1_Init(void)
{
  Test_Init(MDR_ADC1);
}

#ifdef MDR_HAS_ADC2
static void TestCycleOne_ADC2_Init(void)
{
  Test_Init(MDR_ADC2);
}
#endif

static void TestCycleOne_ADCx_Finit(void)
{
  // Возвращение к базовой настройке
  MDR_ADC_Change_CfgIRQ(activeADC, &_CfgIRQ_Off);
  
#if USE_ADC_CLOCK
  MDR_ADC_Change_CfgBase(activeADC, &_CfgADCx_clkCPU);
#endif    
}


static void TestCycleOne_Change(void)
{
  Cfg_SetNextSignal();
  
  LCD_ShowInit();
}

static void TestCycleOne_Exec(void)
{
  ClearData();
  
  DataIndex = 0;
  testStarted = true;
  MDR_ADC_ClearStatus(activeADC);
  MDR_ADC_StartSignal(activeADC, Cfg_GetActiveSignal(), true, NULL);
}

static void TestCycleOne_HandleIRQ(void)
{
  if (!testStarted)
    return;
  
  ADC_Data[DataIndex] = MDR_ADC_GetResult(activeADC).Result;
  ++DataIndex;
  if (DataIndex >= DataCount)
  { 
    //  Статус сбрасывается при MDR_ADC_Stop, читаем заранее
    ADC_LastSatus = MDR_ADC_GetStatus(activeADC);
    
    MDR_ADC_Stop(activeADC);
    testStarted = false;
    
    LCD_ShowResult();
  }
}

void ClearData(void)
{
  uint32_t i;
  for (i = 0; i < ONE_CHANNEL_AVER; ++i)
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
  
//MDRB_LCD_CapturePins();  
  
#ifndef LCD_IS_7SEG_DISPLAY  
  MDRB_LCD_Clear();
  sprintf(message , "C_ADC%d  Sig=%c ", indADC, Cfg_GetActiveSignalName());
  MDRB_LCD_Print (message, LED_LINE_INIT);
#else
  sprintf(message , "C0%d  %d ", indADC, Cfg_GetActiveSignal());
  MDRB_LCD_Print (message);
#endif
  
  
//MDRB_LCD_ReleasePins();    
}

void LCD_ShowResult(void)
{  
  uint32_t i;
  uint32_t sumVal = 0;
  uint32_t sumCh = 0;
  MDR_ADC_Result resADC;
  
  for (i = 0; i < DataCount; ++i)
  {
    resADC.Result = ADC_Data[i];
    sumVal += resADC.Flags.Value;
    sumCh += resADC.Flags.Channel;
  }
  
  sumVal = sumVal / DataCount;
  sumCh = sumCh / DataCount;
 
#ifndef LCD_IS_7SEG_DISPLAY  
  sprintf(message , "Ch=%d  Val=%d ", sumCh, sumVal);
  MDRB_LCD_Print (message, LED_LINE_RESULT);
   
  sprintf(message , "N=%d  St=x%x", DataCount, ADC_LastSatus.Status);
  MDRB_LCD_Print (message, LED_LINE_INFO);
  
  sprintf(message , "Cfg1=%x", MDR_ADC->ADC1_Cfg);
  MDRB_LCD_Print (message, LED_LINE_CFG1);  
  sprintf(message , "Cfg2=%x", MDR_ADC->ADC2_Cfg);
  MDRB_LCD_Print (message, LED_LINE_CFG2); 
#else
  #if LED7_SHOW_INFO
    sprintf(message , "%x  %x", ADC_LastSatus.Status, MDR_ADC->ADC1_Cfg);
    MDRB_LCD_Print (message);  
    MDR_Delay_ms(LED7_DELAY_MS, MDR_CPU_GetFreqHz(false));
  #endif
  
  sprintf(message , "%d %d ", sumCh, sumVal);
  MDRB_LCD_Print (message);  
#endif
}


#include "test_ADC_Interfs.h"

//  =======================   ОПИСАНИЕ    ====================
//  Тест производит единичные измерения сигналов, выбранных маской (Cfg_PinChannelsSelected в ADC_Cfg.h).
//  Каналы переключаются аппаратно, при запуске следующего измерения в ПО (по кнопке Down).
//  Значение считывается в прерывании об окончании измерения и выводится на LCD/
//  Кнопки:
//    UP - поменять тест
//    Down - не используется
//    Right - Измерить следующий канал. НАЖИМАТЬ для отображения данных!

//  Отдельный выбор частоты блока для теста, если не задан глобальный в ADC_Cfg.h
#ifndef USE_ADC_CLOCK
  #define USE_ADC_CLOCK   0
#endif

//  Текущий ADC
static MDR_ADCx_ItemType *activeADC = MDR_ADC1;

//  Значения сигнала
static MDR_ADC_Result ADC_Data;
static MDR_ADC_Status ADC_Status;
static uint32_t RunIndex;

//  LCD Show Result
static void LCD_ShowInit(void);
static void LCD_ShowResult(void);

//  Test Interface functions
static void TestManualSel_ADC1_Init(void);
static void TestManualSel_ADCx_Finit(void);

#ifdef MDR_HAS_ADC2
static void TestManualSel_ADC2_Init(void);
#endif

static void TestManualSel_Change(void);
static void TestManualSel_Exec(void);
static void TestManualSel_HandleIRQ(void);

TestInterface TI_ADC1_ManualSelChannels = {
  .funcInit       = TestManualSel_ADC1_Init,
  .funcFinit      = TestManualSel_ADCx_Finit,
  .funcChange     = TestManualSel_Change,
  .funcExec       = TestManualSel_Exec,
  .funcHandlerIrq = TestManualSel_HandleIRQ
};

#ifdef MDR_HAS_ADC2
TestInterface TI_ADC2_ManualSelChannels = {
  .funcInit       = TestManualSel_ADC2_Init,
  .funcFinit      = TestManualSel_ADCx_Finit,
  .funcChange     = TestManualSel_Change,
  .funcExec       = TestManualSel_Exec,
  .funcHandlerIrq = TestManualSel_HandleIRQ
};
#endif

static void TestInit(MDR_ADCx_ItemType *ADCx)
{
  RunIndex = 0;
  activeADC = ADCx;
  LCD_ShowInit();
  
#if USE_ADC_CLOCK
  MDR_ADC_Change_CfgBase(activeADC, &_CfgADCx_clkADC);
#endif    
  
  // Включение прерываний по завершению преобразования
  MDR_ADC_Change_CfgIRQ(activeADC, &_CfgIRQ_OnResult);
}

static void TestManualSel_ADC1_Init(void)
{
  TestInit(MDR_ADC1);
}

#ifdef MDR_HAS_ADC2
static void TestManualSel_ADC2_Init(void)
{
  TestInit(MDR_ADC2);
}
#endif

static void TestManualSel_ADCx_Finit(void)
{
  //  Выключение АЦП перед выходом
  MDR_ADC_Stop(activeADC);
  // Возвращение к базовой настройке
  MDR_ADC_Change_CfgIRQ(activeADC, &_CfgIRQ_Off);  
  
#if USE_ADC_CLOCK
  MDR_ADC_Change_CfgBase(activeADC, &_CfgADCx_clkCPU);
#endif    
}

static void TestManualSel_Change(void)
{
  RunIndex = 0;
}

static void TestManualSel_Exec(void)
{  
  MDR_ADC_ClearStatus(activeADC);
  if (RunIndex == 0)
    MDR_ADC_StartSelected(activeADC, Cfg_PinChannelsSelected, false, NULL);
  else
    MDR_ADC_StartNextGo(activeADC);
  
  ++RunIndex;  
}

static void TestManualSel_HandleIRQ(void)
{
  ADC_Data.Result = MDR_ADC_GetResult(activeADC).Result;
  ADC_Status.Status = MDR_ADC_GetStatus(activeADC).Status;
  LCD_ShowResult();
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
  sprintf(message , "M_ADC%d SelCh=x%x ", indADC, Cfg_PinChannelsSelected.Select);
  MDRB_LCD_Print (message, LED_LINE_INIT);
#else
  sprintf(message , "BF%d %x ", indADC, Cfg_PinChannelsSelected.Select);
  MDRB_LCD_Print (message);
#endif   
}

void LCD_ShowResult(void)
{  
#ifndef LCD_IS_7SEG_DISPLAY    
  sprintf(message , "Ch=%d  Val=%d ", ADC_Data.Flags.Channel, ADC_Data.Flags.Value);
  MDRB_LCD_Print (message, LED_LINE_RESULT);
  
  sprintf(message , "Run=%d  St=x%x", RunIndex, ADC_Status.Status);
  MDRB_LCD_Print (message, LED_LINE_INFO);
  
  sprintf(message , "Cfg1=%x", MDR_ADC->ADC1_Cfg);
  MDRB_LCD_Print (message, LED_LINE_CFG1);  
  sprintf(message , "Cfg2=%x", MDR_ADC->ADC2_Cfg);
  MDRB_LCD_Print (message, LED_LINE_CFG2);    
#else
  #if LED7_SHOW_INFO
    sprintf(message , "%x  %x", ADC_Status.Status, MDR_ADC->ADC1_Cfg);
    MDRB_LCD_Print (message);
    MDR_Delay_ms(LED7_DELAY_MS, MDR_CPU_GetFreqHz(false));
  #endif
  
  sprintf(message , "%d %d ", ADC_Data.Flags.Channel, ADC_Data.Flags.Value);
  MDRB_LCD_Print (message);  
#endif   
}


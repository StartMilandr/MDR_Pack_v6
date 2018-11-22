#include "test_ADC_Interfs.h"

//  =======================   ОПИСАНИЕ    ====================
//  Если ADC2_SELF_SIGNAL_SEL не определен, то тест измеряет синхронно двумя АЦП сигналы заданные маской (Cfg_PinChannelsSelected в ADC_Cfg.h).
//  Если ADC2_SELF_SIGNAL определен, тогда второй АЦП измеряет свои сигналы - ADC2_PinChannels.
//  Кнопки:
//    UP - поменять тест
//    Right - Не используется
//    Down  - Аппаратно переключается канал и производится его измерение. НАЖИМАТЬ для обновления данных!


//  Значения каналов
static MDR_ADC_Result ADC1_Data, ADC2_Data;
static MDR_ADC_Status ADC1_Status, ADC2_Status;
static uint32_t RunIndex;

#define ADC2_SELF_SIGNAL_SEL  0

#if ADC2_SELF_SIGNAL_SEL
  MDR_ADC_Select_PinChannels ADC2_PinChannels = {.Select = 3};
#endif

//  LCD Show Result
static void LCD_ShowInit(void);
static void LCD_ShowResult(void);

//  Test Interface functions
static void TestSyncroSel_Init(void);
static void TestSyncroSel_Finit(void);

static void TestSyncroSel_Change(void);
static void TestSyncroSel_Exec(void);
static void TestSyncroSel_HandleIRQ(void);

TestInterface TI_ADC12_SyncroSelChannel = {
  .funcInit       = TestSyncroSel_Init,
  .funcFinit      = TestSyncroSel_Finit,
  .funcChange     = TestSyncroSel_Change,
  .funcExec       = TestSyncroSel_Exec,
  .funcHandlerIrq = TestSyncroSel_HandleIRQ
};

static void TestSyncroSel_Init(void)
{
  RunIndex = 0;  
  LCD_ShowInit();
  
  //  Включение синхронного режима
  MDR_ADC_Change_CfgSync(&_CfgSync_On);
}


static void TestSyncroSel_Finit(void)
{
  //  Выключение АЦП1
  MDR_ADC_Disable(MDR_ADC2);
  MDR_ADC_Disable(MDR_ADC1);  
  //  ВЫключение синхронного режима
  MDR_ADC_Clear_CfgSync();
}


static void TestSyncroSel_Change(void)
{
  // Not Used
}

static void TestSyncroSel_Exec(void)
{
  MDR_ADC_ClearStatus(MDR_ADC1);
  MDR_ADC_ClearStatus(MDR_ADC2);
  
  //  Запускается только первым ADC
  if (RunIndex == 0)
    #if ADC2_SELF_SIGNAL_SEL
      MDR_ADC_StartSelectedSyncro(Cfg_PinChannelsSelected, ADC2_PinChannels, false, NULL, NULL);      
    #else
      MDR_ADC_StartSelectedSyncro(Cfg_PinChannelsSelected, Cfg_PinChannelsSelected, false, NULL, NULL);
    #endif  
  else
    MDR_ADC_StartNextGoSyncro();
  
  //  Считываем оба результата
  ADC1_Data.Result = MDR_ADC_WaitAndGetResultEx(MDR_ADC1, &ADC1_Status).Result;  
  ADC2_Data.Result = MDR_ADC_WaitAndGetResultEx(MDR_ADC2, &ADC2_Status).Result;
  
  ++RunIndex;
  
  LCD_ShowResult();
}

static void TestSyncroSel_HandleIRQ(void)
{
  //  Not used
}

static char message[64];

void LCD_ShowInit(void)
{ 
//MDRB_LCD_CapturePins();  
  
  MDRB_LCD_Clear();
  sprintf(message , "S_ADC12  Sel=x%d ", Cfg_PinChannelsSelected.Select);
  MDRB_LCD_Print (message, LED_LINE_INIT);
  
//MDRB_LCD_ReleasePins();    
}

void LCD_ShowResult(void)
{   
//MDRB_LCD_CapturePins();
  
  sprintf(message , "Val=%d St=x%d", ADC1_Data.Flags.Value, ADC1_Status.Status);
  MDRB_LCD_Print (message, 2);
  sprintf(message , "Val=%d St=x%d", ADC2_Data.Flags.Value, ADC2_Status.Status);
  MDRB_LCD_Print (message, 3);
  
  sprintf(message , "N=%d Ch1=%d Ch2=%d", RunIndex, ADC1_Data.Flags.Channel, ADC2_Data.Flags.Channel);
  MDRB_LCD_Print (message, 5);
  
  sprintf(message , "Cfg1=%x", MDR_ADC->ADC1_Cfg);
  MDRB_LCD_Print (message, LED_LINE_CFG1);  
  sprintf(message , "Cfg2=%x", MDR_ADC->ADC2_Cfg);
  MDRB_LCD_Print (message, LED_LINE_CFG2); 
  
//MDRB_LCD_ReleasePins();  
}


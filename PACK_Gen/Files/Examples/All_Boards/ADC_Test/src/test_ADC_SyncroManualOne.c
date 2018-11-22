#include "test_ADC_Interfs.h"

//  =======================   ОПИСАНИЕ    ====================
//  Если ADC2_SELF_SIGNAL не определен, то тест измеряет один и тот же сигнал (activeSignal) синхронно двумя АЦП.
//  Если ADC2_SELF_SIGNAL определен, тогда второй АЦП измеряет отдельный сигнал - ADC2_SELF_SIGNAL.
//  Кнопки:
//    UP - поменять тест
//    Right - Поменять канал, который будет измеряться
//    Down - запустить описанный выше цикл измерения для выбранного канала. НАЖИМАТЬ для обновления данных!
//  Сигналы выбираются в ADC_Cfg.h. Без определения ADC2_SELF_SIGNAL можно измерять сигналы от термосенсора.
//
//  ВАЖНО! 
//  1. Необходимо включать АЦП2 битом ADON. В спецификации написано что бит ADON берется от АПЦ1, но вероятно подразумевался бит GO. 
//     Бит GO в ADC1_Cfg действительно запускает измерения в обоих АЦП.
//  2. Для измерения одинаковых каналов необходимо выставлять поле CHS. Это поле не берется из ADC1_Cfg!
//  3. Сигналы термосенсора (температуры и опорного напряжения) могут измеряться только АЦП1. 
//     На экране видно, что АЦП2 показывает не температуру - сигнал находится у верхней границы.


//  Значения каналов
static MDR_ADC_Result ADC1_Data, ADC2_Data;
static MDR_ADC_Status ADC1_Status, ADC2_Status;
static uint32_t RunIndex;


#define ADC2_SELF_SIGNAL 0

#if ADC2_SELF_SIGNAL 
  MDR_ADC_Signal ADC2_SelfSignal = ADC_Signal_Ch1;
#endif

//  LCD Show Result
static void LCD_ShowInit(void);
static void LCD_ShowResult(void);

//  Test Interface functions
static void TestSyncroOne_Init(void);
static void TestSyncroOne_Finit(void);

static void TestSyncroOne_Change(void);
static void TestSyncroOne_Exec(void);
static void TestSyncroOne_HandleIRQ(void);

TestInterface TI_ADC12_SyncroOneChannel = {
  .funcInit       = TestSyncroOne_Init,
  .funcFinit      = TestSyncroOne_Finit,
  .funcChange     = TestSyncroOne_Change,
  .funcExec       = TestSyncroOne_Exec,
  .funcHandlerIrq = TestSyncroOne_HandleIRQ
};

static void TestSyncroOne_Init(void)
{
  RunIndex = 0;  
  LCD_ShowInit();
  
  //  Включение синхронного режима
  MDR_ADC_Change_CfgSync(&_CfgSync_On);
}


static void TestSyncroOne_Finit(void)
{
  //  Выключение АЦП1
  MDR_ADC_Disable(MDR_ADC2);
  MDR_ADC_Disable(MDR_ADC1);  
  //  ВЫключение синхронного режима
  MDR_ADC_Clear_CfgSync();
}


static void TestSyncroOne_Change(void)
{
  RunIndex = 0;
  Cfg_SetNextSignal(); 
  
  LCD_ShowInit();
}

static void TestSyncroOne_Exec(void)
{
  MDR_ADC_ClearStatus(MDR_ADC1);
  MDR_ADC_ClearStatus(MDR_ADC2);
  
  //  Запускается только первым ADC
  if (RunIndex == 0)
    #if ADC2_SELF_SIGNAL
      MDR_ADC_StartSignalSyncro(Cfg_GetActiveSignal(), ADC2_SelfSignal, false, NULL, NULL);
    #else
      MDR_ADC_StartSignalSyncro(Cfg_GetActiveSignal(), Cfg_GetActiveSignal(), false, NULL, NULL);
    #endif  
  else
    MDR_ADC_StartNextGoSyncro();
  
  //  Считываем оба результата
  ADC1_Data.Result = MDR_ADC_WaitAndGetResultEx(MDR_ADC1, &ADC1_Status).Result;  
  ADC2_Data.Result = MDR_ADC_WaitAndGetResultEx(MDR_ADC2, &ADC2_Status).Result;
  
  ++RunIndex;
  
  LCD_ShowResult();
}

static void TestSyncroOne_HandleIRQ(void)
{
  //  Not used
}

static char message[64];

void LCD_ShowInit(void)
{ 
//MDRB_LCD_CapturePins();  
  
  MDRB_LCD_Clear();
  sprintf(message , "S_ADC12  Sig=%c ", Cfg_GetActiveSignalName());
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
  
  sprintf(message , "Ch1=%d Ch2=%d", ADC1_Data.Flags.Channel, ADC2_Data.Flags.Channel);
  MDRB_LCD_Print (message, 4);  
  sprintf(message , "N=%d", RunIndex);
  MDRB_LCD_Print (message, 5);
  
  sprintf(message , "Cfg1=%x", MDR_ADC->ADC1_Cfg);
  MDRB_LCD_Print (message, LED_LINE_CFG1);  
  sprintf(message , "Cfg2=%x", MDR_ADC->ADC2_Cfg);
  MDRB_LCD_Print (message, LED_LINE_CFG2); 
  
//MDRB_LCD_ReleasePins();  
}


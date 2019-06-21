#include <MDR_GPIO.h>
#include <MDR_RST_Clock.h>
#include <MDR_Funcs.h>
#include <MDR_SysTimer.h>

#include <MDRB_LEDs.h>


#ifndef USE_MDR1923VK014
  #include <MDRB_Buttons.h>
  #include <MDRB_LCD.h>
#endif

#include "ClockItems.h"


//  ==============  Выбор вариантов тактирования для перебора в тесте  ===========
//  Можно поменять очередность переключения, Закомментировать не интересующие варианты, 
//  Новые варианты прописать в ClockItems.c и ClockItems.h
#if defined (USE_MDR1986VE8) || defined (USE_MDR1923VK014)   
  static ClockItemsEnum  ClockItems[] = {
    iLSI,
    iLSE ,
    iHSI,
    iHSId2,
    iHSE0,
    iHSE0d2,
    iHSE1,
    iHSE1d2,
    iHSI_P0_40,
    iHSI_P1_36,
    iHSI_P2_20,
    iHSE0_P0_40,
    iHSE0_P1_36,
    iHSE0_P2_20,
    iHSE1_P0_40,
    iHSE1_P1_36,
    iHSE1_P2_20,
  } ;
#elif defined (USE_ESila)    
  static ClockItemsEnum  ClockItems[] = {
    iLSI,
    iLSE ,
    iHSI,
    iHSId2,
    iHSE0,
    iHSE0d2,
    iHSE1,
    iHSE1d2,
    iHSI_P0_120,
    iHSI_P1_100,
    iHSI_P2_80,
    iHSI_P3_40,
    iHSE0_P0_120,
    iHSE0_P1_100,
    iHSE0_P2_80,
    iHSE0_P3_60,
    iHSE1_P0_120,
    iHSE1_P1_100,
    iHSE1_P2_80,
    iHSE1_P3_60,
  } ;
#else
  static  ClockItemsEnum  ClockItems[] = {
    iLSI,
    iLSE ,
    iHSI,
    iHSId2,
    iHSE,
    iHSEd2,
    iHSI_P_128,
    iHSI_P_64,
    iHSI_P_32,
    iHSE_P_128,
    iHSE_P_80,
    iHSE_P_40,
  };  
#endif


#define   ITEMS_COUNT     (sizeof(ClockItems)/sizeof(ClockItems[0]))  
  //  Текущий вариант частоты
static uint32_t    activeItemInd = 2;

//  Переключение через промежуточное переключение на HSI
#define USE_TEMP_TO_HSI  1

//-----------   LED and Buttons   ------------
#define PERIOD_MS           1000
#define DEBOUNCE_MS         5

static uint32_t ledPinSel;
static uint32_t sysTimRescale = 1;
static uint32_t sysTimPeriod;

//  Если lastSetClockStatus == MDR_SET_CLOCK_OK то на светодиодах мигает activeItemInd в бинарном виде. 
//  Иначе светодиоды не мигая показывают бинарной значени MDR_CPU_SetClockResult
static MDR_CPU_SetClockResult lastSetClockStatus;

//  Варианты тактирования переключаются по кнпкам, но можно перекомпилировать с changeByTimerEna = true
//  Тогда вместо кнопок варианты будут переключаться по таймеру через TIMER_CHANGE_CLK_PERIOD/2 переключений светодиодов.
static uint32_t changeByTimerCnt;
static bool     changeByTimer = false;
#define TIMER_CHANGE_CLK_PERIOD     10

#ifndef USE_MDR1923VK014  
  static bool     changeByTimerEna = false;
#else
  static bool     changeByTimerEna = true;
#endif

void SysTick_Handler(void);
void SetNextClockItem(int32_t step);
void UpdateNewClockToDrivers(void);
MDR_CPU_SetClockResult TrySwitchToClock(const CLK_Item *item);

//  Вывод результата на LCD
void ShowSetItemResult(const CLK_Item *item, MDR_CPU_SetClockResult status);
void ShowClearResult(void);

MDR_CPU_SetClockResult  TempToHSI(void);
MDR_CPU_SetClockResult  ChangeClockCPU(const CLK_Item *item);


int main(void)
{
#if 1  
  MDR_DebugerProtectDelay();
#endif
   
  //  Сброс блока, тактирование от HSI
  MDR_CLK_ResetBlock_def(true);
  
  // Инициализация светодиодов и кнопок
  MDRB_LED_Init(MDRB_LED_PinAll);
#ifndef USE_MDR1923VK014  
  MDRB_Buttons_Init(DEBOUNCE_MS, HSI_FREQ_HZ);
#endif
#ifdef MDRB_HAS_LCD  
  MDRB_LCD_Init(HSI_FREQ_HZ);  
#endif
  
  //  Индикация начала теста - подмигивание всеми светодиодами
  MDRB_LED_Set(MDRB_LED_PinAll, true);
  MDR_Delay_ms(PERIOD_MS, HSI_FREQ_HZ);
  MDRB_LED_Set(MDRB_LED_PinAll, false);
  
  //  Включение тактирования и отображение начальной частоты
  MDR_CLK_Enable_RST_BPK();  
  SetNextClockItem(0);
  
  while (1)
  {
#ifndef USE_MDR1923VK014
    //  Next Clock
    if (MDRB_BntClicked_Up(true))
      SetNextClockItem(1);
    //  Prev Clock
    if (MDRB_BntClicked_Right(true))
      SetNextClockItem(-1);
    //  Change by Timer
    if (MDRB_BntClicked_Down(true))
      changeByTimerEna = !changeByTimerEna;
#endif
    
    if (changeByTimer)
    {
      SetNextClockItem(1);
      changeByTimer = false;
    }
  }
}

void SysTick_Handler(void)
{
  static uint32_t period = 0;
  
  ++period;
  if (period >= sysTimRescale)
  {
    if (lastSetClockStatus == MDR_SET_CLOCK_OK)
      MDRB_LED_Toggle(ledPinSel);
    period = 0;
    
    //  Change Clock by Timer
    if (changeByTimerEna)
    {
      changeByTimerCnt++;
      if (changeByTimerCnt == TIMER_CHANGE_CLK_PERIOD)
      {
        changeByTimer = true;
        changeByTimerCnt = 0;
      }
    }
  }
}

//  =================  Функция переключения на следующий/предыдущий вариант тактирования =======================
void UpdateNewClockToDrivers(void)
{
  uint32_t cpuFreqHz = MDR_CPU_GetFreqHz(true);
#ifndef USE_MDR1923VK014    
  MDRB_Buttons_ChangeDebounceDelay(DEBOUNCE_MS, cpuFreqHz);
#endif
    
  #ifdef MDRB_HAS_LCD    
    MDRB_LCD_ChangeFreqCPU(cpuFreqHz);
  #endif  
}

MDR_CPU_SetClockResult  TempToHSI(void)
{
  bool fromLowerFreq = HSI_FREQ_HZ > MDR_CPU_GetFreqHz(false); 
  
#ifdef MDR_CLK_LIKE_VE8
  MDR_CPU_SetClockResult result = MDR_CPU_SetClock_HSI_def(fromLowerFreq);  
#else
  MDR_CPU_SetClockResult result = MDR_CPU_SetClock_HSI_Dir_def(fromLowerFreq);  
#endif
  if (result == MDR_SET_CLOCK_OK)
    UpdateNewClockToDrivers();
  
  return result;  
}


MDR_CPU_SetClockResult TrySwitchToClock(const CLK_Item *item)
{
  MDR_CPU_SetClockResult result = ChangeClockCPU(item);
  if (result == MDR_SET_CLOCK_OK)
    UpdateNewClockToDrivers();
  
  return result;  
}

void SetNextClockItem(int32_t step)
{
  //  Stop LED and SysTimer
  MDR_SysTimerStop();
  MDRB_LED_Set(MDRB_LED_PinAll, false);    
  
  //  Calc Next Clock
  int32_t nextItemInd = (int32_t)activeItemInd + step;
  if (nextItemInd < 0)
    activeItemInd = ITEMS_COUNT - 1;
  else if (nextItemInd >= (int32_t)ITEMS_COUNT) 
    activeItemInd = 0;
  else
    activeItemInd = (uint32_t)nextItemInd;

  //  Set New Clock
  ShowClearResult();
  lastSetClockStatus = TrySwitchToClock(&ClockConfigs[ClockItems[activeItemInd]]);  
#if USE_TEMP_TO_HSI  
  if (lastSetClockStatus == MDR_SET_CLOCK_ERR__SRC_USING)
  {
    lastSetClockStatus = TempToHSI();
    ShowSetItemResult(NULL, lastSetClockStatus);
  
    if (lastSetClockStatus == MDR_SET_CLOCK_OK)
      lastSetClockStatus = TrySwitchToClock(&ClockConfigs[ClockItems[activeItemInd]]);
  }
#endif
  ShowSetItemResult(&ClockConfigs[ClockItems[activeItemInd]], lastSetClockStatus);
        
  //  Вывод на светодиоды номера теста (Мигает от SysTimer) или ошибки (не мигает)
  if (lastSetClockStatus == MDR_SET_CLOCK_OK)
    ledPinSel = MDRB_LED_NumToSel(activeItemInd + 1);
  else
  {  
    ledPinSel = MDRB_LED_NumToSel(lastSetClockStatus + 1);
    MDRB_LED_Set(ledPinSel, true);
  }
  
  // Start SysTimer
  // Период 24-битный. Масштабирование чтобы не выйти за диапазон.
  uint32_t cpuFreqHz = MDR_CPU_GetFreqHz(true);
  sysTimPeriod = MS_TO_CLOCKS(PERIOD_MS, cpuFreqHz);
  if (sysTimPeriod & 0xFF000000)
    sysTimRescale = 1000;
  else
    sysTimRescale = 1;
  sysTimPeriod = sysTimPeriod / sysTimRescale;        
  MDR_SysTimerStart(sysTimPeriod);
}


//  =================  Отображение статуса переключения на вариант тактирования =======================
#ifdef MDRB_HAS_LCD    

  static char mess[100];
  static char *strStatus[MDR_SET_CLOCK_ERR__Undef + 1] = {"OK", "GenNotReady", "SrcBusy", "PLLNotReady", "Unknown"};

  void ShowClearResult(void)
  {
    MDRB_LCD_ClearLine(3);
    MDRB_LCD_ClearLine(4);
    MDRB_LCD_ClearLine(5);
    MDRB_LCD_ClearLine(6);
    MDRB_LCD_ClearLine(7);
  }

  void ShowSetItemResult(const CLK_Item *item, MDR_CPU_SetClockResult status)
  {
    uint32_t freqAct = MDR_CPU_GetFreqHz(true);
    
    if (item == NULL)
    {
      sprintf(mess, "tempHSI: %s\n", strStatus[status]);
      MDRB_LCD_Print(mess, 3);
      sprintf(mess, "Freq, KHz: %d\n", freqAct/1000);
      MDRB_LCD_Print(mess, 4);
    }
    else
    {
      sprintf(mess, "%s: %s", item->name, strStatus[status]);
      MDRB_LCD_Print(mess, 5);
      
      uint32_t freqItem = item->freqHz;    
      sprintf(mess, "Act KHz: %d\n", freqAct/1000);
      MDRB_LCD_Print(mess, 6);    
      sprintf(mess, "Ref KHz: %d\n", freqItem/1000);
      MDRB_LCD_Print(mess, 7);    
    }
  }

#else

  void ShowClearResult(void)
  {  
  }

  void ShowSetItemResult(const CLK_Item *item, MDR_CPU_SetClockResult status)
  {
    UNUSED(item);
    UNUSED(status);
  }

#endif


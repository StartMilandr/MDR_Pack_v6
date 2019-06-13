#include <MDR_GPIO.h>
#include <MDR_RST_Clock.h>
#include <MDR_Funcs.h>
#include <MDR_SysTimer.h>

#include <MDRB_LEDs.h>
#include <MDRB_Buttons.h>
#include <MDRB_LCD.h>

//-----------   LED and Buttons   ------------
#define PERIOD_MS           1000
#define LED_TIMER           MDRB_LED_1
#define DEBOUNCE_MS         5

static uint32_t sysTimRescale = 1;
static uint32_t sysTimPeriod;

//-----------   LCD Parameters   ------------
#define CLD_LINE_FREQ   3
#define CLD_LINE_EXT    5

#if defined (MDRB_LCD_CONFLICT_LED) || defined (MDRB_LCD_CONFLICT_BTN)
  #define LCD_PIN_CONFLICT
#endif

//-----------   Clock Parameters   ------------
typedef enum {
  // LSE
  clkLSE,
  // LSI
  clkLSI,  
  // HSI
  clkHSI_dir,
  clkHSI,
  clkHSIdiv2,
  // HSE
  clkHSE,
  clkHSEdiv2,
  // PLL
  clkPLL_HSI,
  clkPLL_HSIdiv2,
  clkPLL_HSE,
  clkPLL_HSEdiv2
}   CPU_ClockSource;

#define DIV_SRC_START_IND   clkHSI
#define MUL_SRC_START_IND   clkPLL_HSI

#define CLK_SRC_COUNT  11
#ifndef LCD_IS_7SEG_DISPLAY 
  static char* srcNames[CLK_SRC_COUNT] = {"LSE", "LSI", "HSIdir", "HSI", "HSI/2", "HSE", "HSE/2", "PLL_HSI", "P_HSI/2", "PLL_HSE", "P_HSE/2"};
            // Indexes for 7SEG_DISPLAY:    0      1       2       3      4        5       6         7           8         9          10
#endif

 
#define CLK_DIV_COUNT  9
static MDR_Div256P   clkDivs[CLK_DIV_COUNT] = {MDR_Div256P_div1, MDR_Div256P_div2, MDR_Div256P_div4, MDR_Div256P_div8, MDR_Div256P_div16, 
                                               MDR_Div256P_div32, MDR_Div256P_div64, MDR_Div256P_div128, MDR_Div256P_div256};

#ifndef LCD_IS_7SEG_DISPLAY 
  static char* divNames[CLK_DIV_COUNT] = {"1", "2", "4", "8", "16", "32", "64", "128", "256"};
#endif

#define CLK_MULL_COUNT  16

static CPU_ClockSource  activeClockSrc  = clkHSI_dir;
static uint32_t         activeDivInd    = 0;
static MDR_MUL_x16      activeMulPLL    = MDR_x1;

#define BY_PASS_OFF     MDR_Off


//  Прототипы функций
void SysTick_Handler(void);

MDR_CPU_SetClockResult TempTo_HSI_Dir(void);
void ChangeClockCPU(CPU_ClockSource clockSrc, uint32_t divInd, MDR_MUL_x16 mulPLL);

void LCD_ShowResult(uint32_t cpuFreqHz);
void LCD_ShowError(CPU_ClockSource clockSrc, MDR_Div256P divMuxC3, MDR_MUL_x16 mulPLL);


//  Программа
int main(void)
{ 
#if 1  
  MDR_DebugerProtectDelay();
#endif
   
  //  Сброс блока, тактирование от HSI
  MDR_CLK_ResetBlock_def(true);

  // Инициализация экрана для вывода статуса
  MDRB_LCD_Init(HSI_FREQ_HZ);
  
  // Инициализация светодиодов и кнопок
  MDRB_LED_Init(LED_TIMER);
  MDRB_Buttons_Init(DEBOUNCE_MS, HSI_FREQ_HZ);
  
  //  Индикация начала теста - подмигивание всеми светодиодами
  MDRB_LED_Set(LED_TIMER, true);
  MDR_Delay_ms(PERIOD_MS, HSI_FREQ_HZ);
  MDRB_LED_Set(LED_TIMER, false);
  
  //  Стартовая настройка
  MDR_CLK_Enable_RST_BPK();
  ChangeClockCPU(activeClockSrc, activeDivInd, activeMulPLL);  
     
  while (1)
  {    
    if (MDRB_BntClicked_Up(true))
    {
      ChangeClockCPU((CPU_ClockSource)((activeClockSrc + 1) % CLK_SRC_COUNT), activeDivInd, activeMulPLL);
    }
    if (MDRB_BntClicked_Down(true))
    {
      if (activeClockSrc != 0)
        ChangeClockCPU((CPU_ClockSource)(activeClockSrc - 1), activeDivInd, activeMulPLL);
      else
        ChangeClockCPU((CPU_ClockSource)(CLK_SRC_COUNT - 1), activeDivInd, activeMulPLL);
    }
    //  Увеличения делителя Mux_C3
    if (MDRB_BntClicked_Left(true))
    {
      if (activeClockSrc >= DIV_SRC_START_IND)
        ChangeClockCPU(activeClockSrc, (activeDivInd + 1) % CLK_DIV_COUNT, activeMulPLL);
    }
    // Увеличение множителя PLL
    if (MDRB_BntClicked_Right(true))
    {
      if (activeClockSrc >= MUL_SRC_START_IND)
        ChangeClockCPU(activeClockSrc, activeDivInd, (MDR_MUL_x16)((activeMulPLL + 1) % CLK_MULL_COUNT));
    }
    // Сброc Div = Mull = 1
    if (MDRB_BntClicked_Select(true))
    {
      ChangeClockCPU(activeClockSrc, 0, MDR_x1);
    }
  }
}

void SysTick_Handler(void)
{
  static uint32_t period = 0;
  
  ++period;
  if (period >= sysTimRescale)
  {
    MDRB_LED_Switch(LED_TIMER);
    period = 0;
  }
}

MDR_CPU_SetClockResult TempTo_HSI_Dir(void)
{
  MDR_CPU_CfgHSI_Dir cfgHSI = MDR_CPU_CFG_HSI_DEF_DIR;
  bool fromLowerFreq = HSI_FREQ_HZ > MDR_CPU_GetFreqHz(false);
      
  return MDR_CPU_SetClock_HSI_Dir(&cfgHSI, HSI_TIMEOUT, fromLowerFreq);
}

void ChangeClockCPU(CPU_ClockSource clockSrc, uint32_t divInd, MDR_MUL_x16 mulPLL)
{
  MDR_CPU_SetClockResult result = MDR_SET_CLOCK_ERR__Undef;
  uint32_t cpuFreqHz;
  MDR_CLK_Delay_EEPROM delayEEPROM;
  MDR_CLK_LDO_LowSRI   lowRI;
  MDR_Div256P divMuxC3 = clkDivs[divInd];
    
  
  //  Stop LED and SysTimer
  MDR_SysTimerStop();
  MDRB_LED_Set(LED_TIMER, false);  
  
  //  Set New Frequency
  switch (clockSrc)
  {
    // LSE
    case clkLSE:
      result = MDR_CPU_SetClock_LSE_Res_def();
      break;
    // LSI
    case clkLSI:
      result = MDR_CPU_SetClock_LSI_def();
      break;    
    // HSI
    case clkHSI_dir: {
      result = TempTo_HSI_Dir();
      break; }
    case clkHSI: {     
      //  Временный переход на HSI_Dir, чтобы переключать тракт CPU_C3
      TempTo_HSI_Dir();
      
      //  Переход на готовую частоту
      MDR_CPU_CfgHSI cfgHSI = MDR_CPU_CFG_HSI_DEF;
      cfgHSI.divC3 = divMuxC3;      
      result = MDR_CPU_SetClock_HSI(&cfgHSI, HSI_TIMEOUT, true);
      break; }
    case clkHSIdiv2: {
      //  Временный переход на HSI_Dir, чтобы переключать тракт CPU_C3
      TempTo_HSI_Dir();
      
      //  Переход на готовую частоту      
      MDR_CPU_CfgHSI cfgHSI = MDR_CPU_CFG_HSI_DEF;
      cfgHSI.divC3 = divMuxC3;      
      result = MDR_CPU_SetClock_HSI_div2(&cfgHSI, HSI_TIMEOUT, false);
      break; }
    // HSE
    case clkHSE: {
      //  Временный переход на HSI_Dir, чтобы переключать тракт CPU_C3
      TempTo_HSI_Dir();
      
      //  Переход на готовую частоту      
      MDR_CPU_CfgHSE cfgHSE = MDR_CPU_CFG_HSE_RES_DEF;
      cfgHSE.divC3 = divMuxC3;
      bool fromLowerFreq = HSE_FREQ_HZ > MDR_CPU_GetFreqHz(false);
      
      result = MDR_CPU_SetClock_HSE(&cfgHSE, HSE_TIMEOUT, fromLowerFreq);
      break; }
    case clkHSEdiv2: {
      //  Временный переход на HSI_Dir, чтобы переключать тракт CPU_C3
      TempTo_HSI_Dir();
      
      //  Переход на готовую частоту      
      MDR_CPU_CfgHSE cfgHSE = MDR_CPU_CFG_HSE_RES_DEF;
      cfgHSE.divC3 = divMuxC3;
      bool fromLowerFreq = (HSE_FREQ_HZ >> 1) > MDR_CPU_GetFreqHz(false);
      
      result = MDR_CPU_SetClock_HSE_div2(&cfgHSE, HSE_TIMEOUT, fromLowerFreq);
      break; }
    // PLL - HSI
    case clkPLL_HSI: {
      //  Временный переход на HSI_Dir, чтобы переключать тракт CPU_C3
      TempTo_HSI_Dir();
           
      //  Рассчет новой частоты и параметров под нее
      cpuFreqHz   = (HSI_FREQ_HZ * (mulPLL + 1)) >> divInd;
      delayEEPROM = MDR_FreqCPU_ToDelayEEPROM(cpuFreqHz);
      lowRI       = MDR_FreqCPU_ToLowSRI(cpuFreqHz);
      bool fromLowerFreq = cpuFreqHz > MDR_CPU_GetFreqHz(false);
      
      // Переключение на новую частоту
      MDR_CPU_PLL_CfgHSI cfgPLL_HSI = MDR_CPU_CFG_PLL_HSI_DEF(mulPLL, delayEEPROM, lowRI);    
      cfgPLL_HSI.divC3 = divMuxC3;
      result = MDR_CPU_SetClock_HSI_PLL(&cfgPLL_HSI, fromLowerFreq);
      break; }
    case clkPLL_HSIdiv2: {
      //  Временный переход на HSI_Dir, чтобы переключать тракт CPU_C3
      TempTo_HSI_Dir();
            
      //  Рассчет новой частоты и параметров под нее
      cpuFreqHz   = (HSI_FREQ_HZ * (mulPLL + 1)) >> divInd;
      delayEEPROM = MDR_FreqCPU_ToDelayEEPROM(cpuFreqHz);
      lowRI       = MDR_FreqCPU_ToLowSRI(cpuFreqHz);
      bool fromLowerFreq = cpuFreqHz > MDR_CPU_GetFreqHz(false);
    
      // Переключение на новую частоту
      MDR_CPU_PLL_CfgHSI cfgPLL_HSI = MDR_CPU_CFG_PLL_HSI_DEF(mulPLL, delayEEPROM, lowRI);    
      cfgPLL_HSI.divC3 = divMuxC3;
      result = MDR_CPU_SetClock_HSI_div2_PLL(&cfgPLL_HSI, fromLowerFreq);
      break; }
    // PLL - HSE
    case clkPLL_HSE: {
      //  Временный переход на HSI_Dir, чтобы переключать тракт CPU_C3
      TempTo_HSI_Dir();
      
      //  Рассчет новой частоты и параметров под нее
      cpuFreqHz   = (HSI_FREQ_HZ * (mulPLL + 1)) >> divInd;
      delayEEPROM = MDR_FreqCPU_ToDelayEEPROM(cpuFreqHz);
      lowRI       = MDR_FreqCPU_ToLowSRI(cpuFreqHz);
      bool fromLowerFreq = cpuFreqHz > MDR_CPU_GetFreqHz(false);
    
      // Переключение на новую частоту    
      MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDR_CPU_CFG_PLL_HSE_RES_DEF(mulPLL, delayEEPROM, lowRI);
      cfgPLL_HSE.divC3 = divMuxC3;
      result = MDR_CPU_SetClock_HSE_PLL(&cfgPLL_HSE, fromLowerFreq);
      break; }
    case clkPLL_HSEdiv2: {
      //  Временный переход на HSI_Dir, чтобы переключать тракт CPU_C3
      TempTo_HSI_Dir();
      
      //  Рассчет новой частоты и параметров под нее
      cpuFreqHz   = (HSI_FREQ_HZ * (mulPLL + 1)) >> divInd;
      delayEEPROM = MDR_FreqCPU_ToDelayEEPROM(cpuFreqHz);
      lowRI       = MDR_FreqCPU_ToLowSRI(cpuFreqHz);
      bool fromLowerFreq = cpuFreqHz > MDR_CPU_GetFreqHz(false);
    
      // Переключение на новую частоту    
      MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDR_CPU_CFG_PLL_HSE_RES_DEF(mulPLL, delayEEPROM, lowRI);
      cfgPLL_HSE.divC3 = divMuxC3;
      result = MDR_CPU_SetClock_HSE_div2_PLL(&cfgPLL_HSE, fromLowerFreq);
      break; }
  }
  
  if (result == MDR_SET_CLOCK_OK)
  {
    activeClockSrc = clockSrc;  
    activeMulPLL   = mulPLL;
    activeDivInd   = divInd;
    
    //  Get CPU_Clock
    cpuFreqHz = MDR_CPU_GetFreqHz(true);
    
    //  Update Result LCD Delay
    MDRB_LCD_ChangeFreqCPU(cpuFreqHz);
    
    //  Период 24-битный. Масштабирование чтобы не выйти за диапазон.
    sysTimPeriod = MS_TO_CLOCKS(PERIOD_MS, cpuFreqHz);
    if (sysTimPeriod & 0xFF000000)
      sysTimRescale = 1000;
    else
      sysTimRescale = 1;
    sysTimPeriod = sysTimPeriod / sysTimRescale;    
    
    //  Show result to LED
    LCD_ShowResult(cpuFreqHz);
    //  Update Buttons debounce delay
    MDRB_Buttons_ChangeDebounceDelay(DEBOUNCE_MS, cpuFreqHz);
    
    // Start LED and SysTimer
    MDR_SysTimerStart(sysTimPeriod);    
  }
  else
  {
    LCD_ShowError(clockSrc, divMuxC3, mulPLL);
  }  
}

void LCD_ShowResult(uint32_t cpuFreqHz)
{
  static char mess[64];  

#ifdef LCD_PIN_CONFLICT
  // Захват пинов для работы с экраном
  MDRB_LCD_CapturePins();
#endif
  
#ifndef LCD_IS_7SEG_DISPLAY   
  //  Вывод источника тактирования и текущей частоты
  sprintf(mess, "%s=%d", srcNames[activeClockSrc], cpuFreqHz);
  MDRB_LCD_Print(mess, CLD_LINE_FREQ);
  
  switch (activeClockSrc)
  {
    case clkHSI:
    case clkHSIdiv2:
    case clkHSE:
    case clkHSEdiv2:
      sprintf(mess, "div=%s", divNames[activeDivInd]);
      MDRB_LCD_Print(mess, CLD_LINE_EXT);
      break;
    // PLL - HSI
    case clkPLL_HSI:
    case clkPLL_HSIdiv2:
    case clkPLL_HSE:
    case clkPLL_HSEdiv2:
      sprintf(mess, "div=%s pll=%d", divNames[activeDivInd], activeMulPLL + 1);
      MDRB_LCD_Print(mess, CLD_LINE_EXT);
      break;
    case clkLSI:
    case clkLSE:
    case clkHSI_dir:
      strcpy(mess, "");
      MDRB_LCD_Print(mess, CLD_LINE_EXT);
      break;
  }  
#else
  //  Вывод источника тактирования
  sprintf(mess, "%d %d", (uint8_t)activeClockSrc, cpuFreqHz);
  MDRB_LCD_Print(mess);
#endif  

#ifdef LCD_PIN_CONFLICT  
  // Возврат пинов в изначальное состояние
  MDRB_LCD_ReleasePins();
#endif
}

void LCD_ShowError(CPU_ClockSource clockSrc, MDR_Div256P divMuxC3, MDR_MUL_x16 mulPLL)
{
  static char mess[64];
   
#ifdef LCD_PIN_CONFLICT
  // Захват пинов для работы с экраном
  MDRB_LCD_CapturePins();
#endif
  
#ifndef LCD_IS_7SEG_DISPLAY  
  //  Вывод источника тактирования
  sprintf(mess, "ERROR %s", srcNames[clockSrc]);
  MDRB_LCD_Print(mess, CLD_LINE_FREQ);
  
  switch (activeClockSrc)
  {
    case clkHSI:
    case clkHSIdiv2:
    case clkHSE:
    case clkHSEdiv2:
      sprintf(mess, "div=%s", divNames[divMuxC3]);
      MDRB_LCD_Print(mess, CLD_LINE_EXT);
      break;
    // PLL - HSI
    case clkPLL_HSI:
    case clkPLL_HSIdiv2:
    case clkPLL_HSE:
    case clkPLL_HSEdiv2:
      sprintf(mess, "div=%s pll=%d", divNames[divMuxC3], mulPLL);
      MDRB_LCD_Print(mess, CLD_LINE_EXT);
      break;
    case clkLSI:
    case clkLSE:
    case clkHSI_dir:
      break;
  }
#else
  
  UNUSED(clockSrc);
  UNUSED(divMuxC3);
  UNUSED(mulPLL);
  
  //  Вывод источника тактирования
  sprintf(mess, "%d EEEE", (uint8_t)activeClockSrc);
  MDRB_LCD_Print(mess);
#endif
  
#ifdef LCD_PIN_CONFLICT
  // Возврат пинов в изначальные настройки
  MDRB_LCD_ReleasePins();
#endif
}


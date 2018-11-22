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
  static char* srcNames[CLK_SRC_COUNT] = {"LSE", "LSI", "HSIc3", "HSI", "HSI/2", "HSE", "HSE/2", "PLL_HSI", "P_HSI/2", "PLL_HSE", "P_HSE/2"};
#endif

#define CLK_DIV_COUNT  9
static MDR_CLK_DIV_256 clkDivs[CLK_DIV_COUNT] = {MDR_CLK_div1, MDR_CLK_div2, MDR_CLK_div4, MDR_CLK_div8, MDR_CLK_div16, MDR_CLK_div32, MDR_CLK_div64, MDR_CLK_div128, MDR_CLK_div256};
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

void ChangeClockCPU(CPU_ClockSource clockSrc, uint32_t divInd, MDR_MUL_x16 mulPLL);

void LCD_ShowResult(uint32_t cpuFreqHz);
void LCD_ShowError(CPU_ClockSource clockSrc, MDR_CLK_DIV_256 divMuxC3, MDR_MUL_x16 mulPLL);


//  Программа
int main(void)
{ 
 // MDR_DebugerProtectDelay();
   
  //  Сброс блока, тактирование от HSI
  MDR_RST_ResetBlock_def();

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

void ChangeClockCPU(CPU_ClockSource clockSrc, uint32_t divInd, MDR_MUL_x16 mulPLL)
{
  bool result = false;
  uint32_t cpuFreqHz;
  MDR_RST_EEPROM_Delay delayEEPROM;
  MDR_RST_BKP_LowRI    lowRI;
  MDR_CLK_DIV_256 divMuxC3 = clkDivs[divInd];
  
  //  Stop LED and SysTimer
  MDR_SysTimerStop();
  MDRB_LED_Set(LED_TIMER, false);  
  
  //  Set New Frequency
  switch (clockSrc)
  {
    // LSE
    case clkLSE:
      result = MDR_CPU_SetClock_LSE_def(BY_PASS_OFF);
      break;
    // LSI
    case clkLSI:
      result = MDR_CPU_SetClock_LSI_def();
      break;    
    // HSI
    case clkHSI_dir:
      result = MDR_CPU_SetClock_HSI_def();
      break;
    case clkHSI:
      result = MDR_CPU_SetClock_HSI_C1(divMuxC3, HSI_TIMEOUT, HSI_FREQ_TRIM);
      break;
    case clkHSIdiv2:
      result = MDR_CPU_SetClock_HSI_div2(divMuxC3, HSI_TIMEOUT, HSI_FREQ_TRIM);
      break;
    // HSE
    case clkHSE:
      result = MDR_CPU_SetClock_HSE(BY_PASS_OFF, MDR_LOWRI_le10MHz, divMuxC3, HSE_TIMEOUT);
      break;
    case clkHSEdiv2:
      result = MDR_CPU_SetClock_HSE_div2(BY_PASS_OFF, divMuxC3, HSE_TIMEOUT);
      break;
    // PLL - HSI
    case clkPLL_HSI:
      //  Рассчет новой частоты и параметров под нее
      cpuFreqHz   = (HSI_FREQ_HZ * (mulPLL + 1)) >> divInd;
      delayEEPROM = MDR_FreqCPU_ToDelayEEPROM(cpuFreqHz);
      lowRI       = MDR_FreqCPU_ToLowRI(cpuFreqHz);
    
      // Переключение на новую частоту
      result = MDR_CPU_SetClock_HSI_PLL(mulPLL, lowRI, delayEEPROM, divMuxC3, HSI_TIMEOUT, HSI_FREQ_TRIM);
      break;
    case clkPLL_HSIdiv2:
      //  Рассчет новой частоты и параметров под нее
      cpuFreqHz   = (HSI_FREQ_HZ * (mulPLL + 1)) >> divInd;
      delayEEPROM = MDR_FreqCPU_ToDelayEEPROM(cpuFreqHz);
      lowRI       = MDR_FreqCPU_ToLowRI(cpuFreqHz);
    
      // Переключение на новую частоту
      result = MDR_CPU_SetClock_HSI_div2_PLL(mulPLL, lowRI, delayEEPROM, divMuxC3, HSI_TIMEOUT, HSI_FREQ_TRIM);
      break;
    // PLL - HSE
    case clkPLL_HSE:
      //  Рассчет новой частоты и параметров под нее
      cpuFreqHz   = (HSI_FREQ_HZ * (mulPLL + 1)) >> divInd;
      delayEEPROM = MDR_FreqCPU_ToDelayEEPROM(cpuFreqHz);
      lowRI       = MDR_FreqCPU_ToLowRI(cpuFreqHz);
    
      // Переключение на новую частоту    
      result = MDR_CPU_SetClock_HSE_PLL(BY_PASS_OFF, mulPLL, lowRI, delayEEPROM, divMuxC3, HSE_TIMEOUT);
      break;
    case clkPLL_HSEdiv2:
      //  Рассчет новой частоты и параметров под нее
      cpuFreqHz   = (HSI_FREQ_HZ * (mulPLL + 1)) >> divInd;
      delayEEPROM = MDR_FreqCPU_ToDelayEEPROM(cpuFreqHz);
      lowRI       = MDR_FreqCPU_ToLowRI(cpuFreqHz);
    
      // Переключение на новую частоту    
      result = MDR_CPU_SetClock_HSE_div2_PLL(BY_PASS_OFF, mulPLL, lowRI, delayEEPROM, divMuxC3, HSE_TIMEOUT);
      break;
  }
  
  if (result)
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

void LCD_ShowError(CPU_ClockSource clockSrc, MDR_CLK_DIV_256 divMuxC3, MDR_MUL_x16 mulPLL)
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
  //  Вывод источника тактирования
  sprintf(mess, "%d EEEE", (uint8_t)activeClockSrc);
  MDRB_LCD_Print(mess);
#endif
  
#ifdef LCD_PIN_CONFLICT
  // Возврат пинов в изначальные настройки
  MDRB_LCD_ReleasePins();
#endif
}


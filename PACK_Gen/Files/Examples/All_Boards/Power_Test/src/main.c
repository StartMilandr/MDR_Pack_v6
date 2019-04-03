#include <MDR_RST_Clock.h>
#include <MDR_PER_Clock.h>
#include <MDRB_Buttons.h>
#include <MDRB_LCD.h>
#include <MDRB_UART_Debug.h>

#include "MDR_Power.h"
#include "PowerUtils.h"

#define BTN_DEBOUNCE_MS 10

#define MAX_WAIT_LEVEL_DELAY  100

#ifdef USE_MDR1986VK214
  #define USE_IRQ  false
#else
  #define USE_IRQ  true  
#endif

//  Начальные условия такие, чтобы события не стали активны при инициализации
//  События по: Ucc < 3V, BUcc < 3V
static const MDR_Power_Cfg cfgPower = {
  // Ucc
  .levelUcc        = PWR_Ucc_3V0,
  .enaEventUccIRQ  = MDR_Off,
  .condEventUcc    = PWR_xUcc_Lower,
  //  BUcc
  .levelBUcc       = PWR_BUcc_3V0,
  .enaEventBUccIRQ = MDR_Off,
  .condEventBUcc   = PWR_xUcc_Lower,
  //  NVIC IRQ enable
  .activateNVIC_IRQ = USE_IRQ,
  .priorityIRQ = 0
};

void Test_Ucc(void);
void Test_BUcc(void);
void ShowResult(uint32_t selTest, double levelBelow, double levelAbove, PWR_LevelWaitCycles *waitCycles);
void ShowFault (uint32_t selTest, double levelBelow, double levelAbove);

//  На 7-ми сегментный слова не вывести, поэтомы результат выдается в UART
#ifdef LCD_IS_7SEG_DISPLAY
  #define UART_ENABLED    1
#else
  #define UART_ENABLED    0
#endif

int main(void)
{
  uint32_t freqCPU_Hz;
  
  //  Максимальная скорость тактирования
  MDR_CPU_SetClock_HSE_Max(MDR_Off);
  
  //  Инициализация кнопок и LCD дисплея (кроме 7-ми сегментного)
  freqCPU_Hz = MDR_CPU_GetFreqHz(true);
  MDRB_Buttons_Init(BTN_DEBOUNCE_MS, freqCPU_Hz);
  
#ifndef LCD_IS_7SEG_DISPLAY        
  MDRB_LCD_Init(freqCPU_Hz);
#endif
#if UART_ENABLED  
  MDR_UART_DBG_Init();
#endif
  
  //  Инициализация детектора питания
  MDR_Power_Init(&cfgPower);
  
#ifndef LCD_IS_7SEG_DISPLAY
  MDRB_LCD_Print("Test  Ucc: Up", 3);
  MDRB_LCD_Print("Test BUcc: Right", 5);
#endif
  
  while (1)
  {
    if (MDRB_BntClicked_Up(true))
    {
#ifndef LCD_IS_7SEG_DISPLAY      
      MDRB_LCD_ClearLine(3);
      MDRB_LCD_ClearLine(5);
#endif      
      Test_Ucc();
    }
    
    if (MDRB_BntClicked_Right(true))
    {
#ifndef LCD_IS_7SEG_DISPLAY      
      MDRB_LCD_ClearLine(3);
      MDRB_LCD_ClearLine(5);
#endif
      Test_BUcc();
    }
  }
}

#define TEST_ID_Ucc    0
#define TEST_ID_BUcc   1
static const double voltageUcc [] = {2.0, 2.2, 2.4, 2.6, 2.8, 3.0, 3.2, 3.4}; // of MDR_PWR_LevelUcc
static const double voltageBUcc[] = {1.8, 2.2, 2.6, 3.0}; // of MDR_PWR_LevelBUcc

void Test_Ucc(void)
{
  PWR_Range_Ucc       rangeUcc;
  PWR_LevelWaitCycles waitCycles;
  bool                rangeOk;

  rangeOk = FindRange_Ucc(MAX_WAIT_LEVEL_DELAY, &rangeUcc);
  if (rangeOk)
  {
    FindLevelSetCycles_Ucc(&rangeUcc, MAX_WAIT_LEVEL_DELAY, &waitCycles);
    ShowResult(TEST_ID_Ucc, voltageUcc[rangeUcc.levelBelow], voltageUcc[rangeUcc.levelAbove], &waitCycles);
  }
  else
    ShowFault(TEST_ID_Ucc, voltageUcc[rangeUcc.levelBelow], voltageUcc[rangeUcc.levelAbove]);
}

void Test_BUcc(void)
{
  PWR_Range_BUcc      rangeUcc;
  PWR_LevelWaitCycles waitCycles;
  bool                rangeOk;

  rangeOk = FindRange_BUcc(MAX_WAIT_LEVEL_DELAY, &rangeUcc);
  if (rangeOk)
  {  
    FindLevelSetCycles_BUcc(&rangeUcc, MAX_WAIT_LEVEL_DELAY, &waitCycles);
    ShowResult(TEST_ID_BUcc, voltageBUcc[rangeUcc.levelBelow], voltageBUcc[rangeUcc.levelAbove], &waitCycles);
  }
  else
    ShowFault(TEST_ID_BUcc, voltageBUcc[rangeUcc.levelBelow], voltageBUcc[rangeUcc.levelAbove]);
}

#ifndef LCD_IS_7SEG_DISPLAY
static void LCD_ShowResult(uint32_t selTest, double levelBelow, double levelAbove, PWR_LevelWaitCycles *waitCycles)
{
  static char message[64];
  
  if (selTest == TEST_ID_Ucc)
  {
    sprintf(message , "Ucc %.1f %.1f", levelBelow, levelAbove);
    MDRB_LCD_Print (message, 3);  
  }
  else
  {
    sprintf(message , "BUcc %.1f %.1f", levelBelow, levelAbove);
    MDRB_LCD_Print (message, 3);  
  }

  sprintf(message , "Tr=%d, Tf=%d", waitCycles->cyclesRise, waitCycles->cyclesFall);
  MDRB_LCD_Print (message, 5);  
}
#endif

#if UART_ENABLED
static void UART_SendResult(uint32_t selTest, double levelBelow, double levelAbove, PWR_LevelWaitCycles *waitCycles)
{
  if (selTest == TEST_ID_Ucc)
    printf("Ucc in %.1f .. %.1f\n", levelBelow, levelAbove);
  else
    printf("BUcc in %.1f .. %.1f\n", levelBelow, levelAbove);

  printf("Tr=%d, Tf=%d\n", waitCycles->cyclesRise, waitCycles->cyclesFall);
}
#endif

void ShowResult(uint32_t selTest, double levelBelow, double levelAbove, PWR_LevelWaitCycles *waitCycles)
{
#ifndef LCD_IS_7SEG_DISPLAY
  LCD_ShowResult(selTest, levelBelow, levelAbove, waitCycles);
#endif  
#if UART_ENABLED
  UART_SendResult(selTest, levelBelow, levelAbove, waitCycles);
#endif    
}

void ShowFault (uint32_t selTest, double levelBelow, double levelAbove)
{
#ifndef LCD_IS_7SEG_DISPLAY
  static char message[64];
  
  MDRB_LCD_Print ("Range Fault", 3);
  if (selTest == TEST_ID_Ucc)
  {
    sprintf(message , "Ucc %.1f %.1f", levelBelow, levelAbove);
    MDRB_LCD_Print (message, 5);  
  }
  else
  {
    sprintf(message , "BUcc %.1f %.1f", levelBelow, levelAbove);
    MDRB_LCD_Print (message, 5);  
  }
#endif  
  
#if UART_ENABLED
  printf("Range Fault\n");  
  if (selTest == TEST_ID_Ucc)
    printf("Ucc in %.1f .. %.1f\n", levelBelow, levelAbove);
  else
    printf("BUcc in %.1f .. %.1f\n", levelBelow, levelAbove);
#endif 
}




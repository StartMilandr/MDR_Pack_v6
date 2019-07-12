#include <MDR_RST_Clock.h>
#include <MDR_CLK_Checker.h>
#include <MDR_CPU_ClockSelect.h>
#include <MDR_SysTimer.h>

#include <MDRB_LEDs.h>
#include <MDRB_Buttons.h>

#ifndef USE_MDR1923VK014
  #include <MDRB_Buttons.h>
#endif

//  Выбрать только один источник частоты для теста!
#define USE_PLL_CLOCK    1
#define USE_HSI0_CLOCK   0


#if USE_PLL_CLOCK
  #define ACTIVE_CHECKER    MDR_CLKCHK_PLL0  
#elif USE_HSI0_CLOCK
  #define ACTIVE_CHECKER    MDR_CLKCHK_HSE0
#endif

//  ОПИСАНИЕ (USE_PLL_CLOCK=1):
//    Системный таймер, кнопки и светодиоды настраиваются при старте от HSI. Поэтому при работе от HSI светодиод LED1 от системного таймера должен мигать с периодом примерно 1сек.
//    Дальше настраивается тактирование от HSE0 через PLL0 с более высокой частотой. Поэтому на самом деле светодиод начинает мигать гораздо чаще.
//    Далее настраивается CLK_Checker в PLL0 который мониторит текущую частоту.
//    По кнопке KEY1 выключается PLL0, поэтому срабатывает CLK_Checker и переключает тактирование на HSI. Светодиод мигает с периодом ~1сек.
//    По кнопке KEY2 восстанавливается исходная частота от HSE0 через PLL0, светодиод возвращается к частому миганию.
//  ОСОБЕННОСТИ:
//    Для восставновления частоты от от HSE0 через PLL0 необходимо предварительно переключиться на любую другую частоту, в данном тесте это HSI от MAXCLK.
//    После этого можно перенастроить CLK_Checker и настроить частоту заново.
//  ВАЖНО:
//    Если после аварийного перехода на HSI выключить CLK_Checker битом MDR_CLK_CHK_EN_Msk, то пропадает тактовая частота, отладчик отваливается!
//    Если же CLK_Checker не выключить, то он продолжает мониторить частоту и сбрасывает ее аварийно на HSI.

//  ДОПОЛНИТЕЛЬНО (USE_HSI0_CLOCK=1):
//    Этот вариант сравнивает HSE и HSI при ручном изменении в отладчике HSI_Trim, блоке BKP. 
//    Менять надо хотя бы два значения HSI_Trim в троированных регистрах BKP чтобы значение применилось.
//    Наблюдать можно выработку флагов и изменение MAX_SHIFT_REG0 и MAX_SHIFT_REG1.
 


#define PERIOD_MS     1000
#define LED_TIMER     MDRB_LED_1
#define DEBOUNCE_MS   10

void SysTick_Handler(void);
void InitClockChecker(void);
void BreakClock(void);
void SetWorkClock(void);
void RestoreClock(void);

int main(void)
{ 
  MDR_CPU_SetClock_HSI_def(false);
  
  //  LED and Buttons
  MDRB_LED_Init(MDRB_LED_PinAll);
#ifndef USE_MDR1923VK014  
  MDRB_Buttons_Init(DEBOUNCE_MS, HSI_FREQ_HZ);
#endif

  MDRB_LED_Set(MDRB_LED_PinAll, true);
  MDR_Delay_ms(PERIOD_MS, HSI_FREQ_HZ);
  MDRB_LED_Set(MDRB_LED_PinAll, false);

  MDR_SysTimerStart_ms(PERIOD_MS, HSI_FREQ_HZ);
  
  //  Clock from HSE0_PLL0 40MHz
  MDR_CLK_Enable_RST_BPK();
  SetWorkClock();  
  InitClockChecker(); 
  
  while (1)
  {    
    if (MDRB_BntClicked_Up(true))
      BreakClock();
    
    if (MDRB_BntClicked_Right(true))
      RestoreClock();
    
    if (MDRB_BntClicked_Down(true))
      MDR_CLKCHK_ClearAllEvents(ACTIVE_CHECKER);
  }    
}

void SysTick_Handler(void)
{
  MDRB_LED_Toggle(LED_TIMER);
}

void BreakClock(void)
{
  MDR_CLOCK->PLL0_CLK &= ~MDR_RST_PLL_PLL_ON_Msk;   //  PLL OFF
}

void RestoreClock(void)
{
  //  Switch to safe frequency
  MDR_CPU_SetClock_HSI_def(false);

  //  Stop ClockChecker
  MDR_CLKCHK_Stop(ACTIVE_CHECKER);    
  //  Switch to work frequency
  SetWorkClock(); 
  //  Restart ClockChecker
  MDR_CLKCHK_ClearAllEvents(ACTIVE_CHECKER);
  MDR_CLKCHK_Restart(ACTIVE_CHECKER);
}


#if USE_PLL_CLOCK
// ============  Для тактирования от HSE1_PLL0  ==============

  void SetWorkClock(void)
  {     
    MDR_CPU_PLL_CfgHSE cfgPLL_HSE_40M = MDR_CLK_PLL_HSE_RES_DEF(MDRB_PLL_10MHz_TO_40MHz, MDRB_CPU_FREQ_SUPP_40MHz);
    MDR_CPU_SetClock_HSE0_PLL0(&cfgPLL_HSE_40M, true);  
  }
  
  void InitClockChecker(void)
  {
    // CASE HSI < CLK(HSE0):
    //   K0 = HSI / (HSI_PrescREG2 + 1) * (CLK_PrescREG1 + 1) / CLK =  8MHz / 1 * 40 / 40MHz = 8
    //   K1 = CLK / (CLK_PrescREG3 + 1) *  HSI_PrescREG0      / HSI = 40MHz / 5 *  8 /  8MHz = 8
    
    // K0_SlowEvent0 =  HSI        / (HSI_PrescREG2 + 1) * (CLK_PrescREG1 + 1) / (CLK - dF1) =  8MHz  / 1 * 40 / 35MHz  = 9.14
    // K0_SlowEvent1 =  HSI        / (HSI_PrescREG2 + 1) * (CLK_PrescREG1 + 1) / (CLK - dF2) =  8MHz  / 1 * 40 / 30MHz  = 10.6
    // K1_FastEvent2 = (CLK + dF1) / (CLK_PrescREG3 + 1) *  HSI_PrescREG0      /  HSI        = 50MHz  / 5 * 8  / 8MHz  = 10
    // K1_FastEvent3 = (CLK + dF2) / (CLK_PrescREG3 + 1) *  HSI_PrescREG0      /  HSI        = 60MHz  / 5 * 8  / 8MHz  = 12
       
    MDR_CLKCHK_Cfg cfgChk = {
      //  Prescallers with
      .slowHSI_PrescREG2 = 0,       // HSI_PrescREG2
      .slowCLK_PrescREG1 = 39,      // CLK_PrescREG1
      .fastCLK_PrescREG3 = 4,       // CLK_PrescREG3
      .fastHSI_PrescREG0 = 8,       // HSI_PrescREG0
    
      //  Event Levels
      .level_SlowEvent0 = 10,
      .level_SlowEvent1 = 11,
      .level_FastEvent2 = 10,
      .level_FastEvent3 = 12,
      //  go to HSI by any Event
      .enaGoHSI_byEvents.eventSel = MDR_CLKCHK_SEL_ALL_EVENTS
    };
    
    MDR_CLKCHK_Init(ACTIVE_CHECKER, &cfgChk);
  }

  
#elif USE_HSI0_CLOCK
// ============  Для тактирования от HSE1  ==============

  void SetWorkClock(void)  
  {  
    MDR_CPU_CfgHSE cfgHSE = MDR_CPU_CFG_HSE_RES_DEF;    
    MDR_CPU_SetClock_HSE0(&cfgHSE, HSE_TIMEOUT, true);  
  }

  
  void InitClockChecker(void)
  {
    // CASE HSI < CLK(HSE0):
    //   K0 = HSI / (HSI_PrescREG2 + 1) * (CLK_PrescREG1 + 1) / CLK =  8MHz / 2 * 10 / 10MHz = 4
    //   K1 = CLK / (CLK_PrescREG3 + 1) *  HSI_PrescREG0      / HSI = 10MHz / 2 *  8 /  8MHz = 5
    
    // K0_SlowEvent0 =  HSI        / (HSI_PrescREG2 + 1) * (CLK_PrescREG1 + 1) / (CLK - dF1) =  8MHz  / 2 * 10 / 8MHz  = 5
    // K0_SlowEvent1 =  HSI        / (HSI_PrescREG2 + 1) * (CLK_PrescREG1 + 1) / (CLK - dF2) =  8MHz  / 2 * 10 / 6MHz  = 6.6
    // K1_FastEvent2 = (CLK + dF1) / (CLK_PrescREG3 + 1) *  HSI_PrescREG0      /  HSI        = 12MHz  / 2 * 8  / 8MHz  = 6
    // K1_FastEvent3 = (CLK + dF2) / (CLK_PrescREG3 + 1) *  HSI_PrescREG0      /  HSI        = 16MHz  / 2 * 8  / 8MHz  = 8
       
    MDR_CLKCHK_Cfg cfgChk = {
      //  Prescallers with
      .slowHSI_PrescREG2 = 2 - 1,       // HSI_PrescREG2
      .slowCLK_PrescREG1 = 10 - 1,      // CLK_PrescREG1
      .fastCLK_PrescREG3 = 2 - 1,       // CLK_PrescREG3
      .fastHSI_PrescREG0 = 8,           // HSI_PrescREG0
      //  Event Levels
      .level_SlowEvent0 = 5,
      .level_SlowEvent1 = 7,
      .level_FastEvent2 = 6,
      .level_FastEvent3 = 8,
      //  go to HSI by any Event
      .enaGoHSI_byEvents.eventSel = MDR_CLKCHK_SEL_ALL_EVENTS
    };
    
    MDR_CLKCHK_Init(ACTIVE_CHECKER, &cfgChk);
  }
  
#endif



#include <MDR_RST_Clock.h>
#include <MDR_CLK_Checker.h>
#include <MDR_CPU_ClockSelect.h>
#include <MDR_SysTimer.h>

#include <MDRB_LEDs.h>
#include <MDRB_Buttons.h>

#ifndef USE_MDR1923VK014
  #include <MDRB_Buttons.h>
#endif

//  ОПИСАНИЕ:
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
  }    
}

void SysTick_Handler(void)
{
  MDRB_LED_Toggle(LED_TIMER);
}

void InitClockChecker(void)
{
  // K0 = (HSI / PrescSlow_HSI) * (PrescSlow_CLK / CLK) = 8MHz  / 1 * 50 / 40MHz = 10
  // K1 = (CLK / PrescFast_CLK) * (PrescFast_HSI / HSI) = 40MHz / 1 *  1 / 8MHz  = 5
  
  // K0_SlowEvent0 = (HSI / PrescSlow_HSI) * (PrescSlow_CLK / (CLK - dF0)) = 8MHz  / 1 * 50 / (40MHz - 8MHz)  = 12.5
  // K0_SlowEvent1 = (HSI / PrescSlow_HSI) * (PrescSlow_CLK / (CLK - dF1)) = 8MHz  / 1 * 50 / (40MHz - 12MHz) = 14.3
  // K1_FastEvent2 = ((CLK + dF2) / PrescFast_CLK) * (PrescFast_HSI / HSI) = (40MHz +  8MHz) / 1 *  1 / 8MHz  = 6
  // K1_FastEvent3 = ((CLK + dF3) / PrescFast_CLK) * (PrescFast_HSI / HSI) = (40MHz + 16MHz) / 1 *  1 / 8MHz  = 7
  
  MDR_CLKCHK_Cfg cfgChk = {
    //  Prescallers
    .PrescSlow_HSI = 1,
    .PrescSlow_CLK = 50,
    .PrescFast_HSI = 1,  
    .PrescFast_CLK = 1,
    //  Event Levels
    .level_SlowEvent0 = 12,
    .level_SlowEvent1 = 14,
    .level_FastEvent2 = 6,
    .level_FastEvent3 = 7,
    //  go to HSI by any Event
    .enaGoHSI_byEvents.eventSel = MDR_CLKCHK_SEL_ALL_EVENTS
  };
  
  MDR_CLKCHK_Init(MDR_CLKCHK_PLL0, &cfgChk);
}

void BreakClock(void)
{
  //  PLL OFF
  MDR_CLOCK->PLL0_CLK &= ~MDR_RST_PLL_PLL_ON_Msk;
}

void RestoreClock(void)
{
  //  Switch to safe frequency
  MDR_CPU_SetClock_HSI_def(false);

  //  Stop ClockChecker
  MDR_CLKCHK_Stop(MDR_CLKCHK_PLL0);    
  //  Switch to work frequency
  SetWorkClock(); 
  //  Restart ClockChecker
  MDR_CLKCHK_ClearAllEvents(MDR_CLKCHK_PLL0);
  MDR_CLKCHK_Restart(MDR_CLKCHK_PLL0);
}

void SetWorkClock(void)
{  
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE_40M = MDR_CLK_PLL_HSE_RES_DEF(MDRB_PLL_8MHz_TO_40MHz, MDRB_CPU_FREQ_SUPP_40MHz);
  MDR_CPU_SetClock_HSE0_PLL0(&cfgPLL_HSE_40M, true);  
}


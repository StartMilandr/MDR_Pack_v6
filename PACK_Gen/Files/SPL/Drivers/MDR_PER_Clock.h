#ifndef _MDR_PER_CLOCK_H
#define _MDR_PER_CLOCK_H

#include <MDR_Config.h>
#include <MDR_Funcs.h>
#include <MDR_Types.h>

//=================   Переключение входных мультиплексоров С1 ==================
void MDR_SelectClock_HSI_C1(MDR_CLK_DIV_256 divClk);
void MDR_SelectClock_HSE_C1(MDR_CLK_DIV_256 divClk);

#ifdef MDR_PER_CLK_LIKE_VE4
  void MDR_SelectClock_PER1_C1(MDR_CLK_SEL_LSIE2 selPer1C1);
#else
  void MDR_SelectClock_USB_C1(MDR_CLK_SEL_HSIE2 selPer1C1);
#endif


//=================   Выбор источника тактовой частоты для UART, SSP, Timers ==================
//  В большинстве МК источник  тактирования всегда HCLK (==CPU_CLK), кроме:
#ifdef MDR_PER_CLOCK_SELF_TIM_UART_SSP
  // For 1986VK214 Only
  void MDR_SetClock_Uart1 (MDR_CLK_SEL_PER selClockSrc);
  void MDR_SetClock_Uart2 (MDR_CLK_SEL_PER selClockSrc);
  void MDR_SetClock_SSP1  (MDR_CLK_SEL_PER selClockSrc);
  void MDR_SetClock_Timer1(MDR_CLK_SEL_PER selClockSrc);
  void MDR_SetClock_Timer2(MDR_CLK_SEL_PER selClockSrc);
  
#elif defined (MDR_ADC_CLK_LIKE_VE4)
  // For 1986VK234 and 1986VE4 - устанавливает PER1_C2
  void MDR_SetClock_UartTimSSP(MDR_CLK_SEL_PER selClockSrc);  
#endif


//=================   Выбор источника тактовой частоты для ADC_CLOCK ==================
//  Выключение частоты ADC_Clock
__STATIC_INLINE void MDR_ADC_SetClock_Off(void) {MDR_CLOCK->ADC_CLOCK &= ~MDR_RST_ADC__ADC_CLK_EN_Msk;}

//  Включение частоты ADC_Clock от разных источников
void MDR_ADC_SetClock_CPU_C1(MDR_CLK_DIV_256 divClk);
void MDR_ADC_SetClock_PllCPU(MDR_CLK_DIV_256 divClk);
void MDR_ADC_SetClock_HSI_C1(MDR_CLK_DIV_256 divClk);

// Настройка частоты ADC_Clock
#ifndef MDR_ADC_CLK_LIKE_VE4
  //  For 1986VE9x,VE1,VE3, 1901VC1
  void MDR_ADC_SetClock_LSI(MDR_CLK_DIV_256 divClk);
  void MDR_ADC_SetClock_LSE(MDR_CLK_DIV_256 divClk);

  void MDR_ADC_SetClock_USB_C1(MDR_CLK_DIV_256 divClk);
  void MDR_ADC_SetClock_USB_C2(MDR_CLK_DIV_256 divClk);  

#else
  //  For 1986VE4,VE214,VE234 
  void MDR_ADC_SetClock_PER1_C1(MDR_CLK_DIV_256 divClk);
#endif


//=================   Выбор источника тактовой частоты для ADCUI_CLOCK ==================
#ifdef MDR_ADCUI_CLOCK_FROM_PER_CLOCK
  void MDR_ADCUI_SetClock_PllCPU(MDR_CLK_DIV_256 divClk);
  void MDR_ADCUI_SetClock_HSI_С1(MDR_CLK_DIV_256 divClk);
  void MDR_ADCUI_SetClock_CPU_C1(MDR_CLK_DIV_256 divClk);
  void MDR_ADCUI_SetClock_PER_С1(MDR_CLK_DIV_256 divClk);
#endif




#endif  // _MDR_PER_CLOCK_H


#ifndef _MDR_PER_CLOCK_VEx_H
#define _MDR_PER_CLOCK_VEx_H

#include <MDR_Config.h>
#include <MDR_Funcs.h>
#include <MDR_Types.h>


//=================   Переключение входных мультиплексоров С1 ==================
void MDR_SelectClock_HSI_C1(MDR_Div256P divClk);
void MDR_SelectClock_HSE_C1(MDR_Div256P divClk);

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
void MDR_ADC_SetClock_CPU_C1(MDR_Div256P divClk);
void MDR_ADC_SetClock_PllCPU(MDR_Div256P divClk);
void MDR_ADC_SetClock_HSI_C1(MDR_Div256P divClk);

// Настройка частоты ADC_Clock
#ifndef MDR_ADC_CLK_LIKE_VE4
  //  For 1986VE9x,VE1,VE3, 1901VC1
  void MDR_ADC_SetClock_LSI(MDR_Div256P divClk);
  void MDR_ADC_SetClock_LSE(MDR_Div256P divClk);

  void MDR_ADC_SetClock_USB_C1(MDR_Div256P divClk);
  void MDR_ADC_SetClock_USB_C2(MDR_Div256P divClk);  

#else
  //  For 1986VE4,VE214,VE234 
  void MDR_ADC_SetClock_PER1_C1(MDR_Div256P divClk);
#endif


//=================   Выбор источника тактовой частоты для ADCUI_CLOCK ==================
#ifdef MDR_ADCUI_CLOCK_FROM_PER_CLOCK
  void MDR_ADCUI_SetClock_PllCPU(MDR_Div256P divClk);
  void MDR_ADCUI_SetClock_HSI_C1(MDR_Div256P divClk);
  void MDR_ADCUI_SetClock_CPU_C1(MDR_Div256P divClk);
  void MDR_ADCUI_SetClock_PER1_C1(MDR_Div256P divClk);
#endif


//===============  Получение некоторых частот ===============
uint32_t MDR_GetFreqHz_CPU_C1(void);
uint32_t MDR_GetFreqHz_PLLCPUo(void);

#ifdef MDR_PER_CLOCK_LIKE_VE4
  uint32_t  MDR_GetFreqHz_Per1_C1(void);
  uint32_t _MDR_GetFreqHz_Per1_C2(MDR_CLK_SEL_PER selPER_C2);

  #ifdef MDR_PER_CLOCK_SELF_TIM_UART_SSP
    #define  MDR_GetFreqHz_UART1_C2()  _MDR_GetFreqHz_Per1_C2(MDR_CLOCK->PER1_CLOCK_b.UART1_C2_SEL)
    #define  MDR_GetFreqHz_UART2_C2()  _MDR_GetFreqHz_Per1_C2(MDR_CLOCK->PER1_CLOCK_b.UART2_C2_SEL)
    #define  MDR_GetFreqHz_SSP1_C2()   _MDR_GetFreqHz_Per1_C2(MDR_CLOCK->PER1_CLOCK_b.SSP1_C2_SEL)
    #define  MDR_GetFreqHz_SSP2_C2()   _MDR_GetFreqHz_Per1_C2(MDR_CLOCK->PER1_CLOCK_b.SSP2_C2_SEL)
    #define  MDR_GetFreqHz_TIM1_C2()   _MDR_GetFreqHz_Per1_C2(MDR_CLOCK->PER1_CLOCK_b.TIM1_C2_SEL)
    #define  MDR_GetFreqHz_TIM2_C2()   _MDR_GetFreqHz_Per1_C2(MDR_CLOCK->PER1_CLOCK_b.TIM2_C2_SEL)
  #else
    #define  MDR_GetFreqHz_Per1_C2()   _MDR_GetFreqHz_Per1_C2(MDR_CLOCK->PER1_CLOCK_b.PER1_C2_SEL)  
  #endif
#endif

  
#endif  // _MDR_PER_CLOCK_VEx_H


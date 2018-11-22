#ifndef _MDR_PER_CLOCK_H
#define _MDR_PER_CLOCK_H

#include <MDR_Config.h>
#include <MDR_Funcs.h>
#include <MDR_Types.h>

//  Выключение частоты ADC_Clock
__STATIC_INLINE void MDR_ADC_SetClock_Off(void) {MDR_CLOCK->ADC_CLOCK &= ~MDR_RST_ADC__ADC_CLK_EN_Msk;}

//  Включение частоты ADC_Clock от источников
void MDR_ADC_SetClock_InputCPU(MDR_CLK_DIV_256 divClk);
void MDR_ADC_SetClock_PllCPU(MDR_CLK_DIV_256 divClk);
void MDR_ADC_SetClock_RTSHSI(MDR_CLK_DIV_256 divClk);

// Настройка частоты ADC_Clock
#ifndef MDR_ADC_CLK_LIKE_VE4
  //  For 1986VE9x,VE1,VE3, 1901VC1
  void MDR_ADC_SetClock_LSI(MDR_CLK_DIV_256 divClk);
  void MDR_ADC_SetClock_LSE(MDR_CLK_DIV_256 divClk);

  void MDR_ADC_SetClock_InputUSB(MDR_CLK_DIV_256 divClk);
  void MDR_ADC_SetClock_PllUSB(MDR_CLK_DIV_256 divClk);  

  //  Переопределяют выбор тактирования сторонних блоков - CPU, USB, RTS
  void MDR_ADC_SetClockEx_InputCPU(MDR_CLK_SEL_HSIE2 selInp, MDR_CLK_DIV_256 divClk); //  HSI,HSI/2,HSE,HSE/2
  void MDR_ADC_SetClockEx_InputUSB(MDR_CLK_SEL_HSIE2 selInp, MDR_CLK_DIV_256 divClk); //  HSI,HSI/2,HSE,HSE/2
  void MDR_ADC_SetClockEx_RTSHSI(MDR_CLK_DIV_256 divHSI, MDR_CLK_DIV_256 divClk);

#else
  //  For 1986VE4,VE214,VE234 
  void MDR_ADC_SetClock_InputPER(MDR_CLK_DIV_256 divClk);
  
  //  Переопеределяют выбор частоты PER_Clock общей для нескольких блоков. (мультиплексор PER1_C1)
  void MDR_ADC_SetClockEx_InputPER(MDR_CLK_SEL_LSIE2 selLSIE, MDR_CLK_DIV_256 divClk);  //  LSI,LSI/2,LSE/LSE/2  
  void MDR_ADC_SetClockEx_InputCPU(MDR_CLK_SEL_HSIE2 selInp, MDR_CLK_DIV_256 divClk);   //  HSI,HSI/2,HSE,HSE/2
  void MDR_ADC_SetClockEx_RTSHSI(MDR_CLK_DIV_256 divHSI, MDR_CLK_DIV_256 divClk);
#endif



#endif  // _MDR_PER_CLOCK_H


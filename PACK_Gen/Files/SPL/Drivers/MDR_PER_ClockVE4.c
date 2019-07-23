#include <MDR_PER_Clock.h>


//=================   Переключение входных мультиплексоров С1 ==================
void MDR_SelectClock_HSI_C1(MDR_Div256P divClk)
{
  MDR_CLOCK->RTC_CLOCK = MDR_MaskClrSet(MDR_CLOCK->RTC_CLOCK, MDR_RST_RTC__HSI_SEL_Msk, VAL2FLD_Pos(divClk,  MDR_RST_RTC__HSI_SEL_Pos));
}

void MDR_SelectClock_HSE_C1(MDR_Div256P divClk)
{
  MDR_CLOCK->RTC_CLOCK = MDR_MaskClrSet(MDR_CLOCK->RTC_CLOCK, MDR_RST_RTC__HSE_SEL_Msk, VAL2FLD_Pos(divClk,  MDR_RST_RTC__HSE_SEL_Pos));
}

#ifdef MDR_PER_CLK_LIKE_VE4
  void MDR_SelectClock_PER1_C1(MDR_CLK_SEL_LSIE2 selPer1C1)
  {
    MDR_CLOCK->PER1_CLOCK = MDR_MaskClrSet(MDR_CLOCK->PER1_CLOCK, MDR_RST_PER1__PER1_C1_SEL_Msk, VAL2FLD_Pos(selPer1C1,  MDR_RST_PER1__PER1_C1_SEL_Pos));
  }
#endif

//=================   Задание частоты ADC_CLOCK ==================
//  Выбор готовых частот, не влияют на настройки других блоков.
#define   ADC_CLEAR_C1    (MDR_RST_ADC__ADC_CLK_EN_Msk | MDR_RST_ADC__ADC_C3_SEL_Msk | MDR_RST_ADC__ADC_C1_SEL_Msk)

static void ADC_Set_C1C3_loc(uint32_t regADC, uint32_t selC1, MDR_Div256P divClk)
{
  regADC &= ~ADC_CLEAR_C1;
  regADC |= VAL2FLD_Pos(selC1,  MDR_RST_ADC__ADC_C1_SEL_Pos) 
          | VAL2FLD_Pos(divClk, MDR_RST_ADC__ADC_C3_SEL_Pos)
          | VAL2FLD_Pos(MDR_On, MDR_RST_ADC__ADC_CLK_EN_Pos);
  
  MDR_CLOCK->ADC_CLOCK = regADC;  
}

void MDR_ADC_SetClock_PllCPU(MDR_Div256P divClk)
{
  ADC_Set_C1C3_loc(MDR_CLOCK->ADC_CLOCK, MDR_PER_PLLCPUo, divClk);
}

void MDR_ADC_SetClock_HSI_C1(MDR_Div256P divClk)
{
  ADC_Set_C1C3_loc(MDR_CLOCK->ADC_CLOCK, MDR_PER_HSI_C1, divClk);
}

void MDR_ADC_SetClock_CPU_C1(MDR_Div256P divClk)
{
  ADC_Set_C1C3_loc(MDR_CLOCK->ADC_CLOCK, MDR_PER_CPU_C1, divClk);
}

void MDR_ADC_SetClock_PER1_C1(MDR_Div256P divClk)
{
  ADC_Set_C1C3_loc(MDR_CLOCK->ADC_CLOCK, MDR_PER_PER1_C1, divClk);
}


//=================   Выбор источника тактовой частоты для ADCUI_CLOCK ==================
#ifdef MDR_ADCUI_CLOCK_FROM_PER_CLOCK
  #define   ADCUI_CLEAR_C1    (MDR_RST_ADC__ADCUI_CLK_EN_Msk | MDR_RST_ADC__ADCUI_C3_SEL_Msk | MDR_RST_ADC__ADCUI_C1_SEL_Msk)

  static void ADCUI_Set_C1C3_loc(uint32_t regADC, uint32_t selC1, MDR_Div256P divClk)
  {
    regADC &= ~ADCUI_CLEAR_C1;
    regADC |= VAL2FLD_Pos(selC1,  MDR_RST_ADC__ADCUI_C1_SEL_Pos) 
            | VAL2FLD_Pos(divClk, MDR_RST_ADC__ADCUI_C3_SEL_Pos)
            | VAL2FLD_Pos(MDR_On, MDR_RST_ADC__ADCUI_CLK_EN_Pos);
    
    MDR_CLOCK->ADC_CLOCK = regADC;  
  }

  void MDR_ADCUI_SetClock_PllCPU(MDR_Div256P divClk)
  {
    ADCUI_Set_C1C3_loc(MDR_CLOCK->ADC_CLOCK, MDR_PER_PLLCPUo, divClk);
  }

  void MDR_ADCUI_SetClock_HSI_C1(MDR_Div256P divClk)
  {
    ADCUI_Set_C1C3_loc(MDR_CLOCK->ADC_CLOCK, MDR_PER_HSI_C1, divClk);
  }

  void MDR_ADCUI_SetClock_CPU_C1(MDR_Div256P divClk)
  {
    ADCUI_Set_C1C3_loc(MDR_CLOCK->ADC_CLOCK, MDR_PER_CPU_C1, divClk);
  }

  void MDR_ADCUI_SetClock_PER1_C1(MDR_Div256P divClk)
  {
    ADCUI_Set_C1C3_loc(MDR_CLOCK->ADC_CLOCK, MDR_PER_PER1_C1, divClk);
  }
#endif


//=================   Выбор источника тактовой частоты для UART_CLOCK ==================
#ifdef MDR_PER_CLOCK_SELF_TIM_UART_SSP
  // For 1986VK214 Only
  void MDR_SetClock_Uart1 (MDR_CLK_SEL_PER selClockSrc)
  {   
    MDR_CLOCK->PER1_CLOCK = MDR_MaskClrSet(MDR_CLOCK->PER1_CLOCK, MDR_RST_PER1__UART1_C2_SEL_Msk, VAL2FLD_Pos(selClockSrc,  MDR_RST_PER1__UART1_C2_SEL_Pos));
  }
  
  void MDR_SetClock_Uart2 (MDR_CLK_SEL_PER selClockSrc)
  {
    MDR_CLOCK->PER1_CLOCK = MDR_MaskClrSet(MDR_CLOCK->PER1_CLOCK, MDR_RST_PER1__UART2_C2_SEL_Msk, VAL2FLD_Pos(selClockSrc,  MDR_RST_PER1__UART2_C2_SEL_Pos));
  }
  
  void MDR_SetClock_SSP1  (MDR_CLK_SEL_PER selClockSrc)
  {
    MDR_CLOCK->PER1_CLOCK = MDR_MaskClrSet(MDR_CLOCK->PER1_CLOCK, MDR_RST_PER1__SSP2_C2_SEL_Msk, VAL2FLD_Pos(selClockSrc,  MDR_RST_PER1__SSP2_C2_SEL_Pos));  
  }
  
  void MDR_SetClock_Timer1(MDR_CLK_SEL_PER selClockSrc)
  {
    MDR_CLOCK->PER1_CLOCK = MDR_MaskClrSet(MDR_CLOCK->PER1_CLOCK, MDR_RST_PER1__TIM1_C2_SEL_Msk, VAL2FLD_Pos(selClockSrc,  MDR_RST_PER1__TIM1_C2_SEL_Pos));  
  }
  
  void MDR_SetClock_Timer2(MDR_CLK_SEL_PER selClockSrc)
  {
    MDR_CLOCK->PER1_CLOCK = MDR_MaskClrSet(MDR_CLOCK->PER1_CLOCK, MDR_RST_PER1__TIM2_C2_SEL_Msk, VAL2FLD_Pos(selClockSrc,  MDR_RST_PER1__TIM2_C2_SEL_Pos));  
  }
  
#else
  // For 1986VK234 and 1986VE4 - устанавливает PER1_C2
  void MDR_SetClock_UartTimSSP(MDR_CLK_SEL_PER selClockSrc)
  {    
    MDR_CLOCK->PER1_CLOCK = MDR_MaskClrSet(MDR_CLOCK->PER1_CLOCK, MDR_RST_PER1__PER1_C2_SEL_Msk, VAL2FLD_Pos(selClockSrc,  MDR_RST_PER1__PER1_C2_SEL_Pos));  
  }
#endif


//===============  Получение некоторых частот ===============
static const uint32_t _CPU_C1_FreqHz[] = {HSI_FREQ_HZ, HSI_FREQ_HZ >> 1, HSE_FREQ_HZ, HSE_FREQ_HZ >> 1};

uint32_t MDR_GetFreqHz_CPU_C1(void)
{
  return _CPU_C1_FreqHz[(uint32_t)MDR_CLOCK->CPU_CLOCK_b.CPU_C1_SEL];  
}


uint32_t MDR_GetFreqHz_PLLCPUo(void)
{
  return MDR_GetFreqHz_CPU_C1() * ((uint32_t)MDR_CLOCK->PLL_CONTROL_b.PLL_CPU_MUL + 1);  
}

static const uint32_t _PER1_C1_FreqHz[] = {LSI_FREQ_HZ, LSI_FREQ_HZ >> 1, LSE_FREQ_HZ, LSE_FREQ_HZ >> 1};

uint32_t MDR_GetFreqHz_Per1_C1(void)
{
  return _PER1_C1_FreqHz[(uint32_t)MDR_CLOCK->PER1_CLOCK_b.PER1_C1_SEL];  
}

uint32_t _MDR_GetFreqHz_Per1_C2(MDR_CLK_SEL_PER selPER_C2)  
{  
  switch (selPER_C2)
  {
    case MDR_PER_CPU_C1: return MDR_GetFreqHz_CPU_C1();
    case MDR_PER_PER1_C1: return MDR_GetFreqHz_Per1_C1();
    case MDR_PER_PLLCPUo: return MDR_GetFreqHz_PLLCPUo();
    case MDR_PER_HSI_C1: return HSI_FREQ_HZ;
  }
  return 0; // Error
}





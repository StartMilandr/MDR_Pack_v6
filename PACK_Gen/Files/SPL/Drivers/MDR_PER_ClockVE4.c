#include <MDR_PER_Clock.h>

//=================   Задание частоты ADC_CLOCK ==================
//  Выбор готовых частот, не влияют на настройки других блоков.
#define   ADC_CLEAR_C1    (MDR_RST_ADC__ADC_CLK_EN_Msk | MDR_RST_ADC__ADC_C3_SEL_Msk | MDR_RST_ADC__ADC_C1_SEL_Msk)

static void ADC_Set_C1C3_loc(uint32_t regADC, uint32_t selC1, MDR_CLK_DIV_256 divClk)
{
  regADC &= ~ADC_CLEAR_C1;
  regADC |= VAL2FLD_Pos(selC1,  MDR_RST_ADC__ADC_C1_SEL_Pos) 
          | VAL2FLD_Pos(divClk, MDR_RST_ADC__ADC_C3_SEL_Pos)
          | VAL2FLD_Pos(MDR_On, MDR_RST_ADC__ADC_CLK_EN_Pos);
  
  MDR_CLOCK->ADC_CLOCK = regADC;  
}

void MDR_ADC_SetClock_PllCPU(MDR_CLK_DIV_256 divClk)
{
  ADC_Set_C1C3_loc(MDR_CLOCK->ADC_CLOCK, MDR_PER_PLLCPUo, divClk);
}

void MDR_ADC_SetClock_RTSHSI(MDR_CLK_DIV_256 divClk)
{
  ADC_Set_C1C3_loc(MDR_CLOCK->ADC_CLOCK, MDR_PER_HSI_C1, divClk);
}

void MDR_ADC_SetClock_InputCPU(MDR_CLK_DIV_256 divClk)
{
  ADC_Set_C1C3_loc(MDR_CLOCK->ADC_CLOCK, MDR_PER_CPU_C1, divClk);
}

void MDR_ADC_SetClock_InputPER(MDR_CLK_DIV_256 divClk)
{
  ADC_Set_C1C3_loc(MDR_CLOCK->ADC_CLOCK, MDR_PER_PER1_C1, divClk);
}


//  Переопеределяют выбор частоты PER_Clock общей для нескольких блоков. (мультиплексор PER1_C1)
void MDR_ADC_SetClockEx_InputPER(MDR_CLK_SEL_LSIE2 selLSIE, MDR_CLK_DIV_256 divClk)  //  LSI,LSI/2,LSE/LSE/2  
{
  uint32_t regPER1 = MDR_CLOCK->PER1_CLOCK;
  regPER1 &= ~MDR_RST_PER1__PER1_C1_SEL_Msk;
  MDR_CLOCK->PER1_CLOCK = regPER1 | VAL2FLD_Pos(selLSIE, MDR_RST_PER1__PER1_C1_SEL_Pos);  
  
  MDR_ADC_SetClock_InputPER(divClk);
}

void MDR_ADC_SetClockEx_InputCPU(MDR_CLK_SEL_HSIE2 selInp, MDR_CLK_DIV_256 divClk)   //  HSI,HSI/2,HSE,HSE/2
{
  uint32_t regCPU = MDR_CLOCK->CPU_CLOCK;
  regCPU &= ~MDR_RST_CPU__C1_SEL_Msk;
  MDR_CLOCK->CPU_CLOCK = regCPU | VAL2FLD_Pos(selInp, MDR_RST_CPU__C1_SEL_Pos);  

  MDR_ADC_SetClock_InputCPU(divClk);  
}

void MDR_ADC_SetClockEx_RTSHSI(MDR_CLK_DIV_256 divHSI, MDR_CLK_DIV_256 divClk)
{
  uint32_t regADC = MDR_CLOCK->RTC_CLOCK;
  regADC &= ~MDR_RST_RTC__HSI_SEL_Msk;
  MDR_CLOCK->RTC_CLOCK = regADC | VAL2FLD_Pos(divHSI, MDR_RST_RTC__HSI_SEL_Pos);  

  MDR_ADC_SetClock_RTSHSI(divClk);
}

//=================   Выбор источника тактовой частоты для SSP_CLOCK ==================
#ifdef MDR_SSP_CLOCK_FROM_PER_CLOCK
void MDR_SelectSrcFor_UartTimSSP_Clock(MDR_CLK_SEL_PER selClockSource)
{
  uint32_t regPER1 = MDR_CLOCK->PER1_CLOCK;
  regPER1 &= ~MDR_RST_PER1__PER1_C2_SEL_Msk;
  regPER1 |= VAL2FLD_Pos(selClockSource,  MDR_RST_PER1__PER1_C2_SEL_Pos);

  MDR_CLOCK->PER1_CLOCK = regPER1;  
}
#endif


//=================   Выбор источника тактовой частоты для SSP_CLOCK ==================
#ifdef MDR_SSP_CLOCK_FROM_PER_CLOCK
//  Выбор готовых частот, не влияют на настройки других блоков.
#define   ADCUI_CLEAR_C1    (MDR_RST_ADC__ADCUI_CLK_EN_Msk | MDR_RST_ADC__ADCUI_C3_SEL_Msk | MDR_RST_ADC__ADCUI_C1_SEL_Msk)

static void ADCUI_Set_C1C3_loc(uint32_t regADC, uint32_t selC1, MDR_CLK_DIV_256 divClk)
{
  regADC &= ~ADCUI_CLEAR_C1;
  regADC |= VAL2FLD_Pos(selC1,  MDR_RST_ADC__ADCUI_C1_SEL_Pos) 
          | VAL2FLD_Pos(divClk, MDR_RST_ADC__ADCUI_C3_SEL_Pos)
          | VAL2FLD_Pos(MDR_On, MDR_RST_ADC__ADCUI_CLK_EN_Pos);
  
  MDR_CLOCK->ADC_CLOCK = regADC;  
}

void MDR_ADCUI_SetClock_PllCPU(MDR_CLK_DIV_256 divClk)
{
  ADCUI_Set_C1C3_loc(MDR_CLOCK->ADC_CLOCK, MDR_PER_PLLCPUo, divClk);
}

void MDR_ADCUI_SetClock_RTSHSI(MDR_CLK_DIV_256 divClk)
{
  ADCUI_Set_C1C3_loc(MDR_CLOCK->ADC_CLOCK, MDR_PER_HSI_C1, divClk);
}

void MDR_ADCUI_SetClock_InputCPU(MDR_CLK_DIV_256 divClk)
{
  ADCUI_Set_C1C3_loc(MDR_CLOCK->ADC_CLOCK, MDR_PER_CPU_C1, divClk);
}

void MDR_ADCUI_SetClock_InputPER(MDR_CLK_DIV_256 divClk)
{
  ADCUI_Set_C1C3_loc(MDR_CLOCK->ADC_CLOCK, MDR_PER_PER1_C1, divClk);
}
#endif


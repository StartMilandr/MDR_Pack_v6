#include <MDR_PER_Clock.h>

//==============================    ADC_CLOCK ===================================
//  Выбор готовых частот, не влияют на настройки других блоков.
#define   ADC_CLEAR_C2    (MDR_RST_ADC__ADC_CLK_EN_Msk | MDR_RST_ADC__ADC_C3_SEL_Msk | MDR_RST_ADC__ADC_C2_SEL_Msk)

static void ADC_Set_C2C3_loc(uint32_t regADC, uint32_t selC2, MDR_CLK_DIV_256 divClk)
{
  regADC &= ~ADC_CLEAR_C2;
  regADC |= VAL2FLD_Pos(selC2, MDR_RST_ADC__ADC_C2_SEL_Pos) 
          | VAL2FLD_Pos(divClk, MDR_RST_ADC__ADC_C3_SEL_Pos)
          | VAL2FLD_Pos(MDR_On, MDR_RST_ADC__ADC_CLK_EN_Pos);
  
  MDR_CLOCK->ADC_CLOCK = regADC;  
}

void MDR_ADC_SetClock_LSI(MDR_CLK_DIV_256 divClk)
{
  ADC_Set_C2C3_loc(MDR_CLOCK->ADC_CLOCK, MDR_ADC_C2_LSI, divClk);
}

void MDR_ADC_SetClock_LSE(MDR_CLK_DIV_256 divClk)
{
  ADC_Set_C2C3_loc(MDR_CLOCK->ADC_CLOCK, MDR_ADC_C2_LSE, divClk);  
}

void MDR_ADC_SetClock_RTSHSI(MDR_CLK_DIV_256 divClk)
{
  ADC_Set_C2C3_loc(MDR_CLOCK->ADC_CLOCK, MDR_ADC_C2_HSI_C1, divClk);  
}

static void ADC_Set_C1_loc(MDR_CLK_ADC_C1 selC1, MDR_CLK_DIV_256 divClk)
{
  uint32_t regADC = MDR_CLOCK->ADC_CLOCK;
  
  regADC &= ~MDR_RST_ADC__ADC_C1_SEL_Msk;
  regADC |= VAL2FLD_Pos(selC1, MDR_RST_ADC__ADC_C2_SEL_Pos);
  
  ADC_Set_C2C3_loc(regADC, MDR_ADC_C2_ADC_C1, divClk);  
}

void MDR_ADC_SetClock_PllCPU(MDR_CLK_DIV_256 divClk)
{
  ADC_Set_C1_loc(MDR_ADC_C1_CPU_C2, divClk);
}

void MDR_ADC_SetClock_PllUSB(MDR_CLK_DIV_256 divClk)
{
  ADC_Set_C1_loc(MDR_ADC_C1_USB_C2, divClk);
}

void MDR_ADC_SetClock_InputCPU(MDR_CLK_DIV_256 divClk)
{
  ADC_Set_C1_loc(MDR_ADC_C1_CPU_C1, divClk);
}

void MDR_ADC_SetClock_InputUSB(MDR_CLK_DIV_256 divClk)
{
  ADC_Set_C1_loc(MDR_ADC_C1_USB_C1, divClk);
}


//  Переопределяют настройку тактирования сторонних блоков
void MDR_ADC_SetClockEx_RTSHSI(MDR_CLK_DIV_256 divHSI, MDR_CLK_DIV_256 divClk)
{
  uint32_t regADC = MDR_CLOCK->RTC_CLOCK;
  regADC &= ~MDR_RST_RTC__HSI_SEL_Msk;
  MDR_CLOCK->RTC_CLOCK = regADC | VAL2FLD_Pos(divHSI, MDR_RST_RTC__HSI_SEL_Pos);  

  ADC_Set_C2C3_loc(MDR_CLOCK->ADC_CLOCK, MDR_ADC_C2_HSI_C1, divClk);
}


//  Change input CPU and USB
void MDR_ADC_SetClockEx_InputCPU(MDR_CLK_SEL_HSIE2 selInp, MDR_CLK_DIV_256 divClk)
{
  uint32_t regCPU = MDR_CLOCK->CPU_CLOCK;
  regCPU &= ~MDR_RST_CPU__C1_SEL_Msk;
  MDR_CLOCK->CPU_CLOCK = regCPU | VAL2FLD_Pos(selInp, MDR_RST_CPU__C1_SEL_Pos);  

  ADC_Set_C1_loc(MDR_ADC_C1_CPU_C2, divClk);
}

void MDR_ADC_SetClockEx_InputUSB(MDR_CLK_SEL_HSIE2 selInp, MDR_CLK_DIV_256 divClk)
{
  uint32_t regUSB = MDR_CLOCK->USB_CLOCK;
  regUSB &= ~MDR_RST_USB__C1_SEL_Msk;
  MDR_CLOCK->USB_CLOCK = regUSB | VAL2FLD_Pos(selInp, MDR_RST_USB__C1_SEL_Pos);  
  
  ADC_Set_C1_loc(MDR_ADC_C1_USB_C2, divClk);
}


//==============================    SSP_CLOCK ===================================


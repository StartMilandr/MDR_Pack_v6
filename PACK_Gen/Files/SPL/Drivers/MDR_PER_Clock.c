#include <MDR_PER_Clock.h>

//=================   Переключение входных мультиплексоров С1 ==================
void MDR_SelectClock_HSI_C1(MDR_CLK_DIV_256 divClk)
{
  MDR_CLOCK->RTC_CLOCK = MaskClrSet(MDR_CLOCK->RTC_CLOCK, MDR_RST_RTC__HSI_SEL_Msk, VAL2FLD_Pos(divClk,  MDR_RST_RTC__HSI_SEL_Pos));
}

void MDR_SelectClock_HSE_C1(MDR_CLK_DIV_256 divClk)
{
  MDR_CLOCK->RTC_CLOCK = MaskClrSet(MDR_CLOCK->RTC_CLOCK, MDR_RST_RTC__HSE_SEL_Msk, VAL2FLD_Pos(divClk,  MDR_RST_RTC__HSE_SEL_Pos));
}

void MDR_SelectClock_USB_C1(MDR_CLK_SEL_HSIE2 selPer1C1)
{
  MDR_CLOCK->USB_CLOCK = MaskClrSet(MDR_CLOCK->USB_CLOCK, MDR_RST_USB__C1_SEL_Msk, VAL2FLD_Pos(selPer1C1,  MDR_RST_USB__C1_SEL_Pos));
}


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

void MDR_ADC_SetClock_HSI_C1(MDR_CLK_DIV_256 divClk)
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

void MDR_ADC_SetClock_USB_C2(MDR_CLK_DIV_256 divClk)
{
  ADC_Set_C1_loc(MDR_ADC_C1_USB_C2, divClk);
}

void MDR_ADC_SetClock_CPU_C1(MDR_CLK_DIV_256 divClk)
{
  ADC_Set_C1_loc(MDR_ADC_C1_CPU_C1, divClk);
}

void MDR_ADC_SetClock_USB_C1(MDR_CLK_DIV_256 divClk)
{
  ADC_Set_C1_loc(MDR_ADC_C1_USB_C1, divClk);
}



#include <MDR_RST_Clock.h>
 

//  Сброс блока тактирования RST_CLOCK в начальное состояние
bool RST_ResetBlock(uint32_t timeoutCycles, MDR_BKP_HSI_TRIM freqTrim)
{
  if (!(CPU_SetClock_HSI(timeoutCycles, freqTrim)))
    return false;

  // PER_CLOCK
  REG_PER_CLOCK_ENA_b.RST_CLK_EN  = MDR_On;

//  MDR_CLOCK->CLOCK_STATUS  
  MDR_CLOCK->CPU_CLOCK   = 0;                 /*!< (@ 0x0000000C) CPU Clock Control                                          */
  MDR_CLOCK->PLL_CONTROL = 0;                 /*!< (@ 0x00000004) PLL Control Register                                       */
  MDR_CLOCK->HS_CONTROL  = 0;                 /*!< (@ 0x00000008) HSE Generator Control                                      */
  MDR_CLOCK->ADC_CLOCK   = 0;                 /*!< (@ 0x00000014) ADC Clock Control                                          */
  MDR_CLOCK->RTC_CLOCK   = 0;                 /*!< (@ 0x00000018) RTC Clock Control                                          */
  MDR_CLOCK->TIM_CLOCK   = 0;                 /*!< (@ 0x00000024) Timer's Clock Control                                      */
  MDR_CLOCK->UART_CLOCK  = 0;                 /*!< (@ 0x00000028) UART's Clock Control                                       */
  MDR_CLOCK->SSP_CLOCK   = 0;                 /*!< (@ 0x0000002C) SSP's Clock Control                                        */
  
  // Custom Periph blocks
#ifdef MDR_USB
  MDR_CLOCK->USB_CLOCK = 0;                   /*!< (@ 0x00000010) USB Clock Control                                          */
#endif  

#ifdef MDR_CAN
  MDR_CLOCK->CAN_CLOCK = 0;                   /*!< (@ 0x00000020) CAN's Clock Control                                        */
#endif

#ifdef MDR_ETH
  MDR_CLOCK->ETH_CLOCK = 0;                   /*!< (@ 0x00000034) Ethernet and MIL Clock Control                             */
#endif
 
#if defined (USE_MDR1986BE4) || defined (USE_MDR1986BK214) || defined (USE_MDR1986BK234)
  MDR_CLOCK->PER1_CLOCK  = 0;                 /*!< (@ 0x00000010) Peripherials Clock Control1                                */
#endif  
  
  return true;
}

//=============   Включение генераторов ============== 

//-------------------  HSE Control ---------------------
bool RST_HSE_GetReady(void)
{
  return MDR_CLOCK->CLOCK_STATUS_b.HSE_RDY == MDR_On;
}

bool RST_HSE_Enable(uint32_t timeoutCycles, MDR_OnOff byPass)
{
//  uint32_t reg = FLD_CLEAR(MDR_CLOCK->HS_CONTROL, MDR_RST_HS__HSE_BYP_Msk);
//  MDR_CLOCK->HS_CONTROL = reg | VAL2FLD(byPass, MDR_RST_HS__HSE_ON) |  VAL2FLD(MDR_On, MDR_RST_HS__HSE_BYP);
  
  MDR_CLOCK->HS_CONTROL_b.HSE_BYP = byPass;
  MDR_CLOCK->HS_CONTROL_b.HSE_ON = MDR_On;  
  
  if (timeoutCycles > 0)
    return WaitCondition(timeoutCycles, RST_HSE_GetReady);
  else  
    return RST_HSE_GetReady();
}

//-------------------  HSE2 Control ---------------------
#ifdef MDR_EXIST_HSE2

bool RST_HSE2_GetReady(void)
{
  return MDR_CLOCK->CLOCK_STATUS_b.HSE2_RDY == MDR_On;
}

bool RST_HSE2_Enable(uint32_t timeoutCycles, MDR_OnOff byPass)
{
//  uint32_t reg = FLD_CLEAR(MDR_CLOCK->HS_CONTROL, MDR_RST_HS__HSE2_BYP_Msk);
//  MDR_CLOCK->HS_CONTROL = reg | VAL2FLD(byPass, MDR_RST_HS__HSE2_ON) |  VAL2FLD(MDR_On, MDR_RST_HS__HSE2_BYP);
  
  MDR_CLOCK->HS_CONTROL_b.HSE2_BYP = byPass;
  MDR_CLOCK->HS_CONTROL_b.HSE2_ON = MDR_On;
  
  if (timeoutCycles > 0)
    return WaitCondition(timeoutCycles, RST_HSE2_GetReady);
  else  
    return RST_HSE2_GetReady();
}

#endif

//-------------------  LSI Control ---------------------
bool RST_LSI_GetReady(void)
{
  return MDR_BKP->REG_0F_b.LSI_RDY == MDR_On;
}

bool RST_LSI_Enable(uint32_t timeoutCycles, MDR_BKP_LSI_TRIM freqTrim)
{  
  MDR_BKP->REG_0F_b.LSI_TRIM = freqTrim;
  MDR_BKP->REG_0F_b.LSI_ON = MDR_On;
 
  if (timeoutCycles > 0)
    return WaitCondition(timeoutCycles, RST_LSI_GetReady);
  else  
    return RST_LSI_GetReady();
}

//-------------------  HSI Control ---------------------
bool RST_HSI_GetReady(void)
{
  return MDR_BKP->REG_0F_b.HSI_RDY == MDR_On;
}

bool RST_HSI_Enable(uint32_t timeoutCycles, MDR_BKP_HSI_TRIM freqTrim)
{
  MDR_BKP->REG_0F_b.HSI_TRIM = freqTrim;
  MDR_BKP->REG_0F_b.HSI_ON = MDR_On;
  
  if (timeoutCycles > 0)
    return WaitCondition(timeoutCycles, RST_HSI_GetReady);
  else  
    return RST_HSI_GetReady();
}

//-------------------  LSE Control ---------------------
bool RST_LSE_GetReady(void)
{
  return MDR_BKP->REG_0F_b.LSE_RDY == MDR_On;
}

bool RST_LSE_Enable(uint32_t timeoutCycles, MDR_OnOff byPass)
{
  MDR_BKP->REG_0F_b.LSE_BYP = byPass;  
  MDR_BKP->REG_0F_b.LSE_ON = MDR_On;
  
  if (timeoutCycles > 0)
    return WaitCondition(timeoutCycles, RST_LSE_GetReady);
  else  
    return RST_LSE_GetReady();  
}

//-------------------  PLL Control ---------------------
bool RST_PLL_GetReady(void)
{
  return MDR_CLOCK->CLOCK_STATUS_b.PLL_CPU_RDY == MDR_On;
}

bool RST_PLL_Enable(MDR_MUL_x16 pllMul, uint32_t timeoutCycles)
{
  MDR_CLOCK->PLL_CONTROL_b.PLL_CPU_MUL = pllMul;
  if (MDR_CLOCK->PLL_CONTROL_b.PLL_CPU_ON == MDR_Off)
    MDR_CLOCK->PLL_CONTROL_b.PLL_CPU_ON = MDR_On;
  else
  {
    MDR_CLOCK->PLL_CONTROL_b.PLL_CPU_PLD = MDR_On;
    MDR_CLOCK->PLL_CONTROL_b.PLL_CPU_PLD = MDR_Off;
  }
  
  if (timeoutCycles > 0)
    return WaitCondition(timeoutCycles, RST_PLL_GetReady);
  else
    return RST_PLL_GetReady();
}


//=============   Выбор тактирования для CPU ==============

//-------------------  Тактирование от HSI  ---------------------
bool CPU_SetClock_HSI(uint32_t timeoutCycles, MDR_BKP_HSI_TRIM freqTrim)
{ 
  bool result = false;  
  
  RST_HSI_Open();
  if (RST_HSI_Enable(timeoutCycles, freqTrim))
  {
    MDR_CLOCK->CPU_CLOCK_b.HCLK_SEL = MDR_HCLK_HSI;
    result =  true;
  }
  RST_HSI_Close();
  
  return result;
}

//-------------------  Тактирование от LSI  ---------------------
bool CPU_SetClock_LSI(uint32_t timeoutCycles, MDR_BKP_LSI_TRIM freqTrim)
{
  bool result = false;
  
  RST_LSI_Open();
  if (RST_LSI_Enable(timeoutCycles, freqTrim))
  {
    MDR_CLOCK->CPU_CLOCK_b.HCLK_SEL = MDR_HCLK_LSI;
    result = true;
  }
  RST_LSI_Close();

  return result;
}

//-------------------  Тактирование от LSE  ---------------------
bool CPU_SetClock_LSE(MDR_OnOff byPass, uint32_t timeoutCycles)
{
  if (RST_LSE_Enable(timeoutCycles, byPass))
  {
    MDR_CLOCK->CPU_CLOCK_b.HCLK_SEL = MDR_HCLK_LSE;
    return true;
  }
  else
    return false;
}

//-------------------  Тактирование от HSE  ---------------------
bool CPU_SetClock_HSE(uint32_t timeoutCycles)
{
  //  Включение генератора HSE
  MDR_CLOCK->HS_CONTROL_b.HSE_ON = MDR_On;
  //  Переключение мультиплексоров, пока раскачивается генератор HSE
  MDR_CLOCK->CPU_CLOCK =  (MDR_HSIE2_HSE << MDR_RST_CPU__C1_SEL_Pos)
                        | (MDR_CPU_C1    << MDR_RST_CPU__C2_SEL_Pos)
                        | (MDR_CLK_div1  << MDR_RST_CPU__C3_SEL_Pos)
                        | (MDR_HCLK_HSI  << MDR_RST_CPU__HCLK_SEL_Pos);
  
  // Ожидание готовности частоты HSE
  if (WaitCondition(timeoutCycles, RST_HSE_GetReady))
  {
    //  Переход на частоту HSE
    MDR_CLOCK->CPU_CLOCK_b.HCLK_SEL = MDR_HCLK_CPU_C3;
    return true;
  }
  else
    return true;
}

//-------------------  Тактирование от HSE с умножением в PLL ------------------

bool CPU_SetClock_HSE_PLL(MDR_MUL_x16 pllMul, MDR_OnOff byPass, uint32_t timeoutCycles)
{
  if (!(RST_HSE_Enable(timeoutCycles, byPass)))
    return false;

  MDR_CLOCK->CPU_CLOCK =   (MDR_HSIE2_HSE << MDR_RST_CPU__C1_SEL_Pos)
                         | (MDR_CPU_PLL   << MDR_RST_CPU__C2_SEL_Pos)
                         | (MDR_CLK_div1  << MDR_RST_CPU__C3_SEL_Pos)
                         | (MDR_HCLK_HSI  << MDR_RST_CPU__HCLK_SEL_Pos);
  
  if (!(RST_PLL_Enable(pllMul, timeoutCycles)))
    return false;

  MDR_CLOCK->CPU_CLOCK_b.HCLK_SEL = MDR_HCLK_CPU_C3;
  return true;  
}

bool CPU_SetClock_HSE_div2_PLL(MDR_MUL_x16 pllMul, MDR_OnOff byPass, uint32_t timeoutCycles)
{
  if (!(RST_HSE_Enable(timeoutCycles, byPass)))
    return false;

  MDR_CLOCK->CPU_CLOCK =   (MDR_HSIE2_HSE_div2 << MDR_RST_CPU__C1_SEL_Pos)
                         | (MDR_CPU_PLL   << MDR_RST_CPU__C2_SEL_Pos)
                         | (MDR_CLK_div1  << MDR_RST_CPU__C3_SEL_Pos)
                         | (MDR_HCLK_HSI  << MDR_RST_CPU__HCLK_SEL_Pos);
  
  if (!(RST_PLL_Enable(pllMul, timeoutCycles)))
    return false;

  MDR_CLOCK->CPU_CLOCK_b.HCLK_SEL = MDR_HCLK_CPU_C3;
  return true;  
}

//-------------------  Тактирование от HSI с умножением в PLL ------------------

bool CPU_SetClock_HSI_PLL(MDR_MUL_x16 pllMul, uint32_t timeoutCycles, MDR_BKP_HSI_TRIM freqTrim)
{
  bool result = false;
  
  RST_HSI_Open();
  if (RST_HSI_Enable(timeoutCycles, freqTrim))
  {  
    MDR_CLOCK->CPU_CLOCK =  (MDR_HSIE2_HSI << MDR_RST_CPU__C1_SEL_Pos)
                          | (MDR_CPU_PLL   << MDR_RST_CPU__C2_SEL_Pos)
                          | (MDR_CLK_div1  << MDR_RST_CPU__C3_SEL_Pos)
                          | (MDR_HCLK_HSI  << MDR_RST_CPU__HCLK_SEL_Pos);
  
    if (RST_PLL_Enable(pllMul, timeoutCycles))
    {
      MDR_CLOCK->CPU_CLOCK_b.HCLK_SEL = MDR_HCLK_CPU_C3;
      result = true;
    }  
  }
  RST_HSI_Close();
  
  return result;
}

bool CPU_SetClock_HSI_div2_PLL(MDR_MUL_x16 pllMul, uint32_t timeoutCycles, MDR_BKP_HSI_TRIM freqTrim)
{
  bool result = false;
  
  RST_HSI_Open();
  if (RST_HSI_Enable(timeoutCycles, freqTrim))
  {  
    MDR_CLOCK->CPU_CLOCK =  (MDR_HSIE2_HSI_div2 << MDR_RST_CPU__C1_SEL_Pos)
                          | (MDR_CPU_PLL   << MDR_RST_CPU__C2_SEL_Pos)
                          | (MDR_CLK_div1  << MDR_RST_CPU__C3_SEL_Pos)
                          | (MDR_HCLK_HSI  << MDR_RST_CPU__HCLK_SEL_Pos);
  
    if (RST_PLL_Enable(pllMul, timeoutCycles))
    {
      MDR_CLOCK->CPU_CLOCK_b.HCLK_SEL = MDR_HCLK_CPU_C3;
      result = true;
    }  
  }
  RST_HSI_Close();
  
  return result; 
}


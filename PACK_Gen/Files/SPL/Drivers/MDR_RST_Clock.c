#include <MDR_RST_Clock.h>
 
//  ====================    Заметки  =====================
//  При переключении частот, всегда происходит переключение на HSI через мультиплексор MUX_C3.
//  На этой частоте ядро работает пока переключается и настраивается весь остальной тракт.
//  Итого:
//    1. Уход на частоту HSI, первая команда          - MDR_CLOCK->CPU_CLOCK_b.HCLK_SEL = MDR_HCLK_HSI;
//    2. Переход на другую частоту, последняя команда - MDR_CLOCK->CPU_CLOCK_b.HCLK_SEL = MDR_HCLK_CPU_C3 или иное.
//  За раз весь регистр CPU_CLOCK не переключать, иначе зависает. Необходимо переключение текущей частоты, только одним мультиплексором!


//  Сброс блока тактирования RST_CLOCK в начальное состояние
bool MDR_RST_ResetBlock(uint32_t timeoutCycles, MDR_BKP_HSI_TRIM freqTrim)
{
  if (!(MDR_CPU_SetClock_HSI(timeoutCycles, freqTrim)))
    return false;

  // PER_CLOCK
  MDR_CLOCK->MDR_CLK_EN_REG_BKP_b.RST_CLK_EN  = MDR_On;

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

uint32_t MDR_CPU_GetFreqHz(bool doUpdate)
{
  if (doUpdate)
  {  
    SystemCoreClockUpdate();
  }  
  return SystemCoreClock;
}

//=============   Включение генераторов ============== 

//-------------------  HSE Control ---------------------
bool MDR_RST_HSE_GetReady(void)
{
  return MDR_CLOCK->CLOCK_STATUS_b.HSE_RDY == MDR_On;
}

bool MDR_RST_HSE_Enable(uint32_t timeoutCycles, MDR_OnOff byPass)
{
//  uint32_t reg = FLD_CLEAR(MDR_CLOCK->HS_CONTROL, MDR_RST_HS__HSE_BYP_Msk);
//  MDR_CLOCK->HS_CONTROL = reg | VAL2FLD(byPass, MDR_RST_HS__HSE_ON) |  VAL2FLD(MDR_On, MDR_RST_HS__HSE_BYP);
  
  MDR_CLOCK->HS_CONTROL_b.HSE_BYP = byPass;
  MDR_CLOCK->HS_CONTROL_b.HSE_ON = MDR_On;  
  
  if (timeoutCycles > 0)
    return WaitCondition(timeoutCycles, MDR_RST_HSE_GetReady);
  else  
    return MDR_RST_HSE_GetReady();
}

//-------------------  HSE2 Control ---------------------
#ifdef MDR_EXIST_HSE2

bool MDR_RST_HSE2_GetReady(void)
{
  return MDR_CLOCK->CLOCK_STATUS_b.HSE2_RDY == MDR_On;
}

bool MDR_RST_HSE2_Enable(uint32_t timeoutCycles, MDR_OnOff byPass)
{
//  uint32_t reg = FLD_CLEAR(MDR_CLOCK->HS_CONTROL, MDR_RST_HS__HSE2_BYP_Msk);
//  MDR_CLOCK->HS_CONTROL = reg | VAL2FLD(byPass, MDR_RST_HS__HSE2_ON) |  VAL2FLD(MDR_On, MDR_RST_HS__HSE2_BYP);
  
  MDR_CLOCK->HS_CONTROL_b.HSE2_BYP = byPass;
  MDR_CLOCK->HS_CONTROL_b.HSE2_ON = MDR_On;
  
  if (timeoutCycles > 0)
    return WaitCondition(timeoutCycles, MDR_RST_HSE2_GetReady);
  else  
    return MDR_RST_HSE2_GetReady();
}

#endif

//-------------------  LSI Control ---------------------
bool MDR_RST_LSI_GetReady(void)
{
  return MDR_BKP->REG_0F_b.LSI_RDY == MDR_On;
}

bool MDR_RST_LSI_Enable(uint32_t timeoutCycles, MDR_BKP_LSI_TRIM freqTrim)
{  
  MDR_BKP->REG_0F_b.LSI_TRIM = freqTrim;
  MDR_BKP->REG_0F_b.LSI_ON = MDR_On;
 
  if (timeoutCycles > 0)
    return WaitCondition(timeoutCycles, MDR_RST_LSI_GetReady);
  else  
    return MDR_RST_LSI_GetReady();
}

//-------------------  HSI Control ---------------------
bool MDR_RST_HSI_GetReady(void)
{
  return MDR_BKP->REG_0F_b.HSI_RDY == MDR_On;
}

bool MDR_RST_HSI_Enable(uint32_t timeoutCycles, MDR_BKP_HSI_TRIM freqTrim)
{
  MDR_BKP->REG_0F_b.HSI_TRIM = freqTrim;
  MDR_BKP->REG_0F_b.HSI_ON = MDR_On;
  
  if (timeoutCycles > 0)
    return WaitCondition(timeoutCycles, MDR_RST_HSI_GetReady);
  else  
    return MDR_RST_HSI_GetReady();
}

//-------------------  LSE Control ---------------------
bool MDR_RST_LSE_GetReady(void)
{
  return MDR_BKP->REG_0F_b.LSE_RDY == MDR_On;
}

bool MDR_RST_LSE_Enable(uint32_t timeoutCycles, MDR_OnOff byPass)
{
  MDR_BKP->REG_0F_b.LSE_BYP = byPass;  
  MDR_BKP->REG_0F_b.LSE_ON = MDR_On;
  
  if (timeoutCycles > 0)
    return WaitCondition(timeoutCycles, MDR_RST_LSE_GetReady);
  else  
    return MDR_RST_LSE_GetReady();  
}

//-------------------  PLL Control ---------------------
bool MDR_RST_PLL_GetReady(void)
{
  return MDR_CLOCK->CLOCK_STATUS_b.PLL_CPU_RDY == MDR_On;
}

bool MDR_RST_PLL_Enable(MDR_MUL_x16 pllMul, uint32_t timeoutCycles)
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
    return WaitCondition(timeoutCycles, MDR_RST_PLL_GetReady);
  else
    return MDR_RST_PLL_GetReady();
}

//==========   Функции для активирования батарейного домена, доступ к флагам ==============
static uint32_t _regClockCapturedBKP;

__STATIC_INLINE void RST_BKP_ClockOn_loc(void)
{
  _regClockCapturedBKP = MDR_CLOCK->MDR_CLK_EN_REG_BKP;
  MDR_CLOCK->MDR_CLK_EN_REG_BKP = _regClockCapturedBKP | (1UL << MDR_RST_PER__BKP_CLK_EN_Pos);    
}

__STATIC_INLINE void RST_BKP_ClockRestore_loc(void)
{
  MDR_CLOCK->MDR_CLK_EN_REG_BKP = _regClockCapturedBKP;
}

//==========   Вспомогательные функции стабилизации потребления и доступа к EEPROM ==============
MDR_RST_EEPROM_Delay MDR_FreqCPU_ToDelayEEPROM(uint32_t CPU_FregHz)
{
  if      (CPU_FregHz < 25E+6)  return EEPROM_Delay_le25MHz;
	else if (CPU_FregHz < 50E+6)  return EEPROM_Delay_le50MHz;
	else if (CPU_FregHz < 75E+6)  return EEPROM_Delay_le75MHz;
	else if (CPU_FregHz < 100E+6) return EEPROM_Delay_le100MHz;
	else if (CPU_FregHz < 125E+6) return EEPROM_Delay_le125MHz;
  else if (CPU_FregHz < 150E+6) return EEPROM_Delay_le150MHz;
  else if (CPU_FregHz < 175E+6) return EEPROM_Delay_le175MHz;
  else return EEPROM_Delay_le200MHz;
}

MDR_RST_BKP_LowRI MDR_FreqCPU_ToLowRI(uint32_t CPU_FregHz)
{
	if      (CPU_FregHz >  80E+6) return MDR_LOWRI_gt80MHz;
	else if (CPU_FregHz >  40E+6) return MDR_LOWRI_le80MHz;
	else if (CPU_FregHz >  10E+6) return MDR_LOWRI_le40MHz;  
  else if (CPU_FregHz >   1E+3) return MDR_LOWRI_le10MHz;
  else if (CPU_FregHz > 500E+3) return MDR_LOWRI_le1MHz;
  else if (CPU_FregHz > 200E+3)	return MDR_LOWRI_le500KHz;
  else if (CPU_FregHz > 0)	    return MDR_LOWRI_le200KHz;
  else 
    return MDR_LOWRI_GensOff;
}


__STATIC_INLINE void RST_SetLowRI_loc(MDR_RST_BKP_LowRI lowRI)
{ 
  //  Выставление SelectRI и LOW
  uint32_t regVal = MDR_BKP->REG_0E;
  regVal &= ~(MDR_BKP_REG_0E_LOW_Msk | MDR_BKP_REG_0E_SelectRI_Msk);
  MDR_BKP->REG_0E = regVal | ((uint32_t)lowRI << MDR_BKP_REG_0E_LOW_Pos) | ((uint32_t)lowRI << MDR_BKP_REG_0E_SelectRI_Pos);   
}

void MDR_RST_SetLowRI(MDR_RST_BKP_LowRI lowRI)
{
  RST_BKP_ClockOn_loc();
  RST_SetLowRI_loc(lowRI);
  RST_BKP_ClockRestore_loc();
}

void MDR_RST_SetDelayEEPROM(MDR_RST_EEPROM_Delay delayEEPROM)
{

}

//=============   Выбор тактирования для CPU ==============

//-------------------  Тактирование от HSI  ---------------------
__STATIC_INLINE bool CPU_SetClock_HSI_loc(uint32_t timeoutCycles, MDR_BKP_HSI_TRIM freqTrim)
{ 
  //  Включение HSI с таймаутом
  if (MDR_RST_HSI_Enable(timeoutCycles, freqTrim))
  {
    // Переключение ядра на HSI
    MDR_CLOCK->CPU_CLOCK_b.HCLK_SEL = MDR_HCLK_HSI;
    return true;
  }
  else
   return false;
}

bool MDR_CPU_SetClock_HSI(uint32_t timeoutCycles, MDR_BKP_HSI_TRIM freqTrim)
{
  bool result = false;
  
  //  Доступ к флагам BKP
  RST_BKP_ClockOn_loc();
  
  //  Переход на HSI
  if (CPU_SetClock_HSI_loc(timeoutCycles, freqTrim))
  {  
    // Стабилизация потребления под частоту CPU
    RST_SetLowRI_loc(MDR_LOWRI_le10MHz);
    // Время доступа к EEPROM
    MDR_RST_SetDelayEEPROM(EEPROM_Delay_le25MHz);
    
    result = true;
  }
  
  //  Восстановление тактирования BKP
  RST_BKP_ClockRestore_loc();
  return result;
}

#define TO_CPU_CLOCK(sel1, sel2, sel3, hsel)  (uint32_t)(((sel1)   << MDR_RST_CPU__C1_SEL_Pos)   \
                                                       | ((sel2)   << MDR_RST_CPU__C2_SEL_Pos)   \
                                                       | ((sel3)   << MDR_RST_CPU__C3_SEL_Pos)   \
                                                       | ((hsel)   << MDR_RST_CPU__HCLK_SEL_Pos));

bool MDR_CPU_SetClock_HSI_div2(MDR_CLK_DIV_256 divC3, uint32_t timeoutCycles, MDR_BKP_HSI_TRIM freqTrim)
{ 
  bool result = false;
  
  //  Доступ к флагам BKP
  RST_BKP_ClockOn_loc();  
  
  //  Переход на HSI
  if (CPU_SetClock_HSI_loc(timeoutCycles, freqTrim))
  {
    // Стабилизация потребления под частоту CPU
    RST_SetLowRI_loc(MDR_LOWRI_le10MHz);
    // Время доступа к EEPROM
    MDR_RST_SetDelayEEPROM(EEPROM_Delay_le25MHz);    
    
    //  Предварительное переключение мультиплексоров
    MDR_CLOCK->CPU_CLOCK = TO_CPU_CLOCK(MDR_HSIE2_HSI_div2, MDR_CPU_C1, divC3, MDR_HCLK_HSI);
    //  Переключение ядра на сформированную частоту
    MDR_CLOCK->CPU_CLOCK = TO_CPU_CLOCK(MDR_HSIE2_HSI_div2, MDR_CPU_C1, divC3, MDR_HCLK_CPU_C3);
    
    result = true;
  }
  
  //  Восстановление тактирования BKP
  RST_BKP_ClockRestore_loc();
  return result;
}

bool MDR_CPU_SetClock_HSI_C1(MDR_CLK_DIV_256 divC3, uint32_t timeoutCycles, MDR_BKP_HSI_TRIM freqTrim)
{ 
  bool result = false;
  
  //  Доступ к флагам BKP
  RST_BKP_ClockOn_loc(); 
  
  //  Переход на HSI
  if (CPU_SetClock_HSI_loc(timeoutCycles, freqTrim))
  {
    // Стабилизация потребления под частоту CPU
    RST_SetLowRI_loc(MDR_LOWRI_le10MHz);
    // Время доступа к EEPROM
    MDR_RST_SetDelayEEPROM(EEPROM_Delay_le25MHz);     
    
    //  Предварительное переключение мультиплексоров
    MDR_CLOCK->CPU_CLOCK = TO_CPU_CLOCK(MDR_HSIE2_HSI, MDR_CPU_C1, divC3, MDR_HCLK_HSI);
    //  Переключение ядра на сформированную частоту
    MDR_CLOCK->CPU_CLOCK = TO_CPU_CLOCK(MDR_HSIE2_HSI, MDR_CPU_C1, divC3, MDR_HCLK_CPU_C3);
    
    result = true;
  }
  
  //  Восстановление тактирования BKP
  RST_BKP_ClockRestore_loc();
  return result;
}

//-------------------  Тактирование от HSI с умножением в PLL ------------------

bool MDR_CPU_SetClock_HSI_PLL(MDR_MUL_x16 pllMul, MDR_RST_BKP_LowRI lowRI, MDR_RST_EEPROM_Delay delayEEPROM, 
                              MDR_CLK_DIV_256 divC3, uint32_t timeoutCycles, MDR_BKP_HSI_TRIM freqTrim)
{
  bool result = false;
  
  //  Доступ к флагам BKP
  RST_BKP_ClockOn_loc();
  
  //  Переход на HSI
  if (CPU_SetClock_HSI_loc(timeoutCycles, freqTrim))
  {
    // Стабилизация потребления под частоту CPU
    RST_SetLowRI_loc(lowRI);
    // Время доступа к EEPROM
    MDR_RST_SetDelayEEPROM(delayEEPROM);    
    
    //  Предварительное переключение мультиплексоров
    MDR_CLOCK->CPU_CLOCK =   TO_CPU_CLOCK(MDR_HSIE2_HSI, MDR_CPU_PLL, divC3, MDR_HCLK_HSI);
    //  Включение PLL
    if (MDR_RST_PLL_Enable(pllMul, timeoutCycles))
    {
      //  Переключение ядра на сформированную частоту
      MDR_CLOCK->CPU_CLOCK = TO_CPU_CLOCK(MDR_HSIE2_HSI, MDR_CPU_PLL, divC3, MDR_HCLK_CPU_C3);
      result = true;
    }
  }
  
  //  Восстановление тактирования BKP
  RST_BKP_ClockRestore_loc();
  return result;
}

bool MDR_CPU_SetClock_HSI_div2_PLL(MDR_MUL_x16 pllMul, MDR_RST_BKP_LowRI lowRI, MDR_RST_EEPROM_Delay delayEEPROM, 
                              MDR_CLK_DIV_256 divC3, uint32_t timeoutCycles, MDR_BKP_HSI_TRIM freqTrim)
{
  bool result = false;
  
  //  Доступ к флагам BKP
  RST_BKP_ClockOn_loc();
  
  //  Переход на HSI
  if (CPU_SetClock_HSI_loc(timeoutCycles, freqTrim))
  {
    // Стабилизация потребления под частоту CPU
    RST_SetLowRI_loc(lowRI);
    // Время доступа к EEPROM
    MDR_RST_SetDelayEEPROM(delayEEPROM);    
    
    //  Предварительное переключение мультиплексоров
    MDR_CLOCK->CPU_CLOCK =   TO_CPU_CLOCK(MDR_HSIE2_HSI_div2, MDR_CPU_PLL, divC3, MDR_HCLK_HSI);
    //  Включение PLL
    if (MDR_RST_PLL_Enable(pllMul, timeoutCycles))
    {
      //  Переключение ядра на сформированную частоту
      MDR_CLOCK->CPU_CLOCK = TO_CPU_CLOCK(MDR_HSIE2_HSI_div2, MDR_CPU_PLL, divC3, MDR_HCLK_CPU_C3);
      result = true;
    }
  }
  
  //  Восстановление тактирования BKP
  RST_BKP_ClockRestore_loc();
  return result;
}

//-------------------  Тактирование от LSI  ---------------------
bool MDR_CPU_SetClock_LSI(uint32_t timeoutCycles, MDR_BKP_LSI_TRIM freqTrim)
{
  bool result = false;
  
  //  Доступ к флагам BKP
  RST_BKP_ClockOn_loc();
  
  //  Включение LSI с таймаутом
  if (MDR_RST_LSI_Enable(timeoutCycles, freqTrim))
  {
    // Переключение ядра на HSI
    MDR_CLOCK->CPU_CLOCK_b.HCLK_SEL = MDR_HCLK_LSI;
    result =  true;    
  }  
  // Стабилизация потребления под частоту CPU
  RST_SetLowRI_loc(MDR_LOWRI_le200KHz);
  // Время доступа к EEPROM
  MDR_RST_SetDelayEEPROM(EEPROM_Delay_le25MHz);  
  
  //  Восстановление тактирования BKP
  RST_BKP_ClockRestore_loc();
  return result;
}

//-------------------  Тактирование от LSE  ---------------------
bool MDR_CPU_SetClock_LSE(MDR_OnOff byPass, uint32_t timeoutCycles)
{
  bool result = false;
  
  //  Доступ к флагам BKP
  RST_BKP_ClockOn_loc();
  
  //  Включение LSE с таймаутом
  if (MDR_RST_LSE_Enable(timeoutCycles, byPass))
  {
    MDR_CLOCK->CPU_CLOCK_b.HCLK_SEL = MDR_HCLK_LSE;
    result = true;
  }
  // Стабилизация потребления под частоту CPU
  RST_SetLowRI_loc(MDR_LOWRI_le200KHz);
  // Время доступа к EEPROM
  MDR_RST_SetDelayEEPROM(EEPROM_Delay_le25MHz); 
  
  //  Восстановление тактирования BKP
  RST_BKP_ClockRestore_loc();
  return result;
}


//-------------------  Тактирование от HSE  ---------------------
bool MDR_CPU_SetClock_HSE(MDR_OnOff byPass, MDR_RST_BKP_LowRI lowRI, MDR_CLK_DIV_256 divC3, uint32_t timeoutCycles)
{
  bool result = false;
  
  //  Доступ к флагам BKP
  RST_BKP_ClockOn_loc();
  
  //  Переход на HSI
  if (CPU_SetClock_HSI_loc(timeoutCycles, HSI_FREQ_TRIM))
    // Включение HSE
    if (MDR_RST_HSE_Enable(timeoutCycles, byPass))
    { 
      // Стабилизация потребления под частоту CPU
      RST_SetLowRI_loc(lowRI);
      // Время доступа к EEPROM
      MDR_RST_SetDelayEEPROM(EEPROM_Delay_le25MHz);
      
      //  Предварительное переключение мультиплексоров
      MDR_CLOCK->CPU_CLOCK =   TO_CPU_CLOCK(MDR_HSIE2_HSE, MDR_CPU_C1, divC3, MDR_HCLK_HSI);
      //  Переключение ядра на сформированную частоту
      MDR_CLOCK->CPU_CLOCK = TO_CPU_CLOCK(MDR_HSIE2_HSE, MDR_CPU_C1, divC3, MDR_HCLK_CPU_C3);
      result = true;
    }
  
  //  Восстановление тактирования BKP
  RST_BKP_ClockRestore_loc();
  return result;
}

bool MDR_CPU_SetClock_HSE_div2(MDR_OnOff byPass, MDR_CLK_DIV_256 divC3, uint32_t timeoutCycles)
{
  bool result = false;
  
  //  Доступ к флагам BKP
  RST_BKP_ClockOn_loc();  
  
  //  Переход на HSI
  if (CPU_SetClock_HSI_loc(timeoutCycles, HSI_FREQ_TRIM))
    // Включение HSE
    if (MDR_RST_HSE_Enable(timeoutCycles, byPass))
    {
      // Стабилизация потребления под частоту CPU
      RST_SetLowRI_loc(MDR_LOWRI_le10MHz);
      // Время доступа к EEPROM
      MDR_RST_SetDelayEEPROM(EEPROM_Delay_le25MHz);      
      
      //  Предварительное переключение мультиплексоров
      MDR_CLOCK->CPU_CLOCK = TO_CPU_CLOCK(MDR_HSIE2_HSE_div2, MDR_CPU_C1, divC3, MDR_HCLK_HSI);
      //  Переключение ядра на сформированную частоту
      MDR_CLOCK->CPU_CLOCK = TO_CPU_CLOCK(MDR_HSIE2_HSE_div2, MDR_CPU_C1, divC3, MDR_HCLK_CPU_C3);
      result = true;
    }
  
  //  Восстановление тактирования BKP
  RST_BKP_ClockRestore_loc();
  return result;
}

//-------------------  Тактирование от HSE с умножением в PLL ------------------

bool MDR_CPU_SetClock_HSE_PLL(MDR_OnOff byPass, MDR_MUL_x16 pllMul, MDR_RST_BKP_LowRI lowRI, MDR_RST_EEPROM_Delay delayEEPROM, MDR_CLK_DIV_256 divC3, uint32_t timeoutCycles)
{
  bool result = false;
  
  //  Доступ к флагам BKP
  RST_BKP_ClockOn_loc();   
  
  //  Переход на HSI
  if (CPU_SetClock_HSI_loc(timeoutCycles, HSI_FREQ_TRIM))
    // Включение HSE
    if (MDR_RST_HSE_Enable(timeoutCycles, byPass))
    {  
      // Стабилизация потребления под частоту CPU
      RST_SetLowRI_loc(lowRI);
      // Время доступа к EEPROM
      MDR_RST_SetDelayEEPROM(delayEEPROM);
      
      //  Предварительное переключение мультиплексоров
      MDR_CLOCK->CPU_CLOCK = TO_CPU_CLOCK(MDR_HSIE2_HSE, MDR_CPU_PLL, divC3, MDR_HCLK_HSI);      
      //  Включение PLL
      if (MDR_RST_PLL_Enable(pllMul, timeoutCycles))
      {
        //  Переключение ядра на сформированную частоту
        MDR_CLOCK->CPU_CLOCK = TO_CPU_CLOCK(MDR_HSIE2_HSE, MDR_CPU_PLL, divC3, MDR_HCLK_CPU_C3);
        result = true;
      }
    }
  
  //  Восстановление тактирования BKP
  RST_BKP_ClockRestore_loc();
  return result;
}

bool MDR_CPU_SetClock_HSE_div2_PLL(MDR_OnOff byPass, MDR_MUL_x16 pllMul, MDR_RST_BKP_LowRI lowRI, MDR_RST_EEPROM_Delay delayEEPROM, MDR_CLK_DIV_256 divC3, uint32_t timeoutCycles)
{
  bool result = false;
  
  //  Доступ к флагам BKP
  RST_BKP_ClockOn_loc();  
  
  //  Переход на HSI
  if (CPU_SetClock_HSI_loc(timeoutCycles, HSI_FREQ_TRIM))
    // Включение HSE
    if (MDR_RST_HSE_Enable(timeoutCycles, byPass))
    {      
      // Стабилизация потребления под частоту CPU
      MDR_RST_SetLowRI(lowRI);
      // Время доступа к EEPROM
      MDR_RST_SetDelayEEPROM(delayEEPROM);
      
      //  Предварительное переключение мультиплексоров
      MDR_CLOCK->CPU_CLOCK = TO_CPU_CLOCK(MDR_HSIE2_HSE_div2, MDR_CPU_PLL, divC3, MDR_HCLK_HSI);      
      //  Включение PLL
      if (MDR_RST_PLL_Enable(pllMul, timeoutCycles))
      {
        //  Переключение ядра на сформированную частоту
        MDR_CLOCK->CPU_CLOCK = TO_CPU_CLOCK(MDR_HSIE2_HSE_div2, MDR_CPU_PLL, divC3, MDR_HCLK_CPU_C3);
        result = true;
      }
    }
  
  //  Восстановление тактирования BKP
  RST_BKP_ClockRestore_loc();
  return result;  
}




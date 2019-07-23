#include <MDR_RST_Clock_VEx.h>
 

//=================   Сброс блока и чтение текущей частоты CPU ==============
//  Желательно вызывать после смены частоты, тогда впоследствии можно вызывать без флага обновления
uint32_t MDR_CPU_GetFreqHz(bool doUpdate)
{
  if (doUpdate)
    SystemCoreClockUpdate();

  return SystemCoreClock;
}  

//  Сброс блока тактирования RST_CLOCK в начальное состояние
bool MDR_CLK_ResetBlock(const MDR_CPU_CfgHSI_Dir *cfgHSI, uint32_t timeoutCycles, bool fromLowerFreq)
{
  if ((MDR_CPU_SetClock_HSI_Dir(cfgHSI, timeoutCycles, fromLowerFreq)) != MDR_SET_CLOCK_OK)
    return false;

  // PER_CLOCK
  MDR_CLOCK->MDR_CLK_EN_REG_RST |= MDR_CLK_EN_BIT_RST;

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
  MDR_CLOCK->PER1_CLOCK  = MDR_RST_PER1__DEBUG_EN_Msk;                 /*!< (@ 0x00000010) Peripherials Clock Control1                                */
#endif  
  
  return true;
}  
 

//=====================================================================
//======================   Включение генераторов ======================
//=====================================================================

// --- LSE ---
bool MDR_LSE_GetReady(void)
{
  return (MDR_BKP->REG_0F & MDR_BKP_REG_0F_LSE_RDY_Msk);
}

// ----- LSI -----
bool MDR_LSI_GetReady(void)
{
  return (MDR_BKP->REG_0F & MDR_BKP_REG_0F_LSI_RDY_Msk);
}  

// ----- HSI ----- 
bool MDR_HSI_GetReady(void)
{
  return (MDR_BKP->REG_0F & MDR_BKP_REG_0F_HSI_RDY_Msk);
}
  
// ----- HSE -----
bool MDR_HSE_GetReady(void)
{
  return (MDR_CLOCK->CLOCK_STATUS & MDR_RST_STATUS__HSE_RDY_Msk);
}


// ----- HSE2 -----  
#ifdef MDR_EXIST_HSE2
  bool MDR_HSE2_GetReady(void)
  {
    return (MDR_CLOCK->CLOCK_STATUS & MDR_RST_STATUS__HSE2_RDY_Msk);
  }
#endif


// ----- PLL -----
void MDR_PLL_Enable(MDR_MUL_x16 pllMul)
{
  uint32_t regValue = MDR_CLOCK->PLL_CONTROL;

  regValue &= ~MDR_RST_PLL__CPU_MUL_Msk;
  regValue |= VAL2FLD_Pos(pllMul, MDR_RST_PLL__CPU_MUL_Pos) | MDR_RST_PLL__CPU_ON_Msk;
  
  MDR_CLOCK->PLL_CONTROL = regValue | MDR_RST_PLL__CPU_RLD_Msk;  //  Reset PLL On
  MDR_CLOCK->PLL_CONTROL = regValue;                             //  Reset PLL Off
}
  
bool MDR_PLL_GetReady(void)
{
  return (MDR_CLOCK->CLOCK_STATUS & MDR_RST_STATUS__PLL_CPU_RDY_Msk);
}


//==============================================================================
//=======     Подстройка питания и временных параметров под частоту   ==========
//==============================================================================

// --- Подстройка LDO от частоты ---
MDR_CLK_LDO_LowSRI MDR_FreqCPU_ToLowSRI(uint32_t CPU_FregHz)
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

#define LOW_SRI_HSI  MDR_LOWRI_le10MHz

// --- Задержка доступа к EEPROM от частоты ---
#ifndef MDR_EEPROM_18MHz
  //  Для 1986ВЕ4, 1986ВК214, 1986ВК234
  MDR_CLK_Delay_EEPROM MDR_FreqCPU_ToDelayEEPROM(uint32_t CPU_FregHz)
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
#else
  //  Для 1986ВЕ1, 1986ВЕ3, 1986ВЕ9х, 1901ВЦ1 
  MDR_CLK_Delay_EEPROM MDR_FreqCPU_ToDelayEEPROM(uint32_t CPU_FregHz)
  {
    if (CPU_FregHz <= 18E+6) 
      return EEPROM_Delay_le18MHz;
    else 
      return EEPROM_Delay_le36MHz;
  }
#endif


void MDR_CLK_ApplyFreqSupport_LDO(MDR_CLK_LDO_LowSRI lowSRI)
{ 
  //  Выставление SelectRI и LOW
  uint32_t regVal = MDR_BKP->REG_0E;
  regVal &= ~(MDR_BKP_REG_0E_LOW_Msk | MDR_BKP_REG_0E_SelectRI_Msk);
  MDR_BKP->REG_0E = regVal | VAL2FLD_Pos(lowSRI, MDR_BKP_REG_0E_LOW_Pos) | VAL2FLD_Pos(lowSRI, MDR_BKP_REG_0E_SelectRI_Pos);
}


void MDR_CLK_ApplyFreqSupport_EEPROM(MDR_CLK_Delay_EEPROM delayEEPROM)
{
  // Включение тактирования EEPROM
  uint32_t regPerClock = MDR_CLOCK->MDR_CLK_EN_REG_EEPROM;
  MDR_CLOCK->MDR_CLK_EN_REG_EEPROM = regPerClock | MDR_CLK_EN_BIT_EEPROM; 

  //  Выставление задержки
  MDR_EEPROM->CMD = MDR_MaskClrSet(MDR_EEPROM->CMD, MDR_EEPROM_CMD_DELAY_Msk, VAL2FLD_Pos(delayEEPROM, MDR_EEPROM_CMD_DELAY_Pos));
  
  //  Восстановление тактирования
  MDR_CLOCK->MDR_CLK_EN_REG_EEPROM = regPerClock;
}


//==============================================================================
//========================     Тактирование ядра   ===================
//==============================================================================

//-------------------  Тактирование от LSI  ---------------------
MDR_CPU_SetClockResult MDR_CPU_SetClock_LSI(const MDR_CPU_CfgLSI *cfgLSI, uint32_t timeoutCycles)
{
  if (!MDR_LSI_EnableAndWaitReady(cfgLSI->freqTrim, timeoutCycles))
    return MDR_SET_CLOCK_ERR__GEN_NotReady;

  MDR_CLOCK->CPU_CLOCK = MDR_MaskClrSet(MDR_CLOCK->CPU_CLOCK, MDR_RST_CPU__HCLK_SEL_Msk, VAL2FLD_Pos(MDR_HCLK_LSI, MDR_RST_CPU__HCLK_SEL_Pos));

  MDR_CPU_ApplyFreqSupport(&cfgLSI->freqSupp);
  return MDR_SET_CLOCK_OK;  
}

//-------------------  Тактирование от LSE  ---------------------
MDR_CPU_SetClockResult  MDR_CPU_SetClock_LSE(const MDR_CPU_CfgLSE *cfgLSE, uint32_t timeoutCycles)
{
  if (!MDR_LSE_EnableAndWaitReady(cfgLSE->freqSource, timeoutCycles))
    return MDR_SET_CLOCK_ERR__GEN_NotReady;
  
  MDR_CLOCK->CPU_CLOCK = MDR_MaskClrSet(MDR_CLOCK->CPU_CLOCK, MDR_RST_CPU__HCLK_SEL_Msk, VAL2FLD_Pos(MDR_HCLK_LSE, MDR_RST_CPU__HCLK_SEL_Pos));
  
  MDR_CPU_ApplyFreqSupport(&cfgLSE->freqSupp);
  return MDR_SET_CLOCK_OK;
}


//-------------------  Тактирование от HSI, ~8МГц (6МГц .. 10МГц)  ---------------------
MDR_CPU_SetClockResult MDR_CPU_SetClock_HSI_Dir(const MDR_CPU_CfgHSI_Dir *cfgHSI_d, uint32_t timeoutCycles, bool fromLowerFreq)
{
  if (!MDR_HSI_EnableAndWaitReady(cfgHSI_d->freqTrim, timeoutCycles))
    return MDR_SET_CLOCK_ERR__GEN_NotReady;
  
  if (fromLowerFreq)
    MDR_CPU_ApplyFreqSupport(&cfgHSI_d->freqSupp);
  
  MDR_CLOCK->CPU_CLOCK &= ~MDR_RST_CPU__HCLK_SEL_Msk;   // because MDR_HCLK_HSI = 0,
  
  if (!fromLowerFreq)
    MDR_CPU_ApplyFreqSupport(&cfgHSI_d->freqSupp);
  return MDR_SET_CLOCK_OK;
}

MDR_CPU_SetClockResult MDR_CPU_SetClock_HSI(const MDR_CPU_CfgHSI *cfgHSI, uint32_t timeoutCycles, bool fromLowerFreq)
{
  //  Check if current clock is from CPU_C3
  uint32_t regValue = MDR_CLOCK->CPU_CLOCK;  
  if (_FLD2VAL(MDR_RST_CPU__HCLK_SEL, regValue) == MDR_HCLK_CPU_C3)
    return MDR_SET_CLOCK_ERR__SRC_USING;

  //  Enable HSI
  if (!MDR_HSI_EnableAndWaitReady(cfgHSI->freqTrim, timeoutCycles))
    return MDR_SET_CLOCK_ERR__GEN_NotReady;  
  
  if (fromLowerFreq)
    MDR_CPU_ApplyFreqSupport(&cfgHSI->freqSupp);
  
  //  Prepare CPU_C1 Muxes
  regValue &= MDR_RST_CPU__HCLK_SEL_Msk;
  regValue |=  VAL2FLD_Pos(cfgHSI->selDiv2 + MDR_HSIE2_HSI, MDR_RST_CPU__C1_SEL_Pos)
             | VAL2FLD_Pos(MDR_CPU_C1  , MDR_RST_CPU__C2_SEL_Pos)
             | VAL2FLD_Pos(cfgHSI->divC3       , MDR_RST_CPU__C3_SEL_Pos);
  
  MDR_CLOCK->CPU_CLOCK = regValue;
  MDR_CLOCK->CPU_CLOCK = MDR_MaskClrSet(regValue, MDR_RST_CPU__HCLK_SEL_Msk, VAL2FLD_Pos(MDR_HCLK_CPU_C3, MDR_RST_CPU__HCLK_SEL_Pos));
  
  if (!fromLowerFreq)
    MDR_CPU_ApplyFreqSupport(&cfgHSI->freqSupp);  
  return MDR_SET_CLOCK_OK;
}


//-------------------  Тактирование от HSE  ---------------------

MDR_CPU_SetClockResult  MDR_CPU_SetClock_HSE(const MDR_CPU_CfgHSE *cfgHSE, uint32_t timeoutCycles, bool fromLowerFreq)  
{
  //  Check if current clock is from CPU_C3
  uint32_t regValue = MDR_CLOCK->CPU_CLOCK;  
  if (_FLD2VAL(MDR_RST_CPU__HCLK_SEL, regValue) == MDR_HCLK_CPU_C3)
    return MDR_SET_CLOCK_ERR__SRC_USING;  
  
  //  Enable HSE
  if (!MDR_HSE_EnableAndWaitReady(cfgHSE->freqSource, timeoutCycles))
    return MDR_SET_CLOCK_ERR__GEN_NotReady;

  if (fromLowerFreq)
    MDR_CPU_ApplyFreqSupport(&cfgHSE->freqSupp); 
  
  //  Prepare CPU_C1 Muxes
  regValue &= MDR_RST_CPU__HCLK_SEL_Msk;
  regValue |=  VAL2FLD_Pos(cfgHSE->selDiv2 + MDR_HSIE2_HSE, MDR_RST_CPU__C1_SEL_Pos)
             | VAL2FLD_Pos(MDR_CPU_C1     , MDR_RST_CPU__C2_SEL_Pos)
             | VAL2FLD_Pos(cfgHSE->divC3  , MDR_RST_CPU__C3_SEL_Pos);
  
  MDR_CLOCK->CPU_CLOCK = regValue;
  MDR_CLOCK->CPU_CLOCK = MDR_MaskClrSet(regValue, MDR_RST_CPU__HCLK_SEL_Msk, VAL2FLD_Pos(MDR_HCLK_CPU_C3, MDR_RST_CPU__HCLK_SEL_Pos));
  
  if (!fromLowerFreq)
    MDR_CPU_ApplyFreqSupport(&cfgHSE->freqSupp);   
  return MDR_SET_CLOCK_OK;  
}

  
//-------------------  Тактирование от HSI через PLL  ---------------------
MDR_CPU_SetClockResult  MDR_CPU_SetClock_PLL_HSI(const MDR_CPU_PLL_CfgHSI *cfgPLL_HSI, bool fromLowerFreq)
{
  //  Check if current clock is from CPU_C3
  uint32_t regValue = MDR_CLOCK->CPU_CLOCK;  
  if (_FLD2VAL(MDR_RST_CPU__HCLK_SEL, regValue) == MDR_HCLK_CPU_C3)
    return MDR_SET_CLOCK_ERR__SRC_USING;  

  //  Enable HSI
  if (!MDR_HSI_EnableAndWaitReady(cfgPLL_HSI->freqTrim, cfgPLL_HSI->timeoutCycles_HSI))
    return MDR_SET_CLOCK_ERR__GEN_NotReady;  
  //  Enable PLL
  if (!MDR_PLL_EnableAndWaitReady(cfgPLL_HSI->pllMul, cfgPLL_HSI->timeoutCycles_PLL))
    return MDR_SET_CLOCK_ERR__PLL_NotReady;
    
  if (fromLowerFreq)
    MDR_CPU_ApplyFreqSupport(&cfgPLL_HSI->freqSupp);
  
  //  Prepare CPU_C1 Muxes
  regValue &= MDR_RST_CPU__HCLK_SEL_Msk;
  regValue |= VAL2FLD_Pos(cfgPLL_HSI->selDiv2 + MDR_HSIE2_HSI, MDR_RST_CPU__C1_SEL_Pos)
            | VAL2FLD_Pos(MDR_CPU_PLL , MDR_RST_CPU__C2_SEL_Pos)
            | VAL2FLD_Pos(cfgPLL_HSI->divC3, MDR_RST_CPU__C3_SEL_Pos);
  
  MDR_CLOCK->CPU_CLOCK = regValue;
  MDR_CLOCK->CPU_CLOCK = MDR_MaskClrSet(regValue, MDR_RST_CPU__HCLK_SEL_Msk, VAL2FLD_Pos(MDR_HCLK_CPU_C3, MDR_RST_CPU__HCLK_SEL_Pos));
  
  if (!fromLowerFreq)
    MDR_CPU_ApplyFreqSupport(&cfgPLL_HSI->freqSupp);
  return MDR_SET_CLOCK_OK;
}
 

//-------------------  Тактирование от HSE через PLL  ---------------------
MDR_CPU_SetClockResult  MDR_CPU_SetClock_PLL_HSE(const MDR_CPU_PLL_CfgHSE  *cfgPLL_HSE, bool fromLowerFreq)  
{
  //  Check if current clock is from CPU_C3
  uint32_t regValue = MDR_CLOCK->CPU_CLOCK;  
  if (_FLD2VAL(MDR_RST_CPU__HCLK_SEL, regValue) == MDR_HCLK_CPU_C3)
    return MDR_SET_CLOCK_ERR__SRC_USING; 

  //  Enable HSE
  if (!MDR_HSE_EnableAndWaitReady(cfgPLL_HSE->freqSource, cfgPLL_HSE->timeoutCycles_HSE))
    return MDR_SET_CLOCK_ERR__GEN_NotReady;
  //  Enable PLL
  if (!MDR_PLL_EnableAndWaitReady(cfgPLL_HSE->pllMul, cfgPLL_HSE->timeoutCycles_PLL))
    return MDR_SET_CLOCK_ERR__PLL_NotReady;

  if (fromLowerFreq)
    MDR_CPU_ApplyFreqSupportF(cfgPLL_HSE->freqSupp.lowSRI, cfgPLL_HSE->freqSupp.delayAccessEEPROM);  
  
  //  Prepare CPU_C1 Muxes
  regValue &= MDR_RST_CPU__HCLK_SEL_Msk;
  regValue |= VAL2FLD_Pos(cfgPLL_HSE->selDiv2 + MDR_HSIE2_HSE, MDR_RST_CPU__C1_SEL_Pos)
            | VAL2FLD_Pos(MDR_CPU_PLL, MDR_RST_CPU__C2_SEL_Pos)
            | VAL2FLD_Pos(cfgPLL_HSE->divC3, MDR_RST_CPU__C3_SEL_Pos);
  
  MDR_CLOCK->CPU_CLOCK = regValue;
  MDR_CLOCK->CPU_CLOCK = MDR_MaskClrSet(regValue, MDR_RST_CPU__HCLK_SEL_Msk, VAL2FLD_Pos(MDR_HCLK_CPU_C3, MDR_RST_CPU__HCLK_SEL_Pos));
  
  if (!fromLowerFreq)
    MDR_CPU_ApplyFreqSupportF(cfgPLL_HSE->freqSupp.lowSRI, cfgPLL_HSE->freqSupp.delayAccessEEPROM);  
  return MDR_SET_CLOCK_OK; 
}
 


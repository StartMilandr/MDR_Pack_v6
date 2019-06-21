#include <MDR_RST_Clock.h>

//=================   Сброс блока и чтение текущей частоты CPU ==============
//  Желательно обновить после смены частоты, тогда впоследствии можно вызывать без флага обновления
uint32_t MDR_CPU_GetFreqHz(bool doUpdate)
{
  if (doUpdate)
    SystemCoreClockUpdate();
  
  return SystemCoreClock;
}

//  Сброс блока тактирования RST_CLOCK в начальное состояние
bool MDR_CLK_ResetBlock(const MDR_CPU_CfgHSI *cfgHSI, uint32_t timeoutCycles, bool fromLowerFreq)  
{ 
  if ((MDR_CPU_SetClock_HSI(cfgHSI, timeoutCycles, fromLowerFreq)) != MDR_SET_CLOCK_OK)
    return false;  
  
  MDR_CLOCK->MAX_CLK = 0;
  
  MDR_CLOCK->CPU_CLK = 0;
  MDR_CLOCK->PER0_CLK = 0;
  MDR_CLOCK->PER1_CLK = 0;
  MDR_CLOCK->CPU_CHKR.CPU_CHK0 = 0;
  MDR_CLOCK->CPU_CHKR.CPU_CHK1 = 0;
  MDR_CLOCK->CPU_CHKR.CPU_CHK2 = 0;
  MDR_CLOCK->CPU_STAT = 0;
  
  MDR_CLOCK->LSI_CLK = 0;
  MDR_CLOCK->LSI_CHKR.CPU_CHK0 = 0;
  MDR_CLOCK->LSI_CHKR.CPU_CHK1 = 0;
  MDR_CLOCK->LSI_CHKR.CPU_CHK2 = 0;
  MDR_CLOCK->LSI_STAT = 0;
    
  MDR_CLOCK->LSE_CLK = 0;
  MDR_CLOCK->LSE_CHKR.CPU_CHK0 = 0;
  MDR_CLOCK->LSE_CHKR.CPU_CHK1 = 0;
  MDR_CLOCK->LSE_CHKR.CPU_CHK2 = 0;
  MDR_CLOCK->LSE_STAT = 0;
  
  MDR_CLOCK->HSE0_CLK = 0;
  MDR_CLOCK->HSE0_CHKR.CPU_CHK0 = 0;
  MDR_CLOCK->HSE0_CHKR.CPU_CHK1 = 0;
  MDR_CLOCK->HSE0_CHKR.CPU_CHK2 = 0;
  MDR_CLOCK->HSE0_STAT = 0;
  MDR_CLOCK->HSE1_CLK = 0;
  MDR_CLOCK->HSE1_CHKR.CPU_CHK0 = 0;
  MDR_CLOCK->HSE1_CHKR.CPU_CHK1 = 0;
  MDR_CLOCK->HSE1_CHKR.CPU_CHK2 = 0;
  MDR_CLOCK->HSE1_STAT = 0;
  
  MDR_CLOCK->PLL0_CLK = 0;
  MDR_CLOCK->PLL0_CHKR.CPU_CHK0 = 0;
  MDR_CLOCK->PLL0_CHKR.CPU_CHK1 = 0;
  MDR_CLOCK->PLL0_CHKR.CPU_CHK2 = 0;
  MDR_CLOCK->PLL0_STAT = 0;
  MDR_CLOCK->PLL1_CLK = 0;
  MDR_CLOCK->PLL1_CHKR.CPU_CHK0 = 0;
  MDR_CLOCK->PLL1_CHKR.CPU_CHK1 = 0;
  MDR_CLOCK->PLL1_CHKR.CPU_CHK2 = 0;
  MDR_CLOCK->PLL1_STAT = 0;
  MDR_CLOCK->PLL2_CLK = 0;
  MDR_CLOCK->PLL2_CHKR.CPU_CHK0 = 0;
  MDR_CLOCK->PLL2_CHKR.CPU_CHK1 = 0;
  MDR_CLOCK->PLL2_CHKR.CPU_CHK2 = 0;
  MDR_CLOCK->PLL2_STAT = 0;
  
  MDR_CLOCK->PLL3_CLK = 0;
  MDR_CLOCK->PLL3_CHKR.CPU_CHK0 = 0;
  MDR_CLOCK->PLL3_CHKR.CPU_CHK1 = 0;
  MDR_CLOCK->PLL3_CHKR.CPU_CHK2 = 0;
  MDR_CLOCK->PLL3_STAT = 0;
  
  MDR_CLOCK->ETH_CLK = 0;
  MDR_CLOCK->USB_CLK = 0;
  MDR_CLOCK->RTC_CLK = 0;
  MDR_CLOCK->SSP1_CLK = 0;
  MDR_CLOCK->SSP2_CLK = 0;
  MDR_CLOCK->CAN1_CLK = 0;
  MDR_CLOCK->CAN2_CLK = 0;
  MDR_CLOCK->UART1_CLK = 0;
  MDR_CLOCK->UART2_CLK = 0;
  MDR_CLOCK->UART3_CLK = 0;
  MDR_CLOCK->UART4_CLK = 0;
  MDR_CLOCK->MIL_CLK = 0;
  MDR_CLOCK->TIM1_CLK = 0;
  MDR_CLOCK->TIM2_CLK = 0;
  MDR_CLOCK->TIM3_CLK = 0;
  MDR_CLOCK->TIM4_CLK = 0;
  MDR_CLOCK->CAP1_CLK = 0;
  MDR_CLOCK->CAP2_CLK = 0;
  MDR_CLOCK->CAP3_CLK = 0;
  MDR_CLOCK->CAP4_CLK = 0;
  MDR_CLOCK->QEP1_CLK = 0;
  MDR_CLOCK->QEP2_CLK = 0;
  MDR_CLOCK->PWM1_CLK = 0;
  MDR_CLOCK->PWM2_CLK = 0;
  MDR_CLOCK->PWM3_CLK = 0;
  MDR_CLOCK->PWM4_CLK = 0;
  MDR_CLOCK->PWM5_CLK = 0;
  MDR_CLOCK->PWM6_CLK = 0;
  MDR_CLOCK->PWM7_CLK = 0;
  MDR_CLOCK->PWM8_CLK = 0;
  MDR_CLOCK->PWM9_CLK = 0;
  MDR_CLOCK->ADC1_CLK = 0;
  MDR_CLOCK->ADC2_CLK = 0;
  MDR_CLOCK->ADC3_CLK = 0;
  MDR_CLOCK->CORDIC_CLK = 0;

  return true;
}

//=============   Включение генераторов - LSE ==============
bool MDR_LSE_GetReady(void)
{
#ifdef MDR_CLK_READY_BY_BKP
  return BKP_REG63x_Get() & MDR_BKP_REG63_LSE_RDY_Msk;  
#else  
  return MDR_CLOCK->LSE_STAT & MDR_RST_CLK_STAT_READY_Msk;
#endif
}


//=============   Включение генераторов - LSI ==============
bool MDR_LSI_GetReady(void)
{
#ifdef MDR_CLK_READY_BY_BKP
  return BKP_REG63x_Get() & MDR_BKP_REG63_LSI_RDY_Msk;  
#else  
  return MDR_CLOCK->LSI_STAT & MDR_RST_CLK_STAT_READY_Msk;
#endif
}


//=============   Включение генераторов - HSI ==============
bool MDR_HSI_GetReady(void)
{
#ifdef MDR_CLK_READY_BY_BKP
  return BKP_REG63x_Get() & MDR_BKP_REG63_HSI_RDY_Msk;  
#else  
  return MDR_CLOCK->HSI_STAT & MDR_RST_CLK_STAT_READY_Msk;
#endif
}


//=============   Включение генераторов - HSEx ==============


bool MDR_HSE0_GetReady(void) 
{ 
  return MDR_BKP->TMR0.REG_63 & MDR_BKP_REG63_HSE0_RDY_Msk;
}

bool MDR_HSE1_GetReady(void) 
{ 
  return MDR_BKP->TMR0.REG_63 & MDR_BKP_REG63_HSE1_RDY_Msk;
}


//=============   Настройка PLL ==============
//  Closure
static MDR_RST_PLL_Type *_PLLx;
static bool _PLLx_GetReady_Local(void)
{
  return MDR_PLLx_GetReady(_PLLx);
}

bool MDR_PLLx_WaitReady(MDR_RST_PLL_Type *PLLx, uint32_t timeoutCycles)
{
  _PLLx = PLLx;
  return WaitCondition(timeoutCycles, _PLLx_GetReady_Local);  
}

void MDR_PLLx_Enable(MDR_RST_PLL_Type *PLLx, MDR_PLL_IN_SEL inpSrc, const MDR_CLK_CfgPLL *cfgPLL)
{
  uint32_t regValue = PLLx->PLL_CLK;
  
  regValue &= ~(MDR_RST_PLL_PLL_Q_Msk | MDR_RST_PLL_DV_Msk | MDR_RST_PLL_PLL_N_Msk | MDR_RST_PLL_SELECT_Msk | MDR_RST_PLL_PLL_ReadyMode_Msk | MDR_RST_PLL_PLL_ON_Msk);
  regValue |= VAL2FLD(cfgPLL->mulN_3_75, MDR_RST_PLL_PLL_N) | 
              VAL2FLD(cfgPLL->divQ_0_15, MDR_RST_PLL_PLL_Q) | 
              VAL2FLD(cfgPLL->divOut   , MDR_RST_PLL_DV)    | 
              VAL2FLD(inpSrc   , MDR_RST_PLL_SELECT)| 
              MDR_RST_PLL_PLL_ON_Msk;
  
  PLLx->PLL_CLK = regValue;
}


//==============================================================================
//=======     Подстройка питания и временных параметров под частоту   ==========
//==============================================================================

MDR_CLK_LDO_LowSRI    MDR_FreqCPU_ToLowSRI(uint32_t CPU_FregHz)
{
  if      (CPU_FregHz >  100E+6) return MDR_BKP_LDO_SRILow_ge100MHz;
  else if (CPU_FregHz >  50E+6)  return MDR_BKP_LDO_SRILow_lt100MHz;
  else if (CPU_FregHz >  30E+6)  return MDR_BKP_LDO_SRILow_lt50MHz;  
  else if (CPU_FregHz >  10E+6)  return MDR_BKP_LDO_SRILow_lt30MHz;
  else if (CPU_FregHz >   1E+6)  return MDR_BKP_LDO_SRILow_lt10MHz;
  else if (CPU_FregHz > 500E+3)	 return MDR_BKP_LDO_SRILow_lt1MHz;
  else if (CPU_FregHz > 100E+3)	 return MDR_BKP_LDO_SRILow_lt500KHz;
  else 
    return MDR_BKP_LDO_SRILow_lt100KHz;
}

//  Выставлять ДО перехода на более высокие частоты, и ПОСЛЕ перехода на более низкие.
//  Функция регулирует LDO под частоту тактирования и выставляет задержку для доступа к OTP
void MDR_CLK_ApplyFreqSupport_LDO(MDR_CLK_LDO_LowSRI  lowSRI)
{ 
  //  HLDO
  MDR_BKP->TMR0.REG_61 = MDR_MaskClrSet(MDR_BKP->TMR0.REG_61, MDR_BKP_REG61_HLDO_SRILow_Msk, VAL2FLD_Pos(lowSRI, MDR_BKP_REG61_HLDO_SRILow_Pos));
  //  BLDO
  MDR_BKP->BLDO_CTRL0 = MDR_MaskClrSet(MDR_BKP->TMR0.REG_61, MDR_BKP_BLDO_BLDO_SRILow_Msk, VAL2FLD_Pos(lowSRI, MDR_BKP_BLDO_BLDO_SRILow_Pos));
  //  ???
  MDR_BKP->TMR0.REG_62 = MDR_MaskClrSet(MDR_BKP->TMR0.REG_62, MDR_BKP_REG62_BLDO_SRILow_Msk, VAL2FLD_Pos(lowSRI, MDR_BKP_REG62_BLDO_SRILow_Pos));
}

//  Функция выставляет задержку для доступа к OTP
void MDR_CLK_ApplyFreqSupport_EEPROM(MDR_CLK_Delay_EEPROM delayEEPROM)
{
  MDR_EEPROM->KEY  = MDR_KEY_UNLOCK;
  MDR_EEPROM->CNTR = MDR_MaskClrSet(MDR_EEPROM->CNTR, MDR_EEPROM_CMD_DELAY_Msk, VAL2FLD_Pos(delayEEPROM, MDR_EEPROM_CMD_DELAY_Pos));
  MDR_EEPROM->KEY  = 0x00000000;  
}

//==============================================================================
//=============     Инициализация тактирования CPU "под ключ"   ================
//==============================================================================
  

//  Выбор тактирования ядра от MAXCLK
void MDR_CPU_SetClock_srcMAXCLK(MDR_MAXCLK_SEL selMaxClk, uint16_t divMaxToCpu_0, const MDR_CLK_FreqSupport *freqSupp, bool fromLowerFreq)
{
  if (fromLowerFreq)
    MDR_CPU_ApplyFreqSupport(freqSupp);
  
  MDR_CLK_SetMAXCLK(selMaxClk);
  MDR_CLK_SetDiv_MaxToCPU(divMaxToCpu_0);
  
  if (!fromLowerFreq)
    MDR_CPU_ApplyFreqSupport(freqSupp);  
}

//  Тактирование ядра от внутреннего генератора LSI, ~40КГц
MDR_CPU_SetClockResult  MDR_CPU_SetClock_LSI(const MDR_CPU_CfgLSI *cfgLSI, uint32_t timeoutCycles)
{
  if (!MDR_LSI_EnableAndWaitReady(cfgLSI->freqTrim, timeoutCycles))
    return MDR_SET_CLOCK_ERR__GEN_NotReady;
    
  MDR_CPU_SetClock_srcMAXCLK(MAXCLK_LSI, cfgLSI->divMaxToCpu_0, &cfgLSI->freqSupp, false);
  return MDR_SET_CLOCK_OK;
}

//  Тактирование ядра от внешнего генератора LSE, частота задается в MDR_Config LSE_FREQ_HZ
MDR_CPU_SetClockResult  MDR_CPU_SetClock_LSE(const MDR_CPU_CfgLSE *cfgLSE, uint32_t timeoutCycles)                                             
{
  if (!MDR_LSE_EnableAndWaitReady(cfgLSE->freqSource, timeoutCycles))
    return MDR_SET_CLOCK_ERR__GEN_NotReady;

  MDR_CPU_SetClock_srcMAXCLK(MAXCLK_LSE, cfgLSE->divMaxToCpu_0, &cfgLSE->freqSupp, false);
  return MDR_SET_CLOCK_OK;
}

//  Тактирование ядра от внутреннего генератора HSI, ~8МГц (6МГц .. 10МГц)                                                  
MDR_CPU_SetClockResult  MDR_CPU_SetClock_HSI(const MDR_CPU_CfgHSI *cfgHSI, uint32_t timeoutCycles, bool fromLowerFreq)
{
  if (!MDR_HSI_EnableAndWaitReady(cfgHSI->freqTrim, timeoutCycles))
    return MDR_SET_CLOCK_ERR__GEN_NotReady;
  
  if (cfgHSI->selDiv2)
    MDR_CPU_SetClock_srcMAXCLK(MAXCLK_HSIdiv2, cfgHSI->divMaxToCpu_0, &cfgHSI->freqSupp, fromLowerFreq);
  else
    MDR_CPU_SetClock_srcMAXCLK(MAXCLK_HSI, cfgHSI->divMaxToCpu_0, &cfgHSI->freqSupp, fromLowerFreq);
  return MDR_SET_CLOCK_OK;  
}

//  Тактирование ядра от внешнего генератора HSE, частоту необходимо указать в MDR_Config
MDR_CPU_SetClockResult  MDR_CPU_SetClock_HSE0(const MDR_CPU_CfgHSE *cfgHSE, uint32_t timeoutCycles, bool fromLowerFreq)
{
  if (!MDR_HSE0_EnableAndWaitReady(cfgHSE->freqSource, timeoutCycles))
    return MDR_SET_CLOCK_ERR__GEN_NotReady;
  
  if (cfgHSE->selDiv2)
    MDR_CPU_SetClock_srcMAXCLK(MAXCLK_HSE0div2, cfgHSE->divMaxToCpu_0, &cfgHSE->freqSupp, fromLowerFreq);
  else
    MDR_CPU_SetClock_srcMAXCLK(MAXCLK_HSE0, cfgHSE->divMaxToCpu_0, &cfgHSE->freqSupp, fromLowerFreq);
  return MDR_SET_CLOCK_OK;      
}

MDR_CPU_SetClockResult  MDR_CPU_SetClock_HSE1(const MDR_CPU_CfgHSE *cfgHSE, uint32_t timeoutCycles, bool fromLowerFreq)
{
  if (!MDR_HSE1_EnableAndWaitReady(cfgHSE->freqSource, timeoutCycles))
    return MDR_SET_CLOCK_ERR__GEN_NotReady;
  
  if (cfgHSE->selDiv2)
    MDR_CPU_SetClock_srcMAXCLK(MAXCLK_HSE1div2, cfgHSE->divMaxToCpu_0, &cfgHSE->freqSupp, fromLowerFreq);
  else
    MDR_CPU_SetClock_srcMAXCLK(MAXCLK_HSE1, cfgHSE->divMaxToCpu_0, &cfgHSE->freqSupp, fromLowerFreq);
  return MDR_SET_CLOCK_OK;      
}


//  Тактирование ядра от внутреннего генератора HSI через PLL, ~8МГц (6МГц .. 10МГц)                         
MDR_CPU_SetClockResult  MDR_CPU_SetClock_PLL_srcHSI(MDR_RST_PLL_Type *PLLx, MDR_MAXCLK_SEL selMaxClk, 
  const MDR_CPU_PLL_CfgHSI  *cfgPLL_HSI, MDR_PLL_IN_SEL inpPll, bool fromLowerFreq)
{
  if (selMaxClk == MDR_CLK_GetMAXCLK())
    return MDR_SET_CLOCK_ERR__SRC_USING;
  
  if (!MDR_HSI_EnableAndWaitReady(cfgPLL_HSI->freqTrim, cfgPLL_HSI->timeoutCycles_HSI))
    return MDR_SET_CLOCK_ERR__GEN_NotReady;
  
  if (cfgPLL_HSI->selDiv2)
    inpPll += 1;
  if (!MDR_PLLx_EnableAndWaitReady(PLLx, inpPll, &cfgPLL_HSI->cfgPLL, cfgPLL_HSI->timeoutCycles_PLL))
    return MDR_SET_CLOCK_ERR__PLL_NotReady;
  

  MDR_CPU_SetClock_srcMAXCLK(selMaxClk, cfgPLL_HSI->divMaxToCpu_0, &cfgPLL_HSI->freqSupp, fromLowerFreq);
  return MDR_SET_CLOCK_OK;
}


//  Тактирование ядра от внешнего генератора HSЕ (1МГц - 30МГц) через PLL
MDR_CPU_SetClockResult  MDR_CPU_SetClock_PLL_srcHSE0(MDR_RST_PLL_Type *PLLx, MDR_MAXCLK_SEL selMaxClk, 
  const MDR_CPU_PLL_CfgHSE  *cfgPLL_HSE, MDR_PLL_IN_SEL inpPll, bool fromLowerFreq)
{
  if (selMaxClk == MDR_CLK_GetMAXCLK())
    return MDR_SET_CLOCK_ERR__SRC_USING;  
  
  if (!MDR_HSE0_EnableAndWaitReady(cfgPLL_HSE->freqSource, cfgPLL_HSE->timeoutCycles_HSE))
    return MDR_SET_CLOCK_ERR__GEN_NotReady;

  if (cfgPLL_HSE->selDiv2)
    inpPll += 1;  
  if (!MDR_PLLx_EnableAndWaitReady(PLLx, inpPll, &cfgPLL_HSE->cfgPLL, cfgPLL_HSE->timeoutCycles_PLL))
    return MDR_SET_CLOCK_ERR__PLL_NotReady;
  
  MDR_CPU_SetClock_srcMAXCLK(selMaxClk, cfgPLL_HSE->divMaxToCpu_0, &cfgPLL_HSE->freqSupp, fromLowerFreq);
  return MDR_SET_CLOCK_OK;
}

MDR_CPU_SetClockResult  MDR_CPU_SetClock_PLL_srcHSE1(MDR_RST_PLL_Type *PLLx, MDR_MAXCLK_SEL selMaxClk, 
  const MDR_CPU_PLL_CfgHSE  *cfgPLL_HSE, MDR_PLL_IN_SEL inpPll, bool fromLowerFreq)
{
  if (selMaxClk == MDR_CLK_GetMAXCLK())
    return MDR_SET_CLOCK_ERR__SRC_USING;  
  
  if (!MDR_HSE1_EnableAndWaitReady(cfgPLL_HSE->freqSource, cfgPLL_HSE->timeoutCycles_HSE))
    return MDR_SET_CLOCK_ERR__GEN_NotReady;

  if (cfgPLL_HSE->selDiv2)
    inpPll += 1;  
  if (!MDR_PLLx_EnableAndWaitReady(PLLx, inpPll, &cfgPLL_HSE->cfgPLL, cfgPLL_HSE->timeoutCycles_PLL))
    return MDR_SET_CLOCK_ERR__PLL_NotReady;
  
  MDR_CPU_SetClock_srcMAXCLK(selMaxClk, cfgPLL_HSE->divMaxToCpu_0, &cfgPLL_HSE->freqSupp, fromLowerFreq);
  return MDR_SET_CLOCK_OK;
}
  

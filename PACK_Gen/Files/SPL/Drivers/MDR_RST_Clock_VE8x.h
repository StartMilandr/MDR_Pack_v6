#ifndef MDR_RST_CLOCK_VE8x_H
#define MDR_RST_CLOCK_VE8x_H

#include <MDR_Config.h>
#include <MDR_Types.h>
#include <MDR_Funcs.h>

#if defined (USE_MDR1986VE8) || defined (USE_MDR1986VE81)
  #include <MDR_RST_Clock_DefsVE8.h>
#elif defined (USE_MDR1923VK014)
  #include <MDR_RST_Clock_DefsVK14.h>
#endif

  
//=================   Доступ к регистрам блока ===============

//  Включение доступа к регистрам блоков RST и BKP. (В BKP управление генераторами)
//  Вызывать перед вызовом остальных функций работы с блоком.
__STATIC_INLINE void MDR_CLK_Enable_RST_BPK(void)
{
#ifdef MDR_CLK_EN__RST_BKP
  REG32(MDR_CLK_EN_ADDR_RST) |= MDR_CLK_EN_BIT_RST;
  REG32(MDR_CLK_EN_ADDR_BKP) |= MDR_CLK_EN_BIT_BKP;
#endif
  MDR_CLOCK->KEY = MDR_KEY_UNLOCK;  
  MDR_BKP->KEY   = MDR_KEY_UNLOCK;
}

//  Тактирование блоков RST и BKP можно выключить после работы с блоком, можно и не отключать:
//  Отключение доступа к регистрам блока RST
__STATIC_INLINE void MDR_CLK_Disable_RST(void)
{
  MDR_CLOCK->KEY = 0;
#ifdef MDR_CLK_EN_ADDR_RST
  REG32(MDR_CLK_EN_ADDR_RST) &= ~MDR_CLK_EN_BIT_RST;
#endif
}

//  Отключение доступа к регистрам блока BKP
__STATIC_INLINE void MDR_CLK_Disable_BKP(void)
{
  MDR_BKP->KEY = 0;
#ifdef MDR_CLK_EN_ADDR_BKP
  REG32(MDR_CLK_EN_ADDR_BKP) &= ~MDR_CLK_EN_BIT_BKP;
#endif
}


//=================   Сброс блока и чтение текущей частоты CPU ==============
//  Сброс блока тактирования RST_CLOCK в начальное состояние, тактирование от HSI.
//  В fromLowerFreq указать с большей или меньшей частоты происходит сброс. 
//  fromLowerFreq влияет на очередность выставления параметров MDR_CLK_FreqSupport - до или после переключения частоты.
bool MDR_CLK_ResetBlock(const MDR_CPU_CfgHSI *cfgHSI, uint32_t timeoutCycles, bool fromLowerFreq);

//  Желательно вызывать после смены частоты, тогда впоследствии можно вызывать без флага обновления
uint32_t MDR_CPU_GetFreqHz(bool doUpdate);


//=============   Функции обращения с троированными регистрами блока BKP ==============

__STATIC_INLINE void BKP_REG63x_Set(uint32_t setMask)
{  
  MDR_BKP->TMR0.REG_63 |= setMask;
  MDR_BKP->TMR1.REG_63 |= setMask;
  MDR_BKP->TMR2.REG_63 |= setMask;  
}

__STATIC_INLINE void BKP_REG63x_Clr(uint32_t clrMask)
{  
  clrMask = ~clrMask;
  MDR_BKP->TMR0.REG_63 &= clrMask;
  MDR_BKP->TMR1.REG_63 &= clrMask;
  MDR_BKP->TMR2.REG_63 &= clrMask;  
}

__STATIC_INLINE void BKP_REG63x_ClrSet(uint32_t clrMask, uint32_t setMask)
{
  BKP_REG63x_Clr(clrMask);
  BKP_REG63x_Set(setMask);
}

__STATIC_INLINE uint32_t BKP_REG63x_Get(void)
{  
  return MDR_BKP->TMR0.REG_63 & MDR_BKP->TMR1.REG_63 & MDR_BKP->TMR2.REG_63;
}


//=====================================================================
//======================   Включение генераторов ======================
//=====================================================================

// --- LSE ---
__STATIC_INLINE void MDR_LSE_Enable(MDR_CLK_Source freqSource)
{
  switch (freqSource) {
    case MDR_CLK_Resonator: 
      BKP_REG63x_ClrSet(MDR_BKP_REG63_LSE_BYP_Msk | MDR_BKP_REG63_LSE_FilterEn_Msk, MDR_BKP_REG63_LSE_On_Msk); 
      break;
    case MDR_CLK_Generator: 
      BKP_REG63x_ClrSet(MDR_BKP_REG63_LSE_FilterEn_Msk, MDR_BKP_REG63_LSE_On_Msk | MDR_BKP_REG63_LSE_BYP_Msk);
      break;
    case MDR_CLK_GeneratorFilterEn: 
      BKP_REG63x_Set(MDR_BKP_REG63_LSE_On_Msk | MDR_BKP_REG63_LSE_BYP_Msk | MDR_BKP_REG63_LSE_FilterEn_Msk);
      break;
  }
}

__STATIC_INLINE void MDR_LSE_Disable (void) {BKP_REG63x_Clr(MDR_BKP_REG63_LSE_On_Msk);}
                bool MDR_LSE_GetReady(void);

//  Включает генератор LSE с ожиданием готовности LSE_Ready. Возвращает LSE_Ready.
__STATIC_INLINE bool MDR_LSE_EnableAndWaitReady(MDR_CLK_Source freqSource, uint32_t timeoutCycles)
                                              { MDR_LSE_Enable(freqSource);  
                                                return WaitCondition(timeoutCycles, MDR_LSE_GetReady);}


// --- LSI ---
#ifdef MDR_BKP_REG63_LSI_On_Msk
  __STATIC_INLINE void MDR_LSI_EnableAndTrim(MDR_CLK_LSI_TRIM freqTrim)  
    { BKP_REG63x_ClrSet(MDR_BKP_REG63_LSI_Trim_Msk, MDR_BKP_REG63_LSI_On_Msk | VAL2FLD_Pos(freqTrim, MDR_BKP_REG63_LSI_Trim_Pos)); }
    
  __STATIC_INLINE void MDR_LSI_Enable  (void) {BKP_REG63x_Set(MDR_BKP_REG63_LSI_On_Msk);}                
  __STATIC_INLINE void MDR_LSI_Disable (void) {BKP_REG63x_Clr(MDR_BKP_REG63_LSI_On_Msk);}
#else
  __STATIC_INLINE void MDR_LSI_EnableAndTrim(MDR_CLK_LSI_TRIM freqTrim)  
    { BKP_REG63x_ClrSet(MDR_BKP_REG63_LSI_Trim_Msk | MDR_BKP_REG63_LSI_Dis_Msk, VAL2FLD_Pos(freqTrim, MDR_BKP_REG63_LSI_Trim_Pos)); }
    
  __STATIC_INLINE void MDR_LSI_Enable  (void) {BKP_REG63x_Clr(MDR_BKP_REG63_LSI_Dis_Msk);}                
  __STATIC_INLINE void MDR_LSI_Disable (void) {BKP_REG63x_Set(MDR_BKP_REG63_LSI_Dis_Msk);}
#endif

bool MDR_LSI_GetReady(void);  
  //  Включает генератор LSE с ожиданием готовности LSE_Ready. Возвращает LSE_Ready.
__STATIC_INLINE 
bool MDR_LSI_EnableAndWaitReady(MDR_CLK_LSI_TRIM freqTrim, uint32_t timeoutCycles)
                               { MDR_LSI_EnableAndTrim(freqTrim);  
                                 return WaitCondition(timeoutCycles, MDR_LSI_GetReady);}
  
// --- HSI ---
#ifdef MDR_BKP_REG63_HSI_On_Msk
  __STATIC_INLINE void MDR_HSI_EnableAndTrim(MDR_CLK_HSI_TRIM freqTrim) 
    { BKP_REG63x_ClrSet(MDR_BKP_REG63_HSI_Trim_Msk, MDR_BKP_REG63_HSI_On_Msk | VAL2FLD_Pos(freqTrim, MDR_BKP_REG63_HSI_Trim_Pos)); }
    
  __STATIC_INLINE void MDR_HSI_Enable  (void) {BKP_REG63x_Set(MDR_BKP_REG63_HSI_On_Msk);}
  __STATIC_INLINE void MDR_HSI_Disable (void) { BKP_REG63x_Clr(MDR_BKP_REG63_HSI_On_Msk); }
#else
  __STATIC_INLINE void MDR_HSI_EnableAndTrim(MDR_CLK_HSI_TRIM freqTrim) 
    { BKP_REG63x_ClrSet(MDR_BKP_REG63_HSI_Trim_Msk | MDR_BKP_REG63_HSI_Dis_Msk, VAL2FLD_Pos(freqTrim, MDR_BKP_REG63_HSI_Trim_Pos)); }
    
  __STATIC_INLINE void MDR_HSI_Enable  (void) {BKP_REG63x_Clr(MDR_BKP_REG63_HSI_Dis_Msk);}
  __STATIC_INLINE void MDR_HSI_Disable (void) { BKP_REG63x_Set(MDR_BKP_REG63_HSI_Dis_Msk); }  
#endif

bool MDR_HSI_GetReady(void);  
//  Включает генератор HSI с ожиданием готовности HSI_Ready. Возвращает HSI_Ready.
__STATIC_INLINE 
bool MDR_HSI_EnableAndWaitReady(MDR_CLK_HSI_TRIM freqTrim, uint32_t timeoutCycles)
                               { MDR_HSI_EnableAndTrim(freqTrim);  
                                 return WaitCondition(timeoutCycles, MDR_HSI_GetReady); }

// --- HSE ---
__STATIC_INLINE void MDR_HSEx_Enable(MDR_RST_HSE_Type *HSEx, MDR_CLK_Source freqSource)
{
  switch (freqSource) {
    case MDR_CLK_Resonator: 
      HSEx->HSE_CLK &= ~(MDR_RST_HSE_HSE_BYP_Msk | MDR_RST_HSE_FILTER_EN_Msk);
      HSEx->HSE_CLK |= MDR_RST_HSE_HSE_ON_Msk;
      break;
    case MDR_CLK_Generator: 
      HSEx->HSE_CLK &= ~(MDR_RST_HSE_FILTER_EN_Msk);
      HSEx->HSE_CLK |= MDR_RST_HSE_HSE_ON_Msk | MDR_RST_HSE_HSE_BYP_Msk;
      break;
    case MDR_CLK_GeneratorFilterEn:
      HSEx->HSE_CLK |= MDR_RST_HSE_HSE_ON_Msk | MDR_RST_HSE_HSE_BYP_Msk | MDR_RST_HSE_FILTER_EN_Msk;
      break;
  }
}

__STATIC_INLINE bool MDR_HSEx_GetReady(MDR_RST_HSE_Type *HSEx) { return HSEx->HSE_STAT & MDR_RST_CLK_STAT_READY_Msk; }
__STATIC_INLINE void MDR_HSEx_Disable(MDR_RST_HSE_Type *HSEx) { HSEx->HSE_CLK &= ~MDR_RST_HSE_HSE_ON_Msk; }
                bool MDR_HSEx_WaitReady(MDR_RST_HSE_Type *HSEx, uint32_t timeoutCycles);
                                                
//  Включает генератор HSE с ожиданием готовности HSE_Ready. Возвращает HSE_Ready.
__STATIC_INLINE bool MDR_HSEx_EnableAndWaitReady(MDR_RST_HSE_Type *HSEx, MDR_CLK_Source freqSource, uint32_t timeoutCycles)
                                              { MDR_HSEx_Enable(HSEx, freqSource);  
                                                return MDR_HSEx_WaitReady(HSEx, timeoutCycles); }
                                                
                                                
#define MDR_HSE0_EnableAndWaitReady(freqSrc, timeout)     MDR_HSEx_EnableAndWaitReady(MDR_CLOCK_HSE0, (freqSrc), (timeout))
#define MDR_HSE0_Enable(freqSrc)              MDR_HSEx_Enable(MDR_CLOCK_HSE0, (freqSrc))
#define MDR_HSE0_GetReady()                   MDR_HSEx_GetReady(MDR_CLOCK_HSE0)
#define MDR_HSE0_Disable()                    MDR_HSEx_Disable(MDR_CLOCK_HSE0)

#define MDR_HSE1_EnableAndWaitReady(freqSrc, timeout)     MDR_HSEx_EnableAndWaitReady(MDR_CLOCK_HSE1, (freqSrc), (timeout))  
#define MDR_HSE1_Enable(freqSrc)              MDR_HSEx_Enable(MDR_CLOCK_HSE1, (freqSrc))
#define MDR_HSE1_GetReady()                   MDR_HSEx_GetReady(MDR_CLOCK_HSE1)
#define MDR_HSE1_Disable()                    MDR_HSEx_Disable(MDR_CLOCK_HSE1)  

#define MDR_HSE_EnableAndWaitReady(freqSrc, timeout)     MDR_HSEx_EnableAndWaitReady(MDR_HSE_Def, (freqSrc), (timeout))  
#define MDR_HSE_Enable(freqSrc)               MDR_HSEx_Enable(MDR_HSE_Def, (freqSrc))
#define MDR_HSE_GetReady()                    MDR_HSEx_GetReady(MDR_HSE_Def)
#define MDR_HSE_Disable()                     MDR_HSEx_Disable(MDR_HSE_Def)



//=============   Настройка PLL ==============                                               
void MDR_PLLx_Enable(MDR_RST_PLL_Type *PLLx, MDR_PLL_IN_SEL inpSrc, const MDR_CLK_CfgPLL *cfgPLL);
__STATIC_INLINE bool MDR_PLLx_GetReady(MDR_RST_PLL_Type *PLLx) {return PLLx->PLL_STAT & MDR_RST_CLK_STAT_READY_Msk;}
__STATIC_INLINE void MDR_PLLx_Disable (MDR_RST_PLL_Type *PLLx) {PLLx->PLL_CLK &= ~MDR_RST_PLL_PLL_ON_Msk;}

                bool MDR_PLLx_WaitReady(MDR_RST_PLL_Type *PLLx, uint32_t timeoutCycles);

// Включение PLL от источника сигнала с ожиданием готовности
__STATIC_INLINE bool MDR_PLLx_EnableAndWaitReady(MDR_RST_PLL_Type *PLLx, MDR_PLL_IN_SEL inpSrc, const MDR_CLK_CfgPLL *cfgPLL, uint32_t timeoutCycles)
                                                { MDR_PLLx_Enable(PLLx, inpSrc, cfgPLL);
                                                  return MDR_PLLx_WaitReady(PLLx, timeoutCycles); }

#define  MDR_PLL_Enable(inpSrc, cfgPLL)             MDR_PLLx_Enable(MDR_PLL_Def, inpSrc, cfgPLL)
#define  MDR_PLL_GetReady()                         MDR_PLLx_GetReady(MDR_PLL_Def)
#define  MDR_PLL_Disable()                          MDR_PLLx_Disable(MDR_PLL_Def)
#define  MDR_PLL_EnableAndWaitReady(inpSrc, cfgPLL) MDR_PLLx_EnableAndWaitReady(MDR_PLL_Def, inpSrc, cfgPLL)
                                                  
                                                  
//==============================================================================
//=======     Подстройка питания и временных параметров под частоту   ==========
//==============================================================================
//  Выставлять ДО перехода на более высокие частоты, и ПОСЛЕ перехода на более низкие.

//  Рассчет подстройка LDO от частоты
MDR_CLK_LDO_LowSRI    MDR_FreqCPU_ToLowSRI(uint32_t CPU_FregHz);
                                                  
//  Применение параметров в микроконтроллер
void MDR_CLK_ApplyFreqSupport_LDO(MDR_CLK_LDO_LowSRI  lowSRI);

#ifdef MDR_HAS_OTP
  //  Задержка доступа к ОТР памяти от частоты CPU -  Warning TODO: Add implementation, Run from RAM!!!
  bool MDR_CLK_ApplyFreqSupport_OTP(MDR_CLK_Delay_OTP delayAccessOTP);// __RAM_EXEC; 


  // Все сместе - Функция регулирует LDO под частоту тактирования и выставляет задержку для доступа к OTP
  __STATIC_INLINE
  void MDR_CPU_ApplyFreqSupportF(MDR_CLK_Delay_OTP delayAccessOTP, MDR_CLK_LDO_LowSRI  lowSRI)
  {
    MDR_CLK_ApplyFreqSupport_LDO(lowSRI); 
    MDR_CLK_ApplyFreqSupport_OTP(delayAccessOTP);
  }
                                
  __STATIC_INLINE
  void MDR_CPU_ApplyFreqSupport(const MDR_CLK_FreqSupport *freqSupp) 
  {
    MDR_CLK_ApplyFreqSupport_LDO(freqSupp->lowSRI); 
    MDR_CLK_ApplyFreqSupport_OTP(freqSupp->delayAccessOTP);
  }
#else
  __STATIC_INLINE
  void MDR_CPU_ApplyFreqSupportF(MDR_CLK_LDO_LowSRI  lowSRI)
  {
    MDR_CLK_ApplyFreqSupport_LDO(lowSRI); 
  }
                                
  __STATIC_INLINE
  void MDR_CPU_ApplyFreqSupport(const MDR_CLK_FreqSupport *freqSupp) 
  {
    MDR_CLK_ApplyFreqSupport_LDO(freqSupp->lowSRI); 
  }
#endif

//============================================================================
//=============     Тактирование ядра от MAXCLK               ================
//============================================================================

//  Переключение мультиплексора MAXCLK
__STATIC_INLINE 
void MDR_CLK_SetMAXCLK(MDR_MAXCLK_SEL selMaxClk) {MDR_CLOCK->MAX_CLK = (uint32_t)selMaxClk & MDR_RST_CLOCK_MAX_CLK_Select_Msk;}

__STATIC_INLINE 
MDR_MAXCLK_SEL  MDR_CLK_GetMAXCLK(void) 
{
  uint32_t regValue = MDR_CLOCK->MAX_CLK & MDR_RST_CLOCK_MAX_CLK_Select_Msk;
  if (regValue <= MAXCLK_PLL2)
    return (MDR_MAXCLK_SEL)regValue;
  else
    return MAXCLK_ERR;
}

//  Переключение делителя частоты MAXCLK (100MHz max) для получения частоты CPU (64MHz max)
__STATIC_INLINE 
void MDR_CLK_SetDiv_MaxToCPU(uint16_t divMaxToCpu_0)  
    {MDR_CLOCK->CPU_CLK = MDR_MaskClrSet(MDR_CLOCK->CPU_CLK, MDR_RST_CLK_DIV_Msk, VAL2FLD_Pos(divMaxToCpu_0, MDR_RST_CLK_DIV_Pos));}

  
//==============================================================================
//=============     Тактирование MAX_CLK и ядра                 ================
//=============     Инициализация тактирования CPU "под ключ"   ================
//==============================================================================
  
//  Необходимо вызвать MDR_CLK_Enable_RST_BPK для включения тактирования.
//  Далее функция настроит источник частоты и переведет на него CPU.
//  Нельзя настраивать частоту с которой в текущий момент осуществляется тактирование.
//  Функция вернет в этом случае MDR_SET_CLOCK_ERR__SRC_USING.
//  Необходимо предварительно переключиться на другую частоту.
//  Например, при перестройке HSE и PLL, необходимо с HSE временно переключиться на HSI, 
//  а после окончания настройки HSE_PLL, переключитья на HSE_PLL.
//  Параметры потребления перед переключением должны быть выставлены для большей частоты (новая vs текущая частота), 
//  это задается параметром fromLowerFreq.
    
typedef enum {
  MDR_SET_CLOCK_OK,
  MDR_SET_CLOCK_ERR__GEN_NotReady,
  MDR_SET_CLOCK_ERR__SRC_USING,
  MDR_SET_CLOCK_ERR__PLL_NotReady,
  MDR_SET_CLOCK_ERR__Undef,
} MDR_CPU_SetClockResult;


//-----------------------------------------------------------------------                         
//  Выбор тактирования ядра из MAXCLK
void MDR_CPU_SetClock_srcMAXCLK(MDR_MAXCLK_SEL selMaxClk, uint16_t divMaxToCpu_0, const MDR_CLK_FreqSupport *freqSupp, bool fromLowerFreq);
                              
//  Тактирование ядра от внутреннего генератора LSI, ~40КГц
MDR_CPU_SetClockResult  MDR_CPU_SetClock_LSI(const MDR_CPU_CfgLSI *cfgLSI, uint32_t timeoutCycles);

//  Тактирование ядра от внешнего генератора LSE, частоту необходимо указать в MDR_Config
MDR_CPU_SetClockResult  MDR_CPU_SetClock_LSE(const MDR_CPU_CfgLSE *cfgLSE, uint32_t timeoutCycles);
  
                              
//-----------------------------------------------------------------------                         
//  Тактирование ядра от внутреннего генератора HSI, ~8МГц (6МГц .. 10МГц)
MDR_CPU_SetClockResult  MDR_CPU_SetClock_HSI(const MDR_CPU_CfgHSI *cfgHSI, uint32_t timeoutCycles, bool fromLowerFreq);


//-----------------------------------------------------------------------                         
//  Тактирование ядра от внешних генераторов HSE0/HSE1, частоту необходимо указать в MDR_Config
MDR_CPU_SetClockResult  MDR_CPU_SetClock_srcHSEx(MDR_RST_HSE_Type *HSEx, MDR_MAXCLK_SEL selMaxClk, const MDR_CPU_CfgHSE *cfgHSE, 
                                                 uint32_t timeoutCycles, bool fromLowerFreq);
                         
__STATIC_INLINE 
MDR_CPU_SetClockResult  MDR_CPU_SetClock_HSE0(const MDR_CPU_CfgHSE *cfgHSE, uint32_t timeoutCycles, bool fromLowerFreq) 
                         {return MDR_CPU_SetClock_srcHSEx(MDR_CLOCK_HSE0, MAXCLK_HSE0, cfgHSE, timeoutCycles, fromLowerFreq);}

__STATIC_INLINE 
MDR_CPU_SetClockResult  MDR_CPU_SetClock_HSE1(const MDR_CPU_CfgHSE *cfgHSE, uint32_t timeoutCycles, bool fromLowerFreq) 
                         {return MDR_CPU_SetClock_srcHSEx(MDR_CLOCK_HSE1, MAXCLK_HSE1, cfgHSE, timeoutCycles, fromLowerFreq);}  

//  defaults from MDR_Conig
#if MDR_HSE_IND_Def == 0
  #define MDR_CPU_SetClock_HSE        MDR_CPU_SetClock_HSE0
  #define MDR_CPU_SetClock_HSE_div2   MDR_CPU_SetClock_HSE0_div2
#else
  #define MDR_CPU_SetClock_HSE        MDR_CPU_SetClock_HSE1
  #define MDR_CPU_SetClock_HSE_div2   MDR_CPU_SetClock_HSE1_div2
#endif                         

                         
//-----------------------------------------------------------------------                         
//  Тактирование ядра от внутреннего генератора HSI через PLL, ~8МГц (6МГц .. 10МГц)                         
MDR_CPU_SetClockResult  MDR_CPU_SetClock_PLL_srcHSI(MDR_RST_PLL_Type *PLLx, MDR_MAXCLK_SEL selMaxClk, 
                          const MDR_CPU_PLL_CfgHSI  *cfgPLL_HSI, MDR_PLL_IN_SEL inpPll, bool fromLowerFreq);

//  HSI to PLLx
__STATIC_INLINE 
MDR_CPU_SetClockResult  MDR_CPU_SetClock_HSI_PLL0(const MDR_CPU_PLL_CfgHSI  *cfgPLL_HSI, bool fromLowerFreq)
                         {return MDR_CPU_SetClock_PLL_srcHSI(MDR_CLOCK_PLL0, MAXCLK_PLL0, cfgPLL_HSI, MDR_PLL_IN_HSI, fromLowerFreq);}

__STATIC_INLINE 
MDR_CPU_SetClockResult  MDR_CPU_SetClock_HSI_PLL1(const MDR_CPU_PLL_CfgHSI  *cfgPLL_HSI, bool fromLowerFreq)
                         {return MDR_CPU_SetClock_PLL_srcHSI(MDR_CLOCK_PLL1, MAXCLK_PLL1, cfgPLL_HSI, MDR_PLL_IN_HSI, fromLowerFreq);}
                          
__STATIC_INLINE 
MDR_CPU_SetClockResult  MDR_CPU_SetClock_HSI_PLL2(const MDR_CPU_PLL_CfgHSI  *cfgPLL_HSI, bool fromLowerFreq)
                         {return MDR_CPU_SetClock_PLL_srcHSI(MDR_CLOCK_PLL2, MAXCLK_PLL2, cfgPLL_HSI, MDR_PLL_IN_HSI, fromLowerFreq);}
                          

//  defaults from MDR_Conig
__STATIC_INLINE 
MDR_CPU_SetClockResult  MDR_CPU_SetClock_PLL_HSI(const MDR_CPU_PLL_CfgHSI  *cfgPLL_HSI, bool fromLowerFreq)
                         {return MDR_CPU_SetClock_PLL_srcHSI(MDR_PLL_Def, MDR_MAXCLK_SEL_Def, cfgPLL_HSI, MDR_PLL_IN_HSI, fromLowerFreq);}

                         
//-----------------------------------------------------------------------                         
//  Тактирование ядра от внешнего генератора HSЕ (1МГц - 30МГц) через PLL
                         
MDR_CPU_SetClockResult  MDR_CPU_SetClock_PLL_srcHSE(MDR_RST_PLL_Type *PLLx, MDR_RST_HSE_Type *HSEx, MDR_MAXCLK_SEL selMaxClk, 
  const MDR_CPU_PLL_CfgHSE  *cfgPLL_HSE, MDR_PLL_IN_SEL inpPll, bool fromLowerFreq);
                              
                              
// ---  HSE0 to PLL1, PLL2, PLL3  ---
                              
//  HSE0 to PLL0
__STATIC_INLINE 
MDR_CPU_SetClockResult MDR_CPU_SetClock_HSE0_PLL0(const MDR_CPU_PLL_CfgHSE  *cfgPLL_HSE, bool fromLowerFreq)
  {return MDR_CPU_SetClock_PLL_srcHSE(MDR_CLOCK_PLL0, MDR_CLOCK_HSE0, MAXCLK_PLL0, cfgPLL_HSE, MDR_PLL_IN_HSE0, fromLowerFreq);}
//  HSE0 to PLL1
__STATIC_INLINE 
MDR_CPU_SetClockResult MDR_CPU_SetClock_HSE0_PLL1(const MDR_CPU_PLL_CfgHSE  *cfgPLL_HSE, bool fromLowerFreq)
  {return MDR_CPU_SetClock_PLL_srcHSE(MDR_CLOCK_PLL1, MDR_CLOCK_HSE0, MAXCLK_PLL1, cfgPLL_HSE, MDR_PLL_IN_HSE0, fromLowerFreq);}

//  HSE0 to PLL2
__STATIC_INLINE 
MDR_CPU_SetClockResult MDR_CPU_SetClock_HSE0_PLL2(const MDR_CPU_PLL_CfgHSE  *cfgPLL_HSE, bool fromLowerFreq)
  {return MDR_CPU_SetClock_PLL_srcHSE(MDR_CLOCK_PLL2, MDR_CLOCK_HSE0, MAXCLK_PLL2, cfgPLL_HSE, MDR_PLL_IN_HSE0, fromLowerFreq);}
                                                            

//---  HSE1 to PLL1, PLL2, PLL3  ---
//  HSE1 to PLL0
__STATIC_INLINE 
MDR_CPU_SetClockResult MDR_CPU_SetClock_HSE1_PLL0(const MDR_CPU_PLL_CfgHSE  *cfgPLL_HSE, bool fromLowerFreq)
  {return MDR_CPU_SetClock_PLL_srcHSE(MDR_CLOCK_PLL0, MDR_CLOCK_HSE1, MAXCLK_PLL0, cfgPLL_HSE, MDR_PLL_IN_HSE1, fromLowerFreq);}
//  HSE1 to PLL1
__STATIC_INLINE 
MDR_CPU_SetClockResult MDR_CPU_SetClock_HSE1_PLL1(const MDR_CPU_PLL_CfgHSE  *cfgPLL_HSE, bool fromLowerFreq)
  {return MDR_CPU_SetClock_PLL_srcHSE(MDR_CLOCK_PLL1, MDR_CLOCK_HSE1, MAXCLK_PLL1, cfgPLL_HSE, MDR_PLL_IN_HSE1, fromLowerFreq);}

//  HSE1 to PLL2
__STATIC_INLINE 
MDR_CPU_SetClockResult MDR_CPU_SetClock_HSE1_PLL2(const MDR_CPU_PLL_CfgHSE  *cfgPLL_HSE, bool fromLowerFreq)
  {return MDR_CPU_SetClock_PLL_srcHSE(MDR_CLOCK_PLL2, MDR_CLOCK_HSE1, MAXCLK_PLL2, cfgPLL_HSE, MDR_PLL_IN_HSE1, fromLowerFreq);}
                                      
  
// --- defaults from MDR_Conig ---
__STATIC_INLINE 
MDR_CPU_SetClockResult MDR_CPU_SetClock_PLL_HSE(const MDR_CPU_PLL_CfgHSE  *cfgPLL_HSE, bool fromLowerFreq)
  {return MDR_CPU_SetClock_PLL_srcHSE(MDR_PLL_Def, MDR_HSE_Def, MDR_MAXCLK_SEL_Def, cfgPLL_HSE, MDR_PLL_IN_HSE_Def, fromLowerFreq);}

  
//------------------------------------------------------------------------------------------------------------------------  
//-------------------------   Эти же функции SetClock_... с параметрами по умолчанию из MDR_Config.h  ----------------------  
//------------------------------------------------------------------------------------------------------------------------
//  Reset Block
__STATIC_INLINE 
bool MDR_CLK_ResetBlock_def(bool fromLowerFreq)
{
  MDR_CPU_CfgHSI cfgHSI = MDR_CPU_CFG_HSI_DEF;  
  return MDR_CLK_ResetBlock(&cfgHSI, HSI_TIMEOUT, fromLowerFreq);  
}
  

//  LSI
__STATIC_INLINE 
MDR_CPU_SetClockResult  MDR_CPU_SetClock_LSI_def(void)
{ 
  MDR_CPU_CfgLSI cfgLSI = MDR_CPU_CFG_LSI_DEF;
  return MDR_CPU_SetClock_LSI(&cfgLSI, LSI_TIMEOUT);
}


//  LSE
__STATIC_INLINE 
MDR_CPU_SetClockResult  MDR_CPU_SetClock_LSE_Res_def(void)
{ 
  MDR_CPU_CfgLSE cfgLSE = MDR_CPU_CFG_LSE_RES_DEF;
  return MDR_CPU_SetClock_LSE(&cfgLSE, LSE_TIMEOUT);
}

__STATIC_INLINE 
MDR_CPU_SetClockResult  MDR_CPU_SetClock_LSE_Gen_def(void)
{ 
  MDR_CPU_CfgLSE cfgLSE = MDR_CPU_CFG_LSE_GEN_DEF;
  return MDR_CPU_SetClock_LSE(&cfgLSE, LSE_TIMEOUT);  
}


//  HSI
__STATIC_INLINE 
MDR_CPU_SetClockResult  MDR_CPU_SetClock_HSI_def(bool fromLowerFreq) 
{
  MDR_CPU_CfgHSI cfgHSI = MDR_CPU_CFG_HSI_DEF;
  return MDR_CPU_SetClock_HSI(&cfgHSI, HSI_TIMEOUT, fromLowerFreq);
}

__STATIC_INLINE 
MDR_CPU_SetClockResult  MDR_CPU_SetClock_HSIdiv2_def(bool fromLowerFreq) 
{
  MDR_CPU_CfgHSI cfgHSI = MDR_CPU_CFG_HSI_DIV2_DEF;
  return MDR_CPU_SetClock_HSI(&cfgHSI, HSI_TIMEOUT, fromLowerFreq);
}


//  HSE
__STATIC_INLINE 
MDR_CPU_SetClockResult  MDR_CPU_SetClock_HSE_def(MDR_CLK_Source freqSource, bool fromLowerFreq) 
{
  MDR_CPU_CfgHSE cfgHSE = MDR_CPU_CFG_HSE_SRC_DEF(freqSource);
    
  #if MDR_HSE_IND_Def == 0  
    return MDR_CPU_SetClock_HSE0(&cfgHSE, HSE_TIMEOUT, fromLowerFreq);  
  #else
    return MDR_CPU_SetClock_HSE1(&cfgHSE, HSE_TIMEOUT, fromLowerFreq);  
  #endif
}

__STATIC_INLINE
MDR_CPU_SetClockResult  MDR_CPU_SetClock_HSEdiv2_def(MDR_CLK_Source freqSource, bool fromLowerFreq) 
{
  MDR_CPU_CfgHSE cfgHSE = MDR_CPU_CFG_HSE_SRC_DIV_DEF(freqSource, true);
    
#if MDR_HSE_IND_Def == 0  
  return MDR_CPU_SetClock_HSE0(&cfgHSE, HSE_TIMEOUT, fromLowerFreq);  
#else
  return MDR_CPU_SetClock_HSE1(&cfgHSE, HSE_TIMEOUT, fromLowerFreq);  
#endif
}

#define MDR_CPU_SetClock_HSE_Res_def(fromLower)       MDR_CPU_SetClock_HSE_def(MDR_CLK_Resonator, (fromLower))
#define MDR_CPU_SetClock_HSE_Gen_def(fromLower)       MDR_CPU_SetClock_HSE_def(MDR_CLK_Generator, (fromLower))

#define MDR_CPU_SetClock_HSEdiv2_Res_def(fromLower)   MDR_CPU_SetClock_HSEdiv2_def(MDR_CLK_Resonator, (fromLower))
#define MDR_CPU_SetClock_HSEdiv2_Gen_def(fromLower)   MDR_CPU_SetClock_HSEdiv2_def(MDR_CLK_Generator, (fromLower))


//  HSI_PLL
#define MDR_CPU_SetClock_HSI_PLLx_def(pCfgPLL, pFreqSupp, fromLower, div2, setFunc)    MDR_CPU_PLL_CfgHSI cfgPLL_HSI = {          \
                                                                                   .freqTrim          = HSI_FREQ_TRIM,      \
                                                                                   .selDiv2           = div2,            \
                                                                                   .timeoutCycles_HSI = HSI_TIMEOUT,        \
                                                                                   .cfgPLL            = *pCfgPLL,           \
                                                                                   .timeoutCycles_PLL = PLL_TIMEOUT,        \
                                                                                   .freqSupp          = *pFreqSupp};        \
                                                                                 return setFunc(&cfgPLL_HSI, fromLower)

__STATIC_INLINE 
MDR_CPU_SetClockResult  MDR_CPU_SetClock_HSI_PLL0_def(MDR_CLK_CfgPLL *cfgPLL, MDR_CLK_FreqSupport *freqSupp, bool fromLowerFreq) 
{
  MDR_CPU_SetClock_HSI_PLLx_def(cfgPLL, freqSupp, fromLowerFreq, false, MDR_CPU_SetClock_HSI_PLL0);
}

__STATIC_INLINE 
MDR_CPU_SetClockResult  MDR_CPU_SetClock_HSI_PLL1_def(MDR_CLK_CfgPLL *cfgPLL, MDR_CLK_FreqSupport *freqSupp, bool fromLowerFreq) 
{
  MDR_CPU_SetClock_HSI_PLLx_def(cfgPLL, freqSupp, fromLowerFreq, false, MDR_CPU_SetClock_HSI_PLL1);
}
__STATIC_INLINE 
MDR_CPU_SetClockResult  MDR_CPU_SetClock_HSI_PLL2_def(MDR_CLK_CfgPLL *cfgPLL, MDR_CLK_FreqSupport *freqSupp, bool fromLowerFreq) 
{
  MDR_CPU_SetClock_HSI_PLLx_def(cfgPLL, freqSupp, fromLowerFreq, false, MDR_CPU_SetClock_HSI_PLL2);
}

//  HSI/2 PLL
__STATIC_INLINE 
MDR_CPU_SetClockResult  MDR_CPU_SetClock_HSIdiv2_PLL0_def(MDR_CLK_CfgPLL *cfgPLL, MDR_CLK_FreqSupport *freqSupp, bool fromLowerFreq) 
{
  MDR_CPU_SetClock_HSI_PLLx_def(cfgPLL, freqSupp, fromLowerFreq, true, MDR_CPU_SetClock_HSI_PLL0);
}
__STATIC_INLINE 
MDR_CPU_SetClockResult  MDR_CPU_SetClock_HSIdiv2_PLL1_def(MDR_CLK_CfgPLL *cfgPLL, MDR_CLK_FreqSupport *freqSupp, bool fromLowerFreq) 
{
  MDR_CPU_SetClock_HSI_PLLx_def(cfgPLL, freqSupp, fromLowerFreq, true, MDR_CPU_SetClock_HSI_PLL1);
}
__STATIC_INLINE 
MDR_CPU_SetClockResult  MDR_CPU_SetClock_HSIdiv2_PLL2_def(MDR_CLK_CfgPLL *cfgPLL, MDR_CLK_FreqSupport *freqSupp, bool fromLowerFreq) 
{
  MDR_CPU_SetClock_HSI_PLLx_def(cfgPLL, freqSupp, fromLowerFreq, true, MDR_CPU_SetClock_HSI_PLL2);
}
                                                                                 
#if MDR_PLL_IND_Def == 0
  #define MDR_CPU_SetClock_HSI_PLL_def        MDR_CPU_SetClock_HSI_PLL0_def
  #define MDR_CPU_SetClock_HSIdiv2_PLL_def    MDR_CPU_SetClock_HSIdiv2_PLL0_def
#elif MDR_PLL_IND_Def == 1
  #define MDR_CPU_SetClock_HSI_PLL_Def        MDR_CPU_SetClock_HSI_PLL1_Def
  #define MDR_CPU_SetClock_HSIdiv2_PLL_Def    MDR_CPU_SetClock_HSIdiv2_PLL1_Def
#else
  #define MDR_CPU_SetClock_HSI_PLL_Def        MDR_CPU_SetClock_HSI_PLL2_Def
  #define MDR_CPU_SetClock_HSIdiv2_PLL_Def    MDR_CPU_SetClock_HSIdiv2_PLL2_Def
#endif


//  HSE0 to PLLx
#define MDR_CPU_SetClock_HSEx_PLLx_Def(freqSrc, timeHSEx, pCfgPLL, pFreqSupp, fromLower, div2, setFunc)    MDR_CPU_PLL_CfgHSE cfgPLL_HSE = {         \
                                                                                                       .selDiv2           = div2,              \
                                                                                                       .freqSource        = freqSrc,           \
                                                                                                       .timeoutCycles_HSE = timeHSEx,          \
                                                                                                       .cfgPLL            = *pCfgPLL,          \
                                                                                                       .divMaxToCpu_0     = 0,                 \
                                                                                                       .timeoutCycles_PLL = PLL_TIMEOUT,       \
                                                                                                       .freqSupp          = *pFreqSupp};       \
                                                                                                     return setFunc(&cfgPLL_HSE, fromLower)

                                                                                                     
__STATIC_INLINE 
MDR_CPU_SetClockResult  MDR_CPU_SetClock_HSE0_PLL0_Def(MDR_CLK_Source freqSource, MDR_CLK_CfgPLL *cfgPLL, MDR_CLK_FreqSupport *freqSupp, bool fromLowerFreq) 
{
  MDR_CPU_SetClock_HSEx_PLLx_Def(freqSource, HSE0_TIMEOUT, cfgPLL, freqSupp, fromLowerFreq, false, MDR_CPU_SetClock_HSE0_PLL0);
}

__STATIC_INLINE 
MDR_CPU_SetClockResult  MDR_CPU_SetClock_HSE0_PLL1_Def(MDR_CLK_Source freqSource, MDR_CLK_CfgPLL *cfgPLL, MDR_CLK_FreqSupport *freqSupp, bool fromLowerFreq) 
{
  MDR_CPU_SetClock_HSEx_PLLx_Def(freqSource, HSE0_TIMEOUT, cfgPLL, freqSupp, fromLowerFreq, false, MDR_CPU_SetClock_HSE0_PLL1);
}

__STATIC_INLINE 
MDR_CPU_SetClockResult  MDR_CPU_SetClock_HSE0_PLL2_Def(MDR_CLK_Source freqSource, MDR_CLK_CfgPLL *cfgPLL, MDR_CLK_FreqSupport *freqSupp, bool fromLowerFreq) 
{
  MDR_CPU_SetClock_HSEx_PLLx_Def(freqSource, HSE0_TIMEOUT, cfgPLL, freqSupp, fromLowerFreq, false, MDR_CPU_SetClock_HSE0_PLL2);
}

//  HSE1 to PLLx
__STATIC_INLINE 
MDR_CPU_SetClockResult  MDR_CPU_SetClock_HSE1_PLL0_Def(MDR_CLK_Source freqSource, MDR_CLK_CfgPLL *cfgPLL, MDR_CLK_FreqSupport *freqSupp, bool fromLowerFreq) 
{
  MDR_CPU_SetClock_HSEx_PLLx_Def(freqSource, HSE1_TIMEOUT, cfgPLL, freqSupp, fromLowerFreq, false, MDR_CPU_SetClock_HSE1_PLL1);
}

__STATIC_INLINE 
MDR_CPU_SetClockResult  MDR_CPU_SetClock_HSE1_PLL1_Def(MDR_CLK_Source freqSource, MDR_CLK_CfgPLL *cfgPLL, MDR_CLK_FreqSupport *freqSupp, bool fromLowerFreq) 
{
  MDR_CPU_SetClock_HSEx_PLLx_Def(freqSource, HSE1_TIMEOUT, cfgPLL, freqSupp, fromLowerFreq, false, MDR_CPU_SetClock_HSE1_PLL1);
}

__STATIC_INLINE 
MDR_CPU_SetClockResult  MDR_CPU_SetClock_HSE1_PLL2_Def(MDR_CLK_Source freqSource, MDR_CLK_CfgPLL *cfgPLL, MDR_CLK_FreqSupport *freqSupp, bool fromLowerFreq) 
{
  MDR_CPU_SetClock_HSEx_PLLx_Def(freqSource, HSE1_TIMEOUT, cfgPLL, freqSupp, fromLowerFreq, false, MDR_CPU_SetClock_HSE1_PLL2);
}

//  HSE0/2 to PLL
__STATIC_INLINE 
MDR_CPU_SetClockResult  MDR_CPU_SetClock_HSE0div2_PLL0_Def(MDR_CLK_Source freqSource, MDR_CLK_CfgPLL *cfgPLL, MDR_CLK_FreqSupport *freqSupp, bool fromLowerFreq) 
{
  MDR_CPU_SetClock_HSEx_PLLx_Def(freqSource, HSE0_TIMEOUT, cfgPLL, freqSupp, fromLowerFreq, true, MDR_CPU_SetClock_HSE0_PLL0);
}

__STATIC_INLINE 
MDR_CPU_SetClockResult  MDR_CPU_SetClock_HSE0div2_PLL1_Def(MDR_CLK_Source freqSource, MDR_CLK_CfgPLL *cfgPLL, MDR_CLK_FreqSupport *freqSupp, bool fromLowerFreq) 
{
  MDR_CPU_SetClock_HSEx_PLLx_Def(freqSource, HSE0_TIMEOUT, cfgPLL, freqSupp, fromLowerFreq, true, MDR_CPU_SetClock_HSE0_PLL1);
}

__STATIC_INLINE 
MDR_CPU_SetClockResult  MDR_CPU_SetClock_HSE0div2_PLL2_Def(MDR_CLK_Source freqSource, MDR_CLK_CfgPLL *cfgPLL, MDR_CLK_FreqSupport *freqSupp, bool fromLowerFreq) 
{
  MDR_CPU_SetClock_HSEx_PLLx_Def(freqSource, HSE0_TIMEOUT, cfgPLL, freqSupp, fromLowerFreq, true, MDR_CPU_SetClock_HSE0_PLL2);
}

//  HSE1/2 to PLL
__STATIC_INLINE 
MDR_CPU_SetClockResult  MDR_CPU_SetClock_HSE1div2_PLL0_Def(MDR_CLK_Source freqSource, MDR_CLK_CfgPLL *cfgPLL, MDR_CLK_FreqSupport *freqSupp, bool fromLowerFreq) 
{
  MDR_CPU_SetClock_HSEx_PLLx_Def(freqSource, HSE1_TIMEOUT, cfgPLL, freqSupp, fromLowerFreq, true, MDR_CPU_SetClock_HSE1_PLL0);
}

__STATIC_INLINE 
MDR_CPU_SetClockResult  MDR_CPU_SetClock_HSE1div2_PLL1_Def(MDR_CLK_Source freqSource, MDR_CLK_CfgPLL *cfgPLL, MDR_CLK_FreqSupport *freqSupp, bool fromLowerFreq) 
{
  MDR_CPU_SetClock_HSEx_PLLx_Def(freqSource, HSE1_TIMEOUT, cfgPLL, freqSupp, fromLowerFreq, true, MDR_CPU_SetClock_HSE1_PLL1);
}

__STATIC_INLINE 
MDR_CPU_SetClockResult  MDR_CPU_SetClock_HSE1div2_PLL2_Def(MDR_CLK_Source freqSource, MDR_CLK_CfgPLL *cfgPLL, MDR_CLK_FreqSupport *freqSupp, bool fromLowerFreq) 
{
  MDR_CPU_SetClock_HSEx_PLLx_Def(freqSource, HSE1_TIMEOUT, cfgPLL, freqSupp, fromLowerFreq, true, MDR_CPU_SetClock_HSE1_PLL2);
}

                                                                                              
#if MDR_PLL_IND_Def == 0
  #if MDR_HSE_IND_Def == 0
    #define MDR_CPU_SetClock_HSE_Res_PLL_def(cfgPLL, freqSupp, fromLower)     MDR_CPU_SetClock_HSE0_PLL0_Def(MDR_CLK_Resonator, (cfgPLL), (freqSupp), (fromLower))
    #define MDR_CPU_SetClock_HSE_Gen_PLL_def(cfgPLL, freqSupp, fromLower)     MDR_CPU_SetClock_HSE0_PLL0_Def(MDR_CLK_Generator, (cfgPLL), (freqSupp), (fromLower))
    #define MDR_CPU_SetClock_HSEdiv2_Res_PLL_def(cfgPLL, freqSupp, fromLower) MDR_CPU_SetClock_HSE0div2_PLL0_Def(MDR_CLK_Resonator, (cfgPLL), (freqSupp), (fromLower))
    #define MDR_CPU_SetClock_HSEdiv2_Gen_PLL_def(cfgPLL, freqSupp, fromLower) MDR_CPU_SetClock_HSE0div2_PLL0_Def(MDR_CLK_Generator, (cfgPLL), (freqSupp), (fromLower))
  #else
    #define MDR_CPU_SetClock_HSE_Res_PLL_def(cfgPLL, freqSupp, fromLower)     MDR_CPU_SetClock_HSE1_PLL0_Def(MDR_CLK_Resonator, (cfgPLL), (freqSupp), (fromLower))
    #define MDR_CPU_SetClock_HSE_Gen_PLL_def(cfgPLL, freqSupp, fromLower)     MDR_CPU_SetClock_HSE1_PLL0_Def(MDR_CLK_Generator, (cfgPLL), (freqSupp), (fromLower))
    #define MDR_CPU_SetClock_HSEdiv2_Res_PLL_def(cfgPLL, freqSupp, fromLower) MDR_CPU_SetClock_HSE1div2_PLL0_Def(MDR_CLK_Resonator, (cfgPLL), (freqSupp), (fromLower))
    #define MDR_CPU_SetClock_HSEdiv2_Gen_PLL_def(cfgPLL, freqSupp, fromLower) MDR_CPU_SetClock_HSE1div2_PLL0_Def(MDR_CLK_Generator, (cfgPLL), (freqSupp), (fromLower))
  #endif
#elif MDR_PLL_IND_Def == 1
  #if MDR_HSE_IND_Def == 0
    #define MDR_CPU_SetClock_HSE_Res_PLL_def(cfgPLL, freqSupp, fromLower)     MDR_CPU_SetClock_HSE0_PLL1_Def(MDR_CLK_Resonator, (cfgPLL), (freqSupp), (fromLower))
    #define MDR_CPU_SetClock_HSE_Gen_PLL_def(cfgPLL, freqSupp, fromLower)     MDR_CPU_SetClock_HSE0_PLL1_Def(MDR_CLK_Generator, (cfgPLL), (freqSupp), (fromLower))
    #define MDR_CPU_SetClock_HSEdiv2_Res_PLL_def(cfgPLL, freqSupp, fromLower) MDR_CPU_SetClock_HSE0div2_PLL1_Def(MDR_CLK_Resonator, (cfgPLL), (freqSupp), (fromLower))
    #define MDR_CPU_SetClock_HSEdiv2_Gen_PLL_def(cfgPLL, freqSupp, fromLower) MDR_CPU_SetClock_HSE0div2_PLL1_Def(MDR_CLK_Generator, (cfgPLL), (freqSupp), (fromLower))
  #else
    #define MDR_CPU_SetClock_HSE_Res_PLL_def(cfgPLL, freqSupp, fromLower)     MDR_CPU_SetClock_HSE1_PLL1_Def(MDR_CLK_Resonator, (cfgPLL), (freqSupp), (fromLower))
    #define MDR_CPU_SetClock_HSE_Gen_PLL_def(cfgPLL, freqSupp, fromLower)     MDR_CPU_SetClock_HSE1_PLL1_Def(MDR_CLK_Generator, (cfgPLL), (freqSupp), (fromLower))
    #define MDR_CPU_SetClock_HSEdiv2_Res_PLL_def(cfgPLL, freqSupp, fromLower) MDR_CPU_SetClock_HSE1div2_PLL1_Def(MDR_CLK_Resonator, (cfgPLL), (freqSupp), (fromLower))
    #define MDR_CPU_SetClock_HSEdiv2_Gen_PLL_def(cfgPLL, freqSupp, fromLower) MDR_CPU_SetClock_HSE1div2_PLL1_Def(MDR_CLK_Generator, (cfgPLL), (freqSupp), (fromLower))
  #endif
#else
  #if MDR_HSE_IND_Def == 0
    #define MDR_CPU_SetClock_HSE_Res_PLL_def(cfgPLL, freqSupp, fromLower)     MDR_CPU_SetClock_HSE0_PLL2_Def(MDR_CLK_Resonator, (cfgPLL), (freqSupp), (fromLower))
    #define MDR_CPU_SetClock_HSE_Gen_PLL_def(cfgPLL, freqSupp, fromLower)     MDR_CPU_SetClock_HSE0_PLL2_Def(MDR_CLK_Generator, (cfgPLL), (freqSupp), (fromLower))
    #define MDR_CPU_SetClock_HSEdiv2_Res_PLL_def(cfgPLL, freqSupp, fromLower) MDR_CPU_SetClock_HSE0div2_PLL2_Def(MDR_CLK_Resonator, (cfgPLL), (freqSupp), (fromLower))
    #define MDR_CPU_SetClock_HSEdiv2_Gen_PLL_def(cfgPLL, freqSupp, fromLower) MDR_CPU_SetClock_HSE0div2_PLL2_Def(MDR_CLK_Generator, (cfgPLL), (freqSupp), (fromLower))
  #else
    #define MDR_CPU_SetClock_HSE_Res_PLL_def(cfgPLL, freqSupp, fromLower)     MDR_CPU_SetClock_HSE1_PLL2_Def(MDR_CLK_Resonator, (cfgPLL), (freqSupp), (fromLower))
    #define MDR_CPU_SetClock_HSE_Gen_PLL_def(cfgPLL, freqSupp, fromLower)     MDR_CPU_SetClock_HSE1_PLL2_Def(MDR_CLK_Generator, (cfgPLL), (freqSupp), (fromLower))
    #define MDR_CPU_SetClock_HSEdiv2_Res_PLL_def(cfgPLL, freqSupp, fromLower) MDR_CPU_SetClock_HSE1div2_PLL2_Def(MDR_CLK_Resonator, (cfgPLL), (freqSupp), (fromLower))
    #define MDR_CPU_SetClock_HSEdiv2_Gen_PLL_def(cfgPLL, freqSupp, fromLower) MDR_CPU_SetClock_HSE1div2_PLL2_Def(MDR_CLK_Generator, (cfgPLL), (freqSupp), (fromLower))
  #endif
#endif


//===============  Функции включения тактирования и подачи тактирования для блоков с BRG  ===============
typedef struct {
  // Clock Enable reg: PER_CLock
  volatile uint32_t* ClockEna_Addr;
  uint32_t           ClockEna_Mask;
  //  Clock Sync/Asunc control register. Like
  volatile uint32_t* ClockGate_Addr;
} MDR_PerClock_Cfg;

//  Включение тактирования на блок для доступа к регистрам
__STATIC_INLINE void MDR_PerClock_Enable (const MDR_PerClock_Cfg *pCfgClock) {REG32(pCfgClock->ClockEna_Addr) |= pCfgClock->ClockEna_Mask;}
__STATIC_INLINE void MDR_PerClock_Disable(const MDR_PerClock_Cfg *pCfgClock) {REG32(pCfgClock->ClockEna_Addr) &= ~pCfgClock->ClockEna_Mask;}

//  Выставление делителя и подача рабочей частоты Uart_Clock, SSP_Clock, Timer_Clock, и т.д.
__STATIC_INLINE void MDR_PerClock_GateOpen(const MDR_PerClock_Cfg *pCfgClock, MDR_Div128P clockBRG) 
  {  REG32(pCfgClock->ClockGate_Addr) = MDR_MaskClrSet(REG32(pCfgClock->ClockGate_Addr), MDR_PER_CLK_DIV_Msk, (uint32_t)clockBRG | MDR_PER_CLK_CLK_EN_Msk); }
  
  //  Аналогично MDR_PerClock_GateOpen но еще и с выбором источника частоты
__STATIC_INLINE void MDR_PerClock_GateOpenAsync(const MDR_PerClock_Cfg *pCfgClock, MDR_Div128P clockBRG, MDR_RST_ASYNC_IN_SEL selClockSrc) 
  {  
    REG32(pCfgClock->ClockGate_Addr) = MDR_MaskClrSet(REG32(pCfgClock->ClockGate_Addr), MDR_RST_ASYNC_CLK_CLEAR_ALL, 
                                       (uint32_t)clockBRG | MDR_PER_CLK_CLK_EN_Msk | VAL2FLD_Pos(selClockSrc, MDR_RST_ASYNC_CLK_SELECT_Pos)); 
  }

  //  Просто выбор частоты для асинхронного блока
__STATIC_INLINE void MDR_PerClock_SetAsyncSrc(const MDR_PerClock_Cfg *pCfgClock, MDR_RST_ASYNC_IN_SEL selClockSrc) 
  {  
    REG32(pCfgClock->ClockGate_Addr) = MDR_MaskClrSet(REG32(pCfgClock->ClockGate_Addr), MDR_RST_ASYNC_CLK_SELECT_Msk, 
                                                      VAL2FLD_Pos(selClockSrc, MDR_RST_ASYNC_CLK_SELECT_Pos)); 
  }  
  
  
  //  Отключение частоты Uart_Clock, SSP_Clock, Timer_Clock, и т.д.
__STATIC_INLINE void MDR_PerClock_GateClose(const MDR_PerClock_Cfg *pCfgClock) {REG32(pCfgClock->ClockGate_Addr) &= ~MDR_PER_CLK_CLK_EN_Msk;}


//  Выставление делителя входной частоты для получения UART_Clock, SSP_Clock, TIM_Clock, и т.д.
__STATIC_INLINE void MDR_PerClock_SetBRG(const MDR_PerClock_Cfg *pCfgClock, MDR_Div128P clockBRG) 
  { REG32(pCfgClock->ClockGate_Addr) = MDR_MaskClrSet(REG32(pCfgClock->ClockGate_Addr), MDR_PER_CLK_DIV_Msk, clockBRG); }

//  Подача на блок периферии частоты UART_Clock, SSP_Clock, TIM_Clock, и т.д.
__STATIC_INLINE void MDR_PerClock_SetGateOpen(const MDR_PerClock_Cfg *pCfgClock) { REG32(pCfgClock->ClockGate_Addr) |= MDR_PER_CLK_CLK_EN_Msk; }


#endif //MDR_RST_CLOCK_VE8x_H

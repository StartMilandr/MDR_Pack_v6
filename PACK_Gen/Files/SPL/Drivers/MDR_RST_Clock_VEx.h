#ifndef MDR_RST_CLOCK_VEx_H
#define MDR_RST_CLOCK_VEx_H

#include <MDR_Config.h>
#include <MDR_Types.h>
#include <MDR_Funcs.h>

//  Приведение имен к названию блока MDR_CLK_ххх
//        Подстройка частоты генераторов HSI и LSI
#define   MDR_CLK_HSI_TRIM       MDR_BKP_HSI_TRIM
#define   MDR_CLK_LSI_TRIM       MDR_BKP_LSI_TRIM
//        Стабилизация потребления в зависимости от частоты
#define   MDR_CLK_LDO_LowSRI     MDR_BKP_LOW_RI
//        Такты паузы ядра для доступа к данным EEPROM. 
//        EEPROM не работает быстрее чем 25МГц (18МГц). Считывается за раз четыре 32-разрядных слова.
#define   MDR_CLK_Delay_EEPROM   MDR_EEPROM_DELAY  


//  Типы истоников частоты для внешний генераторов HSE и LSE
typedef enum {
  MDR_CLK_Resonator,          //  ByPass Off
  MDR_CLK_Generator,          //  ByPass On    
} MDR_CLK_Source;  


//  Подавление warnings компилятора V6 о добавлении  "пустот" в структуры
#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wpadded"
#endif

  //  Подстройки питания и доступа к EEPROM под частоту тактирования
  typedef struct {
    MDR_CLK_Delay_EEPROM  delayAccessEEPROM;
    MDR_CLK_LDO_LowSRI    lowSRI;
  } MDR_CLK_FreqSupport; 

  #define MDR_CPU_FREQ_SUPP(delEE, sri)  {.delayAccessEEPROM = delEE, \
                                          .lowSRI = sri}
  
  //  Парамеры, необходимые для переключения CPU на тактирование от LSI
  typedef struct {
    MDR_CLK_LSI_TRIM    freqTrim;
    MDR_CLK_FreqSupport freqSupp;
  } MDR_CPU_CfgLSI;
  
  #define  MDR_CPU_CFG_LSI_DEF    { .freqTrim                   = LSI_FREQ_TRIM,    \
                                    .freqSupp.delayAccessEEPROM = LSI_DELAY_EEPROM, \
                                    .freqSupp.lowSRI            = LSI_LOW_SRI}
    
                                    
  //  Парамеры, необходимые для переключения CPU на тактирование от LSI
  typedef struct {
    MDR_CLK_Source      freqSource;
    MDR_CLK_FreqSupport freqSupp;
  } MDR_CPU_CfgLSE;

  #define  MDR_CPU_CFG_LSE_SRC_DEF(FrSrc)    {.freqSource        = FrSrc,      \
                                              .freqSupp.delayAccessEEPROM = LSE_DELAY_EEPROM, \
                                              .freqSupp.lowSRI            = LSE_LOW_SRI}

  #define  MDR_CPU_CFG_LSE_RES_DEF        MDR_CPU_CFG_LSE_SRC_DEF(MDR_CLK_Resonator)  
  #define  MDR_CPU_CFG_LSE_GEN_DEF        MDR_CPU_CFG_LSE_SRC_DEF(MDR_CLK_Generator)  
                                    
  //  Парамеры, необходимые для переключения CPU на тактирование от HSI
  typedef struct {
    MDR_CLK_HSI_TRIM    freqTrim;
    bool                selDiv2;
    MDR_Div256P         divC3; 
    MDR_CLK_FreqSupport freqSupp;
  } MDR_CPU_CfgHSI;

  #define  MDR_CPU_CFG_HSI_DV_DEF(div2)    { .freqTrim                   = HSI_FREQ_TRIM,    \
                                    .selDiv2                    = div2,           \
                                    .divC3                      = MDR_Div256P_div1,  \
                                    .freqSupp.delayAccessEEPROM = HSI_DELAY_EEPROM, \
                                    .freqSupp.lowSRI            = HSI_LOW_SRI}

  #define  MDR_CPU_CFG_HSI_DEF              MDR_CPU_CFG_HSI_DV_DEF(false)
  #define  MDR_CPU_CFG_HSI_DIV2_DEF         MDR_CPU_CFG_HSI_DV_DEF(true)
                                    
  typedef struct {
    MDR_CLK_HSI_TRIM    freqTrim;
    MDR_CLK_FreqSupport freqSupp;
  } MDR_CPU_CfgHSI_Dir;
                                    
  #define  MDR_CPU_CFG_HSI_DEF_DIR  { .freqTrim                   = HSI_FREQ_TRIM,    \
                                      .freqSupp.delayAccessEEPROM = HSI_DELAY_EEPROM, \
                                      .freqSupp.lowSRI            = HSI_LOW_SRI}

  
  //  Парамеры, необходимые для переключения CPU на тактирование от HSE
  typedef struct {
    MDR_CLK_Source        freqSource;
    bool                  selDiv2;    
    MDR_Div256P           divC3; 
    MDR_CLK_FreqSupport   freqSupp;
  } MDR_CPU_CfgHSE;
  
  #define  MDR_CPU_CFG_HSE_SRC_DIV_DEF(FrSrc, div2) {.freqSource                 = (FrSrc),           \
                                                     .selDiv2                    = div2,              \
                                                     .divC3                      = MDR_Div256P_div1,  \
                                                     .freqSupp.delayAccessEEPROM = HSE_DELAY_EEPROM,  \
                                                     .freqSupp.lowSRI            = HSE_LOW_SRI}       
  
  #define  MDR_CPU_CFG_HSE_SRC_DEF(FrSrc)             MDR_CPU_CFG_HSE_SRC_DIV_DEF(FrSrc, false)
  #define  MDR_CPU_CFG_HSE_DIV2_SRC_DEF(FrSrc)        MDR_CPU_CFG_HSE_SRC_DIV_DEF(FrSrc, true)
                                                     
  #define  MDR_CPU_CFG_HSE_RES_DEF                    MDR_CPU_CFG_HSE_SRC_DEF(MDR_CLK_Resonator)  
  #define  MDR_CPU_CFG_HSE_GEN_DEF                    MDR_CPU_CFG_HSE_SRC_DEF(MDR_CLK_Generator)  
  #define  MDR_CPU_CFG_HSE_DIV2_RES_DEF               MDR_CPU_CFG_HSE_DIV2_SRC_DEF(MDR_CLK_Resonator)  
  #define  MDR_CPU_CFG_HSE_DIV2_GEN_DEF               MDR_CPU_CFG_HSE_DIV2_SRC_DEF(MDR_CLK_Generator)    

  
  
  //  Парамеры, необходимые для переключения CPU на тактирование от HSI через PLL
  typedef struct {
    MDR_CLK_HSI_TRIM      freqTrim;
    bool                  selDiv2;
    uint32_t              timeoutCycles_HSI;
    MDR_MUL_x16           pllMul;
    uint32_t              timeoutCycles_PLL;
    MDR_Div256P           divC3;
    MDR_CLK_FreqSupport   freqSupp;
  } MDR_CPU_PLL_CfgHSI;  
  
  #define  MDR_CPU_CFG_PLL_HSI_DV_DEF(mul, delEE, lowRI, div2)    {.freqTrim                  = HSI_FREQ_TRIM,    \
                                                                   .selDiv2                   = div2,             \
                                                                   .timeoutCycles_HSI         = HSI_TIMEOUT,      \
                                                                   .pllMul                    = (mul),            \
                                                                   .timeoutCycles_PLL         = PLL_TIMEOUT,      \
                                                                   .divC3                     = MDR_Div256P_div1, \
                                                                   .freqSupp.delayAccessEEPROM = (delEE),         \
                                                                   .freqSupp.lowSRI            = (lowRI)}    

  #define  MDR_CPU_CFG_PLL_HSI_DEF(mul, delEE, lowRI)         MDR_CPU_CFG_PLL_HSI_DV_DEF(mul, delEE, lowRI, false)
  #define  MDR_CPU_CFG_PLL_HSI_DIV2_DEF(mul, delEE, lowRI)    MDR_CPU_CFG_PLL_HSI_DV_DEF(mul, delEE, lowRI, true)

  
  //  Парамеры, необходимые для переключения CPU на тактирование от HSE через PLL
  typedef struct {
    MDR_CLK_Source        freqSource;
    bool                  selDiv2;    
    uint32_t              timeoutCycles_HSE;
    MDR_MUL_x16           pllMul;
    uint32_t              timeoutCycles_PLL;
    MDR_Div256P           divC3;
    MDR_CLK_FreqSupport   freqSupp;    
  } MDR_CPU_PLL_CfgHSE;  
  
  #define  MDR_CPU_CFG_PLL_HSE_SRC_DV_DEF(src, mul, delEE, lowRI, div2)  {.freqSource               = (src),        \
                                                                          .selDiv2                  = div2,            \
                                                                          .timeoutCycles_HSE        = HSE_TIMEOUT,       \
                                                                          .pllMul                   = (mul),             \
                                                                          .timeoutCycles_PLL        = PLL_TIMEOUT,       \
                                                                          .divC3                    = MDR_Div256P_div1,  \
                                                                          .freqSupp.delayAccessEEPROM = (delEE),         \
                                                                          .freqSupp.lowSRI            = (lowRI)}

  #define  MDR_CPU_CFG_PLL_HSE_SRC_DEF(src, mul, delEE, lowRI)        MDR_CPU_CFG_PLL_HSE_SRC_DV_DEF(src, mul, delEE, lowRI, false)
  #define  MDR_CPU_CFG_PLL_HSE_DIV2_SRC_DEF(src, mul, delEE, lowRI)   MDR_CPU_CFG_PLL_HSE_SRC_DV_DEF(src, mul, delEE, lowRI, true)  

  #define  MDR_CPU_CFG_PLL_HSE_RES_DEF(mul, delEE, lowRI)          MDR_CPU_CFG_PLL_HSE_SRC_DEF(MDR_CLK_Resonator, mul, delEE, lowRI)
  #define  MDR_CPU_CFG_PLL_HSE_GEN_DEF(mul, delEE, lowRI)          MDR_CPU_CFG_PLL_HSE_SRC_DEF(MDR_CLK_Generator, mul, delEE, lowRI)
  #define  MDR_CPU_CFG_PLL_HSE_DIV2_RES_DEF(mul, delEE, lowRI)     MDR_CPU_CFG_PLL_HSE_DIV2_SRC_DEF(MDR_CLK_Resonator, mul, delEE, lowRI)
  #define  MDR_CPU_CFG_PLL_HSE_DIV2_GEN_DEF(mul, delEE, lowRI)     MDR_CPU_CFG_PLL_HSE_DIV2_SRC_DEF(MDR_CLK_Generator, mul, delEE, lowRI)  
  
#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic pop  
#endif  




//=================   Доступ к регистрам блока ===============

//  Включение тактирования к регистрам блоков RST и BKP. (В BKP управление генераторами)
//  Вызывать перед вызовом остальных функций работы с блоком.
__STATIC_INLINE void MDR_CLK_Enable_RST_BPK(void)  {MDR_CLOCK->MDR_CLK_EN_REG_BKP |= MDR_CLK_EN_BIT_BKP;
                                                    MDR_CLOCK->MDR_CLK_EN_REG_RST |= MDR_CLK_EN_BIT_RST;}

//  Тактирование блоков RST и BKP можно выключить после работы с блоком, можно и не отключать:
//  Отключение доступа к регистрам блока RST
__STATIC_INLINE void MDR_CLK_Disable_RST(void) {MDR_CLOCK->MDR_CLK_EN_REG_RST &= ~MDR_CLK_EN_BIT_RST;}
//  Отключение доступа к регистрам блока BKP
__STATIC_INLINE void MDR_CLK_Disable_BKP(void) {MDR_CLOCK->MDR_CLK_EN_REG_BKP &= ~MDR_CLK_EN_BIT_BKP;}


//=================   Сброс блока и чтение текущей частоты CPU ==============
//  Сброс блока тактирования RST_CLOCK в начальное состояние, тактирование от HSI.
//  В fromLowerFreq указать с большей или меньшей частоты происходит сброс. 
//  fromLowerFreq влияет на очередность выставления параметров MDR_CLK_FreqSupport - до или после переключения частоты.
bool MDR_CLK_ResetBlock(const MDR_CPU_CfgHSI_Dir *cfgHSI, uint32_t timeoutCycles, bool fromLowerFreq);

//  Получение текущей частоты работы ядра с опросом регистров или из глобальной переменной CMSIS - SystemCoreClock
//  Желательно вызывать после смены частоты, тогда впоследствии можно вызывать без флага обновления
uint32_t MDR_CPU_GetFreqHz(bool doUpdate);




//=====================================================================
//======================   Включение генераторов ======================
//=====================================================================

// ----- LSE ~32KHz -----
//  Включение/Выключение генератора LSE, опрос готовности.
__STATIC_INLINE void MDR_LSE_Enable(MDR_CLK_Source freqSource)
{
  if (freqSource == MDR_CLK_Resonator)
    MDR_BKP->REG_0F = MDR_MaskClrSet(MDR_BKP->REG_0F, MDR_BKP_REG_0F_LSE_BYP_Msk, MDR_BKP_REG_0F_LSE_ON_Msk);
  else
    MDR_BKP->REG_0F |= MDR_BKP_REG_0F_LSE_BYP_Msk | MDR_BKP_REG_0F_LSE_ON_Msk;                  
}

__STATIC_INLINE void MDR_LSE_Disable(void) {MDR_BKP->REG_0F &= ~MDR_BKP_REG_0F_LSE_ON_Msk;}

                bool MDR_LSE_GetReady(void);

//  Включает генератор LSE с ожиданием готовности LSE_Ready. Возвращает LSE_Ready.
//  Параметры MDR_CLK_FreqSupport выставляются по умолчанию, переход с большей частоты.
__STATIC_INLINE bool MDR_LSE_EnableAndWaitReady(MDR_CLK_Source freqSource, uint32_t timeoutCycles)
                                               {MDR_LSE_Enable(freqSource);
                                                return WaitCondition(timeoutCycles, MDR_LSE_GetReady);}


// ----- LSI ~40KHz -----
//  Включение/Выключение генератора LSI, опрос готовности.     
__STATIC_INLINE void MDR_LSI_Enable(void)  {MDR_BKP->REG_0F |=  MDR_BKP_REG_0F_LSI_ON_Msk;}
__STATIC_INLINE void MDR_LSI_Disable(void) {MDR_BKP->REG_0F &= ~MDR_BKP_REG_0F_LSI_ON_Msk;}
                bool MDR_LSI_GetReady(void);
                                                
__STATIC_INLINE void MDR_LSI_EnableAndTrim(MDR_CLK_LSI_TRIM freqTrim)
{ MDR_BKP->REG_0F = MDR_MaskClrSet(MDR_BKP->REG_0F, MDR_BKP_REG_0F_LSI_TRIM_Msk, MDR_BKP_REG_0F_LSI_ON_Msk | VAL2FLD_Pos(freqTrim, MDR_BKP_REG_0F_LSI_TRIM_Pos)); }

//  Включает генератор LSE с ожиданием готовности LSE_Ready. Возвращает LSE_Ready.
//  Параметры MDR_CLK_FreqSupport выставляются по умолчанию, переход с большей частоты.
__STATIC_INLINE bool MDR_LSI_EnableAndWaitReady(MDR_CLK_LSI_TRIM freqTrim, uint32_t timeoutCycles)
                                              { MDR_LSI_EnableAndTrim(freqTrim);
                                                return WaitCondition(timeoutCycles, MDR_LSI_GetReady); }


// ----- HSI ~8MHz -----
//  Включение/Выключение генератора HSI, опрос готовности.     
__STATIC_INLINE void MDR_HSI_EnableAndTrim(MDR_CLK_HSI_TRIM freqTrim) 
{ MDR_BKP->REG_0F = MDR_MaskClrSet(MDR_BKP->REG_0F, MDR_BKP_REG_0F_HSI_TRIM_Msk, MDR_BKP_REG_0F_HSI_ON_Msk | VAL2FLD_Pos(freqTrim, MDR_BKP_REG_0F_HSI_TRIM_Pos)); }
  
__STATIC_INLINE void MDR_HSI_Enable (void) {MDR_BKP->REG_0F |=  MDR_BKP_REG_0F_HSI_ON_Msk;}
__STATIC_INLINE void MDR_HSI_Disable(void) {MDR_BKP->REG_0F &= ~MDR_BKP_REG_0F_HSI_ON_Msk;}

                bool MDR_HSI_GetReady(void);

//  Включает генератор HSI с ожиданием готовности HSI_Ready. Возвращает HSI_Ready.
__STATIC_INLINE bool MDR_HSI_EnableAndWaitReady(MDR_CLK_HSI_TRIM freqTrim, uint32_t timeoutCycles)
                                                { MDR_HSI_EnableAndTrim(freqTrim);
                                                  return WaitCondition(timeoutCycles, MDR_HSI_GetReady); }

                                                  
// ----- HSE 2MHz .. 16MHz-----
__STATIC_INLINE void MDR_HSE_Enable(MDR_CLK_Source freqSource) 
{
  if (freqSource == MDR_CLK_Resonator)
    MDR_CLOCK->HS_CONTROL = MDR_MaskClrSet(MDR_CLOCK->HS_CONTROL, MDR_RST_HS__HSE_BYP_Msk, MDR_RST_HS__HSE_ON_Msk);
  else
    MDR_CLOCK->HS_CONTROL |= MDR_RST_HS__HSE_BYP_Msk | MDR_RST_HS__HSE_ON_Msk;  
}

__STATIC_INLINE void MDR_HSE_Disable(void) {MDR_CLOCK->HS_CONTROL &= ~MDR_RST_HS__HSE_ON_Msk;}

                bool MDR_HSE_GetReady(void);

//  Включает генератор HSE с ожиданием готовности HSE_Ready. Возвращает HSE_Ready.
__STATIC_INLINE bool MDR_HSE_EnableAndWaitReady(MDR_CLK_Source freqSource, uint32_t timeoutCycles)
                                                { MDR_HSE_Enable(freqSource);
                                                  return WaitCondition(timeoutCycles, MDR_HSE_GetReady); }


//=============   Включение PLL ==============
                void MDR_PLL_Enable(MDR_MUL_x16 pllMul);
                bool MDR_PLL_GetReady(void);  
__STATIC_INLINE void MDR_PLL_Disable(void) {MDR_CLOCK->PLL_CONTROL &= ~MDR_RST_PLL__CPU_ON_Msk;}

//  Включение PLL с ожиданием готовности
__STATIC_INLINE bool MDR_PLL_EnableAndWaitReady(MDR_MUL_x16 pllMul, uint32_t timeoutCycles)
                                               { MDR_PLL_Enable(pllMul);
                                                 return WaitCondition(timeoutCycles, MDR_PLL_GetReady); }

  
//=============   Настройка HSE2 ==============  
#ifdef MDR_EXIST_HSE2
                                                  
  __STATIC_INLINE void MDR_HSE2_Enable(MDR_CLK_Source freqSource)
    {
      if (freqSource == MDR_CLK_Resonator)
        MDR_CLOCK->HS_CONTROL = MDR_MaskClrSet(MDR_CLOCK->HS_CONTROL, MDR_RST_HS__HSE2_BYP_Msk, MDR_RST_HS__HSE2_ON_Msk);
      else
        MDR_CLOCK->HS_CONTROL |= MDR_RST_HS__HSE2_BYP_Msk | MDR_RST_HS__HSE2_ON_Msk;  
    }
    
  __STATIC_INLINE void MDR_HSE2_Disable(void) {MDR_CLOCK->HS_CONTROL &= ~MDR_RST_HS__HSE2_ON_Msk;}
    
  bool MDR_HSE2_GetReady(void);
                                                  
//  Включает генератор HSE2 с ожиданием готовности HSE2_Ready. Возвращает HSE2_Ready.
__STATIC_INLINE  bool MDR_HSE2_EnableAndWaitReady(MDR_CLK_Source freqSource, uint32_t timeoutCycles)
                                                { MDR_HSE2_Enable(freqSource);
                                                  return WaitCondition(timeoutCycles, MDR_HSE2_GetReady); }
#endif


//==============================================================================
//=======     Подстройка питания и временных параметров под частоту   ==========
//==============================================================================
                                                 
//  Рассчет задержки доступа к EEPROM от частоты CPU
MDR_CLK_Delay_EEPROM  MDR_FreqCPU_ToDelayEEPROM(uint32_t CPU_FregHz);
//  Рассчет подстройка LDO от частоты
MDR_CLK_LDO_LowSRI    MDR_FreqCPU_ToLowSRI(uint32_t CPU_FregHz);
  
//  Применение параметров в микроконтроллер
void MDR_CLK_ApplyFreqSupport_LDO(MDR_CLK_LDO_LowSRI lowSRI);
void MDR_CLK_ApplyFreqSupport_EEPROM(MDR_CLK_Delay_EEPROM delayEEPROM);

__STATIC_INLINE void MDR_CPU_ApplyFreqSupportF(MDR_CLK_LDO_LowSRI lowRI, MDR_CLK_Delay_EEPROM delayEEPROM)
{
  MDR_CLK_ApplyFreqSupport_LDO(lowRI);
  MDR_CLK_ApplyFreqSupport_EEPROM(delayEEPROM);
}

__STATIC_INLINE void MDR_CPU_ApplyFreqSupport(const MDR_CLK_FreqSupport *freqSupp)
{
  MDR_CLK_ApplyFreqSupport_LDO(freqSupp->lowSRI);
  MDR_CLK_ApplyFreqSupport_EEPROM(freqSupp->delayAccessEEPROM);
}

  
//==============================================================================
//=============     Инициализация тактирования CPU "под ключ"   ================
//==============================================================================
  
//  Необходимо вызвать MDR_CLK_Enable_RST_BPK для включения тактирования.
//  Далее функция настроит источник частоты и переведет на него CPU
//  Нельзя настраивать частоту на CPU_C3 с которой в текущий момент осуществляется тактирование.
//  Функция вернет в этом случае MDR_SET_CLOCK_ERR__SRC_USING.
//  Необходимо предварительно переключиться на другую частоту.
//  Например, при перестройке HSE и PLL, необходимо с HSE временно переключиться на HSI, 
//  а после окончания настройки HSE_PLL, переключитья на HSE_PLL
//  Параметры потребления перед переключением должны быть выставлены для большей частоты (новая vs текущая частота), 
//  это задается параметром fromLowerFreq.

typedef enum {
  MDR_SET_CLOCK_OK,
  MDR_SET_CLOCK_ERR__GEN_NotReady,
  MDR_SET_CLOCK_ERR__SRC_USING,
  MDR_SET_CLOCK_ERR__PLL_NotReady,    
  MDR_SET_CLOCK_ERR__Undef,    
} MDR_CPU_SetClockResult;


//  Тактирование ядра от внутреннего генератора LSI, ~40КГц
MDR_CPU_SetClockResult MDR_CPU_SetClock_LSI(const MDR_CPU_CfgLSI *cfgLSI, uint32_t timeoutCycles);

//  Тактирование ядра от внешнего генератора LSE, частота задается в MDR_Config LSE_FREQ_HZ ~32KHz
MDR_CPU_SetClockResult  MDR_CPU_SetClock_LSE(const MDR_CPU_CfgLSE *cfgLSE, uint32_t timeoutCycles);

//  Тактирование ядра от внутреннего генератора HSI, ~8МГц (6МГц .. 10МГц), напрямую с MUX_HCLK
MDR_CPU_SetClockResult MDR_CPU_SetClock_HSI_Dir(const MDR_CPU_CfgHSI_Dir *cfgHSI_d, uint32_t timeoutCycles, bool fromLowerFreq);


//  Тактирование ядра от внутреннего генератора HSI или HSI/2 от мультиплексора CPU_C1
//  Предварительно необходимо переключиться с CPU_C3 на другой источник - HSI.
MDR_CPU_SetClockResult MDR_CPU_SetClock_HSI(const MDR_CPU_CfgHSI *cfgHSI, uint32_t timeoutCycles, bool fromLowerFreq);

                            
//  Тактирование ядра от внешнего резонатора или генератора HSE или HSE/2 от мультиплексора CPU_C1
MDR_CPU_SetClockResult  MDR_CPU_SetClock_HSE(const MDR_CPU_CfgHSE *cfgHSE, uint32_t timeoutCycles, bool fromLowerFreq);
                                                        

//  Тактирование ядра от внутреннего генератора HSI через PLL, ~8МГц (6МГц .. 10МГц)
MDR_CPU_SetClockResult  MDR_CPU_SetClock_PLL_HSI(const MDR_CPU_PLL_CfgHSI *cfgPLL_HSI, bool fromLowerFreq);

                    

//  Тактирование ядра от внешнего генератора HSE через PLL 
MDR_CPU_SetClockResult  MDR_CPU_SetClock_PLL_HSE(const MDR_CPU_PLL_CfgHSE  *cfgPLL_HSE, bool fromLowerFreq);
                            
                           
  


//===============  Функции с параметрами по умолчанию из MDR_Config.h,  ===============
//===============  Файл MDR_ConfigVExx.h модифицируется пользователем под проект и плату  =========

__STATIC_INLINE
bool MDR_CLK_ResetBlock_def(bool fromLowerFreq) 
{
  MDR_CPU_CfgHSI_Dir cfgHSI = MDR_CPU_CFG_HSI_DEF_DIR;
  return MDR_CLK_ResetBlock(&cfgHSI, HSI_TIMEOUT, fromLowerFreq);
}

//  LSI
__STATIC_INLINE
MDR_CPU_SetClockResult  MDR_CPU_SetClock_LSI_def(void) 
{ 
  MDR_CPU_CfgLSI cfgLSI = MDR_CPU_CFG_LSI_DEF;
  return  MDR_CPU_SetClock_LSI(&cfgLSI, LSI_TIMEOUT);
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
MDR_CPU_SetClockResult  MDR_CPU_SetClock_HSI_Dir_def(bool fromLowerFreq) 
{
  MDR_CPU_CfgHSI_Dir cfgHSI = MDR_CPU_CFG_HSI_DEF_DIR;
  return MDR_CPU_SetClock_HSI_Dir(&cfgHSI, HSI_TIMEOUT, fromLowerFreq);
}
  
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
  return MDR_CPU_SetClock_HSE(&cfgHSE, HSE_TIMEOUT, fromLowerFreq);
}

__STATIC_INLINE
MDR_CPU_SetClockResult  MDR_CPU_SetClock_HSEdiv2_def(MDR_CLK_Source freqSource, bool fromLowerFreq)
{
  MDR_CPU_CfgHSE cfgHSE = MDR_CPU_CFG_HSE_SRC_DIV_DEF(freqSource, true);
  return MDR_CPU_SetClock_HSE(&cfgHSE, HSE_TIMEOUT, fromLowerFreq);
}

#define MDR_CPU_SetClock_HSE_Res_def(fromLower)       MDR_CPU_SetClock_HSE_def(MDR_CLK_Resonator, (fromLower))
#define MDR_CPU_SetClock_HSE_Gen_def(fromLower)       MDR_CPU_SetClock_HSE_def(MDR_CLK_Generator, (fromLower))

#define MDR_CPU_SetClock_HSEdiv2_Res_def(fromLower)   MDR_CPU_SetClock_HSEdiv2_def(MDR_CLK_Resonator, (fromLower))
#define MDR_CPU_SetClock_HSEdiv2_Gen_def(fromLower)   MDR_CPU_SetClock_HSEdiv2_def(MDR_CLK_Generator, (fromLower))


//  HSI_PLL
__STATIC_INLINE
MDR_CPU_SetClockResult  MDR_CPU_SetClock_PLL_HSI_def(MDR_MUL_x16 pll_Mul, MDR_CLK_Delay_EEPROM  delayAccessEEPROM, MDR_CLK_LDO_LowSRI lowSRI, bool fromLowerFreq)
{
  MDR_CPU_PLL_CfgHSI cfgPLL_HSI = MDR_CPU_CFG_PLL_HSI_DEF(pll_Mul, delayAccessEEPROM, lowSRI);
  return MDR_CPU_SetClock_PLL_HSI(&cfgPLL_HSI, fromLowerFreq);
}

__STATIC_INLINE
MDR_CPU_SetClockResult  MDR_CPU_SetClock_PLL_HSIdiv2_def(MDR_MUL_x16 pll_Mul, MDR_CLK_Delay_EEPROM  delayAccessEEPROM, MDR_CLK_LDO_LowSRI lowSRI, bool fromLowerFreq)
{
  MDR_CPU_PLL_CfgHSI cfgPLL_HSI = MDR_CPU_CFG_PLL_HSI_DIV2_DEF(pll_Mul, delayAccessEEPROM, lowSRI);
  return MDR_CPU_SetClock_PLL_HSI(&cfgPLL_HSI, fromLowerFreq);
}


//  HSE_PLL
__STATIC_INLINE
MDR_CPU_SetClockResult  MDR_CPU_SetClock_PLL_HSE_def(MDR_CLK_Source freqSource, MDR_MUL_x16 pll_Mul, 
  MDR_CLK_Delay_EEPROM  delayAccessEEPROM, MDR_CLK_LDO_LowSRI lowSRI, bool fromLowerFreq)
{
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDR_CPU_CFG_PLL_HSE_SRC_DEF(freqSource, pll_Mul, delayAccessEEPROM, lowSRI);  
  return MDR_CPU_SetClock_PLL_HSE(&cfgPLL_HSE, fromLowerFreq);
}

__STATIC_INLINE
MDR_CPU_SetClockResult  MDR_CPU_SetClock_PLL_HSEdiv2_def(MDR_CLK_Source freqSource, MDR_MUL_x16 pll_Mul, 
  MDR_CLK_Delay_EEPROM  delayAccessEEPROM, MDR_CLK_LDO_LowSRI lowSRI, bool fromLowerFreq)
{
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDR_CPU_CFG_PLL_HSE_DIV2_SRC_DEF(freqSource, pll_Mul, delayAccessEEPROM, lowSRI);  
  return MDR_CPU_SetClock_PLL_HSE(&cfgPLL_HSE, fromLowerFreq);
}

#define MDR_CPU_SetClock_HSE_Res_PLL_def(mul, freqSupp, fromLower)     MDR_CPU_SetClock_PLL_HSE_def(MDR_CLK_Resonator, (mul), (freqSupp), (fromLower))
#define MDR_CPU_SetClock_HSE_Gen_PLL_def(mul, freqSupp, fromLower)     MDR_CPU_SetClock_PLL_HSE_def(MDR_CLK_Generator, (mul), (freqSupp), (fromLower))
#define MDR_CPU_SetClock_HSEdiv2_Res_PLL_def(mul, freqSupp, fromLower) MDR_CPU_SetClock_PLL_HSEdiv2_def(MDR_CLK_Resonator, (mul), (freqSupp), (fromLower))
#define MDR_CPU_SetClock_HSEdiv2_Gen_PLL_def(mul, freqSupp, fromLower) MDR_CPU_SetClock_PLL_HSEdiv2_def(MDR_CLK_Generator, (mul), (freqSupp), (fromLower))



//__STATIC_INLINE
//MDR_CPU_SetClockResult  MDR_CPU_SetClock_HSE_Res_PLL_def(MDR_MUL_x16 pll_Mul, MDR_CLK_Delay_EEPROM  delayAccessEEPROM, MDR_CLK_LDO_LowSRI lowSRI)
//                                                        { return MDR_CPU_SetClock_PLL_srcHSE_def(MDR_CLK_Resonator, pll_Mul, delayAccessEEPROM, lowSRI, MDR_Off); }
//__STATIC_INLINE                                                        
//MDR_CPU_SetClockResult  MDR_CPU_SetClock_HSE_Gen_PLL_def(MDR_MUL_x16 pll_Mul, MDR_CLK_Delay_EEPROM  delayAccessEEPROM, MDR_CLK_LDO_LowSRI lowSRI)
//                                                        { return MDR_CPU_SetClock_PLL_srcHSE_def(MDR_CLK_Generator, pll_Mul, delayAccessEEPROM, lowSRI, MDR_Off); }
//__STATIC_INLINE                                                        
//MDR_CPU_SetClockResult  MDR_CPU_SetClock_HSEdiv2_Res_PLL_def(MDR_MUL_x16 pll_Mul, MDR_CLK_Delay_EEPROM  delayAccessEEPROM, MDR_CLK_LDO_LowSRI lowSRI)
//                                                        { return MDR_CPU_SetClock_PLL_srcHSE_def(MDR_CLK_Resonator, pll_Mul, delayAccessEEPROM, lowSRI, MDR_On); }
//__STATIC_INLINE                                                        
//MDR_CPU_SetClockResult  MDR_CPU_SetClock_HSEdiv2_Gen_PLL_def(MDR_MUL_x16 pll_Mul, MDR_CLK_Delay_EEPROM  delayAccessEEPROM, MDR_CLK_LDO_LowSRI lowSRI)
//                                                        { return MDR_CPU_SetClock_PLL_srcHSE_def(MDR_CLK_Generator, pll_Mul, delayAccessEEPROM, lowSRI, MDR_On); }



//===============  Функции включения тактирования и подачи тактирования для блоков с BRG  ===============
typedef struct {
  // Clock Enable reg: PER_CLock
  volatile uint32_t* ClockEna_Addr;
  uint32_t           ClockEna_Mask;
  //  Clock On and BRG regs: Uart_Clock, SSP_Clock, Timer_Clock
  volatile uint32_t* ClockGate_Addr;
  uint32_t           ClockGate_ClockOn_Msk;
  uint32_t           ClockGate_BRG_Pos;
} MDR_PerClock_Cfg;

//  Включение тактирования на блок для доступа к регистрам
__STATIC_INLINE void MDR_PerClock_Enable (const MDR_PerClock_Cfg *pCfgClock) {REG32(pCfgClock->ClockEna_Addr) |= pCfgClock->ClockEna_Mask;}
__STATIC_INLINE void MDR_PerClock_Disable(const MDR_PerClock_Cfg *pCfgClock) {REG32(pCfgClock->ClockEna_Addr) &= ~pCfgClock->ClockEna_Mask;}

//  Подача рабочей частоты Uart_Clock, SSP_Clock, Timer_Clock
__STATIC_INLINE void MDR_PerClock_GateOpen (const MDR_PerClock_Cfg *pCfgClock, MDR_Div128P clockBRG)
  { REG32(pCfgClock->ClockGate_Addr) = MDR_MaskClrSet(REG32(pCfgClock->ClockGate_Addr), 
                                                            MDR_BRG_DIV_128_CLR << pCfgClock->ClockGate_BRG_Pos, 
                                                            ((uint32_t)clockBRG << pCfgClock->ClockGate_BRG_Pos) | pCfgClock->ClockGate_ClockOn_Msk); } 
  

__STATIC_INLINE void MDR_PerClock_GateClose(const MDR_PerClock_Cfg *pCfgClock) {REG32(pCfgClock->ClockGate_Addr) &= ~pCfgClock->ClockGate_ClockOn_Msk;}

__STATIC_INLINE void MDR_PerClock_SetBRG(const MDR_PerClock_Cfg *pCfgClock, MDR_Div128P clockBRG)
  { REG32(pCfgClock->ClockGate_Addr) = MDR_MaskClrSet(REG32(pCfgClock->ClockGate_Addr), 
                                                      MDR_BRG_DIV_128_CLR << pCfgClock->ClockGate_BRG_Pos, 
                                                      ((uint32_t)clockBRG << pCfgClock->ClockGate_BRG_Pos)); }
                
__STATIC_INLINE void MDR_PerClock_SetGateOpen(const MDR_PerClock_Cfg *pCfgClock) {REG32(pCfgClock->ClockGate_Addr) |= pCfgClock->ClockGate_ClockOn_Msk;}





#endif //MDR_RST_CLOCK_VEx_H

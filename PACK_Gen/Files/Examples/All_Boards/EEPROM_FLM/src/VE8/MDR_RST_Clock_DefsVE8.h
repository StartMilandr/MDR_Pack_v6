#ifndef _MDR_RST_CLOCK_DefsVE8_H
#define _MDR_RST_CLOCK_DefsVE8_H

#include <MDR_Config.h>

//  Приведение имен к названию блока MDR_CLK_ххх
//        Подстройка частоты генераторов HSI и LSI
#define   MDR_CLK_HSI_TRIM       uint8_t
#define   MDR_CLK_LSI_TRIM       MDR_BKP_REG63_LSI_Trim
//        Стабилизация потребления в зависимости от частоты
#define   MDR_CLK_LDO_LowSRI    MDR_BKP_LDO_SRILow
//        Такты паузы ядра для доступа к памяти OTP.
#define   MDR_CLK_Delay_OTP     MDR_OTP_Delay  


//  Типы истоников частоты для внешний генераторов HSE и LSE
typedef enum {
  MDR_CLK_Resonator,          //  ByPass Off
  MDR_CLK_Generator,          //  ByPass On
  MDR_CLK_GeneratorFilterEn,  //  ByPass On + InpFilter
} MDR_CLK_Source;

typedef enum {
    MDR_PLL_DV_div1 = 0,
    MDR_PLL_DV_div2 = 1,
} MDR_PLL_DV_Div;


//  ============  Структуры задания конфигурации для переключения CPU на частоты  =========
//  Подавление warnings компилятора V6 о добавлении  "пустот" в структуры
#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wpadded"
#endif

  //  Подстройки питания и доступа к OTP под частоту тактирования
  typedef struct {
    MDR_CLK_Delay_OTP   delayAccessOTP;
    MDR_CLK_LDO_LowSRI  lowSRI;
  } MDR_CLK_FreqSupport;

  #define  MDR_CPU_FREQ_SUPP(del, sri)    {.delayAccessOTP = del, \
                                           .lowSRI         = sri}
  
  //  Парамеры, необходимые для переключения CPU на тактирование от LSI
  typedef struct {
    MDR_CLK_LSI_TRIM    freqTrim;
    uint16_t            divMaxToCpu_0;
    MDR_CLK_FreqSupport freqSupp;
  } MDR_CPU_CfgLSI;
  
  #define  MDR_CPU_CFG_LSI_DEF     {.freqTrim                = LSI_FREQ_TRIM,   \
                                    .divMaxToCpu_0           = 0,               \
                                    .freqSupp.delayAccessOTP = LSI_OTP_DELAY,   \
                                    .freqSupp.lowSRI         = LSI_LOW_SRI}     

  //  Парамеры, необходимые для переключения CPU на тактирование от LSE
  typedef struct {
    MDR_CLK_Source      freqSource;
    uint16_t            divMaxToCpu_0;
    MDR_CLK_FreqSupport freqSupp;
  } MDR_CPU_CfgLSE;
  
  #define  MDR_CPU_CFG_LSE_SRC_DEF(FrSrc)    {.freqSource              = FrSrc,           \
                                              .divMaxToCpu_0           = 0,               \
                                              .freqSupp.delayAccessOTP = LSE_OTP_DELAY,   \
                                              .freqSupp.lowSRI         = LSE_LOW_SRI}     
  
  #define  MDR_CPU_CFG_LSE_RES_DEF        MDR_CPU_CFG_LSE_SRC_DEF(MDR_CLK_Resonator)  
  #define  MDR_CPU_CFG_LSE_GEN_DEF        MDR_CPU_CFG_LSE_SRC_DEF(MDR_CLK_Generator)  

                                              
                                              
  //  Парамеры, необходимые для переключения CPU на тактирование от HSE
  typedef struct {
    MDR_CLK_HSI_TRIM      freqTrim;
    bool                  selDiv2;
    uint16_t              divMaxToCpu_0;
    MDR_CLK_FreqSupport   freqSupp;
  } MDR_CPU_CfgHSI;
  
  #define  MDR_CPU_CFG_HSI_DV_DEF(trim, div2)    {.freqTrim                = trim,            \
                                                  .selDiv2                 = div2,            \
                                                  .divMaxToCpu_0           = 0,               \
                                                  .freqSupp.delayAccessOTP = HSI_OTP_DELAY,   \
                                                  .freqSupp.lowSRI         = HSI_LOW_SRI}       

  #define  MDR_CPU_CFG_HSI_DEF                   MDR_CPU_CFG_HSI_DV_DEF(HSI_FREQ_TRIM, false)
  #define  MDR_CPU_CFG_HSI_DIV2_DEF              MDR_CPU_CFG_HSI_DV_DEF(HSI_FREQ_TRIM, true)
    
  #define  MDR_CPU_CFG_HSI_TRIM_DEF(trim)        MDR_CPU_CFG_HSI_DV_DEF(trim, false)
  #define  MDR_CPU_CFG_HSI_TRIM_DIV2_DEF(trim)   MDR_CPU_CFG_HSI_DV_DEF(trim, false)
    
                                              
  //  Парамеры, необходимые для переключения CPU на тактирование от HSE
  typedef struct {
    //  HSE Params
    MDR_CLK_Source        freqSource;
    bool                  selDiv2;
    uint16_t              divMaxToCpu_0;
    //  FreqSupport Params
    MDR_CLK_FreqSupport   freqSupp;
  } MDR_CPU_CfgHSE;
  
  #define  MDR_CPU_CFG_HSE_SRC_DIV_DEF(FrSrc, div2) {.freqSource              = (FrSrc),         \
                                                     .selDiv2                = div2,            \
                                                     .divMaxToCpu_0           = 0,               \
                                                     .freqSupp.delayAccessOTP = HSE_OTP_DELAY,   \
                                                     .freqSupp.lowSRI         = HSE_LOW_SRI}       
  
  #define  MDR_CPU_CFG_HSE_SRC_DEF(FrSrc)             MDR_CPU_CFG_HSE_SRC_DIV_DEF(FrSrc, false)
  #define  MDR_CPU_CFG_HSE_DIV2_SRC_DEF(FrSrc)        MDR_CPU_CFG_HSE_SRC_DIV_DEF(FrSrc, true)
                                                     
  #define  MDR_CPU_CFG_HSE_RES_DEF                    MDR_CPU_CFG_HSE_SRC_DEF(MDR_CLK_Resonator)  
  #define  MDR_CPU_CFG_HSE_GEN_DEF                    MDR_CPU_CFG_HSE_SRC_DEF(MDR_CLK_Generator)  
  #define  MDR_CPU_CFG_HSE_DIV2_RES_DEF               MDR_CPU_CFG_HSE_DIV2_SRC_DEF(MDR_CLK_Resonator)  
  #define  MDR_CPU_CFG_HSE_DIV2_GEN_DEF               MDR_CPU_CFG_HSE_DIV2_SRC_DEF(MDR_CLK_Generator)    
   

  //  Парамеры PLL
  typedef struct {
    uint8_t         mulN_3_75; 
    uint8_t         divQ_0_15; 
    MDR_PLL_DV_Div  divOut;
  } MDR_CLK_CfgPLL;  

  #define  MDR_CPU_CFG_PLL(N, Q, DV)   {.mulN_3_75        = (N),            \
                                        .divQ_0_15        = (Q),            \
                                        .divOut           = (DV)}
  
  
  //  Парамеры, необходимые для переключения CPU на тактирование от HSI через PLL
  typedef struct {
    MDR_CLK_HSI_TRIM    freqTrim;
    bool                selDiv2;
    uint32_t            timeoutCycles_HSI;
    MDR_CLK_CfgPLL      cfgPLL;
    uint32_t            timeoutCycles_PLL;
    uint16_t            divMaxToCpu_0;
    MDR_CLK_FreqSupport freqSupp;
  } MDR_CPU_PLL_CfgHSI;

  #define  MDR_CPU_CFG_PLL_HSI_DV_DEF(N, Q, DV, delOTP, lowRI, div2)  {.freqTrim  = HSI_FREQ_TRIM,  \
                                                                       .selDiv2                = div2,            \
                                                                       .timeoutCycles_HSI       = HSI_TIMEOUT,    \
                                                                       .cfgPLL.mulN_3_75        = (N),            \
                                                                       .cfgPLL.divQ_0_15        = (Q),            \
                                                                       .cfgPLL.divOut           = (DV),           \
                                                                       .timeoutCycles_PLL       = PLL_TIMEOUT,    \
                                                                       .divMaxToCpu_0           = 0,              \
                                                                       .freqSupp.delayAccessOTP = (delOTP),       \
                                                                       .freqSupp.lowSRI         = (lowRI)}       
  
  #define  MDR_CPU_CFG_PLL_HSI_DEF(N, Q, DV, delOTP, lowRI)         MDR_CPU_CFG_PLL_HSI_DV_DEF(N, Q, DV, delOTP, lowRI, false)
  #define  MDR_CPU_CFG_PLL_HSI_DIV2_DEF(N, Q, DV, delOTP, lowRI)    MDR_CPU_CFG_PLL_HSI_DV_DEF(N, Q, DV, delOTP, lowRI, true)
                                                               
  //  Парамеры, необходимые для переключения CPU на тактирование от HSE через PLL
  typedef struct {
    MDR_CLK_Source      freqSource;
    bool                selDiv2;
    uint32_t            timeoutCycles_HSE;    
    MDR_CLK_CfgPLL      cfgPLL;
    uint32_t            timeoutCycles_PLL;
    uint16_t            divMaxToCpu_0;
    MDR_CLK_FreqSupport freqSupp;
  } MDR_CPU_PLL_CfgHSE;

  #define  MDR_CPU_CFG_PLL_HSE_SRC_DV_DEF(src, N, Q, DV, delOTP, lowRI, div2)    {.freqSource  = (src),  \
                                                                         .selDiv2                = div2,            \
                                                                         .timeoutCycles_HSE       = HSE_TIMEOUT,    \
                                                                         .cfgPLL.mulN_3_75        = (N),            \
                                                                         .cfgPLL.divQ_0_15        = (Q),            \
                                                                         .cfgPLL.divOut           = (DV),           \
                                                                         .timeoutCycles_PLL       = PLL_TIMEOUT,    \
                                                                         .divMaxToCpu_0           = 0,              \
                                                                         .freqSupp.delayAccessOTP = (delOTP),       \
                                                                         .freqSupp.lowSRI         = (lowRI)}  

  #define   MDR_CPU_CFG_PLL_HSE_SRC_DEF(src, N, Q, DV, delOTP, lowRI)         MDR_CPU_CFG_PLL_HSE_SRC_DV_DEF(src, N, Q, DV, delOTP, lowRI, false)
  #define   MDR_CPU_CFG_PLL_HSE_DIV2_SRC_DEF(src, N, Q, DV, delOTP, lowRI)    MDR_CPU_CFG_PLL_HSE_SRC_DV_DEF(src, N, Q, DV, delOTP, lowRI, true)
                                                                         
  #define  MDR_CPU_CFG_PLL_HSE_RES_DEF(N, Q, DV, delOTP, lowRI)          MDR_CPU_CFG_PLL_HSE_SRC_DEF(MDR_CLK_Resonator, N, Q, DV, delOTP, lowRI)
  #define  MDR_CPU_CFG_PLL_HSE_GEN_DEF(N, Q, DV, delOTP, lowRI)          MDR_CPU_CFG_PLL_HSE_SRC_DEF(MDR_CLK_Generator, N, Q, DV, delOTP, lowRI)
  #define  MDR_CPU_CFG_PLL_HSE_DIV2_RES_DEF(N, Q, DV, delOTP, lowRI)     MDR_CPU_CFG_PLL_HSE_DIV2_SRC_DEF(MDR_CLK_Resonator, N, Q, DV, delOTP, lowRI)
  #define  MDR_CPU_CFG_PLL_HSE_DIV2_GEN_DEF(N, Q, DV, delOTP, lowRI)     MDR_CPU_CFG_PLL_HSE_DIV2_SRC_DEF(MDR_CLK_Generator, N, Q, DV, delOTP, lowRI)  
  
#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic pop  
#endif  

#endif //  _MDR_RST_CLOCK_DefsVE8_H

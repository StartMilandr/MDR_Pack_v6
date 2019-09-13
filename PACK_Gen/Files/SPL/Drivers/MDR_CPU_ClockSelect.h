#ifndef _MDR_CPU_CLOCK_SELECT_H
#define _MDR_CPU_CLOCK_SELECT_H

#include <MDR_Config.h>  

#if defined (USE_MDR1986VE8) || defined (USE_MDR1986VE81)
  //  PLL from 8MHz 
  //  Удовлетворяют FInt = F*N/(Q+1) в диапазоне [75MHz .. 150MHz]
  #define  MDRB_PLL_8MHz_TO_36MHz     MDR_CPU_CFG_PLL(18, 1, MDR_PLL_DV_div2)
  #define  MDRB_PLL_8MHz_TO_38MHz     MDR_CPU_CFG_PLL(19, 1, MDR_PLL_DV_div2)
  #define  MDRB_PLL_8MHz_TO_39MHz     MDR_CPU_CFG_PLL(39, 2, MDR_PLL_DV_div2)
  #define  MDRB_PLL_8MHz_TO_40MHz     MDR_CPU_CFG_PLL(10, 0, MDR_PLL_DV_div2)
  //  Дробные
  #define  MDRB_PLL_8MHz_TO_37MHz5    MDR_CPU_CFG_PLL(75, 7, MDR_PLL_DV_div2)
  #define  MDRB_PLL_8MHz_TO_37MHz6    MDR_CPU_CFG_PLL(47, 4, MDR_PLL_DV_div2)
  #define  MDRB_PLL_8MHz_TO_38MHz4    MDR_CPU_CFG_PLL(48, 4, MDR_PLL_DV_div2)
  #define  MDRB_PLL_8MHz_TO_39MHz2    MDR_CPU_CFG_PLL(49, 4, MDR_PLL_DV_div2)

  //  PLL from 10MHz 
  //  Удовлетворяют FInt = F*N/(Q+1) в диапазоне [75MHz .. 150MHz]
  #define  MDRB_PLL_10MHz_TO_37MHz     MDR_CPU_CFG_PLL(37, 4, MDR_PLL_DV_div2)
  #define  MDRB_PLL_10MHz_TO_38MHz     MDR_CPU_CFG_PLL(38, 4, MDR_PLL_DV_div2)
  #define  MDRB_PLL_10MHz_TO_39MHz     MDR_CPU_CFG_PLL(39, 4, MDR_PLL_DV_div2)
  #define  MDRB_PLL_10MHz_TO_40MHz     MDR_CPU_CFG_PLL(8,  0, MDR_PLL_DV_div2)
  
  #define  MDRB_PLL_10MHz_TO_80MHz     MDR_CPU_CFG_PLL(16,  1, MDR_PLL_DV_div1)
  
  //  Дробные
  #define  MDRB_PLL_10MHz_TO_37MHz5    MDR_CPU_CFG_PLL(15, 1, MDR_PLL_DV_div2)
  

  //  Настройки зависящие от частоты
  #define  MDRB_CPU_FREQ_SUPP_40MHz   MDR_CPU_FREQ_SUPP(MDR_OTP_Delay_le_62MHz5,  MDR_BKP_LDO_SRILow_lt50MHz)
  #define  MDRB_CPU_FREQ_SUPP_20MHz   MDR_CPU_FREQ_SUPP(MDR_OTP_Delay_le_41MHz66, MDR_BKP_LDO_SRILow_lt30MHz)


  //  Максимальная тастота PLL
  #define  MDRB_PLL_8MHz_TO_MAX       MDRB_PLL_8MHz_TO_40MHz
  #define  MDRB_PLL_8MHz_FSUPP_MAX    MDRB_CPU_FREQ_SUPP_40MHz  
  
  #define  MDRB_PLL_8MHz_TO_MIN       MDRB_PLL_8MHz_TO_37MHz5
  #define  MDRB_PLL_8MHz_FSUPP_MIN    MDRB_CPU_FREQ_SUPP_40MHz

  #define  MDRB_CPU_FREQ_SUPP_MIN     MDR_CPU_FREQ_SUPP(MDR_OTP_Delay_le_20MHz84, MDR_BKP_LDO_SRILow_lt100KHz)  
  #define  MDRB_CPU_FREQ_SUPP_MAX     MDR_CPU_FREQ_SUPP(MDR_OTP_Delay_le_83MHz33, MDR_BKP_LDO_SRILow_lt100MHz)  


#elif defined (USE_MDR1923VK014)
  //  PLL from 8MHz 
  //  Удовлетворяют FInt = F*N/(Q+1) в диапазоне [75MHz .. 150MHz]
  #define  MDRB_PLL_8MHz_TO_36MHz     MDR_CPU_CFG_PLL(18, 1, MDR_PLL_DV_div2)
  #define  MDRB_PLL_8MHz_TO_38MHz     MDR_CPU_CFG_PLL(19, 1, MDR_PLL_DV_div2)
  #define  MDRB_PLL_8MHz_TO_39MHz     MDR_CPU_CFG_PLL(39, 2, MDR_PLL_DV_div2)
  #define  MDRB_PLL_8MHz_TO_40MHz     MDR_CPU_CFG_PLL(10, 0, MDR_PLL_DV_div2)
  //  Дробные
  #define  MDRB_PLL_8MHz_TO_37MHz5    MDR_CPU_CFG_PLL(75, 7, MDR_PLL_DV_div2)
  #define  MDRB_PLL_8MHz_TO_37MHz6    MDR_CPU_CFG_PLL(47, 4, MDR_PLL_DV_div2)
  #define  MDRB_PLL_8MHz_TO_38MHz4    MDR_CPU_CFG_PLL(48, 4, MDR_PLL_DV_div2)
  #define  MDRB_PLL_8MHz_TO_39MHz2    MDR_CPU_CFG_PLL(49, 4, MDR_PLL_DV_div2)
  
  //  Настройки зависящие от частоты
  #define  MDRB_CPU_FREQ_SUPP_40MHz   MDR_CPU_FREQ_SUPP(MDR_BKP_LDO_SRILow_lt80MHz)
  #define  MDRB_CPU_FREQ_SUPP_20MHz   MDR_CPU_FREQ_SUPP(MDR_BKP_LDO_SRILow_lt40MHz)


  //  Максимальная тастота PLL
  #define  MDRB_PLL_8MHz_TO_MAX       MDRB_PLL_8MHz_TO_40MHz
  #define  MDRB_PLL_8MHz_FSUPP_MAX    MDRB_CPU_FREQ_SUPP_40MHz  
  
  #define  MDRB_PLL_8MHz_TO_MIN       MDRB_PLL_8MHz_TO_37MHz5
  #define  MDRB_PLL_8MHz_FSUPP_MIN    MDRB_CPU_FREQ_SUPP_40MHz

  #define  MDRB_CPU_FREQ_SUPP_MIN     MDR_CPU_FREQ_SUPP(MDR_BKP_LDO_SRILow_lt200KHz)  
  #define  MDRB_CPU_FREQ_SUPP_MAX     MDR_CPU_FREQ_SUPP(MDR_BKP_LDO_SRILow_lt80MHz)  


#elif defined (USE_ESila)
  //  PLL from 8MHz 
  //  Удовлетворяют FInt = F*N/(Q+1) в диапазоне [150MHz .. 300MHz]
  #define  MDRB_PLL_8MHz_TO_38MHz     MDR_CPU_CFG_PLL(19, 0, MDR_PLL_DV_div4)
  #define  MDRB_PLL_8MHz_TO_40MHz     MDR_CPU_CFG_PLL(20, 0, MDR_PLL_DV_div4)
  #define  MDRB_PLL_8MHz_TO_50MHz     MDR_CPU_CFG_PLL(25, 0, MDR_PLL_DV_div4)
  #define  MDRB_PLL_8MHz_TO_60MHz     MDR_CPU_CFG_PLL(30, 0, MDR_PLL_DV_div4)
  #define  MDRB_PLL_8MHz_TO_70MHz     MDR_CPU_CFG_PLL(35, 0, MDR_PLL_DV_div4)
  #define  MDRB_PLL_8MHz_TO_80MHz     MDR_CPU_CFG_PLL(20, 0, MDR_PLL_DV_div2)
  #define  MDRB_PLL_8MHz_TO_92MHz     MDR_CPU_CFG_PLL(23, 0, MDR_PLL_DV_div2)
  #define  MDRB_PLL_8MHz_TO_100MHz    MDR_CPU_CFG_PLL(25, 0, MDR_PLL_DV_div2)
  #define  MDRB_PLL_8MHz_TO_108MHz    MDR_CPU_CFG_PLL(27, 0, MDR_PLL_DV_div2)
  #define  MDRB_PLL_8MHz_TO_120MHz    MDR_CPU_CFG_PLL(30, 0, MDR_PLL_DV_div2)
  
  #ifdef ERRATA_1001_FIXED  
    #define  MDRB_PLL_8MHz_TO_132MHz    MDR_CPU_CFG_PLL(33, 0, MDR_PLL_DV_div2)
    #define  MDRB_PLL_8MHz_TO_140MHz    MDR_CPU_CFG_PLL(35, 0, MDR_PLL_DV_div2)
    #define  MDRB_PLL_8MHz_TO_148MHz    MDR_CPU_CFG_PLL(37, 0, MDR_PLL_DV_div2)
    #define  MDRB_PLL_8MHz_TO_152MHz    MDR_CPU_CFG_PLL(19, 0, MDR_PLL_DV_div1)
    #define  MDRB_PLL_8MHz_TO_160MHz    MDR_CPU_CFG_PLL(20, 0, MDR_PLL_DV_div1)
  #endif
  
  //  Настройки зависящие от частоты
  #define  MDRB_CPU_FREQ_SUPP_38MHz   MDR_CPU_FREQ_SUPP(EEPROM_Delay_le63MHz,  MDR_BKP_LDO_SRILow_lt50MHz)
  #define  MDRB_CPU_FREQ_SUPP_40MHz   MDR_CPU_FREQ_SUPP(EEPROM_Delay_le63MHz,  MDR_BKP_LDO_SRILow_lt50MHz)
  #define  MDRB_CPU_FREQ_SUPP_50MHz   MDR_CPU_FREQ_SUPP(EEPROM_Delay_le63MHz,  MDR_BKP_LDO_SRILow_lt100MHz)
  #define  MDRB_CPU_FREQ_SUPP_60MHz   MDR_CPU_FREQ_SUPP(EEPROM_Delay_le63MHz,  MDR_BKP_LDO_SRILow_lt100MHz)
  #define  MDRB_CPU_FREQ_SUPP_70MHz   MDR_CPU_FREQ_SUPP(EEPROM_Delay_le94MHz,  MDR_BKP_LDO_SRILow_lt100MHz)
  #define  MDRB_CPU_FREQ_SUPP_80MHz   MDR_CPU_FREQ_SUPP(EEPROM_Delay_le94MHz,  MDR_BKP_LDO_SRILow_lt100MHz)
  #define  MDRB_CPU_FREQ_SUPP_92MHz   MDR_CPU_FREQ_SUPP(EEPROM_Delay_le94MHz,  MDR_BKP_LDO_SRILow_lt100MHz)
  #define  MDRB_CPU_FREQ_SUPP_100MHz  MDR_CPU_FREQ_SUPP(EEPROM_Delay_le125MHz, MDR_BKP_LDO_SRILow_ge100MHz)
  #define  MDRB_CPU_FREQ_SUPP_108MHz  MDR_CPU_FREQ_SUPP(EEPROM_Delay_le125MHz, MDR_BKP_LDO_SRILow_ge100MHz)
  #define  MDRB_CPU_FREQ_SUPP_120MHz  MDR_CPU_FREQ_SUPP(EEPROM_Delay_le125MHz, MDR_BKP_LDO_SRILow_ge100MHz)


  #ifdef ERRATA_1001_FIXED
    #define  MDRB_CPU_FREQ_SUPP_132MHz  MDR_CPU_FREQ_SUPP(EEPROM_Delay_le157MHz, MDR_BKP_LDO_SRILow_ge100MHz)
    #define  MDRB_CPU_FREQ_SUPP_140MHz  MDR_CPU_FREQ_SUPP(EEPROM_Delay_le157MHz, MDR_BKP_LDO_SRILow_ge100MHz)
    #define  MDRB_CPU_FREQ_SUPP_148MHz  MDR_CPU_FREQ_SUPP(EEPROM_Delay_le157MHz, MDR_BKP_LDO_SRILow_ge100MHz)
    #define  MDRB_CPU_FREQ_SUPP_152MHz  MDR_CPU_FREQ_SUPP(EEPROM_Delay_le157MHz, MDR_BKP_LDO_SRILow_ge100MHz)
    #define  MDRB_CPU_FREQ_SUPP_160MHz  MDR_CPU_FREQ_SUPP(EEPROM_Delay_le188MHz, MDR_BKP_LDO_SRILow_ge100MHz)
    
    //  Максимальная частота PLL
    #define  MDRB_PLL_8MHz_TO_MAX       MDRB_PLL_8MHz_TO_160MHz
    #define  MDRB_PLL_8MHz_FSUPP_MAX    MDRB_CPU_FREQ_SUPP_160MHz  
    #define  MDRB_CPU_FREQ_SUPP_MAX     MDR_CPU_FREQ_SUPP(EEPROM_Delay_le188MHz, MDR_BKP_LDO_SRILow_ge100MHz)   
    
  #else
    //  Максимальная частота PLL
    #define  MDRB_PLL_8MHz_TO_MAX       MDRB_PLL_8MHz_TO_120MHz
    #define  MDRB_PLL_8MHz_FSUPP_MAX    MDRB_CPU_FREQ_SUPP_120MHz  
    #define  MDRB_CPU_FREQ_SUPP_MAX     MDR_CPU_FREQ_SUPP(EEPROM_Delay_le125MHz, MDR_BKP_LDO_SRILow_ge100MHz)   
  #endif

  //  Минимальная частота PLL
  #define  MDRB_PLL_8MHz_TO_MIN       MDRB_PLL_8MHz_TO_38MHz
  #define  MDRB_PLL_8MHz_FSUPP_MIN    MDRB_CPU_FREQ_SUPP_38MHz
  
  #define  MDRB_CPU_FREQ_SUPP_MIN     MDR_CPU_FREQ_SUPP(EEPROM_Delay_le32MHz,  MDR_BKP_LDO_SRILow_lt100KHz) 


#else
  //  Множитель PLL
  #define  MDRB_PLL_8MHz_TO_8MHz       MDR_x1
  #define  MDRB_PLL_8MHz_TO_16MHz      MDR_x2
  #define  MDRB_PLL_8MHz_TO_24MHz      MDR_x3
  #define  MDRB_PLL_8MHz_TO_32MHz      MDR_x4
  #define  MDRB_PLL_8MHz_TO_40MHz      MDR_x5
  #define  MDRB_PLL_8MHz_TO_48MHz      MDR_x6
  #define  MDRB_PLL_8MHz_TO_56MHz      MDR_x7
  #define  MDRB_PLL_8MHz_TO_64MHz      MDR_x8
  #define  MDRB_PLL_8MHz_TO_72MHz      MDR_x9
  #define  MDRB_PLL_8MHz_TO_80MHz      MDR_x10
  #define  MDRB_PLL_8MHz_TO_88MHz      MDR_x11
  #define  MDRB_PLL_8MHz_TO_96MHz      MDR_x12
  #define  MDRB_PLL_8MHz_TO_104MHz     MDR_x13
  #define  MDRB_PLL_8MHz_TO_112MHz     MDR_x14
  #define  MDRB_PLL_8MHz_TO_120MHz     MDR_x15
  #define  MDRB_PLL_8MHz_TO_128MHz     MDR_x16

  //  Настройки зависящие от частоты
  #define  MDRB_CPU_FREQ_SUPP_8MHz     MDR_CPU_FREQ_SUPP(EEPROM_Delay_le25MHz,   MDR_LOWRI_le10MHz)
  #define  MDRB_CPU_FREQ_SUPP_16MHz    MDR_CPU_FREQ_SUPP(EEPROM_Delay_le25MHz,   MDR_LOWRI_le40MHz)
  #define  MDRB_CPU_FREQ_SUPP_24MHz    MDR_CPU_FREQ_SUPP(EEPROM_Delay_le25MHz,   MDR_LOWRI_le40MHz)
  #define  MDRB_CPU_FREQ_SUPP_32MHz    MDR_CPU_FREQ_SUPP(EEPROM_Delay_le50MHz,   MDR_LOWRI_le40MHz)
  #define  MDRB_CPU_FREQ_SUPP_40MHz    MDR_CPU_FREQ_SUPP(EEPROM_Delay_le50MHz,   MDR_LOWRI_le80MHz)
  #define  MDRB_CPU_FREQ_SUPP_48MHz    MDR_CPU_FREQ_SUPP(EEPROM_Delay_le50MHz,   MDR_LOWRI_le80MHz)
  #define  MDRB_CPU_FREQ_SUPP_56MHz    MDR_CPU_FREQ_SUPP(EEPROM_Delay_le75MHz,   MDR_LOWRI_le80MHz)
  #define  MDRB_CPU_FREQ_SUPP_64MHz    MDR_CPU_FREQ_SUPP(EEPROM_Delay_le75MHz,   MDR_LOWRI_le80MHz)
  #define  MDRB_CPU_FREQ_SUPP_72MHz    MDR_CPU_FREQ_SUPP(EEPROM_Delay_le75MHz,   MDR_LOWRI_le80MHz)
  #define  MDRB_CPU_FREQ_SUPP_80MHz    MDR_CPU_FREQ_SUPP(EEPROM_Delay_le100MHz,  MDR_LOWRI_gt80MHz)
  #define  MDRB_CPU_FREQ_SUPP_88MHz    MDR_CPU_FREQ_SUPP(EEPROM_Delay_le100MHz,  MDR_LOWRI_gt80MHz)
  #define  MDRB_CPU_FREQ_SUPP_96MHz    MDR_CPU_FREQ_SUPP(EEPROM_Delay_le100MHz,  MDR_LOWRI_gt80MHz)
  #define  MDRB_CPU_FREQ_SUPP_104MHz   MDR_CPU_FREQ_SUPP(EEPROM_Delay_le125MHz,  MDR_LOWRI_gt80MHz)
  #define  MDRB_CPU_FREQ_SUPP_112MHz   MDR_CPU_FREQ_SUPP(EEPROM_Delay_le125MHz,  MDR_LOWRI_gt80MHz)
  #define  MDRB_CPU_FREQ_SUPP_120MHz   MDR_CPU_FREQ_SUPP(EEPROM_Delay_le125MHz,  MDR_LOWRI_gt80MHz)
  #define  MDRB_CPU_FREQ_SUPP_128MHz   MDR_CPU_FREQ_SUPP(EEPROM_Delay_le150MHz,  MDR_LOWRI_gt80MHz)

#endif


#if defined (USE_MDR1986VE8) || defined (USE_MDR1986VE81) ||  defined (USE_MDR1923VK014) || defined (USE_ESila)
  #define MDR_CLK_PLL_HSI_DEF(pllCfg, suppFreq)     {.freqTrim            = HSI_FREQ_TRIM,            \
                                                     .selDiv2             = false,                    \
                                                     .timeoutCycles_HSI   = HSI_TIMEOUT,              \
                                                     .cfgPLL              = pllCfg,                   \
                                                     .timeoutCycles_PLL   = PLL_TIMEOUT,              \
                                                     .divMaxToCpu_0       = 0,                        \
                                                     .freqSupp            = suppFreq}

  #define MDR_CLK_PLL_HSE_RES_DEF(pllCfg, suppFreq) {.freqSource          = MDR_CLK_Resonator,        \
                                                     .selDiv2             = false,                    \
                                                     .timeoutCycles_HSE   = HSI_TIMEOUT,              \
                                                     .cfgPLL              = pllCfg,                   \
                                                     .timeoutCycles_PLL   = PLL_TIMEOUT,              \
                                                     .divMaxToCpu_0       = 0,                        \
                                                     .freqSupp            = suppFreq}

  #define MDR_CLK_PLL_HSE_GEN_DEF(pllCfg, suppFreq) {.freqSource          = MDR_CLK_Generator,        \
                                                     .selDiv2             = false,                    \
                                                     .timeoutCycles_HSE   = HSI_TIMEOUT,              \
                                                     .cfgPLL              = pllCfg,                   \
                                                     .timeoutCycles_PLL   = PLL_TIMEOUT,              \
                                                     .divMaxToCpu_0       = 0,                        \
                                                     .freqSupp            = suppFreq}
                                  
#endif
                                   
                                                     
#endif //_MDR_CPU_CLOCK_SELECT_H

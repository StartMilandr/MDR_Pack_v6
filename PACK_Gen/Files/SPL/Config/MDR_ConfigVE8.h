#ifndef MDR_CONFIG_VE8_H
#define MDR_CONFIG_VE8_H

#include <MDR_1986VE8.h>
  

//================  Параметры источников частоты ================
//  Internal Generators
#define HSI_FREQ_HZ       8000000UL
#define HSI_FREQ_TRIM     MDR_BKP_REG63_HSI_Trim_Def
#define HSI_TIMEOUT       0x0600UL
#define HSI_OTP_DELAY     MDR_OTP_Delay_le_20MHz84
#define HSI_LOW_SRI       MDR_BKP_LDO_SRILow_lt10MHz

#define LSI_FREQ_HZ       40000UL
#define LSI_FREQ_TRIM     MDR_BKP_REG63_LSI_Trim_Def
#define LSI_TIMEOUT       0x0600UL
#define LSI_OTP_DELAY     MDR_OTP_Delay_le_20MHz84
#define LSI_LOW_SRI       MDR_BKP_LDO_SRILow_lt100KHz

//  External Generators
#define HSE0_FREQ_HZ      8000000UL
#define HSE0_TIMEOUT      0x8000UL
#define HSE0_OTP_DELAY    MDR_OTP_Delay_le_20MHz84
#define HSE0_LOW_SRI      MDR_BKP_LDO_SRILow_lt10MHz


#define HSE1_FREQ_HZ      8000000UL
#define HSE1_TIMEOUT      0x8000UL
#define HSE1_OTP_DELAY    MDR_OTP_Delay_le_20MHz84
#define HSE1_LOW_SRI      MDR_BKP_LDO_SRILow_lt10MHz

#define LSE_FREQ_HZ       32768UL
#define LSE_TIMEOUT       0x8000UL
#define LSE_OTP_DELAY     MDR_OTP_Delay_le_20MHz84
#define LSE_LOW_SRI       MDR_BKP_LDO_SRILow_lt100KHz

//  PLL Ready Timeout
#define PLL_TIMEOUT       0x8000UL


//  Выбор HSEx и PLLx для использования по умолчанию для MDR_CPU_SetClock_HSE_PLL() в MDR_RST_Clock.h
#define MDR_HSE_Def         MDR_CLOCK_HSE0
#define MDR_PLL_IN_Def      MDR_PLL_IN_HSE0
#define MDR_PLL_Def         MDR_CLOCK_PLL0
#define MDR_MAXCLK_SEL_Def  MAXCLK_PLL0




#endif  //  MDR_CONFIG_VE8_H

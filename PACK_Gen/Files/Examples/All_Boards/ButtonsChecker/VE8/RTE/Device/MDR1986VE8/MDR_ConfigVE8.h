#ifndef MDR_CONFIG_VE8_H
#define MDR_CONFIG_VE8_H

#include <MDR_1986VE8.h>
  

//================  Параметры источников частоты ================
//  Internal Generators
#define HSI_FREQ_HZ       8000000UL
#define HSI_FREQ_TRIM     MDR_BKP_HSI_TRIM_8M0Hz
#define HSI_TIMEOUT       0x0600UL

#define LSI_FREQ_HZ       40000UL
#define LSI_FREQ_TRIM     MDR_BKP_LSI_TRIM_40KHz
#define LSI_TIMEOUT       0x0600UL

//  External Generators
#define HSE0_FREQ_HZ       8000000UL
#define HSE0_TIMEOUT       0x8000UL

#define HSE1_FREQ_HZ       8000000UL
#define HSE1_TIMEOUT       0x8000UL

#define LSE_FREQ_HZ       32768UL
#define LSE_TIMEOUT       0x8000UL

//  PLL Ready Timeout
#define PLL_TIMEOUT_MS    100



#endif  //  MDR_CONFIG_VE8_H

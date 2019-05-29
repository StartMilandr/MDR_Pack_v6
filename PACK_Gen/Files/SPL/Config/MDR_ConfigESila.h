#ifndef MDR_CONFIG_ESila_H
#define MDR_CONFIG_ESila_H

#include <MDR_ESila.h>
  

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

//=============  Защита пинов совмещенных с Jtag  ==================
// Писать в пины порта совмещенные с Jtag можно только 0.
// Иначе отладчик потеряет соединение. Активным может быть только один.

//#define USE_JTAG_A
//#define USE_JTAG_B
//#define USE_SWD_A
//#define USE_SWD_B

#endif  //  MDR_CONFIG_ESila_H

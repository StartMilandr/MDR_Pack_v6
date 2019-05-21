#ifndef MDR_CONFIG_VE3_H
#define MDR_CONFIG_VE3_H

#include <MDR_1986VE3.h>

//=============  Debug Uart printf settings  ==================
#define UART_DEBUG_IND              1    
#define UART_DEBUG_SHOW_WELLCOME    1
#define UART_DEBUG_BAUD_DEF         9600


//================  Параметры источников частоты ================
//  Internal Generators
#define HSI_FREQ_HZ       8000000UL
#define HSI_FREQ_TRIM     MDR_BKP_HSI_TRIM_8M0Hz
#define HSI_TIMEOUT       0x0600UL

#define LSI_FREQ_HZ       40000UL
#define LSI_FREQ_TRIM     MDR_BKP_LSI_TRIM_40KHz
#define LSI_TIMEOUT       0x0600UL

//  External Generators
#define HSE_FREQ_HZ       8000000UL
#define HSE_TIMEOUT       0x8000UL

#define LSE_FREQ_HZ       32768UL
#define LSE_TIMEOUT       0x8000UL

//  PLL Ready Timeout
#define PLL_TIMEOUT_MS    100

//  External Generator for Ethernet PHY
#define HSE2_FREQ_HZ         25000000UL
#define HSE2_TIMEOUT_CYCLES  2400


// =========================   DMA   ================================
//  Для экономии памяти можно прописать 0, если альтернативные структуры DMA не используются
#define USE_DMA_ALTER_STRUCT            1
//  Можно завести собственную управляющую структуру каналов вместо глобальной (по умолчанию). 
#define USE_DMA_USER_CNTLS_CTRL_TABLE   0


// =========================   Timer Bugfixes   ================================
//  Прерывание возникает раньше, чем обновляются регистры CCR и CCR1
#define USE_TIM_CAP_FIX   0


// =========================   POWER Bugfixes   ================================
// Флаги событий не стираются с первого раза
#define USE_PWR_CLR_FIX   1



#endif  //  MDR_CONFIG_VE3_H

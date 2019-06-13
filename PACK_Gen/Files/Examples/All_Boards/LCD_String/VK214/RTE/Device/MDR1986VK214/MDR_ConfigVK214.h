#ifndef MDR_CONFIG_VK214_H
#define MDR_CONFIG_VK214_H

#include <MDR_1986VK214.h> 
  

//=============  Debug Uart printf settings  ==================
#define UART_DEBUG_IND              1    
#define UART_DEBUG_SHOW_WELLCOME    1
#define UART_DEBUG_BAUD_DEF         9600


//=============  Защита пинов совмещенных с Jtag  ==================
// Писать в пины порта совмещенные с Jtag можно только 0.
// Иначе отладчик потеряет соединение.

#define USE_SWD_A


//================  Параметры источников частоты ================
//  Internal Generators
//  Internal Generators
#define HSI_FREQ_HZ         8000000UL
#define HSI_FREQ_TRIM       MDR_BKP_HSI_TRIM_8M0Hz
#define HSI_TIMEOUT         0x0600UL
#define HSI_LOW_SRI         MDR_LOWRI_le10MHz
#define HSI_DELAY_EEPROM    EEPROM_Delay_le18MHz

#define LSI_FREQ_HZ         40000UL
#define LSI_FREQ_TRIM       MDR_BKP_LSI_TRIM_40KHz
#define LSI_TIMEOUT         0x0600UL
#define LSI_LOW_SRI         MDR_LOWRI_le200KHz
#define LSI_DELAY_EEPROM    EEPROM_Delay_le18MHz

//  External Generators
#define HSE_FREQ_HZ         8000000UL
#define HSE_TIMEOUT         0x0600UL
#define HSE_LOW_SRI         MDR_LOWRI_le40MHz
#define HSE_DELAY_EEPROM    EEPROM_Delay_le36MHz

#define LSE_FREQ_HZ         32768UL
#define LSE_TIMEOUT         0x0600UL
#define LSE_LOW_SRI         MDR_LOWRI_le200KHz
#define LSE_DELAY_EEPROM    EEPROM_Delay_le18MHz


//  PLL Ready Timeout
#define PLL_TIMEOUT       0x0600UL


// =========================   DMA   ================================
//  Для экономии памяти можно прописать 0, если альтернативные структуры DMA не используются
#define USE_DMA_ALTER_STRUCT   1
//  Можно завести собственную управляющую структуру каналов вместо глобальной (по умолчанию). 
#define USE_DMA_USER_CNTLS_CTRL_TABLE   0


// =========================   Timer Bugfixes   ================================
//  Прерывание возникает раньше, чем обновляются регистры CCR и CCR1
#define USE_TIM_CAP_FIX   1


// =========================   POWER Bugfixes   ================================
// Флаги событий не стираются с первого раза
#define USE_PWR_CLR_FIX   1

// Только для 1986VK214. Регистр PVDCS не прописывается с первого раза - MDR_Power.c
#define USE_PWR_WR_FIX_VK214  




#endif  //  MDR_CONFIG_VK214_H

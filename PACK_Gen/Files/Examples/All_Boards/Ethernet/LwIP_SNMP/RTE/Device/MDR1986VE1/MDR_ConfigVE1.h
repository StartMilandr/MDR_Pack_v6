#ifndef MDR_CONFIG_VE1_H
#define MDR_CONFIG_VE1_H

#include <MDR_1986VE1.h>

//=============  Debug Uart printf settings  ==================
#define UART_DEBUG_IND              1    
#define UART_DEBUG_SHOW_WELLCOME    1
#define UART_DEBUG_BAUD_DEF         9600


//================  Параметры источников частоты ================
//  Internal Generators
#define HSI_FREQ_HZ         8000000UL
#define HSI_FREQ_TRIM       MDR_BKP_HSI_TRIM_8M0Hz
#define HSI_TIMEOUT         0x0600UL
#define HSI_LOW_SRI         MDR_LOWRI_le40MHz
#define HSI_DELAY_EEPROM    EEPROM_Delay_le25MHz


#define LSI_FREQ_HZ         40000UL
#define LSI_FREQ_TRIM       MDR_BKP_LSI_TRIM_40KHz
#define LSI_TIMEOUT         0x0600UL
#define LSI_LOW_SRI         MDR_LOWRI_le40MHz
#define LSI_DELAY_EEPROM    EEPROM_Delay_le25MHz

//  External Generators
#define HSE_FREQ_HZ         8000000UL
#define HSE_TIMEOUT         0x0600UL
#define HSE_LOW_SRI         MDR_LOWRI_le40MHz
#define HSE_DELAY_EEPROM    EEPROM_Delay_le25MHz

#define LSE_FREQ_HZ         32768UL
#define LSE_TIMEOUT         0xF0000UL
#define LSE_LOW_SRI         MDR_LOWRI_le40MHz
#define LSE_DELAY_EEPROM    EEPROM_Delay_le25MHz


//  PLL Ready Timeout
#define PLL_TIMEOUT         0x0600UL

//  External Generator for Ethernet PHY
#define HSE2_IS_RESONATOR    1
#define HSE2_FREQ_HZ         25000000UL
#define HSE2_TIMEOUT_CYCLES  0x0600UL


// =========================   DMA   ================================
//  Для экономии памяти можно прописать 0, если альтернативные структуры DMA не используются
#define USE_DMA_ALTER_STRUCT            1
//  Можно завести собственную управляющую структуру каналов вместо глобальной (по умолчанию). 
#define USE_DMA_USER_CNTLS_CTRL_TABLE   0


// =========================   Timer Bugfixes   ================================
//  Прерывание возникает раньше, чем обновляются регистры CCR и CCR1
#define USE_TIM_CAP_FIX   1


// =========================   POWER Bugfixes   ================================
// Флаги событий не стираются с первого раза
#define USE_PWR_CLR_FIX   1


// =========================   MDR_Delay ===========================
//  Выбор реализации для MDR_Delay: 
//    По умолчанию используется ассемблерный вариант, универсальный
//    Вариант на Си сильно зависит от опций компилятора
//    Вариант на DWT есть только в Cortex-M3/M4 и требует предварительное включение вызовом MDR_Delay_Init().
#define   USE_MDR_DELAY_ASM
//#define   USE_MDR_DELAY_C


//  Исполнение функции задержки из ОЗУ / EEPROM происходит за разное количество тактов CPU. 
//  Данными параметрами можно уточнить сколько тактов CPU занимает один цикл задержки в MDR_Funcs, для повышения точности.
#define DELAY_LOOP_CYCLES_ASM       4
#define DELAY_LOOP_CYCLES_ASM_RAM   8
#define DELAY_LOOP_CYCLES_C         9
#define DELAY_LOOP_CYCLES_C_RAM     16


#ifdef USE_MDR_DELAY_C
  #define DELAY_LOOP_CYCLES         DELAY_LOOP_CYCLES_C
  #define DELAY_LOOP_CYCLES_RAM     DELAY_LOOP_CYCLES_C_RAM
#else
  #define DELAY_LOOP_CYCLES         DELAY_LOOP_CYCLES_ASM
  #define DELAY_LOOP_CYCLES_RAM     DELAY_LOOP_CYCLES_ASM_RAM
#endif


// =========================   ETHERNET ===========================
//  Выбор режима работы буферов Ethernet (Только один!)
#define MDR_ETH_BUFF_LIN        0
#define MDR_ETH_BUFF_AUTO_PTR   0
#define MDR_ETH_BUFF_FIFO       1

#define MDR_ETH_BUFF_LEN_TX     1514
#define MDR_ETH_MDIO_TIMEOUT    0x0004FFFFUL

#define MDR_ETH_DMA_CHANNEL_RX  MDR_DMA_CH_REQ_SOFT1
#define MDR_ETH_DMA_CHANNEL_TX  MDR_DMA_CH_REQ_SOFT2


#endif  //  MDR_CONFIG_VE1_H

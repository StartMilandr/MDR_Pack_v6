#ifndef MDR_CONFIG_MLDR155_H
#define MDR_CONFIG_MLDR155_H

#include <MDR_MLDR155.h>
  

//=============  Debug Uart printf settings  ==================
#define UART_DEBUG_IND              1    
#define UART_DEBUG_SHOW_WELLCOME    1
#define UART_DEBUG_BAUD_DEF         9600


//================  Параметры источников частоты ================
//  Internal Generators
#define HSI_FREQ_HZ         8000000UL
#define HSI_FREQ_TRIM       MDR_BKP_REG63_HSI_Trim_Def
#define HSI_TIMEOUT         0x0600UL
#define HSI_LOW_SRI         MDR_BKP_LDO_SRILow_lt10MHz
#define HSI_EEPROM_DELAY    EEPROM_Delay_le32MHz

#define LSI_FREQ_HZ         40000UL
#define LSI_FREQ_TRIM       MDR_BKP_REG63_LSI_Trim_Def
#define LSI_TIMEOUT         0x0600UL
#define LSI_LOW_SRI         MDR_BKP_LDO_SRILow_lt100KHz 
#define LSI_EEPROM_DELAY    EEPROM_Delay_le32MHz

//  External Generators
#define HSE0_FREQ_HZ        8000000UL
#define HSE0_TIMEOUT        0x8000UL
#define HSE0_LOW_SRI        MDR_BKP_LDO_SRILow_lt50MHz
#define HSE0_EEPROM_DELAY   EEPROM_Delay_le32MHz

#define HSE1_FREQ_HZ        8000000UL
#define HSE1_TIMEOUT        0x8000UL
#define HSE1_LOW_SRI        MDR_BKP_LDO_SRILow_lt50MHz
#define HSE1_EEPROM_DELAY   EEPROM_Delay_le32MHz

#define LSE_FREQ_HZ         32768UL
#define LSE_TIMEOUT         0x8000UL
#define LSE_LOW_SRI         MDR_BKP_LDO_SRILow_lt100KHz
#define LSE_EEPROM_DELAY    EEPROM_Delay_le32MHz

//  PLL Ready Timeout
#define PLL_TIMEOUT         0x8000UL


//  Выбор HSEx и PLLx для использования по умолчанию для MDR_CPU_SetClock_HSE_PLL() в MDR_RST_Clock.h
#define MDR_HSE_IND_Def     0
#define MDR_PLL_IND_Def     0


#if MDR_HSE_IND_Def == 0
  #define MDR_HSE_Def             MDR_CLOCK_HSE0
  #define MDR_PLL_IN_HSE_Def      MDR_PLL_IN_HSE0
  #define MDR_PLL_IN_HSEdiv2_Def  MDR_PLL_IN_HSE0div2

  #define HSE_FREQ_HZ             HSE0_FREQ_HZ  
  #define HSE_TIMEOUT             HSE0_TIMEOUT  
  #define HSE_EEPROM_DELAY        HSE0_EEPROM_DELAY
  #define HSE_LOW_SRI             HSE0_LOW_SRI  
#else
  #define MDR_HSE_Def             MDR_CLOCK_HSE1
  #define MDR_PLL_IN_HSE_Def      MDR_PLL_IN_HSE1
  #define MDR_PLL_IN_HSEdiv2_Def  MDR_PLL_IN_HSE1div2

  #define HSE_FREQ_HZ             HSE1_FREQ_HZ  
  #define HSE_TIMEOUT             HSE1_TIMEOUT  
  #define HSE_EEPROM_DELAY        HSE1_EEPROM_DELAY
  #define HSE_LOW_SRI             HSE1_LOW_SRI  
#endif

#if  MDR_PLL_IND_Def == 0
  #define MDR_PLL_Def         MDR_CLOCK_PLL0
  #define MDR_MAXCLK_SEL_Def  MAXCLK_PLL0
  
#elif  MDR_PLL_IND_Def == 1
  #define MDR_PLL_Def         MDR_CLOCK_PLL1
  #define MDR_MAXCLK_SEL_Def  MAXCLK_PLL1

#elif  MDR_PLL_IND_Def == 2
  #define MDR_PLL_Def         MDR_CLOCK_PLL2
  #define MDR_MAXCLK_SEL_Def  MAXCLK_PLL2
  
#else
  #define MDR_PLL_Def         MDR_CLOCK_PLL3
  #define MDR_MAXCLK_SEL_Def  MAXCLK_PLL3
#endif

//=============  Защита пинов совмещенных с Jtag  ==================
// Писать в пины порта совмещенные с Jtag можно только 0.
// Иначе отладчик потеряет соединение. Активным может быть только один.

//#define USE_JTAG_A
//#define USE_JTAG_B
//#define USE_SWD_A
//#define USE_SWD_B


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
//#define   USE_MDR_DELAY_DWT

//  Исполнение функции задержки из ОЗУ / EEPROM происходит за разное количество тактов CPU. 
//  Данными параметрами можно уточнить сколько тактов CPU занимает один цикл задержки в MDR_Funcs, для повышения точности.
#define DELAY_LOOP_CYCLES_ASM       9
#define DELAY_LOOP_CYCLES_ASM_RAM   9
#define DELAY_LOOP_CYCLES_C         14
#define DELAY_LOOP_CYCLES_C_RAM     14
#define DELAY_LOOP_CYCLES_DWT       1

#ifdef USE_MDR_DELAY_C
  #define DELAY_LOOP_CYCLES         DELAY_LOOP_CYCLES_C
  #define DELAY_LOOP_CYCLES_RAM     DELAY_LOOP_CYCLES_C_RAM
#elif defined USE_MDR_DELAY_DWT  
  #define DELAY_LOOP_CYCLES         DELAY_LOOP_CYCLES_DWT
  #define DELAY_LOOP_CYCLES_RAM     DELAY_LOOP_CYCLES_DWT
#else
  #define DELAY_LOOP_CYCLES         DELAY_LOOP_CYCLES_ASM
  #define DELAY_LOOP_CYCLES_RAM     DELAY_LOOP_CYCLES_ASM_RAM
#endif


// =========================   ETHERNET ===========================
//  Выбор режима работы буферов Ethernet (Только один!)
#define MDR_ETH_BUFF_LIN        1
#define MDR_ETH_BUFF_AUTO_PTR   0
#define MDR_ETH_BUFF_FIFO       0

#define MDR_ETH_BUFF_LEN_TX     1514
#define MDR_ETH_BUFF_LEN_RX     MDR_ETH_BUFF_LEN_TX
#define MDR_ETH_MDIO_TIMEOUT    0x0004FFFFUL

#define MDR_ETH_DMA_CHANNEL_RX  MDR_DMA_CH_REQ_ETH_RX
#define MDR_ETH_DMA_CHANNEL_TX  MDR_DMA_CH_REQ_ETH_TX


//===========================  FreeRTOS (for FreeRTOSConfig.h)  ===========================
//  Выбор таймера для отсчета configTICK_RATE_HZ, по умолчанию - системный таймер SysTimer
#define configOVERRIDE_DEFAULT_TICK_CONFIGURATION     0 

#if configOVERRIDE_DEFAULT_TICK_CONFIGURATION != 0
  // Выбор аппаратного таймера для FreeRTOS (вместо SysTimer который в ВЕ1 и ВЕ3 имеет ошибку в errata)
  #define MDR_FREE_RTOS_TIMER                MDR_TIMER1ex
  #define MDR_FREE_RTOS_TIMER_HANDLER        TIMER1_IRQHandler
  
  // Подстройка отсчетов времени при configUSE_TICKLESS_IDLE = 1
  // !!! Значение неправильное (взято наглаз по скорости мигания светодиода), перемерить осциллографом и поменять!!!
  // см функцию - vPortSuppressTicksAndSleep() файл FreeRTOS/port.c
  #define MDR_FREE_RTOS_TIMER_MISSED_FACTOR  445
#endif



#endif  //  MDR_CONFIG_MLDR155_H

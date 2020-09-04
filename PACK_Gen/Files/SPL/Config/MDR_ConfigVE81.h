#ifndef MDR_CONFIG_VE8_H
#define MDR_CONFIG_VE8_H

#include <MDR_1986VE81.h>


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
#define HSE0_FREQ_HZ      10000000UL
#define HSE0_TIMEOUT      0x8000UL
#define HSE0_OTP_DELAY    MDR_OTP_Delay_le_20MHz84
#define HSE0_LOW_SRI      MDR_BKP_LDO_SRILow_lt10MHz


#define HSE1_FREQ_HZ      10000000UL
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
#define MDR_HSE_IND_Def     0
#define MDR_PLL_IND_Def     0


#if MDR_HSE_IND_Def == 0
  #define MDR_HSE_Def             MDR_CLOCK_HSE0
  #define MDR_PLL_IN_HSE_Def      MDR_PLL_IN_HSE0
  #define MDR_PLL_IN_HSEdiv2_Def  MDR_PLL_IN_HSE0div2

  #define HSE_FREQ_HZ             HSE0_FREQ_HZ  
  #define HSE_TIMEOUT             HSE0_TIMEOUT  
  #define HSE_OTP_DELAY           HSE0_OTP_DELAY
  #define HSE_LOW_SRI             HSE0_LOW_SRI  
#else
  #define MDR_HSE_Def             MDR_CLOCK_HSE1
  #define MDR_PLL_IN_HSE_Def      MDR_PLL_IN_HSE1
  #define MDR_PLL_IN_HSEdiv2_Def  MDR_PLL_IN_HSE1div2

  #define HSE_FREQ_HZ             HSE1_FREQ_HZ  
  #define HSE_TIMEOUT             HSE1_TIMEOUT  
  #define HSE_OTP_DELAY           HSE1_OTP_DELAY
  #define HSE_LOW_SRI             HSE1_LOW_SRI  
#endif

#if  MDR_PLL_IND_Def == 0
  #define MDR_PLL_Def         MDR_CLOCK_PLL0
  #define MDR_MAXCLK_SEL_Def  MAXCLK_PLL0
  
#elif  MDR_PLL_IND_Def == 1
  #define MDR_PLL_Def         MDR_CLOCK_PLL1
  #define MDR_MAXCLK_SEL_Def  MAXCLK_PLL1
  
#else
  #define MDR_PLL_Def         MDR_CLOCK_PLL2
  #define MDR_MAXCLK_SEL_Def  MAXCLK_PLL2

#endif


//=============  Debug Uart printf settings  ==================
#define UART_DEBUG_IND              1    
#define UART_DEBUG_SHOW_WELLCOME    1
#define UART_DEBUG_BAUD_DEF         9600

//=============  UART CLI Interface  ==================
#define CFG_CLI_UARTex          MDR_UART1ex
#define CFG_CLI_DMA_ChanTX      MDR_DMA_CH_SREQ_UART1_TX
#define CFG_CLI_DMA_ChanRX      MDR_DMA_CH_SREQ_UART1_RX

//  Максимальное количество байт за один трансфер (длина, команда + данные)
//  Не более 1023 (ограничение от DMA на 1024 байта и нечетное количество байт)
#define CFG_CLI_MESS_LEN_MAX    128

//  Дописать команды для своего приложения.
typedef enum {
  cliCMD_NONE  = 0,
  cliCMD_ERROR = 1,
  //  User Defs
  cliCMD_,
  
  //  Not for use
  cliCMD_LEN
} CLI_CMD_e;


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
#define MDR_ETH_BUFF_LIN        0
#define MDR_ETH_BUFF_AUTO_PTR   0
#define MDR_ETH_BUFF_FIFO       1

#define MDR_ETH_BUFF_LEN_TX     1514
#define MDR_ETH_MDIO_TIMEOUT    0x0004FFFFUL

#define MDR_ETH_DMA_CHANNEL_RX  MDR_DMA_CH_REQ_SOFT1
#define MDR_ETH_DMA_CHANNEL_TX  MDR_DMA_CH_REQ_SOFT2


//===========================  Soft I2C  ===========================
// "Отключение" программного SlaveI2C, чтобы собирался MDR_SoftI2C_byTimer, если драйвер MDR_SoftI2C_SlaveStates не подключен
#define I2C_SOFT_SLAVE_DISABLE   1

// "Отключение" программного MasterI2C, чтобы собирался MDR_SoftI2C_byTimer, если драйвер MDR_SoftI2C_MasterStates не подключен
#define I2C_SOFT_MASTER_DISABLE  0

//  Включение задержки после формирования СТОП, чтобы отложить следующий СТАРТ. 
//  Иначе SDA фронт-спад возможно "сливаются" слишком близко для какого нибудь ведомого и он их не поймет.
#define I2C_SOFT_STOP_DELAY_EN   0


#endif  //  MDR_CONFIG_VE8_H

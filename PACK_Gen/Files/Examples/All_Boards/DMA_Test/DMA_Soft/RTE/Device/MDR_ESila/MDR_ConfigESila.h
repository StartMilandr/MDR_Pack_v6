#ifndef MDR_CONFIG_ESila_H
#define MDR_CONFIG_ESila_H

#include <MDR_ESila.h>
  

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


#endif  //  MDR_CONFIG_ESila_H

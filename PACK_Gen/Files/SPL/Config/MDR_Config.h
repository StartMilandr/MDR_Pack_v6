#ifndef MDR_CONFIG_H
#define MDR_CONFIG_H

#if defined (USE_MDR1986VE91) || defined (USE_MDR1986VE92) || defined (USE_MDR1986VE93) || defined (USE_MDR1986VE94)
  #define USE_MDR1986VE9x
#endif

#if   defined (USE_MDR1986VE1)
  #include <MDR_1986VE1.h>
#elif defined (USE_MDR1986VE3)
  #include <MDR_1986VE3.h>
#elif defined (USE_MDR1986VE4)
  #include <MDR_1986VE4.h>
#elif defined (USE_MDR1986VE9x)
  #include <MDR_1986VE9x.h> 
#elif defined (USE_MDR1901VC1)
  #include <MDR_1901VC1.h>
#elif defined (USE_MDR1986VK214)
  #include <MDR_1986VK214.h>
#elif defined (USE_MDR1986VK234)
  #include <MDR_1986VK234.h>  
#endif

//=============  Защита пинов совмещенных с Jtag  ==================
// Писать в пины порта совмещенные с Jtag можно только 0.
// Иначе отладчик потеряет соединение. Активным может быть только один.
#if defined (USE_MDR1986VE9x) || defined (USE_MDR1901VC1)
  //#define USE_JTAG_A
  #define USE_JTAG_B
#endif

//================  Парамется подключенных осциляторов ================
//  Internal Generators
#define HSI_FREQ_HZ     (8000000UL)
#define HSI_FREQ_TRIM    MDR_BKP_HSI_TRIM_8M0Hz
#define HSI_TIMEOUT      0x0600UL   //#define HSI_TIMEOUT_MS  1

#define LSI_FREQ_HZ      (40000UL)
#define LSI_FREQ_TRIM    MDR_BKP_LSI_TRIM_40KHz
#define LSI_TIMEOUT      0x0600UL  //#define LSI_TIMEOUT_MS  80

//  External Generators
#define HSE_FREQ_HZ     (8000000UL)
#define HSE_TIMEOUT     0x8000UL

#define LSE_FREQ_HZ     (32768UL)
#define LSE_TIMEOUT     0x8000UL


//  External Generator for Ethernet PHY
#define HSE2_FREQ_HZ    (25000000UL)

#define HSE2_TIMEOUT_CYCLES  2400

//  PLL Ready Timeout
#define PLL_TIMEOUT_MS  100


#endif  //  MDR_CONFIG_H

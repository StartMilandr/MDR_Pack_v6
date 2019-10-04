#include <MDR_RST_Clock.h>
#include <MDR_Funcs.h>

#include <MDRB_LEDs.h>

#define  USE_MAX_CLOCK    1

#ifdef USE_MDR1986VE9x
  
  #define  DWT_AVAILABLE    1
  //  Длительность цикла для получения ~3мс в режиме MAX_CLK(-O2)
  #define LOOP_CYCLES_ASM       3
  #define LOOP_CYCLES_ASM_RAM   9
  #define LOOP_CYCLES_C         6
  #define LOOP_CYCLES_C_RAM    12
  #define LOOP_CYCLES_DWT       1
  
  //  РЕЗУЛЬТАТ на осциллографе (Compiler V5)
  //                  HSI(-O0)   HSI(-O2)    MAX_CLK(-O2)   MAX_CLK(-O0)
  //      ASM         3.09ms     3.09ms      3.00ms         3.03ms
  //  ASM_RAM         3.09ms     3.09ms      3.00ms         3.03ms
  //        C         4.08ms     3.06ms      3.00ms         4.01ms
  //    C_RAM              -          -      3.00ms              -
  //      DWT         3.09ms     3.09ms      3.00ms         3.03ms  

#elif defined USE_MDR1986VE4

  #define  DWT_AVAILABLE    0
  //  Длительность цикла для получения ~3мс в режиме MAX_CLK(-O2)
  #define LOOP_CYCLES_ASM       8
  #define LOOP_CYCLES_ASM_RAM   4
  #define LOOP_CYCLES_C        14
  #define LOOP_CYCLES_C_RAM     9
  
  
  //  РЕЗУЛЬТАТ на осциллографе (Compiler V5)
  //                  HSI(-O0)   HSI(-O2)    MAX_CLK(-O2)   MAX_CLK(-O0)
  //      ASM         3.21ms     3.21ms      2.94ms         2.94ms
  //  ASM_RAM         3.21ms     3.21ms      2.94ms         2.94ms
  //        C         3.96ms     3.21ms      2.94ms         3.52ms
  //    C_RAM              -          -      2.94ms              -
  //      DWT - НЕТ БЛОКА В ЯДРЕ!

#elif defined USE_MDR1986VE1

  #define  DWT_AVAILABLE    0
  //  Длительность цикла для получения ~3мс в режиме MAX_CLK(-O2)
  #define LOOP_CYCLES_ASM       4
  #define LOOP_CYCLES_ASM_RAM   8
  #define LOOP_CYCLES_C         9
  #define LOOP_CYCLES_C_RAM     16
  
  //  РЕЗУЛЬТАТ на осциллографе (Compiler V5)
  //                  HSI(-O0)   HSI(-O2)    MAX_CLK(-O2)   MAX_CLK(-O0)
  //      ASM         3.03ms     3.03ms      3.03ms         3.03ms
  //  ASM_RAM         3.03ms     3.03ms      3.03ms         3.03ms
  //        C         4.33ms     3.03ms      3.03ms         4.33ms
  //    C_RAM              -          -      3.03ms              -
  //      DWT - НЕТ БЛОКА В ЯДРЕ!

#elif defined USE_MDR1986VE8

  #define  DWT_AVAILABLE    1
  //  Длительность цикла для получения ~3мс в режиме MAX_CLK(-O2)
  #define LOOP_CYCLES_ASM       9
  #define LOOP_CYCLES_ASM_RAM   9
  #define LOOP_CYCLES_C         14
  #define LOOP_CYCLES_DWT       1
  
  //  РЕЗУЛЬТАТ на осциллографе (Compiler V5)
  //                  HSI(-O0)   HSI(-O2)    MAX_CLK(-O2)   MAX_CLK(-O0)
  //      ASM         3.34ms     3.34ms      3.00ms         3.03ms  - Проект запускается из ОЗУ, поэтому результат идентичный с ASM_RAM
  //  ASM_RAM         3.34ms     3.34ms      3.00ms         3.03ms  
  //        C         3.58ms     2.34ms      3.03ms         3.21ms
  //      DWT         3.34ms     3.34ms      3.00ms         3.00ms  
#endif


#define DELAY_US    3000


void MDR_DelayASM_RAM(uint32_t Ticks);
void MDR_DelayC_RAM(volatile uint32_t Ticks);


int main(void)
{  
#if USE_MAX_CLOCK
  //  Максимальная скорость тактирования
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDRB_CLK_PLL_HSE_RES_MAX;
  MDR_CPU_SetClock_PLL_HSE(&cfgPLL_HSE, true);  
#else    
  MDR_CPU_SetClock_HSI_def(false);  
#endif  
  
  uint32_t freqCPU_Hz = MDR_CPU_GetFreqHz(true); 
  MDRB_LED_Init(MDRB_LED_1);  

  uint32_t asmDelay     = US_TO_DELAY_LOOPS_EX(DELAY_US, freqCPU_Hz, LOOP_CYCLES_ASM);
  uint32_t asmDelayRAM  = US_TO_DELAY_LOOPS_EX(DELAY_US, freqCPU_Hz, LOOP_CYCLES_ASM_RAM);
  uint32_t cDelay       = US_TO_DELAY_LOOPS_EX(DELAY_US, freqCPU_Hz, LOOP_CYCLES_C);
  uint32_t cDelayRAM    = US_TO_DELAY_LOOPS_EX(DELAY_US, freqCPU_Hz, LOOP_CYCLES_C_RAM);
  
#if DWT_AVAILABLE
  uint32_t dwtDelay     = US_TO_DELAY_LOOPS_EX(DELAY_US, freqCPU_Hz, LOOP_CYCLES_DWT);  
  MDR_DelayDWT_Init();
#endif
  
  while (1)
  { 
    //  Asm Delay
    MDRB_LED_Set(MDRB_LED_1, 0);
    MDR_DelayASM(asmDelay);
    MDRB_LED_Set(MDRB_LED_1, 1);
    MDR_DelayASM(asmDelay);

    //  Asm Delay from RAM
    MDRB_LED_Set(MDRB_LED_1, 0);
    MDR_DelayASM_RAM(asmDelayRAM);
    MDRB_LED_Set(MDRB_LED_1, 1);
    MDR_DelayASM_RAM(asmDelayRAM);
    
    //  C Delay
    MDRB_LED_Set(MDRB_LED_1, 0);
    MDR_DelayC(cDelay);
    MDRB_LED_Set(MDRB_LED_1, 1);
    MDR_DelayC(cDelay);
    
    //  C Delay RAM
    MDRB_LED_Set(MDRB_LED_1, 0);
    MDR_DelayC_RAM(cDelayRAM);
    MDRB_LED_Set(MDRB_LED_1, 1);
    MDR_DelayC_RAM(cDelayRAM);  

#if DWT_AVAILABLE
    //  WDT Delay
    MDRB_LED_Set(MDRB_LED_1, 0);
    MDR_DelayDWT(dwtDelay);
    MDRB_LED_Set(MDRB_LED_1, 1);
    MDR_DelayDWT(dwtDelay);    
#endif

    //  New Cycle
    MDRB_LED_Set(MDRB_LED_1, 0);    
    MDR_DelayC(cDelay);
    MDR_DelayC(cDelay);    
    MDRB_LED_Set(MDRB_LED_1, 1);
    MDR_DelayC(cDelay);    
    MDR_DelayC(cDelay);    
  }  
}

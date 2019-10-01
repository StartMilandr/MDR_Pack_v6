#include <MDR_RST_Clock.h>
#include <MDR_Funcs.h>

#include <MDRB_LEDs.h>

#define  USE_MAX_CLOCK    1

#ifdef USE_MDR1986VE9x
  
  #define  DWT_AVAILABLE    1
  
  #define LOOP_CYCLES_ASM       3
  #define LOOP_CYCLES_ASM_RAM   8
  #define LOOP_CYCLES_C         8
  #define LOOP_CYCLES_DWT       1
  
  //  РЕЗУЛЬТАТ на осциллографе (Compiler V5)
  //                  HSI(-O0)   HSI(-O2)    MAX_CLK(-O2)   MAX_CLK(-O0)
  //      ASM         3.09ms     3.09ms      3.00ms         3.03ms
  //  ASM_RAM         3.40ms     3.40ms      3.34ms         3.34ms
  //        C         3.09ms     2.35ms      2.22ms         3.03ms
  //      DWT         3.09ms     3.09ms      3.09ms         3.03ms  

#elif defined USE_MDR1986VE4

  #define  DWT_AVAILABLE    0
  
  #define LOOP_CYCLES_ASM       8
  #define LOOP_CYCLES_ASM_RAM   4
  #define LOOP_CYCLES_C        18
  
  //  РЕЗУЛЬТАТ на осциллографе (Compiler V5)
  //                  HSI(-O0)   HSI(-O2)    MAX_CLK(-O2)   MAX_CLK(-O0)
  //      ASM         3.21ms     3.21ms      2.97ms         2.90ms
  //  ASM_RAM         3.21ms     3.21ms      2.97ms         2.90ms
  //        C         3.03ms     2.53ms      2.29ms         2.78ms
  //      DWT - НЕТ БЛОКА В ЯДРЕ!

#elif defined USE_MDR1986VE1

  #define  DWT_AVAILABLE    0
  
  #define LOOP_CYCLES_ASM       4
  #define LOOP_CYCLES_ASM_RAM   8
  #define LOOP_CYCLES_C        12
  
  //  РЕЗУЛЬТАТ на осциллографе (Compiler V5)
  //                  HSI(-O0)   HSI(-O2)    MAX_CLK(-O2)   MAX_CLK(-O0)
  //      ASM         3.03ms     3.03ms      3.03ms         3.03ms
  //  ASM_RAM         3.03ms     3.03ms      3.03ms         3.34ms
  //        C         3.28ms     2.04ms      2.04ms         3.28ms    - При -О2 длительность 3,03ms при LOOP_CYCLES_C = 8
  //      DWT - НЕТ БЛОКА В ЯДРЕ!

#elif defined USE_MDR1986VE8

  #define  DWT_AVAILABLE    1
  
  #define LOOP_CYCLES_ASM       10
  #define LOOP_CYCLES_ASM_RAM   10
  #define LOOP_CYCLES_C         16
  #define LOOP_CYCLES_DWT       1
  
  //  РЕЗУЛЬТАТ на осциллографе (Compiler V5)
  //                  HSI(-O0)   HSI(-O2)    MAX_CLK(-O2)   MAX_CLK(-O0)
  //      ASM         3.03ms     3.00ms      2.72ms         2.72ms  - Проект запускается из ОЗУ, поэтому результат идентичный с ASM_RAM
  //  ASM_RAM         3.03ms     3.00ms      2.72ms         2.72ms  
  //        C         3.03ms     2.90ms      2.66ms         2.84ms
  //      DWT         3.34ms     3.34ms      3.00ms         3.00ms  

#endif


#define DELAY_US    3000
#define US_TO_LOOPS(mSec, CPU_FregHz, LoopCycles)     ((uint32_t)((double)(mSec) * (CPU_FregHz) / LoopCycles / 1000000 ))

__asm void MDR_DelayASM_RAM(uint32_t Ticks);

__asm void MDR_DelayASM(uint32_t Ticks)
{
           CMP   r0,#0x00
           BEQ   __Exit
           NOP   
__NextLoop SUBS  r0,r0,#1
           BNE   __NextLoop
__Exit BX  lr
}

void MDR_DelayC(uint32_t Ticks)
{
  volatile uint32_t i = Ticks;
  if (i)
    while (--i);  
}

int main(void)
{
  MDR_Delay(2000000);

#if USE_MAX_CLOCK
  //  Максимальная скорость тактирования
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDRB_CLK_PLL_HSE_RES_MAX;
  MDR_CPU_SetClock_PLL_HSE(&cfgPLL_HSE, true);  
#else    
  MDR_CPU_SetClock_HSI_def(false);  
#endif  
  
  uint32_t freqCPU_Hz = MDR_CPU_GetFreqHz(true); 
  MDRB_LED_Init(MDRB_LED_1);  

  uint32_t asmDelay     = US_TO_LOOPS(DELAY_US, freqCPU_Hz, LOOP_CYCLES_ASM);
  uint32_t asmDelayRAM  = US_TO_LOOPS(DELAY_US, freqCPU_Hz, LOOP_CYCLES_ASM_RAM);
  uint32_t cDelay       = US_TO_LOOPS(DELAY_US, freqCPU_Hz, LOOP_CYCLES_C);
#if DWT_AVAILABLE
  uint32_t dwtDelay     = US_TO_LOOPS(DELAY_US, freqCPU_Hz, LOOP_CYCLES_DWT);  
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

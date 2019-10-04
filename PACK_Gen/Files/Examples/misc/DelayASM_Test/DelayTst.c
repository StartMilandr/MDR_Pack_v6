#include <stdint.h>

void MDR_DelayC_RAM(volatile uint32_t Ticks)
{
  if (Ticks)
    while(--Ticks);  
}


#if   defined (__CC_ARM)

__asm void MDR_DelayASM_RAM(uint32_t Ticks)
{
           CMP   r0,#0x00
           BEQ   __Exit
           NOP   
__NextLoop SUBS  r0,r0,#1
           BNE   __NextLoop
__Exit BX  lr
}

#elif (__ARMCC_VERSION >= 6010050)
//  __attribute__((naked)) void MDR_DelayASM_RAM(uint32_t Ticks)
//  {
//    __asm("CMP   r0,#0x00");
//    __asm("BEQ   __Exit");
//    __asm("NOP");
//    __asm("__NextLoop: SUBS  r0,r0,#1");
//    __asm("BNE   __NextLoop");
//    __asm("__Exit: BX  lr");
//  }

__attribute__((naked)) void MDR_DelayASM_RAM(uint32_t Ticks)
{
  __asm(
  "  CMP   r0,#0x00     ;\n"
  "  BEQ   1f           ;\n"
  "  NOP                ;\n"
  "0:                   ;\n"
  "  SUBS  r0,r0,#1     ;\n"
  "  BNE   0b           ;\n"
  "1:                   ;\n"
  "  BX  lr             ;\n"
  );
}

#endif
















#include <stdint.h>

__asm void MDR_DelayASM_RAM(uint32_t Ticks)
{
           CMP   r0,#0x00
           BEQ   __Exit
           NOP   
__NextLoop SUBS  r0,r0,#1
           BNE   __NextLoop
__Exit BX  lr
}

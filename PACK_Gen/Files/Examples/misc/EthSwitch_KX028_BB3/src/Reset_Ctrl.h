#ifndef RESET_CTRL_H
#define RESET_CTRL_H

#include <MDR_GPIO.h>
#include "board_defs.h"

void ResetCtrlInit(void);
void ResetApply(uint32_t selPins, uint32_t delayTicks);

__STATIC_INLINE void ResetApplyAll(uint32_t delayTicks) 
{ 
  ResetApply(RESET_PINS_ALL, delayTicks); 
}

#endif  //RESET_CTRL_H

#include "Reset_Ctrl.h"

void ResetCtrlInit(void)
{
  MDR_GPIO_Enable(RESET_PORT);
  MDR_GPIO_Init_PortOUT(RESET_PORT, RESET_PINS_ALL, MDR_PIN_SLOW);  
  MDR_GPIO_SetPins(RESET_PORT, RESET_PINS_ALL);
}

void ResetApply(uint32_t selPins, uint32_t delayTicks)
{
  MDR_GPIO_ClearPins(RESET_PORT, selPins | RESETB_PIN_EPHY);
  MDR_Delay(delayTicks);
  MDR_GPIO_SetPins(RESET_PORT, selPins & (~RESETB_PIN_EPHY));
}

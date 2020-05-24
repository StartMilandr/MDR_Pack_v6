#include <MDR_Config.h>
#include <MDR_RST_Clock.h>
#include <MDR_GPIO.h>
#include "board_defs.h"

#include "BB3_Ctrl.h"
#include "KX028_Ctrl.h"
#include "ePHY_Ctrl.h"
#include "Reset_Ctrl.h"




int main(void)
{
  //  Максимальная скорость тактирования
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDRB_CLK_PLL_HSE_RES_MAX;
  MDR_CPU_SetClock_PLL_HSE(&cfgPLL_HSE, true);
  uint32_t freqCPU_Hz = MDR_CPU_GetFreqHz(true);  
  
  //  Enable Reset 
  ResetCtrlInit();
  ResetApplyAll(MS_TO_DELAY_LOOPS(freqCPU_Hz, RESET_APPLY_DELAY_MS));
  //  ePHY Open
  ePHY_VE1_Init(freqCPU_Hz);
  ePHY_VE1_Open();
  //  SPI Controls Init
  BB3_SPI_Init(); 
  KX028_SPI_Init(freqCPU_Hz);
  
  MDR_1923KX028_Mode modeKX028 = KX028_GetMode();
  switch (modeKX028) {
    case MDR_1923KX028_Mode0_PCIe: break;
    case MDR_1923KX028_Mode1_ExtFlash: break;
    case MDR_1923KX028_Mode2_SlaveSPI: break;
    case MDR_1923KX028_Mode3_Uncontrolled: break;
  }
  
  while(1)
  {
  
  }
}








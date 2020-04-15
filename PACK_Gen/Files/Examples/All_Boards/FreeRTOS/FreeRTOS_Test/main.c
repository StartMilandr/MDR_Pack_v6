#include <MDR_Config.h>
#include <MDR_RST_Clock.h>
#include <MDR_Funcs.h>
#include <MDRB_LEDs.h>
#include <MDRB_LCD.h>

#include "FreeRTOS.h"
#include "task.h"

#define LED_ALL   MDRB_LED_1 | MDRB_LED_2 | MDRB_LED_3 | MDRB_LED_4

void FreeRTOS_DemoExample_CORTEX_STM32F103_Keil(void);

int main(void)
{
  //  Максимальная скорость тактирования
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDRB_CLK_PLL_HSE_RES_MAX;
  MDR_CPU_SetClock_PLL_HSE(&cfgPLL_HSE, true);
  uint32_t freqCPU_Hz = MDR_CPU_GetFreqHz(true);
	
	
  MDRB_LED_Init(LED_ALL);
  MDRB_LED_Set(LED_ALL, true);
  MDRB_LCD_Init(freqCPU_Hz);
  
  FreeRTOS_DemoExample_CORTEX_STM32F103_Keil();
}



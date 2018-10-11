#include <MDR_GPIO.h>
#include <MDR_Funcs.h>
#include <MDR_Config.h>
#include <MDR_SysTimer.h>
#include <MDRB_LEDs.h>

//  Мигание только одной кнопкой, если второй нет
//  В этом случае мигание будет не равномерное, поскольку светодиод будет переключаться и в цикле, и от системного таймера
#ifndef MDRB_LED_2
  #define MDRB_LED_2  MDRB_LED_1
#endif

#define PERIOD_MS     1000
#define LED_CYCLE     MDRB_LED_1
#define LED_TIMER     MDRB_LED_2
#define DEBOUNCE_MS   10

void SysTick_Handler(void);

int main(void)
{ 
  MDRB_LED_InitALL();
  
  MDRB_LED_Set(MDRB_LED_PinAll, true);
  MDR_Delay_ms(PERIOD_MS, HSI_FREQ_HZ);
  MDRB_LED_Set(MDRB_LED_PinAll, false);
  
  MDR_SysTimerStart_ms(PERIOD_MS, HSI_FREQ_HZ);
  
  while (1)
  {    
    MDRB_LED_Switch(LED_CYCLE);
    MDR_Delay_ms(PERIOD_MS, HSI_FREQ_HZ);
  }
}

void SysTick_Handler(void)
{
  MDRB_LED_Switch(LED_TIMER);
}


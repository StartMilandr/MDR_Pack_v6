#include <MDR_Config.h>
#include <MDR_RST_Clock.h>
#include <MDR_Funcs.h>
#include <MDRB_LEDs.h>

//#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"

void vLedTask(void *argument);

typedef struct {
  uint32_t   ledMask;
  TickType_t taskSleep;  
} ledTaskCfg;


#ifdef MDRB_LED_4
  ledTaskCfg ledTask1 = {.ledMask = MDRB_LED_1, .taskSleep = 125};
  ledTaskCfg ledTask2 = {.ledMask = MDRB_LED_2, .taskSleep = 250};
  ledTaskCfg ledTask3 = {.ledMask = MDRB_LED_3, .taskSleep = 500};
  ledTaskCfg ledTask4 = {.ledMask = MDRB_LED_4, .taskSleep = 1000};
  #define LED_ALL   MDRB_LED_1 | MDRB_LED_2 | MDRB_LED_3 | MDRB_LED_4
#elif defined(MDRB_LED_2)
  ledTaskCfg ledTask1 = {.ledMask = MDRB_LED_1, .taskSleep = 125};
  ledTaskCfg ledTask2 = {.ledMask = MDRB_LED_2, .taskSleep = 250};
  #define LED_ALL   MDRB_LED_1 | MDRB_LED_2
#else
  ledTaskCfg ledTask1 = {.ledMask = MDRB_LED_1, .taskSleep = 125};
  #define LED_ALL   MDRB_LED_1
#endif

int main(void)
{
  //  Максимальная скорость тактирования
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDRB_CLK_PLL_HSE_RES_MAX;
  MDR_CPU_SetClock_PLL_HSE(&cfgPLL_HSE, true);
  uint32_t freqCPU_Hz = MDR_CPU_GetFreqHz(true);
	
	
  MDRB_LED_Init(LED_ALL);
  MDRB_LED_Set(LED_ALL, true);
  
  //  FreeRTOS init tasks and Run  
  xTaskCreate(vLedTask, "Led1", configMINIMAL_STACK_SIZE, &ledTask1, tskIDLE_PRIORITY + 1, NULL);  
#ifdef MDRB_LED_2    
  xTaskCreate(vLedTask, "Led2", configMINIMAL_STACK_SIZE, &ledTask2, tskIDLE_PRIORITY + 1, NULL);
#endif  
#ifdef MDRB_LED_4  
  xTaskCreate(vLedTask, "Led3", configMINIMAL_STACK_SIZE, &ledTask3, tskIDLE_PRIORITY + 1, NULL);
  xTaskCreate(vLedTask, "Led4", configMINIMAL_STACK_SIZE, &ledTask4, tskIDLE_PRIORITY + 1, NULL);
#endif 

  vTaskStartScheduler();  
}


void vLedTask(void *argument)
{
  ledTaskCfg *ledTask = (ledTaskCfg *)argument;
  while(1)
  {
      MDRB_LED_Toggle(ledTask->ledMask);
      vTaskDelay(ledTask->taskSleep);
  }
}

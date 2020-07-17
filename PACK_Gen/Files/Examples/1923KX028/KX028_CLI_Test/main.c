#include <MDR_Config.h>
#include <MDR_RST_Clock.h>
#include <MDR_GPIO.h>
#include <MDR_UART.h>

#include "KX028_CLI.h"


//  Таймаут ожиданиz окончания операции, в количествах чтения регистра статуса
#define TABLES_TIMEOUT_READY_READS       100


int main(void)
{
  //  Максимальная скорость тактирования
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDRB_CLK_PLL_HSE_RES_MAX;
  MDR_CPU_SetClock_PLL_HSE(&cfgPLL_HSE, true);
  uint32_t freqCPU_Hz = MDR_CPU_GetFreqHz(true);  

  //  CLI
  KX028_InitCLI(UART_BAUD_115200, freqCPU_Hz);     
  while(1)
  {
    //  Команды с COM порта
    KX028_ProcessCLI(TABLES_TIMEOUT_READY_READS); 
  }
}


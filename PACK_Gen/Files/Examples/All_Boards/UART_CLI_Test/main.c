#include <MDR_RST_Clock.h>
#include <MDRB_Buttons.h>
#include <MDRB_LEDs.h>
#include <MDR_Funcs.h>
#include <MDR_UART_CLI.h>
#include <MDRB_UART_PinSelect.h>

int main(void)
{
  MDR_DebugerProtectDelay();
  
  //  Максимальная скорость тактирования 96MHz
  MDR_CLK_Enable_RST_BPK();
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDRB_CLK_PLL_HSE_RES_MAX; 
  MDR_CPU_SetClock_PLL_HSE(&cfgPLL_HSE, true);
  uint32_t freqCPU_Hz = MDR_CPU_GetFreqHz(true);
  
  MDRB_LED_InitALL();
  
  //  CLI Init
	MDR_UART_CfgPinsGPIO pinsGPIO = {
		.pPinTX = &MDRB_UART_PinTX,
    .pPinRX = &MDRB_UART_PinRX,	
	};  
  MDR_CLI_UART_Init(UART_BAUD_115200, freqCPU_Hz, &pinsGPIO);  

  CLI_CMD_e cliCMD;
  uint8_t  cliParamLen;
  uint8_t *pCliParams;
  
  while (1)
  {   
    cliCMD = MDR_CLI_GetCommand(&cliParamLen, &pCliParams);
    switch (cliCMD) {
      case cliCMD_NONE: break;
      case cliCMD_LedShow: 
        MDRB_LED_Set(MDRB_LED_SelIndToMask(pCliParams[0]), true); 
        MDR_CLI_SetResponse(cliCMD, 0, NULL);
        break; 
      case cliCMD_LedHide: 
        MDRB_LED_Set(MDRB_LED_SelIndToMask(pCliParams[0]), false); 
        MDR_CLI_SetResponse(cliCMD, 0, NULL);
        break;
      case cliCMD_LedOut:  
        LED_SetOut(pCliParams[0]); 
        MDR_CLI_SetResponse(cliCMD, 0, NULL);
        break;
      case cliCMD_Echo:
      case cliCMD_ERROR: 
      default: // Send Echo
        MDR_CLI_SetResponse(cliCMD, cliParamLen, pCliParams);
    }
  }  
  
}


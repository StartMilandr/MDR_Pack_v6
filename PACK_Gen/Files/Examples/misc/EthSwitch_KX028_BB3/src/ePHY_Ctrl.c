#include "ePHY_Ctrl.h"

#include <MDR_Funcs.h>
//#include <MDR_GPIO.h>
#include <MDR_JTAG_GPIO.h>

#include "board_defs.h"

 
void ePHY_VE1_Init(uint32_t freqCPU_Hz)
{
  MDR_GPIO_CfgPinPort pCfgTRST = {.portGPIO = EPHY_JTAG_PORT, .selPins = EPHY_JTAG_TRST};
  MDR_JTAG_Cfg cfgJTAG = {
    //  Pins defs
    .cfgTCK = {.portGPIO = EPHY_JTAG_PORT, .selPins = EPHY_JTAG_TCK},
    .cfgTMS = {.portGPIO = EPHY_JTAG_PORT, .selPins = EPHY_JTAG_TMS},
    .cfgTDI = {.portGPIO = EPHY_JTAG_PORT, .selPins = EPHY_JTAG_TDI},
    .cfgTDO = {.portGPIO = EPHY_JTAG_PORT, .selPins = EPHY_JTAG_TDO},
    .pCfgTRST = &pCfgTRST,
    //  Clock width delay for MDR_Delay
    .widthTCK_Ticks = CLOCKS_TO_DELAY_LOOPS((double)freqCPU_Hz / EPHY_JTAG_FREQ_HZ) / 2 + 1,
    .funcWaitTicks = MDR_Delay,
  };

  MDR_JTAG_Init(&cfgJTAG);
}

void ePHY_VE1_Open(void)
{
  MDR_JTAG_ResetAndParking();
  MDR_JTAG_WriteIR(MDR_1986VE1_JTAG_OPEN_EthPHY_IR_LEN, MDR_1986VE1_JTAG_OPEN_EthPHY_IR);
}


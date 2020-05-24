#include "BB3_Ctrl.h"
#include "board_defs.h"

#include <MDR_5600BB3.h>


static MDR_SSP_Type      *spiBB3;

void BB3_SPI_Init(void)
{
  //  5600BB3 SPI
  MDR_SSP_Rates spiRates = {
    .divSCR_0_255 = BB3_SPI_DivSCR_0_255,      // 0 - 255, Serial Clock Rate
    .divPSR_2_254 = BB3_SPI_DivPSR_2_254};     // 2 - 254, EVEN ONLY! Clock prescaller
      
  MDR_SSP_CfgPinGPIO pinCLK = {.portGPIO = BB3_SPI_PORT, .pinIndex = BB3_SPI_SCL, .pinFunc = BB3_SPI_CLK_FUNC};
  MDR_SSP_CfgPinGPIO pinTX  = {.portGPIO = BB3_SPI_PORT, .pinIndex = BB3_SPI_TX,  .pinFunc = BB3_SPI_TX_FUNC};
  MDR_SSP_CfgPinGPIO pinRX  = {.portGPIO = BB3_SPI_PORT, .pinIndex = BB3_SPI_RX,  .pinFunc = BB3_SPI_RX_FUNC};
  MDR_SSP_CfgPinGPIO pinFSS = {.portGPIO = BB3_SPI_PORT, .pinIndex = BB3_SPI_FSS, .pinFunc = BB3_SPI_FSS_FUNC};    
    
  MDR_SSP_CfgPinsGPIO spiPins = {
    .pPinCLK = &pinCLK,
    .pPinTX  = &pinTX,
    .pPinRX  = &pinRX,
    .pPinFSS = &pinFSS,
  };
    
  spiBB3 = MDR_5600BB3_Init(BB3_SPI, spiRates, &spiPins, BB3_SPI_POWER);
}

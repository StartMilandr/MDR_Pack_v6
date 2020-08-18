#include "KX028_Ctrl.h"

#include <MDR_Funcs.h>
#include <MDR_GPIO.h>
#include "MDRB_Basis_v2.h"

//static MDR_1923KX028_Obj  _spiKX028;


void KX028_SPI_Init(uint32_t freqCPU_Hz)
{
  //  KX028 SPI      
  MDR_SSP_CfgPinGPIO pinCLK = {.portGPIO = KX028_SPI_PORT, .pinIndex = KX028_SPI_SCL, .pinFunc = KX028_SPI_CLK_FUNC};
  MDR_SSP_CfgPinGPIO pinTX  = {.portGPIO = KX028_SPI_PORT, .pinIndex = KX028_SPI_TX,  .pinFunc = KX028_SPI_TX_FUNC};
  MDR_SSP_CfgPinGPIO pinRX  = {.portGPIO = KX028_SPI_PORT, .pinIndex = KX028_SPI_RX,  .pinFunc = KX028_SPI_RX_FUNC};
  MDR_SSP_CfgPinGPIO pinFSS = {.portGPIO = KX028_SPI_PORT, .pinIndex = KX028_SPI_FSS, .pinFunc = KX028_SPI_FSS_FUNC};    

  MDR_1923KX028_Cfg cfgKX028 =  {
    .divSCR_0_255 = KX028_SPI_DivSCR_0_255,
    .divPSR_2_254 = KX028_SPI_DivPSR_2_254,
    .pPinCLK      = &pinCLK,
    .pPinTX       = &pinTX,
    .pPinRX       = &pinRX,
    .pPinManualCS = &pinFSS,        
    .pinsPower    = KX028_SPI_POWER,
    .ticksDelayCS = NS_TO_DELAY_LOOPS(0, freqCPU_Hz),
  } ;
  
  //_spiKX028 = MDR_1923KX028_Init(KX028_SPI, &cfgKX028);
  MDR_KX028_Init(KX028_SPI, &cfgKX028);
  //  Частота SSP_Clock для SPI
  MDR_SSPex_SetSSPClock_InpPLLCPU(MDR_SSP1ex, MDR_Div128P_div1);  
}

static inline void KX028_ModePins_Init(void)
{
  MDR_GPIO_Enable(KX028_MODE_PORT);
  MDR_GPIO_Init_PortIN(KX028_MODE_PORT, KX028_MODE_PINS_ALL);  
}

static inline void KX028_ModePins_Deinit(void)
{
  MDR_GPIO_InitAnalog(KX028_MODE_PORT, KX028_MODE_PINS_ALL);  
}

uint32_t KX028_GetModePins(void)
{
  KX028_ModePins_Init();
  uint32_t result = MDR_GPIO_Get(KX028_MODE_PORT);
  result = (result & KX028_MODE_PINS_Msk) >> KX028_MODE_PINS_Pos;
  
  KX028_ModePins_Deinit();  
  
  return result;
}


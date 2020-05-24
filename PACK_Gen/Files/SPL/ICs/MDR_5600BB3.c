#include "MDR_5600BB3.h"



MDR_SSP_Type* MDR_5600BB3_Init(const MDR_SSP_TypeEx *exSSPx, MDR_SSP_Rates spiRates, const MDR_SSP_CfgPinsGPIO *spiPins, MDR_PIN_PWR pinsPower)
{
  //  SPI Init  
  MDR_SSP_Config cfgSSP = {
    .DataBits     = SSP_DataBits_16,
    .FrameFormat  = SSP_Frame_SPI,
    .SPI_Mode     = SPI_CPHA0_CPOL0,
    .DivSCR_0_255 = spiRates.divSCR_0_255,
    .DivPSR_2_254 = spiRates.divPSR_2_254,
  };  
  MDR_SSPex_Init(exSSPx, &cfgSSP);
  MDR_SSPex_EnableMaster(exSSPx, false);
  
  //  Init SPI Pins  
  MDR_SSP_InitPinsGPIO(spiPins, pinsPower);
  return exSSPx->SSPx;
}


//  --------------   MAC Table Control  -------------------
#define SUB_REG_ENUM(regID, decr)     (MDR_5600BB3_Reg)((uint8_t)(regID) - (decr))

bool MDR_5600BB3_TableMAC_Write(MDR_SSP_Type *SSPx, uint16_t tableIndex, const MDR_5600BB3_TableMAC_Item *itemMac, uint16_t timeoutRdStatusCnt)
{
  uint32_t i;
  
  //  Write ItemMAC to RamData Registers
  for (i = 0; i < 6; ++i)
    MDR_5600BB3_Write(SSPx, SUB_REG_ENUM(MDR_5600BB3_regRamData5, i), itemMac->srcMAC[i]);  
  MDR_5600BB3_Write(SSPx, MDR_5600BB3_regRamData6, itemMac->Ctrl);
  MDR_5600BB3_Write(SSPx, MDR_5600BB3_regRamData7, itemMac->Ctrl >> 8);

  // Write AddrLo
  MDR_5600BB3_Write(SSPx, MDR_5600BB3_regRamCtrl1, tableIndex);
  // Write AddrHi and start writing from RamData registers to Memory
  uint8_t regCtrl0 = (tableIndex >> 8) | MDR_5600BB3_RamCtrl0_SPI_EN_Msk | MDR_5600BB3_RamCtrl0_SPI_WE_nRD_Msk;
  MDR_5600BB3_Write(SSPx, MDR_5600BB3_regRamCtrl0, regCtrl0);

  //  Wait internal write completed
  while (--timeoutRdStatusCnt)
  {
    regCtrl0 = MDR_5600BB3_Read(SSPx, MDR_5600BB3_regRamCtrl0);
    if ((regCtrl0 & MDR_5600BB3_RamCtrl0_SPI_EN_Msk) == 0)
      return true;
  }
  
  return false;
}


bool MDR_5600BB3_TableMAC_Read(MDR_SSP_Type *SSPx, uint16_t tableIndex, MDR_5600BB3_TableMAC_Item *itemMac, uint16_t timeoutRdStatusCnt)
{ 
  uint32_t i;

  // Write AddrLo
  MDR_5600BB3_Write(SSPx, MDR_5600BB3_regRamCtrl1, tableIndex);
  // Write AddrHi and start reading to RamData registers from Memory
  uint8_t regCtrl0 = (tableIndex >> 8) | MDR_5600BB3_RamCtrl0_SPI_EN_Msk;
  MDR_5600BB3_Write(SSPx, MDR_5600BB3_regRamCtrl0, regCtrl0);
  
  //  Wait internal Read completed
  bool result;
  while (true)
  {
    regCtrl0 = MDR_5600BB3_Read(SSPx, MDR_5600BB3_regRamCtrl0);
    result = (regCtrl0 & MDR_5600BB3_RamCtrl0_SPI_EN_Msk) == 0;
    if (result)
      break;
    else if (timeoutRdStatusCnt == 0)
      return false;
    
    --timeoutRdStatusCnt;
  }
  
  //  Read from RamData registers
  for (i = 0; i < 6; ++i)
    itemMac->srcMAC[i] = MDR_5600BB3_Read(SSPx, SUB_REG_ENUM(MDR_5600BB3_regRamData5, i));  
  itemMac->Ctrl  = MDR_5600BB3_Read(SSPx, MDR_5600BB3_regRamData6);
  itemMac->Ctrl |= MDR_5600BB3_Read(SSPx, MDR_5600BB3_regRamData7) << 8;
  
  return true;
}

uint16_t MDR_5600BB3_TableMAC_CalcIndex(uint8_t *MAC, uint8_t userSubIndex)
{
  uint32_t i;
  uint16_t result = 0;
  
  //  Calc Hash
  for (i = 0; i < 6; ++i)
		result ^= MAC[0];

	result = (result << MDR_5600BB3_MAC_ADDR_HASH_Pos) | (userSubIndex & MDR_5600BB3_MAC_ADDR_USER_Msk);
  return result;
}

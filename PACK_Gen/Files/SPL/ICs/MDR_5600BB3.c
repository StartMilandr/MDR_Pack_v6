#include <MDR_5600BB3.h>
#include <MDR_Funcs.h>



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
  //  Подача SSP_Clock на SPI - ПОДАТЬ СНАРУЖИ!
  //MDR_SSPex_SetSSPClock_InpPLLCPU(exSSPx, MDR_Div128P_div1);    
  MDR_SSPex_EnableMaster(exSSPx, false);
  
  //  Init SPI Pins  
  MDR_SSP_InitPinsGPIO(spiPins, pinsPower);
  return exSSPx->SSPx;
}


//  --------------   MAC Table Control  -------------------
bool MDR_5600BB3_TableMAC_Write(MDR_SSP_Type *SSPx, uint16_t tableIndex, const MDR_5600BB3_TableMAC_Item *itemMac, uint16_t timeoutRdStatusCnt)
{
  uint32_t i;
  
  //  Write ItemMAC to RamData Registers 
  uint8_t *pData8 = (uint8_t *)itemMac;
  for (i = 0; i < 8; ++i)
    MDR_5600BB3_WriteAddr(SSPx, ((uint8_t)MDR_5600BB3_regRamData1) + i, pData8[i]);  

  // Write AddrLo
  MDR_5600BB3_Write(SSPx, MDR_5600BB3_regRamCtrl1, tableIndex);
  // Write AddrHi and start writing from RamData registers to Memory
  uint8_t regCtrl0 = ((tableIndex >> MDR_5600BB3_RamCtrl0_RAM_AddrHi_Shift) & MDR_5600BB3_RamCtrl0_RAM_AddrHi_Msk) 
                     | MDR_5600BB3_RamCtrl0_SPI_EN_Msk | MDR_5600BB3_RamCtrl0_SPI_WE_nRD_Msk;
  MDR_5600BB3_Write(SSPx, MDR_5600BB3_regRamCtrl0, regCtrl0);

  //  Wait internal write completed
  MDR_Delay(1000);
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
  // Write AddrLo
  MDR_5600BB3_Write(SSPx, MDR_5600BB3_regRamCtrl1, tableIndex);
  // Write AddrHi and start reading to RamData registers from Memory
  uint8_t regCtrl0 = ((tableIndex >> MDR_5600BB3_RamCtrl0_RAM_AddrHi_Shift) & MDR_5600BB3_RamCtrl0_RAM_AddrHi_Msk) | MDR_5600BB3_RamCtrl0_SPI_EN_Msk;
  MDR_5600BB3_Write(SSPx, MDR_5600BB3_regRamCtrl0, regCtrl0);
  
  //  Wait internal Read completed
  //MDR_Delay(1000);  
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
  uint8_t *pData8 = (uint8_t *)itemMac;
  uint32_t i;  
  for (i = 0; i < 8; ++i)
    pData8[i] = MDR_5600BB3_ReadAddr(SSPx, ((uint8_t)MDR_5600BB3_regRamData1) + i);  
  
  return true;
}


bool MDR_5600BB3_TableMAC_ReadRAW(MDR_SSP_Type *SSPx, uint16_t tableIndex, uint8_t *data, uint16_t timeoutRdStatusCnt)
{ 
  // Write AddrLo
  MDR_5600BB3_Write(SSPx, MDR_5600BB3_regRamCtrl1, tableIndex);
  // Write AddrHi and start reading to RamData registers from Memory
  uint8_t regCtrl0 = ((tableIndex >> MDR_5600BB3_RamCtrl0_RAM_AddrHi_Shift) & MDR_5600BB3_RamCtrl0_RAM_AddrHi_Msk) | MDR_5600BB3_RamCtrl0_SPI_EN_Msk;
  MDR_5600BB3_Write(SSPx, MDR_5600BB3_regRamCtrl0, regCtrl0);
  
  //  Wait internal Read completed
  //MDR_Delay(1000);  
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
  uint32_t i;  
  for (i = 0; i < 8; ++i)
    data[i] = MDR_5600BB3_ReadAddr(SSPx, ((uint8_t)MDR_5600BB3_regRamData1) + i);  
    
  return true;
}

uint16_t MDR_5600BB3_TableMAC_CalcIndex(uint8_t *MAC, uint8_t userSubIndex)
{
  uint32_t i;
  uint16_t result = 0;
  
  //  Calc Hash
  for (i = 0; i < 6; ++i)
		result ^= MAC[i];

	result = (result << MDR_5600BB3_MAC_ADDR_HASH_Pos) | (userSubIndex & MDR_5600BB3_MAC_ADDR_USER_Msk);
  return result;
}

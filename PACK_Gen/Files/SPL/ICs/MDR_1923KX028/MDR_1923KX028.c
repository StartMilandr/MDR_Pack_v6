#include <MDR_1923KX028.h>


// Инициализация SPI для общения с 1923KX028
MDR_1923KX028_Obj  MDR_1923KX028_Init(const MDR_SSP_TypeEx *exSSPx, MDR_1923KX028_Cfg *cfg)
{
  //  SPI Init  
  MDR_SSP_Config cfgSSP = {
    .DataBits     = SSP_DataBits_8,
    .FrameFormat  = SSP_Frame_SPI,
    .SPI_Mode     = SPI_CPHA0_CPOL0,
    .DivSCR_0_255 = cfg->divSCR_0_255,
    .DivPSR_2_254 = cfg->divPSR_2_254,
  };  
  MDR_SSPex_Init(exSSPx, &cfgSSP);
  MDR_SSPex_EnableMaster(exSSPx, false);

  //  SPI Pins Init
  MDR_SSP_CfgPinsGPIO spiPins = {  
    .pPinCLK = cfg->pPinCLK,
    .pPinTX = cfg->pPinTX,
    .pPinRX = cfg->pPinRX,
    .pPinFSS = NULL,
  };
  MDR_SSP_InitPinsGPIO(&spiPins, cfg->pinsPower);
    
  //  CS Manual PinInit
  MDR_PinDig_GroupPinCfg pinPermRegs;  
  MDR_GPIO_Enable(cfg->pPinManualCS->portGPIO);
  MDR_Port_InitDigGroupPinCfg(MDR_Off, cfg->pinsPower, MDR_Off, MDR_Off, &pinPermRegs);
  MDR_GPIO_InitDigPin(cfg->pPinManualCS->portGPIO, cfg->pPinManualCS->pinIndex, MDR_Pin_Out, MDR_PIN_PORT, &pinPermRegs);  

  // Result
  MDR_1923KX028_Obj result = {
    .SSPx         = exSSPx->SSPx,
    .CS_Port      = cfg->pPinManualCS->portGPIO->PORTx, 
    .CS_PinSel    = (uint32_t)(1UL << cfg->pPinManualCS->pinIndex),
    .ticksDelayCS = cfg->ticksDelayCS
  };

  return result; 
}


void MDR_1923KX028_CS_SetActive(const MDR_1923KX028_Obj *objKX028) 
{
  MDR_Port_ClearPins(objKX028->CS_Port, objKX028->CS_PinSel);
  MDR_Delay(objKX028->ticksDelayCS);
}

void MDR_1923KX028_CS_SetInactive(const MDR_1923KX028_Obj *objKX028) 
{
  MDR_Delay(objKX028->ticksDelayCS);  
  MDR_Port_SetPins(objKX028->CS_Port, objKX028->CS_PinSel);
}

void MDR_1923KX028_ReadAXI_Begin(MDR_1923KX028_Obj *objKX028, uint32_t addr)
{
  MDR_SSP_Type *SSPx = objKX028->SSPx;    
  while (!MDR_SSP_IsEmptyFIFO_TX(SSPx));
  MDR_SSP_ClearFIFO_RX(SSPx);
  
  MDR_1923KX028_CS_SetActive(objKX028);
  
  //  Write Addr and dummy byte
  MDR_SSP_WriteData(SSPx,  MDR_1923KX028_CMD_AXI_RD);  
  MDR_SSP_WriteData(SSPx, (uint8_t)(addr >> 16));
  MDR_SSP_WriteData(SSPx, (uint8_t)(addr >> 8));
  MDR_SSP_WriteData(SSPx, (uint8_t)(addr >> 0));
  MDR_SSP_WriteData(SSPx,  0); //  Dummy write  
  
  while (MDR_SSP_IsBusy(SSPx));
  MDR_SSP_ClearFIFO_RX(SSPx);
}  

uint32_t MDR_1923KX028_ReadAXI_Next(MDR_1923KX028_Obj *objKX028)
{
  MDR_SSP_Type *SSPx = objKX028->SSPx;
  
  //  Write Zeros for Read Data
  MDR_SSP_WriteData(SSPx, 0);
  MDR_SSP_WriteData(SSPx, 0);
  MDR_SSP_WriteData(SSPx, 0);
  MDR_SSP_WriteData(SSPx, 0);
  while (MDR_SSP_IsBusy(SSPx));
  
  //  Read Data
  uint32_t result = 0;
  uint8_t *pRes = (uint8_t *)&result;
  pRes[3] = (uint8_t)MDR_SSP_ReadData(SSPx);
  pRes[2] = (uint8_t)MDR_SSP_ReadData(SSPx);
  pRes[1] = (uint8_t)MDR_SSP_ReadData(SSPx);
  pRes[0] = (uint8_t)MDR_SSP_ReadData(SSPx);

//  MDR_1923KX028_CS_SetInactive(objKX028);
  
  return result;
}

uint32_t MDR_1923KX028_ReadAXI(MDR_1923KX028_Obj *objKX028, uint32_t addr)
{
  MDR_1923KX028_ReadAXI_Begin(objKX028, addr);
  uint32_t result = MDR_1923KX028_ReadAXI_Next(objKX028);
  MDR_1923KX028_ReadAXI_End(objKX028);
  
  return result;
}

//uint32_t MDR_1923KX028_ReadAXI(MDR_1923KX028_Obj *objKX028, uint32_t addr)
//{
//  MDR_SSP_Type *SSPx = objKX028->SSPx;    
//  while (!MDR_SSP_IsEmptyFIFO_TX(SSPx));
//  MDR_SSP_ClearFIFO_RX(SSPx);
//  
//  MDR_1923KX028_CS_SetActive(objKX028);
//  
//  //  Write Addr and dummy byte
//  MDR_SSP_WriteData(SSPx,  MDR_1923KX028_CMD_AXI_WR);  
//  MDR_SSP_WriteData(SSPx, (uint8_t)(addr >> 16));
//  MDR_SSP_WriteData(SSPx, (uint8_t)(addr >> 8));
//  MDR_SSP_WriteData(SSPx, (uint8_t)(addr >> 0));
//  MDR_SSP_WriteData(SSPx,  0); //  Dummy write  
//  
//  while (MDR_SSP_IsBusy(SSPx));
//  MDR_SSP_ClearFIFO_RX(SSPx);
//    
//  //  Write Zeros for Read Data
//  MDR_SSP_WriteData(SSPx, 0);
//  MDR_SSP_WriteData(SSPx, 0);
//  MDR_SSP_WriteData(SSPx, 0);
//  MDR_SSP_WriteData(SSPx, 0);
//  while (MDR_SSP_IsBusy(SSPx));
//  
//  //  Read Data
//  uint32_t result = 0;
//  uint8_t *pRes = (uint8_t *)&result;
//  pRes[3] = (uint8_t)MDR_SSP_ReadData(SSPx);
//  pRes[2] = (uint8_t)MDR_SSP_ReadData(SSPx);
//  pRes[1] = (uint8_t)MDR_SSP_ReadData(SSPx);
//  pRes[0] = (uint8_t)MDR_SSP_ReadData(SSPx);

//  MDR_1923KX028_CS_SetInactive(objKX028);
//  
//  return result;
//}

uint32_t MDR_1923KX028_ReadReg(MDR_1923KX028_Obj *objKX028, uint32_t addr)
{
  MDR_SSP_Type *SSPx = objKX028->SSPx;    
  
  while (!MDR_SSP_IsEmptyFIFO_TX(SSPx));
  MDR_SSP_ClearFIFO_RX(SSPx);  
  MDR_1923KX028_CS_SetActive(objKX028);
  
  //  Write Addr
  MDR_SSP_WriteData(SSPx,  MDR_1923KX028_CMD_REG_RD);  
  MDR_SSP_WriteData(SSPx, (uint8_t)(addr >> 16));
  MDR_SSP_WriteData(SSPx, (uint8_t)(addr >> 8));
  MDR_SSP_WriteData(SSPx, (uint8_t)(addr >> 0));   
  //  Write Zeros for Read Data
  MDR_SSP_WriteData(SSPx, 0);
  MDR_SSP_WriteData(SSPx, 0);
  MDR_SSP_WriteData(SSPx, 0);
  MDR_SSP_WriteData(SSPx, 0);
  while (MDR_SSP_IsBusy(SSPx));
  
  //  Dummy Data
  MDR_SSP_ReadData(SSPx);
  MDR_SSP_ReadData(SSPx);
  MDR_SSP_ReadData(SSPx);
  MDR_SSP_ReadData(SSPx);
  //  Read Data
  uint32_t result = 0;
  uint8_t *pRes = (uint8_t *)&result;
  pRes[3] = (uint8_t)MDR_SSP_ReadData(SSPx);
  pRes[2] = (uint8_t)MDR_SSP_ReadData(SSPx);
  pRes[1] = (uint8_t)MDR_SSP_ReadData(SSPx);
  pRes[0] = (uint8_t)MDR_SSP_ReadData(SSPx);

  MDR_1923KX028_CS_SetInactive(objKX028);
  
  return result;
}  


void MDR_1923KX028_Write(MDR_1923KX028_Obj *objKX028, uint32_t addr24, uint32_t data, uint8_t cmd)  
{
  MDR_SSP_Type *SSPx = objKX028->SSPx;  
  while (!MDR_SSP_IsEmptyFIFO_TX(SSPx));
  
  MDR_1923KX028_CS_SetActive(objKX028);
  
  MDR_SSP_WriteData(SSPx, cmd);  
  MDR_SSP_WriteData(SSPx, (uint8_t)(addr24 >> 16));
  MDR_SSP_WriteData(SSPx, (uint8_t)(addr24 >> 8));
  MDR_SSP_WriteData(SSPx, (uint8_t)(addr24 >> 0));
  
  MDR_SSP_WriteData(SSPx, (uint8_t)(data >> 24));
  MDR_SSP_WriteData(SSPx, (uint8_t)(data >> 16));
  MDR_SSP_WriteData(SSPx, (uint8_t)(data >> 8));
  MDR_SSP_WriteData(SSPx, (uint8_t)(data >> 0));

  while (MDR_SSP_IsBusy(SSPx));  
  MDR_SSP_ClearFIFO_RX(SSPx);
  
  MDR_1923KX028_CS_SetInactive(objKX028);
}


uint16_t MDR_1923KX028_ReadID(MDR_1923KX028_Obj *objKX028)
{
MDR_SSP_Type *SSPx = objKX028->SSPx;    
  
  while (!MDR_SSP_IsEmptyFIFO_TX(SSPx));
  MDR_SSP_ClearFIFO_RX(SSPx);  
  MDR_1923KX028_CS_SetActive(objKX028);
  
  //  Write Addr
  MDR_SSP_WriteData(SSPx,  MDR_1923KX028_CMD_ID_RD);  
  //  Write Zeros for Read Data
  MDR_SSP_WriteData(SSPx, 0);
  MDR_SSP_WriteData(SSPx, 0);  
  while (MDR_SSP_IsBusy(SSPx));
  
  //  Dummy Data
  MDR_SSP_ReadData(SSPx);
  //  Read Data
  uint16_t result = 0;
  uint8_t *pRes = (uint8_t *)&result;
  pRes[1] = (uint8_t)MDR_SSP_ReadData(SSPx);
  pRes[0] = (uint8_t)MDR_SSP_ReadData(SSPx);

  MDR_1923KX028_CS_SetInactive(objKX028);
  
  return result;
}  


//=============================================================================
//==============    Функции для работы с ресурсами базиса   ===================
//===    Переопределить с CriticalSection при использовании с FreeRTOS  =======
//=============================================================================

static MDR_1923KX028_Obj _objKX028;

MDR_1923KX028_Obj* MDR_KX028_Init(const MDR_SSP_TypeEx *exSSPx, MDR_1923KX028_Cfg *cfg)
{
  _objKX028 = MDR_1923KX028_Init(exSSPx, cfg);
  return &_objKX028;
}


uint32_t MDR_KX028_ReadAXI_def(uint32_t addr)
{
  return MDR_1923KX028_ReadAXI(&_objKX028, addr);
}

void     MDR_KX028_WriteAXI_def(uint32_t addr, uint32_t data)
{
  MDR_1923KX028_WriteAXI(&_objKX028, addr, data);
}

void     MDR_KX028_ReadBeginAXI_def(uint32_t fromAddr)
{
  MDR_1923KX028_ReadAXI_Begin(&_objKX028, fromAddr);
}

uint32_t MDR_KX028_ReadNextAXI_def(void)
{
  return MDR_1923KX028_ReadAXI_Next(&_objKX028);
}

void     MDR_KX028_ReadEndAXI_def(void)
{
  MDR_1923KX028_ReadAXI_End(&_objKX028);
}

uint32_t MDR_KX028_MaskAXI_def(uint32_t addr, uint32_t clrMask, uint32_t setMask)
{
  uint32_t regValue = MDR_1923KX028_ReadAXI(&_objKX028, addr);
  regValue &= ~clrMask;
  regValue |= setMask;
  MDR_1923KX028_WriteAXI(&_objKX028, addr, regValue);
  return regValue;
}

void MDR_KX028_ReadByAddrList(uint16_t count, const uint32_t addrBase, const uint32_t *addrList, uint32_t *rdData)
{
  uint16_t i;
  for (i = 0; i < count; i++)
    rdData[i] = MDR_KX028_ReadSequence(addrBase + addrList[i]);
  MDR_KX028_ReadSequenceStop();
}

//  Оптимизированное чтение последовательных адресов
static uint32_t _seqLastAddr = 0;

uint32_t MDR_KX028_ReadSequence(const uint32_t addrBase)
{
  if (_seqLastAddr == 0)
  {
    MDR_KX028_ReadBeginAXI(addrBase);
  }
  else if (addrBase != _seqLastAddr + 4)
  {
    MDR_KX028_ReadEndAXI();
    MDR_KX028_ReadBeginAXI(addrBase);    
  }
  
  _seqLastAddr = addrBase;
  return MDR_KX028_ReadNextAXI();  
}

void MDR_KX028_ReadSequenceStop(void)
{
  if (_seqLastAddr)
  {
    MDR_KX028_ReadEndAXI();
    _seqLastAddr = 0;
  }
}


//  ----------------    Registers control ------------------
uint32_t  MDR_KX028_ReadReg (uint32_t addr)
{
  return MDR_1923KX028_ReadReg(&_objKX028, addr);
}

void MDR_KX028_WriteReg(uint32_t addr, uint32_t data)
{
  MDR_1923KX028_WriteReg(&_objKX028, addr, data);
}

void MDR_KX028_MaskReg(uint32_t addr, uint32_t maskClr, uint32_t maskSet)
{
  uint32_t regValue = MDR_KX028_ReadReg(addr);
  regValue &= ~maskClr;
  regValue |= maskSet;
  MDR_1923KX028_WriteReg(&_objKX028, addr, regValue);
}



// ================  SFP Amplitude Control ==============
#define PHY_COUNT   16
static const uint8_t _phy_amp_offs[PHY_COUNT] = 
// PHY:  0   1   2   3  4  5   6   7   8   9  10  11  12  13  14  15
        {4, 11, 18, 25, 0, 7, 14, 21,  0,  7, 14, 21,  0,  7, 14, 21};

static void MDR_KX028_ResetPhyByMask(uint32_t resetMask)
{
  uint32_t regCtrl12 = MDR_KX028_ReadReg(MDR_1923KX028_Control_12);  
  // SGMII PHYs reset
  MDR_KX028_WriteReg(MDR_1923KX028_Control_12, regCtrl12 | resetMask);  
  // SGMII PHYs in normal mode operations
  MDR_KX028_WriteReg(MDR_1923KX028_Control_12, regCtrl12);
}        
        
void MDR_KX028_SetPhyAmp(uint8_t port, uint8_t level)
{   
  uint8_t offset = _phy_amp_offs[port];
  uint32_t maskClr  = MDR_1923KX028_PhyAmpMask << offset;
  uint32_t value = level << offset;       
  if( port < 4 )
  {
    MDR_KX028_MaskReg(MDR_1923KX028_Control_10, maskClr, value);
    MDR_KX028_ResetPhyByMask(MDR_1923KX028_Ctrl12_SoftRstXauiPhy1_4_Msk);
  }
  else if( port < 8 )
  {
    MDR_KX028_MaskReg(MDR_1923KX028_Control_11, maskClr, value);
    MDR_KX028_ResetPhyByMask(MDR_1923KX028_Ctrl12_SoftRstXauiPhy5_8_Msk);
  }
  else if( port < 12 )
  {
    MDR_KX028_MaskReg(MDR_1923KX028_Control_12, maskClr, value);
    MDR_KX028_ResetPhyByMask(MDR_1923KX028_Ctrl12_SoftRstXauiPhy8_12_Msk);
  }
  else
  {
    MDR_KX028_MaskReg(MDR_1923KX028_Control_13, maskClr, value);
    MDR_KX028_ResetPhyByMask(MDR_1923KX028_Ctrl12_SoftRstXauiPhy13_16_Msk);
  }     
}

void MDR_KX028_RestorePhyAmpDef(uint8_t port)
{
  MDR_KX028_SetPhyAmp(port, MDR_1923KX028_PhyAmpDef);
}

#include "MDR_1636RR52.h"


//==================  Инициализация задержек, необходимых по протоколу ======================
//  Инициализация по умолчанию под максимальную частоту в 144МГц (1986ВЕ1)
static MDR_RR52_Delays _RR52_Delay = 
{
  .Erase_55ms   = MS_TO_DELAY_LOOPS(55, 144E+6),
  .Program_45us = US_TO_DELAY_LOOPS(44, 144E+6),
  .Reset_30us   = US_TO_DELAY_LOOPS(55, 144E+6),
  .CS_20ns      = NS_TO_DELAY_LOOPS(20, 144E+6),
  .RD_30ns      = NS_TO_DELAY_LOOPS(30, 144E+6),
  .WR_1us       = US_TO_DELAY_LOOPS(1,  144E+6),
};

void MDR_RR52_InitDelaysEx(const MDR_RR52_Delays *delays)
{
  _RR52_Delay = *delays;
}

void MDR_RR52_InitDelays(uint32_t CPU_FregHz)
{
  _RR52_Delay.Erase_55ms   = MS_TO_DELAY_LOOPS(55, CPU_FregHz);
  _RR52_Delay.Program_45us = US_TO_DELAY_LOOPS(44, CPU_FregHz);
  _RR52_Delay.Reset_30us   = US_TO_DELAY_LOOPS(55, CPU_FregHz);
  _RR52_Delay.CS_20ns      = NS_TO_DELAY_LOOPS(20, CPU_FregHz);
  _RR52_Delay.RD_30ns      = NS_TO_DELAY_LOOPS(30, CPU_FregHz);
  _RR52_Delay.WR_1us       = US_TO_DELAY_LOOPS(1,  CPU_FregHz);
}


//==================  Инициализация и управление SPI ======================
MDR_1636RR52_Obj MDR_RR52_Init(const MDR_SSP_TypeEx *exSSPx, const MDR_1636RR52_Cfg *cfgRR52)
{
  MDR_1636RR52_Obj result;
  
  //  SPI Init  
  MDR_SSP_Config cfgSSP = {
    .DataBits     = SSP_DataBits_8,
    .FrameFormat  = SSP_Frame_SPI,
    .SPI_Mode     = SPI_CPHA0_CPOL0,
    .DivSCR_0_255 = cfgRR52->DivSCR_0_255,
    .DivPSR_2_254 = cfgRR52->DivPSR_2_254,
  };  
  MDR_SSPex_Init(exSSPx, &cfgSSP, cfgRR52->ClockBRG);
  MDR_SSPex_EnableMaster(exSSPx, false);

  //  Для 1986VE4,VE214,VE234 частота UART_Clock формируется мультиплексорами
  //  В VE214 отдельный выбор частоты с делителем для каждого из блоков UART, SSP, Timer
  //  В остальных МК UART_Clock формируется только из HCLK (равной CPU_Clock) - выбор источника не требуется
#ifdef MDR_PER_CLOCK_SELF_TIM_UART_SSP  
  MDR_SetClock_SSP1(MDR_PER_PLLCPUo);
#elif defined (MDR_PER_CLK_LIKE_VE4)
  MDR_SetClock_UartTimSSP(MDR_PER_PLLCPUo);
#endif 
  
  //  Init SPI Pins  
  MDR_SSP_CfgPinsGPIO cfgPins;  
  cfgPins.pPinCLK = cfgRR52->pPinCLK; 
  cfgPins.pPinRX  = cfgRR52->pPinRX; 
  cfgPins.pPinTX  = cfgRR52->pPinTX;   
  cfgPins.pPinFSS = NULL;
  MDR_SSP_InitPinsGPIO(&cfgPins, cfgRR52->pinsPower);  
  
  //  CS Manual pin init and fill result
  result.SSPx = exSSPx->SSPx;
  MDR_RR52_InitPinCS(cfgRR52->pPinManualCS, cfgRR52->pinsPower, &result);
 
  //  Set CS to inactive State
  MDR_RR52_CS_SetInactive(&result);
  
  result.CompletedTimeoutCount = MDR_RR52_CHECK_COMPLETED_COUNT_DEF;
  
  return result;
}

void MDR_RR52_InitPinCS(const MDR_SSP_CfgPinGPIO  *pPinManualCS, MDR_PIN_PWR pinsPower, MDR_1636RR52_Obj *pObjRR52)
{
  MDR_PinDig_PermRegs pinPermRegs;
  MDR_Port_InitDigPermRegs(MDR_PIN_PullPush, pinsPower, MDR_Off, MDR_Off, &pinPermRegs);
  MDR_GPIO_InitDigPin(pPinManualCS->portGPIO, pPinManualCS->pinIndex, MDR_Pin_Out, MDR_PIN_PORT, &pinPermRegs);  
  
  pObjRR52->CS_Port    = pPinManualCS->portGPIO->PORTx; 
  pObjRR52->CS_PinSel  = (uint32_t)(1UL << pPinManualCS->pinIndex);
}


//  ==================    Функции работы с 1636РР52   ===========================
static void MDR_RR52_SendAddr(MDR_SSP_Type *SSPx, uint32_t addr)
{
  MDR_SSP_MasterTransfer(SSPx, (uint8_t)((addr >> 16) & 0xFF));
  MDR_SSP_MasterTransfer(SSPx, (uint8_t)((addr >> 8)  & 0xFF));
  MDR_SSP_MasterTransfer(SSPx, (uint8_t)((addr >> 0)  & 0xFF));  
}

static bool MDR_RR52_WaitCompletedWEL(const MDR_1636RR52_Obj *objRR52)
{
  uint8_t status;
  uint32_t i;
  
  for (i = 0; i < objRR52->CompletedTimeoutCount; ++i)
  {
    status = MDR_RR52_ReadStatusReg(objRR52);
    if ((status & (MDR_RR52_STATUS__WEL_Msk | MDR_RR52_STATUS__BUSY_Msk)) == 0)
      return ((status & MDR_RR52_STATUS__EPE_Msk) == 0);
  }
  
  return false;
}

void MDR_RR52_CS_SetActive(const MDR_1636RR52_Obj *objRR52) 
{
  MDR_Port_ClearPins(objRR52->CS_Port, objRR52->CS_PinSel);
  MDR_Delay(_RR52_Delay.CS_20ns);
}

void MDR_RR52_CS_SetInactive(const MDR_1636RR52_Obj *objRR52) 
{
  MDR_Port_SetPins(objRR52->CS_Port, objRR52->CS_PinSel);
  MDR_Delay(_RR52_Delay.CS_20ns);
}


static void MDR_RR52_WriteByte(const MDR_1636RR52_Obj *objRR52, uint32_t addr, uint8_t Data)
{
  MDR_RR52_CS_SetActive(objRR52);  
  MDR_SSP_MasterTransfer(objRR52->SSPx, MDR_RR52_CMD__BYTE_PROGRAM);
  MDR_RR52_SendAddr(objRR52->SSPx, addr);  
  MDR_SSP_MasterTransfer(objRR52->SSPx, Data);
  MDR_RR52_CS_SetInactive(objRR52);
}

void MDR_RR52_SendComAndAddr(const MDR_1636RR52_Obj *objRR52, uint8_t command, uint32_t addr)
{
  MDR_RR52_CS_SetActive(objRR52);  
  MDR_SSP_MasterTransfer(objRR52->SSPx, command);
  MDR_RR52_SendAddr(objRR52->SSPx, addr);
  MDR_RR52_CS_SetInactive(objRR52);
}
 
void MDR_RR52_SendCom(const MDR_1636RR52_Obj *objRR52, uint8_t command)
{
  MDR_RR52_CS_SetActive(objRR52);  
  MDR_SSP_MasterTransfer(objRR52->SSPx, command);
  MDR_RR52_CS_SetInactive(objRR52);  
}

void MDR_RR52_SendComAndData(const MDR_1636RR52_Obj *objRR52, uint8_t command, uint8_t data)
{
  MDR_RR52_CS_SetActive(objRR52);  
  MDR_SSP_MasterTransfer(objRR52->SSPx, command);
  MDR_SSP_MasterTransfer(objRR52->SSPx, data);
  MDR_RR52_CS_SetInactive(objRR52);  
}

//uint8_t MDR_RR52_SendComRD(const MDR_1636RR52_Obj *objRR52, uint8_t command)
//{
//  uint8_t rdData;
//  
//  MDR_RR52_CS_SetActive(objRR52);  
//  MDR_SSP_MasterTransfer(objRR52->SSPx, command);
//  
//#if MDR_RR52_USE_READ_DBL
//  //  На больших скоростях CLK первое ответное слово может быть неправильным, пропускаем
//  MDR_SSP_MasterTransfer(objRR52->SSPx, 0);  
//#endif  
//  
//  rdData = MDR_SSP_MasterTransfer(objRR52->SSPx, 0);  
//  MDR_RR52_CS_SetInactive(objRR52);  
//  
//  return rdData;
//}



//=============   1636RR52 API  ================
#define MDR_RR52_SetWEL                 MDR_RR52_WriteEnable
#define MDR_RR52_ClearWEL               MDR_RR52_WriteDisable


void MDR_RR52_ProtectSector(const MDR_1636RR52_Obj *objRR52, uint32_t addrSector) 
{
  MDR_RR52_SetWEL(objRR52);  
  MDR_RR52_SendComAndAddr(objRR52, MDR_RR52_CMD__PROTECT_SECTOR,   addrSector);  
  MDR_RR52_WaitCompletedWEL(objRR52);  
}

void MDR_RR52_UnprotectSector(const MDR_1636RR52_Obj *objRR52, uint32_t addrSector) 
{
  MDR_RR52_SetWEL(objRR52);  
  MDR_RR52_SendComAndAddr(objRR52, MDR_RR52_CMD__UNPROTECT_SECTOR, addrSector);
  MDR_RR52_WaitCompletedWEL(objRR52);
}

uint8_t MDR_RR52_ReadProtSectReg (const MDR_1636RR52_Obj *objRR52, uint32_t addrSector) 
{
  uint8_t rdData;
  
  MDR_RR52_CS_SetActive(objRR52);  
  MDR_SSP_MasterTransfer(objRR52->SSPx, MDR_RR52_CMD__READ_SECT_PROT_REG);
  MDR_RR52_SendAddr(objRR52->SSPx, addrSector);
  
#if MDR_RR52_USE_READ_DBL
  //  На больших скоростях CLK первое ответное слово может быть неправильным, пропускаем
  MDR_SSP_MasterTransfer(objRR52->SSPx, 0);  
#endif  
  
  rdData = MDR_SSP_MasterTransfer(objRR52->SSPx, 0);  
  MDR_RR52_CS_SetInactive(objRR52);  
  
  return rdData;
}

void MDR_RR52_WriteStatusReg(const MDR_1636RR52_Obj *objRR52, uint8_t status) 
{
  MDR_RR52_SetWEL(objRR52);  
  MDR_RR52_SendComAndData(objRR52, MDR_RR52_CMD__WRITE_STATUS_REG, status);
  MDR_RR52_WaitCompletedWEL(objRR52);
}

uint8_t MDR_RR52_ReadStatusReg (const MDR_1636RR52_Obj *objRR52) 
{
  uint8_t rdData;
  
  MDR_RR52_CS_SetActive(objRR52);  
  MDR_SSP_MasterTransfer(objRR52->SSPx, MDR_RR52_CMD__READ_STATUS_REG);
  
#if MDR_RR52_USE_READ_DBL
  //  На больших скоростях CLK первое ответное слово может быть неправильным, пропускаем
  MDR_SSP_MasterTransfer(objRR52->SSPx, 0);  
#endif  
  
  rdData = MDR_SSP_MasterTransfer(objRR52->SSPx, 0);  
  MDR_RR52_CS_SetInactive(objRR52);  
  
  return rdData;
}


void MDR_RR52_SectorErase(const MDR_1636RR52_Obj *objRR52, uint32_t addrSector)
{ 
  MDR_RR52_SetWEL(objRR52);
  
  //  Start SectorErase, 55ms
  MDR_RR52_SendComAndAddr(objRR52, MDR_RR52_CMD__SECTOR_ERASE, addrSector);  
  MDR_Delay(_RR52_Delay.Erase_55ms);
  
  MDR_RR52_WaitCompletedWEL(objRR52);
}
  
void MDR_RR52_ChipErase(const MDR_1636RR52_Obj *objRR52)
{
  MDR_RR52_SetWEL(objRR52);
  
  //  Start ChipErase, 110ms
  MDR_RR52_SendCom(objRR52, MDR_RR52_CMD__CHIP_ERASE);
  MDR_Delay(_RR52_Delay.Erase_55ms << 1);

  MDR_RR52_WaitCompletedWEL(objRR52);
} 

bool MDR_RR52_ByteProgram(const MDR_1636RR52_Obj *objRR52, uint32_t addr, uint8_t Data)
{
  MDR_RR52_SetWEL(objRR52);
  
  //  Start ByteProgram, 45us
  MDR_RR52_WriteByte(objRR52, addr, Data);  
  MDR_Delay(_RR52_Delay.Program_45us);
  
  return MDR_RR52_WaitCompletedWEL(objRR52);
}
    
uint32_t MDR_RR52_ProgramArray(const MDR_1636RR52_Obj *objRR52, uint32_t addr, uint32_t count, uint8_t *pData)
{
  uint32_t i;
  uint32_t wrCount;
  for (i = 0; i < count; ++i)
    if (MDR_RR52_ByteProgram(objRR52, addr + i, pData[i]))
    {
      MDR_Delay(_RR52_Delay.WR_1us);
      ++wrCount;
    }
  
  return wrCount;    
}

void MDR_RR52_Reset(const MDR_1636RR52_Obj *objRR52) 
{
  //  Reset active operation, 30us
  MDR_RR52_SendComAndData(objRR52, MDR_RR52_CMD__RESET, MDR_RR52_CMD__RESET_CONFIRM);
  MDR_Delay(_RR52_Delay.Reset_30us);
  
  MDR_RR52_WaitCompletedWEL(objRR52);
}


uint16_t MDR_RR52_ReadID(const MDR_1636RR52_Obj *objRR52)
{
  uint8_t rdLo, rdHi;
  
  MDR_RR52_CS_SetActive(objRR52);  
  MDR_SSP_MasterTransfer(objRR52->SSPx, MDR_RR52_CMD__READ_ID);
  rdHi = MDR_SSP_MasterTransfer(objRR52->SSPx, 0);
  rdLo = MDR_SSP_MasterTransfer(objRR52->SSPx, 0);
  MDR_RR52_CS_SetInactive(objRR52);  
  
  return (uint16_t)((rdHi << 8) | rdLo);
}


void MDR_RR52_ReadArray_15MHz(const MDR_1636RR52_Obj *objRR52, uint32_t addr, uint32_t count, uint8_t *pData)
{
  uint32_t i;
  MDR_RR52_CS_SetActive(objRR52);  
  MDR_SSP_MasterTransfer(objRR52->SSPx, MDR_RR52_CMD__READ_ARRAY_15MHz);
  MDR_RR52_SendAddr(objRR52->SSPx, addr);
  //  Read Data
  for (i = 0; i < count; ++i)
  {
    pData[i] = MDR_SSP_MasterTransfer(objRR52->SSPx, 0);
    MDR_Delay(_RR52_Delay.RD_30ns);
  }
  
  MDR_RR52_CS_SetInactive(objRR52);  
}
  
void MDR_RR52_ReadArray(const MDR_1636RR52_Obj *objRR52, uint32_t addr, uint32_t count, uint8_t *pData)
{
  uint32_t i;
  MDR_RR52_CS_SetActive(objRR52);  
  MDR_SSP_MasterTransfer(objRR52->SSPx, MDR_RR52_CMD__READ_ARRAY);
  MDR_RR52_SendAddr(objRR52->SSPx, addr);
  //  Read Data
  MDR_SSP_MasterTransfer(objRR52->SSPx, 0);    
  for (i = 0; i < count; ++i)
  {
    pData[i] = MDR_SSP_MasterTransfer(objRR52->SSPx, 0);
    MDR_Delay(_RR52_Delay.RD_30ns);
  }
  
  MDR_RR52_CS_SetInactive(objRR52);    
}



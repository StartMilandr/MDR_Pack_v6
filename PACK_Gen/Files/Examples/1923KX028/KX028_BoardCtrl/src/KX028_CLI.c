#include <MDR_Config.h>
#include <MDR_UART_CLI.h>
#include <MDR_1923KX028.h>
#include "KX028_CLI.h"

#include <MDR_1923KX028_M2_TableMAC.h>
#include <MDR_1923KX028_M2_TableVLAN.h>
#include <MDR_1923KX028_M2_Init.h>

#define CLI_UART_PORT           MDRB_UART2_RX_PD0_Port
#define CLI_UART_TX             MDRB_UART2_TX_PD1_Ind
#define CLI_UART_RX             MDRB_UART2_RX_PD0_Ind
#define CLI_UART_TX_FUNC        MDRB_UART2_TX_PD1_Func
#define CLI_UART_RX_FUNC        MDRB_UART2_RX_PD0_Func


uint8_t *cli_OutData;
uint16_t cli_OutDataLen;

void KX028_InitCLI(uint32_t baudRate, uint32_t freqCPU_Hz)
{
  MDR_UART_CfgPinGPIO _pinUartTX = {CLI_UART_PORT, CLI_UART_TX, CLI_UART_TX_FUNC};
  MDR_UART_CfgPinGPIO _pinUartRX = {CLI_UART_PORT, CLI_UART_RX, CLI_UART_RX_FUNC};  
	MDR_UART_CfgPinsGPIO pinsGPIO = {
		.pPinTX = &_pinUartTX,
    .pPinRX = &_pinUartRX,	
	};

  MDR_CLI_UART_Init(baudRate, freqCPU_Hz, &pinsGPIO);  
  
  cli_OutDataLen = MDR_CLI_GetResponceBuf(&cli_OutData);
}

static uint16_t CLI_MAC_UpdAdd(uint16_t lenCmdParams, uint8_t *pCmdParams, uint32_t waitCyclesMax);
static uint16_t CLI_MAC_Read  (uint16_t lenCmdParams, uint8_t *pCmdParams, uint32_t waitCyclesMax);
static uint16_t CLI_MAC_Del   (uint16_t lenCmdParams, uint8_t *pCmdParams, uint32_t waitCyclesMax);
static uint16_t CLI_MAC_Clear (uint16_t lenCmdParams, uint8_t *pCmdParams, uint32_t waitCyclesMax);

static uint16_t CLI_VLAN_UpdAdd(uint16_t lenCmdParams, uint8_t *pCmdParams, uint32_t waitCyclesMax);
static uint16_t CLI_VLAN_Read  (uint16_t lenCmdParams, uint8_t *pCmdParams, uint32_t waitCyclesMax);
static uint16_t CLI_VLAN_Del   (uint16_t lenCmdParams, uint8_t *pCmdParams, uint32_t waitCyclesMax);
static uint16_t CLI_VLAN_Clear (uint16_t lenCmdParams, uint8_t *pCmdParams, uint32_t waitCyclesMax);

static uint16_t CLI_ReadAXI (uint16_t lenCmdParams, uint8_t *pCmdParams, uint32_t waitCyclesMax);
static uint16_t CLI_WriteAXI(uint16_t lenCmdParams, uint8_t *pCmdParams, uint32_t waitCyclesMax);

static uint16_t CLI_ReadStatEMAC(uint16_t lenCmdParams, uint8_t *pCmdParams, uint32_t waitCyclesMax);
static uint16_t CLI_ReadStatClass(uint16_t lenCmdParams, uint8_t *pCmdParams, uint32_t waitCyclesMax);
static uint16_t CLI_ClearStatEMAC(uint16_t lenCmdParams, uint8_t *pCmdParams, uint32_t waitCyclesMax);
static uint16_t CLI_ClearStatClass(uint16_t lenCmdParams, uint8_t *pCmdParams, uint32_t waitCyclesMax);

static uint16_t CLI_WriteEMacCfg(uint16_t lenCmdParams, uint8_t *pCmdParams, uint32_t waitCyclesMax);



typedef uint16_t (*CLI_HandlerFunc)(uint16_t lenCmdParams, uint8_t *pCmdParams, uint32_t waitCyclesMax);

CLI_HandlerFunc HandlersCLI[cliCMD_LEN] = {
  NULL,               //cliCMD_NONE  = 0, - CLI_CMD_e from MDR_ConfigXX.h
  NULL,               //cliCMD_ERROR = 1,
  //  User Defs
  //  MAC
  CLI_MAC_Read,       //cliCMD_ReadMAC,
  CLI_MAC_UpdAdd,     //cliCMD_UpdAddMAC,
  CLI_MAC_Del,        //cliCMD_DelMAC,
  CLI_MAC_Clear,      //cliCMD_ClearMAC,
  //  VLAN
  CLI_VLAN_Read,      //cliCMD_ReadVLAN
  CLI_VLAN_UpdAdd,    //cliCMD_UpdAddVLAN,
  CLI_VLAN_Del,       //cliCMD_DelVLAN,
  CLI_VLAN_Clear,     //cliCMD_ClearVLAN,
  //  STAT
  CLI_ReadStatEMAC,   //cliCMD_ReadStatPort,
  CLI_ReadStatClass,  //cliCMD_ReadStatClass,
  CLI_ClearStatEMAC,  //cliCMD_ClearStatPort,  
  CLI_ClearStatClass, //cliCMD_ClearStatClass,
  //  Port
  CLI_WriteEMacCfg,   //cliCMD_WriteEmacCfg
  //  AXI
  CLI_ReadAXI,        //cliCMD_ReadAXI,
  CLI_WriteAXI,       //cliCMD_WriteAXI
};

typedef enum {
  cliAck_LenError,
  cliAck_Ok,
  cliAck_TBL_AddOk,
  cliAck_TBL_AddFault,
  cliAck_TBL_UpdOk,
  cliAck_TBL_RdFault,
  cliAck_TBL_Empty,
} KX028_CLI_ACK_e;


void KX028_ProcessCLI(uint32_t waitCyclesMax)
{ 
  uint16_t  cliParamLen;
  uint8_t *pCliParams;  
  CLI_CMD_e cliCMD;
  
  cliCMD = MDR_CLI_GetCommand(&cliParamLen, &pCliParams);
  if (cliCMD == cliCMD_NONE)
    return;
  
  //  Call HandlerFunction
  CLI_HandlerFunc handlerCLI = HandlersCLI[cliCMD];
  uint16_t  ackParamLen;  
  if (handlerCLI != NULL)
    ackParamLen = handlerCLI(cliParamLen, pCliParams, waitCyclesMax);
  else
  {
    cliCMD = cliCMD_ERROR;
    ackParamLen = cliParamLen;
  }
    
  //  Send Respoce
  MDR_CLI_SetResponse(cliCMD, ackParamLen);
}

//  ----------------    Handlers MAC  ----------------
static uint16_t CLI_MAC_UpdAdd(uint16_t lenCmdParams, uint8_t *pCmdParams, uint32_t waitCyclesMax)
{
  if (lenCmdParams == sizeof(MDR_KX028_KeyEntryMAC_t))
  {
    if (MDR_KX028_MAC_TableUpdateByKey((MDR_KX028_KeyEntryMAC_t *)pCmdParams, waitCyclesMax))
      cli_OutData[0] = cliAck_TBL_UpdOk;
    else
    {
      if (MDR_KX028_MAC_TableAddByKey((MDR_KX028_KeyEntryMAC_t *)pCmdParams, waitCyclesMax))
        cli_OutData[0] = cliAck_TBL_AddOk;
      else
        cli_OutData[0] = cliAck_TBL_AddFault;
    }  
  }
  else
    cli_OutData[0] = cliAck_LenError;
  
  return 1;
}

static uint16_t CLI_MAC_Del(uint16_t lenCmdParams, uint8_t *pCmdParams, uint32_t waitCyclesMax)
{
  if (lenCmdParams == sizeof(MDR_KX028_KeyMAC_t))
  {
    MDR_KX028_MAC_TableDelByKey((MDR_KX028_KeyMAC_t *)pCmdParams, waitCyclesMax);
    cli_OutData[0] = cliAck_Ok;
  }
  else
    cli_OutData[0] = cliAck_LenError;
  return 1;
}

//  Если возвращаемое количество не кратно 4, то это код ошибки
//  Иначе это данные
static uint16_t CLI_MAC_Read(uint16_t lenCmdParams, uint8_t *pCmdParams, uint32_t waitCyclesMax)
{
  uint16_t retCnt = 1;
  
  if (lenCmdParams == sizeof(uint16_t))
  {
    uint16_t hashAddr = *((uint16_t *)pCmdParams);
    
    if (MDR_KX028_MAC_TableRead((MDR_KX028_MAC_TableItem_t *)cli_OutData, hashAddr, waitCyclesMax))
      retCnt = sizeof(MDR_KX028_MAC_TableItem_t);
    else
      cli_OutData[0] = cliAck_TBL_RdFault;
  }
  else if (lenCmdParams == (sizeof(uint16_t) * 2))
  { // Return only activeItems
    uint16_t fromHash  = ((uint16_t *)pCmdParams)[0];
    uint16_t rdCount = ((uint16_t *)pCmdParams)[1];
    
    retCnt = 0;
    MDR_KX028_MAC_TableItem_t *pRetItem;
    while (fromHash < CFG_MAC_TABLE_ITEMS_COUNT)
    {
      pRetItem = &((MDR_KX028_MAC_TableItem_t *)cli_OutData)[retCnt];
      if (MDR_KX028_MAC_TableRead(pRetItem, fromHash, waitCyclesMax))
        if (pRetItem->regMAC4 & KX028_ItemMAC_REG4_IsActive_Msk)
        {
          retCnt++;
          if (retCnt == rdCount)
            break;
        }      
      fromHash++;
    }
    if (retCnt == 0)      
    {
      cli_OutData[0] = cliAck_TBL_Empty;
      retCnt = 1;
    }
    else
      retCnt *= sizeof(MDR_KX028_MAC_TableItem_t);    
  }
  else
    cli_OutData[0] = cliAck_LenError;
  
  return retCnt;
}


static uint16_t CLI_MAC_Clear(uint16_t lenCmdParams, uint8_t *pCmdParams, uint32_t waitCyclesMax)
{
  if (lenCmdParams == 1)
  {
    uint32_t options = (uint32_t)pCmdParams[0] << 8;
    MDR_KX028_MAC_TableFlush(options, waitCyclesMax);  
    cli_OutData[0] = cliAck_Ok;  
  }
  else
    cli_OutData[0] = cliAck_LenError;
  return 1;
}


//  ----------------    Handlers VLAN  ----------------
typedef __PACKED_STRUCT {
  uint16_t                vlanId;
  MDR_KX028_VLAN_Entry_t  brentry;
} CLI_VLAN_KeyEntry_t;

static uint16_t CLI_VLAN_UpdAdd(uint16_t lenCmdParams, uint8_t *pCmdParams, uint32_t waitCyclesMax)
{
  if (lenCmdParams == sizeof(CLI_VLAN_KeyEntry_t))
  {
    CLI_VLAN_KeyEntry_t *pKeyEntry = (CLI_VLAN_KeyEntry_t *)pCmdParams;
    if (MDR_KX028_VLAN_TableUpdate(pKeyEntry->vlanId, pKeyEntry->brentry, waitCyclesMax))
      cli_OutData[0] = cliAck_TBL_UpdOk;
    else
    {
      if (MDR_KX028_VLAN_TableAdd(pKeyEntry->vlanId, pKeyEntry->brentry, waitCyclesMax))
        cli_OutData[0] = cliAck_TBL_AddOk;
      else
        cli_OutData[0] = cliAck_TBL_AddFault;
    }  
  }
  else
    cli_OutData[0] = cliAck_LenError;
  
  return 1;
}

static uint16_t CLI_VLAN_Del(uint16_t lenCmdParams, uint8_t *pCmdParams, uint32_t waitCyclesMax)
{
  if (lenCmdParams == sizeof(uint16_t))
  {
    uint16_t vlanID = *(uint16_t *)pCmdParams;
    MDR_KX028_VLAN_TableDel(vlanID, waitCyclesMax);
    cli_OutData[0] = cliAck_Ok;
  }
  else
    cli_OutData[0] = cliAck_LenError;
  return 1;  
}

//  Если возвращаемое количество не кратно 4, то это код ошибки
//  Иначе это данные
static uint16_t CLI_VLAN_Read(uint16_t lenCmdParams, uint8_t *pCmdParams, uint32_t waitCyclesMax)
{
  uint16_t retCnt = 1;
  
  if (lenCmdParams == sizeof(uint16_t))
  {
    uint16_t hashAddr = *((uint16_t *)pCmdParams);
    
    if (MDR_KX028_VLAN_TableRead((MDR_KX028_VLAN_TableItem *)cli_OutData, hashAddr, waitCyclesMax))
      retCnt = sizeof(MDR_KX028_VLAN_TableItem);
    else
      cli_OutData[0] = cliAck_TBL_RdFault;
  }
  else if (lenCmdParams == (sizeof(uint16_t) * 2))
  { // Return only activeItems
    uint16_t fromHash  = ((uint16_t *)pCmdParams)[0];
    uint16_t rdCount = ((uint16_t *)pCmdParams)[1];
    
    retCnt = 0;
    MDR_KX028_VLAN_TableItem *pRetItem;
    while (fromHash < CFG_VLAN_TABLE_ENTRIES)
    {
      pRetItem = &((MDR_KX028_VLAN_TableItem *)cli_OutData)[retCnt];
      if (MDR_KX028_VLAN_TableRead(pRetItem, fromHash, waitCyclesMax))
        if (pRetItem->regMAC4 & KX028_ItemVLAN_REG4_IsActive_Msk)
        {
          retCnt++;
          if (retCnt == rdCount)
            break;
        }      
      fromHash++;
    }
    if (retCnt == 0)      
    {
      cli_OutData[0] = cliAck_TBL_Empty;
      retCnt = 1;
    }
    else
      retCnt *= sizeof(MDR_KX028_VLAN_TableItem);
  }
  else
    cli_OutData[0] = cliAck_LenError;
  
  return retCnt;
}


static uint16_t CLI_VLAN_Clear(uint16_t lenCmdParams, uint8_t *pCmdParams, uint32_t waitCyclesMax)
{
  if (lenCmdParams == 1)
  {
    uint32_t options = (uint32_t)pCmdParams[0] << 8;
    MDR_KX028_VLAN_TableFlush(options, waitCyclesMax);  
    cli_OutData[0] = cliAck_Ok;  
  }
  else
    cli_OutData[0] = cliAck_LenError;
  return 1;
}


//  ----------------    Handlers AXI BUS  ----------------
//  Если возвращаемое количество не кратно 4, то это код ошибки
//  Иначе это данные
static uint16_t CLI_ReadAXI(uint16_t lenCmdParams, uint8_t *pCmdParams, uint32_t waitCyclesMax)
{
  uint16_t rdCount = lenCmdParams >> 2;   // 32-bit Addresses count to read
  if (rdCount > 0)
  {
    uint16_t i;
    uint32_t *pAddr = (uint32_t *)pCmdParams;
    uint32_t *pOutData = (uint32_t *)cli_OutData;
    
    for (i = 0; i < rdCount; i++)
      pOutData[i] = MDR_KX028_ReadAXI(pAddr[i]);    
      
    return rdCount << 2;
  }
  else
  {
    cli_OutData[0] = cliAck_LenError;
    return 1;
  }
}

static uint16_t CLI_WriteAXI(uint16_t lenCmdParams, uint8_t *pCmdParams, uint32_t waitCyclesMax)
{
  uint16_t wdCount = lenCmdParams >> 2;   // 32-bit Addresses count to write    
  if (wdCount > 0)
  {
    uint32_t *pAddrData = (uint32_t *)pCmdParams;
    uint32_t  addr, data;

    while (wdCount--)  
    {
      addr = *pAddrData++;
      data = *pAddrData++;
      MDR_KX028_WriteAXI(addr, data);
    }
      
    return (lenCmdParams >> 2) << 2;
  }
  else
  {
    cli_OutData[0] = cliAck_LenError;
    return 1;
  }  
}


//  ----------------    Handlers Statistics  ----------------
static uint16_t CLI_ReadStatEMAC(uint16_t lenCmdParams, uint8_t *pCmdParams, uint32_t waitCyclesMax)
{
  if (lenCmdParams == 1)
  {  
    uint8_t portInd = pCmdParams[0];
    
    uint32_t cnt32 = sizeof(MDR_KX028_StatsEMAC_t) >> 2;
    uint32_t *pInData = (uint32_t *)&statsEMAC[portInd];
    uint32_t *pOutData = (uint32_t *)cli_OutData;
    
    uint32_t i;    
    for (i = 0; i < cnt32; i++)
      *pOutData++ = *pInData++;
      
    return sizeof(MDR_KX028_StatsEMAC_t);
  }
  else
  {
    cli_OutData[0] = cliAck_LenError;
    return 1;
  }  
}


static uint16_t CLI_ReadStatClass(uint16_t lenCmdParams, uint8_t *pCmdParams, uint32_t waitCyclesMax)
{
  if (lenCmdParams == 1)
  {  
    uint8_t portInd = pCmdParams[0];
    
    uint32_t i;
    uint32_t cnt32 = sizeof(MDR_KX028_StatsClassHW_t) >> 2;
    uint32_t *pInData = (uint32_t *)&statsClassHW[portInd];
    uint32_t *pOutData = (uint32_t *)cli_OutData;  
    
    for (i = 0; i < cnt32; i++)
      *pOutData++ = *pInData++;
      
    return sizeof(MDR_KX028_StatsClassHW_t);
  }
  else
  {
    cli_OutData[0] = cliAck_LenError;
    return 1;
  } 
}

static uint16_t CLI_ClearStatEMAC(uint16_t lenCmdParams, uint8_t *pCmdParams, uint32_t waitCyclesMax)
{
  if (lenCmdParams == 1)
  {
    uint8_t portInd = pCmdParams[0];
    uint32_t cnt32 = sizeof(MDR_KX028_StatsEMAC_t) >> 2;
    uint32_t *pData = (uint32_t *)&statsEMAC[portInd];
    
    uint32_t i;    
    for (i = 0; i < cnt32; i++)
      *pData++ = 0;
    
    cli_OutData[0] = cliAck_Ok;  
  }
  else
    cli_OutData[0] = cliAck_LenError;
  return 1;  
}

static uint16_t CLI_ClearStatClass(uint16_t lenCmdParams, uint8_t *pCmdParams, uint32_t waitCyclesMax)
{
  if (lenCmdParams == 1)
  {
    uint8_t portInd = pCmdParams[0];
    uint32_t cnt32 = sizeof(MDR_KX028_StatsClassHW_t) >> 2;
    uint32_t *pData = (uint32_t *)&statsClassHW[portInd];
    
    uint32_t i;    
    for (i = 0; i < cnt32; i++)
      *pData++ = 0;
    
    cli_OutData[0] = cliAck_Ok;  
  }
  else
    cli_OutData[0] = cliAck_LenError;
  return 1;   
}

static uint16_t CLI_WriteEMacCfg(uint16_t lenCmdParams, uint8_t *pCmdParams, uint32_t waitCyclesMax)
{
  if (lenCmdParams == 9)
  {
    uint32_t *pInp32 = (uint32_t *)pCmdParams;
    uint32_t struct1 = pInp32[0];
    uint32_t struct2 = pInp32[1];
    uint8_t portInd = pCmdParams[8];    
    
    MDR_KX028_WritePortStruct((MDR_KX028_EMAC_e)portInd, struct1, struct2);
    
    cli_OutData[0] = cliAck_Ok;  
  }
  else
    cli_OutData[0] = cliAck_LenError;
  return 1;
}

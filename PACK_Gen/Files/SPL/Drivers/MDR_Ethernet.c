#include <MDR_Ethernet.h>
#include <MDR_Funcs.h>
#include <MDR_DMA.h>
#include <MDR_RST_Clock.h>

#ifdef MDR_EXIST_HSE2
  void MDR_Eth_SetClockHSE2(void)
  {
    #if  HSE2_IS_RESONATOR
      MDR_HSE2_EnableAndWaitReady(MDR_CLK_Resonator, HSE2_TIMEOUT_CYCLES);
    #else
      MDR_HSE2_EnableAndWaitReady(MDR_CLK_Generator, HSE2_TIMEOUT_CYCLES);
    #endif
    
    MDR_CLOCK->ETH_CLOCK = MDR_MaskClrSet(MDR_CLOCK->ETH_CLOCK,
        MDR_RST_ETH__PHY_BRG_Msk    | MDR_RST_ETH__ETH_BRG_Msk 
      | MDR_RST_ETH__PHY_CLK_EN_Msk | MDR_RST_ETH__ETH_CLK_EN_Msk | MDR_RST_ETH__PHY_CLK_SEL_Msk
     ,  MDR_ETH_CLK_EN_MASK) 
      | VAL2FLD_Pos(MDR_PHY_HSE2, MDR_RST_ETH__PHY_CLK_SEL_Pos);      
  }
#endif

bool MDR_EthPHY_AutoNegDisable100Mbps(MDR_ETH_Type *MDR_Eth, uint8_t addrPHY)
{ 
  if (MDR_ETH_MDIO_MaskSetClear(MDR_Eth, addrPHY, MDR_ETH_PHY_R4, MDR_ETH_PHY_R4_SEL_100Mbps, 0))
    return MDR_ETH_MDIO_GetMaskClear(MDR_Eth, addrPHY, MDR_ETH_PHY_R4, MDR_ETH_PHY_R4_SEL_100Mbps);       
  
  return false;
}

#ifdef MDR_HAS_ETH_PHY
  static void MDR_EthIntPHY_EnaAndWaitReady(MDR_ETH_Type *MDR_Eth, const uint16_t phyCfgReg)
  {
    MDR_Eth->PHY_CTRL = phyCfgReg;
    while ((MDR_Eth->PHY_STATUS & MDR_ETH_PHY_STATUS_READY_Msk) == 0);    
    
    MDR_Eth->PHY_CTRL |= MDR_ETH_PHY_CTRL_nRST_Msk;
  }  
#endif

void MDR_EthExtPHY_EnaAndWaitReady(MDR_ETH_Type *MDR_Eth, const uint8_t addrPHY, uint16_t phyCfgReg)
{
  uint16_t regVal;
  
  if (MDR_ETH_ReadMDIO(MDR_Eth, addrPHY, MDR_ETH_PHY_R0, &regVal))
  {
    //  Reset PHY
    MDR_ETH_WriteMDIO(MDR_Eth, addrPHY, MDR_ETH_PHY_R0, regVal | MDR_ETH_PHY_R0_RESET_Msk);
    MDR_Delay(MS_TO_CLOCKS(50, 50E+6));
    //  Wait Ready
    while (!MDR_ETH_MDIO_GetMaskClear(MDR_Eth, addrPHY, MDR_ETH_PHY_R0, MDR_ETH_PHY_R0_RESET_Msk)) {}
      
    //  SetConfigs
    MDR_ETH_WriteMDIO(MDR_Eth, addrPHY, MDR_ETH_PHY_R0, (regVal & MDR_ETH_PHY_R0_Reserved_Msk) | phyCfgReg);      
  }
}

void MDR_Eth_Init(MDR_ETH_Type *MDR_Eth, const MDR_ETH_InitCfg *cfg)
{
#ifdef MDR_HAS_ETH_PHY  
  //  Встроенный PHY
  MDR_EthIntPHY_EnaAndWaitReady(MDR_Eth, cfg->phyCfgReg);
#endif
   
  MDR_Eth_InitMAC(MDR_Eth, cfg->cfgRegsMAC);

#ifndef MDR_HAS_ETH_PHY    
  //  Внешний PHY
  uint8_t phyAddr = cfg->phyCfgReg & MDR_ETH_PHY_R0_Reserved_Msk;  
  MDR_EthExtPHY_EnaAndWaitReady(MDR_Eth, phyAddr, cfg->phyCfgReg & (~MDR_ETH_PHY_R0_Reserved_Msk));
#endif
}
  
void MDR_Eth_InitMAC(MDR_ETH_Type *MDR_Eth, const MDR_ETH_MAC_CfgRegs  *cfgRegs)  
{  
  //  Apply cfg to Ethernet Registers  
  MDR_Eth->MAC_L = cfgRegs->MAC_L;
  MDR_Eth->MAC_M = cfgRegs->MAC_M;
  MDR_Eth->MAC_H = cfgRegs->MAC_H;
  
  MDR_Eth->HASH0 = cfgRegs->HASH0;
  MDR_Eth->HASH1 = cfgRegs->HASH1;
  MDR_Eth->HASH2 = cfgRegs->HASH2;
  MDR_Eth->HASH3 = cfgRegs->HASH3;

	MDR_Eth->IPG = cfgRegs->IPG;
	MDR_Eth->PSC = cfgRegs->PSC;
	MDR_Eth->BAG = cfgRegs->BAG;
	MDR_Eth->JitterWnd	= cfgRegs->JitterWnd;
	 
	MDR_Eth->IMR	= cfgRegs->IMR;
//	MDR_Eth->IFR	= MDR_ETH_EVENT_CLEAR_ALL;

	MDR_Eth->DELIMETER 	= cfgRegs->DELIMETER;
	MDR_Eth->R_HEAD			= MDR_Eth->R_TAIL;
	MDR_Eth->X_TAIL			= MDR_Eth->X_HEAD;

  MDR_Eth->MDIO_CTRL = cfgRegs->MDIO_CTRL;

  MDR_Eth->G_CFGH = cfgRegs->G_CFGH;
  MDR_Eth->G_CFGL = cfgRegs->G_CFGL;
  MDR_Eth->R_CFG  = cfgRegs->R_CFG;
  MDR_Eth->X_CFG  = cfgRegs->X_CFG;  

  //  Select BuffMode
#if MDR_ETH_BUFF_FIFO
  MDR_DMA_Init();
#endif

  MDR_ETH_ResetRXTX_On(MDR_Eth);
}

void MDR_Eth_Start(MDR_ETH_Type *MDR_Eth)
{
  //  Clear Buffs and Events
  MDR_ETH_ClearEventsAll(MDR_Eth);
  MDR_ETH_ClearBuffRX(MDR_Eth);
  MDR_ETH_ClearBuffTX(MDR_Eth);
  
  //  Phy Enable
//  Перенесмено в MDR_EthIntPHY_EnaAndWaitReady()
//  MDR_Eth->PHY_CTRL |= MDR_ETH_PHY_CTRL_nRST_Msk;
 
  //  Enable RX and TX
  MDR_ETH_ResetRXTX_Off(MDR_Eth);
  MDR_ETH_EnableTX(MDR_Eth);
  MDR_ETH_EnableRX(MDR_Eth);
}

void MDR_Eth_Stop(MDR_ETH_Type *MDR_Eth)
{
  MDR_ETH_DisableTX(MDR_Eth);
  MDR_ETH_DisableRX(MDR_Eth);
}


MDR_ETH_FrameStatusRX  MDR_ETH_ReadFrameByPTR(MDR_ETH_Type *MDR_Eth, uint8_t *frame, bool doSetRxHead)
{
  //  Get BuffPTR
  uint32_t buffStartAddr = ((uint32_t)MDR_Eth) + MDR_ETH_TO_BUFF_OFFSET;  
  uint32_t rdHead  = MDR_Eth->R_HEAD;
  uint32_t delim = MDR_Eth->DELIMETER;
  
  //  Read Receive Status Word and get Frame_Length
  uint32_t *pFrom32 = (uint32_t *)(buffStartAddr + rdHead);         
  MDR_ETH_FrameStatusRX result;
  result.Status = *pFrom32++;
  uint32_t readLen32 = (result.Fields.Length + 3) >> 2;  
  //  4 - already read status
  uint32_t lenToEnd32 = (delim - rdHead - 4) >> 2;
  if (lenToEnd32 <= 0)
    pFrom32 = (uint32_t *)buffStartAddr;
  
  uint32_t i;
  uint32_t *pTo32 = (uint32_t *)frame;
  if (readLen32 < lenToEnd32)
  {
    for (i = 0; i < readLen32; ++i)
      *pTo32++ = *pFrom32++;
  }
  else
  {
    for (i = 0; i < lenToEnd32; ++i)
      *pTo32++ = *pFrom32++;
    
    readLen32 -= lenToEnd32;    
    pFrom32 = (uint32_t *)(buffStartAddr);
    for (i = 0; i < readLen32; ++i)
      *pTo32++ = *pFrom32++;
  }
   
  if  (doSetRxHead)
  {
    rdHead = (uint32_t)pFrom32 - buffStartAddr;
    if (rdHead < delim)
      MDR_Eth->R_HEAD = rdHead;
    else
      MDR_Eth->R_HEAD = 0;
  }

  MDR_ETH_DecCountRx(MDR_Eth);
  return result;
}


void MDR_ETH_SendFrameByPTR(MDR_ETH_Type *MDR_Eth, MDR_ETH_FrameTX *frameTX, bool doSetTxTail)
{
  uint32_t wrTail  = MDR_Eth->X_TAIL;
  uint32_t frameLen32 = ((frameTX->frameLen + 3) >> 2);
  uint32_t writeCount32 = frameLen32 + 1;
  uint32_t buffFreeLen32 = (MDR_ETH_BUF_LEN - wrTail) >> 2;

  uint32_t i;
  uint32_t *pFrom32 = (uint32_t *)frameTX;  
  uint32_t *pTo32 = (uint32_t *)(((uint32_t)MDR_Eth) + MDR_ETH_TO_BUFF_OFFSET + wrTail);
  
  if (writeCount32 < buffFreeLen32)  
  {
    for (i = 0; i < writeCount32; ++i)
      *pTo32++ = *pFrom32++;
  }
  else
  { 
    for (i = 0; i < buffFreeLen32; ++i)
      *pTo32++ = *pFrom32++;
    
    pTo32 = (uint32_t *)(((uint32_t)MDR_Eth) + MDR_ETH_TO_BUFF_OFFSET + MDR_Eth->DELIMETER);
    writeCount32 -= buffFreeLen32;
    for (i = 0; i < writeCount32; ++i)
      *pTo32++ = *pFrom32++;
  }
  //  For statusTx
  *pTo32++ = 0;
  
  if (doSetTxTail)  
  {
    //  Lin - change X_TAIL to start
    if ((uint32_t)pTo32 < (((uint32_t)MDR_Eth) + MDR_ETH_TO_BUFF_OFFSET + MDR_ETH_BUF_LEN))
      MDR_Eth->X_TAIL = (uint32_t)pTo32;
    else
      MDR_Eth->X_TAIL = MDR_Eth->DELIMETER;
  }
}

MDR_ETH_FrameStatusRX  MDR_ETH_ReadFrame_FIFO(MDR_ETH_Type *MDR_Eth, uint8_t *frame)
{
  //  Get BuffPTR
  uint32_t *pInpFrame = (uint32_t *)((uint32_t)MDR_Eth + MDR_ETH_TO_BUFF_OFFSET + MDR_ETH_BUF_FIFO_RX_OFFS);  
  
  //  Read Receive Status Word and get Frame_Length
  MDR_ETH_FrameStatusRX result;
  result.Status = *pInpFrame;  
  uint32_t frameLen32 = (result.Fields.Length + 3) >> 2;

  //  DMA_Copy
  MDR_DMA_Copy32_FromNoInc(MDR_ETH_DMA_CHANNEL_RX, pInpFrame, (uint32_t *) frame, frameLen32);  
  
  MDR_ETH_DecCountRx(MDR_Eth);    
  return result;
}

void  MDR_ETH_WriteFrame_FIFO(MDR_ETH_Type *MDR_Eth, MDR_ETH_FrameTX *frameTX)
{
  //  Get BuffPTR
  uint32_t *pOutBuff = (uint32_t *)((uint32_t)MDR_Eth + MDR_ETH_TO_BUFF_OFFSET + MDR_ETH_BUF_FIFO_TX_OFFS); 
  //  Length with extra SendStatus word
  uint32_t sendCount32 = ((frameTX->frameLen + 3) >> 2) + 2;    
  //  DMA_Copy Frame data
  MDR_DMA_Copy32_ToNoInc(MDR_ETH_DMA_CHANNEL_TX, (uint32_t *) frameTX, pOutBuff, sendCount32);
}

uint32_t MDR_ETH_GetBuffFreeSizefRX(MDR_ETH_Type *MDR_Eth)
{
  uint16_t head = MDR_Eth->R_HEAD;
  uint16_t tail = MDR_Eth->R_TAIL;
  
  if (head < tail)
    return tail - head;
  else
    return MDR_Eth->DELIMETER - head + tail;
}
 
uint32_t MDR_ETH_GetBuffFreeSizeTX(MDR_ETH_Type *MDR_Eth)
{
  uint16_t head = MDR_Eth->X_HEAD;
  uint16_t tail = MDR_Eth->X_TAIL;
  if (tail < head)
    return head - tail;
  else
    return (MDR_ETH_BUF_LEN - MDR_Eth->DELIMETER) - (tail - head);
}


bool MDR_ETH_TryReadFrame(MDR_ETH_Type *MDR_Eth, uint8_t *frame, MDR_ETH_FrameStatusRX *status)
{
  bool result = MDR_ETH_HasFrameToRead(MDR_Eth);
  if (result)
    *status = MDR_ETH_ReadFrame(MDR_Eth, frame);
  return result;
}

bool MDR_ETH_TrySendFrame(MDR_ETH_Type *MDR_Eth, MDR_ETH_FrameTX *frameTX)
{
  bool result = MDR_ETH_GetBuffFreeSizeTX(MDR_Eth) > (frameTX->frameLen + MDR_ETH_BUFF_TX_LEN_SIZE + MDR_ETH_BUFF_TX_STATUS_SIZE);
  if (result)
    MDR_ETH_SendFrame(MDR_Eth, frameTX); 
  return result;
}


bool MDR_ETH_ReadMDIO(MDR_ETH_Type *MDR_Eth, uint16_t addrPHY, uint16_t addrRegInPHY, uint16_t *value)
{
	volatile uint32_t timeout = MDR_ETH_MDIO_TIMEOUT;

  //  Run transfer
	MDR_Eth->MDIO_CTRL = MDR_MaskClrSet(MDR_Eth->MDIO_CTRL,
            //  Clear
            MDR_ETH_MDIO_CTRL_REG_Addr_Msk |  MDR_ETH_MDIO_CTRL_PHY_Addr_Msk | MDR_ETH_MDIO_CTRL_OP_Msk | MDR_ETH_MDIO_CTRL_CTRL_RDY_Msk,
            //  OR
            VAL2FLD_Pos(addrPHY,                 MDR_ETH_MDIO_CTRL_PHY_Addr_Pos) 
          | VAL2FLD_Pos(addrRegInPHY,            MDR_ETH_MDIO_CTRL_REG_Addr_Pos) 
          | VAL2FLD_Pos(MDR_ETH_MDIO_CTRL_OP_RD, MDR_ETH_MDIO_CTRL_OP_Pos)
          | MDR_ETH_MDIO_CTRL_CTRL_RDY_Msk 
          );
  
  //  Wait Completed
	while (timeout)
  {
		timeout--;
    if (MDR_Eth->MDIO_CTRL & MDR_ETH_MDIO_CTRL_CTRL_RDY_Msk)
    {
      *value = (uint16_t)MDR_Eth->MDIO_DATA;
      return true;
    }
  }
  return false;
}

bool MDR_ETH_WriteMDIO(MDR_ETH_Type *MDR_Eth, uint16_t addrPHY, uint16_t addrRegInPHY, uint16_t value)
{
	volatile uint32_t timeout = MDR_ETH_MDIO_TIMEOUT;

  //  Run transfer
  MDR_Eth->MDIO_DATA = value;
	MDR_Eth->MDIO_CTRL = MDR_MaskClrSet(MDR_Eth->MDIO_CTRL,
            //  Clear
            MDR_ETH_MDIO_CTRL_REG_Addr_Msk |  MDR_ETH_MDIO_CTRL_PHY_Addr_Msk | MDR_ETH_MDIO_CTRL_OP_Msk | MDR_ETH_MDIO_CTRL_CTRL_RDY_Msk,
            //  OR
            VAL2FLD_Pos(addrPHY,                 MDR_ETH_MDIO_CTRL_PHY_Addr_Pos) 
          | VAL2FLD_Pos(addrRegInPHY,            MDR_ETH_MDIO_CTRL_REG_Addr_Pos) 
          | MDR_ETH_MDIO_CTRL_CTRL_RDY_Msk 
          );  

  //  Wait Completed
	while (timeout)
  {
		timeout--;
    if (MDR_Eth->MDIO_CTRL & MDR_ETH_MDIO_CTRL_CTRL_RDY_Msk)
    {
      return true;
    }
  }
  return false;
}

bool MDR_ETH_MDIO_GetMaskSet(MDR_ETH_Type *MDR_Eth, uint16_t addrPHY, uint16_t addrRegPHY, uint16_t setMask)
{
  uint16_t regValue;
  
  if (MDR_ETH_ReadMDIO(MDR_Eth, addrPHY, addrRegPHY, &regValue))
    return (regValue & setMask) == setMask;
  
  return false;
}

bool MDR_ETH_MDIO_GetMaskClear(MDR_ETH_Type *MDR_Eth, uint16_t addrPHY, uint16_t addrRegPHY, uint16_t setMask)
{
  uint16_t regValue;
  
  if (MDR_ETH_ReadMDIO(MDR_Eth, addrPHY, addrRegPHY, &regValue))
    return (regValue & setMask) == 0;
  
  return false;
}


void MDR_ETH_MDIO_WaitMaskSet(MDR_ETH_Type *MDR_Eth, uint16_t addrPHY, uint16_t addrRegPHY, uint16_t setMask)
{ 
  while (!MDR_ETH_MDIO_GetMaskSet(MDR_Eth, addrPHY, addrRegPHY, setMask)) { }
}

bool MDR_ETH_MDIO_MaskSetClear(MDR_ETH_Type *MDR_Eth, uint16_t addrPHY, uint16_t addrRegPHY, uint16_t clrMask, uint16_t setMask)
{
  uint16_t value;
    
  if (MDR_ETH_ReadMDIO(MDR_Eth, addrPHY, addrRegPHY, &value))
  {
    value &= ~clrMask;
    value |= setMask;
    return MDR_ETH_WriteMDIO(MDR_Eth, addrPHY, addrRegPHY, value);
  }
  else
    return false;
}


//===================     MDIO Managable Device Registers Access (MMD)  ==========
#define MDIO_MMD_CTRL_FUNC_ADDR      0
#define MDIO_MMD_CTRL_FUNC_DATA      0x4000
#define MDIO_MMD_CTRL_DEVAD_Msk      0x001F


void MDR_ETH_MDIO_BindRegMMD(MDR_ETH_Type *MDR_Eth, const MDR_ETH_MDIO_CfgMMD *cfgMMD, uint16_t addrMMD)
{
  addrMMD = addrMMD & MDIO_MMD_CTRL_DEVAD_Msk;
  //  Write Addr
  MDR_ETH_WriteMDIO(MDR_Eth, cfgMMD->addrPHY, cfgMMD->regMMD_Ctrl, MDIO_MMD_CTRL_FUNC_ADDR | cfgMMD->devad);
  MDR_ETH_WriteMDIO(MDR_Eth, cfgMMD->addrPHY, cfgMMD->regMMD_Data, addrMMD);

  //  Bind MMD_Register to MII_Register
  MDR_ETH_WriteMDIO(MDR_Eth, cfgMMD->addrPHY, cfgMMD->regMMD_Ctrl, MDIO_MMD_CTRL_FUNC_DATA | cfgMMD->devad);     
}

bool MDR_ETH_MDIO_WriteRegMMD(MDR_ETH_Type *MDR_Eth, const MDR_ETH_MDIO_CfgMMD *cfgMMD, uint16_t addrMMD, uint16_t value)
{
  MDR_ETH_MDIO_BindRegMMD(MDR_Eth, cfgMMD, addrMMD);
  return MDR_ETH_MDIO_ReWriteRegMMD(MDR_Eth, cfgMMD, value);
}

bool MDR_ETH_MDIO_ReadRegMMD(MDR_ETH_Type *MDR_Eth, const MDR_ETH_MDIO_CfgMMD *cfgMMD, uint16_t addrMMD, uint16_t *value)
{
  MDR_ETH_MDIO_BindRegMMD(MDR_Eth, cfgMMD, addrMMD);
  return MDR_ETH_MDIO_ReReadRegMMD(MDR_Eth, cfgMMD, value);  
}

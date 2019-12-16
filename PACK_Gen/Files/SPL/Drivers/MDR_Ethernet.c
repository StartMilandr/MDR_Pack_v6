#include <MDR_Ethernet.h>
#include <MDR_Funcs.h>
#include <MDR_DMA.h>
#include <MDR_RST_Clock.h>

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
   ,  MDR_RST_ETH__PHY_CLK_EN_Msk | MDR_RST_ETH__ETH_CLK_EN_Msk) 
    | VAL2FLD_Pos(MDR_PHY_HSE2, MDR_RST_ETH__PHY_CLK_SEL_Pos);  
}

void MDR_EthPHY_EnaAndWaitReady(MDR_ETH_Type *MDR_Eth, const uint16_t phyCfgReg)
{
  MDR_Eth->PHY_CTRL = phyCfgReg;
	while ((MDR_Eth->PHY_STATUS & MDR_ETH_PHY_STATUS_READY_Msk) == 0);    
}


void MDR_Eth_Init(MDR_ETH_Type *MDR_Eth, const MDR_ETH_InitCfg *cfg)
{
  //  Wait PHY Ready
  MDR_EthPHY_EnaAndWaitReady(MDR_Eth, cfg->phyCfgReg);
  
  //  Apply cfg to Ethernet Registers
  const MDR_ETH_MAC_CfgRegs  *cfgRegs = cfg->cfgRegsMAC;
  
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
//	MDR_Eth->R_HEAD			= MDR_Eth->R_TAIL;
//	MDR_Eth->X_TAIL			= MDR_Eth->X_HEAD;

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
  MDR_Eth->PHY_CTRL |= MDR_ETH_PHY_CTRL_nRST_Msk;
 
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


//MDR_ETH_FrameStatusRX  MDR_ETH_ReadFrameByPTR(MDR_ETH_Type *MDR_Eth, uint8_t *frame, bool doSetRxHead)
//{
//  //  Get BuffPTR
//  uint32_t buffStartAddr = ((uint32_t)MDR_Eth) + MDR_ETH_TO_BUFF_OFFSET;  
//  uint32_t rdHead  = MDR_Eth->R_HEAD;
//  uint32_t *pBuff32 = (uint32_t *)(buffStartAddr + rdHead);
//  //  Buff Length
//  uint32_t delim = MDR_Eth->DELIMETER;    
//  uint32_t buffSise32 = delim >> 2;
//  
//  //  Read Receive Status Word and get Frame_Length
//  MDR_ETH_FrameStatusRX result;
//  result.Status = *pBuff32++;
//  uint32_t frameLen32 = (result.Fields.Length + 3) >> 2;

//  //  Read Cycle vars
//  uint32_t i;
//  uint32_t *pFrame32 = (uint32_t *)frame;
//  
//  if ((rdHead + (frameLen32 << 2)) < delim)
//  {
//    for (i = 0; i < frameLen32; ++i)
//      *pFrame32++ = *pBuff32++;
//  }
//  else
//  {
//    uint32_t cnt;
//    cnt = buffSise32 - (rdHead >> 2) - 1;
//    for (i = 0; i < cnt; ++i)
//      *pFrame32++ = *pBuff32++;
//    
//    pBuff32 = (uint32_t *)(buffStartAddr);
//    cnt = frameLen32 - cnt;
//    for (i = 0; i < cnt; ++i)
//      *pFrame32++ = *pBuff32++;
//  }
//  
//  if  (doSetRxHead)
//  {
//    rdHead = (uint32_t)pBuff32 - buffStartAddr;
//    if (rdHead < delim)
//      MDR_Eth->R_HEAD = rdHead;
//    else
//      MDR_Eth->R_HEAD = 0;
//  }

//  MDR_ETH_DecCountRx(MDR_Eth);
//  return result;
//}

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


#ifndef MDR_ETHERNET_H
#define MDR_ETHERNET_H

#include <MDR_Config.h>
#include <MDR_Types.h>
#include <MDR_Funcs.h>
#include <MDR_RST_Clock.h>
#include <MDR_Ethernet_FrameDefs.h>
#include <MDR_DMA.h>

//  ----------    Clock Init Functions    ----------
#ifdef MDR_EXIST_HSE2
  void MDR_Eth_SetClockHSE2(void);
  
#elif defined(MDR_CLK_LIKE_VE8)
	//	VE8, VK014, ESila
  __STATIC_INLINE void  MDR_Eth_SetClock(MDR_Div128P divForEthClock, MDR_RST_ASYNC_IN_SEL clockSource)
  {
    MDR_CLOCK->ETH_CLK = MDR_MaskClrSet(MDR_CLOCK->ETH_CLK, MDR_RST_ASYNC_CLK_CLEAR_ALL, 
      (uint32_t)divForEthClock | MDR_PER_CLK_CLK_EN_Msk | VAL2FLD_Pos(clockSource, MDR_RST_ASYNC_CLK_SELECT_Pos));
  } 
#endif

__STATIC_INLINE void MDR_Eth_ClockOff(void) { MDR_CLOCK->MDR_ETH_CLK_EN_REG &= ~MDR_ETH_CLK_EN_MASK; }


//  ----------    Ethernet Init Functions    ----------
typedef struct {
  const MDR_ETH_MAC_CfgRegs  *cfgRegsMAC;  
  const uint16_t              phyCfgReg;  
} MDR_ETH_InitCfg;

//  Инициализация блоков MAC и внутреннего PHY (там где он есть)
void MDR_Eth_Init(MDR_ETH_Type *MDR_Eth, const MDR_ETH_InitCfg *cfg);
void MDR_Eth_Start(MDR_ETH_Type *MDR_Eth);
void MDR_Eth_Stop (MDR_ETH_Type *MDR_Eth);

//  Инициализация раздельно MAC and PHY:
//    Инициализация внешнего PHY
void MDR_EthExtPHY_EnaAndWaitReady(MDR_ETH_Type *MDR_Eth, const uint8_t addrPHY, uint16_t phyCfgReg);
//    Инициализация блока MAC
void MDR_Eth_InitMAC(MDR_ETH_Type *MDR_Eth, const MDR_ETH_MAC_CfgRegs  *cfgRegs);

#ifdef MDR_HAS_ETH_PHY
  //    Инициализация встроенного PHY
  void MDR_EthIntPHY_EnaAndWaitReady(MDR_ETH_Type *MDR_Eth, const uint16_t phyCfgReg);
#endif


//  ----------    Read Frame Functions    ----------
uint32_t MDR_ETH_GetBuffFreeSizefRX(MDR_ETH_Type *MDR_Eth);

//  Проверка что есть фрейм для чтения
__STATIC_INLINE bool  MDR_ETH_HasFrameToRead(MDR_ETH_Type *MDR_Eth) { return MDR_Eth->R_HEAD != MDR_Eth->R_TAIL; }

//  общая функция вычитывания фрейма из буфера Ethernet по указателям - линейный режим и AutoPTR
MDR_ETH_FrameStatusRX  MDR_ETH_ReadFrameByPTR(MDR_ETH_Type *MDR_Eth, uint8_t *frame, bool doSetRxHead);

//  Линейный режим чтения
__STATIC_INLINE MDR_ETH_FrameStatusRX  MDR_ETH_ReadFrame_Lin(MDR_ETH_Type *MDR_Eth, uint8_t *frame)
  { return MDR_ETH_ReadFrameByPTR(MDR_Eth, frame, true); }

//  Режим чтения с автоматическими указателями AutoPTR
__STATIC_INLINE MDR_ETH_FrameStatusRX  MDR_ETH_ReadFrame_Auto(MDR_ETH_Type *MDR_Eth, uint8_t *frame)
  { return MDR_ETH_ReadFrameByPTR(MDR_Eth, frame, false); }
  
//  Режим чтения через FIFO, используется DMA
MDR_ETH_FrameStatusRX  MDR_ETH_ReadFrame_FIFO(MDR_ETH_Type *MDR_Eth, uint8_t *frame);  

	
	
//	--- Вариант вычитывания фрейма в структуру MDR_ETH_FrameRX (для совместимости с MDR_ETH_FrameTX) ---
typedef __PACKED_STRUCT {
  MDR_ETH_FrameStatusRX statusRX;
  uint8_t  							frame[MDR_ETH_BUFF_LEN_RX];
	uint32_t 							reserved;  //  Reserved for TX status
} MDR_ETH_FrameRX;
  

//  Линейный режим чтения
__STATIC_INLINE void MDR_ETH_ReadFrame_LinF(MDR_ETH_Type *MDR_Eth, MDR_ETH_FrameRX *frameRX)
  { frameRX->statusRX = MDR_ETH_ReadFrameByPTR(MDR_Eth, frameRX->frame, true); }

//  Режим чтения с автоматическими указателями AutoPTR
__STATIC_INLINE void MDR_ETH_ReadFrame_AutoF(MDR_ETH_Type *MDR_Eth, MDR_ETH_FrameRX *frameRX)
  { frameRX->statusRX = MDR_ETH_ReadFrameByPTR(MDR_Eth, frameRX->frame, false); }
  
//  Режим чтения через FIFO, используется DMA
__STATIC_INLINE void MDR_ETH_ReadFrame_FIFOF(MDR_ETH_Type *MDR_Eth, MDR_ETH_FrameRX *frameRX)
	{ frameRX->statusRX = MDR_ETH_ReadFrame_FIFO(MDR_Eth, frameRX->frame); }

  
//  ----------    Send Frame Functions    ----------
uint32_t MDR_ETH_GetBuffFreeSizeTX(MDR_ETH_Type *MDR_Eth);

typedef __PACKED_STRUCT {
  uint32_t frameLen;
  uint8_t  frame[MDR_ETH_BUFF_LEN_TX];
  uint32_t sendStatus;  //  Reserved for TX status
} MDR_ETH_FrameTX;  
  
void MDR_ETH_SendFrameByPTR(MDR_ETH_Type *MDR_Eth, MDR_ETH_FrameTX *frameTX, bool doSetTxTail);

__STATIC_INLINE void  MDR_ETH_WriteFrame_Lin(MDR_ETH_Type *MDR_Eth, MDR_ETH_FrameTX *frameTX)
  { MDR_ETH_SendFrameByPTR(MDR_Eth, frameTX, true); }

__STATIC_INLINE void  MDR_ETH_WriteFrame_Auto(MDR_ETH_Type *MDR_Eth, MDR_ETH_FrameTX *frameTX)
  { MDR_ETH_SendFrameByPTR(MDR_Eth, frameTX, false); }

void  MDR_ETH_WriteFrame_FIFO(MDR_ETH_Type *MDR_Eth, MDR_ETH_FrameTX *frameTX);

  
MDR_ETH_FrameStatusRX  MDR_ETH_ReadFrame_FIFO_Start (MDR_ETH_Type *MDR_Eth, uint8_t *frame, uint32_t dmaChan);
                 void  MDR_ETH_WriteFrame_FIFO_Start(MDR_ETH_Type *MDR_Eth, MDR_ETH_FrameTX *frameTX, uint32_t dmaChan);
__STATIC_INLINE  bool  MDR_ETH_Frame_FIFO_Completed(uint32_t dmaChan) { return MDR_DMA_CopyGetCompleted(dmaChan); }


//  асинхронное чтение и запись фреймов через DMA в режиме FIFO, возвращают TRUE по окончании операции.
//  inProgress - внешняя переменная "потока", для хранения состояния запущен "поток" или нет
bool MDR_ETH_TryReadFrame_AsyncFIFO(MDR_ETH_Type *MDR_Eth, uint8_t *frame, MDR_ETH_FrameStatusRX *status, uint32_t dmaChan, bool *inProgress);
                bool MDR_ETH_ReadAsyncFIFO_TryStart(MDR_ETH_Type *MDR_Eth, uint8_t *frame, MDR_ETH_FrameStatusRX *status, uint32_t dmaChan);
__STATIC_INLINE bool MDR_ETH_ReadAsyncFIFO_WaitCompleted(uint32_t dmaChan) { return MDR_ETH_Frame_FIFO_Completed(dmaChan);  }    

bool MDR_ETH_TrySendFrame_AsyncFIFO(MDR_ETH_Type *MDR_Eth, MDR_ETH_FrameTX *frameTX, uint32_t dmaChan, bool *inProgress);
                 bool MDR_ETH_SendAsyncFIFO_TryStart(MDR_ETH_Type *MDR_Eth, MDR_ETH_FrameTX *frameTX, uint32_t dmaChan);
__STATIC_INLINE  bool MDR_ETH_SendAsyncFIFO_WaitCompleted(uint32_t dmaChan) { return MDR_ETH_Frame_FIFO_Completed(dmaChan); }  

  


//  ----------    Send / Receive Select    ----------
#if MDR_ETH_BUFF_LIN
  #define MDR_ETH_SendFrame   MDR_ETH_WriteFrame_Lin
  #define MDR_ETH_ReadFrame   MDR_ETH_ReadFrame_Lin
	#define MDR_ETH_ReadFrameF  MDR_ETH_ReadFrame_LinF
#elif MDR_ETH_BUFF_AUTO_PTR
  #define MDR_ETH_SendFrame   MDR_ETH_WriteFrame_Auto
  #define MDR_ETH_ReadFrame   MDR_ETH_ReadFrame_Auto
	#define MDR_ETH_ReadFrameF  MDR_ETH_ReadFrame_AutoF
#elif MDR_ETH_BUFF_FIFO
  #define MDR_ETH_SendFrame   MDR_ETH_WriteFrame_FIFO
  #define MDR_ETH_ReadFrame   MDR_ETH_ReadFrame_FIFO
	#define MDR_ETH_ReadFrameF  MDR_ETH_ReadFrame_FIFOF
#else  
  Select Ethernet Buffer mode in MDR_Config.h!
#endif  

bool MDR_ETH_TryReadFrame(MDR_ETH_Type *MDR_Eth, uint8_t *frame, MDR_ETH_FrameStatusRX *status);
bool MDR_ETH_TrySendFrame(MDR_ETH_Type *MDR_Eth, MDR_ETH_FrameTX *frameTX);

bool MDR_ETH_TryReadFrameF(MDR_ETH_Type *MDR_Eth, MDR_ETH_FrameRX *frameRX);
  

//  ----------    Misc Control Functions    ----------
__STATIC_INLINE void MDR_ETH_EnableTX (MDR_ETH_Type *MDR_Eth) { MDR_Eth->X_CFG |= MDR_ETH_XCFG_EN_Msk; }
__STATIC_INLINE void MDR_ETH_EnableRX (MDR_ETH_Type *MDR_Eth) { MDR_Eth->R_CFG |= MDR_ETH_RCFG_EN_Msk; }
__STATIC_INLINE void MDR_ETH_DisableTX(MDR_ETH_Type *MDR_Eth) { MDR_Eth->X_CFG &= ~MDR_ETH_XCFG_EN_Msk; }
__STATIC_INLINE void MDR_ETH_DisableRX(MDR_ETH_Type *MDR_Eth) { MDR_Eth->R_CFG &= ~MDR_ETH_RCFG_EN_Msk; }

__STATIC_INLINE void MDR_ETH_ResetRXTX_On (MDR_ETH_Type *MDR_Eth) { MDR_Eth->G_CFGH |=   MDR_ETH_GCFGH_XRST_Msk | MDR_ETH_GCFGH_RRST_Msk; }
__STATIC_INLINE void MDR_ETH_ResetRXTX_Off(MDR_ETH_Type *MDR_Eth) { MDR_Eth->G_CFGH &= ~(MDR_ETH_GCFGH_XRST_Msk | MDR_ETH_GCFGH_RRST_Msk); }

__STATIC_INLINE void MDR_ETH_ClearBuffRX(MDR_ETH_Type *MDR_Eth) { MDR_Eth->R_HEAD	= MDR_Eth->R_TAIL; }
__STATIC_INLINE void MDR_ETH_ClearBuffTX(MDR_ETH_Type *MDR_Eth) { MDR_Eth->X_TAIL	= MDR_Eth->X_HEAD; }


__STATIC_INLINE void MDR_ETH_DecCountRx(MDR_ETH_Type *MDR_Eth) { MDR_Eth->STAT	-= 1 << MDR_ETH_STAT_RX_Count_Pos; }

  
//  Events Mask
#define MDR_ETH_EVENT_ReceivedOK      MDR_ETH_EVENT_RF_OK_Msk
#define MDR_ETH_EVENT_FrameLost       MDR_ETH_EVENT_MISSED_F_Msk
#define MDR_ETH_EVENT_RxBuffOver      MDR_ETH_EVENT_OVF_Msk
#define MDR_ETH_EVENT_SomeErr         MDR_ETH_EVENT_SMB_Err_Msk
#define MDR_ETH_EVENT_CRC_Err         MDR_ETH_EVENT_CRC_Err_Msk
#define MDR_ETH_EVENT_ControlFrame    MDR_ETH_EVENT_CF_Msk
#define MDR_ETH_EVENT_LongFrame       MDR_ETH_EVENT_LF_Msk
#define MDR_ETH_EVENT_ShortFrame      MDR_ETH_EVENT_SF_Msk
#define MDR_ETH_EVENT_SendOK          MDR_ETH_EVENT_XF_Ok_Msk
#define MDR_ETH_EVENT_SendErr         MDR_ETH_EVENT_XF_Err_Msk
#define MDR_ETH_EVENT_EmptyBuffTx     MDR_ETH_EVENT_UNDEF_Msk
#define MDR_ETH_EVENT_LateCollision   MDR_ETH_EVENT_LC_Msk
#define MDR_ETH_EVENT_CRS_Lost        MDR_ETH_EVENT_CRS_Lost_Msk
#define MDR_ETH_EVENT_MDIO_IRQ        MDR_ETH_EVENT_MDIO_INT_Msk
#define MDR_ETH_EVENT_MDIO_Ready      MDR_ETH_EVENT_MDIO_RDY_Msk

__STATIC_INLINE void MDR_ETH_ClearEvent(MDR_ETH_Type *MDR_Eth, uint32_t selEvents) { MDR_Eth->IFR	|= selEvents; }
__STATIC_INLINE void MDR_ETH_ClearEventsAll(MDR_ETH_Type *MDR_Eth) { MDR_Eth->IFR	= MDR_ETH_EVENT_CLEAR_ALL; }  

__STATIC_INLINE void MDR_ETH_EnableEventIRQ (MDR_ETH_Type *MDR_Eth, uint32_t selEvents) { MDR_Eth->IMR	|= selEvents; }
__STATIC_INLINE void MDR_ETH_DisableEventIRQ(MDR_ETH_Type *MDR_Eth, uint32_t selEvents) { MDR_Eth->IMR	&= ~selEvents; }

__STATIC_INLINE bool MDR_ETH_GetEventSet(MDR_ETH_Type *MDR_Eth, uint32_t selEvents) { return (MDR_Eth->IFR & selEvents) == selEvents; }

__STATIC_INLINE bool MDR_ETH_IsEventReceivedOk(MDR_ETH_Type *MDR_Eth) { return MDR_ETH_GetEventSet(MDR_Eth, MDR_ETH_EVENT_ReceivedOK); }
__STATIC_INLINE void MDR_ETH_ClearEventReceivedOk(MDR_ETH_Type *MDR_Eth) { MDR_ETH_ClearEvent(MDR_Eth, MDR_ETH_EVENT_ReceivedOK); }


__STATIC_INLINE void MDR_ETH_NVIC_Enable(MDR_ETH_Type *MDR_Eth, uint32_t priority)
{
  if (MDR_Eth == MDR_ETH1)
  {
    NVIC_SetPriority(ETH1_IRQn, priority);
    NVIC_EnableIRQ(ETH1_IRQn);
  }
#ifdef MDR_ETH2	
	else
	{
    NVIC_SetPriority(ETH2_IRQn, priority);
    NVIC_EnableIRQ(ETH2_IRQn);
  }		
#endif
}

__STATIC_INLINE void MDR_ETH_NVIC_Disable(MDR_ETH_Type *MDR_Eth, uint32_t priority)
{
  if (MDR_Eth == MDR_ETH1)
  {
    NVIC_DisableIRQ(ETH1_IRQn);
  }
}


//  ----------    MDIO PHY Control    ----------
bool MDR_ETH_ReadMDIO (MDR_ETH_Type *MDR_Eth, uint16_t addrPHY, uint16_t addrRegInPHY, uint16_t *value);
bool MDR_ETH_WriteMDIO(MDR_ETH_Type *MDR_Eth, uint16_t addrPHY, uint16_t addrRegInPHY, uint16_t value);  

bool MDR_ETH_MDIO_GetMaskSet(MDR_ETH_Type *MDR_Eth, uint16_t addrPHY, uint16_t addrRegPHY, uint16_t setMask);
bool MDR_ETH_MDIO_GetMaskClear(MDR_ETH_Type *MDR_Eth, uint16_t addrPHY, uint16_t addrRegPHY, uint16_t setMask);
void MDR_ETH_MDIO_WaitMaskSet(MDR_ETH_Type *MDR_Eth, uint16_t addrPHY, uint16_t addrRegPHY, uint16_t setMask);

bool MDR_ETH_MDIO_MaskSetClear(MDR_ETH_Type *MDR_Eth, uint16_t addrPHY, uint16_t addrRegPHY, uint16_t clrMask, uint16_t setMask);

__STATIC_INLINE bool MDR_ETH_SetPhyLoopBack(MDR_ETH_Type *MDR_Eth, uint16_t addrPHY)  
{ 
  return MDR_ETH_MDIO_MaskSetClear(MDR_Eth, addrPHY, MDR_ETH_PHY_R0, 0, MDR_ETH_PHY_R0_Loopback_Msk);
}


__STATIC_INLINE bool MDR_ETH_GetAutonegCompleted(MDR_ETH_Type *MDR_Eth, uint16_t addrPHY)  
{ 
  return MDR_ETH_MDIO_GetMaskSet(MDR_Eth, addrPHY, MDR_ETH_PHY_R1, MDR_ETH_PHY_R1_AutonegReady_Msk);
}

__STATIC_INLINE bool MDR_ETH_GetLinkUp(MDR_ETH_Type *MDR_Eth, uint16_t addrPHY)  
{ 
  return MDR_ETH_MDIO_GetMaskSet(MDR_Eth, addrPHY, MDR_ETH_PHY_R1, MDR_ETH_PHY_R1_Link_Msk);
}

__STATIC_INLINE void MDR_ETH_WaitAutonegCompleted(MDR_ETH_Type *MDR_Eth, uint16_t addrPHY)
{ 
  MDR_ETH_MDIO_WaitMaskSet(MDR_Eth, addrPHY, MDR_ETH_PHY_R1, MDR_ETH_PHY_R1_AutonegReady_Msk);
}  

__STATIC_INLINE void MDR_ETH_WaitLinkUp(MDR_ETH_Type *MDR_Eth, uint16_t addrPHY)
{ 
  MDR_ETH_MDIO_WaitMaskSet(MDR_Eth, addrPHY, MDR_ETH_PHY_R1, MDR_ETH_PHY_R1_Link_Msk);
}  

__STATIC_INLINE void MDR_EthPHY_AutoNegRestart(MDR_ETH_Type *MDR_Eth, const uint8_t addrPHY) 
{ 
  MDR_ETH_MDIO_MaskSetClear(MDR_Eth, addrPHY, MDR_ETH_PHY_R0, 0, MDR_ETH_PHY_R0_RESTART_AUTONEG_Msk); 
}


//    Принудительная установка скорости 10Mbps
bool MDR_EthPHY_AutoNegDisable100Mbps(MDR_ETH_Type *MDR_Eth, const uint8_t addrPHY);

__STATIC_INLINE 
void MDR_EthPHY_AutoNegTo10Mbps(MDR_ETH_Type *MDR_Eth, const uint8_t addrPHY) 
{
  MDR_EthPHY_AutoNegDisable100Mbps(MDR_Eth, addrPHY);
  MDR_EthPHY_AutoNegRestart(MDR_Eth, addrPHY);
}

  
#ifdef MDR_HAS_ETH_PHY
  
  #define ETH_INT_PHY_ADDR(eth)   FLD2VAL(eth->PHY_CTRL, MDR_ETH_PHY_CTRL_PHY_ADDR)

  __STATIC_INLINE void MDR_EthIntPHY_AutoNegRestart(MDR_ETH_Type *MDR_Eth) 
  { MDR_EthPHY_AutoNegRestart(MDR_Eth, ETH_INT_PHY_ADDR(MDR_Eth)); }

  __STATIC_INLINE bool MDR_EthIntPHY_AutoNegDisable100Mbps(MDR_ETH_Type *MDR_Eth)
  { return MDR_EthPHY_AutoNegDisable100Mbps(MDR_Eth, ETH_INT_PHY_ADDR(MDR_Eth)); }

  //  Настройка на обмен 10Mbps
  __STATIC_INLINE void MDR_EthIntPHY_AutoNegTo10Mbps(MDR_ETH_Type *MDR_Eth) 
  { MDR_EthPHY_AutoNegTo10Mbps(MDR_Eth, ETH_INT_PHY_ADDR(MDR_Eth)); }
#endif


//===================     MDIO Managable Device Registers Access (MMD)  ==========
typedef struct {
  uint16_t addrPHY;
  uint16_t regMMD_Ctrl;
  uint16_t regMMD_Data;
  uint16_t devad;
} MDR_ETH_MDIO_CfgMMD;

bool MDR_ETH_MDIO_WriteRegMMD(MDR_ETH_Type *MDR_Eth, const MDR_ETH_MDIO_CfgMMD *cfgMMD, uint16_t addrMMD, uint16_t value);
bool MDR_ETH_MDIO_ReadRegMMD (MDR_ETH_Type *MDR_Eth, const MDR_ETH_MDIO_CfgMMD *cfgMMD, uint16_t addrMMD, uint16_t *value);


//  Привязка к одному регистру MMD, для последующего быстрого циклического это регистра (для отладки)
void MDR_ETH_MDIO_BindRegMMD(MDR_ETH_Type *MDR_Eth, const MDR_ETH_MDIO_CfgMMD *cfgMMD, uint16_t addrMMD);

__STATIC_INLINE bool MDR_ETH_MDIO_ReWriteRegMMD(MDR_ETH_Type *MDR_Eth, const MDR_ETH_MDIO_CfgMMD *cfgMMD, uint16_t value)
{ return MDR_ETH_WriteMDIO(MDR_Eth, cfgMMD->addrPHY, cfgMMD->regMMD_Data, value); }

__STATIC_INLINE bool MDR_ETH_MDIO_ReReadRegMMD(MDR_ETH_Type *MDR_Eth, const MDR_ETH_MDIO_CfgMMD *cfgMMD, uint16_t *value)
{ return MDR_ETH_ReadMDIO(MDR_Eth, cfgMMD->addrPHY, cfgMMD->regMMD_Data, value);   }


//===================   Misc Utils   =========================
//	Проверка что МАС адреса одинаковы - с выровненным доступом.
bool MDR_ETH_IsSameMACs(const uint8_t *MAC1, const uint8_t *MAC2);
//  Тоже самое, наверное быстрее, но с невыровненным доступом - не подходит для ядер младше Cortex-M3!!!
bool MDR_ETH_IsSameMACs32(const uint8_t *MAC1, const uint8_t *MAC2);

//	Обмен МАС адресов фрейма
void MDR_ETH_SwapMACs(uint8_t *payload);

// Модификация входного фрейма в эхо фрейм для отправки (меняются только МАС).
MDR_ETH_FrameTX* MDR_ETH_FrameRx_ToEchoTx(MDR_ETH_FrameRX *frameRX);

//	Отправка echo фрейма
__STATIC_INLINE bool MDR_ETH_SendEcho(MDR_ETH_Type *MDR_Eth, MDR_ETH_FrameRX *frameRX)
{
  MDR_ETH_FrameTX *frameTX = MDR_ETH_FrameRx_ToEchoTx(frameRX);	
	return MDR_ETH_TrySendFrame(MDR_Eth, frameTX);
}

//  Копирование МАС адреса
__STATIC_INLINE void MDR_ETH_CopyMAC(uint8_t *destMem, const uint8_t *fromMem)
{
  uint16_t *dest = (uint16_t *)destMem;
  uint16_t *from = (uint16_t *)fromMem;
  dest[0] = from[0];
	dest[1] = from[1];
	dest[2] = from[2];
}

#define MDR_ETH_FillDestMAC(pFrame, destMAC) MDR_ETH_CopyMAC((uint8_t *)pFrame, destMAC);


//	Функция формирования простейшего фрейма для быстрой проверки соединения. Для тестовых целей.
void MDR_ETH_Debug_FillTestFrameTX(MDR_ETH_FrameTX* frameTX, uint16_t frameLen, uint8_t* srcMAC, uint8_t* destMAC);

//	Отправка тестового фрейма заданной длины
__STATIC_INLINE bool MDR_ETH_Debug_SendTestFrame(MDR_ETH_Type *MDR_Eth, uint16_t frameLen, uint8_t* srcMAC, uint8_t* destMAC)
{
  MDR_ETH_FrameTX frameTX;	
	MDR_ETH_Debug_FillTestFrameTX(&frameTX, frameLen, srcMAC, destMAC);
	return MDR_ETH_TrySendFrame(MDR_Eth, &frameTX);
}

//	Отправка тестового фрейма
__STATIC_INLINE bool MDR_ETH_Debug_SendTestFrameBroadcast(MDR_ETH_Type *MDR_Eth, uint16_t frameLen, uint8_t* srcMAC)
{
	uint8_t broadcastMAC[MDR_ETH_MAC_LEN] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
  return MDR_ETH_Debug_SendTestFrame(MDR_Eth, frameLen, srcMAC, broadcastMAC);
}

//  Фрейм паузы
void MDR_ETH_FillPauseFrameTX(MDR_ETH_FrameTX* frameTX, uint8_t* srcMAC, uint16_t pause);

__STATIC_INLINE void MDR_ETH_PauseFrame_SetPause(MDR_ETH_FrameTX* frameTX, uint16_t newPause)
{
  eth_frame_t *frame = (eth_frame_t *)frameTX->frame;
  *((uint16_t *)&(frame->payload[2])) = htons(newPause);
}

__STATIC_INLINE uint16_t MDR_ETH_PauseFrame_GetPause(const eth_frame_t *frame)
{
  return ntohs(*((uint16_t *)&(frame->payload[2])));
}

//  Замена типа фрейма
__STATIC_INLINE void MDR_ETH_FrameFill_FrameType(void* frame, uint16_t frameType) { ((eth_frame_t *)frame)->type = frameType; }


#endif // MDR_ETHERNET_H


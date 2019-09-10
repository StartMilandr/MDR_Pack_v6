#include <MDR_RST_Clock.h>
#include <MDRB_UART_Debug.h>
#include <MDR_DMA.h>
#include <stdio.h>


//  ------  DMA Config  ------
#ifdef MDR_DMA_CHMUX_LIKE_VE8
  #define DMA_Chan_RX            0
  #define DMA_Chan_RX_Src        MDR_DMA_CH_SREQ_UART1_RX
#elif defined (USE_MDR1986VE92) || defined(USE_BOARD_VE91) || defined(USE_BOARD_VE94)
  #define DMA_Chan_RX            MDR_DMA_CH_SREQ_UART2_RX
#else
  #define DMA_Chan_RX            MDR_DMA_CH_SREQ_UART1_RX  
#endif

#define DMA_IRQ_PRIORITY       0

#define DATA_LEN        5
static  uint8_t         DataRX[DATA_LEN + 1];
static  MDR_DMA_ChCtrl  RestartCtrl_RX;

static const MDR_DMA_CfgTransf  cfgDMA_RX = { 
  //  DMA
  .CfgFileds.Mode         = DMA_MODE_Base,
  .CfgFileds.UseBurst     = MDR_Off,
  .CfgFileds.ArbitrCount  = DMA_Arbitr_1,  
  .CfgFileds.DataSize     = MDR_DMA_Data8,
  .CfgFileds.Src_AddrInc  = MDR_DMA_AddrIncOff,
  .CfgFileds.Dest_AddrInc = MDR_DMA_AddrInc8,
  //  NULL for default init
  .Src_ProtAHB  = NULL,
  .Dest_ProtAHB = NULL,
};

void DMA_ProcessCycleCompleted(void);

int main (void)
{
  //  Максимальная скорость тактирования
  MDR_CLK_Enable_RST_BPK();
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDRB_CLK_PLL_HSE_RES_MAX; 
  MDR_CPU_SetClock_PLL_HSE(&cfgPLL_HSE, true);  
  
  //  UART по умолчанию
  MDR_UART_DBG_InitEx(UART_DEBUG_BAUD_DEF, true, true);  
  
  MDR_UART_RX_DMA_Enable(UART_DBG->UARTx);
  
  //  DMA
  MDR_DMA_Init();
  RestartCtrl_RX = MDR_DMA_InitTransfPri(DMA_Chan_RX, (uint32_t)&(UART_DBG->UARTx)->DR, (uint32_t)DataRX, DATA_LEN, &cfgDMA_RX);
    
  //  Select PeriphEvents to DMA_Channels
#ifdef MDR_DMA_CHMUX_LIKE_VE8  
  MDR_DMA_SetChannelSource(DMA_Chan_RX, DMA_Chan_RX_Src);
#endif  
  
  //  Enable IRQ
#ifndef MDR_DMA_IRQ_LIKE_VE8  
  MDR_DMA_EnableIRQ(DMA_IRQ_PRIORITY);
#else  
  MDR_DMA_EnableIRQ(DMA_Chan_RX, DMA_IRQ_PRIORITY);
#endif
  
  
  //  DMA Start Read
  MDR_UART_ClearRxFIFO(UART_DBG->UARTx);
  MDR_DMA_StartChannel(DMA_Chan_RX, false, false, true);
  
  while(1)
  {
  
  }
}

void DMA_ProcessCycleCompleted(void)
{
  if (MDR_DMA_GetChannelCompleted(DMA_Chan_RX))
  {
    //  Restart DMA Cycle
    MDR_UART_ClearRxFIFO(UART_DBG->UARTx);
    MDR_DMA_InitNextCyclePri(DMA_Chan_RX, RestartCtrl_RX);
    MDR_DMA_ReStartChannel(DMA_Chan_RX);
    
    //  Echo received data
    DataRX[DATA_LEN] = 0;
    printf("%s\n", DataRX);
  }  
}

#ifdef MDR_DMA_IRQ_LIKE_VE8
  void DMA_DONE0_IRQHandler(void)
  {
    DMA_ProcessCycleCompleted();
  }
#else
  void DMA_IRQHandler(void)
  {
    DMA_ProcessCycleCompleted();
  }
#endif


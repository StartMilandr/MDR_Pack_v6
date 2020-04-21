#include <MDR_Config.h>
#include <MDR_RST_Clock.h>
#include <MDR_Ethernet.h>
#include <MDR_Ethernet_FrameDefs.h>
#include <MDR_Funcs.h>
#include <MDRB_Buttons.h>
#include <MDRB_LEDs.h>
#include <string.h>

#include "MDR_Ethernet_Cfg1.h"
#include "MDRB_ETH_ExtPHY_MII.h"

#include "MDR_HSRPRP_Config.h"
#include "MDR_HSRPRP_Frames.h"
#include "MDR_HSRPRP_Error.h"
#include "MDR_HSRPRP_RX.h"
#include "MDR_HSRPRP_TX.h"
#include "MDR_HSRPRP_Time.h"
#include "MDR_HSRPRP_DuplicateTables.h"
#include "MDR_HSR.h"
#include "MDR_HSRPRP_NodeTable.h"

#include "MDR_HSRPRP_Core.h"

#define LED_SHOW_MS 			1000

#define TEST_FRAME_LEN		100

//  Ethernet
//uint16_t destMAC[] = {0xFFFF, 0xFFFF, 0xFFFF};
uint8_t destMAC[] = ETHCFG1_MAC_INIT_BYTES_ARR;


MDR_HSR_NodeCfg cfgNode = {
  //uint8_t             multicast_addr[6];
	.hostMAC 									= ETHCFG1_MAC_INIT_BYTES_ARR,
  .forwMode 								= MDR_HSR_HsrForw,
  .hasLocalCriteria 				= false,
  .lanID 										= MDR_HSRPRP_LanA,
	.seqNum 									= 0,
	.lastTimeForgetDuplicate  = 0,
	.lastTimeForgetNode				= 0,
	.lastTimeForgetProxy			= 0,
	.lastTimeSuperSend				= 0,

};

void HostProcessReceivedFrame(MDR_ETH_FrameRX *frameRX);
void MDR_HSRPRP_EventHandler(MDR_HSRPRP_Events event);

int main(void)
{   
#ifndef USE_MLDR155
  //  Максимальная скорость тактирования
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDRB_CLK_PLL_HSE_RES_MAX;
  MDR_CPU_SetClock_PLL_HSE(&cfgPLL_HSE, true);
  uint32_t freqCPU_Hz = MDR_CPU_GetFreqHz(true);
#else
  uint32_t freqCPU_Hz = MDR_MLDR155_FPGA_CPU_HZ;  
#endif	
	
  MDRB_LED_InitALL();
  MDRB_Buttons_Init(DEBOUNCE_MS_DEF, freqCPU_Hz);
	

  //  ---  НАСТРОЙКА ETHERNET  ---  
#ifndef USE_MLDR155
	//	Enable EthClock  
	MDR_Eth_SetClockHSE2();
  MDR_ETH_MAC_CfgRegs  cfgRegs = MDR_ETH_MAC_INIT_DEF(128, MDC_DIV_le160MHz); 
#else
  //  Тактирование для Ethernet - 50МГц от FPGA
  MDR_Eth_SetClock(MDR_Div128P_div1, MDR_RST_ASYNC_IN_FPGA);  
  MDR_ETH_MAC_CfgRegs  cfgRegs = MDR_ETH_MAC_INIT_DEF(50, MDC_DIV_le80MHz);
#endif
	
  //  Ethernet Init and start
  MDR_ETH_InitCfg      initCfg = {
    .cfgRegsMAC = &cfgRegs,
    .phyCfgReg  = MDR_REG_PHY_CTRL
  };  
    
  MDR_Eth_Init(MDR_ETH1, &initCfg);  
  MDR_Eth_Start(MDR_ETH1);  
	MDR_ETH_NVIC_Enable(MDR_ETH1, 0);

#ifdef 	MDR_ETH2
  MDR_Eth_Init(MDR_ETH2, &initCfg);
  MDR_Eth_Start(MDR_ETH2);
	MDR_ETH_NVIC_Enable(MDR_ETH2, 0);
#endif

	//	Show started by LEDs
  MDRB_LED_Set(MDRB_LED_PinAll, true);
  MDR_Delay_ms(LED_SHOW_MS, freqCPU_Hz);
  MDRB_LED_Set(MDRB_LED_PinAll, false);

	//  Инициализация HSRPRP:
	MDR_HSR_CoreInit(MDR_HSRPRP_EventHandler);
//	MDR_HSRPRP_TimeInit();
	

  // ссылка на обрабатываемый frameItem, frameItem - это сам фрейм данных и сопутствующая информация к нему для обработки.
	MDR_HSRPRP_FrameItem* frameItem;

  while(1)
  {
		//	Send Test frame
		if (MDRB_BntClicked_Down(true))
		{
		  MDR_ETH_Debug_SendTestFrameBroadcast(MDR_ETH1, TEST_FRAME_LEN, cfgNode.hostMAC);
		}
		
		//	Send HSR tagged frame
    if (MDRB_BntClicked_Up(true))
		{
			//	Получаем для frameItem для заполнения frameTX
			frameItem = ETH_HSRPRP_HostGetFrameItem();
			if (frameItem != NULL)
			{
				MDR_ETH_FrameTX *frameTX = FrameItemGetFrameTX(frameItem);
				//	Заполняем frameTX
				MDR_ETH_Debug_FillTestFrameTX(frameTX, TEST_FRAME_LEN, cfgNode.hostMAC, destMAC);			
				//	Посылаем фрейм на обработку и forwarding
				ETH_HSRPRP_HostSendFrameItem(frameItem);
				
MDR_LOG_Add_def(LOG_HOST_SEND);
MDR_LOG_Add_def(frameItem->_frmIndex);
			}
		}
		
		//	Send SuperHSR frame
    if (MDRB_BntClicked_Right(true))
    {
			MDR_HSR_SendSuperFrame(&cfgNode);
		}
		
		//	Process HSR DANH mode
		MDR_HSR_ProcessDANH(&cfgNode, HostProcessReceivedFrame);
		//	Process Timed tasks
		MDR_HSR_ProcessNextTimedTask(&cfgNode, MDR_HSRPRP_GetHostTime);
  }
}

void HostProcessReceivedFrame(MDR_ETH_FrameRX *frameRX)
{
	MDRB_LED_Toggle(MDRB_LED_1);
	MDR_ETH_FrameRx_ToEchoTx(frameRX);
	MDRB_LED_Toggle(MDRB_LED_2);
	
MDR_LOG_Add_def(LOG_HOST_RX);	
}

void MDR_HSRPRP_EventHandler(MDR_HSRPRP_Events event)
{
  switch (event) {
		case MDR_HSRPRP_EVENT_RingBroken: 
			//	Do some stuff
			break;
	}
}

//------------------    HSR-PRP Receive ---------------
void ETHx_HSRPRP_IRQHandler(MDR_ETH_Type *MDR_Eth, MDR_HSRPRP_FramePort portSrc)
{
  if (MDR_ETH_IsEventReceivedOk(MDR_Eth))
  {
    ETH_HSRPRP_ReceiveFrame(MDR_Eth, portSrc);
    // MDR_ETH_ClearEventReceivedOk(MDR_Eth); // Выставить GCFGL.RCLR_EN = 1, сброс IFR при чтении.
  }
}

void ETH1_IRQHandler(void)
{
  ETHx_HSRPRP_IRQHandler(MDR_ETH1, ETH1_HSRPRP_PORT);
MDR_LOG_Add_def(LOG_PORTA_RX);	
}

#ifdef 	MDR_ETH2
	void ETH2_IRQHandler(void)
	{
		ETHx_HSRPRP_IRQHandler(MDR_ETH2, ETH2_HSRPRP_PORT);
MDR_LOG_Add_def(LOG_PORTB_RX);		
	}
#endif



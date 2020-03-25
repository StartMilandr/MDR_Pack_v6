#include "MDR_Config.h"
#include <MDR_RST_Clock.h>
#include <MDR_Ethernet.h>
#include <MDR_Ethernet_FrameDefs.h>
#include <MDRB_LEDs.h>
#include <MDR_Funcs.h>
#include <string.h>

#include "MDR_Ethernet_Cfg1.h"
#include "MDRB_ETH_ExtPHY_MII.h"


#define LED_CYCLE             MDRB_LED_1
#define LED_TRANSF            MDRB_LED_2
#define LED_CYCLIC_PERIOD     5000000

#define MAX_ETH_FRAME_LEN     1514

#define MDR_Eth               MDR_ETH1

uint16_t myMAC[] = {ETHCFG1_MAC_L, ETHCFG1_MAC_M, ETHCFG1_MAC_H};

MDR_ETH_FrameTX echoFrame  __attribute__((section("EXECUTABLE_MEMORY_SECTION"))) __attribute__ ((aligned (4)));


bool frameReceived = false;
MDR_ETH_FrameStatusRX statusRX;


int main(void)
{
  uint32_t cnt = 0;
  
  //  Максимальная скорость тактирования
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDRB_CLK_PLL_HSE_RES_MAX;
  MDR_CPU_SetClock_PLL_HSE(&cfgPLL_HSE, true);
  uint32_t freqCPU_Hz = MDR_CPU_GetFreqHz(true);
  
  //  Internal PHY, HSE2 8MHz * 16 = 128MHz  
  MDR_ETH_MAC_CfgRegs  cfgRegs = MDR_ETH_MAC_INIT_DEF(128, MDC_DIV_le160MHz); 
  MDR_Eth_SetClockHSE2();

//  ---  НАСТРОЙКА ETHERNET  ---  
  MDR_ETH_InitCfg      initCfg = {
    .cfgRegsMAC = &cfgRegs,
    .phyCfgReg  = MDR_REG_PHY_CTRL
  };  
  MDR_Eth_Init(MDR_Eth, &initCfg);
  MDR_Eth_Start(MDR_Eth);
  
  //  Wait autonegotiation or PC connection
  if (ETHCFG1_PHY_AUTONEG_EN)
  {
    MDR_ETH_WaitAutonegCompleted(MDR_Eth, ETHCFG1_PHY_ADDR);
  }
  else  
    MDR_ETH_WaitLinkUp(MDR_Eth, ETHCFG1_PHY_ADDR);
  
//  ---  ПРОЧЕЕ - светодиоды   ---  
  MDRB_LED_Init(LED_CYCLE | LED_TRANSF);  
  
    
  while (1)
  {
    //  Проверка приема по Ethernet
    if (MDR_ETH_TryReadFrame(MDR_Eth, echoFrame.frame, &statusRX))
    {     
      //  Индикация получения команды от РС      
      MDRB_LED_Toggle(LED_TRANSF);
      
      //  Change MAC
      eth_frame_t *ethFrame = (void *)echoFrame.frame;
      uint8_t tmpAddr[6];
      memcpy(tmpAddr, ethFrame->from_addr, 6);
      memcpy(ethFrame->from_addr, ethFrame->to_addr, 6);
      memcpy(ethFrame->to_addr, tmpAddr, 6);
      
      //  Ответный траффик
      echoFrame.frameLen = statusRX.Fields.Length - 4;
      while (!MDR_ETH_TrySendFrame(MDR_Eth, &echoFrame)) {}      
    }
    
    //  Индикация того что цикл исполняется
    ++cnt;
    if (cnt == LED_CYCLIC_PERIOD)
    {  
      MDRB_LED_Toggle(LED_CYCLE);
      cnt = 0;
    }  
  }
}



#include <MDR_Config.h>
#include <MDR_RST_Clock.h>
#include <MDR_GPIO.h>
#include <MDR_Funcs.h>
#include <MDR_Ethernet.h>
#include <MDR_Ethernet_Cfg1.h>
#include <stdio.h>
#include <MDR_Timer.h>
#include <MDRB_LEDs.h>
#include <MDRB_Buttons.h>

#ifdef USE_MDR1986VE1
  #define ETH_TEST   MDR_ETH1
#else
  #define ETH_TEST   MDR_ETH2
#endif

#define DEBOUNCE_MS   10

MDR_ETH_FrameRX  frameRX __RAM_EXEC_ALIGN4;
uint32_t         framesCountRX;
uint32_t         sentFrameIndex;

#define FRAME_LEN_TX_MAX  1024
MDR_ETH_FrameTX frameTX  __RAM_EXEC_ALIGN4;
uint8_t MAC_A[6] __RAM_ALIGN4 = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66};
uint8_t MAC_B[6] __RAM_ALIGN4 = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC};

#define KEY_UP_FRAME_LEN     64
#define KEY_RIGHT_FRAME_LEN  128
#define KEY_DOWN_FRAME_LEN   512
#define KEY_LEFT_FRAME_LEN   1024

#define LED_TX    MDRB_LED_1
#define LED_RX    MDRB_LED_2

int main(void)
{
  //  Максимальная скорость тактирования
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDRB_CLK_PLL_HSE_RES_MAX;
  MDR_CPU_SetClock_PLL_HSE(&cfgPLL_HSE, true);
  uint32_t freqCPU_Hz = MDR_CPU_GetFreqHz(true); 
    
  MDRB_LED_Init(LED_TX | LED_RX);
  MDRB_Buttons_Init(DEBOUNCE_MS, freqCPU_Hz);

  //  НАСТРОЙКА ETHERNET
  MDR_Eth_SetClockHSE2();
  //    Internal PHY, HSE2 8MHz * 16 = 128MHz  
  MDR_ETH_MAC_CfgRegs  cfgRegs = MDR_ETH_MAC_INIT_DEF(128, MDC_DIV_le160MHz);   
  MDR_ETH_InitCfg      initCfg = {
    .cfgRegsMAC = &cfgRegs,
    .phyCfgReg  = MDR_REG_PHY_CTRL
  };  
  MDR_Eth_Init(ETH_TEST, &initCfg);
  MDR_Eth_Start(ETH_TEST);
  
  MDR_ETH_Debug_FillTestFrameTX(&frameTX, FRAME_LEN_TX_MAX, MAC_A, MAC_B);  
  
  while(1)
  {
    //  Прием по Ethernet
    if (MDR_ETH_TryReadFrameF(ETH_TEST, &frameRX))
    {
      framesCountRX++;    
      MDRB_LED_Toggle(LED_RX);
    }

    //  Передача фреймов по кнопкам
    if (MDRB_BntClicked_Up(true))
    {
      frameTX.frameLen = KEY_UP_FRAME_LEN;
      ((eth_frame_t *)frameTX.frame)->type = KEY_UP_FRAME_LEN;      
      MDR_ETH_TrySendFrame(ETH_TEST, &frameTX);
      MDRB_LED_Toggle(LED_TX);
    }
    
    if (MDRB_BntClicked_Right(true))
    {
      frameTX.frameLen = KEY_RIGHT_FRAME_LEN;
      ((eth_frame_t *)frameTX.frame)->type = KEY_RIGHT_FRAME_LEN;      
      MDR_ETH_TrySendFrame(ETH_TEST, &frameTX);
      MDRB_LED_Toggle(LED_TX);
    }
    
    if (MDRB_BntClicked_Down(true))
    {
      frameTX.frameLen = KEY_DOWN_FRAME_LEN;
      ((eth_frame_t *)frameTX.frame)->type = KEY_DOWN_FRAME_LEN;      
      MDR_ETH_TrySendFrame(ETH_TEST, &frameTX);
      MDRB_LED_Toggle(LED_TX);
    }
    
    if (MDRB_BntClicked_Left(true))
    {
      frameTX.frameLen = KEY_LEFT_FRAME_LEN;
      ((eth_frame_t *)frameTX.frame)->type = KEY_LEFT_FRAME_LEN;      
      MDR_ETH_TrySendFrame(ETH_TEST, &frameTX);
      MDRB_LED_Toggle(LED_TX);
    }
  }
}



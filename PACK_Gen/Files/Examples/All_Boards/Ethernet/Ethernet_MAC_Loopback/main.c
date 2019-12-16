#include "MDR_Config.h"
#include <MDR_RST_Clock.h>
#include <MDR_Ethernet.h>
#include <MDR_Ethernet_FrameDefs.h>
#include "MDR_Ethernet_Cfg1.h"
#include <string.h>


#include <MDR_Funcs.h>
#include <MDRB_LEDs.h>
#include <MDRB_Buttons.h>


#define MDR_Eth               MDR_ETH1


//--------      ETHERNET SETTINGS  ---------
uint16_t myMAC[] = {ETHCFG1_MAC_L, ETHCFG1_MAC_M, ETHCFG1_MAC_H};
uint8_t toMAC[] = {0x1c, 0x34, 0x56, 0x78, 0x9a, 0xbc};


#ifdef IS_STARTER
  #define MAC_DEST    MAC1
  #define MAC_SRC     MAC2
#else
  #define MAC_DEST    MAC2
  #define MAC_SRC     MAC1
#endif

#define FRAME_LEN_MIN   64
#define FRAME_LEN_MAX   1514

uint8_t InpArr[FRAME_LEN_MAX] __attribute__((section("EXECUTABLE_MEMORY_SECTION"))) __attribute__ ((aligned (4)));
MDR_ETH_FrameTX outFrame  __attribute__((section("EXECUTABLE_MEMORY_SECTION"))) __attribute__ ((aligned (4)));

#define REPEAT_LEN_COUNT 5

//--------      LED Status  ---------
#define LED_TRANSFER      MDRB_LED_1
#define LED_START         MDRB_LED_2
#define LED_DATA_ERR      MDRB_LED_3
#define LED_LEN_ERR       MDRB_LED_4

#define LED_ALL     (LED_TRANSFER | LED_START | LED_DATA_ERR | LED_LEN_ERR)

#define LED_FRAME_PERIOD  1000


void LED_CheckSwitch(uint32_t ledSel, int32_t * ledIndex);

//--------      ETHERNET Status  ---------
#define BTN_DEBOUNCE_MS   10

uint32_t GetReceivedErrCount(MDR_ETH_FrameTX *txFrame, uint8_t *inpFrame, MDR_ETH_FrameStatusRX statusRX, uint16_t activeLen);
void     SendTestFrame(MDR_ETH_FrameTX *txFrame, uint16_t frameLen, uint16_t frameInd);

uint32_t transfFrameIndex = 0;

int main()
{
  MDR_ETH_FrameStatusRX statusRX;  
  uint32_t repeatLenTX;
  int32_t  LED_TransfInd = LED_FRAME_PERIOD;
  uint32_t frameLen = FRAME_LEN_MIN;  
  uint32_t doFrameSend = 0;
  uint32_t Rx_ErrCnt = 0;
  
  //  Максимальная скорость тактирования
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDRB_CLK_PLL_HSE_RES_MAX;
  MDR_CPU_SetClock_PLL_HSE(&cfgPLL_HSE, true);
  
  //  Инициализация кнопок и светодиодов  
  uint32_t freqCPU_Hz = MDR_CPU_GetFreqHz(true);
  MDRB_Buttons_Init(BTN_DEBOUNCE_MS, freqCPU_Hz);
  MDRB_LED_Init(LED_ALL); 
  
  //  Инициализация Ethernet - все настройки в MDR_Ethernet_Cfg1
  MDR_ETH_MAC_CfgRegs  cfgRegs = MDR_ETH_MAC_INIT_DEF(144, 10);
  MDR_ETH_InitCfg      initCfg = {
      .cfgRegsMAC = &cfgRegs,
      .phyCfgReg = MDR_REG_PHY_CTRL
    };

  MDR_Eth_SetClockHSE2();
  MDR_Eth_Init(MDR_Eth, &initCfg);
  MDR_Eth_Start(MDR_Eth);

      
  while(1)
  { 
   
    if (MDRB_BntClicked_Up(true))
    {
      MDRB_LED_Set(LED_ALL, 0);
      MDRB_LED_Set(LED_START, 1);
      
      transfFrameIndex = 0;
      repeatLenTX = 0;      
      frameLen = FRAME_LEN_MIN;
      LED_TransfInd = 0;      
      
      doFrameSend = 1;      
    }
        
    //  ------------  Receive Frame -------------
    if (MDR_ETH_TryReadFrame(MDR_Eth, InpArr, &statusRX))
    { 
      Rx_ErrCnt = GetReceivedErrCount(&outFrame, InpArr, statusRX, frameLen);

      if (!Rx_ErrCnt)
      {
        //  Увеличиваем счетчик передач
        transfFrameIndex++;
        //  Увеличиваем длину фрейма
        repeatLenTX++;
        if (repeatLenTX >= REPEAT_LEN_COUNT)
        {  
          repeatLenTX = 0;        
          frameLen++;
        }      
    
        //  Led Period
        LED_CheckSwitch(LED_TRANSFER, &LED_TransfInd);
        
        //  Сброс статуса
        MDR_Eth->STAT = 0;
        
        //  Запуск передачи следующего фрейма
        if (frameLen <= FRAME_LEN_MAX)      
          doFrameSend = 1;
        else
          MDRB_LED_Set(LED_START, 0);
      }
    }  
    
    //  ------------  Send Frame ---------
    if (doFrameSend)
    {
      SendTestFrame(&outFrame, frameLen, transfFrameIndex);      
      doFrameSend = 0;
    }  
  }
}  

//  Переключение светодиодов по периоду
void LED_CheckSwitch(uint32_t ledSel, int32_t * ledIndex)
{
  (*ledIndex)--;
  if ((*ledIndex) < 0)
  {  
    (*ledIndex) = LED_FRAME_PERIOD;
    MDRB_LED_Toggle(ledSel);    
  }  
}


uint32_t GetReceivedErrCount(MDR_ETH_FrameTX *txFrame, uint8_t *rxFrame, MDR_ETH_FrameStatusRX statusRX, uint16_t activeLen)
{  
  uint16_t errDataCount = 0;
  
  //  Проверка длины пакета
  if (statusRX.Fields.Length != (activeLen + ETH_CRC_SIZE))
    MDRB_LED_Set(LED_LEN_ERR, 1);

  eth_frame_t *inFrame  = (void *)rxFrame;
  uint8_t     *inPayload = (void *)inFrame->payload;
  
  uint16_t dataCnt = statusRX.Fields.Length - sizeof(eth_frame_t) - ETH_CRC_SIZE;
  uint16_t i;
  uint8_t *pOutData = txFrame->frame + sizeof(eth_frame_t);
  for (i = 0; i < dataCnt; ++i)
  {
    if (inPayload[i] != pOutData[i])
      errDataCount++;
  }
  if (errDataCount)
    MDRB_LED_Set(LED_DATA_ERR, 1);
  
  return errDataCount;
}


void SendTestFrame(MDR_ETH_FrameTX *txFrame, uint16_t frameLen, uint16_t frameInd)
{
  eth_frame_t *outFrame   = (void *)txFrame->frame;
  uint8_t     *outPayload = (void *)outFrame->payload;
  
  //  Set Control Length
  txFrame->frameLen = frameLen;
  //  Fill Output Frame
	memcpy(outFrame->from_addr, myMAC, 6);
	memcpy(outFrame->to_addr,   toMAC, 6);  
  outFrame->type = REV_BYTES16(frameLen - sizeof(eth_frame_t));
  
  uint16_t dataCnt = frameLen - sizeof(eth_frame_t);
  uint16_t i;
  for (i = 0; i < dataCnt; ++i)
    outPayload[i] = frameInd; // + i;
  
  while (!MDR_ETH_TrySendFrame(MDR_Eth, txFrame)) {}
}  



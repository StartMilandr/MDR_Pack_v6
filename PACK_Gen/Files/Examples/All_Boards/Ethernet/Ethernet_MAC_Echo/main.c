#include "MDR_Config.h"
#include <MDR_RST_Clock.h>
#include <MDR_Ethernet.h>
#include <MDR_Ethernet_FrameDefs.h>
#include "MDR_Ethernet_Cfg1.h"
#include <MDRB_LEDs.h>
#include <string.h>

//  ОПИСАНИЕ:
/*
  Пример ждет входящий фрейм от РС, в котором приходит количество фреймов которые необходимо послать в ответ и количество байт в фрейме.
  Режима работы буферов задается в MDR_ConfigVE1.h, остальные настройки блока Ethernet задаются в MDR_Ethernet_Cfg1.h 
  и макросом собираются в значения регистров для инициализации.
  
  ОСОБЕННОСТЬ:
  При использовании режима буферов MDR_ETH_BUFF_AUTO_PTR с прерываниями есть опасность, что прерывание прервет запись данных в буфер на отправку. 
  Т.е. указатель X_Head (аппаратно увеличивающийся при выдаче данных из буфера в линию) догонит X_Tail (увеличивается при записи данных в буфер), 
  потому что запись в буфер прервется прерыванием. Т.к. фремй записан в буфер не полностью, X_Tail не будет указывать на конец фрейма и фрейм уйдет битый.
  Чтобы избежать этого в данном примере вставлено выключение прерываний на время выдачи ответа - __disable_irq.
*/

#define LED_CYCLE             MDRB_LED_1
#define LED_TRANSF            MDRB_LED_2
#define LED_CYCLIC_PERIOD     5000000

#define MAX_ETH_FRAME_LEN     1514

#define MDR_Eth               MDR_ETH1

uint16_t myMAC[] = {ETHCFG1_MAC_L, ETHCFG1_MAC_M, ETHCFG1_MAC_H};

uint8_t         inpFrame[MAX_ETH_FRAME_LEN] __attribute__((section("EXECUTABLE_MEMORY_SECTION"))) __attribute__ ((aligned (4)));
MDR_ETH_FrameTX outFrame __attribute__((section("EXECUTABLE_MEMORY_SECTION"))) __attribute__ ((aligned (4)));

void Eth_Send_Echo(MDR_ETH_FrameStatusRX statusRX, uint8_t *InpFrame);
void ETH1_IRQHandler(void);

bool frameReceived = false;
MDR_ETH_FrameStatusRX statusRX;

int main(void)
{
  uint32_t cnt = 0;
  
  //  Максимальная скорость тактирования
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDRB_CLK_PLL_HSE_RES_MAX;
  MDR_CPU_SetClock_PLL_HSE(&cfgPLL_HSE, true);
  
  //  Инициализация кнопок
  MDRB_LED_Init(LED_CYCLE | LED_TRANSF);  
  
  //  Инициализация Ethernet - все настройки в MDR_Ethernet_Cfg1
  MDR_ETH_MAC_CfgRegs  cfgRegs = MDR_ETH_MAC_INIT_DEF(144, 10);
  MDR_ETH_InitCfg      initCfg = {
    .cfgRegsMAC = &cfgRegs,
    .phyCfgReg = MDR_REG_PHY_CTRL
  };

  MDR_Eth_SetClockHSE2();
  MDR_Eth_Init(MDR_Eth, &initCfg);
  MDR_Eth_Start(MDR_Eth);
  
#if ETHCFG1_IRQ_ON_RECEIVE_OK
  MDR_ETH_NVIC_Enable(MDR_Eth, 0);
#endif  

  //  Wait autonegotiation or PC connection
  if (ETHCFG1_PHY_MODE == MDR_ETH_PHY_CTRL_MODE_Auto)
    MDR_ETH_WaitAutonegCompleted(MDR_Eth, ETHCFG1_PHY_ADDR);
  else  
    MDR_ETH_WaitLinkUp(MDR_Eth, ETHCFG1_PHY_ADDR);
   
  while (1)
  {
    //  Проверка приема по Ethernet
#if ETHCFG1_IRQ_ON_RECEIVE_OK    
    if (frameReceived)
#else
    if (MDR_ETH_TryReadFrame(MDR_Eth, inpFrame, &statusRX))
#endif
    {     
      //  Индикация получения команды от РС      
      MDRB_LED_Toggle(LED_TRANSF);
      
      //  Ответный траффик
      __disable_irq();
      Eth_Send_Echo(statusRX, inpFrame);
      frameReceived = false;      
      __enable_irq();
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

void ETH1_IRQHandler(void)
{
  frameReceived = MDR_ETH_TryReadFrame(MDR_ETH1, inpFrame, &statusRX);
  
#if !ETHCFG1_EVENT_CLR_ON_READ
  MDR_ETH_ClearEvent(MDR_ETH1, MDR_ETH_EVENT_ReceivedOK);
#endif  
}
  
void Eth_Send_Echo(MDR_ETH_FrameStatusRX statusRX, uint8_t *InpFrame)
{
  uint16_t echoPayloadLen;
  uint16_t echoFrameCount;
  uint16_t i;
  
  eth_frame_t *inFrame     = (void *)InpFrame;
  uint16_t    *inPayload   = (void *)inFrame->payload;
  eth_frame_t *outFrm      = (void *)outFrame.frame;
  uint8_t     *outPayload  = (void *)outFrm->payload;
  
  echoPayloadLen   = REV_BYTES16(inPayload[0]) - sizeof(eth_frame_t);
  echoFrameCount = REV_BYTES16(inPayload[1]);
    
  //  Fill Output Frame
	memcpy(outFrm->to_addr, inFrame->from_addr, 6);
	memcpy(outFrm->from_addr, myMAC, 6);  
  outFrm->type = REV_BYTES16(echoPayloadLen);
  for (i = 1; i < (echoPayloadLen); ++i)
    outPayload[i] = i;
  
  //  Send reply frames
  for (i = 0; i < echoFrameCount; ++i)
  {
    //  Write Frame Index to output frame
    outPayload[0] = i;
    //  Send frame
    outFrame.frameLen = echoPayloadLen + sizeof(eth_frame_t);
    while (!MDR_ETH_TrySendFrame(MDR_Eth, &outFrame)) {}
  }
}


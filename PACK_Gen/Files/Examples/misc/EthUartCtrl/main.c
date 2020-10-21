#include <MDR_Config.h>
#include <MDR_RST_Clock.h>
#include <MDR_GPIO.h>
#include <MDR_Funcs.h>
#include <MDR_UART.h>
#include <MDRB_UART_Debug.h>
#include <MDR_Ethernet.h>
#include <MDR_Ethernet_Cfg1.h>
#include <stdio.h>
#include <MDR_Timer.h>
#include <MDRB_LEDs.h>
#include <MDRB_Buttons.h>

// UART Messages
#define  UART_CMD_LEN     9

typedef __PACKED_STRUCT {
  uint16_t  _resAlign16;
  uint8_t   _resAlign8;
  uint8_t   dataRx[UART_CMD_LEN];
} UART_MessAligned_Buff;

typedef __PACKED_STRUCT {
  uint16_t  _resAlign16;
  uint8_t   _resAlign8;
  uint8_t   cmd;
  uint16_t  addr;
  uint16_t  data;
} UART_CmdAligned_Buff;

UART_MessAligned_Buff  uartMess;
uint8_t  uartCmdLen = 0;
uint32_t uartUndefIrqErrCount = 0;
uint32_t uartCmdLenErrCount = 0;
bool     uartDoProcessCmd = false;
static uint16_t _lastPhyStatus = 0;

//static bool CheckMessLen(uint8_t refLen);
static void ReadRegMAC(void);
static void WriteRegMAC(void);
static void ReadRegPHY(void);
static void WriteRegPHY(void);
static void ReadFrameRx(void);
static void ReadInfo(void);
static void CheckLinkRoutine(void);

MDR_ETH_FrameRX  frameRX __RAM_EXEC_ALIGN4;
uint32_t         framesCountRX;
uint32_t         sentFrameIndex;

typedef enum {
  cmdReadMAC = 0,
  cmdWriteMAC,
  cmdReadPHY,
  cmdWritePHY,
  cmdReadInfo,
  cmdReadFrame,
  //  Count
  cmdCOUNT
} CMD_e;

uint8_t _cmdLen[cmdCOUNT] = {3, 5, 3, 5, 1, 1};
uint8_t activeCmdLen;

#define TIM_CNT   20
uint32_t timInd = 0;
uint32_t timIn[TIM_CNT];
uint32_t timOut[TIM_CNT];

uint32_t timWork[TIM_CNT];
uint32_t timPass[TIM_CNT];
uint32_t timWorkAver;
uint32_t timPassAver;

#define DEBOUNCE_MS   10
#define FRAME_LEN_TX  100
MDR_ETH_FrameTX frameTX  __RAM_EXEC_ALIGN4;
uint8_t MAC_A[6] __RAM_ALIGN4 = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66};
uint8_t MAC_B[6] __RAM_ALIGN4 = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC};

int main(void)
{
  //  Максимальная скорость тактирования
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDRB_CLK_PLL_HSE_RES_MAX;
  MDR_CPU_SetClock_PLL_HSE(&cfgPLL_HSE, true);
  uint32_t freqCPU_Hz = MDR_CPU_GetFreqHz(true); 
  
  // Прием команд в прерывании по RT
  MDR_UART_DBG_InitIrqRT(UART_BAUD_115200, true);  
  
  MDRB_LED_Init(MDRB_LED_1);
  MDRB_Buttons_Init(DEBOUNCE_MS, freqCPU_Hz);

  //  НАСТРОЙКА ETHERNET
  MDR_Eth_SetClockHSE2();
  //    Internal PHY, HSE2 8MHz * 16 = 128MHz  
  MDR_ETH_MAC_CfgRegs  cfgRegs = MDR_ETH_MAC_INIT_DEF(128, MDC_DIV_le160MHz);   
  MDR_ETH_InitCfg      initCfg = {
    .cfgRegsMAC = &cfgRegs,
    .phyCfgReg  = MDR_REG_PHY_CTRL
  };  
  MDR_Eth_Init(MDR_ETH1, &initCfg);
  MDR_Eth_Start(MDR_ETH1);
  
  MDR_ETH_Debug_FillTestFrameTX(&frameTX, FRAME_LEN_TX, MAC_A, MAC_B);  
  
  while(1)
  {
    if (uartDoProcessCmd)
    {      
      switch (uartMess.dataRx[0]){
        case cmdReadMAC:   ReadRegMAC();  break;
        case cmdWriteMAC:  WriteRegMAC(); break;
        case cmdReadPHY:   ReadRegPHY();  break;
        case cmdWritePHY:  WriteRegPHY(); break;
        case cmdReadInfo:  ReadInfo();    break;
        case cmdReadFrame: ReadFrameRx(); break;          
      }
           
      //  For Next CMD
      uartCmdLen = 0;
      uartDoProcessCmd = false;      
    }
    
    //  Прием по Ethernet
    if (MDR_ETH_TryReadFrameF(MDR_ETH1, &frameRX))
      framesCountRX++;    

    //  Передача фрейма по кнопке UP
    if (MDRB_BntClicked_Up(false))
      MDR_ETH_TrySendFrame(MDR_ETH1, &frameTX);
    
    CheckLinkRoutine();    
  }
}

void UART1_IRQHandler(void)
{
	MDR_UART_EventFlags eventFlags = MDR_UART_GetEvents(UART_DBG->UARTx);
  if (eventFlags.Flags.RT == MDR_On)
	{
		while (MDR_UART_CanRead(UART_DBG->UARTx))
    {
      uint8_t data = MDR_UART_ReadData(UART_DBG->UARTx) & 0xFF;      
      if (!uartDoProcessCmd)
      {        
        if (uartCmdLen == 0) 
        {
          if (data < cmdCOUNT)
            activeCmdLen = _cmdLen[data];
          else
            printf("Wrong CMD: %d!", data);
        }
        
        if (uartCmdLen < UART_CMD_LEN)
          uartMess.dataRx[uartCmdLen++] = data;
        else
          uartCmdLenErrCount++;
      }
      
      if (uartCmdLen == activeCmdLen)
        uartDoProcessCmd = true;
//      else
//        MDR_UART_SendData(UART_DBG->UARTx, data);
    }
		
		MDR_UART_ClearEventsIRQ(UART_DBG->UARTx, MDR_UART_EFL_RT | MDR_UART_EFL_RX);
	}	
	else
	{
		uartUndefIrqErrCount++;		
	}
}

static void ReadRegMAC(void)
{
  uint32_t addr = (*(UART_CmdAligned_Buff *)&uartMess).addr;
  addr += ADDR_ETH1_BASE;
  uint16_t data = REG16(addr);
  printf("(0x%x): 0x%x\n", addr, data);
}

static void WriteRegMAC(void)
{
  uint32_t addr = (*(UART_CmdAligned_Buff *)&uartMess).addr;
  uint16_t data = (*(UART_CmdAligned_Buff *)&uartMess).data;
  addr += ADDR_ETH1_BASE;
  REG16(addr) = data;
  printf("(0x%x) = 0x%x\n", addr, data);  
}

static void ReadRegPHY(void)
{
  uint16_t addr = (*(UART_CmdAligned_Buff *)&uartMess).addr;
  uint16_t data;
  if (MDR_ETH_ReadMDIO(MDR_ETH1, ETHCFG1_PHY_ADDR, addr, &data))
    printf("(0x%x): 0x%x\n", addr, data);  
  else
    printf("MDIO read 0x%x faults\n", addr);  
}

static void WriteRegPHY(void)
{
  uint16_t addr = (*(UART_CmdAligned_Buff *)&uartMess).addr;
  uint16_t data = (*(UART_CmdAligned_Buff *)&uartMess).data;
  if (MDR_ETH_WriteMDIO(MDR_ETH1, ETHCFG1_PHY_ADDR, addr, data))
    printf("(0x%x) = 0x%x\n", addr, data);  
  else
    printf("MDIO write 0x%x to (0x%x) faults\n", data, addr);  
}

static void ReadFrameRx(void)
{
  uint16_t len = frameRX.statusRX.Fields.Length;
  uint16_t i;
  printf("FrameStatus: 0x%x\n", frameRX.statusRX.Status);
  printf("FrameData: \n");
  for (i = 0; i < len; i++)  
    printf("0x%02x ", frameRX.frame[i]);
  printf("\nBytesCount: %d\n", len);
}

static void ReadInfo(void)
{
  printf("Frames Received: %d\n", framesCountRX);
  printf("Last FrameRX Status: 0x%x\n", frameRX.statusRX.Status);
  printf("Last PHY Status: 0x%x\n", _lastPhyStatus);
}

static void CheckLinkRoutine(void)
{
  uint16_t value = MDR_ETH1->PHY_STATUS;
  if (_lastPhyStatus != value)
  {
    uint16_t changedBits = _lastPhyStatus ^ value;
    if (changedBits & MDR_ETH_PHY_STATUS_LED1_Msk)
    {
      if (value & MDR_ETH_PHY_STATUS_LED1_Msk)
      {
        MDRB_LED_Set(MDRB_LED_1, 0);
        printf("LINK_DOWN\n");
      }
      else
      {
        MDRB_LED_Set(MDRB_LED_1, 1);
        printf("LINK_UP\n");
      }
    }
    
    _lastPhyStatus = value;
  }
}


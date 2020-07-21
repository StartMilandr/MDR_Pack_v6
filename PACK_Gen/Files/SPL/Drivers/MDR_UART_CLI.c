#include <MDR_UART_CLI.h>
#include <MDR_UART.h>
#include <MDR_DMA.h>


#define _CLI_UART     CFG_CLI_UARTex->UARTx
// Буфер с запасом под OddTail
#define DMA_BUFF_LEN  CFG_CLI_MESS_LEN_MAX + 1

// countLo, cmd_cntHi - служебные байты: команда/кол. байт в посылке
// buff - параметры к команде. Для удобства работы с 32-разрядными значениями, 
//        надо чтобы buff начинался с выровненного адреса. 
//        (CortexM1 не поддерживает невыровненные операции с памятью
//         CortexM3 делает доступ за несколько циклов выровненный транзакций)
typedef __PACKED_STRUCT {
  uint16_t  _alignOffset;
  uint8_t   countLo;
  uint8_t   cmd_cntHi;
  uint8_t   buff[DMA_BUFF_LEN];  // Aligned by 4!
} CLI_AlignedBuff;

#ifdef DMA_NEED_EXECUTABLE_MEM_RANGE
  static CLI_AlignedBuff  _inpAlignedBuff  __RAM_EXEC __attribute__ ((aligned (4)));
  static CLI_AlignedBuff  _outAlignedBuff  __RAM_EXEC __attribute__ ((aligned (4)));
#else
  static CLI_AlignedBuff  _inpAlignedBuff  __attribute__ ((aligned (4)));
  static CLI_AlignedBuff  _outAlignedBuff  __attribute__ ((aligned (4)));
#endif

static uint8_t         *_inpData = &_inpAlignedBuff.countLo;
static uint16_t         _inpDataLen = 0;

static uint16_t   _messLen = 0;

static uint8_t         *_outData = &_outAlignedBuff.countLo;
static uint16_t         _outDataLen = 0;

static CLI_CMD_e  _cmdID;

static MDR_DMA_ChCtrl RestartCtrl_TX;
static MDR_DMA_ChCtrl RestartCtrl_RX;


static void CLI_DMA_Init(void);
static bool CLI_GetDataReceived(void);



void MDR_CLI_UART_Init(uint32_t baudRate, uint32_t UART_ClockHz, MDR_UART_CfgPinsGPIO *pinsGPIO)
{	  
  //  Init UART PIN
	MDR_UART_InitPinsGPIO(pinsGPIO, MDR_PIN_FAST);  
  
	//	Подача на UARTx_Clock частоты ядра или MAX_Clock.
  MDR_UARTex_SetUartClock_InpPLLCPU(CFG_CLI_UARTex, MDR_Div128P_div1);  
	
	//	Рассчет делителей под частоту обмена (из UART_ClockHz под baudRate)
  MDR_UART_cfgBaud cfgBaud;	
	MDR_UART_CalcBaudRate(&cfgBaud, baudRate, UART_ClockHz);
		 
	//	Параметры UART
  MDR_UART_CfgIRQ cfgFIFO = {
    .SelEventIRQ   = MDR_UART_EFL_RT,
    .Rx_FIFO_Event = UART_FIFO_2,
    .Tx_FIFO_Event = UART_FIFO_2
  };  
  
	MDR_UART_Cfg cfgUART = {
		.cfgBase.WordLength    = MDR_UART_WordLen8,
		.cfgBase.Parity        = UART_Parity_Off,
		.cfgBase.useFIFO       = MDR_On,
		.cfgBase.Options.Value = 0, //  Some Options, инициализировать нулем если опции не нужны
    .pCfgIRQ = &cfgFIFO,        //  Настройка IRQ		
		.pCfgDMA = NULL,            //  DMA Disabled
		.pCfgIrDA = NULL,           //  IrDA Disabled
		.pCfgModem = NULL           //  Modem Disabled
	};  
  
	MDR_UARTex_InitByBaud(CFG_CLI_UARTex, &cfgUART, &cfgBaud);	  
  //  Clear FIFO and RX Event
  MDR_UART_ClearRxFIFO(_CLI_UART);
  MDR_UART_ClearEventsIRQ(_CLI_UART, MDR_UART_EFL_ALL);
  
  //  Init DMA
  CLI_DMA_Init();
  
  //  UART Enable DMA call
  MDR_UART_TX_DMA_Enable(_CLI_UART);  
  MDR_UART_RX_DMA_Enable(_CLI_UART);
}

static void CLI_DMA_Init(void) 
{
  MDR_DMA_CfgTransf  cfgDMA_TX = { 
    .CfgFileds.Mode         = DMA_MODE_Base,
    .CfgFileds.UseBurst     = MDR_Off,
    .CfgFileds.ArbitrCount  = DMA_Arbitr_2, //DMA_Arbitr_1024,  
    .CfgFileds.DataSize     = MDR_DMA_Data8,
    .CfgFileds.Src_AddrInc  = MDR_DMA_AddrInc8,
    .CfgFileds.Dest_AddrInc = MDR_DMA_AddrIncOff,
    .Src_ProtAHB  = NULL,
    .Dest_ProtAHB = NULL,
  };

  MDR_DMA_CfgTransf  cfgDMA_RX = { 
    .CfgFileds.Mode         = DMA_MODE_Base,
    .CfgFileds.UseBurst     = MDR_Off,
    .CfgFileds.ArbitrCount  = DMA_Arbitr_2, //DMA_Arbitr_1024,  
    .CfgFileds.DataSize     = MDR_DMA_Data8,
    .CfgFileds.Src_AddrInc  = MDR_DMA_AddrIncOff,
    .CfgFileds.Dest_AddrInc = MDR_DMA_AddrInc8,
    .Src_ProtAHB  = NULL,
    .Dest_ProtAHB = NULL,
  };
  
  //  DMA
  MDR_DMA_Init();
  //  TX
  RestartCtrl_TX = MDR_DMA_InitTransfPri(CFG_CLI_DMA_ChanTX, (uint32_t)_outData, (uint32_t)&(_CLI_UART)->DR, CFG_CLI_MESS_LEN_MAX * 2, &cfgDMA_TX); 
  MDR_DMA_StartChannel(CFG_CLI_DMA_ChanTX, false, false, true);
  MDR_DMA_StopChannel(CFG_CLI_DMA_ChanTX);
  //  RX
  RestartCtrl_RX = MDR_DMA_InitTransfPri(CFG_CLI_DMA_ChanRX, (uint32_t)&(_CLI_UART)->DR, (uint32_t)_inpData, CFG_CLI_MESS_LEN_MAX * 2, &cfgDMA_RX);  
  MDR_DMA_StartChannel(CFG_CLI_DMA_ChanRX, true, false, true);
}

//void MDR_CLI_UART_IRQHandler(void)
//{
//  _doProcessInpData = true;
//  MDR_UART_ClearEventsIRQ(_CLI_UART, MDR_UART_EFL_RT);
//  MDR_DMA_StopChannel(CFG_CLI_DMA_ChanRX);
//}

//  CMD - [0..63], LEN - [0..1023]
//  _inpData[0] - LenLo
//  _inpData[1] - LenHi[6..7], Cmd[0..5]
#define CLI_CMD_OFFS    0
#define CLI_CMD_MSK     0x3F
//#define CLI_LEN_OFFS    6
//#define CLI_LEN_HI_MSK     0xFFC0

#define MESS_MIN_LEN    3
#define MESS_GET_CMD    (_inpData[1] & CLI_CMD_MSK)
#define MESS_GET_LEN   ( (uint16_t)_inpData[0] | ((uint16_t)(_inpData[1] & 0xC0) << 2) )

#define MESS_SET_HEADER(arr, cmd, len)    arr[1] = (uint8_t)(((uint16_t)(len) >> 2) & 0x00C0) | (uint8_t)(cmd); \
                                          arr[0] = (uint8_t)(len);

#define MESS_HEADER_LEN   2    
#define MESS_IND_CMD      1    
#define MESS_IND_DATA     2    



//static inline uint16_t GetLength(void)
//{
//  uint16_t *pBuff16 = (uint16_t *)_inpData;
//  return pBuff16[0] & CLI_LEN_MSK >> CLI_LEN_OFFS;
//}

static bool CLI_GetDataReceived(void)
{
  // Наличие флага TimeoutRx говорит о том, что оно слово еще лежит в FIFO
  // Потому что DMA выяитывает блоками по 2 слова
  bool hasNewData = _CLI_UART->RIS & MDR_UART_EFL_RT;
  //MDR_DMA_ChCtrl ctrl = MDR_DMA_GetChCtrlPri(CFG_CLI_DMA_ChanRX);
  if (hasNewData)    
  {
    MDR_UART_ClearEventsIRQ(_CLI_UART, MDR_UART_EFL_RT);
    //MDR_UART_ClearEventsIRQ(_CLI_UART, MDR_UART_EFL_ALL);

    // Проверяем, что пришло байт не меньше 3-х (Два скачало DMA, одно еще в FIFO)
    // Если меньше - выходим, ждем следующий приход данных
    MDR_DMA_ChCtrl ctrl = MDR_DMA_GetChCtrlPri(CFG_CLI_DMA_ChanRX);
    _inpDataLen = RestartCtrl_RX.Fields.N_minus1 - ctrl.Fields.N_minus1;
    if (_inpDataLen < (MESS_MIN_LEN - 1))
      return false;
    // Достаем длину посылки из первых 2-х байт, проверяем что пришли все байты, включая один в FIFO
    // Если не все - выходим до следующего таймаута
    _messLen = MESS_GET_LEN;
    if (_inpDataLen < (_messLen - 1))
      return false;
    
    // Даем DMA вычитать последний байт из UART_FIFO_RX
    MDR_DMA_EnableSREQ(CFG_CLI_DMA_ChanRX);
    while (MDR_UART_CanRead(_CLI_UART));
    MDR_DMA_DisableSREQ(CFG_CLI_DMA_ChanRX);       
    // Останавливаем DMA, (позже будем переинициализировать под новый цикл обмена)
    MDR_DMA_StopChannel(CFG_CLI_DMA_ChanRX);
    
    // Вычитываем последнее слово из FIFO
    // _inpDataLen - общее количество пришедших байт
    ctrl = MDR_DMA_GetChCtrlPri(CFG_CLI_DMA_ChanRX);
    _inpDataLen = RestartCtrl_RX.Fields.N_minus1 - ctrl.Fields.N_minus1;
  }
   
  return hasNewData;
}


CLI_CMD_e MDR_CLI_GetCommand(uint16_t *lenCmdParams, uint8_t **pCmdParams)
{
  if (CLI_GetDataReceived())
  {   
    bool messOK;
    if ((_messLen & 1) == 0)
      messOK = _inpDataLen == (_messLen + 1);
    else
      messOK = _inpDataLen == _messLen;
    
    uint8_t cmd;
    if (messOK)
    {
      cmd = MESS_GET_CMD;
      messOK = (cmd < cliCMD_LEN);
    }  
    
    if (messOK)
    { 
      _cmdID = (CLI_CMD_e)cmd;
      *lenCmdParams = _messLen - MESS_HEADER_LEN;
      *pCmdParams = &_inpData[MESS_HEADER_LEN];      
    }
    else
    {
      _cmdID = cliCMD_ERROR;
      *lenCmdParams = _inpDataLen;
      *pCmdParams = _inpData;      
    }
  }
  return _cmdID;
}

uint16_t MDR_CLI_GetResponceBuf(uint8_t **pAckBuf)
{
  *pAckBuf = &_outData[MESS_HEADER_LEN];
  return DMA_BUFF_LEN - MESS_HEADER_LEN;
}

void MDR_CLI_SetResponse(CLI_CMD_e cmd, uint16_t lenAckParams)
{ 
  //  Посылка ответа
  _cmdID = cliCMD_NONE;  
  if (cmd != cliCMD_ERROR)
  { 
    _outDataLen = lenAckParams + MESS_HEADER_LEN;
    MESS_SET_HEADER(_outData, cmd, _outDataLen);
    if ((_outDataLen & 1) == 0)
      _outDataLen++;    
    MDR_DMA_RunNextBuff8_Pri(CFG_CLI_DMA_ChanTX, RestartCtrl_TX, _outData, _outDataLen);
  }
  else
  {
    MDR_DMA_RunNextBuff8_Pri(CFG_CLI_DMA_ChanTX, RestartCtrl_TX, _inpData, _inpDataLen);
  }

  //  Инициализируем DMA для приема следующей команды
  MDR_DMA_InitNextCyclePri(CFG_CLI_DMA_ChanRX, RestartCtrl_RX);
  MDR_DMA_ReStartChannel(CFG_CLI_DMA_ChanRX);  
    
  //  Инициализируем DMA для посылки ответа
//  MDR_DMA_RunNextBuff8_Pri(CFG_CLI_DMA_ChanTX, RestartCtrl_TX, _outData, _outDataLen);
  
//  RestartCtrl_TX.Fields.N_minus1 = _outDataLen - 1;
//  MDR_DMA_InitNextCyclePri(CFG_CLI_DMA_ChanTX, RestartCtrl_TX);  
//  MDR_DMA_ReStartChannel(CFG_CLI_DMA_ChanTX);
  
//  MDR_Delay(100000);
//  volatile MDR_DMA_ChCfg chCtrl = MDR_DMA_CtrlTablePri(CFG_CLI_DMA_ChanTX);
//  volatile MDR_DMA_ChCtrl ctrl1 = MDR_DMA_GetChCtrlPri(CFG_CLI_DMA_ChanTX);  
}




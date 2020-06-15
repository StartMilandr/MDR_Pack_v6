#include <MDR_UART_CLI.h>
#include <MDR_UART.h>
#include <MDR_DMA.h>


#define _CLI_UART     CFG_CLI_UARTex->UARTx

static uint32_t   _inpData[CFG_CLI_MESS_LEN_MAX * 2] __RAM_EXEC;
static uint32_t   _inpDataLen;
static uint32_t   _outData[CFG_CLI_MESS_LEN_MAX * 2] __RAM_EXEC;
static uint32_t   _outDataLen;

static CLI_CMD_e _cmdID;
static uint8_t   _cmdData[CFG_CLI_MESS_LEN_MAX];
static uint8_t   _cmdDataLen;

static MDR_DMA_ChCtrl RestartCtrl_TX;
static MDR_DMA_ChCtrl RestartCtrl_RX;


static void CLI_DMA_Init(void);
static bool CLI_GetDataReceived(void);



void MDR_CLI_UART_Init(uint32_t baudRate, uint32_t UART_ClockHz, MDR_UART_CfgPinsGPIO *pinsGPIO)
{	
	//	Подача на UARTx_Clock частоты ядра или MAX_Clock.
  MDR_UARTex_SetUartClock_InpPLLCPU(CFG_CLI_UARTex, MDR_Div128P_div1);  
	
	//	Рассчет делителей под частоту обмена (из UART_ClockHz под baudRate)
  MDR_UART_cfgBaud cfgBaud;	
	MDR_UART_CalcBaudRate(&cfgBaud, baudRate, UART_ClockHz);
		 
	//	Параметры UART
	MDR_UART_Cfg cfgUART = {
		.cfgBase.WordLength    = MDR_UART_WordLen8,
		.cfgBase.Parity        = UART_Parity_Off,
		.cfgBase.useFIFO       = MDR_On,
		.cfgBase.Options.Value = 0, //  Some Options, инициализировать нулем если опции не нужны
    .pCfgIRQ = NULL,            //  Настройка IRQ		
		.pCfgDMA = NULL,            //  DMA Disabled
		.pCfgIrDA = NULL,           //  IrDA Disabled
		.pCfgModem = NULL           //  Modem Disabled
	};
	
	MDR_UARTex_InitByBaud(CFG_CLI_UARTex, &cfgUART, &cfgBaud);	  
  
  //  Init UART PIN
	MDR_UART_InitPinsGPIO(pinsGPIO, MDR_PIN_FAST);    
  
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
    .CfgFileds.ArbitrCount  = DMA_Arbitr_1024,  
    .CfgFileds.DataSize     = MDR_DMA_Data8,
    .CfgFileds.Src_AddrInc  = MDR_DMA_AddrInc8,
    .CfgFileds.Dest_AddrInc = MDR_DMA_AddrIncOff,
    .Src_ProtAHB  = NULL,
    .Dest_ProtAHB = NULL,
  };

  MDR_DMA_CfgTransf  cfgDMA_RX = { 
    .CfgFileds.Mode         = DMA_MODE_Base,
    .CfgFileds.UseBurst     = MDR_Off,
    .CfgFileds.ArbitrCount  = DMA_Arbitr_1024,  
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
  MDR_DMA_StartChannel(CFG_CLI_DMA_ChanRX, false, false, true);
}

//void MDR_CLI_UART_IRQHandler(void)
//{
//  _doProcessInpData = true;
//  MDR_UART_ClearEventsIRQ(_CLI_UART, MDR_UART_EFL_RT);
//  MDR_DMA_StopChannel(CFG_CLI_DMA_ChanRX);
//}

static bool CLI_GetDataReceived(void)
{
  bool hasNewData = _CLI_UART->RIS & MDR_UART_EFL_RT;
  if (hasNewData)    
  {
    MDR_UART_ClearEventsIRQ(_CLI_UART, MDR_UART_EFL_RT);

#if CFG_CLI_PROC_BY_END_CODES
    MDR_DMA_ChCtrl ctrl = MDR_DMA_GetChCtrlPri(CFG_CLI_DMA_ChanRX);
    uint32_t cntRX = RestartCtrl_RX.Fields.N_minus1 - ctrl.Fields.N_minus1;
    if (cntRX > 4)
      if ((_inpData[cntRX - 2] == CFG_CLI_PROC_END_CODE1) && (_inpData[cntRX - 1] == CFG_CLI_PROC_END_CODE2))
      {
        // Stop DMA_RX
        MDR_DMA_StopChannel(CFG_CLI_DMA_ChanRX);
        _inpDataLen = cntRX;
      }      
#else      
    // Stop DMA_RX
    MDR_DMA_StopChannel(CFG_CLI_DMA_ChanRX);
    MDR_DMA_ChCtrl ctrl = MDR_DMA_GetChCtrlPri(CFG_CLI_DMA_ChanRX);
    _inpDataLen = RestartCtrl_RX.Fields.N_minus1 - ctrl.Fields.N_minus1;
#endif    
  }
  
  return hasNewData;
}

CLI_CMD_e MDR_CLI_GetCommand(uint8_t *lenAckParams, uint8_t **pCmdParams)
{
  if (CLI_GetDataReceived())
  {
    // Данные передаются парами - "слово"/"инверсия слова" для проверки отсутствия ошибок        
    // Если данные вне этого протокола, то просто возвращаем их "сырыми"
    _cmdID = cliCMD_ERROR;
    _cmdDataLen = _inpDataLen;
    // Прореживаем данные если они по инферсному протоколу
    if (_inpDataLen > 2)
      if (_inpData[0] == ~_inpData[1])
        if (_inpData[0] < cliCMD_LEN)
        {
          _cmdID = (CLI_CMD_e)_inpData[0];
          
          uint32_t i;
          _cmdDataLen = 0;
          for (i = 2; i < (_inpDataLen - 2); i += 2)
          {
            if (_inpData[i] == ~_inpData[i+1])
              _cmdData[_cmdDataLen++] = _inpData[i];
            else
              break;  //  неправильное количество данных к команде покажет что была ошибка
          }
        }
  }
  
  *lenAckParams = _cmdDataLen;
  *pCmdParams = _cmdData;
  return _cmdID;
}

void MDR_CLI_SetResponse(CLI_CMD_e cmd, uint8_t lenAckParams, uint8_t *pAckParams)
{
  _outData[0] = (uint8_t)cmd;
  _outData[1] = ~_outData[0];
  
  uint32_t i;
  _outDataLen = 2;
  for (i = 0; i < lenAckParams; i++)  
  {
    _outData[_outDataLen++] = pAckParams[i];
    _outData[_outDataLen++] = ~pAckParams[i];
  }

  //  Инициализируем DMA для приема следующей команды
  MDR_DMA_InitNextCyclePri(CFG_CLI_DMA_ChanRX, RestartCtrl_RX);
  MDR_DMA_ReStartChannel(CFG_CLI_DMA_ChanRX);  
  
  //  Инициализируем DMA для посылки ответа
  RestartCtrl_TX.Fields.N_minus1 = _outDataLen - 1;
  MDR_DMA_InitNextCyclePri(CFG_CLI_DMA_ChanTX, RestartCtrl_TX);  
  MDR_DMA_ReStartChannel(CFG_CLI_DMA_ChanTX);
}




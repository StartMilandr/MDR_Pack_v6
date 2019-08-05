#include <MDR_RST_Clock.h>
#include <MDR_UART.h>
#include <MDR_PER_Clock.h>
#include <MDRB_LEDs.h>

#include "Commands.h"
#include <stdio.h>
#include <MDR_Config.h>


#define USE_UART1

#ifdef USE_UART1
	#define UARTx_Ex 	MDR_UART1ex
	#define UARTx 	  MDR_UART1ex->UARTx
	
  #ifdef USE_BOARD_VE8
		static const MDR_UART_CfgPinGPIO _pinTX_UART = {MDRB_UART1_TX_PE15_Port, MDRB_UART1_TX_PE15_Ind, MDRB_UART1_TX_PE15_Func};
		static const MDR_UART_CfgPinGPIO _pinRX_UART = {MDRB_UART1_RX_PE16_Port, MDRB_UART1_RX_PE16_Ind, MDRB_UART1_RX_PE16_Func};
	#elif defined(USE_BOARD_ESila)
	  static const MDR_UART_CfgPinGPIO _pinTX_UART = {MDRB_UART1_TX_PB1_Port, MDRB_UART1_TX_PB1_Ind, MDRB_UART1_TX_PB1_Func};
		static const MDR_UART_CfgPinGPIO _pinRX_UART = {MDRB_UART1_RX_PB0_Port, MDRB_UART1_RX_PB0_Ind, MDRB_UART1_RX_PB0_Func};  	
	#endif
		
#endif
	
//	В прерывании по уровню FIFO_RX вычитывать на 1 слово меньше, чтобы работало прерывание по таймауту
#define UART_FIFO_LEVEL  UART_FIFO_8
#define UART_RX_COUNT		 7		
		

void UartInit(uint32_t baudRate, uint32_t UART_ClockHz);
void UartInitPins(void);

int main(void)
{ 
	uint32_t freqCPU_Hz;
	
	//	Вместо максимальной, можно выставить желаемую частоту:
	//  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDR_CLK_PLL_HSE_RES_DEF(MDRB_PLL_8MHz_TO_80MHz, MDRB_CPU_FREQ_SUPP_80MHz);
	
  //  Максимальная скорость тактирования
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDRB_CLK_PLL_HSE_RES_MAX;	
  MDR_CPU_SetClock_PLL_HSE(&cfgPLL_HSE, true);	
	freqCPU_Hz = MDR_CPU_GetFreqHz(true);	
	
	//	Инициализаия светодиодов
	MDRB_LED_InitALL();
	
	//	Мигание для индикации запуска программы
	MDRB_LED_Set(MDRB_LED_PinAll, 1);
	MDR_Delay_ms(1000, freqCPU_Hz);
	MDRB_LED_Set(MDRB_LED_PinAll, 0);
	
	
	//	MaxClock to UART_Clock
	UartInit(UART_BAUD_115200, freqCPU_Hz);
	UartInitPins();
	
	//	Command description
	printf("Available commands:\n");
	printf(" - LedToggle: 0, LedSel\n");
	printf(" - LedSyclicToggleOn: 1, LedSel\n");
	printf(" - LedSyclicToggleOff: 2, LedSel\n");
	printf(">\n");
	
	volatile bool deReedout = false;
	
	while (1)
	{		
	  if (COMM_CheckDoExecCommand())
		{
		  if (COMM_ExecCommand())
				printf("Ok\n");
			else
				printf("Wrong Command\n");
			printf(">\n");
		}
	}
}

//===========		UART ===============
void UartInit(uint32_t baudRate, uint32_t UART_ClockHz)
{	
	//	Включение MAX_Clock на UART_Clock 
#ifdef USE_UART1	
	MDR_SetClock_Uart1(MDR_RST_ASYNC_IN_MAX_CLK);
#endif
	
	//	Рассчет делителей под частоту обмена (из UART_ClockHz под baudRate)
  MDR_UART_cfgBaud cfgBaud;	
	MDR_UART_CalcBaudRate(&cfgBaud, baudRate, UART_ClockHz);
		
	//	Прерывание по наличию 4 слов в FIFO_RX и по таймауту приема
	//   - Прием - просто вычитываем данные в приемный буфер, оставляя одно слово, чтобы срабатывал таймаут.
	//   - Таймаут - окончание потока данных, вычитываем остаток и обрабатываем данные
	MDR_UART_CfgIRQ   CfgIRQ = {
		.SelEventIRQ.Value = MDR_UART_EFL_RT | MDR_UART_EFL_RX,
		.Rx_FIFO_Event = UART_FIFO_LEVEL,
		.Tx_FIFO_Event = UART_FIFO_LEVEL
	};			
	//	Параметры UART
	MDR_UART_Cfg cfgUART = {
		//  Main Settings
		.cfgBase.WordLength    = MDR_UART_WordLen8,
		.cfgBase.Parity        = UART_Parity_Off,
		.cfgBase.useFIFO       = MDR_On,
		//  Some Options, инициализировать нулем если опции не нужны
		.cfgBase.Options.Value = 0,  
		//  Настройка IRQ
		.pCfgIRQ = &CfgIRQ,
		//  DMA Disabled
		.pCfgDMA = NULL,
		//  IrDA Disabled
		.pCfgIrDA = NULL,
		//  Modem Disabled
		.pCfgModem  = NULL
	};	
	//	Все настройки в одну структуру.
	MDR_UART_CfgEx cfgUartEx = {
		//  Делитель частоты для Uart_Clock
		.ClockBRG = MDR_Div128P_div1,
		//  Настройки блока
		.pCfgUART = &cfgUART,  
		//  Инициализация прерываний в NVIC
		.priorityIRQ = 0,
		.activateNVIC_IRQ = true
	};	
	
	MDR_UARTex_InitByBaud(UARTx_Ex, &cfgUartEx, &cfgBaud);	
}

void UartInitPins(void)
{
	MDR_UART_CfgPinsGPIO pinsGPIO = {
		.pPinTX = &_pinTX_UART,
    .pPinRX = &_pinRX_UART,	
	};
	
	MDR_UART_InitPinsGPIO(&pinsGPIO, MDR_PIN_FAST);
}

void UART1_IRQHandler(void)
{
	MDR_UART_EventFlags eventFlags = MDR_UART_GetEvents(UARTx);
  if (eventFlags.Flags.RT == MDR_On)
	{
		//  Вычитывание всех данных
		while (MDR_UART_CanRead(UARTx))
			COMM_AddData((uint8_t)(MDR_UART_ReadData(UARTx) & 0xFF));
		//  Выставление флага на обработку данных
		COMM_DataThreadCompleted();
		
		MDR_UART_ClearEventsIRQ(UARTx, MDR_UART_EFL_RT | MDR_UART_EFL_RX);
	}	
	else if (eventFlags.Flags.RX == MDR_On)
	{
		//  Вычитывание всех данных кроме одного, чтобы FIFO не был пуст.
		//  Иначе не будет прерывания по таймауту
		uint32_t i;
		for (i = 0; i < UART_RX_COUNT; ++i)
		{
		  if (MDR_UART_CanRead(UARTx)) 
				COMM_AddData((uint8_t)(MDR_UART_ReadData(UARTx) & 0xFF));
			else
			{
				printf("FIFO_RX wrong level!");
				break;
			}
		}
		
		MDR_UART_ClearEventsIRQ(UARTx, MDR_UART_EFL_RX);
	}
}


//===========		PRINTF ===============
#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION < 6010050)
struct __FILE
{
  int handle;
  /* Whatever you require here. If the only file you are using is */
  /* standard output using printf() for debugging, no file handling */
  /* is required. */
};
#endif

/* FILE is typedef’d in stdio.h. */
FILE __stdout;

int fputc(int ch, FILE *f)
{ 
  UNUSED(f);
  
  while(!MDR_UART_CanSend(UARTx));
  MDR_UART_SendData(UARTx, (uint8_t)ch);
  
  return ch;
}

int ferror(FILE *f)
{
  UNUSED(f);
  
  /* Your implementation of ferror(). */
  return 0;
}

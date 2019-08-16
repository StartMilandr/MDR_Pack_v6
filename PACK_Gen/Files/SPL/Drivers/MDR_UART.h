#ifndef MDR_UART_H
#define MDR_UART_H

#include <MDR_Config.h>
#include <MDR_RST_Clock.h>
#include <MDR_PER_Clock.h>
#include <MDR_GPIO.h>
#include <MDR_UART_defs.h>
#include <MDR_UART_CfgRegs.h>

//  Подавление warnings компилятора V6 о добавлении  "пустот" в структуры
#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wpadded"
#endif


//  ----------------    Some Standards BaudRates   -------------------------
#define UART_BAUD_9600        9600
#define UART_BAUD_19200      19200
#define UART_BAUD_38400      38400 
#define UART_BAUD_57600      57600 
#define UART_BAUD_115200    115200 
#define UART_BAUD_230400    230400 
#define UART_BAUD_460800    460800 
#define UART_BAUD_921600    921600

//  ----------------    EventFlags   -------------------------
typedef union {
  uint32_t            Value;
  MDR_UART_EventBits  Flags;
} MDR_UART_EventFlags;


//  ----------------    Base Options   -------------------------
typedef enum {
  UART_Parity_Off,
  UART_Parity_Odd,
  UART_Parity_Even,
  UART_Parity_1,
  UART_Parity_0
} MDR_UART_Parity;

typedef struct {
  uint16_t            BaudDivInt;
  uint16_t            BaudDivFrac;
} MDR_UART_cfgBaud;

typedef struct { 
  MDR_OnOff sendBreak   : 1;
  MDR_OnOff TX_Disable  : 1;    //  Передатчик остается выключенным при вызове Init
  MDR_OnOff RX_Disable  : 1;    //  Приемник остается выключенным при вызове Init    
  MDR_OnOff use2StopBit : 1;
  MDR_OnOff useLBM      : 1;
  uint32_t  reserved    : 27;
} MDR_UART_OptionFlags;

#define MDR_UART_OPT_Break      MDR_UART_LCR_H_BRK_Msk
#define MDR_UART_OPT_DisTX      0x02UL
#define MDR_UART_OPT_DisRX      0x04UL
#define MDR_UART_OPT_STOP2      MDR_UART_LCR_H_STP2_Msk
#define MDR_UART_OPT_LBM        0x10UL


#define UART_SEL_BKR_STOP2      (MDR_UART_OPT_Break | MDR_UART_OPT_STOP2)

typedef union {
  uint32_t              Value;
  MDR_UART_OptionFlags  Flags_b;
} MDR_UART_CfgOptions;

//  Основные настройки (минимальные)
typedef enum {
  MDR_UART_WordLen5 = 0,
  MDR_UART_WordLen6 = 1,
  MDR_UART_WordLen7 = 2,
  MDR_UART_WordLen8 = 3,
#ifdef MDR_UART_HAS_LEN9  
  MDR_UART_WordLen9 = 4
#endif  
} MDR_UART_WordLen;


typedef struct {  
  //  Main Settings
  MDR_UART_WordLen    WordLength;
  MDR_UART_Parity     Parity;
  MDR_OnOff           useFIFO;
    
  //  Some Options, инициализировать нулем если опции не нужны
  MDR_UART_CfgOptions Options;
} MDR_UART_CfgBase;


//  Events for IRQ
typedef struct {
  MDR_UART_EventFlags SelEventIRQ;
  MDR_UART_EventFIFO  Rx_FIFO_Event;
  MDR_UART_EventFIFO  Tx_FIFO_Event;
} MDR_UART_CfgIRQ;

//  ----------------    Modem Option   -------------------------
typedef struct { 
  MDR_OnOff setDTR_Low  : 1;
  MDR_OnOff setRTS_Low  : 1;
  MDR_OnOff setOut1_Low : 1;
  MDR_OnOff setOut2_Low : 1;
  MDR_OnOff RTSEn       : 1;
  MDR_OnOff CTSEn       : 1;
  uint32_t  reserved    : 26;
} MDR_UART_ModemFlags;

#define MDR_UART_MFL_RIM         0x01UL
#define MDR_UART_MFL_STCM        0x02UL
#define MDR_UART_MFL_DCDM        0x04UL
#define MDR_UART_MFL_DSRM        0x08UL
#define MDR_UART_MFL_RX          0x10UL
#define MDR_UART_MFL_TX          0x20UL

typedef union {
  uint32_t             Value;
  MDR_UART_ModemFlags  Flags_b;
} MDR_UART_CfgModem;


//  ----------------    IrDA Option   -------------------------
typedef struct {
  MDR_OnOff         LowPower;
  uint32_t          DivSampleRate;
} MDR_UART_CfgIrDA;


//  ----------------    DMA Option   -------------------------
typedef union {
  uint32_t             Value;
  MDR_UART_DMAFlags    Flags_b;
} MDR_UART_CfgDMA;


//=======================   Инициализация только блока UART через структуру MDR_UART_Cfg. ===============
//  Требуется предварительное включение тактирования блока и разрешение подачи этой частоты на блок с делителем BRG!
//  В структуре MDR_UART_Cfg настройки сгруппированы по назначению, для облегчения восприятия.
//  cfgBase - обязательная минимальная настройка блока UART.
//  Если какая-то из прочих опций не используется - то указать на нее задать NULL. 


typedef struct {
  MDR_UART_CfgBase  cfgBase;
  //  IRQ Enable
  MDR_UART_CfgIRQ   *pCfgIRQ;
  //  DMA Enable
  MDR_UART_CfgDMA   *pCfgDMA; 
  //  IrDA
  MDR_UART_CfgIrDA  *pCfgIrDA;  
  //  Modem Options
  MDR_UART_CfgModem *pCfgModem;
} MDR_UART_Cfg;


//  Частоту UART_Clock_Hz можно получить функцией MDR_UARTex_GetUartClockHz, см. ниже.

//  Рассчет делителей cfgBaud для получения необходимой BaudRate_Hz. 
void  MDR_UART_CalcBaudRate(MDR_UART_cfgBaud *cfgBaud, uint32_t baudRate, uint32_t UART_ClockHz);

//  Возвращает ошибку в % между реальной и заданной частотой.
double MDR_UART_CalcBaudError(const MDR_UART_cfgBaud *cfgBaud, uint32_t baudRate, uint32_t UART_ClockHz);

//  Инициализация блока с высчитыванием cfgBaud по входным параметрам.
void MDR_UART_Init(MDR_UART_Type *UART, const MDR_UART_Cfg *cfg, uint32_t baudRate, uint32_t UART_ClockHz);

//  Аналог MDR_UART_Init, но с проверкой ошибки выставления BaudRate_Hz
//  При превышении ошибки BaudErrMax функция вернет Fault, блок не будет инициализирован
bool MDR_UART_InitEx(MDR_UART_Type *UART, const MDR_UART_Cfg *cfg, uint32_t baudRate, uint32_t UART_ClockHz, double baudErrMax);

//  Делители cfgBaud задаются вручную, рассчитываются пользователем заранее
void MDR_UART_InitByBaud(MDR_UART_Type *UART, const MDR_UART_Cfg *cfg, const MDR_UART_cfgBaud *cfgBaud);

//  Функции, полезные при регистровой настройке
//  Деинициализация блока
void MDR_UART_DeInit(MDR_UART_Type *UART);
//  Обнуление регистров
void MDR_UART_ClearRegs(MDR_UART_Type *UART);


//==================    CfgRegs - выборка только конфигурационных регистров ===============
// Инициализация блока через структуру регистров отвечающих за конфигурацию.
// Аналогична инициализации через MDR_UART_Cfg, но выполняется быстрее. Привязана к железу, не HAL.

//  Конвертация структуры Cfg в CfgRegs.
void MDR_UART_ToCfgRegs(const MDR_UART_Cfg *cfg, const MDR_UART_cfgBaud *cfgBaud, MDR_UART_CfgRegs *pCfgRegs);

//  Инициализация блока через CfgRegs 
void MDR_UART_Init_ByCfgRegs(MDR_UART_Type *UART, MDR_UART_CfgRegs *pCfgRegs);

//  Запись / чтение регистров в блок.
void MDR_UART_CfgRegs_Read(MDR_UART_Type *UART, MDR_UART_CfgRegs *pCfgRegs);
void MDR_UART_CfgRegs_Apply(MDR_UART_Type *UART, MDR_UART_CfgRegs *pCfgRegs);

//  Обнуление структуры CfgRegs
void MDR_UART_CfgRegs_Clear(MDR_UART_CfgRegs *pCfgRegs);


//==================    MDR_UART_TypeEx - Инициализация UART с тактированием  ===============
// Для ВЕ4, ВК214, ВК234 требуется предварительный выбор частоты для UART_Clock!
// В остальных МК UART_Clock берется только от HCLK, т.е. частоты ядра.

typedef struct {
  // UART Block
  MDR_UART_Type     *UARTx;
  // UART_Clock and BRG
  MDR_PerClock_Cfg  CfgClock;
  //  IRQn
  IRQn_Type         UARTx_IRQn;
} MDR_UART_TypeEx;

extern const MDR_UART_TypeEx    _MDR_UART1ex;
#define MDR_UART1ex            (&_MDR_UART1ex)

extern const MDR_UART_TypeEx   _MDR_UART2ex;
#define MDR_UART2ex            (&_MDR_UART2ex)

#ifdef MDR_UART3
  extern const MDR_UART_TypeEx  _MDR_UART3ex;
  #define MDR_UART3ex          (&_MDR_UART3ex)
#endif
#ifdef MDR_UART4
  extern const MDR_UART_TypeEx  _MDR_UART4ex;
  #define MDR_UART4ex          (&_MDR_UART4ex)
#endif

//----------	Шаг 1 - инициализация UART_Clock	-------------

//  Возвращает частоту UART_CLOCK, определяется по значению ключей в схеме тактирования. 
//  Используется для подачи в функцию MDR_UART_Init, MDR_UART_AssignBaudRate и т.д.
//  Обычно частота задается в ПО, поэтому рациональней задать ее напрямую.
uint32_t  MDR_UARTex_GetUartClockHz(const MDR_UART_TypeEx *exUART, bool doUpdate);

//	Включение частоты UARTx_Clock
#if defined (MDR_PER_CLOCK_SELF_TIM_UART_SSP)
	//  VK214
  __STATIC_INLINE
	void  MDR_UARTex_SetUartClock(const MDR_UART_TypeEx *UARTex, MDR_Div128P divForUartClock, MDR_CLK_SEL_PER clockSource)
	{
		if (UARTex == MDR_UART1ex) 
			MDR_SetClock_Uart1(clockSource);
		else
			MDR_SetClock_Uart2(clockSource);
		MDR_PerClock_GateOpen(&UARTex->CfgClock, divForUartClock);
	}
	
#elif defined (MDR_UART_CLOCK_FROM_PER_CLOCK)
  //  VK234, VE4
	//	Входная частота - PER1_C2, предварительно задать MDR_SetClock_UartTimSSP(clockSource) из MDR_PER_Clock.h;
  __STATIC_INLINE
  void  MDR_UARTex_SetUartClock(const MDR_UART_TypeEx *UARTex, MDR_Div128P divForUartClock)
                                { MDR_PerClock_GateOpen(&UARTex->CfgClock, divForUartClock); }	
#elif defined (MDR_CLK_LIKE_VE8)  
	//	VE8, VK014, ESila
  __STATIC_INLINE
	void  MDR_UARTex_SetUartClock(const MDR_UART_TypeEx *UARTex, MDR_Div128P divForUartClock, MDR_RST_ASYNC_IN_SEL clockSource)
                                { MDR_PerClock_GateOpenAsync(&UARTex->CfgClock, divForUartClock, clockSource); }
#else  
	//	Входная частота - PCLK=HCLK=CPU_CLK
  __STATIC_INLINE
	void  MDR_UARTex_SetUartClock(const MDR_UART_TypeEx *UARTex, MDR_Div128P divForUartClock)
                                {	MDR_PerClock_GateOpen(&UARTex->CfgClock, divForUartClock); }
#endif

                                
//  Выбор частоты и делителя для UART_Clock "по умолчанию" (частота ядра от PLL или MAX_Clock)
__STATIC_INLINE
void  MDR_UARTex_SetUartClock_InpPLLCPU(const MDR_UART_TypeEx *UARTex, MDR_Div128P divForUartClock)
{
#if defined (MDR_PER_CLOCK_SELF_TIM_UART_SSP)
	MDR_UARTex_SetUartClock(UARTex, divForUartClock, MDR_PER_PLLCPUo);	
  
#elif defined (MDR_UART_CLOCK_FROM_PER_CLOCK)
  MDR_SetClock_UartTimSSP(MDR_PER_PLLCPUo);
  MDR_UARTex_SetUartClock(UARTex, divForUartClock);
  
#elif defined (MDR_CLK_LIKE_VE8)  
	MDR_UARTex_SetUartClock(UARTex, divForUartClock, MDR_RST_ASYNC_IN_MAX_CLK);
  
#else  
  MDR_UARTex_SetUartClock(UARTex, divForUartClock);
#endif
}

//----------	Шаг 2 - инициализация UART	-------------
//  Инициализация блока с высчитыванием cfgBaud по входным параметрам.
void MDR_UARTex_Init(const MDR_UART_TypeEx *UARTex, const MDR_UART_Cfg *cfg, uint32_t baudRate, uint32_t UART_ClockHz);

//  Аналог MDR_UART_Init, но с проверкой ошибки выставления BaudRate_Hz
//  При превышении ошибки BaudErrMax функция вернет Fault, блок не будет инициализирован
//  divForUartClock - Делитель для формирования UART_Clock из частоты тактирования блока.
bool MDR_UARTex_InitEx(const MDR_UART_TypeEx *UARTex, const MDR_UART_Cfg *cfg, uint32_t baudRate, uint32_t UART_ClockHz, double baudErrMax);

//  Делители cfgBaud задаются вручную, рассчитываются пользователем заранее
//  divForUartClock - Делитель для формирования UART_Clock из частоты тактирования блока.
void MDR_UARTex_InitByBaud(const MDR_UART_TypeEx *UARTex, const MDR_UART_Cfg *cfg, const MDR_UART_cfgBaud *cfgBaud);

//  Выключение со всеми частотами
void MDR_UARTex_DeInit(const MDR_UART_TypeEx *UARTex);

//	Включение соответствующего прерывания в NVIC
__STATIC_INLINE 
void MDR_UARTex_NVIC_EnableIRQ(const MDR_UART_TypeEx *UARTex, uint32_t priorityIRQ)
{
  NVIC_SetPriority(UARTex->UARTx_IRQn, priorityIRQ);
	NVIC_EnableIRQ(UARTex->UARTx_IRQn);
}

__STATIC_INLINE
void MDR_UARTex_NVIC_DisableIRQ(const MDR_UART_TypeEx *UARTex) { NVIC_DisableIRQ(UARTex->UARTx_IRQn); }

//===================   UART GPIO pins Init ==========================
//  Функция инициализации выводов GPIO в функции UART
typedef struct {
  const MDR_GPIO_Port *portGPIO;
  uint32_t       pinIndex;
  MDR_PIN_FUNC   pinFunc;
} MDR_UART_CfgPinGPIO;

//  Все пины кроме pPinCLK могут быть NULL и тогда они не будут проинициализированы.
//  Это на случай, если надо только принимать, или только посылать, или FSS не нужен.
typedef struct {
  const MDR_UART_CfgPinGPIO *pPinTX;  
  const MDR_UART_CfgPinGPIO *pPinRX;
} MDR_UART_CfgPinsGPIO;

void MDR_UART_InitPinsGPIO(const MDR_UART_CfgPinsGPIO *pinsCfg, MDR_PIN_PWR pinsPower);


//==================    Функции работы с блоком UART ===============

void MDR_UART_ChangeRate  (MDR_UART_Type *UART, uint32_t baudRate, uint32_t UART_ClockHz);
void MDR_UART_ChangeRateEx(MDR_UART_Type *UART, const MDR_UART_cfgBaud *cfgBaud);

//  Опрос статуса
__STATIC_INLINE uint32_t MDR_UART_GetStatus(MDR_UART_Type *UART) {return UART->FR;}

//  Передача и Чтение принятых данных
__STATIC_INLINE bool MDR_UART_CanSend  (MDR_UART_Type *UART) {return (UART->FR & MDR_UART_SFL_TxFull)  == 0;}
__STATIC_INLINE bool MDR_UART_CanRead  (MDR_UART_Type *UART) {return (UART->FR & MDR_UART_SFL_RxEmpty) == 0;}

__STATIC_INLINE void     MDR_UART_SendData(MDR_UART_Type *UART, uint8_t data) {UART->DR = data;}
__STATIC_INLINE uint16_t MDR_UART_ReadData(MDR_UART_Type *UART) {return (uint16_t)UART->DR;}

bool MDR_UART_TrySend(MDR_UART_Type *UART, uint8_t data);

// Разрешение/запрет прерываний
void MDR_UART_ChangeEventIRQ(MDR_UART_Type *UART, uint32_t eventsMask);
void MDR_UART_ChangeEventIRQEx(MDR_UART_Type *UART, MDR_UART_EventFlags selEventIRQ);

// Сброс запроса прерывания
__STATIC_INLINE void MDR_UART_ClearEventsIRQ  (MDR_UART_Type *UART, uint32_t eventsMask) {UART->ICR = eventsMask;}
__STATIC_INLINE void MDR_UART_ClearEventsIRQEx(MDR_UART_Type *UART, MDR_UART_EventFlags eventsSel) {UART->ICR = eventsSel.Value;}

// Считывание флагов всех событий (RIS)
MDR_UART_EventFlags  MDR_UART_GetEvents(MDR_UART_Type *UART);

// Изменение уровней заполнения FIFO, при которых срабатывают флаги и прерывания (если разрешены)
void MDR_UART_ChangeEventTxFIFO(MDR_UART_Type *UART, MDR_UART_EventFIFO levelFIFO);
void MDR_UART_ChangeEventRxFIFO(MDR_UART_Type *UART, MDR_UART_EventFIFO levelFIFO);

void MDR_UART_ClearTxFIFO(MDR_UART_Type *UART);
void MDR_UART_ClearRxFIFO(MDR_UART_Type *UART);


typedef union {
  uint32_t             Value;
  MDR_UART_StatusBits  Flags;
} MDR_UART_Status;

MDR_UART_Status MDR_UART_GetStatusEx(MDR_UART_Type *UART);

typedef union {
  uint16_t             Value;
  MDR_UART_DataBits    Flags;
} MDR_UART_Data;

MDR_UART_Data MDR_UART_ReadDataEx(MDR_UART_Type *UART);


#ifndef MDR_HAS_NO_DMA
//  Включение - выключение запросов к DMA. 
//  Функции изменяет настройки заданные при Init.
__STATIC_INLINE void MDR_UART_RX_DMA_Enable (MDR_UART_Type *UARTx) {UARTx->DMACR |=  MDR_UART_DMA_RX_EN;}
__STATIC_INLINE void MDR_UART_RX_DMA_Disable(MDR_UART_Type *UARTx) {UARTx->DMACR &= ~MDR_UART_DMA_RX_EN;}

__STATIC_INLINE void MDR_UART_TX_DMA_Enable (MDR_UART_Type *UARTx) {UARTx->DMACR |=  MDR_UART_DMA_TX_EN;}
__STATIC_INLINE void MDR_UART_TX_DMA_Disable(MDR_UART_Type *UARTx) {UARTx->DMACR &= ~MDR_UART_DMA_TX_EN;}
#endif


#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic pop  
#endif



#endif // MDR_UART_H


#ifndef _MDR_SSP_H
#define _MDR_SSP_H

#include <MDR_Config.h>
#include <MDR_Funcs.h>
#include <MDR_RST_Clock.h>
#include <MDR_PER_Clock.h>
#include <MDR_GPIO.h>

#include <MDR_SSP_def.h>

//  Подавление warnings компилятора V6 о добавлении  "пустот" в структуры
#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wpadded"
#endif

typedef enum {
  SPI_CPHA0_CPOL0,
  SPI_CPHA0_CPOL1,
  SPI_CPHA1_CPOL0,
  SPI_CPHA1_CPOL1,
} MDR_SPI_CPHA_CPOL;

//  Прерывания возникают даже при не включенном блоке, поэтому вынесены в отдельные функции.
//  Поэтому не инициализируются через Init
typedef struct {
  //  Config
  MDR_SSP_DataBits      DataBits;
  MDR_SSP_FrameFormat   FrameFormat;
  MDR_SPI_CPHA_CPOL     SPI_Mode;               // for SPI Only
  // BitRate                                    // BitRate = SSP_Clock / (PSR * (1 + SCR))
  uint8_t               DivSCR_0_255;           // 0 - 255, Serial Clock Rate
  uint8_t               DivPSR_2_254;           // 2 - 254, EVEN ONLY! Clock prescaller
} MDR_SSP_Config;


//  Инициализация регистров блока и FIFO. 
//  Требуется предварительное формирование частоты SSP_Clock и включение тактирования блока от этой частоты.
void MDR_SSP_Init  (MDR_SSP_Type *SSPx, MDR_SSP_Config *cfg);
//  Сброс регистров блока и FIFO_RX, FIFO_TX  
void MDR_SSP_DeInit(MDR_SSP_Type *SSPx);


//  Включение - выключение блока. Данные могут быть записаны в FIFO_TX до включения.
void MDR_SSP_EnableMaster(MDR_SSP_Type *SSPx, bool loopBackEnable);
void MDR_SSP_EnableSlave (MDR_SSP_Type *SSPx, bool outputDisable);
void MDR_SSP_Disable     (MDR_SSP_Type *SSPx);

//  Очистка буферов FIFO
void MDR_SSP_ClearFIFO_RX(MDR_SSP_Type *SSPx);
void MDR_SSP_ClearFIFO_TX(MDR_SSP_Type *SSPx);

//  Опрос статуса SSP
typedef union {
  uint32_t            Status;
  MDR_SSP_StatusFlags Flags;
} MDR_SSP_Status;

MDR_SSP_Status MDR_SSP_GetStatus(MDR_SSP_Type *SSPx);

__STATIC_INLINE uint32_t MDR_SSP_GetStatusInt(MDR_SSP_Type *SSPx) { return SSPx->SR; }
__STATIC_INLINE bool     MDR_SSP_GetStatusFlagSet(MDR_SSP_Type *SSPx, uint32_t flagSel) { return (SSPx->SR & flagSel) != 0; }

__STATIC_INLINE bool MDR_SSP_IsEmptyFIFO_TX(MDR_SSP_Type *SSPx) {return MDR_SSP_GetStatusFlagSet(SSPx, MDR_SSP_SR_TX_Empty); }
__STATIC_INLINE bool MDR_SSP_IsBusy(MDR_SSP_Type *SSPx) {return MDR_SSP_GetStatusFlagSet(SSPx, MDR_SSP_SR_Busy); }


//  Запись данных в FIFO_TX. Проверять флаги что FIFO_TX не полон и есть куда писать.
__STATIC_INLINE bool MDR_SSP_CanWrite(MDR_SSP_Type *SSPx) {return MDR_SSP_GetStatusFlagSet(SSPx, MDR_SSP_SR_TX_NotFull); }
__STATIC_INLINE void MDR_SSP_WriteData(MDR_SSP_Type *SSPx, uint16_t data) {SSPx->DR = data;}

// Чтение из FIFO_RX. Проверять флаги, что данные в FIFO_RX есть. Пустое не читать.
__STATIC_INLINE bool     MDR_SSP_CanRead (MDR_SSP_Type *SSPx) {return MDR_SSP_GetStatusFlagSet(SSPx, MDR_SSP_SR_RX_NotEmpty); }
__STATIC_INLINE uint16_t MDR_SSP_ReadData(MDR_SSP_Type *SSPx) {return (uint16_t)SSPx->DR;}


//  Ожидание появления места в буфере FIFO_RX и запись данных на отправку
void MDR_SSP_WaitAndSendData(MDR_SSP_Type *SSPx, uint16_t data);
//  Ожидание появления данных в FIFO_RX и чтение
uint16_t MDR_SSP_WaitAndReadData(MDR_SSP_Type *SSPx);
//  Посылка и прием данных в режиме мастера. Возвращает данные, синхронно полученные с посылкой.
uint16_t MDR_SSP_MasterTransfer (MDR_SSP_Type *SSPx, uint16_t data);


//  Структура для флагов событий
typedef union {
  uint32_t           Events;
  MDR_SSP_EventFlags Flags;
} MDR_SSP_Events;

//  Разрешение прерываний по возникновению событий
//  Прерывания возникают даже при не включенном блоке, поэтому вынесены в отдельные функции.
//  Вызывать после Init!
                void MDR_SSP_EnableEventIRQ(MDR_SSP_Type *SSPx, MDR_SSP_Events eventIRQ);
__STATIC_INLINE void MDR_SSP_DisableEventIRQ(MDR_SSP_Type *SSPx) {SSPx->IMSC = 0;}
      MDR_SSP_Events MDR_SSP_GetEventIRQ(MDR_SSP_Type *SSPx);

//  Чтение флагов событий
MDR_SSP_Events MDR_SSP_GetEventsMasked(MDR_SSP_Type *SSPx);
MDR_SSP_Events MDR_SSP_GetEventsAll(MDR_SSP_Type *SSPx);

//  Сброс флагов событий. Write-Only!
__STATIC_INLINE void MDR_SSP_ClearEvent_RxOverrun(MDR_SSP_Type *SSPx) {SSPx->ICR |= MDR_SSP_ICR_RORIC_Msk;}
__STATIC_INLINE void MDR_SSP_ClearEvent_RxTimeout(MDR_SSP_Type *SSPx) {SSPx->ICR |= MDR_SSP_ICR_RTIC_Msk;}

//  Разрешение запрет прерываний по FIFO_RX, FIFO_TX
__STATIC_INLINE void MDR_SSP_RxHalfFull_IRQ_Enable (MDR_SSP_Type *SSPx) {SSPx->IMSC |=  MDR_SSP_IRQ_RxHalfFull_Msk;}
__STATIC_INLINE void MDR_SSP_RxHalfFull_IRQ_Disable(MDR_SSP_Type *SSPx) {SSPx->IMSC &= ~MDR_SSP_IRQ_RxHalfFull_Msk;}
__STATIC_INLINE void MDR_SSP_TxHalfEmpty_IRQ_Enable (MDR_SSP_Type *SSPx) {SSPx->IMSC |=  MDR_SSP_IRQ_TxHalfEmpty_Msk;}
__STATIC_INLINE void MDR_SSP_TxHalfEmpty_IRQ_Disable(MDR_SSP_Type *SSPx) {SSPx->IMSC &= ~MDR_SSP_IRQ_TxHalfEmpty_Msk;}

__STATIC_INLINE void MDR_SSP_RxTimeout_IRQ_Enable (MDR_SSP_Type *SSPx) {SSPx->IMSC |=  MDR_SSP_IRQ_RxTimeout_Msk;}
__STATIC_INLINE void MDR_SSP_RxTimeout_IRQ_Disable(MDR_SSP_Type *SSPx) {SSPx->IMSC &= ~MDR_SSP_IRQ_RxTimeout_Msk;}
__STATIC_INLINE void MDR_SSP_RxOverrun_IRQ_Enable (MDR_SSP_Type *SSPx) {SSPx->IMSC |=  MDR_SSP_IRQ_RxOver_Msk;}
__STATIC_INLINE void MDR_SSP_RxOverrun_IRQ_Disable(MDR_SSP_Type *SSPx) {SSPx->IMSC &= ~MDR_SSP_IRQ_RxOver_Msk;}


#ifndef MDR_HAS_NO_DMA
//  Включение - выключение запросов к DMA. 
//  Функции изменяет настройки заданные при Init.
__STATIC_INLINE void MDR_SSP_RX_DMA_Enable (MDR_SSP_Type *SSPx) {SSPx->DMACR |=  MDR_SSP_DMACR_RXDMAE_Msk;}
__STATIC_INLINE void MDR_SSP_RX_DMA_Disable(MDR_SSP_Type *SSPx) {SSPx->DMACR &= ~MDR_SSP_DMACR_RXDMAE_Msk;}

__STATIC_INLINE void MDR_SSP_TX_DMA_Enable (MDR_SSP_Type *SSPx) {SSPx->DMACR |=  MDR_SSP_DMACR_TXDMAE_Msk;}
__STATIC_INLINE void MDR_SSP_TX_DMA_Disable(MDR_SSP_Type *SSPx) {SSPx->DMACR &= ~MDR_SSP_DMACR_TXDMAE_Msk;}
#endif

// Вспомогательные функции
void MDR_SSP_ChangeSPIMode(MDR_SSP_Type *SSPx, MDR_SPI_CPHA_CPOL newMode);
void MDR_SSP_ChangeDataBits(MDR_SSP_Type *SSPx, MDR_SSP_DataBits newDataBits);
void MDR_SSP_ChangeRate(MDR_SSP_Type *SSPx, uint8_t divSCR_0_255, uint8_t divPSR_2_254);
void MDR_SSP_ChangeFrameFormat(MDR_SSP_Type *SSPx, MDR_SSP_FrameFormat newFrameFormat);


//  ===============   Функции управления через расширенную структуру блока MDR_SSP_TypeEx ==================

//  Расширенная структура содержат дополнительную конфигурацию для включения тактирования и настройки прерывания
typedef struct {
  // SSP Block
  MDR_SSP_Type *     SSPx;
  // SSPClock and BRG
  MDR_PerClock_Cfg   CfgClock;  
  //  IRQn
  IRQn_Type          SSPx_IRQn;
} MDR_SSP_TypeEx;


extern const MDR_SSP_TypeEx    _MDR_SSP1ex;
#define MDR_SSP1ex            (&_MDR_SSP1ex)

#ifdef MDR_SSP2
  extern const MDR_SSP_TypeEx  _MDR_SSP2ex;
  #define MDR_SSP2ex          (&_MDR_SSP2ex)
#endif
#ifdef MDR_SSP3
  extern const MDR_SSP_TypeEx  _MDR_SSP3ex;
  #define MDR_SSP3ex          (&_MDR_SSP3ex)
#endif
#ifdef MDR_SSP4
  extern const MDR_SSP_TypeEx  _MDR_SSP4ex;
  #define MDR_SSP4ex          (&_MDR_SSP4ex)
#endif
#ifdef MDR_SSP5
  extern const MDR_SSP_TypeEx  _MDR_SSP5ex;
  #define MDR_SSP5ex          (&_MDR_SSP5ex)
#endif
#ifdef MDR_SSP6
  extern const MDR_SSP_TypeEx  _MDR_SSP6ex;
  #define MDR_SSP6ex          (&_MDR_SSP6ex)
#endif

//  Эти расширенные Функции Init/Finit включают/выключают 
//   - частоту SSP_Clock. (В ВЕ4,ВК214,ВК234 предварительно должна быть выбрана входная частота для SSP_Clock (см. MDR_PER_Clock.h). 
//     В остальных контроллерах SSP_Clock всегда формируется от HCLK, которая равна частоте CPU.)
//   - тактирование блока от частоты SSP_Clock.
//   - активацию прерываний.
//  Т.е. обеспечавают полную инициализацию блока "под ключ".

void MDR_SSPex_Init  (const MDR_SSP_TypeEx *exSSPx, MDR_SSP_Config *cfgSSP);
void MDR_SSPex_DeInit(const MDR_SSP_TypeEx *exSSPx);


//	Включение соответствующего прерывания в NVIC
__STATIC_INLINE
void MDR_SSP_NVIC_EnableIRQ(const MDR_SSP_TypeEx *exSSPx, uint32_t priorityIRQ)
{
  NVIC_EnableIRQ(exSSPx->SSPx_IRQn);
  NVIC_SetPriority(exSSPx->SSPx_IRQn, priorityIRQ);
}

__STATIC_INLINE
void MDR_SSP_NVIC_DisableIRQ(const MDR_SSP_TypeEx *exSSPx)
{
  NVIC_DisableIRQ(exSSPx->SSPx_IRQn);
}

// Следующие функции повтояют варинт без "ex" для единообразия вызова. Вместо структуры блока SSPx, просто подается расширенная exSSPx.
// Т.к. в коде проще использовать одну структуру для вызова всех функций. Но выборка адреса exSSPx->SSPx занимает дополнительное время.
// Поэтому пользователю необходимо решить что ему больше подходит - удобство и читабельность кода или экономия пары тактов CPU на выборку SSPx.
// Либо можно вызвать MDR_SSPex_Init c расширенной структурой exSSPx, а остальные функции использовать с нормальной SSPx.

//  Включение - выключение блока. Данные могут быть записаны в FIFO_TX до включения.
__STATIC_INLINE void MDR_SSPex_EnableMaster(const MDR_SSP_TypeEx *exSSPx, bool loopBackEnable){MDR_SSP_EnableMaster(exSSPx->SSPx, loopBackEnable);}
__STATIC_INLINE void MDR_SSPex_EnableSlave (const MDR_SSP_TypeEx *exSSPx, bool outputDisable) {MDR_SSP_EnableSlave(exSSPx->SSPx, outputDisable);}
__STATIC_INLINE void MDR_SSPex_Disable     (const MDR_SSP_TypeEx *exSSPx) {MDR_SSP_Disable(exSSPx->SSPx);}

//  Очистка буферов FIFO
__STATIC_INLINE void MDR_SSPex_ClearFIFO_RX(const MDR_SSP_TypeEx *exSSPx) {MDR_SSP_ClearFIFO_RX(exSSPx->SSPx);}
__STATIC_INLINE void MDR_SSPex_ClearFIFO_TX(const MDR_SSP_TypeEx *exSSPx) {MDR_SSP_ClearFIFO_TX(exSSPx->SSPx);}

//  Опрос статуса SSP
__STATIC_INLINE MDR_SSP_Status MDR_SSPex_GetStatus(const MDR_SSP_TypeEx *exSSPx) {return MDR_SSP_GetStatus(exSSPx->SSPx);}

//  Запись данных в FIFO_TX. Проверять флаги что FIFO_TX не полон и есть куда писать.
__STATIC_INLINE bool MDR_SSPex_CanWrite (const MDR_SSP_TypeEx *exSSPx) {return MDR_SSP_CanWrite(exSSPx->SSPx); }
__STATIC_INLINE void MDR_SSPex_WriteData(const MDR_SSP_TypeEx *exSSPx, uint16_t data) {exSSPx->SSPx->DR = data;}

// Чтение из FIFO_RX. Проверять флаги, что данные в FIFO_RX есть. Пустое не читать.
__STATIC_INLINE bool     MDR_SSPex_CanRead (const MDR_SSP_TypeEx *exSSPx) {return MDR_SSP_CanRead(exSSPx->SSPx); }
__STATIC_INLINE uint16_t MDR_SSPex_ReadData(const MDR_SSP_TypeEx *exSSPx) {return (uint16_t)exSSPx->SSPx->DR;}


//  Ожидание появления места в буфере FIFO_RX и запись данных на отправку
__STATIC_INLINE void MDR_SSPex_WaitAndSendData(const MDR_SSP_TypeEx *exSSPx, uint16_t data) {MDR_SSP_WaitAndSendData(exSSPx->SSPx, data);}
//  Ожидание появления данных в FIFO_RX и чтение
__STATIC_INLINE uint16_t MDR_SSPex_WaitAndReadData(const MDR_SSP_TypeEx *exSSPx) {return MDR_SSP_WaitAndReadData(exSSPx->SSPx);}
//  Посылка и прием данных в режиме мастера. Возвращает данные, синхронно полученные с посылкой.
__STATIC_INLINE uint16_t MDR_SSPex_MasterTransfer(const MDR_SSP_TypeEx *exSSPx, uint16_t data) {return MDR_SSP_MasterTransfer(exSSPx->SSPx, data);}

//  Разрешение прерываний по возникновению событий
//  Прерывания возникают даже при не включенном блоке, поэтому вынесены в отдельные функции.
//  Вызывать после Init!
__STATIC_INLINE void MDR_SSPex_EnableEventIRQ(const MDR_SSP_TypeEx *exSSPx, MDR_SSP_Events eventIRQ) {MDR_SSP_EnableEventIRQ(exSSPx->SSPx, eventIRQ);}
__STATIC_INLINE void MDR_SSPex_DisableEventIRQ(const MDR_SSP_TypeEx *exSSPx) {exSSPx->SSPx->IMSC = 0;}
__STATIC_INLINE MDR_SSP_Events MDR_SSPex_GetEventIRQ(const MDR_SSP_TypeEx *exSSPx) {return MDR_SSP_GetEventIRQ(exSSPx->SSPx);}

//  Чтение флагов событий, замаскированных и нет.
__STATIC_INLINE MDR_SSP_Events MDR_SSPex_GetEventsMasked(const MDR_SSP_TypeEx *exSSPx) {return MDR_SSP_GetEventsMasked(exSSPx->SSPx);}
__STATIC_INLINE MDR_SSP_Events MDR_SSPex_GetEventsAll   (const MDR_SSP_TypeEx *exSSPx) {return MDR_SSP_GetEventsAll(exSSPx->SSPx);}

//  Сброс флагов событий. Write-Only!
__STATIC_INLINE void MDR_SSPex_ClearEvent_RxOverrun(const MDR_SSP_TypeEx *exSSPx) {exSSPx->SSPx->ICR |= MDR_SSP_ICR_RORIC_Msk;}
__STATIC_INLINE void MDR_SSPex_ClearEvent_RxTimeout(const MDR_SSP_TypeEx *exSSPx) {exSSPx->SSPx->ICR |= MDR_SSP_ICR_RTIC_Msk;}

//  Разрешение запрет прерываний по FIFO_RX, FIFO_TX
__STATIC_INLINE void MDR_SSPex_RxHalfFull_IRQ_Enable (const MDR_SSP_TypeEx *exSSPx) {exSSPx->SSPx->IMSC |=  MDR_SSP_IRQ_RxHalfFull_Msk;}
__STATIC_INLINE void MDR_SSPex_RxHalfFull_IRQ_Disable(const MDR_SSP_TypeEx *exSSPx) {exSSPx->SSPx->IMSC &= ~MDR_SSP_IRQ_RxHalfFull_Msk;}
__STATIC_INLINE void MDR_SSPex_TxHalfEmpty_IRQ_Enable (const MDR_SSP_TypeEx *exSSPx) {exSSPx->SSPx->IMSC |=  MDR_SSP_IRQ_TxHalfEmpty_Msk;}
__STATIC_INLINE void MDR_SSPex_TxHalfEmpty_IRQ_Disable(const MDR_SSP_TypeEx *exSSPx) {exSSPx->SSPx->IMSC &= ~MDR_SSP_IRQ_TxHalfEmpty_Msk;}

__STATIC_INLINE void MDR_SSPex_RxTimeout_IRQ_Enable (const MDR_SSP_TypeEx *exSSPx) {exSSPx->SSPx->IMSC |=  MDR_SSP_IRQ_RxTimeout_Msk;}
__STATIC_INLINE void MDR_SSPex_RxTimeout_IRQ_Disable(const MDR_SSP_TypeEx *exSSPx) {exSSPx->SSPx->IMSC &= ~MDR_SSP_IRQ_RxTimeout_Msk;}
__STATIC_INLINE void MDR_SSPex_RxOverrun_IRQ_Enable (const MDR_SSP_TypeEx *exSSPx) {exSSPx->SSPx->IMSC |=  MDR_SSP_IRQ_RxOver_Msk;}
__STATIC_INLINE void MDR_SSPex_RxOverrun_IRQ_Disable(const MDR_SSP_TypeEx *exSSPx) {exSSPx->SSPx->IMSC &= ~MDR_SSP_IRQ_RxOver_Msk;}



#ifndef MDR_HAS_NO_DMA
//  Включение - выключение запросов к DMA. 
//  Функции изменяет настройки заданные при Init.
__STATIC_INLINE void MDR_SSPex_RX_DMA_Enable (const MDR_SSP_TypeEx *exSSPx) {exSSPx->SSPx->DMACR |=  MDR_SSP_DMACR_RXDMAE_Msk;}
__STATIC_INLINE void MDR_SSPex_RX_DMA_Disable(const MDR_SSP_TypeEx *exSSPx) {exSSPx->SSPx->DMACR &= ~MDR_SSP_DMACR_RXDMAE_Msk;}

__STATIC_INLINE void MDR_SSPex_TX_DMA_Enable (const MDR_SSP_TypeEx *exSSPx) {exSSPx->SSPx->DMACR |=  MDR_SSP_DMACR_TXDMAE_Msk;}
__STATIC_INLINE void MDR_SSPex_TX_DMA_Disable(const MDR_SSP_TypeEx *exSSPx) {exSSPx->SSPx->DMACR &= ~MDR_SSP_DMACR_TXDMAE_Msk;}
#endif


// Вспомогательные функции
__STATIC_INLINE void MDR_SSPex_ChangeSPIMode(const MDR_SSP_TypeEx *exSSPx, MDR_SPI_CPHA_CPOL newMode)    {MDR_SSP_ChangeSPIMode(exSSPx->SSPx, newMode);}
__STATIC_INLINE void MDR_SSPex_ChangeDataBits(const MDR_SSP_TypeEx *exSSPx, MDR_SSP_DataBits newDataBits) {MDR_SSP_ChangeDataBits(exSSPx->SSPx, newDataBits);}
__STATIC_INLINE void MDR_SSPex_ChangeRate(const MDR_SSP_TypeEx *exSSPx, uint8_t divSCR_0_255, uint8_t divPSR_2_254){MDR_SSP_ChangeRate(exSSPx->SSPx, divSCR_0_255, divPSR_2_254);}
__STATIC_INLINE void MDR_SSPex_ChangeFrameFormat(const MDR_SSP_TypeEx *exSSPx, MDR_SSP_FrameFormat newFrameFormat) {MDR_SSP_ChangeFrameFormat(exSSPx->SSPx, newFrameFormat);}



//===================   Вспомогательные функции ==========================
//  BitRate:                  // BitRate = SSP_Clock / (PSR * (1 + SCR))
//    DivSCR_0_255;           // 0 - 255, Serial Clock Rate
//    DivPSR_2_254;           // 2 - 254, EVEN ONLY! Clock prescaller
//  Убедиться что SPI не передает (Busy)
void MDR_SPI_ChangeRate(MDR_SSP_Type *SSPx, uint8_t divSCR_0_255, uint8_t divPSR_2_254);

// using anonymous
#if defined (__CC_ARM)
  #pragma push
  #pragma anon_unions
#endif
  //  Вспогательная структура, исползуется в драйверах микросхем, например 5600ВВ3Т
  typedef union {
     uint16_t Rates;
     struct {                    // BitRate = SSP_Clock / (PSR * (1 + SCR))
     uint8_t  divSCR_0_255;      // 0 - 255, Serial Clock Rate
     uint8_t  divPSR_2_254;      // 2 - 254, EVEN ONLY! Clock prescaller
     };
  } MDR_SSP_Rates;
#if defined (__CC_ARM)
  #pragma pop
#endif


//===================   SSP GPIO pins Init ==========================
//  Функция инициализации выводов GPIO в функции SSP
typedef struct {
  const MDR_GPIO_Port *portGPIO;
  uint32_t       pinIndex;
  MDR_PIN_FUNC   pinFunc;
} MDR_SSP_CfgPinGPIO;

//  Все пины кроме pPinCLK могут быть NULL и тогда они не будут проинициализированы.
//  Это на случай, если надо только принимать, или только посылать, или FSS не нужен.
typedef struct {
  const MDR_SSP_CfgPinGPIO *pPinCLK;
  const MDR_SSP_CfgPinGPIO *pPinTX;
  const MDR_SSP_CfgPinGPIO *pPinRX;
  const MDR_SSP_CfgPinGPIO *pPinFSS;
} MDR_SSP_CfgPinsGPIO;

void MDR_SSP_InitPinsGPIO(const MDR_SSP_CfgPinsGPIO *pinsCfg, MDR_PIN_PWR pinsPower);


//  ============    Расширенная инициализация для ESila и 1923ВК014   =============
//  Длина посылки до 32-бит, Fast режим для slave
#ifdef MDR_SSP_HAS_LEN32
  //  Инициализация только SSP
  void MDR_SSP_Init_Len32(MDR_SSP_Type *SSPx, MDR_SSP_Config *cfg, bool useFastForSlave);

  //  Инициализация SSP c тактированием и SSP_CLock
  void MDR_SSPex_Init_Len32(const MDR_SSP_TypeEx *exSSPx, MDR_SSP_Config *cfgSSP, bool useFastForSlave);

#endif



#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic pop  
#endif



//	Включение частоты SSPx_Clock
#if defined (MDR_PER_CLOCK_SELF_TIM_UART_SSP)
	//  VK214
  __STATIC_INLINE
  void  MDR_SSPex_SetSSPClock(const MDR_SSP_TypeEx *SSPex, MDR_Div128P divForSSPClock, MDR_CLK_SEL_PER clockSource)
	{
  	MDR_SetClock_SSP1(clockSource);
		MDR_PerClock_GateOpen(&SSPex->CfgClock, divForSSPClock);
	}
	
#elif defined (MDR_SSP_CLOCK_FROM_PER_CLOCK)
  //  VK234, VE4
	//	Входная частота - PER1_C2, предварительно задать MDR_SetClock_UartTimSSP(clockSource) из MDR_PER_Clock.h;
  __STATIC_INLINE
  void  MDR_SSPex_SetSSPClock(const MDR_SSP_TypeEx *SSPex, MDR_Div128P divForSSPClock)
                              { MDR_PerClock_GateOpen(&SSPex->CfgClock, divForSSPClock); }
  
#elif defined (MDR_CLK_LIKE_VE8)  
	//	VE8, VK014, ESila
  __STATIC_INLINE
  void  MDR_SSPex_SetSSPClock(const MDR_SSP_TypeEx *SSPex, MDR_Div128P divForSSPClock, MDR_RST_ASYNC_IN_SEL clockSource)
                              { MDR_PerClock_GateOpenAsync(&SSPex->CfgClock, divForSSPClock, clockSource); }
  
#else  
	//	Входная частота - PCLK=HCLK=CPU_CLK
  __STATIC_INLINE
  void  MDR_SSPex_SetSSPClock(const MDR_SSP_TypeEx *SSPex, MDR_Div128P divForSSPClock)
                              {	MDR_PerClock_GateOpen(&SSPex->CfgClock, divForSSPClock); }
#endif

                              
//  Выбор частоты и делителя для SSP_Clock "по умолчанию" (частота ядра от PLL или MAX_Clock)
__STATIC_INLINE
void  MDR_SSPex_SetSSPClock_InpPLLCPU(const MDR_SSP_TypeEx *SSPex, MDR_Div128P divForSSPClock)
{
#if defined (MDR_PER_CLOCK_SELF_TIM_UART_SSP)
  MDR_SSPex_SetSSPClock(SSPex, divForSSPClock, MDR_PER_PLLCPUo);	
  
#elif defined (MDR_UART_CLOCK_FROM_PER_CLOCK)
  MDR_SetClock_UartTimSSP(MDR_PER_PLLCPUo);
  MDR_SSPex_SetSSPClock(SSPex, divForSSPClock);
  
#elif defined (MDR_CLK_LIKE_VE8)  
	MDR_SSPex_SetSSPClock(SSPex, divForSSPClock, MDR_RST_ASYNC_IN_MAX_CLK);
  
#else  
  MDR_SSPex_SetSSPClock(SSPex, divForSSPClock);
#endif
}

#endif //  _MDR_SSP_H

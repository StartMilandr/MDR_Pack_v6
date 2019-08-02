#include "test_SSP_Interfs.h"
#include "SSP_cfg.h"
#include "SSP_CommonFuncs.h"

//===============   ОПИСАНИЕ  ======================
//  Тест проверяет выработку прерываний по событиям, и в их обработчиках делает следующее:
//    FIFO_TX_HalfEmpty - записываются данные в FIFO_TX ведомого и мастера.
//    FIFO_RX_HalfFull  - вычитываются данные из FIFO_RX (3 слова), но так чтобы в FIFO_RX остались данные, чтобы сработало прерывание по таймауту RX_Timeout.
//    RX_Timeout  - Вычитываются оставшиеся данные, т.к. прерывание возникает последним.
//    Данные передаются порциями, чтобы согласовать работу мастера и ведомого в одном микроконтроллере. 
//    Необходимо чтобы задержка между "порциями" не превышала время таймаута приемника, равного 32-периодам частоты передачи.
//    Эта задержка определяется скоростью исполнения кода по вычитыванию принятых данных и записью новых в FIFO_TX мастера и ведомого.
//    Чтобы код успевал исполняться, используется большой делитель DivPSR_2_254 = 25, для получения относительно низкой частоты передачи.
//    В таком варианте прерывание по таймауту срабатывает по завершению передачи всего объема данных.
//  Кнопки:
//    - Up    - Смена теста
//    - Right - Смена количества бит в слове данных
//    - Down  - Запуск передачи-приема массива данных из 100 значений
//  Принимаемые данные сравниваются с отправляемыми, количество ошибок выводится на экран LCD.
//  Если ошибок нет выводится Success Transfer

//  LBM Test Interface functions
static void TestSSP_Init(void);
static void TestSSP_Finit(void);
static void TestSSP_Change(void);
static void TestSSP_Exec(void);
static void TestSSP_MasterHandleIRQ(void);
static void TestSSP_SlaveHandleIRQ(void);

TestInterface TI_SSP_IRQ = {
  .funcInit       = TestSSP_Init,
  .funcFinit      = TestSSP_Finit,
  .funcChange     = TestSSP_Change,
  .funcExec       = TestSSP_Exec,
  .funcHandlerIrqMaster = TestSSP_MasterHandleIRQ,
  .funcHandlerIrqSlave  = TestSSP_SlaveHandleIRQ
};


static uint8_t tempDivPSR_2_254;

static void TestSSP_Init(void)
{ 
  tempDivPSR_2_254 = cfgSSPex.cfgSSP->DivPSR_2_254;
  //  Уменьшаем скорость обмена
  //  Необходимо, чтобы SPI работал медленнее, чем исполняется код.
  //  Иначе исполнение кода исполняется дольше, чем длительность таймаута для RX. 
  //  Т.е. задержка на посылку новой порции данных превышает длительность в 32-такта частоты обмена.
  cfgSSPex.cfgSSP->DivSCR_0_255 = 0;
  cfgSSPex.cfgSSP->DivPSR_2_254 = 254;
  
  //  Init  Master  
  MDR_SSPex_InitEx(SSP_MASTER, &cfgSSPex);
  MDR_SSPex_EnableMaster(SSP_MASTER, false);
  //  Init  Slave
  MDR_SSPex_InitEx(SSP_SLAVE, &cfgSSPex);
  MDR_SSPex_EnableSlave(SSP_SLAVE, false);  
  
  LCD_ShowInit(SSP_MASTER, "IRQ Bits");
}

static void TestSSP_Finit(void)
{ 
  MDR_SSPex_DeInit(SSP_MASTER);
  MDR_SSPex_DeInit(SSP_SLAVE);
  
  cfgSSPex.cfgSSP->DivPSR_2_254 = tempDivPSR_2_254;
}

static void TestSSP_Change(void)
{
  Cfg_NextDataBits();
  MDR_SSPex_ChangeDataBits(SSP_MASTER, cfgSSPex.cfgSSP->DataBits);
  MDR_SSPex_ChangeDataBits(SSP_SLAVE,  cfgSSPex.cfgSSP->DataBits);  
  
  LCD_ShowInit(SSP_MASTER, "IRQ Bits");
}


#define TRANSF_DATA_COUNT   100
static uint16_t transferData[TRANSF_DATA_COUNT];
static uint16_t dataRX_M[TRANSF_DATA_COUNT];
static uint16_t dataRX_S[TRANSF_DATA_COUNT];

typedef struct {
  uint32_t indSend; 
  uint32_t indRead;
  uint16_t *pDataRD;
} SSP_DataCfg;

static SSP_DataCfg cfgDataMaster, cfgDataSlave;

static uint32_t TransferReady = 0;
static uint16_t lastData = 0;

static void SSP_Handler_WriteSlave(const MDR_SSP_TypeEx *exSSPx, SSP_DataCfg * cfg);
void SSP_Handler_WriteMaster(const MDR_SSP_TypeEx *exSSPx, SSP_DataCfg * cfg);

static void PrepareDataBuffs(void)
{  
  uint32_t i;  
  for (i = 0; i < TRANSF_DATA_COUNT; ++i)
  {
    transferData[i] = lastData;
    ++lastData;
    if (lastData >= Cfg_DataMaxValue)
      lastData = 0;

    dataRX_M[i] = 0;
    dataRX_S[i] = 0; 
  }
}

static void TestSSP_Exec(void)
{ 
  LCD_ShowStarted();  
  
  TransferReady = 0;
  
  cfgDataMaster.indRead = 0;
  cfgDataMaster.indSend = 0;
  cfgDataMaster.pDataRD = dataRX_M;

  cfgDataSlave.indRead = 0;
  cfgDataSlave.indSend = 0;
  cfgDataSlave.pDataRD = dataRX_S;
  
  PrepareDataBuffs();
    
  //  Инициализация выводов GPIO в функции SSP
  Cfg_SSP_Master_CapturePins();
  Cfg_SSP_Slave_CapturePins();  
  
  //  Включение прерываний по приему в мастере.
  //  Они сработают когда появятся данные в FIFO_RX.
  MDR_SSP_Events cfgIRQ = {.Flags.RX_Timeout = MDR_On, .Flags.RX_HalfFull = MDR_On};
  MDR_SSPex_EnableEventIRQ(SSP_MASTER, cfgIRQ);
  
  //  Добавлем прерывание по TX_HalfEmpty - оно сработает сразу. Т.к. FIFO_TX пустое.
  //  В этом обработчике включится прерывание TX_HalfEmpty в Мастере, которое уже начнет обмен данными.
  //  Необходимо чтобы в FIFO_TX ведомого уже были данные, когда мастер начнет обмен. Поэтому ведомый запускается первым.
  cfgIRQ.Flags.TX_HalfEmpty = MDR_On;
  MDR_SSPex_EnableEventIRQ(SSP_SLAVE, cfgIRQ); 
}

static void CheckResults(void)
{
  uint32_t i;
  uint32_t errCount = 0;

  //  Сравнение отправляемых и принятых данных
  for (i = 0; i < TRANSF_DATA_COUNT; ++i)
    if ((transferData[i] != dataRX_M[i]) || (transferData[i] != dataRX_S[i]))
      ++errCount;

  //  Возврат пинов GPIO в исходное состояние - для работы LCD
  Cfg_SSP_Slave_ReleasePins();
  Cfg_SSP_Master_ReleasePins();    
    
  LCD_ShowResult(errCount);  
}

// Вычитывание данных в прерывании SSP
static bool SSP_Handler_Read(const MDR_SSP_TypeEx *exSSPx, SSP_DataCfg * cfg)
{  
  uint32_t i;
   
  //  Есть событие по FIFO_RX на половину полон
  if (MDR_SSPex_GetEventsMasked(exSSPx).Flags.RX_HalfFull == MDR_On) 
  {
    if (cfg->indRead < TRANSF_DATA_COUNT)
    {
      //  Оставляем в FIFO_RX одно слово, чтобы могло сработать событие по таймауту
      for (i = 0; i < 3; ++i)
      {
        cfg->pDataRD[cfg->indRead] = MDR_SSPex_ReadData(exSSPx);
        ++cfg->indRead;
        if (cfg->indRead >= TRANSF_DATA_COUNT)
          MDR_SSPex_RxHalfFull_IRQ_Disable(exSSPx);
      }
    }
    else
      while (1);   // Error - Событие замаскировано!
  }
  
  //  Таймаут RX - вычитывает оставшиеся данные
  if (MDR_SSPex_GetEventsMasked(exSSPx).Flags.RX_Timeout == MDR_On) 
  {
    if (cfg->indRead < TRANSF_DATA_COUNT)
    {
      while (MDR_SSPex_CanRead(exSSPx))    
      {
        cfg->pDataRD[cfg->indRead] = MDR_SSPex_ReadData(exSSPx);
        ++cfg->indRead;
        if (cfg->indRead >= TRANSF_DATA_COUNT)
        {
          MDR_SSPex_RxTimeout_IRQ_Disable(exSSPx);
          return true;
        }
      }
    }
    else
      while (1);   // Error - Событие замаскировано!
  }
  return false;
}

// Посылка данных в прерывании SSP для ведомого
void SSP_Handler_WriteSlave(const MDR_SSP_TypeEx *exSSPx, SSP_DataCfg * cfg)
{
  //  Есть событие по FIFO_TX на половину пуст
  if (MDR_SSPex_GetEventsMasked(exSSPx).Flags.TX_HalfEmpty == MDR_On) 
  {
    if (cfg->indSend < TRANSF_DATA_COUNT)
    {
      while (MDR_SSPex_CanWrite(exSSPx))
      {
        MDR_SSPex_WriteData(exSSPx, transferData[cfg->indSend]);
        ++cfg->indSend;
        if (cfg->indSend >= TRANSF_DATA_COUNT)
          MDR_SSPex_TxHalfEmpty_IRQ_Disable(exSSPx);
      }
      //  Enable Master Send
      MDR_SSPex_TxHalfEmpty_IRQ_Enable(SSP_MASTER);
    }
    else
      while (1);   // Error - Событие замаскировано!
  }  
}

// Посылка данных в прерывании SSP для мастера
void SSP_Handler_WriteMaster(const MDR_SSP_TypeEx *exSSPx, SSP_DataCfg * cfg)
{
  uint32_t i;
  uint32_t cnt;
  
  //  Есть событие по FIFO_TX на половину пуст
  if (MDR_SSPex_GetEventsMasked(exSSPx).Flags.TX_HalfEmpty == MDR_On) 
  {   
    //  Запрещаем прерывание, чтобы мастер не висел в прерывании непреревно выдавая данные
    //  Разрешаем после инициализации буфера ведомым.
    MDR_SSPex_TxHalfEmpty_IRQ_Disable(exSSPx);
    
    //  Заполняем буфер новыми данными
    //  Тут же начинается передача данных, поэтому если цикл сделать по MDR_SSPex_CanWrite(), то 
    //  в цикле запишется больше значений, чем ведомый сможет принять. (Больше размера FIFO)
    //  Поэтому посылаем данные в количестве размера приемного FIFO или его половины
    if (MDR_SSPex_GetStatus(exSSPx).Flags.TX_Empty == MDR_On)
      cnt = MDR_SSP_FIFO_LEN;
    else
      cnt = MDR_SSP_FIFO_LEN / 2;    
    if (cfg->indSend + cnt > TRANSF_DATA_COUNT)
      cnt = TRANSF_DATA_COUNT - cfg->indSend;
    
    for (i = 0; i < cnt; ++i)
      MDR_SSPex_WriteData(exSSPx, transferData[cfg->indSend++]);
  }  
}

static void TestSSP_MasterHandleIRQ(void)
{
  if (SSP_Handler_Read(SSP_MASTER, &cfgDataMaster))
  {
    TransferReady |= 1;
    if (TransferReady == 3)
      CheckResults();    
  }
  else
    SSP_Handler_WriteMaster(SSP_MASTER, &cfgDataMaster);  
}

static void TestSSP_SlaveHandleIRQ(void)
{
  if (SSP_Handler_Read(SSP_SLAVE, &cfgDataSlave))
  {
    TransferReady |= 2;
    if (TransferReady == 3)
      CheckResults();    
  }
  else
    SSP_Handler_WriteSlave(SSP_SLAVE, &cfgDataSlave);
}





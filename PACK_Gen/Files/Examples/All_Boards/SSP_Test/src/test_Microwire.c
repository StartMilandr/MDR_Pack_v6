#include "test_SSP_Interfs.h"
#include "SSP_cfg.h"
#include "SSP_CommonFuncs.h"

//===============   ОПИСАНИЕ  ======================
//  Команда посылаемая мастером всегда имеет длину 8 бит. В тесте регулируется длина посылаемых ведомым данных в ответ.
//  Диаграмма обмена показана на картинке в папке проекта Microwire.png.
//  Кнопки:
//    - Up    - Смена теста
//    - Right - Смена длины посылки ведомого
//    - Down  - Запуск передачи-приема слов, количество 65535.
//  Принимаемые данные сравниваются с отправляемыми, количество ошибок выводится на экран LCD.
//  Если ошибок нет выводится Success Transfer

//  LBM Test Interface functions
static void TestSSP_Init(void);
static void TestSSP_Finit(void);
static void TestSSP_Change(void);
static void TestSSP_Exec(void);
static void TestSSP_HandleIRQ(void);


TestInterface TI_SSP_Microwire = {
  .funcInit       = TestSSP_Init,
  .funcFinit      = TestSSP_Finit,
  .funcChange     = TestSSP_Change,
  .funcExec       = TestSSP_Exec,
  .funcHandlerIrqMaster = TestSSP_HandleIRQ,
  .funcHandlerIrqSlave  = TestSSP_HandleIRQ
};

static MDR_SSP_FrameFormat frameFormatForRestore;

static void TestSSP_Init(void)
{
  //  Ограничение на скорость ведомого
  cfgSSP.DivSCR_0_255 = 0;
  if (cfgSSP.DivPSR_2_254 < 12) 
    cfgSSP.DivPSR_2_254 = 12; 
    
  frameFormatForRestore = cfgSSP.FrameFormat;
  cfgSSP.FrameFormat = SSP_Frame_Microwire;
  
  //  Init  Master
  MDR_SSPex_SetSSPClock_InpPLLCPU(SSP_MASTER, MDR_Div128P_div1);
  MDR_SSPex_Init(SSP_MASTER, &cfgSSP);
  MDR_SSPex_EnableMaster(SSP_MASTER, false);
  
  //  Init  Slave
  MDR_SSPex_SetSSPClock_InpPLLCPU(SSP_SLAVE, MDR_Div128P_div1);
  MDR_SSPex_Init(SSP_SLAVE, &cfgSSP);
  MDR_SSPex_EnableSlave(SSP_SLAVE, false);

  LCD_ShowInit(SSP_MASTER, "MCR Bits");
}

static void TestSSP_Finit(void)
{
  MDR_SSPex_DeInit(SSP_MASTER);
  MDR_SSPex_DeInit(SSP_SLAVE);
  
  cfgSSP.FrameFormat = frameFormatForRestore;
}

static void TestSSP_Change(void)
{
  Cfg_NextDataBits();
  MDR_SSPex_ChangeDataBits(SSP_MASTER, cfgSSP.DataBits);
  MDR_SSPex_ChangeDataBits(SSP_SLAVE,  cfgSSP.DataBits);  
  
  LCD_ShowInit(SSP_MASTER, "MCR Bits");
}

static uint32_t Microwire_MasterSlave_TestTransfer(void);

static void TestSSP_Exec(void)
{
  uint32_t errCount = 0;
  
  LCD_ShowStarted();  
  errCount = Microwire_MasterSlave_TestTransfer();
  LCD_ShowResult(errCount);    
}

static void TestSSP_HandleIRQ(void)
{
  // Not Used
}

static uint32_t Microwire_MasterSlave_TestTransfer(void)
{
  uint8_t dataWR_M = 0;
  uint8_t dataRD_S;  
  uint16_t dataRD_M;
  uint16_t dataWR_S = Cfg_DataMaxValue;
  uint32_t errCount = 0;
  uint32_t i;
   
  Cfg_SSP_Master_CapturePins();
  Cfg_SSP_Slave_CapturePins();
  
  for (i = 0; i < TRANSFER_WORD_COUNT; ++i)
  {
    //  Запись слова в FIFO_TX ведомого SSP, будет отправлено при обмене с мастером.
    //  Функция избыточна для данного случая, т.е. ожидать пока в FIFO_TX будет свободное место не надо.
    //  Обмен происходит по одному слову - в буфере всегда будет место.
    //  Но для проверки отработки флагов используется именно эта функция.
    //  Иначе использовать - MDR_SSPex_WriteData(SSP_SLAVE, dataWR_S);
    MDR_SSPex_WaitAndSendData(SSP_SLAVE, dataWR_S);
    
    //  Обмен данными (Передача-прием в обоих SSP)
    dataRD_M = MDR_SSPex_MasterTransfer(SSP_MASTER, dataWR_M);
    
    //  Вычитывание слова из ведомого
    //  Ожидание флага наличия данных в FIFO_RX необязательно в данном случае.
    //  После окончания трансфера в мастере очевидно, что он выставился и в ведомом.
    dataRD_S = (uint8_t)MDR_SSPex_WaitAndReadData(SSP_SLAVE);
    
    if ((dataRD_M != dataWR_S) ||  (dataRD_S != dataWR_M))
      ++errCount;
       
    if (dataWR_M >= 0xFF)
      dataWR_M = 0;
    else
      dataWR_M += 1;
    if (dataWR_S == 0)
      dataWR_S = Cfg_DataMaxValue;
    else  
      dataWR_S -= 1;
  }
  Cfg_SSP_Slave_ReleasePins();
  Cfg_SSP_Master_ReleasePins();
  
  return errCount;
}



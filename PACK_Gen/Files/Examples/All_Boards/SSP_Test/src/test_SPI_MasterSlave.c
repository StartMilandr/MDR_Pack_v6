#include "test_SSP_Interfs.h"
#include "SSP_cfg.h"
#include "SSP_CommonFuncs.h"

//===============   ОПИСАНИЕ  ======================
//  Тест проверяет обмен SPI master-slave при разных значениях делителя PSR
//  Делитель SCR всегда равен 0, делитель PSR увеличивается по нажатию на кнопку Right
//  Все сигналы двух SPI должны быть соединены проводниками на плате.
//  Выводы GPIO этих сигналов инициализируются функциями Cfg_SSP_Master_CapturePins() и Cfg_SSP_Slave_CapturePins()
//  на время проведения обмена. Затем деинициализируются аналогичными функциями с ..._ReleasePins().
//  Это необходимо чтобы не сломать работу LCD экрана на который выводится информация, 
//  поскольку в некоторых платах выводы разведены и на SPI и на LCD.
//  Кнопки:
//    - Up    - Смена теста
//    - Right - Смена режима SPI
//    - Down  - Запуск передачи-приема слов, количество 65535.
//  Принимаемые данные сравниваются с отправляемыми, количество ошибок выводится на экран LCD.
//  Если ошибок нет выводится Success Transfer
//
//  НЕ ЗАПУСКАТЬ этот тест при делителе меньше 12-ти! Частота ведомого должна быть в 12 раз меньше частоты тактирования блока SSP_CLK.
//  Иначе тест зависает, поскольку slave не может детектировать фронты и передать свое слово, поэтому ждет еще фронты с флагом BUSY, не передав слово целиком.
//  При этом функция MDR_SSPex_WaitAndSendData() повиснет в ожидании появления свободного места в FIFO_TX через некоторое количество посылок.


//  LBM Test Interface functions
static void TestSSP_Init(void);
static void TestSSP_Finit(void);
static void TestSSP_ChangeRate(void);
static void TestSSP_Exec(void);
static void TestSSP_HandleIRQ(void);


TestInterface TI_SPI_MasterSlave = {
  .funcInit       = TestSSP_Init,
  .funcFinit      = TestSSP_Finit,
  .funcChange     = TestSSP_ChangeRate,
  .funcExec       = TestSSP_Exec,
  .funcHandlerIrqMaster = TestSSP_HandleIRQ,
  .funcHandlerIrqSlave  = TestSSP_HandleIRQ
};

static void TestSSP_Init(void)
{
  //  Ограничение на скорость ведомого
  cfgSSPex.cfgSSP->DivSCR_0_255 = 0;
  if (cfgSSPex.cfgSSP->DivPSR_2_254 < 12) 
    cfgSSPex.cfgSSP->DivPSR_2_254 = 12;
   
  //  Init  Master
  MDR_SSPex_InitEx(SSP_MASTER, &cfgSSPex);
  MDR_SSPex_EnableMaster(SSP_MASTER, false);
  
  //  Init  Slave
  MDR_SSPex_InitEx(SSP_SLAVE, &cfgSSPex);
  MDR_SSPex_EnableSlave(SSP_SLAVE, false);

  LCD_ShowInit(SSP_MASTER, "Ms-Sl Rate");
}

static void TestSSP_Finit(void)
{
  MDR_SSPex_DeInit(SSP_MASTER);
}

static void TestSSP_ChangeRate(void)
{
  Cfg_NextDIV_PSR_2_254();
  MDR_SSPex_ChangeRate(SSP_MASTER, cfgSSPex.cfgSSP->DivSCR_0_255, cfgSSPex.cfgSSP->DivPSR_2_254);
  LCD_ShowInit(SSP_MASTER, "Ms-Sl Rate");
}

static void TestSSP_Exec(void)
{
  uint32_t errCount = 0;
  
  LCD_ShowStarted();  
  errCount = MasterSlave_TestTransfer();
  LCD_ShowResult(errCount);
}

static void TestSSP_HandleIRQ(void)
{
  // Not Used
}




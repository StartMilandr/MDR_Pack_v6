#include "test_SSP_Interfs.h"
#include "SSP_cfg.h"
#include "SSP_CommonFuncs.h"

//===============   ОПИСАНИЕ  ======================
//  Тест проверяет работу SPI в тестовом режиме передаче данных самому себе - LoopBackMode.
//  Скорость передачи - максимальная для мастера BitRate = SSP_Clock/2
//  Кнопки:
//    - Up    - Смена теста
//    - Right - Смена режима SPI
//    - Down  - Запуск передачи-приема слов, количество 65535.
//  Принимаемые данные сравниваются с отправляемыми, количество ошибок выводится на экран LCD.
//  Если ошибок нет выводится Success Transfer


//  LBM Test Interface functions
static void TestSSP_Init(void);
static void TestSSP_Finit(void);
static void TestSSP_Change(void);
static void TestSSP_Exec(void);
static void TestSSP_HandleIRQ(void);


TestInterface TI_SPI_TXRX = {
  .funcInit       = TestSSP_Init,
  .funcFinit      = TestSSP_Finit,
  .funcChange     = TestSSP_Change,
  .funcExec       = TestSSP_Exec,
  .funcHandlerIrqMaster = TestSSP_HandleIRQ,
  .funcHandlerIrqSlave  = TestSSP_HandleIRQ
};


static void TestSSP_Init(void)
{  
  //  Init
  MDR_SSPex_Init(SSP_MASTER, &cfgSSPex);
  MDR_SSPex_EnableMaster(SSP_MASTER, false);

  LCD_ShowInit(SSP_MASTER, "TX-RX Rate");
}

static void TestSSP_Finit(void)
{
  MDR_SSPex_DeInit(SSP_MASTER);
}

static void TestSSP_Change(void)
{
  Cfg_NextDIV_PSR_2_254();
  MDR_SSPex_ChangeRate(SSP_MASTER, 0, cfgSSPex.cfgSSP->DivPSR_2_254);
  LCD_ShowInit(SSP_MASTER, "TX-RX Rate");
}

static void TestSSP_Exec(void)
{
  uint32_t errCount ;
  
  LCD_ShowStarted();  
  
  Cfg_SSP_Master_CapturePins();
  errCount = MasterTXRX_TestTransfer(SSP_MASTER);   
  Cfg_SSP_Master_ReleasePins();  
  
  LCD_ShowResult(errCount);
}

static void TestSSP_HandleIRQ(void)
{
  // Not Used
}


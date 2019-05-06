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

TestInterface TI_SPI_LBM = {
  .funcInit       = TestSSP_Init,
  .funcFinit      = TestSSP_Finit,
  .funcChange     = TestSSP_Change,
  .funcExec       = TestSSP_Exec,
  .funcHandlerIrqMaster = TestSSP_HandleIRQ,
  .funcHandlerIrqSlave  = TestSSP_HandleIRQ
};

static uint8_t divForRestore;

static void TestSSP_Init(void)
{
  // Сохраняем выбраный общий делитель для всех тестов.
  divForRestore = cfgSSPex.cfgSSP->DivPSR_2_254;
  
  //  Включаем минимальный делитель для получения максимальной скорости
  cfgSSPex.cfgSSP->DivSCR_0_255 = 0;
  cfgSSPex.cfgSSP->DivPSR_2_254 = 2;
  
  //  Init
  MDR_SSPex_InitEx(SSP_MASTER, &cfgSSPex);
  MDR_SSPex_EnableMaster(SSP_MASTER, true);
  
  LCD_ShowInit(SSP_MASTER, "LBM");
}

static void TestSSP_Finit(void)
{
  MDR_SSPex_DeInit(SSP_MASTER);
  // Восстанавливаем делитель в глобальной конфигурации для других тестов
  cfgSSPex.cfgSSP->DivPSR_2_254 = divForRestore;  
}

static void TestSSP_Change(void)
{
  Cfg_NextSPI_Mode();
  MDR_SSPex_ChangeSPIMode(SSP_MASTER, cfgSSPex.cfgSSP->SPI_Mode);
  
  LCD_ShowInit(SSP_MASTER, "LBM");
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


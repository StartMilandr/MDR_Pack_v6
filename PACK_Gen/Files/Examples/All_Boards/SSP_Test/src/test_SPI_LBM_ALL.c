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

TestInterface TI_SPI_LBM_ALL = {
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
  divForRestore = cfgSSP.DivPSR_2_254;
  
  //  Включаем минимальный делитель для получения максимальной скорости
  cfgSSP.DivSCR_0_255 = 0;
  cfgSSP.DivPSR_2_254 = 2;
  
  //  Init
  MDR_SSPex_SetSSPClock_InpPLLCPU(SSP_List[activeIndSSP], MDR_Div128P_div1);  
  MDR_SSPex_Init(SSP_List[activeIndSSP], &cfgSSP);
  MDR_SSPex_EnableMaster(SSP_List[activeIndSSP], true);
  
  LCD_ShowInit(SSP_List[activeIndSSP], "LBM ALL");
}

static void TestSSP_Finit(void)
{
  MDR_SSPex_DeInit(SSP_List[activeIndSSP]);
  // Восстанавливаем делитель в глобальной конфигурации для других тестов
  cfgSSP.DivPSR_2_254 = divForRestore;  
}

static void TestSSP_Change(void)
{
  //  Deinit
  MDR_SSPex_DeInit(SSP_List[activeIndSSP]);
  //  Change Active
  NextIndexSSP();
  //  Init
  MDR_SSPex_SetSSPClock_InpPLLCPU(SSP_List[activeIndSSP], MDR_Div128P_div1);  
  MDR_SSPex_Init(SSP_List[activeIndSSP], &cfgSSP);
  MDR_SSPex_EnableMaster(SSP_List[activeIndSSP], true);  
   
  LCD_ShowInit(SSP_List[activeIndSSP], "LBM ALL");
}

static void TestSSP_Exec(void)
{
  uint32_t errCount ;
  
  LCD_ShowStarted();  

  Cfg_SSP_Master_CapturePins();
  errCount = MasterTXRX_TestTransfer(SSP_List[activeIndSSP]);   
  Cfg_SSP_Master_ReleasePins();  
  
  LCD_ShowResult(errCount);
}

static void TestSSP_HandleIRQ(void)
{
  // Not Used
}


#include "test_SSP_Interfs.h"
#include "SSP_cfg.h"
#include "SSP_CommonFuncs.h"

//===============   ОПИСАНИЕ  ======================
//  В тесте переключаются протоколы обмена - SPI и SSI. Обмен Microwire реализован в отдельном тесте.
//  Кнопки:
//    - Up    - Смена теста
//    - Right - Смена протокола SPI или SSI
//    - Down  - Запуск передачи-приема слов, количество 65535.
//  Принимаемые данные сравниваются с отправляемыми, количество ошибок выводится на экран LCD.
//  Если ошибок нет выводится Success Transfer

//  LBM Test Interface functions
static void TestSSP_Init(void);
static void TestSSP_Finit(void);
static void TestSSP_Change(void);
static void TestSSP_Exec(void);
static void TestSSP_HandleIRQ(void);


TestInterface TI_SSP_Frames = {
  .funcInit       = TestSSP_Init,
  .funcFinit      = TestSSP_Finit,
  .funcChange     = TestSSP_Change,
  .funcExec       = TestSSP_Exec,
  .funcHandlerIrqMaster = TestSSP_HandleIRQ,
  .funcHandlerIrqSlave  = TestSSP_HandleIRQ
};

static void TestSSP_Init(void)
{
  //  Ограничение на скорость ведомого
  cfgSSP.DivSCR_0_255 = 0;
  if (cfgSSP.DivPSR_2_254 < 12) 
    cfgSSP.DivPSR_2_254 = 12; 
    
  //  Init  Master
  MDR_SSPex_Init(SSP_MASTER, &cfgSSP, MDR_Div128P_div1);
  MDR_SSPex_EnableMaster(SSP_MASTER, false);
  
  //  Init  Slave
  MDR_SSPex_Init(SSP_SLAVE, &cfgSSP, MDR_Div128P_div1);
  MDR_SSPex_EnableSlave(SSP_SLAVE, false);

  LCD_ShowInit(SSP_MASTER, "Ms-Sl Frame");
}

static void TestSSP_Finit(void)
{
  MDR_SSPex_DeInit(SSP_MASTER);
  MDR_SSPex_DeInit(SSP_SLAVE);
}

static void TestSSP_Change(void)
{
  Cfg_NextSSP_FrameFormat();
  MDR_SSPex_ChangeFrameFormat(SSP_MASTER, cfgSSP.FrameFormat);
  MDR_SSPex_ChangeFrameFormat(SSP_SLAVE, cfgSSP.FrameFormat);
  
  LCD_ShowInit(SSP_MASTER, "Ms-Sl Frame");
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



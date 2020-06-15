#include <MDR_Config.h>
#include <MDR_RST_Clock.h>
#include <MDR_GPIO.h>
#include <MDR_Timer.h>
#include <MDR_UART_CLI.h>

#include "board_defs.h"

#include "BB3_Ctrl.h"
#include "KX028_Ctrl.h"
#include "ePHY_Ctrl.h"
#include "Reset_Ctrl.h"

#include <MDR_1923KX028_M0_Ctrl.h>
#include <MDR_1923KX028_M0_TransferPC.h>

#include <MDR_1923KX028_M2_Init.h>
#include <MDR_1923KX028_M2_TablesCtrl.h>
#include <MDR_1923KX028_M2_Stats.h>
#include <MDR_1923KX028_Config.h>



//  Сколько Items обрабатывать за один вызвов Learn/Ageing/StatsUpdate
#define TABLES_AGING_CNT_PER_ITERATION   10
#define TABLES_LEARN_CNT_PER_ITERATION   10
#define STATS_UPDATE_ITERATION           1

//  Таймаут ожидании окончания операции, в количествах чтения регистра статуса
#define TABLES_TIMEOUT_READY_READS       100

//  Делители для таймера на 1мс при 144МГц
#define TIM_BRG_144MHZ_TO_1MS 		MDR_Div128P_div32
#define TIM_PSC_144MHZ_TO_1MS 		4000
//  Таймер старения, текущее время берется из Timer->CNT, 
#define TABLE_AGEING_PERIOD_MIN   5
#define TABLE_AGEING_PERIOD_MS    (60 * 1000 * TABLE_AGEING_PERIOD_MIN)
#define AGE_TIMER                 MDR_TIMER2ex

#define STATS_UPDATE_PERIOD_MS    TABLE_AGEING_PERIOD_MS

// Максимальное количество пакетов в очереди которое TMU отдает на HOST. 
// Если придут пакеты при заполненной очереди, то они отбрасываются. (Чтобы хост успевал отрабатывать)
#define HOST_LEARN_QUEUE_LEN    3

#define PORTS_VLAN_FALLBACK     1UL
#define PORTS_CNT_ON_BOARD      3

//  Mode2 Process
static uint32_t ModeM2_InitKX028(void);
static void Mode2_Process(void);
//  Ageing
static void Mode2_ProcessAgeing(uint32_t nowTime, uint32_t ageingPeriod, uint32_t procItemsCount);
//  Statistics
MDR_KX028_StatsEMAC_t    statsEMAC[PORTS_CNT_ON_BOARD];
static void Mode2_ProcessStatsUpdate(uint32_t nowTime, uint32_t processPeriod, uint32_t procItemsCount);

static void Mode0_Process(void);

int main(void)
{
  //  Максимальная скорость тактирования
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDRB_CLK_PLL_HSE_RES_MAX;
  MDR_CPU_SetClock_PLL_HSE(&cfgPLL_HSE, true);
  uint32_t freqCPU_Hz = MDR_CPU_GetFreqHz(true);  
  
  //  Enable Reset 
  ResetCtrlInit();
  ResetApplyAll(MS_TO_DELAY_LOOPS(freqCPU_Hz, RESET_APPLY_DELAY_MS));
  //  ePHY Open
  ePHY_VE1_Init(freqCPU_Hz);
  ePHY_VE1_Open();
  //  SPI Controls Init
  BB3_SPI_Init(); 
  KX028_SPI_Init(freqCPU_Hz);
  
  MDR_1923KX028_Mode modeKX028 = KX028_GetMode();
  switch (modeKX028) {
    case MDR_1923KX028_Mode0_PCIe: 
      Mode0_Process();  
      break;
    case MDR_1923KX028_Mode2_SlaveSPI: 
      Mode2_Process();
      break;
    case MDR_1923KX028_Mode1_ExtFlash: break;    
    case MDR_1923KX028_Mode3_Uncontrolled: break;
  }
  
  while(1)
  {
    // Fault Mode
  }
}


void DelayMs(uint32_t delayMs)
{

}

//===========  MODE0: PC Driver - PCIe Control  ============
static void Mode0_Process(void)
{
  CLI_CMD_e cliCMD;
  uint8_t  cliParamLen;
  uint8_t *pCliParams;
  
  MDR_KX028_M0_WaitPC_DriverReady();
  MDR_KX028_M0_SetupBars();  
  
  while (1)
  {
    MDR_KX028_M0_TransferPC();
    
    cliCMD = MDR_CLI_GetCommand(&cliParamLen, &pCliParams);
    switch (cliCMD) {
      case cliCMD_NONE: break;
      case cliCMD_ERROR: 
        MDR_CLI_SetResponse(cliCMD_ERROR, 0, NULL);
        break;
    }
    
  }
}

//===========  MODE2: - SlaveSPI  ============
static void Mode2_Process(void)
{
  // Таймер старения, отсчет - 1мс
  MDR_Timer_InitPeriod(AGE_TIMER, TIM_BRG_144MHZ_TO_1MS, TIM_PSC_144MHZ_TO_1MS, TIM_MAX_VALUE, false);
	MDR_Timer_Start(AGE_TIMER);  
   
  // Инициализация 1923KX028
  uint32_t usedPortList = ModeM2_InitKX028();  
  MDR_KX028_M2_InitTables(TABLES_TIMEOUT_READY_READS);
  //  User VLAN Init
  MDR_KX028_VLAN_Entry_t  action_entry = {.value = MDR_KX028_VLAN_ENTRY_FILL_FORW_ALL(usedPortList, 0)};  // 0 - untagged port list
  MDR_KX028_VLAN_TableAdd(1, action_entry, TABLES_TIMEOUT_READY_READS);  
  
  //  Process
  while (1)
  {
    //  Старение
    Mode2_ProcessAgeing(AGE_TIMER->TIMERx->CNT, TABLE_AGEING_PERIOD_MS, TABLES_AGING_CNT_PER_ITERATION);  
    //  Обучение
    MDR_KX028_M2_ProcessTablesLearning(TABLES_LEARN_CNT_PER_ITERATION, TABLES_TIMEOUT_READY_READS, usedPortList);
    //  Статистика
    Mode2_ProcessStatsUpdate(AGE_TIMER->TIMERx->CNT, STATS_UPDATE_PERIOD_MS, STATS_UPDATE_ITERATION);
  }
}


static uint32_t ModeM2_InitKX028(void)
{
  MDR_KX028_InitEMAC_MII_FD_100M_def(KX028_EMAC1);
  MDR_KX028_InitEMAC_MII_FD_100M_def(KX028_EMAC2);
  MDR_KX028_InitEMAC_SGMII_FD_1G_def(KX028_EMAC3);
  //MDR_KX028_InitEMAC_SGMII_FD_1G_def(KX028_EMAC4); - TODO?
  
  MDR_KX028_EMAC_e emac;
  for (emac = KX028_EMAC4; emac < KX028_EMAC_NUMS; ++emac)
    MDR_KX028_InitEMAC_None(emac);
  
  for (emac = KX028_EMAC1; emac < KX028_EMAC_NUMS; ++emac)
  {
    MDR_KX028_InitPortStruct(emac, KX028_PORTS_STRUC1_DEF(PORTS_VLAN_FALLBACK), KX028_PORTS_STRUC2_DEF);
  }  
  
  MDR_KX028_InitBMU_GPI_TMU_CLASS(DelayMs);
  //MDR_KX028_InitBMU_GPI_TMU_CLASS_ex(); - extra init from demoBoard  
  MDR_KX028_M2_HostPort_InitTailDrop(HOST_LEARN_QUEUE_LEN, TABLES_TIMEOUT_READY_READS);
  
  MDR_KX028_EnableBlocks();
  
  return (1 << KX028_EMAC1) | (1 << KX028_EMAC2) | (1 << KX028_EMAC3); // Mask of used Ports
}

static void Mode2_ProcessAgeing(uint32_t nowTime, uint32_t ageingPeriod, uint32_t procItemsCount)
{
  static uint16_t activeHashAddr = 0;  
  static int32_t  cntToProcess = 0;
  static uint32_t lastStart = 0;
  int32_t  cntItems;
  
  //  Start ageing
  if ((nowTime - lastStart) > ageingPeriod) 
  {
    lastStart = nowTime;
    cntToProcess = MDR_KX028_MAC_TABLE_LEN;
  }  
  
  //  Process ageing
  if (cntToProcess > 0) 
  {
    cntItems = cntToProcess - procItemsCount;
    if (cntItems < 0)
      cntItems = procItemsCount - cntToProcess;
    
    activeHashAddr = MDR_KX028_M2_ProcessTablesAgeing(cntItems, activeHashAddr, TABLES_TIMEOUT_READY_READS);       
    cntToProcess -= cntItems;
  }  
}

static void Mode2_ProcessStatsUpdate(uint32_t nowTime, uint32_t processPeriod, uint32_t procItemsCount)
{
  static MDR_KX028_EMAC_e activeEMAC = KX028_EMAC1;
  static int32_t  cntToProcess = 0;
  static uint32_t lastStart = 0;
  int32_t  cntItems;

  //  Start processing
  if ((nowTime - lastStart) > processPeriod) 
  {
    lastStart = nowTime;
    cntToProcess = PORTS_CNT_ON_BOARD;
  }  

  //  Processing
  if (cntToProcess > 0) 
  {
    cntItems = cntToProcess - procItemsCount;
    if (cntItems < 0)
      cntItems = procItemsCount - cntToProcess;
      
    activeEMAC = MDR_KX028_M2_UpdateStatNextEMACs(cntItems, activeEMAC, PORTS_CNT_ON_BOARD, &(statsEMAC[activeEMAC]));    
    cntToProcess -= cntItems;
  }  
}

void CLI_Init(uint32_t freqCPU_Hz)
{
  MDR_UART_CfgPinGPIO _pinUartTX = {MDR_GPIO_C, CLI_UART_TX, CLI_UART_TX_FUNC};
  MDR_UART_CfgPinGPIO _pinUartRX = {MDR_GPIO_C, CLI_UART_RX, CLI_UART_RX_FUNC};  
	MDR_UART_CfgPinsGPIO pinsGPIO = {
		.pPinTX = &_pinUartTX,
    .pPinRX = &_pinUartRX,	
	};

  MDR_CLI_UART_Init(0, freqCPU_Hz, &pinsGPIO);  
}


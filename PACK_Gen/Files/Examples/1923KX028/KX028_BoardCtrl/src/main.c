#include <MDR_RST_Clock.h>
#include <MDR_PER_Clock.h>

//#include <stdio.h>
#include <MDR_Funcs.h>
#include "BasisCfg.h"
#include <MDR_BKP_RTC.h>
#include <MDR_RTC_Cfg1.h>


//#include <MDR_Config.h>
//#include <MDR_RST_Clock.h>
//#include <MDR_GPIO.h>
#include <MDR_Timer.h>
#include <MDR_UART.h>
#include <MDR_SN74HC595D_ShiftReg.h>

#include <MDR_1923KX028_M2_Init.h>
#include <MDR_1923KX028_M2_Ctrl.h>
#include <MDR_1923KX028_M2_Stats.h>
#include <MDR_1923KX028_Config.h>

#include "KX028_Ctrl.h"
#include "KX028_CLI.h"


#define PORTS_VLAN_FALLBACK     1UL
// Максимальное количество пакетов в очереди которое TMU отдает на HOST. 
// Если придут пакеты при заполненной очереди, то они отбрасываются. (Чтобы хост успевал отрабатывать)
#define HOST_LEARN_QUEUE_LEN    3


//  ShifterReg - PHYs reset control
#define MDR_SN74HC595D_CLK_US         10
#define PHYs_RESET_TIME_US            10
#define SHIFTER_CLK_DELAY(cpuFreq)    US_TO_DELAY_LOOPS(MDR_SN74HC595D_CLK_US, cpuFreq)
#define RESET_DELAY(cpuFreq)          US_TO_DELAY_LOOPS(PHYs_RESET_TIME_US, cpuFreq)

#define PHYs_Reset_PinsInit           MDR_SN74HC595D_PinsInid

//  PLL
#define HSE_PLL_MUL_MAX              MDR_x10   //  HSE_max = 8MHz * 10 = 80MHz
#define HSE_LOW_SELRI_MAX            MDR_LOWRI_gt80MHz
#define HSE_EEPROM_DELAY_MAX         EEPROM_Delay_le100MHz

#define MDRB_CLK_PLL_HSE_RES_MAX     MDR_CPU_CFG_PLL_HSE_RES_DEF(HSE_PLL_MUL_MAX, HSE_EEPROM_DELAY_MAX, HSE_LOW_SELRI_MAX)

////  Ageing timer
//#define AGE_TIMER               MDR_TIMER2ex
//  //  Делители для таймера на 1мс при 80МГц
//#define TIM_BRG_80MHZ_TO_1MS 		MDR_Div128P_div32
//#define TIM_PSC_80MHZ_TO_1MS 		4000
//  //  Таймер старения, текущее время берется из Timer->CNT, 
//#define TABLE_AGEING_PERIOD_MIN   5
//#define TABLE_AGEING_PERIOD_MS    (60 * 1000 * TABLE_AGEING_PERIOD_MIN)

#define STATS_UPDATE_PERIOD_S            10
#define STATS_UPDATE_PER_ITERATION       1

//  Ports Mask
#define SEL_USED_EMACs    0xFFFFUL

//  Таймаут ожидания окончания операции, в количествах чтения регистра статуса
#define TABLES_TIMEOUT_READY_READS       20


MDR_KX028_StatsEMAC_t    statsEMAC[ KX028_EMAC_NUMS ];
uint32_t nowTime_sec = 0;
static uint32_t _delayMs;

//  Functions
static void Mode2_Process(uint32_t freqCPU_Hz);
static void PHYs_Reset(uint32_t shiftClkTicks, uint32_t resetTicks);
static void Mode2_ProcessStatsUpdate(uint32_t nowTime, uint32_t processPeriod, uint32_t procItemsCount, uint32_t usedPortList);
static uint32_t ModeM2_InitKX028(void);

//  Statistics
MDR_KX028_StatsEMAC_t     statsEMAC[KX028_EMAC_PORT_COUNT];
MDR_KX028_StatsEMAC_Item  statsTableEmac[KX028_EMAC_PORT_COUNT] = {
  {.eMAC = KX028_EMAC1, .pStatBuff = &statsEMAC[0]},
  {.eMAC = KX028_EMAC2, .pStatBuff = &statsEMAC[1]},
  {.eMAC = KX028_EMAC3, .pStatBuff = &statsEMAC[2]},
  {.eMAC = KX028_EMAC4, .pStatBuff = &statsEMAC[3]},
  {.eMAC = KX028_EMAC5, .pStatBuff = &statsEMAC[4]},
  {.eMAC = KX028_EMAC6, .pStatBuff = &statsEMAC[5]},
  {.eMAC = KX028_EMAC7, .pStatBuff = &statsEMAC[6]},
  {.eMAC = KX028_EMAC8, .pStatBuff = &statsEMAC[7]},
  {.eMAC = KX028_EMAC9, .pStatBuff = &statsEMAC[8]},
  {.eMAC = KX028_EMAC10, .pStatBuff = &statsEMAC[9]},
  {.eMAC = KX028_EMAC11, .pStatBuff = &statsEMAC[10]},
  {.eMAC = KX028_EMAC12, .pStatBuff = &statsEMAC[11]},
  {.eMAC = KX028_EMAC13, .pStatBuff = &statsEMAC[12]},
  {.eMAC = KX028_EMAC14, .pStatBuff = &statsEMAC[13]},
  {.eMAC = KX028_EMAC15, .pStatBuff = &statsEMAC[14]},
  {.eMAC = KX028_EMAC16, .pStatBuff = &statsEMAC[15]},
};


int main(void)
{ 
  MDR_DebugerProtectDelay();
  
  //  Максимальная скорость тактирования
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDRB_CLK_PLL_HSE_RES_MAX;
  MDR_CPU_SetClock_PLL_HSE(&cfgPLL_HSE, true);
  uint32_t freqCPU_Hz = MDR_CPU_GetFreqHz(true);
  _delayMs = MS_TO_DELAY_LOOPS(1, freqCPU_Hz);
   
  //  Reset Phy
  PHYs_Reset_PinsInit();
  PHYs_Reset(SHIFTER_CLK_DELAY(freqCPU_Hz), RESET_DELAY(freqCPU_Hz));
     
 
  MDR_1923KX028_Mode modeKX028 = KX028_GetMode();
  switch (modeKX028) {
    case MDR_1923KX028_Mode0_PCIe: 
      //Mode0_Process(freqCPU_Hz);  
      break;
    case MDR_1923KX028_Mode2_SlaveSPI: 
      Mode2_Process(freqCPU_Hz);
      break;
    case MDR_1923KX028_Mode1_ExtFlash: break;    
    case MDR_1923KX028_Mode3_Uncontrolled: break;
  }
  
  while (1)
  {
    // WrongMode
  }
}

//static void AXI_DebugSPI(void)
//{
//  bool doRead = false;  
//  uint32_t regAddr = AXI_CLASS_HW1_BASE_ADDR + AXI_CLASS_PORT0_STRUC1;
//  volatile uint32_t regValue;
//  while (1)  
//  {
//    //if (doRead)
//      regValue = MDR_KX028_ReadAXI(regAddr);
//  }  
//}

static void Mode2_Process(uint32_t freqCPU_Hz)
{ 
  // Инициализация 1923KX028
  uint32_t usedPortList = ModeM2_InitKX028();  
  
//AXI_DebugSPI();  
  
  MDR_KX028_M2_InitTables(TABLES_TIMEOUT_READY_READS);
  //  User VLAN Init
  MDR_KX028_VLAN_Entry_t  action_entry = {.value = MDR_KX028_VLAN_ENTRY_FILL_FORW_ALL(usedPortList, 0)};  // 0 - untagged port list
  MDR_KX028_VLAN_TableAdd(1, action_entry, TABLES_TIMEOUT_READY_READS);  
  //  CLI
  KX028_InitCLI(UART_BAUD_115200, freqCPU_Hz);
  
  // Таймер старения, отсчет - 1мс
  //  MDR_Timer_InitPeriod(AGE_TIMER, TIM_BRG_80MHZ_TO_1MS, TIM_PSC_80MHZ_TO_1MS, TIM_MAX_VALUE, false);    
  //	MDR_Timer_Start(AGE_TIMER); 
  MDR_RTC_CfgRegs cfgRegs = RTCCFG1_CFG_REGS_FILL;
  MDR_RTC_Init(&cfgRegs, RTCCFG1_DIV_TO_1HZ, 0);
  
  while (1)
  {
    //  Статистика
    nowTime_sec = MDR_RTC_GetTime();
    Mode2_ProcessStatsUpdate(nowTime_sec, STATS_UPDATE_PERIOD_S, STATS_UPDATE_PER_ITERATION, usedPortList);
    //  Команды с COM порта
    KX028_ProcessCLI(TABLES_TIMEOUT_READY_READS); 
  }
}

static void PHYs_Reset(uint32_t shiftClkTicks, uint32_t resetTicks)
{
  MDR_SN74HC595D_OutputZero(shiftClkTicks);
  MDR_Delay(resetTicks);
  MDR_SN74HC595D_SetShiftValue(0xFFFF, shiftClkTicks);
}

//static void Mode2_ProcessStatsUpdate(uint32_t nowTime, uint32_t processPeriod, uint32_t procItemsCount, uint32_t usedPortList)
//{
//  static MDR_KX028_EMAC_e activeEMAC = KX028_EMAC1;
//  static int32_t  cntToProcess = 0;
//  static uint32_t lastStart = 0;
//  int32_t  cntItems;

//  //  Start processing
//  if ((nowTime - lastStart) > processPeriod) 
//  {
//    lastStart = nowTime;
//    cntToProcess = KX028_EMAC_PORT_COUNT + 1;
//  }  

//  //  Processing
//  if (cntToProcess > 0) 
//  {
//    if (cntToProcess <= KX028_EMAC_PORT_COUNT)
//    {
//      cntItems = cntToProcess - procItemsCount;
//      if (cntItems < 0)
//        cntItems = procItemsCount - cntToProcess;
//        
//      activeEMAC = MDR_KX028_M2_UpdateStatNextEMACs(cntItems, activeEMAC, KX028_EMAC_PORT_COUNT, &(statsEMAC[activeEMAC]));    
//      cntToProcess -= cntItems;
//    }
//    else
//    {
//      MDR_KX028_M2_UpdateStatsClassHW(usedPortList);
//      cntToProcess--;
//    }

//  }  
//}

static void Mode2_ProcessStatsUpdate(uint32_t nowTime, uint32_t processPeriod, uint32_t procItemsCount, uint32_t usedPortSel)
{
  static uint8_t nextItemEmac = 0;
  static int32_t  cntToProcess = 0;
  static uint32_t lastStart = 0;
  int32_t  cntItems;

  //  Start processing
  if ( ((nowTime - lastStart) > processPeriod) && (cntToProcess ==0) )
  {
    lastStart = nowTime;
    cntToProcess = KX028_EMAC_PORT_COUNT + 1;
  }  

  //  Processing
  if (cntToProcess > 0) 
  {
    if (cntToProcess <= KX028_EMAC_PORT_COUNT)
    {
      if (procItemsCount <= cntToProcess)        
        cntItems = procItemsCount;
      else
        cntItems = cntToProcess;
        
      MDR_KX028_M2_UpdateStatNextEMACs(statsTableEmac, KX028_EMAC_PORT_COUNT, cntItems, &nextItemEmac);          
      cntToProcess -= cntItems;
    }
    else
    {
      MDR_KX028_M2_UpdateStatsClassHW(usedPortSel);
      cntToProcess--;
    }
  }
}

void DelayMs(uint32_t delayMs)
{
  MDR_Delay(_delayMs);
}

//static uint32_t ModeM2_InitKX028(uint32_t freqCPU_Hz)
//{
//  //  SPI Controls Init
//  //BB3_SPI_Init(); 
//  KX028_SPI_Init(freqCPU_Hz);
//  
//  //  KX028 Init
////  MDR_KX028_InitEMAC_MII_FD_100M_def(KX028_EMAC1);
////  MDR_KX028_InitEMAC_MII_FD_100M_def(KX028_EMAC2);
////  MDR_KX028_InitEMAC_SGMII_FD_1G_def(KX028_EMAC3);
////  //MDR_KX028_InitEMAC_SGMII_FD_1G_def(KX028_EMAC4); - TODO?
////  
//  MDR_KX028_EMAC_e emac;
////  for (emac = KX028_EMAC4; emac < KX028_EMAC_NUMS; ++emac)
////    MDR_KX028_InitEMAC_None(emac);
//  
//  for (emac = KX028_EMAC1; emac < KX028_EMAC_NUMS; ++emac)
//  {
//    MDR_KX028_InitEMAC_MII_FD_100M_def(KX028_EMAC1);
//    MDR_KX028_WritePortStruct(emac, KX028_PORTS_STRUC1_DEF(PORTS_VLAN_FALLBACK), KX028_PORTS_STRUC2_DEF);
//  }  
//  
//  MDR_KX028_InitBMU_GPI_TMU_CLASS(DelayMs);
//  //MDR_KX028_InitBMU_GPI_TMU_CLASS_ex(); - extra init from demoBoard  
//  MDR_KX028_M2_HostPort_InitTailDrop(HOST_LEARN_QUEUE_LEN, TABLES_TIMEOUT_READY_READS);
//  
//  MDR_KX028_EnableBlocks();
//  
//  //return (1 << KX028_EMAC1) | (1 << KX028_EMAC2) | (1 << KX028_EMAC3); // Mask of used Ports
//  return SEL_USED_EMACs;
//}

static uint32_t ModeM2_InitKX028(void)
{   
  uint32_t selEMACs = MDR_KX028_InitAll(DelayMs);
  
  //  Tail Drop for LearningHost
#if USE_TAIL_DROP  
  #if CFG_LEANR_BY_EMAC  
    MDR_KX028_M2_TMU_InitTailDropGPI(CFG_LEARN_EGPI, HOST_LEARN_QUEUE_LEN, TABLES_TIMEOUT_READY_READS);
  #else
    MDR_KX028_M2_HostPort_InitTailDrop(HOST_LEARN_QUEUE_LEN, TABLES_TIMEOUT_READY_READS);  
  #endif  
#endif
  
  //  Set Blocks Enable
  MDR_KX028_EnableBlocks();
  
  //  Init ePhy MDIO
#if USE_ePHY_MDIO  
  MDR_KX028_InitEMAC_MII_FD_100M_def(KX028_EMAC1);  // for MDIO  
  MDR_KX028_MDIO_Init(emac, KX028_MDC_Div96);
  
//  uint32_t delayTicksMDIO = MS_TO_DELAY_LOOPS(10, freqCPU_Hz);  
//  EMAC_MII_PhyInit_100FD_AUTO(KX028_EMAC1, KX028_MDC_Div96, EPHY_PHY_ADDR, delayTicksMDIO);
#endif
  
  return selEMACs; // Mask of used Ports
}

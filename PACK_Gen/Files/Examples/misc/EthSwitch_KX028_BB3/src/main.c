#include <MDR_Config.h>
#include <MDR_RST_Clock.h>
#include <MDR_GPIO.h>
#include <MDR_Timer.h>
#include "board_defs.h"

#include "BB3_Ctrl.h"
#include "KX028_Ctrl.h"
#include "ePHY_Ctrl.h"
#include "Reset_Ctrl.h"

#include <MDR_1923KX028_M2_Init.h>
#include <MDR_1923KX028_M2_TablesCtrl.h>
#include <MDR_1923KX028_Config.h>

//  Table Processing
#define TABLES_AGING_CNT_PER_ITERATION   10 // MDR_KX028_MAC_TABLE_LEN
#define TABLES_LEARN_CNT_PER_ITERATION   10
//  Таймаут ожидании окончания операции, в количествах чтения регистра статуса
#define TABLES_TIMEOUT_READY_READS       100

//  Делители для таймера на 1мс при 144МГц
#define TIM_BRG_144MHZ_TO_1MS 		MDR_Div128P_div32
#define TIM_PSC_144MHZ_TO_1MS 		4000
//  Таймер старения, текущее время берется из Timer->CNT, 
#define TABLE_AGEING_PERIOD_MS    10
#define TIM_AGEING_BRG            TIM_BRG_144MHZ_TO_1MS
#define TIM_AGEING_PSC 		        TABLE_AGEING_PERIOD_MS * TIM_PSC_144MHZ_TO_1MS
#define AGE_TIMER                 MDR_TIMER2ex


#define PORTS_VLAN_FALLBACK     1UL
#define BOARD_USED_PORT_LIST    0x7

static void ModeM2_InitKX028(void);
static void Mode2_Process(void);
static void Mode2_ProcessAgeing(uint32_t nowTime, uint32_t ageingPeriod);

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
    case MDR_1923KX028_Mode0_PCIe: break;
    case MDR_1923KX028_Mode1_ExtFlash: break;
    case MDR_1923KX028_Mode2_SlaveSPI: 
      Mode2_Process();
      break;
    case MDR_1923KX028_Mode3_Uncontrolled: break;
  }
  
  while(1)
  {
    // Fault Mode
  }
}

static void Mode2_Process(void)
{
  // Таймер старения
  MDR_Timer_InitPeriod(AGE_TIMER, TIM_AGEING_BRG, TIM_AGEING_PSC, TIM_MAX_VALUE, false);
	MDR_Timer_Start(AGE_TIMER);  
   
  // Инициализация 1923KX028
  ModeM2_InitKX028();  
  MDR_KX028_M2_InitTables(TABLES_TIMEOUT_READY_READS);
  
  //  Process
  while (1)
  {
    //  Старение
    Mode2_ProcessAgeing(AGE_TIMER->TIMERx->CNT, TABLE_AGEING_PERIOD_MS);  
    //  Обучение
    MDR_KX028_M2_ProcessTablesLearning(TABLES_LEARN_CNT_PER_ITERATION, TABLES_TIMEOUT_READY_READS, BOARD_USED_PORT_LIST);
  }
}

void DelayMs(uint32_t delayMs)
{

}

static void ModeM2_InitKX028(void)
{
  MDR_KX028_InitEMAC_MII_FD_100M_def(KX028_EMAC1);
  MDR_KX028_InitEMAC_MII_FD_100M_def(KX028_EMAC2);
  MDR_KX028_InitEMAC_SGMII_FD_1G_def(KX028_EMAC3);
  //MDR_KX028_InitEMAC_SGMII_FD_1G_def(KX028_EMAC4); - TODO
  
  MDR_KX028_EMAC_e emac;
  for (emac = KX028_EMAC4; emac < KX028_EMAC_NUMS; ++emac)
    MDR_KX028_InitEMAC_None(emac);
  
  for (emac = KX028_EMAC4; emac < KX028_EMAC_NUMS; ++emac)
  {
    MDR_KX028_InitPortStruct(emac, KX028_PORTS_STRUC1_DEF(PORTS_VLAN_FALLBACK), KX028_PORTS_STRUC2_DEF);
  }  
  
  MDR_KX028_InitBMU_GPI_TMU_CLASS(DelayMs);
  MDR_KX028_EnableBlocks();
}

static void Mode2_ProcessAgeing(uint32_t nowTime, uint32_t ageingPeriod)
{
  int32_t  cntToAgeing = 0;
  int32_t  cntItems;
  uint32_t lastStart;
  
  //  Start ageing
  if ((nowTime - lastStart) > ageingPeriod)  
  {
    lastStart = nowTime;
    cntToAgeing = MDR_KX028_MAC_TABLE_LEN;
  }  
  
  //  Process ageing
  if (cntToAgeing > 0) 
  {
    cntItems = cntToAgeing - TABLES_AGING_CNT_PER_ITERATION;
    if (cntItems < 0)
      cntItems = TABLES_AGING_CNT_PER_ITERATION - cntToAgeing;
    MDR_KX028_M2_ProcessTablesAgeing(cntItems, TABLES_TIMEOUT_READY_READS);
    cntToAgeing -= cntItems;
  }
}




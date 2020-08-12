#include <MDR_RST_Clock.h>
#include <MDR_PER_Clock.h>

#include <MDR_SoftI2C_ByTimer.h>
#include <MDRB_UART_Debug.h>
#include <stdio.h>
#include <MDR_SFP_PresenceCtrl.h>
#include "BasisCfg.h"

#define I2C_FREQ_HZ      1000
#define I2C_TO_TIM_HZ    4
#define I2C_USE_RESTART  false

// MASTER: Timer and pins select
#define I2C_TIMER_M     MDR_TIMER1ex
#define I2C_TIMER_M_CH  MDR_TIMER1_CH1

static const MDR_I2C_CfgPinGPIO _pinSCL_I2C = {MDR_GPIO_C, 0, MDR_PIN_PORT}; //  PC0_ALT
static const MDR_I2C_CfgPinGPIO _pinSDA_I2C = {MDR_GPIO_C, 1, MDR_PIN_PORT}; //  PC1_ALT
static const MDR_I2C_CfgPinsGPIO pinsGPIO_I2C = {
    .pPinSCL = &_pinSCL_I2C,
    .pPinSDA = &_pinSDA_I2C,
};  

MDR_I2Cst_MasterObj   masterI2C;

#define HSE_PLL_MUL_MAX         MDR_x10   //  HSE_max = 8MHz * 10 = 80MHz
#define HSE_LOW_SELRI_MAX       MDR_LOWRI_gt80MHz
#define HSE_EEPROM_DELAY_MAX    EEPROM_Delay_le100MHz

#define MDRB_CLK_PLL_HSE_RES_MAX     MDR_CPU_CFG_PLL_HSE_RES_DEF(HSE_PLL_MUL_MAX, HSE_EEPROM_DELAY_MAX, HSE_LOW_SELRI_MAX)

uint8_t  InfoBuffSFP[SFP_COUNT * CFG_SFP_ITEMS_TABLE_LEN];
uint8_t  *pInfoSFP[SFP_COUNT];
static const uint8_t SFP_toMUX[SFP_COUNT] = {SFP_MUX_X1_1, SFP_MUX_X1_2, SFP_MUX_X8_1, SFP_MUX_X8_2};

void ResetMuxI2C(void);
void InitResetMuxI2C(void);

void ShowInfoSPF(uint32_t indSFP);
void ShowInfoSPFex(uint32_t indSFP, uint32_t indInfo, uint8_t *rdData);  
void ShowDisconected(uint32_t indSFP);
void InfoTableInit(void);

int main(void)
{ 
  MDR_DebugerProtectDelay();
  
  //  Максимальная скорость тактирования
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDRB_CLK_PLL_HSE_RES_MAX;
  MDR_CPU_SetClock_PLL_HSE(&cfgPLL_HSE, true);
  
  //  Вывод информации от SFP на UART
  MDR_UART_DBG_Init(true);
  
  //  Reset Phy
  PhyResetPinsInit();
  vResetPhys();
  
  //  PresenceBit 
  SFP_PresencePinsInit();
  InfoTableInit();

  // ====  Инициализация I2C - Master  ====
  MDR_I2Cs_MasterInitCfg cfgI2C_Mst;
  //  Timer
  cfgI2C_Mst.timerEx = I2C_TIMER_M;
  cfgI2C_Mst.timerCh_PWM = I2C_TIMER_M_CH;
  cfgI2C_Mst.timClockBRG = MDR_Div128P_div1;  
  uint32_t freqCPU_Hz = MDR_CPU_GetFreqHz(true);  
  MDR_Timer_CalcPeriodAndPSG_F(I2C_FREQ_HZ * I2C_TO_TIM_HZ, freqCPU_Hz, &cfgI2C_Mst.timPeriod, &cfgI2C_Mst.timClockPSG);
  //  Pins
  cfgI2C_Mst.pinsCfg = &pinsGPIO_I2C;
  cfgI2C_Mst.pinsPower = MDR_PIN_FAST;
  cfgI2C_Mst.pullUpPins = true;
  
  masterI2C = MDR_I2Cst_InitMasterSoft(&cfgI2C_Mst); 
  
  // ===== Инициализация опроса SFP =========== 
  MDR_SFP_PresCtrl_Cfg presCfg = {
    .pMasterI2C = &masterI2C,
    .GetPresenceMaskFunc = SFP_PresenceGetMask,
    .pPresenceMask = SFP_PinSel,
    .OnConnected = ShowInfoSPF,
    .OnDisconnected = ShowDisconected,
    .countSFP = SFP_COUNT,
    .pInfoSFP = pInfoSFP,
    .useRestart = I2C_USE_RESTART};

  MDR_SFP_PresCtrl_MuxI2C_Cfg muxCfg = {
    .muxAddr = I2C_ADDR_MUX,
    .pIndToMux = SFP_toMUX}; 
  
  MDR_SFP_PresCtrlInit(&presCfg, &muxCfg);
    
  uint32_t eventCount = 0;
    
  while (1)
  {
    if (MDR_SFP_PresCtrl_Process())
      eventCount++;      
  }
}

void TIMER1_IRQHandler(void)
{
  MDR_I2Cst_MasterHandlerIRQ_Soft(&masterI2C);
}

const char *SFP_Names[SFP_COUNT] = {"SFP_X1_1", "SFP_X1_2", "SFP_X8_1", "SFP_X8_2"};

void ShowInfoSPF(uint32_t indSFP)
{
  printf("========  Connected %s ======== \n", SFP_Names[indSFP]);
  uint32_t i;
  uint8_t *infoSFP = pInfoSFP[indSFP];
  for (i = 0; i < CFG_SFP_ITEMS_CNT; i++)
  {
    ShowInfoSPFex(indSFP, i, &infoSFP[MDR_ReadSFP_GetInfoItemOffset(i)]); 
  }
}

void ShowInfoSPFex(uint32_t indSFP, uint32_t indInfo, uint8_t *rdData)
{ 
  uint8_t i;
  printf("A%2d_%9s: ", MDR_SFP_InfoItems[indInfo].addr, MDR_SFP_InfoItems[indInfo].name);
  for (i = 0 ; i < MDR_SFP_InfoItems[indInfo].len; ++i )
    printf("%x ", rdData[i]); 
  printf("\n"); 
}


void ShowDisconected(uint32_t indSFP)
{
  printf("--------  Disconected %s -------- \n", SFP_Names[indSFP]);
}

void InfoTableInit(void)
{
  uint32_t i;
  uint32_t cnt  = SFP_COUNT * CFG_SFP_ITEMS_TABLE_LEN;
  for (i = 0; i < cnt; i++)
    InfoBuffSFP[i] = 2;  

  pInfoSFP[0] = InfoBuffSFP;
  for (i = 0; i < SFP_COUNT; i++)
    pInfoSFP[i] = &(InfoBuffSFP[i * CFG_SFP_ITEMS_TABLE_LEN]);
}


#define RESET_PIN_IND   2

void ResetMuxI2C(void)
{
  MDR_Port_ClearPins(MDR_GPIO_C->PORTx, 1 << RESET_PIN_IND);
  MDR_Delay(1000);
  MDR_Port_SetPins(MDR_GPIO_C->PORTx, 1 << RESET_PIN_IND);
}

void InitResetMuxI2C(void)
{    
  MDR_GPIO_Enable(MDR_GPIO_C); 
  MDR_Port_InitPin_PortOUT(MDR_GPIO_C->PORTx, RESET_PIN_IND, MDR_PIN_FAST);
  ResetMuxI2C();
}





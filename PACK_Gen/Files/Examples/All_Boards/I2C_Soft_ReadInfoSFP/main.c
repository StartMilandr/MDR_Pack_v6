#include <MDR_RST_Clock.h>

#include <MDR_SoftI2C_ByTimer.h>
#include <MDRB_UART_Debug.h>
#include <MDRB_Buttons.h>
#include <stdio.h>
#include "MDR_SFP_Config.h"
#include "MDR_SFP_ReadInfo.h"

#define BTN_DEBOUNCE_MS 10

#define  I2C_FREQ_HZ      10000
#define  I2C_TO_TIM_HZ    4
#define  I2C_RESTART_EN   false

#define I2C_TIMER_M     MDR_TIMER1ex
#define I2C_TIMER_M_CH  MDR_TIMER1_CH1

static const MDR_I2C_CfgPinGPIO _pinSCL_I2C = {MDR_GPIO_C, 11, MDR_PIN_PORT}; // BE2 - MOD1
static const MDR_I2C_CfgPinGPIO _pinSDA_I2C = {MDR_GPIO_C,  9, MDR_PIN_PORT}; // BE0 - MOD2
static const MDR_I2C_CfgPinsGPIO pinsGPIO_I2C = {
    .pPinSCL = &_pinSCL_I2C,
    .pPinSDA = &_pinSDA_I2C,
};  

MDR_I2Cst_MasterObj   masterI2C;
uint8_t infoSFP[CFG_SFP_ITEMS_TABLE_LEN];

void TIMER1_IRQHandler(void);
void ShowInfoItemSPF(uint32_t indInfo, uint8_t *rdData);
void ShowInfoSPF(void);

int main(void)
{ 
  //  Максимальная скорость тактирования
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDRB_CLK_PLL_HSE_RES_MAX;
  MDR_CPU_SetClock_PLL_HSE(&cfgPLL_HSE, true);
  
  //  Инициализация кнопок
  uint32_t freqCPU_Hz = MDR_CPU_GetFreqHz(true);
  MDRB_Buttons_Init(BTN_DEBOUNCE_MS, freqCPU_Hz);
  
  //  Вывод информации от SFP на UART
  MDR_UART_DBG_Init(true);
    
  // ====  Инициализация I2C - Master  ====
  MDR_I2Cs_MasterInitCfg cfgI2C_Mst;
  //  Timer
  cfgI2C_Mst.timerEx = I2C_TIMER_M;
  cfgI2C_Mst.timerCh_PWM = I2C_TIMER_M_CH;
  cfgI2C_Mst.timClockBRG = MDR_Div128P_div1;  
  MDR_Timer_CalcPeriodAndPSG_F(I2C_FREQ_HZ * I2C_TO_TIM_HZ, freqCPU_Hz, &cfgI2C_Mst.timPeriod, &cfgI2C_Mst.timClockPSG);
  //  Pins
  cfgI2C_Mst.pinsCfg = &pinsGPIO_I2C;
  cfgI2C_Mst.pinsPower = MDR_PIN_FAST;
  cfgI2C_Mst.pullUpPins = true;
  
  masterI2C = MDR_I2Cst_InitMasterSoft(&cfgI2C_Mst);   
  
  if (!MDR_ReadSFP_Init())
  {
    printf("Wrong Items Length table!\n"); 
    while (1);
  }
  
  bool readStarted = false;  
  while (1)
  {
    if (MDRB_BntClicked_Up(true))
    {
      uint32_t i;
      for (i = 0; i < CFG_SFP_ITEMS_TABLE_LEN; i++)
        infoSFP[i] = 2; // fill with some char
      readStarted = MDR_ReadSFP_Start(&masterI2C, infoSFP, I2C_RESTART_EN);
    }
    
    if (readStarted)
      if (MDR_ReadSFP_ProcessCompleted())
      {
        readStarted = false;
        ShowInfoSPF();
      }    
  } 
}

void TIMER1_IRQHandler(void)
{
  MDR_I2Cst_MasterHandlerIRQ_Soft(&masterI2C);
}

void ShowInfoItemSPF(uint32_t indInfo, uint8_t *rdData)
{ 
  uint8_t i;
  printf("A%2d_%9s: ", MDR_SFP_InfoItems[indInfo].addr, MDR_SFP_InfoItems[indInfo].name);
  for (i = 0 ; i < MDR_SFP_InfoItems[indInfo].len; ++i )
    printf("%x ", rdData[i]); 
  printf("\n"); 
}

void ShowInfoSPF(void)
{
  uint32_t i;
  for (i = 0; i < CFG_SFP_ITEMS_CNT; i++)
    ShowInfoItemSPF(i, &infoSFP[ MDR_ReadSFP_GetInfoItemOffset(i)]);
}

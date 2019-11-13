#include <MDR_RST_Clock.h>
#include <MDR_PER_Clock.h>

#include <MDR_I2C.h>
#include <stdio.h>
#include "SFP_Defs.h"
#include "BasisCfg.h"
#include <MDRB_UART_Debug.h>

#define I2C_FREQ_HZ     100000

static const MDR_I2C_CfgPinGPIO _pinSCL_I2C = {MDR_GPIO_C, 0, MDR_PIN_ALT}; //  PC0_ALT
static const MDR_I2C_CfgPinGPIO _pinSDA_I2C = {MDR_GPIO_C, 1, MDR_PIN_ALT}; //  PC1_ALT
static const MDR_I2C_CfgPinsGPIO pinsGPIO_I2C = {
    .pPinSCL = &_pinSCL_I2C,
    .pPinSDA = &_pinSDA_I2C,
};  

#define HSE_PLL_MUL_MAX         MDR_x10   //  HSE_max = 8MHz * 10 = 80MHz
#define HSE_LOW_SELRI_MAX       MDR_LOWRI_gt80MHz
#define HSE_EEPROM_DELAY_MAX    EEPROM_Delay_le100MHz

#define MDRB_CLK_PLL_HSE_RES_MAX     MDR_CPU_CFG_PLL_HSE_RES_DEF(HSE_PLL_MUL_MAX, HSE_EEPROM_DELAY_MAX, HSE_LOW_SELRI_MAX)

void SFP_OnConnected(uint32_t indSFP);
void SFP_OnDisconnected(uint32_t indSFP);
void SFP_Routine_CheckConnected(void);

void ShowConnected(uint32_t indSFP);
void ShowInfoSPF(uint32_t indSFP, uint32_t indInfo, uint8_t *rdData);  
void ShowDisconected(uint32_t indSFP);

int main(void)
{ 
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
  
  // Инициализация I2C
  uint32_t freqCPU_Hz = MDR_CPU_GetFreqHz(true);  
  MDR_I2C_InitPinsGPIO(&pinsGPIO_I2C, MDR_PIN_FAST, false);  
  MDR_I2C_Init(I2C_FREQ_HZ, freqCPU_Hz); 
  
  //RoutineCyclickMux();
  SFP_Routine_CheckConnected();
}


void SFP_Routine_CheckConnected(void)
{
  static uint32_t activeSFP = SFP_DISCONNECTED_STATUS;
  uint32_t newSFP;
  uint32_t i, selMsk, changedBits;
    
  while (1)
  {
    newSFP = SFP_GetPresenceStatus();
    if (newSFP != activeSFP)
    {
      changedBits = newSFP ^ activeSFP;
      for (i = 0; i < SFP_COUNT; i++)
      {
        selMsk = 1UL << i;
        //  SFP presence changed
        if (changedBits & selMsk)
        {
          if (newSFP & selMsk)
            SFP_OnDisconnected(i);
          else
            SFP_OnConnected(i);
        }        
      }      
      activeSFP = newSFP;
    }
  }
}

void SFP_OnConnected(uint32_t indSFP)
{
  uint8_t rdData[SFP_LEN_MAX];
  
  SFP_MuxSetActive(indSFP);
  ShowConnected(indSFP);
  
  uint32_t i;
  uint32_t cnt = SFP_INFO_CNT;
  for (i = 0; i < cnt; i++)
  {
    if (SFP_ReadInfo(i, rdData))
      ShowInfoSPF(indSFP, i, rdData);
  }
}
 

void SFP_OnDisconnected(uint32_t indSFP)
{
  ShowDisconected(indSFP);
}

const char *SFP_Names[SFP_COUNT] = {"SFP_X1_1", "SFP_X1_2", "SFP_X8_1", "SFP_X8_2"};

void ShowInfoSPF(uint32_t indSFP, uint32_t indInfo, uint8_t *rdData)
{ 
  uint8_t i;
  printf("A%2d_%9s: ", InfoItems[indInfo].addr, InfoItems[indInfo].name);
  for (i = 0 ; i < InfoItems[indInfo].len; ++i )
    printf("%x ", rdData[i]); 
  printf("\n"); 
}

void ShowConnected(uint32_t indSFP)
{
  printf("========  Connected %s ======== \n", SFP_Names[indSFP]);
}

void ShowDisconected(uint32_t indSFP)
{
  printf("--------  Disconected %s -------- \n", SFP_Names[indSFP]);
}



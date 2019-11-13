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

bool doRead = false;

//void RoutineCheckMux(void);
//void RoutineCyclickMux(void);

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
//  NVIC_SetPriority(I2C_IRQn, 0);
//  NVIC_EnableIRQ(I2C_IRQn);
  
  
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



//void RoutineCyclickMux(void)
//{
//  uint8_t  muxAct = 16;
//  uint8_t  muxNew = 4;  
//  volatile uint32_t result;
//  volatile uint32_t result1;
//  volatile uint32_t result2;
//  volatile uint32_t result3;
//  volatile uint32_t result4;  
//  uint8_t readData1[SFP_LEN_MAX];
////  uint8_t readData2[SFP_LEN_MAX];
////  uint8_t readData3[SFP_LEN_MAX];
////  uint8_t readData4[SFP_LEN_MAX];

//  
//  while (1)
//  {
////  muxNew = 1;
////  result = MDR_I2C_TransferWrite(I2C_ADDR_MUX, 1, &muxNew);    
////  MDR_Delay(10000);    
//    
//    //  Change Mux
//    if (muxNew != muxAct)
//    {      
//      result = MDR_I2C_TransferWrite(I2C_ADDR_MUX, 1, &muxNew);
//      //result = MDR_I2C_TransferWrite(I2C_ADDR_MUX, 1, &muxNew);
//      if (MDR_I2C_TransferRead(I2C_ADDR_MUX, 1, &muxNew) == 1)
//        muxAct = muxNew;
//    }  
//  
//    uint8_t  addr;
//    for (addr = 0; addr < 0x7F; addr++)   
//    {
//      result1 = MDR_I2C_TransferRead(addr, 1, readData1);
//      if (result1 == 1)
//        MDR_Delay(10000);
//    }
////    result2 = MDR_I2C_TransferRead(SFP_ADDR_IDEX,       SFP_LEN_IDEX,       readData2);
////    result3 = MDR_I2C_TransferRead(SFP_ADDR_CONNECTOR,  SFP_LEN_CONNECTOR,  readData3);
////    result4 = MDR_I2C_TransferRead(SFP_ADDR_TANSCEIVER, SFP_LEN_TANSCEIVER, readData4);   
//    
//    MDR_Delay(10000);
//  }
//}

//void RoutineCheckMux(void)
//{
//  uint8_t readData1[SFP_LEN_MAX];
//  uint8_t readData2[SFP_LEN_MAX];
//  uint8_t readData3[SFP_LEN_MAX];
//  uint8_t readData4[SFP_LEN_MAX];
//  volatile uint32_t result;
//  volatile uint32_t result1;
//  volatile uint32_t result2;
//  volatile uint32_t result3;
//  volatile uint32_t result4;
//  volatile bool presSFP1_1;
//  volatile bool presSFP1_2;
//  volatile bool presSFP8_1;
//  volatile bool presSFP8_2;    
//  
//  while (1)
//  {
//    if (doRead)
//    {      
//      presSFP1_1 = SFP_GetPrecence(SFP_PRES_PIN_X1_1);
//      presSFP1_2 = SFP_GetPrecence(SFP_PRES_PIN_X1_2);
//      presSFP8_1 = SFP_GetPrecence(SFP_PRES_PIN_X8_1);
//      presSFP8_2 = SFP_GetPrecence(SFP_PRES_PIN_X8_2);
//      
//      uint32_t i;      
//      for (i = 0; i < SFP_LEN_MAX; ++i)
//      {
//        readData1[i] = 0;
//        readData2[i] = 0;
//        readData3[i] = 0;
//        readData4[i] = 0;
//      }
//           
//      uint8_t  muxSel;
//      uint8_t  muxRD;
////      for (i = 0; i < 4; ++i)
////      {
////        //  Select I2CMux
////        muxSel = 1 << i;
//        muxSel = 1;
//        result = MDR_I2C_TransferWrite(I2C_ADDR_MUX, 1, &muxSel);
//        //result = MDR_I2C_TransferRead(I2C_ADDR_MUX, 1, &muxRD);
//        
//        //  Read Serial
//        result1 = MDR_I2C_ReadAddrData(I2C_ADDR_SFR, SFP_ADDR_ID,         SFP_LEN_ID,         readData1);
//        result2 = MDR_I2C_ReadAddrData(I2C_ADDR_SFR, SFP_ADDR_IDEX,       SFP_LEN_IDEX,       readData2);
//        result3 = MDR_I2C_ReadAddrData(I2C_ADDR_SFR, SFP_ADDR_CONNECTOR,  SFP_LEN_CONNECTOR,  readData3);
//        result4 = MDR_I2C_ReadAddrData(I2C_ADDR_SFR, SFP_ADDR_TANSCEIVER, SFP_LEN_TANSCEIVER, readData4);
////      }
//    
//      doRead = false;
//    }
//  }
//}

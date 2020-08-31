#include <MDR_Config.h>
#include <MDR_RST_Clock.h>
#include <MDR_GPIO.h>
#include <MDRB_Buttons.h>
#include <MDRB_UART_Debug.h>
#include <MDR_5600BB3.h>
#include <MDR_5600BB3_defs.h>
#include <stdio.h>

// Определения под 1986ВЕ1Т
#define BB3_SPI                 MDR_SSP1ex
#define BB3_SPI_DivSCR_0_255    SPI_DivSCR_144MHZ_TO_6MHz
#define BB3_SPI_DivPSR_2_254    SPI_DivPSR_144MHZ_TO_6MHz

#define BB3_SPI_PORT            MDR_GPIO_D
#define BB3_SPI_TX              2
#define BB3_SPI_RX              3
#define BB3_SPI_SCL             4
#define BB3_SPI_FSS             5
#define BB3_SPI_TX_FUNC         MDR_PIN_ALT
#define BB3_SPI_RX_FUNC         MDR_PIN_ALT
#define BB3_SPI_CLK_FUNC        MDR_PIN_ALT
#define BB3_SPI_FSS_FUNC        MDR_PIN_ALT
#define BB3_SPI_POWER           MDR_PIN_FAST

// SPI Rates
// BitRate = SSP_Clock / (PSR * (1 + SCR)) = 128 MHz / (PSR * (SCR + 1))
//            0 - 255, Serial Clock Rate
//            2 - 254, EVEN ONLY! Clock prescaller
//  1 MHz
#define SPI_DivSCR_128MHZ_TO_1MHz      63
#define SPI_DivPSR_128MHZ_TO_1MHz       2

#define SPI_DivSCR_128MHZ_TO_500KHz    63
#define SPI_DivPSR_128MHZ_TO_500KHz     4

#define SPI_DivSCR_128MHZ_TO_250KHz    63
#define SPI_DivPSR_128MHZ_TO_250KHz     8

#define SPI_DivSCR_SEL    SPI_DivSCR_128MHZ_TO_250KHz
#define SPI_DivPSR_SEL    SPI_DivPSR_128MHZ_TO_250KHz

typedef struct {
  MDR_5600BB3_Reg addr;
  char            *name;
} BB3_RegItem;

#define BB_RegTable_CTRL_Len   10
#define BB_RegTable_Len   38 - BB_RegTable_CTRL_Len

//#define BB_RegTable_Len   38
BB3_RegItem BB_RegTable[BB_RegTable_Len] = {
  {.addr = MDR_5600BB3_regControl   , .name = "regControl"},
  {.addr = MDR_5600BB3_regStatus    , .name = "regStatus"},    
  {.addr = MDR_5600BB3_regFD_Mode5  , .name = "regFD_Mode5"},  
  {.addr = MDR_5600BB3_regPhyModes12, .name = "regPhyModes12"},
  {.addr = MDR_5600BB3_regPhyModes34, .name = "regPhyModes34"},
//  {.addr = MDR_5600BB3_regRamData1  , .name = "regRamData1"},  
//  {.addr = MDR_5600BB3_regRamData2  , .name = "regRamData2"},  
//  {.addr = MDR_5600BB3_regRamData3  , .name = "regRamData3"},  
//  {.addr = MDR_5600BB3_regRamData4  , .name = "regRamData4"},  
//  {.addr = MDR_5600BB3_regRamData5  , .name = "regRamData5"},  
//  {.addr = MDR_5600BB3_regRamData6  , .name = "regRamData6"},  
//  {.addr = MDR_5600BB3_regRamData7  , .name = "regRamData7"},  
//  {.addr = MDR_5600BB3_regRamData8  , .name = "regRamData8"},  
//  {.addr = MDR_5600BB3_regRamCtrl0  , .name = "regRamCtrl0"},  
//  {.addr = MDR_5600BB3_regRamCtrl1  , .name = "regRamCtrl1"},  
  {.addr = MDR_5600BB3_regAgeCtrl0  , .name = "regAgeCtrl0"},  
  {.addr = MDR_5600BB3_regAgeCtrl1  , .name = "regAgeCtrl1"},  
  {.addr = MDR_5600BB3_regAgeCtrl2  , .name = "regAgeCtrl2"},  
  {.addr = MDR_5600BB3_regMacRamWrEn, .name = "regMacRamWrEn"},
  {.addr = MDR_5600BB3_regPN1_MskAnd, .name = "regPN1_MskAnd"},
  {.addr = MDR_5600BB3_regPN2_MskAnd, .name = "regPN2_MskAnd"},
  {.addr = MDR_5600BB3_regPN3_MskAnd, .name = "regPN3_MskAnd"},
  {.addr = MDR_5600BB3_regPN4_MskAnd, .name = "regPN4_MskAnd"},
  {.addr = MDR_5600BB3_regPN5_MskAnd, .name = "regPN5_MskAnd"},
  {.addr = MDR_5600BB3_regPN1_MskOr , .name = "regPN1_MskOr"},
  {.addr = MDR_5600BB3_regPN2_MskOr , .name = "regPN2_MskOr"}, 
  {.addr = MDR_5600BB3_regPN3_MskOr , .name = "regPN3_MskOr"}, 
  {.addr = MDR_5600BB3_regPN4_MskOr , .name = "regPN4_MskOr"}, 
  {.addr = MDR_5600BB3_regPN5_MskOr , .name = "regPN5_MskOr"}, 
  {.addr = MDR_5600BB3_regIPGh      , .name = "regIPGh"},      
  {.addr = MDR_5600BB3_regIPGl      , .name = "regIPGl"},      
  {.addr = MDR_5600BB3_regMAC_CtrlTx, .name = "regMAC_CtrlTx"},
  {.addr = MDR_5600BB3_regCollWindow, .name = "regCollWindow"},
  {.addr = MDR_5600BB3_regMAC_CtrlRx, .name = "regMAC_CtrlRx"},
  {.addr = MDR_5600BB3_regMinFrameH , .name = "regMinFrameH"}, 
  {.addr = MDR_5600BB3_regMinFrameL , .name = "regMinFrameL"}, 
  {.addr = MDR_5600BB3_regMaxFrameH , .name = "regMaxFrameH"}, 
  {.addr = MDR_5600BB3_regMaxFrameL , .name = "regMaxFrameL"} 
};

MDR_5600BB3_TableMAC_Item itemMacWR1 = 
{
  .srcMAC = {0x11, 0x22, 0x33, 0x44, 0x55, 0x66}, 
  .AgeCnt = 100,
  .isActive = true,
  .srcPort = 1
};

MDR_5600BB3_TableMAC_Item itemMacWR2 = 
{
  .srcMAC = {0x12, 0x34, 0x56, 0x78, 0x9A, 0xBC}, 
  .AgeCnt = 200,
  .isActive = true,
  .srcPort = 2
};



#define BTN_DEBOUNCE_MS  10
static MDR_SSP_Type      *spiBB3;
void printItemMAC(MDR_5600BB3_TableMAC_Item *itemMac);

int main(void)
{
  //  Максимальная скорость тактирования
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDRB_CLK_PLL_HSE_RES_MAX;
  MDR_CPU_SetClock_PLL_HSE(&cfgPLL_HSE, true);
  uint32_t freqCPU_Hz = MDR_CPU_GetFreqHz(true);  

  //  Кнопки
  MDRB_Buttons_Init(BTN_DEBOUNCE_MS, freqCPU_Hz);  
  //  Debug UART
  MDR_UART_DBG_Init(true);  
  
  //  Подача SSP_Clock на SPI
  MDR_SSPex_SetSSPClock_InpPLLCPU(BB3_SPI, MDR_Div128P_div1);    
  
  //  5600BB3 SPI Init
  MDR_SSP_Rates spiRates = {
    .divSCR_0_255 = SPI_DivSCR_SEL,
    .divPSR_2_254 = SPI_DivPSR_SEL};
      
  MDR_SSP_CfgPinGPIO pinCLK = {.portGPIO = BB3_SPI_PORT, .pinIndex = BB3_SPI_SCL, .pinFunc = BB3_SPI_CLK_FUNC};
  MDR_SSP_CfgPinGPIO pinTX  = {.portGPIO = BB3_SPI_PORT, .pinIndex = BB3_SPI_TX,  .pinFunc = BB3_SPI_TX_FUNC};
  MDR_SSP_CfgPinGPIO pinRX  = {.portGPIO = BB3_SPI_PORT, .pinIndex = BB3_SPI_RX,  .pinFunc = BB3_SPI_RX_FUNC};
  MDR_SSP_CfgPinGPIO pinFSS = {.portGPIO = BB3_SPI_PORT, .pinIndex = BB3_SPI_FSS, .pinFunc = BB3_SPI_FSS_FUNC};    
    
  MDR_SSP_CfgPinsGPIO spiPins = {
    .pPinCLK = &pinCLK,
    .pPinTX  = &pinTX,
    .pPinRX  = &pinRX,
    .pPinFSS = &pinFSS,
  };
    
  spiBB3 = MDR_5600BB3_Init(BB3_SPI, spiRates, &spiPins, MDR_PIN_FAST);  
  
  
  while (1)
  {
    //  Read Regs
    if (MDRB_BntClicked_Up(true))
    {
      printf("  READ REGs\n");
      uint32_t i;
      uint32_t value;
      for (i = 0; i < BB_RegTable_Len; i++)
      {
        value = MDR_5600BB3_Read(spiBB3, BB_RegTable[i].addr);
        printf("%s = %x\n", BB_RegTable[i].name, value);
      }
    }    
    //  Write Regs
    if (MDRB_BntClicked_Right(true))
    {
      printf("  WRITE REGs\n");
      MDR_5600BB3_MII_SetFD(spiBB3);  
      MDR_5600BB3_MII_OldClearStop(spiBB3);
    }
    //  Read MAC Table
    if (MDRB_BntClicked_Down(true))
    {
      uint32_t i;
      MDR_5600BB3_TableMAC_Item itemMac;
      printf("  MAC TABLE\n");      
      for (i = 0; i < MDR_5600BB3_MAC_TABLE_LEN; i++)
      {
        if (MDR_5600BB3_TableMAC_Read(spiBB3, i, &itemMac, 500))
        {
          if (itemMac.isActive)
          {
            printf("HASH: 0x%x ", i);
            printItemMAC(&itemMac);
          }
        }
        else
          printf("ReadItem[%d] faults\n", i);
      }
      printf("  read completed\n");
    }    
    //  Write MAC Table
    if (MDRB_BntClicked_Left(true))
    {     
      printf("  WRITE TWO MAC ITEMS\n");
      uint16_t indMAC1 = MDR_5600BB3_TableMAC_CalcIndex(itemMacWR1.srcMAC, 0);
      MDR_5600BB3_TableMAC_Write(spiBB3, indMAC1, &itemMacWR1, 100);
      printf("HASH1: 0x%x ", indMAC1);
      printItemMAC(&itemMacWR1);   
      
      uint16_t indMAC2 = MDR_5600BB3_TableMAC_CalcIndex(itemMacWR2.srcMAC, 0);
      MDR_5600BB3_TableMAC_Write(spiBB3, indMAC2, &itemMacWR2, 500);
      printf("HASH2: 0x%x ", indMAC2);
      printItemMAC(&itemMacWR2);
    }
    
    //  Read Raw Data
    if (MDRB_BntClicked_Back(true))
    {
      uint32_t i;
      printf("  RAW TABLE\n");   
      uint8_t data[10];
      for (i = 0; i < MDR_5600BB3_MAC_TABLE_LEN; i++)
      {
        if (MDR_5600BB3_TableMAC_ReadRAW(spiBB3, i, data, 500))
        {
          if ((data[0]+ data[1] + data[2] + data[3] + data[4] + data[5] + data[6] + data[7]) != 0)
          {
            printf("HASH: 0x%x ", i);
            printf("%02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx %02hhx \n", data[0], data[1], data[2], data[3], data[4], data[5], data[6], data[7]);
          }
        }
        else
          printf("ReadItem[%d] faults\n", i);
      }
      printf("  read completed\n");
    }      
    
  }  // while  
} // main


void printItemMAC(MDR_5600BB3_TableMAC_Item *itemMac)
{
  printf(" MAC: %02hhx:%02hhx:%02hhx:%02hhx:%02hhx:%02hhx  AGE: 0x%x  PORT: 0x%x\n", 
    itemMac->srcMAC[0],itemMac->srcMAC[1],itemMac->srcMAC[2],itemMac->srcMAC[3],itemMac->srcMAC[4],itemMac->srcMAC[5],
    itemMac->AgeCnt, itemMac->srcPort); 
}



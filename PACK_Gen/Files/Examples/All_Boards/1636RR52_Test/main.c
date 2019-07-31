#include <MDR_RST_Clock.h>
#include <MDR_SSP.h>
#include <MDR_PER_Clock.h>
#include <MDRB_Buttons.h>
#include <MDRB_UART_Debug.h>
#include <stdio.h>

#include <MDRB_SSP_PinSelect.h>
#include <MDR_1636RR52.h>

#define BTN_DEBOUNCE_MS   20

#define RR52_USE_READ_15MHz   1

#if RR52_USE_READ_15MHz
  #define MDR_RR52_READ    MDR_RR52_ReadArray_15MHz
#else
  #define MDR_RR52_READ    MDR_RR52_ReadArray
#endif

static MDR_1636RR52_Obj RR52_Obj;

typedef enum {
  tstReadID,
  tstStatus,        //  toggle SPRL, RSTE
  tstProtection,    //  toggle Sector Protections
  tstEraseSect1,  
  tstCheckClear1,
  tstWriteSect1,
  tstCheckSect1,
  tstEraseSect2, 
  tstCheckClear2,  
  tstWriteSect2,
  tstCheckSect2,
  tstEraseAll,
  tstReset,  
} TEST_COM_ID;

static TEST_COM_ID activeID = tstReadID;

void ShowActionName(TEST_COM_ID testID);
void PerformTestAction(TEST_COM_ID testID);

void ChangeStatusAction(void);
void ChangeProtection(void);
void WriteSectionData(MDR_1636RR52_Sector sector, uint8_t valueOffs);
uint32_t CheckSectionClear(MDR_1636RR52_Sector sector);
uint32_t CheckSectionData(MDR_1636RR52_Sector sector, uint8_t valueOffs);

#ifdef USE_MDR1986VK234
  static const MDR_SSP_CfgPinGPIO _pinCS = {MDR_GPIO_B, 12, MDR_PIN_MAIN};
#endif

int main(void)
{
  uint32_t freqCPU_Hz;
  MDR_1636RR52_Cfg cfgRR52 = { 
    //  SPI BitRate = SSP_Clock / (PSR * (1 + SCR))
    .DivSCR_0_255 = 20,
    .DivPSR_2_254 = 2,
    .ClockBRG = MDR_Div128P_div1,
    //  Pins
    .pPinCLK = MDRB_PinsSSP1.pPinCLK,
    .pPinTX  = MDRB_PinsSSP1.pPinTX,
    .pPinRX  = MDRB_PinsSSP1.pPinRX,
#ifdef USE_MDR1986VK234
    .pPinManualCS = &_pinCS,
#else    
    .pPinManualCS = MDRB_PinsSSP1.pPinFSS,
#endif    
    .pinsPower = MDR_PIN_MAXFAST
  };

  
  //  Максимальная скорость тактирования
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDRB_CLK_PLL_HSE_RES_MAX;
  MDR_CPU_SetClock_PLL_HSE(&cfgPLL_HSE, true);
  
  //  Инициализация LCD дисплея и кнопок
  freqCPU_Hz = MDR_CPU_GetFreqHz(true);
  MDRB_Buttons_Init(BTN_DEBOUNCE_MS, freqCPU_Hz);

  //  Включение UART_DBG для printf
  MDR_UART_DBG_Init();  
  
  //  Инициализация RR52
  MDR_RR52_InitDelays(freqCPU_Hz); 
  RR52_Obj = MDR_RR52_Init(MDR_SSP1ex, &cfgRR52);  
  
  //  Начальные настройки
  MDR_RR52_UnprotectSector(&RR52_Obj, MDR_RR52_SectToAddr(RR52_Sector1));
  MDR_RR52_UnprotectSector(&RR52_Obj, MDR_RR52_SectToAddr(RR52_Sector2));  
  activeID = tstReadID;
  ShowActionName(activeID);
  
  
  
  while (1) 
  {
    if (MDRB_BntClicked_Up(true))
    {      
      if (activeID == tstReset)
        activeID = tstReadID;
      else
        ++activeID;
      
      ShowActionName(activeID);
    }  
    
    if (MDRB_BntClicked_Right(true))
    {      
      PerformTestAction(activeID);
    } 
  }
}


void ChangeStatusAction(void)
{
  static uint32_t statusBitCase = 0;
  
  ++statusBitCase;
  if (statusBitCase >= 4)
    statusBitCase = 0;
  
  switch (statusBitCase) {
    case 0: MDR_RR52_WriteStatusReg(&RR52_Obj, 0); break;
    case 1: MDR_RR52_WriteStatusReg(&RR52_Obj, MDR_RR52_STATUS__RSTE_Msk); break;
    case 2: MDR_RR52_WriteStatusReg(&RR52_Obj, MDR_RR52_STATUS__SPRL_Msk); break;
    case 3: MDR_RR52_WriteStatusReg(&RR52_Obj, MDR_RR52_STATUS__RSTE_Msk | MDR_RR52_STATUS__SPRL_Msk); break;
  };
}

void ChangeProtection(void)
{
  static uint32_t statusBitCase = 0;
  
  ++statusBitCase;
  if (statusBitCase >= 4)
    statusBitCase = 0;
  
  switch (statusBitCase) {
    case 0: 
      MDR_RR52_UnprotectSector(&RR52_Obj, MDR_RR52_SectToAddr(RR52_Sector1));
      MDR_RR52_UnprotectSector(&RR52_Obj, MDR_RR52_SectToAddr(RR52_Sector2));
      break;
    case 1:
      MDR_RR52_ProtectSector  (&RR52_Obj, MDR_RR52_SectToAddr(RR52_Sector1));
      MDR_RR52_UnprotectSector(&RR52_Obj, MDR_RR52_SectToAddr(RR52_Sector2));
      break;      
    case 2:
      MDR_RR52_UnprotectSector(&RR52_Obj, MDR_RR52_SectToAddr(RR52_Sector1));
      MDR_RR52_ProtectSector  (&RR52_Obj, MDR_RR52_SectToAddr(RR52_Sector2));
      break;      
    case 3:
      MDR_RR52_ProtectSector(&RR52_Obj, MDR_RR52_SectToAddr(RR52_Sector1));
      MDR_RR52_ProtectSector(&RR52_Obj, MDR_RR52_SectToAddr(RR52_Sector2));
      break;     
  };
}

//-------------------     DataBuffs ------------------
#define BUFF_L          1024
#define BUFF_IN_SECT    MDR_1636RR52_SectSize / BUFF_L
static uint8_t buff[BUFF_L];
static uint8_t ValueOffs[MDR_1636RR52_SectCount] = {0, 0};

uint32_t CheckSectionClear(MDR_1636RR52_Sector sector)
{
  uint32_t i, j;
  uint32_t errCount = 0;
  uint32_t startAddr = MDR_RR52_SectToAddr(sector);
  
  for (j = 0; j < BUFF_L; ++j)
    buff[j] = 0;
  
  for (i = 0; i < BUFF_IN_SECT; ++i)
  {
    MDR_RR52_READ(&RR52_Obj, startAddr + i * BUFF_L, BUFF_L, buff);
    for (j = 0; j < BUFF_L; ++j)
      if (buff[j] != 0xFF)
        ++errCount;
  }
  
  return errCount;
}

void WriteSectionData(MDR_1636RR52_Sector sector, uint8_t valueOffs)
{
  uint32_t i, j;
  uint8_t value = valueOffs;
  uint32_t startAddr = MDR_RR52_SectToAddr(sector);
  
  for (i = 0; i < BUFF_IN_SECT; ++i)
  {
    for (j = 0; j < BUFF_L; ++j)
      buff[j] = value++;
    
    MDR_RR52_ProgramArray(&RR52_Obj, startAddr + i * BUFF_L, BUFF_L, buff);
  }
}

uint32_t CheckSectionData(MDR_1636RR52_Sector sector, uint8_t valueOffs)
{
  uint32_t i, j;
  uint32_t errCount = 0;
  uint8_t value = valueOffs;
  uint32_t startAddr = MDR_RR52_SectToAddr(sector);

  for (j = 0; j < BUFF_L; ++j)
    buff[j] = 0;
  
  for (i = 0; i < BUFF_IN_SECT; ++i)
  {
    MDR_RR52_READ(&RR52_Obj, startAddr + i * BUFF_L, BUFF_L, buff);
    for (j = 0; j < BUFF_L; ++j)
      if (buff[j] != value++)
        ++errCount;
  }
  
  return errCount;
}

void PerformTestAction(TEST_COM_ID testID)
{   
  switch (testID) {
    case tstReadID: 
      printf("        ID: 0x%x\n",      MDR_RR52_ReadID(&RR52_Obj)); 
      break;
    case tstStatus:
      ChangeStatusAction(); 
      printf("        Status: 0x%x\n",  MDR_RR52_ReadStatusReg(&RR52_Obj)); 
      break;
    case tstProtection: 
      ChangeProtection();   
      printf("        Prot:  0x%x   0x%x\n", MDR_RR52_ReadProtSectReg(&RR52_Obj, MDR_RR52_SectToAddr(RR52_Sector1)), 
                                             MDR_RR52_ReadProtSectReg(&RR52_Obj, MDR_RR52_SectToAddr(RR52_Sector2))); 
      printf("        Status: 0x%x\n",  MDR_RR52_ReadStatusReg(&RR52_Obj));
      break;
    case tstEraseSect1:
      MDR_RR52_SectorEraseByInd(&RR52_Obj, RR52_Sector1);
      printf("        Completed\n");
      break;
    case tstCheckClear1:
      printf("        ErrCount: 0x%x\n",  CheckSectionClear(RR52_Sector1));
      break;
    case tstWriteSect1:
      ++ValueOffs[0];
      WriteSectionData(RR52_Sector1, ValueOffs[0]);
      printf("        Completed\n");
      break;      
    case tstCheckSect1: 
      printf("        ErrCount: 0x%x\n",  CheckSectionData(RR52_Sector1, ValueOffs[0]));  
      break;
    case tstEraseSect2:
      MDR_RR52_SectorEraseByInd(&RR52_Obj, RR52_Sector2);
      printf("        Completed\n");
      break;
    case tstCheckClear2:
      printf("        ErrCount: 0x%x\n",  CheckSectionClear(RR52_Sector2));
      break;        
    case tstWriteSect2:
      ++ValueOffs[1];
      WriteSectionData(RR52_Sector2, ValueOffs[1]);
      printf("        Completed\n");
      break;      
    case tstCheckSect2: 
      printf("        ErrCount: 0x%x\n",  CheckSectionData(RR52_Sector2, ValueOffs[1]));  
      break;
    case tstEraseAll:  
      MDR_RR52_ChipErase(&RR52_Obj);
      printf("        Sect1 ErrCount: 0x%x\n",  CheckSectionClear(RR52_Sector1));
      printf("        Sect2 ErrCount: 0x%x\n",  CheckSectionClear(RR52_Sector2));
      break;
    case tstReset: 
      MDR_RR52_Reset(&RR52_Obj);
      printf("        STATUS: 0x%x\n",  MDR_RR52_ReadStatusReg(&RR52_Obj));    
      break;
  }
}

void ShowActionName(TEST_COM_ID testID)
{  
  switch (testID) {
    case tstReadID: 
      printf("Read ID:\n"); 
      break;
    case tstStatus: 
      printf("Change STATUS:\n");
      printf("        Status: 0x%x\n",  MDR_RR52_ReadStatusReg(&RR52_Obj));     
      break;
    case tstProtection: 
      printf("Change PROTECTION:\n"); 
      printf("        Prot:  0x%x   0x%x\n", MDR_RR52_ReadProtSectReg(&RR52_Obj, MDR_RR52_SectToAddr(RR52_Sector1)), 
                                      MDR_RR52_ReadProtSectReg(&RR52_Obj, MDR_RR52_SectToAddr(RR52_Sector2))); 
      printf("        Status: 0x%x\n",  MDR_RR52_ReadStatusReg(&RR52_Obj));    
      break;
    case tstEraseSect1:
      printf("ERASE Sect1:\n");
      break;
    case tstCheckClear1:
      printf("CHECK CLEAR Sect1:\n");
      break;    
    case tstWriteSect1: 
      printf("WRITE Sect1:\n");
      break;
    case tstCheckSect1:
      printf("CHECK Sect1:\n");
      break;      
    case tstEraseSect2:
      printf("ERASE Sect2:\n");
      break;
    case tstCheckClear2:
      printf("CHECK CLEAR Sect2:\n");
      break;
    case tstWriteSect2: 
      printf("WRITE Sect2:\n");
      break;
    case tstCheckSect2:
      printf("CHECK Sect2:\n");
      break;      
    case tstEraseAll:
      printf("ERASE ALL:\n");
      break;      
    case tstReset: 
      printf("RESET:\n");
      break;
  }
}





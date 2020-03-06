#include <MDR_Config.h>
#include <MDR_Funcs.h>
#include <MDR_RST_Clock.h>
#include <MDR_5101NA015.h>

// Задержка на старте ПО - для переходные процессы при включении питания
#define START_DELAY_MS          1000

//  SPI Settings
#define SPI_DAC   MDR_SSP1ex

MDR_SSP_CfgPinGPIO _pinRX_SSP1  = {MDR_GPIO_D, 3, MDR_PIN_ALT};
MDR_SSP_CfgPinGPIO _pinFSS_SSP1 = {MDR_GPIO_C, 5, MDR_PIN_PORT};
MDR_SSP_CfgPinGPIO _pinTX_SSP1  = {MDR_GPIO_C, 6, MDR_PIN_OVER};  
MDR_SSP_CfgPinGPIO _pinCLK_SSP1 = {MDR_GPIO_C, 7, MDR_PIN_ALT};


const MDR_5101NA015_Cfg cfgDAC = {
  .rates = {
    //  Write SPI BitRate - max 30MHz (min 33ns)     // BitRate = SSP_Clock / (PSR * (1 + SCR))
    .WR_DivPSR_2_254 = 160,    // 8MHz   / 20 = 50KHz , 2 - 254, EVEN ONLY! Clock prescaller
    .WR_DivSCR_0_255 = 0,      // 50MHz  / 1  = 50MHz , 0 - 255, Serial Clock Rate
    //  Read SPI BitRate - max 2.5MHz (min 400ns)
    .RD_DivPSR_2_254 = 160,    // 8MHz   / 20 = 50KHz , 2 - 254, EVEN ONLY! Clock prescaller
    .RD_DivSCR_0_255 = 0,      // 50MHz  / 1  = 50MHz , 0 - 255, Serial Clock Rate
  },
  //  Pins
  .pPinCLK = &_pinCLK_SSP1,
  .pPinTX  = &_pinTX_SSP1,
  .pPinRX  = &_pinRX_SSP1,
  .pPinManualCS = &_pinFSS_SSP1,
  .pinsPower = MDR_PIN_FAST
};

MDR_5101NA015_Obj       dacObj;


//  Log Registers
#define  REG_LOG_LEN    100
uint32_t RegsDAC_CalOn1[REG_LOG_LEN];
uint32_t RegsDAC_CalOff[REG_LOG_LEN];
uint32_t RegsDAC_CalOn2[REG_LOG_LEN];

void LogDacRegisters(uint32_t *regList);
bool TestRegOffsetWR_RD(void);
void TestCalibrAndLogRegs(void);

int main(void)
{
  MDR_Delay_ms(START_DELAY_MS, HSI_FREQ_HZ);
  
  //  Тактирование от HSI
  uint32_t freqCPU_Hz = MDR_CPU_GetFreqHz(true);
  uint32_t delayTicks = US_TO_DELAY_LOOPS(100, freqCPU_Hz);

  //  Частота SSP_Clock для SPI
  MDR_SSPex_SetSSPClock_InpPLLCPU(MDR_SSP1ex, MDR_Div128P_div1);    
  //  5101НА015 ЦАП
  MDR_5101NA015_InitDelaysDef(freqCPU_Hz);
  dacObj = MDR_5101NA015_Init(SPI_DAC, &cfgDAC);
 
  //  Запуск калибровки и тестовое чтения регистров в
  MDR_5101NA015_RunCalibrDef(&dacObj);
  TestCalibrAndLogRegs();
  
  //  Write-Read Offset Test
  volatile bool testWrRd = TestRegOffsetWR_RD();
  
  //  Параметры выставить для наблюдения Меадра или Пилы на выходе ЦАП
  bool doMeandr = false;
  bool doSaw = true;
  //  Тестовое чтение регистра - использовалось для отладки обмена
  bool doRead   = false;
  
  
  volatile uint32_t wrValue = MDR_5101NA015_VALUE_MIN;
  volatile uint32_t rdValue = 0;
  volatile uint32_t rdValuePrev = 0;    
  while (1)
  {    
    if (doMeandr)
    {
      MDR_5101NA015_SetValue(&dacObj, MDR_5101NA015_VALUE_MIN);
      MDR_Delay(delayTicks);
      
      MDR_5101NA015_SetValue(&dacObj, MDR_5101NA015_VALUE_MAX);
      MDR_Delay(delayTicks);  
    }
    
    if (doSaw)
    {
      wrValue += 1000;
      if (wrValue > MDR_5101NA015_VALUE_MAX)
        wrValue = MDR_5101NA015_VALUE_MIN; 
      
      MDR_5101NA015_SetValue(&dacObj, wrValue);
      MDR_Delay(delayTicks);  
    }
    
    if (doRead)
    {
      rdValuePrev = rdValue;
      rdValue = MDR_5101NA015_Read(&dacObj, MDR_5101NA015_CMD__RD_CALIBR);
      MDR_Delay(delayTicks);
    }
  }  
}

void LogDacRegisters(uint32_t *regList)
{
  MDR_5101NA015_ReadEnter(&dacObj);
  
  *regList++ = MDR_5101NA015_ReadTransfer(&dacObj, MDR_5101NA015_CMD__RD_ACC);
  *regList++ = MDR_5101NA015_ReadTransfer(&dacObj, MDR_5101NA015_CMD__RD_BAS_LSB);
  *regList++ = MDR_5101NA015_ReadTransfer(&dacObj, MDR_5101NA015_CMD__RD_BAS_MSB);
  *regList++ = MDR_5101NA015_ReadTransfer(&dacObj, MDR_5101NA015_CMD__RD_OFFSET);
  *regList++ = MDR_5101NA015_ReadTransfer(&dacObj, MDR_5101NA015_CMD__RD_MIN);
  *regList++ = MDR_5101NA015_ReadTransfer(&dacObj, MDR_5101NA015_CMD__RD_CALIBR);
  
  uint32_t rdAdd;
  for (rdAdd = MDR_5101NA015_CMD__RD_MEMT_START; rdAdd <= MDR_5101NA015_CMD__RD_MEMT_END; rdAdd++)
    *regList++ = MDR_5101NA015_ReadTransfer(&dacObj, rdAdd);
  
  for (rdAdd = MDR_5101NA015_CMD__RD_MEM_START; rdAdd <= MDR_5101NA015_CMD__RD_MEM_END; rdAdd++)
    *regList++ = MDR_5101NA015_ReadTransfer(&dacObj, rdAdd);  
  
  MDR_5101NA015_ReadExit(&dacObj);
}

void TestCalibrAndLogRegs(void)
{
  //  Тройное чтение регистров чтобы убедиться что возвращается одно и тоже.
  //  Но по факту это не так, какие-то значения внутри меняются.
  LogDacRegisters(RegsDAC_CalOn1);
  LogDacRegisters(RegsDAC_CalOn2);
  LogDacRegisters(RegsDAC_CalOff);
  
  //  Чтение значений регистров после сброса калибровки.
  MDR_5101NA015_CalibrClear(&dacObj);
  LogDacRegisters(RegsDAC_CalOff);
  
  //  Выполнение калибровки и чтение получившихся регистров
  MDR_5101NA015_RunCalibrDef(&dacObj);
  LogDacRegisters(RegsDAC_CalOn2);  
}

bool TestRegOffsetWR_RD(void)
{ 
  uint16_t regCalibrStart = MDR_5101NA015_Read(&dacObj, MDR_5101NA015_CMD__RD_CALIBR);

  //  Offset Enable
  MDR_5101NA015_WriteTransfer(&dacObj, MDR_5101NA015_CMD__WR_CALIBR, regCalibrStart | MDR_5101NA015_VAL_CALIBR_OFFS_EN_MSK);
  uint16_t regCalibrOffsEn = MDR_5101NA015_Read(&dacObj, MDR_5101NA015_CMD__RD_CALIBR); 
  
  //  Test Offset Value WR-RD
  uint16_t regOffset1 = MDR_5101NA015_Read(&dacObj, MDR_5101NA015_CMD__RD_OFFSET); 
  MDR_5101NA015_WriteTransfer(&dacObj, MDR_5101NA015_CMD__WR_OFFSET, regOffset1 + 100);
  uint16_t regOffset2 = MDR_5101NA015_Read(&dacObj, MDR_5101NA015_CMD__RD_OFFSET);
  bool offsOK = (regOffset2 == (regOffset1 + 100));
    
  //  Offset Disable
  MDR_5101NA015_WriteTransfer(&dacObj, MDR_5101NA015_CMD__WR_CALIBR, regCalibrStart);  
  uint16_t regCalibrEnd = MDR_5101NA015_Read(&dacObj, MDR_5101NA015_CMD__RD_CALIBR);
    
  bool restoreCalOK = (regCalibrEnd == regCalibrStart);
  bool writeOffsEnOK = (((regCalibrStart ^ regCalibrOffsEn) & MDR_5101NA015_VAL_CALIBR_OFFS_EN_MSK) == MDR_5101NA015_VAL_CALIBR_OFFS_EN_MSK);
  return offsOK && writeOffsEnOK && restoreCalOK;
}



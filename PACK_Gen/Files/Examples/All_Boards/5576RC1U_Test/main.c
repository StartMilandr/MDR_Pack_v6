#include <MDR_Config.h>
#include <MDR_Funcs.h>
#include <MDR_RST_Clock.h>

#include <MDR_ISC_5576RC1U.h>
#include "MDR_JTAG_Config.h"

// Задержка на старте ПО - для переходные процессы при включении питания
#define START_DELAY_MS          1000

//  Тактирование
#define HSE_PLL_MUL_MAX         MDR_x16   //  HSE_max = 8MHz * 16 = 128MHz
#define HSE_LOW_SELRI_MAX       MDR_LOWRI_gt80MHz
#define HSE_EEPROM_DELAY_MAX    EEPROM_Delay_le150MHz

#define MDRB_CLK_PLL_HSE_RES_MAX     MDR_CPU_CFG_PLL_HSE_RES_DEF(HSE_PLL_MUL_MAX, HSE_EEPROM_DELAY_MAX, HSE_LOW_SELRI_MAX)

//  Примерная скорость Jtag
#define JTAG_FREQ_HZ            200E+3
#define OUTPUT_TO_FPGA          0

#define TEST_DATA               0xAAAA

void Test_ProgFillMem(uint32_t value);
uint32_t Test_ProgVerifMem(uint32_t value);

int main(void)
{ 
  MDR_Delay_ms(START_DELAY_MS, HSI_FREQ_HZ);
  
  //  Максимальная скорость тактирования
  MDR_CLK_Enable_RST_BPK();
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDRB_CLK_PLL_HSE_RES_MAX; 
  MDR_CPU_SetClock_PLL_HSE(&cfgPLL_HSE, true);
  uint32_t freqCPU_Hz = MDR_CPU_GetFreqHz(true);
  
  //  Инициализация Jtag и драйвера 5576РС1У
  MDR_5576RC_Delays delays = {
    .ticks_eraseSect_4s = S_TO_DELAY_LOOPS(4, freqCPU_Hz),
    .ticks_ena_RD_1ms   = MS_TO_DELAY_LOOPS(1, freqCPU_Hz),
    .ticks_prog_200ns   = NS_TO_DELAY_LOOPS(200, freqCPU_Hz),   
  };

  MDR_JTAG_Cfg cfgJTAG = {
    //  Pins defs
    .cfgTCK = {.portGPIO = JTAG_PORT_TCK, .selPins = JTAG_PIN_TCK},
    .cfgTMS = {.portGPIO = JTAG_PORT_TMS, .selPins = JTAG_PIN_TMS},
    .cfgTDI = {.portGPIO = JTAG_PORT_TDI, .selPins = JTAG_PIN_TDI},
    .cfgTDO = {.portGPIO = JTAG_PORT_TDO, .selPins = JTAG_PIN_TDO},
    .pCfgTRST = NULL,
    //  Clock width delay for MDR_Delay
    .widthTCK_Ticks = CLOCKS_TO_DELAY_LOOPS((double)freqCPU_Hz / JTAG_FREQ_HZ) / 2 + 1,
    .funcWaitTicks = MDR_Delay
  };
    
  MDR_5576RC_Init(&cfgJTAG, &delays);  
  
  // Выставить отладчиком в true для запуска теста
  bool doTest = false;
  volatile uint32_t errBlankCnt = 0;
  volatile uint32_t errCnt = 0;
  volatile uint32_t idCode = 0;
  
  while (1)  
  {
    if (doTest)
    {
      //  Стираем всю память, от 0x8000 и до конца 0x40000. Длительность ~30сек
      MDR_5576RC1U_Erase();
      //  Проверяем что память стерта. Длительность ~35сек.
      errBlankCnt = MDR_5576RC1U_CheckBlank();
      if (errBlankCnt == 0)
      {
        //  Конфигурируем DONE_BIT (с адреса 0x8000) и прочие неизвестные биты (значения скопированы из ТУ (а туда видимо с Altera))
        MDR_5576RC1U_ProgCfgBits();
        //  Программирование пользовательской памяти. Длительность ~15сек.
        Test_ProgFillMem(TEST_DATA);  
        //  Проверка зашитых значений. Длительность ~35сек.
        errCnt = Test_ProgVerifMem(TEST_DATA);
        
        //  SUCCESS = (errCnt == 1)
        //  Ошибка только при чтении из последнего адреса (причина неизвестна)
        //  Читается 0xFFFF вместо 0xAAAA, адрес 0x3FFFF.
        
      //  Опционально - чтобы вывести прошивку в FPGA через выводы DATA и DCLK
      #if OUTPUT_TO_FPGA
        MDR_5576RC1U_Exit();            // ISC_DISABLE
        MDR_5576RC1U_SentInitConfig();  // запуск вывода на DATA и DCLK
        MDR_JTAG_ToReset();             //  JTAG State to Reset
      #endif
      }
      
      doTest = false;
    }
    
    idCode = MDR_5576RC_Read_IDCODE();
    MDR_Delay(100);
  }
}  

void Test_ProgFillMem(uint32_t value)
{
  MDR_5576RC1U_ProgStart(MDR_5576RC_USER_DATA_ADDR);
  uint32_t i;
  for (i = MDR_5576RC_USER_DATA_ADDR; i < MDR_5576RC_DATA_LEN; i++)
    MDR_5576RC1U_ProgNextData(value);
}

uint32_t Test_ProgVerifMem(uint32_t value)
{
  MDR_5576RC1U_ReadStart(MDR_5576RC_USER_DATA_ADDR);
  
  uint32_t i, rdData;
  uint32_t errCnt = 0;
  for (i = MDR_5576RC_USER_DATA_ADDR; i < MDR_5576RC_DATA_LEN; i++)
  {
    rdData = MDR_5576RC1U_ReadNextData();
    if (rdData != value)
      ++errCnt;
  }
  
  return errCnt;
}


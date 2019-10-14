#include <MDR_Config.h>
#include <MDR_RST_Clock.h>
#include <MDR_OTP_VE8x.h>
#include <MDR_Funcs.h>

#include <MDRB_Buttons.h>
#include <MDRB_LEDs.h>

//  ОПИСАНИЕ:

//  Работает так-же на максимальной частоте
#define OTP_PROG_WITH_HSE0_MAX_CLOCK  1
#define OTP_PROG_WITH_HSI             0
#define OTP_PROG_WITH_HSE1_GEN_24MHZ  0


#if OTP_PROG_WITH_HSI
  //  8MHz
  #define LED_CYCLICK_PERIOD  5000
#elif OTP_PROG_WITH_HSE0_MAX_CLOCK
  //  40MHz
  #define LED_CYCLICK_PERIOD  25000
#elif OTP_PROG_WITH_HSE1_GEN_24MHZ  
  //  24MHz
  #define LED_CYCLICK_PERIOD  15000
#endif

#define BTN_DEBOUNCE_MS  10

#define LED_CYCLE     MDRB_LED_1
#define LED_OK        MDRB_LED_2
#define LED_ERR       MDRB_LED_3



//  Увеличивать после каждой записи - сдвиг на чистую память с конца ОТР.
//  Минимальное значение = 1
#define OTP_TEST_TEST_IND          1

#define OTP_TEST_ADDR_END          0x01020000
#define OTP_TEST_PROG_ADDR         (OTP_TEST_ADDR_END - (OTP_TEST_TEST_IND * 4))

//  Значения записываемые/записанные в память в порядке OTP_TEST_TEST_IND
#define OTP_TEST_PROG_DATA         0x1234ABCD

void OPT_WriteTestData(void);
bool OPT_ReadAndCheck(void);
void LedCyclicToggle(void);

uint32_t RunIndex = 0;
uint32_t freqCPU_Hz;
uint32_t rdValue;
bool     _ShowDelayCycles = false;


int main(void)
{ 
  MDR_CLK_Enable_RST_BPK();
  
#if OTP_PROG_WITH_HSE0_MAX_CLOCK
  //  Максимальная скорость тактирования
  MDR_CPU_PLL_CfgHSE cfgPLL_HSE = MDRB_CLK_PLL_HSE_RES_MAX;
  MDR_CPU_SetClock_PLL_HSE(&cfgPLL_HSE, true);

#elif OTP_PROG_WITH_HSI
  //  HSI имеет разброс и для каждого кристалла неободима своя подстройка.
  //  В данном проекте используется отклонение от значения по умолчанию (trim_def = 32)
  #define MY_CHIP_HSI_TRIM_SHIFT (-10)
  
  //  Для варианта без Trim
  //#define MY_CHIP_HSI_TRIM_SHIFT    0
  
  MDR_CPU_CfgHSI cfgHSI = MDR_CPU_CFG_HSI_TRIM_DEF(MDR_BKP_REG63_HSI_Trim_Def_32 + MY_CHIP_HSI_TRIM_SHIFT);
  MDR_CPU_SetClock_HSI(&cfgHSI, HSI_TIMEOUT, false);
  
#elif OTP_PROG_WITH_HSE1_GEN_24MHZ
  MDR_CPU_SetClock_HSE1_def(MDR_CLK_Generator, true);
  
#endif
  
  freqCPU_Hz = MDR_CPU_GetFreqHz(true); 
  MDRB_Buttons_Init(BTN_DEBOUNCE_MS, freqCPU_Hz);
  MDRB_LED_Init(LED_CYCLE | LED_OK | LED_ERR);
   
  MDR_OTP_ProgDelays delays = MDR_OTP_GetProgDelays(freqCPU_Hz);
  MDR_Delay_Init();
  
  while (1)
  {
    //  Programm
    if (MDRB_BntClicked_Up(true))
    {
      MDRB_LED_Set(LED_CYCLE | LED_OK | LED_ERR, 1);
      MDR_Delay_ms(200, freqCPU_Hz);
      
      OPT_WriteTestData();     
      MDRB_LED_Set(LED_CYCLE | LED_OK | LED_ERR, 0);
    }
    //  Read and compare
    if (MDRB_BntClicked_Right(true))
    {
      MDRB_LED_Set(LED_CYCLE | LED_OK | LED_ERR, 0);
      MDR_Delay_ms(200, freqCPU_Hz);
      
      if (OPT_ReadAndCheck())
        MDRB_LED_Set(LED_OK, 1);
      else
        MDRB_LED_Set(LED_ERR, 1);
    }
    //  Show Delay to LedErr Pin
    if (MDRB_BntClicked_Down(true))
    {      
      _ShowDelayCycles = !_ShowDelayCycles;
    }
    
    if (_ShowDelayCycles)
    {
      MDRB_LED_Set(LED_ERR, 0);
      MDR_Delay(delays.delay_HV_PE);
      MDRB_LED_Set(LED_ERR, 1);
      MDR_Delay(delays.delay_A_D);
      MDRB_LED_Set(LED_ERR, 0);
      MDR_Delay(delays.delay_Prog);
      MDRB_LED_Set(LED_ERR, 1);
    }
    
    LedCyclicToggle();
  }
}

void OPT_WriteTestData(void)
{
  MDR_OTP_Enable();  
  MDR_OTP_ProgBegin_ByClockCPU_Hz(freqCPU_Hz); 
  MDR_OTP_ProgWord(OTP_TEST_PROG_ADDR, OTP_TEST_PROG_DATA);
  MDR_OTP_ProgEnd();
  MDR_OTP_Disable(); 
}

bool OPT_ReadAndCheck(void)
{ 
  MDR_OTP_Enable();
  rdValue = MDR_OTP_ReadWord(OTP_TEST_PROG_ADDR);
  MDR_OTP_Disable();
 
  return (rdValue == OTP_TEST_PROG_DATA);
}

void LedCyclicToggle(void)
{
  static uint32_t cnt = 0;
  
  ++cnt;
  if (cnt > LED_CYCLICK_PERIOD)
  {
    MDRB_LED_Toggle(LED_CYCLE);
    cnt = 0;
  }
}


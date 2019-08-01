#include <MDR_RST_Clock.h>
#include <MDR_ADC.h>
#include <MDRB_LEDs.h>
#include <MDRB_Buttons.h>
#include <MDR_EEPROM.h>

//  Обязательная настройка отдельного АЦП
static const MDR_ADCx_CfgBase _CfgADCx_clkCPU = {
  .ClockSource    = MDR_ADC_CLK_CPU,
  .CPU_ClockDiv   = MDR_ADC_CPU_div2048,
  .MagRefExternal = MDR_Off,             // GND..AUcc
  .SwitchDelay_GO = MDR_ADC_DelayGO_7    // Delay between continuous start
};

static const MDR_ADCx_CfgIRQ _CfgIRQ_OnResult = {
  .OnResult_IRQEna = MDR_On,             // Enable IRQ on ResultReady
  .OnLimit_IRQEna  = MDR_Off             // Enable IRQ on Limit
};

//  Общая базовая конфигурация для примеров
static MDR_ADC_Config _cfgAdc = 
{
  .pCfgThermo = NULL,
  
  .pCfgADC1   = &_CfgADCx_clkCPU,
  .pCfgLim1   = NULL,
  .pCfgIRQ1   = &_CfgIRQ_OnResult,

  //  flags
  .ActivateNVIC_IRQ = MDR_On,
  .Priority_IRQ = 1
};

#define MEAS_AVER     10
static uint32_t dataADC[MEAS_AVER];
static uint32_t ind = 0;
static volatile uint32_t resultADC;

#define EE_READ_CNT   3000
static uint32_t SectDataEE[EE_READ_CNT];

void ADC_IRQHandler(void);

int main(void)
{
  uint32_t i; //, data;
  volatile uint32_t sum;

  //MDR_DebugerProtectDelay();
  
  uint32_t startPageAddr = MDR_EEPROM_PageToAddr(EEPROM_Page16, EEPROM_IFREN_Main);
  
  //  Максимальная скорость тактирования
  MDR_EEPROM_Init(HSI_FREQ_HZ);
  
  MDRB_LED_Init(MDRB_LED_1 | MDRB_LED_2);
  MDRB_Buttons_Init(10, HSI_FREQ_HZ);
    
 // MDR_ADC_PinsInitByMask(MDR_GPIO_D, PIN_PD9);
  MDR_ADC_Init(&_cfgAdc);
  MDR_ADC_StartSignal(MDR_ADC1, ADC_Signal_Ch0, true, NULL);
  
  while (1)
  {      
    //------- ADC Processing ---------
    if (ind == MEAS_AVER)
    {
      sum = 0;
      for (i = 0; i < MEAS_AVER; ++i)
        sum += dataADC[i];
      resultADC = sum / MEAS_AVER;
      
      MDRB_LED_Toggle(MDRB_LED_1);
      
      ind = 0;
    }

    //------- EEPROM Read ---------
    __disable_irq();    
    MDR_EEPROM_ReadBuff(startPageAddr, EE_READ_CNT, SectDataEE, EEPROM_IFREN_Main);
    __enable_irq();
    
    sum = 0;
    for (i = 0; i < EE_READ_CNT; ++i)
    { 
      if (SectDataEE[i] != i)
        ++sum;
    }
    if (sum == 0)
      MDRB_LED_Toggle(MDRB_LED_2);
    
    //------- EEPROM Write ---------
    if (MDRB_BntClicked_Up(true))
    {
      MDRB_LED_Set(MDRB_LED_1 | MDRB_LED_2, 1);
      
      for (i = 0; i < EE_READ_CNT; ++i)
        SectDataEE[i] = i;
      
      __disable_irq();    
      MDR_EEPROM_WriteBuff(startPageAddr, EE_READ_CNT, SectDataEE, EEPROM_IFREN_Main);
      __enable_irq();    
    
      MDRB_LED_Set(MDRB_LED_1 | MDRB_LED_2, 0);
    }
  }
}


void ADC_IRQHandler(void)
{
  if (ind < MEAS_AVER)
  {
    dataADC[ind] = MDR_ADC_GetResult(MDR_ADC1).Result & 0x0FFFUL;
    ++ind;
  }
  else
    MDR_ADC_GetResult(MDR_ADC1);
}


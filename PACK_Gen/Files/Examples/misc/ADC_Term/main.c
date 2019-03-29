#include <MDR_RST_Clock.h>
#include <MDR_ADC.h>
#include <MDRB_LCD.h>
#include <MDRB_LEDs.h>
#include <MDRB_Buttons.h>
#include <MDRB_UART_Debug.h>

#include <stdio.h>

//  Обязательная настройка отдельного АЦП
const MDR_ADCx_CfgBase _CfgADCx_clkCPU = {
  .ClockSource    = MDR_ADC_CLK_CPU,
  .CPU_ClockDiv   = MDR_ADC_CPU_div512,
  .MagRefExternal = MDR_Off,             // GND..AUcc
  .SwitchDelay_GO = MDR_ADC_DelayGO_1    // Delay between continuous start
};

const MDR_ADC_CfgThermo   _CfgThermo = {
  .UseThermoVref  = MDR_On,              //  Vref from ThermoSensor - ADC1_OP and ADC2_OP
  .TrimThermoVref = MDR_ADC_TRIM_def
};

const MDR_ADCx_CfgIRQ _CfgIRQ_OnResult = {
  .OnResult_IRQEna = MDR_On,             // Enable IRQ on ResultReady
  .OnLimit_IRQEna  = MDR_Off             // Enable IRQ on Limit
};

//  Общая базовая конфигурация для примеров
MDR_ADC_Config _cfgAdc = 
{
  .pCfgThermo = &_CfgThermo,
  
  .pCfgADC1   = &_CfgADCx_clkCPU,
  .pCfgLim1   = NULL,
  .pCfgIRQ1   = &_CfgIRQ_OnResult,

  //  flags
  .ActivateNVIC_IRQ = MDR_On,
  .Priority_IRQ = 1
};

#define COUNT_TO_SEND   200
uint16_t dataADC[COUNT_TO_SEND];
uint16_t lastDataADC;
uint32_t countToSend = 0;
bool     doSendData = false;

#define BUTTON_DEBOUNCE_MS  10
#define LCD_UPDATE_PERIOD   100000

void LCD_ShowTemperature(uint16_t valueADC);

int main(void)
{
  uint32_t freqCPU_Hz;
  uint32_t i;
  uint32_t cntShow = 0;

  //  Максимальная скорость тактирования
  MDR_CPU_SetClock_HSE_Max(MDR_Off);  
  freqCPU_Hz = MDR_CPU_GetFreqHz(true);  
  
  MDRB_Buttons_Init(BUTTON_DEBOUNCE_MS, freqCPU_Hz);
  MDRB_LCD_Init(freqCPU_Hz);
  MDR_UART_DBG_Init();
    
  MDR_ADC_Init(&_cfgAdc);
  MDR_ADC_StartSignal(MDR_ADC1, ADC_Signal_TS_Temper, true, NULL);
  
  while (1)
  {
    //  Restart ADC Sample data
    if (MDRB_BntClicked_Up(true))
    {
      countToSend = COUNT_TO_SEND;
      doSendData = true;
    }
    
    //  Send Data to Uart
    if ((countToSend == 0) & doSendData)
    {
      printf("ADC: \n");
      for (i = 0; i < COUNT_TO_SEND; ++i)
        printf(" 0x%x  ", dataADC[i]);
      printf("\n");
      
      printf("DELTA: \n");
      for (i = 0; i < (COUNT_TO_SEND - 1); ++i)
        printf(" %3d  ", dataADC[i + 1] - dataADC[i]);
      printf("\n");
      
      doSendData = false;
    }
    
    //  Show Temperature to LCD
    ++cntShow;
    if (cntShow > LCD_UPDATE_PERIOD)
    {
      LCD_ShowTemperature(lastDataADC);
      cntShow = 0;
    }
  }
}

void ADC_IRQHandler(void)
{
  lastDataADC = MDR_ADC_GetResult(MDR_ADC1).Result & 0x0FFFUL;
  if (countToSend > 0)
  { 
    dataADC[COUNT_TO_SEND - countToSend] = lastDataADC;
    --countToSend;
  }
}

//  ЗНАЧЕНИЯ ИЗМЕРЯЮТСЯ ПРИ ДВУХ ТЕМПЕРАТУРАХ ДЛЯ КАЖДОГО ЭКЗЕМПЛЯРА МК!
#define CALIBR_CONST_T1 25.0F  // Температура в первой точке
#define CALIBR_CONST_T2 60.0F  // Температура во второй точке
#define CALIBR_CONST_D1 0x6A0  // Результат цифро-аналогового преобразования в первой точке
#define CALIBR_CONST_D2 0x7A0  // Результат цифро-аналогового преобразования во второй точке

//  Коэффициенты считаются из формулы T = scale * D + offset
#define T_SCALE     ((CALIBR_CONST_T2 - CALIBR_CONST_T1) / (CALIBR_CONST_D2 - CALIBR_CONST_D1))
#define T_BIAS      (CALIBR_CONST_T1 - (T_SCALE * CALIBR_CONST_D1))

void LCD_ShowTemperature(uint16_t valueADC)
{  
  static char message[64];
  float       temper = valueADC * T_SCALE + T_BIAS;
  
  sprintf(message , "T = %.1f\xB0\x43", temper);      
  MDRB_LCD_Print (message, 3);
  
  sprintf(message , "ADC = %d", valueADC);      
  MDRB_LCD_Print (message, 5);  
}


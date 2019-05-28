#include "ADC_cfg.h"


//======================  Настройки АЦП ======================
//  Опция использования термосенсора
const MDR_ADC_CfgThermo   _CfgThermo = {
  .UseThermoVref  = MDR_On,              //  Vref from ThermoSensor - ADC1_OP and ADC2_OP
  .TrimThermoVref = MDR_ADC_TRIM_def
};

//  Обязательная настройка отдельного АЦП
const MDR_ADCx_CfgBase _CfgADCx_clkCPU = {
  .ClockSource    = MDR_ADC_CLK_CPU,
  .CPU_ClockDiv   = MDR_ADC_CPU_div2048,
  .MagRefExternal = MDR_Off,             // GND..AUcc
  .SwitchDelay_GO = MDR_ADC_DelayGO_7    // Delay between continuous start
};

const MDR_ADCx_CfgBase _CfgADCx_clkADC = {
  .ClockSource    = MDR_ADC_CLK_ADC,
  .CPU_ClockDiv   = MDR_ADC_CPU_div1,    // not used
  .MagRefExternal = MDR_Off,             // GND..AUcc
  .SwitchDelay_GO = MDR_ADC_DelayGO_7    // Delay between continuous start
};

//  Опции прерываний 
const MDR_ADCx_CfgIRQ _CfgIRQ_Off = {
  .OnResult_IRQEna = MDR_Off,            // Enable IRQ on ResultReady
  .OnLimit_IRQEna  = MDR_Off             // Enable IRQ on Limit
};

const MDR_ADCx_CfgIRQ _CfgIRQ_OnResult = {
  .OnResult_IRQEna = MDR_On,             // Enable IRQ on ResultReady
  .OnLimit_IRQEna  = MDR_Off             // Enable IRQ on Limit
};

// Опция отслеживания лимитов сигнала
const MDR_ADCx_CfgLimits _CfgLims = {
  .HighLevelLim = 0x0D00,
  .LowLevelLim  = 0x0100 
};

#ifdef MDR_HAS_ADC2
//  Опция синхронного измерения АЦП1 и АЦП2
const MDR_ADC_CfgSync _CfgSync_On = {
  .SynMeasADCs_Ena  = MDR_On,
  .DelayBetweenADCs = MDR_ADC_DelayADC_0//MDR_ADC_DelayADC_10 //MDR_ADC_DelayADC_0
};
#endif


//  Общая базовая конфигурация для примеров
MDR_ADC_Config _cfgAdc = 
{
  .pCfgThermo = &_CfgThermo,
  
  .pCfgADC1   = &_CfgADCx_clkCPU,
  .pCfgLim1   = &_CfgLims,
  .pCfgIRQ1   = &_CfgIRQ_Off,

#ifdef MDR_HAS_ADC2
  .pCfgADC2   = &_CfgADCx_clkCPU,
  .pCfgLim2   = &_CfgLims,
  .pCfgIRQ2   = &_CfgIRQ_Off,
  
  .pCfgSync   = NULL,
#endif
  
  //  flags
  .ActivateNVIC_IRQ = MDR_On,
  .Priority_IRQ = 1
};

//======================  Выбор измеряемых сигналов ======================
//  Неинтересующие сигналы закомментировать (чтобы не листать слишком много сигналов в тестах).
#if   defined(USE_BOARD_VE1)
  //  см. MDRB_1986VE1.h
  //  Ch2 (PD9) - TuneResistor (R14 jumper on board)
  static MDR_ADC_Signal _UsedSignals[] = {ADC_Signal_Ch2, ADC_Signal_Ch3, ADC_Signal_Ch4, ADC_Signal_Ch5, ADC_Signal_TS_Temper, ADC_Signal_TS_Vref, ADC_Signal_TS_VrefBuf};
  
#elif defined(USE_BOARD_VE3)
  //  см. MDRB_1986VE3.h
  //  Ch5 (PD12) Ch3 - совмещен с LCD (не использовать в этом примере)
  //  Нет регулируемого резистора на входе АЦП.
  static MDR_ADC_Signal _UsedSignals[] = {ADC_Signal_Ch0, ADC_Signal_Ch1, ADC_Signal_Ch2, ADC_Signal_Ch3, ADC_Signal_TS_Temper, ADC_Signal_TS_Vref, ADC_Signal_TS_VrefBuf};
  
#elif defined(USE_BOARD_VE91) || defined(USE_BOARD_VE94)
  //  см. MDRB_1986VE91.h
  //  Ch7 (PD7) - TuneResistor
  static MDR_ADC_Signal _UsedSignals[] = {ADC_Signal_Ch7, ADC_Signal_Ch8, ADC_Signal_TS_Temper, ADC_Signal_TS_Vref};
  
#elif defined(USE_BOARD_VE92)
  //  см. MDRB_1986VE92.h
  //  Ch0-Ch3 (PD0-PD3) _ JtagB, Pulled up to Ucc
  //  Ch7 (PD7) - TuneResistor
  static MDR_ADC_Signal _UsedSignals[] = {ADC_Signal_Ch6, ADC_Signal_Ch7, ADC_Signal_TS_Temper, ADC_Signal_TS_Vref};

#elif defined(USE_BOARD_VE93)
  //  см. MDRB_1986VE93.h
  //  Ch2 (PD2) - TuneResistor, Ch3 - совмещен с LCD (не использовать в этом примере)
  //  Ch5 - не выведен на пин корпуса, но в кристалле есть. Добавлен чтобы было что переключать, в тестах по маске.
  static MDR_ADC_Signal _UsedSignals[] = {ADC_Signal_Ch2, ADC_Signal_Ch5, ADC_Signal_TS_Temper, ADC_Signal_TS_Vref};
  
#elif defined(USE_BOARD_VC1)
  //  см. MDRB_1901VС1.h
  //  Не использовать Ch8 - совмещен с LCD, ломает вывод. 
  //  Нет регулируемого резистора на входе АЦП.
  static MDR_ADC_Signal _UsedSignals[] = {ADC_Signal_Ch5, ADC_Signal_Ch6, ADC_Signal_TS_Temper, ADC_Signal_TS_Vref};
  
#elif defined (USE_MDR1986VE4)
  //  см. MDRB_1986VE4.h
  //  Не использовать Ch8 - совмещен с LCD, ломает вывод. 
  //  Нет регулируемого резистора на входе АЦП.
  static MDR_ADC_Signal _UsedSignals[] = {ADC_Signal_Ch2, ADC_Signal_Ch5, ADC_Signal_Ch7, ADC_Signal_TS_Temper, ADC_Signal_TS_Vref, ADC_Signal_TS_VrefBuf};
  
#elif defined (USE_MDR1986VK214)
  //  см. MDRB_1986VE4.h
  //  Не использовать Ch0 - совмещен с LED1
  static MDR_ADC_Signal _UsedSignals[] = {ADC_Signal_Ch0, ADC_Signal_Ch1, ADC_Signal_TS_Temper, ADC_Signal_TS_Vref, ADC_Signal_TS_VrefBuf};
	
#elif defined (USE_MDR1986VK234)
  //  см. MDRB_1986VE4.h
  //  Не использовать Ch0 - совмещен с LED1
  static MDR_ADC_Signal _UsedSignals[] = {ADC_Signal_Ch4, ADC_Signal_Ch5, ADC_Signal_TS_Temper, ADC_Signal_TS_Vref, ADC_Signal_TS_VrefBuf};
#endif

static uint32_t CFG_SignalCount = sizeof(_UsedSignals)/sizeof(_UsedSignals[0]);

//  Количество выбраных сигналов с выводов GPIO
uint32_t Cfg_PinSignalCount = 0;
//  Используемые выводы GPIO
uint32_t Cfg_GPIO_PinSelected = 0;
uint32_t Cfg_GPIO_PinSelectedEx = 0;
//  Выбраные каналы АЦП в выводов GPIO
MDR_ADC_Select_PinChannels Cfg_PinChannelsSelected = {.Select = 0};

static void InitGPIOPinSelect(void);

void Cfg_InitSelectedConfigs(void)
{
  uint32_t i;

  // Signals Select
  Cfg_PinChannelsSelected.Select = 0;
  Cfg_PinSignalCount = 0;
  for (i = 0; i < CFG_SignalCount; ++i)
    if (_UsedSignals[i] < ADC_Signal_TS_Temper)
    {
      Cfg_PinChannelsSelected.Select |= 1 << _UsedSignals[i];
      ++Cfg_PinSignalCount;
    }
    
  //  Select GPIO Pins
  InitGPIOPinSelect();
}
  
//  Привязка внешних сигналов к пинам GPIO
#if defined(USE_MDR1986VE9x) || defined(USE_MDR1901VC1)
  static uint32_t _SignalToPinSelect[] = {
      PIN_PD0           // ADC_Signal_Ch0
    , PIN_PD1           // ADC_Signal_Ch1
    , PIN_PD2           // ADC_Signal_Ch2
    , PIN_PD3           // ADC_Signal_Ch3
    , MDR_Pin_4         // ADC_Signal_Ch4
    , MDR_Pin_5         // ADC_Signal_Ch5
    , MDR_Pin_6         // ADC_Signal_Ch6
    , MDR_Pin_7         // ADC_Signal_Ch7
    , MDR_Pin_8         // ADC_Signal_Ch8
    , MDR_Pin_9         // ADC_Signal_Ch9
    , MDR_Pin_10        // ADC_Signal_Ch10
    , MDR_Pin_11        // ADC_Signal_Ch11
    , MDR_Pin_12        // ADC_Signal_Ch12
    , MDR_Pin_13        // ADC_Signal_Ch13
    , MDR_Pin_14        // ADC_Signal_Ch14
    , MDR_Pin_15        // ADC_Signal_Ch15
    , 0                 // ADC_Signal_TS_Temper
    , 0                 // ADC_Signal_TS_Vref
    , 0                 // ADC_Signal_TS_VrefBuf
  };
#elif defined(USE_MDR1986VE1) || defined(USE_MDR1986VE3)
  static uint32_t _SignalToPinSelect[] = {
      PIN_PD7           // ADC_Signal_Ch0
    , PIN_PD8           // ADC_Signal_Ch1
    , PIN_PD9           // ADC_Signal_Ch2
    , PIN_PD10          // ADC_Signal_Ch3
    , PIN_PD11          // ADC_Signal_Ch4
    , PIN_PD12          // ADC_Signal_Ch5
    , PIN_PD13          // ADC_Signal_Ch6
    , PIN_PD14          // ADC_Signal_Ch7
    , 0                 // ADC_Signal_TS_Temper
    , 0                 // ADC_Signal_TS_Vref
    , 0                 // ADC_Signal_TS_VrefBuf
  };
#elif defined(USE_MDR1986VE4) || defined(USE_MDR1986VK214) || defined(USE_MDR1986VK234)
  
  #define USED_GPIO_CB
  
  static uint32_t _SignalToPinSelect[] = {
      PIN_PC4           // ADC_Signal_Ch0
    , PIN_PC3           // ADC_Signal_Ch1
    , PIN_PC2           // ADC_Signal_Ch2
    , PIN_PC1           // ADC_Signal_Ch3
    , PIN_PB9           // ADC_Signal_Ch4
    , PIN_PB8           // ADC_Signal_Ch5
    , PIN_PB7           // ADC_Signal_Ch6
    , PIN_PB6           // ADC_Signal_Ch7
    , 0                 // ADC_Signal_TS_Temper
    , 0                 // ADC_Signal_TS_Vref
    , 0                 // ADC_Signal_TS_VrefBuf
  };  
#endif  

#ifndef USED_GPIO_CB  
  static void InitGPIOPinSelect(void)
  {
    uint32_t i;
    
    Cfg_GPIO_PinSelected = 0;
    Cfg_GPIO_PinSelectedEx = 0;
    for (i = 0; i < CFG_SignalCount; ++i)
      Cfg_GPIO_PinSelected |= _SignalToPinSelect[_UsedSignals[i]];
    
    //  Настраиваем на измерение АЦП только те выводы на демоплате, которые не ломают работу LCD экрана.
    //  Иначе в примере некуда будет выводить результат.
  #ifdef MDRB_ADC_PIN_ALL_LCD  
    Cfg_GPIO_PinSelected &= MDRB_ADC_PIN_ALL_LCD;
  #endif
  }
#else
  static void InitGPIOPinSelect(void)
  {
    uint32_t i;
    
    Cfg_GPIO_PinSelected = 0;
    Cfg_GPIO_PinSelectedEx = 0;
    for (i = 0; i < CFG_SignalCount; ++i)
    {
      if (_UsedSignals[i] <= ADC_Signal_Ch3)
        Cfg_GPIO_PinSelected |= _SignalToPinSelect[_UsedSignals[i]];
      else
        Cfg_GPIO_PinSelectedEx |= _SignalToPinSelect[_UsedSignals[i]];
    }
    
    //  Настраиваем на измерение АЦП только те выводы на демоплате, которые не ломают работу LCD экрана.
    //  Иначе в примере некуда будет выводить результат.
  #ifdef MDRB_ADC_PIN_KEY_PROTECT2  
    Cfg_GPIO_PinSelected &= MDRB_ADC_PIN_KEY_PROTECT2;
  #endif
  }
#endif

//=============  Переключение активного сигнала при переборе ===============
//  Программное переключение сигналов 
static uint32_t activeSignal = 0;

void Cfg_SetNextSignal(void)
{
  ++activeSignal;
  if (activeSignal >= CFG_SignalCount)
    activeSignal = 0;  
}

MDR_ADC_Signal Cfg_GetActiveSignal(void)
{
  return _UsedSignals[activeSignal];
}

//  Символ сигнала для вывода на экран
static char signalThermoName[] = {
  'T'
  ,'V'
#ifndef MDR_HAS_ADC2   
  ,'B'
#endif
};

char Cfg_GetActiveSignalName(void)
{
  if (_UsedSignals[activeSignal] <= MDR_ADC_PinSignal_Last)
    return ('0' + _UsedSignals[activeSignal]);
  else if (_UsedSignals[activeSignal] < ADC_Signal_TS_Temper)
    return ('A' + _UsedSignals[activeSignal] - MDR_ADC_PinSignal_Last);  
  else
    return signalThermoName[(uint32_t)(_UsedSignals[activeSignal] - ADC_Signal_TS_Temper)];  
}




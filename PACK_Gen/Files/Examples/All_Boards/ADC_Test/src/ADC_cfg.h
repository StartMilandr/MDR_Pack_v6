#ifndef _ADC_CFG_H
#define _ADC_CFG_H

#include <MDR_ADC.h>
#include <MDRB_BoardSelect.h>


//======================  Настройки АЦП ======================

//  Глобальный выбор частоты работы АЦП
//  Закомментировать, чтобы включать в тестах по отдельности
#define USE_ADC_CLOCK   0

//  Общая базовая конфигурация для примеров
extern MDR_ADC_Config    _cfgAdc;


//  Обязательная настройка отдельного АЦП
extern const MDR_ADCx_CfgBase   _CfgADCx_clkCPU;
extern const MDR_ADCx_CfgBase   _CfgADCx_clkADC;
//  Опция использования термосенсора
extern const MDR_ADC_CfgThermo  _CfgThermo;
// Опция отслеживания лимитов сигнала
extern const MDR_ADCx_CfgLimits _CfgLims;
//  Опции прерываний 
extern const MDR_ADCx_CfgIRQ _CfgIRQ_Off;
extern const MDR_ADCx_CfgIRQ _CfgIRQ_OnResult;

#ifdef MDR_HAS_ADC2
//  Опция синхронного измерения АЦП1 и АЦП2
extern const MDR_ADC_CfgSync    _CfgSync_On;
#endif

//=================  Выбор измеряемых сигналов =================

#ifdef MDR_ADC_IN_PORTD  
  #define CFG_ADC_GPIO_Port     MDR_GPIO_D  
#elif defined(MDR_ADC_IN_PORTS_CB)
  #define CFG_ADC_GPIO_Port     MDR_GPIO_C
  #define CFG_ADC_GPIO_PortEx   MDR_GPIO_B
#endif  

//  Инициализация глобальных переменных согласно выбраным сигналам в _UsedSignals.
void Cfg_InitSelectedConfigs(void);

//  Глобальные переменные, инициализируются вызовом Cfg_InitSelectedConfigs()
//  Количество выбраных сигналов с выводов GPIO
extern uint32_t Cfg_PinSignalCount;
//  Используемые выводы GPIO
extern uint32_t Cfg_GPIO_PinSelected;
extern uint32_t Cfg_GPIO_PinSelectedEx;
//  Выбраные каналы АЦП в выводов GPIO
extern MDR_ADC_Select_PinChannels Cfg_PinChannelsSelected;


//=============  Переключение активного сигнала при переборе ===============
void            Cfg_SetNextSignal(void);
MDR_ADC_Signal  Cfg_GetActiveSignal(void);
char            Cfg_GetActiveSignalName(void);


//=============  Прочие параметры ===============
//  Выбор строк для вывода на экран
#define LED_LINE_INIT    0
#define LED_LINE_RESULT  2
#define LED_LINE_INFO    4
#define LED_LINE_CFG1    6
#define LED_LINE_CFG2    7

#define LED7_SHOW_INFO    1
#define LED7_DELAY_MS     500

//  Количество усреднений при измерении сигнала
#define ONE_CHANNEL_AVER  10


#endif  //_ADC_CFG_H


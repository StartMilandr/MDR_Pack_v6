#ifndef _MDR_ADC_H
#define _MDR_ADC_H

#include <MDR_Config.h>
#include <MDR_Funcs.h>
#include <MDR_GPIO.h>


//  ============    Настройка выводов GPIO в качестве каналов АЦП ==============
//  Выбор пинов GPIO, для настройки в аналоговую функцию - сигналы каналов АЦП
#define MDR_ADC_PinsInitByMask(PortGPIO, PinSelect)    MDR_GPIO_InitAnalog(PortGPIO, PinSelect)


//  ============    Управление отдельными опциями конфигурации АЦП ==============
//  Обязательные настройки: 
//    MDR_ADCx_CfgBase  - настройки работы АЦП
//  Дополнительные настройки (необязательные опции): 
//    MDR_ADC_CfgThermo - использование термосенсора и его параметры.
//    MDR_ADCx_CfgIRQ   - Разрешение работы прерываний.
//    MDR_ADC_CfgSync   - Режим синхронного измерения АЦП1 и АЦП2.
//    MDR_ADCx_CfgLimits- Режим с проверкой выхода сигнала за пороги знчений.
//  Функции
//    Clear  - Выключает опцию, (стирают параметры относящиеся к настройкам опций).
//    Set    - Включает опцию. NULL в указателе на структуру подавать нельзя!
//    Change - Меняют текущее настройки, (Clear + Set). Если указатель NULL, то опция только выключается.


//  Управление настройками термосенсора 
typedef struct {
  MDR_OnOff             UseThermoVref;          //  Vref from ThermoSensor - ADC1_OP and ADC2_OP
  MDR_ADC_TRIM_TS_Vref  TrimThermoVref;         //  Vref voltage tune
} MDR_ADC_CfgThermo;  

void MDR_ADC_Clear_CfgThermo(void);
void MDR_ADC_Apply_CfgThermo(const MDR_ADC_CfgThermo * cfgThermo);
void MDR_ADC_Change_CfgThermo(const MDR_ADC_CfgThermo *cfgThermo);


//  Управление настройками отдельного ADC
typedef struct {
  MDR_ADC_CLK_SEL       ClockSource;            // CPU_Clock / ADC_Clock
  MDR_ADC_CPU_DIV       CPU_ClockDiv;           // 1 .. 2048
  MDR_OnOff             MagRefExternal;         // GND..AUcc / Ref- .. Ref+
  MDR_ADC_DelayGO       SwitchDelay_GO;         // Delay between continuous start  
} MDR_ADCx_CfgBase;

void MDR_ADC_Clear_CfgBase(MDR_ADCx_ItemType *ADCx);
void MDR_ADC_Apply_CfgBase(MDR_ADCx_ItemType *ADCx, const MDR_ADCx_CfgBase *cfgBase);
void MDR_ADC_Change_CfgBase(MDR_ADCx_ItemType *ADCx, const MDR_ADCx_CfgBase * cfgBase);


//  Настройка прерываний
typedef struct {
  MDR_OnOff             OnResult_IRQEna;        // Enable IRQ on ResultReady
  MDR_OnOff             OnLimit_IRQEna;         // Enable IRQ on SignalLevel
} MDR_ADCx_CfgIRQ;

void MDR_ADC_Clear_CfgIRQ(MDR_ADCx_ItemType *ADCx);
void MDR_ADC_Apply_CfgIRQ(MDR_ADCx_ItemType *ADCx, const MDR_ADCx_CfgIRQ *cfgIRQ);
void MDR_ADC_Change_CfgIRQ(MDR_ADCx_ItemType *ADCx, const MDR_ADCx_CfgIRQ * cfgIRQ);

#ifdef MDR_HAS_ADC2
//  Управление синхронным запуском ADC1 и ADC2
typedef struct {
  MDR_OnOff             SynMeasADCs_Ena;
  MDR_ADC_DelayADC      DelayBetweenADCs;
} MDR_ADC_CfgSync;

void MDR_ADC_Clear_CfgSync(void);
void MDR_ADC_Apply_CfgSync(const MDR_ADC_CfgSync *cfgSync);
void MDR_ADC_Change_CfgSync(const MDR_ADC_CfgSync *cfgSync);
#endif

//  Выставление порогов значений сигнала
typedef struct {
  uint32_t              HighLevelLim;
  uint32_t              LowLevelLim;  
} MDR_ADCx_CfgLimits;

void MDR_ADC_Clear_CfgLims(MDR_ADCx_ItemType *ADCx);
void MDR_ADC_Apply_CfgLims(MDR_ADCx_ItemType *ADCx, const MDR_ADCx_CfgLimits *cfgSync);
void MDR_ADC_Change_CfgLims(MDR_ADCx_ItemType *ADCx, const MDR_ADCx_CfgLimits *cfgSync);


//  ============    Полная инициализация блока ==============
//  Объединение всех опций (для всех АЦП) в одну структуру, чтобы инициализировать одной функцией - MDR_ADC_Init.
//  Обязательно должны быть заданы MDR_ADCx_CfgBase.
//  Параметры прерываний (_IRQ) активируют прерывания в контроллере NVIC (Упрощение, чтобы не вызывать эти функции извне).
//  Прерывания в самом блоке АЦП должны быть активированы опциями MDR_ADCx_CfgIRQ.

typedef struct {
  const MDR_ADC_CfgThermo   *pCfgThermo;
  
  const MDR_ADCx_CfgBase    *pCfgADC1;
  const MDR_ADCx_CfgLimits  *pCfgLim1;
  const MDR_ADCx_CfgIRQ     *pCfgIRQ1;

#ifdef MDR_HAS_ADC2
  const MDR_ADCx_CfgBase    *pCfgADC2;
  const MDR_ADCx_CfgLimits  *pCfgLim2;
  const MDR_ADCx_CfgIRQ     *pCfgIRQ2;
  
  const MDR_ADC_CfgSync     *pCfgSync;
#endif
  
  //  flags
  MDR_OnOff           ActivateNVIC_IRQ;
  uint32_t            Priority_IRQ;
} MDR_ADC_Config;


void MDR_ADC_Init(const MDR_ADC_Config *cfg);

//  Вспомогательные функции, могут пригодится
void MDR_ADC_ClearRegs(void);

__STATIC_INLINE void MDR_ADC_ClockOn(void)  {MDR_CLOCK->MDR_CLK_EN_REG_PER_b.ADC_CLK_EN  = MDR_On;}
__STATIC_INLINE void MDR_ADC_ClockOff(void) {MDR_CLOCK->MDR_CLK_EN_REG_PER_b.ADC_CLK_EN  = MDR_Off;}
__STATIC_INLINE void MDR_ADC_DeInit(void);


//  ============    Варианты запуска измерений внешних сигналов (на выводах GPIO) ==============
//  Запуск измерения одного внешнего канала
//    channel - канал на выводе GPIO, который будет измеряться
//    cyclic  - возможность непрерывного измерения
//    cfgLims - возможность поменять лимиты для предстоящего измерения канала (свои лимиты для каждого канала)
//              если не NULL, меняет настройки лимитов заданные ранее (при инициализации или предыдущем запуске)
//              если NULL - не влияет на текущие настройки. (Не выключает лимиты, если они были включены. Выключить - MDR_ADC_Clear_CfgLims()).
void MDR_ADC_StartChannel(MDR_ADCx_ItemType *ADCx, MDR_ADC_PinChannel channel, bool cyclic, const MDR_ADCx_CfgLimits *cfgLims);


//  Запуск измерения нескольких внешних каналов с автопереключением
//    channelSelected - маска выбора каналов на выводах GPIO.
//    Не использовать сигналы термосенсора, им требуется отдельная инициализация перед измерением (и деинализация перед измерением внешних сигналов).
typedef union {
  uint32_t                  Select;
  MDR_ADC_PinChannel_Flags  Flags;
} MDR_ADC_Select_PinChannels;

void MDR_ADC_StartSelected(MDR_ADCx_ItemType *ADCx, MDR_ADC_Select_PinChannels channelSelected, bool cyclic, const MDR_ADCx_CfgLimits *cfgLims);

//  Повторный запуск измерения, если не был запущен непрерывный режим
__STATIC_INLINE void MDR_ADC_StartNextGo(MDR_ADCx_ItemType *ADCx) {ADCx->ADCx_Cfg |= VAL2FLD_Pos(MDR_On, MDR_ADCx_Cfg_GO_Pos);}

//  Остановка измерений для непрерывного режима.
__STATIC_INLINE void MDR_ADC_Stop(MDR_ADCx_ItemType *ADCx) {ADCx->ADCx_Cfg &= ~(MDR_ADCx_Cfg_ADON_Msk | MDR_ADCx_Cfg_GO_Msk);}

//  Отдельное включение АЦП. Обычно уже вставлено в функцию Start вместе с выставлением бита GO. 
__STATIC_INLINE void MDR_ADC_Enable(MDR_ADCx_ItemType *ADCx)  {ADCx->ADCx_Cfg |= VAL2FLD_Pos(MDR_On, MDR_ADCx_Cfg_ADON_Pos);}
__STATIC_INLINE void MDR_ADC_Disable(MDR_ADCx_ItemType *ADCx) {ADCx->ADCx_Cfg &= ~MDR_ADCx_Cfg_ADON_Msk;}

//  ============    Измерение внутренних сигналов от термосенсора ==============
typedef enum {
    MDR_ADC_ThermoSig_Temper   = 0
  , MDR_ADC_ThermoSig_Vref     = 1
#ifndef MDR_HAS_ADC2  
  , MDR_ADC_ThermoSig_VrefBuff = 2
#endif
} MDR_ADC_ThermoSignal;

//  Запуск режима измерения внутренних сигналов от термо-сенсора
void MDR_ADC_StartThermoSignal(MDR_ADCx_ItemType *ADCx, MDR_ADC_ThermoSignal thermoSignal, bool cyclic, const MDR_ADCx_CfgLimits *cfgLims);
void MDR_ADC_StartThermoSignalSelected(MDR_ADCx_ItemType *ADCx, MDR_ADC_ThermoSignal thermoSignal, bool cyclic, const MDR_ADCx_CfgLimits *cfgLims);

//  Выход из режима измерения сигналов от термосенсора. Применять перед измерением внешних сигналов.
void MDR_ADC_Exit_ThermoSignal(void);


//  ============    Чтение/сброс статуса ==============
typedef union {
  uint32_t             Status;
  MDR_ADC_Status_Flags Flags;
} MDR_ADC_Status;

//  Чтение результата
//__INLINE MDR_ADC_Status MDR_ADC_GetStatus(MDR_ADCx_ItemType *ADCx);
MDR_ADC_Status MDR_ADC_GetStatus(MDR_ADCx_ItemType *ADCx);

//  Сброс статусных бит, кроме тех, что разрешают прерывания
__STATIC_INLINE void MDR_ADC_ClearStatus(MDR_ADCx_ItemType *ADCx) {ADCx->ADCx_Status &= ~(MDR_ADC_STATUS_Overwrite_Msk | MDR_ADC_STATUS_AWOIFEN_Msk | MDR_ADC_STATUS_EOCIF_Msk);}


//  ============    Чтение результата ==============
typedef union {
  uint32_t            Result;
  MDR_ADC_Result_Bits Flags;
} MDR_ADC_Result;

//  Чтение результата. Вызывать когда выставлен флаг готовности в регистре статуса.
//__INLINE  MDR_ADC_Result MDR_ADC_GetResult(MDR_ADCx_ItemType *ADCx);
MDR_ADC_Result MDR_ADC_GetResult(MDR_ADCx_ItemType *ADCx);

//  Ожидание выставления бита готовности и чтение результата.
MDR_ADC_Result MDR_ADC_WaitAndGetResult(MDR_ADCx_ItemType *ADCx);

//  Тоже самое, но возвращает еще и статус, если не NULL
MDR_ADC_Result MDR_ADC_WaitAndGetResultEx(MDR_ADCx_ItemType *ADCx, MDR_ADC_Status *status);


//  ==========================    ADC Signals  ============================
//  Объединение внешних сигналов и сигналов термосенсора под одним управлением
typedef enum {
   ADC_Signal_Ch0
  ,ADC_Signal_Ch1
  ,ADC_Signal_Ch2
  ,ADC_Signal_Ch3
  ,ADC_Signal_Ch4
  ,ADC_Signal_Ch5
  ,ADC_Signal_Ch6
  ,ADC_Signal_Ch7
#if MDR_ADC_PIN_CHANNEL_COUNT > 8   
  ,ADC_Signal_Ch8
  ,ADC_Signal_Ch9
  ,ADC_Signal_Ch10
  ,ADC_Signal_Ch11
  ,ADC_Signal_Ch12
  ,ADC_Signal_Ch13
  ,ADC_Signal_Ch14
  ,ADC_Signal_Ch15
#endif  
  ,ADC_Signal_TS_Temper
  ,ADC_Signal_TS_Vref  
#ifndef MDR_HAS_ADC2
  ,ADC_Signal_TS_VrefBuf
#endif
} MDR_ADC_Signal;

#if MDR_ADC_PIN_CHANNEL_COUNT > 8
  #define MDR_ADC_PinSignal_Last   ADC_Signal_Ch10
#else
  #define MDR_ADC_PinSignal_Last   ADC_Signal_Ch7
#endif

void MDR_ADC_StartSignal(MDR_ADCx_ItemType *ADCx, MDR_ADC_Signal signal, bool cyclic, const MDR_ADCx_CfgLimits *cfgLims);


//  ============    Получение значения сигнала (запуск с ожиданием окончания)   ==============
MDR_ADC_Result MDR_ADC_MeasSignalValue(MDR_ADCx_ItemType *ADCx, MDR_ADC_Signal signal, const MDR_ADCx_CfgLimits *cfgLims);
MDR_ADC_Result MDR_ADC_MeasNextValue(MDR_ADCx_ItemType *ADCx);


//  ============    Запуск синхронных измерений ADC1 и ADC2 ==============
//  Запуск сигнала
void MDR_ADC_StartSignalSyncro(MDR_ADC_Signal signalADC1, MDR_ADC_Signal signalADC2, bool cyclic, 
   const MDR_ADCx_CfgLimits *cfgLimsADC1, const MDR_ADCx_CfgLimits *cfgLimsADC2);

//  Запуск по маске
void MDR_ADC_StartSelectedSyncro(MDR_ADC_Select_PinChannels channelsADC1, MDR_ADC_Select_PinChannels channelsADC2, bool cyclic, 
  const MDR_ADCx_CfgLimits *cfgLimsADC1, const MDR_ADCx_CfgLimits *cfgLimsADC2);

//  Повтор предыдущего одиночного запуска
#define MDR_ADC_StartNextGoSyncro()   MDR_ADC_StartNextGo(MDR_ADC1)



#endif  // _MDR_ADC_H


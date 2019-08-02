#include <MDR_ADC.h>


//  ============    Управление настройками термосенсора ==============
void MDR_ADC_Clear_CfgThermo(void)
{  
#ifdef MDR_HAS_ADC2
  MDR_ADC->ADC1_Cfg &= ~(MDR_ADC1_Cfg_TS_EN_Msk | MDR_ADC1_Cfg_TR_Msk);  
  MDR_ADC->ADC2_Cfg &= ~(MDR_ADC2_Cfg_ADC1_OP_Msk | MDR_ADC2_Cfg_ADC2_OP_Msk);  
#else
  MDR_ADC->ADC1_Cfg &= ~(MDR_ADC1_Cfg_TS_EN_Msk);
  MDR_ADC->ADC2_Cfg &= ~(MDR_ADC2_Cfg_ADC1_OP_Msk);
  MDR_ADC->ADC1_Trim &= ~(MDR_ADC_TRIM_TS_Trim_Msk);  
#endif 
}

void MDR_ADC_Apply_CfgThermo(const MDR_ADC_CfgThermo *cfgThermo)
{ 
#ifdef MDR_HAS_ADC2
  // Включение и Подстройка
  MDR_ADC->ADC1_Cfg |=  MDR_ADC1_Cfg_TS_EN_Msk
                      | VAL2FLD_Pos(cfgThermo->TrimThermoVref, MDR_ADC1_Cfg_TR_Pos);
  
  //  Выбор Vref от термосенсора для обоих АЦП
  if (cfgThermo->UseThermoVref == MDR_On)
    MDR_ADC->ADC2_Cfg |=  VAL2FLD_Pos(3,   MDR_ADC2_Cfg_ADC1_OP_Pos);
  
#else
  // Включение
  MDR_ADC->ADC1_Cfg |=  VAL2FLD_Pos(1,   MDR_ADC1_Cfg_TS_EN_Pos);
  // Подстройка
  MDR_ADC->ADC1_Trim |= VAL2FLD_Pos(cfgThermo->TrimThermoVref, MDR_ADC_TRIM_TS_Trim_Pos);
  
  //  Выбор Vref от термосенсора.
  if (cfgThermo->UseThermoVref == MDR_On)
   MDR_ADC->ADC2_Cfg |=  VAL2FLD_Pos(1,   MDR_ADC2_Cfg_ADC1_OP_Pos);
#endif 
}

void MDR_ADC_Change_CfgThermo(const MDR_ADC_CfgThermo *cfgThermo)
{
  MDR_ADC_Clear_CfgThermo();
  if (cfgThermo != NULL)
    MDR_ADC_Apply_CfgThermo(cfgThermo);
}


//  ============    Управление настройками отдельного ADC ==============
#define CFG_INIT_CLEAR   (uint32_t) (  MDR_ADCx_Cfg_CLKS_Msk     \
                                     | MDR_ADCx_Cfg_M_REF_Msk    \
                                     | MDR_ADCx_Cfg_DIV_CLK_Msk  \
                                     | MDR_ADC1_Cfg_Delay_GO_Msk)

void MDR_ADC_Clear_CfgBase(MDR_ADCx_ItemType *ADCx)
{
  ADCx->ADCx_Cfg &= ~CFG_INIT_CLEAR;
}

void MDR_ADC_Apply_CfgBase(MDR_ADCx_ItemType *ADCx, const MDR_ADCx_CfgBase * cfgBase)
{
  uint32_t regCfg = ADCx->ADCx_Cfg;  
  regCfg |=   VAL2FLD_Pos(cfgBase->ClockSource,      MDR_ADCx_Cfg_CLKS_Pos)
            | VAL2FLD_Pos(cfgBase->MagRefExternal,   MDR_ADCx_Cfg_M_REF_Pos)
            | VAL2FLD_Pos(cfgBase->CPU_ClockDiv,     MDR_ADCx_Cfg_DIV_CLK_Pos)
            | VAL2FLD_Pos(cfgBase->SwitchDelay_GO,   MDR_ADC1_Cfg_Delay_GO_Pos);
  
#ifdef MDR_HAS_ADC2
  if (ADCx == MDR_ADC2)
    regCfg &= MDR_ADC2_AVALABLE_BITS;
#endif
  
  ADCx->ADCx_Cfg = regCfg;
}

void MDR_ADC_Change_CfgBase(MDR_ADCx_ItemType *ADCx, const MDR_ADCx_CfgBase * cfgBase)
{
  MDR_ADC_Clear_CfgBase(ADCx);
  if (cfgBase != NULL)
    MDR_ADC_Apply_CfgBase(ADCx, cfgBase);
}

//  ============    Настройка прерываний ==============
void MDR_ADC_Clear_CfgIRQ(MDR_ADCx_ItemType *ADCx)
{
  ADCx->ADCx_Status &= ~(MDR_ADC_STATUS_AWOIF_IE_Msk | MDR_ADC_STATUS_EOCIF_EN_Msk);
}

void MDR_ADC_Apply_CfgIRQ(MDR_ADCx_ItemType *ADCx, const MDR_ADCx_CfgIRQ *cfgIRQ)
{
  ADCx->ADCx_Status |=  VAL2FLD_Pos(cfgIRQ->OnResult_IRQEna, MDR_ADC_STATUS_EOCIF_EN_Pos)
                      | VAL2FLD_Pos(cfgIRQ->OnLimit_IRQEna,  MDR_ADC_STATUS_AWOIF_IE_Pos);
}

void MDR_ADC_Change_CfgIRQ(MDR_ADCx_ItemType *ADCx, const MDR_ADCx_CfgIRQ * cfgIRQ)
{
  MDR_ADC_Clear_CfgIRQ(ADCx);
  if (cfgIRQ != NULL)
    MDR_ADC_Apply_CfgIRQ(ADCx, cfgIRQ);
}

#ifdef MDR_HAS_ADC2
//  ============    Управление синхронным запуском ADC1 и ADC2 ==============
void MDR_ADC_Clear_CfgSync(void)
{  
  MDR_ADC->ADC1_Cfg &= ~(MDR_ADC1_Cfg_SYNC_CONV_Msk | MDR_ADC1_Cfg_Delay_ADC_Msk);  
}

void MDR_ADC_Apply_CfgSync(const MDR_ADC_CfgSync *cfgSync)
{
  uint32_t regCfg = MDR_ADC->ADC1_Cfg;
  
  regCfg |=  VAL2FLD_Pos(cfgSync->SynMeasADCs_Ena,  MDR_ADC1_Cfg_SYNC_CONV_Pos)
           | VAL2FLD_Pos(cfgSync->DelayBetweenADCs, MDR_ADC1_Cfg_Delay_ADC_Pos);  
  
  MDR_ADC->ADC1_Cfg = regCfg;
}

void MDR_ADC_Change_CfgSync(const MDR_ADC_CfgSync *cfgSync)
{
  MDR_ADC_Clear_CfgSync();
  if (cfgSync != NULL)
    MDR_ADC_Apply_CfgSync(cfgSync);
}
#endif

//  ============    Выставление порогов значений сигнала ==============
void MDR_ADC_Clear_CfgLims(MDR_ADCx_ItemType *ADCx)
{
  ADCx->ADCx_L_Level = 0;
  ADCx->ADCx_H_Level = ADC_MAX_VALUE;
  ADCx->ADCx_Cfg &= ~MDR_ADCx_Cfg_RGNC_Msk;
}

void MDR_ADC_Apply_CfgLims(MDR_ADCx_ItemType *ADCx, const MDR_ADCx_CfgLimits *cfgSync)
{
  ADCx->ADCx_L_Level = cfgSync->LowLevelLim;
  ADCx->ADCx_H_Level = cfgSync->HighLevelLim;
  ADCx->ADCx_Cfg |= VAL2FLD_Pos(MDR_On,  MDR_ADCx_Cfg_RGNC_Pos);
}

void MDR_ADC_Change_CfgLims(MDR_ADCx_ItemType *ADCx, const MDR_ADCx_CfgLimits *cfgSync)
{
  if (cfgSync != NULL)
    MDR_ADC_Apply_CfgLims(ADCx, cfgSync);
  else
    MDR_ADC_Clear_CfgLims(ADCx);
}

//  ============    Полная инициализация блока ==============
void MDR_ADC_ClearRegs(void)
{
  MDR_ADC->ADC1_Cfg = 0;
  MDR_ADC->ADC2_Cfg = 0;
  
  MDR_ADC->ADC1_H_Level = 0;
  MDR_ADC->ADC1_L_Level = 0;
  MDR_ADC->ADC1_Status = 0;
  MDR_ADC->ADC1_CHSEL = 0;

#ifdef MDR_HAS_ADC2  
  MDR_ADC->ADC2_H_Level = 0;
  MDR_ADC->ADC2_L_Level = 0;  
  MDR_ADC->ADC2_Status = 0;
  MDR_ADC->ADC2_CHSEL = 0;
#endif
}

void MDR_ADC_DeInit(void)
{
  //  Включение тактирования
  MDR_ADC_ClockOn();
  //  Обнуление регистров
  MDR_ADC_ClearRegs();  
}

void MDR_ADC_Init(const MDR_ADC_Config *cfg)
{
  //  Включение тактирования и Обнуление регистров
  MDR_ADC_DeInit();
  
  //  Включение блока термосенсора, если не NULL
  if (cfg->pCfgThermo != NULL)
    MDR_ADC_Apply_CfgThermo(cfg->pCfgThermo);
  
  //  Инициализация ADC1, если не NULL
  if (cfg->pCfgADC1 != NULL)
    MDR_ADC_Apply_CfgBase(MDR_ADC1, cfg->pCfgADC1);
  //  Инициализация порогов сигнала
  if (cfg->pCfgLim1 != NULL)
    MDR_ADC_Apply_CfgLims(MDR_ADC1, cfg->pCfgLim1);  
  //  Инициализация прерываний
  if (cfg->pCfgIRQ1 != NULL)
    MDR_ADC_Apply_CfgIRQ(MDR_ADC1, cfg->pCfgIRQ1);
    
#ifdef MDR_HAS_ADC2  
  //  Инициализация ADC2, если не NULL
  if (cfg->pCfgADC2 != NULL)
    MDR_ADC_Apply_CfgBase(MDR_ADC2, cfg->pCfgADC2);
  //  Инициализация порогов сигнала
  if (cfg->pCfgLim2 != NULL)
    MDR_ADC_Apply_CfgLims(MDR_ADC2, cfg->pCfgLim2);
  //  Инициализация прерываний
  if (cfg->pCfgIRQ2 != NULL)
    MDR_ADC_Apply_CfgIRQ(MDR_ADC2, cfg->pCfgIRQ2);  
  
  //  Инициализация синхронного измерения ADC1 и ADC2, если не NULL
  if (cfg->pCfgSync != NULL)
    MDR_ADC_Apply_CfgSync(cfg->pCfgSync);  
#endif  
 
  //  Инициализация прерываний в NVIC, чтобы пользователь не забыл
  if (cfg->ActivateNVIC_IRQ == MDR_On)
  {
    NVIC_EnableIRQ(ADC_IRQn);
    NVIC_SetPriority(ADC_IRQn, cfg->Priority_IRQ);
  }
}


//========================    Вспомогательные внутренние функции  ========================
static void ADC_Enable_loc(MDR_ADCx_ItemType *ADCx, uint32_t regCfg, bool cyclic, const MDR_ADCx_CfgLimits *cfgLims, uint32_t runFlag)
{  
  //  Если заданы лимиты
  if (cfgLims)
  {
    regCfg |= VAL2FLD_Pos(MDR_On, MDR_ADCx_Cfg_RGNC_Pos);
    ADCx->ADCx_H_Level = cfgLims->HighLevelLim;
    ADCx->ADCx_L_Level = cfgLims->LowLevelLim;
  }  
  //  Задание конфигурации ДО установки GO или Sample!
  ADCx->ADCx_Cfg = regCfg;
  
  //  Цикличное преобразование до команды остановки
  if (cyclic)
    regCfg |= VAL2FLD_Pos(MDR_ADC_SAMPLE_CONTINUOUS, MDR_ADCx_Cfg_SAMPLE_Pos);
  
  //  Запуск
  ADCx->ADCx_Cfg = regCfg | runFlag | VAL2FLD_Pos(MDR_On, MDR_ADCx_Cfg_ADON_Pos);
}

static void ADC_Start_loc(MDR_ADCx_ItemType *ADCx, uint32_t regCfg, bool cyclic, const MDR_ADCx_CfgLimits *cfgLims)  
{
  ADC_Enable_loc(ADCx, regCfg, cyclic, cfgLims, VAL2FLD_Pos(MDR_On, MDR_ADCx_Cfg_GO_Pos));
}


#define CFG_START_CLEAR   (uint32_t)(  MDR_ADCx_Cfg_ADON_Msk    \
                                     | MDR_ADCx_Cfg_GO_Msk      \
                                     | MDR_ADCx_Cfg_SAMPLE_Msk  \
                                     | MDR_ADCx_Cfg_CHS_Msk     \
                                     | MDR_ADCx_Cfg_CHCH_Msk    \
                                     | MDR_ADC1_Cfg_SEL_TS_Msk  \
                                     | MDR_ADC1_Cfg_SEL_VREF_Msk  )


//  ============    Запуск измерения одного канала ==============
void MDR_ADC_StartChannel(MDR_ADCx_ItemType *ADCx, MDR_ADC_PinChannel channel, bool cyclic, const MDR_ADCx_CfgLimits *cfgLims)
{
  uint32_t regCfg = ADCx->ADCx_Cfg;
  
  //  Измерение одного канала
  regCfg &= ~CFG_START_CLEAR;  
  regCfg |= VAL2FLD_Pos(channel, MDR_ADCx_Cfg_CHS_Pos);
  
  ADC_Start_loc(ADCx, regCfg, cyclic, cfgLims);
}  

//  ============    Запуск измерения нескольких каналов ==============
void MDR_ADC_StartSelected(MDR_ADCx_ItemType *ADCx, MDR_ADC_Select_PinChannels channelSelected, bool cyclic, const MDR_ADCx_CfgLimits *cfgLims)
{
  uint32_t regCfg = ADCx->ADCx_Cfg;
  
  //  Измерение нескольких каналов
  regCfg &= ~CFG_START_CLEAR;
  regCfg |= VAL2FLD_Pos(MDR_On, MDR_ADCx_Cfg_CHCH_Pos);
  ADCx->ADCx_CHSEL = channelSelected.Select;

  //  Запуск
  ADC_Start_loc(ADCx, regCfg, cyclic, cfgLims);
}


//  ==================    Внутренние сигналы от Термосенсора  ===========
static void ADC_Init_ThermoSignal(MDR_ADC_ThermoSignal thermoSignal)
{
  uint32_t regCfg = MDR_ADC->ADC1_Cfg;
  
  //  Включение буферного усилителя
  regCfg |= VAL2FLD_Pos(MDR_On,   MDR_ADC1_Cfg_TS_BUFF_EN_Pos);  

  // Выбор выходного сигнала термосенсора
#ifdef MDR_HAS_ADC2
  regCfg |=  VAL2FLD_Pos(thermoSignal + 1, MDR_ADC1_Cfg_SEL_TS_Pos);                  //  SEL_TS or SEL_Vref 
#else
  if (thermoSignal <= MDR_ADC_ThermoSig_Vref)
    regCfg |= VAL2FLD_Pos(thermoSignal + 1, MDR_ADC1_Cfg_SEL_TS_Pos);                 //  SEL_TS or SEL_Vref
  else
    MDR_ADC->ADC1_Trim |= VAL2FLD_Pos(MDR_On, MDR_ADC_TRIM_SEL_VREF_BUF_Pos);         //  SEL_Vref_Buf
#endif
  
  MDR_ADC->ADC1_Cfg = regCfg;
}

void MDR_ADC_Exit_ThermoSignal(void)
{
#ifdef MDR_HAS_ADC2
  MDR_ADC->ADC1_Cfg &= ~(MDR_ADC1_Cfg_TS_BUFF_EN_Msk | MDR_ADC1_Cfg_SEL_TS_Msk | MDR_ADC1_Cfg_SEL_TS_Msk | MDR_ADC1_Cfg_SEL_VREF_Msk);  
#else
  MDR_ADC->ADC1_Cfg &= ~(MDR_ADC1_Cfg_TS_BUFF_EN_Msk | MDR_ADC1_Cfg_SEL_TS_Msk | MDR_ADC1_Cfg_SEL_VREF_Msk);  
  MDR_ADC->ADC1_Trim &= ~(MDR_ADC_TRIM_SEL_VREF_BUF_Msk);
#endif  
}

void MDR_ADC_StartThermoSignal(MDR_ADCx_ItemType *ADCx, MDR_ADC_ThermoSignal thermoSignal, bool cyclic, const MDR_ADCx_CfgLimits *cfgLims)
{
  //  Выключение текущего режима
  uint32_t regCfg = ADCx->ADCx_Cfg;
  regCfg &= ~CFG_START_CLEAR;
  ADCx->ADCx_Cfg = regCfg;

  //  Включение сигнала термосенсора
  ADC_Init_ThermoSignal(thermoSignal);
  
  //  Выбор канала с термосенсора
  regCfg = ADCx->ADCx_Cfg;
  if (thermoSignal == MDR_ADC_ThermoSig_Temper)
    regCfg |= VAL2FLD_Pos(MDR_ADC_ChTS_Temper, MDR_ADCx_Cfg_CHS_Pos); // ch = 31 - themperature
  else
    regCfg |= VAL2FLD_Pos(MDR_ADC_ChTS_Vref, MDR_ADCx_Cfg_CHS_Pos);   // ch = 30 - vref 
  
  //  Запуск
  ADC_Start_loc(ADCx, regCfg, cyclic, cfgLims);
}

void MDR_ADC_StartThermoSignalSelected(MDR_ADCx_ItemType *ADCx, MDR_ADC_ThermoSignal thermoSignal, bool cyclic, const MDR_ADCx_CfgLimits *cfgLims)
{
  //  Выключение текущего режима
  uint32_t regCfg = ADCx->ADCx_Cfg;
  regCfg &= ~CFG_START_CLEAR;
  ADCx->ADCx_Cfg = regCfg;

  //  Включение сигнала термосенсора
  ADC_Init_ThermoSignal(thermoSignal);
  
  //  Выбор канала с термосенсора
  regCfg = ADCx->ADCx_Cfg;
  regCfg |= VAL2FLD_Pos(MDR_On, MDR_ADCx_Cfg_CHCH_Pos);
  if (thermoSignal == MDR_ADC_ThermoSig_Temper)
    MDR_ADC->ADC1_CHSEL = (uint32_t)(1UL << (uint32_t)MDR_ADC_ChTS_Temper);
  else
    MDR_ADC->ADC1_CHSEL = (uint32_t)(1UL << (uint32_t)MDR_ADC_ChTS_Vref);  

  //  Запуск
  ADC_Start_loc(ADCx, regCfg, cyclic, cfgLims);
}


//  ============    Чтение/сброс статуса статуса ==============
MDR_ADC_Status MDR_ADC_GetStatus(MDR_ADCx_ItemType *ADCx)
{
  MDR_ADC_Status res;
  res.Status = ADCx->ADCx_Status;
  return res;
}


//  ============    Чтение результата ==============
MDR_ADC_Result MDR_ADC_GetResult(MDR_ADCx_ItemType *ADCx)
{
  MDR_ADC_Result res;
  res.Result = ADCx->ADCx_Result;
  return res;
}


MDR_ADC_Result MDR_ADC_WaitAndGetResult(MDR_ADCx_ItemType *ADCx)
{
  while (MDR_ADC_GetStatus(ADCx).Flags.Ready != MDR_On);
  
  return MDR_ADC_GetResult(ADCx);
}

MDR_ADC_Result MDR_ADC_WaitAndGetResultEx(MDR_ADCx_ItemType *ADCx, MDR_ADC_Status *status)
{
  MDR_ADC_Status stat;
  do
    stat.Status = ADCx->ADCx_Status;
  while (stat.Flags.Ready != MDR_On);
  
  if (status != NULL)
    status->Status = stat.Status;
  
  return MDR_ADC_GetResult(ADCx);
}

//  ============    Получение значения с канала с ожиданием   ==============
MDR_ADC_Result MDR_ADC_MeasSignalValue(MDR_ADCx_ItemType *ADCx, MDR_ADC_Signal signal, const MDR_ADCx_CfgLimits *cfgLims)
{
  MDR_ADC_StartSignal(ADCx, signal, false, cfgLims);
  return MDR_ADC_WaitAndGetResult(ADCx);
}

MDR_ADC_Result MDR_ADC_MeasNextValue(MDR_ADCx_ItemType *ADCx)
{
  MDR_ADC_StartNextGo(ADCx);
  return MDR_ADC_WaitAndGetResult(ADCx);
}

//  ============    ADC Signals ==============
void MDR_ADC_StartSignal(MDR_ADCx_ItemType *ADCx, MDR_ADC_Signal signal, bool cyclic, const MDR_ADCx_CfgLimits *cfgLims)
{
  static bool isThermoSignalActive = false;
  
  if (signal < ADC_Signal_TS_Temper)
  {
    if (isThermoSignalActive)
    {
      MDR_ADC_Exit_ThermoSignal();
      isThermoSignalActive = false;
    }
    MDR_ADC_StartChannel(ADCx, (MDR_ADC_PinChannel)(signal), cyclic, cfgLims);
  }
  else
  { 
    isThermoSignalActive = true;
    MDR_ADC_StartThermoSignal(ADCx, (MDR_ADC_ThermoSignal)(signal - ADC_Signal_TS_Temper), cyclic, cfgLims);
  } 
}

#ifdef MDR_HAS_ADC2
//  ============    Syncro Start ADC1-ADC2 ==============
void MDR_ADC_StartSignalSyncro(MDR_ADC_Signal signalADC1, MDR_ADC_Signal signalADC2, bool cyclic, 
   const MDR_ADCx_CfgLimits *cfgLimsADC1, const MDR_ADCx_CfgLimits *cfgLimsADC2)
{
  uint32_t regCfg = MDR_ADC->ADC2_Cfg;
  
  //  Выключение АЦП2, если был включен
  regCfg &= ~CFG_START_CLEAR;
  MDR_ADC->ADC2_Cfg = regCfg;
  
  //  Выбор канала  
  if (signalADC2 < ADC_Signal_TS_Temper)
    regCfg |=  VAL2FLD_Pos(signalADC2, MDR_ADCx_Cfg_CHS_Pos);
  else if (signalADC2 == ADC_Signal_TS_Temper)
    regCfg |= VAL2FLD_Pos(MDR_ADC_ChTS_Temper, MDR_ADCx_Cfg_CHS_Pos); // ch = 31 - themperature
  else
    regCfg |= VAL2FLD_Pos(MDR_ADC_ChTS_Vref, MDR_ADCx_Cfg_CHS_Pos);   // ch = 30 - vref 

  //  Включение АЦП2
  ADC_Enable_loc(MDR_ADC2, regCfg, cyclic, cfgLimsADC2, 0);
   
  MDR_ADC_StartSignal(MDR_ADC1, signalADC1, cyclic, cfgLimsADC1);
}

//  Запуск каналов по маске
void MDR_ADC_StartSelectedSyncro(MDR_ADC_Select_PinChannels channelsADC1, MDR_ADC_Select_PinChannels channelsADC2, bool cyclic, 
  const MDR_ADCx_CfgLimits *cfgLimsADC1, const MDR_ADCx_CfgLimits *cfgLimsADC2)
{
  uint32_t regCfg = MDR_ADC->ADC2_Cfg;
  
  //  Выключение АЦП2, если был включен
  regCfg &= ~CFG_START_CLEAR;
  MDR_ADC->ADC2_Cfg = regCfg;
  
  //  Выбор каналов
  MDR_ADC->ADC2_CHSEL = channelsADC2.Select;
  regCfg |=  VAL2FLD_Pos(MDR_On, MDR_ADCx_Cfg_CHCH_Pos);

  //  Включение АЦП2
  ADC_Enable_loc(MDR_ADC2, regCfg, cyclic, cfgLimsADC2, 0);  
  
  //  Запуск через АЦП1
  MDR_ADC_StartSelected(MDR_ADC1, channelsADC1, cyclic, cfgLimsADC1);
}
#endif




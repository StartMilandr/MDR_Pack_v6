#ifndef MDR_ADCUI_VE4_H
#define MDR_ADCUI_VE4_H

#include <MDR_Config.h>
#include <MDR_Types.h>
#include <MDR_Funcs.h>

#include <MDR_ADCUI_VE4_CfgRegs.h>


//-------------------   Инициализация -------------------
//  ВАРИАНТ1: (Простейшая)
//  Настройка ADCUI по умолчанию - без DMA и усилений, 
//  прерывание по готовности данных и подавление постоянной составляющей для всех каналов одинаково.
void MDR_ADCUI_InitDef        (MDR_ADCUI_SelCH chanSelect, bool enaIrqOnReady, bool suppressDC, bool useExternalVRef, MDR_ADCUI_Decim decimSamplRate);
void MDR_ADCUI_InitDefAndStart(MDR_ADCUI_SelCH chanSelect, bool enaIrqOnReady, bool suppressDC, bool useExternalVRef, MDR_ADCUI_Decim decimSamplRate);


//  ВАРИАНТ2:
//  Одинаковая настройка каналов, выбранных маской chanSelect
//  doStart - запуск каналов после инициализации
typedef struct {
  bool            suppressDC;
  bool            enaIrqOnReady;
  bool            enaIrqOnOver;
  bool            enaDMA;
  MDR_ADCUI_Decim decimSamplRate;
} MDR_ADCUI_Cfg;

void MDR_ADCUI_Init(MDR_ADCUI_SelCH chanSelect, MDR_ADCUI_Cfg *Cfg, bool useExternalVRef, bool doStart);


//  ВАРИАНТ3:
//  Настройка и запуск ADCUI - c заданием настроек для каждого канала
//  chSel_DoStart - запуск каналов после инициализации

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wpadded"
#endif

typedef struct {
  MDR_ADCUI_SelCH   chSel_DoStart;
  MDR_ADCUI_SelCH   chSel_SuppressDC;
  MDR_ADCUI_SelCH   chSel_EnaIRQ_OnReady;
  MDR_ADCUI_SelCH   chSel_EnaIRQ_OnOver;
  MDR_ADCUI_SelCH   chSel_EnaDMA;
  MDR_ADCUI_GainCH  gains;
  MDR_OnOff         useExternalVRef;
  MDR_ADCUI_Decim   decimSamplRate;
} MDR_ADCUI_CfgFull;

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic pop  
#endif

//  Расширенная настройка с указанием коррекции фильтров - 
//  Использовать для экспериментов, если штатная настройка не устраивает 
//  и есть желание как-то повлиять на поведение.
//  Для значений по умолчанию задавать в MDR_ADCUI_InitEx как NULL
typedef struct {
  MDR_ADCUI_Decim   decimSamplRate;            /*!< [9..7] Sinc Filter Rough correction */  
  uint8_t           decimSamplRate_Fine;       /*!< [6..0] Sinc Filter Fine correction  */
} MDR_ADCUI_CfgEx;

void MDR_ADCUI_InitEx(MDR_ADCUI_CfgFull *cfg, MDR_ADCUI_CfgEx *cfgEx);


//  ВАРИАНТ4: (Самый быстрый, напрямую в регистры)
void MDR_ADCUI_InitByCfgRegs(MDR_ADCUI_CfgRegs *cfgRegs);

//-------------------   Прочие функции  -------------------
//  Отключение блока - запускать если была инициализация, блок должен быть затактирован!
void MDR_ADCUI_DeInit(void);

//  Start/Stop channel
__STATIC_INLINE void MDR_ADCUI_ShartChannel(MDR_ADCUI_CH ch) { MDR_ADCUI->CTRL1 |=   1 << (MDR_ADCUI_CTRL1_ADC1_EN_Msk + (uint32_t)ch) ; }
__STATIC_INLINE void MDR_ADCUI_StopChannel (MDR_ADCUI_CH ch) { MDR_ADCUI->CTRL1 &= ~(1 << (MDR_ADCUI_CTRL1_ADC1_EN_Msk + (uint32_t)ch)); }

__STATIC_INLINE void MDR_ADCUI_ShartChannelSel(MDR_ADCUI_SelCH  SelChs) { MDR_ADCUI->CTRL1 |=  SelChs.Value; }
__STATIC_INLINE void MDR_ADCUI_StopChannelSel (MDR_ADCUI_SelCH  SelChs) { MDR_ADCUI->CTRL1 &= ~SelChs.Value; }


//  IRQ
__STATIC_INLINE void MDR_ADCUI_EnableIRQ (MDR_ADCUI_SelCH  SelChs) { MDR_ADCUI->INTEN |=  SelChs.Value; }
__STATIC_INLINE void MDR_ADCUI_DisableIRQ(MDR_ADCUI_SelCH  SelChs) { MDR_ADCUI->INTEN &= ~SelChs.Value; }

__STATIC_INLINE void MDR_ADCUI_EnableIRQ_ALL (void) { MDR_ADCUI->INTEN = MDR_ADCUI_SEL_CH_ALL; }
__STATIC_INLINE void MDR_ADCUI_DisableIRQ_ALL(void) { MDR_ADCUI->INTEN = 0; }

//	Включение соответствующего прерывания в NVIC
#define _ADCUI_TO_IRQn(irq, ival)  ((IRQn_Type)((uint32_t)(irq) + (ival)))

__STATIC_INLINE
void MDR_ADCUI_NVIC_EnableIRQ(MDR_ADCUI_CH ch, uint32_t priorityIRQ)
{
  NVIC_EnableIRQ(_ADCUI_TO_IRQn(ADCUI_CH1_IRQn, ch));
  NVIC_SetPriority(_ADCUI_TO_IRQn(ADCUI_CH1_IRQn, ch), priorityIRQ);
}

__STATIC_INLINE
void MDR_ADCUI_NVIC_DisableIRQ(MDR_ADCUI_CH ch)
{
  NVIC_DisableIRQ(_ADCUI_TO_IRQn(ADCUI_CH1_IRQn, ch));
}


//  DMA
__STATIC_INLINE void MDR_ADCUI_EnableDMA (MDR_ADCUI_SelCH  SelChs) { MDR_ADCUI->DMAEN |= SelChs.Value; }
__STATIC_INLINE void MDR_ADCUI_DisableDMA(MDR_ADCUI_SelCH  SelChs) { MDR_ADCUI->DMAEN &= ~SelChs.Value; }

__STATIC_INLINE void MDR_ADCUI_EnableDMA_ALL (void) { MDR_ADCUI->DMAEN = MDR_ADCUI_SEL_CH_ALL; }
__STATIC_INLINE void MDR_ADCUI_DisableDMA_ALL(void) { MDR_ADCUI->DMAEN = 0; }


//  Status
__STATIC_INLINE uint32_t MDR_ADCUI_GetStatus(void) { return MDR_ADCUI->STAT; }
__STATIC_INLINE bool     MDR_ADCUI_GetStatusFlagSet(uint32_t flagSel) { return (MDR_ADCUI->STAT & flagSel) == flagSel; }

__STATIC_INLINE bool     MDR_ADCUI_CanReadData(MDR_ADCUI_CH ch) { return MDR_ADCUI_GetStatusFlagSet(1 << (MDR_ADCUI_EVENT_NS1_Pos + (uint32_t)ch)); }
__STATIC_INLINE bool     MDR_ADCUI_IsFIFO_Over(MDR_ADCUI_CH ch) { return MDR_ADCUI_GetStatusFlagSet(1 << (MDR_ADCUI_EVENT_OV1_Pos + (uint32_t)ch)); }

__STATIC_INLINE void     MDR_ADUI_ClearFIFO_Over(MDR_ADCUI_CH ch) { MDR_ADCUI->STAT |= (1 << (MDR_ADCUI_EVENT_OV1_Pos + (uint32_t)ch)); }
__STATIC_INLINE void     MDR_ADUI_ClearFIFO_OverALL(void)         { MDR_ADCUI->STAT |= MDR_ADCUI_EVENT_CLR_OV_ALL; }


//  Data
__STATIC_INLINE int32_t MDR_ADCUI_ReadData(MDR_ADCUI_CH ch) 
{ 
  volatile uint32_t result = MDR_ADCUI->DAT[(uint32_t)ch] << MDR_ADCUI_SIGN_OFFS;
  return (int32_t)(result) >> MDR_ADCUI_SIGN_OFFS;
}

//  Gain
__STATIC_INLINE void MDR_ADCUI_SetGain (MDR_ADCUI_CH ch, MDR_ADCUI_PGA gain) 
{ MDR_ADCUI->ANGAIN = MDR_MaskClrSet(MDR_ADCUI->ANGAIN, MDR_ADCUI_ANGAIN_CH_CLR(ch), ((uint32_t)gain) << MDR_ADCUI_ANGAIN_CH_OFFS(ch)); }

//  Decim
void MDR_ADCUI_ChangeDecim (MDR_ADCUI_Decim decim);


//  ----------    Вспомогательные функции ----------
__STATIC_INLINE void MDR_ADCUI_ClockEnable (void) { MDR_CLOCK->PER2_CLOCK |=  MDR_RST_PER2__ADCIU_CLK_EN_Msk; }
__STATIC_INLINE void MDR_ADCUI_ClockDisable(void) { MDR_CLOCK->PER2_CLOCK &= ~MDR_RST_PER2__ADCIU_CLK_EN_Msk; }

__STATIC_INLINE MDR_ADCUI_SelCH MDR_ADCUI_ChanToSelCH(MDR_ADCUI_CH ch)
{
  MDR_ADCUI_SelCH result = {.Value = 1 << (uint32_t)ch};
  return result;
}

__STATIC_INLINE MDR_ADCUI_SelCH MDR_ADCUI_SelIntToSelCH(uint32_t chSel)
{
  MDR_ADCUI_SelCH result = {.Value = chSel & 0xFFUL};
  return result;
}



#endif // MDR_ADCUI_VE4_H


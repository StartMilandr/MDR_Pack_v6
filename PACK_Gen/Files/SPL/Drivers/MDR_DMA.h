#ifndef MDR_DMA_H
#define MDR_DMA_H

#include <MDR_Config.h>
#include <MDR_Types.h>
#include <MDR_DMA_defs.h>
#include <MDR_Funcs.h>

// ==============  Общая инициализация блока DMA ================
#if !USE_DMA_USER_CNTLS_CTRL_TABLE
  //  Функции Init сами включают тактирование!
  //  Инициализация DMA с правами доступа к таблице управляющих структур каналов по умолчанию
  void MDR_DMA_Init(void);

  //  Инициализация DMA с заданием прав доступа к таблице управляющих структур каналов
  void MDR_DMA_InitProtAHB(MDR_DMA_ProtAHB chnlsTableAccess);
#endif

//  Инициализация DMA с пользовательским расположением управляющи структур каналов и привилегиями доступа
//  Использовать с запретом собственной глобальной структуры USE_DMA_USER_CNTLS_CTRL_TABLE в MDR_Config 
void MDR_DMA_InitProtEx(const MDR_DMA_ChCfg *channelsCtrlTable,  MDR_DMA_ProtAHB chnlsTableAccess);

//  Деинициализация DMA, выключает тактирование блока
void MDR_DMA_DeInit(void);


//  ============   Инициализация каналов DMA   ======================
typedef struct { 
  // Data copy params
  uint32_t          SrcAddr;
  uint32_t          DestAddr;
  uint32_t          Count;
  MDR_DMA_DataSize  DataSize;
  MDR_DMA_AddrInc   Src_AddrInc;
  MDR_DMA_AddrInc   Dest_AddrInc;
  //  DMA
  MDR_DMA_Mode      Mode;
  MDR_OnOff         UseBurst;
  MDR_DMA_Arbitr    ArbitrCount;  
  //  NULL for default
  MDR_DMA_ProtAHB   *Src_ProtAHB;
  MDR_DMA_ProtAHB   *Dest_ProtAHB;
  //  IRQ
  bool              activateNVIC;
  uint32_t          priority;
} MDR_DMA_Init_ChStruct;

//  Функции возвращают контрольное слово, которое потребуется для перезапуска следующего цикла DMA.
MDR_DMA_ChCtrl  MDR_DMA_InitChannelPri(uint32_t chIndex, const MDR_DMA_Init_ChStruct *initCh);
MDR_DMA_ChCtrl  MDR_DMA_InitChannelAlt(uint32_t chIndex, const MDR_DMA_Init_ChStruct *initCh);


//  Инициализация через более лаконичную структуру, идентичную структуре в железе за исключением IRQ
typedef struct {
  //  DMA
  uint32_t          Src_EndAddr;
  uint32_t          Dest_EndAddr;
  MDR_DMA_ChCtrl    Control;
  //  IRQ
  bool              activateNVIC;
  uint32_t          priority;  
} MDR_DMA_Init_ChCfg;

//  Рассчет конечного адреса из стартового
uint32_t MDR_DMA_Calc_SrcEndAddr (uint32_t startAddr, MDR_DMA_AddrInc AddrInc, uint32_t dataCount);
uint32_t MDR_DMA_Calc_DestEndAddr(uint32_t startAddr, MDR_DMA_AddrInc AddrInc, uint32_t dataCount, MDR_DMA_Mode mode);

//  Функции возвращают контрольное слово, которое потребуется для перезапуска следующего цикла DMA.
MDR_DMA_ChCtrl  MDR_DMA_InitChannelCfgPri(uint32_t chIndex, const MDR_DMA_Init_ChCfg *initChCfg);
MDR_DMA_ChCtrl  MDR_DMA_InitChannelCfgAlt(uint32_t chIndex, const MDR_DMA_Init_ChCfg *initChCfg);


//  Запуск работы канала и остановка
void  MDR_DMA_StartChannel(uint32_t chIndex, MDR_OnOff IgnoreSReq, MDR_OnOff HighPriority, bool startWithPrimary);
void  MDR_DMA_StartChannelSoft(uint32_t chIndex, MDR_OnOff HighPriority, bool startWithPrimary);
void  MDR_DMA_StopChannel (uint32_t chIndex);

//  Проверка закончил ли канал работу
__STATIC_INLINE bool  MDR_DMA_GetChannelCompleted(uint32_t chIndex)           {return (MDR_DMA->CHNL_ENABLE_SET & (1 << chIndex)) == 0;}
__STATIC_INLINE bool  MDR_DMA_GetChannelCompletedSel(uint32_t selectChannels) {return (MDR_DMA->CHNL_ENABLE_SET & selectChannels) == 0;}

//  Програмный запрос на передачу слова
__STATIC_INLINE void MDR_DMA_SendSoftReq(uint32_t chIndex) {MDR_DMA->CHNL_SW_REQUEST = 1 << chIndex;}


//  Вспомогательные функции доступа к контрольному слову канала
#define MDR_DMA_CtrlTablePri(ch)    ((MDR_DMA_ChCfg *)MDR_DMA->CTRL_BASE_PTR)[ch]
#define MDR_DMA_CtrlTableAlt(ch)    ((MDR_DMA_ChCfg *)MDR_DMA->ALT_CTRL_BASE_PTR)[ch]

__STATIC_INLINE void MDR_DMA_SetChCtrlPri(uint32_t chIndex, uint32_t value)
  {  MDR_DMA_CtrlTablePri(chIndex).Control.Value = value;}
  
__STATIC_INLINE void MDR_DMA_SetChCtrlAlt(uint32_t chIndex, uint32_t value)
  {  MDR_DMA_CtrlTableAlt(chIndex).Control.Value = value;}
  
__STATIC_INLINE MDR_DMA_ChCtrl   MDR_DMA_GetChCtrlPri(uint32_t chIndex)
  {  return MDR_DMA_CtrlTablePri(chIndex).Control;}
  
__STATIC_INLINE MDR_DMA_ChCtrl   MDR_DMA_GetChCtrlAlt(uint32_t chIndex)
  {  return MDR_DMA_CtrlTableAlt(chIndex).Control;}


//  Перезапуск следующего цикла DMA
//  Обновляет контрольное слово в упр. структуре и выставляет Enable!
void  MDR_DMA_RunNextCyclePri(uint32_t chIndex, MDR_DMA_ChCtrl chCtrl);
void  MDR_DMA_RunNextCycleAlt(uint32_t chIndex, MDR_DMA_ChCtrl chCtrl);

//  Обновляет контрольное слово в упр. структуре и НЕ выставляет Enable! (для Ping-Pong)
__STATIC_INLINE void MDR_DMA_InitNextCyclePri(uint32_t chIndex, MDR_DMA_ChCtrl chCtrl) {MDR_DMA_SetChCtrlPri(chIndex, chCtrl.Value);}
__STATIC_INLINE void MDR_DMA_InitNextCycleAlt(uint32_t chIndex, MDR_DMA_ChCtrl chCtrl) {MDR_DMA_SetChCtrlAlt(chIndex, chCtrl.Value);}

//  Выбор активной структуры
__STATIC_INLINE void MDR_DMA_SetActivePri(uint32_t chIndex, bool setActive) 
  { if (setActive) MDR_DMA->CHNL_PRI_ALT_CLR = 1 << chIndex; else MDR_DMA->CHNL_PRI_ALT_SET = 1 << chIndex;}

//   
__STATIC_INLINE bool MDR_DMA_GetCycleCompletedPri(uint32_t chIndex) {return (MDR_DMA_GetChCtrlPri(chIndex).Value & MDR_DMA_ChCtrl_Mode_Msk) == DMA_MODE_Stop;}
__STATIC_INLINE bool MDR_DMA_GetCycleCompletedAlt(uint32_t chIndex) {return (MDR_DMA_GetChCtrlAlt(chIndex).Value & MDR_DMA_ChCtrl_Mode_Msk) == DMA_MODE_Stop;}


//  Готовые функции копирования массивов с использованием DMA
//  Необходима предварительная инициализация блока - MDR_DMA_Init()
void MDR_DMA_CopyStart8 (uint32_t chIndex, uint8_t  *src, uint8_t  *dest, uint16_t count);
void MDR_DMA_CopyStart16(uint32_t chIndex, uint16_t *src, uint16_t *dest, uint16_t count);
void MDR_DMA_CopyStart32(uint32_t chIndex, uint32_t *src, uint32_t *dest, uint16_t count);

#define MDR_DMA_CopyGetCompleted(ch)        MDR_DMA_GetChannelCompleted(ch)
#define MDR_DMA_CopyGetCompletedSel(chSel)  MDR_DMA_GetChannelCompletedSel(chSel)

void MDR_DMA_Copy8 (uint32_t chIndex, uint8_t  *src, uint8_t  *dest, uint16_t count);
void MDR_DMA_Copy16(uint32_t chIndex, uint16_t *src, uint16_t *dest, uint16_t count);
void MDR_DMA_Copy32(uint32_t chIndex, uint32_t *src, uint32_t *dest, uint16_t count);


#endif // MDR_DMA_H


#ifndef MDR_POWER_H
#define MDR_POWER_H

#include <MDR_Config.h>
#include <MDR_Types.h>
#include <MDR_Funcs.h>


//  Инициализация блока
typedef struct {
  // Ucc
  MDR_PWR_LevelUcc          levelUcc;
  MDR_OnOff                 enaEventUccIRQ;
  MDR_Power_EventCondition  condEventUcc;

  //  BUcc
  MDR_PWR_LevelBUcc         levelBUcc;
  MDR_OnOff                 enaEventBUccIRQ;
  MDR_Power_EventCondition  condEventBUcc;
  
  //  NVIC IRQ enable
  bool                      activateNVIC_IRQ; 
  uint32_t                  priorityIRQ;
} MDR_Power_Cfg;

void MDR_Power_Init(const MDR_Power_Cfg *cfgPWR);

void MDR_Power_InitReg(const MDR_Power_CtrlAndStatus cfgPWR, bool activateNVIC_IRQ, uint32_t priorityIRQ);
void MDR_Power_DeInit(void);


//  Выставление пороговых уровней
__STATIC_INLINE void MDR_Power_ChangeLevelUcc (MDR_PWR_LevelUcc levelUcc)   
  {MDR_POWER->PVDCS = MaskClrSet(MDR_POWER->PVDCS, MDR_PWR_PVDCS_PLS_Msk,  VAL2FLD_Pos(levelUcc,  MDR_PWR_PVDCS_PLS_Pos));}
  
__STATIC_INLINE void MDR_Power_ChangeLevelBUcc(MDR_PWR_LevelBUcc levelBUcc) 
  {MDR_POWER->PVDCS = MaskClrSet(MDR_POWER->PVDCS, MDR_PWR_PVDCS_PBLS_Msk, VAL2FLD_Pos(levelBUcc, MDR_PWR_PVDCS_PBLS_Pos));}


//  Изменение условия срабатывания событий
__STATIC_INLINE void MDR_Power_ChangeEventCondUcc(MDR_Power_EventCondition eventCond)  
  {MDR_POWER->PVDCS = MaskClrSet(MDR_POWER->PVDCS, MDR_PWR_PVDCS_INV_Msk,  VAL2FLD_Pos(eventCond, MDR_PWR_PVDCS_INV_Pos));}
  
__STATIC_INLINE void MDR_Power_ChangeEventCondBUcc(MDR_Power_EventCondition eventCond) 
  {MDR_POWER->PVDCS = MaskClrSet(MDR_POWER->PVDCS, MDR_PWR_PVDCS_INVB_Msk, VAL2FLD_Pos(eventCond, MDR_PWR_PVDCS_INVB_Pos));}


//  Доступ к Флагам событий
MDR_Power_CtrlAndStatus  MDR_Power_GetStatus(void);

#define PWR_EVENT_Ucc    MDR_PWR_PVDCS_PVD_Msk
#define PWR_EVENT_BUcc   MDR_PWR_PVDCS_PVBD_Msk

__STATIC_INLINE bool     MDR_Power_GetEventUcc(void)  {return MDR_POWER->PVDCS & PWR_EVENT_Ucc;}
__STATIC_INLINE bool     MDR_Power_GetEventBUcc(void) {return MDR_POWER->PVDCS & PWR_EVENT_BUcc;}


__STATIC_INLINE void     MDR_Power_ClearEvents(void)
{
  MDR_POWER->PVDCS &= (uint32_t) ~(PWR_EVENT_Ucc | PWR_EVENT_BUcc);
#if USE_PWR_CLR_FIX  
  MDR_POWER->PVDCS &= (uint32_t) ~(PWR_EVENT_Ucc | PWR_EVENT_BUcc);
#endif
}

//  Разрешение/запрет прерываний
__STATIC_INLINE void MDR_Power_EnaIRQ(void)  {MDR_POWER->PVDCS |=  (MDR_PWR_PVDCS_IEPVD_Msk | MDR_PWR_PVDCS_IEPVBD_Msk);}
__STATIC_INLINE void MDR_Power_DisIRQ(void)  {MDR_POWER->PVDCS &= ~(MDR_PWR_PVDCS_IEPVD_Msk | MDR_PWR_PVDCS_IEPVBD_Msk);}

__STATIC_INLINE void MDR_Power_EnaIRQ_Ucc(void)  {MDR_POWER->PVDCS |=  MDR_PWR_PVDCS_IEPVD_Msk;}
__STATIC_INLINE void MDR_Power_DisIRQ_Ucc(void)  {MDR_POWER->PVDCS &= ~MDR_PWR_PVDCS_IEPVD_Msk;}

__STATIC_INLINE void MDR_Power_EnaIRQ_BUcc(void)  {MDR_POWER->PVDCS |=  MDR_PWR_PVDCS_IEPVBD_Msk;}
__STATIC_INLINE void MDR_Power_DisIRQ_BUcc(void)  {MDR_POWER->PVDCS &= ~MDR_PWR_PVDCS_IEPVBD_Msk;}

//  Разрешение - запрет работы блока
__STATIC_INLINE void MDR_Power_Enable(void)  {MDR_POWER->PVDCS |=  MDR_PWR_PVDCS_ENA_MSK;}
__STATIC_INLINE void MDR_Power_Disable(void) {MDR_POWER->PVDCS &= ~MDR_PWR_PVDCS_ENA_MSK;}



#endif // MDR_POWER_H


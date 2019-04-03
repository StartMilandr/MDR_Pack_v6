#include "MDR_Power.h"
    
//  Инициализация блока HAL
void MDR_Power_Init(const MDR_Power_Cfg *cfgPWR)
{
  MDR_Power_CtrlAndStatus regControl;

  regControl.Value =  MDR_PWR_PVDCS_ENA_MSK  
                    | VAL2FLD_Pos(cfgPWR->levelUcc,        MDR_PWR_PVDCS_PLS_Pos)
                    | VAL2FLD_Pos(cfgPWR->enaEventUccIRQ,  MDR_PWR_PVDCS_IEPVD_Pos)
                    | VAL2FLD_Pos(cfgPWR->condEventUcc,    MDR_PWR_PVDCS_INV_Pos)
                    
                    | VAL2FLD_Pos(cfgPWR->levelBUcc,       MDR_PWR_PVDCS_PBLS_Pos)
                    | VAL2FLD_Pos(cfgPWR->enaEventBUccIRQ, MDR_PWR_PVDCS_IEPVBD_Pos)
                    | VAL2FLD_Pos(cfgPWR->condEventBUcc,   MDR_PWR_PVDCS_INVB_Pos);
                      
  MDR_Power_InitReg(regControl, cfgPWR->activateNVIC_IRQ, cfgPWR->priorityIRQ);
}


//  Инициализация блока регистровая
void MDR_Power_InitReg(const MDR_Power_CtrlAndStatus cfgPWR, bool activateNVIC_IRQ, uint32_t priorityIRQ)
{
	//	Clock Enable
  REG32(MDR_PWR_CLK_EN_ADDR) |= MDR_PWR_CLK_EN_MSK;
  //  Apply config
  MDR_POWER->PVDCS = cfgPWR.Value;
  
#ifdef USE_PWR_WR_FIX_VK214  
  // В 1986ВК214 запись 0xC2F отрабатывает не с первого раза
  // Чтение показывает что в регистре значение 0xE2F вместо 0xC2F - включено прерывание по Ucc!
  // Вторичная запись решает проблему, но к NVIC уже зависает PendingBit, который необходимо сбросить.  
  MDR_POWER->PVDCS = cfgPWR.Value;
#endif
  
	//	Clear Events
  MDR_Power_ClearEvents();
  //  Enable IRQ
  if (activateNVIC_IRQ)
  {
    NVIC_ClearPendingIRQ(POWER_IRQn); //  Сброс от ложного запроса от записи в PVDCS
    NVIC_EnableIRQ(POWER_IRQn);
    NVIC_SetPriority(POWER_IRQn, priorityIRQ);
  }
}

void MDR_Power_DeInit(void)
{
  //  Clear Reg
  MDR_POWER->PVDCS = 0;
  //  Clock Off
  REG32(MDR_PWR_CLK_EN_ADDR) &= ~MDR_PWR_CLK_EN_MSK;
}


//  Доступ к Флагам событий
MDR_Power_CtrlAndStatus  MDR_Power_GetStatus(void)
{
  MDR_Power_CtrlAndStatus status;
  status.Value = MDR_POWER->PVDCS;
  return status;
}



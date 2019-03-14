#include "MDR_Timer.h"

//=====================   TimerEx Definitions ============
const MDR_TIMER_TypeEx _MDR_TIMER1ex = {
  .TIMERx = MDR_TIMER1,
  //  TimerClock Enable
  .CfgClock.ClockEna_Addr = MDR_TIMER1_CLK_EN_ADDR,
  .CfgClock.ClockEna_Mask = MDR_TIMER1_CLK_EN_MSK,
  //  TimerClock Gate On and BRG
  .CfgClock.ClockGate_Addr        = MDR_TIMER1_CLOCK_GATE_ADDR,
  .CfgClock.ClockGate_ClockOn_Msk = MDR_TIMER1_CLOCK_GATE_ENA_MSK,
  .CfgClock.ClockGate_BRG_Pos     = MDR_TIMER1_CLOCK_GATE_BRG_POS,
  //  NVIC
  .TIMERx_IRQn = TIMER1_IRQn
};

const MDR_TIMER_TypeEx _MDR_TIMER2ex = {
  .TIMERx = MDR_TIMER2,
  //  TimerClock Enable
  .CfgClock.ClockEna_Addr = MDR_TIMER2_CLK_EN_ADDR,
  .CfgClock.ClockEna_Mask = MDR_TIMER2_CLK_EN_MSK,
  //  TimerClock Gate On and BRG
  .CfgClock.ClockGate_Addr        = MDR_TIMER2_CLOCK_GATE_ADDR,
  .CfgClock.ClockGate_ClockOn_Msk = MDR_TIMER2_CLOCK_GATE_ENA_MSK,
  .CfgClock.ClockGate_BRG_Pos     = MDR_TIMER2_CLOCK_GATE_BRG_POS,
  //  NVIC
  .TIMERx_IRQn = TIMER2_IRQn
};

#ifdef TIMER3_EXIST
const MDR_TIMER_TypeEx _MDR_TIMER3ex = {
  .TIMERx = MDR_TIMER3,
  //  TimerClock Enable
  .CfgClock.ClockEna_Addr = MDR_TIMER3_CLK_EN_ADDR,
  .CfgClock.ClockEna_Mask = MDR_TIMER3_CLK_EN_MSK,
  //  TimerClock Gate On and BRG
  .CfgClock.ClockGate_Addr        = MDR_TIMER3_CLOCK_GATE_ADDR,
  .CfgClock.ClockGate_ClockOn_Msk = MDR_TIMER3_CLOCK_GATE_ENA_MSK,
  .CfgClock.ClockGate_BRG_Pos     = MDR_TIMER3_CLOCK_GATE_BRG_POS,
  //  NVIC
  .TIMERx_IRQn = TIMER3_IRQn
};
#endif

#ifdef TIMER4_EXIST
const MDR_TIMER_TypeEx _MDR_TIMER4ex = {
  .TIMERx = MDR_TIMER4,
  //  TimerClock Enable
  .CfgClock.ClockEna_Addr = MDR_TIMER4_CLK_EN_ADDR,
  .CfgClock.ClockEna_Mask = MDR_TIMER4_CLK_EN_MSK,
  //  TimerClock Gate On and BRG
  .CfgClock.ClockGate_Addr        = MDR_TIMER4_CLOCK_GATE_ADDR,
  .CfgClock.ClockGate_ClockOn_Msk = MDR_TIMER4_CLOCK_GATE_ENA_MSK,
  .CfgClock.ClockGate_BRG_Pos     = MDR_TIMER4_CLOCK_GATE_BRG_POS,
  //  NVIC
  .TIMERx_IRQn = TIMER4_IRQn
};
#endif


//=====================   Timer AUX function ==================
static void MDR_Timer_ClearRegs(MDR_TIMER_Type *TIMER)
{
  TIMER->CNT = 0;
  TIMER->PSG = 0;
  TIMER->ARR = 0;
  TIMER->CNTRL = 0;
  TIMER->CCR1 = 0;
  TIMER->CCR2 = 0;
  TIMER->CCR3 = 0;
  TIMER->CCR4 = 0;
  TIMER->CH1_CNTRL = 0;
  TIMER->CH2_CNTRL = 0;
  TIMER->CH3_CNTRL = 0;
  TIMER->CH4_CNTRL = 0;
  TIMER->CH1_CNTRL1 = 0;
  TIMER->CH2_CNTRL1 = 0;
  TIMER->CH3_CNTRL1 = 0;
  TIMER->CH4_CNTRL1 = 0;
  TIMER->CH1_DTG = 0;
  TIMER->CH2_DTG = 0;
  TIMER->CH3_DTG = 0;
  TIMER->CH4_DTG = 0;
  TIMER->BRKETR_CNTRL = 0;
  TIMER->STATUS = 0;
  TIMER->IE = 0;
  TIMER->DMA_RE = 0;
  TIMER->CH1_CNTRL2 = 0;
  TIMER->CH2_CNTRL2 = 0;
  TIMER->CH3_CNTRL2 = 0;
  TIMER->CH4_CNTRL2 = 0;
  TIMER->CCR11 = 0;
  TIMER->CCR21 = 0;
  TIMER->CCR31 = 0;
  TIMER->CCR41 = 0;
  
#ifdef TIMER_HAS_DMA_REx  
  TIMER->DMA_RE1 = 0;
  TIMER->DMA_RE2 = 0;
  TIMER->DMA_RE3 = 0;
  TIMER->DMA_RE4 = 0;
#endif
}


//=====================   Timers Start and most usefull control ==================
void MDR_Timer_ChangeCNT(MDR_TIMER_Type *TIMERx, uint_tim value)
{
  while ((TIMERx->CNTRL & MDR_TIMER_CNTRL_WR_CMPL_Msk) != 0){};
  TIMERx->CNT = (uint32_t)value;
}

void MDR_Timer_ChangePeriod(MDR_TIMER_Type *TIMERx, uint_tim value)
{
  while ((TIMERx->CNTRL & MDR_TIMER_CNTRL_WR_CMPL_Msk) != 0){};
  TIMERx->ARR = (uint32_t)(value - 1);
}

void MDR_Timer_ChangePSG(MDR_TIMER_Type *TIMERx, uint_tim value)
{
  while ((TIMERx->CNTRL & MDR_TIMER_CNTRL_WR_CMPL_Msk) != 0){};
  TIMERx->PSG = (uint32_t)value;
}

void MDR_TimerCh_ChangeCCR(MDR_TIMER_CH_Type *TIMER_CH, uint_tim value)
{
  while ((TIMER_CH->CHx_CNTRL & MDR_TIM_CHx_CNTRL_WR_CMPL_Msk) != 0){};
  TIMER_CH->CCR = (uint32_t)value;
}

void MDR_TimerCh_ChangeCCR1(MDR_TIMER_CH_Type *TIMER_CH, uint_tim value)
{
  while ((TIMER_CH->CHx_CNTRL & MDR_TIM_CHx_CNTRL_WR_CMPL_Msk) != 0){};
  TIMER_CH->CCR1 = (uint32_t)value;
}


//=========================================================================================================
//================================      Counting TIM_Clock or Events   ====================================
//=========================================================================================================

//=====================   Simplest Timer Period IQR (like SystemTimer) ==================

static void MDR_Timer_InitAndClear_loc(const MDR_TIMER_TypeEx *TIMERex)
{
  //  Включение тактирования блока
  MDR_PerClock_Enable(&TIMERex->CfgClock);  
  //  Clear Regs
  MDR_Timer_ClearRegs(TIMERex->TIMERx);  
}

static void MDR_Timer_InitPeriod_loc(const MDR_TIMER_TypeEx *TIMERex, MDR_BRG_DIV_128 clockBRG, uint_tim period, const uint32_t selectIRQ, const uint32_t flags)
{ 
  //  Set Timer Settings
  TIMERex->TIMERx->ARR = period - 1;

  TIMERex->TIMERx->IE = selectIRQ;
  TIMERex->TIMERx->CNTRL = MDR_TIMER_CNTRL_CNT_EN_Msk | flags;
  //  В 1986ВЕ9х:
  //  При включении таймера EN выставляется флаг CNT==ARR и CNT==0 (STATUS = 0x3)
  //  Поэтому NVIC инициализируется после включения таймера. 
  //  Иначе сразу произойдет прерывание при EN - не успеем стереть STATUS = 0  
  //  Оставлено всем, для универсальности
  TIMERex->TIMERx->STATUS = 0;
  
  //  IRQ Enable
  if (selectIRQ != 0)
  {
    //NVIC_ClearPendingIRQ(TIMERex->TIMERx_IRQn);
    NVIC_EnableIRQ(TIMERex->TIMERx_IRQn);
  }
  
  //  Выставление BRG. Для подачи частоты и начала счета необходимо вызвать функцию Start
  MDR_PerClock_SetBRG(&TIMERex->CfgClock, clockBRG);  
}

void MDR_Timer_InitPeriod(const MDR_TIMER_TypeEx *TIMERex, MDR_BRG_DIV_128 clockBRG, uint16_t timClockPSG, uint_tim period, bool enaIRQ)
{
  MDR_Timer_InitAndClear_loc(TIMERex);
  TIMERex->TIMERx->PSG = timClockPSG;
  if (enaIRQ)
    MDR_Timer_InitPeriod_loc(TIMERex, clockBRG, period, TIM_FL_CNT_ARR, 0);
  else
    MDR_Timer_InitPeriod_loc(TIMERex, clockBRG, period, 0, 0);
}

static const uint32_t _TIM_DirFlags_CountClock[3] = {
       0,                                                                       // TIM_CountUp,
       MDR_TIMER_CNTRL_DIR_DOWN,                                                // TIM_CountDown,
       VAL2FLD_Pos(TIM_CntMode_UpDown_TimClk, MDR_TIMER_CNTRL_CNT_MODE_Pos)     // TIM_CountUpDown 
};

void MDR_Timer_InitPeriodDir(const MDR_TIMER_TypeEx *TIMERex, MDR_BRG_DIV_128 clockBRG, uint16_t timClockPSG, uint_tim period, bool enaIRQ, MDR_TIM_CountDir dir)
{  
  if (enaIRQ)
    MDR_Timer_InitPeriodDirIRQ(TIMERex, clockBRG, timClockPSG, period, TIM_FL_CNT_ARR, dir);
  else
    MDR_Timer_InitPeriodDirIRQ(TIMERex, clockBRG, timClockPSG, period, 0, dir);
}

void MDR_Timer_InitPeriodDirIRQ(const MDR_TIMER_TypeEx *TIMERex, MDR_BRG_DIV_128 clockBRG, uint16_t timClockPSG, uint_tim period, uint32_t selectIRQ, MDR_TIM_CountDir dir)
{  
  MDR_Timer_InitAndClear_loc(TIMERex);  
  TIMERex->TIMERx->PSG = timClockPSG;
  MDR_Timer_InitPeriod_loc(TIMERex, clockBRG, period, selectIRQ, _TIM_DirFlags_CountClock[dir]);
}

#ifdef TIMER4_EXIST
  static const uint32_t _TIM_EventSel_CountTIMs[4] = {
       VAL2FLD_Pos(MDR_TIM_Event_CNT_eq_ARR_TIM1, MDR_TIMER_CNTRL_EVENT_SEL_Pos),  // TIM_EventTIM1_CNT_ARR
       VAL2FLD_Pos(MDR_TIM_Event_CNT_eq_ARR_TIM2, MDR_TIMER_CNTRL_EVENT_SEL_Pos),  // TIM_EventTIM2_CNT_ARR
       VAL2FLD_Pos(MDR_TIM_Event_CNT_eq_ARR_TIM3, MDR_TIMER_CNTRL_EVENT_SEL_Pos),  // TIM_EventTIM3_CNT_ARR
       VAL2FLD_Pos(MDR_TIM_Event_CNT_eq_ARR_TIM4, MDR_TIMER_CNTRL_EVENT_SEL_Pos),  // TIM_EventTIM4_CNT_ARR
};
#elif defined(TIMER3_EXIST)
  static const uint32_t _TIM_EventSel_CountTIMs[3] = {
       VAL2FLD_Pos(MDR_TIM_Event_CNT_eq_ARR_TIM1, MDR_TIMER_CNTRL_EVENT_SEL_Pos),
       VAL2FLD_Pos(MDR_TIM_Event_CNT_eq_ARR_TIM2, MDR_TIMER_CNTRL_EVENT_SEL_Pos),
       VAL2FLD_Pos(MDR_TIM_Event_CNT_eq_ARR_TIM3, MDR_TIMER_CNTRL_EVENT_SEL_Pos),
  };
#else
  static const uint32_t _TIM_EventSel_CountTIMs[2] = {
       VAL2FLD_Pos(MDR_TIM_Event_CNT_eq_ARR_TIM1, MDR_TIMER_CNTRL_EVENT_SEL_Pos),
       VAL2FLD_Pos(MDR_TIM_Event_CNT_eq_ARR_TIM2, MDR_TIMER_CNTRL_EVENT_SEL_Pos),
  };
#endif  
  
void MDR_Timer_AddCascadePeriod(const MDR_TIMER_TypeEx *TIMERex, MDR_BRG_DIV_128 clockBRG, MDR_Timer_EventTimer countEvent, uint_tim period, bool enaIRQ)
{
  uint32_t regCNTRL = _TIM_EventSel_CountTIMs[countEvent] | VAL2FLD_Pos(TIM_CntMode_DIR_ExtEvents, MDR_TIMER_CNTRL_CNT_MODE_Pos);
  
  MDR_Timer_InitAndClear_loc(TIMERex);  
  
  if (enaIRQ)
    MDR_Timer_InitPeriod_loc(TIMERex, clockBRG, period, TIM_FL_CNT_ARR, regCNTRL);
  else
    MDR_Timer_InitPeriod_loc(TIMERex, clockBRG, period, 0, regCNTRL);  
}

//=====================   DeInit ==================
void MDR_Timer_DeInit(const MDR_TIMER_TypeEx *TIMERex)
{
  //  Count Clock Off
  MDR_PerClock_GateClose(&TIMERex->CfgClock);  

  NVIC_DisableIRQ(TIMERex->TIMERx_IRQn);
  MDR_Timer_ClearRegs(TIMERex->TIMERx);
  
  //  Set Timer Settings
  MDR_PerClock_Disable(&TIMERex->CfgClock);  
}

//=====================   Internal Counting, CNT_CLOCK = TIM_CLOCK/(PSG + 1), TIM_CLOCK = CLK / BRG ==================
static void MDR_Timer_InitCount_loc(const MDR_TIMER_TypeEx *TIMERex, const MDR_Timer_CfgPeriod *cfgPeriod, const MDR_Timer_CfgIRQ *cfgIRQ, const uint32_t regCtrl)
{
  //  Set Timer Settings 
  TIMERex->TIMERx->ARR = cfgPeriod->period - 1;
  TIMERex->TIMERx->CNT = cfgPeriod->startValue;
  
  TIMERex->TIMERx->IE = cfgIRQ->SelectIRQ;
  if (cfgPeriod->periodUpdateImmediately == MDR_On)  
    TIMERex->TIMERx->CNTRL = regCtrl | MDR_TIMER_CNTRL_CNT_EN_Msk;
  else
    TIMERex->TIMERx->CNTRL = regCtrl | MDR_TIMER_CNTRL_CNT_EN_Msk | MDR_TIMER_CNTRL_ARRB_EN_Msk;
  //  При включении таймера EN выставляется флаг CNT==ARR!?
  //  Поэтому и NVIC инициализируется после включения таймера. 
  //  Иначе сразу произойдет прерывание при EN - не успеем стереть STATUS = 0
  TIMERex->TIMERx->STATUS = 0;
  
  //  IRQ Init
  if (cfgIRQ->activateNVIC_IRQ)
  {
    NVIC_SetPriority(TIMERex->TIMERx_IRQn, cfgIRQ->priorityIRQ);
    NVIC_EnableIRQ(TIMERex->TIMERx_IRQn);
  }
  
  //  Выставление BRG. Для подачи частоты и начала счета необходимо вызвать функцию Start
  MDR_PerClock_SetBRG(&TIMERex->CfgClock, cfgPeriod->clockBRG); 
}

void MDR_Timer_InitCountTimClock(const MDR_TIMER_TypeEx *TIMERex, const MDR_Timer_CfgCountClock *cfgCntClock)
{ 
  MDR_Timer_InitAndClear_loc(TIMERex);
  TIMERex->TIMERx->PSG = cfgCntClock->timClockPSG;
  MDR_Timer_InitCount_loc(TIMERex, &cfgCntClock->cfgPeriod, &cfgCntClock->cfgIRQ, _TIM_DirFlags_CountClock[cfgCntClock->countDir]);
}

//=====================   Count External Events CNT==ARR in Timers, TIM_CLOCK = CLK / BRG ==================
#ifdef MDR_TIMER_Can_UpDown_ByExtEvents
  static const uint32_t _TIM_DirFlags_CountExtEvent[3] = {
       VAL2FLD_Pos(TIM_CntMode_DIR_ExtEvents, MDR_TIMER_CNTRL_CNT_MODE_Pos),                            // TIM_CountUp,
       VAL2FLD_Pos(TIM_CntMode_DIR_ExtEvents, MDR_TIMER_CNTRL_CNT_MODE_Pos) | MDR_TIMER_CNTRL_DIR_DOWN, // TIM_CountDown,
       VAL2FLD_Pos(TIM_CntMode_UpDown_ExtEvents, MDR_TIMER_CNTRL_CNT_MODE_Pos)                          // TIM_CountUpDown 
  };
#else
  static const uint32_t _TIM_DirFlags_CountExtEvent[2] = {
       VAL2FLD_Pos(TIM_CntMode_DIR_ExtEvents, MDR_TIMER_CNTRL_CNT_MODE_Pos),                            // TIM_DIR_UP,
       VAL2FLD_Pos(TIM_CntMode_DIR_ExtEvents, MDR_TIMER_CNTRL_CNT_MODE_Pos) | MDR_TIMER_CNTRL_DIR_DOWN  // TIM_DIR_DOWN,
  };  
#endif  

void MDR_Timer_InitCountTimerEvent(const MDR_TIMER_TypeEx *TIMERex, const MDR_Timer_CfgCountTimerEvent *cfgCntTimEvent)
{
  uint32_t flCNTRL = _TIM_EventSel_CountTIMs[cfgCntTimEvent->countEvent] | _TIM_DirFlags_CountExtEvent[cfgCntTimEvent->countDir];

  MDR_Timer_InitAndClear_loc(TIMERex);
  MDR_Timer_InitCount_loc(TIMERex, &cfgCntTimEvent->cfgPeriod, &cfgCntTimEvent->cfgIRQ, flCNTRL);
}


//=====================   Count External ETR Signal Events, TIM_CLOCK = CLK / BRG ==================

void MDR_Timer_InitCountETR(const MDR_TIMER_TypeEx *TIMERex, const MDR_Timer_CfgCountETR *cfgCntETR)
{
  uint32_t flCNTRL = _TIM_DirFlags_CountExtEvent[cfgCntETR->countDir]
                   | VAL2FLD_Pos(cfgCntETR->selFrontETR + MDR_TIM_Event_Rise_ETR, MDR_TIMER_CNTRL_EVENT_SEL_Pos)
                   | VAL2FLD_Pos(cfgCntETR->clockDTS,    MDR_TIMER_CNTRL_FDTS_Pos);
  
  MDR_Timer_InitAndClear_loc(TIMERex);
  MDR_Timer_InitCount_loc(TIMERex, &cfgCntETR->cfgPeriod, &cfgCntETR->cfgIRQ, flCNTRL);
}

//=====================   Count Channel Capture Events, TIM_CLOCK = CLK / BRG ==================

void MDR_Timer_InitCountChannelEvent(const MDR_TIMER_TypeEx *TIMERex, const MDR_Timer_CfgCountCH *cfgCntCH)
{
  uint32_t flCNTRL = _TIM_DirFlags_CountExtEvent[cfgCntCH->countDir]
                   | VAL2FLD_Pos(cfgCntCH->selEventCH + MDR_TIM_Event_Ch1, MDR_TIMER_CNTRL_EVENT_SEL_Pos)
                   | VAL2FLD_Pos(cfgCntCH->clockDTS,   MDR_TIMER_CNTRL_FDTS_Pos);
  
  MDR_Timer_InitAndClear_loc(TIMERex);
  MDR_Timer_InitCount_loc(TIMERex, &cfgCntCH->cfgPeriod, &cfgCntCH->cfgIRQ, flCNTRL);
}

//=========================================================================================================
//===================================    Timer channel Pins   =============================================
//=========================================================================================================

void MDR_TimerCh_InitPinGPIO(const MDR_Timer_CfgPinGPIO *pinCfg, MDR_PIN_PWR pinsPower)
{
  MDR_PinDig_PermRegs pinPermCfg;
  
  MDR_Port_InitDigPermRegs(MDR_PIN_PullPush, pinsPower, MDR_Off, MDR_Off, &pinPermCfg);

  MDR_GPIO_ClockOn(pinCfg->portGPIO);
  MDR_GPIO_InitDigPin(pinCfg->portGPIO, pinCfg->pinIndex, MDR_Pin_In, pinCfg->pinFunc, &pinPermCfg);
}

void MDR_TimerCh_DeInitPinGPIO(const MDR_Timer_CfgPinGPIO *pinCfg)
{
  MDR_GPIO_InitAnalog(pinCfg->portGPIO, 1 << pinCfg->pinIndex);
}

//=========================================================================================================
//======================================      Channel PWM    ==============================================
//=========================================================================================================

//  ----------    Полная инициализация режима PWM со всеми настройками  --------------
void MDR_TimerCh_InitByCfgRegs(MDR_TIMER_CH_Type *TIMER_CH, MDR_TIMER_CH_CfgRegs *cfgRegs)
{
  TIMER_CH->CHx_DTG = cfgRegs->CH_DTG;
  TIMER_CH->CHx_CNTRL  = cfgRegs->CH_CNTRL;
  TIMER_CH->CHx_CNTRL2 = cfgRegs->CH_CNTRL2;  
  TIMER_CH->CHx_CNTRL1 = cfgRegs->CH_CNTRL1;
}

static void MDR_TimerCh_OptionsToCfgRegs(MDR_TIMER_CH_CfgRegs *cfgRegs, const MDR_TimerCh_CfgOptionsPWM *cfgOptions)
{  
  if (cfgOptions->cfgPin_CH != NULL)
  {
    cfgRegs->CH_CNTRL1 =  VAL2FLD_Pos(cfgOptions->cfgPin_CH->ModeIO,    MDR_TIM_CHx_CNTRL1_SelOE_Pos)
                        | VAL2FLD_Pos(cfgOptions->cfgPin_CH->OutSignal, MDR_TIM_CHx_CNTRL1_SelO_Pos)
                        | VAL2FLD_Pos(cfgOptions->cfgPin_CH->Invert,    MDR_TIM_CHx_CNTRL1_Inv_Pos);
  }
  if (cfgOptions->cfgPin_nCH != NULL)
  {
    cfgRegs->CH_CNTRL1 |=  VAL2FLD_Pos(cfgOptions->cfgPin_nCH->ModeIO,    MDR_TIM_CHx_CNTRL1_NSelOE_Pos)
                         | VAL2FLD_Pos(cfgOptions->cfgPin_nCH->OutSignal, MDR_TIM_CHx_CNTRL1_NSelO_Pos)
                         | VAL2FLD_Pos(cfgOptions->cfgPin_nCH->Invert,    MDR_TIM_CHx_CNTRL1_NInv_Pos);
  }  

  if (cfgOptions->cfgDTG != NULL)
  {
    cfgRegs->CH_DTG = VAL2FLD_Pos(cfgOptions->cfgDTG->Presc,    MDR_TIM_CHx_DTG_DTG_Pos)
                    | VAL2FLD_Pos(cfgOptions->cfgDTG->ClockSel, MDR_TIM_CHx_DTG_EDTS_Pos)
                    | VAL2FLD_Pos(cfgOptions->cfgDTG->Mul,      MDR_TIM_CHx_DTG_DTGx_Pos);
  }
  
  //  BRK and ETR
  cfgRegs->CH_CNTRL |= VAL2FLD_Pos(cfgOptions->ClearRef_ByBRK, MDR_TIM_CHx_CNTRL_BRKEN_Pos);
  if (cfgOptions->ClearRef_ByETR)
    cfgRegs->CH_CNTRL |= MDR_TIM_CHx_CNTRL_ETREN_Msk | MDR_TIM_CHx_CNTRL_OCCE_Msk;
}

static void MDR_TimerCh_CfgPWM_ToCfgRegs(MDR_TIMER_CH_CfgRegs *cfgRegs, const MDR_TimerCh_CfgPWM *cfgPWM)
{
  bool defInit_CH, defInit_nCH = true;
  MDR_TIM_SelOut selOutSignal = MDR_TIM_SelO_Ref;
  
  // Gather settings
  if (cfgPWM->cfgOptions != NULL)
  {
    MDR_TimerCh_OptionsToCfgRegs(cfgRegs, cfgPWM->cfgOptions);
    
    defInit_CH  = cfgPWM->cfgOptions->cfgPin_CH  == NULL;
    defInit_nCH = cfgPWM->cfgOptions->cfgPin_nCH == NULL;
    if (cfgPWM->cfgOptions->cfgDTG != NULL)
      selOutSignal = MDR_TIM_SelO_DTG;
  }
  
  if (defInit_CH)
  {
    cfgRegs->CH_CNTRL1 =  VAL2FLD_Pos(MDR_TIM_SelOE_PinOUT, MDR_TIM_CHx_CNTRL1_SelOE_Pos)
                        | VAL2FLD_Pos(selOutSignal,         MDR_TIM_CHx_CNTRL1_SelO_Pos)
                        | VAL2FLD_Pos(MDR_Off,              MDR_TIM_CHx_CNTRL1_Inv_Pos);
  }
  if (defInit_nCH && cfgPWM->use_nCH)
  {
    cfgRegs->CH_CNTRL1 |= VAL2FLD_Pos(MDR_TIM_SelOE_PinOUT, MDR_TIM_CHx_CNTRL1_NSelOE_Pos)
                        | VAL2FLD_Pos(selOutSignal,         MDR_TIM_CHx_CNTRL1_NSelO_Pos)
                        | VAL2FLD_Pos(MDR_Off,              MDR_TIM_CHx_CNTRL1_NInv_Pos);
  }  
 
  cfgRegs->CH_CNTRL2 = VAL2FLD_Pos(cfgPWM->CCRs_UpdImmediately, MDR_TIM_CHx_CNTRL2_CCRRLD_Pos);
}

static void MDR_TimerCh_DefaultPWM_ToCfgRegs(MDR_TIMER_CH_CfgRegs *cfgRegs)
{
  //  CH outputs Ref signal
  cfgRegs->CH_CNTRL1 =  VAL2FLD_Pos(MDR_TIM_SelOE_PinOUT, MDR_TIM_CHx_CNTRL1_SelOE_Pos)
                      | VAL2FLD_Pos(MDR_TIM_SelO_Ref,     MDR_TIM_CHx_CNTRL1_SelO_Pos)
                      | VAL2FLD_Pos(MDR_Off,              MDR_TIM_CHx_CNTRL1_Inv_Pos);
  //  nCH outputs nRef signal
  cfgRegs->CH_CNTRL1 |= VAL2FLD_Pos(MDR_TIM_SelOE_PinOUT, MDR_TIM_CHx_CNTRL1_NSelOE_Pos)
                      | VAL2FLD_Pos(MDR_TIM_SelO_Ref,     MDR_TIM_CHx_CNTRL1_NSelO_Pos)
                      | VAL2FLD_Pos(MDR_Off,              MDR_TIM_CHx_CNTRL1_NInv_Pos);  
  //  CCRs immediately reload
  cfgRegs->CH_CNTRL2 = MDR_TIM_CHx_CNTRL2_CCRRLD_Msk;
  //  No DTG, ETR, BRK
}

void MDR_TimerCh_InitPWM(MDR_TIMER_CH_Type *TIMER_CH, const MDR_TimerCh_CfgPWM *cfgPWM, MDR_TIM_PWM_Ref modeRef, uint_tim CCR)
{
  MDR_TIMER_CH_CfgRegs cfgRegs;

  cfgRegs.CH_CNTRL  = 0;
  cfgRegs.CH_CNTRL1 = 0;
  cfgRegs.CH_DTG    = 0;
  cfgRegs.CH_CNTRL2 = 0;
  
  if (cfgPWM != NULL)
    MDR_TimerCh_CfgPWM_ToCfgRegs(&cfgRegs, cfgPWM);
  else
    MDR_TimerCh_DefaultPWM_ToCfgRegs(&cfgRegs);
  
  //  Ref signal mode
  cfgRegs.CH_CNTRL |= VAL2FLD_Pos(modeRef, MDR_TIM_CHx_CNTRL_OCCM_Pos);  

  //  Apply
  TIMER_CH->CCR = CCR;
  MDR_TimerCh_InitByCfgRegs(TIMER_CH, &cfgRegs);  
}
 
void MDR_TimerCh_InitPWM1(MDR_TIMER_CH_Type *TIMER_CH, const MDR_TimerCh_CfgPWM *cfgPWM, MDR_TIM_PWM1_Ref modeRef, uint_tim CCR, uint_tim CCR1)
{
  MDR_TIMER_CH_CfgRegs cfgRegs;

  cfgRegs.CH_CNTRL  = 0;
  cfgRegs.CH_CNTRL1 = 0;
  cfgRegs.CH_DTG    = 0;
  cfgRegs.CH_CNTRL2 = 0;
  
  if (cfgPWM != NULL)
    MDR_TimerCh_CfgPWM_ToCfgRegs(&cfgRegs, cfgPWM);
  else
    MDR_TimerCh_DefaultPWM_ToCfgRegs(&cfgRegs);
  
  //  Ref signal mode
  cfgRegs.CH_CNTRL |= VAL2FLD_Pos(modeRef, MDR_TIM_CHx_CNTRL_OCCM_Pos);  
  //  Enable CCR1
  cfgRegs.CH_CNTRL2 |= MDR_TIM_CHx_CNTRL2_CCR1_En_Msk;
  
  //  Apply  
  TIMER_CH->CCR  = CCR;
  TIMER_CH->CCR1 = CCR1;
  MDR_TimerCh_InitByCfgRegs(TIMER_CH, &cfgRegs);  
}

void MDR_TimerCh_DeInit(MDR_TIMER_CH_Type *TIMER_CH)
{
  TIMER_CH->CHx_CNTRL1 = 0;
  TIMER_CH->CHx_CNTRL  = 0;
  TIMER_CH->CHx_CNTRL2 = 0;
  TIMER_CH->CHx_DTG    = 0;
}


// ------------  Простейшая инициализация вывода импульсов - PulsePWM  -----------------------
void MDR_TimerPulse_InitPulse  (MDR_TIMER_CH_Type *TIMER_CH, uint_tim period, uint8_t widthPerc)
{
  uint_tim width = period / 100 * widthPerc;
  MDR_TimerCh_InitPWM(TIMER_CH, NULL, MDR_TIM_PWM_Ref1_ltCCR, width);
}

void MDR_TimerPulse_ChangeWidth(MDR_TIMER_CH_Type *TIMER_CH, uint_tim period, uint8_t widthPerc)
{
  uint_tim width = period * widthPerc / 100;
  MDR_TimerCh_ChangeCCR(TIMER_CH, width);
}

void MDR_TimerPulse_ChangePeriod(MDR_TIMER_Type *TIMERx, uint_tim period, MDR_TIMER_CH_Type *TIMER_CH, uint8_t widthPerc)
{ 
  uint_tim width = period * widthPerc / 100;
  
  MDR_Timer_ChangePeriod(TIMERx, period);  
  MDR_TimerCh_ChangeCCR(TIMER_CH, width);
}


//=========================================================================================================
//=================================      Channel Capture Rise/Fall events (CAP)    =========================================
//=========================================================================================================

static void MDR_TimerCh_CfgCAP_ToCfgRegs(MDR_TIMER_CH_CfgRegs *cfgRegs, const MDR_TimerCh_CfgCAP *cfgCAP)
{
  cfgRegs->CH_CNTRL = VAL2FLD_Pos(cfgCAP->Filter,   MDR_TIM_CHx_CNTRL_CHFLTR_Pos)
                    | VAL2FLD_Pos(cfgCAP->EventCAP, MDR_TIM_CHx_CNTRL_CHSEL_Pos)
                    | VAL2FLD_Pos(cfgCAP->EventPSC, MDR_TIM_CHx_CNTRL_CHPSC_Pos)
                    | MDR_TIM_CHx_CNTRL_CAP_Mode;
  
  cfgRegs->CH_CNTRL2 = VAL2FLD_Pos(cfgCAP->EventCAP1,  MDR_TIM_CHx_CNTRL2_CHSel1_Pos)
                     | VAL2FLD_Pos(cfgCAP->enableCAP1, MDR_TIM_CHx_CNTRL2_CCR1_En_Pos)
                     | MDR_TIM_CHx_CNTRL2_CAP_Fix_Msk;
}

static void MDR_TimerCh_DefaultCAP_ToCfgRegs(MDR_TIMER_CH_CfgRegs *cfgRegs)
{
  cfgRegs->CH_CNTRL = VAL2FLD_Pos(MDR_TIM_FLTR_TIM_CLK,   MDR_TIM_CHx_CNTRL_CHFLTR_Pos)
                    | VAL2FLD_Pos(MDR_TIM_CAP_RiseOnPin,  MDR_TIM_CHx_CNTRL_CHSEL_Pos)
                    | VAL2FLD_Pos(MDR_PSC_div1,           MDR_TIM_CHx_CNTRL_CHPSC_Pos)
                    | MDR_TIM_CHx_CNTRL_CAP_Mode;
  
  cfgRegs->CH_CNTRL2 = VAL2FLD_Pos(MDR_TIM_CAP1_FallOnPin,  MDR_TIM_CHx_CNTRL2_CHSel1_Pos)
                     | VAL2FLD_Pos(true,                    MDR_TIM_CHx_CNTRL2_CCR1_En_Pos)
                     | MDR_TIM_CHx_CNTRL2_CAP_Fix_Msk;  
  
}

void MDR_TimerCh_InitCAP(MDR_TIMER_CH_Type *TIMER_CH, const MDR_TimerCh_CfgCAP *cfgCAP)
{
  MDR_TIMER_CH_CfgRegs cfgRegs;

  cfgRegs.CH_CNTRL  = 0;
  cfgRegs.CH_CNTRL1 = 0;
  cfgRegs.CH_DTG    = 0;
  cfgRegs.CH_CNTRL2 = 0;
  
  if (cfgCAP != NULL)
    MDR_TimerCh_CfgCAP_ToCfgRegs(&cfgRegs, cfgCAP);
  else
    MDR_TimerCh_DefaultCAP_ToCfgRegs(&cfgRegs);

  //  Apply
  TIMER_CH->CCR = 0;
  TIMER_CH->CCR1 = 0;
  MDR_TimerCh_InitByCfgRegs(TIMER_CH, &cfgRegs);
}


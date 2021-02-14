#include <MDR_GPIO.h>


// Значение для хранения последного значения в режиме Port. Вместо регистра RDTX, которого нет в 1986ВЕ9х.
// В 1986ВЕ1Т такой регистр есть, это поле не нужно.
// С данным полем работают функции типа - MDR_GPIOPort_Set (префикс MDR_GPIOPort_)
#ifndef MDR_GPIO_HAS_SET_CLEAR  
  static MDR_GPIO_SoftRDTX MDR_PortA_SoftRDTX;
  static MDR_GPIO_SoftRDTX MDR_PortB_SoftRDTX;
  static MDR_GPIO_SoftRDTX MDR_PortC_SoftRDTX;
  #ifdef MDR_PORTD  
    static MDR_GPIO_SoftRDTX MDR_PortD_SoftRDTX;
  #endif
  #ifdef MDR_PORTE
    static MDR_GPIO_SoftRDTX MDR_PortE_SoftRDTX;
  #endif
  #ifdef MDR_PORTF  
    static MDR_GPIO_SoftRDTX MDR_PortF_SoftRDTX;
  #endif
  #ifdef MDR_PORTG  
    static MDR_GPIO_SoftRDTX MDR_PortG_SoftRDTX;
  #endif
  #ifdef MDR_PORTH  
    static MDR_GPIO_SoftRDTX MDR_PortH_SoftRDTX;
  #endif
  #ifdef MDR_PORTI  
    static MDR_GPIO_SoftRDTX MDR_PortI_SoftRDTX;
  #endif
#endif

//  Привязка портов к включению тактирования
const MDR_GPIO_Port   GPIO_A_Port = {
  .PORTx            =  MDR_PORTA,
  .RST_ClockEn_Addr =  MDR_CLK_EN_ADDR_PORT_A,
  .ClockEnaMask     = (1 << MDR_CLK_EN_BIT_PORT_A),
  
#ifndef MDR_GPIO_HAS_SET_CLEAR  
  .pSoftRDTX        = &MDR_PortA_SoftRDTX
#endif
};

const MDR_GPIO_Port   GPIO_B_Port = {
  .PORTx            =  MDR_PORTB,
  .RST_ClockEn_Addr =  MDR_CLK_EN_ADDR_PORT_B,
  .ClockEnaMask     = (1 << MDR_CLK_EN_BIT_PORT_B),
  
#ifndef MDR_GPIO_HAS_SET_CLEAR  
  .pSoftRDTX        = &MDR_PortB_SoftRDTX
#endif  
};

const MDR_GPIO_Port   GPIO_C_Port = {
  .PORTx            =  MDR_PORTC,
  .RST_ClockEn_Addr =  MDR_CLK_EN_ADDR_PORT_C,
  .ClockEnaMask     = (1 << MDR_CLK_EN_BIT_PORT_C),
  
#ifndef MDR_GPIO_HAS_SET_CLEAR  
  .pSoftRDTX        = &MDR_PortC_SoftRDTX
#endif  
};

#ifdef MDR_PORTD
const MDR_GPIO_Port   GPIO_D_Port = {
  .PORTx            =  MDR_PORTD,
  .RST_ClockEn_Addr =  MDR_CLK_EN_ADDR_PORT_D,
  .ClockEnaMask     = (1 << MDR_CLK_EN_BIT_PORT_D),
  
#ifndef MDR_GPIO_HAS_SET_CLEAR  
  .pSoftRDTX        = &MDR_PortD_SoftRDTX
#endif  
};
#endif

#ifdef MDR_PORTE
const MDR_GPIO_Port   GPIO_E_Port = {
  .PORTx            =  MDR_PORTE,
  .RST_ClockEn_Addr =  MDR_CLK_EN_ADDR_PORT_E,
  .ClockEnaMask     = (1 << MDR_CLK_EN_BIT_PORT_E),
  
#ifndef MDR_GPIO_HAS_SET_CLEAR  
  .pSoftRDTX        = &MDR_PortE_SoftRDTX
#endif  
};
#endif

#ifdef MDR_PORTF
const MDR_GPIO_Port   GPIO_F_Port = {
  .PORTx            =  MDR_PORTF,
  .RST_ClockEn_Addr =  MDR_CLK_EN_ADDR_PORT_F,
  .ClockEnaMask     = (1 << MDR_CLK_EN_BIT_PORT_F),
  
#ifndef MDR_GPIO_HAS_SET_CLEAR  
  .pSoftRDTX        = &MDR_PortF_SoftRDTX
#endif  
};
#endif

#ifdef MDR_PORTG
const MDR_GPIO_Port   GPIO_G_Port = {
  .PORTx            =  MDR_PORTG,
  .RST_ClockEn_Addr =  MDR_CLK_EN_ADDR_PORT_G,
  .ClockEnaMask     = (1 << MDR_CLK_EN_BIT_PORT_G),

#ifndef MDR_GPIO_HAS_SET_CLEAR  
  .pSoftRDTX        = &MDR_PortG_SoftRDTX
#endif
};
#endif

#ifdef MDR_PORTH
const MDR_GPIO_Port   GPIO_H_Port = {
  .PORTx            =  MDR_PORTH,
  .RST_ClockEn_Addr =  MDR_CLK_EN_ADDR_PORT_H,
  .ClockEnaMask     = (1 << MDR_CLK_EN_BIT_PORT_H),

#ifndef MDR_GPIO_HAS_SET_CLEAR  
  .pSoftRDTX        = &MDR_PortH_SoftRDTX
#endif
};
#endif

#ifdef MDR_PORTI
const MDR_GPIO_Port   GPIO_I_Port = {
  .PORTx            =  MDR_PORTI,
  .RST_ClockEn_Addr =  MDR_CLK_EN_ADDR_PORT_I,
  .ClockEnaMask     = (1 << MDR_CLK_EN_BIT_PORT_I),
  
#ifndef MDR_GPIO_HAS_SET_CLEAR  
  .pSoftRDTX        = &MDR_PortI_SoftRDTX
#endif  
};
#endif


// =========== Cброс регистров блока в исходное состояние ===============
void MDR_Port_Reset(MDR_PORT_Type *GPIO_Port)
{
  GPIO_Port->ANALOG = 0;
  GPIO_Port->PULL = 0;
  GPIO_Port->OE = 0;
  GPIO_Port->RXTX = 0;
  GPIO_Port->FUNC = 0;
  GPIO_Port->PD = 0;
  GPIO_Port->PWR = 0;
  GPIO_Port->GFEN = 0;  
}

// =========== Функции настройки портов GPIO, базовая реализация ===============

//  Маски для стирания бит
#define CLR_FUNC     MDR_GPIO_FUNC__Pin_Msk
#define CLR_PD      (MDR_GPIO_PD_Driver__Pin_Msk | MDR_GPIO_PD_Schmitt__Pin_Msk)

#define SET_OR_CLEAR(cfg, valSet, outReg, mask)     if ((cfg) == valSet) (outReg) |=  (mask); else (outReg) &= ~(mask)
#define SET_OR_CLEAR_HI(cfg, valSet, outReg, mask)  if ((cfg) == valSet) (outReg) |= ((mask) << 16); else (outReg) &= ~((mask) << 16)

void MDR_Port_Init(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect, MDR_GPIO_PinCfg *pinCfg)
{
  uint32_t i;
  uint32_t offsVal;
  MDR_GPIO_SetCfg tmpRegs;
  
  MDR_Port_ReadRegs(GPIO_Port, &tmpRegs);

  SET_OR_CLEAR(pinCfg->RxTx,         MDR_RIN_High,  tmpRegs.RXTX,   pinSelect);
  SET_OR_CLEAR(pinCfg->OutputEnable, MDR_On,        tmpRegs.OE,     pinSelect);
  SET_OR_CLEAR(pinCfg->DigMode,      MDR_On,        tmpRegs.ANALOG, pinSelect);
  SET_OR_CLEAR(pinCfg->InpFilterEn,  MDR_On,        tmpRegs.GFEN,   pinSelect);
  
  SET_OR_CLEAR   (pinCfg->PullDown,  MDR_On, tmpRegs.PULL, pinSelect);
  SET_OR_CLEAR_HI(pinCfg->PullUp,    MDR_On, tmpRegs.PULL, pinSelect);
  
  SET_OR_CLEAR   (pinCfg->OpenDrain, MDR_On, tmpRegs.PD, pinSelect);
  SET_OR_CLEAR_HI(pinCfg->InpSchmEn, MDR_On, tmpRegs.PD, pinSelect);
   
  for (i = 0; i < MDR_GPIO_Pin_Count; ++i)
    if (pinSelect & (1 << i))
    { 
      //  By two bits
      offsVal = i << 1;
      tmpRegs.PWR  = (tmpRegs.PWR & ~(MDR_GPIO_PWR__Pin_Msk   << offsVal)) | ((uint32_t)pinCfg->Power << offsVal);
      tmpRegs.FUNC = (tmpRegs.FUNC & ~(MDR_GPIO_FUNC__Pin_Msk << offsVal)) | ((uint32_t)pinCfg->Func << offsVal);
    }
  
  MDR_Port_WriteRegs(GPIO_Port, &tmpRegs);   
}

void MDR_Port_InitAnalog(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect)
{
  uint32_t i;
  MDR_GPIO_SetCfg tmpRegs;
  uint32_t andMask;
  
  MDR_Port_ReadRegs(GPIO_Port, &tmpRegs);
  
  andMask = ~pinSelect;
  tmpRegs.RXTX    &= andMask;
  tmpRegs.OE      &= andMask;
  tmpRegs.ANALOG  &= andMask;
  tmpRegs.GFEN    &= andMask;
  
  andMask = ~(pinSelect | (pinSelect << 16));
  tmpRegs.PD      &= andMask;
  tmpRegs.PULL    &= andMask;
  
  for (i = 0; i < MDR_GPIO_Pin_Count; ++i)
    if (pinSelect & (1 << i)) 
    {  
      //  By two bits
      tmpRegs.PWR  &= ~(MDR_GPIO_PWR__Pin_Msk  << (i << 1));
      tmpRegs.FUNC &= ~(MDR_GPIO_FUNC__Pin_Msk << (i << 1));
    }
  
  MDR_Port_WriteRegs(GPIO_Port, &tmpRegs);    
}

// ======= Вспомогательные функции, для логгирования и отладки ===========

void MDR_Port_ReadRegs(MDR_PORT_Type *GPIO_Port, MDR_GPIO_SetCfg *cfgRegs)
{
  cfgRegs->RXTX    = GPIO_Port->RXTX;
  cfgRegs->OE      = GPIO_Port->OE;
  cfgRegs->FUNC    = GPIO_Port->FUNC;
  cfgRegs->ANALOG  = GPIO_Port->ANALOG;
  cfgRegs->PULL    = GPIO_Port->PULL;
  cfgRegs->PD      = GPIO_Port->PD;
  cfgRegs->PWR     = GPIO_Port->PWR;
  cfgRegs->GFEN    = GPIO_Port->GFEN;
}

void MDR_Port_WriteRegs(MDR_PORT_Type *GPIO_Port, MDR_GPIO_SetCfg *cfgRegs)
{
#ifndef PORT_JTAG
  #ifndef GPIO_INIT_HOLD_RXTX
  GPIO_Port->RXTX   = cfgRegs->RXTX;
  #endif
  GPIO_Port->OE     = cfgRegs->OE;
  GPIO_Port->FUNC   = cfgRegs->FUNC;
  GPIO_Port->ANALOG = cfgRegs->ANALOG;
  GPIO_Port->PULL   = cfgRegs->PULL;
  GPIO_Port->PD     = cfgRegs->PD;
  GPIO_Port->PWR    = cfgRegs->PWR;
  GPIO_Port->GFEN   = cfgRegs->GFEN;
#else
  #ifndef GPIO_INIT_HOLD_RXTX
  GPIO_Port->RXTX   = cfgRegs->RXTX   & (~JTAG_PINS(GPIO_Port));
  #endif
  GPIO_Port->OE     = cfgRegs->OE     & (~JTAG_PINS(GPIO_Port));
  GPIO_Port->FUNC   = cfgRegs->FUNC   & (~JTAG_PINS_x2(GPIO_Port));
  GPIO_Port->ANALOG = cfgRegs->ANALOG & (~JTAG_PINS(GPIO_Port));
  GPIO_Port->PULL   = cfgRegs->PULL   & (~JTAG_PINS_HILO(GPIO_Port));
  GPIO_Port->PD     = cfgRegs->PD     & (~JTAG_PINS_HILO(GPIO_Port));
  GPIO_Port->PWR    = cfgRegs->PWR    & (~JTAG_PINS_x2(GPIO_Port));
  GPIO_Port->GFEN   = cfgRegs->GFEN   & (~JTAG_PINS(GPIO_Port));  
#endif  
}

// ============  По-пиновая реализация с выделенными групповыми настройками  =================
// Групповые настройки в структуру
void MDR_Port_InitDigGroupPinCfg(MDR_OnOff pinOpenDrain, MDR_PIN_PWR pinPower, MDR_OnOff InpSchmEn, MDR_OnOff InpFilterEn, MDR_PinDig_GroupPinCfg *groupPinCfg) 
{
  groupPinCfg->DigMode   = MDR_On;
  groupPinCfg->OpenDrain = pinOpenDrain;
  groupPinCfg->Power     = pinPower;
  groupPinCfg->InpFilterEn = InpFilterEn;  
  groupPinCfg->InpSchmEn   = InpSchmEn;  
}

//  Конвертация в MDR_GPIO_CfgRegs для вызова первого варианта инициализации
__STATIC_INLINE void IO_ToCfg(MDR_Pin_IO InOut, MDR_OnOff *OutEna, MDR_OnOff *regPullUp, MDR_OnOff *regPullDown)
{  
  *OutEna = (MDR_OnOff)(InOut == MDR_Pin_Out);
  switch (InOut) {  
    case MDR_Pin_In_PU: {*regPullUp   = MDR_On; break;}
    case MDR_Pin_In_PD: {*regPullDown = MDR_On; break;}
    case MDR_Pin_Out: 
    case MDR_Pin_In:
    {
      *regPullUp = MDR_Off;
      *regPullDown = MDR_Off;
    }
  }
}

void MDR_Port_ToPinCfgEx(MDR_Pin_IO InOut, MDR_PIN_FUNC pinFunc, const MDR_PinDig_GroupPinCfg *groupPinCfg, MDR_GPIO_PinCfg *pinCfg, MDR_PIN_RXTX pinLevel)  
{
  IO_ToCfg(InOut, &pinCfg->OutputEnable, &pinCfg->PullUp, &pinCfg->PullDown);    
  pinCfg->RxTx        = pinLevel; //MDR_PIN_Low; 
  pinCfg->Func        = pinFunc;
  pinCfg->DigMode     = groupPinCfg->DigMode;
  pinCfg->OpenDrain   = groupPinCfg->OpenDrain;
  pinCfg->Power       = groupPinCfg->Power;  
  pinCfg->InpFilterEn = groupPinCfg->InpFilterEn;
  pinCfg->InpSchmEn   = groupPinCfg->InpSchmEn;
}


//  Применение настроек сразу в порт для указанных маской PinSelect пинов
void MDR_Port_InitDig(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect, MDR_Pin_IO InOut, MDR_PIN_FUNC pinFunc, const MDR_PinDig_GroupPinCfg *groupPinCfg)
{
  MDR_GPIO_PinCfg pinCfg;
   
  MDR_Port_ToPinCfg(InOut, pinFunc, groupPinCfg, &pinCfg);
  MDR_Port_Init(GPIO_Port, pinSelect, &pinCfg);
}

//  Применение настроек в порт для одного пина
void MDR_Port_InitDigPinEx(MDR_PORT_Type *GPIO_Port, uint32_t pinInd, MDR_Pin_IO pinInOut, MDR_PIN_FUNC pinFunc, const MDR_PinDig_GroupPinCfg *groupPinCfg, bool setHiLevel)  
{
  uint32_t offsVal;
  MDR_GPIO_SetCfg tmpRegs; 
  uint32_t pinSelect;
  
  MDR_OnOff  regOutEn, regPULL_Up, regPULL_Down;
  
  IO_ToCfg(pinInOut, &regOutEn, &regPULL_Up, &regPULL_Down);      
  
  MDR_Port_ReadRegs(GPIO_Port, &tmpRegs);

  pinSelect = 1 << pinInd;
  if (!setHiLevel)
    tmpRegs.RXTX   &= ~pinSelect;
  else
    tmpRegs.RXTX   |= pinSelect;
  tmpRegs.ANALOG |= pinSelect;  
  
  SET_OR_CLEAR   (regOutEn,     MDR_On,  tmpRegs.OE,   pinSelect);  
  SET_OR_CLEAR   (regPULL_Down, MDR_On,  tmpRegs.PULL, pinSelect);
  SET_OR_CLEAR_HI(regPULL_Up,   MDR_On,  tmpRegs.PULL, pinSelect);
  
  SET_OR_CLEAR   (groupPinCfg->InpFilterEn, MDR_On, tmpRegs.GFEN, pinSelect);    
  SET_OR_CLEAR   (groupPinCfg->OpenDrain,   MDR_On, tmpRegs.PD,   pinSelect);
  SET_OR_CLEAR_HI(groupPinCfg->InpSchmEn,   MDR_On, tmpRegs.PD,   pinSelect);
   
  //  By two bits
  offsVal = pinInd << 1;
  tmpRegs.PWR  = (tmpRegs.PWR & ~(MDR_GPIO_PWR__Pin_Msk << offsVal)) | ((uint32_t)groupPinCfg->Power << offsVal);
  tmpRegs.FUNC = (tmpRegs.FUNC & ~(MDR_GPIO_FUNC__Pin_Msk << offsVal)) | ((uint32_t)pinFunc << offsVal);
  
  MDR_Port_WriteRegs(GPIO_Port, &tmpRegs);
}


// Обнуление масок CLR и SET перед накоплением в них настроек Variable и Permanent
void MDR_Port_Clear_ClearCfg(MDR_GPIO_ClearCfg *cfgClr)
{
  cfgClr->clrPins  = 0;
  cfgClr->clrFUNC  = 0;
  cfgClr->clrHiLo  = 0;
  cfgClr->clrPWR   = 0;
}

void MDR_Port_Clear_SetCfg(MDR_GPIO_SetCfg *cfgSet)
{
  cfgSet->RXTX    = 0;
  cfgSet->OE      = 0;
  cfgSet->FUNC    = 0;
  cfgSet->ANALOG  = 0;
  cfgSet->PULL    = 0;
  cfgSet->PD      = 0; 
  cfgSet->PWR     = 0;
  cfgSet->GFEN    = 0;
}

void MDR_Port_MaskClear(MDR_Port_ApplyMask *applyMask)
{
  MDR_Port_Clear_ClearCfg(&applyMask->MaskCLR);
  MDR_Port_Clear_SetCfg(&applyMask->MaskSET); 
}

// Внесение настроек Variable и Permanent в маски CLR и SET для указанных маской PinSelect пинов
void MDR_Port_FillClearMask(uint32_t pinSelect, MDR_GPIO_ClearCfg *cfgClr)
{
  uint32_t i;  
  
  cfgClr->clrPins =  pinSelect;
  cfgClr->clrHiLo = (pinSelect | (pinSelect << 16));

  for (i = 0; i < MDR_GPIO_Pin_Count; ++i)
    if (pinSelect & (1 << i)) 
    {  
      //  By two bits
      cfgClr->clrPWR  |= MDR_GPIO_PWR__Pin_Msk  << (i << 1);
      cfgClr->clrFUNC |= MDR_GPIO_FUNC__Pin_Msk << (i << 1);
    }
}

void MDR_Port_MaskAddAnalog(uint32_t pinSelect, MDR_Port_ApplyMask *applyMask)
{
  MDR_Port_FillClearMask(pinSelect, &applyMask->MaskCLR);
}

void MDR_Port_MaskAdd(uint32_t pinSelect, MDR_Pin_IO pinInOut, MDR_PIN_FUNC pinFunc, const MDR_PinDig_GroupPinCfg *groupPinCfg, MDR_Port_ApplyMask *applyMask)
{
  uint32_t i, offsVal;
  MDR_GPIO_ClearCfg *pCfgClr = &applyMask->MaskCLR;
  MDR_GPIO_SetCfg   *pCfgSet = &applyMask->MaskSET;
  
  MDR_OnOff  regOutEn, regPULL_Up, regPULL_Down;
  
  IO_ToCfg(pinInOut, &regOutEn, &regPULL_Up, &regPULL_Down);  
  
  //  Clear Masks
  pCfgClr->clrPins |=  pinSelect;
  pCfgClr->clrHiLo |= (pinSelect | (pinSelect << 16));
  
  //  Set Mask
  if (regOutEn == MDR_On)     pCfgSet->OE     |= pinSelect;
  if (regPULL_Down == MDR_On) pCfgSet->PULL   |= pinSelect;
  if (regPULL_Up   == MDR_On) pCfgSet->PULL   |= (pinSelect << 16);  
  
  if (groupPinCfg->DigMode == MDR_On)     pCfgSet->ANALOG |= pinSelect;
  if (groupPinCfg->InpFilterEn == MDR_On) pCfgSet->GFEN   |= pinSelect;
  if (groupPinCfg->OpenDrain == MDR_On)   pCfgSet->PD     |= pinSelect;  
  if (groupPinCfg->InpSchmEn == MDR_On)   pCfgSet->PD     |= (pinSelect << 16);  
  
  for (i = 0; i < MDR_GPIO_Pin_Count; ++i)
    if (pinSelect & (1 << i)) 
    {  
      //  By two bits
      offsVal = i << 1;
      pCfgSet->PWR    |= (uint32_t)groupPinCfg->Power    << offsVal;      
      pCfgClr->clrPWR |= MDR_GPIO_PWR__Pin_Msk << offsVal;
      
      pCfgSet->FUNC    |= (uint32_t)pinFunc   << offsVal;      
      pCfgClr->clrFUNC |= MDR_GPIO_FUNC__Pin_Msk << offsVal;
    }
}

// Внесение настроек Variable и Permanent в маски CLR и SET для одного пина
void MDR_Port_MaskAddPin(uint32_t pinInd, MDR_Pin_IO pinInOut, MDR_PIN_FUNC pinFunc, const MDR_PinDig_GroupPinCfg *groupPinCfg, MDR_Port_ApplyMask *applyMask)  
{
  uint32_t offsVal;
  uint32_t pinSelect = 1 << pinInd;
  MDR_GPIO_ClearCfg *pCfgClr = &applyMask->MaskCLR;
  MDR_GPIO_SetCfg   *pCfgSet = &applyMask->MaskSET;
  
  MDR_OnOff  regOutEn, regPULL_Up, regPULL_Down;
  
  IO_ToCfg(pinInOut, &regOutEn, &regPULL_Up, &regPULL_Down);   
  
//  Clear Masks
  pCfgClr->clrPins =  pinSelect;
  pCfgClr->clrHiLo = (pinSelect | (pinSelect << 16));
  
  //  Set Mask
  if (regOutEn     == MDR_On) pCfgSet->OE     |= pinSelect;
  if (regPULL_Down == MDR_On) pCfgSet->PULL   |= pinSelect;
  if (regPULL_Up   == MDR_On) pCfgSet->PULL   |= (pinSelect << 16);  
  
  if (groupPinCfg->DigMode     == MDR_On) pCfgSet->ANALOG |= pinSelect;
  if (groupPinCfg->InpFilterEn == MDR_On) pCfgSet->GFEN   |= pinSelect;
  if (groupPinCfg->OpenDrain == MDR_On)   pCfgSet->PD     |= pinSelect;  
  if (groupPinCfg->InpSchmEn == MDR_On)   pCfgSet->PD     |= (pinSelect << 16);  
  
  //  By two bits
  offsVal = pinInd << 1;
  pCfgSet->PWR    |= (uint32_t)groupPinCfg->Power    << offsVal;      
  pCfgClr->clrPWR |= MDR_GPIO_PWR__Pin_Msk << offsVal;
  
  pCfgSet->FUNC    |= (uint32_t)pinFunc   << offsVal;      
  pCfgClr->clrFUNC |= MDR_GPIO_FUNC__Pin_Msk << offsVal;
}


//  Применение масок CLR и SET в порт
void MDR_Port_MaskApplyEx(MDR_PORT_Type *GPIO_Port, MDR_Port_ApplyMask *applyMask, MDR_GPIO_SetCfg *readRegs)
{  
  MDR_GPIO_ClearCfg *pCfgClr = &applyMask->MaskCLR;
  MDR_GPIO_SetCfg   *pCfgSet = &applyMask->MaskSET;  
  
  readRegs->RXTX    = (readRegs->RXTX   & ~pCfgClr->clrPins)   | pCfgSet->RXTX;
  readRegs->OE      = (readRegs->OE     & ~pCfgClr->clrPins)   | pCfgSet->OE;
  readRegs->FUNC    = (readRegs->FUNC   & ~pCfgClr->clrFUNC)   | pCfgSet->FUNC;
  readRegs->ANALOG  = (readRegs->ANALOG & ~pCfgClr->clrPins)   | pCfgSet->ANALOG;
  readRegs->PULL    = (readRegs->PULL   & ~pCfgClr->clrHiLo)   | pCfgSet->PULL;
  readRegs->PD      = (readRegs->PD     & ~pCfgClr->clrHiLo)   | pCfgSet->PD;
  readRegs->PWR     = (readRegs->PWR    & ~pCfgClr->clrPWR)    | pCfgSet->PWR;
  readRegs->GFEN    = (readRegs->GFEN   & ~pCfgClr->clrPins)   | pCfgSet->GFEN;
  
  MDR_Port_WriteRegs(GPIO_Port, readRegs);
}


void MDR_Port_MaskApply(  MDR_PORT_Type *GPIO_Port, MDR_Port_ApplyMask *pCfgSet)  
{
  MDR_GPIO_SetCfg tmpRegs;
  
  MDR_Port_ReadRegs(GPIO_Port, &tmpRegs);  
  MDR_Port_MaskApplyEx(GPIO_Port, pCfgSet, &tmpRegs);
}


// Упрощенная настройка пинов/пина в функции порт IN/OUT по умолчанию
void MDR_Port_Init_PortOUT   (MDR_PORT_Type *GPIO_Port, uint32_t pinSelect, MDR_PIN_PWR pinPWR)
{
  MDR_PinDig_GroupPinCfg groupPinCfg = {
    .DigMode   = MDR_On,
    .OpenDrain = MDR_Off,
    .Power     = pinPWR,
    .InpFilterEn  = MDR_Off,
    .InpSchmEn    = MDR_Off};
  
  MDR_Port_InitDigPort(GPIO_Port, pinSelect, MDR_Pin_Out, &groupPinCfg);
}

void MDR_Port_InitPin_PortOUT(MDR_PORT_Type *GPIO_Port, uint32_t pinInd,    MDR_PIN_PWR pinPWR)
{
  MDR_PinDig_GroupPinCfg groupPinCfg = {
    .DigMode   = MDR_On,
    .OpenDrain = MDR_Off,
    .Power     = pinPWR,
    .InpFilterEn  = MDR_Off,
    .InpSchmEn    = MDR_Off};    
      
  MDR_Port_InitDigPinPort(GPIO_Port, pinInd, MDR_Pin_Out, &groupPinCfg);  
}

void MDR_Port_Init_PortIN_Pull(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect, MDR_Pin_InPull pinPull)
{
  MDR_PinDig_GroupPinCfg groupPinCfg = {
    .DigMode   = MDR_On,
    .OpenDrain = MDR_Off,
    .Power     = MDR_PIN_PWR_OFF,
    .InpFilterEn  = MDR_Off,
    .InpSchmEn    = MDR_Off}; 
    
  MDR_Port_InitDigPort(GPIO_Port, pinSelect, (MDR_Pin_IO)pinPull, &groupPinCfg);  
}

void MDR_Port_InitPin_PortIN_Pull(MDR_PORT_Type *GPIO_Port, uint32_t pinInd, MDR_Pin_InPull pinPull)
{
  MDR_PinDig_GroupPinCfg groupPinCfg = {
    .DigMode   = MDR_On,
    .OpenDrain = MDR_Off,
    .Power     = MDR_PIN_PWR_OFF,
    .InpFilterEn  = MDR_Off,
    .InpSchmEn    = MDR_Off};  
  
  MDR_Port_InitDigPinPort(GPIO_Port, pinInd, (MDR_Pin_IO)pinPull, &groupPinCfg);    
}


// Управление подтяжками
void MDR_Port_SetPullUp(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect)
{
  uint32_t regVal = GPIO_Port->PULL;
  regVal &= ~pinSelect;
  GPIO_Port->PULL = regVal | (pinSelect << MDR_GPIO_PULL_UP__Pin_Pos);
}

void MDR_Port_SetPullDown(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect)
{
  uint32_t regVal = GPIO_Port->PULL;
  regVal &= ~(pinSelect << MDR_GPIO_PULL_UP__Pin_Pos);
  GPIO_Port->PULL = regVal | pinSelect;

}

void MDR_Port_ClearPull(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect)
{
  GPIO_Port->PULL &= ~(pinSelect | pinSelect << MDR_GPIO_PULL_UP__Pin_Pos);  
}

//  Получение информации для переключения функции для пина
MDR_GPIO_PinFuncCfg MDR_GPIO_GetPinFuncCfg(MDR_PORT_Type *GPIO_Port, uint32_t pinInd)
{
  MDR_GPIO_PinFuncCfg result;
  result.addrFuncReg = (uint32_t)&GPIO_Port->FUNC;
  result.funcPinPos = pinInd << MDR_GPIO_FUNC__Pin_MskOffs;
  result.funcPinMsk = MDR_GPIO_FUNC__Pin_Msk << result.funcPinPos;
  
  return result;
}

MDR_GPIO_PinFuncMasks MDR_GPIO_GetPinFuncMasks(MDR_PORT_Type *GPIO_Port, uint32_t pinInd, MDR_PIN_FUNC pinFunc)
{
  MDR_GPIO_PinFuncMasks pinMasks;
  MDR_GPIO_PinFuncCfg   pinCfg = MDR_GPIO_GetPinFuncCfg(GPIO_Port, pinInd);
  
  pinMasks.addrFuncReg = pinCfg.addrFuncReg;
  pinMasks.maskPinPort = pinCfg.funcPinMsk;  
  pinMasks.maskPinFunc = MDR_GPIO_GetPinFuncMask(&pinCfg, pinFunc);
  
  return pinMasks;
}

void MDR_GPIO_PinFunc_SetFunc(MDR_GPIO_PinFuncMasks *pinFuncMasks)
{
  uint32_t regValue = REG32(pinFuncMasks->addrFuncReg);
  REG32(pinFuncMasks->addrFuncReg) = MDR_MaskClrSet(regValue, pinFuncMasks->maskPinPort, pinFuncMasks->maskPinFunc);    
}

void MDR_GPIO_PinFunc_SetPort(MDR_GPIO_PinFuncMasks *pinFuncMasks)
{
  uint32_t regValue = REG32(pinFuncMasks->addrFuncReg);
  REG32(pinFuncMasks->addrFuncReg) = MDR_MaskClrSet(regValue, pinFuncMasks->maskPinPort, 0);    
}


void MDR_GPIO_InitPinsRXTX(const MDR_GPIO_CfgPinRXTX *pinsCfg, MDR_PIN_PWR pinsPower)
{
  MDR_PinDig_PermRegs pinPermCfg;

#ifdef MDR_GPIO_HAS_GFEN_SCHMT  
  MDR_Port_InitDigGroupPinCfg(MDR_Off, pinsPower, MDR_Off, MDR_Off, &pinPermCfg);
#else
  MDR_Port_InitDigGroupPinCfg(MDR_Off, pinsPower, &pinPermCfg);  
#endif
  
  //  TX
  if (pinsCfg->pPinTX != NULL)
  {
    MDR_GPIO_Enable(pinsCfg->pPinTX->portGPIO);
    MDR_GPIO_InitDigPin(pinsCfg->pPinTX->portGPIO, pinsCfg->pPinTX->pinIndex, MDR_Pin_In, pinsCfg->pPinTX->pinFunc, &pinPermCfg);  
  }
  //  RX
  if (pinsCfg->pPinRX != NULL)
  {
    MDR_GPIO_Enable(pinsCfg->pPinRX->portGPIO);
    MDR_GPIO_InitDigPin(pinsCfg->pPinRX->portGPIO, pinsCfg->pPinRX->pinIndex, MDR_Pin_In, pinsCfg->pPinRX->pinFunc, &pinPermCfg);
  }
}


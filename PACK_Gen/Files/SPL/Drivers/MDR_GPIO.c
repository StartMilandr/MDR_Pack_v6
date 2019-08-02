#include <MDR_GPIO.h>

//  Привязка портов к включению тактирования
const MDR_GPIO_Port   GPIO_A_Port = {
  .PORTx            =  MDR_PORTA,
  .RST_ClockEn_Addr =  MDR_CLK_EN_ADDR_PORT_A,
  .ClockEnaMask     = (1 << MDR_CLK_EN_BIT_PORT_A)
};

const MDR_GPIO_Port   GPIO_B_Port = {
  .PORTx            =  MDR_PORTB,
  .RST_ClockEn_Addr =  MDR_CLK_EN_ADDR_PORT_B,
  .ClockEnaMask     = (1 << MDR_CLK_EN_BIT_PORT_B)
};

const MDR_GPIO_Port   GPIO_C_Port = {
  .PORTx            =  MDR_PORTC,
  .RST_ClockEn_Addr =  MDR_CLK_EN_ADDR_PORT_C,
  .ClockEnaMask     = (1 << MDR_CLK_EN_BIT_PORT_C)
};

#ifdef MDR_PORTD
const MDR_GPIO_Port   GPIO_D_Port = {
  .PORTx            =  MDR_PORTD,
  .RST_ClockEn_Addr =  MDR_CLK_EN_ADDR_PORT_D,
  .ClockEnaMask     = (1 << MDR_CLK_EN_BIT_PORT_D)
};
#endif

#ifdef MDR_PORTE
const MDR_GPIO_Port   GPIO_E_Port = {
  .PORTx            =  MDR_PORTE,
  .RST_ClockEn_Addr =  MDR_CLK_EN_ADDR_PORT_E,
  .ClockEnaMask     = (1 << MDR_CLK_EN_BIT_PORT_E)
};
#endif

#ifdef MDR_PORTF
const MDR_GPIO_Port   GPIO_F_Port = {
  .PORTx            =  MDR_PORTF,
  .RST_ClockEn_Addr =  MDR_CLK_EN_ADDR_PORT_F,
  .ClockEnaMask     = (1 << MDR_CLK_EN_BIT_PORT_F)
};
#endif

#ifdef MDR_PORTG
const MDR_GPIO_Port   GPIO_G_Port = {
  .PORTx            =  MDR_PORTG,
  .RST_ClockEn_Addr =  MDR_CLK_EN_ADDR_PORT_G,
  .ClockEnaMask     = (1 << MDR_CLK_EN_BIT_PORT_G)
};
#endif

#ifdef MDR_PORTH
const MDR_GPIO_Port   GPIO_H_Port = {
  .PORTx            =  MDR_PORTH,
  .RST_ClockEn_Addr =  MDR_CLK_EN_ADDR_PORT_H,
  .ClockEnaMask     = (1 << MDR_CLK_EN_BIT_PORT_H)
};
#endif

#ifdef MDR_PORTI
const MDR_GPIO_Port   GPIO_I_Port = {
  .PORTx            =  MDR_PORTI,
  .RST_ClockEn_Addr =  MDR_CLK_EN_ADDR_PORT_I,
  .ClockEnaMask     = (1 << MDR_CLK_EN_BIT_PORT_I)
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

#define SET_OR_CLEAR(cfg, valSet, outReg, mask)     if ((cfg) == valSet) (outReg) =  (mask); else (outReg) &= ~(mask)
#define SET_OR_CLEAR_HI(cfg, valSet, outReg, mask)  if ((cfg) == valSet) (outReg) = ((mask) << 16); else (outReg) &= ~((mask) << 16)

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
  GPIO_Port->RXTX   = cfgRegs->RXTX;
  GPIO_Port->OE     = cfgRegs->OE;
  GPIO_Port->FUNC   = cfgRegs->FUNC;
  GPIO_Port->ANALOG = cfgRegs->ANALOG;
  GPIO_Port->PULL   = cfgRegs->PULL;
  GPIO_Port->PD     = cfgRegs->PD;
  GPIO_Port->PWR    = cfgRegs->PWR;
  GPIO_Port->GFEN   = cfgRegs->GFEN;
#else
  GPIO_Port->RXTX   = cfgRegs->RXTX   & (~JTAG_PINS(GPIO_Port));
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

void MDR_Port_ToPinCfg(MDR_Pin_IO InOut, MDR_PIN_FUNC pinFunc, const MDR_PinDig_GroupPinCfg *groupPinCfg, MDR_GPIO_PinCfg *pinCfg)  
{
  IO_ToCfg(InOut, &pinCfg->OutputEnable, &pinCfg->PullUp, &pinCfg->PullDown);    
  pinCfg->RxTx        = MDR_PIN_Low; 
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
void MDR_Port_InitDigPin(MDR_PORT_Type *GPIO_Port, uint32_t pinInd, MDR_Pin_IO pinInOut, MDR_PIN_FUNC pinFunc, const MDR_PinDig_GroupPinCfg *groupPinCfg)  
{
  uint32_t offsVal;
  MDR_GPIO_SetCfg tmpRegs; 
  uint32_t pinSelect;
  
  MDR_OnOff  regOutEn, regPULL_Up, regPULL_Down;
  
  IO_ToCfg(pinInOut, &regOutEn, &regPULL_Up, &regPULL_Down);      
  
  MDR_Port_ReadRegs(GPIO_Port, &tmpRegs);

  pinSelect = 1 << pinInd;
  tmpRegs.RXTX   &= pinSelect;  
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
  pCfgClr->clrPins =  pinSelect;
  pCfgClr->clrHiLo = (pinSelect | (pinSelect << 16));
  
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

void MDR_Port_Init_PortIN(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect)
{
  MDR_PinDig_GroupPinCfg groupPinCfg = {
    .DigMode   = MDR_On,
    .OpenDrain = MDR_Off,
    .Power     = MDR_PIN_PWR_OFF,
    .InpFilterEn  = MDR_Off,
    .InpSchmEn    = MDR_Off}; 
    
  MDR_Port_InitDigPort(GPIO_Port, pinSelect, MDR_Pin_In, &groupPinCfg);  
}

void MDR_Port_InitPin_PortIN(MDR_PORT_Type *GPIO_Port, uint32_t pinInd)
{
  MDR_PinDig_GroupPinCfg groupPinCfg = {
    .DigMode   = MDR_On,
    .OpenDrain = MDR_Off,
    .Power     = MDR_PIN_PWR_OFF,
    .InpFilterEn  = MDR_Off,
    .InpSchmEn    = MDR_Off};  
  
  MDR_Port_InitDigPinPort(GPIO_Port, pinInd, MDR_Pin_In, &groupPinCfg);    
}


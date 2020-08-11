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
  GPIO_Port->RXTX_Clr   = 0xFFFFFFFFUL;  
  GPIO_Port->OE_Clr     = 0xFFFFFFFFUL; 
  GPIO_Port->FUNC0_Clr  = 0xFFFFFFFFUL; 
  GPIO_Port->FUNC1_Clr  = 0xFFFFFFFFUL; 
  GPIO_Port->FUNC2_Clr  = 0xFFFFFFFFUL; 
  GPIO_Port->FUNC3_Clr  = 0xFFFFFFFFUL; 
  GPIO_Port->ANALOG_Clr = 0xFFFFFFFFUL; 
  GPIO_Port->PULLUP_Clr = 0xFFFFFFFFUL; 
  GPIO_Port->PULLDOWN_Clr = 0xFFFFFFFFUL; 
  GPIO_Port->PD_Clr     = 0xFFFFFFFFUL;  
  GPIO_Port->PWR0_Clr   = 0xFFFFFFFFUL; 
  GPIO_Port->PWR1_Clr   = 0xFFFFFFFFUL; 
}

// ======= Вспомогательные функции, для логгирования и отладки ===========

void MDR_Port_ReadRegs(MDR_PORT_Type *GPIO_Port, MDR_GPIO_SetCfg *portCfg)
{
  portCfg->RXTX    = GPIO_Port->RXTX;
  portCfg->OE      = GPIO_Port->OE_Set;
  
  portCfg->FUNC_0_7   = GPIO_Port->FUNC0_Set;
  portCfg->FUNC_8_15  = GPIO_Port->FUNC1_Set;
  portCfg->FUNC_16_23 = GPIO_Port->FUNC2_Set;
  portCfg->FUNC_24_31 = GPIO_Port->FUNC3_Set;
  portCfg->ANALOG     = GPIO_Port->ANALOG_Set; 
  portCfg->PULL_Up    = GPIO_Port->PULLUP_Set;
  portCfg->PULL_Down  = GPIO_Port->PULLDOWN_Set;
  portCfg->PD         = GPIO_Port->PD_Set;
  portCfg->PWR_0_15   = GPIO_Port->PWR0_Set;
  portCfg->PWR_16_31  = GPIO_Port->PWR1_Set;
}

void MDR_Port_WriteRegs(MDR_PORT_Type *GPIO_Port, MDR_GPIO_SetCfg *cfgSet, MDR_GPIO_ClearCfg *cfgClr)
{
#ifndef PORT_JTAG
  GPIO_Port->ANALOG_Clr = cfgClr->clrPins;
  GPIO_Port->OE_Clr     = cfgClr->clrPins;  
  GPIO_Port->PD_Clr     = cfgClr->clrPins;  
  GPIO_Port->PWR0_Clr   = cfgClr->clrPWR_0_15;
  GPIO_Port->PWR1_Clr   = cfgClr->clrPWR_16_31;  
  GPIO_Port->RXTX_Clr   = cfgClr->clrPins;
  GPIO_Port->FUNC0_Clr  = cfgClr->clrFUNC_0_7;
  GPIO_Port->FUNC1_Clr  = cfgClr->clrFUNC_8_15;
  GPIO_Port->FUNC2_Clr  = cfgClr->clrFUNC_16_23;
  GPIO_Port->FUNC3_Clr  = cfgClr->clrFUNC_24_31;
  GPIO_Port->PULLUP_Clr = cfgClr->clrPins;
  GPIO_Port->PULLDOWN_Clr = cfgClr->clrPins;  
  
  GPIO_Port->FUNC0_Set  = cfgSet->FUNC_0_7;
  GPIO_Port->FUNC1_Set  = cfgSet->FUNC_8_15;
  GPIO_Port->FUNC2_Set  = cfgSet->FUNC_16_23;
  GPIO_Port->FUNC3_Set  = cfgSet->FUNC_24_31;
  GPIO_Port->PULLUP_Set = cfgSet->PULL_Up;
  GPIO_Port->PULLDOWN_Set = cfgSet->PULL_Down;
  GPIO_Port->PD_Set     = cfgSet->PD;  
  GPIO_Port->PWR0_Set   = cfgSet->PWR_0_15;
  GPIO_Port->PWR1_Set   = cfgSet->PWR_16_31;  
  GPIO_Port->RXTX_Set   = cfgSet->RXTX;
  GPIO_Port->OE_Set     = cfgSet->OE;
  GPIO_Port->ANALOG_Set = cfgSet->ANALOG; 
#else
  if (GPIO_Port != PORT_JTAG)
  {
    GPIO_Port->ANALOG_Clr = cfgClr->clrPins;
    GPIO_Port->OE_Clr     = cfgClr->clrPins;  
    GPIO_Port->PD_Clr     = cfgClr->clrPins;  
    GPIO_Port->PWR0_Clr   = cfgClr->clrPWR_0_15;
    GPIO_Port->PWR1_Clr   = cfgClr->clrPWR_16_31;  
    GPIO_Port->RXTX_Clr   = cfgClr->clrPins;
    GPIO_Port->FUNC0_Clr  = cfgClr->clrFUNC_0_7;
    GPIO_Port->FUNC1_Clr  = cfgClr->clrFUNC_8_15;
    GPIO_Port->FUNC2_Clr  = cfgClr->clrFUNC_16_23;
    GPIO_Port->FUNC3_Clr  = cfgClr->clrFUNC_24_31;
    GPIO_Port->PULLUP_Clr = cfgClr->clrPins;
    GPIO_Port->PULLDOWN_Clr = cfgClr->clrPins;  
    
    GPIO_Port->FUNC0_Set  = cfgSet->FUNC_0_7;
    GPIO_Port->FUNC1_Set  = cfgSet->FUNC_8_15;
    GPIO_Port->FUNC2_Set  = cfgSet->FUNC_16_23;
    GPIO_Port->FUNC3_Set  = cfgSet->FUNC_24_31;
    GPIO_Port->PULLUP_Set = cfgSet->PULL_Up;
    GPIO_Port->PULLDOWN_Set = cfgSet->PULL_Down;
    GPIO_Port->PD_Set     = cfgSet->PD;  
    GPIO_Port->PWR0_Set   = cfgSet->PWR_0_15;
    GPIO_Port->PWR1_Set   = cfgSet->PWR_16_31;  
    GPIO_Port->RXTX_Set   = cfgSet->RXTX;
    GPIO_Port->OE_Set     = cfgSet->OE;
    GPIO_Port->ANALOG_Set = cfgSet->ANALOG; 
  }
  else
  {
    //  Clear
    GPIO_Port->ANALOG_Clr = cfgClr->clrPins;
    GPIO_Port->OE_Clr     = cfgClr->clrPins;  
    GPIO_Port->PD_Clr     = cfgClr->clrPins;  
    GPIO_Port->PWR0_Clr   = cfgClr->clrPWR_0_15;
    GPIO_Port->PWR1_Clr   = cfgClr->clrPWR_16_31;  
    GPIO_Port->RXTX_Clr   = cfgClr->clrPins;
    GPIO_Port->FUNC0_Clr  = cfgClr->clrFUNC_0_7;
    GPIO_Port->FUNC1_Clr  = cfgClr->clrFUNC_8_15;
    GPIO_Port->FUNC2_Clr  = cfgClr->clrFUNC_16_23;
    GPIO_Port->FUNC3_Clr  = cfgClr->clrFUNC_24_31;
    GPIO_Port->PULLUP_Clr   = cfgClr->clrPins;
    GPIO_Port->PULLDOWN_Clr = cfgClr->clrPins;

    //  Set
    GPIO_Port->FUNC0_Set    = cfgSet->FUNC_0_7   & ~(PORT_JTAG_Func0Sel);
    GPIO_Port->FUNC1_Set    = cfgSet->FUNC_8_15  & ~(PORT_JTAG_Func1Sel);
    GPIO_Port->FUNC2_Set    = cfgSet->FUNC_16_23 & ~(PORT_JTAG_Func2Sel);
    GPIO_Port->FUNC3_Set    = cfgSet->FUNC_24_31 & ~(PORT_JTAG_Func3Sel);
    GPIO_Port->PULLUP_Set   = cfgSet->PULL_Up    & ~(PORT_JTAG_PinSel);
    GPIO_Port->PULLDOWN_Set = cfgSet->PULL_Down  & ~(PORT_JTAG_PinSel);
    GPIO_Port->PD_Set       = cfgSet->PD         & ~(PORT_JTAG_PinSel);
    GPIO_Port->PWR0_Set     = cfgSet->PWR_0_15   & ~(PORT_JTAG_PWR0);
    GPIO_Port->PWR1_Set     = cfgSet->PWR_16_31  & ~(PORT_JTAG_PWR1);
    GPIO_Port->RXTX_Set     = cfgSet->RXTX       & ~(PORT_JTAG_PinSel);
    GPIO_Port->OE_Set       = cfgSet->OE         & ~(PORT_JTAG_PinSel);
    GPIO_Port->ANALOG_Set   = cfgSet->ANALOG     & ~(PORT_JTAG_PinSel);
  }
#endif   
}

void MDR_Port_Clear_ClearCfg(MDR_GPIO_ClearCfg *cfgClr)
{
  cfgClr->clrPins       = 0;
  cfgClr->clrFUNC_0_7   = 0;
  cfgClr->clrFUNC_8_15  = 0;
  cfgClr->clrFUNC_16_23 = 0;
  cfgClr->clrFUNC_24_31 = 0;
  cfgClr->clrPWR_0_15   = 0;
  cfgClr->clrPWR_16_31  = 0;
}


void MDR_Port_Clear_SetCfg(MDR_GPIO_SetCfg *cfgSet)
{
  cfgSet->RXTX       = 0;
  cfgSet->OE         = 0;
  cfgSet->FUNC_0_7   = 0;
  cfgSet->FUNC_8_15  = 0;
  cfgSet->FUNC_16_23 = 0;
  cfgSet->FUNC_24_31 = 0;
  cfgSet->ANALOG     = 0;
  cfgSet->PULL_Up    = 0;
  cfgSet->PULL_Down  = 0;
  cfgSet->PD         = 0;
  cfgSet->PWR_0_15   = 0;
  cfgSet->PWR_16_31  = 0;
}


// =========== Функции настройки портов GPIO, базовая реализация ===============

static void MDR_Port_MaskAddCfg(uint32_t pinSelect, MDR_GPIO_PinCfg *pinCfg, MDR_Port_ApplyMask *applyMask)
{
  uint32_t i, j; 
  uint32_t offsPin, pinInd;
  uint32_t offsPWD;
  
  MDR_GPIO_SetCfg   *setRegs = &(applyMask->MaskSET);
  MDR_GPIO_ClearCfg *clrRegs = &(applyMask->MaskCLR);
  
  uint32_t *pSetFUNC[4] = {&(setRegs->FUNC_0_7),    &(setRegs->FUNC_8_15),    &(setRegs->FUNC_16_23),    &(setRegs->FUNC_24_31)};
  uint32_t *pClrFUNC[4] = {&(clrRegs->clrFUNC_0_7), &(clrRegs->clrFUNC_8_15), &(clrRegs->clrFUNC_16_23), &(clrRegs->clrFUNC_24_31)};
  
  uint32_t *pSetPWD[4] = {&(setRegs->PWR_0_15),    &(setRegs->PWR_0_15),    &(setRegs->PWR_16_31),     &(setRegs->PWR_16_31)};
  uint32_t *pClrPWD[4] = {&(clrRegs->clrPWR_0_15), &(clrRegs->clrPWR_0_15), &(clrRegs->clrPWR_16_31), &(clrRegs->clrPWR_16_31)};  

  //  Clear Mask
  clrRegs->clrPins   |= pinSelect;
  //  Set Mask
  setRegs->RXTX      |= (pinCfg->RxTx    == MDR_RIN_High) ? pinSelect : 0;
  setRegs->OE        |= (pinCfg->OutputEnable == MDR_On)  ? pinSelect : 0;
  setRegs->ANALOG    |= (pinCfg->DigMode   == MDR_On)     ? pinSelect : 0;
  setRegs->PULL_Up   |= (pinCfg->PullUp    == MDR_On)     ? pinSelect : 0;
  setRegs->PULL_Down |= (pinCfg->PullDown  == MDR_On)     ? pinSelect : 0;
  setRegs->PD        |= (pinCfg->OpenDrain == MDR_On)     ? pinSelect : 0; 

  //  Fill Funcx and PWRx Regs 
  for (j = 0; j < 4; ++j)
  {
    offsPin = 8 * j;
    offsPWD = (j & 0x1UL) * 16;
    
    for (i = 0; i < 8; ++i)
    {
      pinInd = i + offsPin;
      if (pinSelect & (1 << pinInd))
      {
        *pSetFUNC[j] |= (uint32_t)pinCfg->Func <<  (i << 2);
        *pSetPWD[j]  |= (uint32_t)pinCfg->Power  << ((i << 1) + offsPWD);

        *pClrFUNC[j] |= MDR_GPIO_FUNC__Pin_Msk <<  (i << 2);
        *pClrPWD[j]  |= MDR_GPIO_PWR__Pin_Msk  << ((i << 1) + offsPWD);
      }
    }
  }  
}

void MDR_Port_Init(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect, MDR_GPIO_PinCfg *pinCfg)
{
  MDR_Port_ApplyMask applyMask;
  
  MDR_Port_Clear_SetCfg(&applyMask.MaskSET);
  MDR_Port_Clear_ClearCfg(&applyMask.MaskCLR);
  
  MDR_Port_MaskAddCfg(pinSelect, pinCfg, &applyMask);    
  MDR_Port_MaskApply(GPIO_Port, &applyMask);   
}

void MDR_Port_FillClearMask(uint32_t pinSelect, MDR_GPIO_ClearCfg *clrRegs)
{
  uint32_t i, j;
  uint32_t offsPin, pinInd;
  uint32_t offsPWD;
  
  uint32_t *pClrFUNC[4] = {&(clrRegs->clrFUNC_0_7), &(clrRegs->clrFUNC_8_15), &(clrRegs->clrFUNC_16_23), &(clrRegs->clrFUNC_24_31)};
  uint32_t *pClrPWD[4]  = {&(clrRegs->clrPWR_0_15), &(clrRegs->clrPWR_0_15),  &(clrRegs->clrPWR_16_31),  &(clrRegs->clrPWR_16_31)};  

  clrRegs->clrPins |= pinSelect;
  
  for (j = 0; j < 4; ++j)
  {
    offsPin = 8 * j;
    offsPWD = (j & 0x1UL) * 16;
    
    for (i = 0; i < 8; ++i)
    {
      pinInd = i + offsPin;
      if (pinSelect & (1 << pinInd))
      {
        *pClrFUNC[j] |= MDR_GPIO_FUNC__Pin_Msk <<  (i << 2);
        *pClrPWD[j]  |= MDR_GPIO_PWR__Pin_Msk  << ((i << 1) + offsPWD);
      }
    }
  }
  
}

void MDR_Port_InitAnalog(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect)
{
  MDR_GPIO_ClearCfg clrRegs;   

  MDR_Port_Clear_ClearCfg(&clrRegs);    
  MDR_Port_FillClearMask(pinSelect, &clrRegs);
  
  GPIO_Port->ANALOG_Clr = clrRegs.clrPins;    
  GPIO_Port->OE_Clr     = clrRegs.clrPins;    
  GPIO_Port->PD_Clr     = clrRegs.clrPins;    
  GPIO_Port->PWR0_Clr   = clrRegs.clrPWR_0_15;  
  GPIO_Port->PWR1_Clr   = clrRegs.clrPWR_16_31;  
  GPIO_Port->RXTX_Clr   = clrRegs.clrPins;
  
  GPIO_Port->FUNC0_Clr  = clrRegs.clrFUNC_0_7;  
  GPIO_Port->FUNC1_Clr  = clrRegs.clrFUNC_8_15;  
  GPIO_Port->FUNC2_Clr  = clrRegs.clrFUNC_16_23;  
  GPIO_Port->FUNC3_Clr  = clrRegs.clrFUNC_24_31;  
  GPIO_Port->PULLUP_Clr = clrRegs.clrPins;  
  GPIO_Port->PULLDOWN_Clr = clrRegs.clrPins;  
}


// =============================== ВАРИАНТ НАСТРОЙКИ 2 ====================================
// Общие настройки для группы битов вынесены в отдельную структуру - MDR_PinDig_GroupPinCfg. 
// Остальные, часто различающиеся, настройки для одиночных или нескольких пинов задаются при вызове функций
// в параметрах - InOut и Func.


// Variable настройки в структуру

__STATIC_INLINE void IO_ToCfg(MDR_Pin_IO InOut, MDR_OnOff *regOutEn, MDR_OnOff *regPullUp, MDR_OnOff *regPullDown)
{  
  *regOutEn = (MDR_OnOff)(InOut == MDR_Pin_Out);
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

//  Выделение настроек, одинаковых для группы пинов, в отдельную структуру
void MDR_Port_InitDigGroupPinCfg(MDR_OnOff pinOpenDrain, MDR_PIN_PWR pinPower, MDR_PinDig_GroupPinCfg *groupPinCfg)
{
  groupPinCfg->DigMode   = MDR_On;
  groupPinCfg->OpenDrain = pinOpenDrain;
  groupPinCfg->Power     = pinPower;
}

//  Конвертация в MDR_GPIO_PinCfg для вызова первого варианта
void MDR_Port_ToPinCfgEx(MDR_Pin_IO pinInOut, MDR_PIN_FUNC pinFunc, const MDR_PinDig_GroupPinCfg *groupPinCfg, MDR_GPIO_PinCfg *pinCfg, MDR_PIN_RXTX pinLevel)
{
  IO_ToCfg(pinInOut, &pinCfg->OutputEnable, &pinCfg->PullUp, &pinCfg->PullDown);    
  pinCfg->RxTx = pinLevel; 
  pinCfg->Func = pinFunc;
  pinCfg->DigMode   = groupPinCfg->DigMode;
  pinCfg->OpenDrain = groupPinCfg->OpenDrain;
  pinCfg->Power     = groupPinCfg->Power;
}

//  Инициализация пинов с дополнительными настройками и групповыми.
void MDR_Port_InitDig(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect, MDR_Pin_IO pinInOut, MDR_PIN_FUNC pinFunc, const MDR_PinDig_GroupPinCfg *groupPinCfg)
{
  MDR_GPIO_PinCfg pinCfg;
   
  MDR_Port_ToPinCfg(pinInOut, pinFunc, groupPinCfg, &pinCfg);
  MDR_Port_Init(GPIO_Port, pinSelect, &pinCfg);
}

void MDR_Port_InitDigPinEx(MDR_PORT_Type *GPIO_Port, uint32_t pinInd, MDR_Pin_IO pinInOut, MDR_PIN_FUNC pinFunc, const MDR_PinDig_GroupPinCfg *groupPinCfg, bool setHiLevel)
{
  MDR_Port_ApplyMask applyMask;
  
  MDR_Port_Clear_SetCfg(&applyMask.MaskSET);
  MDR_Port_Clear_ClearCfg(&applyMask.MaskCLR);

  if (setHiLevel)
    applyMask.MaskSET.RXTX = 1 << pinInd;
  
  MDR_Port_MaskAddPin(pinInd, pinInOut, pinFunc, groupPinCfg, &applyMask);
  MDR_Port_WriteRegs(GPIO_Port, &applyMask.MaskSET, &applyMask.MaskCLR);
}


// Упрощенная настройка пинов/пина в функции порт IN/OUT по умолчанию
void MDR_Port_Init_PortOUT   (MDR_PORT_Type *GPIO_Port, uint32_t pinSelect, MDR_PIN_PWR pinPWR)
{
  MDR_PinDig_GroupPinCfg groupPinCfg = {
    .DigMode   = MDR_On,
    .OpenDrain = MDR_Off,
    .Power     = pinPWR};
  
  MDR_Port_InitDigPort(GPIO_Port, pinSelect, MDR_Pin_Out, &groupPinCfg);
}

void MDR_Port_InitPin_PortOUT(MDR_PORT_Type *GPIO_Port, uint32_t pinInd,    MDR_PIN_PWR pinPWR)
{
  MDR_PinDig_GroupPinCfg groupPinCfg = {
    .DigMode   = MDR_On,
    .OpenDrain = MDR_Off,
    .Power     = pinPWR};
  
  MDR_Port_InitDigPinPort(GPIO_Port, pinInd, MDR_Pin_Out, &groupPinCfg);  
}

void MDR_Port_Init_PortIN_Pull(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect, MDR_Pin_InPull pinPull)
{
  MDR_PinDig_GroupPinCfg groupPinCfg = {
    .DigMode   = MDR_On,
    .OpenDrain = MDR_Off,
    .Power     = MDR_PIN_PWR_OFF};
  
  MDR_Port_InitDigPort(GPIO_Port, pinSelect, (MDR_Pin_IO)pinPull, &groupPinCfg);  
}

void MDR_Port_InitPin_PortIN_Pull(MDR_PORT_Type *GPIO_Port, uint32_t pinInd, MDR_Pin_InPull pinPull)
{
  MDR_PinDig_GroupPinCfg groupPinCfg = {
    .DigMode   = MDR_On,
    .OpenDrain = MDR_Off,
    .Power     = MDR_PIN_PWR_OFF};
  
  MDR_Port_InitDigPinPort(GPIO_Port, pinInd, (MDR_Pin_IO)pinPull, &groupPinCfg);    
}


// =============================== ВАРИАНТ НАСТРОЙКИ 2+ (Дополнение) ========================
//  Сбор настроек пинов порта в структуру с масками CLR и SET для последующего применения к портам за один вызов Apply
//  Иногда это оптимальней, чем вызывать применение в порт для каждого отдельного пина

// Структура масок, куда будут собираться настройки пинов
void MDR_Port_MaskClear(MDR_Port_ApplyMask *applyMask)
{
  MDR_Port_Clear_ClearCfg(&applyMask->MaskCLR);
  MDR_Port_Clear_SetCfg(&applyMask->MaskSET);
}

//  Добавление в маски настроек группы пинов
//    Пины в аналоговую функцию
void MDR_Port_MaskAddAnalog(uint32_t PinSelect, MDR_Port_ApplyMask *ApplyMask)
{
  MDR_Port_FillClearMask(PinSelect, &ApplyMask->MaskCLR);
}

void MDR_Port_MaskAdd(uint32_t PinSelect, MDR_Pin_IO InOut, MDR_PIN_FUNC pinFunc, const MDR_PinDig_GroupPinCfg *groupPinCfg, MDR_Port_ApplyMask *applyMask)
{
  MDR_GPIO_PinCfg pinCfg;
  
  MDR_Port_ToPinCfg(InOut, pinFunc, groupPinCfg, &pinCfg);
  MDR_Port_MaskAddCfg(PinSelect, &pinCfg, applyMask);
}

//  Добавление в маски настроек одного пина
void MDR_Port_MaskAddPin(uint32_t pinInd, MDR_Pin_IO pinInOut, MDR_PIN_FUNC pinFunc, const MDR_PinDig_GroupPinCfg *groupPinCfg, MDR_Port_ApplyMask *applyMask)
{
  uint32_t offs;
  MDR_OnOff  regOutEn, regPULL_Up, regPULL_Down;
  
  MDR_GPIO_SetCfg   *setRegs = &(applyMask->MaskSET);
  MDR_GPIO_ClearCfg *clrRegs = &(applyMask->MaskCLR);
    
  IO_ToCfg(pinInOut, &regOutEn, &regPULL_Up, &regPULL_Down);    
  
  setRegs->OE        |= (uint32_t)regOutEn     << pinInd;
  setRegs->ANALOG    |= 1                      << pinInd;
  setRegs->PULL_Up   |= (uint32_t)regPULL_Up   << pinInd;
  setRegs->PULL_Down |= (uint32_t)regPULL_Down << pinInd;
  setRegs->PD        |= (uint32_t)groupPinCfg->OpenDrain  << pinInd;
  
  clrRegs->clrPins |= 1 << pinInd;
  
  //  Func 
  offs = (pinInd % 8) << 2;
  switch (pinInd / 8) {
    case 0: 
      setRegs->FUNC_0_7    |= (uint32_t)pinFunc << offs; 
      clrRegs->clrFUNC_0_7 |= MDR_GPIO_FUNC__Pin_Msk << offs;
      break;
    case 1: 
      setRegs->FUNC_8_15    |= (uint32_t)pinFunc << offs; 
      clrRegs->clrFUNC_8_15 |= MDR_GPIO_FUNC__Pin_Msk << offs;
      break;
    case 2: 
      setRegs->FUNC_16_23    |= (uint32_t)pinFunc << offs; 
      clrRegs->clrFUNC_16_23 |= MDR_GPIO_FUNC__Pin_Msk << offs;
      break;
    case 3: 
      setRegs->FUNC_24_31    |= (uint32_t)pinFunc << offs; 
      clrRegs->clrFUNC_24_31 |= MDR_GPIO_FUNC__Pin_Msk << offs;
      break;
  }
  //  PWR 
  offs = (pinInd % 16) << 1;
  switch (pinInd / 16) {
    case 0: 
      setRegs->PWR_0_15    |= (uint32_t)groupPinCfg->Power << offs; 
      clrRegs->clrPWR_0_15 |= MDR_GPIO_PWR__Pin_Msk << offs;
      break;
    case 1: 
      setRegs->PWR_16_31    |= (uint32_t)groupPinCfg->Power << offs; 
      clrRegs->clrPWR_16_31 |= MDR_GPIO_PWR__Pin_Msk << offs;
      break;
  }  
}

//  Применение маски в порт
void MDR_Port_MaskApply(MDR_PORT_Type *GPIO_Port, MDR_Port_ApplyMask *ApplyMask)
{
  MDR_Port_WriteRegs(GPIO_Port, &ApplyMask->MaskSET, &ApplyMask->MaskCLR);
}

//  Применение масок к ранее считанному состоянию регистров порта - в ВЕ8 не имеет смылка, т.к. регистры задаются масками
void MDR_Port_MaskApplyEx(MDR_PORT_Type *GPIO_Port, MDR_Port_ApplyMask *applyMask, MDR_GPIO_SetCfg *readRegs)
{
  UNUSED(readRegs);
  MDR_Port_WriteRegs(GPIO_Port, &applyMask->MaskSET, &applyMask->MaskCLR);
}

// ========= Дополнительная настройка - Прерывания по уровню и контроль тока ===========
void MDR_Port_InitEx(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect, MDR_GPIO_PinCfgEx *pinCfg)
{
  GPIO_Port->CL_Clr = pinSelect;
  GPIO_Port->CL_Set = (pinCfg->CurrLim_En == MDR_On) ? pinSelect : 0;
  
  GPIO_Port->IE_Clr = pinSelect;
  GPIO_Port->IE_Set = (pinCfg->IRQ_En == MDR_On) ? pinSelect : 0;
  
  GPIO_Port->IT_Clr = pinSelect;
  GPIO_Port->IT_Set = (pinCfg->IRQ_LevelHigh == MDR_On) ? pinSelect : 0;
  
  GPIO_Port->IR_Clr = pinSelect;
  GPIO_Port->IR_Set = (pinCfg->IRQ_Req == MDR_On) ? pinSelect : 0;  
}

void MDR_Port_InitPinEx(MDR_PORT_Type *GPIO_Port, uint32_t pinInd, MDR_GPIO_PinCfgEx *pinCfg)
{
  MDR_Port_InitEx(GPIO_Port, 1 << pinInd, pinCfg);
}


// Управление подтяжками
void MDR_Port_SetPullUp(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect)
{
  GPIO_Port->PULLDOWN_Clr = pinSelect;
  GPIO_Port->PULLUP_Set = pinSelect; 
}

void MDR_Port_SetPullDown(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect)
{
  GPIO_Port->PULLUP_Clr = pinSelect;
  GPIO_Port->PULLDOWN_Set = pinSelect; 
}

void MDR_Port_ClearPull(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect)
{
  GPIO_Port->PULLDOWN_Clr = pinSelect;
  GPIO_Port->PULLUP_Clr = pinSelect;  
}

//  Получение информации для переключения функции для пина
MDR_GPIO_PinFuncCfg MDR_GPIO_GetPinFuncCfg(MDR_PORT_Type *GPIO_Port, uint32_t pinInd)
{
  MDR_GPIO_PinFuncCfg result;
  uint32_t pinRegOffs;

  if (pinInd < 8)
  {
    result.addrFuncSet = (uint32_t)&GPIO_Port->FUNC0_Set;
    result.addrFuncClr = (uint32_t)&GPIO_Port->FUNC0_Clr;
    pinRegOffs = pinInd;
    
  }
  else if (pinInd < 16)
  {
    result.addrFuncSet = (uint32_t)&GPIO_Port->FUNC1_Set;
    result.addrFuncClr = (uint32_t)&GPIO_Port->FUNC1_Clr;
    pinRegOffs = pinInd - 8;
  }
  else if (pinInd < 24)
  {
    result.addrFuncSet = (uint32_t)&GPIO_Port->FUNC2_Set;
    result.addrFuncClr = (uint32_t)&GPIO_Port->FUNC2_Clr;
    pinRegOffs = pinInd - 16;
  }
  else
  {
    result.addrFuncSet = (uint32_t)&GPIO_Port->FUNC3_Set;
    result.addrFuncClr = (uint32_t)&GPIO_Port->FUNC3_Clr;
    pinRegOffs = pinInd - 24;
  }
  
  result.funcPinPos = pinRegOffs << MDR_GPIO_FUNC__Pin_MskOffs;
  result.funcPinMsk = MDR_GPIO_FUNC__Pin_Msk << result.funcPinPos;  
  return result;
}

MDR_GPIO_PinFuncMasks MDR_GPIO_GetPinFuncMasks(MDR_PORT_Type *GPIO_Port, uint32_t pinInd, MDR_PIN_FUNC pinFunc)
{
  MDR_GPIO_PinFuncMasks pinMasks;
  MDR_GPIO_PinFuncCfg   pinCfg = MDR_GPIO_GetPinFuncCfg(GPIO_Port, pinInd);
  
  pinMasks.addrFuncSet = pinCfg.addrFuncSet;
  pinMasks.addrFuncClr = pinCfg.addrFuncClr;
  pinMasks.maskPinPort = pinCfg.funcPinMsk;  
  pinMasks.maskPinFunc = MDR_GPIO_GetPinFuncMask(&pinCfg, pinFunc);
  
  return pinMasks;
}

void MDR_GPIO_PinFunc_SetFunc(MDR_GPIO_PinFuncMasks *pinFuncMasks)
{
  REG32(pinFuncMasks->addrFuncClr) = pinFuncMasks->maskPinPort;
  REG32(pinFuncMasks->addrFuncSet) = pinFuncMasks->maskPinFunc;
}

void MDR_GPIO_PinFunc_SetPort(MDR_GPIO_PinFuncMasks *pinFuncMasks)
{
  REG32(pinFuncMasks->addrFuncClr) = pinFuncMasks->maskPinPort;
}

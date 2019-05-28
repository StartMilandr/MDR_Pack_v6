#include <MDR_GPIO_VE8x.h>

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
  GPIO_Port->RXTX_Clr   = cfgClr->clrPins;
  GPIO_Port->RXTX_Set   = cfgSet->RXTX;
  
  GPIO_Port->OE_Clr     = cfgClr->clrPins;  
  GPIO_Port->OE_Set     = cfgSet->OE;  
  
  GPIO_Port->FUNC0_Clr  = cfgClr->clrFUNC_0_7;
  GPIO_Port->FUNC0_Set  = cfgSet->FUNC_0_7;
  
  GPIO_Port->FUNC1_Clr  = cfgClr->clrFUNC_8_15;
  GPIO_Port->FUNC1_Set  = cfgSet->FUNC_8_15;
  
  GPIO_Port->FUNC2_Clr  = cfgClr->clrFUNC_16_23;
  GPIO_Port->FUNC2_Set  = cfgSet->FUNC_16_23;
  
  GPIO_Port->FUNC3_Clr  = cfgClr->clrFUNC_24_31;
  GPIO_Port->FUNC3_Set  = cfgSet->FUNC_24_31;
  
  GPIO_Port->ANALOG_Clr = cfgClr->clrPins;
  GPIO_Port->ANALOG_Set = cfgSet->ANALOG; 
  
  GPIO_Port->PULLUP_Clr = cfgClr->clrPins;
  GPIO_Port->PULLUP_Set = cfgSet->PULL_Up;
  
  GPIO_Port->PULLDOWN_Clr = cfgClr->clrPins;
  GPIO_Port->PULLDOWN_Set = cfgSet->PULL_Down;
  
  GPIO_Port->PD_Clr     = cfgClr->clrPins;  
  GPIO_Port->PD_Set     = cfgSet->PD;
  
  GPIO_Port->PWR0_Clr   = cfgClr->clrPWR_0_15;
  GPIO_Port->PWR0_Set   = cfgSet->PWR_0_15;
  
  GPIO_Port->PWR1_Clr   = cfgClr->clrPWR_16_31;
  GPIO_Port->PWR1_Set   = cfgSet->PWR_16_31;  
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
  setRegs->RXTX      |= (pinCfg->RXTX    == MDR_RIN_High)  ? pinSelect : 0;
  setRegs->OE        |= (pinCfg->OE      == MDR_PIN_OUT)   ? pinSelect : 0;
  setRegs->ANALOG    |= (pinCfg->ANALOG  == MDR_PIN_DIGIT) ? pinSelect : 0;
  setRegs->PULL_Up   |= (pinCfg->PULL_Up   == MDR_On)      ? pinSelect : 0;
  setRegs->PULL_Down |= (pinCfg->PULL_Down == MDR_On)      ? pinSelect : 0;
  setRegs->PD        |= (pinCfg->PD == MDR_PIN_OpenDrain)  ? pinSelect : 0; 

  //  Fill Funcx and PWRx Regs 
  for (j = 0; j < 4; ++j)
  {
    offsPin = 8 * j;
    offsPWD = (j & 0x1UL) * 16;
    
    for (i = 0; i < 8; ++i)
    {
      pinInd = i + offsPin;
      if (pinSelect & (i << pinInd))
      {
        *pSetFUNC[j] |= (uint32_t)pinCfg->FUNC <<  (i << 2);
        *pSetPWD[j]  |= (uint32_t)pinCfg->PWR  << ((i << 1) + offsPWD);

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

static void MDR_Port_AddAnalogPinCfg(uint32_t pinSelect, MDR_GPIO_ClearCfg *clrRegs)
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
      if (pinSelect & (i << pinInd))
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
  MDR_Port_AddAnalogPinCfg(pinSelect, &clrRegs);
  
  GPIO_Port->RXTX_Clr   = clrRegs.clrPins;
  GPIO_Port->OE_Clr     = clrRegs.clrPins;    
  GPIO_Port->FUNC0_Clr  = clrRegs.clrFUNC_0_7;  
  GPIO_Port->FUNC1_Clr  = clrRegs.clrFUNC_8_15;  
  GPIO_Port->FUNC2_Clr  = clrRegs.clrFUNC_16_23;  
  GPIO_Port->FUNC3_Clr  = clrRegs.clrFUNC_24_31;  
  GPIO_Port->ANALOG_Clr = clrRegs.clrPins;  
  GPIO_Port->PULLUP_Clr = clrRegs.clrPins;  
  GPIO_Port->PULLDOWN_Clr = clrRegs.clrPins;  
  GPIO_Port->PD_Clr     = clrRegs.clrPins;    
  GPIO_Port->PWR0_Clr   = clrRegs.clrPWR_0_15;  
  GPIO_Port->PWR1_Clr   = clrRegs.clrPWR_16_31;
}


// =============================== ВАРИАНТ НАСТРОЙКИ 2 ====================================
// Общие настройки для группы битов вынесены в отдельную структуру - MDR_PinDig_GroupPinCfg. 
// Остальные, часто различающиеся, настройки для одиночных или нескольких пинов задаются при вызове функций
// в параметрах - InOut и Func.


// Variable настройки в структуру

__STATIC_INLINE void IO_ToRegs(MDR_Pin_IO InOut, MDR_PIN_OE *regOE, MDR_OnOff *regPullUp, MDR_OnOff *regPullDown)
{  
  *regOE = (MDR_PIN_OE)(InOut == MDR_Pin_Out);
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
void MDR_Port_InitDigGroupRegs(MDR_PIN_PD pinDriver, MDR_PIN_PWR pinPower, MDR_PinDig_GroupPinCfg *groupPinCfg)
{
  groupPinCfg->ANALOG  = MDR_PIN_DIGIT;
  groupPinCfg->PD      = pinDriver;
  groupPinCfg->PWR     = pinPower;
}

//  Инициализация пинов с дополнительными настройками и групповыми.
void MDR_Port_InitDig(MDR_PORT_Type *GPIO_Port, uint32_t pinSelect, MDR_Pin_IO pinInOut, MDR_PIN_FUNC pinFunc, const MDR_PinDig_GroupPinCfg *groupPinCfg)
{
  MDR_GPIO_PinCfg pinCfg;
  
  IO_ToRegs(pinInOut, &pinCfg.OE, &pinCfg.PULL_Up, &pinCfg.PULL_Down);    
  pinCfg.RXTX = MDR_PIN_Low; 
  pinCfg.FUNC = pinFunc;
  pinCfg.ANALOG = groupPinCfg->ANALOG;
  pinCfg.PD = groupPinCfg->PD;
  pinCfg.PWR = groupPinCfg->PWR;
  
  MDR_Port_Init(GPIO_Port, pinSelect, &pinCfg);
}

void MDR_Port_InitDigPin(MDR_PORT_Type *GPIO_Port, uint32_t pinInd, MDR_Pin_IO pinInOut, MDR_PIN_FUNC pinFunc, const MDR_PinDig_GroupPinCfg *groupPinCfg)
{
  MDR_Port_ApplyMask applyMask;
  
  MDR_Port_Clear_SetCfg(&applyMask.MaskSET);
  MDR_Port_Clear_ClearCfg(&applyMask.MaskCLR);

  MDR_Port_MaskAddPin(pinInd, pinInOut, pinFunc, groupPinCfg, &applyMask);
  MDR_Port_WriteRegs(GPIO_Port, &applyMask.MaskSET, &applyMask.MaskCLR);
}

//  Конвертация в MDR_GPIO_PinCfg для вызова первого варианта
void MDR_Port_ToCfgRegs(MDR_Pin_IO InOut, MDR_PIN_FUNC pinFunc, const MDR_PinDig_GroupPinCfg *groupPinCfg, MDR_GPIO_PinCfg *pinCfg)
{
  IO_ToRegs(InOut, &pinCfg->OE, &pinCfg->PULL_Up, &pinCfg->PULL_Down);    
  pinCfg->RXTX = MDR_PIN_Low; 
  pinCfg->FUNC = pinFunc;
  pinCfg->ANALOG = groupPinCfg->ANALOG;
  pinCfg->PD = groupPinCfg->PD;
  pinCfg->PWR = groupPinCfg->PWR;
}


// =============================== ВАРИАНТ НАСТРОЙКИ 2+ (Дополнение) ========================
//  Сбор настроек пинов порта в структуру с масками CLR и SET для последующего применения к портам за один вызов Apply
//  Иногда это оптимальней, чем вызывать применение в порт для каждого отдельного пина

// Структура масок, куда будут собираться настройки пинов
void MDR_Port_MaskClear(MDR_Port_ApplyMask *ApplyMask)
{
  MDR_Port_Clear_ClearCfg(&ApplyMask->MaskCLR);
  MDR_Port_Clear_SetCfg(&ApplyMask->MaskSET);
}

//  Добавление в маски настроек группы пинов
//    Пины в аналоговую функцию
void MDR_Port_MaskAddAnalog(uint32_t PinSelect, MDR_Port_ApplyMask *ApplyMask)
{
  MDR_Port_AddAnalogPinCfg(PinSelect, &ApplyMask->MaskCLR);
}

void MDR_Port_MaskAdd(uint32_t PinSelect, MDR_Pin_IO InOut, MDR_PIN_FUNC pinFunc, const MDR_PinDig_GroupPinCfg *groupPinCfg, MDR_Port_ApplyMask *ApplyMask)
{
  MDR_GPIO_PinCfg pinCfg;
  
  MDR_Port_ToCfgRegs(InOut, pinFunc, groupPinCfg, &pinCfg);
  MDR_Port_MaskAddCfg(PinSelect, &pinCfg, ApplyMask);
}

//  Добавление в маски настроек одного пина
void MDR_Port_MaskAddPin(uint32_t pinInd, MDR_Pin_IO pinInOut, MDR_PIN_FUNC pinFunc, const MDR_PinDig_GroupPinCfg *groupPinCfg, MDR_Port_ApplyMask *applyMask)
{
  uint32_t offs;
  MDR_PIN_OE regOE;
  MDR_OnOff  regPULL_Up, regPULL_Down;
  
  MDR_GPIO_SetCfg   *setRegs = &(applyMask->MaskSET);
  MDR_GPIO_ClearCfg *clrRegs = &(applyMask->MaskCLR);
    
  IO_ToRegs(pinInOut, &regOE, &regPULL_Up, &regPULL_Down);    
  
  setRegs->RXTX      = 0;
  setRegs->OE        = (uint32_t)regOE        << pinInd;
  setRegs->ANALOG    = 1            << pinInd;
  setRegs->PULL_Up   = (uint32_t)regPULL_Up   << pinInd;
  setRegs->PULL_Down = (uint32_t)regPULL_Down << pinInd;
  setRegs->PD        = (uint32_t)groupPinCfg->PD  << pinInd;
  
  //  Func
  setRegs->FUNC_0_7      = 0;
  setRegs->FUNC_8_15     = 0;
  setRegs->FUNC_16_23    = 0;
  setRegs->FUNC_24_31    = 0;
  clrRegs->clrFUNC_0_7   = 0;
  clrRegs->clrFUNC_8_15  = 0;
  clrRegs->clrFUNC_16_23 = 0;
  clrRegs->clrFUNC_24_31 = 0;
  
  offs = (pinInd % 8) << 2;
  switch (pinInd / 8) {
    case 0: 
      setRegs->FUNC_0_7    = (uint32_t)pinFunc << offs; 
      clrRegs->clrFUNC_0_7 = MDR_GPIO_FUNC__Pin_Msk << offs;
      break;
    case 1: 
      setRegs->FUNC_8_15  = (uint32_t)pinFunc << offs; 
      clrRegs->clrFUNC_8_15 = MDR_GPIO_FUNC__Pin_Msk << offs;
      break;
    case 2: 
      setRegs->FUNC_16_23 = (uint32_t)pinFunc << offs; 
      clrRegs->clrFUNC_16_23 = MDR_GPIO_FUNC__Pin_Msk << offs;
      break;
    case 3: 
      setRegs->FUNC_24_31 = (uint32_t)pinFunc << offs; 
      clrRegs->clrFUNC_24_31 = MDR_GPIO_FUNC__Pin_Msk << offs;
      break;
  };
  //  PWR
  setRegs->PWR_0_15 = 0;
  setRegs->PWR_16_31 = 0;
  clrRegs->clrPWR_0_15 = 0;
  clrRegs->clrPWR_16_31 = 0;
  
  offs = (pinInd % 16) << 1;
  switch (pinInd / 16) {
    case 0: 
      setRegs->PWR_0_15   = (uint32_t)groupPinCfg->PWR << offs; 
      clrRegs->clrPWR_0_15 = MDR_GPIO_PWR__Pin_Msk << offs;
      break;
    case 1: 
      setRegs->PWR_16_31  = (uint32_t)groupPinCfg->PWR << offs; 
      clrRegs->clrPWR_16_31 = MDR_GPIO_PWR__Pin_Msk << offs;
      break;
  };  
}

//  Применение маски в порт
void MDR_Port_MaskApply(MDR_PORT_Type *GPIO_Port, MDR_Port_ApplyMask *ApplyMask)
{
  MDR_Port_WriteRegs(GPIO_Port, &ApplyMask->MaskSET, &ApplyMask->MaskCLR);
}

//  Применение масок к ранее считанному состоянию регистров порта - в ВЕ8 не имеет смылка, т.к. регистры задаются масками
void MDR_Port_MaskApplyEx(MDR_PORT_Type *GPIO_Port, MDR_Port_ApplyMask *ApplyMask, MDR_GPIO_PinCfg *readRegs)
{
  UNUSED(readRegs);
  MDR_Port_WriteRegs(GPIO_Port, &ApplyMask->MaskSET, &ApplyMask->MaskCLR);
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


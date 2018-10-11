#include <MDR_GPIO.h>

//  Маски для стирания бит
#define CLR_FUNC     MDR_GPIO_FUNC__Pin_Msk
#define CLR_PD      (MDR_GPIO_PD_Driver__Pin_Msk | MDR_GPIO_PD_Schmitt__Pin_Msk)

//  Параметры для настройки пинов по умолчанию
const MDR_PinDig_PermRegs PinDig_PermRegsDef = 
{
  .ANALOG  = 1,
  .PD      = VAL2FLD(MDR_PIN_PullPush, MDR_GPIO_PD_Driver__Pin) | VAL2FLD(MDR_Off, MDR_GPIO_PD_Schmitt__Pin),
  .PWR     = MDR_PIN_SLOW,
  .GFEN    = MDR_Off
};

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
void MDR_Port_Init(MDR_PORT_Type *GPIO_Port, uint32_t PinSelect, MDR_GPIO_CfgRegs *cfgRegs)
{
  uint32_t i, i2;
  uint32_t bitInd;
  uint32_t clrBit, clrBit2, clrHiLo;  
  MDR_GPIO_CfgRegs tmpRegs;
  
  MDR_Port_ReadRegs(GPIO_Port, &tmpRegs);

  for (i = 0; i < MDR_GPIO_Pin_Count; ++i)
  {
    bitInd = 1 << i;
    if (PinSelect & bitInd)
    { 
      i2 = i << 1;
      
      clrBit  = ~bitInd;
      clrBit2 = ~(CLR_FUNC << i2);
      clrHiLo = ~(CLR_PD   << i);
      
      tmpRegs.RXTX    = (tmpRegs.RXTX   & clrBit ) | (cfgRegs->RXTX   << i);
      tmpRegs.OE      = (tmpRegs.OE     & clrBit ) | (cfgRegs->OE     << i);
      tmpRegs.FUNC    = (tmpRegs.FUNC   & clrBit2) | (cfgRegs->FUNC   << i2);
      tmpRegs.ANALOG  = (tmpRegs.ANALOG & clrBit ) | (cfgRegs->ANALOG << i);
      tmpRegs.PULL    = (tmpRegs.PULL   & clrHiLo) | (cfgRegs->PULL   << i);
      tmpRegs.PD      = (tmpRegs.PD     & clrHiLo) | (cfgRegs->PD     << i);      
      tmpRegs.PWR     = (tmpRegs.PWR    & clrBit2) | (cfgRegs->PWR    << i2);
      tmpRegs.GFEN    = (tmpRegs.GFEN   & clrBit ) | (cfgRegs->GFEN   << i);
      
      PinSelect &= clrBit;
      if (PinSelect == 0)
        break;
    }
  }
  
  MDR_Port_WriteRegs(GPIO_Port, &tmpRegs);   
}

void MDR_Port_InitAnalog(MDR_PORT_Type *GPIO_Port, uint32_t PinSelect)
{
  uint32_t i;
  uint32_t bitInd;
  uint32_t clrBit, clrBit2, clrHiLo;
  MDR_GPIO_CfgRegs tmpRegs;
  
  MDR_Port_ReadRegs(GPIO_Port, &tmpRegs);
  
  for (i = 0; i < MDR_GPIO_Pin_Count; ++i)
  {
    bitInd = 1 << i;
    if (PinSelect & bitInd)
    {  
      clrBit  = ~bitInd;
      clrBit2 = ~(CLR_FUNC << (i << 1));
      clrHiLo = ~(CLR_PD   << i);
      
      tmpRegs.RXTX    &= clrBit;
      tmpRegs.OE      &= clrBit;
      tmpRegs.FUNC    &= clrBit2;
      tmpRegs.ANALOG  &= clrBit;
      tmpRegs.PULL    &= clrHiLo;
      tmpRegs.PD      &= clrHiLo;
      tmpRegs.PWR     &= clrBit2;
      tmpRegs.GFEN    &= clrBit;
      
      PinSelect &= clrBit;
      if (PinSelect == 0)
        break;
    }
  }
  
  MDR_Port_WriteRegs(GPIO_Port, &tmpRegs);    
}

// ======= Вспомогательные функции, для логгирования и отладки ===========

void MDR_Port_ReadRegs(MDR_PORT_Type *GPIO_Port, MDR_GPIO_CfgRegs *cfgRegs)
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

void MDR_Port_WriteRegs(MDR_PORT_Type *GPIO_Port, MDR_GPIO_CfgRegs *cfgRegs)
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
// VarRegs  - часто изменяемые настройки (Variable)
// PermRegs - групповые настройки (Permanent - редко изменяемые настройки)

typedef struct {
  uint32_t RXTX;
  uint32_t OE;
  uint32_t FUNC;
  uint32_t PULL;
} MDR_Pin_VarRegs;


// Variable настройки в структуру
__STATIC_INLINE void ToVarRegs(MDR_Pin_IO InOut, MDR_PIN_FUNC Func, MDR_Pin_VarRegs *VarRegs)
{
  VarRegs->RXTX = 0;
  VarRegs->FUNC = Func;
  
  VarRegs->OE = (InOut == MDR_Pin_Out);
  switch (InOut) {  
    case MDR_Pin_In_PU: {VarRegs->PULL = VAL2FLD(1, MDR_GPIO_PULL_UP__Pin);   break;}
    case MDR_Pin_In_PD: {VarRegs->PULL = VAL2FLD(1, MDR_GPIO_PULL_Down__Pin); break;}
    case MDR_Pin_Out:
    case MDR_Pin_In:
      VarRegs->PULL = 0;
  }
}

// Permanent настройки в структуру
void MDR_Port_InitDigPermRegs(MDR_PIN_PD OutDriver, MDR_PIN_PWR Power, MDR_OnOff InpSchmEn, MDR_OnOff InpFilterEn, MDR_PinDig_PermRegs *PinPermRegs)
{
  PinPermRegs->ANALOG  = 1;
  PinPermRegs->PD      = VAL2FLD(OutDriver, MDR_GPIO_PD_Driver__Pin) | VAL2FLD(InpSchmEn, MDR_GPIO_PD_Schmitt__Pin);
  PinPermRegs->PWR     = Power;
  PinPermRegs->GFEN    = InpFilterEn;  
}

// Обнуление масок CLR и SET перед накоплением в них настроек Variable и Permanent
void MDR_Port_MaskClear(MDR_Port_ApplyMask *ApplyMask)
{
  ApplyMask->MaskCLR.RXTX    = 0;
  ApplyMask->MaskCLR.OE      = 0;
  ApplyMask->MaskCLR.FUNC    = 0;
  ApplyMask->MaskCLR.ANALOG  = 0;
  ApplyMask->MaskCLR.PULL    = 0;
  ApplyMask->MaskCLR.PD      = 0;
  ApplyMask->MaskCLR.PWR     = 0;
  ApplyMask->MaskCLR.GFEN    = 0;
  
  ApplyMask->MaskSET.RXTX    = 0;
  ApplyMask->MaskSET.OE      = 0;
  ApplyMask->MaskSET.FUNC    = 0;
  ApplyMask->MaskSET.ANALOG  = 0;
  ApplyMask->MaskSET.PULL    = 0;
  ApplyMask->MaskSET.PD      = 0; 
  ApplyMask->MaskSET.PWR     = 0;
  ApplyMask->MaskSET.GFEN    = 0;
}

// Внесение настроек Variable и Permanent в маски CLR и SET для указанных маской PinSelect пинов
void MDR_Port_MaskAdd(uint32_t PinSelect, MDR_Pin_IO InOut, MDR_PIN_FUNC Func, const MDR_PinDig_PermRegs *PinPermRegs, MDR_Port_ApplyMask *ApplyMask)
{
  MDR_Pin_VarRegs pinVarRegs;

  uint32_t i, i2;
  uint32_t bitInd;
  uint32_t clrBit2, clrHiLo;
  
  ToVarRegs(InOut, Func, &pinVarRegs);
  
  for (i = 0; i < MDR_GPIO_Pin_Count; ++i)
  {
    bitInd = 1 << i;
    if (PinSelect & bitInd)
    {  
      i2 = i << 1;
      clrBit2 = CLR_FUNC << i2;
      clrHiLo = CLR_PD   << i;
            
      ApplyMask->MaskCLR.RXTX    |= bitInd;
      ApplyMask->MaskCLR.OE      |= bitInd;
      ApplyMask->MaskCLR.FUNC    |= clrBit2;
      ApplyMask->MaskCLR.ANALOG  |= bitInd;
      ApplyMask->MaskCLR.PULL    |= clrHiLo;
      ApplyMask->MaskCLR.PD      |= clrHiLo;      
      ApplyMask->MaskCLR.PWR     |= clrBit2;
      ApplyMask->MaskCLR.GFEN    |= bitInd;
      
      ApplyMask->MaskSET.RXTX    |= (pinVarRegs.RXTX      << i);
      ApplyMask->MaskSET.OE      |= (pinVarRegs.OE        << i);
      ApplyMask->MaskSET.FUNC    |= (pinVarRegs.FUNC      << i2);
      ApplyMask->MaskSET.ANALOG  |= (PinPermRegs->ANALOG  << i);
      ApplyMask->MaskSET.PULL    |= (pinVarRegs.PULL      << i);
      ApplyMask->MaskSET.PD      |= (PinPermRegs->PD      << i);  
      ApplyMask->MaskSET.PWR     |= (PinPermRegs->PWR     << i2);
      ApplyMask->MaskSET.GFEN    |= (PinPermRegs->GFEN    << i);

      PinSelect &= ~bitInd;
      if (PinSelect == 0)
        break;
    }
  } 
}

// Внесение настроек Variable и Permanent в маски CLR и SET для одного пина
void MDR_Port_MaskAddPin(uint32_t PinInd, MDR_Pin_IO InOut, MDR_PIN_FUNC Func, const MDR_PinDig_PermRegs *PinPermRegs, MDR_Port_ApplyMask *ApplyMask)
{
  uint32_t ind2;
  uint32_t clrBit, clrBit2, clrHiLo;
  MDR_Pin_VarRegs pinVarRegs;  
  
  ToVarRegs(InOut, Func, &pinVarRegs);
  
  ind2 = PinInd << 1;
  clrBit = 1 << PinInd;  
  clrBit2 = CLR_FUNC << ind2;
  clrHiLo = CLR_PD   << PinInd;
        
  ApplyMask->MaskCLR.RXTX    |= clrBit;
  ApplyMask->MaskCLR.OE      |= clrBit;
  ApplyMask->MaskCLR.FUNC    |= clrBit2;
  ApplyMask->MaskCLR.ANALOG  |= clrBit;
  ApplyMask->MaskCLR.PULL    |= clrHiLo;
  ApplyMask->MaskCLR.PD      |= clrHiLo;      
  ApplyMask->MaskCLR.PWR     |= clrBit2;
  ApplyMask->MaskCLR.GFEN    |= clrBit;
  
  ApplyMask->MaskSET.RXTX    |= (pinVarRegs.RXTX      << PinInd);
  ApplyMask->MaskSET.OE      |= (pinVarRegs.OE        << PinInd);
  ApplyMask->MaskSET.FUNC    |= (pinVarRegs.FUNC      << ind2);
  ApplyMask->MaskSET.ANALOG  |= (PinPermRegs->ANALOG  << PinInd);
  ApplyMask->MaskSET.PULL    |= (pinVarRegs.PULL      << PinInd);
  ApplyMask->MaskSET.PD      |= (PinPermRegs->PD      << PinInd);  
  ApplyMask->MaskSET.PWR     |= (PinPermRegs->PWR     << ind2);
  ApplyMask->MaskSET.GFEN    |= (PinPermRegs->GFEN    << PinInd);
}


//  Применение масок CLR и SET в порт
void MDR_Port_MaskApplyEx(MDR_PORT_Type *GPIO_Port, MDR_Port_ApplyMask *ApplyMask, MDR_GPIO_CfgRegs *readRegs)
{  
  MDR_GPIO_CfgRegs tmpRegs = *readRegs;
  
  tmpRegs.RXTX    = (tmpRegs.RXTX   & ~ApplyMask->MaskCLR.RXTX)   | ApplyMask->MaskSET.RXTX;
  tmpRegs.OE      = (tmpRegs.OE     & ~ApplyMask->MaskCLR.OE)     | ApplyMask->MaskSET.OE;
  tmpRegs.FUNC    = (tmpRegs.FUNC   & ~ApplyMask->MaskCLR.FUNC)   | ApplyMask->MaskSET.FUNC;
  tmpRegs.ANALOG  = (tmpRegs.ANALOG & ~ApplyMask->MaskCLR.ANALOG) | ApplyMask->MaskSET.ANALOG;
  tmpRegs.PULL    = (tmpRegs.PULL   & ~ApplyMask->MaskCLR.PULL)   | ApplyMask->MaskSET.PULL;
  tmpRegs.PD      = (tmpRegs.PD     & ~ApplyMask->MaskCLR.PD)     | ApplyMask->MaskSET.PD;
  tmpRegs.PWR     = (tmpRegs.PWR    & ~ApplyMask->MaskCLR.PWR)    | ApplyMask->MaskSET.PWR;
  tmpRegs.GFEN    = (tmpRegs.GFEN   & ~ApplyMask->MaskCLR.GFEN)   | ApplyMask->MaskSET.GFEN;
  
  MDR_Port_WriteRegs(GPIO_Port, &tmpRegs);
}


void MDR_Port_MaskApply(MDR_PORT_Type *GPIO_Port, MDR_Port_ApplyMask *ApplyMask)
{
  MDR_GPIO_CfgRegs tmpRegs;
  
  MDR_Port_ReadRegs(GPIO_Port, &tmpRegs);
  
  MDR_Port_MaskApplyEx(GPIO_Port, ApplyMask, &tmpRegs);
}

//  Применение настроек сразу в порт для указанных маской PinSelect пинов
void MDR_Port_InitDig(MDR_PORT_Type *GPIO_Port, uint32_t PinSelect, MDR_Pin_IO InOut, MDR_PIN_FUNC Func, const MDR_PinDig_PermRegs *PinPermRegs) 
{
  uint32_t i, i2;
  uint32_t bitInd;
  uint32_t clrBit, clrBit2, clrHiLo;
  MDR_Pin_VarRegs pinVarRegs;
  MDR_GPIO_CfgRegs tmpRegs;
  
  ToVarRegs(InOut, Func, &pinVarRegs);
  
  MDR_Port_ReadRegs(GPIO_Port, &tmpRegs);

  for (i = 0; i < MDR_GPIO_Pin_Count; ++i)
  {
    bitInd = 1 << i;
    if (PinSelect & bitInd)
    { 
      i2 = i << 1;
      
      clrBit  = ~bitInd;
      clrBit2 = ~(CLR_FUNC << i2);
      clrHiLo = ~(CLR_PD   << i);
      
      tmpRegs.RXTX    = (tmpRegs.RXTX   & clrBit ) | (pinVarRegs.RXTX      << i);
      tmpRegs.OE      = (tmpRegs.OE     & clrBit ) | (pinVarRegs.OE        << i);
      tmpRegs.FUNC    = (tmpRegs.FUNC   & clrBit2) | (pinVarRegs.FUNC      << i2);
      tmpRegs.ANALOG  = (tmpRegs.ANALOG & clrBit ) | (PinPermRegs->ANALOG  << i);
      tmpRegs.PULL    = (tmpRegs.PULL   & clrHiLo) | (pinVarRegs.PULL      << i);
      tmpRegs.PD      = (tmpRegs.PD     & clrHiLo) | (PinPermRegs->PD      << i);     
      tmpRegs.PWR     = (tmpRegs.PWR    & clrBit2) | (PinPermRegs->PWR     << i2);
      tmpRegs.GFEN    = (tmpRegs.GFEN   & clrBit ) | (PinPermRegs->GFEN    << i);
      
      PinSelect &= clrBit;
      if (PinSelect == 0)
        break;
    }
  }
  
  MDR_Port_WriteRegs(GPIO_Port, &tmpRegs);
}

//  Применение настроек в порт для одного пина
void MDR_Port_InitDigPin(MDR_PORT_Type *GPIO_Port, uint32_t PinInd, MDR_Pin_IO InOut, MDR_PIN_FUNC Func, const MDR_PinDig_PermRegs *PinPermRegs)
{
  uint32_t ind2;
  uint32_t clrBit, clrBit2, clrHiLo;  
  MDR_GPIO_CfgRegs tmpRegs;
  MDR_Pin_VarRegs pinVarRegs;  
  
  ToVarRegs(InOut, Func, &pinVarRegs);
  
  MDR_Port_ReadRegs(GPIO_Port, &tmpRegs);

  ind2 = PinInd << 1;
  
  clrBit  = ~(1 << PinInd);
  clrBit2 = ~(CLR_FUNC << ind2);
  clrHiLo = ~(CLR_PD   << PinInd);
  
  tmpRegs.RXTX    = (tmpRegs.RXTX   & clrBit ) | (pinVarRegs.RXTX      << PinInd);
  tmpRegs.OE      = (tmpRegs.OE     & clrBit ) | (pinVarRegs.OE        << PinInd);
  tmpRegs.FUNC    = (tmpRegs.FUNC   & clrBit2) | (pinVarRegs.FUNC      << ind2);
  tmpRegs.ANALOG  = (tmpRegs.ANALOG & clrBit ) | (PinPermRegs->ANALOG  << PinInd);
  tmpRegs.PULL    = (tmpRegs.PULL   & clrHiLo) | (pinVarRegs.PULL      << PinInd);
  tmpRegs.PD      = (tmpRegs.PD     & clrHiLo) | (PinPermRegs->PD      << PinInd);     
  tmpRegs.PWR     = (tmpRegs.PWR    & clrBit2) | (PinPermRegs->PWR     << ind2);
  tmpRegs.GFEN    = (tmpRegs.GFEN   & clrBit ) | (PinPermRegs->GFEN    << PinInd);
        
  MDR_Port_WriteRegs(GPIO_Port, &tmpRegs);
}

//  Конвертация в MDR_GPIO_CfgRegs для вызова первого варианта
void MDR_Port_ToCfgRegs(MDR_Pin_IO InOut, MDR_PIN_FUNC Func, const MDR_PinDig_PermRegs *PinPermRegs, MDR_GPIO_CfgRegs *cfgRegs)
{
  MDR_Pin_VarRegs pinVarRegs;  
  
  ToVarRegs(InOut, Func, &pinVarRegs);

  cfgRegs->RXTX    = pinVarRegs.RXTX;
  cfgRegs->OE      = pinVarRegs.OE;
  cfgRegs->FUNC    = pinVarRegs.FUNC;
  cfgRegs->ANALOG  = PinPermRegs->ANALOG;
  cfgRegs->PULL    = pinVarRegs.PULL;
  cfgRegs->PD      = PinPermRegs->PD;
  cfgRegs->PWR     = PinPermRegs->PWR;
  cfgRegs->GFEN    = PinPermRegs->GFEN;
}

#include <MDR_CRC.h>

void MDR_CRC_Init(MDR_CRC_CfgReg cfg, uint16_t polinomBitSel)
{
  //	Clock Enable
  REG32(MDR_CRC_CLK_EN_ADDR) |= MDR_CRC_CLK_EN_MSK;  
  
  //  Apply Cfg
  MDR_CRC->CTRL    = cfg.Cfg;
  MDR_CRC->CRC_POL = polinomBitSel | 0x10001UL;
  MDR_CRC->STAT    = MDR_CRC_STAT_FIFO_Over_Msk;  
}

void MDR_CRC_ReInit(MDR_CRC_CfgReg cfg, uint16_t polinomBitSel)
{
//  Apply Cfg
  MDR_CRC->CTRL    = cfg.Cfg;
  MDR_CRC->CRC_POL = polinomBitSel | 0x10001UL;
  MDR_CRC->STAT    = MDR_CRC_STAT_FIFO_Over_Msk;  
}

void MDR_CRC_DeInit(void)
{
  //  Cfg Off
  MDR_CRC->CTRL    = 0;
  MDR_CRC->CRC_POL = 0;
  MDR_CRC->STAT    = MDR_CRC_STAT_FIFO_Over_Msk;  
  
  //  Clock Off
  REG32(MDR_CRC_CLK_EN_ADDR) &= ~MDR_CRC_CLK_EN_MSK;  
}

uint16_t MDR_CRC_Calc(uint16_t startValue, uint32_t count,  uint8_t  *data)
{
  uint32_t i;
  MDR_CRC->CTRL = MaskClrSet(MDR_CRC->CTRL, MDR_CRC_CNTRL_CLR_SIZES, MDR_CRC_CNTRL_SIZE_8BIT);
  MDR_CRC->CRC_OUT = startValue;
  
  for (i = 0; i < count; ++i)
  {
    while (MDR_CRC_GetFIFO_Full()) {};
    MDR_CRC->DATAI = data[i];    
  }
  
  while (!MDR_CRC_GetCompleted()) {};  
  return  (uint16_t)MDR_CRC->CRC_OUT; 
}

//uint16_t MDR_CRC_CalcCRC_D16(uint16_t startValue, uint32_t count, uint16_t *data)
//{
//  uint32_t i;
//  MDR_CRC->CTRL = MaskClrSet(MDR_CRC->CTRL, MDR_CRC_CNTRL_CLR_SIZES, MDR_CRC_CNTRL_SIZE_16BIT);
//  MDR_CRC->CRC_OUT = startValue;
//  
//  for (i = 0; i < count; ++i)
//  {
//    while (MDR_CRC_GetFIFO_Empty()) {};
//    MDR_CRC->DATAI = data[i];    
//  }
//  
//  while (!MDR_CRC_GetCompleted()) {};  
//  return  (uint16_t)MDR_CRC->CRC_OUT; 
//}

//uint16_t MDR_CRC_CalcCRC_D32(uint16_t startValue, uint32_t count, uint32_t *data)
//{
//  uint32_t i;
//  MDR_CRC->CTRL = MaskClrSet(MDR_CRC->CTRL, MDR_CRC_CNTRL_CLR_SIZES, MDR_CRC_CNTRL_SIZE_32BIT);
//  MDR_CRC->CRC_OUT = startValue;
//  
//  for (i = 0; i < count; ++i)
//  {
//    while (MDR_CRC_GetFIFO_Empty()) {};
//    MDR_CRC->DATAI = data[i];    
//  }
//  
//  while (!MDR_CRC_GetCompleted()) {};  
//  return  (uint16_t)MDR_CRC->CRC_OUT;
//}


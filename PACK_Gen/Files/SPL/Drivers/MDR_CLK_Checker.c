#include <MDR_CLK_Checker.h>


MDR_RST_CLK_CHECKER* const MDR_CLKCHK_REGS[MDR_CLKCHK_COUNT] = {
  &MDR_CLOCK->CPU_CHKR, 
  &MDR_CLOCK->LSI_CHKR, 
  &MDR_CLOCK->LSE_CHKR, 
  &MDR_CLOCK->HSE0_CHKR,
  &MDR_CLOCK->HSE1_CHKR,
  &MDR_CLOCK->PLL0_CHKR,
  &MDR_CLOCK->PLL1_CHKR,
  &MDR_CLOCK->PLL2_CHKR,
#ifdef MDR_HAS_PLL3   
  &MDR_CLOCK->PLL2_CHKR,
#endif
};

volatile MDR_CLKCHK_Status* const MDR_CLKCHK_STATUS[MDR_CLKCHK_COUNT] = {
  (volatile MDR_CLKCHK_Status*)&MDR_CLOCK->CPU_STAT, 
  (volatile MDR_CLKCHK_Status*)&MDR_CLOCK->LSI_STAT, 
  (volatile MDR_CLKCHK_Status*)&MDR_CLOCK->LSE_STAT, 
  (volatile MDR_CLKCHK_Status*)&MDR_CLOCK->HSE0_STAT,
  (volatile MDR_CLKCHK_Status*)&MDR_CLOCK->HSE1_STAT,
  (volatile MDR_CLKCHK_Status*)&MDR_CLOCK->PLL0_STAT,
  (volatile MDR_CLKCHK_Status*)&MDR_CLOCK->PLL1_STAT,
  (volatile MDR_CLKCHK_Status*)&MDR_CLOCK->PLL2_STAT,
#ifdef MDR_HAS_PLL3 
  (volatile MDR_CLKCHK_Status*)&MDR_CLOCK->PLL3_STAT,
#endif
};

volatile MDR_CLKCHK_Ctrl* const MDR_CLKCHK_CTRL[MDR_CLKCHK_COUNT] = {
  (volatile MDR_CLKCHK_Ctrl*)&MDR_CLOCK->CPU_CLK, 
  (volatile MDR_CLKCHK_Ctrl*)&MDR_CLOCK->LSI_CLK, 
  (volatile MDR_CLKCHK_Ctrl*)&MDR_CLOCK->LSE_CLK, 
  (volatile MDR_CLKCHK_Ctrl*)&MDR_CLOCK->HSE0_CLK,
  (volatile MDR_CLKCHK_Ctrl*)&MDR_CLOCK->HSE1_CLK,
  (volatile MDR_CLKCHK_Ctrl*)&MDR_CLOCK->PLL0_CLK,
  (volatile MDR_CLKCHK_Ctrl*)&MDR_CLOCK->PLL1_CLK,
  (volatile MDR_CLKCHK_Ctrl*)&MDR_CLOCK->PLL2_CLK,
#ifdef MDR_HAS_PLL3 
  (volatile MDR_CLKCHK_Ctrl*)&MDR_CLOCK->PLL3_CLK,
#endif
};


void MDR_CLKCHK_Init_byRegs(MDR_CLKCHK_Target target, const MDR_CLKCHK_Regs *cfgRegs)
{
  MDR_RST_CLK_CHECKER* chkrHrd = MDR_CLKCHK_REGS[target];
  
  chkrHrd->CLK_CHK0 = cfgRegs->CLK_CHK0;
  chkrHrd->CLK_CHK1 = cfgRegs->CLK_CHK1;
  chkrHrd->CLK_CHK2 = cfgRegs->CLK_CHK2;
  
  uint32_t regCTRL = MDR_MaskClrSet((*MDR_CLKCHK_CTRL[target]).CTRL, MDR_CLK_CHK_SEL_ALL, cfgRegs->CTRL);
  //  Сбросить теневые регистры MAX_SHIFT раньше разрешения аварийных переключений на HSI!
  (*MDR_CLKCHK_CTRL[target]).CTRL = regCTRL & (~MDR_CLK_CHK_SEL_EN_EVENTS);  
  (*MDR_CLKCHK_CTRL[target]).CTRL = regCTRL;
}


void MDR_CLKCHK_Init(MDR_CLKCHK_Target target, const MDR_CLKCHK_Cfg *cfg)
{
  MDR_CLKCHK_Regs cfgRegs;
  
  cfgRegs.CLK_CHK0 =  VAL2FLD(cfg->slowHSI_PrescREG2, MDR_CLK_CHK0_PRES_HSI_SLOW) | VAL2FLD(cfg->fastHSI_PrescREG0, MDR_CLK_CHK0_PRES_HSI_FAST);
  cfgRegs.CLK_CHK1 =  VAL2FLD(cfg->slowCLK_PrescREG1, MDR_CLK_CHK1_PRES_CLK_SLOW) | VAL2FLD(cfg->fastCLK_PrescREG3, MDR_CLK_CHK1_PRES_CLK_FAST);
  cfgRegs.CLK_CHK2 =  VAL2FLD(cfg->level_SlowEvent0, MDR_RST_CHK2_BASE_SLOW_EVENT0) | VAL2FLD(cfg->level_SlowEvent1, MDR_RST_CHK2_BASE_SLOW_EVENT1)
                    | VAL2FLD(cfg->level_FastEvent2, MDR_RST_CHK2_BASE_FAST_EVENT2) | VAL2FLD(cfg->level_FastEvent3, MDR_RST_CHK2_BASE_FAST_EVENT3);
  
  cfgRegs.CTRL = MDR_CLK_CHK_CLR_ALL_EVENTS | MDR_CLK_CHK_EN_Msk | VAL2FLD_Pos(cfg->enaGoHSI_byEvents.eventSel, MDR_CLK_CHK_EN_SLOW_EVENT0_Pos);

  MDR_CLKCHK_Init_byRegs(target, &cfgRegs);
}


void MDR_CLKCHK_Deinit(MDR_CLKCHK_Target target)
{
  (*MDR_CLKCHK_CTRL[target]).CTRL &= ~MDR_CLK_CHK_EN_Msk;
}

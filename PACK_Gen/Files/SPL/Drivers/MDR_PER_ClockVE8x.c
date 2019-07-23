#include <MDR_PER_Clock.h>

//   extern from system_MDR1986VE8.c
extern uint32_t MDR_MaxClock;
uint32_t MDR_GetClockHz_InputPLL(uint32_t selInpPll);
uint32_t MDR_GetClockHz_MaxClock(bool doUpdate);

//  Получение частот UART_Clock, SSP_CLock  и т.д.
uint32_t  MDR_GetFreqHz_PerAsync(MDR_PERCLK_ASYNC_REG asyncRegValue, bool doUpdate)
{ 
  uint32_t freqHz = MDR_GetClockHz_AsyncSrc(FLD2VAL(asyncRegValue.Value, MDR_RST_ASYNC_CLK_SELECT), doUpdate);
  uint32_t freqDiv = FLD2VAL(asyncRegValue.Value, MDR_RST_ASYNC_CLK_DIV);
  
  freqHz = freqHz / (freqDiv + 1);
  return freqHz;
}

uint32_t  MDR_GetFreqHz_PerSync(MDR_PERCLK_SYNC_REG  syncRegValue, bool doUpdate)
{
  if (doUpdate)
    SystemCoreClockUpdate();
  
  uint32_t freqHz = SystemCoreClock;
  uint32_t freqDiv = FLD2VAL(syncRegValue.Value, MDR_RST_ASYNC_CLK_DIV);
  
  freqHz = freqHz / (freqDiv + 1);
  return freqHz;
}



#define FREQ_FAULT_HZ       HSI_FREQ_HZ

#define CLK_SEL_COUNT_PLL   MDR_PLL_IN_HSE1div2 + 1
#define CLK_SEL_COUNT       MDR_RST_ASYNC_IN_PLL0

static const uint32_t _AsyncFreqsHz[CLK_SEL_COUNT] = {
  HSI_FREQ_HZ,        //  MDR_RST_ASYNC_IN_HSI      = 0,      MDR_PLL_IN_HSI       = 0,
  HSE0_FREQ_HZ,       //  MDR_RST_ASYNC_IN_HSE0     = 1,      MDR_PLL_IN_HSI/2     = 1,
  HSE1_FREQ_HZ,       //  MDR_RST_ASYNC_IN_HSE1     = 2,      MDR_PLL_IN_HSE0      = 2,
  LSI_FREQ_HZ,        //  MDR_RST_ASYNC_IN_LSI      = 3,      MDR_PLL_IN_HSE0/2    = 3,
  LSE_FREQ_HZ         //  MDR_RST_ASYNC_IN_LSE      = 4,      MDR_PLL_IN_HSE1      = 4,
};                    //  MDR_RST_ASYNC_IN_PLL0     = 5,      MDR_PLL_IN_HSE1/2    = 5,
                      //  MDR_RST_ASYNC_IN_PLL1     = 6,      } MDR_PLL_IN_SEL;
                      //  MDR_RST_ASYNC_IN_PLL2     = 7,
                      //  MDR_RST_ASYNC_IN_MAX_CLK  = 13
                      //  } MDR_RST_ASYNC_IN_SEL;


uint32_t MDR_GetClockHz_AsyncSrc(uint32_t freqSel, bool doUpdate)
{
  uint32_t regCLK;
  uint32_t pll_source, pll_N, pll_Q, pll_DIV;
  uint32_t sel_pll;
  uint32_t freqHz = FREQ_FAULT_HZ;

  if (freqSel == MDR_RST_ASYNC_IN_MAX_CLK)
    freqHz = MDR_GetClockHz_MaxClock(doUpdate);
  else if (freqSel <= MDR_RST_ASYNC_IN_PLL0)
    freqHz = _AsyncFreqsHz[freqSel];
  else if (freqSel <= MDR_RST_ASYNC_IN_PLL2)
  {  
    switch (freqHz)
    {
      case MAXCLK_PLL1: regCLK = MDR_CLOCK->PLL1_CLK; break;        
      case MAXCLK_PLL2: regCLK = MDR_CLOCK->PLL2_CLK; break;
//      case MAXCLK_PLL3: regCLK = MDR_CLOCK->PLL3_CLK; break;
      default:          regCLK = MDR_CLOCK->PLL0_CLK; break;
    }  
    sel_pll = _FLD2VAL(MDR_RST_PLL_SELECT, regCLK);
    if (sel_pll < CLK_SEL_COUNT_PLL)
    {
      pll_source = MDR_GetClockHz_InputPLL(sel_pll);
      
      pll_Q   = FLD2VAL(regCLK, MDR_RST_PLL_PLL_Q);
      pll_DIV = FLD2VAL(regCLK, MDR_RST_PLL_DV);
      pll_N   = FLD2VAL(regCLK, MDR_RST_PLL_PLL_N);
      if (pll_N == 0)
        pll_N = 2;          
     
      freqHz = ((pll_source * pll_N / (pll_Q + 1)) / (pll_DIV + 1));	    
    }
  } 
  
  return freqHz;
}



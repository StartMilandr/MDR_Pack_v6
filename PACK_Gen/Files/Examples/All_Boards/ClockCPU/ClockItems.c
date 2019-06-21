#include "ClockItems.h"


#if defined (USE_MDR1986VE8) || defined (USE_MDR1923VK014)

//  ======================  MDR1986VE8 и MDR1923VK014 ===================
//  ================= Настройки источников частот =======================
//  =====================================================================


//  ================= Настройки источников частот =======================
  static MDR_CPU_CfgLSI cfgLSI   = MDR_CPU_CFG_LSI_DEF;
  static MDR_CPU_CfgLSE cfgLSE   = MDR_CPU_CFG_LSE_RES_DEF;

  static MDR_CPU_CfgHSI cfgHSI   = MDR_CPU_CFG_HSI_DEF;
  static MDR_CPU_CfgHSI cfgHSI_2 = MDR_CPU_CFG_HSI_DIV2_DEF;

  static MDR_CPU_CfgHSE cfgHSE   = MDR_CPU_CFG_HSE_RES_DEF;
  static MDR_CPU_CfgHSE cfgHSE_2 = MDR_CPU_CFG_HSE_DIV2_RES_DEF;
                      

  static MDR_CPU_PLL_CfgHSI cfgPLL_HSI_40M = {.freqTrim     = HSI_FREQ_TRIM,
                                       .selDiv2             = false,
                                       .timeoutCycles_HSI   = HSI_TIMEOUT,
                                       .cfgPLL              = MDRB_PLL_8MHz_TO_40MHz,
                                       .timeoutCycles_PLL   = PLL_TIMEOUT,
                                       .divMaxToCpu_0       = 0,
                                       .freqSupp            = MDRB_CPU_FREQ_SUPP_40MHz};  

  static MDR_CPU_PLL_CfgHSI cfgPLL_HSI_36M = {.freqTrim     = HSI_FREQ_TRIM,
                                       .selDiv2             = false,
                                       .timeoutCycles_HSI   = HSI_TIMEOUT,
                                       .cfgPLL              = MDRB_PLL_8MHz_TO_36MHz,
                                       .timeoutCycles_PLL   = PLL_TIMEOUT,
                                       .divMaxToCpu_0       = 0,
                                       .freqSupp            = MDRB_CPU_FREQ_SUPP_40MHz};

  static MDR_CPU_PLL_CfgHSI cfgPLL_HSI_20M = {.freqTrim     = HSI_FREQ_TRIM,
                                       .selDiv2             = false,
                                       .timeoutCycles_HSI   = HSI_TIMEOUT,
                                       .cfgPLL              = MDRB_PLL_8MHz_TO_40MHz,
                                       .timeoutCycles_PLL   = PLL_TIMEOUT,
                                       .divMaxToCpu_0       = 1,
                                       .freqSupp            = MDRB_CPU_FREQ_SUPP_20MHz};

  static MDR_CPU_PLL_CfgHSE cfgPLL_HSE_40M = {.freqSource   = MDR_CLK_Resonator,
                                       .selDiv2             = false,
                                       .timeoutCycles_HSE   = HSI_TIMEOUT,
                                       .cfgPLL              = MDRB_PLL_8MHz_TO_40MHz,
                                       .timeoutCycles_PLL   = PLL_TIMEOUT,
                                       .divMaxToCpu_0       = 0,
                                       .freqSupp            = MDRB_CPU_FREQ_SUPP_40MHz};  

  static MDR_CPU_PLL_CfgHSE cfgPLL_HSE_36M = {.freqSource   = MDR_CLK_Resonator,
                                       .selDiv2             = false,
                                       .timeoutCycles_HSE   = HSI_TIMEOUT,
                                       .cfgPLL              = MDRB_PLL_8MHz_TO_36MHz,
                                       .timeoutCycles_PLL   = PLL_TIMEOUT,
                                       .divMaxToCpu_0       = 0,
                                       .freqSupp            = MDRB_CPU_FREQ_SUPP_40MHz};

  static MDR_CPU_PLL_CfgHSE cfgPLL_HSE_20M = {.freqSource   = MDR_CLK_Resonator,
                                       .selDiv2             = false,
                                       .timeoutCycles_HSE   = HSI_TIMEOUT,
                                       .cfgPLL              = MDRB_PLL_8MHz_TO_40MHz,
                                       .timeoutCycles_PLL   = PLL_TIMEOUT,
                                       .divMaxToCpu_0       = 1,
                                       .freqSupp            = MDRB_CPU_FREQ_SUPP_20MHz};


  //  =================  Таблица вариантов тактирования =======================   
                           
  CLK_Item ClockConfigs[_ClockItemsCount] = {
  /* iLSI */        {.setFuncID = ID_SetLSI,     .cfgStruct = &cfgLSI,   .indHSE = 0, .indPLL = 0, .freqHz = LSI_FREQ_HZ, .name = "LSI"},
  /* iLSE */        {.setFuncID = ID_SetLSE,     .cfgStruct = &cfgLSE,   .indHSE = 0, .indPLL = 0, .freqHz = LSE_FREQ_HZ, .name = "LSE"},
                    //  HSI
  /* iHSI   */      {.setFuncID = ID_SetHSI,     .cfgStruct = &cfgHSI,   .indHSE = 0, .indPLL = 0, .freqHz = HSI_FREQ_HZ, .name = "HSI"},
  /* iHSId2 */      {.setFuncID = ID_SetHSI,     .cfgStruct = &cfgHSI_2, .indHSE = 0, .indPLL = 0, .freqHz = (HSI_FREQ_HZ >> 1), .name = "HSI/2"},
                    //  HSE0
  /* iHSE0   */     {.setFuncID = ID_SetHSE,     .cfgStruct = &cfgHSE,   .indHSE = 0, .indPLL = 0, .freqHz = HSE_FREQ_HZ, .name = "HSE0"},
  /* iHSE0d2 */     {.setFuncID = ID_SetHSE,     .cfgStruct = &cfgHSE_2, .indHSE = 0, .indPLL = 0, .freqHz = (HSE_FREQ_HZ >> 1), .name = "HSE0/2"},
                    //  HSE1
  /* iHSE1   */     {.setFuncID = ID_SetHSE,     .cfgStruct = &cfgHSE,   .indHSE = 1, .indPLL = 0, .freqHz = HSE_FREQ_HZ, .name = "HSE1"},
  /* iHSE1d2 */     {.setFuncID = ID_SetHSE,     .cfgStruct = &cfgHSE_2, .indHSE = 1, .indPLL = 0, .freqHz = (HSE_FREQ_HZ >> 1), .name = "HSE1/2"},
                    //  PLLx_HSI
  /* iHSI_P0_40*/   {.setFuncID = ID_SetPLL_HSI, .cfgStruct = &cfgPLL_HSI_40M, .indHSE = 0, .indPLL = 0, 40000000, .name = "P0HSI_40"},
  /* iHSI_P1_36*/   {.setFuncID = ID_SetPLL_HSI, .cfgStruct = &cfgPLL_HSI_36M, .indHSE = 0, .indPLL = 1, 18000000, .name = "P1HSI_36"},  
  /* iHSI_P2_20*/   {.setFuncID = ID_SetPLL_HSI, .cfgStruct = &cfgPLL_HSI_20M, .indHSE = 0, .indPLL = 2, 20000000, .name = "P2HSI_20"},
                    //  PLLx_HSE0
  /* iHSE0_P0_40 */ {.setFuncID = ID_SetPLL_HSE, .cfgStruct = &cfgPLL_HSE_40M, .indHSE = 0, .indPLL = 0, 40000000, .name = "P0HSE0_40"},
  /* iHSE0_P1_36 */ {.setFuncID = ID_SetPLL_HSE, .cfgStruct = &cfgPLL_HSE_36M, .indHSE = 0, .indPLL = 1, 18000000, .name = "P1HSE0_36"},  
  /* iHSE0_P2_20 */ {.setFuncID = ID_SetPLL_HSE, .cfgStruct = &cfgPLL_HSE_20M, .indHSE = 0, .indPLL = 2, 20000000, .name = "P2HSE0_20"},      
                    //  PLLx_HSE1
  /* iHSE1_P0_40 */ {.setFuncID = ID_SetPLL_HSE, .cfgStruct = &cfgPLL_HSE_40M, .indHSE = 1, .indPLL = 0, 40000000, .name = "P0HSE1_40"},
  /* iHSE1_P1_36 */ {.setFuncID = ID_SetPLL_HSE, .cfgStruct = &cfgPLL_HSE_36M, .indHSE = 1, .indPLL = 1, 18000000, .name = "P1HSE1_36"},  
  /* iHSE1_P2_20 */ {.setFuncID = ID_SetPLL_HSE, .cfgStruct = &cfgPLL_HSE_20M, .indHSE = 1, .indPLL = 2, 20000000, .name = "P2HSE1_20"},  
  };


  //  =================  Функция переключения на вариант тактирования =======================
  MDR_CPU_SetClockResult  ChangeClockCPU(const CLK_Item *item)
  {
    bool fromLowerFreq = item->freqHz > MDR_CPU_GetFreqHz(false);
    
    switch (item->setFuncID) {
      case ID_SetLSI:        
        return MDR_CPU_SetClock_LSI((MDR_CPU_CfgLSI *)(item->cfgStruct), LSI_TIMEOUT);
      
      case ID_SetLSE:  
        return MDR_CPU_SetClock_LSE((MDR_CPU_CfgLSE *)(item->cfgStruct), LSE_TIMEOUT);
      
      case ID_SetHSI:
        return MDR_CPU_SetClock_HSI((MDR_CPU_CfgHSI *)(item->cfgStruct), HSI_TIMEOUT, fromLowerFreq);
        
      case ID_SetHSE: 
      {
        if (item->indHSE == 0)
          return MDR_CPU_SetClock_HSE0((MDR_CPU_CfgHSE *)(item->cfgStruct), HSE_TIMEOUT, fromLowerFreq);
        else 
          return MDR_CPU_SetClock_HSE1((MDR_CPU_CfgHSE *)(item->cfgStruct), HSE_TIMEOUT, fromLowerFreq);
      }
      
      case ID_SetPLL_HSI:
      {  
        if (item->indPLL == 0)
          return MDR_CPU_SetClock_HSI_PLL0((MDR_CPU_PLL_CfgHSI *)(item->cfgStruct), fromLowerFreq);
        else if (item->indPLL == 1)
          return MDR_CPU_SetClock_HSI_PLL1((MDR_CPU_PLL_CfgHSI *)(item->cfgStruct), fromLowerFreq);
        else
          return MDR_CPU_SetClock_HSI_PLL2((MDR_CPU_PLL_CfgHSI *)(item->cfgStruct), fromLowerFreq);
      }

      case ID_SetPLL_HSE:
      {
        if (item->indHSE == 0)
        { // HSE0_PLL
          if (item->indPLL == 0)
            return MDR_CPU_SetClock_HSE0_PLL0((MDR_CPU_PLL_CfgHSE *)(item->cfgStruct), fromLowerFreq);
          else if (item->indPLL == 1)
            return MDR_CPU_SetClock_HSE0_PLL1((MDR_CPU_PLL_CfgHSE *)(item->cfgStruct), fromLowerFreq);
          else
            return MDR_CPU_SetClock_HSE0_PLL2((MDR_CPU_PLL_CfgHSE *)(item->cfgStruct), fromLowerFreq);
        } 
        else 
        { // HSE1_PLL
          if (item->indPLL == 0)
            return MDR_CPU_SetClock_HSE1_PLL0((MDR_CPU_PLL_CfgHSE *)(item->cfgStruct), fromLowerFreq);
          else if (item->indPLL == 1)
            return MDR_CPU_SetClock_HSE1_PLL1((MDR_CPU_PLL_CfgHSE *)(item->cfgStruct), fromLowerFreq);
          else
            return MDR_CPU_SetClock_HSE1_PLL2((MDR_CPU_PLL_CfgHSE *)(item->cfgStruct), fromLowerFreq);
        }    
      } //   ID_SetPLL_HSE
    } // switch
      
    
    return MDR_SET_CLOCK_ERR__Undef;
  }
  
#elif defined (USE_ESila)
//  ===========================     ESila ===============================
//  ================= Настройки источников частот =======================
//  =====================================================================
  
  static MDR_CPU_CfgLSI cfgLSI   = MDR_CPU_CFG_LSI_DEF;
  static MDR_CPU_CfgLSE cfgLSE   = MDR_CPU_CFG_LSE_RES_DEF;

  static MDR_CPU_CfgHSI cfgHSI   = MDR_CPU_CFG_HSI_DEF;
  static MDR_CPU_CfgHSI cfgHSI_2 = MDR_CPU_CFG_HSI_DIV2_DEF;

  static MDR_CPU_CfgHSE cfgHSE   = MDR_CPU_CFG_HSE_RES_DEF;
  static MDR_CPU_CfgHSE cfgHSE_2 = MDR_CPU_CFG_HSE_DIV2_RES_DEF;
                      

  static MDR_CPU_PLL_CfgHSI cfgPLL_HSI_120M = {.freqTrim     = HSI_FREQ_TRIM,
                                       .selDiv2             = false,
                                       .timeoutCycles_HSI   = HSI_TIMEOUT,
                                       .cfgPLL              = MDRB_PLL_8MHz_TO_120MHz,
                                       .timeoutCycles_PLL   = PLL_TIMEOUT,
                                       .divMaxToCpu_0       = 0,
                                       .freqSupp            = MDRB_CPU_FREQ_SUPP_120MHz};

  static MDR_CPU_PLL_CfgHSI cfgPLL_HSI_100M = {.freqTrim     = HSI_FREQ_TRIM,
                                       .selDiv2             = false,
                                       .timeoutCycles_HSI   = HSI_TIMEOUT,
                                       .cfgPLL              = MDRB_PLL_8MHz_TO_100MHz,
                                       .timeoutCycles_PLL   = PLL_TIMEOUT,
                                       .divMaxToCpu_0       = 0,
                                       .freqSupp            = MDRB_CPU_FREQ_SUPP_100MHz};  

                                       
  static MDR_CPU_PLL_CfgHSI cfgPLL_HSI_80M = {.freqTrim     = HSI_FREQ_TRIM,
                                       .selDiv2             = false,
                                       .timeoutCycles_HSI   = HSI_TIMEOUT,
                                       .cfgPLL              = MDRB_PLL_8MHz_TO_80MHz,
                                       .timeoutCycles_PLL   = PLL_TIMEOUT,
                                       .divMaxToCpu_0       = 1,
                                       .freqSupp            = MDRB_CPU_FREQ_SUPP_80MHz};
  
  static MDR_CPU_PLL_CfgHSI cfgPLL_HSI_40M = {.freqTrim     = HSI_FREQ_TRIM,
                                       .selDiv2             = false,
                                       .timeoutCycles_HSI   = HSI_TIMEOUT,
                                       .cfgPLL              = MDRB_PLL_8MHz_TO_40MHz,
                                       .timeoutCycles_PLL   = PLL_TIMEOUT,
                                       .divMaxToCpu_0       = 0,
                                       .freqSupp            = MDRB_CPU_FREQ_SUPP_40MHz};  
                                       
                                       
  static MDR_CPU_PLL_CfgHSE cfgPLL_HSE_120M = {.freqSource   = MDR_CLK_Resonator,
                                       .selDiv2             = false,
                                       .timeoutCycles_HSE   = HSI_TIMEOUT,
                                       .cfgPLL              = MDRB_PLL_8MHz_TO_120MHz,
                                       .timeoutCycles_PLL   = PLL_TIMEOUT,
                                       .divMaxToCpu_0       = 0,
                                       .freqSupp            = MDRB_CPU_FREQ_SUPP_120MHz};  

  static MDR_CPU_PLL_CfgHSE cfgPLL_HSE_100M = {.freqSource   = MDR_CLK_Resonator,
                                       .selDiv2             = false,
                                       .timeoutCycles_HSE   = HSI_TIMEOUT,
                                       .cfgPLL              = MDRB_PLL_8MHz_TO_100MHz,
                                       .timeoutCycles_PLL   = PLL_TIMEOUT,
                                       .divMaxToCpu_0       = 0,
                                       .freqSupp            = MDRB_CPU_FREQ_SUPP_100MHz};

  static MDR_CPU_PLL_CfgHSE cfgPLL_HSE_80M = {.freqSource   = MDR_CLK_Resonator,
                                       .selDiv2             = false,
                                       .timeoutCycles_HSE   = HSI_TIMEOUT,
                                       .cfgPLL              = MDRB_PLL_8MHz_TO_80MHz,
                                       .timeoutCycles_PLL   = PLL_TIMEOUT,
                                       .divMaxToCpu_0       = 1,
                                       .freqSupp            = MDRB_CPU_FREQ_SUPP_80MHz};

  static MDR_CPU_PLL_CfgHSE cfgPLL_HSE_60M = {.freqSource   = MDR_CLK_Resonator,
                                       .selDiv2             = false,
                                       .timeoutCycles_HSE   = HSI_TIMEOUT,
                                       .cfgPLL              = MDRB_PLL_8MHz_TO_60MHz,
                                       .timeoutCycles_PLL   = PLL_TIMEOUT,
                                       .divMaxToCpu_0       = 1,
                                       .freqSupp            = MDRB_CPU_FREQ_SUPP_60MHz};

  //  =================  Таблица вариантов тактирования =======================   
                           
  CLK_Item ClockConfigs[_ClockItemsCount] = {
  /* iLSI */        {.setFuncID = ID_SetLSI,     .cfgStruct = &cfgLSI,   .indHSE = 0, .indPLL = 0, .freqHz = LSI_FREQ_HZ, .name = "LSI"},
  /* iLSE */        {.setFuncID = ID_SetLSE,     .cfgStruct = &cfgLSE,   .indHSE = 0, .indPLL = 0, .freqHz = LSE_FREQ_HZ, .name = "LSE"},
                    //  HSI
  /* iHSI   */      {.setFuncID = ID_SetHSI,     .cfgStruct = &cfgHSI,   .indHSE = 0, .indPLL = 0, .freqHz = HSI_FREQ_HZ, .name = "HSI"},
  /* iHSId2 */      {.setFuncID = ID_SetHSI,     .cfgStruct = &cfgHSI_2, .indHSE = 0, .indPLL = 0, .freqHz = (HSI_FREQ_HZ >> 1), .name = "HSI/2"},
                    //  HSE0
  /* iHSE0   */     {.setFuncID = ID_SetHSE,     .cfgStruct = &cfgHSE,   .indHSE = 0, .indPLL = 0, .freqHz = HSE_FREQ_HZ, .name = "HSE0"},
  /* iHSE0d2 */     {.setFuncID = ID_SetHSE,     .cfgStruct = &cfgHSE_2, .indHSE = 0, .indPLL = 0, .freqHz = (HSE_FREQ_HZ >> 1), .name = "HSE0/2"},
                    //  HSE1
  /* iHSE1   */     {.setFuncID = ID_SetHSE,     .cfgStruct = &cfgHSE,   .indHSE = 1, .indPLL = 0, .freqHz = HSE_FREQ_HZ, .name = "HSE1"},
  /* iHSE1d2 */     {.setFuncID = ID_SetHSE,     .cfgStruct = &cfgHSE_2, .indHSE = 1, .indPLL = 0, .freqHz = (HSE_FREQ_HZ >> 1), .name = "HSE1/2"},
                    //  PLLx_HSI
  /* iHSI_P0_120*/  {.setFuncID = ID_SetPLL_HSI, .cfgStruct = &cfgPLL_HSI_120M, .indHSE = 0, .indPLL = 0, 120000000, .name = "P0HSI_120"},
  /* iHSI_P1_100*/  {.setFuncID = ID_SetPLL_HSI, .cfgStruct = &cfgPLL_HSI_100M, .indHSE = 0, .indPLL = 1, 100000000, .name = "P1HSI_100"},  
  /* iHSI_P2_80*/   {.setFuncID = ID_SetPLL_HSI, .cfgStruct = &cfgPLL_HSI_80M,  .indHSE = 0, .indPLL = 2,  80000000, .name = "P2HSI_80"},
  /* iHSI_P3_40*/   {.setFuncID = ID_SetPLL_HSI, .cfgStruct = &cfgPLL_HSI_40M,  .indHSE = 0, .indPLL = 3,  40000000, .name = "P3HSI_40"},  
                    //  PLLx_HSE0
  /* iHSE0_P0_120*/ {.setFuncID = ID_SetPLL_HSE, .cfgStruct = &cfgPLL_HSE_120M, .indHSE = 0, .indPLL = 0, 120000000, .name = "P0HSE0_120"},
  /* iHSE0_P1_100*/ {.setFuncID = ID_SetPLL_HSE, .cfgStruct = &cfgPLL_HSE_100M, .indHSE = 0, .indPLL = 1, 100000000, .name = "P1HSE0_100"},  
  /* iHSE0_P2_80 */ {.setFuncID = ID_SetPLL_HSE, .cfgStruct = &cfgPLL_HSE_80M,  .indHSE = 0, .indPLL = 2,  80000000, .name = "P2HSE0_80"},
  /* iHSE0_P3_60*/  {.setFuncID = ID_SetPLL_HSE, .cfgStruct = &cfgPLL_HSE_60M,  .indHSE = 0, .indPLL = 3,  60000000, .name = "P3HSE0_60"},  
                    //  PLLx_HSE1
  /* iHSE1_P0_120*/ {.setFuncID = ID_SetPLL_HSE, .cfgStruct = &cfgPLL_HSE_120M, .indHSE = 1, .indPLL = 0, 120000000, .name = "P0HSE1_120"},
  /* iHSE1_P1_100*/ {.setFuncID = ID_SetPLL_HSE, .cfgStruct = &cfgPLL_HSE_100M, .indHSE = 1, .indPLL = 1, 100000000, .name = "P1HSE1_100"},  
  /* iHSE1_P2_80 */ {.setFuncID = ID_SetPLL_HSE, .cfgStruct = &cfgPLL_HSE_80M,  .indHSE = 1, .indPLL = 2,  80000000, .name = "P2HSE1_80"},  
  /* iHSE1_P3_60*/  {.setFuncID = ID_SetPLL_HSE, .cfgStruct = &cfgPLL_HSE_60M,  .indHSE = 1, .indPLL = 3,  60000000, .name = "P3HSE1_60"},    
  };


  //  =================  Функция переключения на вариант тактирования =======================
  MDR_CPU_SetClockResult  ChangeClockCPU(const CLK_Item *item)
  {
    bool fromLowerFreq = item->freqHz > MDR_CPU_GetFreqHz(false);
    
    switch (item->setFuncID) {
      case ID_SetLSI:        
        return MDR_CPU_SetClock_LSI((MDR_CPU_CfgLSI *)(item->cfgStruct), LSI_TIMEOUT);
      
      case ID_SetLSE:  
        return MDR_CPU_SetClock_LSE((MDR_CPU_CfgLSE *)(item->cfgStruct), LSE_TIMEOUT);
      
      case ID_SetHSI:
        return MDR_CPU_SetClock_HSI((MDR_CPU_CfgHSI *)(item->cfgStruct), HSI_TIMEOUT, fromLowerFreq);
        
      case ID_SetHSE: 
      {
        if (item->indHSE == 0)
          return MDR_CPU_SetClock_HSE0((MDR_CPU_CfgHSE *)(item->cfgStruct), HSE_TIMEOUT, fromLowerFreq);
        else 
          return MDR_CPU_SetClock_HSE1((MDR_CPU_CfgHSE *)(item->cfgStruct), HSE_TIMEOUT, fromLowerFreq);
      }
      
      case ID_SetPLL_HSI:
      {  
        if (item->indPLL == 0)
          return MDR_CPU_SetClock_HSI_PLL0((MDR_CPU_PLL_CfgHSI *)(item->cfgStruct), fromLowerFreq);
        else if (item->indPLL == 1)
          return MDR_CPU_SetClock_HSI_PLL1((MDR_CPU_PLL_CfgHSI *)(item->cfgStruct), fromLowerFreq);
        else if (item->indPLL == 2)
          return MDR_CPU_SetClock_HSI_PLL2((MDR_CPU_PLL_CfgHSI *)(item->cfgStruct), fromLowerFreq);        
        else
          return MDR_CPU_SetClock_HSI_PLL3((MDR_CPU_PLL_CfgHSI *)(item->cfgStruct), fromLowerFreq);
      }

      case ID_SetPLL_HSE:
      {
        if (item->indHSE == 0)
        { // HSE0_PLL
          if (item->indPLL == 0)
            return MDR_CPU_SetClock_HSE0_PLL0((MDR_CPU_PLL_CfgHSE *)(item->cfgStruct), fromLowerFreq);
          else if (item->indPLL == 1)
            return MDR_CPU_SetClock_HSE0_PLL1((MDR_CPU_PLL_CfgHSE *)(item->cfgStruct), fromLowerFreq);
          else if (item->indPLL == 2)
            return MDR_CPU_SetClock_HSE0_PLL2((MDR_CPU_PLL_CfgHSE *)(item->cfgStruct), fromLowerFreq);          
          else
            return MDR_CPU_SetClock_HSE0_PLL3((MDR_CPU_PLL_CfgHSE *)(item->cfgStruct), fromLowerFreq);
        } 
        else 
        { // HSE1_PLL
          if (item->indPLL == 0)
            return MDR_CPU_SetClock_HSE1_PLL0((MDR_CPU_PLL_CfgHSE *)(item->cfgStruct), fromLowerFreq);
          else if (item->indPLL == 1)
            return MDR_CPU_SetClock_HSE1_PLL1((MDR_CPU_PLL_CfgHSE *)(item->cfgStruct), fromLowerFreq);
          else if (item->indPLL == 2)
            return MDR_CPU_SetClock_HSE1_PLL2((MDR_CPU_PLL_CfgHSE *)(item->cfgStruct), fromLowerFreq);
          else
            return MDR_CPU_SetClock_HSE1_PLL3((MDR_CPU_PLL_CfgHSE *)(item->cfgStruct), fromLowerFreq);
        }    
      } //   ID_SetPLL_HSE
    } // switch
      
    
    return MDR_SET_CLOCK_ERR__Undef;
  }
#else
  //  ================= Настройки источников частот - VE1, VE3, VE4, VE9x,VK234, VK214, VC01=======================
  static MDR_CPU_CfgLSI cfgLSI   = MDR_CPU_CFG_LSI_DEF;
  static MDR_CPU_CfgLSE cfgLSE   = MDR_CPU_CFG_LSE_RES_DEF;

  static MDR_CPU_CfgHSI cfgHSI   = MDR_CPU_CFG_HSI_DEF;
  static MDR_CPU_CfgHSI cfgHSI_2 = MDR_CPU_CFG_HSI_DIV2_DEF;

  static MDR_CPU_CfgHSE cfgHSE   = MDR_CPU_CFG_HSE_RES_DEF;
  static MDR_CPU_CfgHSE cfgHSE_2 = MDR_CPU_CFG_HSE_DIV2_RES_DEF;
                      

  static MDR_CPU_PLL_CfgHSI cfgPLL_HSI_128M = {.freqTrim     = HSI_FREQ_TRIM,
                                       .selDiv2             = false,
                                       .timeoutCycles_HSI   = HSI_TIMEOUT,
                                       .pllMul              = MDRB_PLL_8MHz_TO_128MHz,
                                       .timeoutCycles_PLL   = PLL_TIMEOUT,
                                       .divC3               = MDR_Div256P_div1,
                                       .freqSupp            = MDRB_CPU_FREQ_SUPP_128MHz};  

  static MDR_CPU_PLL_CfgHSI cfgPLL_HSI_64M = {.freqTrim     = HSI_FREQ_TRIM,
                                       .selDiv2             = false,
                                       .timeoutCycles_HSI   = HSI_TIMEOUT,
                                       .pllMul              = MDRB_PLL_8MHz_TO_64MHz,
                                       .timeoutCycles_PLL   = PLL_TIMEOUT,
                                       .divC3               = MDR_Div256P_div1,
                                       .freqSupp            = MDRB_CPU_FREQ_SUPP_64MHz};

  static MDR_CPU_PLL_CfgHSI cfgPLL_HSI_32M = {.freqTrim     = HSI_FREQ_TRIM,
                                       .selDiv2             = false,
                                       .timeoutCycles_HSI   = HSI_TIMEOUT,
                                       .pllMul              = MDRB_PLL_8MHz_TO_32MHz,
                                       .timeoutCycles_PLL   = PLL_TIMEOUT,
                                       .divC3               = MDR_Div256P_div1,
                                       .freqSupp            = MDRB_CPU_FREQ_SUPP_32MHz};

  static MDR_CPU_PLL_CfgHSE cfgPLL_HSE_128M = {.freqSource   = MDR_CLK_Resonator,
                                       .selDiv2             = false,
                                       .timeoutCycles_HSE   = HSI_TIMEOUT,
                                       .pllMul              = MDRB_PLL_8MHz_TO_128MHz,
                                       .timeoutCycles_PLL   = PLL_TIMEOUT,
                                       .divC3               = MDR_Div256P_div1,
                                       .freqSupp            = MDRB_CPU_FREQ_SUPP_128MHz};  

  static MDR_CPU_PLL_CfgHSE cfgPLL_HSE_80M = {.freqSource   = MDR_CLK_Resonator,
                                       .selDiv2             = false,
                                       .timeoutCycles_HSE   = HSI_TIMEOUT,
                                       .pllMul              = MDRB_PLL_8MHz_TO_80MHz,
                                       .timeoutCycles_PLL   = PLL_TIMEOUT,
                                       .divC3               = MDR_Div256P_div1,
                                       .freqSupp            = MDRB_CPU_FREQ_SUPP_80MHz};

  static MDR_CPU_PLL_CfgHSE cfgPLL_HSE_48M = {.freqSource   = MDR_CLK_Resonator,
                                       .selDiv2             = false,
                                       .timeoutCycles_HSE   = HSI_TIMEOUT,
                                       .pllMul              = MDRB_PLL_8MHz_TO_48MHz,
                                       .timeoutCycles_PLL   = PLL_TIMEOUT,
                                       .divC3               = MDR_Div256P_div1,
                                       .freqSupp            = MDRB_CPU_FREQ_SUPP_48MHz};


  //  =================  Таблица вариантов тактирования =======================   
  CLK_Item ClockConfigs[_ClockItemsCount] = {
  /* iLSI */       {.setFuncID = ID_SetLSI,     .cfgStruct = &cfgLSI,   .indHSE = 0, .indPLL = 0, .freqHz = LSI_FREQ_HZ, .name = "LSI"},
  /* iLSE */       {.setFuncID = ID_SetLSE,     .cfgStruct = &cfgLSE,   .indHSE = 0, .indPLL = 0, .freqHz = LSE_FREQ_HZ, .name = "LSE"},
                   //  HSI
  /* iHSI   */     {.setFuncID = ID_SetHSI,     .cfgStruct = &cfgHSI,   .indHSE = 0, .indPLL = 0, .freqHz = HSI_FREQ_HZ, .name = "HSI"},
  /* iHSId2 */     {.setFuncID = ID_SetHSI,     .cfgStruct = &cfgHSI_2, .indHSE = 0, .indPLL = 0, .freqHz = (HSI_FREQ_HZ >> 1), .name = "HSI/2"},
                   //  HSE0
  /* iHSE   */     {.setFuncID = ID_SetHSE,     .cfgStruct = &cfgHSE,   .indHSE = 0, .indPLL = 0, .freqHz = HSE_FREQ_HZ, .name = "HSE"},
  /* iHSEd2 */     {.setFuncID = ID_SetHSE,     .cfgStruct = &cfgHSE_2, .indHSE = 0, .indPLL = 0, .freqHz = (HSE_FREQ_HZ >> 1), .name = "HSE/2"},
                   //  PLLx_HSI
  /* iHSI_P_128*/  {.setFuncID = ID_SetPLL_HSI, .cfgStruct = &cfgPLL_HSI_128M, .indHSE = 0, .indPLL = 0, 128000000, .name = "PHSI_128"},
  /* iHSI_P_64*/   {.setFuncID = ID_SetPLL_HSI, .cfgStruct = &cfgPLL_HSI_64M,  .indHSE = 0, .indPLL = 1, 64000000,  .name = "PHSI_64"},  
  /* iHSI_P_32*/   {.setFuncID = ID_SetPLL_HSI, .cfgStruct = &cfgPLL_HSI_32M,  .indHSE = 0, .indPLL = 2, 32000000,  .name = "PHSI_32"},
                   //  PLLx_HSE0
  /* iHSE_P_128 */ {.setFuncID = ID_SetPLL_HSE, .cfgStruct = &cfgPLL_HSE_128M, .indHSE = 0, .indPLL = 0, 128000000, .name = "PHSE_128"},
  /* iHSE_P_80 */  {.setFuncID = ID_SetPLL_HSE, .cfgStruct = &cfgPLL_HSE_80M,  .indHSE = 0, .indPLL = 1, 80000000,  .name = "PHSE_80"},  
  /* iHSE_P_48 */  {.setFuncID = ID_SetPLL_HSE, .cfgStruct = &cfgPLL_HSE_48M,  .indHSE = 0, .indPLL = 2, 48000000,  .name = "PHSE_48"},
  };


  //  =================  Функция переключения на вариант тактирования =======================
  MDR_CPU_SetClockResult  ChangeClockCPU(const CLK_Item *item)
  {
    bool fromLowerFreq = item->freqHz > MDR_CPU_GetFreqHz(false);
    
    switch (item->setFuncID) {
      case ID_SetLSI:        
        return MDR_CPU_SetClock_LSI((MDR_CPU_CfgLSI *)(item->cfgStruct), LSI_TIMEOUT);
      
      case ID_SetLSE:  
        return MDR_CPU_SetClock_LSE((MDR_CPU_CfgLSE *)(item->cfgStruct), LSE_TIMEOUT);
      
      case ID_SetHSI:
        return MDR_CPU_SetClock_HSI((MDR_CPU_CfgHSI *)(item->cfgStruct), HSI_TIMEOUT, fromLowerFreq);
        
      case ID_SetHSE: 
        return MDR_CPU_SetClock_HSE((MDR_CPU_CfgHSE *)(item->cfgStruct), HSE_TIMEOUT, fromLowerFreq);
      
      case ID_SetPLL_HSI:
        return MDR_CPU_SetClock_PLL_HSI((MDR_CPU_PLL_CfgHSI *)(item->cfgStruct), fromLowerFreq);

      case ID_SetPLL_HSE:
        return MDR_CPU_SetClock_PLL_HSE((MDR_CPU_PLL_CfgHSE *)(item->cfgStruct), fromLowerFreq);
    }
      
    
    return MDR_SET_CLOCK_ERR__Undef;
  }
#endif  



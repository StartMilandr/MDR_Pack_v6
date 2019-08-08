/**************************************************************************//**
 * @file     system_ESila.c
 * @brief    CMSIS Cortex-M4 Device Peripheral Access Layer Source File for
 *           Device ESila
 * @version  V5.00
 * @date     10. January 2018
 ******************************************************************************/
/*
 * Copyright (c) 2009-2018 Arm Limited. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "MDR_ESila.h"
#include "MDR_Config.h"


/*----------------------------------------------------------------------------
  Define clocks
 *----------------------------------------------------------------------------*/
#define XTAL            HSI_FREQ_HZ       /* HSI Oscillator frequency             */

#define SYSTEM_CLOCK    (1 * XTAL)


/*----------------------------------------------------------------------------
  System Core Clock Variable
 *----------------------------------------------------------------------------*/
uint32_t SystemCoreClock = SYSTEM_CLOCK;  /* System Clock Frequency (Core Clock)*/
static uint32_t MDR_MaxClock = SYSTEM_CLOCK;



/*----------------------------------------------------------------------------
  Clock functions
 *----------------------------------------------------------------------------*/

#define FERQ_FAULT_HZ       HSI_FREQ_HZ

#define CLK_SEL_COUNT_PLL   MDR_PLL_IN_HSE1div2 + 1
#define CLK_SEL_COUNT       MAXCLK_PLL0

static const uint32_t _GenFreqsHz[CLK_SEL_COUNT] = {
                      //typedef enum {             typedef enum {          
  HSI_FREQ_HZ,        //  MAXCLK_HSI      = 0,       MDR_PLL_IN_HSI       = 0,
  HSI_FREQ_HZ/2,      //  MAXCLK_HSIdiv2  = 1,       MDR_PLL_IN_HSIdiv2   = 1,
  HSE0_FREQ_HZ,       //  MAXCLK_HSE0     = 2,       MDR_PLL_IN_HSE0      = 2,
  HSE0_FREQ_HZ/2,     //  MAXCLK_HSE0div2 = 3,       MDR_PLL_IN_HSE0div2  = 3,
  HSE1_FREQ_HZ,       //  MAXCLK_HSE1     = 4,       MDR_PLL_IN_HSE1      = 4,
  HSE1_FREQ_HZ/2,     //  MAXCLK_HSE1div2 = 5,       MDR_PLL_IN_HSE1div2  = 5,
  LSI_FREQ_HZ,        //  MAXCLK_LSI      = 6,     } MDR_PLL_IN_SEL;
  LSE_FREQ_HZ         //  MAXCLK_LSE      = 7,
};                    //  MAXCLK_PLL0     = 8,  
                      //  MAXCLK_PLL1     = 9,
                      //  MAXCLK_PLL2     = 10,
                      //  MAXCLK_PLL3     = 11,
                      //} MDR_MAXCLK_SEL;

#define PLL_DIV4_CODE    2

void SystemCoreClockUpdate (void)
{
  uint32_t regCLK;
  uint32_t pll_source, pll_N, pll_Q, pll_DIV;
  uint32_t sel_max_clk, sel_pll;
  uint32_t freqHz;

  sel_max_clk = MDR_CLOCK->MAX_CLK & MDR_RST_CLOCK_MAX_CLK_Select_Msk;

  if (sel_max_clk < MAXCLK_PLL0)
    freqHz = _GenFreqsHz[sel_max_clk];
  else if (sel_max_clk <= MAXCLK_PLL3)
  {  
    switch (sel_max_clk)
    {
      case MAXCLK_PLL1: regCLK = MDR_CLOCK->PLL1_CLK; break;
      case MAXCLK_PLL2: regCLK = MDR_CLOCK->PLL2_CLK; break;
      case MAXCLK_PLL3: regCLK = MDR_CLOCK->PLL3_CLK; break;
      default:          regCLK = MDR_CLOCK->PLL0_CLK; break;
    }  
    sel_pll = _FLD2VAL(MDR_RST_PLL_SELECT, regCLK);
    if (sel_pll < CLK_SEL_COUNT_PLL)
    {
      pll_source = _GenFreqsHz[sel_pll];
      
      pll_Q   = _FLD2VAL(MDR_RST_PLL_PLL_Q, regCLK);
      pll_DIV = _FLD2VAL(MDR_RST_PLL_DV,    regCLK);
      pll_N   = _FLD2VAL(MDR_RST_PLL_PLL_N, regCLK);     
      if (pll_N == 0)
        pll_N = 2;          
     
      if (pll_DIV < PLL_DIV4_CODE)
        freqHz = ((pll_source * pll_N / (pll_Q + 1)) / (pll_DIV + 1));	    
      else
        freqHz = ((pll_source * pll_N / (pll_Q + 1)) / 4);
    }
    else
      freqHz = FERQ_FAULT_HZ;   
  } 
  else
    freqHz = FERQ_FAULT_HZ;
  
  uint32_t freqDiv = (MDR_CLOCK->CPU_CLK & MDR_RST_CLK_DIV_Msk) >> MDR_RST_CLK_DIV_Pos;
  
  MDR_MaxClock = freqHz;  
  SystemCoreClock = freqHz / (freqDiv + 1);
}

void SystemInit (void)
{
  MDR_CLOCK->KEY = MDR_KEY_UNLOCK;
  
  // Включение внутренних источников тока для аналоговых блоков - PLL, ADC и т.д.
  MDR_CLOCK->PER1_CLK  |= MDR_RST_PER1_CMP1_CLK_EN_Msk;
  MDR_COMP1->ANABG_CTRL = MDR_COMP_ANABG_BGEN_Msk | MDR_COMP_ANABG_IREFEN_Msk; 
  MDR_CLOCK->PER1_CLK  &= ~MDR_RST_PER1_CMP1_CLK_EN_Msk;
  
  SystemCoreClock = SYSTEM_CLOCK;
}


/*----------------------------------------------------------------------------
  AUX functions for SPL
 *----------------------------------------------------------------------------*/
uint32_t MDR_GetClockHz_InputPLL(uint32_t selInpPll);
uint32_t MDR_GetClockHz_MaxClock(bool doUpdate);

uint32_t MDR_GetClockHz_InputPLL(uint32_t selInpPll)
{
  return _GenFreqsHz[selInpPll];
}

uint32_t MDR_GetClockHz_MaxClock(bool doUpdate)
{
  if (doUpdate)
   SystemCoreClockUpdate(); 
  
  return MDR_MaxClock;
}

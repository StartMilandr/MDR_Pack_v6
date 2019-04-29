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



/*----------------------------------------------------------------------------
  Clock functions
 *----------------------------------------------------------------------------*/


//static const uint32_t _GenFreqsHz[8] = {HSI_Value, HSI_Value/2, HSE0_Value, HSE0_Value/2, HSE1_Value, HSE1_Value/2, LSI_Value, LSE_Value};

void SystemCoreClockUpdate (void)
{
  //  uint32_t cpu_freq;
  //  uint32_t regCLK;
  //  uint32_t pll_source, pll_N, pll_Q, pll_DIV;
  //  uint32_t sel_max_clk, sel_pll;
	
	// sel_max_clk = CLK_CNTR->MAX_CLK & 0xF;

  // if (sel_max_clk < MAXCLK_PLL0)
  //   SystemCoreClock = _GenFreqsHz[sel_max_clk];
  // else if (sel_max_clk <= MAXCLK_PLL2)
  // {  
  //   switch (sel_max_clk)
  //   {
  //     case MAXCLK_PLL0: regCLK = CLK_CNTR->PLL0_CLK; break;
  //     case MAXCLK_PLL1: regCLK = CLK_CNTR->PLL1_CLK; break;        
  //     case MAXCLK_PLL2: regCLK = CLK_CNTR->PLL2_CLK; break;
  //   }
  //   sel_pll = ((regCLK >> 29) & 0x7);
  //   if (sel_pll < 6)
  //     pll_source = _GenFreqsHz[sel_pll];
  //   else
  //     pll_source = FERQ_FAULT_HZ;
  //   if (((regCLK >> 8) & 0x7F) == 0)
  //     pll_N = 2;
  //   else 
  //     pll_N =((regCLK >> 8) & 0x7F);	
  //   pll_Q = (regCLK & 0xF);
  //   pll_DIV = ((regCLK >> 4) & 0x1);
  //   SystemCoreClock = ((pll_source * pll_N / (pll_Q + 1)) / (pll_DIV + 1));	    
  // } 
  // else
	//   SystemCoreClock = FERQ_FAULT_HZ;
}

void SystemInit (void)
{
/* ToDo: add code to initialize the system
         do not use global variables because this function is called before
         reaching pre-main. RW section maybe overwritten afterwards. */
  SystemCoreClock = SYSTEM_CLOCK;
}

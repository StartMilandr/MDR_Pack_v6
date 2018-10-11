/**************************************************************************//**
 * @file     system_MDR1986BE1.c
 * @brief    CMSIS Cortex-M1 Device Peripheral Access Layer Source File for
 *           Device MDR1986BE1
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

#include "MDR_1986BE1.h"
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

void SystemCoreClockUpdate (void)            /* Get Core Clock Frequency      */
{
  uint32_t freq = SystemCoreClock;
  MDR_RST_CPU_Bits regCPU_CLOCK = MDR_CLOCK->CPU_CLOCK_b;
  
  switch (regCPU_CLOCK.HCLK_SEL)
  {    
    case MDR_HCLK_HSI:
      freq = HSI_FREQ_HZ;
      break;
    case MDR_HCLK_LSE:
      freq = LSE_FREQ_HZ;
      break;
    case MDR_HCLK_LSI:
      freq = LSI_FREQ_HZ;
      break;
    case MDR_HCLK_CPU_C3: 
    {
      switch (regCPU_CLOCK.CPU_C1_SEL)
      {
        case MDR_HSIE2_HSI:
          freq = HSI_FREQ_HZ;
          break;
        case MDR_HSIE2_HSI_div2:
          freq = HSI_FREQ_HZ / 2;
          break;
        case MDR_HSIE2_HSE:
          freq = HSE_FREQ_HZ;
          break;
        case MDR_HSIE2_HSE_div2:
          freq = HSE_FREQ_HZ / 2;
          break;
      }
      
      if (regCPU_CLOCK.CPU_C2_SEL == MDR_CPU_PLL)
        freq *= (MDR_CLOCK->PLL_CONTROL_b.PLL_CPU_MUL + 1);
      
      break;
    }    
  }
 
  if (regCPU_CLOCK.CPU_C3_SEL >= MDR_CLK_div2)
   freq = freq >> (regCPU_CLOCK.CPU_C3_SEL - MDR_CLK_div2 + 1);
  
  SystemCoreClock = freq;
}

void SystemInit (void)
{
/* ToDo: add code to initialize the system
         do not use global variables because this function is called before
         reaching pre-main. RW section maybe overwritten afterwards. */
  SystemCoreClock = SYSTEM_CLOCK;
}

/**************************************************************************//**
 * @file     system_MDR1986VK214.c
 * @brief    CMSIS Cortex-M0 Device Peripheral Access Layer Source File for
 *           Device MDR1986VK214
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

#include "MDR_1986VK214.h"
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

static uint32_t _clockFreqHz[] = {HSI_FREQ_HZ, 0, LSE_FREQ_HZ, LSI_FREQ_HZ,                     //  HCLK_SEL
                                  HSI_FREQ_HZ, HSI_FREQ_HZ / 2, HSE_FREQ_HZ, HSE_FREQ_HZ / 2};  //  CPU_C1_SEL

void SystemCoreClockUpdate (void)
{
  uint32_t freq = SystemCoreClock;
  uint32_t regCPU_CLOCK = MDR_CLOCK->CPU_CLOCK;
  
  uint32_t value = _FLD2VAL(MDR_RST_CPU__HCLK_SEL, regCPU_CLOCK);  
  if (value != MDR_HCLK_CPU_C3)  
    freq = _clockFreqHz[value];
  else
  {
    value = _FLD2VAL(MDR_RST_CPU__C1_SEL, regCPU_CLOCK);      
    freq = _clockFreqHz[value + 4];

    value = _FLD2VAL(MDR_RST_CPU__C2_SEL, regCPU_CLOCK);      
    if (value == MDR_CPU_PLL)
    {
      value = _FLD2VAL(MDR_RST_PLL__CPU_MUL, MDR_CLOCK->PLL_CONTROL);      
      freq *= (value + 1);
    }
  }
  
  value = _FLD2VAL(MDR_RST_CPU__C3_SEL, regCPU_CLOCK); 
  if (value >= MDR_Div256P_div2)
   freq = freq >> (value - MDR_Div256P_div2 + 1);
  
  SystemCoreClock = freq;
}

void SystemInit (void)
{
/* ToDo: add code to initialize the system
         do not use global variables because this function is called before
         reaching pre-main. RW section maybe overwritten afterwards. */
  SystemCoreClock = SYSTEM_CLOCK;
}

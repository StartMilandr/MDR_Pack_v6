/**************************************************************************//**
 * @file     MDR_1923VK014.h
 * @brief    CMSIS Cortex-M0 Core Peripheral Access Layer Header File for
 *           Device MDR1923VK014
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

#ifndef MDR_1923VK014_H
#define MDR_1923VK014_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup Milandr
  * @{
  */


/** @addtogroup MDR1923VK014
  * @{
  */


/** @addtogroup Configuration_of_CMSIS
  * @{
  */



/* =========================================================================================================================== */
/* ================                                Interrupt Number Definition                                ================ */
/* =========================================================================================================================== */

typedef enum IRQn
{
/******  Cortex-M0 Processor Exceptions Numbers ***************************************/
  NonMaskableInt_IRQn           = -14,      /*  2 Non Maskable Interrupt */
  HardFault_IRQn                = -13,      /*  3 HardFault Interrupt */
  SVCall_IRQn                   =  -5,      /* 11 SV Call Interrupt */
  PendSV_IRQn                   =  -2,      /* 14 Pend SV Interrupt */
  SysTick_IRQn                  =  -1,      /* 15 System Tick Interrupt */

/******  1923VK014 specific Interrupt Numbers *******************************************/                                       
  FT_ERR_IRQn             = 0,
  CLK_IRQn                = 1,
  POWER_IRQn              = 2,
  RTC_IRQn                = 3,
  BKP_IRQn                = 4,
  EBC_ERROR_IRQn          = 5,
  DMA_IRQn                = 6,
  CCSDS_TX_IRQn           = 7,
  CCSDS_RX_IRQn           = 8,
  GPIO_IRQn               = 9,
  SPW1_IRQn        		    = 10,
  SPW2_IRQn        		    = 11,
  TIMER1_IRQn        	    = 12,
  TIMER2_IRQn             = 13,
  TIMER3_IRQn        	    = 14,
  TIMER4_IRQn        	    = 15,
  CAN1_IRQn         	    = 16,
  CAN2_IRQn         	    = 17,
  UART1_IRQn         	    = 18,	
  UART2_IRQn         	    = 19,
  MIL1_IRQn               = 20,
  MIL2_IRQn               = 21, 
  MIL3_IRQn               = 22,
  MIL4_IRQn               = 23, 
  SSP1_IRQn         	    = 24,
  SSP2_IRQn         	    = 25,
  SSP3_IRQn         	    = 26,
  SSP4_IRQn         	    = 27,
  SSP5_IRQn         	    = 28,
  SSP6_IRQn         	    = 29,
  CRC_IRQn         	      = 30,
  ECC_IRQn         	      = 31,
} IRQn_Type;




/* =========================================================================================================================== */
/* ================                           Processor and Core Peripheral Section                           ================ */
/* =========================================================================================================================== */

/* --------  Configuration of the Cortex-M0 Processor and Core Peripherals  ------- */
#define __CM0_REV                 0x0000U   /* Core revision r0p0 */
#define __MPU_PRESENT             0U        /* MPU present or not */
#define __VTOR_PRESENT            0U        /* no VTOR present*/
#define __NVIC_PRIO_BITS          2U        /* Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig    0U        /* Set to 1 if different SysTick Config is used */


/** @} */ /* End of group Configuration_of_CMSIS */


#include <core_cm0.h>                          /*!< Arm Cortex-M0 processor and core peripherals */
#include "system_MDR1923VK014.h"                 /*!< MDR1923VK014 System */


/* ========================================  Start of section using anonymous unions  ======================================== */
#if   defined (__CC_ARM)
  #pragma push
  #pragma anon_unions
#elif defined (__ICCARM__)
  #pragma language=extended
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wc11-extensions"
  #pragma clang diagnostic ignored "-Wreserved-id-macro"
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning 586
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif


/* =========================================================================================================================== */
/* ================                            Device Specific Peripheral Section                             ================ */
/* =========================================================================================================================== */


#define MDR_KEY_UNLOCK    0x8555AAA1UL

/*===============  RST_Clock ===================*/
#include <MDR_RST_VE8x_defs.h>
#include <MDR_RST_VK014_defs.h>


/*===============  BKP ===================*/
#include <MDR_BKP_VK014_defs.h>


/*===============  GPIO Port ===================*/
#include <MDR_GPIO_VE8x_defs.h>


/*=========  SSP - Synchronous Serial Port ========*/
#include "MDR_SSP_def.h"

/*=========  UART ========*/
#include <MDR_UART_defs.h>

/*=========  TIMER ========*/
#include <MDR_TimerVE13_defs.h>




/*@}*/ /* end of group MDR1923VK014_Peripherals */


/* =========================================  End of section using anonymous unions  ========================================= */
#if   defined (__CC_ARM)
  #pragma pop
#elif defined (__ICCARM__)
  /* leave anonymous unions enabled */
#elif (__ARMCC_VERSION >= 6010050)
  #pragma clang diagnostic pop
#elif defined (__GNUC__)
  /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
  /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
  #pragma warning restore
#elif defined (__CSMC__)
  /* anonymous unions are enabled by default */
#else
  #warning Not supported compiler type
#endif


/* =========================================================================================================================== */
/* ================                          Device Specific Peripheral Address Map                           ================ */
/* =========================================================================================================================== */

/** @addtogroup Device_Peripheral_peripheralAddr
  * @{
  */

/* Peripheral and SRAM base address */
// #define ADDR_FLASH_BASE       (0x00000000UL)                              /*!< (FLASH     ) Base Address */
// #define ADDR_SRAM_BASE        (0x20000000UL)                              /*!< (SRAM      ) Base Address */
 #define ADDR_PERIPH_BASE      (0x40000000UL)                              /*!< (Peripheral) Base Address */

/* Peripheral memory map */
#define ADDR_RST_CLOCK_BASE   0x40000000UL                              /*!< RST_CLOCK Base Address      */
#define ADDR_BKP_BASE         0x40001000UL                              /*!< Backup and RTC Base Address */

#define ADDR_PORTA_BASE       0x40080000UL                              /*!< GPIO PORT_A Base Address */
#define ADDR_PORTB_BASE       0x40081000UL                              /*!< GPIO PORT_B Base Address */
#define ADDR_PORTC_BASE       0x40082000UL                              /*!< GPIO PORT_C Base Address */
#define ADDR_PORTD_BASE       0x40083000UL                              /*!< GPIO PORT_D Base Address */
#define ADDR_PORTE_BASE       0x40084000UL                              /*!< GPIO PORT_E Base Address */



#define ADDR_SSP1_BASE        0x40095000UL                                   /*!< SSP Base Address      */
#define ADDR_SSP2_BASE        0x40096000UL                                   /*!< SSP Base Address      */

#define ADDR_UART1_BASE       0x40099000UL
#define ADDR_UART2_BASE       0x4009A000UL

#define ADDR_TIMER1_BASE      0x4008A000UL
#define ADDR_TIMER2_BASE      0x4008B000UL
#define ADDR_TIMER3_BASE      0x4008C000UL
#define ADDR_TIMER4_BASE      0x4008D000UL
#define ADDR_TIMER5_BASE      0x4008E000UL
#define ADDR_TIMER6_BASE      0x4008F000UL


/** @} */ /* End of group Device_Peripheral_peripheralAddr */


/* =========================================================================================================================== */
/* ================                                  Peripheral declaration                                   ================ */
/* =========================================================================================================================== */

/** @addtogroup Device_Peripheral_declaration
  * @{
  */

#define MDR_CLOCK                      ((MDR_RST_CLOCK_Type *) ADDR_RST_CLOCK_BASE)

#if defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
  #define MDR_CLOCK_HSE0                 ((MDR_RST_HSE_Type   *) (__IOM uint32_t)(&MDR_CLOCK->HSE0_CLK))
  #define MDR_CLOCK_HSE1                 ((MDR_RST_HSE_Type   *) (__IOM uint32_t)(&MDR_CLOCK->HSE1_CLK))
  #define MDR_CLOCK_PLL0                 ((MDR_RST_PLL_Type   *) (__IOM uint32_t)(&MDR_CLOCK->PLL0_CLK))
  #define MDR_CLOCK_PLL1                 ((MDR_RST_PLL_Type   *) (__IOM uint32_t)(&MDR_CLOCK->PLL1_CLK))
  #define MDR_CLOCK_PLL2                 ((MDR_RST_PLL_Type   *) (__IOM uint32_t)(&MDR_CLOCK->PLL2_CLK))
#else
  #define MDR_CLOCK_HSE0                 ((MDR_RST_HSE_Type   *) (&MDR_CLOCK->HSE0_CLK))
  #define MDR_CLOCK_HSE1                 ((MDR_RST_HSE_Type   *) (&MDR_CLOCK->HSE1_CLK))
  #define MDR_CLOCK_PLL0                 ((MDR_RST_PLL_Type   *) (&MDR_CLOCK->PLL0_CLK))
  #define MDR_CLOCK_PLL1                 ((MDR_RST_PLL_Type   *) (&MDR_CLOCK->PLL1_CLK))
  #define MDR_CLOCK_PLL2                 ((MDR_RST_PLL_Type   *) (&MDR_CLOCK->PLL2_CLK))
#endif


#define MDR_BKP                        ((MDR_BKP_Type       *) ADDR_BKP_BASE)

#define MDR_PORTA                      ((MDR_PORT_Type 	    *) ADDR_PORTA_BASE)
#define MDR_PORTB                      ((MDR_PORT_Type 	    *) ADDR_PORTB_BASE)
#define MDR_PORTC                      ((MDR_PORT_Type 	    *) ADDR_PORTC_BASE)
#define MDR_PORTD                      ((MDR_PORT_Type 	    *) ADDR_PORTD_BASE)
#define MDR_PORTE                      ((MDR_PORT_Type 	    *) ADDR_PORTE_BASE)


#define MDR_SSP1                       ((MDR_SSP_Type       *) ADDR_SSP1_BASE)
#define MDR_SSP2                       ((MDR_SSP_Type       *) ADDR_SSP2_BASE)

#define MDR_UART1                      ((MDR_UART_Type 	    *) ADDR_UART1_BASE)
#define MDR_UART2                      ((MDR_UART_Type 	    *) ADDR_UART2_BASE)

#define MDR_TIMER1                     ((MDR_TIMER_Type 	  *) ADDR_TIMER1_BASE)
#define MDR_TIMER2                     ((MDR_TIMER_Type 	  *) ADDR_TIMER2_BASE)
#define MDR_TIMER3                     ((MDR_TIMER_Type 	  *) ADDR_TIMER3_BASE)
#define MDR_TIMER4                     ((MDR_TIMER_Type 	  *) ADDR_TIMER4_BASE)
#define MDR_TIMER5                     ((MDR_TIMER_Type 	  *) ADDR_TIMER5_BASE)
#define MDR_TIMER6                     ((MDR_TIMER_Type 	  *) ADDR_TIMER6_BASE)

//  Timer Channels
#define MDR_TIMER1_CH1                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER1->CCR1))
#define MDR_TIMER1_CH2                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER1->CCR2))
#define MDR_TIMER1_CH3                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER1->CCR3))
#define MDR_TIMER1_CH4                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER1->CCR4))

#define MDR_TIMER2_CH1                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER2->CCR1))
#define MDR_TIMER2_CH2                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER2->CCR2))
#define MDR_TIMER2_CH3                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER2->CCR3))
#define MDR_TIMER2_CH4                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER2->CCR4))

#define MDR_TIMER3_CH1                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER3->CCR1))
#define MDR_TIMER3_CH2                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER3->CCR2))
#define MDR_TIMER3_CH3                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER3->CCR3))
#define MDR_TIMER3_CH4                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER3->CCR4))

#define MDR_TIMER4_CH1                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER4->CCR1))
#define MDR_TIMER4_CH2                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER4->CCR2))
#define MDR_TIMER4_CH3                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER4->CCR3))
#define MDR_TIMER4_CH4                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER4->CCR4))

#define MDR_TIMER5_CH1                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER5->CCR1))
#define MDR_TIMER5_CH2                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER5->CCR2))
#define MDR_TIMER5_CH3                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER5->CCR3))
#define MDR_TIMER5_CH4                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER5->CCR4))

#define MDR_TIMER6_CH1                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER6->CCR1))
#define MDR_TIMER6_CH2                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER6->CCR2))
#define MDR_TIMER6_CH3                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER6->CCR3))
#define MDR_TIMER6_CH4                 ((MDR_TIMER_CH_Type 	*) (&MDR_TIMER6->CCR4))


/* ================================================================================================================ */
/* ================                                  SPL_Configs                                   ================ */
/* ================================================================================================================ */

//  Clock Enable bits
//----------------    PORT Definitions  --------------------
#define   MDR_CLK_EN_ADDR_PORT_A    &MDR_CLOCK->PER0_CLK
#define   MDR_CLK_EN_ADDR_PORT_B    &MDR_CLOCK->PER0_CLK
#define   MDR_CLK_EN_ADDR_PORT_C    &MDR_CLOCK->PER0_CLK
#define   MDR_CLK_EN_ADDR_PORT_D    &MDR_CLOCK->PER0_CLK
#define   MDR_CLK_EN_ADDR_PORT_E    &MDR_CLOCK->PER0_CLK

#define   MDR_CLK_EN_BIT_PORT_A     MDR_RST_PER0_PORTA_CLK_EN_Pos
#define   MDR_CLK_EN_BIT_PORT_B     MDR_RST_PER0_PORTB_CLK_EN_Pos
#define   MDR_CLK_EN_BIT_PORT_C     MDR_RST_PER0_PORTC_CLK_EN_Pos
#define   MDR_CLK_EN_BIT_PORT_D     MDR_RST_PER0_PORTD_CLK_EN_Pos
#define   MDR_CLK_EN_BIT_PORT_E     MDR_RST_PER0_PORTE_CLK_EN_Pos


// //----------------    SSP Definitions  --------------------
// //  SSP Block Clock enable
// #define   MDR_SSP1_CLK_EN_ADDR          (&MDR_CLOCK->PER_CLOCK)
// #define   MDR_SSP2_CLK_EN_ADDR          (&MDR_CLOCK->PER_CLOCK)

// #define   MDR_SSP1_CLK_EN_MSK             MDR_RST_PER__SSP1_CLK_EN_Msk
// #define   MDR_SSP2_CLK_EN_MSK             MDR_RST_PER__SSP2_CLK_EN_Msk

// //  SSP_Clock freq configs
// #define   MDR_SSP1_CLOCK_GATE_ADDR      (&MDR_CLOCK->SSP_CLOCK)
// #define   MDR_SSP2_CLOCK_GATE_ADDR      (&MDR_CLOCK->SSP_CLOCK)

// #define   MDR_SSP1_CLOCK_GATE_ENA_MSK     MDR_RST_SSP__SSP1_CLK_EN_Msk
// #define   MDR_SSP2_CLOCK_GATE_ENA_MSK     MDR_RST_SSP__SSP2_CLK_EN_Msk

// #define   MDR_SSP1_CLOCK_GATE_BRG_POS     MDR_RST_SSP__SSP1_BRG_Pos
// #define   MDR_SSP2_CLOCK_GATE_BRG_POS     MDR_RST_SSP__SSP2_BRG_Pos


// //----------------    UART Definitions  --------------------
// //  UART Block Clock enable
// #define   MDR_UART1_CLK_EN_ADDR         (&MDR_CLOCK->PER_CLOCK)
// #define   MDR_UART2_CLK_EN_ADDR         (&MDR_CLOCK->PER_CLOCK)

// #define   MDR_UART1_CLK_EN_MSK            MDR_RST_PER__UART1_CLK_EN_Msk
// #define   MDR_UART2_CLK_EN_MSK            MDR_RST_PER__UART2_CLK_EN_Msk

// //  UART_ClockGate configs
// #define   MDR_UART1_CLOCK_GATE_ADDR     (&MDR_CLOCK->UART_CLOCK)
// #define   MDR_UART2_CLOCK_GATE_ADDR     (&MDR_CLOCK->UART_CLOCK)

// #define   MDR_UART1_CLOCK_GATE_ENA_MSK    MDR_RST_UART__UART1_CLK_EN_Msk
// #define   MDR_UART2_CLOCK_GATE_ENA_MSK    MDR_RST_UART__UART2_CLK_EN_Msk

// #define   MDR_UART1_CLOCK_GATE_BRG_POS    MDR_RST_UART__UART1_BRG_Pos
// #define   MDR_UART2_CLOCK_GATE_BRG_POS    MDR_RST_UART__UART2_BRG_Pos


// //----------------    TIMER Definitions  --------------------
// //  UART Block Clock enable
// #define   MDR_TIMER1_CLK_EN_ADDR         (&MDR_CLOCK->PER_CLOCK)
// #define   MDR_TIMER2_CLK_EN_ADDR         (&MDR_CLOCK->PER_CLOCK)
// #define   MDR_TIMER3_CLK_EN_ADDR         (&MDR_CLOCK->PER_CLOCK)

// #define   MDR_TIMER1_CLK_EN_MSK            MDR_RST_PER__TIMER1_CLK_EN_Msk
// #define   MDR_TIMER2_CLK_EN_MSK            MDR_RST_PER__TIMER2_CLK_EN_Msk
// #define   MDR_TIMER3_CLK_EN_MSK            MDR_RST_PER__TIMER3_CLK_EN_Msk


// //  UART_ClockGate configs
// #define   MDR_TIMER1_CLOCK_GATE_ADDR     (&MDR_CLOCK->TIM_CLOCK)
// #define   MDR_TIMER2_CLOCK_GATE_ADDR     (&MDR_CLOCK->TIM_CLOCK)
// #define   MDR_TIMER3_CLOCK_GATE_ADDR     (&MDR_CLOCK->TIM_CLOCK)

// #define   MDR_TIMER1_CLOCK_GATE_ENA_MSK    MDR_RST_TIM__TIM1_CLK_EN_Msk
// #define   MDR_TIMER2_CLOCK_GATE_ENA_MSK    MDR_RST_TIM__TIM2_CLK_EN_Msk
// #define   MDR_TIMER3_CLOCK_GATE_ENA_MSK    MDR_RST_TIM__TIM3_CLK_EN_Msk

// #define   MDR_TIMER1_CLOCK_GATE_BRG_POS    MDR_RST_TIM__TIM1_BRG_Pos
// #define   MDR_TIMER2_CLOCK_GATE_BRG_POS    MDR_RST_TIM__TIM2_BRG_Pos
// #define   MDR_TIMER3_CLOCK_GATE_BRG_POS    MDR_RST_TIM__TIM3_BRG_Pos

// //  Enable Count UpDown by external events
// #define MDR_TIMER_Can_UpDown_ByExtEvents



/** @} */ /* End of group MDR1923VK014 */

/** @} */ /* End of group Milandr */

#ifdef __cplusplus
}
#endif

#endif  /* MDR_1923VK014_H */

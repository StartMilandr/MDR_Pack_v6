/**************************************************************************//**
 * @file     MDR_1986VE8.h
 * @brief    CMSIS Cortex-M4 Core Peripheral Access Layer Header File for
 *           Device MDR1986VE8
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

#ifndef MDR_1986VE8_H
#define MDR_1986VE8_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup Milandr
  * @{
  */


/** @addtogroup MDR1986VE8
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
/******  Cortex-M4 Processor Exceptions Numbers ***************************************/
  NonMaskableInt_IRQn     = -14,    /*!< 2 Non Maskable Interrupt                     */
  HardFault_IRQn          = -13,    /*!< 3 Cortex-M4 Hard Fault Interrupt             */
  MemoryManagement_IRQn		=	-12,		/*!< 4 Cortex-M4 Memory Management Interrupt      */
  BusFault_IRQn				    =	-11,		/*!< 5 Cortex-M4 Bus Fault Interrupt			        */
  UsageFault_IRQn		      = -10,		/*!< 6 Cortex-M4 Usage Fault Interrupt			      */
  SVCall_IRQn             = -5,     /*!< 11 Cortex-M4 SV Call Interrupt               */
  DebugMonitor_IRQn             =  -4,      /* 12 Debug Monitor Interrupt */
  PendSV_IRQn             = -2,     /*!< 14 Cortex-M4 Pend SV Interrupt               */
  SysTick_IRQn            = -1,     /*!< 15 Cortex-M4 System Tick Interrupt           */

/******  1986VE8 specific Interrupt Numbers *******************************************/                                       
  FT_RESET0_4_IRQn        = 32,
  FT_EVENT0_4_IRQn        = 33,
  FT_EVENT5_8_IRQn        = 34,
  FT_EVENT9_12_IRQn       = 35,
  CLK_IRQn                = 36,
  POWER_IRQn              = 37,
  RTC_IRQn                = 38,
  BKP_IRQn                = 39,
  EBC_ERROR0_IRQn         = 40,
  EBC_ERROR1_IRQn         = 41,
  EBC_ERROR2_IRQn         = 42,
  EBC_ERROR3_IRQn         = 43,
  EBC_ERROR4_IRQn         = 44,
  EBC_ERROR5_IRQn         = 45,
  EBC_ERROR6_IRQn         = 46,
  EBC_ERROR7_IRQn         = 47,

  DMA_ERR_IRQn            = 50,
  DMA_DONE0_IRQn          = 51,
  DMA_DONE1_IRQn          = 52,
  DMA_DONE2_IRQn          = 53,
  DMA_DONE3_IRQn          = 54,
  DMA_DONE4_IRQn          = 55,
  DMA_DONE5_IRQn          = 56,
  DMA_DONE6_IRQn          = 57,
  DMA_DONE7_IRQn          = 58,
  DMA_DONE8_IRQn          = 59,
  DMA_DONE9_IRQn          = 60,
  DMA_DONE10_IRQn         = 61,
  DMA_DONE11_IRQn         = 62,
  DMA_DONE12_IRQn         = 63,
  DMA_DONE13_IRQn         = 64,
  DMA_DONE14_IRQn         = 65,
  DMA_DONE15_IRQn         = 66,  
  DMA_DONE16_IRQn         = 67,
  DMA_DONE17_IRQn         = 68,
  DMA_DONE18_IRQn         = 69,
  DMA_DONE19_IRQn         = 70,
  DMA_DONE20_IRQn         = 71,
  DMA_DONE21_IRQn         = 72,
  DMA_DONE22_IRQn         = 73,
  DMA_DONE23_IRQn         = 74,
  DMA_DONE24_IRQn         = 75,
  DMA_DONE25_IRQn         = 76,  
  DMA_DONE26_IRQn         = 77,
  DMA_DONE27_IRQn         = 78,
  DMA_DONE28_IRQn         = 79,
  DMA_DONE29_IRQn         = 80,
  DMA_DONE30_IRQn         = 81,
  DMA_DONE31_IRQn         = 82,  
  PORTA_IRQn         	    = 83,
  PORTB_IRQn         	    = 84,
  PORTC_IRQn         	    = 85,
  PORTD_IRQn         	    = 86,
  PORTE_IRQn         	    = 87,

  ETH1_IRQn     	        = 89,
	
  SPW1_IRQn        		    = 91,
  
  TIMER1_IRQn        	    = 93,
  TIMER2_IRQn             = 94,
  TIMER3_IRQn        	    = 95,
  TIMER4_IRQn        	    = 96,
  
  CAN1_IRQn         	    = 99,
  
  SSP1_IRQn         	    = 104,
  
  UART1_IRQn         	    = 108,	
  UART2_IRQn         	    = 109,	
  
  ARINC_RX_IRQn           = 113,
  ARINC_TX_IRQn      	    = 114,	  
  
  MIL1_IRQn               = 117,
  MIL2_IRQn               = 118, 
  ADC1_IRQn         	    = 119,
  ADC2_IRQn         	    = 120,
  DAC1_IRQn         	    = 121,
  DAC2_IRQn         	    = 122,
} IRQn_Type;




/* =========================================================================================================================== */
/* ================                           Processor and Core Peripheral Section                           ================ */
/* =========================================================================================================================== */

/* --------  Configuration of the Cortex-M4 Processor and Core Peripherals  ------- */
#define __CM4_REV                 0x0001U   /* Core revision r0p1 */
#define __MPU_PRESENT             1U        /* MPU present */
#define __VTOR_PRESENT            1U        /* VTOR present */
#define __NVIC_PRIO_BITS          3U        /* Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig    0U        /* Set to 1 if different SysTick Config is used */
#define __FPU_PRESENT             1U        /* FPU present */



/** @} */ /* End of group Configuration_of_CMSIS */


#include <core_cm4.h>                          /*!< Arm Cortex-M4 processor and core peripherals */
#include "system_MDR1986VE8.h"                 /*!< MDR1986VE8 System */


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


#define MDR_KEY_UNLOCK    0x8FFFAAA1UL

/*===============  RST_Clock ===================*/
#include <MDR_RST_VE8_defs.h>

/*===============  BKP ===================*/
#include <MDR_BKP_VE8_defs.h>
#include <MDR_RST_VE8x_defs.h>


/*=========  SSP - Synchronous Serial Port ========*/
#include <MDR_SSP_def.h>

/*=========  UART ========*/
#include <MDR_UART_defs.h>

/*=========  TIMER ========*/
#include <MDR_TimerVE13_defs.h>




/*@}*/ /* end of group MDR1986VE8_Peripherals */


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
#define ADDR_PERIPH_BASE      0x40000000UL                              /*!< (Peripheral) Base Address */

/* Peripheral memory map */

#define ADDR_RST_CLOCK_BASE   0x40000000UL                              /*!< RST_CLOCK Base Address      */
#define ADDR_BKP_BASE         0x40001000UL                              /*!< Backup and RTC Base Address */

#define ADDR_SSP1_BASE        0x40095000UL                              /*!< SSP Base Address      */

#define ADDR_UART1_BASE       0x40099000UL
#define ADDR_UART2_BASE       0x4009A000UL

#define ADDR_TIMER1_BASE      0x4008A000UL
#define ADDR_TIMER2_BASE      0x4008B000UL
#define ADDR_TIMER3_BASE      0x4008C000UL
#define ADDR_TIMER4_BASE      0x4008D000UL


/** @} */ /* End of group Device_Peripheral_peripheralAddr */


/* =========================================================================================================================== */
/* ================                                  Peripheral declaration                                   ================ */
/* =========================================================================================================================== */

/** @addtogroup Device_Peripheral_declaration
  * @{
  */

#define MDR_CLOCK                      ((MDR_RST_CLOCK_Type *) ADDR_RST_CLOCK_BASE)
#define MDR_BKP                        ((MDR_BKP_Type       *) ADDR_BKP_BASE)


#define MDR_SSP1                       ((MDR_SSP_Type       *) ADDR_SSP1_BASE)

#define MDR_UART1                      ((MDR_UART_Type 	    *) ADDR_UART1_BASE)
#define MDR_UART2                      ((MDR_UART_Type 	    *) ADDR_UART2_BASE)

#define MDR_TIMER1                     ((MDR_TIMER_Type 	  *) ADDR_TIMER1_BASE)
#define MDR_TIMER2                     ((MDR_TIMER_Type 	  *) ADDR_TIMER2_BASE)
#define MDR_TIMER3                     ((MDR_TIMER_Type 	  *) ADDR_TIMER3_BASE)
#define MDR_TIMER4                     ((MDR_TIMER_Type 	  *) ADDR_TIMER4_BASE)

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

/* =========================================================================================================================== */
/* ================                                  SPL_Configs                                   ================ */
/* =========================================================================================================================== */

//  Clock Enable bits

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



/** @} */ /* End of group MDR1986VE8 */

/** @} */ /* End of group Milandr */

#ifdef __cplusplus
}
#endif

#endif  /* MDR_1986VE8_H */

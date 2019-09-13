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

typedef enum
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


#define MDR_KEY_UNLOCK    0x8555AAA1UL

/*===============  RST_Clock ===============*/
#include <MDR_RST_VE8x_defs.h>
#include <MDR_RST_VE8_defs.h>

/*===============  BKP =====================*/
#include <MDR_BKP_VE8_defs.h>


/*===============  GPIO Port ===============*/
#include <MDR_GPIO_VE8x_defs.h>

/*===============  OneTimeProgramm (OTP) memory ===============*/
#include <MDR_OTP_VE8_defs.h>

/*=========  SSP - Synchronous Serial Port ========*/
#include <MDR_SSP_def16.h>

/*=========  UART ========*/
#include <MDR_UART_8Bit_defs.h>

/*=========  TIMER ========*/
#include <MDR_TimerVE13_defs.h>

/*=========  DMA ========*/
#include <MDR_DMA_VE8x_defs.h>




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
#define ADDR_PERIPH_BASE      0x40000000UL                              /*!< (Peripheral) Base Address */

/* Peripheral memory map */

#define ADDR_RST_CLOCK_BASE   0x40000000UL                              /*!< RST_CLOCK Base Address      */
#define ADDR_BKP_BASE         0x40001000UL                              /*!< Backup and RTC Base Address */
#define ADDR_OTP_BASE         0x40006000UL

#define ADDR_PORTA_BASE       0x40080000UL                              /*!< GPIO PORT_A Base Address */
#define ADDR_PORTB_BASE       0x40081000UL                              /*!< GPIO PORT_B Base Address */
#define ADDR_PORTC_BASE       0x40082000UL                              /*!< GPIO PORT_C Base Address */
#define ADDR_PORTD_BASE       0x40083000UL                              /*!< GPIO PORT_D Base Address */
#define ADDR_PORTE_BASE       0x40084000UL                              /*!< GPIO PORT_E Base Address */


#define ADDR_SSP1_BASE        0x40095000UL                              /*!< SSP Base Address      */

#define ADDR_UART1_BASE       0x40099000UL
#define ADDR_UART2_BASE       0x4009A000UL

#define ADDR_TIMER1_BASE      0x4008A000UL
#define ADDR_TIMER2_BASE      0x4008B000UL
#define ADDR_TIMER3_BASE      0x4008C000UL
#define ADDR_TIMER4_BASE      0x4008D000UL

#define ADDR_DMA_BASE         0xE0042000UL

/** @} */ /* End of group Device_Peripheral_peripheralAddr */


/* =========================================================================================================================== */
/* ================                                  Peripheral declaration                                   ================ */
/* =========================================================================================================================== */

/** @addtogroup Device_Peripheral_declaration
  * @{
  */

#define MDR_CLOCK                        ((MDR_RST_CLOCK_Type *) ADDR_RST_CLOCK_BASE)

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


#define MDR_OTP                        ((MDR_OTP_Type       *) ADDR_OTP_BASE)
#define MDR_BKP                        ((MDR_BKP_Type       *) ADDR_BKP_BASE)

#define MDR_PORTA                      ((MDR_PORT_Type 	    *) ADDR_PORTA_BASE)
#define MDR_PORTB                      ((MDR_PORT_Type 	    *) ADDR_PORTB_BASE)
#define MDR_PORTC                      ((MDR_PORT_Type 	    *) ADDR_PORTC_BASE)
#define MDR_PORTD                      ((MDR_PORT_Type 	    *) ADDR_PORTD_BASE)
#define MDR_PORTE                      ((MDR_PORT_Type 	    *) ADDR_PORTE_BASE)


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

#define MDR_DMA                        ((MDR_DMA_Type       *)  ADDR_DMA_BASE)

/* =========================================================================================================================== */
/* ================                                  SPL_Configs                                   ================ */
/* =========================================================================================================================== */

//  Clock Enable bits

//----------------    RST Clock Definitions  --------------------
//  Всегда тактируется!
//#define   MDR_CLK_EN_ADDR_RST       &MDR_CLOCK->PER0_CLK
//#define   MDR_CLK_EN_BIT_RST        ---

//----------------    BKP Clock Definitions  --------------------
//  Всегда тактируется!
//#define   MDR_CLK_EN_ADDR_BKP       &MDR_CLOCK->PER0_CLK
//#define   MDR_CLK_EN_BIT_BKP        --- MDR_RST_PER0_PORTA_CLK_EN_Pos


//----------------    PORT Clock Definitions  --------------------
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


 //----------------    SSP Definitions  --------------------
 //  SSP Block Clock enable
 #define   MDR_SSP1_CLK_EN_ADDR          (&MDR_CLOCK->PER1_CLK)
 #define   MDR_SSP2_CLK_EN_ADDR          (&MDR_CLOCK->PER1_CLK)

 #define   MDR_SSP1_CLK_EN_MSK             MDR_RST_PER1_SSP1_CLK_EN_Msk
 #define   MDR_SSP2_CLK_EN_MSK             MDR_RST_PER1_SSP1_CLK_EN_Msk

 //  SSP_Clock freq configs
 #define   MDR_SSP1_CLOCK_GATE_ADDR      (&MDR_CLOCK->SSP1_CLK)
 #define   MDR_SSP2_CLOCK_GATE_ADDR      (&MDR_CLOCK->SSP1_CLK)


 //----------------    UART Definitions  --------------------
 //  UART Block Clock enable
 #define   MDR_UART1_CLK_EN_ADDR         (&MDR_CLOCK->PER1_CLK)
 #define   MDR_UART2_CLK_EN_ADDR         (&MDR_CLOCK->PER1_CLK)

 #define   MDR_UART1_CLK_EN_MSK            MDR_RST_PER1_UART1_CLK_EN_Msk
 #define   MDR_UART2_CLK_EN_MSK            MDR_RST_PER1_UART2_CLK_EN_Msk

 //  UART_ClockGate configs
 #define   MDR_UART1_CLOCK_GATE_ADDR     (&MDR_CLOCK->UART1_CLK)
 #define   MDR_UART2_CLOCK_GATE_ADDR     (&MDR_CLOCK->UART2_CLK)
 

 //----------------    TIMER Definitions  --------------------
 //  UART Block Clock enable
 #define   MDR_TIMER1_CLK_EN_ADDR         (&MDR_CLOCK->PER0_CLK)
 #define   MDR_TIMER2_CLK_EN_ADDR         (&MDR_CLOCK->PER0_CLK)
 #define   MDR_TIMER3_CLK_EN_ADDR         (&MDR_CLOCK->PER0_CLK)
 #define   MDR_TIMER4_CLK_EN_ADDR         (&MDR_CLOCK->PER0_CLK)

 #define   MDR_TIMER1_CLK_EN_MSK            MDR_RST_PER0_TIM1_CLK_EN_Msk
 #define   MDR_TIMER2_CLK_EN_MSK            MDR_RST_PER0_TIM2_CLK_EN_Msk
 #define   MDR_TIMER3_CLK_EN_MSK            MDR_RST_PER0_TIM3_CLK_EN_Msk
 #define   MDR_TIMER4_CLK_EN_MSK            MDR_RST_PER0_TIM4_CLK_EN_Msk


 //  UART_ClockGate configs
 #define   MDR_TIMER1_CLOCK_GATE_ADDR     (&MDR_CLOCK->TIM1_CLK)
 #define   MDR_TIMER2_CLOCK_GATE_ADDR     (&MDR_CLOCK->TIM2_CLK)
 #define   MDR_TIMER3_CLOCK_GATE_ADDR     (&MDR_CLOCK->TIM3_CLK)
 #define   MDR_TIMER4_CLOCK_GATE_ADDR     (&MDR_CLOCK->TIM4_CLK)

// //  Enable Count UpDown by external events
// #define MDR_TIMER_Can_UpDown_ByExtEvents

//----------------    DMA Definitions  --------------------
#define MDR_DMA_CHMUX_LIKE_VE8
#define MDR_DMA_IRQ_LIKE_VE8

//  Block request
#define  MDR_DMA_CH_REQ_SPW1_RX         4
#define  MDR_DMA_CH_REQ_SPW1_TX         6
#define  MDR_DMA_CH_REQ_SSP1_TX        38
#define  MDR_DMA_CH_REQ_SSP1_RX        42
#define  MDR_DMA_CH_REQ_UART1_TX       46
#define  MDR_DMA_CH_REQ_UART2_TX       47
#define  MDR_DMA_CH_REQ_UART1_RX       50
#define  MDR_DMA_CH_REQ_UART2_RX       51
#define  MDR_DMA_CH_REQ_ADC1_REQ5      59
#define  MDR_DMA_CH_REQ_ADC2_REQ5      65
#define  MDR_DMA_CH_REQ_DAC1           66
#define  MDR_DMA_CH_REQ_DAC2           67

//  Single request
#define  MDR_DMA_CH_SREQ_ETH_TX         0
#define  MDR_DMA_CH_SREQ_ETH_RX         1
#define  MDR_DMA_CH_SREQ_SPW1_RX        4
#define  MDR_DMA_CH_SREQ_SPW1_TX        6

#define  MDR_DMA_CH_SREQ_TIM1           8
#define  MDR_DMA_CH_SREQ_TIM2           9
#define  MDR_DMA_CH_SREQ_TIM3          10
#define  MDR_DMA_CH_SREQ_TIM4          11
#define  MDR_DMA_CH_SREQ_TIM1_CH1      14
#define  MDR_DMA_CH_SREQ_TIM2_CH1      15
#define  MDR_DMA_CH_SREQ_TIM3_CH1      16
#define  MDR_DMA_CH_SREQ_TIM4_CH1      17
#define  MDR_DMA_CH_SREQ_TIM1_CH2      20
#define  MDR_DMA_CH_SREQ_TIM2_CH2      21
#define  MDR_DMA_CH_SREQ_TIM3_CH2      22
#define  MDR_DMA_CH_SREQ_TIM4_CH2      23
#define  MDR_DMA_CH_SREQ_TIM1_CH3      26
#define  MDR_DMA_CH_SREQ_TIM2_CH3      27
#define  MDR_DMA_CH_SREQ_TIM3_CH3      28
#define  MDR_DMA_CH_SREQ_TIM4_CH3      29
#define  MDR_DMA_CH_SREQ_TIM1_CH4      32
#define  MDR_DMA_CH_SREQ_TIM2_CH4      33
#define  MDR_DMA_CH_SREQ_TIM3_CH4      34
#define  MDR_DMA_CH_SREQ_TIM4_CH4      35

#define  MDR_DMA_CH_SREQ_SSP1_TX       38
#define  MDR_DMA_CH_SREQ_SSP1_RX       42
#define  MDR_DMA_CH_SREQ_UART1_TX      46
#define  MDR_DMA_CH_SREQ_UART2_TX      47
#define  MDR_DMA_CH_SREQ_UART1_RX      50
#define  MDR_DMA_CH_SREQ_UART2_RX      51

#define  MDR_DMA_CH_SREQ_ADC1_REQ0     54
#define  MDR_DMA_CH_SREQ_ADC1_REQ1     55
#define  MDR_DMA_CH_SREQ_ADC1_REQ2     56
#define  MDR_DMA_CH_SREQ_ADC1_REQ3     57
#define  MDR_DMA_CH_SREQ_ADC1_REQ4     58
#define  MDR_DMA_CH_SREQ_ADC1_REQ5     59

#define  MDR_DMA_CH_SREQ_ADC2_REQ0     60
#define  MDR_DMA_CH_SREQ_ADC2_REQ1     61
#define  MDR_DMA_CH_SREQ_ADC2_REQ2     62
#define  MDR_DMA_CH_SREQ_ADC2_REQ3     63
#define  MDR_DMA_CH_SREQ_ADC2_REQ4     64
#define  MDR_DMA_CH_SREQ_ADC2_REQ5     65

#define  MDR_DMA_CH_SREQ_DAC1          66
#define  MDR_DMA_CH_SREQ_DAC2          67


/** @} */ /* End of group MDR1986VE8 */

/** @} */ /* End of group Milandr */

#ifdef __cplusplus
}
#endif

#endif  /* MDR_1986VE8_H */

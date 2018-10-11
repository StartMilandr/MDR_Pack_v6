/**************************************************************************//**
 * @file     MDR_1901VC1.h
 * @brief    CMSIS Cortex-M3 Core Peripheral Access Layer Header File for
 *           Device MDR1901VC1
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

#ifndef MDR_1901VC1_H
#define MDR_1901VC1_H

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup Milandr
  * @{
  */


/** @addtogroup MDR1901VC1
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
/* =======================================  ARM Cortex-M3 Specific Interrupt Numbers  ======================================== */
  Reset_IRQn                = -15,              /*!< -15  Reset Vector, invoked on Power up and warm reset                     */
  NonMaskableInt_IRQn       = -14,              /*!< -14  Non maskable Interrupt, cannot be stopped or preempted               */
  HardFault_IRQn            = -13,              /*!< -13  Hard Fault, all classes of Fault                                     */
  MemoryManagement_IRQn     = -12,              /*!< -12  Memory Management, MPU mismatch, including Access Violation
                                                          and No Match                                                         */
  BusFault_IRQn             = -11,              /*!< -11  Bus Fault, Pre-Fetch-, Memory Access Fault, other address/memory
                                                          related Fault                                                        */
  UsageFault_IRQn           = -10,              /*!< -10  Usage Fault, i.e. Undef Instruction, Illegal State Transition        */
  SVCall_IRQn               =  -5,              /*!< -5 System Service Call via SVC instruction                                */
  DebugMonitor_IRQn         =  -4,              /*!< -4 Debug Monitor                                                          */
  PendSV_IRQn               =  -2,              /*!< -2 Pendable request for system service                                    */
  SysTick_IRQn              =  -1,              /*!< -1 System Tick Timer                                                      */

/* ===========================================  MDR1901VC1 Specific Interrupt Numbers  ========================================= */
	SSP3_IRQn                 = 0,     /*!< SSP3 Interrupt            */
	SSP4_IRQn                 = 1,     /*!< SSP4  Interrupt           */
	USB_IRQn                  = 2,     /*!< USB Host  Interrupt       */
	DSP_MCBSP1_IRQn           = 3,     /*!< DSP MCBSP1  Interrupt     */
	DSP_MCBSP2_IRQn           = 4,     /*!< DSP MCBSP2  Interrupt     */
	DMA_IRQn                  = 5,     /*!< DMA  Interrupt            */
	UART1_IRQn                = 6,     /*!< UART1  Interrupt          */
	UART2_IRQn                = 7,     /*!< UART2  Interrupt          */
	SSP1_IRQn                 = 8,     /*!< SSP1  Interrupt           */
	DSP_MCBSP3_IRQn           = 9,     /*!< DSP MCBSP3  Interrupt     */
	I2C_IRQn                  = 10,    /*!< I2C  Interrupt            */
	POWER_IRQn                = 11,    /*!< Power Detecor Interrupt   */
	WWDG_IRQn                 = 12,    /*!< Window Watchdog Interrupt */
	DSP_DMA_IRQn              = 13,    /*!< DSP DMA  Interrupt        */
	TIMER1_IRQn               = 14,    /*!< Timer1  Interrupt         */
	TIMER2_IRQn               = 15,    /*!< Timer2  Interrupt         */
	TIMER3_IRQn               = 16,    /*!< Timer3  Interrupt         */
	ADC_IRQn                  = 17,    /*!< ADC  Interrupt            */
	SDIO_IRQn                 = 18,    /*!< SDIO  Interrupt           */
	COMP_IRQn                 = 19,    /*!< Comparator  Interrupt     */
	SSP2_IRQn                 = 20,    /*!< SSP2  Interrupt           */
	DSP_AUC_IRQn              = 21,    /*!< DSP AudioCodec  Interrupt */
	DSP_CRPT_IRQn             = 22,    /*!< DSP CRPT  Interrupt       */
	DSP_TIMER_IRQn            = 23,    /*!< DSP TIMER  Interrupt      */
	DSP_CORE_IRQn             = 24,    /*!< DSP CORE  Interrupt       */
	DSP_STATE_IRQn            = 25,    /*!< DSP STATE  Interrupt      */
	UART3_IRQn                = 26,    /*!< UART3  Interrupt          */
	BKP_IRQn                  = 27,    /*!< Backup and RTC Interrupt  */
	EXT1_IRQn                 = 28,    /*!< EXT_INT1  Interrupt       */
	EXT2_IRQn                 = 29,    /*!< EXT_INT2  Interrupt       */
	EXT3_IRQn                 = 30,    /*!< EXT_INT3  Interrupt       */
	EXT4_IRQn                 = 31     /*!< EXT_INT4  Interrupt       */
} IRQn_Type;



/* =========================================================================================================================== */
/* ================                           Processor and Core Peripheral Section                           ================ */
/* =========================================================================================================================== */

/* ===========================  Configuration of the Arm Cortex-M3 Processor and Core Peripherals  =========================== */
#define __CM3_REV                 0x0102    /*!< Core Revision r2p1 */
#define __MPU_PRESENT             1         /*!< Set to 1 if MPU is present */
#define __VTOR_PRESENT            1         /*!< Set to 1 if VTOR is present */
#define __NVIC_PRIO_BITS          3         /*!< Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig    0         /*!< Set to 1 if different SysTick Config is used */
#define __FPU_PRESENT             0         /*!< Set to 1 if FPU is present */
#define __FPU_DP                  0         /*!< Set to 1 if FPU is double precision FPU (default is single precision FPU) */
#define __ICACHE_PRESENT          0         /*!< Set to 1 if I-Cache is present */
#define __DCACHE_PRESENT          0         /*!< Set to 1 if D-Cache is present */
#define __DTCM_PRESENT            0         /*!< Set to 1 if DTCM is present */


/** @} */ /* End of group Configuration_of_CMSIS */


#include <core_cm3.h>                          /*!< Arm Cortex-M3 processor and core peripherals */
#include "system_MDR1901VC1.h"                 /*!< MDR1901VC1 System */


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


/** @addtogroup Device_Peripheral_peripherals
  * @{
  */

/*===============  RST_Clock ===================*/
#include "MDR_RST_VC1_defs.h"

/*===============  Backup and RST ==============*/
#include "MDR_BKP_VC1_defs.h"

/*===============  GPIO Port ===================*/
#include "MDR_GPIO_defs.h"

#define MDR_PORT_Type  MDR_PORT_Type__Base


/*@}*/ /* end of group MDR1901VC1_Peripherals */


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
#define ADDR_FLASH_BASE       (0x00000000UL)                              /*!< (FLASH     ) Base Address */
#define ADDR_SRAM_BASE        (0x20000000UL)                              /*!< (SRAM      ) Base Address */
#define ADDR_PERIPH_BASE      (0x40000000UL)                              /*!< (Peripheral) Base Address */

/* Peripheral memory map */
#define ADDR_RST_CLOCK_BASE   (0x40020000UL)                              /*!< RST_CLOCK Base Address */
#define ADDR_BKP_BASE         (0x400D8000UL)                              /*!< Backup and RTC Base Address */

#define ADDR_PORTA_BASE       (0x400A8000UL)                              /*!< GPIO PORT_A Base Address */
#define ADDR_PORTB_BASE       (0x400B0000UL)                              /*!< GPIO PORT_B Base Address */
#define ADDR_PORTC_BASE       (0x400B8000UL)                              /*!< GPIO PORT_C Base Address */
#define ADDR_PORTD_BASE       (0x400C0000UL)                              /*!< GPIO PORT_D Base Address */
#define ADDR_PORTE_BASE       (0x400C8000UL)                              /*!< GPIO PORT_E Base Address */
#define ADDR_PORTF_BASE       (0x400E8000UL)                              /*!< GPIO PORT_F Base Address */

/** @} */ /* End of group Device_Peripheral_peripheralAddr */


/* =========================================================================================================================== */
/* ================                                  Peripheral declaration                                   ================ */
/* =========================================================================================================================== */

/** @addtogroup Device_Peripheral_declaration
  * @{
  */

#define MDR_CLOCK                      ((MDR_RST_CLOCK_Type *) ADDR_RST_CLOCK_BASE)
#define MDR_BKP                        ((MDR_BKP_Type   *) ADDR_BKP_BASE)

#define MDR_PORTA                      ((MDR_PORT_Type 	*) ADDR_PORTA_BASE)
#define MDR_PORTB                      ((MDR_PORT_Type 	*) ADDR_PORTB_BASE)
#define MDR_PORTC                      ((MDR_PORT_Type 	*) ADDR_PORTC_BASE)
#define MDR_PORTD                      ((MDR_PORT_Type 	*) ADDR_PORTD_BASE)
#define MDR_PORTE                      ((MDR_PORT_Type 	*) ADDR_PORTE_BASE)
#define MDR_PORTF                      ((MDR_PORT_Type 	*) ADDR_PORTF_BASE)


/* =========================================================================================================================== */
/* ================                                  SPL_Configs                                   ================ */
/* =========================================================================================================================== */

//  Clock Enable bits
#define   MDR_CLK_EN_REG_BKP      PER_CLOCK
#define   MDR_CLK_EN_REG_BKP_b    PER_CLOCK_b

#define   MDR_CLK_EN_ADDR_PORT_A  &MDR_CLOCK->PER_CLOCK
#define   MDR_CLK_EN_ADDR_PORT_B  &MDR_CLOCK->PER_CLOCK
#define   MDR_CLK_EN_ADDR_PORT_C  &MDR_CLOCK->PER_CLOCK
#define   MDR_CLK_EN_ADDR_PORT_D  &MDR_CLOCK->PER_CLOCK
#define   MDR_CLK_EN_ADDR_PORT_E  &MDR_CLOCK->PER_CLOCK
#define   MDR_CLK_EN_ADDR_PORT_F  &MDR_CLOCK->PER_CLOCK

#define   MDR_CLK_EN_BIT_PORT_A   MDR_RST_PER__PORTA_CLK_EN_Pos
#define   MDR_CLK_EN_BIT_PORT_B   MDR_RST_PER__PORTB_CLK_EN_Pos
#define   MDR_CLK_EN_BIT_PORT_C   MDR_RST_PER__PORTC_CLK_EN_Pos
#define   MDR_CLK_EN_BIT_PORT_D   MDR_RST_PER__PORTD_CLK_EN_Pos
#define   MDR_CLK_EN_BIT_PORT_E   MDR_RST_PER__PORTE_CLK_EN_Pos
#define   MDR_CLK_EN_BIT_PORT_F   MDR_RST_PER__PORTF_CLK_EN_Pos

#define   MDR_JTAG_A_PORT         MDR_PORTB
#define   MDR_JTAG_A_PINS         0x0000001FUL
#define   MDR_JTAG_A_PINS_FUNC    0x000003FFUL
#define   MDR_JTAG_A_PINS_PD      0x001F001FUL

#define   MDR_JTAG_B_PORT         MDR_PORTD
#define   MDR_JTAG_B_PINS         0x0000001FUL
#define   MDR_JTAG_B_PINS_FUNC    0x000003FFUL
#define   MDR_JTAG_B_PINS_PD      0x001F001FUL


/** @} */ /* End of group MDR1901VC1 */

/** @} */ /* End of group Milandr */

#ifdef __cplusplus
}
#endif

#endif  /* MDR_1901VC1_H */
